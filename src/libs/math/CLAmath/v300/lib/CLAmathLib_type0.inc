;; TI File Version : 3.00
;; Checkin Date :Fri 09/24/2010  05:42 PM
;;##############################################################################
;;
;; FILE: CLAmathLib_type0.inc
;;
;; TITLE: CLA type 0 Math Macros
;;
;; This file contains the CLA assembly macrosfor common math functions.
;;
;; The macros in this file are valid for CLA type 0.
;;
;; Macro Contents: 
;;
;; CLAacos .macro     y, x 
;; CLAasin .macro     y, x 
;; CLAatan .macro     y, x 
;; CLAatan2 .macro     z , y, x 
;; CLAatan2PU .macro     z , y, x 
;; CLAcos .macro   y, rad 
;; CLAcosPU .macro   y, radPU 
;; CLAdiv .macro   Dest, Num, Den 
;; CLAexp .macro     y, x 
;; CLAexp10 .macro     y, x 
;; CLAexp2 .macro     y, Num, Den 
;; CLAisqrt   .macro y, x 
;; CLALn .macro     y, x 
;; CLALogN .macro     C,yt1,yt2, A, B 
;; CLALog10 .macro     y, x 
;; CLAexpN .macro     y, Num, x 
;; CLAsin .macro    y, rad 
;; CLASinCos .macro  y1, y2, rad, tmp1, tmp2 
;; CLAsinPU .macro    y, radPU 
;; CLAsqrt .macro     y, x 
;; CLAsqrt .macro     y, x 
;; CLAsqrt .macro     y, x 
;; CLAsqrt .macro     y, x 
;; CLAsqrt .macro     y, x 
;; CLAsqrt .macro     y, x 
;;
;;##############################################################################
;; TI Release: 
;; Release Date: Fri 09/24/2010  
;;##############################################################################
;;
;; This software is licensed for use with Texas Instruments Control
;; Law Accelerator (CLA). This license was provided to you prior
;; to installing the software.  You may review this license by 
;; consulting a copy of the agreement in the doc directory of this library.
;;------------------------------------------------------------------------
;;         Copyright (C) 2009 Texas Instruments, Incorporated.
;;                         All Rights Reserved.
;;
;;##############################################################################
;;============================================================================
;; Macro: CLAacos
;;----------------------------------------------------------------------------
;; Description: 
;;
;;             Step(1): Calculate absolute of the input X  
;;
;;             Step(2): Use the upper 6-bits of input "X" value as an
;;                          index into the table to obtain the coefficients
;;                          for a second order equation:
;;
;;                        _FPUasinTable:
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
;;                            Angle = Pi - Angle
;;
;; Equation:    y = acos(x)
;;
;; Regs Used:   MR0, MR1, MR2, MR3 , MAR0,MAR1
;;
;; Input:   x           f32 value in memory
;;
;; Output:  y           f32 value in memory
;;          MR3 = y     f32 result
;; 
;; Benchmark:   Cycles =  19 
;;              Instructions =  19
;;----------------------------------------------------------------------------  

CLAacos .macro     y, x
     MMOV32      MR0,@_:x:          ; MR0 = X
	
; Perform Step (1):
     MABSF32     MR3,MR0            ; MR3 = abs(X)
     
; Perform Step (2):
     MMPYF32     MR2,MR3,#64.0      ; 64 = Elements In Table
     MF32TOUI16  MR2,MR2            ; MR2 = int(64*x)
     MADD32      MR2,MR2,MR2        ; MR2 = 2*MR2
     MADD32      MR1,MR2,MR2        ; MR1 = 4*MR2
     MADD32      MR2,MR2,MR1        ; MR2 = 6*MR2 this is the index value for the stored data array
     MMOV16      MAR0,MR2,#_CLAacosinTable+4       ; MAR0 points to A2, this will be used in step 4
     MMOVI16     MAR1,#_CLAacosinHalfPITable+2     ; MAR1 points to pi/2, this will be used in step 5
     MNOP
     MNOP
; Perform Step (4):
; arcsin(x) = A0 + x(A1 + A2*x)
     MMOV32      MR1,*MAR0[#-2]++   ; MR1 = A2
     MMPYF32     MR1,MR1,MR3        ; MR1 = A2*x
  || MMOV32      MR2,*MAR0[#-2]++   ; MR2 = A1

     MADDF32     MR2,MR2,MR1        ; MR2 = A1 + A2*x
  || MMOV32      MR1,*MAR0          ; MR1 = A0
     MMPYF32     MR2,MR2,MR3        ; MR3 = x*(A1 + A2*x)
  
     MADDF32     MR3,MR1,MR2        ; MR3 = A0 + x*(A1 + A2*x)=arccosin(x)

; Perform Step (5):
    MMOV32      MR1,*MAR1,UNC     ; MR1 = pi  (no flag change)
	MSUBF32     MR1,MR1,MR3       ; MR2= pi - arcos(x)
  
  MMOV32      MR2,@_:x:          ; MR2 = x (set/clear NF,ZF)
   
  MMOV32      MR3,MR1,LT 
  

  MMOV32      @_:y:,MR3          ; Store Y = asin(X)
 
     .endm
 
;;============================================================================
;; End of macro
;;============================================================================

;;============================================================================
;; Macro: CLAasin
;;----------------------------------------------------------------------------
;; Description: 
;;
;;             Step(1): Calculate absolute of the input X  
;;
;;             Step(2):   Use the upper 6-bits of input "X" value as an
;;                          index into the table to obtain the coefficients
;;                          for a second order equation:
;;
;;                        _FPUasinTable:
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
;;          MR3 = y     f32 result
;; 
;; Benchmark:   Cycles =  19 
;;              Instructions =  19
;;----------------------------------------------------------------------------  

CLAasin .macro     y, x
     MMOV32      MR0,@_:x:          ; MR0 = X
	
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
 
  MMOV32      MR2,@_:x:          ; MR2 = x (set/clear NF,ZF)
   
   
  MNEGF32     MR3,MR3,LT         ; if (X < 0) Angle = -Angle
  MMOV32      @_:y:,MR3          ; Store Y = asin(X)
 
     .endm
 
;;============================================================================
;; End of macro
;;============================================================================


;;----------------------------------------------------------------------------
;; TI Macro $Revision: \main\1 $
;; Checkin $Date: January 11, 2010 $
;;============================================================================
;; Macro: CLAatan
;;----------------------------------------------------------------------------
;; Description: 
;;             Step(1):   if( 1.0 >= abs(Y) )
;;                            Numerator   = abs(Y)
;;                            Denominator = 1.0
;;                        else
;;                            Numerator   = 1.0
;;                            Denominator = abs(Y)
;;
;;             Step(2):   Ratio = Numerator/Denominator
;;
;;                        Note: Ratio range = 0.0 to 1.0
;;
;;             Step(3):   Use the upper 6-bits of the "Ratio" value as an
;;                        index into the table to obtain the coefficients
;;                        for a second order equation:
;;
;;                        _FPUatan2Table:
;;                             CoeffA0[0]
;;                             CoeffA1[0]
;;                             CoeffA2[0]
;;                                .
;;                                .
;;                             CoeffA0[63]
;;                             CoeffA1[63]
;;                             CoeffA2[63]
;;
;;             Step(4):   Calculate the angle using the folowing equation:
;;
;;                        arctan(Ratio) = A0 + A1*Ratio + A2*Ratio*Ratio
;;                        arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
;;
;;             Step(5):   The final angle is determined as follows:
;;
;;                        if( Y >= 0 and 1.0 >= abs(Y) )
;;                            Angle = arctan(abs(Y)/1.0)
;;                        if( Y >= 0 and 1.0 <  abs(Y) )
;;                            Angle = PI/2 - arctan(1.0/abs(Y))
;;                        if( Y < 0 )
;;                            Angle = -Angle
;; Equation:    y = atan(x)
;;
;; Regs Used:   MR0, MR1, MR2, MR3 , MAR0,MAR1
;;
;; Input:   x           f32 value in memory
;;
;; Output:  y           f32 value in memory
;;          MR3 = y     f32 result
;; 
;; Benchmark:   Cycles =  38 
;;              Instructions =  38
;;----------------------------------------------------------------------------  

CLAatan .macro     y, x
     MMOV32      MR0,@_:x:          ; MR0 = X
; Perform Step (1):
     MABSF32     MR3,MR0            ; MR3 = abs(X)
     MMOVIZ      MR1,#0x3f80        ; MR1 = 1.0 , 0x3f800000 = 1.0 in 32 bit Float
     MMOV32      MR2,MR3            ; Store abs(X) in MR2
     MMINF32     MR3,MR1            ; MR3 = numerator (A) = min(abs(X),1.0) 
     MMOV32      MR1,MR2,GT         ; MR1 = denominator (B) = max(abs(X),1.0)
                                    ; Ratio = A/B
; Perform Step (2):
     MEINVF32    MR2,MR1            ; MR2 = Ye = Estimate(1/Dinominator) i.e 1/B
     MTESTTF     LEQ                ; Set TF if 1.0 >= abs(X) , this will be used in step 5
     MMPYF32     MR0,MR2,MR1        ; MR0 = Ye*B
     MSUBF32     MR0,#2.0,MR0       ; MR0 = 2.0 - Ye*B
     MMPYF32     MR2,MR2,MR0        ; MR2 = Ye = Ye*(2.0 - Ye*B)  (first estimate)
     MMPYF32     MR0,MR2,MR1        ; MR0 = Ye*B
     MSUBF32     MR0,#2.0,MR0       ; MR0 = 2.0 - Ye*B
     MMPYF32     MR2,MR2,MR0        ; MR2 = Ye = Ye*(2.0 - Ye*B)  (second estimate)
     MMPYF32     MR0,MR2,MR3        ; MR0 = Ratio = A*Ye = A/B
; Perform Step (3):
     MMPYF32     MR2,MR0,#64.0      ; 64 = Elements In Table
     MF32TOUI16  MR2,MR2            ; MR2 = int(64*ratio)
     MADD32      MR2,MR2,MR2        ; MR2 = 2*MR2
     MADD32      MR1,MR2,MR2        ; MR1 = 4*MR2
     MADD32      MR2,MR2,MR1        ; MR2 = 6*MR2 this is the index value for the stored data array
     MMOV16      MAR0,MR2,#_CLAatan2Table+4       ; MAR0 points to A2, this will be used in step 4
     MMOVI16     MAR1,#_CLAatan2HalfPITable+2     ; MAR1 points to pi/2, this will be used in step 5
     MNOP
     MNOP
; Perform Step (4):
; arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
     MMOV32      MR1,*MAR0[#-2]++   ; MR1 = A2
     MMPYF32     MR1,MR1,MR0        ; MR1 = A2*Ratio
  || MMOV32      MR3,*MAR0[#-2]++   ; MR3 = A1
     MADDF32     MR3,MR3,MR1        ; MR3 = A1 + A2*Ratio
  || MMOV32      MR1,*MAR0          ; MR1 = A0
     MMPYF32     MR3,MR3,MR0        ; MR3 = Ratio*(A1 + A2*Ratio)
     MADDF32     MR3,MR1,MR3        ; MR3 = A0 + Ratio*(A1 + A2*Ratio)
; Perform Step (5):
     MMOVIZ      MR0,#0.0
     MMOV32      MR1,*MAR1          ; MR1 = pi/2
     MNEGF32     MR3, MR3, UNC      ; MR3 = flip sign of atan(Ratio)
     MNEGF32     MR3, MR3, TF       ; if (1.0 >= abs(Y)) flip sign of atan(Ratio)
     MMOV32      MR2,@_:x:          ; MR2 = Y (set/clear NF,ZF)
     MMOV32      MR0, MR1, NTF      ; if(1.0 < abs(Y) MR0 = pi/2, else MR0 = 0.0
     MADDF32     MR3, MR3, MR0      ; MR3 = Angle
     MNEGF32     MR3,MR3,LT         ; if (Y < 0) Angle = -Angle
     MMOV32      @_:y:,MR3          ; Store Y = atan(X)
     .endm

;;============================================================================
;; End of macro
;;============================================================================

;;----------------------------------------------------------------------------
;; TI Macro $Revision: \main\1 $
;; Checkin $Date: January 11, 2010 $
;;============================================================================
;; Macro: CLAatan2
;;----------------------------------------------------------------------------
;; Description: 
;;            The algorithm steps to calculate the "atan2" of the given
;             input X and Y is as follows:
;
;             Step(1):   if( abs(X) >= abs(Y) )
;                            Numerator   = abs(Y)
;                            Denominator = abs(X)
;                        else
;                            Numerator   = abs(X)
;                            Denominator = abs(Y)
;
;             Step(2):   Ratio = Numerator/Denominator
;
;                        Note: Ratio range = 0.0 to 1.0
;
;             Step(3):   Use the upper 6-bits of the "Ratio" value as an
;                        index into the table to obtain the coefficients
;                        for a second order equation:
;
;                        _FPUatan2Table:
;                             CoeffA0[0]
;                             CoeffA1[0]
;                             CoeffA2[0]
;                                .
;                                .
;                             CoeffA0[63]
;                             CoeffA1[63]
;                             CoeffA2[63]
;
;             Step(4):   Calculate the angle using the folowing equation:
;
;                        arctan(Ratio) = A0 + A1*Ratio + A2*Ratio*Ratio
;                        arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
;
;             Step(5):   The final angle is determined as follows:
;
;                        if( X >= 0 and Y >= 0 and abs(X) >= abs(Y) )
;                            Angle = arctan(abs(Y)/abs(X))
;                        if( X >= 0 and Y >= 0 and abs(X) <  abs(Y) )
;                            Angle = PI/2 - arctan(abs(X)/abs(Y))
;                        if( X < 0  and Y >= 0 and abs(X) <  abs(Y) )
;                            Angle = PI/2 + arctan(abs(X)/abs(Y))
;                        if( X < 0  and Y >= 0 and abs(X) >= abs(Y) )
;                            Angle = PI - arctan(abs(Y)/abs(X))
;                        if( Y < 0 )
;                            Angle = -Angle
;; Equation:    z = atan(y/x)
;;
;; Regs Used:   MR0, MR1, MR2, MR3, MAR0,MAR1
;;
;; Input:   x , y       two f32 values in memory
;;
;; Output:  z           f32 value in memory
;;          MR3 = z     f32 result
;; 
;; Benchmark:   Cycles = 41  
;;          Instructions = 41 
;;----------------------------------------------------------------------------  

CLAatan2 .macro     z , y, x
     MMOV32      MR0,@_:y:         ; MR0 = Y
     MMOV32      MR1,@_:x:         ; MR1 = X
; Perform Step (1):
     MABSF32     MR3,MR0           ; MR3 = abs(Y)
     MMOV32      MR2,MR3           ; Store abs(Y) in MR2
     MABSF32     MR1,MR1           ; Store abs(X) in MR1
     MMINF32     MR3,MR1           ; MR3 = numerator (A) = min(abs(Y),abs(X)) 
     MMOV32      MR1,MR2,GT        ; MR1 = denominator (B) = max(abs(Y),abs(X))
                                   ; Ratio = A/B
; Perform Step (2):
     MEINVF32    MR2,MR1           ; MR2 = Ye = Estimate(1/Denominator) i.e 1/B
     MTESTTF     LEQ               ; Set TF if 1.0 >= abs(X) , this will be used in step 5
     MMPYF32     MR0,MR2,MR1       ; MR0 = Ye*B
     MSUBF32     MR0,#2.0,MR0      ; MR0 = 2.0 - Ye*B
     MMPYF32     MR2,MR2,MR0       ; MR2 = Ye = Ye*(2.0 - Ye*B)  (first estimate)
     MMPYF32     MR0,MR2,MR1       ; MR0 = Ye*B
     MSUBF32     MR0,#2.0,MR0      ; MR0 = 2.0 - Ye*B
     MMPYF32     MR2,MR2,MR0       ; MR2 = Ye = Ye*(2.0 - Ye*B)  (second estimate)
     MMPYF32     MR0,MR2,MR3       ; MR0 = Ratio = A*Ye = A/B
; Perform Step (3):
     MMPYF32     MR2,MR0,#64.0     ; 64 = Elements In Table
     MF32TOUI16  MR2,MR2           ; MR2 = int(64*ratio)
     MADD32      MR2,MR2,MR2       ; MR2 = 2*MR2
     MADD32      MR1,MR2,MR2       ; MR1 = 4*MR2
     MADD32      MR2,MR2,MR1       ; MR2 = 6*MR2 this is the index value for the stored data array
     MMOV16      MAR0,MR2,#_CLAatan2Table+4     ; MAR0 points to A2, this will be used in step 4
     MMOVI16     MAR1,#_CLAatan2HalfPITable+2   ; MAR1 points to pi/2, this will be used in step 5
     MNOP
     MNOP
; Perform Step (4):
; arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
     MMOV32      MR1,*MAR0[#-2]++  ; MR1 = A2
     MMPYF32     MR1,MR1,MR0       ; MR1 = A2*Ratio
  || MMOV32      MR3,*MAR0[#-2]++  ; MR3 = A1
     MADDF32     MR3,MR3,MR1       ; MR3 = A1 + A2*Ratio
  || MMOV32      MR1,*MAR0         ; MR1 = A0
     MMPYF32     MR3,MR3,MR0       ; MR3 = Ratio*(A1 + A2*Ratio)
     MADDF32     MR3,MR1,MR3       ; MR3 = A0 + Ratio*(A1 + A2*Ratio)
  || MMOV32      MR2,@_:x:         ; MR2 = X (set/clear NF,ZF for use below)
; Perform Step (5):
     MMOV32      MR1,*MAR1,UNC     ; MR1 = pi/2  (no flag change)
     MNEGF32     MR0,MR1,UNC       ; MR0 = -pi/2 (no flag change)
     MMOV32      MR3,MR2,EQ        ; if (X == 0), MR3 = 0
     MNEGF32     MR3,MR3,GEQ       ; if (X >= 0) MR3 flip sign of atan(Ratio)
     MNEGF32     MR3,MR3,TF        ; if (abs(X) >= abs(Y)) flip sign of atan(Ratio)
     
     MNEGF32     MR0,MR0,LT        ; if (X < 0) MR0 = pi/2
     MADDF32     MR0,MR0,MR1       ; MR0 = MR0+pi/2
                                   ; if(X < 0) MR0 = pi
                                   ; if(X > 0) MR0 = 0
  || MMOV32      MR2,@_:y:         ; MR2 = Y (set/clear NF,ZF)
     MMOV32      MR0,MR1,NTF       ; if(abs(X) < abs(Y) R3H = pi/2
     MADDF32     MR3,MR3,MR0       ; MR3 = Angle
     MNEGF32     MR3,MR3,LT        ; if (Y < 0) Angle = -Angle
     MMOV32      @_:z:,MR3
     .endm

;;============================================================================
;; End of macro
;;============================================================================

;;============================================================================
;; Macro: CLAatan2PU
;;----------------------------------------------------------------------------
;; Description: 
;;            The algorithm steps to calculate the "atan2" of the given
;             input X and Y is as follows:
;
;             Step(1):   if( abs(X) >= abs(Y) )
;                            Numerator   = abs(Y)
;                            Denominator = abs(X)
;                        else
;                            Numerator   = abs(X)
;                            Denominator = abs(Y)
;
;             Step(2):   Ratio = Numerator/Denominator
;
;                        Note: Ratio range = 0.0 to 1.0
;
;             Step(3):   Use the upper 6-bits of the "Ratio" value as an
;                        index into the table to obtain the coefficients
;                        for a second order equation:
;
;                        _FPUatan2Table:
;                             CoeffA0[0]
;                             CoeffA1[0]
;                             CoeffA2[0]
;                                .
;                                .
;                             CoeffA0[63]
;                             CoeffA1[63]
;                             CoeffA2[63]
;
;             Step(4):   Calculate the angle using the folowing equation:
;
;                        arctan(Ratio) = A0 + A1*Ratio + A2*Ratio*Ratio
;                        arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
;
;             Step(5):   The final angle is determined as follows:
;
;                        if( X >= 0 and Y >= 0 and abs(X) >= abs(Y) )
;                            Angle = arctan(abs(Y)/abs(X))
;                        if( X >= 0 and Y >= 0 and abs(X) <  abs(Y) )
;                            Angle = PI/2 - arctan(abs(X)/abs(Y))
;                        if( X < 0  and Y >= 0 and abs(X) <  abs(Y) )
;                            Angle = PI/2 + arctan(abs(X)/abs(Y))
;                        if( X < 0  and Y >= 0 and abs(X) >= abs(Y) )
;                            Angle = PI - arctan(abs(Y)/abs(X))
;                        if( Y < 0 )
;                            Angle = -Angle
;
;                            AnglePU =Angle/2pi 
;
;; Equation:    z = { atan(y/x) } / 2pi
;;
;; Regs Used:   MR0, MR1, MR2, MR3, MAR0,MAR1
;;
;; Input:   x , y       two f32 values in memory
;;
;; Output:  z           f32 value in memory
;;          MR3 = z     f32 result
;; 
;; Benchmark:   Cycles = 43  
;;          Instructions = 43 
;;----------------------------------------------------------------------------  

CLAatan2PU .macro     z , y, x
     MMOV32      MR0,@_:y:         ; MR0 = Y
     MMOV32      MR1,@_:x:         ; MR1 = X
; Perform Step (1):
     MABSF32     MR3,MR0           ; MR3 = abs(Y)
     MMOV32      MR2,MR3           ; Store abs(Y) in MR2
     MABSF32     MR1,MR1           ; Store abs(X) in MR1
     MMINF32     MR3,MR1           ; MR3 = numerator (A) = min(abs(Y),abs(X)) 
     MMOV32      MR1,MR2,GT        ; MR1 = denominator (B) = max(abs(Y),abs(X))
                                   ; Ratio = A/B
; Perform Step (2):
     MEINVF32    MR2,MR1           ; MR2 = Ye = Estimate(1/Denominator) i.e 1/B
     MTESTTF     LEQ               ; Set TF if 1.0 >= abs(X) , this will be used in step 5
     MMPYF32     MR0,MR2,MR1       ; MR0 = Ye*B
     MSUBF32     MR0,#2.0,MR0      ; MR0 = 2.0 - Ye*B
     MMPYF32     MR2,MR2,MR0       ; MR2 = Ye = Ye*(2.0 - Ye*B)  (first estimate)
     MMPYF32     MR0,MR2,MR1       ; MR0 = Ye*B
     MSUBF32     MR0,#2.0,MR0      ; MR0 = 2.0 - Ye*B
     MMPYF32     MR2,MR2,MR0       ; MR2 = Ye = Ye*(2.0 - Ye*B)  (second estimate)
     MMPYF32     MR0,MR2,MR3       ; MR0 = Ratio = A*Ye = A/B
; Perform Step (3):
     MMPYF32     MR2,MR0,#64.0     ; 64 = Elements In Table
     MF32TOUI16  MR2,MR2           ; MR2 = int(64*ratio)
     MADD32      MR2,MR2,MR2       ; MR2 = 2*MR2
     MADD32      MR1,MR2,MR2       ; MR1 = 4*MR2
     MADD32      MR2,MR2,MR1       ; MR2 = 6*MR2 this is the index value for the stored data array
     MMOV16      MAR0,MR2,#_CLAatan2Table+4     ; MAR0 points to A2, this will be used in step 4
     MMOVI16     MAR1,#_CLAatan2HalfPITable+2   ; MAR1 points to pi/2, this will be used in step 5
     MNOP
     MNOP
; Perform Step (4):
; arctan(Ratio) = A0 + Ratio(A1 + A2*Ratio)
     MMOV32      MR1,*MAR0[#-2]++  ; MR1 = A2
     MMPYF32     MR1,MR1,MR0       ; MR1 = A2*Ratio
  || MMOV32      MR3,*MAR0[#-2]++  ; MR3 = A1
     MADDF32     MR3,MR3,MR1       ; MR3 = A1 + A2*Ratio
  || MMOV32      MR1,*MAR0         ; MR1 = A0
     MMPYF32     MR3,MR3,MR0       ; MR3 = Ratio*(A1 + A2*Ratio)
     MADDF32     MR3,MR1,MR3       ; MR3 = A0 + Ratio*(A1 + A2*Ratio)
  || MMOV32      MR2,@_:x:         ; MR2 = X (set/clear NF,ZF for use below)
; Perform Step (5):
     MMOV32      MR1,*MAR1,UNC     ; MR1 = pi/2  (no flag change)
     MNEGF32     MR0,MR1,UNC       ; MR0 = -pi/2 (no flag change)
     MMOV32      MR3,MR2,EQ        ; if (X == 0), MR3 = 0
     MNEGF32     MR3,MR3,GEQ       ; if (X >= 0) MR3 flip sign of atan(Ratio)
     MNEGF32     MR3,MR3,TF        ; if (abs(X) >= abs(Y)) flip sign of atan(Ratio)
     
     MNEGF32     MR0,MR0,LT        ; if (X < 0) MR0 = pi/2
     MADDF32     MR0,MR0,MR1       ; MR0 = MR0+pi/2
                                   ; if(X < 0) MR0 = pi
                                   ; if(X > 0) MR0 = 0
  || MMOV32      MR2,@_:y:         ; MR2 = Y (set/clear NF,ZF)
     MMOV32      MR0,MR1,NTF       ; if(abs(X) < abs(Y) R3H = pi/2
     MADDF32     MR3,MR3,MR0       ; MR3 = Angle
     MNEGF32     MR3,MR3,LT        ; if (Y < 0) Angle = -Angle

     MMOV32      MR1,@_CLAINV2PI   ; MR1 = 1/pi*2, this will be used in step 5
     
     
	
     MMPYF32     MR3,MR3,MR1      ;MR3= Angle*(1/pi*2)
     MMOV32      @_:z:,MR3
     .endm

;;============================================================================
;; End of macro
;;============================================================================


;;----------------------------------------------------------------------------
;; TI Macro $Revision: /main/3 $
;; Checkin $Date: May 20, 2009   14:23:08 $
;;============================================================================
;; Macro: CLAcos
;;----------------------------------------------------------------------------
;; Description: Implement sine using taylor series expansion:
;;
;;              rad = K + X
;;
;;              Cos(rad) = Cos(K) - Sin(K)*X 
;;                                - Cos(K)*X^2/2! 
;;                                + Sin(K)*X^3/3! 
;;                                + Cos(K)*X^4/4! 
;;                                - Sin(K)*X^5/5!
;;
;;                       = Cos(K) + X*(-1.0*Sin(K) 
;;                                + X*(-0.5*Cos(K) 
;;                                + X*(0.166666*Sin(K) 
;;                                + X*(0.04166666*Cos(K) 
;;                                + X*(-0.00833333*Sin(K))))))
;;
;;                       = Cos(K) + X*(-Sin(K) 
;;                                + X*(Coef0*Cos(K) 
;;                                + X*(Coef1_pos*Sin(K) 
;;                                + X*(Coef2*Cos(K) 
;;                                + X*(Coef3_neg*Sin(K))))))
;;
;;
;; Equation:    y = Cos(rad)
;;
;; Regs Used:   MR0, MR1, MR2
;;
;; Input:   rad              f32 value in memory
;;
;; // TABLE_SIZE = 128
;;    CLAsincosTable.Sin0  =  0.0;               // sin(  0 * 2*pi/TABLE_SIZE)                  
;;    CLAsincosTable.Sin1  =  0.04906767432742;  // sin(  1 * 2*pi/TABLE_SIZE) 
;;    ...
;;    CLAsincosTable.Sin31 =  0.9987954562052;   // sin( 31 * 2*pi/TABLE_SIZE) 
;;    CLAsincosTable.Cos0  =  1.0;               // sin( 32 * 2*pi/TABLE_SIZE) 
;;    CLAsincosTable.Sin33 =  0.9987954562052;   // sin( 33 * 2*pi/TABLE_SIZE) 
;;    ...
;;    CLAsincosTable.Sin63 =  0.04906767432742;  // sin( 63 * 2*pi/TABLE_SIZE) 
;;    CLAsincosTable.Sin64 =  0.0;               // sin( 64 * 2*pi/TABLE_SIZE)                  
;;    CLAsincosTable.Sin65 = -0.04906767432742;  // sin( 65 * 2*pi/TABLE_SIZE) 
;;    ... 
;;    CLAsincosTable.Sin95 = -0.9987954562052;   // sin( 95 * 2*pi/TABLE_SIZE) 
;;    CLAsincosTable.Sin96 = -1.0;               // sin( 96 * 2*pi/TABLE_SIZE) 
;;    CLAsincosTable.Sin97 = -0.9987954562052;   // sin( 97 * 2*pi/TABLE_SIZE) 
;;    ...
;;    CLAsincosTable.Sin127 = -0.04906767432742; // sin(127 * 2*pi/TABLE_SIZE) 
;;    CLAsincosTable.Cos96  =  0.0;              // sin(  0 * 2*pi/TABLE_SIZE)                  
;;    CLAsincosTable.Cos97  =  0.04906767432742; // sin(  1 * 2*pi/TABLE_SIZE) 
;;    ... 
;;    CLAsincosTable.Cos127 =  0.9987954562052;  // sin( 31 * 2*pi/TABLE_SIZE) 
;;    CLAsincosTable.Cos128 =  1.0;              // sin( 32 * 2*pi/TABLE_SIZE)
;;
;;    // TABLE_SIZE/Pi           
;;    // 2*Pi/TABLE_SIZE
;;    // TABLE_MASK = (TABLE_SIZE*2 - 1) & 0xFFFFFFFE;; 
;;
;;    CLAsincosTable.TABLE_SIZEDivPi     =  40.74366543152;      
;;    CLAsincosTable.TwoPiDivTABLE_SIZE  =  0.04908738521234;    
;;    CLAsincosTable.TABLE_MASK          =  0x000000FE;          
;;    CLAsincosTable.Coef0               = -0.5;
;;    CLAsincosTable.Coef1               = -0.1666666666666;
;;    CLAsincosTable.Coef1_pos           =  0.1666666666666;
;;    CLAsincosTable.Coef2               =  4.1666666666666e-2;
;;    CLAsincosTable.Coef3               =  8.3333333333333e-3;
;;    CLAsincosTable.Coef3_neg           = -8.3333333333333e-3;
;;
;; Output:  y                f32 value in memory
;;          MR0 = y          f32 result
;;
;; Benchmark:   Cycles = 26
;;              Instructions = 26 (104 bytes)
;;----------------------------------------------------------------------------  
CLAcos .macro   y, rad

   ; MR0 = rad
   ; MR1 = TABLE_SIZE/(2*Pi)
   ; MR1 = rad*TABLE_SIZE/(2*Pi)
   ; MR2 = TABLE_MASK

      MMOV32    MR0,@_:rad:                      
      MMOV32    MR1,@_CLAsincosTable_TABLE_SIZEDivTwoPi 
      MMPYF32   MR1,MR0,MR1                      
   || MMOV32    MR2,@_CLAsincosTable_TABLE_MASK         

   ; MR3 = K = integer(rad*TABLE_SIZE/(2*Pi))
   ; MR3 = K & TABLE_MASK
   ; MR3 = K * 2
   ; MAR0 = address of Sin(K)
   ; MR1 = frac(TABLE_SIZE*rad/2*Pi)
   ; MR0 = 2*Pi/TABLE_SIZE
   ; MR1 = X = frac(TABLE_SIZE*rad/2*Pi) * (2*Pi/TABLE_SIZE)
   ; MR0 = Coef3_neg

      MF32TOI32 MR3,MR1                          
      MAND32    MR3,MR3,MR2                      
      MLSL32    MR3,#1                           
      MMOV16    MAR0,MR3,#_CLAsincosTable_Sin0          
      MFRACF32  MR1,MR1                          
      MMOV32    MR0,@_CLAsincosTable_TwoPiDivTABLE_SIZE 
      MMPYF32   MR1,MR1,MR0                      
   || MMOV32    MR0,@_CLAsincosTable_Coef3_neg          

   ; MR2 = Sin(K)
   ; MR3 = Coef3_neg*Sin(K)
   ; MR2 = Cos(K)
   ; MR3 = X*Coef3_neg*Sin(K)

      MMOV32    MR2,*MAR0[#+64]++                
      MMPYF32   MR3,MR0,MR2                      
   || MMOV32    MR2,*MAR0[#-64]++                
      MMPYF32   MR3,MR3,MR1                      
   || MMOV32    MR0,@_CLAsincosTable_Coef2

   ; MR2 = Coef2*Cos(K)
   ; MR3 = Coef2*Cos(K) + X*Coef3_neg*Sin(K)
   ; MR2 = Sin(K)
   ; MR3 = X*Coef2*Cos(K) + X^2*Coef3_neg*Sin(K)

      MMPYF32   MR2,MR0,MR2                      
      MADDF32   MR3,MR3,MR2                      
   || MMOV32    MR2,*MAR0[#+64]++                
      MMPYF32   MR3,MR3,MR1                      
   || MMOV32    MR0,@_CLAsincosTable_Coef1_pos

   ; MR2 = Coef1_pos*Sin(K)
   ; MR3 = Coef1_pos*Sin(K) + X*Coef2*Cos(K) + X^2*Coef3_neg*Sin(K)
   ; MR2 = Cos(K)
   ; MR3 = X*Coef1_pos*Sin(K) + X^2*Coef2*Cos(K) + X^3*Coef3_neg*Sin(K)

      MMPYF32   MR2,MR0,MR2                      
      MADDF32   MR3,MR3,MR2                      
   || MMOV32    MR2,*MAR0[#-64]++                
      MMPYF32   MR3,MR3,MR1                      
   || MMOV32    MR0,@_CLAsincosTable_Coef0

   ; MR2 = Coef0*Cos(K)
   ; MR3 = Coef0*Cos(K) + X*Coef1_pos*Sin(K) + X^2*Coef2*Cos(K) 
   ;       + X^3*Coef3_neg*Sin(K)
   ;
   ; MR2 = Sin(K)
   ; MR3 = X*Coef0*Cos(K) + X^2*Coef1_pos*Sin(K) 
   ;       + X^3*Coef2*Cos(K) + X^4*Coef3_neg*Sin(K)

      MMPYF32   MR2,MR0,MR2                      
      MADDF32   MR3,MR3,MR2                      
   || MMOV32    MR2,*MAR0[#+64]++                
      MMPYF32   MR3,MR3,MR1                      

   ; MR3 = -Sin(K) + X^1*Coef0*Cos(K) + X^2*Coef1_pos*Sin(K) 
   ;       + X^3*Coef2*Cos(K) + X^4*Coef3_neg*Sin(K)
   ;
   ; MR3 = -X*Sin(K) + X^2*Coef0*Cos(K) + X^3*Coef1_pos*Sin(K) 
   ;       + X^4*Coef2*Cos(K) + X^5*Coef3_neg*Sin(K)
   ;
   ; MR2 = Cos(K)

      MSUBF32  MR3,MR3,MR2                      
      MMPYF32  MR3,MR3,MR1                      
   || MMOV32   MR2,*MAR0[#0]++                  

   ; MR3 = Cos(K) - X*Sin(K) + X^2*Coef0*Cos(K) + X^3*Coef1_pos*Sin(K) 
   ;       + X^4*Coef2*Cos(K) + X^5*Coef3_neg*Sin(K)
   ; Store Y = Cos(rad)

      MADDF32  MR3,MR2,MR3                       
      MMOV32   @_:y:,MR3                         
       .endm
        
;;============================================================================
;; End of macro
;;============================================================================ 
;;============================================================================
;; Macro: CLAcosPU
;;----------------------------------------------------------------------------
;; Description: Implement sine using taylor series expansion:
;;				
;;              radPU = K + X
;;
;;	  rad=radPU * 2 PI
;;
;;              Cos(rad) = Cos(K) - Sin(K)*X 
;;                                - Cos(K)*X^2/2! 
;;                                + Sin(K)*X^3/3! 
;;                                + Cos(K)*X^4/4! 
;;                                - Sin(K)*X^5/5!
;;
;;                       = Cos(K) + X*(-1.0*Sin(K) 
;;                                + X*(-0.5*Cos(K) 
;;                                + X*(0.166666*Sin(K) 
;;                                + X*(0.04166666*Cos(K) 
;;                                + X*(-0.00833333*Sin(K))))))
;;
;;                       = Cos(K) + X*(-Sin(K) 
;;                                + X*(Coef0*Cos(K) 
;;                                + X*(Coef1_pos*Sin(K) 
;;                                + X*(Coef2*Cos(K) 
;;                                + X*(Coef3_neg*Sin(K))))))
;;
;;
;; Equation:    y = Cos(rad)
;;
;; Regs Used:   MR0, MR1, MR2
;;
;; Input:   rad              f32 value in memory
;;
;; // TABLE_SIZE = 128
;;    CLAsincosTable.Sin0  =  0.0;               // sin(  0 * 2*pi/TABLE_SIZE)                  
;;    CLAsincosTable.Sin1  =  0.04906767432742;  // sin(  1 * 2*pi/TABLE_SIZE) 
;;    ...
;;    CLAsincosTable.Sin31 =  0.9987954562052;   // sin( 31 * 2*pi/TABLE_SIZE) 
;;    CLAsincosTable.Cos0  =  1.0;               // sin( 32 * 2*pi/TABLE_SIZE) 
;;    CLAsincosTable.Sin33 =  0.9987954562052;   // sin( 33 * 2*pi/TABLE_SIZE) 
;;    ...
;;    CLAsincosTable.Sin63 =  0.04906767432742;  // sin( 63 * 2*pi/TABLE_SIZE) 
;;    CLAsincosTable.Sin64 =  0.0;               // sin( 64 * 2*pi/TABLE_SIZE)                  
;;    CLAsincosTable.Sin65 = -0.04906767432742;  // sin( 65 * 2*pi/TABLE_SIZE) 
;;    ... 
;;    CLAsincosTable.Sin95 = -0.9987954562052;   // sin( 95 * 2*pi/TABLE_SIZE) 
;;    CLAsincosTable.Sin96 = -1.0;               // sin( 96 * 2*pi/TABLE_SIZE) 
;;    CLAsincosTable.Sin97 = -0.9987954562052;   // sin( 97 * 2*pi/TABLE_SIZE) 
;;    ...
;;    CLAsincosTable.Sin127 = -0.04906767432742; // sin(127 * 2*pi/TABLE_SIZE) 
;;    CLAsincosTable.Cos96  =  0.0;              // sin(  0 * 2*pi/TABLE_SIZE)                  
;;    CLAsincosTable.Cos97  =  0.04906767432742; // sin(  1 * 2*pi/TABLE_SIZE) 
;;    ... 
;;    CLAsincosTable.Cos127 =  0.9987954562052;  // sin( 31 * 2*pi/TABLE_SIZE) 
;;    CLAsincosTable.Cos128 =  1.0;              // sin( 32 * 2*pi/TABLE_SIZE)
;;
;;    // TABLE_SIZE/Pi           
;;    // 2*Pi/TABLE_SIZE
;;    // TABLE_MASK = (TABLE_SIZE*2 - 1) & 0xFFFFFFFE;; 
;;
;;    CLAsincosTable.TABLE_SIZE     =  128.0;      
;;    CLAsincosTable.TwoPiDivTABLE_SIZE  =  0.04908738521234;    
;;    CLAsincosTable.TABLE_MASK          =  0x000000FE;          
;;    CLAsincosTable.Coef0               = -0.5;
;;    CLAsincosTable.Coef1               = -0.1666666666666;
;;    CLAsincosTable.Coef1_pos           =  0.1666666666666;
;;    CLAsincosTable.Coef2               =  4.1666666666666e-2;
;;    CLAsincosTable.Coef3               =  8.3333333333333e-3;
;;    CLAsincosTable.Coef3_neg           = -8.3333333333333e-3;
;;
;; Output:  y                f32 value in memory
;;          MR0 = y          f32 result
;;
;; Benchmark:   Cycles = 26
;;              Instructions = 26 (104 bytes)
;;----------------------------------------------------------------------------  

CLAcosPU .macro   y, radPU
   
   ; MR0 = radPU
   ;MR0=MR0*MR3
   ; MR1 = TABLE_SIZE*Pi/(2*Pi)
   ; MR1 = radPU*TABLE_SIZE*Pi/(2*Pi)
   ; MR2 = TABLE_MASK
     		
      MMOV32    MR0,@_:radPU:                      
      MMOV32    MR1,@_CLAsincosTable_TABLE_SIZE							
      MMPYF32   MR1,MR0,MR1                      
   || MMOV32    MR2,@_CLAsincosTable_TABLE_MASK         

   ; MR3 = K = integer(radPU*TABLE_SIZE*Pi/(2*Pi))
   ; MR3 = K & TABLE_MASK
   ; MR3 = K * 2
   ; MAR0 = address of Sin(K)
   ; MR1 = frac(TABLE_SIZE*radPU*Pi/2*Pi)
   ; MR0 = 2*Pi/TABLE_SIZE
   ; MR1 = X = frac(TABLE_SIZE*radPU*Pi/2*Pi) * (2*Pi/TABLE_SIZE)
   ; MR0 = Coef3_neg

      MF32TOI32 MR3,MR1                          
      MAND32    MR3,MR3,MR2                      
      MLSL32    MR3,#1                           
      MMOV16    MAR0,MR3,#_CLAsincosTable_Sin0          
      MFRACF32  MR1,MR1                          
      MMOV32    MR0,@_CLAsincosTable_TwoPiDivTABLE_SIZE 
      MMPYF32   MR1,MR1,MR0                      
   || MMOV32    MR0,@_CLAsincosTable_Coef3_neg          

   ; MR2 = Sin(K)
   ; MR3 = Coef3_neg*Sin(K)
   ; MR2 = Cos(K)
   ; MR3 = X*Coef3_neg*Sin(K)

      MMOV32    MR2,*MAR0[#+64]++                
      MMPYF32   MR3,MR0,MR2                      
   || MMOV32    MR2,*MAR0[#-64]++                
      MMPYF32   MR3,MR3,MR1                      
   || MMOV32    MR0,@_CLAsincosTable_Coef2

   ; MR2 = Coef2*Cos(K)
   ; MR3 = Coef2*Cos(K) + X*Coef3_neg*Sin(K)
   ; MR2 = Sin(K)
   ; MR3 = X*Coef2*Cos(K) + X^2*Coef3_neg*Sin(K)

      MMPYF32   MR2,MR0,MR2                      
      MADDF32   MR3,MR3,MR2                      
   || MMOV32    MR2,*MAR0[#+64]++                
      MMPYF32   MR3,MR3,MR1                      
   || MMOV32    MR0,@_CLAsincosTable_Coef1_pos

   ; MR2 = Coef1_pos*Sin(K)
   ; MR3 = Coef1_pos*Sin(K) + X*Coef2*Cos(K) + X^2*Coef3_neg*Sin(K)
   ; MR2 = Cos(K)
   ; MR3 = X*Coef1_pos*Sin(K) + X^2*Coef2*Cos(K) + X^3*Coef3_neg*Sin(K)

      MMPYF32   MR2,MR0,MR2                      
      MADDF32   MR3,MR3,MR2                      
   || MMOV32    MR2,*MAR0[#-64]++                
      MMPYF32   MR3,MR3,MR1                      
   || MMOV32    MR0,@_CLAsincosTable_Coef0

   ; MR2 = Coef0*Cos(K)
   ; MR3 = Coef0*Cos(K) + X*Coef1_pos*Sin(K) + X^2*Coef2*Cos(K) 
   ;       + X^3*Coef3_neg*Sin(K)
   ;
   ; MR2 = Sin(K)
   ; MR3 = X*Coef0*Cos(K) + X^2*Coef1_pos*Sin(K) 
   ;       + X^3*Coef2*Cos(K) + X^4*Coef3_neg*Sin(K)

      MMPYF32   MR2,MR0,MR2                      
      MADDF32   MR3,MR3,MR2                      
   || MMOV32    MR2,*MAR0[#+64]++                
      MMPYF32   MR3,MR3,MR1                      

   ; MR3 = -Sin(K) + X^1*Coef0*Cos(K) + X^2*Coef1_pos*Sin(K) 
   ;       + X^3*Coef2*Cos(K) + X^4*Coef3_neg*Sin(K)
   ;
   ; MR3 = -X*Sin(K) + X^2*Coef0*Cos(K) + X^3*Coef1_pos*Sin(K) 
   ;       + X^4*Coef2*Cos(K) + X^5*Coef3_neg*Sin(K)
   ;
   ; MR2 = Cos(K)

      MSUBF32  MR3,MR3,MR2                      
      MMPYF32  MR3,MR3,MR1                      
   || MMOV32   MR2,*MAR0[#0]++                  

   ; MR3 = Cos(K) - X*Sin(K) + X^2*Coef0*Cos(K) + X^3*Coef1_pos*Sin(K) 
   ;       + X^4*Coef2*Cos(K) + X^5*Coef3_neg*Sin(K)
   ; Store Y = CosPU(radPU)

      MADDF32  MR3,MR2,MR3                       
      MMOV32   @_:y:,MR3                         
       .endm

;;============================================================================
;; End of macro
;;============================================================================

;;----------------------------------------------------------------------------
;; TI Macro $Revision: /main/4 $
;; Checkin $Date: May 26, 2009   14:58:09 $
;;============================================================================
;; Macro: CLAdiv
;;----------------------------------------------------------------------------
;; Description: Implement division using Newton-Raphson Method
;;              This macro is valid for CLA type 0
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
;; Benchmark:   Cycles = 12
;;              Instructions = 12 (48 bytes)
;;----------------------------------------------------------------------------  


CLAdiv .macro   Dest, Num, Den
      MMOV32    MR1,@_:Den:      ; MR1 = Den
      MEINVF32  MR2,MR1          ; MR2 = Ye = Estimate(1/Den)
      MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
      MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
      MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
      MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
   || MMOV32    MR0,@_:Num:      ; MR0 = Num
      MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
      MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
   || MMOV32    MR1,@_:Den:      ; Optional: Reload Den To Set Sign
      MNEGF32   MR0,MR0,EQ       ; Optional: if(Den == 0.0) Change Sign Of Num 
      MMPYF32   MR0,MR2,MR0      ; MR0 = Y = Ye*Num
      MMOV32    MR0,MR0          ; Optional: Set/Clear MSTF NF and ZF flags
      MMOV32    @_:Dest:,MR0     ; Store Y = Num/Den
      .endm
;;============================================================================
;; End of macro
;;============================================================================   

;;============================================================================
;; Macro: CLAexp
;;----------------------------------------------------------------------------
;; Description: 
;;             Step(1):   Calculate absolute of x   
;;
;;             Step(2):   Identify the integer and mantissa of the input
;;                      
;;             Step(3):   Obtain the e^integer(x) from the table 
;;
;;             Step(4):   Calculate the value of e^(mantissa)by using the 
;;                        polynomial approx = 1 + x*(1+x*0.5(1+(x/3)(1+x/4(1+X/5*(1+Xm/6*(1+Xm/7))))))
;;
;;             Step(5):   The value of e^x is the product of results from (3)&(4)
;;                        
;; 
;; Benchmark:   Cycles =   
;;              Instructions = 37 
;;----------------------------------------------------------------------------  

CLAexp .macro     y, x
;;------------------------------<< STEP 1 >>----------------------------------
       MMOV32    MR3,@_:x:                    ;
	   MABSF32   MR3,MR3                      ; LOAD |X| TO MR3

;;------------------------------<< STEP 2 >>----------------------------------
	   MF32TOI32 MR0,MR3                      ; MR0<=INTEGER(X)   
	   MFRACF32  MR1,MR3                      ; MR1<= MANTISSA(X)
;;------------------------------<< STEP 3 >>----------------------------------
	   MADD32    MR2,MR0,MR0
	   MMOV16    MAR1,MR2,#_CLAExpTable       ;
	  	   
;;------------------------------<< STEP 4 >>----------------------------------
	   MMOV32    MR2,@_CLAINV7                ;MR2<= 1/7
	   MMPYF32   MR3,MR2,MR1                  ;MR3<= Xm/7
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<= 1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=(1+Xm/7)

	   MMOV32    MR2,@_CLAINV6                ;MR2<= 1/6
	 ||MMPYF32   MR3,MR1,MR3                  ;MR3<=Xm(1+Xm/7)
	   MMPYF32   MR3,MR3,MR2                  ;MR3<=Xm(1+Xm/7)/6
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<=1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=1+(Xm/6)*(1+Xm/7)
	   
    || MMOV32    MR0,*MAR1                    ;MR0<= e^(INTEGER(X))

	   MMOV32    MR2,@_CLAINV5                ;MR2<= .2
	 ||MMPYF32   MR3,MR1,MR3                  ;MR3<=Xm(1+Xm/6*(1+Xm/7))
	   MMPYF32   MR3,MR3,MR2                  ;MR3<=Xm(1+Xm/6*(1+Xm/7))/5
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<=1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=1+(Xm/5)*(1+Xm/6*(1+Xm/7))

	   MMOV32    MR2,@_CLAINV4                ;MR2<= .25
	 ||MMPYF32   MR3,MR1,MR3                  ;MR3<=Xm(1+Xm/5*(1+Xm/6*(1+Xm/7)))
	   MMPYF32   MR3,MR3,MR2                  ;MR3<=Xm(1+Xm/5*(1+Xm/6*(1+Xm/7)))/4
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<=1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))

	   MMOV32    MR2,@_CLAINV3                ;MR2<= .3333333
	 ||MMPYF32   MR3,MR1,MR3                  ;MR3<=Xm(1+(Xm/4)*(1+Xm/5)*(1+Xm/6*(1+Xm/7)))
	   MMPYF32   MR3,MR3,MR2                  ;MR3<=Xm(1+(Xm/4)*(1+Xm/5)*(1+Xm/6*(1+Xm/7)))*0.333333
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<=1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7))))

       MMOV32    MR2,@_CLAINV2                ;MR2<= .5
	 ||MMPYF32   MR3,MR1,MR3                  ;MR3<=Xm(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))
	   MMPYF32   MR3,MR3,MR2                  ;MR3<=Xm(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))*0.5
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<=1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))Xm/2

	   MMPYF32   MR3,MR3,MR1                  ;MR3<= Xm(1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))Xm/2)
     ||MMOV32    MR2,@_CLAINV1                ;MR2<= 1
       MADDF32   MR3,MR3,MR2                  ;MR3<= e^(MANTISSA)= 1+Xm(1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6)*(1+Xm/7))))Xm/2)
;;------------------------------<< STEP 5 >>----------------------------------

	   MMPYF32   MR3,MR3,MR0                  ; MR3<= e^(MANTISSA) x e^(INTEGER(X))
       MMOV32    MR1,MR3,UNC
;;************************ Calculation of e^-x ******************************** 
      MEINVF32  MR2,MR1          ; MR2 = Ye = Estimate(1/Den)
      MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
      MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
      MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
      MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
                                 
      MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
      MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
;;****************************************************************************  
                             
     ||MMOV32    MR0,@_:x:          ; MR2 = X (set/clear NF,ZF)
   
      MMOV32    MR1,MR2,LT         ; update e^X with inverse value     

	   MMOV32      @_:y:,MR1                  ; Store Y = e^(X)
 
     .endm

;;============================================================================
;; End of macro
;;============================================================================

;;============================================================================
;; Macro: CLAexp10
;;----------------------------------------------------------------------------
;; Description: 
;;             Step(1):   Calculate absolute of x   
;;
;;             Step(2):   Identify the integer and mantissa of the input
;;                      
;;             Step(3):   Obtain the e^integer(x) from the table 
;;
;;             Step(4):   Calculate the value of e^(mantissa)by using the 
;;                        polynomial approx = 1 + x*(1+x*0.5(1+(x/3)(1+x/4*(1+Xm/5*(1+Xm/6*(1+Xm/7))))))
;;
;;             Step(5):   The value of e^x is the product of results from (3)&(4)
;;                        
;; 
;; Benchmark:   Cycles =    
;;              Instructions =  39
;;----------------------------------------------------------------------------  

CLAexp10 .macro     y, x
;;------------------------------<< STEP 1 >>----------------------------------
       MMOV32    MR3,@_:x:                    ;
	   MMOV32    MR1,@_CLALOG10               ;
	   MMPYF32   MR3,MR3,MR1                  ; X=INPUT/LOG10(e) 
	   MABSF32   MR3,MR3                      ; LOAD |X| TO MR3
;;------------------------------<< STEP 2 >>----------------------------------
	   MF32TOI32 MR0,MR3                      ; MR0<=INTEGER(X)   
	   MFRACF32  MR1,MR3                      ; MR1<= MANTISSA(X)
;;------------------------------<< STEP 3 >>----------------------------------
	   MADD32    MR2,MR0,MR0
	   MMOV16    MAR1,MR2,#_CLAExpTable       ;
	  	   
;;------------------------------<< STEP 4 >>----------------------------------
	   MMOV32    MR2,@_CLAINV7                ;MR2<= 1/7
	   MMPYF32   MR3,MR2,MR1                  ;MR3<= Xm/7
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<= 1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=(1+Xm/7)

	   MMOV32    MR2,@_CLAINV6                ;MR2<= 1/6
	 ||MMPYF32   MR3,MR1,MR3                  ;MR3<=Xm(1+Xm/7)
	   MMPYF32   MR3,MR3,MR2                  ;MR3<=Xm(1+Xm/7)/6
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<=1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=1+(Xm/6)*(1+Xm/7)
	   
    || MMOV32    MR0,*MAR1                    ;MR0<= e^(INTEGER(X))

	   MMOV32    MR2,@_CLAINV5                ;MR2<= .2
	 ||MMPYF32   MR3,MR1,MR3                  ;MR3<=Xm(1+Xm/6*(1+Xm/7))
	   MMPYF32   MR3,MR3,MR2                  ;MR3<=Xm(1+Xm/6*(1+Xm/7))/5
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<=1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=1+(Xm/5)*(1+Xm/6*(1+Xm/7))

	   MMOV32    MR2,@_CLAINV4                ;MR2<= .25
	 ||MMPYF32   MR3,MR1,MR3                  ;MR3<=Xm(1+Xm/5*(1+Xm/6*(1+Xm/7)))
	   MMPYF32   MR3,MR3,MR2                  ;MR3<=Xm(1+Xm/5*(1+Xm/6*(1+Xm/7)))/4
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<=1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))

	   MMOV32    MR2,@_CLAINV3                ;MR2<= .3333333
	 ||MMPYF32   MR3,MR1,MR3                  ;MR3<=Xm(1+(Xm/4)*(1+Xm/5)*(1+Xm/6*(1+Xm/7)))
	   MMPYF32   MR3,MR3,MR2                  ;MR3<=Xm(1+(Xm/4)*(1+Xm/5)*(1+Xm/6*(1+Xm/7)))/3
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<=1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7))))

       MMOV32    MR2,@_CLAINV2                ;MR2<= .5
	 ||MMPYF32   MR3,MR1,MR3                  ;MR3<=Xm(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))
	   MMPYF32   MR3,MR3,MR2                  ;MR3<=Xm(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))*0.5
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<=1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))Xm/2

	   MMPYF32   MR3,MR3,MR1                  ;MR3<= Xm(1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))Xm/2)
     ||MMOV32    MR2,@_CLAINV1                ;MR2<= 1
       MADDF32   MR3,MR3,MR2                  ;MR3<= e^(Xm)= 1+Xm(1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))Xm/2)
;;------------------------------<< STEP 5 >>----------------------------------

	   MMPYF32   MR3,MR3,MR0                  ; MR3<= e^(MANTISSA) x e^(INTEGER(X))
       MMOV32    MR1,MR3,UNC
;;************************ Calculation of e^-x ******************************** 
      MEINVF32  MR2,MR1          ; MR2 = Ye = Estimate(1/Den)
      MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
      MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
      MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
      MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
                                 
      MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
      MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
;;****************************************************************************  
                             
     ||MMOV32    MR0,@_:x:          ; MR2 = X (set/clear NF,ZF)
   
      MMOV32    MR1,MR2,LT         ; update e^X with inverse value     

	   MMOV32      @_:y:,MR1                  ; Store Y = e^(X)
 
     .endm
;;============================================================================
;; End of macro
;;============================================================================


;;============================================================================
;; Macro: CLAexp2
;;----------------------------------------------------------------------------
;; Description: 
;;             Step(1):   Calculate absolute of x=A/B  
;;
;;             Step(2):   Identify the integer and mantissa of the input
;;                      
;;             Step(3):   Obtain the e^integer(x) from the table 
;;
;;             Step(4):   Calculate the value of e^(mantissa)by using the 
;;                        polynomial approx = 1 + x*(1+x*0.5(1+(x/3)(1+x/4(1+X/5*(1+Xm/6*(1+Xm/7))))))
;;
;;             Step(5):   The value of e^x is the product of results from (3)&(4)
;;                        
;; 
;; Benchmark:   Cycles =   
;;              Instructions =  49
;;----------------------------------------------------------------------------  

CLAexp2 .macro     y, Num, Den
;;------------------------------<< STEP 1 >>----------------------------------

      MMOV32    MR1,@_:Den:      ; MR1 = Den
      MEINVF32  MR2,MR1          ; MR2 = Ye = Estimate(1/Den)
      MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
      MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
      MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
      MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
   || MMOV32    MR0,@_:Num:      ; MR0 = Num
      MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
      MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
   || MMOV32    MR1,@_:Den:      ; Optional: Reload Den To Set Sign
      MNEGF32   MR0,MR0,EQ       ; Optional: if(Den == 0.0) Change Sign Of Num 
      MMPYF32   MR0,MR2,MR0      ; MR0 = X = Ye*Num
      MMOV32    MR0,MR0          ; Optional: Set/Clear MSTF NF and ZF flags

    MABSF32   MR3,MR0                      ; LOAD |X| TO MR3
;;------------------------------<< STEP 2 >>----------------------------------
	   MF32TOI32 MR0,MR3                      ; MR0<=INTEGER(X)   
	   MFRACF32  MR1,MR3                      ; MR1<= MANTISSA(X)
;;------------------------------<< STEP 3 >>----------------------------------
	   MADD32    MR2,MR0,MR0
	   MMOV16    MAR1,MR2,#_CLAExpTable       ;
	  	   
;;------------------------------<< STEP 4 >>----------------------------------
	   MMOV32    MR2,@_CLAINV7                ;MR2<= 1/7
	   MMPYF32   MR3,MR2,MR1                  ;MR3<= Xm/7
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<= 1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=(1+Xm/7)
	   
    

       MMOV32    MR2,@_CLAINV6                ;MR2<= .2
	 ||MMPYF32   MR3,MR1,MR3                  ;MR3<=Xm(1+Xm/7)
	   MMPYF32   MR3,MR3,MR2                  ;MR3<=Xm(1+Xm/7)/6
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<=1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=1+(Xm/6)*(1+Xm/7)

	 || MMOV32    MR0,*MAR1                    ;MR0<= e^(INTEGER(X))

	   MMOV32    MR2,@_CLAINV5                ;MR2<= .2
	 ||MMPYF32   MR3,MR1,MR3                  ;MR3<=Xm(1+Xm/6*(1+Xm/7))
	   MMPYF32   MR3,MR3,MR2                  ;MR3<=Xm(1+Xm/6*(1+Xm/7))/5
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<=1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=1+(Xm/5)*(1+Xm/6*(1+Xm/7))

	   MMOV32    MR2,@_CLAINV4                ;MR2<= .25
	 ||MMPYF32   MR3,MR1,MR3                  ;MR3<=Xm(1+Xm/5*(1+Xm/6*(1+Xm/7)))
	   MMPYF32   MR3,MR3,MR2                  ;MR3<=Xm(1+Xm/5*(1+Xm/6*(1+Xm/7)))/4
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<=1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))

	   MMOV32    MR2,@_CLAINV3                ;MR2<= .3333333
	 ||MMPYF32   MR3,MR1,MR3                  ;MR3<=Xm(1+(Xm/4)*(1+Xm/5)*(1+Xm/6*(1+Xm/7)))
	   MMPYF32   MR3,MR3,MR2                  ;MR3<=Xm(1+(Xm/4)*(1+Xm/5)*(1+Xm/6*(1+Xm/7)))/3
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<=1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7))))

       MMOV32    MR2,@_CLAINV2                ;MR2<= .5
	 ||MMPYF32   MR3,MR1,MR3                  ;MR3<=Xm(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))
	   MMPYF32   MR3,MR3,MR2                  ;MR3<=Xm(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))*0.5
	 ||MMOV32    MR2,@_CLAINV1                ;MR2<=1
	   MADDF32   MR3,MR3,MR2                  ;MR3<=1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))Xm/2

	   MMPYF32   MR3,MR3,MR1                  ;MR3<= Xm(1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))Xm/2)
     ||MMOV32    MR2,@_CLAINV1                ;MR2<= 1
       MADDF32   MR3,MR3,MR2                  ;MR3<= e^(Xm)= 1+Xm(1+(1+(Xm/3)*(1+(Xm/4)*(1+Xm/5*(1+Xm/6*(1+Xm/7)))))Xm/2)
;;------------------------------<< STEP 5 >>----------------------------------

	   MMPYF32   MR3,MR3,MR0                  ; MR3<= e^(MANTISSA) x e^(INTEGER(X))
       MMOV32    MR1,MR3,UNC
;;************************ Calculation of e^-x ******************************** 
      MEINVF32  MR2,MR1          ; MR2 = Ye = Estimate(1/Den)
      MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
      MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
      MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
      MMPYF32   MR3,MR2,MR1      ; MR3 = Ye*Den
                                 
      MSUBF32   MR3,#2.0,MR3     ; MR3 = 2.0 - Ye*Den
      MMPYF32   MR2,MR2,MR3      ; MR2 = Ye = Ye*(2.0 - Ye*Den)
;;****************************************************************************  
                          
     ||MMOV32    MR0,@_:Num:          ; MR0 = X (set/clear NF,ZF)
       MMOV32    MR3,@_:Den:          ; MR3 = X (set/clear NF,ZF)
       MXOR32    MR0,MR0,MR3           ;
  
       MMOV32    MR1,MR2,LT         ; update e^X with inverse value     

	   MMOV32      @_:y:,MR1                  ; Store Y = e^(X)
 
    .endm

;;============================================================================
;; End of macro
;;============================================================================

;;----------------------------------------------------------------------------
;; TI Macro $Revision: /main/2 $
;; Checkin $Date: May 26, 2009   16:41:22 $
;;============================================================================
;; Macro: CLAisqrt
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
;; Benchmark:   Cycles = 13
;;              Instructions = 13 (52 bytes)
;;----------------------------------------------------------------------------  

CLAisqrt   .macro y, x
       MMOV32      MR0, @_:x:      ; MR0 = X
       MEISQRTF32  MR1, MR0        ; MR1 = Ye = Estimate(1/sqrt(X))        
       MMPYF32     MR2, MR0, #0.5  ; MR2 = X*0.5
       MMPYF32     MR3, MR1, MR1   ; MR3 = Ye*Ye
       MMPYF32     MR3, MR3, MR2   ; MR3 = Ye*Ye*X*0.5
       MSUBF32     MR3, #1.5,MR3   ; MR3 = 1.5 - Ye*Ye*X*0.5
       MMPYF32     MR1, MR1, MR3   ; MR1 = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
       MMPYF32     MR3, MR1, MR2   ; MR3 = Ye*X*0.5
       MMPYF32     MR3, MR1, MR3   ; MR3 = Ye*Ye*X*0.5
       MSUBF32     MR3, #1.5,MR3   ; MR3 = 1.5 - Ye*Ye*X*0.5        
       MMPYF32     MR0, MR1, MR3   ; MR0 = Ye = Ye*(1.5 - Ye*Ye*X*0.5)
       MMOV32      MR0, MR0        ; Optional: set MSTF NF and ZF flags
       MMOV32      @_:y:,MR0       ; Store Y = 1/(sqrt(X))
       .endm

;;============================================================================
;; End of macro
;;============================================================================  

;;============================================================================
;; Macro: CLALn
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
;;             Step(6):   Result = Ln(1+mantissa) + (Exponent-127)*(Ln(2))
;;                        
;; 
;; Benchmark:   Cycles =  25 
;;              Instructions =  25
;;----------------------------------------------------------------------------  

CLALn .macro     y, x

;;------------------------------<< STEP 1 >>----------------------------------
       MMOV32    MR3,@_:x:                    ;
	;   MABSF32   MR3,MR3                      ; LOAD |X| TO MR3
	   MMOV32   MR2, MR3                     ; LOAD |X| TO MR2

;;------------------------------<< STEP 2 >>----------------------------------
       MLSR32 MR2, #23                        ; MR2<= EXPONENT(X)
	   MI32TOF32 MR2,MR2                      ;
;;------------------------------<< STEP 3 >>----------------------------------
       MMOV32 MR1,@_CLALN_TABLE_MASK1         ; MR1<= 0x07FF FFFF
	   MAND32 MR3, MR1, MR3                   ; 
       MMOV32 MR1,@_CLALN_TABLE_MASK2         ; MR1<= 0x07F8 0000
	   MOR32  MR3, MR1, MR3                   ; MR3<=X/2^(EXPONENT)

	   MFRACF32 MR3,MR3                       ; MR3<= MANTISSA
;;------------------------------<< STEP 4 >>----------------------------------
;      || MMOV32 MR1,@_CLABIAS
;       MSUBF32 MR2,MR2,MR1                    ; MR2<= EXPONENT - BIAS
;
;	   ||MMOV32 MR1,@_CLALNV2                   ;
;       MMPYF32 MR2,MR2,MR1                    ; MR2<= (Exponent-127)*(Ln(2))

         MMPYF32     MR0,MR3,#32.0      ; 32 = Elements In Table
         MF32TOUI16  MR0,MR0            ; MR0 = int(32*x)
         MADD32      MR0,MR0,MR0        ; MR0 = 2*MR0
         MADD32      MR1,MR0,MR0        ; MR1 = 4*MR0
         MADD32      MR0,MR0,MR1        ; MR0 = 6*MR0 this is the index value for the stored data array
     
         MMOV16      MAR1,MR0,#_CLALnTable+4     ; MAR1 points to A2, this will be used later

        MMOV32 MR1,@_CLABIAS
        MSUBF32 MR2,MR2,MR1                    ; MR2<= EXPONENT - BIAS

	   ||MMOV32 MR1,@_CLALNV2                   ;
        MMPYF32 MR2,MR2,MR1                    ; MR2<= (Exponent-127)*(Ln(2))
;;------------------------------<< STEP 5 >>----------------------------------

; Ln(X) = A0 + Xm(A1 + A2*Xm)
        MMOV32      MR1,*MAR1[#-2]++  ; MR1 = A2
        MMPYF32     MR1,MR3,MR1       ; MR1 = A2*Xm
     || MMOV32      MR0,*MAR1[#-2]++  ; MR0 = A1
        MADDF32     MR1,MR0,MR1       ; MR1 = A1 + A2*Xm
        MMPYF32     MR0,MR3,MR1       ; MR0 = Xm*(A1 + A2*Xm)
      ||MMOV32      MR1,*MAR1[#-2]++         ; MR1 = A0 
        MADDF32     MR3,MR1,MR0       ; MR3 = A0 + Ratio*(A1 + A2*Ratio) = Ln(1+mantissa)

		MADDF32     MR3,MR3,MR2       ;
		MMOV32      @_:y:,MR3         ; Y= Ln(1+mantissa) + (Exponent-127)*(Ln(2))
 
     .endm

;;============================================================================
;; End of macro
;;============================================================================

;;============================================================================
;; Macro: CLALogN
;;----------------------------------------------------------------------------
;; Description: 
;;             Step(1):   Calculate log (A)  
;;
;;             Step(2):   Calculate log (B)
;;                      
;;            Step(2):   Calculate the log (A) / log (B)  
;;
;;                        
;; 
;; Benchmark:   Cycles =  
;;              Instructions =  25+25+2+12= 64
;;----------------------------------------------------------------------------  

CLALogN .macro     C,yt1,yt2, A, B
;;------------------------------<< STEP 1 >>----------------------------------

       CLALn      yt1, A                                    ;25 inst. cycles taken by macro.
	   
	   CLALn      yt2, B                                    ;25 inst. cycles taken by macro.
	   MNOP
	   MNOP
	   	  
	   CLAdiv     C,yt1,yt2                                  ;12 inst. cycles taken by macro.
	    
     .endm

;;============================================================================
;; End of macro
;;============================================================================
       

;;============================================================================
;; Macro: CLALOG10
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
;; Benchmark:   Cycles =    
;;              Instructions =  26
;;----------------------------------------------------------------------------  

CLALog10 .macro     y, x

;;------------------------------<< STEP 1 >>----------------------------------
       MMOV32    MR3,@_:x:                    ;
	;   MABSF32   MR3,MR3                      ; LOAD |X| TO MR3
	  MMOV32   MR2, MR3                     ; LOAD |X| TO MR2
;;------------------------------<< STEP 2 >>----------------------------------
       MLSR32 MR2, #23                        ; MR2<= EXPONENT(X)
	   MI32TOF32 MR2,MR2                      ;
;;------------------------------<< STEP 3 >>----------------------------------
       MMOV32 MR1,@_CLALN_TABLE_MASK1         ; MR1<= 0x07FF FFFF
	   MAND32 MR3, MR1, MR3                   ; 
       MMOV32 MR1,@_CLALN_TABLE_MASK2         ; MR1<= 0x07F8 0000
	   MOR32  MR3, MR1, MR3                   ; MR3<=X/2^(EXPONENT)

	   MFRACF32 MR3,MR3                       ; MR3<= MANTISSA
;;------------------------------<< STEP 4 >>----------------------------------
;      || MMOV32 MR1,@_CLABIAS
;       MSUBF32 MR2,MR2,MR1                    ; MR2<= EXPONENT - BIAS
;
;	   ||MMOV32 MR1,@_CLALNV2                   ;
;       MMPYF32 MR2,MR2,MR1                    ; MR2<= (Exponent-127)*(Ln(2))

         MMPYF32     MR0,MR3,#32.0      ; 32 = Elements In Table
         MF32TOUI16  MR0,MR0            ; MR0 = int(32*x)
         MADD32      MR0,MR0,MR0        ; MR0 = 2*MR0
         MADD32      MR1,MR0,MR0        ; MR1 = 4*MR0
         MADD32      MR0,MR0,MR1        ; MR0 = 6*MR0 this is the index value for the stored data array
     
         MMOV16      MAR1,MR0,#_CLALnTable+4     ; MAR1 points to A2, this will be used later

        MMOV32 MR1,@_CLABIAS
        MSUBF32 MR2,MR2,MR1                    ; MR2<= EXPONENT - BIAS

	   ||MMOV32 MR1,@_CLALNV2                   ;
        MMPYF32 MR2,MR2,MR1                    ; MR2<= (Exponent-127)*(Ln(2))
;;------------------------------<< STEP 5 >>----------------------------------

; Ln(X) = A0 + Xm(A1 + A2*Xm)
        MMOV32      MR1,*MAR1[#-2]++  ; MR1 = A2
        MMPYF32     MR1,MR3,MR1       ; MR1 = A2*Xm
      ||MMOV32      MR0,*MAR1[#-2]++  ; MR0 = A1
        MADDF32     MR1,MR0,MR1       ; MR1 = A1 + A2*Xm
        MMPYF32     MR0,MR3,MR1       ; MR0 = Xm*(A1 + A2*Xm)
      ||MMOV32      MR1,*MAR1[#-2]++         ; MR1 = A0 
        MADDF32     MR3,MR1,MR0       ; MR3 = A0 + Ratio*(A1 + A2*Ratio) = Ln(1+mantissa)

		MADDF32     MR3,MR3,MR2       ;
	  ||MMOV32      MR1,@_CLALNV10    ;
        MMPYF32     MR3,MR3,MR1       ;
		MMOV32      @_:y:,MR3         ; Y= (Ln(1+mantissa) + (Exponent-127)*(Ln(2)))/Ln(10)
 
     .endm

;;============================================================================
;; End of macro
;;============================================================================

;;============================================================================
;; Macro: CLAexpN
;;----------------------------------------------------------------------------
;; Description: 
;;             Step(1):   Calculate log (Num  ^ X )  
;;
;;                        Step(1.A):   Calculate log(Num)
;;                      
;;                        Step(1.B):   Multiply log(Num) & X
;;
;;             Step(2):   Calculate the value of e^(X*log(Num))
;;
;;                        
;; 
;; Benchmark:   Cycles =  
;;              Instructions =  25+6+37= 68
;;----------------------------------------------------------------------------  

CLAexpN .macro     y, Num, x
;;------------------------------<< STEP 1 >>----------------------------------

       CLALn      y, Num                                    ;25 inst. cycles taken by macro.
	   MMOV32     MR0,MR3
	   MMOV32     MR1,@_:x:
	   MMPYF32    MR0,MR0,MR1
	   MMOV32      @_:y:,MR0                               ; Store Y = e^(X)
	   MNOP;
	   MNOP;

	   CLAexp      y, y                                     ;37 inst. cycles taken by macro.
 
     .endm

;;============================================================================
;; End of macro
;;============================================================================

;;----------------------------------------------------------------------------
;; TI Macro $Revision: /main/5 $
;; Checkin $Date: May 20, 2009   14:11:20 $
;;============================================================================
;; Macro: CLAsin
;;----------------------------------------------------------------------------
;; Description: Implement sine using taylor series expansion:
;;
;;              rad = K + X
;;
;;              Sin(rad) = Sin(K) + Cos(K)*X 
;;                                - Sin(K)*X^2/2! 
;;                                - Cos(K)*X^3/3! 
;;                                + Sin(K)*X^4/4! 
;;                                + Cos(K)*X^5/5!
;;
;;                       = Sin(K) + X*(Cos(K) 
;;                                + X*(-0.5*Sin(K) 
;;                                + X*(-0.166666*Cos(K) 
;;                                + X*(0.04166666*Sin(K) 
;;                                + X*(0.00833333*Cos(K))))))
;;
;;                       = Sin(K) + X*(Cos(K) 
;;                                + X*(Coef0*Sin(K) 
;;                                + X*(Coef1*Cos(K) 
;;                                + X*(Coef2*Sin(K) 
;;                                + X*(Coef3*Cos(K))))))
;;
;;
;; Equation:    y = Sin(rad)
;; Regs Used:   MAR0, MR0, MR1, MR2, MR3
;; Input:       rad              f32 value in memory
;;
;; // TABLE_SIZE = 128
;; CLAsincosTable.Sin0   =  0.0;               // sin(  0 * 2*pi/TABLE_SIZE)                  
;; CLAsincosTable.Sin1   =  0.04906767432742;  // sin(  1 * 2*pi/TABLE_SIZE) 
;; ...
;; CLAsincosTable.Sin31  =  0.9987954562052;   // sin( 31 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Cos0   =  1.0;               // sin( 32 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Sin33  =  0.9987954562052;   // sin( 33 * 2*pi/TABLE_SIZE) 
;; ...
;; CLAsincosTable.Sin63  =  0.04906767432742;  // sin( 63 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Sin64  =  0.0;               // sin( 64 * 2*pi/TABLE_SIZE)                  
;; CLAsincosTable.Sin65  = -0.04906767432742;  // sin( 65 * 2*pi/TABLE_SIZE) 
;; ... 
;; CLAsincosTable.Sin95  = -0.9987954562052;   // sin( 95 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Sin96  = -1.0;               // sin( 96 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Sin97  = -0.9987954562052;   // sin( 97 * 2*pi/TABLE_SIZE) 
;; ...
;; CLAsincosTable.Sin127 = -0.04906767432742;  // sin(127 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Cos96  =  0.0;               // sin(  0 * 2*pi/TABLE_SIZE)                  
;; CLAsincosTable.Cos97  =  0.04906767432742;  // sin(  1 * 2*pi/TABLE_SIZE) 
;; ... 
;; CLAsincosTable.Cos127 =  0.9987954562052;   // sin( 31 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Cos128 =  1.0;               // sin( 32 * 2*pi/TABLE_SIZE) 
;;
;; CLAsincosTable.TABLE_SIZEDivPi        =  40.74366543152;               
;; CLAsincosTable.TwoPiDivTABLE_SIZE     =  0.04908738521234;  
;; CLAsincosTable.TABLE_MASK             =  0x000000FE;
;;       
;; CLAsincosTable.Coef0                  = -0.5;
;; CLAsincosTable.Coef1                  = -0.1666666666666;
;; CLAsincosTable.Coef1_pos              =  0.1666666666666;
;; CLAsincosTable.Coef2                  =  4.1666666666666e-2;
;; CLAsincosTable.Coef3                  =  8.3333333333333e-3;
;; CLAsincosTable.Coef3_neg              = -8.3333333333333e-3;
;;
;; Output:  y                f32 value in memory
;;          MR0 = y          f32 result
;;
;; Benchmark:   Cycles = 26
;;              Instructions = 26 (104 bytes)
;;----------------------------------------------------------------------------  

CLAsin .macro    y, rad

   ; MR0 = rad
   ; MR1 = TABLE_SIZE/(2*Pi)
   ; MR1 = rad*TABLE_SIZE/(2*Pi)
   ; MR2 = TABLE_MASK

      MMOV32    MR0,@_:rad:                      
      MMOV32    MR1,@_CLAsincosTable_TABLE_SIZEDivTwoPi 
      MMPYF32   MR1,MR0,MR1                      
   || MMOV32    MR2,@_CLAsincosTable_TABLE_MASK         

   ; MR3 = K = integer(rad*TABLE_SIZE/(2*Pi))
   ; MR3 = K & TABLE_MASK
   ; MR3 = K * 2
   ; MAR0 = address of Cos(K)

      MF32TOI32 MR3,MR1                          
      MAND32    MR3,MR3,MR2                      
      MLSL32    MR3,#1                           
      MMOV16    MAR0,MR3,#_CLAsincosTable_Cos0          

   ; MR1 = frac(TABLE_SIZE*rad/2*Pi)
   ; MR0 = 2*Pi/TABLE_SIZE
   ; MR1 = X = frac(TABLE_SIZE*rad/2*Pi) * (2*Pi/TABLE_SIZE)
   ; MR0 = Coef3

      MFRACF32  MR1,MR1                          
      MMOV32    MR0,@_CLAsincosTable_TwoPiDivTABLE_SIZE 
      MMPYF32   MR1,MR1,MR0                      
   || MMOV32    MR0,@_CLAsincosTable_Coef3              

   ; MR2 = Cos(K)
   ; MR3 = Coef3*Cos(K)
   ; MR2 = Sin(K)
   ; MR3 = X*Coef3*Cos(K)

      MMOV32   MR2,*MAR0[#-64]++                 
      MMPYF32  MR3,MR0,MR2                       
   || MMOV32   MR2,*MAR0[#+64]++                 
      MMPYF32  MR3,MR3,MR1                       
   || MMOV32   MR0,@_CLAsincosTable_Coef2

   ; MR2 = Coef2*Sin(K)
   ; MR3 = Coef2*Sin(K) + X*Coef3*Cos(K)
   ; MR2 = Cos(K)
   ; MR3 = X*Coef2*Sin(K) + X^2*Coef3*Cos(K)

      MMPYF32  MR2,MR0,MR2                       
      MADDF32  MR3,MR3,MR2                       
   || MMOV32   MR2,*MAR0[#-64]++                 
      MMPYF32  MR3,MR3,MR1                     
   || MMOV32   MR0,@_CLAsincosTable_Coef1

   ; MR2 = Coef1*Cos(K)
   ; MR3 = Coef1*Cos(K) + X*Coef2*Sin(K) + X^2*Coef3*Cos(K)
   ; MR2 = Sin(K)
   ; MR3 = X*Coef1*Cos(K) + X^2*Coef2*Sin(K) + X^3*Coef3*Cos(K)

      MMPYF32  MR2,MR0,MR2                       
      MADDF32  MR3,MR3,MR2                       
   || MMOV32   MR2,*MAR0[#+64]++                 
      MMPYF32  MR3,MR3,MR1                       
   || MMOV32   MR0,@_CLAsincosTable_Coef0

   ; MR2 = Coef0*Sin(K)
   ; MR3 = Coef0*Sin(K) + X*Coef1*Cos(K) + X^2*Coef2*Sin(K) + X^3*Coef3*Cos(K)
   ; MR2 = Cos(K)
   ; MR3 = X*Coef0*Sin(K) + X^2*Coef1*Cos(K) + X^3*Coef2*Sin(K) + X^4*Coef3*Cos(K)
  
      MMPYF32  MR2,MR0,MR2       
      MADDF32  MR3,MR3,MR2       
   || MMOV32   MR2,*MAR0[#-64]++ 
      MMPYF32  MR3,MR3,MR1                     

   ; MR3 = Cos(K) + X^1*Coef0*Sin(K) + X^2*Coef1*Cos(K) 
   ;       + X^3*Coef2*Sin(K) + X^4*Coef3*Cos(K)
   ;
   ; MR3 = X*Cos(K) + X^2*Coef0*Sin(K) + X^3*Coef1*Cos(K) 
   ;       + X^4*Coef2*Sin(K) + X^5*Coef3*Cos(K)
   ;
   ; MR2 = Sin(K)
   ;
   ; MR3 = Sin(K) + X*Cos(K) + X^2*Coef0*Sin(K) + X^3*Coef1*Cos(K) 
   ;       + X^4*Coef2*Sin(K) + X^5*Coef3*Cos(K)

      MADDF32  MR3,MR3,MR2                       
      MMPYF32  MR3,MR3,MR1                       
   || MMOV32   MR2,*MAR0[#0]++                   
      MADDF32  MR3,MR2,MR3                       

   ; Store Y = Sin(rad)

      MMOV32   @_:y:,MR3                         
      .endm

;;============================================================================
;; End of macro
;;============================================================================  
;;----------------------------------------------------------------------------
;; TI Macro $Revision: /main/4 $
;; Checkin $Date: May 20, 2009   18:09:58 $
;;============================================================================
;; Macro: CLAsincos
;;----------------------------------------------------------------------------        
;; Description: Implement sine + cosine using taylor series expansion:
;;
;;              rad = K + X
;;
;;              Cos(rad) = Cos(K) - Sin(K)*X 
;;                                - Cos(K)*X^2/2! 
;;                                + Sin(K)*X^3/3! 
;;                                + Cos(K)*X^4/4! 
;;                                - Sin(K)*X^5/5!
;;
;;                       = Cos(K) + X*(-1.0*Sin(K) 
;;                                + X*(-0.5*Cos(K) 
;;                                + X*(0.166666*Sin(K) 
;;                                + X*(0.04166666*Cos(K) 
;;                                + X*(-0.00833333*Sin(K))))))
;;
;;                       = Cos(K) + X*(-Sin(K) 
;;                                + X*(Coef0*Cos(K) 
;;                                + X*(Coef1_pos*Sin(K) 
;;                                + X*(Coef2*Cos(K) 
;;                                + X*(Coef3_neg*Sin(K)))))) 
;;
;;
;;              Sin(rad) = Sin(K) + Cos(K)*X 
;;                                - Sin(K)*X^2/2! 
;;                                - Cos(K)*X^3/3! 
;;                                + Sin(K)*X^4/4! 
;;                                + Cos(K)*X^5/5!
;;
;;                       = Sin(K) + X*(Cos(K) 
;;                                + X*(-0.5*Sin(K) 
;;                                + X*(-0.166666*Cos(K) 
;;                                + X*(0.04166666*Sin(K) 
;;                                + X*(0.00833333*Cos(K))))))
;;
;;                       = Sin(K) + X*(Cos(K) 
;;                                + X*(Coef0*Sin(K) 
;;                                + X*(Coef1*Cos(K) 
;;                                + X*(Coef2*Sin(K) 
;;                                + X*(Coef3*Cos(K))))))
;;
;; Equation:    y1 = sin(rad)
;;              y2 = cos(rad)
;;
;; Regs Used:   MR0, MR1, MR2, MR3, MAR0, MAR1
;;
;; Benchmark:   Cycles = 47
;;              Instructions = 47 (188 bytes)
;;----------------------------------------------------------------------------  
      
        
CLASinCos .macro  y1, y2, rad, tmp1, tmp2
   ; MR0 = rad
   ; MR1 = TABLE_SIZE/(2*Pi) 
   ; MR1 = rad*TABLE_SIZE/(2*Pi)
   ; MR2 = TABLE_MASK
   ; MR3 = K = integer(rad*TABLE_SIZE/(2*Pi))
   ; MR3 = K & TABLE_MASK
   ; MR3 = K * 2

      MMOV32    MR0,@_:rad:                              
      MMOV32    MR1,@_CLAsincosTable_TABLE_SIZEDivTwoPi  
      MMPYF32   MR1,MR0,MR1                              
   || MMOV32    MR2,@_CLAsincosTable_TABLE_MASK          
      MF32TOI32 MR3,MR1                                  
      MAND32    MR3,MR3,MR2                              
      MLSL32    MR3,#1                                   

; MAR0 = address of Cos(K)
; MR1 = frac(TABLE_SIZE*rad/2*Pi)
; MR0 = 2*Pi/TABLE_SIZE
; MR1 = X = frac(TABLE_SIZE*rad/2*Pi) * (2*Pi/TABLE_SIZE)
; MR0 = Coef3

      MMOV16    MAR0,MR3,#_CLAsincosTable_Cos0           
      MFRACF32  MR1,MR1                                  
      MMOV32    MR0,@_CLAsincosTable_TwoPiDivTABLE_SIZE  
      MMPYF32   MR1,MR1,MR0                              
   || MMOV32    MR0,@_CLAsincosTable_Coef3               

   ; MR2 = Cos(K)
   ; MR3 = Coef3*Cos(K)
   ; MR2 = Sin(K)
   ; MR3 = X*Coef3*Cos(K)  
   ; MR0 = Coef3_neg 

      MMOV32    MR2,*MAR0[#-64]++                
      MMPYF32   MR3,MR0,MR2                      
   || MMOV32    MR2,*MAR0[#+64]++                
      MMPYF32   MR3,MR3,MR1                      
   || MMOV32    MR0, @_CLAsincosTable_Coef3_neg    

   ; MR3 = Coef3_neg*Sin(K) 
   ; tmp1 = X*Coef3*Cos(K)  
   ; MR3 = X*Coef3_neg*Sin(K)
   ; MR0 = Coef2   
   ; MR2 = Coef2*Sin(K)
   ; tmp2 = X*Coef3*Sin(K) 

      MMPYF32   MR3,MR0,MR2                     
   || MMOV32    @_:tmp1:, MR3                   
      MMPYF32   MR3,MR3,MR1                     
   || MMOV32    MR0,@_CLAsincosTable_Coef2      
      MMPYF32   MR2,MR0,MR2                     
   || MMOV32    @_:tmp2:, MR3                   

   ; MR3 = X*Coef3*Cos(K)          
   ; MR3 = Coef2*Sin(K) + X*Coef3*Cos(K)
   ; MR2 = Cos(K)   
   ; MR3 = X*Coef2*Sin(K) + X^2*Coef3*Cos(K)  
   ; MR0 = Coef2*Cos(K) 
   ; tmp1 = X*Coef2*Sin(K) + X^2*Coef3*Cos(K)  
   
      MMOV32    MR3, @_:tmp1:                     
      MADDF32   MR3,MR3,MR2                       
   || MMOV32    MR2,*MAR0[#-64]++                 
      MMPYF32   MR3,MR3,MR1                       
      MMPYF32   MR0, MR0, MR2                     
   || MMOV32    @_:tmp1:, MR3                            
      
   ; MR3 = X*Coef3*Sin(K)      
   ; MR3 = Coef2*Cos(K) + X*Coef3_neg*Sin(K)
   ; MR3 = X*Coef2*Cos(K) - X^2*Coef3*Sin(K)   
   ; MR0 = Coef1   
   ; MR2 = Coef1*Cos(K)
   ; tmp2 = X*Coef2*Cos(K) - X^2*Coef3*Sin(K)

      MMOV32    MR3, @_:tmp2:                     
      MADDF32   MR3, MR0, MR3                     
      MMPYF32   MR3, MR3, MR1                        
   || MMOV32    MR0,@_CLAsincosTable_Coef1        
      MMPYF32   MR2,MR0,MR2                       
   || MMOV32    @_:tmp2:, MR3                     

   ; MR3 = X*Coef2*Sin(K) + X^2*Coef3*Cos(K)  (G)+(F)      
   ; MR3 = Coef1*Cos(K) + X*Coef2*Sin(K) + X^2*Coef3*Cos(K)      
   ; MR2 = Sin(K)   
   ; MR3 = X*Coef1*Cos(K) + X^2*Coef2*Sin(K) + X^3*Coef3*Cos(K)   
        ; MR0 = Coef1_pos

   ; MR0 = Coef1_pos*Sin(K)
   ; tmp1 = X*Coef1*Cos(K) + X^2*Coef2*Sin(K) + X^3*Coef3*Cos(K)   

      MMOV32    MR3, @_:tmp1:                    
      MADDF32   MR3,MR3,MR2                      
   || MMOV32    MR2,*MAR0[#+64]++                
      MMPYF32   MR3,MR3,MR1                                                                    
   || MMOV32    MR0, @_CLAsincosTable_Coef1_pos  

      MMPYF32   MR0, MR0, MR2                    
   || MMOV32    @_:tmp1:, MR3                    

   ; MR3 = X*Coef2*Cos(K) + X^2*Coef3_neg*Sin(K) (B)-(A) 
   ; MR3 = Coef1-pos*Sin(K) + X*Coef2*Cos(K) + X^2*Coef3_neg*Sin(K)
   ; MR3 = X*Coef1_pos*Sin(K) + X^2*Coef2*Cos(K) + X^3*Coef3_neg*Sin(K)  
       ; MR0 = Coef0 

   ; MR2 = Coef0*Sin(K)
   ; tmp2 = X*Coef1_pos*Sin(K) + X^2*Coef2*Cos(K) + X^3*Coef3_neg*Sin(K) 

   ; MR3 = X*Coef1*Cos(K) + X^2*Coef2*Sin(K) + X^3*Coef3*Cos(K)
   
      MMOV32    MR3, @_:tmp2:                     
      MADDF32   MR3, MR0, MR3                     
      MMPYF32   MR3, MR1, MR3                       
   || MMOV32    MR0,@_CLAsincosTable_Coef0        

      MMPYF32   MR2,MR0,MR2                       
   || MMOV32    @_:tmp2:, MR3                      
      
      MMOV32    MR3, @_:tmp1:                     
                                                  

   ; MR3 = Coef0*Sin(K) + X*Coef1*Cos(K) + X^2*Coef2*Sin(K) 
   ;     + X^3*Coef3*Cos(K)  
   ;                                                  
   ; MR2 = Cos(K)
   ;
   ; MR3 = X*Coef0*Sin(K) + X^2*Coef1*Cos(K) 
   ;     + X^3*Coef2*Sin(K) + X^4*Coef3*Cos(K)
   ;        
   ; MR3 = Cos(K) + X^1*Coef0*Sin(K) + X^2*Coef1*Cos(K) 
   ;     + X^3*Coef2*Sin(K) + X^4*Coef3*Cos(K)
   ;
   ; MR3 = X*Cos(K) + X^2*Coef0*Sin(K) + X^3*Coef1*Cos(K) 
   ;     + X^4*Coef2*Sin(K) + X^5*Coef3*Cos(K)

      MADDF32   MR3, MR2, MR3                     
   || MMOV32    MR2,*MAR0[#-64]++                 

      MMPYF32   MR3,MR3,MR1                       
      MADDF32   MR3,MR3,MR2                       
      MMPYF32   MR3,MR3,MR1                       

    ; MR0 = Coef0*Cos(K)      
    ; MR2 = Sin(K)

    ; MR3 = Sin(K) + X*Cos(K) + X^2*Coef0*Sin(K) 
    ;     + X^3*Coef1*Cos(K) + X^4*Coef2*Sin(K) + X^5*Coef3*Cos(K)
    ; Store Y1 = Sin(rad)
    ;
    ; MR3 = X*Coef1_pos*Sin(K) + X^2*Coef2*Cos(K) + X^3*Coef3_neg*Sin(K)   

      MMPYF32   MR0, MR0, MR2                   
   || MMOV32    MR2,*MAR0[#+64]++               

      MADDF32   MR3,MR2,MR3                     
      MMOV32    @_:y1:,MR3                      
      
      MMOV32    MR3, @_:tmp2:                   

    ; MR3 = Coef0*Cos(K) +  X*Coef1_pos*Sin(K) + X^2*Coef2*Cos(K) 
    ;       + X^3*Coef3_neg*Sin(K)            
    ;     
    ; MR3 = X*Coef0*Cos(K) +  X^2*Coef1_pos*Sin(K) 
    ;       + X^3*Coef2*Cos(K) + X^4*Coef3_neg*Sin(K)
    ;   
    ; MR3 = -Sin(K)+X*Coef0*Cos(K) +  X^2*Coef1_pos*Sin(K) 
    ;       + X^3*Coef2*Cos(K) + X^4*Coef3_neg*Sin(K)
    ;     
    ; MR2 = Cos(K)
    ; MR3 = -X*Sin(K) + X^2*Coef0*Cos(K) + X^3*Coef1_pos*Sin(K)
    ;       + X^4*Coef2*Cos(K) + X^5*Coef3_neg*Sin(K)   
    ;
    ; MR3 = Cos(K) - X*Sin(K) + X^2*Coef0*Cos(K) + X^3*Coef1_pos*Sin(K)
    ;       + X^4*Coef2*Cos(K) + X^5*Coef3_neg*Sin(K)  
    ; Store Y2 = Cos(rad)      
                                                  
      MADDF32   MR3, MR0, MR3                                                     
      MMPYF32   MR3, MR1, MR3                    
      MSUBF32   MR3, MR3, MR2                    
   || MMOV32    MR2,*MAR0[#0]++                  
      MMPYF32   MR3, MR1, MR3     
      MADDF32   MR3, MR2, MR3                                 
      MMOV32    @_:y2:,MR3                       
     .endm       
            
        
;;============================================================================
;; End of macro
;;============================================================================ 
;;============================================================================  
;;============================================================================
;; Macro: CLAsinPU
;;----------------------------------------------------------------------------
;; Description: Implement sine using taylor series expansion:
;;
;;              radPU = K + X
;;
;;              rad = radPU * PI
;;
;;              Sin(rad) = Sin(K) + Cos(K)*X 
;;                                - Sin(K)*X^2/2! 
;;                                - Cos(K)*X^3/3! 
;;                                + Sin(K)*X^4/4! 
;;                                + Cos(K)*X^5/5!
;;
;;                       = Sin(K) + X*(Cos(K) 
;;                                + X*(-0.5*Sin(K) 
;;                                + X*(-0.166666*Cos(K) 
;;                                + X*(0.04166666*Sin(K) 
;;                                + X*(0.00833333*Cos(K))))))
;;
;;                       = Sin(K) + X*(Cos(K) 
;;                                + X*(Coef0*Sin(K) 
;;                                + X*(Coef1*Cos(K) 
;;                                + X*(Coef2*Sin(K) 
;;                                + X*(Coef3*Cos(K))))))
;;
;;
;; Equation:    y = Sin(rad)
;; Regs Used:   MAR0, MR0, MR1, MR2, MR3
;; Input:       rad              f32 value in memory
;;
;; // TABLE_SIZE = 128
;; CLAsincosTable.Sin0   =  0.0;               // sin(  0 * 2*pi/TABLE_SIZE)                  
;; CLAsincosTable.Sin1   =  0.04906767432742;  // sin(  1 * 2*pi/TABLE_SIZE) 
;; ...
;; CLAsincosTable.Sin31  =  0.9987954562052;   // sin( 31 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Cos0   =  1.0;               // sin( 32 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Sin33  =  0.9987954562052;   // sin( 33 * 2*pi/TABLE_SIZE) 
;; ...
;; CLAsincosTable.Sin63  =  0.04906767432742;  // sin( 63 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Sin64  =  0.0;               // sin( 64 * 2*pi/TABLE_SIZE)                  
;; CLAsincosTable.Sin65  = -0.04906767432742;  // sin( 65 * 2*pi/TABLE_SIZE) 
;; ... 
;; CLAsincosTable.Sin95  = -0.9987954562052;   // sin( 95 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Sin96  = -1.0;               // sin( 96 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Sin97  = -0.9987954562052;   // sin( 97 * 2*pi/TABLE_SIZE) 
;; ...
;; CLAsincosTable.Sin127 = -0.04906767432742;  // sin(127 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Cos96  =  0.0;               // sin(  0 * 2*pi/TABLE_SIZE)                  
;; CLAsincosTable.Cos97  =  0.04906767432742;  // sin(  1 * 2*pi/TABLE_SIZE) 
;; ... 
;; CLAsincosTable.Cos127 =  0.9987954562052;   // sin( 31 * 2*pi/TABLE_SIZE) 
;; CLAsincosTable.Cos128 =  1.0;               // sin( 32 * 2*pi/TABLE_SIZE) 
;;
;; CLAsincosTable.TwoPiDivTABLE_SIZE     =  0.04908738521234;  
;; CLAsincosTable.TABLE_MASK             =  0x000000FE;
;;       
;; CLAsincosTable.Coef0                  = -0.5;
;; CLAsincosTable.Coef1                  = -0.1666666666666;
;; CLAsincosTable.Coef1_pos              =  0.1666666666666;
;; CLAsincosTable.Coef2                  =  4.1666666666666e-2;
;; CLAsincosTable.Coef3                  =  8.3333333333333e-3;
;; CLAsincosTable.Coef3_neg              = -8.3333333333333e-3;
;;
;; Output:  y                f32 value in memory
;;          MR0 = y          f32 result
;;
;; Benchmark:   Cycles = 26
;;              Instructions = 26 (104 bytes)
;;----------------------------------------------------------------------------  

CLAsinPU .macro    y, radPU

   ; MR0 = radPU
   ; MR1 = TABLE_SIZE*2Pi/(2*Pi)
   ; MR1 = rad*TABLE_SIZE*2Pi/(2*Pi)
   ; MR2 = TABLE_MASK

      MMOV32    MR0,@_:radPU:                      
      MMOV32    MR1,@_CLAsincosTable_TABLE_SIZE							
      MMPYF32   MR1,MR0,MR1                      
   || MMOV32    MR2,@_CLAsincosTable_TABLE_MASK         

   ; MR3 = K = integer(rad*TABLE_SIZE*Pi/(2*Pi))
   ; MR3 = K & TABLE_MASK
   ; MR3 = K * 2
   ; MAR0 = address of Cos(K)

      MF32TOI32 MR3,MR1                          
      MAND32    MR3,MR3,MR2                      
      MLSL32    MR3,#1                           
      MMOV16    MAR0,MR3,#_CLAsincosTable_Cos0          

   ; MR1 = frac(TABLE_SIZE*radPU*2Pi/2*Pi)
   ; MR0 = 2*Pi/TABLE_SIZE
   ; MR1 = X = frac(TABLE_SIZE*radPU*2Pi/2*Pi) * (2*Pi/TABLE_SIZE)
   ; MR0 = Coef3

      MFRACF32  MR1,MR1                          
      MMOV32    MR0,@_CLAsincosTable_TwoPiDivTABLE_SIZE 
      MMPYF32   MR1,MR1,MR0                      
   || MMOV32    MR0,@_CLAsincosTable_Coef3              

   ; MR2 = Cos(K)
   ; MR3 = Coef3*Cos(K)
   ; MR2 = Sin(K)
   ; MR3 = X*Coef3*Cos(K)

      MMOV32   MR2,*MAR0[#-64]++                 
      MMPYF32  MR3,MR0,MR2                       
   || MMOV32   MR2,*MAR0[#+64]++                 
      MMPYF32  MR3,MR3,MR1                       
   || MMOV32   MR0,@_CLAsincosTable_Coef2

   ; MR2 = Coef2*Sin(K)
   ; MR3 = Coef2*Sin(K) + X*Coef3*Cos(K)
   ; MR2 = Cos(K)
   ; MR3 = X*Coef2*Sin(K) + X^2*Coef3*Cos(K)

      MMPYF32  MR2,MR0,MR2                       
      MADDF32  MR3,MR3,MR2                       
   || MMOV32   MR2,*MAR0[#-64]++                 
      MMPYF32  MR3,MR3,MR1                     
   || MMOV32   MR0,@_CLAsincosTable_Coef1

   ; MR2 = Coef1*Cos(K)
   ; MR3 = Coef1*Cos(K) + X*Coef2*Sin(K) + X^2*Coef3*Cos(K)
   ; MR2 = Sin(K)
   ; MR3 = X*Coef1*Cos(K) + X^2*Coef2*Sin(K) + X^3*Coef3*Cos(K)

      MMPYF32  MR2,MR0,MR2                       
      MADDF32  MR3,MR3,MR2                       
   || MMOV32   MR2,*MAR0[#+64]++                 
      MMPYF32  MR3,MR3,MR1                       
   || MMOV32   MR0,@_CLAsincosTable_Coef0

   ; MR2 = Coef0*Sin(K)
   ; MR3 = Coef0*Sin(K) + X*Coef1*Cos(K) + X^2*Coef2*Sin(K) + X^3*Coef3*Cos(K)
   ; MR2 = Cos(K)
   ; MR3 = X*Coef0*Sin(K) + X^2*Coef1*Cos(K) + X^3*Coef2*Sin(K) + X^4*Coef3*Cos(K)
  
      MMPYF32  MR2,MR0,MR2       
      MADDF32  MR3,MR3,MR2       
   || MMOV32   MR2,*MAR0[#-64]++ 
      MMPYF32  MR3,MR3,MR1                     

   ; MR3 = Cos(K) + X^1*Coef0*Sin(K) + X^2*Coef1*Cos(K) 
   ;       + X^3*Coef2*Sin(K) + X^4*Coef3*Cos(K)
   ;
   ; MR3 = X*Cos(K) + X^2*Coef0*Sin(K) + X^3*Coef1*Cos(K) 
   ;       + X^4*Coef2*Sin(K) + X^5*Coef3*Cos(K)
   ;
   ; MR2 = Sin(K)
   ;
   ; MR3 = Sin(K) + X*Cos(K) + X^2*Coef0*Sin(K) + X^3*Coef1*Cos(K) 
   ;       + X^4*Coef2*Sin(K) + X^5*Coef3*Cos(K)

      MADDF32  MR3,MR3,MR2                       
      MMPYF32  MR3,MR3,MR1                       
   || MMOV32   MR2,*MAR0[#0]++                   
      MADDF32  MR3,MR2,MR3                       

   ; Store Y = SinPU(radPU)

      MMOV32   @_:y:,MR3                         
      .endm

;;============================================================================
;; End of macro
;;============================================================================   

;;----------------------------------------------------------------------------
;; TI Macro $Revision: /main/2 $
;; Checkin $Date: May 20, 2009   14:06:02 $
;;============================================================================
;; Macro: CLAsqrt
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
;; Benchmark:   Cycles = 14
;;          Instructions = 14 (56 bytes)
;;----------------------------------------------------------------------------  

CLAsqrt .macro     y, x
       MMOV32      MR0,@_:x:       ; MR0 = X
       MEISQRTF32  MR1,MR0         ; MR1 = Ye = Estimate(1/sqrt(X))
       MMOV32      MR1,@_:x:,EQ    ; if(X == 0.0) Ye = 0.0
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
       MMOV32      @_:y:,MR0       ; Store Y = sqrt(X)
       .endm

;;============================================================================
;; End of macro
;;============================================================================  
;;----------------------------------------------------------------------------
;; TI Macro $Revision: /main/2 $
;; Checkin $Date: May 20, 2009   14:06:02 $
;;============================================================================
;; Macro: CLAsqrt
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
;; Benchmark:   Cycles = 14
;;          Instructions = 14 (56 bytes)
;;----------------------------------------------------------------------------  

CLAsqrt .macro     y, x
       MMOV32      MR0,@_:x:       ; MR0 = X
       MEISQRTF32  MR1,MR0         ; MR1 = Ye = Estimate(1/sqrt(X))
       MMOV32      MR1,@_:x:,EQ    ; if(X == 0.0) Ye = 0.0
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
       MMOV32      @_:y:,MR0       ; Store Y = sqrt(X)
       .endm

;;============================================================================
;; End of macro
;;============================================================================  
;;----------------------------------------------------------------------------
;; TI Macro $Revision: /main/2 $
;; Checkin $Date: May 20, 2009   14:06:02 $
;;============================================================================
;; Macro: CLAsqrt
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
;; Benchmark:   Cycles = 14
;;          Instructions = 14 (56 bytes)
;;----------------------------------------------------------------------------  

CLAsqrt .macro     y, x
       MMOV32      MR0,@_:x:       ; MR0 = X
       MEISQRTF32  MR1,MR0         ; MR1 = Ye = Estimate(1/sqrt(X))
       MMOV32      MR1,@_:x:,EQ    ; if(X == 0.0) Ye = 0.0
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
       MMOV32      @_:y:,MR0       ; Store Y = sqrt(X)
       .endm

;;============================================================================
;; End of macro
;;============================================================================  
;;----------------------------------------------------------------------------
;; TI Macro $Revision: /main/2 $
;; Checkin $Date: May 20, 2009   14:06:02 $
;;============================================================================
;; Macro: CLAsqrt
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
;; Benchmark:   Cycles = 14
;;          Instructions = 14 (56 bytes)
;;----------------------------------------------------------------------------  

CLAsqrt .macro     y, x
       MMOV32      MR0,@_:x:       ; MR0 = X
       MEISQRTF32  MR1,MR0         ; MR1 = Ye = Estimate(1/sqrt(X))
       MMOV32      MR1,@_:x:,EQ    ; if(X == 0.0) Ye = 0.0
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
       MMOV32      @_:y:,MR0       ; Store Y = sqrt(X)
       .endm

;;============================================================================
;; End of macro
;;============================================================================  
;;----------------------------------------------------------------------------
;; TI Macro $Revision: /main/2 $
;; Checkin $Date: May 20, 2009   14:06:02 $
;;============================================================================
;; Macro: CLAsqrt
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
;; Benchmark:   Cycles = 14
;;          Instructions = 14 (56 bytes)
;;----------------------------------------------------------------------------  

CLAsqrt .macro     y, x
       MMOV32      MR0,@_:x:       ; MR0 = X
       MEISQRTF32  MR1,MR0         ; MR1 = Ye = Estimate(1/sqrt(X))
       MMOV32      MR1,@_:x:,EQ    ; if(X == 0.0) Ye = 0.0
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
       MMOV32      @_:y:,MR0       ; Store Y = sqrt(X)
       .endm

;;============================================================================
;; End of macro
;;============================================================================  
;;----------------------------------------------------------------------------
;; TI Macro $Revision: /main/2 $
;; Checkin $Date: May 20, 2009   14:06:02 $
;;============================================================================
;; Macro: CLAsqrt
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
;; Benchmark:   Cycles = 14
;;          Instructions = 14 (56 bytes)
;;----------------------------------------------------------------------------  

CLAsqrt .macro     y, x
       MMOV32      MR0,@_:x:       ; MR0 = X
       MEISQRTF32  MR1,MR0         ; MR1 = Ye = Estimate(1/sqrt(X))
       MMOV32      MR1,@_:x:,EQ    ; if(X == 0.0) Ye = 0.0
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
       MMOV32      @_:y:,MR0       ; Store Y = sqrt(X)
       .endm

;;============================================================================
;; End of macro
;;============================================================================  
;;----------------------------------------------------------------------------
;;            Copyright (c) 2009, 2010 Texas Instruments, Incorporated.
;;                           All Rights Reserved.
;;============================================================================
;;; End of File
;;===========================================================================
