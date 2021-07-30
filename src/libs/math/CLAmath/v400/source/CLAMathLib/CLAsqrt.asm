;******************************************************************************
; 
; FILE: CLAsqrt.asm
; 
; DESCRIPTION: CLA square root function using Newton Raphson 
;              Approximation
; 
;******************************************************************************
;  $TI Release: CLA Math Library for CLA C Compiler V4.00 $
;  $Release Date: December 10, 2011 $
;******************************************************************************
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
;                          All Rights Reserved.
;******************************************************************************

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
;; Benchmark:   Cycles = 18
;;          Instructions = 18
;;----------------------------------------------------------------------------  

	.sect "Cla1Prog"
	.def  _CLAsqrt
	
_sqrt_tmp .usect "CLAscratch",2
_save_MR3 .usect "CLAscratch",2

_CLAsqrt:
; Context Save
	   MMOV32      @_save_MR3, MR3
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
       MMPYF32     MR1,MR1,MR2     ; MR1 = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
       MMPYF32     MR0,MR1,MR0     ; MR0 = Y = Ye*X
; Context Restore
	   MMOV32      MR3,@_save_MR3 
       MRCNDD      UNC
       MNOP
       MNOP
       MNOP
