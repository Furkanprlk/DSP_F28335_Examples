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
; FILE:        mpy_SP_RSxRV_2.asm
;
; AUTHOR:      David M. Alter, Texas Instruments Inc.
;
; HISTORY:
;   07/14/11 - original (D. Alter)
;
; DESCRIPTION: C-Callable multiplication of a real scalar and a real vector
;              y[i] = c*x[i]
; FUNCTION: 
;   extern void mpy_SP_RSxRV_2(float32 *y, const float32 *x, const float32 c, const Uint16 N)
; USAGE:       mpy_SP_RSxRV_2(y, x, c, N);
; PARAMETERS:  float32 *y = result real array
;              float32 *x = input real array
;              float32 c  = input real scalar
;              Uint16 N = length of x and y array
; RETURNS:     none
; BENCHMARK:   2*N + 15 cycles (including the call and return)
; NOTES:
;   1) N must be even, and at least 4.
;
; =============================================================================
; ###########################################################################
; $TI Release: C28x Floating Point Unit Library V1.30 $
; $Release Date: January 04, 2012 $
; ###########################################################################

		.global _mpy_SP_RSxRV_2
		.text
		.word 0									;needed for RPTB alignment
_mpy_SP_RSxRV_2:
		LSR			AL, #1						;divide N by 2
		ADDB		AL, #-2						;subtract 2 from N since RPTB is 'n-1' times and last iteration done seperately

		MOV32		R1H, *XAR5++				;load first x value

;---Main loop
		RPTB		end_loop, @AL

		MPYF32 		R2H, R1H, R0H				;y[i] = c*x[i]
		|| MOV32 	R1H, *XAR5++				;load next x[i+1]

		MPYF32 		R3H, R1H, R0H				;y[i+1] = c*x[i+1]
		|| MOV32 	R1H, *XAR5++				;load next x[i]

		MOV32		*XAR4++, R2H				;store x[i]
		MOV32		*XAR4++, R3H				;store x[i+1]
end_loop:

;--- Last iteration done seperately to avoid possible pointer overrun into undefined memory
		MPYF32 		R2H, R1H, R0H				;y[i] = c*x[i]
		|| MOV32 	R1H, *XAR5++				;load next x[i+1]

		MPYF32 		R3H, R1H, R0H				;y[i+1] = c*x[i+1]

		MOV32		*XAR4++, R2H				;store x[i]
		MOV32		*XAR4, R3H					;store x[i+1]

;Finish up
		LRETR									;return

;end of function _mpy_SP_RSxRV_2()
;*********************************************************************

       .end
;--------------------------------------------------------------------------
;            Copyright (c) 2010-2011 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================

