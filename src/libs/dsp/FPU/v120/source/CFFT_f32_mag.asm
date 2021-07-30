; TI File $Revision: /main/2 $
; Checkin $Date: January 6, 2011   18:11:15 $
; ========================================================================
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
;                          All Rights Reserved.
;=========================================================================
; FILE:  CFFT_f32_mag.asm
;
; TITLE: Complex FFT magnitude calculations
;
; DESCRIPTION:
;
;   Calculates the magnitude for the 32-bit floating point complex FFT.
;
; FUNCTIONS:
;
;    void CFFT_f32_mag (RFFT_F32_STRUCT *)
;
;    Where CFFT_F32_STRUCT is a structure defined as:
;
;	 typedef struct {
;	 float	*InPtr;
;	 float	*OutPtr;
;	 float	*CoefPtr;
;	 float	*CurrentInPtr;
;	 float	*CurrentOutPtr;
;    //	float	*CurrentSinPtr;
;    //	float	*CurrentCosPtr;
;	 short	Stages;
;	 }CFFT_F32_STRUCT;
;
; ASSUMPTIONS:
;
;     * Stages must be greater or equal to 3
;     * CFFT_f32() has been called prior to this function
;
;
; ALGORITHM:
;
;     Calculate the complex FFT magnitude. The data is organized as follows in
;     the output buffer after calculating FFT:
;
;  +----------------------------+
;  |  R(0)                      | 0
;  |  I(0)                      |
;  |  R(1)                      | 
;  |  I(1)                      |
;  .                            .
;  .                            .
;  .                            .
;  .                            .
;  |  R(FFTSize/2) = fs/2       |
;  |  I(FFTSize/2)              |
;  .                            .
;  .                            .
;  .                            .
;  .                            .
;  |  R(N-2)                    | 
;  |  I(N-2)                    |
;  |  R(N-1)                    |
;  |  I(N-1)                    | FFTSize - 1
;  +----------------------------+
;
;
;  On Entry:   XAR4 = &CFFT_F32_STRUCT
;
;  Regs Used:  XAR1,XAR3,XAR4,XAR6,XAR7,R0H,R1H,R2H,R3H,R5H
;----------------------------------------------------------------------
; ###########################################################################
; $TI Release: C28x FPU Library v1.20 $
; $Release Date: January 11, 2011 $
; ###########################################################################

;----------------------------------------------------------------------
;     FFT_COMPLEX structure offsets from XAR4
;----------------------------------------------------------------------
CFFT_InPtr      		.set        (0*2)
CFFT_OutPtr     		.set        (1*2)
CFFT_CoefPtr    	  	.set        (2*2)
CFFT_CurrentInPtr       .set        (3*2)
CFFT_CurrentOutPtr      .set        (4*2)
CFFT_Stages  			.set        (5*2)
CFFT_FFTSize            .set        (CFFT_Stages+1)

;===========================================================================
; Function: void CFFT_f32_mag(FFT_COMPLEX *cfft)
;===========================================================================

    .global _CFFT_f32_mag
    .ref _sqrt
    .text

_CFFT_f32_mag:
;----------------------------------------------------------------------
;     Save all save-on-entry registers used
;----------------------------------------------------------------------
        PUSH     XAR1
        PUSH     XAR2
        PUSH     XAR3
        MOV32    *SP++,R4H
        MOV32    *SP++,R5H
        MOV32    *SP++,R6H
        MOV32    *SP++,R7H

        ADDB     XAR4, #6
        MOVL     XAR1, *+XAR4[2]        ; XAR1 = &CurrentOutPtr
        MOVL     XAR3, *+XAR4[0]        ; XAR3 = &CurrentInPtr
        MOV      T, *+XAR4[5]             ; T = FFTSize

        MOV      AL, T
        SUB		 AL, #1					; Loop times = FFTSize+1
        MOV      AR6, AL                ; AR6 = calc_magnitude counter

_cfft_f32_calc_mag:

        MOV32    R3H, *XAR3++           ; R2H = CurrentInPtr[ptr++];
        MPYF32   R1H, R3H, R3H          ; R1H = Real * Real
     || MOV32    R4H, *XAR3++           ; R4H = CurrentInPtr[ptr++]
        MPYF32   R6H, R4H, R4H          ; R6H = Imag * Imag
        NOP
        ADDF32   R0H, R1H, R6H          ; R0H = (Real*Real) + (Imag*Imag)
        PUSH     XAR6                   ; Save on call
        LCR      _sqrt                  ; R0H = Mag = sqrt((Real*Real) + (Imag*Imag))
        POP      XAR6
        MOV32    *XAR1++,R0H            ; MagBuf[Mptr++] = Mag

        BANZ     _cfft_f32_calc_mag, AR6--

_cfft_f32_mag_end:

        MOV32    R7H,*--SP
        MOV32    R6H,*--SP
        MOV32    R5H,*--SP
        MOV32    R4H,*--SP
        POP      XAR3
        POP      XAR2
        POP      XAR1

        LRETR
;--------------------------------------------------------------------------
;            Copyright (c) 2010-2011 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================


