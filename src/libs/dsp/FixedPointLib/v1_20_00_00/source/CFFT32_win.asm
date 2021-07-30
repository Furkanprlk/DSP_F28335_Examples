;;#############################################################################
;;! \file source/CFFT32_win.asm
;;!
;;! \brief  Complex FFT Windowing Function
;;!
;;! \date   Jan 11, 2010
;;!
;;
;;  Group:            C2000
;;  Target Family:    C28x
;;
;; (C)Copyright 2014, Texas Instruments, Inc.
;;#############################################################################
;;$TI Release: C28x Fixed Point DSP Library V1.20.00.00 $
;;$Release Date: Oct 23, 2014 $
;;#############################################################################
;;
;;*****************************************************************************
;; includes
;;*****************************************************************************
;;
;;*****************************************************************************
;; globals
;;*****************************************************************************
    ; Module definition for external reference
    .def      _CFFT32_win
    .def      _CFFT32_win_dual

;; Module Structure
;; typedef struct { <--------- XAR4
;;     int32_t *ipcbptr;      /* +0  Pointer to input buffer              */
;;     int32_t *tfptr         /* +2  Pointer to twiddle factors           */
;;     int16_t size;          /* +4  Size of the FFT                      */
;;     int16_t nrstage;       /* +5  Number of FFT stages (log2(size))    */
;;     int16_t *magptr;       /* +6  Pointer to the magnitude buffer      */
;;     int16_t *winptr;       /* +8  Pointer to the sampling window       */
;;     int16_t peakmag;       /* +10 Peak magnitude value                 */
;;     int16_t peakfrq;       /* +11 Peak Frequency                       */
;;     int16_t ratio;         /* +12 Twiddles Skip factor                 */
;;     void (*init)(void);    /* +14 Pointer to the initialization ()     */
;;     void (*izero)(void *); /* +16 Pointer to the zero-out imaginary () */
;;     void (*calc)(void *);  /* +18 Pointer to the calculation ()        */
;;     void (*mag)(void *);   /* +20 Pointer to the magnitude ()          */
;;     void (*win)(void *);   /* +22 Pointer to the windowing ()          */
;;}CFFT32;
;;
ARG_IPCBPTR   .set    0
ARG_TFPTR     .set    0
ARG_SIZE      .set    2
ARG_NRSTAGE   .set    3
ARG_MAGPTR    .set    4
ARG_WINPTR    .set    6
ARG_PEAKMAG   .set    8
ARG_PEAKFREQ  .set    9
ARG_RATIO     .set    10

;;
;;=============================================================================
;;! \fn CFFT32_win
;;! \brief Complex FFT Windowing Function
;;! \param CFFT32_handle pointer to an CFFT32 object
;;
;; This function applies a window to an N-point real data (imaginary portion 
;; zeroed out) sequence that has already been stored in bit-reversed format in the 
;; location pointed to by "ipcbptr". It is to be used with the complex FFT module
;;
;; For an N-pt complex FFT, the stored windows are of size N/2 (they are symmetrical).
;; This routine will apply the window in two steps
;;
;; Step 1: Forward walk through win
;;	Loop for i = 0 to N/2 - 1 {
;;      p -> ipcbptr,  q -> win
;;      a = *p (Q31) , b = *q (Q31)
;;      n = sizeof(ipcbptr) = 2(32-bit wide)*N
;;		temp = ((a x b) >> 32)
;;           = ((A * 2^31 x B * 2^31) x 2^-32) where A and B are the unscaled decimal values
;;           = A x B x 2^30 (Q30)
;;      temp = temp << 1    (Q31)
;;      *p   = temp
;;      p    = p rcadd n (this is the bit reversed address)
;;      q    = q + 1
;;     }
;;
;; Step 2: Backward walk through win
;;	Loop for i = N/2 to N - 1 {
;;      p -> ipcbptr(from the last step),  q -> win(N/2)
;;      a = *p (Q31) , b = *q (Q31)
;;		temp = (A x B x 2^30) << 1 (Q31)
;;      *p   = temp
;;      p    = p rcadd n (this is the bit reversed address)
;;      q    = q - 1
;;     }
;;=============================================================================
;; 
_CFFT32_win:
    MOVL      XAR5,*XAR4++               ; XAR5 = ipcbptr
    MOVL      XAR6,*+XAR4[ARG_WINPTR]    ; XAR6 = winptr
    MOV       ACC,*+XAR4[ARG_SIZE]<<15   ; AH   = size/2
    MOVH      AR0,ACC<<2                 ; AR0  = 2(complex)*size
    MOVZ      AR7,AH                     ; AR7  = (size/2)                                  
    SUBB      XAR7,#1                    ; AR7  = (size/2)-1
    MOVL      XAR4,XAR7                  ; AR4  = (size/2)-1
            
nextsamp1:  
    MOVL      XT,*XAR6++                 ; XT   = win[i]         | i++
    QMPYL     ACC,XT,*XAR5               ; ACC  = (signed XT * signed [*XAR5]) >> 32
                                         ; ARP  = 5 (i.e. XAR5)
    LSL       ACC,#1                     ; ACC  = ACC * 2
    MOVL      *BR0++,ACC                 ; *XAR5 = ACC | AR5L = AR5L rcadd AR0
    BANZ      nextsamp1,AR7--           
                                         ; At the end of this loop, XAR6 points to the
                                         ; N/2 th element of the real input
nextsamp2:  
    MOVL      XT,*--XAR6                 ; XT   = win[i]         | i--
    QMPYL     ACC,XT,*XAR5               ; ACC  = (signed XT * signed [*XAR5]) >> 32
                                         ; ARP  = 5 (i.e. XAR5)
    LSL       ACC,#1                     ; ACC  = ACC * 2
    MOVL      *BR0++,ACC                 ; *XAR5 = ACC | AR5L = AR5L rcadd AR0
    BANZ      nextsamp2,AR4--
    LRETR
    
;;
;;=============================================================================
;;! \fn _CFFT32_win_dual
;;! \brief Complex FFT Windowing Function (both real and imaginary parts)
;;! \param CFFT32_handle pointer to an CFFT32 object
;;
;; This function applies a window to an N-point complex data sequence
;; that has already been stored in bit-reversed format in the location pointed
;; to by "ipcbptr". It is to be used with the complex FFT module
;;
;; For an N-pt complex FFT, the stored windows are of size N/2 (they are symmetrical).
;; This routine will apply the window in two steps
;;
;; Step 1: Forward walk through win
;;	Loop for i = 0 to N/2 - 1 {
;;      p -> ipcbptr,  q -> win
;;      a = *p (Q31) , b = *q (Q31)
;;      c = *(p+1) (Q31), d = *q(Q31)
;;      n = sizeof(ipcbptr) = 2(32-bit wide)*N
;;		temp1 = ((a x b) >> 32)
;;            = ((A * 2^31 x B * 2^31) x 2^-32) where A and B are the unscaled decimal values
;;            = A x B x 2^30 (Q30)
;;		temp2 = ((c x d) >> 32)
;;            = ((C * 2^31 x D * 2^31) x 2^-32) where C and D are the unscaled decimal values
;;            = C x D x 2^30 (Q30)
;;      temp1 = temp1 << 1    (Q31)
;;      temp2 = temp2 << 1    (Q31)
;;      *p   = temp1 , *(p+1) = temp2
;;      p    = p rcadd n (this is the bit reversed address)
;;      q    = q + 1
;;     }
;;
;; Step 2: Backward walk through win
;;	Loop for i = N/2 to N - 1 {
;;      p -> ipcbptr(from the last step),  q -> win(N/2)
;;      a = *p (Q31) , b = *q (Q31)
;;      c = *(p+1) (Q31), d = *q(Q31)
;;		temp1 = (A x B x 2^30) << 1 (Q31)
;;		temp2 = (C x D x 2^30) << 1 (Q31)
;;      *p   = temp1 , *(p+1) = temp2
;;      p    = p rcadd n (this is the bit reversed address)
;;      q    = q - 1
;;     }
;;=============================================================================
;; 
_CFFT32_win_dual:
    MOVL      XAR5,*XAR4++                       ; XAR5 = ipcbptr
    MOVL      XAR6,*+XAR4[ARG_WINPTR]            ; XAR6 = winptr
    MOV       ACC,*+XAR4[ARG_SIZE]<<15           ; AH   = size'/2
    MOVH      AR0,ACC<<2                         ; AR0  = 2(complex)*size'
    MOVZ      AR7,AH                             ; AR7  = (size'/2)                                  
    SUBB      XAR7,#1                            ; AR7  = (size'/2)-1
    MOVL      XAR4,XAR7                          ; AR4  = (size'/2)-1
            
nextsample1:
    MOVL      XT,*+XAR6[0]                       ; XT   = win[i]
    QMPYL     ACC,XT,*XAR5                       ; ACC  = (signed XT * signed [*XAR5.real]) >> 32
                                                 ; ARP  = 5 (i.e. XAR5)
    LSL       ACC,#1                             ; ACC  = ACC * 2
    MOVL      *XAR5, ACC                         ; *XAR5.real = ACC
    
    MOVL      XT,*XAR6++                         ; XT   = win[i]         | i++
    QMPYL     ACC,XT,*+XAR5[2]                   ; ACC  = (signed XT * signed [*XAR5.imag]) >> 32
                                                 ; ARP  = 5 (i.e. XAR5)
    LSL       ACC,#1                             ; ACC  = ACC * 2
    MOVL      *+XAR5[2], ACC                     ; *XAR5.imag = ACC
    NOP       *BR0++                             ; AR5L = AR5L rcadd AR0
    BANZ      nextsample1,AR7--
                                                 ; At the end of this loop, XAR6 points to the
                                                 ; N/2 th element of the real input
nextsample2:
    MOVL      XT,*--XAR6                         ; XT   = win[i]
    QMPYL     ACC,XT,*XAR5                       ; ACC  = (signed XT * signed [*XAR5.real]) >> 32
                                                 ; ARP  = 5 (i.e. XAR5)
    LSL       ACC,#1                             ; ACC  = ACC * 2
    MOVL      *XAR5, ACC                         ; *XAR5.real = ACC
    
    MOVL      XT,*+XAR6[0]                       ; XT   = win[i]         | i--
    QMPYL     ACC,XT,*+XAR5[2]                   ; ACC  = (signed XT * signed [*XAR5.imag]) >> 32
                                                 ; ARP  = 5 (i.e. XAR5)
    LSL       ACC,#1                             ; ACC  = ACC * 2
    MOVL      *+XAR5[2], ACC                     ; *XAR5.imag = ACC
    NOP       *BR0++                             ; AR5L = AR5L rcadd AR0
    BANZ      nextsample2,AR4--
    LRETR
;;#############################################################################
;;  End of File
;;#############################################################################

