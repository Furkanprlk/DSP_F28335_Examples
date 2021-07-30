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
; FILE:         mpy_SP_CVxCV.asm
;
; AUTHOR:      David M. Alter, Texas Instruments Inc.
;
; HISTORY:
;   07/15/11 - original (D. Alter)
;
; DESCRIPTION: C-Callable multiplication of a complex vector and a complex vector
;              y_re[i] = w_re[i]*x_re[i] - w_im[i]*x_im[i]
;              y_im[i] = w_re[i]*x_im[i] + w_im[i]*x_re[i]
; FUNCTION: 
;   extern void mpy_SP_CVxCV(complex_float *y, const complex_float *w, const complex_float *x, const Uint16 N)
; USAGE:       mpy_SP_CVxCV(y, w, x, N);
; PARAMETERS:  complex_float *y = result complex array
;              complex_float *w = input complex array #1
;              complex_float *x = input complex array #2
;              Uint16 N = length of w, x, and y arrays
; RETURNS:     none
; BENCHMARK:  10*N + 16 cycles (including the call and return)
; NOTES:
;   1) The inputs and return value are of type 'complex_float':
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

		.global _mpy_SP_CVxCV
		.text
_mpy_SP_CVxCV:
		MOVL		XAR6, *-SP[4]				;XAR6 = &x
		MOV32		*SP++, R4H					;save R4H on stack
		ADDB		AL, #-1						;Subtract 1 from N since RPTB is 'n-1' times

;---Main loop
		RPTB		end_loop, @AL

		MOV32		R0H, *XAR5++				;R0H = w_re
		MOV32		R2H, *XAR6++				;R2H = x_re
		MPYF32		R3H, R0H, R2H				;R3H = w_re * x_re
		|| MOV32	R1H, *XAR5++				;R1H = w_im
		MPYF32		R2H, R1H, R2H				;R2H = w_im * x_re
		|| MOV32	R4H, *XAR6++				;R4H = x_im
		MPYF32		R1H, R1H, R4H				;R1H = w_im * x_im
		MPYF32		R0H, R0H, R4H				;R0H = w_re * x_im
		SUBF32		R3H, R3H, R1H				;R3H = (w_re * x_re) - (w_im * x_im)
		ADDF32 		R2H, R2H, R0H				;R2H = (w_im * x_re) + (w_re * x_im)
		MOV32 		*XAR4++, R3H				;store y_re[i]
		MOV32 		*XAR4++, R2H				;store y_im[i]
end_loop:

;Finish up
		MOV32 		R4H, *--SP					;restore R4H from stack
		LRETR									;return

;end of function _mpy_SP_CVxCV()
;*********************************************************************

       .end
;--------------------------------------------------------------------------
;            Copyright (c) 2014-2015 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================
