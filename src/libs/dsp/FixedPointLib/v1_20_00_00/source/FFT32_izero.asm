;;#############################################################################
;;! \file source/FFT32_izero.asm
;;!
;;! \brief  Zero out the imaginary part of the complex input to the FFT
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
    .def      _FFT32_izero

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
;;=============================================================================
;; Routine Type  : C Callable        
;; Description   :
;; void FFT32_izero(CFFT32_handle) 
;; This function zeros the imaginary part of the complex input, in the case of 
;; Complex FFT modules.
;; 

           
_FFT32_izero:            
; Fill the imaginary part of the samples with ZERO 
    MOVL      XAR5,*XAR4      ; XAR5=ipcbptr
    MOV       ACC,*+XAR4[4]   ; ACC=size
    SUBB      ACC,#1          ; AL=size-1
                              
    MOVL      XAR6,XAR5       ; XAR6=ipcbptr
                              
    ADDB      XAR5,#2         ; XAR5=ipcbptr+2
    ADDB      XAR6,#3         ; XAR5=ipcbptr+3
    MOVB      XAR0,#4         ; XAR0=0
                              
    NOP       *,ARP5          
    RPT       AL              
 || MOV       *0++,#0         ; Clear MSW of imaginary part
                              
    NOP       *,ARP6          
    RPT       AL              
 || MOV       *0++,#0         ; Clear LSW of imaginart part
                
    LRETR 
;;#############################################################################
;;  End of File
;;#############################################################################
