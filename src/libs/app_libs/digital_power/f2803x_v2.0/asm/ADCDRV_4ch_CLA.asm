;----------------------------------------------------------------------------------
;	FILE:			ADCDRV_4ch_CLA.inc
;
;	Description:	Four Channel ADC Result register interface macro
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
ADCDRV_4ch_CLA_INIT	.macro m,n,p,q
;================================
_ADCDRV_4ch_CLA_RltPtrA	.usect "ADCDRV_4ch_CLA_Section",2,1,1	; output terminal 1
_ADCDRV_4ch_CLA_RltPtrB	.usect "ADCDRV_4ch_CLA_Section",2,1,1	; output terminal 2
_ADCDRV_4ch_CLA_RltPtrC	.usect "ADCDRV_4ch_CLA_Section",2,1,1	; output terminal 3
_ADCDRV_4ch_CLA_RltPtrD	.usect "ADCDRV_4ch_CLA_Section",2,1,1	; output terminal 4

; publish Terminal Pointers for access from the C environment
		.def 	_ADCDRV_4ch_CLA_RltPtrA
		.def 	_ADCDRV_4ch_CLA_RltPtrB
		.def 	_ADCDRV_4ch_CLA_RltPtrC
		.def 	_ADCDRV_4ch_CLA_RltPtrD

		MOVL	XAR2, #ZeroNetCLA						; "ZeroNet" is location initialized to zero
		MOVW	DP, #_ADCDRV_4ch_CLA_RltPtrA
		MOVL	@_ADCDRV_4ch_CLA_RltPtrA, XAR2			; zero output terminal pointer
		MOVL	@_ADCDRV_4ch_CLA_RltPtrB, XAR2			; zero output terminal pointer
		MOVL	@_ADCDRV_4ch_CLA_RltPtrC, XAR2			; zero output terminal pointer
		MOVL	@_ADCDRV_4ch_CLA_RltPtrD, XAR2			; zero output terminal pointer
		.endm

;--------------------------------------------------------------------------------
;=============================
ADCDRV_4ch_CLA		.macro	m,n,p,q
;=============================
_ADC_4ch_CLA_DRV_Start:n:

		
		  MMOV16      	MAR0, @_ADCDRV_4ch_CLA_RltPtrA	; Load MAR0 with Result pointer1 
		  MUI16TOF32  	MR0,  @_AdcResult.ADCRESULT:m:	; Read ADC Result in MR0
		  MMPYF32 		MR0,MR0,#4096.0L				; Multiply by 2^12 to convert to Q24
		  MF32TOUI32 	MR0,MR0							; convert float to integer
		  MMOV32 		*MAR0, MR0						; Store result in Q24 format
		  
		  MMOV16      	MAR1, @_ADCDRV_4ch_CLA_RltPtrB
		  MUI16TOF32  	MR1,  @_AdcResult.ADCRESULT:n:
		  MMPYF32 		MR1,MR1,#4096.0L
		  MF32TOUI32 	MR1,MR1
		  MMOV32 		*MAR1, MR1
		  
		  MMOV16      	MAR0, @_ADCDRV_4ch_CLA_RltPtrC
		  MUI16TOF32  	MR2,  @_AdcResult.ADCRESULT:p:
		  MMPYF32 		MR2,MR2,#4096.0L
		  MF32TOUI32 	MR2,MR2
		  MMOV32 		*MAR0, MR2
		  
		  MMOV16      	MAR1, @_ADCDRV_4ch_CLA_RltPtrD
		  MUI16TOF32  	MR3,  @_AdcResult.ADCRESULT:q:
		  MMPYF32 		MR3,MR3,#4096.0L
		  MF32TOUI32 	MR3,MR3
		  MMOV32 		*MAR1, MR3
		  
_ADC_4ch_CLA_DRV_End:n:

	.endm


