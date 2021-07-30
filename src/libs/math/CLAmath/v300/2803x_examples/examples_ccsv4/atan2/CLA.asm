;// TI File $Revision: /main/1 $
;// Checkin $Date: May 28, 2009   15:37:49 $
;//###########################################################################
;//
;// FILE:  Cla.asm
;//
;// TITLE: CLA Assembly Code.
;//
;// This file contains the CLA assembly code.  When building the project
;// containing this file, use C28x codegen V5.2.0 or later with the switch
;// --cla_support=cla0
;//
;//###########################################################################
;// $TI Release: CLAmath Version 3.00 $
;// $Release Date: Oct 15, 2010 $
;//###########################################################################

;// Include variables and constants that will be shared in the
;// C28x C-code and CLA assembly code.  This is accomplished by
;// using .cdecls to include a C-code header file that contains
;// these variables and constants

      .cdecls   C,LIST,"CLAShared.h"

;// Include the CLA math macro library.  This file has the source
;// code for the CLA macros used in this test program.
;// The macros used in this test are for CLA of type 0

         .include   "CLAmathLib_type0.inc"

;// To include an MDEBUGSTOP (CLA breakpoint) as the first instruction
;// of each task, set CLA_DEBUG to 1.  Use any other value to leave out
;// the MDEBUGSTOP instruction.

CLA_DEBUG .set  1

;// CLA code must be within its own assembly section and must be
;// even aligned.  Note: since all CLA instructions are 32-bit
;// this alignment naturally occurs and the .align 2 is most likely
;// redundant

       .sect        "Cla1Prog"
_Cla1Prog_Start
       .align       2

;// Each task clears the overflow/underflow flags in the STF
;// register.  This is done to test the setting of these
;// bits by some test cases.
;//
;// All tasks set the rounding mode set to 0
;//
;// Each task calls the CLA atan2 macro which is defined in
;// the file CLAMathLib_type0.inc as:
;//
;//    CLAatan2   .macro  Dest, Num, Den    ; Dest = atan2(Num/Den)
;//

_Cla1Task1:
        .if CLA_DEBUG == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0,TF=0
		CLAatan2		Cla1ToCpuMsg.z1.f32, CpuToCla1Msg.y1, CpuToCla1Msg.x1
		MSTOP
_Cla1Task1End:


_Cla1Task2:
        .if CLA_DEBUG == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0,TF=0
		CLAatan2		Cla1ToCpuMsg.z2.f32, CpuToCla1Msg.y2, CpuToCla1Msg.x2
		MSTOP
_Cla1Task2End:


_Cla1Task3:
        .if CLA_DEBUG == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0,TF=0
		CLAatan2		Cla1ToCpuMsg.z3.f32, CpuToCla1Msg.y3, CpuToCla1Msg.x3
		MSTOP
_Cla1Task3End:


_Cla1Task4:
        .if CLA_DEBUG == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0,TF=0
		CLAatan2		Cla1ToCpuMsg.z4.f32, CpuToCla1Msg.y4, CpuToCla1Msg.x4
		MSTOP
_Cla1Task4End:


_Cla1Task5:
        .if CLA_DEBUG == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0,TF=0
		CLAatan2		Cla1ToCpuMsg.z5.f32, CpuToCla1Msg.y5, CpuToCla1Msg.x5
		MSTOP
_Cla1Task5End:


_Cla1Task6:
        .if CLA_DEBUG == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0,TF=0
		CLAatan2		Cla1ToCpuMsg.z6.f32, CpuToCla1Msg.y6, CpuToCla1Msg.x6
		MSTOP
_Cla1Task6End:


_Cla1Task7:
        .if CLA_DEBUG == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0,TF=0
		CLAatan2		Cla1ToCpuMsg.z7.f32, CpuToCla1Msg.y7, CpuToCla1Msg.x7
		MSTOP
_Cla1Task7End:


_Cla1Task8:
        .if CLA_DEBUG == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0,TF=0
		CLAatan2		Cla1ToCpuMsg.z8.f32, CpuToCla1Msg.y8, CpuToCla1Msg.x8
		MSTOP
_Cla1Task8End:

