;----------------------------------------------------------------------------------
;	FILE:			DLOG_4ch.asm
;
;	Description:	4 Channel DataLoggerModule 
;
;	Version: 	
;
;   Target:  		F2802x / F2803x / F2806x / F2805x
;
;--------------------------------------------------------------------------------
;   Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
;   ALL RIGHTS RESERVED
;--------------------------------------------------------------------------------
;  Revision History:
;--------------------------------------------------------------------------------
;  Date	  	| Description
;--------------------------------------------------------------------------------
;--------------------------------------------------------------------------------
;=============================
DLOG_4ch_INIT	.macro	n
;=============================
; allocate memory space for data & terminal pointers
_DLOG_4ch_i1Ptr		.usect "DLOG_4ch_Section",2,1,1
_DLOG_4ch_i2Ptr		.usect "DLOG_4ch_Section",2,1,1
_DLOG_4ch_i3Ptr		.usect "DLOG_4ch_Section",2,1,1
_DLOG_4ch_i4Ptr		.usect "DLOG_4ch_Section",2,1,1
_DLOG_4ch_buff1Ptr	.usect "DLOG_4ch_Section",2,1,1
_DLOG_4ch_buff2Ptr	.usect "DLOG_4ch_Section",2,1,1
_DLOG_4ch_buff3Ptr	.usect "DLOG_4ch_Section",2,1,1
_DLOG_4ch_buff4Ptr	.usect "DLOG_4ch_Section",2,1,1
_DLOG_4ch_TrigVal	.usect "DLOG_4ch_Section",2,1,1	
_DLOG_4ch_CurrTask	.usect "DLOG_4ch_Section",2,1,1
_DLOG_4ch_PreScalar	.usect "DLOG_4ch_Section",1,1,1	
_DLOG_4ch_Size		.usect "DLOG_4ch_Section",1,1,1
_DLOG_4ch_Cnt		.usect "DLOG_4ch_Section",1,1,1
_DLOG_4ch_SkipCnt	.usect "DLOG_4ch_Section",1,1,1

;Publish Terminal Pointers for access from the C environment
		.def 	_DLOG_4ch_i1Ptr
		.def 	_DLOG_4ch_i2Ptr
		.def 	_DLOG_4ch_i3Ptr
		.def 	_DLOG_4ch_i4Ptr
		.def 	_DLOG_4ch_buff1Ptr
		.def	_DLOG_4ch_buff2Ptr
		.def 	_DLOG_4ch_buff3Ptr
		.def	_DLOG_4ch_buff4Ptr
		.def 	_DLOG_4ch_TrigVal
		.def 	_DLOG_4ch_PreScalar
		.def 	_DLOG_4ch_Size
						
; set terminal pointer to ZeroNet
		MOVL	XAR2, #ZeroNet
		MOVW	DP, #_DLOG_4ch_i1Ptr
		MOVL	@_DLOG_4ch_i1Ptr, XAR2
		MOVL	@_DLOG_4ch_i2Ptr, XAR2
		MOVL	@_DLOG_4ch_i3Ptr, XAR2
		MOVL	@_DLOG_4ch_i4Ptr, XAR2
		
;set internal data to zero
		ZAPA
		MOVL	@_DLOG_4ch_TrigVal,ACC
		MOV		@_DLOG_4ch_PreScalar,AL
		MOV		@_DLOG_4ch_Size,AL
		MOV		@_DLOG_4ch_Cnt,AL
		MOV		@_DLOG_4ch_SkipCnt,AL
		
;reset the data log to wait for trigger
		MOVL	XAR0,#WAIT_FOR_TRIGGER
		MOVL	@_DLOG_4ch_CurrTask,XAR0
		
		.endm

;-------------------------------------------------------------------------------------------
;=============================
DLOG_4ch	.macro	n
;=============================
	   	MOVW 	DP,#_DLOG_4ch_i1Ptr                ; load DP for net pointer
       	MOVL	XAR7,@_DLOG_4ch_CurrTask
       	MOVL	XAR1,@_DLOG_4ch_i1Ptr
       	LB		*XAR7
       
WAIT_FOR_TRIGGER:
		MOVL	ACC,*XAR1
		SUBL	ACC,@_DLOG_4ch_TrigVal		; ACC = Input1 - TrigVal
		BF		DATALOG_EXIT, GEQ			; If the input is already greater than TrigVal do not trigger the DataLog
		
		MOVL	XAR0,#CHECK_FOR_RISING_EDGE
		MOVL	@_DLOG_4ch_CurrTask, XAR0
		LB		DATALOG_EXIT 

CHECK_FOR_RISING_EDGE:
		MOVL	ACC,*XAR1
		SUBL	ACC,@_DLOG_4ch_TrigVal
		BF		DATALOG_EXIT, LEQ		  

; Input was less earlier and now it went greater than TrigValue, then LOG Data  
		MOVL	XAR0,#LOG_DATA
		MOVL	@_DLOG_4ch_CurrTask, XAR0
		LB		DATALOG_EXIT 

LOG_DATA:

;Skip PreScalar Number of Points
		INC		@_DLOG_4ch_SkipCnt
		MOV		ACC,@_DLOG_4ch_SkipCnt
		SUB		ACC, @_DLOG_4ch_PreScalar	;ACC=SkipCnt - PreScalar
		SBF		DATALOG_EXIT, NEQ			;if SkipCnt != PreScalar branch to exit; otherwise execute next statement
		
		MOV		@_DLOG_4ch_SkipCnt,#0
		
;Put the DLOG Current index in XAR0
		MOVL	XAR0,@_DLOG_4ch_Cnt

; Log Buff1		
	  	MOVL	XAR1,@_DLOG_4ch_i1Ptr
	  	MOVL	XAR2,@_DLOG_4ch_buff1Ptr
	  	MOVL	ACC,*XAR1
	  	SFR		ACC,#9	; convert from Q24 to Q15
	 	MOV		*+XAR2[AR0],AL
	 	
	 	
; Log Buff2
		MOVL	XAR1,@_DLOG_4ch_i2Ptr
	  	MOVL	XAR2,@_DLOG_4ch_buff2Ptr
	  	MOVL	ACC,*XAR1
	  	SFR		ACC,#9	; convert from Q24 to Q15
	 	MOV		*+XAR2[AR0],AL
	 	
; Log Buff3
		MOVL	XAR1,@_DLOG_4ch_i3Ptr
	  	MOVL	XAR2,@_DLOG_4ch_buff3Ptr
	  	MOVL	ACC,*XAR1
	  	SFR		ACC,#9	; convert from Q24 to Q15
	 	MOV		*+XAR2[AR0],AL

; Log Buff4
		MOVL	XAR1,@_DLOG_4ch_i4Ptr
	  	MOVL	XAR2,@_DLOG_4ch_buff4Ptr
	  	MOVL	ACC,*XAR1
	  	SFR		ACC,#9	; convert from Q24 to Q15
	 	MOV		*+XAR2[AR0],AL
	 	
	 	INC		@_DLOG_4ch_Cnt
	 	MOV		ACC,@_DLOG_4ch_Cnt
		SUB		ACC, @_DLOG_4ch_Size	;ACC=Cnt-Size
		SBF		DATALOG_EXIT, NEQ		;if SkipCnt != PreScalar branch to exit; otherwise execute next statement
	
RESET_DATALOG:
		MOVL	XAR0,#WAIT_FOR_TRIGGER
		MOVL	@_DLOG_4ch_CurrTask, XAR0
		MOV		@_DLOG_4ch_Cnt,#0
		MOV		@_DLOG_4ch_SkipCnt,#0
		

DATALOG_EXIT:	
	   .endm

; end of file

