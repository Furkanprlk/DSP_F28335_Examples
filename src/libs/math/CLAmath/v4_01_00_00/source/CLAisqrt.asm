;;#############################################################################
;; 
;; FILE: CLAisqrt.asm
;; 
;; DESCRIPTION: CLA inverse square root function using Newton Raphson 
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
;; Description: Implement 1/(square root) using Newton-Raphson Method
;;
;; Equation:    y = 1/(sqrt(x))
;;
;; Regs Used:   MR0, MR1, MR2, MR3
;;
;; Input:   x           f32 value in memory
;;
;; Output:  y           f32 value in memory
;;          MR0 = y     f32 result
;;
;; Benchmark:   Cycles = 14
;;              Instructions = 14
;;
;; Scratchpad Usage: (Local Function Scratchpad Pointer (SP))
;;
;;   |_______|<- MR3                               (SP+0)
;;
;;----------------------------------------------------------------------------  

    .def    _CLAisqrt
    .sect   "Cla1Prog:_CLAisqrt"
    .align  2
__CLAisqrt_sp   .usect ".scratchpad:Cla1Prog:_CLAisqrt",2,0,1
    
_CLAisqrt:
    .asmfunc
    .asg    __CLAisqrt_sp + 0, _save_MR3
; Context Save
    MMOV32      @_save_MR3, MR3
; MR0 = Number
    MEISQRTF32  MR1, MR0        ; MR1 = Ye = Estimate(1/sqrt(X))        
    MMPYF32     MR2, MR0, #0.5  ; MR2 = X*0.5
    MMPYF32     MR3, MR1, MR1   ; MR3 = Ye*Ye
    MMPYF32     MR3, MR3, MR2   ; MR3 = Ye*Ye*X*0.5
    MSUBF32     MR3, #1.5,MR3   ; MR3 = 1.5 - Ye*Ye*X*0.5
    MMPYF32     MR1, MR1, MR3   ; MR1 = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
    MMPYF32     MR3, MR1, MR2   ; MR3 = Ye*X*0.5
    MMPYF32     MR3, MR1, MR3   ; MR3 = Ye*Ye*X*0.5
    MSUBF32     MR3, #1.5,MR3   ; MR3 = 1.5 - Ye*Ye*X*0.5        
; Context Restore and Final Operations
    MRCNDD      UNC
    MMPYF32     MR0, MR1, MR3   ; MR0 = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
    MMOV32      MR0, MR0        ; Optional: set MSTF NF and ZF flags
    MMOV32      MR3,@_save_MR3 
    .unasg  _save_MR3
    .endasmfunc

;; End of File
 
