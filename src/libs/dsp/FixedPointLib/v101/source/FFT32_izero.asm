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
; File Name     : FFT32_izero.asm
; 
; Originator    : YU CAI (ASP) 
;                 Texas Instruments 
; 
; Description   : This file contains source code to zero the imaginary parts of 
;                 the complex input to the FFT module.
;               
; Date          : 11/1/2010 (dd/mm/yyyy)
;===========================================================================    
; Routine Type  : C Callable        
;
; Description   :
; void FFT32_izero(FFT32_handle) 
; This function zeros the imaginary part of the complex input, in the case of 
; Complex FFT modules.
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
;        int peakmag;
;        int peakfrq;
;        int normflag;
;        int *winptr; 
;        void (*init)(void);
;        void (*izero)(void *);
;        void (*calc)(void *);
;        void (*mag)(void *);
;        void (*win)(void *);
;        }CFFT32;
;======================================================================
;======================================================================
; ###########################################################################
; $TI Release: C28x Fixed Point Library v1.01 $
; $Release Date: January 11,2011 $
; ###########################################################################

            .def   _FFT32_izero  
            
_FFT32_izero:            
; Fill the imaginary part of the samples with ZERO 
            MOVL    XAR5,*XAR4      ; XAR5=ipcbptr
            MOV     ACC,*+XAR4[4]   ; ACC=size
            SUBB    ACC,#1          ; AL=size-1
            
            MOVL    XAR6,XAR5       ; XAR6=ipcbptr
            
            ADDB    XAR5,#2         ; XAR5=ipcbptr+2
            ADDB    XAR6,#3         ; XAR5=ipcbptr+3
            MOVB    XAR0,#4         ; XAR0=0
            
            NOP     *,ARP5
            RPT     AL
            || MOV      *0++,#0     ; Clear MSW of imaginary part
            
            NOP     *,ARP6
            RPT     AL 
            || MOV      *0++,#0     ; Clear LSW of imaginart part
                        
            LRETR 
            
            
                 
