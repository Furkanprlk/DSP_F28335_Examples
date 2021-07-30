;******************************************************************************
; 
; FILE: CLAdiv.asm
; 
; DESCRIPTION: CLA divide function using Newton Raphson Approximation
; 
;******************************************************************************
;  $TI Release: CLA Math Library for CLA C Compiler V4.00.01.00 $
;  $Release Date: Apr 23, 2014 $
;******************************************************************************
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2014 Texas Instruments, Incorporated.
;                          All Rights Reserved.
;******************************************************************************

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
;; Benchmark:   Cycles = 16
;;              Instructions = 16
;;----------------------------------------------------------------------------  


	.sect "Cla1Prog"
	.def _CLAdiv

_save_MR3 .usect "CLAscratch",2
_save_MR1 .usect "CLAscratch",2

_CLAdiv:
; Context Save
	  MMOV32    @_save_MR3, MR3
	  
; MR0 = Numerator
; MR1 = Denominator	
      MEINVF32  MR2,MR1          ; MR2 = Ye = Estimate(1/Den)
      MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
  ||  MMOV32    @_save_MR1, MR1  ; save off denominator
      MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
      MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
      MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
      MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
      MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
  ||  MMOV32    MR1, @_save_MR1  ; Reload denominator to set sign
      MNEGF32   MR0,MR0,EQ       ; Optional: if(Den == 0.0) Change Sign Of Num 
      MMPYF32   MR0,MR2,MR0      ; MR0 = Y = Ye*Num
      MMOV32    MR0,MR0          ; Optional: Set/Clear MSTF NF and ZF flags
; Context Restore
	  MMOV32    MR3,@_save_MR3 
      MRCNDD    UNC
      MNOP
      MNOP
      MNOP
