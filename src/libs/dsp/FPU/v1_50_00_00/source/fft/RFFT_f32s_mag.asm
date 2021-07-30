;;#############################################################################
;;! \file source/fft/RFFT_f32s_mag.asm
;;!
;;! \brief  Real FFT scaled magnitude calculations
;;! \author David M. Alter
;;! \date   11/20/14
;;! 
;; DESCRIPTION:
;;
;;   Calculates the scaled magnitude for the 32-bit floating point real FFT.
;;
;; HISTORY:
;;   11/20/14 - optimized v1.40.00.00 function. (D. Alter)
;;
;; FUNCTIONS:
;;
;;    void RFFT_f32s_mag (RFFT_F32_STRUCT_Handle)
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
;;     Calculate the real FFT scaled  magnitude. The data is organized as 
;;     follows in the output buffer after calculating FFT:
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
;; The loop was spatially unrolled once to eliminate FPU delay slots.
;;
;; BENCHMARK: 19 cycles/complex value + overhead
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
;RFFT_InBuf             .set        (0*2)
;RFFT_OutBuf            .set        (1*2)
;RFFT_CosSinBuf         .set        (2*2)
;RFFT_MagBuf            .set        (3*2)
;RFFT_PhaseBuf          .set        (4*2)
;RFFT_FFTSize           .set        (5*2)
;RFFT_FFTStages         .set        (RFFT_FFTSize+1)
;----------------------------------------------------------------------


    .global _RFFT_f32s_mag
    .text

_RFFT_f32s_mag:

        MOV32    *SP++, R4H            ; Save R4H (save-on-entry register)
        MOV32    *SP++, R5H            ; Save R5H (save-on-entry register)
        MOV32    *SP++, R6H            ; Save R6H (save-on-entry register)
        MOV32    *SP++, R7H            ; Save R7H (save-on-entry register)

        MOVL     XAR6, *+XAR4[2]      ; XAR6 = Rptr = &OutBuf[0]
        MOVL     XAR5, *+XAR4[6]      ; XAR5 = &MagBuf

        ADDB     XAR4, #10            ; Move the structure pointer up

;--- Calculate the scale factor
        MOV      AL, *+XAR4[1]        ; AL = FFTStages
        SUBB     AL, #2               ; AL = scale_value counter
        B _rfft_f32s_mag_end, LEQ     ; If stages < 3, end the function
        MOV      AR7, AL              ; AR7 = scale_value counter

        MOVIZF32 R7H, #1.0            ; R7H = 1.0
_cfft_f32s_scale_value:
        MPYF32   R7H, R7H, #0.5       ; R7H = scale
        BANZ _cfft_f32s_scale_value, AR7--

        MPYF32   R7H, R7H, R7H        ; R7H = scale*scale

;--- Calculate pointer to imaginary part results
        MOV      ACC, *+XAR4[0] << 1  ; ACC = 2*FFTSize
        ADDL     ACC, XAR6            ; Add OutBuff address
        MOVL     XAR7, ACC            ; XAR7 = Iptr = &OutBuf[last value]

;--- Calculate main loop count
        MOV      AL, *+XAR4[0]        ; AL = FFTSize
        LSR      AL, #2               ; AL = FFTSize/4
        SUBB     AL, #2               ; mag[0:1] handled separately, and "N-1" 
                                      ; loop count so subtract 2

        MOV32    *SP++, R7H           ; Save scale to stack

;----------------------------------------------------------------------
;     Begin magnitude calculations
;----------------------------------------------------------------------

;--- Mag[0] is handled special since no Im part
        MOV32    R0H, *XAR6++         ; R0H = Re[0]
        MPYF32   R0H, R0H, R0H        ; R0H = Re[0]*Re[0]
        NOP
        MPYF32   R0H, R0H, R7H        ; R0H = scale*(Re[0]*Re[0])
        NOP

    ;--- Do the sqrt
        EISQRTF32   R1H, R0H          ; R1H = Ye[0] = Estimate(1/sqrt(X[0]))
        MPYF32      R2H, R0H, #0.5    ; R2H = X[0]*0.5
        MPYF32      R3H, R1H, R1H     ; R3H = Ye[0]*Ye[0]
        NOP
        MPYF32      R3H, R3H, R2H     ; R3H = Ye[0]*Ye[0]*X[0]*0.5
        NOP
        SUBF32      R3H, #1.5, R3H    ; R3H = 1.5 - Ye[0]*Ye[0]*X[0]*0.5
        NOP
        MPYF32      R1H, R1H, R3H     ; R2H = Ye[0] = Ye[0]*(1.5 - Ye[0]*Ye[0]*X[0]*0.5)
        NOP
        MPYF32      R3H, R1H, R2H     ; R3H = Ye[0]*X[0]*0.5
        NOP
        MPYF32      R3H, R1H, R3H     ; R3H = Ye[0]*Ye[0]*X[0]*0.5
        NOP
        SUBF32      R3H, #1.5, R3H    ; R3H = 1.5 - Ye[0]*Ye[0]*X[0]*0.5
        CMPF32      R0H, #0.0         ; Check if X[0] == 0
        MPYF32      R1H, R1H, R3H     ; R2H = Ye[0] = Ye[0]*(1.5 - Ye[0]*Ye[0]*X[0]*0.5)
        NOP
        MOV32       R1H, R0H, EQ      ; If X[0] is zero, change the Ye[0] estimate to 0
        MPYF32      R0H, R0H, R1H     ; R0H = Y[0] = X[0]*Ye[0] = sqrt(X[0])
        NOP

    ;--- Store the result
        MOV32    *XAR5++, R0H         ; Store mag[0]

;--- Must also compute Mag[1] separately to keep an even number of mag 
;    computations in the main loop

    ;--- Compute magnitude squared
        MOV32    R0H, *XAR6++         ; R0H = Re[1]
        MPYF32   R0H, R0H, R0H        ; R0H = Re[1]*Re[1]
     || MOV32    R1H, *--XAR7         ; R1H = Im[1]
        MPYF32   R1H, R1H, R1H        ; R1H = Im[1]*Im[1]
        NOP
        ADDF32   R0H, R0H, R1H        ; R0H = (Re[1]*Re[1]) + (Im[1]*Im[1])
        NOP
        MPYF32   R0H, R0H, R7H        ; R0H = scale*[(Re[1]*Re[1]) + (Im[1]*Im[1])]
        NOP

    ;--- Do the sqrt
        EISQRTF32   R1H, R0H          ; R1H = Ye[1] = Estimate(1/sqrt(X[1]))
        MPYF32      R2H, R0H, #0.5    ; R2H = X[1]*0.5
        MPYF32      R3H, R1H, R1H     ; R3H = Ye[1]*Ye[1]
        NOP
        MPYF32      R3H, R3H, R2H     ; R3H = Ye[1]*Ye[1]*X[1]*0.5
        NOP
        SUBF32      R3H, #1.5, R3H    ; R3H = 1.5 - Ye[1]*Ye[1]*X[1]*0.5
        NOP
        MPYF32      R1H, R1H, R3H     ; R2H = Ye[1] = Ye[1]*(1.5 - Ye[1]*Ye[1]*X[1]*0.5)
        NOP
        MPYF32      R3H, R1H, R2H     ; R3H = Ye[1]*X[1]*0.5
        NOP
        MPYF32      R3H, R1H, R3H     ; R3H = Ye[1]*Ye[1]*X[1]*0.5
        NOP
        SUBF32      R3H, #1.5, R3H    ; R3H = 1.5 - Ye[1]*Ye[1]*X[1]*0.5
        CMPF32      R0H, #0.0         ; Check if X[1] == 0
        MPYF32      R1H, R1H, R3H     ; R2H = Ye[1] = Ye[1]*(1.5 - Ye[1]*Ye[1]*X[1]*0.5)
        NOP
        MOV32       R1H, R0H, EQ      ; If X[1] is zero, change the Ye[1] estimate to 0
        MPYF32      R0H, R0H, R1H     ; R0H = Y[1] = X[1]*Ye[1] = sqrt(X[1])
        NOP

    ;--- Store the result
        MOV32    *XAR5++, R0H         ; Store mag[1]

;--- Main loop

        RPTB _rfft_f32s_mag_end, @AL

    ;--- Compute magnitude squared

        MOV32    R0H, *XAR6++         ; R0H = Re[i]
        MPYF32   R0H, R0H, R0H        ; R0H = Re[i]*Re[i]
     || MOV32    R1H, *--XAR7         ; R1H = Im[i]

        MOV32    R4H, *XAR6++         ; R4H = Re[i+1]
        MPYF32   R4H, R4H, R4H        ; R4H = Re[i+1]*Re[i+1]
     || MOV32    R5H, *--XAR7         ; R5H = Im[i+1]

        MPYF32   R1H, R1H, R1H        ; R1H = Im[i]*Im[i]
        MPYF32   R5H, R5H, R5H        ; R5H = Im[i+1]*Im[i+1]

        ADDF32   R0H, R1H, R0H        ; R0H = (Re[i]*Re[i]) + (Im[i]*Im[i])
        ADDF32   R4H, R5H, R4H        ; R4H = (Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])
     || MOV32    R7H, *-SP[2]         ; R7H = scale

        MPYF32   R0H, R0H, R7H        ; R0H = scale*[(Re[i]*Re[i]) + (Im[i]*Im[i])]
        MPYF32   R4H, R4H, R7H        ; R4H = scale*[(Re[i+1]*Re[i+1]) + (Im[i+1]*Im[i+1])]

    ;--- Do the sqrt

        EISQRTF32   R1H, R0H          ; R1H = Ye[i] = Estimate(1/sqrt(X[i]))
        EISQRTF32   R5H, R4H          ; R5H = Ye[i+1] = Estimate(1/sqrt(X[i+1]))

        MPYF32      R2H, R0H, #0.5    ; R2H = X[i]*0.5
        MPYF32      R6H, R4H, #0.5    ; R6H = X[i+1]*0.5

        MPYF32      R3H, R1H, R1H     ; R3H = Ye[i]*Ye[i]
        MPYF32      R7H, R5H, R5H     ; R7H = Ye[i+1]*Ye[i+1]

        MPYF32      R3H, R3H, R2H     ; R3H = Ye[i]*Ye[i]*X[i]*0.5
        MPYF32      R7H, R7H, R6H     ; R7H = Ye[i+1]*Ye[i+1]*X[i+1]*0.5

        SUBF32      R3H, #1.5, R3H    ; R3H = 1.5 - Ye[i]*Ye[i]*X[i]*0.5
        SUBF32      R7H, #1.5, R7H    ; R7H = 1.5 - Ye[i+1]*Ye[i+1]*X[i+1]*0.5

        MPYF32      R1H, R1H, R3H     ; R2H = Ye[i] = Ye[i]*(1.5 - Ye[i]*Ye[i]*X[i]*0.5)
        MPYF32      R5H, R5H, R7H     ; R6H = Ye[i+1] = Ye[i+1]*(1.5 - Ye[i+1]*Ye[i+1]*X[i+1]*0.5)

        MPYF32      R3H, R1H, R2H     ; R3H = Ye[i]*X[i]*0.5
        MPYF32      R7H, R5H, R6H     ; R7H = Ye[i+1]*X[i+1]*0.5

        MPYF32      R3H, R1H, R3H     ; R3H = Ye[i]*Ye[i]*X[i]*0.5
        MPYF32      R7H, R5H, R7H     ; R7H = Ye[i+1]*Ye[i+1]*X[i+1]*0.5

        SUBF32      R3H, #1.5, R3H    ; R3H = 1.5 - Ye[i]*Ye[i]*X*0.5
        CMPF32      R0H, #0.0         ; Check if X[i] == 0
        MPYF32      R1H, R1H, R3H     ; R1H = Ye[i] = Ye[i]*(1.5 - Ye[i]*Ye[i]*X[i]*0.5)

        SUBF32      R7H, #1.5, R7H    ; R7H = 1.5 - Ye[i+1]*Ye[i+1]*X[i+1]*0.5
        MOV32       R1H, R0H, EQ      ; If X[i] is zero, change the Ye[i] estimate to 0
        CMPF32      R4H, #0.0         ; Check if X[i+1] == 0
        MPYF32      R5H, R5H, R7H     ; R5H = Ye[i+1] = Ye[i+1]*(1.5 - Ye[i+1]*Ye[i+1]*X[i+1]*0.5)

        MPYF32      R0H, R0H, R1H     ; R0H = Y[i] = X[i]*Ye[i] = sqrt(X[i])
        MOV32       R5H, R4H, EQ      ; If X[i+1] is zero, change the Ye[i+1] estimate to 0
        MPYF32      R4H, R4H, R5H     ; R4H = Y[i+1] = X[i+1]*Ye[i+1] = sqrt(X[i+1])

    ;--- Store the result
        MOV32     *XAR5++, R0H        ; Store Mag[i]
        MOV32     *XAR5++, R4H        ; Store Mag[i+1]

_rfft_f32s_mag_end:

;--- Mag[N/2+1] is handled special since no Im part
        MOV32    R0H, *XAR6++         ; R0H = Re[N/2+1]
        MPYF32   R0H, R0H, R0H        ; R0H = Re[N/2+1]*Re[N/2+1]
        MOV32    R7H, *-SP[2]         ; R7H = scale
        MPYF32   R0H, R0H, R7H        ; R0H = scale*(Re[N/2+1]*Re[N/2+1])
        NOP

    ;--- Do the sqrt
        EISQRTF32   R1H, R0H          ; R1H = Ye[N/2+1] = Estimate(1/sqrt(X[N/2+1]))
        MPYF32      R2H, R0H, #0.5    ; R2H = X[N/2+1]*0.5
        MPYF32      R3H, R1H, R1H     ; R3H = Ye[N/2+1]*Ye[N/2+1]
        NOP
        MPYF32      R3H, R3H, R2H     ; R3H = Ye[N/2+1]*Ye[N/2+1]*X[N/2+1]*0.5
        NOP
        SUBF32      R3H, #1.5, R3H    ; R3H = 1.5 - Ye[N/2+1]*Ye[N/2+1]*X[N/2+1]*0.5
        NOP
        MPYF32      R1H, R1H, R3H     ; R2H = Ye[N/2+1] = Ye[N/2+1]*(1.5 - Ye[N/2+1]*Ye[N/2+1]*X[N/2+1]*0.5)
        NOP
        MPYF32      R3H, R1H, R2H     ; R3H = Ye[N/2+1]*X[N/2+1]*0.5
        NOP
        MPYF32      R3H, R1H, R3H     ; R3H = Ye[N/2+1]*Ye[N/2+1]*X[N/2+1]*0.5
        NOP
        SUBF32      R3H, #1.5, R3H    ; R3H = 1.5 - Ye[N/2+1]*Ye[N/2+1]*X[N/2+1]*0.5
        CMPF32      R0H, #0.0         ; Check if X[N/2+1] == 0
        MPYF32      R1H, R1H, R3H     ; R2H = Ye[N/2+1] = Ye[N/2+1]*(1.5 - Ye[N/2+1]*Ye[N/2+1]*X[N/2+1]*0.5)
        NOP
        MOV32       R1H, R0H, EQ      ; If X[N/2+1] is zero, change the Ye[N/2+1] estimate to 0
        MPYF32      R0H, R0H, R1H     ; R0H = Y[N/2+1] = X[N/2+1]*Ye[N/2+1] = sqrt(X[N/2+1])
        NOP

    ;--- Store the result
        MOV32    *XAR5++, R0H         ; Store mag[N/2+1]

;--- Finish up
        SUBB     SP, #2               ; Deallocate local frame
        MOV32    R7H, *--SP           ; Restore R7H
        MOV32    R6H, *--SP           ; Restore R6H
        MOV32    R5H, *--SP           ; Restore R5H
        MOV32    R4H, *--SP           ; Restore R4H
        LRETR
       

;;#############################################################################
;;  End of File
;;#############################################################################

