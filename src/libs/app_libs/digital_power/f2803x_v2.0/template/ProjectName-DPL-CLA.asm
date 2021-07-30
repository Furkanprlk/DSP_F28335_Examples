;----------------------------------------------------------------------------------
;	FILE:			{ProjectName}-DPL-CLA.asm
;
;	Description:	{ProjectName}-DPL-CLA.asm contains the code run by the CLA to service 
;					the tasks and also the initialization portion that is run by the C28x
;					for the DPlib CLA
;   
;   Revision/ Version: See {ProjectName}-Main.c
;----------------------------------------------------------------------------------

;// Include variables and constants that will be shared in the
;// C28x C-code and CLA assembly code.  This is accomplished by
;// using .cdecls to include a C-code header file that contains
;// these variables and constants

      .cdecls   C,LIST,"ProjectName-CLAShared.h"      
      
      
;// The following files have the assembly macros used in this file.
		; MACRO includes
	.include "PWMDRV_1ch_CLA.asm"
	 
;// To include an MDEBUGSTOP (CLA breakpoint) as the first instruction
;// of each task, set CLA_DEBUG to 1.  Use any other value to leave out
;// the MDEBUGSTOP instruction.

CLA_DEBUG .set  1

; label to DPCLA initialisation function
	.def _DPL_CLAInit
	
; dummy variable for pointer initialisation
ZeroNetCLA	.usect "ZeroNetCLA_Section",2,1,1	; output terminal 1

		.text
_DPL_CLAInit:
		ZAPA
		MOVL	XAR0, #ZeroNetCLA
		MOVL	*XAR0, ACC
		;---------------------------------------------------------
		.if(INCR_BUILD = 1)
			PWMDRV_1ch_CLA_INIT 1				; EPWM1A
		.endif
		;---------------------------------------------------------
	LRETR
	
	
;// CLA code must be within its own assembly section and must be
;// even aligned.  
;// Note: since all CLA instructions are 32-bit
;// this alignment naturally occurs and the .align 2 is most likely
;// redundant

      .sect    "Cla1Prog"
      .align  2

_Cla1Prog_Start:

_Cla1Task1:
	MNOP
	MNOP
;instruction to halt the CLA when debugging
    .if(CLA_DEBUG  = 1)
        MDEBUGSTOP  
    .endif
;task specific code 
    .if(INCR_BUILD = 1)
		PWMDRV_1ch_CLA   1
	.endif
;Clear EPWM Flag if PWM1 triggers the CLA task 
	.if(CLATASK1_EPWM1=1)
		MMOVXI		MR0,#0x01
		MMOV16      @_EPwm1Regs.ETCLR, MR0
	.endif
    MSTOP
    MNOP
    MNOP
    MNOP
_ClaT1End:


_Cla1Task2:
	MNOP
	MNOP
;instruction to halt the CLA when debugging
	.if(CLA_DEBUG  = 1)
        MDEBUGSTOP  
    .endif
;Clear EPWM Flag if PWM2 triggers the CLA task 
	.if(CLATASK2_EPWM2=1)
		MMOVXI		MR0,#0x01
		MMOV16      @_EPwm2Regs.ETCLR, MR0
	.endif
    MSTOP
    MNOP
    MNOP
    MNOP
_ClaT2End:


_Cla1Task3:
	MNOP
	MNOP
;instruction to halt the CLA when debugging
	.if(CLA_DEBUG  = 1)
        MDEBUGSTOP  
    .endif
;Clear EPWM Flag if PWM3 triggers the CLA task 
	.if(CLATASK3_EPWM3=1)
		MMOVXI		MR0,#0x01
		MMOV16      @_EPwm3Regs.ETCLR, MR0
	.endif
    MSTOP
    MNOP
    MNOP
    MNOP
_ClaT3End:


_Cla1Task4:
	MNOP
	MNOP
;instruction to halt the CLA when debugging
	.if(CLA_DEBUG  = 1)
        MDEBUGSTOP  
    .endif
;Clear EPWM Flag if PWM4 triggers the CLA task 
	.if(CLATASK4_EPWM4=1)
		MMOVXI		MR0,#0x01
		MMOV16      @_EPwm4Regs.ETCLR, MR0
	.endif
    MSTOP
    MNOP
    MNOP
    MNOP
_ClaT4End:


_Cla1Task5:
	MNOP
	MNOP
;instruction to halt the CLA when debugging
	.if(CLA_DEBUG  = 1)
        MDEBUGSTOP  
    .endif
;Clear EPWM Flag if PWM1 triggers the CLA task 
	.if(CLATASK5_EPWM5=1)
		MMOVXI		MR0,#0x01
		MMOV16      @_EPwm5Regs.ETCLR, MR0
	.endif
    MSTOP
    MNOP
    MNOP
    MNOP
_ClaT5End:

_Cla1Task6:
	MNOP
	MNOP
;instruction to halt the CLA when debugging
	.if(CLA_DEBUG  = 1)
        MDEBUGSTOP  
    .endif
;Clear EPWM Flag if PWM6 triggers the CLA task 
	.if(CLATASK6_EPWM6=1)
		MMOVXI		MR0,#0x01
		MMOV16      @_EPwm6Regs.ETCLR, MR0
	.endif
    MSTOP
    MNOP
    MNOP
    MNOP
_ClaT6End:

_Cla1Task7:
	MNOP
	MNOP
;instruction to halt the CLA when debugging
	.if(CLA_DEBUG  = 1)
        MDEBUGSTOP  
    .endif
;Clear EPWM Flag if PWM7 triggers the CLA task 
	.if(CLATASK7_EPWM7=1)
		MMOVXI		MR0,#0x01
		MMOV16      @_EPwm7Regs.ETCLR, MR0
	.endif
    MSTOP
    MNOP
    MNOP
    MNOP
_ClaT7End:

_Cla1Task8:
	MNOP
	MNOP
;instruction to halt the CLA when debugging
    .if(CLA_DEBUG  = 1)
        MDEBUGSTOP  
    .endif

;add any intialization code for memory in CLAtoCPUMsgRAM here
	.if(INCR_BUILD = 1)
	;.ref	_Var
	;MMOVF32	MR0,#0.0L
	;MF32TOUI32	MR0,MR0
	;MMOV32	@_Var,MR0
	.endif
    MSTOP 
    MNOP
    MNOP
    MNOP 
_ClaT8End:

_Cla1Prog_End:

