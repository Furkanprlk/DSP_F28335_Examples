; TI File $Revision: /main/5 $
; Checkin $Date: January 6, 2011   18:11:22 $
; =============================================================================
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2014-2015 Texas Instruments, Incorporated.
;                          All Rights Reserved.
;========================================================================
; FILE:  RFFT_f32_phase.asm
;
; TITLE: Real FFT phase calculations
;
; DESCRIPTION:
;
;   Calculates the phase for the 32-bit floating point real FFT.
;
; FUNCTIONS:
;
;    void RFFT_f32_phase (RFFT_F32_STRUCT *)
;
;    Where RFFT_F32_STRUCT is a structure defined as:
;
;    typedef struct {
;      float32  *InBuf;
;      float32  *OutBuf;
;      float32  *CosSinBuf;
;      float32  *MagBuf;
;      float32  *PhaseBuf;
;      Uint16 FFTSize;
;      Uint16 FFTStages;
;    } RFFT_F32_STRUCT;
;
; ASSUMPTIONS:
;
;     * FFTSize must be a power of 2 (32, 64, 128, etc)
;     * FFTSize must be greater or equal to 32
;     * FFTStages must be ln(FFTSize)/ln(2)
;     * InBuf, OutBuf, CosSinBuf are FFTSize in length
;     * MagBuf and PhaseBuf are FFTSize/2 in length
;     * RFFT_f32() or RFFT_f32u() has been called prior to this function
;
;
; ALGORITHM:
;
;     Calculate the real FFT phase. The data is organized as follows in
;     the output buffer after calculating FFT:
;
;  +----------------------------+
;  |  R(0) = DC                 | 0
;  |  R(1)                      |
;  |  R(2)                      | Real Component
;  |  R(3)                      |
;  .                            .
;  .                            .
;  .                            .
;  .                            .
;  |  R(FFTSize/2) = fs/2       |
;  |  I(FFTSize/2 - 1)          |
;  .                            .
;  .                            .
;  .                            .
;  .                            .
;  |  I(4)                      | Imaginary Component
;  |  I(3)                      |
;  |  I(2)                      |
;  |  I(1)                      | FFTSize - 1
;  +----------------------------+
;
;
;  On Entry:   XAR4 = &RFFT_F32_STRUCT
;
;  Regs Used:  XAR1,XAR3,XAR4,XAR6,XAR7,R0H,R1H,R2H,R3H,R5H
;--------------------------------------------------------------------
; ###################################################################
; $TI Release: C28x Floating Point Unit Library V1.40.00.00 $
; $Release Date: Mar 10, 2014 $
; ###################################################################


    .global _RFFT_f32_phase
    .ref _atan2
    .text
_RFFT_f32_phase
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

        MOVL     XAR3, *+XAR4[2]    ; XAR3 = Rptr = &OutBuf[0]
        MOVB     XAR0, #8
        MOVL     XAR1, *+XAR4[AR0]  ; XAR1 = &Phasebuf
        ADDB     XAR4, #10
        MOV      T, *XAR4++         ; T    = FFTSize

        MPYB     ACC, T, #2
        ADDL     ACC, XAR3
        MOVL     XAR2, ACC          ; XAR2 = Iptr = &OutBuf[last value]

        MOV      AL, T
        LSR      AL, #1
        SUBB     AL, #2
        B        _rfft_f32_phase_end,LEQ  ; falls to zero, end the function
        MOV      AR6, AL            ; AR6 = calc_phase counter

        MOV      AL, *XAR4
        SUBB     AL, #2
        B        _rfft_f32_phase_end,LEQ  ; falls to zero, end the function
        MOV      AR7, AL            ; AR7 = scale_value1 counter

        MOVIZF32  R5H,#1.0          ; R5H=1

_rfft_f32_scale_value1:
        MPYF32    R5H,R5H,#0.5      ; R5H=scale
        NOP
        BANZ _rfft_f32_scale_value1,AR7--
;---------------------------------------------------------------------------
;   Begin phase calculations
;---------------------------------------------------------------------------
        MOV32       R2H, *XAR3++    ; R2H = Real = OutBuf[Rptr++]
        MPYF32      R1H, R2H, R5H   ; R1H = Real * scale
        MOVIZF32    R0H, #0
        PUSH        XAR6            ; Save on call
        LCR         _atan2          ; R0H =  atan2(0,Real)
        POP         XAR6
        MOV32       *XAR1++, R0H    ; Phasebuf[Mptr++] = atan2(0,Real)

_rfft_f32_calc_phase:

        MOV32       R2H, *XAR3++    ; R2H = Real = OutBuf[Rptr++]
        MPYF32      R1H, R2H, R5H   ; R0H = Real * scale
    ||  MOV32       R3H, *--XAR2    ; R3H = Imag = OutBuf[Iptr--]
        MPYF32      R0H, R3H, R5H   ; R0H = Imag * scale
        PUSH        XAR6            ; Save on Call
        LCR         _atan2          ; R0H = Phase = atan2(Imag, Real);
        POP         XAR6
        MOV32       *XAR1++, R0H    ; PhaseBuf[Mptr++] = Phase;

        BANZ _rfft_f32_calc_phase,AR6--

_rfft_f32_phase_end:

        MOV32    R7H,*--SP
        MOV32    R6H,*--SP
        MOV32    R5H,*--SP
        MOV32    R4H,*--SP
        POP      XAR3
        POP      XAR2
        POP      XAR1
        LRETR

;--------------------------------------------------------------------------
;            Copyright (c) 2014-2015 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================

