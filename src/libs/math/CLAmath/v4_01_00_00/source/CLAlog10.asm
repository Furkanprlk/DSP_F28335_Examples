;;#############################################################################
;; FILE: CLAlog10.asm
;; 
;; DESCRIPTION: CLA Base 10 Logarithmic Function
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
;; Description: 
;;   Step(1):   Calculate absolute of x   
;;   
;;   Step(2):   Identify the exponent of the input, store it float.
;;            
;;   Step(3):   Identify the mantissa{Xm}.
;;   
;;   Step(4):   Subtract the bias from the exponent and multiply it by Ln(2) 
;;   
;;   Step(5):   Calculate the value of Ln(1+mantissa)by using the 
;;              polynomial approx = a0 + Xm*(a1 + Xm*a2)
;;   
;;   Step(6):   Result = {Ln(1+mantissa) + (Exponent-127)*(Ln(2))}/Ln(10)
;;              
;;   
;; Benchmark:   Cycles = 29  
;;              Instructions =  29
;;
;; Scratchpad Usage: (Local Function Scratchpad Pointer (SP))
;;
;;   |_______|<- MR3                               (SP+0)
;;
;;----------------------------------------------------------------------------  

    .def    _CLAlog10
    .sect   "Cla1Prog:_CLAlog10"
    .align  2
__CLAlog10_sp   .usect ".scratchpad:Cla1Prog:_CLAlog10",2,0,1

_CLAlog10:
    .asmfunc
    .asg    __CLAlog10_sp + 0, _save_MR3
; Context Save
    MMOV32      @_save_MR3, MR3
; Step 1    
    MMOV32      MR3,MR0                   
;   MABSF32     MR3,MR3                   ; LOAD |X| TO MR3
    MMOV32      MR2, MR3                  ; LOAD |X| TO MR2
; Step 2
    MLSR32      MR2, #23                  ; MR2 = EXPONENT(X)
    MI32TOF32   MR2,MR2                   
; Step 3    
    MMOV32      MR1,@_CLALN_TABLE_MASK1   ; MR1 = 0x3FFFFFFF
    MAND32      MR3, MR1, MR3              
    MMOV32      MR1,@_CLALN_TABLE_MASK2   ; MR1 = 0x3F800000
    MOR32       MR3, MR1, MR3             ; MR3 =X/2^(EXPONENT)
    MFRACF32    MR3,MR3                   ; MR3 = MANTISSA
; Step 4
; || MMOV32  MR1,@_CLABIAS      
;    MSUBF32 MR2,MR2,MR1                  ; MR2 = EXPONENT - BIAS
;
; || MMOV32  MR1,@_CLALNV2                
;    MMPYF32 MR2,MR2,MR1                  ; MR2 = (Exponent-127)*(Ln(2))

    MMPYF32     MR0,MR3,#32.0             ; 32 = Elements In Table
    MF32TOUI16  MR0,MR0                   ; MR0 = int(32*x)
    MADD32      MR0,MR0,MR0               ; MR0 = 2*MR0
    MADD32      MR1,MR0,MR0               ; MR1 = 4*MR0
    MADD32      MR0,MR0,MR1               ; MR0 = 6*MR0 this is the index value 
                                          ; for the stored data array
; MAR1 points to A2, this will be used later
    MMOV16      MAR1,MR0,#_CLALnTable+4   
    
    MMOV32      MR1,@_CLABIAS
    MSUBF32     MR2,MR2,MR1               ; MR2 = EXPONENT - BIAS
 || MMOV32      MR1,@_CLALNV2             ; 
    MMPYF32     MR2,MR2,MR1               ; MR2 = (Exponent-127)*(Ln(2))
; Step 5
; Ln(X) = A0 + Xm(A1 + A2*Xm)
    MMOV32      MR1,*MAR1[#-2]++          ; MR1 = A2
    MMPYF32     MR1,MR3,MR1               ; MR1 = A2*Xm
 || MMOV32      MR0,*MAR1[#-2]++          ; MR0 = A1
    MADDF32     MR1,MR0,MR1               ; MR1 = A1 + A2*Xm
    MMPYF32     MR0,MR3,MR1               ; MR0 = Xm*(A1 + A2*Xm)
 || MMOV32      MR1,*MAR1[#-2]++          ; MR1 = A0 
    MADDF32     MR3,MR1,MR0               ; MR3 = A0 + Ratio*(A1 + A2*Ratio) = Ln(1+mantissa)
                                          
    MADDF32     MR3,MR3,MR2               
 || MMOV32      MR1,@_CLALNV10         
 
; Context Restore and Final Operations
    MRCNDD      UNC
    MMPYF32     MR3,MR3,MR1               
    MMOV32      MR0,MR3                   ; Y= (Ln(1+mantissa) + (Exponent-127)*(Ln(2)))/Ln(10)
    MMOV32      MR3,@_save_MR3 
    .unasg  _save_MR3
    .endasmfunc

;; End of File
 
