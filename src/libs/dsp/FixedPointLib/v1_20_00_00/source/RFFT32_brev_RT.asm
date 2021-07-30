;;;#############################################################################
;;! \file source/RFFT32_brev_RT.asm
;;!
;;! \brief  Real-Time storage of acquired data samples in bit reversed order
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
            .def    _RFFT32_brev_RT   
;;==============================================================================   
;; Routine Type  : C Callable        
;; Description   :
;; void RFFT32_brev_RT(RFFT32_Handle) 
;; This function acquires N samples in bit-reversed order to cater to the complex
;; FFT computation. The buffer should be aligned to 2N words
;;==============================================================================  
;; typedef struct{<------------ XAR4
;;  int16_t acqflag;             // + 0  Acquisition flag
;;  int16_t count;               // + 1  Integer counter
;;  int32_t input;               // + 2  Input data
;;  int32_t *tempptr;            // + 4  Temporary Pointer
;;  int32_t *buffptr;            // + 6  Pointer to the destination buffer
;;  int16_t size;                // + 7  Number of samples
;;  void (*update)(void *);      // + 8  Pointer to the update function
;; }RFFT32_brev_RT_ACQ;  
;;==============================================================================  
;;
                
_RFFT32_brev_RT:  
    MOV       ACC,*XAR4++       ; ACC=acqflag
    SBF       noacq,EQ  
                            
    MOV       ACC,*XAR4++       ; ACC=count
    SBF       acqover,EQ        ; if count=0, acquisition is complete
                
    DEC       *--XAR4           ; count=count-1
    MOV       ACC,*+XAR4[7]<<1  ; ACC=2*size
    MOVL      XAR0,ACC          ; AR0=2*size            
                
    MOVL      XAR5,*+XAR4[3]    ; XAR5=tempptr
    MOVL      ACC,*+XAR4[1]     ; ACC=input
    MOVL      *XAR5,ACC         ; *tempptr=input
    NOP       *BR0++    
    MOVL      *+XAR4[3],XAR5    
noacq:          
    LRETR       
                
acqover:        
    MOV       ACC,*+XAR4[6] 
    MOV       *--XAR4,ACC       ; count=size
    MOV       *--XAR4,#0        ; acqflag=0
                
    MOVL      XAR5,*+XAR4[6]    ; XAR5=buffptr
    MOVL      *+XAR4[4],XAR5    ; tempptr=buffptr
    LRETR

;;#############################################################################
;;  End of File
;;#############################################################################
