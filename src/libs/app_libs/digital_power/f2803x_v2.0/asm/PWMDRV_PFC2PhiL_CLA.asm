;---------------------------------------------------------------------------------
;	FILE:			PWMDRV_PFC2PhiL.asm
;
;	Description:	PWM driver for 2 phase interleaved Power Factor Correction stage
;
;	Version: 		2.0
;
;   Target:  		F2802x / F2803x
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;  06/15/10	| Release 2.0  		(MB)
;--------------------------------------------------------------------------------
;=============================
PWMDRV_PFC2PhiL_CLA_INIT	.macro	n
;=============================
; variable Declarations
_PWMDRV_PFC2PhiL_CLA_Duty:n:	.usect "PWMDRV_PFC2PhiL_CLA_Section",2,1,1	; Input Terminal 1, Duty
_PWMDRV_PFC2PhiL_CLA_Adj:n: 	.usect "PWMDRV_PFC2PhiL_CLA_Section",2,1,1  ; Input Terminal 2, Adj

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_PFC2PhiL_CLA_Duty:n:
		.def 	_PWMDRV_PFC2PhiL_CLA_Adj:n:

		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNetCLA
			MOVW	DP, #_PWMDRV_PFC2PhiL_CLA_Duty:n:
			MOVL	@_PWMDRV_PFC2PhiL_CLA_Duty:n:, XAR2
			MOVL	@_PWMDRV_PFC2PhiL_CLA_Adj:n:, XAR2
		
		.endm
;--------------------------------------------------------------------------------
;======================
PWMDRV_PFC2PhiL_CLA			.macro	n
;======================

_PWMDRV_PFC2PhiL_CLA_Start:n:

		; MAR0  =  Pointer to PFC2PHIL_ONECH_Duty
        ; MR0   =  ePWM Period, Converted from Q15 to float
        ;          + 2 cycle delay for MAR0 load    
		MMOV16 	MAR0, @_PWMDRV_PFC2PhiL_CLA_Duty:n:
		MMOV16  MAR1, @_PWMDRV_PFC2PhiL_CLA_Adj:n:
		MUI16TOF32	MR0, @_EPwm:n:Regs.TBPRD
		MNOP

		; MR1   = PFC@PHIL_ONECH_Duty in Q24, convert to float and scale it
		MUI32TOF32  MR1,*MAR0
		MMPYF32     MR1, MR1,  #1.0L/16777216.00L   

		; Update CMPA
		; MR2   = Multiply OneCh_Duty scaled{MR1} x TBPRD {MR0} 
		MMPYF32     MR2, MR1, MR0
        MF32TOUI16  MR2, MR2
        MMOV16      @_EPwm:n:Regs.CMPA.half.CMPA, MR2

		;Update CMPB
		; MR3   = PFC@PHIL_ONECHAdj in Q24, convert to float and scale it
		MUI32TOF32  MR3,*MAR1
		MMPYF32     MR3, MR3,  #1.0L/16777216.00L 
			
		MSUBF32     MR2,#1.0L,MR1 ; (1-CMPA{MR1})
		MSUBF32     MR2,MR2,MR3   ; (1-CMPA{MR1}-Adj{MR3})
		MMPYF32     MR2, MR2, MR0  ; (1-CMPA{MR1}-Adj{MR3}) * TBPRD{MR0}
		MF32TOUI16   MR2, MR2
		MMOV16      @_EPwm:n:Regs.CMPB, MR2
	   	 
_PWMDRV_PFC2PhiL_CLA_End:n:
	   	
		.endm


