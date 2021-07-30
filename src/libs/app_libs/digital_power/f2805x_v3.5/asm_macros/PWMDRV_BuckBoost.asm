;----------------------------------------------------------------------------------
;	FILE:			PWMDRV_BuckBoost.asm
;
;	Description:	PWM Driver for Buck Boost 
;
;	Version: 		
;
;   Target:  		F2802x / F2803x / F2806x/ F2805x
;
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments � 2010
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;--------------------------------------------------------------------------------
;=============================
PWMDRV_BuckBoost_INIT	.macro	n,m
;=============================
; variable declarations
_PWMDRV_BuckBoost_Duty:n:			.usect "PWMDRV_BuckBoost_Section",2,1,1	; input terminal
_PWMDRV_BuckBoost_Period:n:			.usect "PWMDRV_BuckBoost_Section",2,1,1	; internal data to store PWM period value

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_BuckBoost_Duty:n:
		.def 	_PWMDRV_BuckBoost_Period:n:

; set terminal pointer to ZeroNet
		MOVL	XAR2, #ZeroNet
		ZAPA
		MOVW	DP, #_PWMDRV_BuckBoost_Duty:n:
		MOVL	@_PWMDRV_BuckBoost_Duty:n:, XAR2
		MOVW	DP,#_EPwm:n:Regs.TBPRD
		MOVL	ACC,@_EPwm:n:Regs.TBPRD
		MOV		AL,#0
		MOVW	DP, #_PWMDRV_BuckBoost_Duty:n:
		MOVL	@_PWMDRV_BuckBoost_Period:n:,ACC 

		.endm

;-------------------------------------------------------------------------------------------
;=============================
PWMDRV_BuckBoost	.macro	n,m
;=============================
	   MOVW 	DP, #_PWMDRV_BuckBoost_Duty:n:                ; load DP for net pointer
       MOVL   	XAR0, @_PWMDRV_BuckBoost_Duty:n:              ; Load net pointer address to XAR0
       MOVL    	XT,@_PWMDRV_BuckBoost_Period:n:
       QMPYL 	ACC,XT,*XAR0        	 			  		  ; ACC= (I8Q24) * (I16Q16) = (I24Q40): upper 32-bits -> ACC = (I24Q8)                         	
       SFR		ACC,#8							  		  	  ; ACC>>8: AL = duty
       MOVW 	DP,#_EPwm:n:Regs.CMPA
       MOV     @_EPwm:n:Regs.CMPA.half.CMPA,AL
       MOVW 	DP,#_EPwm:m:Regs.CMPA
	   MOV     @_EPwm:m:Regs.CMPA.half.CMPA,AL
	   MOVW 	DP,#_EPwm:n:Regs.CMPA
	   ROR     ACC
	   MOV	   @_EPwm:n:Regs.CMPB,AL
	   
	   .endm
;-------------------------------------------------------------------------------------------
; end of file

