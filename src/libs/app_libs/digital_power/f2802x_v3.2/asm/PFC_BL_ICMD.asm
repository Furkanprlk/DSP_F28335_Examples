;----------------------------------------------------------------------------------
;	FILE:			PFC_BL_ICMD.asm 
;
;	Description:	Current command Block for BL PFC 
;
;	Version: 		2.0
;
;   Target:  		C28x 
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;  08/19/10	| Release 1.1  		(DC)
;--------------------------------------------------------------------------------
;=============================
PFC_BL_ICMD_INIT	.macro	n
;=============================
; variable declarations
_PFC_BL_ICMD_Vcmd:n:				.usect "PFC_BL_ICMD_Section",2,1,1	; input terminal
_PFC_BL_ICMD_VinvSqr:n: 			.usect "PFC_BL_ICMD_Section",2,1,1	; output terminal
_PFC_BL_ICMD_VacRect:n:				.usect "PFC_BL_ICMD_Section",2,1,1
_PFC_BL_ICMD_Out:n:					.usect "PFC_BL_ICMD_Section",2,1,1
_PFC_BL_ICMD_VmaxOverVmin:n:		.usect "PFC_BL_ICMD_Section",2,1,1
_PFC_BL_ICMD_Vpfc:n:				.usect "PFC_BL_ICMD_Section",2,1,1
_PFC_BL_ICMD_Duty:n:				.usect "PFC_BL_ICMD_Section",2,1,1
_PFC_BL_ICMD_VoutMaxOverVinMax:n:	.usect "PFC_BL_ICMD_Section",2,1,1
PFC_BL_ICMD_temp:n:					.usect "PFC_BL_ICMD_Section",2,1,1

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PFC_BL_ICMD_Vcmd:n:
		.def	_PFC_BL_ICMD_VinvSqr:n:
		.def	_PFC_BL_ICMD_VacRect:n:
		.def 	_PFC_BL_ICMD_Out:n:
		.def 	_PFC_BL_ICMD_VmaxOverVmin:n:
		.def 	_PFC_BL_ICMD_Vpfc:n:
		.def 	_PFC_BL_ICMD_Duty:n:
		.def	_PFC_BL_ICMD_VoutMaxOverVinMax:n:

; set terminal pointer to ZeroNet
		MOVL	XAR2, #ZeroNet
		MOVW	DP, #_PFC_BL_ICMD_Vcmd:n:
		MOVL	@_PFC_BL_ICMD_Vcmd:n:, XAR2
		MOVL	@_PFC_BL_ICMD_VinvSqr:n:, XAR2
		MOVL	@_PFC_BL_ICMD_VacRect:n:, XAR2
		MOVL	@_PFC_BL_ICMD_Vpfc:n:, XAR2
		MOVL	@_PFC_BL_ICMD_Duty:n:, XAR2
;set internal data to zero
		ZAPA
		MOVL	@_PFC_BL_ICMD_VmaxOverVmin:n:,ACC
		MOVL	@_PFC_BL_ICMD_VoutMaxOverVinMax:n:,ACC
		MOVL	@PFC_BL_ICMD_temp:n:,ACC
		
		.endm

;-------------------------------------------------------------------------------------------
;=============================
PFC_BL_ICMD .macro	n
;=============================
		MOVW	DP, #_PFC_BL_ICMD_Vcmd:n:
		MOVL 	XAR0,@_PFC_BL_ICMD_VinvSqr:n:			; Net pointer to VinvSqr (XAR0)
		MOVL 	XAR1,@_PFC_BL_ICMD_VacRect:n:			; Net pointer to VacRect (XAR1)
		MOVL 	XAR2,@_PFC_BL_ICMD_Vcmd:n:				; Net pointer to Vcmd (XAR2)
		MOVL	XAR3,@_PFC_BL_ICMD_Out:n:
		MOVL	XAR4,@_PFC_BL_ICMD_Vpfc:n:
		MOVL	XAR5,@_PFC_BL_ICMD_Duty:n:
			
		MOVL	XT,*XAR0							; XT = VinvSqr Q24
		QMPYL	ACC,XT,*XAR1						; ACC = VinvSqr * VacRect = Q24* Q24 = I16Q48
		LSL		ACC,#8								; ACC = I8Q24
		MOVL	XT,@ACC								; XT = VinvSqr * VacRect (Q24)
		QMPYL	ACC,XT,*XAR2						; ACC = VinvSqr * VacRect * Vcmd
		LSL		ACC,#8								; ACC = I8Q24
		MOVL	XT,@ACC								; XT = VacRect * VinvSqr * Vcmd 
		QMPYL	ACC,XT,@_PFC_BL_ICMD_VmaxOverVmin:n:	; ACC = VacRect * VinvSqr * Vcmd * VmaxOverVmin
 		LSL		ACC,#8								; ACC = Q24
		MOVL	*XAR3,ACC							; Store result in output pointer location

	; Calculate (VacRect*VinvSqr*Vcmd*VmaxOverVmin)/(Vpfc*Duty)
		;MOVL	XT, *XAR4							; XT = Vpfc Q24
		;QMPYL	ACC,XT,*XAR5						; ACC = Vpfc*Duty = Q48 - Q32 = Q16
	;--------------------------------------------------------------------------------
		; Modified code in this portion. Calculate Vpfc*VoutMaxOverVinMax
		;Testing this section by commenting out the two lines above. (SAC)
		
		MOVL	XT, *XAR4							; XT = Vpfc, Q24
		QMPYL	ACC,XT,@_PFC_BL_ICMD_VoutMaxOverVinMax:n: ; ACC = Vpfc*VoutMaxOverVinMax, Q24*Q24 => Q48
													; ACC stores the higher 32bit of the 64bit product.
													; So ACC (32bit) is in Q16 (32 fractional bits dropped from 48 bits)
		LSL		ACC,#8								; ACC = Q24
		MOVL	XT, @ACC							;Vpfc*VoutMaxOverVinMax, Q24
		QMPYL	ACC,XT,*XAR5						; ACC = Vpfc*VoutMaxOverVinMax*Duty, Q48 (64b) => Q16 (32b)
	;--------------------------------------------------------
		
		;MOVL	XAR2, #200							;Testing a higher value of (Vpfc*VoutMaxOverVinMax*Duty)
		;MOVL    XAR2, #100
		MOVL	XAR2, #1023
		MAXL	ACC, @XAR2							;Set a non-zero min value of Vpfc*VoutMaxOverVinMax*Duty
													;before computing its inverse value
		
		MOVL	@PFC_BL_ICMD_temp:n:, ACC			; temp = Vpfc*VoutMaxOverVinMax*Duty = Q16
		MOV		AL,#0xFFFF
		MOV		AH,#0x7FFF
		MOVL 	P,ACC 								; Load P register with Num32 _IQ31(1.0)
		MOVB ACC,#0 								; Zero ACC
		RPT #31 									; Repeat operation 32 times
		||SUBCUL ACC,@PFC_BL_ICMD_temp:n:			; Conditional subtract with Den32
		MOVL	ACC,@P								; move quotient to ACC register
		LSL		ACC,#9								; shift quotient in Q15 by 9 to get Q24, 1/(Vpfc*VoutMaxOverVinMax*Duty)
		;LSL		ACC,#6								; shift quotient in Q15 by 6 to get Q21, 1/(Vpfc*VoutMaxOverVinMax*Duty)
		
		MOVL	XT, @ACC							; XT = 1/(Vpfc*VoutMaxOverVinMax*Duty), Q24
		QMPYL	ACC,XT,*XAR3						; ACC = (VacRect*VinvSqr*Vcmd*VmaxOverVmin)/(Vpfc*VoutMaxOverVinMax*Duty) = Q48 (64b) => Q16 (32b)
		LSL		ACC,#8								; ACC = Q24
		;LSL		ACC,#11								; ACC = Q24
		MOVL	@PFC_BL_ICMD_temp:n:, ACC			; temp = (VacRect*VinvSqr*Vcmd*VmaxOverVmin)/(Vpfc*VoutMaxOverVinMax*Duty), Q24

	; Calculate Vpfc*VoutMaxOverVinMax
		MOVL	XT, *XAR4							; XT = Vpfc
		QMPYL	ACC,XT,@_PFC_BL_ICMD_VoutMaxOverVinMax:n: ; ACC = Vpfc*VoutMaxOverVinMax = Q48 (64b)=> Q16 (32b)
		LSL		ACC,#8								; ACC = Q24
		
	; Calculate [(VacRect*VinvSqr*Vcmd*VmaxOverVmin)/(Vpfc*Duty)]*(Vpfc*VoutMaxOverVinMax - Vin)
		SUBL	ACC, *XAR1							; ACC = (Vpfc*VoutMaxOverVinMax - Vin), Q24
		
		MOVB	XAR2, #0							;Correction by MB/SAC\Sept23
		MAXL	ACC, @XAR2							;Correction by MB/SAC\Sept23
		
		MOVL	XT, ACC								; XT = (Vpfc*VoutMaxOverVinMax - Vin), Q24
	
		
		QMPYL	ACC,XT,@PFC_BL_ICMD_temp:n:			; ACC = [(VacRect*VinvSqr*Vcmd*VmaxOverVmin)/(Vpfc*VoutMaxOverVinMax*Duty)]*(Vpfc*VoutMaxOverVinMax - Vin) = Q48 - Q32 = Q16
		LSL		ACC,#8								; ACC = Q24

		MOVL	*XAR3,ACC							; Store result in output pointer location
		.endm

; end of file
