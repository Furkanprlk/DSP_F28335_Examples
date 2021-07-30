; ========================================================================
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
;                          All Rights Reserved.
;=========================================================================
;======================================================================
;
; File Name     : SGT2C.ASM
; 
; Originator    : Advanced Embeeded Control (AEC)
;                Texas Instruments Inc.
; 
; Description   : This file contain source code for dual channel
;                 SIN generator module(Using Direct Table look-up)
;                 * Direct Table look-up implementation provides, Standard
;                 THD and Standard phase Resolution
;               
; Routine Type  : CcA
;
; Date          : 27/12/2001 (DD/MM/YYYY)
;======================================================================
; Description:
;                            ___________________
;                           |                   |
;        gain   o---------->|                   |------o OUT1
;        offset o---------->|       SGENT_2     |
;        freq   o---------->|                   |------o OUT2
;                           |___________________|
;
;======================================================================
; ###########################################################################
; $TI Release: C28x SGEN Library Version v1.01 $
; $Release Date: September 30, 2011 $
; ###########################################################################
;======================================================================

; Module definition for external referance
                .def    _SGENT_2_calc      
                .ref    SINTAB_360

_SGENT_2_calc:      
            SETC    SXM,OVM         ; XAR4->freq
                            
; Obtain the step value in pro-rata with the freq input         
            MOV     T,*XAR4++       ; XAR4->step_max, T=freq
            MPY     ACC,T,*XAR4++   ; XAR4->alpha, ACC=freq*step_max (Q15)
            MOVH    AL,ACC<<1           
            
; Increment the angle "alpha" by step value             
            ADD     AL,*XAR4        ; AL=(freq*step_max)+alpha  (Q0)
            MOV     *XAR4,AL        ; XAR4->alpha, alpha=alpha+step (Unsigned 8.8 format)   

; OUT1 Computation
; Obtain the SIN of the angle "X=alpha" using direct Look-up Table            
            MOVL    XAR5,#SINTAB_360
            MOVB    XAR0,#0         
            MOVB    AR0,AL.MSB      ; AR0=indice (alpha/2^8)
            MOV     T,*+XAR5[AR0]   ; T=Y=*(SINTAB_360 + indice)
        
            MPY     ACC,T,*+XAR4[1] 
            LSL     ACC,#1          ; ACC=Y*gain (Q31)
            ADD     ACC,*+XAR4[2]<<16 ; ACC=Y*gain+offset
            MOV     *+XAR4[3],AH    ; out1=Y*gain+offset

; OUT2 Computation    
; Add the phase with the "alpha" of OUT1   
            MOVU    ACC,*XAR4       ; ACC=alpha
            ADD     ACC,*+XAR4[4]   ; ACC=alpha+phase
            
            MOVB    AR0,AL.MSB      ; AR0=indice (alpha/2^8)
            MOV     T,*+XAR5[AR0]   ; T=Y=*(SINTAB_360 + indice)
         
            MPY     ACC,T,*+XAR4[1] 
            LSL     ACC,#1          ; ACC=Y*gain (Q31)
            ADD     ACC,*+XAR4[2]<<16 ; ACC=Y*gain+offset
            MOV     *+XAR4[5],AH    ; out2=Y*gain+offset       
        	CLRC 	OVM
        	LRETR
            

            


