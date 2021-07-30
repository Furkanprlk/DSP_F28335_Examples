;----------------------------------------------------------------------------------
;	FILE:			PWMDRV_LLC_1ch_UpCntDB.asm
;
;	Description:	Single (A output) channel PWM driver macro with period modulation and edge shifting
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
PWMDRV_LLC_1ch_UpCntDB_INIT	.macro	n
;=============================
; variable declarations
_PWMDRV_LLC_1ch_UpCntDB_Duty:n:		.usect "PWMDRV_LLC_1ch_UpCntDB_Section",2,1,1	; input terminal
_PWMDRV_LLC_1ch_UpCntDB_Period:n:	.usect "PWMDRV_LLC_1ch_UpCntDB_Section",2,1,1	; input terminal
_PWMDRV_LLC_1ch_UpCntDB_DeadBandRED:n:	.usect "PWMDRV_LLC_1ch_UpCntDB_Section",1,1,1	; internal data to store PWM deadband value 
_PWMDRV_LLC_1ch_UpCntDB_DeadBandFED:n:	.usect "PWMDRV_LLC_1ch_UpCntDB_Section",1,1,1	; internal data to store PWM deadband value 

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_LLC_1ch_UpCntDB_Duty:n:
		.def 	_PWMDRV_LLC_1ch_UpCntDB_Period:n:
		.def 	_PWMDRV_LLC_1ch_UpCntDB_DeadBandRED:n:
		.def 	_PWMDRV_LLC_1ch_UpCntDB_DeadBandFED:n:
				
; set terminal pointer to ZeroNet
		MOVL	XAR2, #ZeroNet
		MOVW	DP, #_PWMDRV_LLC_1ch_UpCntDB_Duty:n:
		MOVL	@_PWMDRV_LLC_1ch_UpCntDB_Duty:n:, XAR2
		MOVL	@_PWMDRV_LLC_1ch_UpCntDB_Period:n:, XAR2
		MOV	@_PWMDRV_LLC_1ch_UpCntDB_DeadBandRED:n:,#0
		MOV	@_PWMDRV_LLC_1ch_UpCntDB_DeadBandFED:n:,#0

		.endm

;-------------------------------------------------------------------------------------------
;=============================
PWMDRV_LLC_1ch_UpCntDB	.macro	n
;=============================
		MOVW	DP, #_PWMDRV_LLC_1ch_UpCntDB_Duty:n:				; load DP for net pointer
		MOVL	XAR0, @_PWMDRV_LLC_1ch_UpCntDB_Duty:n:			; Load net pointer address to XAR0
		MOVL	XAR1, @_PWMDRV_LLC_1ch_UpCntDB_Period:n:			; Load net pointer address to XAR1

		MOVL	ACC, *XAR1
		SFR		ACC, #14								; ACC>>14: AL = Period  (Q10)
		MOVW	DP, #_EPwm:n:Regs.TBPRD
		MOV		@_EPwm:n:Regs.TBPRD, AL					; Update period register

		MOVL	XT, @_EPwm:n:Regs.TBPRD
		QMPYL	ACC, XT, *XAR0							; ACC = (I16Q16) * (I8Q24) = (I24Q40): upper 32-bits -> ACC = (I24Q8)                         	
		SFR		ACC, #8									; ACC>>8: AL = Duty*Period (Q16)

		MOVW	DP, #_EPwm:n:Regs.DBFED
		SUB		ACC, @_EPwm:n:Regs.DBFED				; use FED value to create Falling Edge Margin (advance falling edge)
		
		MOVW	DP, #_EPwm:n:Regs.CMPA					; Update CMPA (with FEM)
		MOV     @_EPwm:n:Regs.CMPA.half.CMPA, AL

;		MOVW	DP, #_EPwm:n:Regs.DBFED
;		ADD		ACC, @_EPwm:n:Regs.DBFED				; undo FEM
		ROR     ACC										; AL = Duty*Period/2
		SUB		ACC, #13								; compensate for 1st sample bug
		MOVW	DP, #_EPwm:n:Regs.CMPB
		MOV		@_EPwm:n:Regs.CMPB, AL					; Update CMPB = Duty (with FEM) cycle midpoint
		
	   .endm

;-------------------------------------------------------------------------------------------
;=============================
PWMDRV_LLC_1ch_UpCntDB_UpdateDB	.macro	n
;=============================
		MOVW	DP, #_PWMDRV_LLC_1ch_UpCntDB_Duty:n:		; load DP for net pointer
		MOVL	XAR0, @_PWMDRV_LLC_1ch_UpCntDB_DeadBandRED:n:
		MOV	ACC,  @_PWMDRV_LLC_1ch_UpCntDB_DeadBandFED:n:
       
		MOVW	DP,#_EPwm:n:Regs.DBRED
		MOV	@_EPwm:n:Regs.DBRED, AR0	
		MOV	@_EPwm:n:Regs.DBFED, AL
		
	   .endm

; end of file
