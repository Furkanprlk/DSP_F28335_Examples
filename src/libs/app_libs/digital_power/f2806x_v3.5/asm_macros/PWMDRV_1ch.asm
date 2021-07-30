;----------------------------------------------------------------------------------
;	FILE:			PWMDRV_1ch.asm
;
;	Description:	Single (A output) channel PWM driver macro
;
;	Version: 		3.0
;
;   Target:  		F2802x / F2803x / F2806x
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
PWMDRV_1ch_INIT	.macro	n
;=============================
; variable declarations
_PWMDRV_1ch_Duty:n:		.usect "PWMDRV_1ch_Section",2,1,1	; input terminal
_PWMDRV_1ch_Period:n:	.usect "PWMDRV_1ch_Section",2,1,1	; internal data to store PWM period value

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_1ch_Duty:n:
		.def 	_PWMDRV_1ch_Period:n:
				
; set terminal pointer to ZeroNet
		MOVL	XAR2, #ZeroNet
		MOVW	DP, #_PWMDRV_1ch_Duty:n:
		MOVL	@_PWMDRV_1ch_Duty:n:, XAR2
		MOVW	DP,#_EPwm:n:Regs.TBPRD
		MOVL	ACC,@_EPwm:n:Regs.TBPRD
		MOV		AL,#0
		MOVW	DP, #_PWMDRV_1ch_Duty:n:
		MOVL	@_PWMDRV_1ch_Period:n:,ACC 

		.endm

;-------------------------------------------------------------------------------------------
;=============================
PWMDRV_1ch	.macro	n
;=============================
	   MOVW 	DP, #_PWMDRV_1ch_Duty:n:                ; load DP for net pointer
       MOVL   	XAR0, @_PWMDRV_1ch_Duty:n:              ; Load net pointer address to XAR0
       MOVL    	XT,@_PWMDRV_1ch_Period:n:
       MOVW 	DP,#_EPwm:n:Regs.CMPA
       QMPYL 	ACC,XT,*XAR0        	 			  ; ACC= (I8Q24) * (I16Q16) = (I24Q40): upper 32-bits -> ACC = (I24Q8)                         	
       SFR		ACC,#8							  	  ; ACC>>8: AL = duty,  
      
       MOV     @_EPwm:n:Regs.CMPA.half.CMPA,AL
       ROR     ACC									  ;AL=duty/2
	   MOV	   @_EPwm:n:Regs.CMPB,AL
		
	   .endm

; end of file

