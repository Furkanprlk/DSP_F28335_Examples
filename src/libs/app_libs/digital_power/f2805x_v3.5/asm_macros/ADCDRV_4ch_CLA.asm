;----------------------------------------------------------------------------------
;	FILE:			ADCDRV_4ch_CLA.asm
;
;	Description:	Four Channel ADC Result register interface macro
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
		  MUI16TOF32  	MR0,  @_AdcResult.ADCRESULT:m:	; I1 Read ADC Result in MR0
		  MMPYF32 		MR0,MR0,#0.000244140625			; I2 Multiply by 1/(2^12) to convert it to per unit float
		  MMOV16      	MAR1, @_ADCDRV_4ch_CLA_RltPtrB	; I3  I1
		  MMOV32 		*MAR0, MR0						; 	  I2 Store result in per unit float format
		  MUI16TOF32  	MR1,  @_AdcResult.ADCRESULT:n:  ;     I3
		  MMOV16      	MAR0, @_ADCDRV_4ch_CLA_RltPtrC	; I1
		  MMPYF32 		MR1,MR1,#0.000244140625         ; I2
		  MMOV32 		*MAR1, MR1                      ; I3  
		  
		  MUI16TOF32  	MR2,  @_AdcResult.ADCRESULT:p:  ;     
		  MMPYF32 		MR2,MR2,#0.000244140625L        ;       
		  MMOV16      	MAR1, @_ADCDRV_4ch_CLA_RltPtrD  ;     
		  MMOV32 		*MAR0, MR2                      ;	  I1
		  MUI16TOF32  	MR3,  @_AdcResult.ADCRESULT:q:  ;     I2
		  MMPYF32 		MR3,MR3,#0.000244140625			;	  I3
		  MMOV32 		*MAR1, MR3
		  
		  ; Note: Uncomment the below MNOP's if you are using the net variable pointed to by PtrD, 
		  ; that the macro writes to immidately in CLA assembly code, this is for Read After write Protection(RAW)
		  ; if only using DPlib Macro block leave the MNOP's commented as indirect addressing which anyways use MNOP's
		  ; to load the auxillary register
		  ;MNOP
		  ;MNOP
		  ;MNOP
		  
_ADC_4ch_CLA_DRV_End:n:

	.endm


