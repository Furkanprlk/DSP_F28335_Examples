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
; FILE:        mpy_SP_RVxCV.asm
;
; AUTHOR:      David M. Alter, Texas Instruments Inc.
;
; HISTORY:
;   07/14/11 - original (D. Alter)
;
; DESCRIPTION: C-Callable multiplication of a real vector and a complex vector
;              y_re[i] = x[i]*w_re[i]
;              y_im[i] = x[i]*w_im[i]
; FUNCTION:   
;   extern void mpy_SP_RVxCV(complex_float *y, const complex_float *w, const float32 *x, const Uint16 N)
; USAGE:       mpy_SP_RVxCV(y, x, c, N);
; PARAMETERS:  complex_float *y = result complex array
;              complex_float *w = input complex array
;              float32 *x  = input real array
;              Uint16 N = length of w, x, and y arrays
; RETURNS:     none
; BENCHMARK:   5*N + 15 cycles (including the call and return)
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

		.global _mpy_SP_RVxCV
		.text
_mpy_SP_RVxCV:
		MOVL		XAR6, *-SP[4]				;XAR6 = &x
		ADDB		AL, #-2						;Subtract 2 from N since RPTB is 'n-1' times, and last iteration done seperately

		MOV32 R0H, *XAR5++						;load first w_re value

;---Main loop
		RPTB end_loop, @AL

		MOV32 R1H, *XAR6++						;load next x value

		MPYF32 		R2H, R1H, R0H				;y_re[i] = x[i]*w_re[i]
		|| MOV32 	R0H, *XAR5++				;load next w_im

		MPYF32 		R3H, R1H, R0H				;y_re[i] = x[i]*w_re[i]
		|| MOV32 	R0H, *XAR5++				;load next w_re

		MOV32		*XAR4++, R2H				;store y_re[i]
		MOV32		*XAR4++, R3H				;store y_im[i]
end_loop:

;--- Last iteration done seperately to avoid possible pointer overrun into undefined memory
		MOV32 R1H, *XAR6						;load next x value

		MPYF32 		R2H, R1H, R0H				;y_re[i] = x[i]*w_re[i]
		|| MOV32 	R0H, *XAR5					;load next w_im

		MPYF32 		R3H, R1H, R0H				;y_re[i] = x[i]*w_re[i]

		MOV32		*XAR4++, R2H				;store y_re[i]
		MOV32		*XAR4, R3H					;store y_im[i]

;Finish up
		LRETR									;return

;end of function _mpy_SP_RVxCV()
;*********************************************************************

       .end
;--------------------------------------------------------------------------
;            Copyright (c) 2014-2015 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================
