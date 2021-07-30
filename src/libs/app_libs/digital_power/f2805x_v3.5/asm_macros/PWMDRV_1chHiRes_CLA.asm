;------------------------------------------------------------------------------
;	FILE:			PWMDRV_1chHiRes_CLA.asm
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
PWMDRV_1chHiRes_CLA_INIT		.macro	n
;=================================
; Variable Declarations     
_PWMDRV_1chHiRes_CLA_Duty:n:		.usect "PWMDRV_1chHiRes_CLA_Section",2,1,1	; Input Terminal 1
    
;Publish Terminal Pointers for access from the C environment
;===========================================================
        .def 	_PWMDRV_1chHiRes_CLA_Duty:n:               

        ; set terminal to point to ZeroNet
            
        MOVL	XAR2, #ZeroNetCLA
        MOVW	DP, #_PWMDRV_1chHiRes_CLA_Duty:n:
        MOVL	@_PWMDRV_1chHiRes_CLA_Duty:n:, XAR2
              
        .endm
;--------------------------------------------------------------------------------
;=========================
PWMDRV_1chHiRes_CLA		.macro	n
;=========================
_PWMDRV_1chHiRes_CLA_DRV_Start:n:

        ; MAR0  =  Pointer to InA
        ; MR0   =  ePWM Period, Converted from Q15 to float
        ;          + 2 cycle delay for MAR0 load
        ;              
        MMOV16      MAR0, @_PWMDRV_1chHiRes_CLA_Duty:n:   
        MUI16TOF32  MR0,  @_EPwm:n:Regs.TBPRD
		MNOP   
		MNOP    
        ;
        ; MR1   = InA infloat
                        
		MMOV32  	MR1, *MAR0
				      
		;        
        ; CMPA= MR0   = Multipy InA x TBPRD
        ; CMPB = 1/2 *CMPA   
        MMPYF32     MR0, MR0, MR1
        ; As CMPA is shifted by 16 bits, multiply by 2^16 =
		MMPYF32		MR1,MR0,#65536.0L
		MMPYF32		MR0,MR0,#0.5L 	
		
		MF32TOI32   MR1, MR1
		MF32TOUI16   MR0, MR0
		
		MMOV32		@_EPwm:n:Regs.CMPA.all, MR1
		
		MMOV16		@_EPwm:n:Regs.CMPB, MR0
		
	
_PWMDRV_1chHiRes_CLA_DRV_End:n:
    
    .endm
