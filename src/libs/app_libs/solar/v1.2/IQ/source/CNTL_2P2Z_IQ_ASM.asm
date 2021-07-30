
    .def _CNTL_2P2Z_IQ_ASM

_CNTL_2P2Z_IQ_ASM

	; because of C calling convention
	; XAR4 has the cntl3p3z coeff structure pointer
	; XAR5 has the cntl3p3z data buff internal pointer
	; ACC has the reference
	; *-SP[4] has the feedback value

	; calculate error (Ref - Fdbk)
	MOV     AR0,#10
    MOVL    ACC,*+XAR5[AR0]
	MOV     AR0,#12
    SUBL    ACC, *+XAR5[AR0]                ; ACC = Ref(Q24) - Fdbk(Q24)= error(Q24)
	LSL     ACC, #6							; Logical left shift by 6, Q{24}<<6 -> Q{30}

;store error in DBUFF
	MOVL	*+XAR5[4], ACC					; e(n) = ACC = error Q{30}

	ZAPA
; compute 3P3Z filter
	MOV		AR0,#8
	MOVL	XT, *+XAR5[AR0]					; XT  = e(n-2)
	QMPYL	P, XT, *XAR4++					; P   = e(n-2)Q30*B2{Q24} = I8Q22

    MOV     AR0,#6                          ;
	MOVDL	XT,*+XAR5[AR0]					; XT  = e(n-1),   e(n-2) = e(n-1)
	QMPYAL	P, XT, *XAR4++					; P   = e(n-1)Q30*B1{Q24}  = Q24, ACC = e(n-2)*B2
	
	MOVDL	XT,*+XAR5[4]					; XT  = e(n),   e(n-1) = e(n)
	QMPYAL	P, XT, *XAR4++					; P   = e(n)Q30*B0{Q24}  = Q24, ACC = e(n-2)*B2+e(n-1)*B1

	MOVL	XT,*+XAR5[2] 					; XT  = u(n-2)
	QMPYAL	P, XT, *XAR4++ 					; P   = u(n-2)*A2, ACC = e(n-2)B2 +e(n-1)*B1 + e(n)*B0

	MOVDL	XT,*+XAR5[0]					; XT  = u(n-1), u(n-1) = u(n-1)
	QMPYAL	P, XT, *XAR4++					; P   = u(n-1)*A1, ACC = e(n-2)*B2 + e(n-1)*B1 + e(n)*B0 + u(n-2)*A2

	ADDL	ACC, @P							; ACC =  e(n-2)*B2 + e(n-1)*B1 + e(n)*B0 + u(n-2)*A2 + u(n-1)*A1
    LSL     ACC, #2                         ; IQ22 to IQ24
; scale u(n):Q24, saturate (max>u(n)>min0), and save history

	MINL	ACC, *XAR4++ 					; saturate to < max (Q24)
	MAXL	ACC, *XAR4++                    ; saturate to the internal min >internal min (-1.0, Q24)
	MOVL    @XAR6, ACC						; save this value temporaily in XAR6

; Convert the internal u(n) to Q30 format and store in the data buffer
	LSL     ACC, #6							; Logical left shift by 6, Q{24}<<6 -> Q{30}
	MOVL	*XAR5, ACC						; u(n-1) = u(n) = ACC

	MOVL    ACC,@XAR6						; load the temporaily saved value in Q24 from XAR1 to ACC
	MAXL	ACC, *XAR4 						; saturate to > output min (Q24)

; write controller result to output terminal (Q24)
	MOV     AR0,#14
    MOVL    *+XAR5[AR0],ACC
	; ACCC has the output value


	LRETR
