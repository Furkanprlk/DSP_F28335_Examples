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
; FILE:        abs_SP_CV_2_TMU0.asm
;
; AUTHOR:      David M. Alter, Texas Instruments Inc.
;
; HISTORY:
;   06/21/13 - original (D. Alter)
;
; DESCRIPTION: C-Callable absolute value of an even length complex vector.
;              y[i] = sqrt(x_re[i]^2 + x_im[i]^2)
;
; FUNCTION: 
;   extern void abs_SP_CV_TMU0(float32 *y, const complex_float *x, const Uint16 N)
; USAGE:		abs_SP_CV_TMU0(x, y, N);
; PARAMETERS: 	float32 *y = output array
;               complex_float *x = input array
;               Uint16 N = length of x and y arrays
; RETURNS: 		none
; BENCHMARK (including the call and return):
*     if N=1: 30 cycles
*     if 1<N<8 and N even: 7.5*(N)+21 cycles
*     if 1<N<8 and N odd:  7.5*(N-1)+38 cycles
*     if N>=8 and N even:   4*(N-6)+56 cycles
*     if N>=8 and N odd:    4*(N-7)+73 cycles
; NOTES:
* 1) This function is optimized for N>=8.  It is less cycle efficient
*    when N<8.  For very small N (e.g., N=1, 2, maybe 3) the user might
*    consider using the TMU intrinsics in the compiler instead of this
*    function.
* 2) The type 'complex_float' is defined as
*
*      typedef struct {
*         float32 dat[2];
*      } complex_float;
*
*    Element dat[0] is the real part, dat[1] is the imag part.
* 3) For N>=8, main loop is software pipelined (temporal unrolling)
*    and spatially unrolled once.  For 1<N<8, main loop is spatially
*    unrolled once.
; =============================================================================
; ###########################################################################
; $TI Release: C28x Floating Point Unit Library V1.40.00.00 $
; $Release Date: Mar 10, 2014 $
; ###########################################################################

        .global _abs_SP_CV_TMU0
        .text

_abs_SP_CV_TMU0:

;--------------------------------------------------------------------------------
;Check for N odd
;--------------------------------------------------------------------------------
        AND AH, @AL, #1                 ;AND bit 0 of AL with a 1
        BF N_even, EQ                   ;Branch if zero (N was even)

;--------------------------------------------------------------------------------
;Perform the computation on the first complex element to make the remaining N even
;--------------------------------------------------------------------------------
N_odd:
        MOV32   R0H, *XAR5++            ;R0H = x[i]_re
        MPYF32  R0H, R0H, R0H           ;R0H = x[i]re * x[i]re
        ||MOV32 R1H, *XAR5++            ;R1H = x[i]im
        MPYF32  R1H, R1H, R1H           ;R1H = x[i]im * x[i]im
        ADDB AL, #-1                    ;Subtract 1 from N (also delay slot for MPYF32)
        ADDF32  R1H, R1H, R0H           ;R1H = (x[i]re * x[i]re) + (x[i]im * x[i]im)
        NOP                             ;delay slot
        NOP                             ;delay slot
        SQRTF32 R1H, R1H                ;R1H = mag[i] = sqrt[(x[i]re * x[i]re) + (x[i]im * x[i]im)]
        NOP                             ;delay slot
        NOP                             ;delay slot
        NOP                             ;delay slot
		CMPB AL, #0						;Test if remaining N = 0
        MOV32 *XAR4++,R1H               ;Store result[i] to memory

;--------------------------------------------------------------------------------
;Check for the remaining N = 0
;-------------------------------------------------------------------------------
        BF N_even, NEQ                  ;Branch if higher
		LRETR                           ;Return if remaining N was 0

;--------------------------------------------------------------------------------
;Check for the remaining N >= 8
;--------------------------------------------------------------------------------
N_even:
        CMPB AL, #8                     ;Compare N to 8
        BF main_N_GE_8, HIS             ;Branch if higher or same

;--------------------------------------------------------------------------------
;Main computation for remaining N < 8
;--------------------------------------------------------------------------------
main_N_LT_8:
        LSR AL, #1                      ;Divide N by 2
        ADDB AL, #-1                    ;Subtract 1 from N since RPTB is 'n-1' times
        RPTB end_loop1, @AL

        MOV32   R0H, *XAR5++            ;R0H = x[i]_re
        MPYF32  R0H, R0H, R0H           ;R0H = x[i]re * x[i]re
        ||MOV32 R1H, *XAR5++            ;R1H = x[i]im
        MPYF32  R1H, R1H, R1H           ;R1H = x[i]im * x[i]im
        ||MOV32 R2H, *XAR5++            ;R2H = x[i+1]_re
        MPYF32  R2H, R2H, R2H           ;R2H = x[i+1]re * x[i+1]re
        ||MOV32 R3H, *XAR5++            ;R3H = x[i+1]im
        MPYF32  R3H, R3H, R3H           ;R3H = x[i+1]im * x[i+1]im
        ADDF32  R1H, R1H, R0H           ;R1H = (x[i]re * x[i]re) + (x[i]im * x[i]im)
        ADDF32  R3H, R3H, R2H           ;R2H = (x[i+1]re * x[i+1]re) + (x[i+1]im * x[i+1]im)
        NOP                             ;delay slot
        SQRTF32 R1H, R1H                ;R1H = mag[i] = sqrt[(x[i]re * x[i]re) + (x[i]im * x[i]im)]
        SQRTF32 R3H, R3H                ;R3H = mag[i+1] = sqrt[(x[i+1]re * x[i+1]re) + (x[i+1]im * x[i+1]im)]
        NOP                             ;delay slot
        NOP                             ;delay slot
        NOP                             ;delay slot
        MOV32 *XAR4++,R1H               ;Store result[i] to memory
        MOV32 *XAR4++,R3H               ;Store result[i+1] to memory
end_loop1:

;Finish up
        LRETR                           ;Return

;--------------------------------------------------------------------------------
;Main computation for remaining N >= 8
;--------------------------------------------------------------------------------
main_N_GE_8:

prolog1:
        MOV32   R0H, *XAR5++            ;R0H = x[0]re
        MPYF32  R0H, R0H, R0H           ;R0H = x[0]re * x[0]re
        ||MOV32 R1H, *XAR5++            ;R1H = x[0]im
        MPYF32  R1H, R1H, R1H           ;R1H = x[0]im * x[0]im
        MOV32 *SP++, R5H                ;Save R5H on stack (also delay slot for MPYF32)
        ADDF32  R2H, R1H, R0H           ;R2H = (x[0]re * x[0]re) + (x[0]im * x[0]im)
        ||MOV32 R0H, *XAR5++            ;R0H = x[1]re
        MPYF32  R0H, R0H, R0H           ;R0H = x[1]re * x[1]re
        ||MOV32 R1H, *XAR5++            ;R1H = x[1]im
        MPYF32  R1H, R1H, R1H           ;R1H = x[1]im * x[1]im
        MOV32 *SP++, R4H                ;Save R4H on stack (also delay slot for MPYF32)
        ADDF32  R4H, R1H, R0H           ;R4H = (x[1]re * x[1]re) + (x[1]im * x[1]im)
        ||MOV32 R0H, *XAR5++            ;R0H = x[2]re
        MPYF32  R0H, R0H, R0H           ;R0H = x[2]re * x[2]re
        ||MOV32 R1H, *XAR5++            ;R1H = x[2]im
        MPYF32  R1H, R1H, R1H           ;R1H = x[2]im * x[2]im
        SQRTF32 R3H, R2H                ;R3H = mag[0] = sqrt[(x[0]re * x[0]re) + (x[0]im * x[0]im)]
        ADDF32  R2H, R1H, R0H           ;R2H = (x[2]re * x[2]re) + (x[2]im * x[2]im)
        ||MOV32 R0H, *XAR5++            ;R0H = x[3]re
        MPYF32  R0H, R0H, R0H           ;R0H = x[3]re * x[3]re
        ||MOV32 R1H, *XAR5++            ;R1H = x[3]im
        MPYF32  R1H, R1H, R1H           ;R1H = x[3]im * x[3]im
        SQRTF32 R5H, R4H                ;R5H = mag[1] = sqrt[x[1]re * x[1]re) + (x[1]im * x[1]im)]
        ADDF32  R4H, R1H, R0H           ;R4H = (x[3]re * x[3]re) + (x[3]im * x[3]im)
        ||MOV32 R0H, *XAR5++            ;R0H = x[4]re

    ;----------------
    ;Inner Loop, i=4,6,...,N
    ;----------------
        ADDB AL, #-8                    ;[pre-loop] Subtract 6 from N (4 for prolog, 2 for loop since "n-1")
        LSR AL, #1                      ;[pre-loop] Divide by 2
        RPTB epilog1, @AL

        MPYF32  R0H, R0H, R0H           ;[iteration 2] R0H = x[i]re * x[i]re
        ||MOV32 R1H, *XAR5++            ;[iteration 2] R1H = x[i]im
        MPYF32  R1H, R1H, R1H           ;[iteration 2] R1H = x[i]im * x[i]im
        ||MOV32 *XAR4++, R3H            ;[iteration 0] Store result[i-4] to memory
        SQRTF32 R3H, R2H                ;[iteration 1] R3H = mag[i] = sqrt[(x[i]re * x[i]re) + (x[i]im * x[i]im)]
        ADDF32  R2H, R1H, R0H           ;[iteration 2] R2H = (x[i]re * x[i]re) + (x[i]im * x[i]im)
        ||MOV32 R0H, *XAR5++            ;[iteration 2] R0H = x[i+1]re
        MPYF32  R0H, R0H, R0H           ;[iteration 2] R0H = x[i+1]re * x[i+1]re
        ||MOV32 R1H, *XAR5++            ;[iteration 2] R1H = x[i+1]im
        MPYF32  R1H, R1H, R1H           ;[iteration 2] R1H = x[i+1]im * x[i+1]im
        ||MOV32 *XAR4++, R5H            ;[iteration 0] Store result[i-3] to memory
        SQRTF32 R5H, R4H                ;[iteration 1] R5H = mag[i+1] = sqrt[(x[i+1]re * x[i+1]re) + (x[i+1]im * x[i+1]im)]
        ADDF32  R4H, R1H, R0H           ;[iteration 2] R4H = (x[i+1]re * x[i+1]re) + (x[i+1]im * x[i+1]im)
        ||MOV32 R0H, *XAR5++            ;[iteration 2] R0H = x[i]re

epilog1:
        MPYF32  R0H, R0H, R0H           ;R0H = x[N-2]re * x[N-2]re
        ||MOV32 R1H, *XAR5++            ;R1H = x[N-2]im
        MPYF32  R1H, R1H, R1H           ;R1H = x[N-2]im * x[N-2]im
        ||MOV32 *XAR4++, R3H            ;Store result[N-6] to memory
        SQRTF32 R3H, R2H                ;R3H = mag[N-3] = sqrt[(x[N-3]re * x[N-3]re) + (x[N-3]im * x[N-3]im)]
        ADDF32  R2H, R1H, R0H           ;R2H = (x[N-2]re * x[N-2]re) + (x[N-2]im * x[N-2]im)
        ||MOV32 R0H, *XAR5++            ;R0H = x[N-1]re
        MPYF32  R0H, R0H, R0H           ;R0H = x[N-2]re * x[N-2]re
        ||MOV32 R1H, *XAR5++            ;R1H = x[N-1]im
        MPYF32  R1H, R1H, R1H           ;R1H = x[N-1]im * x[N-1]im
        ||MOV32 *XAR4++, R5H            ;Store result[N-5] to memory
        SQRTF32 R5H, R4H                ;R5H = mag[N-2] = sqrt[(x[N-2]re * x[N-2]re) + (x[N-2]im * x[N-2]im)]
        ADDF32  R4H, R1H, R0H           ;R4H = (x[N-1]re * x[N-1]re) + (x[N-1]im * x[N-1]im)
        MOV32 *XAR4++, R3H              ;Store result[N-4] to memory
        SQRTF32 R3H, R2H                ;R3H = mag[N-1] = sqrt[(x[N-1]re * x[N-1]re) + (x[N-1]im * x[N-1]im)]
        NOP                             ;Delay slot
        MOV32 *XAR4++, R5H              ;Store result[N-3] to memory
        SQRTF32 R0H, R4H                ;R5H = mag[N-2] = sqrt[(x[N-2]re * x[N-2]re) + (x[N-2]im * x[N-2]im)]
        NOP                             ;Delay slot
        MOV32 *XAR4++, R3H              ;Store result[N-2] to memory
        MOV32 R4H, *--SP                ;Restore R4H from stack
        MOV32 R5H, *--SP                ;Restore R5H from stack (also delay slot for DIVF32)
        MOV32 *XAR4++, R0H              ;Store result[N-1] to memory

;Finish up
        LRETR                           ;Return

;end of function abs_SP_CV_TMU0()
**********************************************************************

       .end
;--------------------------------------------------------------------------
;            Copyright (c) 2014-2015 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================
