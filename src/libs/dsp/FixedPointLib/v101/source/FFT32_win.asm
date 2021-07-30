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
; File Name     : FFT32_win.asm
; 
; Originator    : YU CAI (ASP) 
;                 Texas Instruments 
; 
; Description   : This file contains source code to window the input data sequence in the case of 
;                 complex FFT modules
;               
; Date          : 11/1/2010 (dd/mm/yyyy)
;===========================================================================    
; Routine Type  : C Callable        
;
; Description   :
; void FFT32_win(FFT32_handle) 
; This function windows N-point real data sequence stored in bit-reversed order 
; in alternate memory location.(used with Complex FFT modules)
; 
;====================================================================== 
; COMPLEX FFT MODULES
;----------------------------------------------------------------------
;typedef struct {   
;        long *ipcbptr;
;        long *tfptr               
;        int size;
;        int nrstage;             
;        int *magptr;
;        int *winptr; 
;        int peakmag;
;        int peakfrq;
;        int normflag;
;        void (*init)(void);
;        void (*izero)(void *);
;        void (*calc)(void *);
;        void (*mag)(void *);
;        void (*win)(void *);
;        }CFFT32;
;======================================================================
; ###########################################################################
; $TI Release: C28x Fixed Point Library v1.01 $
; $Release Date: January 11,2011 $
; ###########################################################################

            .def    _FFT32_win       
                
_FFT32_win:
            MOVL    XAR5,*XAR4++    ; XAR5=ipcbptr
            MOVL    XAR6,*+XAR4[6]  ; XAR6=winptr
            MOV     ACC,*+XAR4[2]<<15 ; AH=size/2
            MOVH    AR0,ACC<<2      ; AR0=2*size
            MOVZ    AR7,AH          ; AR7=(size/2)                                  
            SUBB    XAR7,#1         ; AR7=(size/2)-1
            MOVL    XAR4,XAR7       ; AR4=(size/2)-1
            
nextsamp1:  
            MOVL    XT,*XAR6++
            QMPYL   ACC,XT,*XAR5
            LSL     ACC,#1
            MOVL    *BR0++,ACC
            BANZ    nextsamp1,AR7--
            
nextsamp2:  
            MOVL    XT,*--XAR6
            QMPYL   ACC,XT,*XAR5
            LSL     ACC,#1
            MOVL    *BR0++,ACC
            BANZ    nextsamp2,AR4--
            LRETR

