;---------------------------------------------------------------------------------
;	FILE:			PWMDRV_PSFB_CLA.asm
;
;	Description:	PWM driver for PSFB 
;
;	Version: 		3.0
;
;   Target:  		CLA Type 0
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;  	| Release 3.0  (MB)
;--------------------------------------------------------------------------------
;======================
PWMDRV_PSFB_CLA_INIT	.macro	n
;======================
; variable Declarations
_PWMDRV_PSFB_CLA_Phase:n:	.usect "PWMDRV_PSFB_CLA_Section",2,1,1	; Input Terminal 1, Phase
_PWMDRV_PSFB_CLA_DbLeft:n: 	.usect "PWMDRV_PSFB_CLA_Section",2,1,1 ; Input Terminal 2, DbLeft
_PWMDRV_PSFB_CLA_DbRight:n: .usect "PWMDRV_PSFB_CLA_Section",2,1,1 ; Input Terminal 3, DbRight

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_PSFB_CLA_Phase:n: 
		.def 	_PWMDRV_PSFB_CLA_DbLeft:n:
		.def 	_PWMDRV_PSFB_CLA_DbRight:n:
		
		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNetCLA
			MOVW	DP, #_PWMDRV_PSFB_CLA_Phase:n:
			MOVL	@_PWMDRV_PSFB_CLA_Phase:n:, XAR2
			MOVL	@_PWMDRV_PSFB_CLA_DbLeft:n:, XAR2
			MOVL	@_PWMDRV_PSFB_CLA_DbRight:n:, XAR2
		
		.endm
;--------------------------------------------------------------------------------
;======================
PWMDRV_PSFB_CLA			.macro	n,m
;======================
		
_PWMDRV_PSFB_CLA_Start:n:

		MMOV16 		MAR0, @_PWMDRV_PSFB_CLA_Phase:n:	; Net pointer for phase (MAR0)
		MUI16TOF32	MR0,  @_EPwm:n:Regs.TBPRD 			; Load value of the time base period register in the MR0 and convert it to 32 bit
		MMOV16 		MAR1, @_PWMDRV_PSFB_CLA_DbRight:n:	; Net pointer for dbRight (MAR0)
		MNOP

		; Phase Adjustment between Left and Right Legs
		MMOV32  	MR1,  *MAR0							;Load the phase input value into MR1 and convert it to float
		MMOV16  	MAR0, @_PWMDRV_PSFB_CLA_DbLeft:n:	; Net pointer for dbLeft (MAR0)			
		MMPYF32  	MR1,  MR1,  #0.5					; Note the input is scaled by 1/2 to calculate (input*Period/2) as maximum phase shift is Period/2
		MMPYF32	   	MR0,MR0,MR1							;multiply the time pase perios value with phase input value
		MF32TOUI16	MR0,MR0								; convert the multipled value to U16
		
		; Deadband Adjustment for Right leg ePWM Module(module EPWM(m) )
		MUI32TOF32 MR2, *MAR1
		MF32TOUI16 MR2,MR2
		
		; Deadband Adjustment for Left leg ePWM module(module EPWMn)
		MUI32TOF32	MR3,*MAR0
		MF32TOUI16 MR3,MR3
		
		MEALLOW
		MMOV16     @_EPwm:m:Regs.TBPHS.half.TBPHS, MR0	; store this value in the TBPHS register
		MMOV16	   @_EPwm:m:Regs.DBRED,MR2
		MMOV16     @_EPwm:m:Regs.DBFED,MR2
		MMOV16		@_EPwm:n:Regs.DBRED,MR3
		MMOV16		@_EPwm:n:Regs.DBFED,MR3	
		MEDIS
	   	 
_PWMDRV_PSFB_CLA_End:n:
	   	
		.endm


