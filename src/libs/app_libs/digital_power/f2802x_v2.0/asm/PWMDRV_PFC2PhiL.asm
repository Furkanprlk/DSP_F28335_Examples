;---------------------------------------------------------------------------------
;	FILE:			PWMDRV_PFC2PhiL.asm
;
;	Description:	PWM driver for 2 phase interleaved Power Factor Correction stage
;
;	Version: 		2.0
;
;   Target:  		F2802x / F2803x
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;  03/13/08	| Release 1.0  		New release.
;--------------------------------------------------------------------------------
;=============================
PWMDRV_PFC2PHIL_INIT	.macro	n
;=============================
; variable Declarations
_PWMDRV_PFC2PhiL_Duty:n:	.usect "PWMDRV_PFC2PhiL_Section",2,1,1	; Input Terminal 1, Duty
_PWMDRV_PFC2PhiL_Adj:n: 	.usect "PWMDRV_PFC2PhiL_Section",2,1,1 ; Input Terminal 2
_PWMDRV_PFC2PhiL_Period:n:  .usect "PWMDRV_PFC2PhiL_Section",2,1,1

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_PFC2PhiL_Duty:n:
		.def 	_PWMDRV_PFC2PhiL_Adj:n:
		.def 	_PWMDRV_PFC2PhiL_Period:n:

		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_PWMDRV_PFC2PhiL_Duty:n:
			MOVL	@_PWMDRV_PFC2PhiL_Duty:n:, XAR2
			MOVL	@_PWMDRV_PFC2PhiL_Adj:n:, XAR2
			MOVW	DP,#_EPwm:n:Regs.TBPRD
			MOVL	ACC,@_EPwm:n:Regs.TBPRD
			MOV		AL,#0
			MOVW	DP, #_PWMDRV_PFC2PhiL_Duty:n:
			MOVL	@_PWMDRV_PFC2PhiL_Period:n:,ACC 
		
		.endm
;--------------------------------------------------------------------------------
;======================
PWMDRV_PFC2PHIL		.macro	n
;======================

			MOVW 	DP, #_PWMDRV_PFC2PhiL_Duty:n:       ; load DP for net pointer
       		MOVL   	XAR0, @_PWMDRV_PFC2PhiL_Duty:n:     ; Load net pointer address to XAR0 
       		MOVL	XAR1, @_PWMDRV_PFC2PhiL_Adj:n:		; Load net pointer address to XAR1
       		MOVL    XT, @_PWMDRV_PFC2PhiL_Period:n:		; Load XT  = Period (I16Q16)
       		QMPYL  	ACC,XT,*XAR0    					; ACC= (I8Q24) * (I16Q16) = (I24Q40): upper 32-bits = (I24Q8)
       		SFR  	ACC,#8                           	; ACC>>8: AL = Period * Duty Q0
       		MOVL	XAR2,ACC							; XAR2 = Period * Duty 
       		QMPYL	ACC,XT,*XAR1						; ACC= Adj * Period = Q24 * I16Q16 = I24Q8 
       		ASR64	ACC:P,#8							; Note ASR64 is used because we want singn to be conserved, without worrying about the SXM bit
       		ADDL	ACC,@XAR2							; ACC = Adj *Period + Duty * Period
       		SUB		@T,AL								; T = Period - Adj *Period + Duty * Period
       		MOVW    DP, #_EPwm:n:Regs.CMPA				
       		MOV     @_EPwm:n:Regs.CMPA.half.CMPA,AR2	; CMPA = Duty * Period
       		MOV		@_EPwm:n:Regs.CMPB,T				; CMPB = Period - Adj *Period + Duty * Period
			   	
		.endm


