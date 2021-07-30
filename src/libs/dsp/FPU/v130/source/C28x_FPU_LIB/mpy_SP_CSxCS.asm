; =============================================================================
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
;                          All Rights Reserved.
; =============================================================================
;
; FILE:        mpy_SP_CSxCS.asm
;
; AUTHOR:      David M. Alter, Texas Instruments Inc.
;
; HISTORY:
;   07/20/11 - original (D. Alter)
;
; DESCRIPTION: C-Callable complex multiply of two floating point numbers
; FUNCTION: 
;   extern complex_float mpy_SP_CSxCS(complex_float w, complex_float x);
; USAGE:       y = mpy_SP_CSxCS(w,x);
; PARAMETERS:  complex_float w = input #1
;              complex_float x = input #2
; RETURNS:     complex_float y = result
; BENCHMARK:   19 cycles (including the call and return)
; NOTES:
;   1) This is a highly optimized function.  The order of the instructions
;      is very important.
;   2) The restore of Save-on-entry register R4H is hidden in a parallel
;      instruction after its last use.
;   3) The input and return value is of type 'complex_float':
;
;      typedef struct {
;         float32 dat[2];
;      } complex_float;
;
;      Element dat[0] is the real part, dat[1] is the imag part.
;
; =============================================================================
; ###########################################################################
; $TI Release: C28x Floating Point Unit Library V1.30 $
; $Release Date: January 04, 2012 $
; ###########################################################################

		.global _mpy_SP_CSxCS
		.text

_mpy_SP_CSxCS:
;Save the utilized save on entry registers
		MOV32 *SP++, R4H						;save R4H on stack

;Optimally load the input values and do the math
		MOV32 R0H, *+XAR4[0]					;R0H = a_re
		MOV32 R2H, *+XAR5[0]					;R2H = b_re

		MPYF32 R3H, R0H, R2H					;R3H = a_re * b_re
		|| MOV32 R1H, *+XAR4[2]					;R1H = a_im

		MPYF32 R2H, R1H, R2H					;R2H = a_im * b_re
		|| MOV32 R4H, *+XAR5[2]					;R4H = b_im

		MPYF32 R1H, R1H, R4H					;R1H = a_im * b_im

		MPYF32 R0H, R0H, R4H					;R0H = a_re * b_im
		|| MOV32 R4H, *--SP						;restore R4H from stack

		SUBF32 R3H, R3H, R1H					;R3H = (a_re * b_re) - (a_im * b_im)
		ADDF32 R2H, R2H, R0H					;R2H = (a_im * b_re) + (a_re * b_im)

;Store the return value
		MOV32 *+XAR6[0], R3H					;store real part of return value
		MOV32 *+XAR6[2], R2H					;store imag part of return value

;Finish up
		LRETR									;return

;end of function mpy_SP_CSxCS()
;*********************************************************************

       .end
;--------------------------------------------------------------------------
;            Copyright (c) 2010-2011 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================
