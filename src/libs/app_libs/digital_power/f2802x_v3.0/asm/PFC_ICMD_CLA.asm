;---------------------------------------------------------------------------------
;	FILE:			PFC_ICMD_CLA.asm
;
;	Description:	Current command Block for PFC 
;
;	Version: 		3.0
;
;   Target:  		CLA Type 0
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
; 	| Release 3.0  		(MB)
;--------------------------------------------------------------------------------
;=============================
PFC_ICMD_CLA_INIT	.macro	n
;=============================
; variable Declarations
_PFC_ICMD_CLA_Vcmd:n:			.usect "PFC_ICMD_CLA_Section",2,1,1	; Input Terminal 1, pointer to voltage command variable 
_PFC_ICMD_CLA_VinvSqr:n: 		.usect "PFC_ICMD_CLA_Section",2,1,1 ; Input Terminal 2, pointer to 
_PFC_ICMD_CLA_VacRect:n:		.usect "PFC_ICMD_CLA_Section",2,1,1 ; Input Terminal 3, Vac
_PFC_ICMD_CLA_Out:n:			.usect "PFC_ICMD_CLA_Section",2,1,1
_PFC_ICMD_CLA_VmaxOverVmin:n:	.usect "PFC_ICMD_CLA_InternalData",2,1,1

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PFC_ICMD_CLA_Vcmd:n: 
		.def 	_PFC_ICMD_CLA_VinvSqr:n:
		.def 	_PFC_ICMD_CLA_VacRect:n:
		.def	_PFC_ICMD_CLA_Out:n:
		.def 	_PFC_ICMD_CLA_VmaxOverVmin:n:
		 
		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNetCLA
			MOVW	DP, #_PFC_ICMD_CLA_Vcmd:n:
			MOVL	@_PFC_ICMD_CLA_VinvSqr:n:, XAR2
			MOVL	@_PFC_ICMD_CLA_VacRect:n:, XAR2
			MOVL	@_PFC_ICMD_CLA_Out:n:,XAR2
					
		.endm
;--------------------------------------------------------------------------------
;======================
PFC_ICMD_CLA			.macro	n
;======================
					
_PFC_ICMD_CLA_Start:n:

		MMOV16  	MAR0, @_PFC_ICMD_CLA_Vcmd:n:			;          
        MMOV16  	MAR1, @_PFC_ICMD_CLA_VinvSqr:n:			; I1         				
        MMOV32		MR3,  @_PFC_ICMD_CLA_VmaxOverVmin:n:   	; I2    				I1
        MNOP  												; I3 can not use MAR0   I2 
		; Load MR0 with Voltage Command i.e. Vcmd
		MMOV32		MR0, *MAR0								;						I3 cannot use MAR1
		MMOV16  	MAR0, @_PFC_ICMD_CLA_VacRect:n:		

		; Load MR 1 with VinvSqr
		MMOV32		MR1, *MAR1								;I1					

		MMOV16  	MAR1, @_PFC_ICMD_CLA_Out:n:		        ;I2
		MMPYF32		MR0, MR0, MR1							;I3 cannot use MAR0		MR0=Vcmd * Vinvsqr 	
		
		; Load MR2 with the VacRect
		MMOV32		MR2, *MAR0								;MR2=VacRect 
		
		MMPYF32		MR0, MR0, MR2					;Vcmd * Vinvsqr * Vac
		MMPYF32		MR0, MR0,MR3					;Vcmd * Vinvsqr * Vac * VmaxOverVmin
   
   		MMOV32     	*MAR1, MR0						; Store NetTerminal Output 
   		
   		; Note: Uncomment the below MNOP's if you are using the net variable the macro writes to immidately
		; in CLA assembly code, this is for Read After write Protection(RAW)
		; if only using DPlib Macro block leave the MNOP's commented as indirect addressing which anyways use MNOP's
		; to load the auxillary register
		;MNOP
		;MNOP
		;MNOP
   		
_PFC_ICMD_CLA_End:n:
	   	
		.endm


