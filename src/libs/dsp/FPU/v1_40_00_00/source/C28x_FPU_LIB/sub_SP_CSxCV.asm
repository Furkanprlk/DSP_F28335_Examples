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
; FILE:        sub_SP_CSxCV.asm
;
; AUTHOR:      David M. Alter, Texas Instruments Inc.
;
; HISTORY:
;   07/15/11 - original (D. Alter)
;
; DESCRIPTION: C-Callable subtraction of a complex scalar from a complex vector
;              y_re[i] = x_re[i] - c_re
;              y_im[i] = x_im[i] - c_im
; FUNCTION: 
;   extern void sub_SP_CSxCV(complex_float *y, const complex_float *x, const complex_float c, const Uint16 N)
; USAGE:       sub_SP_CSxCV(y, w, c, N);
; PARAMETERS:  complex_float *y = result complex array
;              complex_float *x = input complex array
;              complex_float  c = input complex scalar
;              Uint16 N = length of x and y arrays
; RETURNS:     none
; BENCHMARK:   4*N + 18 cycles (including the call and return)
; NOTES:
;   1) N must be at least 2.
;   2) The inputs and return value are of type 'complex_float':
;
;      typedef struct {
;         float32 dat[2];
;      } complex_float;
;
; =============================================================================
; ###########################################################################
; $TI Release: C28x Floating Point Unit Library V1.40.00.00 $
; $Release Date: Mar 10, 2014 $
; ###########################################################################

		.global _sub_SP_CSxCV
		.text
		.word 0									;needed for RPTB alignment
_sub_SP_CSxCV:
		MOVL		XAR6, *-SP[4]				;XAR6 = &c
		MOV32		*SP++, R4H					;save R4H on stack
		ADDB		AL, #-2						;subtract 2 from N since RPTB is 'n-1' times and last iteration done seperately

		MOV32		R2H, *XAR6++				;R0H = c_re
		MOV32		R3H, *XAR6					;R1H = c_im

		MOV32		R4H, *XAR5++				;load first x_re[i]

;---Main loop
		RPTB		end_loop, @AL

		SUBF32		R0H, R4H, R2H				;y_re[i] = x_re[i] - c_re
		|| MOV32	R4H, *XAR5++				;load next x_im[i]

		SUBF32		R1H, R4H, R3H				;y_im[i] = x_im[i] - c_im
		||	MOV32	R4H, *XAR5++				;load next x_re[i]

		MOV32		*XAR4++, R0H				;store y_re[i]
		MOV32		*XAR4++, R1H				;store y_im[i]

end_loop:

;--- Last iteration done seperately to avoid possible pointer overrun into undefined memory
		SUBF32		R0H, R4H, R2H				;y_re[i] = x_re[i] - c_re
		|| MOV32	R4H, *XAR5					;load next x_im[i]

		SUBF32		R1H, R4H, R3H				;y_im[i] = x_im[i] - c_im
		||	MOV32	R4H, *--SP					;restore R4H from stack

		MOV32		*XAR4++, R0H				;store y_re[i]
		MOV32		*XAR4, R1H					;store y_im[i]

;Finish up
		LRETR									;return

;end of function _sub_SP_CSxCV()
;*********************************************************************

       .end
;--------------------------------------------------------------------------
;            Copyright (c) 2014-2015 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================
