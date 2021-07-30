;----------------------------------------------------------------------------------
;	FILE:			ADC2DRV_4ch.asm
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
ADC2DRV_4ch_INIT	.macro m,n,p,q
;=============================
_ADC2DRV_4ch_RltPtrA	.usect "ADC2DRV_4ch_Section",2,1,1	; output terminal 1
_ADC2DRV_4ch_RltPtrB	.usect "ADC2DRV_4ch_Section",2,1,1	; output terminal 2
_ADC2DRV_4ch_RltPtrC	.usect "ADC2DRV_4ch_Section",2,1,1	; output terminal 3
_ADC2DRV_4ch_RltPtrD	.usect "ADC2DRV_4ch_Section",2,1,1	; output terminal 4

; publish Terminal Pointers for access from the C environment
		.def 	_ADC2DRV_4ch_RltPtrA
		.def	_ADC2DRV_4ch_RltPtrB
		.def	_ADC2DRV_4ch_RltPtrC
		.def	_ADC2DRV_4ch_RltPtrD

		MOVL	XAR2, #ZeroNet						; "ZeroNet" is address to a location initialised to 0 
		MOVW	DP, #_ADC2DRV_4ch_RltPtrA
		MOVL	@_ADC2DRV_4ch_RltPtrA, XAR2			; zero output terminal pointer
		MOVL	@_ADC2DRV_4ch_RltPtrB, XAR2			; zero output terminal pointer
		MOVL	@_ADC2DRV_4ch_RltPtrC, XAR2			; zero output terminal pointer
		MOVL	@_ADC2DRV_4ch_RltPtrD, XAR2			; zero output terminal pointer
		.endm

;--------------------------------------------------------------------------------
;=============================
ADC2DRV_4ch		.macro	m,n,p,q
;=============================
	
		MOVW 	DP, #_ADC2Result                     ; load Data Page to read ADC results
        UI16TOF32	R0H,@_ADC2Result.ADCRESULT:m:
        UI16TOF32	R1H,@_ADC2Result.ADCRESULT:n:
        UI16TOF32	R2H,@_ADC2Result.ADCRESULT:p:
        UI16TOF32	R3H,@_ADC2Result.ADCRESULT:q:
        
        MOVW    DP, #_ADC2DRV_4ch_RltPtrA			; Load Data Page
        MPYF32	R0H,R0H,#0.000244140625
        MOVL    XAR0,@_ADC2DRV_4ch_RltPtrA			; Load Rlt Data Page Pointer A in XAR0
        MPYF32	R1H,R1H,#0.000244140625
        MOV32   *XAR0,R0H
        MOVL    XAR0,@_ADC2DRV_4ch_RltPtrC			; Load Rlt Data Page Pointer A in XAR0
        MOVL    XAR1,@_ADC2DRV_4ch_RltPtrB			; Load Rlt Data Page Pointer A in XAR0
        MPYF32	R2H,R2H,#0.000244140625
        MOV32    *XAR1,R1H
        MPYF32	R3H,R3H,#0.000244140625
        MOVL    XAR1,@_ADC2DRV_4ch_RltPtrC			; Load Rlt Data Page Pointer A in XAR0
        MOV32    *XAR0,R2H
        MOV32    *XAR1,R3H
        	
		.endm
; end of file

