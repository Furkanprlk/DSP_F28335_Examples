;;#############################################################################
;;! \file source/RFFT32_win.asm
;;!
;;! \brief  Real FFT Windowing Function
;;!
;;! \date   Apr 26, 2001
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
 	.def      _RFFT32_win

;; Module Structure
;; typedef struct { <------------- XAR4
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
;;     void (*calc)(void *);  /* +16 Pointer to the calculation ()        */
;;     void (*split)(void *); /* +18 Pointer to the split(0               */
;;     void (*mag)(void *);   /* +20 Pointer to the magnitude ()          */
;;     void (*win)(void *);   /* +22 Pointer to the windowing ()          */
;; }RFFT32;
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
;;! \fn RFFT32_win
;;! \brief Real FFT Windowing Function
;;! \param RFFT32_Handle pointer to an RFFT32 object
;;
;; This function windows a 2N-point real valued data sequence stored as an 
;; N point complex sequence in bit-reversed format in the location pointed
;; to by "ipcbptr". It is to be used with the real FFT module
;;
;; A 2N-pt real FFT is carried out by first doing an N point complex FFT followed
;; by post processing (unwrapping) to get the correct answer. The windows are of 
;; size N/2 (they are symmetrical).
;;
;; This routine will apply the window in two steps
;;
;; Step 1: Forward walk through win
;;	Loop for i = 0 to N/2 - 1 {
;;      p -> ipcbptr,  q -> win
;;      a = *p (Q31) , b = *q (Q31)
;;      c = *(p+1) (Q31), d = *(q+1)(Q31)
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
;;      c = *(p+1) (Q31), d = *(q+1)(Q31)
;;		temp1 = (A x B x 2^30) << 1 (Q31)
;;		temp2 = (C x D x 2^30) << 1 (Q31)
;;      *p   = temp1 , *(p+1) = temp2
;;      p    = p rcadd n (this is the bit reversed address)
;;      q    = q - 1
;;     }
;;=============================================================================
;; 
_RFFT32_win:
    ; size -> size of RFFT i.e. 2N-point
    ; size'-> size of CFFT used to get the RFFT i.e. N-point
    ; The structure element "size" should be the size of the CFFT i.e. N
    MOVL      XAR5,*XAR4++                       ; XAR5 = ipcbptr
    MOVL      XAR6,*+XAR4[ARG_WINPTR]            ; XAR6 = winptr
    MOV       ACC,*+XAR4[ARG_SIZE]<<15           ; AH   = size'/2
    MOVH      AR0,ACC<<2                         ; AR0  = 2(complex)*size'
    MOVZ      AR7,AH                             ; AR7  = (size'/2)                                  
    SUBB      XAR7,#1                            ; AR7  = (size'/2)-1
    MOVL      XAR4,XAR7                          ; AR4  = (size'/2)-1
            
nextsamp1:  
    MOVL      XT,*XAR6++                         ; XT   = win[i]         | i++
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
    BANZ      nextsamp1,AR7--           
                                                 ; At the end of this loop, XAR6 points to the
                                                 ; N/2 th element of the real input
nextsamp2:  
    MOVL      XT,*--XAR6                         ; XT   = win[i]         | i--
    QMPYL     ACC,XT,*XAR5                       ; ACC  = (signed XT * signed [*XAR5.real]) >> 32
                                                 ; ARP  = 5 (i.e. XAR5)
    LSL       ACC,#1                             ; ACC  = ACC * 2
    MOVL      *XAR5, ACC                         ; *XAR5.real = ACC
    
    MOVL      XT,*--XAR6                         ; XT   = win[i]         | i--
    QMPYL     ACC,XT,*+XAR5[2]                   ; ACC  = (signed XT * signed [*XAR5.imag]) >> 32
                                                 ; ARP  = 5 (i.e. XAR5)
    LSL       ACC,#1                             ; ACC  = ACC * 2
    MOVL      *+XAR5[2], ACC                     ; *XAR5.imag = ACC
    NOP       *BR0++                             ; AR5L = AR5L rcadd AR0
    BANZ      nextsamp2,AR4--
    LRETR

;;#############################################################################
;;  End of File
;;#############################################################################
