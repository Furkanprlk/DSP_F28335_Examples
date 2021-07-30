; TI File $Revision: /main/1 $
; Checkin $Date: January 6, 2011   18:11:18 $
; =============================================================================
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
;                          All Rights Reserved.
;=========================================================================
; FILE:  FIR_f32.asm
;
; TITLE: Floating point FIR filter
;
; DESCRIPTION:
;
; 	This routine implements the non-recursive difference equation of an 
; 	all-zero filter(FIR), of order N. All the coefficients of all-zero 
; 	filter are assumed to be less than 1 in magnitude.	
;
; FUNCTIONS:
;
; 	void FIR_FP_calc(FIR_FP_handle) 
;   
;	where FIR_FP_handle is a pointer to a structure defined as:
;
;  	typedef struct { 
;   float *coeff_ptr;       /*  0 Pointer to Filter co-efficient array */
;   float *dbuffer_ptr;     /*  2 Delay buffer pointer                 */ 
;   int   cbindex;          /*  4 Circular Buffer Index                */
;   int   order;            /*  5 Order of the filter                  */
;   float input;            /*  6 Input data                           */
;   float output;           /*  8 Output data                          */ 
;   void  (*init)(void *)   /* 10 Pointer to init fun                  */  
;   void  (*calc)(void *);  /* 12 Pointer to the calculation function  */
;   }FIR_FP; 
;
; ALGORITHM:
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
;
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
; ###########################################################################
; $TI Release: C28x Floating Point Unit Library V1.30 $
; $Release Date: January 04, 2012 $
; ###########################################################################

; Module definition for external referance
                .def    _FIR_FP_init 
                .def    _FIR_FP_calc


;===============================================================================
; Function: FIR_FP_init() - Initialize the FIR_FP handle and data buffer
;
; Input - FIR_FP structure pointer
; Returns - void
;
; Implementation specifics:
;   Regs used: XAR - 4,6
;===============================================================================


_FIR_FP_init:

            ZAPA
            MOVL    *+XAR4[6], ACC    ; XAR4->ouput, input=0
            ADDB    XAR4, #2          ; Only 0...7 Index allowed
            MOVL    *+XAR4[6], ACC    ; output=0

            MOVL    XAR6, *+XAR4[0]   ; XAR6=dbuffer_ptr            
            MOV     *+XAR4[2], #0     ; cbindex=0

            MOV     ACC, *+XAR4[3] << #1  ; AL = order*2 (for float)
            ADDB    AL, #1
            
            RPT     AL                ; order+1
            || MOV  *XAR6++, #0       ; zero the data buf.
            
            LRETR


;===============================================================================
; Function: FIR_FP_calc() - Compute the FIR out-put for the next sample.
;
; Input - FIR_FP structure pointer
; Returns - void
;
; Description: Input from FIR_FP is stored in the input buffer and output is
;       returned through the FIR_FP structure.
;
; Implementation specifics:
;   Regs used: XAR - 0,1,4,6,7 
;              RH  - 2,3,6,7
;===============================================================================

_FIR_FP_calc:

        ; Context Save
        MOV32   R0H, R6H            ; Store R 6,7 on R 0,1
        MOV32   R1H, R7H
        PUSH    XAR1

        ; XAR7=coeff_ptr. Adjusting base ptr (+2) to index beyond 7
        MOVL    XAR7, *XAR4++           ; XAR7 = coeff_ptr

        MOVL    XAR6, *+XAR4[0]         ; XAR6 = &dbuffer_ptr[cbindex]

        ; Set length of circular buffer ie. (2*num_elements) in XAR1
        ZAPA
        ADD     ACC, *+XAR4[3] << 1     ; ACC = 0 + order*2
        MOVZ    AR1, AL
        ;MOV		AR1, #62
        SUBB	XAR1,#2

        ; fir->dbuffer_ptr[cb_idx] = fir->input;
        MOVL    XAR0, *+XAR4[4]     ; XAR0 = input
        MOVL    *XAR6%++, XAR0      ; Store input into dbuf
        MOVL    *+XAR4[0], XAR6     ; Update dbuffer_ptr (used as cbindex)

        MOVZ    AR0, *+XAR4[3]      ; AR0=order
        ;MOV		AR0,#31
        SUBB	XAR0,#1

        ; FIR: perform convloution 
        ZERO    R2H
        ZERO    R3H
        ZERO    R6H
        ZERO    R7H

        RPT     AR0
        || MACF32    R7H, R3H, *XAR6%++, *XAR7++

        ADDF32  R6H, R6H, R2H       ; Epilogue additions
        ADDF32  R7H, R7H, R3H

        ; NOP. Restore context in the delay slots.
        POP     XAR1 

        ADDF32  R7H, R7H, R6H

        ; NOP. Restore context in the delay slots.
        MOV32   R6H, R0H

        MOV32   *+XAR4[6], R7H       ; fir->output = res;
        
        ; Restore context.
        MOV32   R7H, R1H

        LRETR      
;--------------------------------------------------------------------------
;            Copyright (c) 2010-2011 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================
