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
; File Name     : fir16.asm
; 
; Originator    : YU CAI (ASP)
;                 Texas Instruments Inc.
; 
; Description   : This file contain source code for 16-bit FIR Filter
;               
; Date          : 11/01/2010 (DD/MM/YYYY)
;======================================================================
; 
; Routine Name  : Generic Function      
; Routine Type  : C Callable
; 
; Description   :
; void FIR16_calc(FIR16_handle) 
;       
; This routine implements the non-recursive difference equation of an 
; all-zero filter(FIR), of order N. All the coefficients of all-zero 
; filter are assumed to be less than 1 in magnitude.
;======================================================================
;
; Difference Equation :
;
;       y(n)=H(0)*x(n)+H(1)*x(n-1)+H(2)*x(n-2)+....+H(N)*x(n-N)
;
;      where
;              y(n)=output sample of the filter at index n 
;              x(n)=input sample of the filter at index n 
;
; Transfer Function :
;                                  
;              Y(z)                -1        -2               -N+1       -N
;             ----- = h(0) + h(1) z  + h(2) z  + ... +h(N-1) z   + h(N) z    
;              X(z)
;
;     Network Diagram  : 

;     dbuffer[0]          dbuffer[1]    dbuffer[2]    dbuffer[N}
;     Input           -1  x(n-1)  -1    x(n-2)        x(n-N)
;   x(n) >------o----z---->-o----z---->-o---  - ->- - o
;               |           |           |             |
;               |           |           |             |
;               |           |           |             |
;               v H(0)      v H(1)      v H(2)        v H(N)  
;               |           |           |             |  
;               |           |           |             |        output
;               |---->-----(+)---->----(+)-- - -> -  (+)-----> y(n)    
;
;       Symbols Used :
;             H(0),H(1),H(2),...,H(N) : filter coefficients
;            x(n-1),x(n-2),...,x(n-N) : filter states
;                                x(n) : filter input 
;                                y(n) : filter output
;==============================================================================         
;  Function Input: This function accepts the handle of the below structure
;
;  typedef struct { 
;      int *coeff_ptr;          /* Pointer to Filter co-efficient array */
;      int *dbuffer_ptr;        /* Delay buffer pointer                 */ 
;	   int cbindex;				/* Circular Buffer Index				*/
;      int order;               /* Order of the filter                  */
;      int input;               /* Input data                           */
;      int output;              /* Output data                          */ 
;      void (*init)(void *)     /* Pointer to init fun                  */  
;      void (*calc)(void *);    /* Pointer to the calculation function  */
;     }FIR16_handle;    
;       
; Module definition for external referance
; ###########################################################################
; $TI Release: C28x Fixed Point Library v1.01 $
; $Release Date: January 11,2011 $
; ###########################################################################
				
                .def    _FIR32_init 
                .def    _FIR32_calc

_FIR32_init:
			ADDB	XAR4,#2	
            MOV     *+XAR4[4],#0    ; XAR4->ouput, input=0
            MOV     *+XAR4[6],#0    ; output=0

            MOVL    XAR6,*XAR4  ; XAR6=dbuffer_ptr            
			MOV 	AL,*+XAR4[3]	; AL=order
			MOV		AH,AL			; AH=order
			TBIT 	AL,#0				
			ADDB 	AL,#1			; AL=order+1		
			MOV 	AL,AH,TC		; AL=order, if odd

            MOV		AH,AL
            SUBB	AH,#1
            MOV		*+XAR4[2],AH	; cbindex=order, even
            						; 		 =order-1, odd
			LSL		ACC,#1
            RPT     AL
            || MOV      *XAR6++,#0
            
            LRETR




ConstTable: 
PosSatVal:    .long    0x00FFFFFF   ; Corresponds to >> 6 
NegSatVal:    .long    0xFF000000   ; Corresponds to >> 6 


_FIR32_calc:    
            PUSH    XAR1            ; Context Save           
           
            SETC    SXM,OVM         ; AR4=FIR16_handle->coeff_ptr 
      		SPM   	0              ; Create guard band of >> 6

            MOVL    XAR7,*XAR4    	; XAR4->coeff_ptr, XAR7=coeff_ptr    
            MOVL	ACC,*+XAR4[4]	; XAR4->coeff_ptr, AR1=cbindex
            LSL		ACC,#1
            MOV		AH,#0
            MOVL	XAR1,ACC
            SUBB	XAR1,#2			; critical important, FIR_ORDER-2

            MOVL    XAR6,*+XAR4[2] 	; XAR4->coeff_ptr, XAR6=dbuffer_ptr
      		MOVL   	ACC,*+XAR4[6]    ; ACC = X:Input  
     
     		MOVL  	*XAR6%++,ACC    ; Store in data array and inc circ address 
      		MOVL  	*+XAR4[2],XAR6  ; XAR4->coeff_ptr, update the dbuffer pointer

            MOV		ACC,*+XAR4[5]  	; AR0=cbindex
            MOVZ	AR0,AL			; AR0=order-1
            SUBB	XAR0,#1
            
            ZAPA                    ; Zero the ACC, P registers and OVC counter

			RPT		AR0
			|| QMACL P,*XAR6%++,*XAR7++
			
			ADDL  	ACC,P       	; Add the two sums with shift 

			ADDB	XAR4,#1
    		MOVL  	*+XAR4[7],ACC	; Store saturated result (Q30) 
    		
    		SPM	  	0

            POP     XAR1 
            CLRC    OVM
            LRETR      
            

                           
