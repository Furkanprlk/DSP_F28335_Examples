;----------------------------------------------------------------------------------
;	FILE:			CNTL_2P2Z.asm
;
;	Description:	2nd Order Control Law Macro Module
;
;	Version: 		3.0
;
;   Target:  		F2802x / F2803x 
;
;----------------------------------------------------------------------------------
;  Copyright Texas Instruments © 2010
;----------------------------------------------------------------------------------
;  Revision History:
;----------------------------------------------------------------------------------
;  Date	     | Description
;----------------------------------------------------------------------------------
;   | Release 3.0  (MB)
;----------------------------------------------------------------------------------
;=============================
CNTL_2P2Z_INIT	.macro n
;=============================
; allocate memory space for data & terminal pointers
_CNTL_2P2Z_Ref:n:	.usect 	"CNTL_2P2Z_Section",2,1,1		; reference input terminal
_CNTL_2P2Z_Fdbk:n:	.usect 	"CNTL_2P2Z_Section",2,1,1		; feedback input terminal
_CNTL_2P2Z_Out:n:	.usect 	"CNTL_2P2Z_Section",2,1,1		; output terminal
_CNTL_2P2Z_Coef:n:	.usect 	"CNTL_2P2Z_Section",2,1,1		; coefficients & saturation limits (14 words)
_CNTL_2P2Z_DBUFF:n:	.usect  "CNTL_2P2Z_Section",10,1,1		; internal Data BUFF

; publish terminal pointers for access from the C environment
		.def 	_CNTL_2P2Z_Ref:n:
		.def 	_CNTL_2P2Z_Fdbk:n:
		.def 	_CNTL_2P2Z_Out:n:
		.def 	_CNTL_2P2Z_Coef:n:
		.def 	_CNTL_2P2Z_DBUFF:n:

; set terminal pointers to ZeroNet
		MOVL	XAR2, #ZeroNet
		MOVW	DP, #_CNTL_2P2Z_Ref:n:
		MOVL	@_CNTL_2P2Z_Ref:n:, XAR2
		MOVW	DP, #_CNTL_2P2Z_Fdbk:n:
		MOVL	@_CNTL_2P2Z_Fdbk:n:, XAR2
		MOVW	DP, #_CNTL_2P2Z_Out:n:
		MOVL	@_CNTL_2P2Z_Out:n:, XAR2

; zero data buffer
		MOVW	DP, #_CNTL_2P2Z_DBUFF:n:
		MOVL 	XAR2,#_CNTL_2P2Z_DBUFF:n:
		RPT		#9 	; 10 times
	||	MOV 	*XAR2++, #0
	
		.endm

;----------------------------------------------------------------------------------
;=============================
CNTL_2P2Z	.macro n
;=============================
; set up address pointers
		MOVW	DP, #_CNTL_2P2Z_Ref:n:
		MOVL 	XAR0, @_CNTL_2P2Z_Ref:n:		; net pointer to Ref (XAR0)
		MOVW	DP,#_CNTL_2P2Z_Fdbk:n:
		MOVL    XAR1, @_CNTL_2P2Z_Fdbk:n:		; net pointer to Fdbk (XAR1)
		MOVW	DP,#_CNTL_2P2Z_DBUFF:n:
		MOVL	XAR4, #_CNTL_2P2Z_DBUFF:n:		; pointer to the DBUFF array (used internally by the module)
		
; calculate error (Ref - Fdbk)
		MOV32	R0H, *XAR0						; R0H = Ref
		MOV32	R1H, *XAR1						; R1H = Fdbk
		SUBF32	R0H,R0H,R1H				    	; R0H = e(n) =Ref -Fdbk
		MOVW	DP,#_CNTL_2P2Z_Out:n:
;store error in DBUFF 
		MOV32	*+XAR4[4], R0H					; e(n) =  error	
		
		MOVL    XAR2, @_CNTL_2P2Z_Out:n:		; net pointer to Out (XAR2)
		MOVW	DP,#_CNTL_2P2Z_Coef:n:
		MOVL    XAR3, @_CNTL_2P2Z_Coef:n:		; net pointer to Coef (XAR3)
		
; compute 2P2Z filter
		MOV		AR0,#8
		MOV32	R0H, *+XAR4[AR0]				; 	R0H  = e(n-2)
		MOV32	R1H, *XAR3++					;	R1H  = B2
		MPYF32	R2H,R0H,R1H 					;	R2H = e(n-2)*B(2), R1H=B1
	||  MOV32 	R1H,*XAR3++
		
		
		MOVD32	R0H,*+XAR4[6]					;	R0H = e(n-1) and e(n-2)=e(n-1)
		MPYF32	R3H,R0H,R1H						;	R3H = e(n-1)*B1 
	||  MOV32 R1H,*XAR3++						; 	R1H=B0
		
		
		MOVD32	R0H,*+XAR4[4]					;	R0H=e(n) and e(n-1)=e(n)
		MPYF32	R4H,R0H,R1H						;	R4H =e(n)*B0 , R2H = e(n-2)*B2+e(n-1)*B1  
	||	ADDF32  R2H,R2H,R3H
		
		
		MOV32	R0H,*+XAR4[2]					;	R0H=u(n-2)
		MOV32	R1H,*XAR3++						; 	R1H=A2
		MPYF32	R3H,R0H,R1H						; 	R3H=u(n-2)*A2, R2H = e(n-2)*B2+e(n-1)*B1+e(n)*B0
	||	ADDF32 R2H,R2H,R4H	
		
		MOVD32	R0H,*+XAR4[0]					; 	R0H=u(n-1), u(n-1)=u(n-2)
		MOV32	R1H,*XAR3++						; 	R1H=A1
		MPYF32	R4H,R0H,R1H						;   R4H=u(n-1)*A1 , R2H = e(n-2)*B2+e(n-1)*B1+e(n)*B0+u(n-2)*A2
	||	ADDF32 R2H,R2H,R3H
		MOV32	R0H,*XAR3++						;	R0H = Maximum Value
		
		ADDF32	R2H,R2H,R4H						;	R2H = e(n-2)*B2+e(n-1)*B1+e(n)*B0+u(n-2)*A2+u(n-1)*A1
		MOV32	R1H,*XAR3++						;	R1H	= Internal minimum value
		
		MINF32  R2H,R0H							;   R2H = min (R0H{maximum value}, R2H {computed value})
		MOV32	R3H,*XAR3++						;	R3H	= Output minimum value 
		MAXF32	R2H,R1H							;	R2H = Max(R2H
		
		MOV32	*+XAR4[0],R2H					;   store the internal min saturate value in the data buffer
		MAXF32	R2H,R3H							;   saturate result to the output min value  
		
		MOV32	*XAR2,R2H						;   store the result in the output terminal 
		
		.endm
			
; end of file

