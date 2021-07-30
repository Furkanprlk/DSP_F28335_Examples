;----------------------------------------------------------------------------------
;	FILE:			MATH_EMAVG.asm
;
;	Description:	Exponential Moving Average Math Block  
;
;	Version: 		3.0
;
;   Target:  		F2802x / F2803x / F2806x
;
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;  	| Release 3.0  		New release.
;--------------------------------------------------------------------------------
;=============================
MATH_EMAVG_INIT	.macro	n
;=============================
; variable declarations
_MATH_EMAVG_In:n:			.usect "MATH_EMAVG_Section",2,1,1	; input terminal
_MATH_EMAVG_Out:n: 			.usect "MATH_EMAVG_Section",2,1,1	; output terminal
_MATH_EMAVG_Multiplier:n:	.usect "MATH_EMAVG_Section",2,1,1

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_MATH_EMAVG_In:n:
		.def	_MATH_EMAVG_Out:n:
		.def 	_MATH_EMAVG_Multiplier:n:

; set terminal pointer to ZeroNet
		MOVL	XAR2, #ZeroNet
		MOVW	DP, #_MATH_EMAVG_In:n:
		MOVL	@_MATH_EMAVG_In:n:, XAR2
		MOVL	@_MATH_EMAVG_Out:n:, XAR2
		.endm

;---------------------------------------------------------------------------------
; EMA(n) = (Data(n) - EMA(n-1))*MULTIPLER + EMA(n-1);
;=============================
MATH_EMAVG .macro	n
;=============================
	   MOVW DP,#_MATH_EMAVG_In:n:
	   MOVL	XAR0,@_MATH_EMAVG_In:n:	
	   MOVL	XAR1,@_MATH_EMAVG_Out:n:
	   MOVL	ACC,*XAR0						 	; ACC=Data(n)
	   SUBL	ACC, *XAR1						 	; ACC=Data(n)-EMA(n-1), I824
	   LSL	ACC, #6							 	; I230
	   MOVL	@XAR2,ACC							; XAR2 = (Data(n)-EMA(n-1))
	   MOVL	XT,@_MATH_EMAVG_Multiplier:n:		; XT= _IQ30(Multiplier)
	   MOVL	ACC,*XAR1							; ACC = EMA(n-1)Q24
	   QMPYL P,XT,@XAR2 						; ACC=(Data(n)-EMA(n-1))I2Q30*MultiplierI2Q30, I2Q30 = I4Q60 = I4Q28
	   
	   LSL	ACC, #4								; ACC=  EMA(n-1)Q28
	   ADDL	ACC,@P								; ACC = I4Q28 + I4Q28 
	   ASR64 ACC:P,#4							; ACC = Q24
	   MOVL	*XAR1,ACC							; store value in output pointer
	
	   .endm

; end of file

