;------------------------------------------------------------------------------
;	FILE:			PWMDRV_LLC_ComplPairDB_CLA.asm
;
;	Description:	Single (A output) channel PWM driver macro using CLA 
;
;	Version: 		
;
;   Target:  		CLA Type 0
;
;--------------------------------------------------------------------------------
;   Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
;   ALL RIGHTS RESERVED
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date         | Description
;--------------------------------------------------------------------------------
;--------------------------------------------------------------------------------
;=================================
PWMDRV_LLC_ComplPairDB_CLA_INIT		.macro	n
;=================================
; Variable Declarations  
_PWMDRV_LLC_ComplPairDB_CLA_Duty:n:			.usect "PWMDRV_LLC_ComplPairDB_CLA_Section",2,1,1	; input terminal for PWM duty percentage
_PWMDRV_LLC_ComplPairDB_CLA_Period:n:		.usect "PWMDRV_LLC_ComplPairDB_CLA_Section",2,1,1	; input terminal for PWM period value
_PWMDRV_LLC_ComplPairDB_CLA_DeadBandRED:n:	.usect "PWMDRV_LLC_ComplPairDB_CLA_Section",1,1,1	; internal data to store PWM deadband value 
_PWMDRV_LLC_ComplPairDB_CLA_DeadBandFED:n:	.usect "PWMDRV_LLC_ComplPairDB_CLA_Section",1,1,1	; internal data to store PWM deadband value 
    
;Publish Terminal Pointers for access from the C environment
;===========================================================
        .def 	_PWMDRV_LLC_ComplPairDB_CLA_Duty:n:
        .def 	_PWMDRV_LLC_ComplPairDB_CLA_Period:n:
		.def 	_PWMDRV_LLC_ComplPairDB_CLA_DeadBandRED:n:
		.def 	_PWMDRV_LLC_ComplPairDB_CLA_DeadBandFED:n:               

        ; set terminal to point to ZeroNet            
        MOVL	XAR2, #ZeroNetCLA
        MOVW	DP, #_PWMDRV_LLC_ComplPairDB_CLA_Duty:n:
        MOVL	@_PWMDRV_LLC_ComplPairDB_CLA_Duty:n:, XAR2
        MOVL 	@_PWMDRV_LLC_ComplPairDB_CLA_Period:n:, XAR2
              
        .endm

;=========================
PWMDRV_LLC_ComplPairDB_CLA		.macro	n
;=========================
_PWMDRV_LLC_ComplPairDB_CLA_DRV_Start:n:

        ; MAR0  =  Pointer to In:n:
        ; MR0   =  ePWM Period, Converted from Q15 to float
        ;          + 2 cycle delay for MAR0 load
        ;              
        MMOV16 		MAR0, @_PWMDRV_LLC_ComplPairDB_CLA_Period:n:
        MMOV16      MAR1, @_PWMDRV_LLC_ComplPairDB_CLA_Duty:n:
		MNOP   		; Cannot use MAR0
		MNOP		
        ;
        ; MR1   = In:n: 
		;                
		MMOV32 	MR0, *MAR0
		MMOV32  MR1, *MAR1
		;        
        ; MR1   = Multipy In:n: x TBPRD
		; MR2   = (Multipy In:n: x TBPRD)/2
        ; Convert back to Uint16 and output to CMPA
        ;
        MMPYF32 	MR0, MR0, #1024.0L
        MMPYF32     MR1, MR0, MR1
		MMPYF32		MR2, MR1, #0.5L
		MF32TOUI16  MR1, MR1
		MF32TOUI16  MR2, MR2
		MF32TOUI16 	MR0, MR0
		MMOV16 		@_EPwm:n:Regs.TBPRD, MR0
		MMOV16      @_EPwm:n:Regs.CMPA.half.CMPA, MR1
		MMOV16		@_EPwm:n:Regs.CMPB, MR2
	
_PWMDRV_LLC_ComplPairDB_CLA_DRV_End:n:
    
    .endm
;=============================
PWMDRV_LLC_ComplPairDB_CLA_Update	.macro	n
;=============================
_PWMDRV_LLC_ComplPairDB_CLA_Update_Start:n:
		
		MMOVZ16 MR0, @_PWMDRV_LLC_ComplPairDB_CLA_DeadBandRED:n:
		
		MMOVZ16	MR1, @_PWMDRV_LLC_ComplPairDB_CLA_DeadBandFED:n:
		
		MEALLOW
		
		MMOV16	   @_EPwm:n:Regs.DBRED,MR0
		MMOV16     @_EPwm:n:Regs.DBFED,MR1
		
		MEDIS

_PWMDRV_LLC_ComplPairDB_CLA_Update_End:n:
		
	   .endm

; end of file
