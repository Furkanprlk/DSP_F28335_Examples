; DCL_DF13.asm - Direct Form 1 implementation in third order
; version 1.0, August 2015

; C callable labels
   		.def 	_DCL_runDF13			; full controller
   		.def	_DCL_runDF13i			; immediate controller for pre-computation
   		.def	_DCL_runDF13p			; partial controller for pre-computation
;
; C type definition:
; typedef volatile struct {
;	// coefficients
;	float b0;	// [0] b0
;	float b1;	// [2] b1
;	float b2;	// [4] b2
;	float b3;	// [6] b3
;	float a0;	// [8] a0
;	float a1;	// [A] a1
;	float a2;	// [C] a2
;	float a3;	// [E] a3
;
;	//data
;	float d0;	// [10] e(k)
;	float d1;	// [12] e(k-1)
;	float d2;	// [14] e(k-2)
;	float d3;	// [16] e(k-3)
;	float d4;	// [18] u(k)
;	float d5;	// [1A] u(k-1)
;	float d6;	// [1C] u(k-2)
;	float d7;	// [1E] u(k-3)
; } DF13;


;*** full controller ***

; C prototype:
; float DCL_runDF13(DF13 *p, float ek)
; argument 1 = *p : 32-bit ARMA structure address [XAR4]
; argument 2 = ek : 32-bit floating-point input [R0H]
; return = uk : 32-bit floating-point [R0H]

; XAR4 = coefficient pointer
; XAR5 = data pointer

; example of section allocation in linker command file:
;	dclfuncs		: > RAML4,		PAGE = 0

		.sect	"dclfuncs"
_DCL_runDF13:
; context save
		PUSH  	XAR5
		MOV32   *SP++, R1H
		MOV32   *SP++, R2H
		MOV32   *SP++, R3H
		MOV32   *SP++, R4H
		MOV32   *SP++, R5H

; initialize pointers
		MOVL	ACC, @XAR4					; ACC = &p(0) = &b0
		ADDB	ACC, #0x10					; ACC = &p(8) = &d0
		MOVL	XAR5, ACC					; XAR5 = &d0
		MOV32	*XAR5++, R0H				; save d0, XAR5 = &d1

; v0 = b0 * d0
		MOV32	R1H, *XAR4++				; R1H = b0
		MPYF32	R2H, R0H, R1H				; R2H = v0
||		MOV32	R3H, *XAR5					; R3H = d1
		MOV32	*XAR5++, R0H				; save d0

; v1 = b1 * d1
		MOV32	R1H, *XAR4++				; R1H = b1
		MPYF32	R4H, R1H, R3H				; R4H = v1
||		MOV32	R5H, *XAR5					; R5H = d2
		MOV32	*XAR5++, R3H				; save d1

; v2 = b2 * d2
 		ADDF32	R0H, R2H, R4H				; R0H = v01
|| 		MOV32	R1H, *XAR4++				; R1H = b2
 		MPYF32	R2H, R1H, R5H				; R2H = v2
|| 		MOV32	R4H, *XAR5					; R4H = d3
 		MOV32	*XAR5++, R5H				; save d2

; v3 = b3 * d3
 		ADDF32	R0H, R0H, R2H				; R0H = v012
|| 		MOV32	R1H, *XAR4++				; R1H = b3
		MPYF32	R3H, R1H, R4H				; R3H = v3
		MOV32	R2H, *+XAR5[6]				; R2H = d7

; XAR4 = &a0, XAR5 = &d4.  Indirect offset addressing from here.

; v7 = a3 * d7
		ADDF32	R0H, R0H, R3H				; R0H = v0123
||		MOV32	R1H, *+XAR4[6]				; R1H = a3
		MPYF32	R3H, R1H, R2H				; R3H = v7
		MOV32	R4H, *+XAR5[4]				; R4H = d6
		MOV32	*+XAR5[6], R4H				; save d6

; v6 = a2 * d6
		SUBF32	R0H, R0H, R3H				; R0H = v01237
||		MOV32	R1H, *+XAR4[4]				; R1H = a2
		MPYF32	R2H, R1H, R4H				; R2H = v6
		MOV32	R5H, *+XAR5[2]				; R5H = d5
		MOV32	*+XAR5[4], R5H				; save d5

; v5 = a1 * d5
		SUBF32	R0H, R0H, R2H				; R0H = v012367
||		MOV32	R1H, *+XAR4[2]				; R1H = a1
		MPYF32	R2H, R1H, R5H				; R2H = v5
	    MOV32   R5H, *--SP, UNCF
		SUBF32	R0H, R0H, R2H				; R0H = v0123567
	    MOV32   R4H, *--SP, UNCF
		MOV32	*+XAR5[2], R0H				; save d4
		MOV32	*+XAR5[0], R0H				; save u(k)

; context restore
		MOV32   R3H, *--SP, UNCF
	    MOV32   R2H, *--SP, UNCF
	    MOV32   R1H, *--SP, UNCF
		POP   	XAR5
		LRETR								; return
		
		
;*** immediate controller when using pre-computation ***

; C prototype:
; float DCL_runDF13i(DF13 *p, float ek, float vk)
; argument 1 = *p : controller structure address [XAR4]
; argument 2 = ek : controller input [R0H]
; argument 3 = vk : partial product [R1H]
; return = uk : controller output [R0H]

_DCL_runDF13i:
		MOV32   *SP++, R2H
		MOV32	R2H, *+XAR4[0]				; R2H = b0
		MPYF32	R0H, R0H, R2H				; R0H = e(k) * b0
		MOV 	AR0, #0x18					; AR0 = 24
		ADDF32	R0H, R0H, R1H				; R0H = u(k)
	    MOV32   R2H, *--SP, UNCF
		LRETR


;*** pre-computed partial controller ***

; C prototype:
; float DCL_runDF13p(DF13 *p, float ek, float uk)
; argument 1 = *p : controller structure address [XAR4]
; argument 2 = ek : controller input [R0H]
; argument 3 = uk : controller output [R1H]
; return : v(k)

_DCL_runDF13p:
; context save
        PUSH	AR1H:AR0H
		PUSH  	XAR5
		MOV32   *SP++, R1H
		MOV32   *SP++, R2H
		MOV32   *SP++, R3H
		MOV32   *SP++, R4H
		MOV32   *SP++, R5H
		MOV32   *SP++, R6H
		MOV32   *SP++, R7H

; initialise pointers
		MOVL	ACC, @XAR4					; ACC = &p(0) = &b0
		ADDB	ACC, #0x10					; ACC = &p(8) = &d0
		MOVL	XAR5, ACC					; XAR5 = &d0
		MOV32	*XAR5++, R0H				; save d0, XAR5 = d1

; v1 = e(k) * b1
		MOV32	R2H, *XAR4++				; R2H = b0
		MOV32	R2H, *XAR4++				; R2H = b1
		MPYF32	R3H, R2H, R0H				; R3H = v1
||		MOV32	R4H, *XAR5					; R4H = d1
		MOV32	*XAR5++, R0H				; save e(k-1)

; v2 = e(k-1) * b2
		MOV32	R5H, *XAR4++				; R5H = b2
		MPYF32	R2H, R5H, R4H				; R2H = v2
||		MOV32	R6H, *XAR5					; R6H = d2
		MOV32	*XAR5++, R4H				; save e(k-2)

; v3 = e(k-3) * b3
		MOV32	R5H, *XAR4++				; R5H = b3
		MPYF32	R7H, R5H, R6H				; R7H = v2
||		MOV32	*XAR5++, R6H				; save e(k-3)

; save v123
		ADDF32	R0H, R3H, R2H				; R0H = v1 + v2
		MOV32	R5H, *XAR4++				; R5H = a0
		ADDF32	R0H, R0H, R7H				; R0H = v1 + v2 + v3
||		MOV32	R5H, *XAR4++				; R5H = a1

; v4 = u(k) * a1
		MPYF32	R2H, R1H, R5H				; R2H = v4
||		MOV32	*XAR5++, R1H				; XAR5 = &d5
		MOV32	R3H, *XAR5					; R3H = d5
		SUBF32	R0H, R0H, R2H				; R0H = v1 + v2 + v3 - v4
		MOV32	*XAR5++, R1H				; save u(k-1)

; v5 = u(k-1) * a2
		MOV32	R4H, *XAR4++				; R4H = a2
		MPYF32	R5H, R4H, R3H				; R5H = v5
||		MOV32	R1H, *XAR5					; R2H = d6
		MOV32	*XAR5++, R3H				; save u(k-2)

; v6 = u(k-2) * a3
		SUBF32	R0H, R0H, R5H				; R0H = v1 + v2 + v3 - v4 - v5
||		MOV32	R6H, *XAR4					; R6H = a3
		MPYF32	R7H, R6H, R1H				; R7H = v7
		MOV32	*XAR5, R1H					; save u(k-3)
		SUBF32	R0H, R0H, R7H				; save v(k+1)

; context restore
	    MOV32   R7H, *--SP, UNCF
		MOV32   R6H, *--SP, UNCF
	    MOV32   R5H, *--SP, UNCF
	    MOV32   R4H, *--SP, UNCF
		MOV32   R3H, *--SP, UNCF
	    MOV32   R2H, *--SP, UNCF
	    MOV32   R1H, *--SP, UNCF
		POP   	XAR5
        POP     AR1H:AR0H
		LRETR

		.end
		
; end of file
