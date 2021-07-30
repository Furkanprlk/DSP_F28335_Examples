;---------------------------------------------------------------------------------
;	FILE:			PWMDRV_1ch_UpDwnCnt.asm
;
;	Description:	PWMDRV_1ch_UpDwnCnt
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
;=============================
PWMDRV_1ch_UpDwnCntCompl_INIT	.macro	n
;=============================
; variable Declarations
_PWMDRV_1ch_UpDwnCntCompl_Duty:n:	.usect "PWMDRV_1ch_UpDwnCntCompl_Section",2,1,1	; Input Terminal 1, Duty
_PWMDRV_1ch_UpDwnCntCompl_Period:n:  .usect "PWMDRV_1ch_UpDwnCntCompl_Section",2,1,1

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_1ch_UpDwnCntCompl_Duty:n:
		.def 	_PWMDRV_1ch_UpDwnCntCompl_Period:n:

		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_PWMDRV_1ch_UpDwnCntCompl_Duty:n:
			MOVL	@_PWMDRV_1ch_UpDwnCntCompl_Duty:n:, XAR2

			MOVW	DP,#_EPwm:n:Regs.TBPRD
			MOVL	ACC,@_EPwm:n:Regs.TBPRD
			MOV		AL,#0
			MOVW	DP, #_PWMDRV_1ch_UpDwnCntCompl_Duty:n:
			MOVL	@_PWMDRV_1ch_UpDwnCntCompl_Period:n:,ACC 
		
		.endm
;--------------------------------------------------------------------------------
;======================
PWMDRV_1ch_UpDwnCntCompl		.macro	n
;======================

			MOVW 	DP, #_PWMDRV_1ch_UpDwnCntCompl_Duty:n:       ; load DP for net pointer
       		MOVL   	XAR0, @_PWMDRV_1ch_UpDwnCntCompl_Duty:n:     ; Load net pointer address to XAR0 
       		MOVL    XT, @_PWMDRV_1ch_UpDwnCntCompl_Period:n:		; Load XT  = Period (I16Q16)
       		QMPYL  	ACC,XT,*XAR0    					; ACC= (I8Q24) * (I16Q16) = (I24Q40): upper 32-bits = (I24Q8)
       		SFR  	ACC,#8                           				; ACC>>8: AL = Period * Duty Q0
			SUB		@T,AL						; T=Period-Duty*Period	 
       		MOVW    DP, #_EPwm:n:Regs.CMPA				
       		MOV     @_EPwm:n:Regs.CMPA.half.CMPA,T	; CMPA = Duty * Period
			   	
		.endm


