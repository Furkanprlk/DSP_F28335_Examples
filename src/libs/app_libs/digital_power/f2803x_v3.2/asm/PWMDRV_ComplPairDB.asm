;----------------------------------------------------------------------------------
;	FILE:			PWMDRV_ComplPairDB.asm
;
;	Description:	PWM Driver for complimentary pair PWM
;
;	Version: 		3.0
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
;  	| Release 3.0  		(MB)
;--------------------------------------------------------------------------------
;=============================
PWMDRV_ComplPairDB_INIT	.macro	n
;=============================
; variable declarations
_PWMDRV_ComplPairDB_Duty:n:			.usect "PWMDRV_ComplPairDB_Section",2,1,1	; input terminal
_PWMDRV_ComplPairDB_Period:n:		.usect "PWMDRV_ComplPairDB_Section",2,1,1	; internal data to store PWM period value
_PWMDRV_ComplPairDB_DeadBandRED:n:	.usect "PWMDRV_ComplPairDB_Section",1,1,1	; internal data to store PWM deadband value 
_PWMDRV_ComplPairDB_DeadBandFED:n:	.usect "PWMDRV_ComplPairDB_Section",1,1,1	; internal data to store PWM deadband value 

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_ComplPairDB_Duty:n:
		.def 	_PWMDRV_ComplPairDB_Period:n:
		.def 	_PWMDRV_ComplPairDB_DeadBandRED:n:
		.def 	_PWMDRV_ComplPairDB_DeadBandFED:n:
; set terminal pointer to ZeroNet
		MOVL	XAR2, #ZeroNet
		ZAPA
		MOVW	DP, #_PWMDRV_ComplPairDB_Duty:n:
		MOV		@_PWMDRV_ComplPairDB_DeadBandRED:n:,AL
		MOV		@_PWMDRV_ComplPairDB_DeadBandFED:n:,AL
		MOVL	@_PWMDRV_ComplPairDB_Duty:n:, XAR2
		MOVW	DP,#_EPwm:n:Regs.TBPRD
		MOVL	ACC,@_EPwm:n:Regs.TBPRD
		MOV		AL,#0
		MOVW	DP, #_PWMDRV_ComplPairDB_Duty:n:
		MOVL	@_PWMDRV_ComplPairDB_Period:n:,ACC 

		.endm

;-------------------------------------------------------------------------------------------
;=============================
PWMDRV_ComplPairDB	.macro	n
;=============================
	   MOVW 	DP, #_PWMDRV_ComplPairDB_Duty:n:                ; load DP for net pointer
       MOVL   	XAR0, @_PWMDRV_ComplPairDB_Duty:n:              ; Load net pointer address to XAR0
       MOVL    	XT,@_PWMDRV_ComplPairDB_Period:n:
       QMPYL 	ACC,XT,*XAR0        	 			  		  ; ACC= (I8Q24) * (I16Q16) = (I24Q40): upper 32-bits -> ACC = (I24Q8)                         	
       SFR		ACC,#8							  		  	  ; ACC>>8: AL = duty
       MOVW 	DP,#_EPwm:n:Regs.CMPA
       MOV     @_EPwm:n:Regs.CMPA.half.CMPA,AL
       ROR     ACC
	   MOV	   @_EPwm:n:Regs.CMPB,AL
		
	   .endm
;-------------------------------------------------------------------------------------------
;=============================
PWMDRV_ComplPairDB_UpdateDB	.macro	n
;=============================
	   MOVW 	DP, #_PWMDRV_ComplPairDB_Duty:n:                ; load DP for net pointer
       MOVL   	XAR0, @_PWMDRV_ComplPairDB_DeadBandRED:n:
	   MOV   	ACC,  @_PWMDRV_ComplPairDB_DeadBandFED:n:
       
       MOVW 	DP,#_EPwm:n:Regs.DBRED
       MOV      @_EPwm:n:Regs.DBRED, AR0
       MOV	    @_EPwm:n:Regs.DBFED, AL
		
	   .endm

; end of file

