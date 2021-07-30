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

       .include   "CLAmathBasicLib_type0.inc"

;// To include an MDEBUGSTOP (CLA breakpoint) as the first instruction
;// of each task, set CLA_DEBUG to 1.  Use any other value to leave out
;// the MDEBUGSTOP instruction.

CLA_DEBUG_1 .set  0
CLA_DEBUG_2 .set  0
CLA_DEBUG_3 .set  0
CLA_DEBUG_4 .set  0
CLA_DEBUG_5 .set  0
CLA_DEBUG_6 .set  0
CLA_DEBUG_7 .set  1
CLA_DEBUG_8 .set  0
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

_Cla1Task1:
        .if CLA_DEBUG_1 == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0
		CLAadd		sCLAtoCPUMsg.y1,sCPUtoCLAMsg.x1,sCPUtoCLAMsg.x2
		CLAadd		sCLAtoCPUMsg.y2,sCPUtoCLAMsg.x3,sCPUtoCLAMsg.x4
		CLAadd		sCLAtoCPUMsg.y3,sCPUtoCLAMsg.x5,sCPUtoCLAMsg.x6
		CLAadd		sCLAtoCPUMsg.y4,sCPUtoCLAMsg.x7,sCPUtoCLAMsg.x8
				
		CLAsub		sCLAtoCPUMsg.y5,sCPUtoCLAMsg.x1,sCPUtoCLAMsg.x2
		CLAsub		sCLAtoCPUMsg.y6,sCPUtoCLAMsg.x3,sCPUtoCLAMsg.x4
		CLAsub		sCLAtoCPUMsg.y7,sCPUtoCLAMsg.x5,sCPUtoCLAMsg.x6
		CLAsub		sCLAtoCPUMsg.y8,sCPUtoCLAMsg.x7,sCPUtoCLAMsg.x8
		MSTOP
_Cla1Task1End:


_Cla1Task2:
        .if CLA_DEBUG_2 == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0
		CLAmul		sCLAtoCPUMsg.y1,sCPUtoCLAMsg.x1,sCPUtoCLAMsg.x2
		CLAmul		sCLAtoCPUMsg.y2,sCPUtoCLAMsg.x3,sCPUtoCLAMsg.x4
		CLAmul		sCLAtoCPUMsg.y3,sCPUtoCLAMsg.x5,sCPUtoCLAMsg.x6
		CLAmul		sCLAtoCPUMsg.y4,sCPUtoCLAMsg.x7,sCPUtoCLAMsg.x8
		
		CLAinv		sCLAtoCPUMsg.y5,sCPUtoCLAMsg.x1
		CLAinv		sCLAtoCPUMsg.y6,sCPUtoCLAMsg.x2
		CLAinv		sCLAtoCPUMsg.y7,sCPUtoCLAMsg.x3
		CLAinv		sCLAtoCPUMsg.y8,sCPUtoCLAMsg.x4
		MSTOP
_Cla1Task2End:


_Cla1Task3:
        .if CLA_DEBUG_3 == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0
   		;Save data from the CPU, This also allows you to check
   		;if the data rams switched over properly. This is one way
   		;to save data from the CPU. An alternative is to write the
   		;data to the CLA Data RAMs 0 and 1 before switching it over to
   		;the CLA
   		CLAcopy		sCLARam1Data_u.u1,sCPUtoCLAMsg.x1
   		CLAcopy		sCLARam1Data_u.u2,sCPUtoCLAMsg.x2
   		CLAcopy		sCLARam1Data_u.u3,sCPUtoCLAMsg.x3
   		CLAcopy		sCLARam1Data_u.u4,sCPUtoCLAMsg.x4
   		CLAcopy		sCLARam1Data_u.u5,sCPUtoCLAMsg.x5
   		CLAcopy		sCLARam1Data_u.u6,sCPUtoCLAMsg.x6
   		CLAcopy		sCLARam1Data_u.u7,sCPUtoCLAMsg.x7
   		CLAcopy		sCLARam1Data_u.u8,sCPUtoCLAMsg.x8
   		CLAcopy		sCLARam1Data_v.v1,sCPUtoCLAMsg.x1
   		CLAcopy		sCLARam1Data_v.v2,sCPUtoCLAMsg.x2
   		CLAcopy		sCLARam1Data_v.v3,sCPUtoCLAMsg.x3
   		CLAcopy		sCLARam1Data_v.v4,sCPUtoCLAMsg.x4
		CLAcopy		sCLARam1Data_v.v5,sCPUtoCLAMsg.x5
   		CLAcopy		sCLARam1Data_v.v6,sCPUtoCLAMsg.x6
   		CLAcopy		sCLARam1Data_v.v7,sCPUtoCLAMsg.x7
   		CLAcopy		sCLARam1Data_v.v8,sCPUtoCLAMsg.x8
   		   		
		CLAsatmax	sCLARam1Data_u.u1,sCLARam1Data_u.u2
		CLAsatmax	sCLARam1Data_u.u3,sCLARam1Data_u.u4
		CLAsatmax	sCLARam1Data_u.u5,sCLARam1Data_u.u6
		CLAsatmax	sCLARam1Data_u.u7,sCLARam1Data_u.u8
		
		CLAsatmin	sCLARam1Data_v.v1,sCLARam1Data_v.v2
		CLAsatmin	sCLARam1Data_v.v3,sCLARam1Data_v.v4
		CLAsatmin	sCLARam1Data_v.v5,sCLARam1Data_v.v6
		CLAsatmin	sCLARam1Data_v.v7,sCLARam1Data_v.v8
			
		;Send results back to the CPU
		CLAcopy		sCLAtoCPUMsg.y1,sCLARam1Data_u.u1
   		CLAcopy		sCLAtoCPUMsg.y2,sCLARam1Data_u.u3
   		CLAcopy		sCLAtoCPUMsg.y3,sCLARam1Data_u.u5
   		CLAcopy		sCLAtoCPUMsg.y4,sCLARam1Data_u.u7
   		CLAcopy		sCLAtoCPUMsg.y5,sCLARam1Data_v.v1
   		CLAcopy		sCLAtoCPUMsg.y6,sCLARam1Data_v.v3
   		CLAcopy		sCLAtoCPUMsg.y7,sCLARam1Data_v.v5
   		CLAcopy		sCLAtoCPUMsg.y8,sCLARam1Data_v.v7
   		
		MSTOP
_Cla1Task3End:


_Cla1Task4:
        .if CLA_DEBUG_4 == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0
   		;Save data from the CPU, This also allows you to check
   		;if the data rams switched over properly. This is one way
   		;to save data from the CPU. An alternative is to write the
   		;data to the CLA Data RAMs 0 and 1 before switching it over to
   		;the CLA
   		CLAcopy		sCLARam1Data_v.v1,sCPUtoCLAMsg.x1
   		CLAcopy		sCLARam1Data_v.v2,sCPUtoCLAMsg.x2
   		CLAcopy		sCLARam1Data_v.v3,sCPUtoCLAMsg.x3
   		CLAcopy		sCLARam1Data_v.v4,sCPUtoCLAMsg.x4
		CLAcopy		sCLARam1Data_v.v5,sCPUtoCLAMsg.x5
   		CLAcopy		sCLARam1Data_v.v6,sCPUtoCLAMsg.x6
   		CLAcopy		sCLARam1Data_v.v7,sCPUtoCLAMsg.x7
   		CLAcopy		sCLARam1Data_v.v8,sCPUtoCLAMsg.x8
    		
   		CLAsatmaxmin sCLARam1Data_u.u1,sCLARam1Data_v.v1,sCLARam1Data_v.v2
		CLAsatmaxmin sCLARam1Data_u.u3,sCLARam1Data_v.v3,sCLARam1Data_v.v4
		CLAsatmaxmin sCLARam1Data_u.u5,sCLARam1Data_v.v5,sCLARam1Data_v.v6
		CLAsatmaxmin sCLARam1Data_u.u7,sCLARam1Data_v.v7,sCLARam1Data_v.v8			
		;Send results back to the CPU
		CLAcopy		sCLAtoCPUMsg.y1,sCLARam1Data_u.u1
		CLAcopy		sCLAtoCPUMsg.y2,sCLARam1Data_u.u3
		CLAcopy		sCLAtoCPUMsg.y3,sCLARam1Data_u.u5
   		CLAcopy		sCLAtoCPUMsg.y4,sCLARam1Data_u.u7
		
		MSTOP
_Cla1Task4End:


_Cla1Task5:
        .if CLA_DEBUG_5 == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0
   		;Save data from the CPU, This also allows you to check
   		;if the data rams switched over properly. This is one way
   		;to save data from the CPU. An alternative is to write the
   		;data to the CLA Data RAMs 0 and 1 before switching it over to
   		;the CLA
   		CLAcopy		sCLARam1Data_u.u1,sCPUtoCLAMsg.x1
   		CLAcopy		sCLARam1Data_u.u2,sCPUtoCLAMsg.x2
   		CLAcopy		sCLARam1Data_u.u3,sCPUtoCLAMsg.x3
   		CLAcopy		sCLARam1Data_u.u4,sCPUtoCLAMsg.x4
   		CLAcopy		sCLARam1Data_u.u5,sCPUtoCLAMsg.x5
   		CLAcopy		sCLARam1Data_u.u6,sCPUtoCLAMsg.x6
   		CLAcopy		sCLARam1Data_u.u7,sCPUtoCLAMsg.x7
   		CLAcopy		sCLARam1Data_u.u8,sCPUtoCLAMsg.x8
   		
   		CLAsuboffsetsatzero	sCLARam1Data_u.u1,sCLARam1Data_u.u2
		CLAsuboffsetsatzero	sCLARam1Data_u.u3,sCLARam1Data_u.u4
		CLAsuboffsetsatzero	sCLARam1Data_u.u5,sCLARam1Data_u.u6
		CLAsuboffsetsatzero	sCLARam1Data_u.u7,sCLARam1Data_u.u8
		CLAsuboffsetsatzero	sCLARam1Data_u.u7,sCLARam1Data_u.u8
		CLAsuboffsetsatzero	sCLARam1Data_u.u7,sCLARam1Data_u.u8
		
		CLAabs		sCLAtoCPUMsg.y1,sCPUtoCLAMsg.x1
		CLAabs		sCLAtoCPUMsg.y2,sCPUtoCLAMsg.x2
		CLAabs		sCLAtoCPUMsg.y3,sCPUtoCLAMsg.x3
		CLAabs		sCLAtoCPUMsg.y4,sCPUtoCLAMsg.x4
		
		;Send results back to the CPU
		CLAcopy		sCLAtoCPUMsg.y5,sCLARam1Data_u.u1
   		CLAcopy		sCLAtoCPUMsg.y6,sCLARam1Data_u.u3
		CLAcopy		sCLAtoCPUMsg.y7,sCLARam1Data_u.u5
   		CLAcopy		sCLAtoCPUMsg.y8,sCLARam1Data_u.u7
   			
		MSTOP
_Cla1Task5End:


_Cla1Task6:
        .if CLA_DEBUG_6 == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0
		CLAIQ24toF	sCLARam1Data_u.u1,sCPUtoCLAMsg.x1
		CLAIQ24toF	sCLARam1Data_u.u2,sCPUtoCLAMsg.x2
		CLAIQ24toF	sCLARam1Data_u.u3,sCPUtoCLAMsg.x3
		CLAIQ24toF	sCLARam1Data_u.u4,sCPUtoCLAMsg.x4
		CLAIQ24toF	sCLARam1Data_u.u5,sCPUtoCLAMsg.x5
		CLAIQ24toF	sCLARam1Data_u.u6,sCPUtoCLAMsg.x6
		CLAIQ24toF	sCLARam1Data_u.u7,sCPUtoCLAMsg.x7
		CLAIQ24toF	sCLARam1Data_u.u8,sCPUtoCLAMsg.x8
		CLAadd		sCLAtoCPUMsg.y1,sCLARam1Data_u.u1,sCLARam1Data_u.u2
		CLAsub		sCLAtoCPUMsg.y2,sCLARam1Data_u.u3,sCLARam1Data_u.u4
		CLAmul		sCLAtoCPUMsg.y3,sCLARam1Data_u.u5,sCLARam1Data_u.u6
		CLAmul		sCLAtoCPUMsg.y4,sCLARam1Data_u.u7,sCLARam1Data_u.u8
		CLAFtoIQ24  sCLAtoCPUMsg.y1,sCLAtoCPUMsg.y1
		CLAFtoIQ24  sCLAtoCPUMsg.y2,sCLAtoCPUMsg.y2
		CLAFtoIQ24  sCLAtoCPUMsg.y3,sCLAtoCPUMsg.y3
		CLAFtoIQ24  sCLAtoCPUMsg.y4,sCLAtoCPUMsg.y4
		MSTOP
_Cla1Task6End:


_Cla1Task7:
		;A set of 8 values x1,x2 ....x8 are subjected to conditional
		;tests to check that branching occurs as expected
		;Y - binary 1, N - binary 0
		;A path with two Y and a N i.e. YYN is 110 in binary or 6
		; 										  Y->{L7 ->111,7}
		;						  Y->L3:{x7~=x8}->
		;						  |               N->{L8 ->110,6]
		;		   Y->L1:{x3<x4}->			
		;          |              |				  Y->{L9 ->101,5}
		;          |			  N->L4:{x7==x8}-> 
		;          |							  N->{L10->100,4}
		;{x1>x2}->
		;		   |                              Y->{L11->011,3}
		;          |              Y->L5:{x5>=x6}->
		;          |              |               N->{L12->010,2}
		;		   N->L2:{x4<x3}->
		;						  |               Y->{L13->001,1}
		;						  N->L6:{x5<=x6}->
		;                                         N->{L14->000,0}
		
		
	    .if CLA_DEBUG_7 == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0
		CLAcondexec	sCPUtoCLAMsg.x1,sCPUtoCLAMsg.x2,GT,T7_L1,T7_L2
		
_T7_L1: CLAcondexec	sCPUtoCLAMsg.x3,sCPUtoCLAMsg.x4,LT,T7_L3,T7_L4

_T7_L2: CLAcondexec	sCPUtoCLAMsg.x4,sCPUtoCLAMsg.x3,LT,T7_L5,T7_L6

_T7_L3: CLAcondexec	sCPUtoCLAMsg.x7,sCPUtoCLAMsg.x8,NEQ,T7_L7,T7_L8

_T7_L4: CLAcondexec	sCPUtoCLAMsg.x7,sCPUtoCLAMsg.x8,EQ,T7_L9,T7_L10

_T7_L5: CLAcondexec	sCPUtoCLAMsg.x5,sCPUtoCLAMsg.x6,GEQ,T7_L11,T7_L12

_T7_L6: CLAcondexec	sCPUtoCLAMsg.x5,sCPUtoCLAMsg.x6,LEQ,T7_L13,T7_L14

_T7_L7: MMOVIZ	MR0,#7.0
		MMOV32	@_sCLAtoCPUMsg.y1,MR0
		MSTOP
		
_T7_L8: MMOVIZ	MR0,#6.0
		MMOV32	@_sCLAtoCPUMsg.y1,MR0
		MSTOP
		
_T7_L9: MMOVIZ	MR0,#5.0
		MMOV32	@_sCLAtoCPUMsg.y1,MR0
		MSTOP
		
_T7_L10:MMOVIZ	MR0,#4.0
		MMOV32	@_sCLAtoCPUMsg.y1,MR0
		MSTOP
		
_T7_L11:MMOVIZ	MR0,#3.0
		MMOV32	@_sCLAtoCPUMsg.y1,MR0
		MSTOP
		
_T7_L12:MMOVIZ	MR0,#2.0
		MMOV32	@_sCLAtoCPUMsg.y1,MR0
		MSTOP
		
_T7_L13:MMOVIZ	MR0,#1.0
		MMOV32	@_sCLAtoCPUMsg.y1,MR0
		MSTOP
		
_T7_L14:MMOVIZ	MR0,#0.0
		MMOV32	@_sCLAtoCPUMsg.y1,MR0
		MSTOP
_Cla1Task7End:


_Cla1Task8:
        .if CLA_DEBUG_8 == 1
        MDEBUGSTOP
       .endif
   		MSETFLG   	LUF=0,LVF=0,RNDF32=0
		
		MSTOP
_Cla1Task8End:

