;------------------------------------------------------------------------------
;	FILE:			PWMDRV_DualUpDwnCnt_CLA.inc
;
;	Description:	Single (A output) channel PWM driver macro using CLA 
;
;	Version: 		3.0
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
; 		| Release 3.0  	 (MB)
;--------------------------------------------------------------------------------
;=================================
PWMDRV_DualUpDwnCnt_CLA_INIT		.macro	n
;=================================
; Variable Declarations  
_PWMDRV_DualUpDwnCnt_CLA_Duty:n:A		.usect "PWMDRV_DualUpDwnCnt_CLA_Section",2,1,1	; Input Terminal 1
_PWMDRV_DualUpDwnCnt_CLA_Duty:n:B		.usect "PWMDRV_DualUpDwnCnt_CLA_Section",2,1,1	; Input Terminal 1
    
;Publish Terminal Pointers for access from the C environment
;===========================================================
        .def 	_PWMDRV_DualUpDwnCnt_CLA_Duty:n:A
		.def 	_PWMDRV_DualUpDwnCnt_CLA_Duty:n:B               

        ; set terminal to point to ZeroNet            
        MOVL	XAR2, #ZeroNetCLA
        MOVW	DP, #_PWMDRV_DualUpDwnCnt_CLA_Duty:n:A
        MOVL	@_PWMDRV_DualUpDwnCnt_CLA_Duty:n:A, XAR2
		MOVL	@_PWMDRV_DualUpDwnCnt_CLA_Duty:n:B, XAR2
              
        .endm

;=========================
PWMDRV_DualUpDwnCnt_CLA		.macro	n
;=========================
_PWMDRV_DualUpDwnCnt_CLA_DRV_Start:n:

        ; MAR0  =  Pointer to Duty:n:A
        ; MR0   =  ePWM Period, Converted from Q15 to float
        ;          + 2 cycle delay for MAR0 load
        ;              
        MMOV16      MAR0, @_PWMDRV_DualUpDwnCnt_CLA_Duty:n:A   
		MMOV16      MAR1, @_PWMDRV_DualUpDwnCnt_CLA_Duty:n:B   
        MUI16TOF32  MR0,  @_EPwm:n:Regs.TBPRD
		MNOP   		; Cannot use MAR0
        ;
        ; MR1   = Duty:n:A  float
		; MR2   = Duty:n:B  float
        ;                
		MMOV32  	MR1, *MAR0
		MMOV32  	MR2, *MAR1
		       
		;        
        ; MR1   = Duty:n:A x TBPRD
		; Convert back to Uint16 and output to CMPA
		MMPYF32     MR1, MR0, MR1
		MF32TOUI16  MR1, MR1
		MMOV16      @_EPwm:n:Regs.CMPA.half.CMPA, MR1
		
		; MR2   = (1-Duty:n:B)*TBPRD  
		; Convert back to Uint16 and output to CMPB
		MSUBF32		MR2,#1.0L,MR2
		MMPYF32     MR2, MR0, MR2
		MF32TOUI16  MR2, MR2
		MMOV16		@_EPwm:n:Regs.CMPB, MR2
	
_PWMDRV_DualUpDwnCnt_CLA_DRV_End:n:
    
    .endm
