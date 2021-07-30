;;#############################################################################
;;! \file source/CFFT32_mag.asm
;;!
;;! \brief  Magnitude function for the complex FFT
;;!
;;! \date   Nov 2, 2010
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
;;
;;*****************************************************************************
;; includes
;;*****************************************************************************
;;
;;*****************************************************************************
;; globals
;;*****************************************************************************
    ; Module definition for external reference
    .def      _CFFT32_mag

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
;;=============================================================================
;; Routine Type  : C Callable        
;; Description   :
;; void CFFT32_mag(CFFT32_Handle) 
;; This function computes the magnitude square of complex FFT outputs. Allows in-place
;; and off-place storage of the magnitude square results.
;; 

_CFFT32_mag:
    SETC      SXM
              
    MOVL      XAR7,*XAR4      ; XAR5=ipcbptr
    MOVL      XAR6,*+XAR4[6]  ; XAR6=magptr
              
    MOVZ      AR0,*+XAR4[4]   ; AR7=size
    SUBB      XAR0,#1         ; AR0=size-1
    
MAG_LP:     
    ZAPA                      ; ACC=0, P=0
    QMACL     P,*XAR7,*XAR7++ ; Q15*Q15=Q30
    QMACL     P,*XAR7,*XAR7++ ; Q15*Q15+Q30=Q30
    ADDL      ACC,P
    MOVL      *XAR6++,ACC     ; Store in Q30
    BANZ      MAG_LP,AR0--
            
; Find maximum magnitude
    ADDB      XAR4,#4         ; XAR4->size
    MOVB      ACC,#0
    MOVL      *+XAR4[6],ACC   ; peakmag=0
    MOVZ      AR0,*XAR4       ; AR0=size
    MOVL      XAR5,*+XAR4[2]  ; XAR5=magptr
              
    MOV       ACC,#0
    SUBB      XAR0,#1         ; AR0=size-1
            
;Find the maximum value among the FFT Magnitudes    
    RPT       AR0
 || MAXL      ACC,*XAR5++
              
    MOVL      *+XAR4[6],ACC   ; update peak magnitude
    MOVB      XAR7,#0         ; XAR7=0
    MOVL      XAR5,*+XAR4[2]  ; XAR5=magptr
;Find the spectral bin corresponding to maximum magnitude.  
NEXT_BIN:               
    MAXL      ACC,*XAR5++
    NOP       *XAR7++
    SBF       NEXT_BIN,NEQ    
              
    NOP       *--XAR7
    ADDB      XAR4,#8         ; XAR4->peakfrq
    MOV       *XAR4,AR7       ; update peak magnitude     
    LRETR      
    
;;#############################################################################
;;  End of File
;;#############################################################################
