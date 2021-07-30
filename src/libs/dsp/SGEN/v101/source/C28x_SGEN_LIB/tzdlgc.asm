; ========================================================================
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
;                          All Rights Reserved.
;=========================================================================
;********************************************************************************
; File name     : TZDLGC.ASM                                         
; 
; Originator    : Advanced Embeeded Control (AEC)
;                 Texas Instruments Inc.
; 
; Description   : This module generates trapezoidal output
;               
; Routine Type  : "CcA Only"
;                               
; Date          : 28/12/2001 (DD/MM/YYYY)
;********************************************************************************
; Routine Name: trapgen_calc                                       
;  
; C prototype : void TZDLGEN_calc(TZDLGEN *p);
;             : void TZDLGEN_init(TZDLGEN *P);
;
; The struct object is defined in the header file "sgen.h" as follows:
;
; typedef struct {int skip_cntr;
;                 int prescalar;
;                 int freq;
;                 int step_max;
;                 long task;
;                 int alpha;
;                 int gain;
;                 int offset;
;                 int out;
;                } TZDLGEN;             
;
;********************************************************************************
; ###########################################################################
; $TI Release: C28x SGEN Library Version v1.01 $
; $Release Date: September 30, 2011 $
; ###########################################################################

        .def        _TZDLGEN_calc
        .def        _TZDLGEN_init

;********************************************************************************
;************************ Initialisation Function *******************************
;********************************************************************************

_TZDLGEN_init:
        MOV     *XAR4,#0            ; XAR4->skip_cntr=0
        MOVL    XAR5,#TZDL_MIN
        MOVL    *+XAR4[4],XAR5      ; task=TZDL_MIN
        MOV     *+XAR4[6],#8000h    ; alpha=0x8000
        ADDB    XAR4,#9             ; XAR4->out
        MOV     *XAR4,#0            ; out=0
        LRETR
            
;********************************************************************************
;************************ Computation Function **********************************
;********************************************************************************

_TZDLGEN_calc:
        SETC    SXM,OVM
        
        INC     *XAR4               ; XAR4->skip_cntr=skip_cntr+1
        MOV     ACC,*XAR4           ; ACC=skip_cntr
        SUB     ACC,*+XAR4[1]       ; ACC=skip_cntr-prescalar
        BF      TZDL_EXIT,LT        ; if (skip_cntr+1) < prescalar, then exit
        
        MOV     *XAR4,#0            ; skip_cntr=0 
                

; Obtain the step value in pro-rata with the freq input         
        MOV     T,*+XAR4[2]         ; T=freq
        MPY     ACC,T,*+XAR4[3]     ; ACC=step=freq*step_max (Q15)
        MOVH    PL,ACC<<1           ; PL=freq*step_max (Q0)

; Increment the angle "alpha" by step value   
        MOVU    ACC,*+XAR4[6]       ; ACC=alpha    
        ADDU    ACC,PL     
        MOV     *+XAR4[6],AL        ; alpha=alpha+step
        MOV     T,#0FFFFh
        SUBU    ACC,T               ; alpha=alpha-FFFFh
                     
        MOVL    XAR7,*+XAR4[4]      ; XAR7=task
        ADDB    XAR4,#4             ; XAR4->task
        LB      *XAR7               ; Brach to Task

;--------------------------------------------------------------------------------
; Minimum value Task
;--------------------------------------------------------------------------------
TZDL_MIN:      
        BF      MIN,LT
        MOVL    XAR5,#TZDL_INCR
        MOVL    *XAR4,XAR5          ; task=TZDL_INCR
        BF      POS_RAMP,UNC
        
MIN:
        MOV     T,#8000h
        
        MPY     ACC,T,*+XAR4[3]     ; ACC=Y*gain(Q30)
        LSL     ACC,#1              ; ACC=Y*gain (Q31)
        ADD     ACC,*+XAR4[4]<<16   ; ACC=Y*gain+offset
        MOV     *+XAR4[5],AH        ; out=Y*gain+offset
        CLRC 	OVM
        LRETR
            

;--------------------------------------------------------------------------------
; Positive Ramp Task    
;--------------------------------------------------------------------------------
TZDL_INCR:       
        BF      POS_RAMP,LT
        MOVL    XAR5,#TZDL_MAX
        MOVL    *XAR4,XAR5          ; task=TZDL_MAX
        BF      MAX,UNC  
        
POS_RAMP:
        MOV     ACC,#08000h
        MOV     T,*+XAR4[2]         ; T=alpha
        SUB     T,AL                ; T=alpha-8000h

        MPY     ACC,T,*+XAR4[3]     ; ACC=Y*gain(Q30)
        LSL     ACC,#1              ; ACC=Y*gain (Q31)
        ADD     ACC,*+XAR4[4]<<16   ; ACC=Y*gain+offset
        MOV     *+XAR4[5],AH        ; out=Y*gain+offset
        CLRC 	OVM
        LRETR

;--------------------------------------------------------------------------------
; Maximum value Task
;--------------------------------------------------------------------------------
TZDL_MAX:
; Increment the angle "alpha" by step value         
        BF      MAX,LT
        MOVL    XAR5,#TZDL_DECR
        MOVL    *XAR4,XAR5          ; task=TZDL_MIN
        BF       NEG_RAMP,UNC
        
MAX:
        MOV     T,#7FFFh
        
        MPY     ACC,T,*+XAR4[3]     ; ACC=Y*gain(Q30)
        LSL     ACC,#1              ; ACC=Y*gain (Q31)
        ADD     ACC,*+XAR4[4]<<16   ; ACC=Y*gain+offset
        MOV     *+XAR4[5],AH        ; out=Y*gain+offset
        CLRC 	OVM
        LRETR

;--------------------------------------------------------------------------------
; Negative Ramp Task    
;--------------------------------------------------------------------------------
TZDL_DECR:
        BF      NEG_RAMP,LT
        MOVL    XAR5,#TZDL_MIN
        MOVL    *XAR4,XAR5          ; task=TZDL_MIN
        BF      MIN,UNC
        
NEG_RAMP:
        MOV     ACC,#7FFFh
        SUB     ACC,*+XAR4[2]       ; ACC=0x7fff-alpha
        MOV     T,AL                ; T=0x7fff-alpha

        MPY     ACC,T,*+XAR4[3]     ; ACC=Y*gain(Q30)
        LSL     ACC,#1              ; ACC=Y*gain (Q31)
        ADD     ACC,*+XAR4[4]<<16   ; ACC=Y*gain+offset
        MOV     *+XAR4[5],AH        ; out=Y*gain+offset
        CLRC 	OVM
        LRETR

;--------------------------------------------------------------------------------
; Return  
;--------------------------------------------------------------------------------
TZDL_EXIT:
        CLRC 	OVM
        LRETR

