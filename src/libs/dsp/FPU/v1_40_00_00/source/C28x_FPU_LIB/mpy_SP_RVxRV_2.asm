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
; FILE:        mpy_SP_RVxRV_2.asm
;
; AUTHOR:      David M. Alter, Texas Instruments Inc.
;
; HISTORY:
;   07/15/11 - original (D. Alter)
;
; DESCRIPTION: C-Callable multiplication of a real vector and a real vector
;              y[i] = w[i]*x[i]
; FUNCTION: 
;   extern void mpy_SP_RVxRV_2(float32 *y, const float32 *w, const float32 *x, const Uint16 N)
; USAGE:       mpy_SP_RVxRV_2(y, w, x, N);
; PARAMETERS:  float32 *y = result real array
;              float32 *w = input real array #1
;              float32 *x  = input real array #2
;              Uint16 N = length of w, x and y arrays
; RETURNS:     none
; BENCHMARK:   3*N + 17 cycles (including the call and return)
; NOTES:
;   1) N must be even and at least 4.
;
; =============================================================================
; ###########################################################################
; $TI Release: C28x Floating Point Unit Library V1.40.00.00 $
; $Release Date: Mar 10, 2014 $
; ###########################################################################

		.global _mpy_SP_RVxRV_2
		.text
_mpy_SP_RVxRV_2:
		MOVL		XAR6, *-SP[4]				;XAR6 = &x
		LSR			AL, #1						;divide N by 2
		ADDB		AL, #-2						;subtract 2 from N since RPTB is 'n-1' times and last iteration done seperately

		MOV32		R0H, *XAR5++				;load first w
		MOV32		R1H, *XAR6++				;load first x

;---Main loop
		RPTB		end_loop, @AL

		MPYF32 		R2H, R0H, R1H				;y[i] = w[i]*x[i]
		|| MOV32 	R0H, *XAR5++				;load next w
		MOV32		R1H, *XAR6++				;load next x
		MOV32		*XAR4++, R2H				;store y[i]

		MPYF32 		R2H, R0H, R1H				;y[i] = w[i]*x[i]
		|| MOV32 	R0H, *XAR5++				;load next w
		MOV32		R1H, *XAR6++				;load next x
		MOV32		*XAR4++, R2H				;store y[i]

end_loop:

;--- Last iteration done seperately to avoid possible pointer overrun into undefined memory
		MPYF32 		R2H, R0H, R1H				;y[i] = w[i]*x[i]
		|| MOV32 	R0H, *XAR5++				;load next w
		MOV32		R1H, *XAR6++				;load next x
		MOV32		*XAR4++, R2H				;store y[i]

		MPYF32 		R2H, R0H, R1H				;y[i] = w[i]*x[i]
		NOP										;delay slot
		MOV32		*XAR4++, R2H				;store y[i]

;Finish up
		LRETR									;return

;end of function _mpy_SP_RVxRV_2()
;*********************************************************************

       .end
;--------------------------------------------------------------------------
;            Copyright (c) 2014-2015 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================
