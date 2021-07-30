;----------------------------------------------------------------------------------
;	FILE:			CNTL_3P3Z_CLA.asm
;
;	Description:	3rd Order Control Law Macro Module
;
;	Version: 		3.0
;
;   Target:  		CLA Type 0
;
;----------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;----------------------------------------------------------------------------------
;  Revision History:
;----------------------------------------------------------------------------------
;  Date	     | Description
;----------------------------------------------------------------------------------
;    | Release 3.0  (MB)
;----------------------------------------------------------------------------------
;====================================
CNTL_3P3Z_CLA_INIT	.macro n
;==================================== 
_CNTL_3P3Z_CLA_Ref:n:	.usect "CNTL_3P3Z_CLA_Section",2,1,1		; Ref pointer 
_CNTL_3P3Z_CLA_Fdbk:n:	.usect "CNTL_3P3Z_CLA_Section",2,1,1		; Fdbk pointer
_CNTL_3P3Z_CLA_Out:n:	.usect "CNTL_3P3Z_CLA_Section",2,1,1		; Output pointer
_CNTL_3P3Z_CLA_Coef:n:	.usect "CNTL_3P3Z_CLA_Section",2,1,1 		; Coefficient pointer
  
_CNTL_3P3Z_CLA_DBUFF:n: 	.usect "CNTL_3P3Z_CLA_InternalData",14,1,1   	; "Local" memory (history) 

;Publish Terminal Pointers for access from the C environment 
					.def 	_CNTL_3P3Z_CLA_Ref:n:
					.def 	_CNTL_3P3Z_CLA_Fdbk:n:
					.def 	_CNTL_3P3Z_CLA_Out:n:
					.def 	_CNTL_3P3Z_CLA_Coef:n:
					.def    _CNTL_3P3Z_CLA_DBUFF:n:

		; set terminal to point to ZeroNet
			MOVL	XAR2, #ZeroNetCLA
			MOVW	DP, #_CNTL_3P3Z_CLA_Ref:n:
			MOVL	@_CNTL_3P3Z_CLA_Ref:n:,  XAR2
			MOVL	@_CNTL_3P3Z_CLA_Fdbk:n:, XAR2
			MOVL	@_CNTL_3P3Z_CLA_Coef:n:, XAR2
	.endm
;--------------------------------------------------------------------------------
;====================================
CNTL_3P3Z_CLA		.macro n
;====================================
_ControlLaw_3P3Z_Start:n:	

        ; MAR0  = points to reference
        ; MAR1  = points to feedback
        ;        + 2 delay cycles for MARx load 
        MMOV16  MAR0, @_CNTL_3P3Z_CLA_Ref:n:  
        MMOV16  MAR1, @_CNTL_3P3Z_CLA_Fdbk:n: 
        MNOP  
        MNOP   
        
		; MR0   = reference 
        ; MR1   = feedback  (ADC)
        MMOV32 MR0, *MAR0
		MMOV32 MR1, *MAR1
		
		; load coefficients pointer into MAR0
        MMOV16     MAR0,@_CNTL_3P3Z_CLA_Coef:n:      
        
        ; MR0   = reference - feedback
		MSUBF32    MR0, MR0, MR1					;I1               
		 
        ; Store error in DBuff[3]      
        MMOV32     @_CNTL_3P3Z_CLA_DBUFF:n:+6, MR0	; I2 cannot use MAR0
           
		; MR0   = e(n-3)
		MMOV32     MR0, @_CNTL_3P3Z_CLA_DBUFF:n:+12	; I3 cannot use MAR0
		; MR1   = B3
        MMOV32     MR1, *MAR0[#2]++
		; MR3   = B3 * e(n-3) || MR1   = B2
        MMPYF32    MR3, MR0, MR1
     || MMOV32     MR1, *MAR0[#2]++  
        
        
		; MR0   = e(n-2)  and e(n-3) = e(n-2)
        MMOVD32    MR0, @_CNTL_3P3Z_CLA_DBUFF:n:+10        
		; MR2   = B2 * e(n-2) || MR1   = B1
        MMPYF32    MR2, MR0, MR1        
     || MMOV32     MR1, *MAR0[#2]++     
        
        ; MR0   = e(n-1)  and e(n-2) = e(n-1)
        MMOVD32    MR0, @_CNTL_3P3Z_CLA_DBUFF:n:+8
		; MR2   = B1 * e(n-1) || MR3 = B3*e(n-3) + B2*e(n-2)        
        MMPYF32    MR2, MR1, MR0   
     || MADDF32    MR3, MR3, MR2
        
        ; MR0   = e(n)  and e(n-1) = e(n)
        MMOVD32     MR0, @_CNTL_3P3Z_CLA_DBUFF:n:+6
		; MR1   = B0
        MMOV32     MR1, *MAR0[#2]++
		; MR2   = B0 * e(n) || MR3   = B3*e(n-3)+B2*e(n-2)+B1*e(n-1)
        MMPYF32    MR2, MR0, MR1
     || MADDF32    MR3, MR3, MR2     
        
        ; MR0   = u(n-3) 
        MMOV32    MR0, @_CNTL_3P3Z_CLA_DBUFF:n:+4
		; MR1   = A3
        MMOV32     MR1, *MAR0[#2]++        
		; MR2   = u(n-3)*A3	|| MR3   = B3*e(n-3)+B2*e(n-2)+B1*e(n-1)+B0*e(n)
        MMPYF32    MR2, MR0, MR1
     || MADDF32    MR3, MR3, MR2
        
        ; MR0   = u(n-2) and u(n-3) = u(n-2) 
        MMOVD32    MR0, @_CNTL_3P3Z_CLA_DBUFF:n:+2
		; MR1   = A2
        MMOV32     MR1, *MAR0[#2]++        
		; MR2   = u(n-2)*A2	|| MR3   = B3*e(n-3)+B2*e(n-2)+B1*e(n-1)+B0*e(n)+A3*u(n-3)
        MMPYF32    MR2, MR0, MR1
     || MADDF32    MR3, MR3, MR2
	 
		; MR0   = u(n-1) and u(n-2) = u(n-1) 
        MMOVD32    MR0, @_CNTL_3P3Z_CLA_DBUFF:n:+1
		; MR1   = A1
        MMOV32     MR1, *MAR0[#2]++        
		; MR2   = u(n-1)*A1	|| MR3   = B3*e(n-3)+B2*e(n-2)+B1*e(n-1)+B0*e(n)+A3*u(n-3)+A2*u(n-2)
        MMPYF32    MR2, MR0, MR1
     || MADDF32    MR3, MR3, MR2
	 
		; MAR1  = pointer to the output
        MMOV16     MAR1, @_CNTL_3P3Z_CLA_Out:n:
		
        ; MR3   = B3*e(n-3)+B2*e(n-2)+B1*e(n-1)+B0*e(n)+A3*u(n-3)+A2*u(n-2)+A1*u(n-1)
        MADDF32    MR3, MR3, MR2               ; 1
		
        ;MR1 = Satmax
		MMOV32     MR1, *MAR0[#2]++
		;MR2 = Satmin
		MMOV32     MR2, *MAR0[#2]++
		
		; Check for limits 
        MMINF32    MR3,  MR1                  
        MMAXF32    MR3,  MR2                    
		
		; store result 
        MMOV32     *MAR1[#0]++, MR3  
        
        ; store u(n)
        MMOV32     @_CNTL_3P3Z_CLA_DBUFF:n:+0, MR3
                	
	    ; Note: Uncomment the below MNOP's if you are using the net variable the macro writes to immidately
		; in CLA assembly code, this is for Read After write Protection(RAW)
		; if only using DPlib Macro block leave the MNOP's commented as indirect addressing which anyways use MNOP's
		; to load the auxillary register
		;MNOP
		;MNOP        
             
_ControlLaw_3P3Z_End:n:
 .endm
;--------------------------------------------------------------------------------
;====================================
CNTL_3P3Z_DBUFF_CLA_INIT	.macro n
;====================================
; Initialize the CLA writable DATA buffer
_ControlLaw_3P3Z_DBUFF_CLA_INIT_START:n:
    MSETFLG      RNDF32=1
    MMOVIZ       MR0, #0.0         
    MMOV32       @_CNTL_3P3Z_CLA_DBUFF:n:+0, MR0       
    MMOV32       @_CNTL_3P3Z_CLA_DBUFF:n:+2, MR0       
    MMOV32       @_CNTL_3P3Z_CLA_DBUFF:n:+4, MR0
    MMOV32       @_CNTL_3P3Z_CLA_DBUFF:n:+6, MR0    
    MMOV32       @_CNTL_3P3Z_CLA_DBUFF:n:+8, MR0
	MMOV32       @_CNTL_3P3Z_CLA_DBUFF:n:+10, MR0
	MMOV32       @_CNTL_3P3Z_CLA_DBUFF:n:+12, MR0
_ControlLaw_3P3Z_DBUFF_CLA_INIT_END:n:

    .endm
