;----------------------------------------------------------------------------------
;	FILE:			ADC1DRV_1ch.asm
;
;	Description:	Single channel ADC1 Result register interface macro
;
;	Version: 		3.0
;
;   Target:  		F28M35x
;
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;   | Release 3.0  (MB)
;--------------------------------------------------------------------------------
;================================
ADC1DRV_1ch_INIT	.macro n
;================================
_ADC1DRV_1ch_Rlt:n:	.usect "ADCDRV_1ch_Section",2,1,1	; output terminal 1

; publish Terminal Pointers for access from the C environment
		.def 	_ADC1DRV_1ch_Rlt:n:

		MOVL	XAR2, #ZeroNet						; "ZeroNet" is initialised to 0 in ISR
		MOVW	DP, #_ADC1DRV_1ch_Rlt:n:>>6
		MOVL	@_ADC1DRV_1ch_Rlt:n:, XAR2			; zero output terminal pointer
		.endm

;--------------------------------------------------------------------------------
;=============================
ADC1DRV_1ch		.macro	n
;=============================
	 	MOVW 	DP, #_Adc1Result                     ; load Data Page to read ADC results
        UI16TOF32	R0H,@_Adc1Result.ADCRESULT:n:
        MOVW    DP, #_ADC1DRV_1ch_Rlt:n:				; Load Data Page
        MPYF32	R0H,R0H,#0.000244140625
        MOVL    XAR0,@_ADC1DRV_1ch_Rlt:n:			; Load Rlt Data Page Pointer in XAR0
        MOV32    *XAR0,R0H							; store result in output pointer location
		.endm
; end of file

