; DCL_DF23.asm - Direct Form 2 implementation in third order
; version 1.0, August 2015

; define C callable labels
   		.def 	_DCL_runDF23				; full DF2 controller
		.def	_DCL_runDF23i				; immediate result
		.def	_DCL_runDF23p				; pre-computed partial result
;
; C type definition:
; typedef volatile struct {
;	float b0;	// [0]
;	float b1;	// [2]
;	float b2;	// [4]
;	float b3;	// [6]
;	float a1;	// [8]
;	float a2;	// [A]
;	float a3;	// [C]
;	float x1;	// [E]
;	float x2;	// [10]
;	float x3;	// [12]
; } DF23;


;*** full DF23 controller ***

; C prototype:
; float DCL_runDF23(DF23 *p, float ek)
; argument 1 = *p : 32-bit ARMA structure address [XAR4]
; argument 2 = ek : 32-bit floating-point input [R0H]
; return = uk : 32-bit floating-point [R0H]

; example of section allocation in linker command file:
;	dclfuncs		: > RAML4,		PAGE = 0

		.sect	"dclfuncs"
_DCL_runDF23:
		PUSH  	XAR5
		MOV32   *SP++, R1H
		MOV32   *SP++, R2H
		MOV32   *SP++, R3H
		MOV32   *SP++, R4H
		MOV32   *SP++, R5H
		MOV32   *SP++, R6H
		MOV32	*SP++, R7H
		MOVL	ACC, @XAR4				; ACC = &b0
		ADDB	ACC, #0xE				; ACC = &x1
		MOVL	XAR5, ACC				; XAR5 = &x1
		MOV32	R1H, *XAR5++			; R1H = x1
		MOV32	R2H, *XAR4++			; R2H = b0
		MPYF32	R3H, R2H, R0H			; R3H = v1
		MOV32	R2H, *XAR4++			; R2H = b1
		ADDF32	R7H, R1H, R3H			; R7H = uk
||		MOV32	R3H, *XAR4++			; R3H = b2
		MPYF32	R1H, R2H, R0H			; R1H = v2
||		MOV32	R4H, *XAR4++			; R4H = b3
		MPYF32	R2H, R3H, R0H			; R2H = v4
||		MOV32	R5H, *XAR4++			; R5H = a1
		MPYF32	R3H, R4H, R0H			; R3H = v6
||		MOV32	R6H, *XAR4++			; R6H = a2
		MPYF32	R4H, R5H, R7H			; R4H = v3
||		MOV32	R0H, *XAR5++			; R0H = x2
		ADDF32	R1H, R0H, R1H			; R1H = v2 + x2
		MOV32	R0H, *XAR4++			; R0H = a3
		SUBF32	R1H, R1H, R4H			; R1H = x1d
		MPYF32	R5H, R6H, R7H			; R5H = v5
||		MOV32	R6H, *XAR5				; R6H = x3
		ADDF32	R2H, R2H, R6H			; R2H = v4 + x3
		MOV32	*XAR4++, R1H			; save x1  
		SUBF32	R2H, R2H, R5H			; R2H = x2d
		MPYF32	R5H, R0H, R7H			; R5H = v7
		MOV32	*XAR4++, R2H			; save x2
		SUBF32	R3H, R3H, R5H			; R3H = x3d
		MOV32	R0H, R7H, UNCF			; save uk
		MOV32	*XAR4, R3H				; save x3
	    MOV32   R7H, *--SP, UNCF
	    MOV32   R6H, *--SP, UNCF
		MOV32   R5H, *--SP, UNCF
	    MOV32   R4H, *--SP, UNCF
		MOV32   R3H, *--SP, UNCF
	    MOV32   R2H, *--SP, UNCF
	    MOV32   R1H, *--SP, UNCF
		POP   	XAR5
		LRETR


;*** immediate controller when using pre-computation ***

; C prototype:
; float DCL_runDF23i(DF23 *p, float ek)
; argument 1 = *p : controller structure address [XAR4]
; argument 2 = ek : controller input [R0H]
; return = uk : controller output [R0H]

_DCL_runDF23i:
		MOV32   *SP++, R1H
		MOV32	R1H, *+XAR4[0]				; R1H = b0
		MOV		AR0, #0xE					; AR0 = 14
		MPYF32	R0H, R0H, R1H				; R0H = ek * b0
		MOV32	R1H, *+XAR4[AR0]			; R1H = x1
		ADDF32	R0H, R0H, R1H				; R0H = uk
	    MOV32   R1H, *--SP, UNCF
		LRETR


;*** partial controller when using pre-computation ***

; C prototype:
; void DCL_runDF23p(DF23 *p, float ek, float uk)
; argument 1 = *p : controller structure address [XAR4]
; argument 2 = ek : controller input [R0H]
; argument 3 = uk : u(k) output [R1H]
; return: void

_DCL_runDF23p:
		MOV32   *SP++, R2H
		MOV32   *SP++, R3H
		MOV32   *SP++, R4H
		MOV32   *SP++, R5H
		MOV32   *SP++, R6H
		MOV32	*SP++, R7H
		MOVL	ACC, @XAR4				; ACC = &b0
		ADDB	ACC, #0x10				; ACC = &x2
		MOVL	XAR5, ACC				; XAR5 = &x2
		MOV32	R2H, *XAR4++			; R2H = b0
		MOV32	R2H, *XAR4++			; R2H = b1
		MPYF32	R3H, R0H, R2H			; R3H = v2
||		MOV32	R4H, *XAR5++			; R4H = x2
		MOV32	R2H, *XAR4++			; R2H = b2
		ADDF32	R3H, R3H, R4H			; R3H = v2 + x2
||		MOV32	R4H, *XAR4++			; R4H = b3
		MPYF32	R5H, R0H, R2H 			; R5H = v4
||		MOV32	R6H, *XAR4++			; R6H = a1
		MPYF32	R7H, R4H, R0H			; R7H = v6
||		MOV32	R4H, *XAR4++			; R4H = a2
		MPYF32	R6H, R6H, R1H			; R6H = v3
		MOV32	R0H, *XAR4++			; R0H = a3
		SUBF32	R3H, R3H, R6H			; R3H = x1d
		MPYF32	R4H, R4H, R1H			; R4H = v5
		MOV32	R2H, *XAR5				; R2H = x3
		MOV32	*XAR4++, R3H			; save x1
		ADDF32	R5H, R5H, R2H			; R5H = v4 + x3
		MPYF32	R1H, R0H, R1H			; R1H = v7
		SUBF32	R4H, R5H, R4H			; R4H = x2d
		SUBF32	R7H, R7H, R1H			; R7H = x3d
		MOV32	*XAR4++, R4H			; save x2
		MOV32	*XAR4, R7H				; save x3
	    MOV32   R7H, *--SP, UNCF
	    MOV32   R6H, *--SP, UNCF
		MOV32   R5H, *--SP, UNCF
	    MOV32   R4H, *--SP, UNCF
		MOV32   R3H, *--SP, UNCF
	    MOV32   R2H, *--SP, UNCF
		LRETR

		.end
		
; end of file
