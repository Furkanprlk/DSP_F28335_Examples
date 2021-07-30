;;#############################################################################
;; 
;; FILE: CLAsqrt.asm
;; 
;; DESCRIPTION: CLA square root function using Newton Raphson 
;;              Approximation
;; 
;; Group:            C2000
;; Target Family:    C28x+CLA
;;
;; Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
;; ALL RIGHTS RESERVED
;;#############################################################################
;;$TI Release: CLA Math Library V4.01.00.00 $
;;$Release Date: Apr 6, 2016 $
;;#############################################################################


    .cdecls C,LIST,"CLAmath.h"

;;----------------------------------------------------------------------------
;; Description: Implement square root using Newton-Raphson Method
;;
;; Equation:    y = sqrt(x)
;;
;; Regs Used:   MR0, MR1, MR2, MR3
;;
;; Input:   x           f32 value in memory
;;
;; Output:  y           f32 value in memory
;;          MR0 = y     f32 result
;;
;; Benchmark:   Cycles = 16
;;          Instructions = 16
;;
;; Scratchpad Usage: (Local Function Scratchpad Pointer (SP))
;;
;;   |_______|<- square root temporary variable    (SP+2)
;;   |_______|<- MR3                               (SP+0)
;;
;;----------------------------------------------------------------------------  

    .def    _CLAsqrt
    .sect   "Cla1Prog:_CLAsqrt"
    .align  2
__CLAsqrt_sp    .usect ".scratchpad:Cla1Prog:_CLAsqrt",4,0,1

_CLAsqrt:
    .asmfunc
    .asg __CLAsqrt_sp + 0, _save_MR3
    .asg __CLAsqrt_sp + 2, _sqrt_tmp
; Context Save
    MMOV32      @_save_MR3, MR3
    MMOV32      MR0, MR0        ; Dummy load of MR0 will set/clear ZF
                                ; useful if the compiler load is done with
                                ; a MUInTOF32 which does not alter the ZF bit
; MR0 = Number
    MEISQRTF32  MR1,MR0         ; MR1 = Ye = Estimate(1/sqrt(X))
    MMOV32      MR1,MR0,EQ      ; if(X == 0.0) Ye = 0.0
    MMPYF32     MR3,MR0,#0.5    ; MR3 = X*0.5
    MMPYF32     MR2,MR1,MR3     ; MR2 = Ye*X*0.5
    MMPYF32     MR2,MR1,MR2     ; MR2 = Ye*Ye*X*0.5
    MSUBF32     MR2,#1.5,MR2    ; MR2 = 1.5 - Ye*Ye*X*0.5
    MMPYF32     MR1,MR1,MR2     ; MR1 = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
    MMPYF32     MR2,MR1,MR3     ; MR2 = Ye*X*0.5
    MMPYF32     MR2,MR1,MR2     ; MR2 = Ye*Ye*X*0.5
    MSUBF32     MR2,#1.5,MR2    ; MR2 = 1.5 - Ye*Ye*X*0.5
; Context Restore and Final Operations
    MRCNDD      UNC
    MMPYF32     MR1,MR1,MR2     ; MR1 = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
    MMPYF32     MR0,MR1,MR0     ; MR0 = Y = Ye*X
    MMOV32      MR3,@_save_MR3 
    .unasg  _save_MR3
    .unasg  _sqrt_tmp
    .endasmfunc

;; End of File
 
