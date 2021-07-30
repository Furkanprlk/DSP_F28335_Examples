;----------------------------------------------------------------------------------
;	FILE:			PFC_ICMD.asm 
;
;	Description:	Current command Block for PFC 
;
;	Version: 		3.0
;
;   Target:  		C28x 
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
PFC_ICMD_INIT	.macro	n
;=============================
; variable declarations
_PFC_ICMD_Vcmd:n:				.usect "PFC_ICMD_Section",2,1,1	; input terminal
_PFC_ICMD_VinvSqr:n: 			.usect "PFC_ICMD_Section",2,1,1	; output terminal
_PFC_ICMD_VacRect:n:			.usect "PFC_ICMD_Section",2,1,1
_PFC_ICMD_Out:n:				.usect "PFC_ICMD_Section",2,1,1
_PFC_ICMD_VmaxOverVmin:n:		.usect "PFC_ICMD_Section",2,1,1

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PFC_ICMD_Vcmd:n:
		.def	_PFC_ICMD_VinvSqr:n:
		.def	_PFC_ICMD_VacRect:n:
		.def 	_PFC_ICMD_Out:n:
		.def 	_PFC_ICMD_VmaxOverVmin:n:

; set terminal pointer to ZeroNet
		MOVL	XAR2, #ZeroNet
		MOVW	DP, #_PFC_ICMD_Vcmd:n:
		MOVL	@_PFC_ICMD_Vcmd:n:, XAR2
		MOVL	@_PFC_ICMD_VinvSqr:n:, XAR2
		MOVL	@_PFC_ICMD_VacRect:n:, XAR2
;set internal data to zero
		ZAPA
		MOVL	@_PFC_ICMD_VmaxOverVmin:n:,ACC
		
		.endm

;-------------------------------------------------------------------------------------------
;=============================
PFC_ICMD .macro	n
;=============================
	   MOVW		DP, #_PFC_ICMD_Vcmd:n:
	   MOVL 	XAR0,@_PFC_ICMD_VinvSqr:n:			; Net pointer to VinvSqr (XAR0)
	   MOVL 	XAR1,@_PFC_ICMD_VacRect:n:			; Net pointer to VacRect (XAR1)
	   MOVL 	XAR2,@_PFC_ICMD_Vcmd:n:				; Net pointer to Vcmd (XAR2)
	   MOVL		XAR3,@_PFC_ICMD_Out:n:
	   MOVL		XT,*XAR0							; XT = VinvSqr Q24
	   QMPYL	ACC,XT,*XAR1						; ACC = VinvSqr * VacRect = Q24* Q24 = I16Q48
	   LSL		ACC,#8							; ACC = I8Q24
	   MOVL		XT,@ACC								; XT = VinvSqr * VacRect (Q24)
	   QMPYL	ACC,XT,*XAR2						; ACC = VinvSqr * VacRect * Vcmd
	   LSL		ACC,#8							; ACC = I8Q24
	   MOVL		XT,@ACC								; XT = VacRect * VinvSqr * Vcmd 
	   QMPYL	ACC,XT,@_PFC_ICMD_VmaxOverVmin:n:	; ACC = VacRect * VinvSqr * Vcmd * VmaxOverVmin
	   LSL		ACC,#8							; ACC = Q24
	   MOVL		*XAR3,ACC							; Store result in output pointer location
	   
	   .endm

; end of file

