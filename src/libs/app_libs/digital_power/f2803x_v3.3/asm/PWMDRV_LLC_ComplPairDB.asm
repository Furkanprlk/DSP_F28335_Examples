;----------------------------------------------------------------------------------
;	FILE:			PWMDRV_LLC_ComplPairDB.asm
;
;	Description:	PWM Driver for complimentary pair PWM with period modulation
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
;  05/15/10	| Release 1.0  		(DC)
;--------------------------------------------------------------------------------
;=============================
PWMDRV_LLC_ComplPairDB_INIT	.macro	n
;=============================
; variable declarations
_PWMDRV_LLC_ComplPairDB_Duty:n:			.usect "PWMDRV_LLC_ComplPairDB_Section",2,1,1	; input terminal for PWM duty percentage
_PWMDRV_LLC_ComplPairDB_Period:n:		.usect "PWMDRV_LLC_ComplPairDB_Section",2,1,1	; input terminal for PWM period value
_PWMDRV_LLC_ComplPairDB_DeadBandRED:n:	.usect "PWMDRV_LLC_ComplPairDB_Section",1,1,1	; internal data to store PWM deadband value 
_PWMDRV_LLC_ComplPairDB_DeadBandFED:n:	.usect "PWMDRV_LLC_ComplPairDB_Section",1,1,1	; internal data to store PWM deadband value 

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_LLC_ComplPairDB_Duty:n:
		.def 	_PWMDRV_LLC_ComplPairDB_Period:n:
		.def 	_PWMDRV_LLC_ComplPairDB_DeadBandRED:n:
		.def 	_PWMDRV_LLC_ComplPairDB_DeadBandFED:n:
; set terminal pointer to ZeroNet
		MOVL	XAR2, #ZeroNet
		ZAPA
		MOVW	DP, #_PWMDRV_LLC_ComplPairDB_Duty:n:
		MOVL	@_PWMDRV_LLC_ComplPairDB_Duty:n:, XAR2
		MOVL	@_PWMDRV_LLC_ComplPairDB_Period:n:, XAR2
		MOV		@_PWMDRV_LLC_ComplPairDB_DeadBandRED:n:,#0
		MOV		@_PWMDRV_LLC_ComplPairDB_DeadBandFED:n:,#0

		.endm

;-------------------------------------------------------------------------------------------
;=============================
PWMDRV_LLC_ComplPairDB	.macro	n
;=============================
		MOVW	DP, #_PWMDRV_LLC_ComplPairDB_Duty:n:		; load DP for net pointer
		MOVL	XAR0, @_PWMDRV_LLC_ComplPairDB_Duty:n:		; Load net pointer address to XAR0
		MOVL	XAR1, @_PWMDRV_LLC_ComplPairDB_Period:n:	; Load net pointer address to XAR0

		MOVL	ACC, *XAR1
		SFR		ACC, #14								; ACC>>14: AL = Period (Q10)
		MOVW	DP, #_EPwm:n:Regs.TBPRD
		MOV		@_EPwm:n:Regs.TBPRD, AL					; Update period register

		MOVL	XT, @_EPwm:n:Regs.TBPRD
		QMPYL	ACC, XT, *XAR0							; ACC = (I16Q16) * (I8Q24) = (I24Q40): upper 32-bits -> ACC = (I24Q8)                         	
		SFR		ACC, #8									; ACC>>8: AL = Duty*Period (Q16)

		MOVW	DP, #_EPwm:n:Regs.CMPA
		MOV		@_EPwm:n:Regs.CMPA.half.CMPA, AL		; Update CMPA
		ROR		ACC
		MOVW	DP, #_EPwm:n:Regs.CMPB
		MOV		@_EPwm:n:Regs.CMPB, AL					; Update CMPB = Duty cycle midpoint
		
	   .endm
;-------------------------------------------------------------------------------------------
;=============================
PWMDRV_LLC_ComplPairDB_UpdateDB	.macro	n
;=============================
	   MOVW 	DP, #_PWMDRV_LLC_ComplPairDB_Duty:n:		; load DP for net pointer
       MOVL   	XAR0, @_PWMDRV_LLC_ComplPairDB_DeadBandRED:n:
	   MOV   	ACC,  @_PWMDRV_LLC_ComplPairDB_DeadBandFED:n:
       
       MOVW 	DP,#_EPwm:n:Regs.DBRED
       MOV      @_EPwm:n:Regs.DBRED, AR0
       MOV	    @_EPwm:n:Regs.DBFED, AL
		
	   .endm

; end of file

