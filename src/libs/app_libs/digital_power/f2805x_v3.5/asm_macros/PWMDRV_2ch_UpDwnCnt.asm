;----------------------------------------------------------------------------------
;	FILE:			PWMDRV_2ch_UpDwnCnt.asm
;
;	Description:	Two channel PWM driver macro with HR duty.
;					Output is centered around CTR=PRD.
;
;	Version: 		
;
;   Target:  		F2802x / F2803x / F2806x/ F2805x
;
;--------------------------------------------------------------------------------
;   Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
;   ALL RIGHTS RESERVED
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;--------------------------------------------------------------------------------
;============================================
PWMDRV_2ch_UpDwnCnt_INIT	.macro	n
;============================================
; variable declarations
_PWMDRV_2ch_UpDwnCnt_Duty:n:			.usect "PWMDRV_2ch_UpDwnCnt_Section",2,1,1	; input terminal for PWM duty
;_PWMDRV_LLC_2ch_UpDwnCnt_Period:n:			.usect "PWMDRV_LLC_2ch_UpDwnCnt_Section",2,1,1	; input terminal for PWM period
;_PWMDRV_LLC_2ch_UpDwnCnt_Phase:n:			.usect "PWMDRV_LLC_2ch_UpDwnCnt_Section",2,1,1	; input terminal for PWM phase
;_PWMDRV_LLC_2ch_UpDwnCnt_DeadBandRED:n:		.usect "PWMDRV_LLC_2ch_UpDwnCnt_Section",1,1,1	; internal data to store PWM RE deadband value 
;_PWMDRV_LLC_2ch_UpDwnCnt_DeadBandFED:n:		.usect "PWMDRV_LLC_2ch_UpDwnCnt_Section",1,1,1	; internal data to store PWM FE deadband value

; Publish Terminal Pointers for access from the C environment
;============================================================
		.def	_PWMDRV_2ch_UpDwnCnt_Duty:n:
;		.def	_PWMDRV_LLC_2ch_UpDwnCnt_Period:n:
;		.def	_PWMDRV_LLC_2ch_UpDwnCnt_Phase:n:
;		.def	_PWMDRV_LLC_2ch_UpDwnCnt_DeadBandRED:n:
;		.def	_PWMDRV_LLC_2ch_UpDwnCnt_DeadBandFED:n:
				
; set terminal pointer to ZeroNet
		MOVL	XAR2, #ZeroNet
		MOVW	DP, #_PWMDRV_2ch_UpDwnCnt_Duty:n:
		MOVL	@_PWMDRV_2ch_UpDwnCnt_Duty:n:, XAR2
;		MOVL	@_PWMDRV_LLC_2ch_UpDwnCnt_Period:n:, XAR2
;		MOVL	@_PWMDRV_LLC_2ch_UpDwnCnt_Phase:n:, XAR2
	;	MOV 	@_PWMDRV_LLC_2ch_UpDwnCnt_DeadBandRED:n:,#0
	;	MOV 	@_PWMDRV_LLC_2ch_UpDwnCnt_DeadBandFED:n:,#0

		.endm

;-------------------------------------------------------------------------------------------
;========================================
PWMDRV_2ch_UpDwnCnt	.macro	n
;========================================
		MOVW	DP, #_PWMDRV_2ch_UpDwnCnt_Duty:n:		; load DP for net pointer
		MOVL	XAR0, @_PWMDRV_2ch_UpDwnCnt_Duty:n:		; load net pointer address to XAR0
;		MOVL	XAR1, @_PWMDRV_LLC_2ch_UpDwnCnt_Period:n:	; load net pointer address to XAR1
;		MOVL	XAR2, @_PWMDRV_LLC_2ch_UpDwnCnt_Phase:n:	; load net pointer address to XAR2

;		MOVL	ACC, *XAR2								; ACC = Phase 8(24)
;		LSL 	ACC, #8									; align value in upper 24 bits. (24)8
;		MOVW	DP, #_EPwm:n:Regs.TBPHS
;		MOV 	@_EPwm:n:Regs.TBPHS, AH					; update TBPHS register

;		MOVL	ACC, *XAR1								; ACC = Period 8(24)
;		LSL 	ACC, #7									; align value in upper 24 bits.  only shift by 7 to achieve Period/2 for Up-Down count (24)8
;		MOVW	DP, #_EPwm:n:Regs.TBPRD
;		MOV 	@_EPwm:n:Regs.TBPRD, AH					; update TBPRD register

		; update channel A
		MOVW	DP, #_EPwm:n:Regs.TBPRD
		MOVL 	XT, @_EPwm:n:Regs.TBPRD					; load TBPRD register

		QMPYL	ACC, XT, *XAR0							; ACC = Period*Duty, ACC = 16(16) * 8(24) = 24(40): upper 32-bits -> ACC = 24(8)
		LSL 	ACC, #8									; align the value in the upper 24 bits, ACC = Period*Duty (24)8

	;	MOVW	DP, #_EPwm:n:Regs.DBRED
	;	SUB 	ACC, @_EPwm:n:Regs.DBRED << #15			; use RED value to create dead-band by adjusting CMPA value. 
														; only shift by 15 to achieve RED/2 for symmetric dead-band
		SUBL	@XT, ACC								; XT = Period - (Period*Duty-RED/2) (24)8

		MOVW	DP, #_EPwm:n:Regs.CMPA
		MOV 	@_EPwm:n:Regs.CMPA.half.CMPA, T			; update CMPA register

		; update channel B
		MOVW	DP, #_EPwm:n:Regs.TBPRD
		MOVL	XT, @_EPwm:n:Regs.TBPRD					; load TBPRD register

		QMPYL	ACC, XT, *XAR0							; ACC = Period*Duty, ACC = (24)8 * 8(24) = 8(48)8: upper 32-bits -> ACC = 8(24)
		LSL 	ACC, #8									; align the value in the upper 24 bits, ACC = Period*Duty (24)8

	;	MOVW	DP, #_EPwm:n:Regs.DBFED
	;	SUB 	ACC, @_EPwm:n:Regs.DBFED << #15			; use FED value to create dead-band by adjusting CMPB value. 
														; only shift by 15 to achieve FED/2 for symmetric dead-band
		MOVW	DP, #_EPwm:n:Regs.CMPB					
		MOV 	@_EPwm:n:Regs.CMPB, AH					; update CMPB register
	   .endm

;-------------------------------------------------------------------------------------------
;================================================
;PWMDRV_LLC_2ch_UpDwnCnt_UpdateDB	.macro	n
;================================================
;		MOVW	DP, #_PWMDRV_LLC_2ch_UpDwnCnt_Duty:n:			; load DP for net pointer
;		MOVL	XAR0, @_PWMDRV_LLC_2ch_UpDwnCnt_DeadBandRED:n:	; load value to XAR0
;		MOV 	ACC, @_PWMDRV_LLC_2ch_UpDwnCnt_DeadBandFED:n:	; load value to ACC
       
;		MOVW	DP,#_EPwm:n:Regs.DBRED
;		MOV 	@_EPwm:n:Regs.DBRED, AR0	
;		MOV 	@_EPwm:n:Regs.DBFED, AL
		
;	   .endm

; end of file
