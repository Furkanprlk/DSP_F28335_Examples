;;#############################################################################
;; FILE: CLAexp2.asm
;; 
;; DESCRIPTION: CLA Exponential of Ratio function
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
;;   Step(1):   Calculate absolute of x=A/B  
;;   
;;   Step(2):   Identify the integer and mantissa of the input
;;            
;;   Step(3):   Obtain the e^integer(x) from the table 
;;   
;;   Step(4):   Calculate the value of e^(mantissa)by using the polynomial
;;              approximation,
;;              1 + x*(1+x*0.5(1+(x/3)(1+x/4(1+X/5*(1+Xm/6*(1+Xm/7))))))
;;   
;;   Step(5):   The value of e^x is the product of results from (3)&(4)
;;              
;;   
;; Benchmark:   Cycles = 53
;;              Instructions =  53
;;
;; Scratchpad Usage: (Local Function Scratchpad Pointer (SP))
;;
;;   |_______|<- exponent temporary variable 2     (SP+4)
;;   |_______|<- exponent temporary variable 1     (SP+2)
;;   |_______|<- MR3                               (SP+0)
;;
;;---------------------------------------------------------------------------- 

    .def    _CLAexp2
    .sect   "Cla1Prog:_CLAexp2"
    .align  2
__CLAexp2_sp    .usect ".scratchpad:Cla1Prog:_CLAexp2",6,0,1

_CLAexp2:
    .asmfunc
    .asg    __CLAexp2_sp + 4, _exp2_tmp2
    .asg    __CLAexp2_sp + 2, _exp2_tmp1
    .asg    __CLAexp2_sp + 0, _save_MR3 
; Context Save
    MMOV32    @_save_MR3, MR3
; The input arguments fVal1,fVal2 referred to as A,B repectively
; save input argument on scratchpad
    MMOV32    @_exp2_tmp1,MR0
    MMOV32    @_exp2_tmp2,MR1
; Step 1
    MEINVF32  MR2,MR1          ; MR2 = Ye = Estimate(1/Den)
    MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
    MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
    MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
    MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
 || MMOV32    MR0,@_exp2_tmp1  ; MR0 = Num
    MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
    MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
 || MMOV32    MR1,@_exp2_tmp2  ; Optional: Reload Den To Set Sign
    MNEGF32   MR0,MR0,EQ       ; Optional: if(Den == 0.0) Change Sign Of Num 
    MMPYF32   MR0,MR2,MR0      ; MR0 = X = Ye*Num
    MMOV32    MR0,MR0          ; Optional: Set/Clear MSTF NF and ZF flags

    MABSF32   MR3,MR0          ; LOAD |X| TO MR3
; Step 2
    MF32TOI32 MR0,MR3          ; MR0 = INTEGER(X)   
    MFRACF32  MR1,MR3          ; MR1 = MANTISSA(X)
; Step 3
    MADD32    MR2,MR0,MR0
    MMOV16    MAR1,MR2,#_CLAExpTable       
           
; Step 4
    MMOV32    MR2,@_CLAINV7    ; MR2 = 1/7
    MMPYF32   MR3,MR2,MR1      ; MR3 = Xm/7
 || MMOV32    MR2,@_CLAINV1    ; MR2 = 1
    MADDF32   MR3,MR3,MR2      ; MR3 =(1+Xm/7)
    MMOV32    MR2,@_CLAINV6    ; MR2 = .2
 || MMPYF32   MR3,MR1,MR3      ; MR3 = Xm(1+Xm/7)
    MMPYF32   MR3,MR3,MR2      ; MR3 = Xm(1+Xm/7)/6
 || MMOV32    MR2,@_CLAINV1    ; MR2 = 1
    MADDF32   MR3,MR3,MR2      ; MR3 = 1+(Xm/6)*(1+Xm/7)
 || MMOV32    MR0,*MAR1        ; MR0 = e^(INTEGER(X))
    MMOV32    MR2,@_CLAINV5    ; MR2 = .2
 || MMPYF32   MR3,MR1,MR3      ; MR3 = Xm(1+Xm/6*(1+Xm/7))
    MMPYF32   MR3,MR3,MR2      ; MR3 = Xm(1+Xm/6*(1+Xm/7))/5
 || MMOV32    MR2,@_CLAINV1    ; MR2 = 1
    MADDF32   MR3,MR3,MR2      ; MR3 = 1+(Xm/5)*(1+Xm/6*(1+Xm/7))
    MMOV32    MR2,@_CLAINV4    ; MR2 = .25
 || MMPYF32   MR3,MR1,MR3      ; MR3 = Xm(1+Xm/5*(1+Xm/6*(1+Xm/7)))
    MMPYF32   MR3,MR3,MR2      ; MR3 = Xm(1+Xm/5*(1+Xm/6*(1+Xm/7)))/4
 || MMOV32    MR2,@_CLAINV1    ; MR2 = 1
    MADDF32   MR3,MR3,MR2      ; MR3 = 1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))
    MMOV32    MR2,@_CLAINV3    ; MR2 = .3333333
 || MMPYF32   MR3,MR1,MR3      ; MR3 = Xm(1+(Xm/4)*(1+Xm/5)*(1+Xm/6*(1+Xm/7)))
    MMPYF32   MR3,MR3,MR2      ; MR3 = Xm(1+(Xm/4)*(1+Xm/5)*(1+Xm/6*(1+Xm/7)))/3
 || MMOV32    MR2,@_CLAINV1    ; MR2 = 1
    MADDF32   MR3,MR3,MR2      ; MR3 = 1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7))))
    MMOV32    MR2,@_CLAINV2    ; MR2 = .5
 || MMPYF32   MR3,MR1,MR3      ; MR3 = Xm(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))
    MMPYF32   MR3,MR3,MR2      ; MR3 = Xm(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))*0.5
 || MMOV32    MR2,@_CLAINV1    ; MR2 = 1
    MADDF32   MR3,MR3,MR2      ; MR3 = 1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))Xm/2
    MMPYF32   MR3,MR3,MR1      ; MR3 = Xm(1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))Xm/2)
 || MMOV32    MR2,@_CLAINV1    ; MR2 = 1
    MADDF32   MR3,MR3,MR2      ; MR3 = e^(Xm)= 1+Xm(1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))Xm/2)
; Step 5                         
    MMPYF32   MR3,MR3,MR0      ; MR3 = e^(MANTISSA) x e^(INTEGER(X))
    MMOV32    MR1,MR3,UNC
; Calculation of e^-x 
    MEINVF32  MR2,MR1          ; MR2 = Ye = Estimate(1/Den)
    MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
    MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
    MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
    MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
    MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
    MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
 || MMOV32    MR0,@_exp2_tmp1  ; MR0 = X (set/clear NF,ZF)
    MMOV32    MR3,@_exp2_tmp2  ; MR3 = X (set/clear NF,ZF)
    MXOR32    MR0,MR0,MR3      ;
; Context Restore and Final Operations
    MRCNDD    UNC
    MMOV32    MR1,MR2,LT       ; update e^X with inverse value     
    MMOV32    MR0,MR1          ; Store result in MR0
    MMOV32    MR3,@_save_MR3 
    .unasg  _exp2_tmp2
    .unasg  _exp2_tmp1
    .unasg  _save_MR3 
    .endasmfunc

;; End of File
 
