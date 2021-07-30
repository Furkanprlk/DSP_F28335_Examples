; TI File $Revision: /main/2 $
; Checkin $Date: Thu Jan  6 15:14:02 2011 $
; ========================================================================
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
;                          All Rights Reserved.
; ========================================================================
;============================================================================
;
; File Name     : RFFT32_brev_RT.asm
; 
; Originator    : YU CAI 
;                 Texas Instruments 
; 
; Description   : This file contains to acquire N samples in bit reversed order 
;                 to perform complex FFT computation
;               
; Date          : 11/1/2010 (dd/mm/yyyy)
;===========================================================================    
; Routine Type  : C Callable        
;
; Description   :
; void RFFT32_brev_RT(FFT32_handle) 
; This function acquires N samples in bit-reversed order to cater to the complex
; FFT computation. The buffer should be aligned to 2N words
; 
;======================================================================
; typedef   struct {
;       int acqflag;
;       int count;
;       long input; 
;       long *tempptr;
;       long *buffptr;
;       int size;
;       void (*update)(void *); 
;       }FFT32_brev_RT_ACQ;  
;======================================================================
; ###########################################################################
; $TI Release: C28x Fixed Point Library v1.01 $
; $Release Date: January 11,2011 $
; ###########################################################################

            .def    _RFFT32_brev_RT       
                
_RFFT32_brev_RT:  
            MOV     ACC,*XAR4++     ; ACC=acqflag
            SBF     noacq,EQ
                              
            MOV     ACC,*XAR4++     ; ACC=count
            SBF     acqover,EQ      ; if count=0, acquisition is complete
            
            DEC     *--XAR4         ; count=count-1
            MOV     ACC,*+XAR4[7]<<1; ACC=2*size
            MOVL    XAR0,ACC        ; AR0=2*size            
                    
            MOVL    XAR5,*+XAR4[3]  ; XAR5=tempptr
            MOVL    ACC,*+XAR4[1]   ; ACC=input
            MOVL    *XAR5,ACC       ; *tempptr=input
            NOP     *BR0++
            MOVL    *+XAR4[3],XAR5
noacq:      LRETR   
                     
                     
                     
acqover:    MOV     ACC,*+XAR4[6]
            MOV     *--XAR4,ACC     ; count=size
            MOV     *--XAR4,#0      ; acqflag=0
            
            MOVL    XAR5,*+XAR4[6]  ; XAR5=buffptr
            MOVL    *+XAR4[4],XAR5  ; tempptr=buffptr
            LRETR
            
            
            
            
