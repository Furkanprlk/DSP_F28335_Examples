;---------------------------------------------------------------------------------
;	FILE:			PFC_ICMD_CLA.asm
;
;	Description:	Current command Block for PFC 
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
;  06/15/10	| Release 2.0  		(MB)
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

		MMOV16  	MAR0, @_PFC_ICMD_CLA_Vcmd:n:			; I1         
        MMOV16  	MAR1, @_PFC_ICMD_CLA_VinvSqr:n:			; I2         
        MMOV32		MR3,  @_PFC_ICMD_CLA_VmaxOverVmin:n:   	; I3    
        MNOP  												; can not use MAR0    
		; Load MR0 with Voltage Command i.e. Vcmd
		MI32TOF32	MR0, *MAR0				
		MMOV16  	MAR0, @_PFC_ICMD_CLA_VacRect:n:		;         

		;  Convert Vcmd to per-unit float from Q24 [1/(2^24)]      
        MMPYF32    	MR0, MR0, #(1.0L/16777216.0L)  

		; Load MR 1 with VinvSqr
		MI32TOF32	MR1, *MAR1					

		; Convert  VinvSqr to per-unit float from Q24[1/(2^24)]      
        MMPYF32    	MR1, MR1, #(1.0L/16777216.0L)  

		MMOV16  	MAR1, @_PFC_ICMD_CLA_Out:n:		      
		
		; Load MR2 with the VacRect
		MI32TOF32	MR2, *MAR0								
		; Convert VacRect to per unit float from Q24[1/(2^24)]
        MMPYF32    	MR2, MR2, #(1.0L/16777216.0L)        
		
		MMPYF32		MR0, MR0, MR1					;V1 * V2
		MMPYF32		MR0, MR0, MR2					;V1 * V2 * Vac
		
		MMPYF32		MR0, MR0,MR3					;  
		; Convert to Q24
        MMPYF32    	MR0, MR0, #16777216.0L			; [(2^24)] 
      	MF32TOI32 	MR0, MR0               
   		MMOV32     	*MAR1, MR0		;NetTerminal Output [Q24] _PFC_ICMD_CLA_Out:n:
   		
_PFC_ICMD_CLA_End:n:
	   	
		.endm


