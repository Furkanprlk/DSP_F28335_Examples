;----------------------------------------------------------------------------------
;	FILE:			PWMDRV_1ch_UpCntDB_Compl.asm
;
;	Description:	Single (A output) channel complementary PWM driver macro
;
;	Version: 		2.0
;
;   Target:  		F2802x / F2803x
;
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;  05/15/11	| Release 1.0  		(DC)
;--------------------------------------------------------------------------------
;=============================
PWMDRV_LLC_1ch_UpCntDB_Compl_INIT	.macro	n
;=============================
; variable declarations
_PWMDRV_LLC_1ch_UpCntDB_Compl_Duty:n:	.usect "PWMDRV_LLC_1ch_UpCntDB_Compl_Section",2,1,1	; input terminal
_PWMDRV_LLC_1ch_UpCntDB_Compl_Period:n:	.usect "PWMDRV_LLC_1ch_UpCntDB_Compl_Section",2,1,1	; internal data to store PWM period value
_PWMDRV_LLC_1ch_UpCntDB_Compl_DeadBandRED:n:	.usect "PWMDRV_LLC_1ch_UpCntDB_Compl_Section",1,1,1	; internal data to store PWM deadband value 
_PWMDRV_LLC_1ch_UpCntDB_Compl_DeadBandFED:n:	.usect "PWMDRV_LLC_1ch_UpCntDB_Compl_Section",1,1,1	; internal data to store PWM deadband value 

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_LLC_1ch_UpCntDB_Compl_Duty:n:
		.def 	_PWMDRV_LLC_1ch_UpCntDB_Compl_Period:n:
		.def 	_PWMDRV_LLC_1ch_UpCntDB_Compl_DeadBandRED:n:
		.def 	_PWMDRV_LLC_1ch_UpCntDB_Compl_DeadBandFED:n:
				
; set terminal pointer to ZeroNet
		MOVL	XAR2, #ZeroNet
		MOVW	DP, #_PWMDRV_LLC_1ch_UpCntDB_Compl_Duty:n:
		MOVL	@_PWMDRV_LLC_1ch_UpCntDB_Compl_Duty:n:, XAR2
		MOVL	@_PWMDRV_LLC_1ch_UpCntDB_Compl_Period:n:, XAR2
		MOV	@_PWMDRV_LLC_1ch_UpCntDB_Compl_DeadBandRED:n:,#0
		MOV	@_PWMDRV_LLC_1ch_UpCntDB_Compl_DeadBandFED:n:,#0

		.endm

;-------------------------------------------------------------------------------------------
;=============================
PWMDRV_LLC_1ch_UpCntDB_Compl	.macro	n
;=============================
		MOVW	DP, #_PWMDRV_LLC_1ch_UpCntDB_Compl_Duty:n:		; load DP for net pointer
		MOVL	XAR0, @_PWMDRV_LLC_1ch_UpCntDB_Compl_Duty:n:		; Load net pointer address to XAR0
		MOVL	XAR1, @_PWMDRV_LLC_1ch_UpCntDB_Compl_Period:n:	; Load net pointer address to XAR1

		MOVL	ACC, *XAR1
		SFR		ACC, #14								; ACC>>14: AL = Period (Q10)
		MOVW	DP, #_EPwm:n:Regs.TBPRD
		MOV		@_EPwm:n:Regs.TBPRD, AL					; Update period register

		MOVL	XT, @_EPwm:n:Regs.TBPRD
		QMPYL	ACC, XT, *XAR0							; ACC = (I16Q16) * (I8Q24) = (I24Q40): upper 32-bits -> ACC = (I24Q8)                         	
		SFR		ACC, #8									; ACC>>8: AL = Duty*Period (Q16)
		SUB		@T, AL									; T = Period - Duty*Period
		
		MOVW	DP, #_EPwm:n:Regs.CMPA
		MOV     @_EPwm:n:Regs.CMPA.half.CMPA, T			; Update CMPA
		
		ROR     ACC										; AL = Duty*Period/2
		SUB		ACC, #13								; compensate for 1st sample bug
		ADD		@T, AL

		MOVW	DP, #_EPwm:n:Regs.CMPB
		MOV		@_EPwm:n:Regs.CMPB, T					; Update CMPB = Duty midpoint
		
		MOVL	ACC, *XAR1
		SFR		ACC, #14								; ACC>>14: AL = Period (Q10)
		MOVW	DP, #_EPwm:n:Regs.DBFED					
		SUB		AL, @_EPwm:n:Regs.DBFED					; use FED value to create Falling Edge Margin (advance falling edge)
		MOVW	DP, #_EPwm:n:Regs.TBPRD
		MOV		@_EPwm:n:Regs.TBPRD, AL					; Update period register (with FEM)

	   .endm

;-------------------------------------------------------------------------------------------
;=============================
PWMDRV_LLC_1ch_UpCntDB_Compl_UpdateDB	.macro	n
;=============================
		MOVW	DP, #_PWMDRV_LLC_1ch_UpCntDB_Compl_Duty:n:		; load DP for net pointer
		MOVL	XAR0, @_PWMDRV_LLC_1ch_UpCntDB_Compl_DeadBandRED:n:
		MOV	ACC,  @_PWMDRV_LLC_1ch_UpCntDB_Compl_DeadBandFED:n:
       
		MOVW	DP,#_EPwm:n:Regs.DBRED
		MOV	@_EPwm:n:Regs.DBRED, AR0	
		MOV	@_EPwm:n:Regs.DBFED, AL
		
	   .endm

; end of file
