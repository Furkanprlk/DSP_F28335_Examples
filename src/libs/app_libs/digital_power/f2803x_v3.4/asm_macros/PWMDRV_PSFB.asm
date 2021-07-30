;---------------------------------------------------------------------------------
;	FILE:			PWMDRV_PSFB.asm
;
;	Description:	PWM driver Phase Shifted Full Bridge 
;
;	Version: 		3.0
;
;   Target:  		F2802x / F2803x
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;  	| Release 3.0  		
;--------------------------------------------------------------------------------
;======================
PWMDRV_PSFB_INIT	.macro	n,m
;======================
; variable Declarations
_PWMDRV_PSFB_Phase:n:	.usect "PWMDRV_PSFB_Section",2,1,1	; Input Terminal 1, Phase
_PWMDRV_PSFB_DbLeft:n: 	.usect "PWMDRV_PSFB_Section",2,1,1  ; Input Terminal 2, DbLeft
_PWMDRV_PSFB_DbRight:n: .usect "PWMDRV_PSFB_Section",2,1,1  ; Input Terminal 3, DbRight

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_PSFB_Phase:n: 
		.def 	_PWMDRV_PSFB_DbLeft:n:
		.def 	_PWMDRV_PSFB_DbRight:n:

		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_PWMDRV_PSFB_Phase:n:
			MOVL	@_PWMDRV_PSFB_Phase:n:, XAR2
			MOVL	@_PWMDRV_PSFB_DbLeft:n:, XAR2
			MOVL	@_PWMDRV_PSFB_DbRight:n:, XAR2
		
		.endm
;--------------------------------------------------------------------------------
;======================
PWMDRV_PSFB		.macro	n,m
;======================

		; Phase Adjustment between Left and Right Legs
	   	MOVW 	DP, #_PWMDRV_PSFB_Phase:n:          ; load DP for net pointer
       	MOVL   	XAR0, @_PWMDRV_PSFB_Phase:n:        ; Load net pointer address to XAR0
       	MOVL    XAR1, @_PWMDRV_PSFB_DbLeft:n:
       	MOVL    XAR2, @_PWMDRV_PSFB_DbRight:n:  
       	MOVW    DP, #_EPwm:m:Regs.TBPRD           	; Load DP for EPWMPRD Register, Note use Mirror register for 32 bit read
       	MOVL    XT,@_EPwm:m:Regs.TBPRD              	; Load XT  = Duty (Q24)
		MOV 	TL,#0
       	QMPYL  	ACC,XT,*XAR0            			; ACC= (I8Q24) * (I16Q0) = (I24Q24): upper 32-bits -> P = (I24Q8)
       	LSL  	ACC,#9                          	; ACC>>8 = I32Q0
       	MOV     @_EPwm:m:Regs.TBPHS.half.TBPHS,AL
       	
       	; Deadband Adjustment for Right leg ePWM Module(module EPWM(m) )
       	MOV		AL,*XAR1
       	MOV		@_EPwm:m:Regs.DBRED, AL
       	MOV		@_EPwm:m:Regs.DBFED, AL
       	
       	; Deadband Adjustment for Left leg ePWM module(module EPWMn)
       	MOV 	AL, *XAR2
       	MOVW	DP, #_EPwm:n:Regs.DBRED
       	MOV		@_EPwm:n:Regs.DBRED, AL
       	MOV		@_EPwm:n:Regs.DBFED, AL
       	 
	   	
		.endm


