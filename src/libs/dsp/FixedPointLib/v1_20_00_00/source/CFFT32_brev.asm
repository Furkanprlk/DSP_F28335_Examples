;;#############################################################################
;;! \file source/CFFT32_brev.asm
;;!
;;! \brief  Bit Reversal routine for the complex 32-bit FFT
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
                .def _CFFT32_brev
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
;;============================================================================== 
;; \fn  void CFFT32_brev(int32_t *src, int32_t *dst, uint16_t size)
;; \brief Bit Reversal routine for the complex 32-bit FFT
;;
;; This function bit reverses the N-point real sequence stored in 
;; alternate memory locations, that is, 
;; src(0)    = x(0)    | src(1)    = 0
;; src(2)    = x(1)    | src(3)    = 0
;; ...                 | ...         
;; src(2N-2) = x(N-1)  | src(2N-1) = 0 
;; If src=dst, then in-place bit reversal is performed.
;; The destination array should be aligned to 2N long words, where N is the size
;; of the complex FFT. 
;;
;; \param src (XAR4) pointer to the source array or buffer
;; \param dst (XAR5) pointer to the destination array or buffer
;; \param size(  AL) size of the buffer (must be a power of 2)
;;============================================================================== 
;;
_CFFT32_brev:  
                                   ; XAR4->src, XAR5->dst, AL=size
    MOVL      XAR0,XAR4            ; XAR0->src
    NOP       *,ARP5               
                                   
    CMPR      0                    ; TC=1, if src==dst
    BF        off_place,NTC        ; If not equal, jump to off place bit rev
                                   
; IN-PLACE BIT-REVERSAL            
in_place:                          
    MOVZ      AR7,AL               ; AR0=size
    SUBB      XAR7,#1              ; XAR7=size-1
    LSL       ACC,#1               ; ACC=2*size
    MOVZ      AR6,AL               ; AR0=2*size
                                   
next_data1:                        
    MOVL      XT,*XAR4             ; XT=*src
    MOVL      P,*XAR5              ; P=*dst
    MOVL      XAR0,XAR4            ; XAR0=src
    CMPR      2                    ; check src<dst
    BF        noswap,TC            ; if src<dst, do not swap *src & *dst
                                   
    MOVL      *XAR4,P              ; *src=*dst
    MOVL      *XAR5,XT             ; *dst=*src
                                   
noswap:                            
    ADDB      XAR4,#4              ; XAR4=src+2
    MOVZ      AR0,AR6              ; AR0=2*size
    NOP       *BR0++               ; dst=br(dst+2*size)
    BANZ      next_data1,AR7--     ; ARP=AR3, AR3->src+2, AR7=AR7-1
    LRETR                          
                                   
; OFF-PLACE BIT-REVERSAL                 
off_place:                         
    MOVZ      AR7,AL               ; AR0=size
    SUBB      XAR7,#1              ; XAR7=size-1
    LSL       ACC,#1               ; ACC=2*size
    MOVZ      AR0,AL               ; AR0=2*size
                                   
next_data2:                        
    MOVL      ACC,*XAR4++          ; XAR4=src+1, ACCL=*src
    ADDB      XAR4,#2              ; XAR4=src+2
    NOP       *,ARP5               ; ARP=XAR5
    MOVL      *BR0++,ACC           ; XAR5=br(dst+size)
    BANZ      next_data2,AR7--                 
    LRETR

;;#############################################################################
;;  End of File
;;#############################################################################
