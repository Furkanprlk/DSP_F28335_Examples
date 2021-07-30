;----------------------------------------------------------------------------------
;	FILE:			ADCDRV_1ch_CLA.asm
;
;	Description:	Single channel ADC Result register interface macro
;
;	Version: 	
;
;   Target:  		CLA Type 0 
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
;================================
ADCDRV_1ch_CLA_INIT	.macro n
;================================
_ADCDRV_1ch_CLA_Rlt:n:	.usect "ADCDRV_1ch_CLA_Section",2,1,1	; output terminal 1

; publish Terminal Pointers for access from the C environment
		.def 	_ADCDRV_1ch_CLA_Rlt:n:

		MOVL	XAR2, #ZeroNetCLA						; "ZeroNet" is initialised to 0 in ISR
		MOVW	DP, #_ADCDRV_1ch_CLA_Rlt:n:
		MOVL	@_ADCDRV_1ch_CLA_Rlt:n:, XAR2			; zero output terminal pointer
		.endm

;--------------------------------------------------------------------------------
;=============================
ADCDRV_1ch_CLA		.macro	n
;=============================
_ADC_1ch_CLA_DRV_Start:n:
	
		  MMOV16      MAR0, @_ADCDRV_1ch_CLA_Rlt:n:		; Load MAR0 with Result pointer
		  MUI16TOF32  MR0,  @_AdcResult.ADCRESULT:n:  	;I1	 Read ADC Result in MR0									
		  MMPYF32 	  MR0,MR0,#0.000244140625			;I2  Multiply by 1/(2^12) to convert it to per unit float
		  MNOP											;I3
		  MMOV32 	  *MAR0, MR0						; Store result in per unit float format
		  ; Note: Uncomment the below MNOP's if you are using the net variable the macro writes to immidately
		  ; in CLA assembly code, this is for Read After write Protection(RAW)
		  ; if only using DPlib Macro block leave the MNOP's commented as indirect addressing which anyways use MNOP's
		  ; to load the auxillary register
		  ;MNOP
		  ;MNOP
		  ;MNOP
	
_ADC_1ch_CLA_DRV_End:n:

	.endm


