; =============================================================================
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2014-2015 Texas Instruments, Incorporated.
;                          All Rights Reserved.
; ==================================================================================
;
; FILE:        maxidx_SP_RV_2.asm
;
; AUTHOR:      David M. Alter, Texas Instruments Inc.
;
; HISTORY:
;   07/20/11 - original (D. Alter)
;
; DESCRIPTION: C-Callable index of maximum value of an even length  real array
; FUNCTION:    extern Uint16 maxidx_SP_RV_2(float32 *x, Uint16 N);
; USAGE:       index = maxidx_SP_RV_2(x, N);
; PARAMETERS:  float32 x = input array
;              Uint16 N = length of x
; RETURNS:     Uint16 index = index of maximum value in x
; BENCHMARK:   3N+21 cycles (including the call and return)
; NOTES:
;   1) N must be even.
;   2) If more than one instance of the max value exists in x[], the function
;      will return the index of the first occurence (lowest index value).
;   3) Register usage:
;      R3H = index_candidate
;      R2H = index
;      R1H = max_candidate
;      R0H = max
;      XAR4 = pointer to x array
;
;==============================================================================
; ###########################################################################
; $TI Release: C28x Floating Point Unit Library V1.40.00.00 $
; $Release Date: Mar 10, 2014 $
; ###########################################################################

		.global _maxidx_SP_RV_2
		.text

_maxidx_SP_RV_2:
;Start with x[0] as the assumed max
		MOV32 R0H, *XAR4						;R0H = x[0] (initial max is first element in x[])
		ZERO R2H								;R2H = 0.0 (initial index is 0)
		MOVIZF32 R3H, #-1.0						;R3H = -1.0 (index_candidate, need to start at -1 because loop immediately increments)
		LSR AL, #1								;Divide N by 2
		ADDB AL, #-1							;Subtract 1 from N since RPTB is 'n-1' times

;Main loop
		RPTB end_loop, @AL
		ADDF32 R3H, R3H, #1.0					;increment index candidate
		MOV32 R1H, *XAR4++						;max candidate = x[i] (also delay slot for ADDF32)
		;if max < max_candidate, then max = max_candidate and index = index_candidate
		MAXF32 R0H, R1H || MOV32 R2H, R3H		;if R0H < R1H, then R0H=R1H and R2H=R3H

		ADDF32 R3H, R3H, #1.0					;increment index candidate
		MOV32 R1H, *XAR4++						;max candidate = x[i] (also delay slot for ADDF32)
		;if max < max_candidate, then max = max_candidate and index = index_candidate
		MAXF32 R0H, R1H || MOV32 R2H, R3H		;if R0H < R1H, then R0H=R1H and R2H=R3H

end_loop:

;Prepare the return value
		F32TOUI16 R2H, R2H						;convert index from float32 to Uint16
		NOP										;delay slot for F32TOUI16 
		NOP										;alignment cycle for trailing MOV32
		MOV32 ACC, R2H

;Finish up
		LRETR									;return

;end of function maxidx_SP_RV_2()
;*********************************************************************

       .end
;--------------------------------------------------------------------------
;            Copyright (c) 2014-2015 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================
