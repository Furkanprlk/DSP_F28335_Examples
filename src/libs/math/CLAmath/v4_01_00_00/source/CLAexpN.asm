;;#############################################################################
;; FILE: CLAexpN.asm
;; 
;; DESCRIPTION: CLA Base N Exponent function
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
;;   Step(1):   Calculate ln(Num)
;;   
;;   Step(2):   x*ln(Num)
;;            
;;   Step(3):   N^x = e^(x*ln(Num))
;;              
;; Input : fVal (or x), the power of N - MR0
;;         N, the base - MR1
;;
;; Benchmark:   Cycles = 68
;;              Instructions =  68
;;
;; Scratchpad Usage: (Local Function Scratchpad Pointer (SP))
;;
;;   |_______|<- exponent temporary variable       (SP+4)
;;   |_______|<- exponentN temporary variable      (SP+2)
;;   |_______|<- MR3                               (SP+0)
;;
;;----------------------------------------------------------------------------  
    .def    _CLAexpN
    .sect   "Cla1Prog:_CLAexpN"
    .align  2
__CLAexpN_sp   .usect ".scratchpad:Cla1Prog:_CLAexpN",6,0,1

_CLAexpN:
    .asmfunc
    .asg    __CLAexpN_sp + 0, _save_MR3 
    .asg    __CLAexpN_sp + 2, _expN_tmp
    .asg    __CLAexpN_sp + 2, _exp_tmp
; Context Save
    MMOV32    @_save_MR3, MR3
;;----------------------------------------------------------------------------  
;; Step 1: Calculate ln(Num)
;;----------------------------------------------------------------------------  
    MMOV32      @_expN_tmp, MR0     ; Save fVal (or Num)

; Step 1
    MMOV32      MR3, MR1            ; MR3 = N             
    MMOV32      MR2, MR3            ; LOAD N TO MR2

; Step 2
    MLSR32      MR2, #23            ; MR2 = EXPONENT(X)
    MI32TOF32   MR2,MR2             
; Step 3    
    MMOV32      MR1,@_CLALN_TABLE_MASK1  ; MR1 = 0x3FFFFFFF
    MAND32      MR3, MR1, MR3            ; 
    MMOV32      MR1,@_CLALN_TABLE_MASK2  ; MR1 = 0x3F800000
    MOR32       MR3, MR1, MR3            ; MR3 = X/2^(EXPONENT)
    
    MFRACF32    MR3,MR3             ; MR3 = MANTISSA
; Step 4
;   || MMOV32 MR1,@_CLABIAS
;    MSUBF32 MR2,MR2,MR1            ; MR2 = EXPONENT - BIAS
;       
;   ||MMOV32 MR1,@_CLALNV2          
;    MMPYF32 MR2,MR2,MR1            ; MR2 = (Exponent-127)*(Ln(2))

    MMPYF32     MR0,MR3,#32.0       ; 32 = Elements In Table
    MF32TOUI16  MR0,MR0             ; MR0 = int(32*Xm)
    MADD32      MR0,MR0,MR0         ; MR0 = 2*MR0
    MADD32      MR1,MR0,MR0         ; MR1 = 4*MR0
    MADD32      MR0,MR0,MR1         ; MR0 = 6*MR0 this is the index value for 
                                    ; the stored data array
    
    MMOV16      MAR1,MR0,#_CLALnTable+4     

    MMOV32      MR1,@_CLABIAS        
    MSUBF32     MR2,MR2,MR1         ; MR2 = EXPONENT - BIAS
 || MMOV32      MR1,@_CLALNV2       
    MMPYF32     MR2,MR2,MR1         ; MR2 = (Exponent-127)*(Ln(2))
; Step 5

; Ln(X) = A0 + Xm(A1 + A2*Xm)
    MMOV32      MR1,*MAR1[#-2]++    ; MR1 = A2
    MMPYF32     MR1,MR3,MR1         ; MR1 = A2*Xm
 || MMOV32      MR0,*MAR1[#-2]++    ; MR0 = A1
    MADDF32     MR1,MR0,MR1         ; MR1 = A1 + A2*Xm
    MMPYF32     MR0,MR3,MR1         ; MR0 = Xm*(A1 + A2*Xm)
 || MMOV32      MR1,*MAR1[#-2]++           ; MR1 = A0 
    MADDF32     MR3,MR1,MR0         ; MR3 = A0 + Xm*(A1 + A2*Xm) = Ln(1+mantissa)
    MADDF32     MR3,MR3,MR2         ; Y = Ln(1+mantissa) + (Exponent-127)*(Ln(2))
;;----------------------------------------------------------------------------  
;; Step 2: x*ln(Num)
;;----------------------------------------------------------------------------  
    MMOV32      MR1, @_expN_tmp
    MMPYF32     MR0, MR1, MR3       ; MR0 = x*Ln(Num)
;;----------------------------------------------------------------------------  
;; Step 3: N^x = e^(x*ln(Num))
;;----------------------------------------------------------------------------  
; The input argument fVal is refered to as X
; save input argument on scratchpad
    MMOV32      @_exp_tmp,MR0
; Step 1    
    MMOV32      MR3,MR0           ; Load argument into MR3
    MABSF32     MR3,MR3           ; LOAD |X| TO MR3
        
; Step 2        
    MF32TOI32   MR0,MR3           ; MR0 = INTEGER(X)   
    MFRACF32    MR1,MR3           ; MR1 = MANTISSA(X)
; Step 3    
    MADD32      MR2,MR0,MR0
    MMOV16      MAR1,MR2,#_CLAExpTable       
           
; Step 3
    MMOV32      MR2,@_CLAINV7     ; MR2 = 1/7
    MMPYF32     MR3,MR2,MR1       ; MR3 = Xm/7
 || MMOV32      MR2,@_CLAINV1     ; MR2 = 1
    MADDF32     MR3,MR3,MR2       ; MR3 =(1+Xm/7)
    MMOV32      MR2,@_CLAINV6     ; MR2 = 1/6
 || MMPYF32     MR3,MR1,MR3       ; MR3 = Xm(1+Xm/7)
    MMPYF32     MR3,MR3,MR2       ; MR3 = Xm(1+Xm/7)/6
 || MMOV32      MR2,@_CLAINV1     ; MR2 = 1
    MADDF32     MR3,MR3,MR2       ; MR3 = 1+(Xm/6)*(1+Xm/7)
 || MMOV32      MR0,*MAR1         ; MR0 = e^(INTEGER(X))
    MMOV32      MR2,@_CLAINV5     ; MR2 = .2
 || MMPYF32     MR3,MR1,MR3       ; MR3 = Xm(1+Xm/6*(1+Xm/7))
    MMPYF32     MR3,MR3,MR2       ; MR3 = Xm(1+Xm/6*(1+Xm/7))/5
 || MMOV32      MR2,@_CLAINV1     ; MR2 = 1
    MADDF32     MR3,MR3,MR2       ; MR3 = 1+(Xm/5)*(1+Xm/6*(1+Xm/7))
    MMOV32      MR2,@_CLAINV4     ; MR2 = .25
 || MMPYF32     MR3,MR1,MR3       ; MR3 = Xm(1+Xm/5*(1+Xm/6*(1+Xm/7)))
    MMPYF32     MR3,MR3,MR2       ; MR3 = Xm(1+Xm/5*(1+Xm/6*(1+Xm/7)))/4
 || MMOV32      MR2,@_CLAINV1     ; MR2 = 1
    MADDF32     MR3,MR3,MR2       ; MR3 = 1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))
    MMOV32      MR2,@_CLAINV3     ; MR2 = .3333333
 || MMPYF32     MR3,MR1,MR3       ; MR3 = Xm(1+(Xm/4)*(1+Xm/5)*(1+Xm/6*(1+Xm/7)))
    MMPYF32     MR3,MR3,MR2       ; MR3 = Xm(1+(Xm/4)*(1+Xm/5)*(1+Xm/6*(1+Xm/7)))*0.333333
 || MMOV32      MR2,@_CLAINV1     ; MR2 = 1
    MADDF32     MR3,MR3,MR2       ; MR3 = 1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7))))
    MMOV32      MR2,@_CLAINV2     ; MR2 = .5
 || MMPYF32     MR3,MR1,MR3       ; MR3 = Xm(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))
    MMPYF32     MR3,MR3,MR2       ; MR3 = Xm(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))*0.5
 || MMOV32      MR2,@_CLAINV1     ; MR2 = 1
    MADDF32     MR3,MR3,MR2       ; MR3 = 1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))Xm/2
    MMPYF32     MR3,MR3,MR1       ; MR3 = Xm(1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))Xm/2)
 || MMOV32      MR2,@_CLAINV1     ; MR2 = 1
    MADDF32     MR3,MR3,MR2       ; MR3 = e^(MANTISSA)= 1+Xm(1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6)*(1+Xm/7))))Xm/2)
; Step 4        
    MMPYF32     MR3,MR3,MR0       ; MR3 = e^(MANTISSA) x e^(INTEGER(X))
    MMOV32      MR1,MR3,UNC   
; Calculation of e^-x 
    MEINVF32    MR2,MR1           ; MR2 = Ye = Estimate(1/Den)
    MMPYF32     MR3,MR2,MR1       ; MR3 = Ye*Den
    MSUBF32     MR3,#2.0,MR3      ; MR3 = 2.0 - Ye*Den
    MMPYF32     MR2,MR2,MR3       ; MR2 = Ye = Ye*(2.0 - Ye*Den)
    MMPYF32     MR3,MR2,MR1       ; MR3 = Ye*Den
    MSUBF32     MR3,#2.0,MR3      ; MR3 = 2.0 - Ye*Den
    MMPYF32     MR2,MR2,MR3       ; MR2 = Ye = Ye*(2.0 - Ye*Den)
 || MMOV32      MR0,@_exp_tmp     ; MR2 = X (set/clear NF,ZF)
; Context Restore and Final Operations
    MRCNDD      UNC
    MMOV32      MR1,MR2,LT        ; update e^X with inverse value     
    MMOV32      MR0,MR1           ; Store result in MR0
    MMOV32      MR3,@_save_MR3 
    .unasg  _save_MR3 
    .unasg  _expN_tmp
    .unasg	_exp_tmp
    .endasmfunc

;; End of File
 
