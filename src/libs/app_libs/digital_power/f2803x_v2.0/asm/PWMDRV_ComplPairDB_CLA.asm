;------------------------------------------------------------------------------
;	FILE:			PWMDRV_ComplPairDB_CLA.inc
;
;	Description:	Single (A output) channel PWM driver macro using CLA 
;
;	Version: 		2.0
;
;   Target:  		CLA Type 0
;
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2007
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date         | Description
;--------------------------------------------------------------------------------
; 06/15/10		| Release 2.0  	 (MB)
;--------------------------------------------------------------------------------
;=================================
PWMDRV_ComplPairDB_CLA_INIT		.macro	n
;=================================
; Variable Declarations  
_PWMDRV_ComplPairDB_CLA_In:n:			.usect "PWMDRV_ComplPairDB_CLA_Section",2,1,1	; input terminal
_PWMDRV_ComplPairDB_CLA_DeadBandRED:n:	.usect "PWMDRV_ComplPairDB_CLA_Section",1,1,1	; internal data to store PWM deadband value 
_PWMDRV_ComplPairDB_CLA_DeadBandFED:n:	.usect "PWMDRV_ComplPairDB_CLA_Section",1,1,1	; internal data to store PWM deadband value 
    
;Publish Terminal Pointers for access from the C environment
;===========================================================
        .def 	_PWMDRV_ComplPairDB_CLA_In:n:
		.def 	_PWMDRV_ComplPairDB_CLA_DeadBandRED:n:
		.def 	_PWMDRV_ComplPairDB_CLA_DeadBandFED:n:               

        ; set terminal to point to ZeroNet            
        MOVL	XAR2, #ZeroNetCLA
        MOVW	DP, #_PWMDRV_ComplPairDB_CLA_In:n:
        MOVL	@_PWMDRV_ComplPairDB_CLA_In:n:, XAR2
              
        .endm

;=========================
PWMDRV_ComplPairDB_CLA		.macro	n
;=========================
_PWMDRV_ComplPairDB_CLA_DRV_Start:n:

        ; MAR0  =  Pointer to In:n:
        ; MR0   =  ePWM Period, Converted from Q15 to float
        ;          + 2 cycle delay for MAR0 load
        ;              
        MMOV16      MAR0, @_PWMDRV_ComplPairDB_CLA_In:n:
		MUI16TOF32  MR0,  @_EPwm:n:Regs.TBPRD
		MNOP   		; Cannot use MAR0
		MNOP
        ;
        ; MR1   = In:n: in Q24, convert to float
		;                
		MUI32TOF32  MR1, *MAR0
		MMPYF32     MR1, MR1, #1.0L/16777216.00L        
		;        
        ; MR1   = Multipy In:n: x TBPRD
		; MR2   = (Multipy In:n: x TBPRD)/2
        ; Convert back to Uint16 and output to CMPA
        ;    
        MMPYF32     MR1, MR0, MR1
		MMPYF32		MR2, MR1,#0.5L
		MF32TOUI16  MR1, MR1
		MF32TOUI16  MR2, MR2
		MMOV16      @_EPwm:n:Regs.CMPA.half.CMPA, MR1
		MMOV16		@_EPwm:n:Regs.CMPB, MR2
	
_PWMDRV_ComplPairDB_CLA_DRV_End:n:
    
    .endm
;=============================
PWMDRV_ComplPairDB_CLA_Update	.macro	n
;=============================
_PWMDRV_ComplPairDB_CLA_Update_Start:n:
		
		MMOVZ16 MR0, @_PWMDRV_ComplPairDB_CLA_DeadBandRED:n:
		
		MMOVZ16	MR1, @_PWMDRV_ComplPairDB_CLA_DeadBandFED:n:
		
		MEALLOW
		
		MMOV16	   @_EPwm:n:Regs.DBRED,MR0
		MMOV16     @_EPwm:n:Regs.DBFED,MR1
		
		MEDIS

_PWMDRV_ComplPairDB_CLA_Update_End:n:
		
	   .endm

; end of file
