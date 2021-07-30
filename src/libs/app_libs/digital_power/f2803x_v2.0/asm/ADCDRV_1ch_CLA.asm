;----------------------------------------------------------------------------------
;	FILE:			ADCDRV_1ch_CLA.inc
;
;	Description:	Single channel ADC Result register interface macro
;
;	Version: 		2.0
;
;   Target:  		CLA Type 0 
;
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;  06/15/10  | Release 2.0  (MB)		
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
		  MUI16TOF32  MR0,  @_AdcResult.ADCRESULT:n:	; Read ADC Result in MR0
		  MMPYF32 	  MR0,MR0,#4096.0L					; Multiply by 2^12 to convert to Q24
		  MF32TOUI32  MR1,MR0							; convert float to integer
		  MMOV32 	  *MAR0, MR1						; Store result in Q24 format
	
_ADC_1ch_CLA_DRV_End:n:

	.endm


