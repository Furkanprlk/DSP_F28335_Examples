;----------------------------------------------------------------------------------
;	FILE:			PWMDRV_1chHiResUpDwnCnt.asm
;
;	Description:	Single (A output) channel PWM driver macro with HiRes
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
;=============================
PWMDRV_1chHiResUpDwnCnt_INIT	.macro	n
;=============================
; variable declarations
_PWMDRV_1chHiResUpDwnCnt_Duty:n:		.usect "PWMDRV_1chHiResUpDwnCnt_Section",2,1,1	; input terminal
_PWMDRV_1chHiResUpDwnCnt_Period:n:		.usect "PWMDRV_1chHiResUpDwnCnt_Section",2,1,1	; internal data to store PWM period value

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_1chHiResUpDwnCnt_Duty:n:
		.def 	_PWMDRV_1chHiResUpDwnCnt_Period:n:
				
; set terminal pointer to ZeroNet
		MOVL	XAR2, #ZeroNet
		MOVW	DP, #_PWMDRV_1chHiResUpDwnCnt_Duty:n:
		MOVL	@_PWMDRV_1chHiResUpDwnCnt_Duty:n:, XAR2

		MOVW	DP,#_EPwm:n:Regs.TBPRD
		MOVL	ACC,@_EPwm:n:Regs.TBPRD
		MOV		AL,#0
		MOVW	DP, #_PWMDRV_1chHiResUpDwnCnt_Duty:n:
		MOVL	@_PWMDRV_1chHiResUpDwnCnt_Period:n:,ACC

		.endm

;-------------------------------------------------------------------------------------------
;=============================
PWMDRV_1chHiResUpDwnCnt	.macro	n
;=============================

	   MOVW 	DP, #_PWMDRV_1chHiResUpDwnCnt_Duty:n:                ; load DP for net pointer
       MOVL   	XAR0, @_PWMDRV_1chHiResUpDwnCnt_Duty:n:              ; Load net pointer address to XAR0
       MOVL    	XT,@_PWMDRV_1chHiResUpDwnCnt_Period:n:
       MOVW 	DP,#_EPwm:n:Regs.CMPA
       QMPYL 	ACC,XT,*XAR0        	 			  		; ACC= (I8Q24) * (I16Q16) = (I24Q40): upper 32-bits -> ACC = (I24Q8)                         	
       LSL		ACC,#8							  			; align the cmpa value in the upper 32 bits, for 32 bit write 
       MOVL		@_EPwm:n:Regs.CMPA,ACC

		
	   .endm

; end of file

