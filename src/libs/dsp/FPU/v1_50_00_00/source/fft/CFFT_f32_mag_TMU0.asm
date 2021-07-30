;;#############################################################################
;;! \file source/fft/CFFT_f32_mag_TMU0.asm
;;!
;;! \brief  Complex FFT magnitude calculations using TMU0
;;! \author David M. Alter
;;! \date   11/06/14
;;
;; HISTORY:
;;   11/06/14 - original (D. Alter)
;;
;; DESCRIPTION:
;;
;;   Calculates the magnitude for the 32-bit floating point complex FFT.
;;   Requires a C28x device with TMU0 or higher.
;;   On non-TMU devices, use the CFFT_f32_mag() function.
;;
;; FUNCTIONS:
;;
;;    void CFFT_f32_mag_TMU0 (CFFT_F32_STRUCT_Handle)
;;
;;     where CFFT_F32_STRUCT_Handle is defined as:
;;     typedef CFFT_F32_STRUCT* CFFT_F32_STRUCT_Handle;
;;
;;    and where CFFT_F32_STRUCT is a structure defined as:
;;
;;     typedef struct {
;;     float       *InPtr;
;;     float       *OutPtr;
;;     float       *CoefPtr;
;;     float       *CurrentInPtr;
;;     float       *CurrentOutPtr;
;;     uint16_t  Stages;
;;     uint16_t  FFTSize;
;;     } CFFT_F32_STRUCT;
;;
;; ASSUMPTIONS:
;;
;;     * CFFT_f32() has been called prior to this function
;;     * FFTSize must be at least 4 and even.
;;
;; ALGORITHM:
;;
;;     Calculate the complex FFT magnitude. The data is organized as follows in
;;     the output buffer after calculating FFT:
;;
;;  +----------------------------+
;;  |  R(0)                      | 0
;;  |  I(0)                      |
;;  |  R(1)                      | 
;;  |  I(1)                      |
;;  .                            .
;;  .                            .
;;  .                            .
;;  .                            .
;;  |  R(FFTSize/2) = fs/2       |
;;  |  I(FFTSize/2)              |
;;  .                            .
;;  .                            .
;;  .                            .
;;  .                            .
;;  |  R(N-2)                    | 
;;  |  I(N-2)                    |
;;  |  R(N-1)                    |
;;  |  I(N-1)                    | FFTSize - 1
;;  +----------------------------+
;;
;; CODE OPTIMIZATION:
;;
;; The loop was spatially unrolled once and temporally unrolled once to 
;; eliminate FPU delay slots.
;;
;; BENCHMARK: 4 cycles/complex value + overhead
;;
;;  On Entry:   XAR4 = &CFFT_F32_STRUCT
;;
;;  Group:            C2000
;;  Target Family:    C28x
;;
;; (C)Copyright 2015, Texas Instruments, Inc.
;;#############################################################################
;;$TI Release: C28x Floating Point Unit Library V1.50.00.00 $
;;$Release Date: Jun 2, 2015 $
;;#############################################################################
;;
;----------------------------------------------------------------------
;     CFFT_F32_STRUCT structure offsets from XAR4
;----------------------------------------------------------------------
;CFFT_InPtr              .set        (0*2)
;CFFT_OutPtr             .set        (1*2)
;CFFT_CoefPtr              .set        (2*2)
;CFFT_CurrentInPtr      .set        (3*2)
;CFFT_CurrentOutPtr     .set        (4*2)
;CFFT_Stages            .set        (5*2)
;CFFT_FFTSize           .set        (CFFT_Stages+1)

;===========================================================================
; Function: void CFFT_f32_mag_TMU0(CFFT_F32_STRUCT_Handle)
;===========================================================================

    .global _CFFT_f32_mag_TMU0
    .text

_CFFT_f32_mag_TMU0:
        ADDB     XAR4, #6
        MOVL     XAR5, *+XAR4[2]        ; XAR5 = &CurrentOutPtr
        MOVL     XAR6, *+XAR4[0]        ; XAR6 = &CurrentInPtr

;--- Compute main loop count
        MOV      AL, *+XAR4[5]          ; AL = FFTSize
        LSR      AL, #1                 ; AL = FFTSize/2
        SUB      AL, #3                 ; Init loop counter to "(N-1)" minus 2 
                                        ;more for prologue/epilogue

;----------------------------------------------------------------------
;     Begin magnitude calculations
;----------------------------------------------------------------------

;--- Loop prologue
        MOV32    R0H, *XAR6++           ; R0H = Re[i]

        MPYF32   R0H, R0H, R0H          ; R0H = Re[i]*Re[i]
     || MOV32    R1H, *XAR6++           ; R1H = Im[i]
        MPYF32   R1H, R1H, R1H          ; R1H = Im[i]*Im[i]
     || MOV32    R2H, *XAR6++           ; R2H = Re[i+1]
        MOV32    R3H, *XAR6++           ; R3H = Im[i+1]
        ADDF32   R4H, R1H, R0H          ; R0H = (Re[i]*Re[i]) + (Im[i]*Im[i])
     || MOV32    *SP++, R4H             ; Save R4H (save-on-entry register)

        MPYF32   R2H, R2H, R2H          ; R2H = Re[i+1]*Re[i+1]
     || MOV32    R0H, *XAR6++           ; R0H = Re[i]
        MPYF32   R3H, R3H, R3H          ; R3H = Im[i+1]*Im[i+1]
     || MOV32    R1H, *XAR6++           ; R1H = Im[i]
        SQRTF32  R4H, R4H               ; R4H = sqrt[(Re[i]*Re[i]) + (Im[i]*Im[i])]
        ADDF32   R6H, R3H, R2H          ; R6H = (Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])
     || MOV32    *SP++, R6H             ; Save R6H (save-on-entry register)
        
;--- Loop body
_cfft_f32_calc_mag:

        RPTB _cfft_f32_mag_end, @AL

        MPYF32   R0H, R0H, R0H          ; R0H = Re[i]*Re[i]
     || MOV32    R2H, *XAR6++           ; R2H = Re[i+1]
        MPYF32   R1H, R1H, R1H          ; R1H = Im[i]*Im[i]
     || MOV32    R3H, *XAR6++           ; R3H = Im[i+1]
        SQRTF32  R6H, R6H               ; R6H = sqrt[(Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])]
        ADDF32   R4H, R1H, R0H          ; R0H = (Re[i]*Re[i]) + (Im[i]*Im[i])
     || MOV32    *XAR5++,R4H            ; Store mag[i]

        MPYF32   R2H, R2H, R2H          ; R2H = Re[i+1]*Re[i+1]
     || MOV32    R0H, *XAR6++           ; R0H = Re[i]
        MPYF32   R3H, R3H, R3H          ; R3H = Im[i+1]*Im[i+1]
     || MOV32    R1H, *XAR6++           ; R1H = Im[i]
        SQRTF32  R4H, R4H               ; R4H = sqrt[(Re[i]*Re[i]) + (Im[i]*Im[i])]
        ADDF32   R6H, R3H, R2H          ; R6H = (Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])
     || MOV32    *XAR5++,R6H            ; Store mag[i+1]

_cfft_f32_mag_end:

;--- Loop epilogue.
        MPYF32   R0H, R0H, R0H          ; R0H = Re[i]*Re[i]
     || MOV32    R2H, *XAR6++           ; R2H = Re[i+1]
        MPYF32   R1H, R1H, R1H          ; R1H = Im[i]*Im[i]
     || MOV32    R3H, *XAR6++           ; R3H = Im[i+1]
        SQRTF32  R6H, R6H               ; R6H = sqrt[(Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])]
        ADDF32   R4H, R1H, R0H          ; R0H = (Re[i]*Re[i]) + (Im[i]*Im[i])
     || MOV32    *XAR5++,R4H            ; Store mag[i]

        MPYF32   R2H, R2H, R2H          ; R2H = Re[i+1]*Re[i+1]
        MPYF32   R3H, R3H, R3H          ; R3H = Im[i+1]*Im[i+1]
        SQRTF32  R4H, R4H               ; R4H = sqrt[(Re[i]*Re[i]) + (Im[i]*Im[i])]
        ADDF32   R6H, R3H, R2H          ; R6H = (Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])
     || MOV32    *XAR5++,R6H            ; Store mag[i+1]

        NOP
        NOP
        SQRTF32  R0H, R6H               ; R0H = sqrt[(Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])]
        MOV32    *XAR5++,R4H            ; Store Mag[i]

        NOP
        MOV32    R6H,*--SP              ; Restore R6H
        MOV32    R4H,*--SP              ; Restore R4H
        MOV32    *XAR5++,R0H            ; Store mag[i+1]

;--- Finish up
        LRETR

;;#############################################################################
;;  End of File
;;#############################################################################
