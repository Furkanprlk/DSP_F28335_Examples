;----------------------------------------------------------------------------------
;	FILE:			ADCDRV_8ch.asm
;
;	Description:	Eight Channel ADC Result register interface macro
;
;	Version: 		1.0
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
;  05/2011  | Release 1.0	(HN)
;--------------------------------------------------------------------------------
;=============================
ADCDRV_8ch_INIT	.macro m,n,p,q,r,s,t,u
;=============================
_ADCDRV_8ch_RltPtrA	.usect "ADCDRV_8ch_Section",2,1,1	; output terminal 1
_ADCDRV_8ch_RltPtrB	.usect "ADCDRV_8ch_Section",2,1,1	; output terminal 2
_ADCDRV_8ch_RltPtrC	.usect "ADCDRV_8ch_Section",2,1,1	; output terminal 3
_ADCDRV_8ch_RltPtrD	.usect "ADCDRV_8ch_Section",2,1,1	; output terminal 4
_ADCDRV_8ch_RltPtrE	.usect "ADCDRV_8ch_Section",2,1,1	; output terminal 5
_ADCDRV_8ch_RltPtrF	.usect "ADCDRV_8ch_Section",2,1,1	; output terminal 6
_ADCDRV_8ch_RltPtrG	.usect "ADCDRV_8ch_Section",2,1,1	; output terminal 7
_ADCDRV_8ch_RltPtrH	.usect "ADCDRV_8ch_Section",2,1,1	; output terminal 8

; publish Terminal Pointers for access from the C environment
		.def 	_ADCDRV_8ch_RltPtrA
		.def	_ADCDRV_8ch_RltPtrB
		.def	_ADCDRV_8ch_RltPtrC
		.def	_ADCDRV_8ch_RltPtrD
		.def 	_ADCDRV_8ch_RltPtrE
		.def	_ADCDRV_8ch_RltPtrF
		.def	_ADCDRV_8ch_RltPtrG
		.def	_ADCDRV_8ch_RltPtrH

		MOVL	XAR2, #ZeroNet						; "ZeroNet" is address to a location initialised to 0 
		MOVW	DP, #_ADCDRV_8ch_RltPtrA
		MOVL	@_ADCDRV_8ch_RltPtrA, XAR2			; zero output terminal pointer
		MOVL	@_ADCDRV_8ch_RltPtrB, XAR2			; zero output terminal pointer
		MOVL	@_ADCDRV_8ch_RltPtrC, XAR2			; zero output terminal pointer
		MOVL	@_ADCDRV_8ch_RltPtrD, XAR2			; zero output terminal pointer
		MOVL	@_ADCDRV_8ch_RltPtrE, XAR2			; zero output terminal pointer
		MOVL	@_ADCDRV_8ch_RltPtrF, XAR2			; zero output terminal pointer
		MOVL	@_ADCDRV_8ch_RltPtrG, XAR2			; zero output terminal pointer
		MOVL	@_ADCDRV_8ch_RltPtrH, XAR2			; zero output terminal pointer		
		.endm

;--------------------------------------------------------------------------------
;=============================
ADCDRV_8ch		.macro	m,n,p,q,r,s,t,u
;=============================
	
		MOVW    DP, #_ADCDRV_8ch_RltPtrA			; Load Data Page
        MOVL    XAR0,@_ADCDRV_8ch_RltPtrA			; Load Rlt1 Data Page Pointer in XAR0
		MOVL    XAR1,@_ADCDRV_8ch_RltPtrB			; Load Rlt2 Data Page Pointer in XAR1
		MOVL    XAR2,@_ADCDRV_8ch_RltPtrC			; Load Rlt3 Data Page Pointer in XAR2
		MOVL    XAR3,@_ADCDRV_8ch_RltPtrD			; Load Rlt4 Data Page Pointer in XAR3
        MOVL    XAR4,@_ADCDRV_8ch_RltPtrE			; Load Rlt5 Data Page Pointer in XAR4
		MOVL    XAR5,@_ADCDRV_8ch_RltPtrF			; Load Rlt6 Data Page Pointer in XAR5
		MOVL    XAR6,@_ADCDRV_8ch_RltPtrG			; Load Rlt7 Data Page Pointer in XAR6
		MOVL    XAR7,@_ADCDRV_8ch_RltPtrH			; Load Rlt8 Data Page Pointer in XAR7
				
		MOVW 	DP, #_AdcResult                     ; load Data Page to read ADC results
        MOV     ACC,@_AdcResult.ADCRESULT:m:<<12	; read and shift the 12 bit ADC result by 12 bits to get Q24 value
		MOVL    *XAR0,ACC							; store result in output pointer location
        MOV     ACC,@_AdcResult.ADCRESULT:n:<<12
		MOVL    *XAR1,ACC
		MOV     ACC,@_AdcResult.ADCRESULT:p:<<12
		MOVL    *XAR2,ACC
		MOV     ACC,@_AdcResult.ADCRESULT:q:<<12
		MOVL    *XAR3,ACC
        MOV     ACC,@_AdcResult.ADCRESULT:r:<<12	
		MOVL    *XAR4,ACC							
        MOV     ACC,@_AdcResult.ADCRESULT:s:<<12
		MOVL    *XAR5,ACC
		MOV     ACC,@_AdcResult.ADCRESULT:t:<<12
		MOVL    *XAR6,ACC
		MOV     ACC,@_AdcResult.ADCRESULT:u:<<12
		MOVL    *XAR7,ACC		
		.endm
; end of file

