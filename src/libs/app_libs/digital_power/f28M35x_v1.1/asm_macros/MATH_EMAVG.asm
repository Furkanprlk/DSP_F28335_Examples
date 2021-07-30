;----------------------------------------------------------------------------------
;	FILE:			MATH_EMAVG.asm
;
;	Description:	Exponential Moving Average Math Block  
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
	   MOV32 R0H,*XAR0						 	; R0H=Data(n)
	   MOV32 R1H,*XAR1							; R1H=EMA(n-1)
	   SUBF32 R0H,R0H,R1H						; R0H=Data(n)-EMA(n-1)
	   MOV32 R2H,@_MATH_EMAVG_Multiplier:n:		; R2H=Multiplier
	   NOP
	   MPYF32 R0H,R0H,R2H						; R0H=(Data(n)-EMA(n-1))*Multiplier
	   NOP
	   ADDF32 R0H,R0H,R1H						; R0H=(Data(n)-EMA(n-1))*Multiplier+EMA(n-1)
	   NOP
	   MOV32 *XAR1,R0H							; store value in output pointer
	
	   .endm

; end of file

