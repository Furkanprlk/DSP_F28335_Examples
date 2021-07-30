;// TI File $Revision: /main/1 $
;// Checkin $Date: May 28, 2009   15:40:21 $
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
;// ucosg .cdecls to include a C-code header file that contains
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
;// even aligned.  Note: cosce all CLA instructions are 32-bit
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
;// The task1 calls for the CLA cos & cosPU macro which is defined in
;// the file  CLAmathLib_type0.inc  as:
;//
;// CLAcos    .macro  y, rad, table     ; y = cos(rad)
;// CLAcosPU    .macro  y, radPU, table     ; y = cos(radPU)

_Cla1Task1:
   .if CLA_DEBUG == 1
   MDEBUGSTOP
   .endif
   MSETFLG   	LUF=0,LVF=0,RNDF32=1
   CLAcosPU  Cla1ToCpuMsg.y0.f32,  CpuToCla1Msg.rad0
   CLAcos    Cla1ToCpuMsg.y1.f32,  CpuToCla1Msg.rad1
   CLAcosPU  Cla1ToCpuMsg.y2.f32,  CpuToCla1Msg.rad2
   CLAcos    Cla1ToCpuMsg.y3.f32,  CpuToCla1Msg.rad3
   CLAcosPU  Cla1ToCpuMsg.y4.f32,  CpuToCla1Msg.rad4
   CLAcos    Cla1ToCpuMsg.y5.f32,  CpuToCla1Msg.rad5
   CLAcosPU  Cla1ToCpuMsg.y6.f32,  CpuToCla1Msg.rad6
   CLAcos    Cla1ToCpuMsg.y7.f32,  CpuToCla1Msg.rad7
   CLAcosPU  Cla1ToCpuMsg.y8.f32,  CpuToCla1Msg.rad8
   CLAcos    Cla1ToCpuMsg.y9.f32,  CpuToCla1Msg.rad9
   CLAcosPU  Cla1ToCpuMsg.y10.f32, CpuToCla1Msg.rad10
   CLAcos    Cla1ToCpuMsg.y11.f32, CpuToCla1Msg.rad11
   CLAcosPU  Cla1ToCpuMsg.y12.f32, CpuToCla1Msg.rad12
   CLAcos    Cla1ToCpuMsg.y13.f32, CpuToCla1Msg.rad13
   CLAcosPU  Cla1ToCpuMsg.y14.f32, CpuToCla1Msg.rad14
   CLAcos    Cla1ToCpuMsg.y15.f32, CpuToCla1Msg.rad15
   CLAcosPU  Cla1ToCpuMsg.y16.f32, CpuToCla1Msg.rad16
   CLAcos    Cla1ToCpuMsg.y17.f32, CpuToCla1Msg.rad17
   CLAcosPU  Cla1ToCpuMsg.y18.f32, CpuToCla1Msg.rad18
   CLAcos    Cla1ToCpuMsg.y19.f32, CpuToCla1Msg.rad19
   MSTOP
_Cla1Task1End:


_Cla1Task2:
   .if CLA_DEBUG
   MDEBUGSTOP
   .endif
   MMOVIZ  MR0,#0.0
   MMOV32  @_Cla1ToCpuMsg.y0.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y1.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y2.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y3.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y4.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y5.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y6.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y7.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y8.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y9.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y10.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y11.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y12.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y13.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y14.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y15.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y16.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y17.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y18.f32,MR0
   MMOV32  @_Cla1ToCpuMsg.y19.f32,MR0
   MSTOP
_Cla1Task2End:

   MNOP
   MNOP
   MNOP

_Cla1Task3:
   .if CLA_DEBUG
   MDEBUGSTOP
   .endif
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
