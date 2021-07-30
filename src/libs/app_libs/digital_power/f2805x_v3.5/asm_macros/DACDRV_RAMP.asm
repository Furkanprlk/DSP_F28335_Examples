;----------------------------------------------------------------------------------
;	FILE:			DACDRV_RAMP.asm
;
;	Description:	DAC Ramp Driver interface macro
;
;	Version: 	
;
;   Target:  		F2802x / F2803x / F2806x/ F2805x
;
;--------------------------------------------------------------------------------
;   Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
;   ALL RIGHTS RESERVED
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;--------------------------------------------------------------------------------
;=============================
; Description:
; ------------
; DAC Ramp generator Driver interface
; n = 1, 2, 3 for Piccolo
;----------------------------------------------------------------------------------
;=============================
DACDRV_RAMP_INIT		.macro	n
;=============================
; Variable Declarations
_DACDRV_RAMP_In:n:			.usect "DACDRV_RAMP_Section",2,1,1	; Input Terminal

; Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_DACDRV_RAMP_In:n:

; Set terminal pointers to ZeroNet
		MOVL	XAR2, #ZeroNet
		MOVW	DP, #_DACDRV_RAMP_In:n:
		MOVL	@_DACDRV_RAMP_In:n:, XAR2

		.endm

;----------------------------------------------------------------------------------
;=========================
DACDRV_RAMP		.macro	n
;=========================
; Set up address pointers
		MOVW	DP, #_DACDRV_RAMP_In:n:
		MOVL 	XAR0,@_DACDRV_RAMP_In:n:			; Net pointer for InA (XAR0)
		MOVL 	XAR1,#_Comp:n:Regs.RAMPMAXREF_SHDW	; pointer to Comparator Ramp Max Ref (XAR1)
		MOVL 	XAR2,#_Comp:n:Regs.DACVAL			; pointer to Comparator Ramp Dac Val (XAR2)

; Output for DACn
		MOVL 	ACC,*XAR0							; Q24						
		SFR		ACC,#8								; Q16 because Maximum RAMPMAXREF = 0xFFFF
		MOV 	*XAR1,AL							; Output value to RAMPMAXREF
		LSR		AL, #6								; Q10 to be written to DACVAL
		MOV 	*XAR2,AL							; Output value to DACVAL

		.endm 
					
; end of file