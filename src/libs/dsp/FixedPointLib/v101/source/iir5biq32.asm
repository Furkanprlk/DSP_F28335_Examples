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
;========================================================================
;
; File Name     : iir5biq32.asm
; 
; Originator    : YU CAI (ASP)
;                 Texas Instruments Inc. 
; 
; Description   : This file contain source code for 32 bit IIR implementation
;               
; Date          : 11/1/2011
;======================================================================
; 
; 
; Routine Name  : Generic Function      
; Routine Type  : C Callable
; 
; Description   :
; void IIR5BIQ32_calc(IIR5BIQ32_handle) 
;
; This routine implements the IIR filter using cacade biquad structure
;======================================================================
;typedef struct {  
;   void (*init)(void *);   /* Ptr to Init funtion           */
;   void (*calc)(void *);   /* Ptr to calc fn                */ 
;   long *coeff_ptr;        /* Pointer to Filter coefficient */
;   long *dbuffer_ptr;      /* Delay buffer ptr              */
;   int nbiq;               /* No of biquad                  */
;   int input;              /* Latest Input sample           */
;   long isf;               /* Input Scale Factor            */ 
;   long output32;          /* Filter Output                 */
;   int output16            /* Filter Output                 */
;   int qfmat;              /* Coefficients Q Format         */
;        }IIR5BIQ32;     
;=====================================================================

; Module definition for external referance
; ###########################################################################
; $TI Release: C28x Fixed Point Library v1.01 $
; $Release Date: January 11,2011 $
; ###########################################################################

                .def    _IIR5BIQ32_calc
                .def    _IIR5BIQ32_init 

_IIR5BIQ32_init:
            ADDB    XAR4,#6         ; XAR4->dbuffer_ptr
            MOVL    XAR6,*+XAR4[0]  ; XAR6=dbuffer_ptr
            MOV     ACC,*+XAR4[2]<<2; ACC=4*nbiq
            SUB     ACC,#1          ; ACC=(4*nbiq)-1
            MOVZ    AR0,AL          ; AR0=(4*nbiq)-1
            ADDL    ACC,*XAR4       ; ACC=dbuffer_ptr + (4*nbiq) - 1
            MOVL    *XAR4++,ACC     ; XAR4->nbiq, 
                                    ; dbuffer_ptr=dbuffer_ptr + (4*nbiq) - 1
	
			ADDB	XAR4,#2
            MOV     *+XAR4[1],#0    ; input=0
            MOVB    ACC,#32
            SUB     ACC,*+XAR4[7]
            MOV     *+XAR4[7],AL    ; qfmat=32-qfmat
            MOV     *+XAR4[6],#0    ; output16=0
            MOV     *+XAR4[5],#0    ; output32=0
            MOV     *+XAR4[4],#0    ; output32=0

            RPT     AR0
            || MOV  *XAR6++,#0
            
            LRETR
                        
          
_IIR5BIQ32_calc:    
            SETC    SXM,OVM          
            ZAPA                    ; Zero the ACC, P registers and OVC counter

            ADDB    XAR4,#4         ; AR4->coeff_ptr
            MOVL    XAR7,*XAR4++    ; XAR4->dbuffer_ptr, XAR7=coeff_ptr->a21
            MOVL    XAR6,*XAR4++    ; XAR4->order, XAR6=dbuffer_ptr->d1(n-2)  
            MOVZ    AR0,*XAR4++     ; XAR4->input, AR0=nbiq

            ;MOVX    TL,*XAR4++       ; XAR4->isf, T=input
            ADDB	XAR4,#1
			MOVL    XT,*XAR4++       ; XAR4->isf, T=input

            QMPYL   ACC,XT,*XAR4++  ; XAR4->output32, ACC=input*isf
            ADDB    XAR6,#2 
            SUBB    XAR0,#1         ; AR0=nbiq-1
        
; kth Biquad Computation   where k=1:nbiq
biqd:     
            MOVL    XT,*--XAR6      ; T=dk(n-2)
            QMPYL   P,XT,*XAR7++    ; P= dk(n-2)*a2k
            MOVL    XT,*--XAR6      ; T=dk(n-1)
            QMPYAL  P,XT,*XAR7++    ; ACC=input*isf + dk(n-2)*a2k, P=dk(n-1)*a1k
            
            MOVL    XT,*+XAR6[2]    ; T=dk(n-2)
            QMPYAL  P,XT,*XAR7++    ; ACC=input*isf + dk(n-2)*a2k + dk(n-1)*a1k
                                    ; P=dk(n-2)*b2k
            
            MOV     T,*+XAR4[3]     ; T=qfmat
            LSLL    ACC,T           ; ACC=input*isf + dk(n-2)*a2k + dk(n-1)*a1k (Q31)
                                
            MOVDL   XT,*XAR6        ; XT=dk(n-1), dk(n-2)=dk(n-1)
            MOVL    *XAR6,ACC       ; dk(n-1)=dk(n)
            QMPYL   ACC,XT,*XAR7++  ; ACC=dk(n-1)*b1k
            
            MOVL    XT,*XAR6        ; XT=dk(n)
            QMPYAL  P,XT,*XAR7++    ; ACC=dk(n-1)*b1k + dk(n-2)*b2k, P=dk(n)*b0k
            ADDL    ACC,P
            
            BANZ    biqd,AR0--
            
            MOV     T,*+XAR4[3]     ; T=qfmat, XAR4->output32
            LSLL    ACC,T
            ROR     ACC
            MOVL    *XAR4++,ACC     ; output32=Filtered Output in Q30 format 
            MOV     *XAR4,AH        ; output16=Filtered Output in Q14 format    
            CLRC    OVM
            LRETR                  









            
                           
