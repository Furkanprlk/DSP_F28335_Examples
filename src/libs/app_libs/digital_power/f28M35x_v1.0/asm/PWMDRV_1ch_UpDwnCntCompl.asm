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


;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_1ch_UpDwnCntCompl_Duty:n:

		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_PWMDRV_1ch_UpDwnCntCompl_Duty:n:
			MOVL	@_PWMDRV_1ch_UpDwnCntCompl_Duty:n:, XAR2
		
		.endm
;--------------------------------------------------------------------------------
;======================
PWMDRV_1ch_UpDwnCntCompl		.macro	n
;======================

			MOVW 	DP, #_PWMDRV_1ch_UpDwnCntCompl_Duty:n:       ; load DP for net pointer
       		MOVL   	XAR0, @_PWMDRV_1ch_UpDwnCntCompl_Duty:n:     ; Load net pointer address to XAR0 
       		
       		MOVW	DP,#_EPwm:n:Regs.TBPRD
       		UI16TOF32  R0H,  @_EPwm:n:Regs.TBPRD
       		
       		MOV32	R1H,*XAR0									 ; R1H=Duty
       		MPYF32	R2H,R1H,R0H									 ; R2H=Duty*TBPRD
       		NOP
       		
       		SUBF32	R0H,R0H,R2H									; R0H = Period - Duty*TBPRD
       		NOP
       		F32TOUI16 R1H,R0H
       		NOP
       		       	
       		MOV16     @_EPwm:n:Regs.CMPA.half.CMPA,R1H	; CMPA = Duty * Period
       		 	
		.endm


