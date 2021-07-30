;----------------------------------------------------------------------------------
;	FILE:			PWMDRV_1chHiRes.inc
;
;	Description:	Single (A output) channel PWM driver macro with HiRes
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
;  06/15/10	| Release 2.0  		(MB)
;--------------------------------------------------------------------------------
;=============================
PWMDRV_1chHiRes_INIT	.macro	n
;=============================
; variable declarations
_PWMDRV_1chHiRes_In:n:		.usect "PWMDRV_1chHiRes_Section",2,1,1	; input terminal
_PWMDRV_1chHiRes_Period:n:	.usect "PWMDRV_1chHiRes_Section",2,1,1	; internal data to store PWM period value

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_1chHiRes_In:n:
		.def 	_PWMDRV_1chHiRes_Period:n:
				
; set terminal pointer to ZeroNet
		MOVL	XAR2, #ZeroNet
		MOVW	DP, #_PWMDRV_1chHiRes_In:n:
		MOVL	@_PWMDRV_1chHiRes_In:n:, XAR2
		MOVW	DP,#_EPwm:n:Regs.TBPRD
		MOVL	ACC,@_EPwm:n:Regs.TBPRD
		MOV		AL,#0
		MOVW	DP, #_PWMDRV_1chHiRes_In:n:
		MOVL	@_PWMDRV_1chHiRes_Period:n:,ACC 

		.endm

;-------------------------------------------------------------------------------------------
;=============================
PWMDRV_1chHiRes	.macro	n
;=============================

	   MOVW 	DP, #_PWMDRV_1chHiRes_In:n:                ; load DP for net pointer
       MOVL   	XAR0, @_PWMDRV_1chHiRes_In:n:              ; Load net pointer address to XAR0
       MOVL    	XT,@_PWMDRV_1chHiRes_Period:n:
       MOVW 	DP,#_EPwm:n:Regs.CMPA
       QMPYL 	ACC,XT,*XAR0        	 			  		; ACC= (I8Q24) * (I16Q16) = (I24Q40): upper 32-bits -> ACC = (I24Q8)                         	
       LSL		ACC,#8							  			; align the cmpa value in the upper 32 bits, for 32 bit write 
       MOVL		@_EPwm:n:Regs.CMPA,ACC
	   ROR      ACC
	   MOV	    @_EPwm:n:Regs.CMPB,AH
		
	   .endm

; end of file

