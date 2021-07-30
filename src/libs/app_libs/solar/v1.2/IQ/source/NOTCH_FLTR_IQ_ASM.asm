
    .def _NOTCH_FLTR_IQ_ASM

_NOTCH_FLTR_IQ_ASM

	; because of C calling convention
	; XAR4 has the vars
	; XAR5 has the coeff

; compute notch filter equation
; In(n-2)*B2 +In(n-1)*B1+In(n)*B0+Out(n-2)*A2+Out(n-1)*A1
	MOV		AR0,#8
	MOVL	XT, *+XAR4[AR0]					; XT  = In(n-2)
	IMPYL	P,XT,*XAR5						; P   = In(n-2)Q24*B2{Q24}
	QMPYL	ACC, XT, *XAR5++				; ACC = In(n-2)Q24*B2{Q24} = I16Q48 (upper half)
	LSL64   ACC:P,#(32-24)					; ACC -> I8Q24
	MOVL	@XAR6,ACC						; XAR6 = ACC = In(n-2)*B2

    MOV     AR0,#6                          ;
	MOVDL	XT,*+XAR4[AR0]					; XT  = In(n-1),   In(n-2) = In(n-1)
	IMPYL	P, XT, *XAR5					; P   = In(n-1)Q24*B1{Q24}  = I16Q48,(lower half)
	QMPYL	ACC,XT,*XAR5++					; ACC = In(n-1)Q24*B1{Q24}  = I16Q48,(upper half)
	LSL64   ACC:P,#(32-24)					; ACC -> I8Q24
	ADDL    @XAR6,ACC						; XAR6 = XAR6+ACC = In(n-2)*B2+In(n-1)*B1

	MOVDL	XT,*+XAR4[4]					; XT  = In(n),   In(n-1) = In(n)
	IMPYL	P, XT, *XAR5					; P   = In(n)Q24*B0{Q24}  = I16Q48,(lower half)
	QMPYL	ACC,XT,*XAR5++					; ACC = In(n)Q24*B0{Q24}  = I16Q48,(upper half)
	LSL64   ACC:P,#(32-24)					; ACC -> I8Q24
	ADDL    @XAR6,ACC						; XAR6 = XAR6+ACC = In(n-2)*B2+In(n-1)*B1+In(n)*B0

	MOVL	XT,*+XAR4[2] 					; XT  = Out(n-2)
	IMPYL	P, XT, *XAR5					; P   = Out(n-2)Q24*A2{Q24}  = I16Q48,(lower half)
	QMPYL	ACC,XT,*XAR5++					; ACC = Out(n-2)Q24*A2{Q24}  = I16Q48,(upper half)
	LSL64   ACC:P,#(32-24)					; ACC -> I8Q24
	ADDL    @XAR6,ACC						; XAR6 = XAR6+ACC = In(n-2)*B2+In(n-1)*B1+In(n)*B0+Out(n-2)*A2

	MOVDL	XT,*+XAR4[0] 					; XT  = Out(n-1), Out(n-2)=Out(n-1)
	IMPYL	P, XT, *XAR5					; P   = Out(n-1)Q24*A1{Q24}  = I16Q48,(lower half)
	QMPYL	ACC,XT,*XAR5++					; ACC = Out(n-1)Q24*A1{Q24}  = I16Q48,(upper half)
	LSL64   ACC:P,#(32-24)					; ACC -> I8Q24
	ADDL    ACC,@XAR6						; ACC = XAR6+ACC = In(n-2)*B2+In(n-1)*B1+In(n)*B0+Out(n-2)*A2+Out(n-1)*A1
	MOVL	*XAR4, ACC						; In(n-1) = In(n) = ACC

; write result to output terminal (Q24)
	MOV     AR0,#10
    MOVL    *+XAR4[AR0],ACC

	LRETR
