;----------------------------------------------------------------------------------
;	FILE:			PWMDRV_1ch.asm
;
;	Description:	Single (A output) channel PWM driver macro
;
;	Version: 		2.0
;
;   Target:  		F28M35x
;
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;
;--------------------------------------------------------------------------------
;=============================
PWMDRV_1ch_INIT	.macro	n
;=============================
; variable declarations
_PWMDRV_1ch_Duty:n:		.usect "PWMDRV_1ch_Section",2,1,1	; input terminal

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_1ch_Duty:n:
				
; set terminal pointer to ZeroNet
		MOVL	XAR2, #ZeroNet
		MOVW	DP, #_PWMDRV_1ch_Duty:n:
		MOVL	@_PWMDRV_1ch_Duty:n:, XAR2

		.endm

;-------------------------------------------------------------------------------------------
;=============================
PWMDRV_1ch	.macro	n
;=============================
	
			MOVW 	DP, #_PWMDRV_1ch_Duty:n:       ; load DP for net pointer
       		MOVL   	XAR0, @_PWMDRV_1ch_Duty:n:     ; Load net pointer address to XAR0 
       		
       		MOVW	DP,#_EPwm:n:Regs.TBPRD
       		UI16TOF32  R0H,  @_EPwm:n:Regs.TBPRD
       		MOVF32	R2H,0.5
       		
       		MOV32	R1H,*XAR0
       		MPYF32	R0H,R0H,R1H
       		NOP
       		
       		F32TOUI16 R1H,R0H
			MPYF32	R0H,R0H,R2H
       						
       		MOV16     @_EPwm:n:Regs.CMPA.half.CMPA,R1H	; CMPA = Duty * Period
			F32TOUI16	R1H,R0H
			MOV16	  @_EPwm:n:Regs.CMPB,R1H			; CMPB = Duty * Period 
			  
	   .endm

; end of file

