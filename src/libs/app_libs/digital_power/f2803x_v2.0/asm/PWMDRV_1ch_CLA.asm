;------------------------------------------------------------------------------
;	FILE:			PWMDRV_1ch_CLA.inc
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
PWMDRV_1ch_CLA_INIT		.macro	n
;=================================
; Variable Declarations  
_PWMDRV_1ch_CLA_In:n:		.usect "PWMDRV_1ch_CLA_Section",2,1,1	; Input Terminal 1
    
;Publish Terminal Pointers for access from the C environment
;===========================================================
        .def 	_PWMDRV_1ch_CLA_In:n:               

        ; set terminal to point to ZeroNet            
        MOVL	XAR2, #ZeroNetCLA
        MOVW	DP, #_PWMDRV_1ch_CLA_In:n:
        MOVL	@_PWMDRV_1ch_CLA_In:n:, XAR2
              
        .endm

;=========================
PWMDRV_1ch_CLA		.macro	n
;=========================
_PWMDRV_1ch_CLA_DRV_Start:n:

        ; MAR0  =  Pointer to InA
        ; MR0   =  ePWM Period, Converted from Q15 to float
        ;          + 2 cycle delay for MAR0 load
        ;              
        MMOV16      MAR0, @_PWMDRV_1ch_CLA_In:n:   
        MUI16TOF32  MR0,  @_EPwm:n:Regs.TBPRD
		MNOP   
		MNOP    
        ;
        ; MR1   = InA in Q24, convert to float
        ;                
		MUI32TOF32  MR1, *MAR0
		MMPYF32     MR1, MR1, #1.0L/16777216.00L   
		      
		;        
        ; MR0   = Multipy InA x TBPRD
        ; Convert back to Uint16 and output to CMPA
        ;    
        MMPYF32     MR0, MR0, MR1
		MMPYF32		MR1,MR0,#0.5L
		MF32TOUI16  MR0, MR0
		MF32TOUI16	MR1,MR1

		MMOV16      @_EPwm:n:Regs.CMPA.half.CMPA, MR0
		MMOV16		@_EPwm:n:Regs.CMPB, MR1
	
_PWMDRV_1ch_CLA_DRV_End:n:
    
    .endm
