;---------------------------------------------------------------------------------
;	FILE:			PWMDRV_PFC2PhiL.asm
;
;	Description:	PWM driver for 2 phase interleaved Power Factor Correction stage
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
;  	| Release 3.0  		(MB)
;--------------------------------------------------------------------------------
;=============================
PWMDRV_PFC2PhiL_CLA_INIT	.macro	n
;=============================
; variable Declarations
_PWMDRV_PFC2PhiL_CLA_Duty:n:	.usect "PWMDRV_PFC2PhiL_CLA_Section",2,1,1	; Input Terminal 1, Duty
_PWMDRV_PFC2PhiL_CLA_Adj:n: 	.usect "PWMDRV_PFC2PhiL_CLA_Section",2,1,1  ; Input Terminal 2, Adj

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_PFC2PhiL_CLA_Duty:n:
		.def 	_PWMDRV_PFC2PhiL_CLA_Adj:n:

		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNetCLA
			MOVW	DP, #_PWMDRV_PFC2PhiL_CLA_Duty:n:
			MOVL	@_PWMDRV_PFC2PhiL_CLA_Duty:n:, XAR2
			MOVL	@_PWMDRV_PFC2PhiL_CLA_Adj:n:, XAR2
		
		.endm
;--------------------------------------------------------------------------------
;======================
PWMDRV_PFC2PhiL_CLA			.macro	n
;======================

_PWMDRV_PFC2PhiL_CLA_Start:n:

		; MAR0  =  Pointer to Duty Value
		; MAR1  =  Pointer to Adj value 
        ; MR0   =  ePWM Period
        ;          + 2 cycle delay for MAR0 load    
		MMOV16 	MAR0, @_PWMDRV_PFC2PhiL_CLA_Duty:n:
		MMOV16  MAR1, @_PWMDRV_PFC2PhiL_CLA_Adj:n:
		MUI16TOF32	MR0, @_EPwm:n:Regs.TBPRD
		MNOP

		; MR1   =Duty
		MMOV32	 	MR1,*MAR0
		
		; MR1 = Duty(MR1) * TBPRD (MR0)
		MMPYF32     MR1, MR1, MR0						;MR1= TBPRD * Duty
        
        ; MR2   = Adj
		MMOV32   	MR2,*MAR1							; 
		
		; MR2  = Adj(MR2) *  TBPRD MR0
		MMPYF32     MR2, MR2, MR0						;MR2= TBPRD * Adj
		
		MADDF32 	MR3,MR1,MR2							;MR3= TBPRD * Adj + TBPRD * Duty
		MF32TOI16	MR3,MR3
		
		;update CMPA			
        MF32TOI16  	MR1, MR1					
        MMOV16      @_EPwm:n:Regs.CMPA.half.CMPA, MR1

		MF32TOI16	MR0,MR0
		MSUB32		MR2,MR0,MR3						   ; MR4 = TBPRD(1- Duty-Adj)
		
		MMOV16      @_EPwm:n:Regs.CMPB, MR2
	   	 
_PWMDRV_PFC2PhiL_CLA_End:n:
	   	
		.endm


