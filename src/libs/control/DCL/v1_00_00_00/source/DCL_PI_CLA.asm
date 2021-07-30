; DCL_PI_CLA.asm - PI controller
; version 1.0, August 2015

; C prototype:
; float DCL_runPIc(PI *p, float rk, float yk)
; argument 1 = *p : 32-bit PID structure address [MAR0]
; argument 2 = rk : 32-bit floating-point reference [MR0]
; argument 3 = yk : 32-bit floating-point feedback [MR1]
; return = uk : 32-bit floating-point [MR0]

; C type definition:
; typedef volatile struct {
; 	float Kp;		// [0] proportional gain
; 	float Ki;		// [2] integral gain
; 	float i10;		// [4] I storage
;	float Umax;		// [6] upper saturation limit
;	float Umin;		// [8] lower saturation limit
;	float i6;		// [A] saturation storage
; } PI;

   		.def 	_DCL_runPIc				; C callable function label
		.def	__cla_DCL_runPIc_sp

SIZEOF_LFRAME	.set	5
LFRAME_MR3		.set	0

		.align 	2
__cla_DCL_runPIc_sp	.usect ".scratchpad:Cla1Prog:_DCL_runPIc", SIZEOF_LFRAME, 0, 1
		.asg	 __cla_DCL_runPIc_sp, LFRAME

		.sect 	"Cla1Prog:_DCL_runPIc"

_DCL_runPIc:
;		MDEBUGSTOP
		MMOV32	@LFRAME + LFRAME_MR3, MR3 	; save MR3

;*** servo error ***
		MSUBF32	MR2, MR0, MR1				; MR2 = v1

;*** proportional path ***
		MMOV32	MR1, *MAR0[2]++				; MR1 = Kp
		MMPYF32	MR2, MR1, MR2				; MR2 = v2

;*** integral path ***
||		MMOV32	MR1, *MAR0[8]++				; MR1 = Ki
		MMPYF32	MR0, MR2, MR1				; MR0 = v3
||		MMOV32	MR1, *MAR0[-6]++			; MR1 = i6
		MMPYF32	MR0, MR0, MR1				; MR0 = v8
||		MMOV32	MR1, *MAR0					; MR1 = i10
		MADDF32	MR0, MR0, MR1				; MR0 = v4
		MMOV32	*MAR0[2]++, MR0				; save i10
		MADDF32	MR0, MR0, MR2				; MR0 = v5

;*** output saturation ***
		MMOVF32	MR2, #0.0f					; MR2 = 0.0f
		MMOVF32	MR3, #1.0f					; MR3 = 1.0f
		MMOV32	MR1, *MAR0[2]++				; MR1 = Umax
		MMINF32	MR0, MR1					; MR0 = sat+
		MMOV32	MR3, MR2, GT				; MR3 = v6
		MMOV32	MR1, *MAR0[2]++				; MR1 = Umin
		MMAXF32	MR0, MR1					; MR0 = sat-
		MRCNDD	UNC							; return call
		MMOV32	MR3, MR2, LT				; MR3 = v6
		MMOV32	*MAR0, MR3					; save i6
		MMOV32	MR3, @LFRAME + LFRAME_MR3	; restore MR3

		.unasg	LFRAME
		
; end of file
