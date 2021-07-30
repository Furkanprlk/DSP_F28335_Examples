;// TI File $Revision: /main/1 $
;// Checkin $Date: May 28, 2009   15:38:17 $
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
;// Each task calls the CLAsincos macro which is defined in
;// the file CLAmathLib_type0.inc as:
;//
;; CLAsincos .macro  y1, y2, rad, tmp1, tmp2   ; y1 = sin(rad) y2 = cos(rad)
;//

_Cla1Task1:
   .if CLA_DEBUG == 1
   MDEBUGSTOP
   .endif
   MSETFLG   	LUF=0,LVF=0,RNDF32=1
_CLAsincosStart:
   CLAsincos	Cla1ToCpuMsg.s0.f32,  Cla1ToCpuMsg.c0.f32, CpuToCla1Msg.rad0,  Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
_CLAsincosEnd:
   CLAsincos 	Cla1ToCpuMsg.s1.f32,  Cla1ToCpuMsg.c1.f32, CpuToCla1Msg.rad1,  Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s2.f32,  Cla1ToCpuMsg.c2.f32, CpuToCla1Msg.rad2,  Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s3.f32,  Cla1ToCpuMsg.c3.f32, CpuToCla1Msg.rad3,  Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s4.f32,  Cla1ToCpuMsg.c4.f32, CpuToCla1Msg.rad4,  Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s5.f32,  Cla1ToCpuMsg.c5.f32, CpuToCla1Msg.rad5,  Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s6.f32,  Cla1ToCpuMsg.c6.f32, CpuToCla1Msg.rad6,  Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s7.f32,  Cla1ToCpuMsg.c7.f32, CpuToCla1Msg.rad7,  Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s8.f32,  Cla1ToCpuMsg.c8.f32, CpuToCla1Msg.rad8,  Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s9.f32,  Cla1ToCpuMsg.c9.f32, CpuToCla1Msg.rad9,  Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s10.f32, Cla1ToCpuMsg.c10.f32, CpuToCla1Msg.rad10, Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s11.f32, Cla1ToCpuMsg.c11.f32, CpuToCla1Msg.rad11, Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s12.f32, Cla1ToCpuMsg.c12.f32, CpuToCla1Msg.rad12, Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s13.f32, Cla1ToCpuMsg.c13.f32, CpuToCla1Msg.rad13, Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s14.f32, Cla1ToCpuMsg.c14.f32, CpuToCla1Msg.rad14, Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s15.f32, Cla1ToCpuMsg.c15.f32, CpuToCla1Msg.rad15, Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s16.f32, Cla1ToCpuMsg.c16.f32, CpuToCla1Msg.rad16, Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s17.f32, Cla1ToCpuMsg.c17.f32, CpuToCla1Msg.rad17, Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s18.f32, Cla1ToCpuMsg.c18.f32, CpuToCla1Msg.rad18, Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2
   CLAsincos	Cla1ToCpuMsg.s19.f32, Cla1ToCpuMsg.c19.f32, CpuToCla1Msg.rad19, Cla1ToCpuMsg.temp1, Cla1ToCpuMsg.temp2

   MSTOP
_Cla1Task1End:


_Cla1Task2:
   .if CLA_DEBUG
   MDEBUGSTOP
   .endif
   MMOVIZ  MR0,#0.0
   MMOV32		@_Cla1ToCpuMsg.s0.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s1.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s2.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s3.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s4.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s5.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s6.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s7.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s8.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s9.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s10.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s11.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s12.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s13.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s14.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s15.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s16.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s17.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s18.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.s19.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c0.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c1.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c2.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c3.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c4.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c5.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c6.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c7.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c8.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c9.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c10.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c11.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c12.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c13.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c14.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c15.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c16.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c17.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c18.f32,MR0
   MMOV32		@_Cla1ToCpuMsg.c19.f32,MR0  
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
