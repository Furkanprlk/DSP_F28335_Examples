;------------------------------------------------------------------------------
;	FILE:			PWMDRV_1chHiRes_CLA.inc
;
;	Description:	Single (A output) channel PWM driver macro using CLA 
;
;	Version: 		2.0
;
;   Target:  		CLA Type 1
;
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2007
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date         | Description
;--------------------------------------------------------------------------------
;  06/15/10     | Release 2.0  	 (MB)
;--------------------------------------------------------------------------------
;=================================
PWMDRV_1chHiRes_CLA_INIT		.macro	n
;=================================
; Variable Declarations     
_PWMDRV_1chHiRes_CLA_In:n:		.usect "PWMDRV_1chHiRes_CLA_Section",2,1,1	; Input Terminal 1
    
;Publish Terminal Pointers for access from the C environment
;===========================================================
        .def 	_PWMDRV_1chHiRes_CLA_In:n:               

        ; set terminal to point to ZeroNet
            
        MOVL	XAR2, #ZeroNetCLA
        MOVW	DP, #_PWMDRV_1chHiRes_CLA_In:n:
        MOVL	@_PWMDRV_1chHiRes_CLA_In:n:, XAR2
              
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
        MMOV16      MAR0, @_PWMDRV_1chHiRes_CLA_In:n:   
        MUI16TOF32  MR0,  @_EPwm:n:Regs.TBPRD
		MNOP   
		MNOP    
        ;
        ; MR1   = InA in Q24, convert to float
        ; as the result is desired to be shifted by 16 bits for a 32 bit write
        ; scale by 2^16/2^24                
		MUI32TOF32  MR1, *MAR0
		MMPYF32     MR1, MR1,#1.0L/256.00L   ; 2^16/2^24= 1/256   
		      
		;        
        ; MR0   = Multipy InA x TBPRD
        ; Convert back to Uint16 and output to CMPA
        ; CMPB = 1/2 *CMPA   
        MMPYF32     MR0, MR0, MR1
        ; As CMPA is shifted by 16 bits, scale down by (1/2^16) *(1/2)= 1/131072
		MMPYF32		MR1,MR0,#1.0L/131072.0L 	
		
		MF32TOI32   MR0, MR0
		MF32TOUI16   MR1, MR1
		
		MMOV32		@_EPwm:n:Regs.CMPA.all, MR0
		
		MMOV16		@_EPwm:n:Regs.CMPB, MR1
		
	
_PWMDRV_1chHiRes_CLA_DRV_End:n:
    
    .endm
