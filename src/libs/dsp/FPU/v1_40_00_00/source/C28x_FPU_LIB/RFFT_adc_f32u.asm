; TI File $Revision: /main/2 $
; Checkin $Date: January 6, 2011   18:11:19 $
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
; FILE:  RFFT_adc_f32u.asm
;
; TITLE: Real FFT with 12-bit ADC input.
;
; DESCRIPTION:
;
;    This function calcuates a real FFT with 12-bit fixed-point ADC input.  
;    The input buffer does not have to be aligned.  If alignment can be 
;    done, then use the RFFT_adc_f32 function to improve performance.
;
; FUNCTIONS:
;
;    void RFFT_adc_f32u (RFFT_ADC_F32_STRUCT *)
;
;    Where RFFT_ADC_F32_STRUCT is a structure defined as:
;
;	 typedef struct {
;	  	Uint16   *InBuf;
;  		void	   *Tail;
;	 } RFFT_ADC_F32_STRUCT;
;
; ASSUMPTIONS:
;
;     * FFTSize must be a power of 2 (32, 64, 128, etc)
;     * FFTSize must be greater or equal to 32
;     * FFTStages must be log2(FFTSize)
;     * InBuf, OutBuf, CosSinBuf are FFTSize in length
;     * MagBuf and PhaseBuf are FFTSize/2 in length
;     * MagBuf and PhaseBuf are not used by this function.
;       They are only used by the magitude and phase calculation functions.
;
; ALGORITHUM:
;
; 1) Bit reverse input data and calculate stages 1, 2 & 3:
;
;  In Buf (read in bit reverse order)                             Out Buf
;  +----+                                                          +----+
;  | I1 | (((I1 + I2) + (I3 + I4)) + ((I5 + I6) + (I7 + I8)))/8 -> | I1'|
;  | I2 | ((I1 - I2) + COS*((I5 - I6) + (I8 - I7))          )/8 -> | I2'|
;  | I3 | ((I1 + I2) - (I3 + I4)                            )/8 -> | I3'|
;  | I4 | ((I1 - I2) - COS*((I5 - I6) + (I8 - I7))          )/8 -> | I4'|
;  | I5 | (((I1 + I2) + (I3 + I4)) - ((I5 + I6) + (I7 + I8)))/8 -> | I5'|
;  | I6 | (COS*((I8 - I7) - (I5 - I6)) - (I4 - I3)          )/8 -> | I6'|
;  | I7 | ((I7 + I8) - (I5 + I6)                            )/8 -> | I7'|
;  | I8 | (COS*((I8 - I7) - (I5 - I6)) + (I4 - I3)          )/8 -> | I8'|
;     .
;     .
;    \|/
; Repeat above FFTSize/8 (i.e. if FFTSize = 1024, Repeat = 128 times)
;
; Note: COS = COS( 1*2*PI/8) = SIN( 1*2*PI/8)
;
; 2) Calculate stages 4 and up:
;
;
;             Out Buf   4   5   6   7   8   9   10  <- Stages
; +-        +---------+ -   -   -   -   -   -   --
; |         |    Y1   | 0   0   0   0   0   0    0  <-   Y1 + Y3
; |         |---------|
; |         |  X(I1)  | 1   1   1   1   1   1    1  <-   X(I1) + [X(I3)*COS + X(I4)*SIN]
; |         |---------|
; |         |    .    |
; |         |    .    | 3   7  15  31  63 127  255  <-   Inner Loop Repeat Times
; |         |   \./   |
; |  I      |---------|
; |  N      |    Y2   | 4   8  16  32  64 128  256  <-   Y2
; |  N      |---------|
; |  E      |   /.\   |
; |  R      |    .    |
; |         |    .    |
; |  L      |---------|
; |  O      |  X(I2)  | 7  15  31  63 127 255  511 <-   X(I1) - [X(I3)*COS + X(I4)*SIN]
; |  O      |---------|
; |  P      |    Y3   | 8  16  32  64 128 256  512 <-   Y1 - Y3
; |         |---------|
; |         |  X(I3)  | 9  17  33  65 129 257  513 <-   [X(I4)*COS - X(I3)*SIN] - X(I2)
; |         |---------|
; |         |    .    |
; |         |    .    |
; |         |   \./   |
; |         |---------|
; |         |    Y4   |12  24  48  96 192 384  768 <-   -Y4
; |         |---------|
; |         |   /.\   |
; |         |    .    |
; |         |    .    |
; |         |---------|
; |         |  X(I4)  |15  31  63 127 255 511 1023 <-   [X(I4)*COS - X(I3)*SIN] + X(I2)
; +-        |---------|
;           |         |16  32  64 128 256 512 1024
;                      -- --- --- --- --- --- ----
;                .      1                          <-   Outer Loop Repeat Times (16   FFT)
;                .      2   1                      <-   Outer Loop Repeat Times (32   FFT)
;                .      4   2   1                  <-   Outer Loop Repeat Times (64   FFT)
;                .      8   4   2   1              <-   Outer Loop Repeat Times (128  FFT)
;                .     16   8   4   2   1          <-   Outer Loop Repeat Times (256  FFT)
;                .     32  16   8   4   2   1      <-   Outer Loop Repeat Times (512  FFT)
;                .     64  32  16   8   4   2    1 <-   Outer Loop Repeat Times (1024 FFT)
;                .
;                .
;               \|/
; ###########################################################################
; $TI Release: C28x Floating Point Unit Library V1.40.00.00 $
; $Release Date: Mar 10, 2014 $
; ###########################################################################

;===========================================================================
; Function: void RFFT_adc_f32u(RFFT_ADC_F32_STRUCT *rfft)
;===========================================================================

       .global    _RFFT_adc_f32u
       .ref       _rfft_adc_f32_Stages4andUp
       .sect      .text

_RFFT_adc_f32u:
       ADDB 	  SP,#2
       MOVL 	  *-SP[2],XAR4
       LCR  	  _rfft_adc_f32u_Stages1and2and3andBitReverse
;      MOVL 	  XAR4,*-SP[2]            ;comment this out only for adc version of RFFT
       LCR  	  _rfft_adc_f32_Stages4andUp
       SUBB 	  SP,#2
       LRETR

; ================================================================================
; Function: void rfft_adc_f32u_Stages1and2and3andBitReverse(RFFT_ADC_F32_STRUCT *rfft)
; ================================================================================
;---------------------------------------------------------------------------
;
; DESCRIPTION:
;
;     This function bit reverses the input and computes stages 1, 2 and 3
;     This function does not have any alignment requirements for the input
;     buffer.
;
; ON ENTRY:
;
;     XAR4 = Starting address of the RFFT_F32_STRUCT structure
;
; REGISTER USAGE:
;
;     AR0, XAR1, XAR2, XAR4, XAR5, AR3, AR6, XAR7, ACC,
;     R0H, R1H, R2H, R3H, R4H, R5H, R6H, R7H
;
; On Exit:
;
;     RFFT_F32_STRUCT OutBuf contains the computed result
;
;---------------------------------------------------------------------------
;offsets to the stack which holds the bit reversed elements
;---------------------------------------------------------------------------

I1         .set 06H
I2         .set 08H
I3         .set 0AH
I4         .set 0CH
I5         .set 0EH
I6         .set 10H
I7         .set 12H
I8         .set 14H
cossinBuf  .set 04H
;--------------------------------------------------------------------------------
;Offset to the stack which holds intermediate results of FFT computation
;-------------------------------------------------------------------------------
           .text

_rfft_adc_f32u_Stages1and2and3andBitReverse:
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
        ADDB     SP,#14h

        MOVL     XAR2,*+XAR4[0]         ; &Inbuf
        MOVL     XAR5,*+XAR4[2]         ; &Outbuf
        SUBB     XAR5, #2
        MOVL	 XAR4, XAR5
        MOVL	 XAR5,*+XAR4[2]
        MOVL     XAR3,*+XAR4[2]
        ADDB     XAR3,#8                ; &Outbuf[4]
        MOVL     XAR7,*+XAR4[4]         ; &CosSinbuf

        MOV      AR0,#0Ah
        MOV      AH,*+XAR4[AR0]         ; FFT SIZE
        LSR      AH,1                   ; FFT SIZE/2 - for 16-bit input data
        MOV      AR0,AH
;       LSR      AH,3
        LSR      AH,2                   ; for 16-bit input data
        SUBB     AH,#1                  ; (Size / 8) - 1  3f
        MOVL     XAR1,#0000h            ; index if memory is not aligned

        RPTB    _rfft_32_Last, AH
;--------------------------------------------------------------------------------
; Code assumes no aligment
; Assumes ADC integer data is the input
; Convert and scale while bit reversing
;--------------------------------------------------------------------------------
        MOVI32    R2H, 0x39800801
        NOP       *,ARP1
        UI16TOF32 R0H, *+XAR2[AR1]      ;I1 load
        NOP       *,ARP1
        NOP       *BR0++       
        MPYF32    R0H, R0H, R2H         ;I1 scale        
        UI16TOF32 R1H, *+XAR2[AR1]      ;I2 load                
        NOP       *,ARP1
        MPYF32    R1H, R1H, R2H         ;I2 scale       
     || MOV32     *-SP[I1], R0H         ;I1 save
        NOP       *BR0++        
        UI16TOF32 R0H, *+XAR2[AR1]      ;I3 load
        NOP       *,ARP1
        MPYF32    R0H, R0H, R2H         ;I3 scale
     || MOV32     *-SP[I2], R1H         ;I2 save
        NOP       *BR0++
        UI16TOF32 R1H, *+XAR2[AR1]      ;I4 load
        NOP       *,ARP1
        MPYF32    R1H, R1H, R2H         ;I4 scale
     || MOV32     *-SP[I3], R0H         ;I5 save       
        NOP       *BR0++
        UI16TOF32 R0H, *+XAR2[AR1]      ;I5 load
        NOP       *,ARP1
        MPYF32    R0H, R0H, R2H         ;I5 scale
     || MOV32     *-SP[I4], R1H         ;I4 save
        NOP       *BR0++
        UI16TOF32 R1H, *+XAR2[AR1]      ;I6 load
        NOP       *,ARP1
        MPYF32    R1H, R1H, R2H         ;I6 scale
     || MOV32     *-SP[I5], R0H         ;I5 save
        NOP       *BR0++
        UI16TOF32 R0H, *+XAR2[AR1]      ;I7 load
        NOP       *,ARP1
        MPYF32    R0H, R0H, R2H         ;I7 scale
     || MOV32     *-SP[I6], R1H         ;I6 store
        NOP       *BR0++
        UI16TOF32 R1H, *+XAR2[AR1]      ;I8 load
        NOP       *,ARP1
        MPYF32    R1H, R1H, R2H         ;I8 scale
     || MOV32     *-SP[I7], R0H         ;I7 store
        NOP       *BR0++
        MOV32     *-SP[I8], R1H         ;I8 store
        
;-------------------------------------------------------------------------------
; Computations for stages 1 2, and 3
;   OutBufIndex++ = (I1 + I2) + (I3 + I4) + (I5 + I6) + (I7 + I8);      (A)  <- XAR5
;   OutBufIndex++ = (I1 - I2) + COS x ((I5 - I6) + (I8 - I7));          (B)
;   OutBufIndex++ = (I1 + I2) - (I3 + I4);                              (C)
;   OutBufIndex++ = (I1 - I2) - COS x ((I5 - I6) + (I8 - I7));          (D)
;   OutBufIndex++ = ((I1 + I2) + (I3 + I4)) - ((I5 + I6) + (I7 + I8));  (E)  <- XAR3
;   OutBufIndex++ = COS x ((I8 - I7) - (I5 - I6)) - (I4 - I3);          (F)
;   OutBufIndex++ = (I7 + I8) - (I5 + I6);                              (G)
;   OutBufIndex++ = COS x ((I8 - I7) - (I5 - I6)) + (I4 - I3);          (H)
;-------------------------------------------------------------------------------
        MOV32       R0H, *-SP[I8]           ; R0H   = I8
        MOV32       R1H, *-SP[I7]           ; R1H   = I7
        SUBF32      R2H, R0H, R1H           ; R2H   = I8-I7
     || MOV32       R3H, *-SP[I5]           ; R3H   = I5
        ADDF32      R0H, R1H, R0H           ; R0H   = I7+I8
     || MOV32       R4H, *-SP[I6]           ; R4H   = I6
        SUBF32      R1H, R3H, R4H           ; R1H   = I5-I6
     || MOV32       R5H, *-SP[I1]           ; R5H   = I1
        ADDF32      R3H, R3H, R4H           ; R3H   = I5+I6
        ADDF32      R4H, R1H, R2H           ; R4H   = (I5-I6) + (I8-I7)
     || MOV32       R6H,*XAR7               ; R6H   = COS
        SUBF32      R7H, R0H, R3H           ; R7H   = (I7+I8) - (I5+I6)  (G)
        MPYF32      R4H, R6H, R4H           ; R4H   = COS x ((I5-I6) + (I8-I7))
     || SUBF32      R2H, R2H, R1H           ; R2H   = (I8-I7) - (I5-I6)
        ADDF32      R0H, R3H, R0H           ; R0H   = (I5+I6) + (I7+I8)
     || MOV32       *+XAR3[4], R7H          ; store G
        MPYF32      R2H, R6H, R2H           ; R2H   = COS x ((I8-I7) - (I5-I6))
     || MOV32       R7H, *-SP[I2]           ; R7H   = I2
        SUBF32      R6H, R5H, R7H           ; R6H   = I1-I2
        ADDF32      R5H, R5H, R7H           ; R5H   = I1+I2
     || MOV32       R1H, *-SP[I4]           ; R1H   = I4
        ADDF32      R3H, R6H, R4H           ; R3H   = (I1-I2) + COS x ((I5-I6) + (I8-I7))  (B)
     || MOV32       R7H, *-SP[I3]           ; R7H   = I3
        SUBF32      R6H, R6H, R4H           ; R6H   = (I1-I2) - COS x ((I5-I6) + (I8-I7))  (D)
        SUBF32      R3H, R1H, R7H           ; R3H   = I4-I3
     || MOV32       *+XAR5[2], R3H          ; store B
        ADDF32      R4H, R7H, R1H           ; R4H   = I3+I4
     || MOV32       *+XAR5[6], R6H          ; store D
        SUBF32      R1H, R2H, R3H           ; R1H = COS x ((I8-I7) - (I5-I6)) - (I4-I3)  (F)
        ADDF32      R2H, R2H, R3H           ; R2H = COS x ((I8-I7) - (I5-I6)) + (I4-I3)  (H)
        ADDF32      R6H, R5H, R4H           ; R6H   = (I1+I2) + (I3+I4)
     || MOV32       *+XAR3[2], R1H          ; save F
        SUBF32      R1H, R5H, R4H           ; R1H   = (I1+I2) - (I3+I4)   (C)
     || MOV32       *+XAR3[6], R2H          ; save H
        SUBF32      R3H, R6H, R0H           ; R3H   = (I1+I2) + (I3+I4) - ((I5+I6) + (I8+I7)) (E)
        ADDF32      R0H, R6H, R0H           ; R0H   = (I1+I2) + (I3+I4) + (I5+I6) + (I8+I7) (A)
     || MOV32       *+XAR5[4], R1H          ; store C
        MOV32       *+XAR3[0], R3H          ; store E
        MOV32       *+XAR5[0], R0H          ; store A
        ADDB        XAR5, #16
        ADDB        XAR3, #16


_rfft_32_Last:
        SUBB        SP,#14h
        MOV32       R7H,*--SP
        MOV32       R6H,*--SP
        MOV32       R5H,*--SP
        MOV32       R4H,*--SP
        POP         XAR3
        POP         XAR2
        POP         XAR1
        LRETR

;--------------------------------------------------------------------------
;            Copyright (c) 2014-2015 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================

