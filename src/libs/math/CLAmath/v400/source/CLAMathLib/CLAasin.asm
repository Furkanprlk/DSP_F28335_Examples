;******************************************************************************
; FILE: CLAasin.asm
; 
; DESCRIPTION: CLA arcsine function
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
;; Description: 
;;
;;             Step(1): Calculate absolute of the input X  
;;
;;             Step(2):   Use the upper 6-bits of input "X" value as an
;;                          index into the table to obtain the coefficients
;;                          for a second order equation:
;;
;;                        _CLAasinTable:
;;                             CoeffA0[0]
;;                             CoeffA1[0]
;;                             CoeffA2[0]
;;                                .
;;                                .
;;                             CoeffA0[63]
;;                             CoeffA1[63]
;;                             CoeffA2[63]
;;
;;             Step(3):   Calculate the angle using the folowing equation:
;;
;;                        arctan(Ratio) = A0 + A1*Ratio + A2*Ratio*Ratio
;;                        arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
;;
;;             Step(4):   The final angle is determined as follows:
;;
;;                        if( X < 0 )
;;                            Angle = -Angle
;;
;; Equation:    y = asin(x)
;;
;; Regs Used:   MR0, MR1, MR2, MR3 , MAR0,MAR1
;;
;; Input:   x           f32 value in memory
;;
;; Output:  y           f32 value in memory
;;          MR0 = y     f32 result
;; 
;; Benchmark:   Cycles =  25 
;;              Instructions =  25
;;----------------------------------------------------------------------------  

	.sect "Cla1Prog"
	.def _CLAasin

_asin_tmp .usect "CLAscratch",2
_save_MR3 .usect "CLAscratch",2

_CLAasin:
; Context Save
	 MMOV32		@_save_MR3, MR3
; MR0 = X(fVal) is stored in the scratchpad memory
     MMOV32		@_asin_tmp, MR0
	
; Perform Step (1):
     MABSF32     MR3,MR0            ; MR3 = abs(X)
     
; Perform Step (2):
     MMPYF32     MR2,MR3,#64.0      ;MMPYF32     MR2,MR0,#64.0      ; 64 = Elements In Table
     MF32TOUI16  MR2,MR2            ; MR2 = int(64*x)
     MADD32      MR2,MR2,MR2        ; MR2 = 2*MR2
     MADD32      MR1,MR2,MR2        ; MR1 = 4*MR2
     MADD32      MR2,MR2,MR1        ; MR2 = 6*MR2 this is the index value for the stored data array
     MMOV16      MAR0,MR2,#_CLAasinTable+4       ; MAR0 points to A2, this will be used in step 4
     MMOVI16     MAR1,#_CLAasinHalfPITable+2     ; MAR1 points to pi/2, this will be used in step 5
     MNOP
     MNOP
; Perform Step (3):
; arcsin(x) = A0 + x(A1 + A2*x)
     MMOV32      MR1,*MAR0[#-2]++   ; MR1 = A2
     MMPYF32     MR1,MR1,MR3        ; MR1 = A2*x
  || MMOV32      MR2,*MAR0[#-2]++   ; MR2 = A1

     MADDF32     MR2,MR2,MR1        ; MR2 = A1 + A2*x
  || MMOV32      MR1,*MAR0          ; MR1 = A0
     MMPYF32     MR2,MR2,MR3        ; MR3 = x*(A1 + A2*x)
  
     MADDF32     MR3,MR1,MR2        ; MR3 = A0 + x*(A1 + A2*x)
; Perform Step (4):
 
     MMOV32      MR2,@_asin_tmp       ; MR2 = x (set/clear NF,ZF)
  
     MNEGF32     MR3,MR3,LT         ; if (X < 0) Angle = -Angle
     MMOV32      MR0,MR3            ; Store Y = asin(X)
; Context Restore
	 MMOV32		 MR3,@_save_MR3 
     MRCNDD	     UNC
     MNOP
     MNOP
     MNOP
