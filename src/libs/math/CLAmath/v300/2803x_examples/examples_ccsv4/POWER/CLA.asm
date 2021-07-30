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
;// Each task calls the CLA ExpN macro which is defined in
;// the file CLAmathLib_type0.inc as:
;//
;//    CLAexpN   .macro  Dest, Source1, Source2    ; Dest = (Source1)^Source2
;//

_Cla1Task1:
        .if CLA_DEBUG == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0,TF=0
		CLAexpN		Cla1ToCpuMsg.y1.f32, CpuToCla1Msg.Num1, CpuToCla1Msg.X1
		MSTOP
_Cla1Task1End:


_Cla1Task2:
        .if CLA_DEBUG == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0,TF=0
		CLAexpN		Cla1ToCpuMsg.y1.f32, CpuToCla1Msg.Num1, CpuToCla1Msg.X1
		MSTOP
_Cla1Task2End:


_Cla1Task3:
        .if CLA_DEBUG == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0,TF=0
		CLAexpN		Cla1ToCpuMsg.y1.f32, CpuToCla1Msg.Num1, CpuToCla1Msg.X1
		MSTOP
_Cla1Task3End:


_Cla1Task4:
        .if CLA_DEBUG == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0,TF=0
		CLAexpN		Cla1ToCpuMsg.y1.f32, CpuToCla1Msg.Num1, CpuToCla1Msg.X1
		MSTOP
_Cla1Task4End:


_Cla1Task5:
        .if CLA_DEBUG == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0,TF=0
		CLAexpN		Cla1ToCpuMsg.y1.f32, CpuToCla1Msg.Num1, CpuToCla1Msg.X1
		MSTOP
_Cla1Task5End:


_Cla1Task6:
        .if CLA_DEBUG == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0,TF=0
		MSTOP
_Cla1Task6End:


_Cla1Task7:
        .if CLA_DEBUG == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0,TF=0
		MSTOP
_Cla1Task7End:


_Cla1Task8:
        .if CLA_DEBUG == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0,TF=0
		MSTOP
_Cla1Task8End:

