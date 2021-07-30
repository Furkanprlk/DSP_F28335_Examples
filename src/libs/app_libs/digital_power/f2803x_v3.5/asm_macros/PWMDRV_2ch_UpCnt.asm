;----------------------------------------------------------------------------------
;	FILE:			PWMDRV_2ch_UpCnt.asm
;
;	Description:	Two independent channel (A&B output) PWM driver macro
;
;	Version: 		1.0
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
;  	| Release 1.0  		(DC)
;--------------------------------------------------------------------------------
;================================
PWMDRV_2ch_UpCnt_INIT	.macro	n
;================================
; variable declarations
_PWMDRV_2ch_UpCnt_Duty:n:A		.usect "PWMDRV_2ch_UpCnt_Section",2,1,1	; input terminal
_PWMDRV_2ch_UpCnt_Duty:n:B		.usect "PWMDRV_2ch_UpCnt_Section",2,1,1	; input terminal
_PWMDRV_2ch_UpCnt_Period:n:		.usect "PWMDRV_2ch_UpCnt_Section",2,1,1	; internal data to store PWM period value

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_2ch_UpCnt_Duty:n:A
		.def 	_PWMDRV_2ch_UpCnt_Duty:n:B
		.def 	_PWMDRV_2ch_UpCnt_Period:n:
				
; set terminal pointer to ZeroNet
		MOVL	XAR2, #ZeroNet
		MOVW	DP, #_PWMDRV_2ch_UpCnt_Duty:n:A
		MOVL	@_PWMDRV_2ch_UpCnt_Duty:n:A, XAR2
		MOVL	@_PWMDRV_2ch_UpCnt_Duty:n:B, XAR2
		MOVW	DP,#_EPwm:n:Regs.TBPRD
		MOVL	ACC,@_EPwm:n:Regs.TBPRD
		MOV		AL,#0
		MOVW	DP, #_PWMDRV_2ch_UpCnt_Duty:n:A
		MOVL	@_PWMDRV_2ch_UpCnt_Period:n:,ACC 

		.endm

;-------------------------------------------------------------------------------------------
;============================
PWMDRV_2ch_UpCnt	.macro	n
;============================
	   MOVW 	DP, #_PWMDRV_2ch_UpCnt_Duty:n:A                ; load DP for net pointer
       MOVL   	XAR0, @_PWMDRV_2ch_UpCnt_Duty:n:A              ; Load net pointer address to XAR0
       MOVL   	XAR1, @_PWMDRV_2ch_UpCnt_Duty:n:B              ; Load net pointer address to XAR1
       MOVL    	XT,@_PWMDRV_2ch_UpCnt_Period:n:
       MOVW 	DP,#_EPwm:n:Regs.CMPA

       QMPYL 	ACC,XT,*XAR0        	 			  ; ACC= (I8Q24) * (I16Q16) = (I24Q40): upper 32-bits -> ACC = (I24Q8)                         	
       SFR		ACC,#8							  	  ; ACC>>8: AL = duty,  
       MOV     @_EPwm:n:Regs.CMPA.half.CMPA,AL

       QMPYL 	ACC,XT,*XAR1        	 			  ; ACC= (I8Q24) * (I16Q16) = (I24Q40): upper 32-bits -> ACC = (I24Q8)                         	
       SFR		ACC,#8							  	  ; ACC>>8: AL = duty,  
	   MOV	   @_EPwm:n:Regs.CMPB,AL
	   
	   .endm

; end of file

