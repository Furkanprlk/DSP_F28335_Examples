;// TI File $Revision: /main/1 $
;// Checkin $Date: May 28, 2009   15:38:46 $
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
;// Each task calls the CLA arccos macro which is defined in
;// the file CLAmathLib_type0.inc as:
;//
;// CLAacos    .macro  y, rad, table     ; y = acos(rad)
;//

_Cla1Task1:
   .if CLA_DEBUG == 1
   MDEBUGSTOP
   .endif
   MSETFLG   	LUF=0,LVF=0,RNDF32=1
   
   CLAcos  Cla1ToCpuMsg.y0.f32,  CpuToCla1Msg.rad0
   CLAcos  Cla1ToCpuMsg.y1.f32,  CpuToCla1Msg.rad1
   CLAcos  Cla1ToCpuMsg.y2.f32,  CpuToCla1Msg.rad2
   CLAcos  Cla1ToCpuMsg.y3.f32,  CpuToCla1Msg.rad3
   CLAcos  Cla1ToCpuMsg.y4.f32,  CpuToCla1Msg.rad4
   CLAcos  Cla1ToCpuMsg.y5.f32,  CpuToCla1Msg.rad5
   CLAcos  Cla1ToCpuMsg.y6.f32,  CpuToCla1Msg.rad6
   CLAcos  Cla1ToCpuMsg.y7.f32,  CpuToCla1Msg.rad7
  

   MSTOP
_Cla1Task1End:


_Cla1Task2:
   .if CLA_DEBUG
   MDEBUGSTOP
   .endif
    MNOP
   MNOP
   MNOP
_Cla1Task2End:

  

_Cla1Task3:
   .if CLA_DEBUG
   MDEBUGSTOP
   .endif
   
   CLAacos  Cla1ToCpuMsg.ang0.f32,  CpuToCla1Msg.cos0
   CLAacos  Cla1ToCpuMsg.ang1.f32,  CpuToCla1Msg.cos1
   CLAacos  Cla1ToCpuMsg.ang2.f32,  CpuToCla1Msg.cos2
   CLAacos  Cla1ToCpuMsg.ang3.f32,  CpuToCla1Msg.cos3
   CLAacos  Cla1ToCpuMsg.ang4.f32,  CpuToCla1Msg.cos4
   CLAacos  Cla1ToCpuMsg.ang5.f32,  CpuToCla1Msg.cos5
   CLAacos  Cla1ToCpuMsg.ang6.f32,  CpuToCla1Msg.cos6
   CLAacos  Cla1ToCpuMsg.ang7.f32,  CpuToCla1Msg.cos7
    
   CLAacos  Cla1ToCpuMsg.ang8.f32,  CpuToCla1Msg.cos8
   CLAacos  Cla1ToCpuMsg.ang9.f32,  CpuToCla1Msg.cos9
   CLAacos  Cla1ToCpuMsg.ang10.f32,  CpuToCla1Msg.cos10
   CLAacos  Cla1ToCpuMsg.ang11.f32,  CpuToCla1Msg.cos11
   CLAacos  Cla1ToCpuMsg.ang12.f32,  CpuToCla1Msg.cos12
   CLAacos  Cla1ToCpuMsg.ang13.f32,  CpuToCla1Msg.cos13
   CLAacos  Cla1ToCpuMsg.ang14.f32,  CpuToCla1Msg.cos14
   CLAacos  Cla1ToCpuMsg.ang15.f32,  CpuToCla1Msg.cos15

   MSTOP
_Cla1Task3End:

_Cla1Task4:
   .if CLA_DEBUG
   MDEBUGSTOP
   .endif
   MSTOP
_Cla1Task4End:

_Cla1Task5:
   .if CLA_DEBUG
   MDEBUGSTOP
   .endif
   MSTOP
_Cla1Task5End:

_Cla1Task6:
   .if CLA_DEBUG
   MDEBUGSTOP
   .endif
   MSTOP
_Cla1Task6End:


_Cla1Task7:
   .if CLA_DEBUG
   MDEBUGSTOP
   .endif
   MSETFLG   	LUF=0,LVF=0,RNDF32=1
   MSTOP
_Cla1Task7End:


_Cla1Task8:
   .if CLA_DEBUG
   MDEBUGSTOP
   .endif
   MSETFLG   	LUF=0,LVF=0,RNDF32=1
   MSTOP
_Cla1Task8End:
