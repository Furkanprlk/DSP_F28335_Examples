; DCL_DF23_CLA.asm - Direct Form 2 implementation in third order
; version 1.0, August 2015

; C type definition:
; typedef volatile struct {
;	float b0;	// [0] b0
;	float b1;	// [2] b1
;	float b2;	// [4] b2
;	float b3;	// [6] b3
;	float a1;	// [8] a1
;	float a2;	// [A] a2
;	float a3;	// [C] a3
;	float x1;	// [E] x1
;	float x2;	// [10] x2
;	float x3;	// [12] x3
; } DF23;

; define C callable labels
   		.def 	_DCL_runDF23c
   		.def	__cla_DCL_runDF23c_sp
   		.def 	_DCL_runDF23ic
   		.def 	_DCL_runDF23pc

;*** full controller ***

; C prototype:
; float DCL_runDF23c(DF23 *p, float ek);
; argument 1 = *p : 32-bit structure address [MAR0]
; argument 2 = ek : 32-bit floating-point [MR0]
; return = uk : 32-bit floating-point [MR0]

SIZEOF_LFRAME	.set	2
LFRAME_MR3		.set	0

		.align 	2
__cla_DCL_runDF23c_sp	.usect ".scratchpad:Cla1Prog:_DCL_runDF23c", SIZEOF_LFRAME, 0, 1
		.asg	 __cla_DCL_runDF23c_sp, LFRAME
		.sect 	"Cla1Prog:_DCL_runDF23c"

_DCL_runDF23c:
;		MDEBUGSTOP
		MMOV32	@LFRAME + LFRAME_MR3, MR3 	; save MR3
		MNOP								; MAR0 load delay slot 2
		MNOP								; MAR0 load delay slot 3

		MMOV32	MR1, *MAR0[2]++				; MR1 = b0
		MMPYF32	MR2, MR1, MR0				; MR2 = v1
||		MMOV32	MR3, *MAR0[12]++			; MR3 = b1
		MMOV32	MR1, *MAR0[2]++				; MR1 = x1
		MADDF32	MR2, MR1, MR2				; MR2 = uk

		MMPYF32	MR3, MR0, MR3				; MR3 = v2
		MMOV32	MR1, *MAR0[-8]++			; MR1 = x2
		MADDF32	MR3, MR1, MR3				; MR3 = x2 + v2
||		MMOV32	MR1, *MAR0[-4]++			; MR1 = a1
		MMPYF32	MR1, MR1, MR2				; MR1 = v3
		MNOP
		MSUBF32	MR3, MR3, MR1				; MR3 = x1d
		MMOV32	MR1, *MAR0[10]++			; MR1 = b2
		MMOV32	*MAR0[4]++, MR3				; save x1

		MMPYF32	MR1, MR0, MR1				; MR1 = v4
		MMOV32	MR3, *MAR0[-8]++			; MR3 = x3
		MADDF32	MR3, MR1, MR3				; MR3 = x3 + v4
||		MMOV32	MR1, *MAR0[-4]++			; MR1 = a2
		MMPYF32	MR1, MR1, MR2				; MR1 = v5
		MNOP
		MSUBF32	MR3, MR3, MR1				; MR3 = x2d
		MMOV32	MR1, *MAR0[10]++			; MR1 = b3
		MMOV32	*MAR0[-4]++, MR3			; save x2

		MMPYF32	MR1, MR0, MR1				; MR1 = v6
||		MMOV32	MR3, *MAR0[6]++				; MR3 = a3
		MMPYF32	MR3, MR2, MR3				; MR3 = v7
		MSUBF32	MR1, MR1, MR3				; MR1 = x3d
		MRCNDD	UNC							; return call
		MMOV32	MR0, MR2, UNC				; return uk
		MMOV32	MR3, @LFRAME + LFRAME_MR3	; restore MR3
		MMOV32	*MAR0[0]++, MR1				; save x3



;*** control law with pre-computation ***

; C prototype:
; float DCL_runDF23ic(DF23 *p, float ek);
; argument 1 = *p : controller structure address [MAR0]
; argument 2 = ek : controller input [MR0]
; return = uk : controller output [MR0]

_DCL_runDF23ic:
		MNOP								; MAR0 load delay slot 1
		MNOP								; MAR0 load delay slot 2
		MNOP								; MAR0 load delay slot 3
		MMOV32	MR2, *MAR0[14]++			; MR2 = b0
		MRCNDD	UNC							; return call
		MMPYF32	MR1, MR0, MR2				; MR1 = ek * b0
		MMOV32	MR2, *MAR0[0]++				; MR2 = x1
		MADDF32	MR0, MR1, MR2				; MR0 = uk


;*** partial controller when using pre-computation ***

; void DCL_runDF23pc(DF23 *p, float ek, float uk);
; argument 1 = *p : structure address [MAR0]
; argument 2 = ek : controller input [MR0]
; argument 3 = uk : u(k) controller output [MR1]
; return: void

_DCL_runDF23pc:
;		MDEBUGSTOP
		MMOV32	@LFRAME + LFRAME_MR3, MR3 	; save MR3
		MNOP								; MAR0 load delay slot 2
		MNOP								; MAR0 load delay slot 3
		MMOV32	MR2, *MAR0[2]++				; MR2 = b0
		MMOV32	MR2, *MAR0[14]++			; MR2 = b1	
		MMPYF32	MR2, MR0, MR2				; MR2 = v2
		MMOV32	MR3, *MAR0[-8]++			; MR3 = x2
		MADDF32	MR2, MR2, MR3				; MR2 = x2 + v2
		MMOV32	MR3, *MAR0[-4]++			; MR3 = a1
		MMPYF32	MR3, MR1, MR3				; MR3 = v3
		MNOP
		MSUBF32	MR2, MR2, MR3				; MR2 = x1d
		MMOV32	MR3, *MAR0[10]++			; MR3 = b2
		MMOV32	*MAR0[4]++, MR2				; save x1
		
		MMPYF32	MR3, MR0, MR3				; MR3 = v4
		MMOV32	MR2, *MAR0[-8]++			; MR2 = x3
		MADDF32	MR2, MR2, MR3				; MR2 = x3 + v4
		MMOV32	MR3, *MAR0[-4]++			; MR3 = a2
		MMPYF32	MR3, MR1, MR3				; MR3 = v5
		MNOP
		MSUBF32	MR2, MR2, MR3				; MR2 = x2d
		MMOV32	MR3, *MAR0[10]++			; MR3 = b3
		MMOV32	*MAR0[-4]++, MR2			; save x2
		
		MMPYF32	MR3, MR0, MR3				; MR3 = v6
		MMOV32	MR2, *MAR0[6]++				; MR2 = a3
		MMPYF32	MR2, MR1, MR2				; MR2 = v7
		MNOP
		MSUBF32	MR2, MR3, MR2				; MR2 = x3d
		MRCNDD	UNC							; return call
		MMOV32	*MAR0[0]++, MR2				; save x3
		MNOP
		MMOV32	MR3, @LFRAME + LFRAME_MR3	; restore MR3

		.unasg	LFRAME

; end of file
