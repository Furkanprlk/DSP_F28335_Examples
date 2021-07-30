; DCL_PID.asm - PID controller
; version 1.0, August 2015

; C prototype:
; float DCL_runPID(PID *p, float rk, float yk, float lk)
; argument 1 = *p : 32-bit PID structure address [XAR4]
; argument 2 = rk : 32-bit floating-point reference [R0H]
; argument 3 = yk : 32-bit floating-point feedback [R1H]
; argument 4 = lk : 32-bit floating-point saturation input [R2H]
; return = uk : 32-bit floating-point [R0H]

   		.def 	_DCL_runPID				; define C callable label
;
; C type definition:
; typedef volatile struct {
; 	float Kp;		// [0] proportional gain
; 	float Ki;		// [2] integral gain
; 	float Kd;		// [4] derivative gain
; 	float Kr;		// [6] set-point weight
; 	float c1;		// [8] D filter coefficient 1
; 	float c2;		// [A] D filter coefficient 2
; 	float d2;		// [C] D filter storage 1
; 	float d3;		// [E] D filter storage 2
; 	float i10;		// [10] I storage
;	float i14;		// [12] sat storage
;	float Umax;		// [14] sat+
;	float Umin;		// [16] sat-
; } PID;

; example of section allocation in linker command file:
;	dclfuncs		: > RAML4,		PAGE = 0

		.sect	"dclfuncs"
_DCL_runPID:
; context save
        PUSH	AR1H:AR0H
		MOV32	*SP++, R3H
		MOV32   *SP++, R4H
		MOV32   *SP++, R5H
		MOV32   *SP++, R6H
		MOV32   *SP++, R7H

;*** derivative path ***
		MOV32	R3H, *+XAR4[4]				; R3H = Kd
		MOV		AR0, #8						; AR0 = 8
		MPYF32	R5H, R1H, R3H				; R5H = Kd * yk
||		MOV32	R4H, *+XAR4[AR0]			; R4H = c1
		MOV		AR0, #0xC					; AR0 = 12
		MPYF32	R3H, R4H, R5H				; R3H = v1 = Kd * yk * c1
||		MOV32	R6H, *+XAR4[AR0]			; R6H = d2
		MOV		AR1, #0xE					; AR1 = 14
		SUBF32	R4H, R3H, R6H				; R4H = v1 - d2
||		MOV32	R5H, *+XAR4[AR1]			; R5H = d3
		NOP
		SUBF32	R4H, R4H, R5H				; R4H = v4 = v1 - d2 - d3
||		MOV32	*+XAR4[AR0], R3H			; save d2
		MOV		AR0, #0xA					; AR0 = 10
		MOV32	R6H, *+XAR4[AR0]			; R6H = c2
		MPYF32	R5H, R6H, R4H				; R5H = d3 = c2 * v4
		NOP
		MOV32	*+XAR4[AR1], R5H			; save d3

;*** proportional path ***
		MOV32	R5H, *+XAR4[6]				; R5H = Kr
		MPYF32	R6H, R5H, R0H				; R6H = Kr * rk
		NOP
		SUBF32	R3H, R6H, R1H				; R3H = v5 = (Kr * rk) - yk
		NOP
		SUBF32	R5H, R3H, R4H				; R5H = v5 - v4
||		MOV32	R6H, *+XAR4[0]				; R6H = Kp
		MOV 	AR0, #0x12					; AR0 = 18
		MPYF32	R7H, R5H, R6H				; R7H = v6
||		MOV32	R4H, *+XAR4[2]				; R4H = Ki

;*** integral path ***
		MPYF32	R5H, R4H, R6H				; R5H = Kp * Ki
||		SUBF32	R3H, R0H, R1H				; R3H = rk - yk
		MOV32	R6H, *+XAR4[AR0] 			; R6H = i14
		MPYF32	R4H, R3H, R5H				; R4H = v7
		MOV		AR0, #0x10					; AR0 = 16
		MPYF32	R4H, R4H, R6H				; R4H = v7 * i14
||		MOV32	R6H, *+XAR4[AR0] 			; R6H = i10
		NOP
		ADDF32	R3H, R4H, R6H				; R3H = v8

;*** output saturation ***
		ZERO	R0H							; R0H = 0.0f
		MOV32	*+XAR4[AR0], R3H			; save i10
		ADDF32	R1H, R7H, R3H				; R1H = v9
		ADDF32	R6H, R0H, #1.0				; R6H = 1.0f
		MOV		AR1, #0x14					; AR1 = 20
		MOV32	R3H, *+XAR4[AR1]			; R3H = Umax
		MINF32	R1H, R3H					; sat v9
||		MOV32	R6H, R0H					; R6H = 0.0f if sat
		MOV		AR1, #0x16					; AR1 = 22
		MOV32	R3H, *+XAR4[AR1]			; R3H = Umin
		MAXF32	R1H, R3H					; sat v9
||		MOV32	R6H, R0H					; R6H = 0.0f if sat

;*** return ***
		MPYF32	R3H, R2H, R6H				; R3H = i14
		MOV32	R0H, R1H					; return uk
		MOV		AR0, #0x12					; AR0 = 18
		MOV32	*+XAR4[AR0], R3H			; save i14

; context restore
		MOV32   R7H, *--SP, UNCF
		MOV32   R6H, *--SP, UNCF
	    MOV32   R5H, *--SP, UNCF
	    MOV32   R4H, *--SP, UNCF
	    MOV32   R3H, *--SP, UNCF
        POP     AR1H:AR0H
		LRETR								; return from function

		.end
		
; end of file
