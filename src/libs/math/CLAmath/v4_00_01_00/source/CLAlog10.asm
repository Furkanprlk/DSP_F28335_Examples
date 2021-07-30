;******************************************************************************
; FILE: CLAlog10.asm
; 
; DESCRIPTION: CLA Base 10 Logarithmic Function
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
;; Description: 
;;             Step(1):   Calculate absolute of x   
;;
;;             Step(2):   Identify the exponent of the input, store it float.
;;                      
;;             Step(3):   Identify the mantissa{Xm}.
;;
;;             Step(4):   Subtract the bias from the exponent and multiply it by Ln(2) 
;;
;;             Step(5):   Calculate the value of Ln(1+mantissa)by using the 
;;                        polynomial approx = a0 + Xm*(a1 + Xm*a2)
;;
;;             Step(6):   Result = {Ln(1+mantissa) + (Exponent-127)*(Ln(2))}/Ln(10)
;;                        
;; 
;; Benchmark:   Cycles = 32  
;;              Instructions =  32
;;----------------------------------------------------------------------------  

	.sect "Cla1Prog"
	.def _CLAlog10

_save_MR3 .usect "CLAscratch",2

_CLAlog10:
; Context Save
	   MMOV32   @_save_MR3, MR3
; Step 1
       MMOV32    MR3,MR0                      ;
;      MABSF32   MR3,MR3                      ; LOAD |X| TO MR3
	   MMOV32    MR2, MR3                     ; LOAD |X| TO MR2
; Step 2
       MLSR32 MR2, #23                        ; MR2<= EXPONENT(X)
	   MI32TOF32 MR2,MR2                      ;
; Step 3
       MMOV32 MR1,@_CLALN_TABLE_MASK1         ; MR1<= 0x3FFFFFFF
	   MAND32 MR3, MR1, MR3                   ; 
       MMOV32 MR1,@_CLALN_TABLE_MASK2         ; MR1<= 0x3F800000
	   MOR32  MR3, MR1, MR3                   ; MR3<=X/2^(EXPONENT)
	   MFRACF32 MR3,MR3                       ; MR3<= MANTISSA
; Step 4
;      || MMOV32 MR1,@_CLABIAS
;       MSUBF32 MR2,MR2,MR1                    ; MR2<= EXPONENT - BIAS
;
;	   ||MMOV32 MR1,@_CLALNV2                  ;
;       MMPYF32 MR2,MR2,MR1                    ; MR2<= (Exponent-127)*(Ln(2))

         MMPYF32     MR0,MR3,#32.0             ; 32 = Elements In Table
         MF32TOUI16  MR0,MR0                   ; MR0 = int(32*x)
         MADD32      MR0,MR0,MR0               ; MR0 = 2*MR0
         MADD32      MR1,MR0,MR0               ; MR1 = 4*MR0
         MADD32      MR0,MR0,MR1               ; MR0 = 6*MR0 this is the index value for the stored data array
     
         MMOV16      MAR1,MR0,#_CLALnTable+4   ; MAR1 points to A2, this will be used later

        MMOV32 MR1,@_CLABIAS
        MSUBF32 MR2,MR2,MR1                    ; MR2<= EXPONENT - BIAS
	  ||MMOV32 MR1,@_CLALNV2                   ; 
        MMPYF32 MR2,MR2,MR1                    ; MR2<= (Exponent-127)*(Ln(2))
; Step 5
; Ln(X) = A0 + Xm(A1 + A2*Xm)
        MMOV32      MR1,*MAR1[#-2]++           ; MR1 = A2
        MMPYF32     MR1,MR3,MR1                ; MR1 = A2*Xm
      ||MMOV32      MR0,*MAR1[#-2]++           ; MR0 = A1
        MADDF32     MR1,MR0,MR1                ; MR1 = A1 + A2*Xm
        MMPYF32     MR0,MR3,MR1                ; MR0 = Xm*(A1 + A2*Xm)
      ||MMOV32      MR1,*MAR1[#-2]++           ; MR1 = A0 
        MADDF32     MR3,MR1,MR0                ; MR3 = A0 + Ratio*(A1 + A2*Ratio) = Ln(1+mantissa)

		MADDF32     MR3,MR3,MR2                ;
	  ||MMOV32      MR1,@_CLALNV10             ;
        MMPYF32     MR3,MR3,MR1                ;
		MMOV32      MR0,MR3                    ; Y= (Ln(1+mantissa) + (Exponent-127)*(Ln(2)))/Ln(10)
; Context Restore
	    MMOV32		MR3,@_save_MR3 
        MRCNDD	    UNC
        MNOP
        MNOP
        MNOP
