;----------------------------------------------------------------------------------
;	FILE:			ADCDRV_4ch.asm
;
;	Description:	Four Channel ADC Result register interface macro
;
;	Version: 		3.0
;
;   Target:  		F2802x / F2803x
;
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;    | Release 3.0	(MB)
;--------------------------------------------------------------------------------
;=============================
ADCDRV_4ch_INIT	.macro m,n,p,q
;=============================
_ADCDRV_4ch_RltPtrA	.usect "ADCDRV_4ch_Section",2,1,1	; output terminal 1
_ADCDRV_4ch_RltPtrB	.usect "ADCDRV_4ch_Section",2,1,1	; output terminal 2
_ADCDRV_4ch_RltPtrC	.usect "ADCDRV_4ch_Section",2,1,1	; output terminal 3
_ADCDRV_4ch_RltPtrD	.usect "ADCDRV_4ch_Section",2,1,1	; output terminal 4

; publish Terminal Pointers for access from the C environment
		.def 	_ADCDRV_4ch_RltPtrA
		.def	_ADCDRV_4ch_RltPtrB
		.def	_ADCDRV_4ch_RltPtrC
		.def	_ADCDRV_4ch_RltPtrD

		MOVL	XAR2, #ZeroNet						; "ZeroNet" is address to a location initialised to 0 
		MOVW	DP, #_ADCDRV_4ch_RltPtrA
		MOVL	@_ADCDRV_4ch_RltPtrA, XAR2			; zero output terminal pointer
		MOVL	@_ADCDRV_4ch_RltPtrB, XAR2			; zero output terminal pointer
		MOVL	@_ADCDRV_4ch_RltPtrC, XAR2			; zero output terminal pointer
		MOVL	@_ADCDRV_4ch_RltPtrD, XAR2			; zero output terminal pointer
		.endm

;--------------------------------------------------------------------------------
;=============================
ADCDRV_4ch		.macro	m,n,p,q
;=============================
	
		MOVW    DP, #_ADCDRV_4ch_RltPtrA			; Load Data Page
        MOVL    XAR0,@_ADCDRV_4ch_RltPtrA			; Load Rlt1 Data Page Pointer in XAR0
		MOVL    XAR1,@_ADCDRV_4ch_RltPtrB			; Load Rlt2 Data Page Pointer in XAR1
		MOVL    XAR2,@_ADCDRV_4ch_RltPtrC			; Load Rlt3 Data Page Pointer in XAR2
		MOVL    XAR3,@_ADCDRV_4ch_RltPtrD			; Load Rlt4 Data Page Pointer in XAR0
		
		MOVW 	DP, #_AdcResult                     ; load Data Page to read ADC results
        MOV     ACC,@_AdcResult.ADCRESULT:m:<<12	; read and shift the 12 bit ADC result by 12 bits to get Q24 value
		MOVL    *XAR0,ACC							; store result in output pointer location
        MOV     ACC,@_AdcResult.ADCRESULT:n:<<12
		MOVL    *XAR1,ACC
		MOV     ACC,@_AdcResult.ADCRESULT:p:<<12
		MOVL    *XAR2,ACC
		MOV     ACC,@_AdcResult.ADCRESULT:q:<<12
		MOVL    *XAR3,ACC
		
		.endm
; end of file

