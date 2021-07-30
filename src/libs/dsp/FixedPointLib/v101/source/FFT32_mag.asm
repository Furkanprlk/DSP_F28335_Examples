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
; File Name     : FFT32_mag.asm
; 
; Originator    : YU CAI (ASP) 
;                 Texas Instruments 
; 
; Description   : This file contains source code to compute the magnitude square of
;                 complex spectral bins for complex FFT outputs.
;               
; Date          : 11/2/2010 (dd/mm/yyyy)
;===========================================================================    
; Routine Type  : C Callable        
;
; Description   :
; void FFT32_mag(FFT32_handle) 
; This function computes the magnitude square of complex FFT outputs. Allows in-place
; and off-place storage of the magnitude square results.
; 
;====================================================================== 
; COMPLEX FFT MODULES
;----------------------------------------------------------------------
;typedef struct {   
;        long *ipcbptr;
;        long *tfptr               
;        int size;
;        int nrstage;             
;        long *magptr;
;        long *winptr; 
;        long peakmag;
;        int peakfrq;
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

            .def   _FFT32_mag   
            
_FFT32_mag:
            SETC    SXM
            
            MOVL    XAR7,*XAR4      ; XAR5=ipcbptr
            MOVL    XAR6,*+XAR4[6]  ; XAR6=magptr
            
            MOVZ    AR0,*+XAR4[4]   ; AR7=size
            SUBB    XAR0,#1         ; AR0=size-1

MAG_LP:     
            ZAPA                    ; ACC=0, P=0
            QMACL   P,*XAR7,*XAR7++ ; Q15*Q15=Q30
            QMACL   P,*XAR7,*XAR7++ ; Q15*Q15+Q30=Q30
            ADDL    ACC,P
            MOVL    *XAR6++,ACC     ; Store in Q30
            BANZ    MAG_LP,AR0--
            
; Find maximum magnitude
            ADDB    XAR4,#4         ; XAR4->size
            MOVB    ACC,#0
            MOVL    *+XAR4[6],ACC   ; peakmag=0
            MOVZ    AR0,*XAR4       ; AR0=size
            MOVL    XAR5,*+XAR4[2]  ; XAR5=magptr

            MOV     ACC,#0
            SUBB    XAR0,#1         ; AR0=size-1
            
;Find the maximum value among the FFT Magnitudes    
            RPT     AR0
            || MAXL ACC,*XAR5++
            
            MOVL    *+XAR4[6],ACC   ; update peak magnitude
            MOVB    XAR7,#0         ; XAR7=0
            MOVL    XAR5,*+XAR4[2]  ; XAR5=magptr
;Find the spectral bin corresponding to maximum magnitude.  
NEXT_BIN:               
            MAXL    ACC,*XAR5++
            NOP     *XAR7++
            SBF     NEXT_BIN,NEQ    
            
            NOP     *--XAR7
            ADDB    XAR4,#8         ; XAR4->peakfrq
            MOV     *XAR4,AR7       ; update peak magnitude     
            LRETR      

