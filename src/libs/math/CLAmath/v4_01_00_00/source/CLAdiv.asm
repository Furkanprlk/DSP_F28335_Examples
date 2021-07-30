;;#############################################################################
;; 
;; FILE: CLAdiv.asm
;; 
;; DESCRIPTION: CLA divide function using Newton Raphson Approximation
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
;; Description: Implement division using Newton-Raphson Method
;;
;; Equation:    Dest = Num/Den
;;
;; Regs Used:   MR0, MR1, MR2, MR3
;;
;; Input:   Num         f32 value in memory
;;          Den         f32 value in memory
;;
;; Output:  Dest        f32 value in memory
;;          MR0 = Dest  f32 result
;;
;; Benchmark:   Cycles = 13
;;              Instructions = 13
;;
;; Scratchpad Usage: (Local Function Scratchpad Pointer (SP))
;;
;;   |_______|<- MR1                               (SP+2)
;;   |_______|<- MR3                               (SP+0)
;;
;;----------------------------------------------------------------------------  



    .def    _CLAdiv
    .sect   "Cla1Prog:_CLAdiv"
    .align  2
__CLAdiv_sp .usect ".scratchpad:Cla1Prog:_CLAdiv",4,0,1

_CLAdiv:
    .asmfunc
    .asg    __CLAdiv_sp + 0, _save_MR3
    .asg    __CLAdiv_sp + 2, _save_MR1
; Context Save
    MMOV32    @_save_MR3, MR3
      
; MR0 = Numerator
; MR1 = Denominator 
    MEINVF32  MR2,MR1          ; MR2 = Ye = Estimate(1/Den)
    MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
 || MMOV32    @_save_MR1, MR1  ; save off denominator
    MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
    MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
    MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
    MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
    MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
 || MMOV32    MR1, @_save_MR1  ; Reload denominator to set sign
    MNEGF32   MR0,MR0,EQ       ; Optional: if(Den == 0.0) Change Sign Of Num 
; Context Restore and Final Operations
    MRCNDD    UNC
    MMPYF32   MR0,MR2,MR0      ; MR0 = Y = Ye*Num
    MMOV32    MR0,MR0          ; Optional: Set/Clear MSTF NF and ZF flags
    MMOV32    MR3,@_save_MR3 
    .unasg  _save_MR3
    .unasg  _save_MR1
    .endasmfunc
    
;; End of File
 
