;----------------------------------------------------------------------------------
;	FILE:			{ProjectName}-DPL-ISR.asm
;
;	Description:	{ProjectName}-DPL-ISR.asm contains the ISR for the system
;					It also contains the initailization routine for all the macros 
;					being used in the system both for CLA and C28x macros
;   
;   Revision/ Version: See {ProjectName}-Main.c
;----------------------------------------------------------------------------------

		;Gives peripheral addresses visibility in assembly
	    .cdecls   C,LIST,"PeripheralHeaderIncludes.h"

		;include C header file - sets INCR_BUILD etc.(used in conditional builds)
		.cdecls C,NOLIST, "ProjectName-Settings.h"

		;Include files for the Power Library Maco's being used by the system
		.include "PWMDRV_1ch.asm" 
			
;=============================================================================
; Digital Power library - Initailization Routine 
;=============================================================================

		; label to DP initialisation function
		.def _DPL_Init	

		; dummy variable for pointer initialisation
ZeroNet	 .usect "ZeroNet_Section",2,1,1	; output terminal 1

		.text
_DPL_Init:
		ZAPA
		MOVL	XAR0, #ZeroNet
		MOVL	*XAR0, ACC

		; Initialize all the DP library macro used here 
		;---------------------------------------------------------
		.if(INCR_BUILD = 1)
			PWMDRV_1ch_INIT 2	; PWM2A	
		.endif
		;---------------------------------------------------------			
		LRETR

;-----------------------------------------------------------------------------------------

; Digital Power library - Interrupt Service Routine

		.sect "ramfuncs"
		; label to DP ISR Run function
		.def	_DPL_ISR

_DPL_ISR:
		; full context save - push any unprotected registers onto stack
		PUSH  	AR1H:AR0H
		PUSH  	XAR2
		PUSH  	XAR3
		PUSH  	XAR4
		PUSH  	XAR5
		PUSH  	XAR6
		PUSH  	XAR7
		PUSH  	XT
		SPM   	0          				; set C28 mode
		CLRC  	AMODE       
		CLRC  	PAGE0,OVM 
;		CLRC	INTM					; clear interrupt mask - comment if ISR non-nestable
;-----------------------------------------------------------------------------------------

; call DP library modules

		;---------------------------------------------------------
		.if(INCR_BUILD = 1)
			PWMDRV_1ch 2		; PWM2A
		.endif
		;----------------------------------------------------------
		
;-----------------------------------------------------------------------------------------
; Interrupt management before exit

	.if(EPWMn_DPL_ISR=1)

	.if(EPWM1)
		MOVW 	DP,#_EPwm1Regs.ETCLR
		MOV 	@_EPwm1Regs.ETCLR,#0x01			; Clear EPWM1 Int flag
	.endif ; EPWM1

	.if(EPWM2)
		MOVW 	DP,#_EPwm2Regs.ETCLR
		MOV 	@_EPwm2Regs.ETCLR,#0x01			; Clear EPWM2 Int flag
	.endif ; EPWM2

	.if(EPWM3)
		MOVW 	DP,#_EPwm3Regs.ETCLR
		MOV 	@_EPwm3Regs.ETCLR,#0x01			; Clear EPWM3 Int flag
	.endif ; EPWM3

	.if(EPWM4)
		MOVW 	DP,#_EPwm4Regs.ETCLR
		MOV 	@_EPwm4Regs.ETCLR,#0x01			; Clear EPWM4 Int flag
	.endif ; EPWM4

	.if(EPWM5)
		MOVW 	DP,#_EPwm5Regs.ETCLR
		MOV 	@_EPwm5Regs.ETCLR,#0x01			; Clear EPWM5 Int flag
	.endif ; EPWM5

	.if(EPWM6)
		MOVW 	DP,#_EPwm6Regs.ETCLR
		MOV 	@_EPwm6Regs.ETCLR,#0x01			; Clear EPWM6 Int flag
	.endif ; EPWM6

		MOVW 	DP,#_PieCtrlRegs.PIEACK			; Acknowledge PIE interrupt Group 3
		MOV 	@_PieCtrlRegs.PIEACK, #0x4
	.endif ; EPWMn_ISR

	.if(CLAn_DPL_ISR=1)

		MOVW 	DP,#_PieCtrlRegs.PIEACK			; Acknowledge PIE interrupt Group 11
		MOV 	@_PieCtrlRegs.PIEACK, #0x0400	
		
	.endif 
	
	.if(ADC_DPL_ISR=1)
	; Case where ISR is triggered by ADC 
		MOVW 	DP,#_AdcRegs.ADCINTFLGCLR
		MOV 	@AdcRegs.ADCINTFLGCLR,#0x01		; Clear ADCINT1 Flag

		MOVW 	DP,#_PieCtrlRegs.PIEACK			; Acknowledge PIE interrupt Group 1
		MOV 	@_PieCtrlRegs.PIEACK,0x1
	.endif 

;-----------------------------------------------------------------------------------------
; full context restore
;		SETC	INTM					; set INTM to protect context restore
		POP   	XT
		POP   	XAR7
		POP   	XAR6
		POP   	XAR5
		POP   	XAR4
		POP   	XAR3
		POP   	XAR2
		POP   	AR1H:AR0H
		IRET							; return from interrupt
		.end

; end of file

