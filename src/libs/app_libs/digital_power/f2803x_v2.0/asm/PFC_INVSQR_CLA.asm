;---------------------------------------------------------------------------------
;	FILE:			PFC_INVSQR_CLA.asm
;
;	Description:	Inverse Square Block  
;
;	Version: 		2.0
;
;   Target:  		CLA Type 0
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
PFC_INVSQR_CLA_INIT	.macro	n
;=============================
; variable Declarations
_PFC_INVSQR_CLA_In:n:			.usect "PFC_INVSQR_CLA_Section",2,1,1	; Input Terminal 1, Phase
_PFC_INVSQR_CLA_Out:n: 			.usect "PFC_INVSQR_CLA_Section",2,1,1 ; Input Terminal 2, DbLeft
_PFC_INVSQR_CLA_VminOverVmax:n:	.usect "PFC_INVSQR_CLA_InternalData",2,1,1
_PFC_INVSQR_CLA_Vmin:n:			.usect "PFC_INVSQR_CLA_InternalData",2,1,1


;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PFC_INVSQR_CLA_In:n: 
		.def 	_PFC_INVSQR_CLA_Out:n:
		.def	_PFC_INVSQR_CLA_VminOverVmax:n:
		.def	_PFC_INVSQR_CLA_Vmin:n:
		
		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNetCLA
			MOVW	DP, #_PFC_INVSQR_CLA_In:n:
			MOVL	@_PFC_INVSQR_CLA_In:n:, XAR2
			MOVL	@_PFC_INVSQR_CLA_Out:n:, XAR2
					
		.endm

;======================
PFC_INVSQR_CLA			.macro	n
;======================
				
_PFC_INVSQR_CLA_Start:n:

		MMOV16  MAR0, @_PFC_INVSQR_CLA_In:n:		; I1         
        MMOV16  MAR1, @_PFC_INVSQR_CLA_Out:n:		; I2 
	    MNOP                           				; I3    
        MNOP  										; can not use MAR0        
        MI32TOF32	MR0, *MAR0						; Load PFC_INVSQR_In
        MI32TOF32	MR1, @_PFC_INVSQR_CLA_Vmin:n:
        MMAXF32		MR0,MR1
        MMPYF32		MR0,MR0,#1.5707L
        MEINVF32 	MR0, MR0 						; MR2 = 1/ AVG_ACLINE
        MI32TOF32	MR1, @_PFC_INVSQR_CLA_VminOverVmax:n:
        MMPYF32		MR0,MR0,MR1
        MMPYF32		MR0,MR0,MR0
        MMPYF32		MR0,MR0,#4096.0L    
        MMINF32		MR0,#16777216.0L         		; saturate to Q24(1.0)
        MF32TOI32 	MR0, MR0						; convert to Integer
        
        MMOV32		*MAR1,MR0
		 
_PFC_INVSQR_CLA_End:n:
	   	
		.endm


