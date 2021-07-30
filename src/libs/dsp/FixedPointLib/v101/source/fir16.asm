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
; Originator    : Yu Cai (ASP)
;                 Texas Instruments Inc.
; 
; Description   : This file contain source code for 16-bit FIR Filter
;               
; Date          : 11/05/2010 (DD/MM/YYYY)
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
;;
;; Algorithm:   Y  = sat(X0*C0 + X1*C1 + X2*C2 + ... Xn*Cn) >> 15
;;              Xn = Xn-1
;;                 .
;;                 .
;;              X2 = X1
;;              X1 = X0
;;
;;              X0 = input, Q15
;;              X1,..,Xn = Data, Q15
;;              C0,..,Cn = Coef, Q15
;;              Y  = output, Q15 
;;              n  = N - 1 (N = number of taps, must always be an even number)
;;
;;              This program uses the Dual-MAC capability of the C28x. The data
;;              and coef structures must be organized into 32-bit words as follows:
;;
;;                       31         16 15          0  
;;                       +------------+------------+
;;              *Data -> |     N-2    |   Index    | 0 lowest address
;;                       |          SatMax         | 2
;;                       |          SatMin         | 4
;;                       |   unused   |  (N/2)-1   | 6
;;                       +------------+------------+    
;;                       | .          | .          | 0
;;                       | .          | .          | 2    
;;                tail-> | .          | X(1)       | 4    
;;                head-> | X((n+1)/2) | X(0)       | 6<- index value before 
;;                       | X(n)       | X((n-1)/2) | 8   executing FIR
;;                       | X(n-1)     | .          | .
;;                       | .          | .          | .
;;                       +------------+------------+
;;
;;                       31         16 15          0  
;;                       +------------+------------+   
;;              *Coef -> | C(n)       | C((n-1)/2) | 0 lowest address
;;                       | C(n-1)     | .          | 2
;;                       | .          | .          | 4
;;                       | .          | C(2)       | .
;;                       | .          | C(1)       | .
;;                       | C((n+1)/2) | C(0)       | . 
;;                       +------------+------------+
;;          
;;              * For maximum performance, locate Data & Coef
;;                structures in seperate RAM blocks.
;;              * The Data & Coef pointers must always point to the lowest 
;;                address of the array and always aligned to even address
;;
;;              Before calling FIR, need to initialize following data parameters:
;;
;;                 Index = 0 
;;                     N = Number of filter taps (must always be even)
;;                   N-2 = Size of data buffer (must always be an even number)
;;               (N/2)-1 = number of times to repeat Dual MAC operation
;;                SatMax = 0x00FFFFFF (corresponds to SPM of -6)
;;                SatMin = 0xFF000000 (corresponds to SPM of -6)
;;               
;;                Note: Don't forget to clear all data values
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
				
                .def    _FIR16_init 
                .def    _FIR16_calc

_FIR16_init:	
            MOV     *+XAR4[6],#0    ; XAR4->ouput, input=0
            MOV     *+XAR4[7],#0    ; output=0

            MOVL    XAR6,*+XAR4[2]  ; XAR6=dbuffer_ptr            
			MOV 	AL,*+XAR4[5]	; AL=order
			MOV		AH,AL			; AH=order
			TBIT 	AL,#0				
			ADDB 	AL,#1			; AL=order+1		
			MOV 	AL,AH,TC		; AL=order, if odd

            MOV		AH,AL
            SUBB	AH,#1
            MOV		*+XAR4[4],AH	; cbindex=order, even
            						; 		 =order-1, odd

            RPT     AL
            || MOV      *XAR6++,#0
            
            LRETR

ConstTable: 
PosSatVal:    .long    0x00FFFFFF   ; Corresponds to >> 6 
NegSatVal:    .long    0xFF000000   ; Corresponds to >> 6 


_FIR16_calc:    
            PUSH    XAR1            ; Context Save           
           
            SETC    SXM,OVM         ; AR4=FIR16_handle->coeff_ptr 
      		SPM   	-6              ; Create guard band of >> 6

            MOVL    XAR7,*XAR4    	; XAR4->coeff_ptr, XAR7=coeff_ptr    
            MOVZ	AR1,*+XAR4[4]	; XAR4->coeff_ptr, AR1=cbindex
            SUBB	XAR1,#2			; critical important, FIR_ORDER-2

            MOVL    XAR6,*+XAR4[2] 	; XAR4->coeff_ptr, XAR6=dbuffer_ptr 		 
      		MOVL  	ACC,*XAR6       ; ACC = -:X 
      		MOV   	AH,@AL          ; ACC = X:X 
      		MOV   	AL,*+XAR4[6]    ; ACC = X:Input  
     
     		MOVL  	*XAR6%++,ACC    ; Store in data array and inc circ address 
      		MOVL  	*+XAR4[2],XAR6  ; XAR4->coeff_ptr, update the dbuffer pointer

            MOV		ACC,*+XAR4[5]<<15  	; AR0=cbindex
            MOVZ	AR0,AH			; AR0=order/2
            
            SUBB    XAR0,#1
           
            ZAPA                    ; Zero the ACC, P registers and OVC counter

			RPT	AR0
			|| DMAC	ACC:P,*XAR6%++,*XAR7++
			
			ADDL  	ACC,P       	; Add the two sums with shift 
      		
			MOVW	DP,#PosSatVal
      		MINL  	ACC,@PosSatVal 	; Saturate result 

		    MOVW 	DP,#NegSatVal
      		MAXL  	ACC,@NegSatVal 

    		MOVH  	*+XAR4[7],ACC<<7; Store saturated result (Q15) 
    		
    		SPM	  	0

            POP     XAR1 
            CLRC    OVM
            LRETR      
            

                           
