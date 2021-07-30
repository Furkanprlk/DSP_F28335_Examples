;--------------------------------------------------------------------------------
;	FILE:			PWMDRV_PSFB_VMC_SR.asm
;
;	Description:	PWM driver macro for voltage mode control of a phase shifted 
;					full bridge with synchronous rectification support
;
;	Version: 		1.0
;
;   Target:  		TMS320F280xx
;
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2011
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;  05/04/11	| Release 1.0  		New release(HN)
;--------------------------------------------------------------------------------
;
;============================================================================
;	PWMDRV_PSFB_VMC_SR  n,m,p   Macro module driver
;============================================================================
;			______________________
;			| PWMDRV_PSFB_VMC_SR  |
;			|~~~~~~~~~~~~~~~~~~~~~|
;		 -->| phase		   EPWMnA |--> (Upper switch of legs with Active --> Passive transitions)
;		 -->| dbAtoP  	   EPWMnB |--> (Lower switch of legs with Active --> Passive transitions)
;		 -->| dbPtoA   	   EPWMmA |--> (Upper switch of legs with Passive --> Active transitions)
;		 	| 		   	   EPWMmB |--> (Lower switch of legs with Passive --> Active transitions)
;			|   	   	   EPWMpA |--> (SR-A switch. Note: SR switch PWM selections should be properly made based on the full bridge PWM selections)
;		 	| 		   	   EPWMpB |--> (SR-B switch. Note: SR switch PWM selections should be properly made based on the full bridge PWM selections)
;			|_____________________|

;
;	phase, dbAtoP, dbPtoA, are pointers to signal nets.
;
; Description:
; ------------
;	phase 	- phase relationship between EPWM(n) and EPWM(n+1)
;	dbAtoP	- Active to passive leg deadband time between A and B outputs
;	dbPtoA	- passive to active leg deadband time between A and B outputs
;
;=================================================================================
;=================================
PWMDRV_PSFB_VMC_SR_INIT	.macro	n,m,p
;=================================
; variable Declarations
_PWMDRV_PSFB_Phase:n:	.usect "PWMDRV_PSFB_Section",2,1,1	; Input Terminal 1, Phase
_PWMDRV_PSFB_DbAtoP:n: 	.usect "PWMDRV_PSFB_Section",2,1,1  ; Input Terminal 2, DbAtoP
_PWMDRV_PSFB_DbPtoA:n: 	.usect "PWMDRV_PSFB_Section",2,1,1  ; Input Terminal 3, DbPtoA

;Publish Terminal Pointers for access from the C environment
;===========================================================
		.def 	_PWMDRV_PSFB_Phase:n: 
		.def 	_PWMDRV_PSFB_DbAtoP:n:
		.def 	_PWMDRV_PSFB_DbPtoA:n:

; Set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNet
			MOVW	DP, #_PWMDRV_PSFB_Phase:n:
			MOVL	@_PWMDRV_PSFB_Phase:n:, XAR2
			MOVL	@_PWMDRV_PSFB_DbAtoP:n:, XAR2
			MOVL	@_PWMDRV_PSFB_DbPtoA:n:, XAR2
		
		.endm

;==========================
PWMDRV_PSFB_VMC_SR		.macro	n,m,p				; Note that PWMp time-base operates in up-down count mode
;==========================							; therefore TBPRDp = TBPRDm/2
; Phase Adjustment between the two legs
	   	MOVW 	DP, #_PWMDRV_PSFB_Phase:n:          ; Load DP for net pointer
       	MOVL   	XAR0, @_PWMDRV_PSFB_Phase:n:        ; Load net pointer address to XAR0
       	MOVL    XAR1, @_PWMDRV_PSFB_DbAtoP:n:
       	MOVL    XAR2, @_PWMDRV_PSFB_DbPtoA:n:  
       	MOVW    DP, #_EPwm:m:Regs.TBPRD           	; Load DP for EPWMPRDm Register, Note use Mirror register for 32 bit read
       	MOVL    XT,@_EPwm:m:Regs.TBPRD              ; Load XT  = PWM Period
		MOV 	TL,#0
       	QMPYL  	ACC,XT,*XAR0            			; ACC= (I8Q24) * (I16Q0) = (I24Q24): upper 32-bits -> ACC = (I24Q8)
       	LSL  	ACC,#7                          	; ACC<<7 --> I31Q1 (Includes divide by 2 of AH for phase register calculation)
       	MOV     @_EPwm:m:Regs.TBPHS.half.TBPHS,AH	; Maximum possible value of AH content after this calculation is TBPRDm/2 = TBPRDp
     	MOVW    DP, #_EPwm:p:Regs.TBPRD           	; Load DP for TBPRDp Register (SR)
       	MOV     @_EPwm:p:Regs.TBPHS.half.TBPHS,AH	; SR

		ADD		AH, *XAR2							; Add dbPtoA
		ADDB	AH,	#10								; Extra safety cycles
		CMP 	AH, @_EPwm:p:Regs.TBPRD				; CMP the value to be written to CMPBp with TBPRDp
		B		COMPB, LT							; if this value is > TBPRDp make it = TBPRDp				
		MOV		AH, @_EPwm:p:Regs.TBPRD
		MOVB 	AL,#0
		SUB	    ACC, #10<<15						; Subtract 5 from AL - safety margin that provides dead-band of 10 Clk cycles
													; between the two SR switches
COMPB:	MOV 	@_EPwm:p:Regs.CMPB,AH				; CMPBp = TBPHSp + dbPtoA + 10 = TBPHSm + dbPtoA + 10 
		MOV		AH,@_EPwm:p:Regs.TBPRD				
		SUB	    AH, @_EPwm:p:Regs.CMPB 				
		MOV 	@_EPwm:p:Regs.CMPA.half.CMPA,AH		; CMPAp = TBPRDp - CMPBp
	
; Deadband Adjustment for AtoP leg ePWM Module (module EPWM(n))
       	MOV		AL,*XAR1
       	MOVW	DP, #_EPwm:n:Regs.DBRED
       	MOV		@_EPwm:n:Regs.DBRED, AL
       	MOV		@_EPwm:n:Regs.DBFED, AL
       	
; Deadband Adjustment for PtoA leg ePWM Module (module EPWM(m))
       	MOV 	AL, *XAR2
       	MOVW	DP, #_EPwm:m:Regs.DBRED
       	MOV		@_EPwm:m:Regs.DBRED, AL
       	MOV		@_EPwm:m:Regs.DBFED, AL
		
		.endm

; end of file