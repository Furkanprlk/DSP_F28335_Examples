;----------------------------------------------------------------------------------
;	FILE:			DLOG_1ch.asm
;
;	Description:	Single channel data logger
;
;	Version: 		3.0
;
;   Target:  		F2802x / F2803x / F2806x
;
;--------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;    | Release 3.0  		New release
;--------------------------------------------------------------------------------
;=============================
DLOG_1ch_INIT	.macro	n
;=============================
; allocate memory space for data & terminal pointers
_DLOG_1ch_Input:n:		.usect "DLOG_1ch_Section",2,1,1
_DLOG_1ch_OutputBuff:n:	.usect "DLOG_1ch_Section",2,1,1
_DLOG_1ch_TrigVal:n:	.usect "DLOG_1ch_Section",2,1,1	
_DLOG_1ch_CurrTask:n:	.usect "DLOG_1ch_Section",2,1,1
_DLOG_1ch_PreScalar:n:	.usect "DLOG_1ch_Section",1,1,1	
_DLOG_1ch_Size:n:		.usect "DLOG_1ch_Section",1,1,1
_DLOG_1ch_Cnt:n:		.usect "DLOG_1ch_Section",1,1,1
_DLOG_1ch_SkipCnt:n:	.usect "DLOG_1ch_Section",1,1,1

;Publish Terminal Pointers for access from the C environment
		.def 	_DLOG_1ch_Input:n:
		.def 	_DLOG_1ch_OutputBuff:n:
		.def 	_DLOG_1ch_TrigVal:n:
		.def 	_DLOG_1ch_PreScalar:n:
		.def 	_DLOG_1ch_Size:n:
						
; set terminal pointer to ZeroNet
		MOVL	XAR2, #ZeroNet
		MOVW	DP, #_DLOG_1ch_Input:n:
		MOVL	@_DLOG_1ch_Input:n:, XAR2
				
;set internal data to zero
		ZAPA
		MOVL	@_DLOG_1ch_TrigVal:n:,ACC
		MOV		@_DLOG_1ch_PreScalar:n:,AL
		MOV		@_DLOG_1ch_Size:n:,AL
		MOV		@_DLOG_1ch_Cnt:n:,AL
		MOV		@_DLOG_1ch_SkipCnt:n:,AL
		
;reset the data log to wait for trigger
		MOVL	XAR0,#WAIT_FOR_TRIGGER:n:
		MOVL	@_DLOG_1ch_CurrTask:n:,XAR0
		
		.endm

;-------------------------------------------------------------------------------------------
;=============================
DLOG_1ch	.macro	n
;=============================
	   	MOVW 	DP,#_DLOG_1ch_Input:n:                ; load DP for net pointer
       	MOVL	XAR7,@_DLOG_1ch_CurrTask:n:
       	MOVL	XAR1,@_DLOG_1ch_Input:n:
       	LB		*XAR7
       
WAIT_FOR_TRIGGER:n:
		MOVL	ACC,*XAR1
		SUBL	ACC,@_DLOG_1ch_TrigVal:n:		; ACC = Input1 - TrigVal
		BF		DATALOG_EXIT:n:, GEQ			; If the input is already greater than TrigVal do not trigger the DataLog
		
		MOVL	XAR0,#CHECK_FOR_RISING_EDGE:n:
		MOVL	@_DLOG_1ch_CurrTask:n:, XAR0
		LB		DATALOG_EXIT:n: 

CHECK_FOR_RISING_EDGE:n:
		MOVL	ACC,*XAR1
		SUBL	ACC,@_DLOG_1ch_TrigVal:n:
		BF		DATALOG_EXIT:n:, LEQ		  

; Input was less earlier and now it went greater than TrigValue, then LOG Data  
		MOVL	XAR0,#LOG_DATA:n:
		MOVL	@_DLOG_1ch_CurrTask:n:, XAR0
		LB		DATALOG_EXIT:n: 

LOG_DATA:n:

;Skip PreScalar Number of Points
		INC		@_DLOG_1ch_SkipCnt:n:
		MOV		ACC,@_DLOG_1ch_SkipCnt:n:
		SUB		ACC, @_DLOG_1ch_PreScalar:n:	;ACC=SkipCnt - PreScalar
		SBF		DATALOG_EXIT:n:, NEQ			;if SkipCnt != PreScalar branch to exit; otherwise execute next statement
		
		MOV		@_DLOG_1ch_SkipCnt:n:,#0
		
;Put the DLOG Current index in XAR0
		MOVL	XAR0,@_DLOG_1ch_Cnt:n:

; Log Buff		
	  	MOVL	XAR1,@_DLOG_1ch_Input:n:
	  	MOVL	XAR2,@_DLOG_1ch_OutputBuff:n:
	  	MOVL	ACC,*XAR1
	  	SFR		ACC,#9	; convert from Q24 to Q15
	 	MOV		*+XAR2[AR0],AL
	 	
	 	INC		@_DLOG_1ch_Cnt:n:
	 	MOV		ACC,@_DLOG_1ch_Cnt:n:
		SUB		ACC, @_DLOG_1ch_Size:n:	;ACC=Cnt-Size
		SBF		DATALOG_EXIT:n:, NEQ		;if SkipCnt != PreScalar branch to exit; otherwise execute next statement
	
RESET_DATALOG:n:
		MOVL	XAR0,#WAIT_FOR_TRIGGER:n:
		MOVL	@_DLOG_1ch_CurrTask:n:, XAR0
		MOV		@_DLOG_1ch_Cnt:n:,#0
		MOV		@_DLOG_1ch_SkipCnt:n:,#0
		

DATALOG_EXIT:n:	
	   .endm

; end of file
