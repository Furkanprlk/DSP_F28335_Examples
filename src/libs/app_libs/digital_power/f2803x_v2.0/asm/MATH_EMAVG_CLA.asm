;---------------------------------------------------------------------------------
;	FILE:			MATH_EMAVG_CLA.asm
;
;	Description:	Exponential Moving Average  
;
;	Version: 		2.0
;
;   Target:  		CLA Type 1
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;  06/15/10	| Release 2.0  	(MB)
;--------------------------------------------------------------------------------
;=============================
MATH_EMAVG_CLA_INIT	.macro	n
;=============================
; variable Declarations
_MATH_EMAVG_CLA_In:n:			.usect "MATH_EMAVG_CLA_Section",2,1,1	; Input Terminal 1, Phase
_MATH_EMAVG_CLA_Out:n: 			.usect "MATH_EMAVG_CLA_Section",2,1,1 ; Input Terminal 2, DbLeft
_MATH_EMAVG_CLA_Multiplier:n:	.usect "MATH_EMAVG_CLA_InternalData",2,1,1

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_MATH_EMAVG_CLA_In:n: 
		.def 	_MATH_EMAVG_CLA_Out:n:
		.def 	_MATH_EMAVG_CLA_Multiplier:n:
		
		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNetCLA
			MOVW	DP, #_MATH_EMAVG_CLA_In:n:
			MOVL	@_MATH_EMAVG_CLA_In:n:, XAR2
			MOVL	@_MATH_EMAVG_CLA_Out:n:, XAR2
					
		.endm

;======================
MATH_EMAVG_CLA			.macro	n,m
;======================
				
_MATH_EMAVG_CLA_Start:n:

		MMOV16  MAR0, @_MATH_EMAVG_CLA_In:n:		; Load Input Pointer in MAR0         
        MMOV16  MAR1, @_MATH_EMAVG_CLA_Out:n:		; Load Output pointer in MAR1 
	    MMOV32	MR3,  @_MATH_EMAVG_CLA_Multiplier:n:,UNC        ; MR3= Multiplier
        MNOP  										; can not use MAR0        
        MI32TOF32	MR0,  *MAR0						; MR0 = Input(n)
        MI32TOF32	MR1, *MAR1						; MR1 = EMA(n-1)
        MSUBF32 	MR0,MR0,MR1						; MR0= {Input(n)-EMA(n-1)}
        MMPYF32		MR2,MR0,MR3						; MR2= {Input(n)-EMA(n-1)}*Multiplier
	    MADDF32     MR0, MR1,MR2					; MR0 = EMA(n-1) + MR2
		MF32TOI32 	MR0, MR0						; convert to Integer
		MMOV32     	*MAR1, MR0  					; NetTerminal Output [Q24]
			 
_MATH_EMAVG_CLA_End:n:
	   	
		.endm


