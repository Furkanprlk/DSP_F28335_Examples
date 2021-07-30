; =============================================================================
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2014-2015 Texas Instruments, Incorporated.
;                          All Rights Reserved.
; =============================================================================
;
; FILE:        abs_SP_CV_2.asm
;
; AUTHOR:      David M. Alter, Texas Instruments Inc.
;
; HISTORY:
;   10/05/11 - Fixed bug that caused bad results if an odd indexed
;              complex input element was zero (re[i]=im[i]=0, i=odd).
;   07/20/11 - original (D. Alter)
;
; DESCRIPTION: C-Callable absolute value of an even length complex vector.
;              y[i] = sqrt(x_re[i]^2 + x_im[i]^2)
;
; FUNCTION: 
;   extern void abs_SP_CV_2(float32 *y, const complex_float *x, const Uint16 N)
; USAGE:		abs_SP_CV_2(x, y, N);
; PARAMETERS: 	float32 *y = output array
;               complex_float *x = input array
;               Uint16 N = length of x and y arrays
; RETURNS: 		none
; BENCHMARK: 	18*N+22 cycles (including the call and return)
; NOTES:
;   1) N must be even.
;   2) The type 'complex_float' is defined as
;
;      typedef struct {
;         float32 dat[2];
;      } complex_float;
;
;    Element dat[0] is the real part, dat[1] is the imag part.
; =============================================================================
; ###########################################################################
; $TI Release: C28x Floating Point Unit Library V1.40.00.00 $
; $Release Date: Mar 10, 2014 $
; ###########################################################################

		.global _abs_SP_CV_2
		.text

_abs_SP_CV_2:
;Save the utilized save on entry registers
		MOV32 *SP++, R4H				;save R4H on stack
		MOV32 *SP++, R5H				;save R5H on stack
		MOV32 *SP++, R6H				;save R6H on stack
		MOV32 *SP++, R7H				;save R7H on stack

;---Main loop.  Unroll once to eliminate delay slots.  Code that follows
;---has the two loop iterations heavily interleaved.  Code comments use
;---the notation x1, x2 to differentiate between loop iterations.
		LSR AL, #1						;Divide N by 2
		ADDB AL, #-1					;Subtract 1 from N since RPTB is 'n-1' times
		RPTB end_loop, @AL

;Compute the magnitude squared
		MOV32 R0H, *XAR5++				;R0H = x1_re
		MPYF32 R1H, R0H, R0H			;R1H = x1_re * x1_re
		|| MOV32 R2H, *XAR5++			;R2H = x1_im

		MOV32 R4H, *XAR5++				;R4H = x2_re
		MPYF32 R5H, R4H, R4H			;R5H = x2_re * x2_re]
		|| MOV32 R6H, *XAR5++			;R6H = x2_im

		MPYF32 R3H, R2H, R2H			;R3H = x1_im * x_im1
		MPYF32 R7H, R6H, R6H			;R7H = x2_im * x_im2
		ADDF32 R0H, R1H, R3H			;R0H = (x1_re * x1_re) + (x1_im * x1_im)
		ADDF32 R4H, R5H, R7H			;R4H = (x2_re * x2_re) + (x2_im * x2_im)

;Compute sqrt.  Use the code from the DSP28 Fast FPU Library!
        EISQRTF32   R1H, R0H            ;R1H = Ye1 = Estimate(1/sqrt(X1))
	    MPYF32      R2H, R0H, #0.5      ;R2H = X1*0.5
        EISQRTF32   R5H, R4H            ;R5H = Ye2 = Estimate(1/sqrt(X2))        
        MPYF32      R6H, R4H, #0.5      ;R6H = X2*0.5

        MPYF32      R3H, R1H, R1H       ;R3H = Ye1*Ye1
        MPYF32      R7H, R5H, R5H       ;R7H = Ye2*Ye2
        MPYF32      R3H, R3H, R2H       ;R3H = Ye1*Ye1*X1*0.5
        MPYF32      R7H, R7H, R6H       ;R7H = Ye2*Ye2*X2*0.5
        SUBF32      R3H, #1.5, R3H      ;R3H = 1.5 - Ye1*Ye1*X1*0.5
        SUBF32      R7H, #1.5, R7H      ;R7H = 1.5 - Ye2*Ye2*X2*0.5
        MPYF32      R1H, R1H, R3H       ;R2H = Ye1 = Ye1*(1.5 - Ye1*Ye1*X1*0.5)
        MPYF32      R5H, R5H, R7H       ;R6H = Ye2 = Ye2*(1.5 - Ye2*Ye2*X2*0.5)
        MPYF32      R3H, R1H, R2H       ;R3H = Ye1*X1*0.5
        MPYF32      R7H, R5H, R6H       ;R7H = Ye2*X2*0.5
        MPYF32      R3H, R1H, R3H       ;R3H = Ye1*Ye1*X1*0.5
        MPYF32      R7H, R5H, R7H       ;R7H = Ye2*Ye2*X2*0.5

        SUBF32      R3H, #1.5, R3H      ;R3H = 1.5 - Ye1*Ye1*X1*0.5
        CMPF32      R0H, #0.0           ;Check if X1 == 0
        MPYF32      R1H, R1H, R3H       ;R1H = Ye1 = Ye1*(1.5 - Ye1*Ye1*X1*0.5)
        SUBF32      R7H, #1.5, R7H      ;R7H = 1.5 - Ye2*Ye2*X2*0.5
        MOV32       R1H, R0H, EQ        ;If X1 is zero, change the Ye1 estimate to 0
        CMPF32      R4H, #0.0           ;Check if X2 == 0
        MPYF32      R5H, R5H, R7H       ;R5H = Ye2 = Ye2*(1.5 - Ye2*Ye2*X2*0.5)
        MPYF32      R0H, R0H, R1H       ;R0H = Y1 = X1*Ye1 = sqrt(X1)
        MOV32       R5H, R4H, EQ        ;If X2 is zero, change the Ye2 estimate to 0
        MPYF32      R4H, R4H, R5H       ;R4H = Y2 = X2*Ye2 = sqrt(X2)

		MOV32 *XAR4++, R0H				;store the first result to memory
		MOV32 *XAR4++, R4H				;store the second result to memory

end_loop:

;Restore the utilized save on entry register
		MOV32 R7H, *--SP				;restore R7H from stack
		MOV32 R6H, *--SP				;restore R6H from stack
		MOV32 R5H, *--SP				;restore R5H from stack
		MOV32 R4H, *--SP				;restore R4H from stack

;Finish up
		LRETR							;return

;end of function abs_SP_CV_2()
;*********************************************************************

       .end
;--------------------------------------------------------------------------
;            Copyright (c) 2014-2015 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================

