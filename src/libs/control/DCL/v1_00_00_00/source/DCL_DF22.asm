; DCL_DF22.asm - Direct Form 2 implementation in second order
; version 1.0, August 2015

; define C callable labels
   		.def 	_DCL_runDF22				; full DF2 controller
		.def	_DCL_runDF22i				; immediate result
		.def	_DCL_runDF22p				; pre-computed partial result
;
; C type definition:
; typedef volatile struct {
;	float b0;	// [0]
;	float b1;	// [2]
;	float b2;	// [4]
;	float a1;	// [6]
;	float a2;	// [8]
;	float x1;	// [A]
;	float x2;	// [C]
; } DF22;


;*** full DF22 controller ***

; C prototype:
; float DCL_runDF22(DF22 *p, float ek)
; argument 1 = *p : 32-bit ARMA structure address [XAR4]
; argument 2 = ek : 32-bit floating-point input [R0H]
; return = uk : 32-bit floating-point [R0H]

; example of section allocation in linker command file:
;	dclfuncs		: > RAML4,		PAGE = 0

		.sect	"dclfuncs"
_DCL_runDF22:
		MOV32   *SP++, R1H
		MOV32   *SP++, R2H
		MOV32   *SP++, R3H
		MOV32   *SP++, R4H
		MOV32   *SP++, R5H
		MOV32   *SP++, R6H
		MOV32	*SP++, R7H

		MOV32	R2H, *XAR4++			; R2H = b0
		MPYF32	R3H, R2H, R0H			; R3H = v0 = b0 * ek
||		MOV32	R4H, *XAR4++			; R4H = b1
		MPYF32	R5H, R4H, R0H			; R5H = v1 = b1 * ek
||		MOV32	R6H, *XAR4++			; R6H = b2
		MPYF32	R4H, R6H, R0H			; R4H = v2 = b2 * ek
||		MOV32	R7H, *XAR4++			; R7H = a1
		MOV32	R0H, *XAR4++			; R0H = a2
		MOV32	R6H, *XAR4++			; R6H = x1
		ADDF32	R1H, R3H, R6H			; R1H = uk = v0 + x1
||		MOV32	R2H, *XAR4				; R2H = x2
		ADDF32	R5H, R5H, R2H			; R5H = v1 + x2
		MPYF32	R6H, R7H, R1H			; R6H = v3 = a1 * uk
		MPYF32	R7H, R0H, R1H			; R7H = v4 = a2 * uk
		SUBF32	R5H, R5H, R6H			; R5H = x1d = v1 + x2 - v3
		SUBF32	R6H, R4H, R7H			; R6H = x2d = v2 - v4
		MOV32	R0H, R1H, UNCF			; return uk
		MOV32	*XAR4, R6H				; save x2
		MOV32	*--XAR4, R5H			; save x1

	    MOV32   R7H, *--SP, UNCF
	    MOV32   R6H, *--SP, UNCF
		MOV32   R5H, *--SP, UNCF
	    MOV32   R4H, *--SP, UNCF
		MOV32   R3H, *--SP, UNCF
	    MOV32   R2H, *--SP, UNCF
	    MOV32   R1H, *--SP, UNCF
		LRETR


;*** immediate controller when using pre-computation ***

; C prototype:
; float DCL_runDF22i(DF22 *p, float ek)
; argument 1 = *p : controller structure address [XAR4]
; argument 2 = ek : controller input [R0H]
; return = uk : controller output [R0H]

_DCL_runDF22i:
		MOV32   *SP++, R1H
		MOV32	R1H, *+XAR4[0]				; R1H = b0
		MOV		AR0, #0xA					; AR0 = 10
		MPYF32	R0H, R0H, R1H				; R0H = ek * B0
		MOV32	R1H, *+XAR4[AR0]			; R1H = x1
		ADDF32	R0H, R0H, R1H				; R0H = uk
	    MOV32   R1H, *--SP, UNCF
		LRETR


;*** partial controller when using pre-computation ***

; C prototype:
; void DCL_runDF22p(DF22 *p, float ek, float uk)
; argument 1 = *p : controller structure address [XAR4]
; argument 2 = ek : controller input [R0H]
; argument 3 = uk : u(k) output [R1H]
; return: void

_DCL_runDF22p:
		MOV32   *SP++, R2H
		MOV32   *SP++, R3H
		MOV32   *SP++, R4H
		MOV32   *SP++, R5H
		MOV32   *SP++, R6H
		MOV32	*SP++, R7H
		MOV32	R2H, *XAR4++			; XAR4 = &b1
		MOV32	R2H, *XAR4++			; R2H = b1
		MPYF32	R3H, R2H, R0H			; R3H = v1
||		MOV32	R4H, *XAR4++			; R4H = b2
		MPYF32	R5H, R4H, R0H			; R5H = v2
||		MOV32	R6H, *XAR4++			; R6H = a1
		MPYF32	R7H, R6H, R1H			; R7H = v3
||		MOV32	R0H, *XAR4++			; R0H = a2, XAR4 = &x1
		MPYF32	R0H, R0H, R1H			; R0H = v4
||		MOV32	R2H, *+XAR4[2]			; R2H = x2
		ADDF32	R3H, R3H, R2H			; R3H = v1 + x2
		SUBF32	R5H, R5H, R0H			; R5H = x2d
		SUBF32	R2H, R3H, R7H			; R2H = x1d
		MOV32	*+XAR4[2], R5H			; save x2
	    MOV32   R7H, *--SP, UNCF
		MOV32	*+XAR4[0], R2H			; save x1
	    MOV32   R6H, *--SP, UNCF
		MOV32   R5H, *--SP, UNCF
	    MOV32   R4H, *--SP, UNCF
		MOV32   R3H, *--SP, UNCF
	    MOV32   R2H, *--SP, UNCF
		LRETR

		.end
		
; end of file
