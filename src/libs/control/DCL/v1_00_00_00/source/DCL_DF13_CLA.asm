; DCL_DF13_CLA.asm - Direct Form 1 implementation in third order
; version 1.0, August 2015

; C type definition:
; typedef volatile struct {
;	float c[8];		// coefficients: { b0, b1, b2, b3, a0, a1, a2, a3 }
;	float d[8];		// data: { e(k), e(k-1), e(k-2), e(k-3), u(k), u(k-1), u(k-2), u(k-3) }
; } DF13;

; define C callable labels
   		.def 	_DCL_runDF13c
   		.def	__cla_DCL_runDF13c_sp
   		.def 	_DCL_runDF13ic
   		.def 	_DCL_runDF13pc

;*** full controller ***

; C prototype:
; float DCL_runDF13c(DF13 *p, float ek);
; argument 1 = *p : 32-bit structure address [MAR0]
; argument 2 = ek : 32-bit floating-point [MR0]
; return = uk : 32-bit floating-point [MR0]

SIZEOF_LFRAME	.set	6
LFRAME_MR1		.set	0
LFRAME_MR3		.set	2
LFRAME_MAR0		.set	4
LFRAME_MAR1		.set	5

		.align 	2
__cla_DCL_runDF13c_sp	.usect ".scratchpad:Cla1Prog:_DCL_runDF13c", SIZEOF_LFRAME, 0, 1
		.asg	 __cla_DCL_runDF13c_sp, LFRAME
		.sect 	"Cla1Prog:_DCL_runDF13c"

_DCL_runDF13c:
;		MDEBUGSTOP
		MMOV32	@LFRAME + LFRAME_MR3, MR3 	; save MR3
		MMOV16	@LFRAME + LFRAME_MAR0, MAR0 ; store MAR0 to frame
		MMOV16	@LFRAME + LFRAME_MAR1, MAR1 ; save MAR1
		MNOP								; MAR0 read stall
		MMOVZ16 MR2, @LFRAME + LFRAME_MAR0  ; MR2 = &b0
		MMOV16  MAR1, MR2, #0x10			; MAR1 = &d0
		MMOV32	MR1, *MAR0[2]++				; MR1 = b0
		MNOP								; MAR1 load stall

		MMPYF32	MR2, MR0, MR1				; MR2 = v0
		MMOV32	*MAR1[2]++, MR0				; save d0
		MMOV32	MR0, *MAR0[2]++				; MR0 = b1
		MMOV32	MR1, *MAR1[2]++				; MR1 = d1

		MMPYF32	MR3, MR0, MR1				; MR3 = v1
		MMOV32	MR0, *MAR0[2]++				; MR0 = b2
		MADDF32	MR2, MR2, MR3				; MR2 = v0 + v1
||		MMOV32	MR1, *MAR1[2]++				; MR1 = d2

		MMPYF32	MR3, MR0, MR1				; MR3 = v2
		MMOV32	MR0, *MAR0[4]++				; MR0 = b3
		MADDF32	MR2, MR2, MR3				; MR2 = v0 + v1 + v2
||		MMOV32	MR1, *MAR1[4]++				; MR1 = d3

		MMPYF32	MR3, MR0, MR1				; MR3 = v3
		MMOV32	MR0, *MAR0[2]++				; MR0 = a1
		MADDF32	MR2, MR2, MR3				; MR2 = v0 + v1 + v2 + v3
||		MMOV32	MR1, *MAR1[2]++				; MR1 = d5

		MMPYF32	MR3, MR0, MR1				; MR3 = v5
		MMOV32	MR0, *MAR0[2]++				; MR0 = a2
		MSUBF32	MR2, MR2, MR3				; MR2 = v0 + v1 + v2 + v3 - v5
||		MMOV32	MR1, *MAR1[2]++				; MR1 = d6

		MMPYF32	MR3, MR0, MR1				; MR3 = v6
		MMOV32	MR0, *MAR0[14]++			; MR0 = a3, MAR0 = &d6
		MSUBF32	MR2, MR2, MR3				; MR2 = v0 + v1 + v2 + v3 - v5 - v6
||		MMOV32	MR1, *MAR1[-6]++			; MR1 = d7, MAR1 = &d4

		MMPYF32	MR3, MR0, MR1				; MR3 = v7
		MNOP
		MSUBF32	MR0, MR2, MR3				; MR0 = v0 + v1 + v2 + v3 - v5 - v6 - v7
		MNOP
		MMOV32	*MAR1[-6]++, MR0			; save uk = d4

		MMOVD32	MR1, *MAR0[-2]++			; u(k-3) <- u(k-2)
		MMOVD32	MR1, *MAR0[-2]++			; u(k-2) <- u(k-1)
		MMOVD32	MR1, *MAR0[-4]++			; u(k-1) <- u(k)
		MMOVD32	MR1, *MAR0[-2]++			; e(k-3) <- e(k-2)
		MMOVD32	MR1, *MAR0[-2]++			; e(k-2) <- e(k-1)
		MRCNDD	UNC							; return call
		MMOVD32	MR1, *MAR0					; e(k-1) <- e(k)
		MMOV16	MAR1, @LFRAME + LFRAME_MAR1	; restore MAR1
		MMOV32	MR3, @LFRAME + LFRAME_MR3	; restore MR3


;*** control law with pre-computation ***

; C prototype:
; float DCL_runDF13ic(DF13 *p, float ek, float vk);
; argument 1 = *p : controller structure address [MAR0]
; argument 2 = e(k) : controller input [MR0]
; argument 3 = v(k) : partial control [MR1]
; return = u(k) : controller output [MR0]

_DCL_runDF13ic:
		MNOP								; MAR0 load delay slot 1
		MNOP								; MAR0 load delay slot 2
		MNOP								; MAR0 load delay slot 3
		MMOV32	MR2, *MAR0[0]++				; MR2 = b0
		MRCNDD	UNC							; return call
		MMPYF32	MR0, MR0, MR2				; MR0 = e(k) * b0
		MNOP
		MADDF32	MR0, MR0, MR1				; MR0 = u(k)


;*** partial controller when using pre-computation ***

; float DCL_runDF13pc(DF13 *p, float ek, float uk)
; argument 1 = *p : structure address [MAR0]
; argument 2 = ek : controller input [MR0]
; argument 3 = uk : u(k) output [MR1]
; return: v(k+1) partial control [MR0]

_DCL_runDF13pc:
;		MDEBUGSTOP
		MMOV32	@LFRAME + LFRAME_MR1, MR1 	; save MR1
		MMOV32	@LFRAME + LFRAME_MR3, MR3 	; save MR3
		MMOV16	@LFRAME + LFRAME_MAR0, MAR0 ; store MAR0 to frame
		MMOV16	@LFRAME + LFRAME_MAR1, MAR1 ; save MAR1
		MNOP								; MAR0 read stall
		MMOVZ16 MR2, @LFRAME + LFRAME_MAR0  ; MR2 = &b0
		MMOV16  MAR1, MR2, #0x10			; MAR1 = &d0
		MMOV32	MR1, *MAR0[2]++				; MR1 = b0
		MNOP								; MAR1 load stall
		MNOP

		MMOV32	*MAR1[2]++, MR0				; save d0
		MMOV32	MR3, *MAR1					; MR3 = d1
		MMOV32	*MAR1[2]++, MR0				; save d1

		MMOV32	MR1, *MAR0[2]++				; MR1 = b1
		MMPYF32	MR0, MR0, MR1				; MR0 = v1
		MMOV32	MR1, *MAR0[2]++				; MR1 = b2

		MMOV32	MR2, *MAR1					; MR2 = d2
		MMOV32	*MAR1, MR3					; save d2
		MMPYF32	MR2, MR1, MR3				; MR2 = v2
		MMOV32	MR3, *MAR1[8]++				; MR3 = b3
		MADDF32	MR0, MR0, MR2				; MR0 = v12
		MMOV32	MR1, *MAR0[8]++				; MR1 = b3
		MMPYF32	MR2, MR1, MR3				; MR2 = v3
		MMOV32	MR3, *MAR1[-2]++			; MR3 = d6
		MADDF32	MR0, MR0, MR2				; MR0 = v123

		MMOV32	MR1, *MAR0[-2]++			; MR1 = a3
		MMOV32	MR2, *MAR1[2]++				; MR2 = d5
		MMOV32	*MAR1[-2]++, MR2			; save d6
		MMPYF32	MR3, MR1, MR3				; MR3 = v6
		MMOV32	MR1, *MAR0[-2]++			; MR1 = a2
		MSUBF32	MR0, MR0, MR3				; MR0 = v1236
		MNOP
		MMPYF32	MR3, MR1, MR2				; MR3 = v5
		MMOV32	MR1, *MAR0					; MR1 = a1
		MSUBF32	MR0, MR0, MR3				; MR0 = v12356

		MMOV32	MR2, @LFRAME + LFRAME_MR1	; MR2 = uk
		MMPYF32	MR3, MR1, MR2				; MR4 = v4
||		MMOV32	*MAR1, MR2					; save d5
		MRCNDD	UNC							; return call
		MSUBF32	MR0, MR0, MR3				; MR0 = v(k+1)
		MMOV16	MAR1, @LFRAME + LFRAME_MAR1	; restore MAR1
		MMOV32	MR3, @LFRAME + LFRAME_MR3	; restore MR3

		.unasg	LFRAME


; end of file
