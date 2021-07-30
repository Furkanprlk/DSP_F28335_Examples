;;#############################################################################
;;! \file source/fft/RFFT_f32_mag_TMU0.asm
;;!
;;! \brief  Real FFT magnitude calculations using TMU0
;;! \author David M. Alter
;;! \date   11/12/14
;;
;; DESCRIPTION:
;;
;;   Calculates the magnitude for the 32-bit floating point real FFT.
;;   Requires a C28x device with TMU0 or higher.
;;   On non-TMU devices, use the RFFT_f32_mag() function.
;;
;; HISTORY:
;;   11/12/14 - optimized v1.40.00.00 function. (D. Alter)
;;
;; FUNCTIONS:
;;
;;    void RFFT_f32_mag_TMU0 (RFFT_F32_STRUCT_Handle)
;;
;;     where RFFT_F32_STRUCT_Handle is defined as:
;;     typedef RFFT_F32_STRUCT* RFFT_F32_STRUCT_Handle;
;;
;;    and where RFFT_F32_STRUCT is a structure defined as:
;;
;;    typedef struct {
;;      float   *InBuf;
;;      float   *OutBuf;
;;      float   *CosSinBuf;
;;      float   *MagBuf;
;;      float   *PhaseBuf;
;;      uint16_t FFTSize;
;;      uint16_t FFTStages;
;;    } RFFT_F32_STRUCT;
;;
;; ASSUMPTIONS:
;;
;;     * FFTSize must be a power of 2 (32, 64, 128, etc)
;;     * FFTSize must be greater or equal to 32
;;     * FFTStages must be ln(FFTSize)/ln(2)
;;     * InBuf, OutBuf, CosSinBuf are FFTSize in length
;;     * MagBuf is (FFTSize/2 + 1) in length
;;     * PhaseBuf is FFTSize/2 in length
;;     * RFFT_f32() or RFFT_f32u() has been called prior to this function
;;
;;
;; ALGORITHM:
;;
;;     Calculate the real FFT magnitude. The data is organized as follows in
;;     the output buffer after calculating FFT:
;;
;;  +----------------------------+
;;  |  R(0) = DC                 | 0
;;  |  R(1)                      |
;;  |  R(2)                      | Real Component
;;  |  R(3)                      |
;;  .                            .
;;  .                            .
;;  .                            .
;;  .                            .
;;  |  R(FFTSize/2) = fs/2       |
;;  |  I(FFTSize/2 - 1)          |
;;  .                            .
;;  .                            .
;;  .                            .
;;  .                            .
;;  |  I(4)                      | Imaginary Component
;;  |  I(3)                      |
;;  |  I(2)                      |
;;  |  I(1)                      | FFTSize - 1
;;  +----------------------------+
;;
;; CODE OPTIMIZATION:
;;
;; The loop was temporally unrolled, and then spatially unrolled once to 
;; eliminate FPU delay slots.
;;
;; BENCHMARK: 4 cycles/complex value + overhead
;;
;;  On Entry:   XAR4 = &RFFT_F32_STRUCT
;;
;;  Group:            C2000
;;  Target Family:    C28x+FPU32
;;
;; Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/ 
;; ALL RIGHTS RESERVED
;;#############################################################################
;;$TI Release: C28x Floating Point Unit Library V1.50.00.00 $
;;$Release Date: Jun 2, 2015 $
;;#############################################################################

;----------------------------------------------------------------------
;     RFFT_F32_STRUCT structure offsets from XAR4
;----------------------------------------------------------------------
;RFFT_InBuf              .set        (0*2)
;RFFT_OutBuf             .set        (1*2)
;RFFT_CosSinBuf              .set        (2*2)
;RFFT_MagBuf            .set        (3*2)
;RFFT_PhaseBuf          .set        (4*2)
;RFFT_FFTSize             .set        (5*2)
;RFFT_FFTStages         .set        (RFFT_FFTSize+1)
;----------------------------------------------------------------------

    .global _RFFT_f32_mag_TMU0
    .text

_RFFT_f32_mag_TMU0:
        MOV32    *SP++, R4H             ; Save R4H (save-on-entry register)

        MOVL     XAR6, *+XAR4[2]        ; XAR6 = Rptr = &OutBuf[0]
        MOVL     XAR5, *+XAR4[6]        ; XAR5 = &MagBuf

        ADDB     XAR4, #10              ; Move the structure pointer up

;--- Calculate pointer to imaginary part results
        MOV      ACC, *+XAR4[0] << 1    ; ACC = 2*FFTSize
        ADDL     ACC, XAR6              ; Add OutBuff address
        MOVL     XAR7, ACC              ; XAR7 = Iptr = &OutBuf[last value]

;--- Calculate main loop count
        MOV      AL, *+XAR4[0]          ; AL = FFTSize
        LSR      AL, #2                 ; AL = FFTSize/4
        SUBB     AL, #3                 ; Init loop counter to (N-1) minus 2 
                                        ; more for prologue/epilogue

;----------------------------------------------------------------------
;     Begin magnitude calculations
;----------------------------------------------------------------------

;--- Loop prologue
;    Note: there is no Im[0], so mag[0] is handled differently.

        MOV32    R0H, *XAR6++           ; R0H = Re[i]

        MPYF32   R4H, R0H, R0H          ; R0H = Re[i]*Re[i]
     || MOV32    R2H, *XAR6++           ; R2H = Re[i+1]
        MOV32    R3H, *--XAR7           ; R3H = Im[i+1]

        MPYF32   R2H, R2H, R2H          ; R2H = Re[i+1]*Re[i+1]
     || MOV32    R0H, *XAR6++           ; R0H = Re[i]
        MPYF32   R3H, R3H, R3H          ; R3H = Im[i+1]*Im[i+1]
     || MOV32    R1H, *--XAR7           ; R1H = Im[i]
        SQRTF32  R4H, R4H               ; R4H = sqrt[(Re[i]*Re[i]) + (Im[i]*Im[i])]
        ADDF32   R6H, R3H, R2H          ; R6H = (Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])
     || MOV32    *SP++, R6H             ; Save R6H (save-on-entry register)

;--- Loop body
_rfft_f32_calc_mag:

        RPTB _rfft_f32_mag_end, @AL

        MPYF32   R0H, R0H, R0H          ; R0H = Re[i]*Re[i]
     || MOV32    R2H, *XAR6++           ; R2H = Re[i+1]
        MPYF32   R1H, R1H, R1H          ; R1H = Im[i]*Im[i]
     || MOV32    R3H, *--XAR7           ; R3H = Im[i+1]
        SQRTF32  R6H, R6H               ; R6H = sqrt[(Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])]
        ADDF32   R4H, R1H, R0H          ; R0H = (Re[i]*Re[i]) + (Im[i]*Im[i])
     || MOV32    *XAR5++,R4H            ; Store mag[i]

        MPYF32   R2H, R2H, R2H          ; R2H = Re[i+1]*Re[i+1]
     || MOV32    R0H, *XAR6++           ; R0H = Re[i]
        MPYF32   R3H, R3H, R3H          ; R3H = Im[i+1]*Im[i+1]
     || MOV32    R1H, *--XAR7           ; R1H = Im[i]
        SQRTF32  R4H, R4H               ; R4H = sqrt[(Re[i]*Re[i]) + (Im[i]*Im[i])]
        ADDF32   R6H, R3H, R2H          ; R6H = (Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])
     || MOV32    *XAR5++,R6H            ; Store mag[i+1]

_rfft_f32_mag_end:

;--- Loop epilogue

;    mag[N/2+1] is handled separately, and is not part of the epilogue.  But, 
;    it is interleaved at the end to eliminate some delay slots.  Also, note 
;    that it has no Im part so it is handled differently.

        MPYF32   R0H, R0H, R0H          ; R0H = Re[i]*Re[i]
     || MOV32    R2H, *XAR6++           ; R2H = Re[i+1]
        MPYF32   R1H, R1H, R1H          ; R1H = Im[i]*Im[i]
     || MOV32    R3H, *--XAR7           ; R3H = Im[i+1]
        SQRTF32  R6H, R6H               ; R6H = sqrt[(Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])]
        ADDF32   R4H, R1H, R0H          ; R0H = (Re[i]*Re[i]) + (Im[i]*Im[i])
     || MOV32    *XAR5++,R4H            ; Store mag[i]

        MPYF32   R2H, R2H, R2H          ; R2H = Re[i+1]*Re[i+1]
        MPYF32   R3H, R3H, R3H          ; R3H = Im[i+1]*Im[i+1]
        SQRTF32  R4H, R4H               ; R4H = sqrt[(Re[i]*Re[i]) + (Im[i]*Im[i])]
        ADDF32   R6H, R3H, R2H          ; R6H = (Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])
     || MOV32    *XAR5++,R6H            ; Store mag[i+1]

        MOV32    R0H, *XAR6++           ; R0H  = Re[N/2+1]
        ABSF32   R0H, R0H               ; R0H  = abs(Re[N/2+1])
        SQRTF32  R2H, R6H               ; R2H = sqrt[(Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])]
        MOV32    *XAR5++,R4H            ; Store mag[i]

        NOP
        MOV32    R6H,*--SP              ; Restore R6H
        MOV32    R4H,*--SP              ; Restore R4H
        MOV32    *XAR5++,R2H            ; Store mag[i+1]

        MOV32    *XAR5++, R0H           ; Store mag[N/2+1]

;--- Finish up
        LRETR

;;#############################################################################
;;  End of File
;;#############################################################################
