;---------------------------------------------------------------------------------
;	FILE:			PFC_INVSQR_CLA.asm
;
;	Description:	Inverse Square Block  
;
;	Version: 		
;
;   Target:  		CLA Type 0
;--------------------------------------------------------------------------------
;   Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
;   ALL RIGHTS RESERVED
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
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

		MMOV16  	MAR0, @_PFC_INVSQR_CLA_In:n:			;         
        MMOV16  	MAR1, @_PFC_INVSQR_CLA_Out:n:			; I1 
	    MMOV32		MR1, @_PFC_INVSQR_CLA_Vmin:n:			; I2   
        MMOV32		MR2, @_PFC_INVSQR_CLA_VminOverVmax:n: 	; I3

        MMOV32		MR0, *MAR0								; Load PFC_INVSQR_In
        
        MMAXF32		MR0,MR1
        MMPYF32		MR0,MR0,#1.5707L
        MEINVF32 	MR0, MR0 								; MR0 = 1/ (satmin(AVG_ACLINE)*(pi/2))
        
        MMPYF32		MR0,MR0,MR2								; MR0 = PFC_INVSQR_CLA_VminOverVmax / (satmin(AVG_ACLINE)*(pi/2))
        MMPYF32		MR0,MR0,MR0								; MR0 = MR0 * MR0
        
        MMINF32		MR0,#1.0         						; saturate to 1.0
                
        MMOV32		*MAR1,MR0
       
        ; Note: Uncomment the below MNOP's if you are using the net variable the macro writes to immidately
		; in CLA assembly code, this is for Read After write Protection(RAW)
		; if only using DPlib Macro block leave the MNOP's commented as indirect addressing which anyways use MNOP's
		; to load the auxillary register
		;MNOP
		;MNOP
		;MNOP
		 
_PFC_INVSQR_CLA_End:n:
	   	
		.endm


