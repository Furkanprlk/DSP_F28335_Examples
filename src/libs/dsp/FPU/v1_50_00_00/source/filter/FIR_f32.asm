;;#############################################################################
;;! \file source/filter/FIR_f32.asm
;;!
;;! \brief  Finite Impulse Response Filter
;;! \author C2000   
;;
;; DESCRIPTION:
;;
;;  This routine implements the non-recursive difference equation of an 
;;  all-zero filter(FIR), of order N. All the coefficients of all-zero 
;;  filter are assumed to be less than 1 in magnitude.    
;;
;; FUNCTIONS:
;;
;;  void FIR_FP_calc(FIR_FP_handle) 
;;  
;;  where FIR_FP_handle is a pointer to a structure defined as:
;;
;;  typedef struct { 
;;   float *coeff_ptr;       /*  0 Pointer to Filter co-efficient array */
;;   float *dbuffer_ptr;     /*  2 Delay buffer pointer                 */ 
;;   int   cbindex;          /*  4 Circular Buffer Index                */
;;   int   order;            /*  5 Order of the filter                  */
;;   float input;            /*  6 Input data                           */
;;   float output;           /*  8 Output data                          */ 
;;   void  (*init)(void *)   /* 10 Pointer to init fun                  */  
;;   void  (*calc)(void *);  /* 12 Pointer to the calculation function  */
;;  }FIR_FP; 
;;
;; ALGORITHM:
;;
;; Difference Equation :
;;
;;       y(n)=H(0)*x(n)+H(1)*x(n-1)+H(2)*x(n-2)+....+H(N)*x(n-N)
;;
;;      where
;;              y(n)=output sample of the filter at index n 
;;              x(n)=input sample of the filter at index n 
;;
;; Transfer Function :
;;                                  
;;              Y(z)                -1        -2               -N+1       -N
;;             ----- = h(0) + h(1) z  + h(2) z  + ... +h(N-1) z   + h(N) z    
;;              X(z)
;;
;;     Network Diagram  : 
;;
;;     dbuffer[0]          dbuffer[1]    dbuffer[2]    dbuffer[N}
;;     Input           -1  x(n-1)  -1    x(n-2)        x(n-N)
;;   x(n) >------o----z---->-o----z---->-o---  - ->- - o
;;               |           |           |             |
;;               |           |           |             |
;;               |           |           |             |
;;               v H(0)      v H(1)      v H(2)        v H(N)  
;;               |           |           |             |  
;;               |           |           |             |        output
;;               |---->-----(+)---->----(+)-- - -> -  (+)-----> y(n)    
;;
;;       Symbols Used :
;;             H(0),H(1),H(2),...,H(N) : filter coefficients
;;            x(n-1),x(n-2),...,x(n-N) : filter states
;;                                x(n) : filter input 
;;                                y(n) : filter output
;;
;;  Group:            C2000
;;  Target Family:    C28x+FPU32
;;
;; Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/ 
;; ALL RIGHTS RESERVED
;;#############################################################################
;;$TI Release: C28x Floating Point Unit Library V1.50.00.00 $
;;$Release Date: Jun 2, 2015 $
;;#############################################################################

; Module definition for external referance
                .def    _FIR_FP_init 
                .def    _FIR_FP_calc


;==============================================================================
; Function: FIR_FP_init() - Initialize the FIR_FP handle and data buffer
;
; Input - FIR_FP structure pointer
; Returns - void
;
; Implementation specifics:
;   Regs used: XAR - 4,6
;==============================================================================


_FIR_FP_init:
            .c28_amode
            ZAPA
            MOVL    *+XAR4[6], ACC    ; XAR4->ouput, input=0
            ADDB    XAR4, #2          ; Only 0...7 Index allowed
            MOVL    *+XAR4[6], ACC    ; output=0

            MOVL    XAR6, *+XAR4[0]   ; XAR6=dbuffer_ptr            
            MOV     *+XAR4[2], #0     ; cbindex=0

            MOV     ACC, *+XAR4[3] << #1  ; AL = order*2 (for float)
            ADDB    AL, #1
            
            RPT     AL                ; order+1
            || MOV  *XAR6++, #0       ; zero the data buf.
            
            LRETR


;==============================================================================
; Function: FIR_FP_calc() - Compute the FIR out-put for the next sample.
;
; Input - FIR_FP structure pointer
; Returns - void
;
; Description: Input from FIR_FP is stored in the input buffer and output is
;       returned through the FIR_FP structure.
;
; Implementation specifics:
; - This file requires the --c2xlp_src_compatible option to be enabled as
;   it uses the circular addressing mode for C2xLP devices which permits
;   circular buffers > 256 words (upto 65536 words). This does however require
;   the dbuffer be aligned to a 16-bit boundary;
;
; Register Usage:
;   XAR0: Counter used in the repeat loop / index into the structure
;   AR1L: Offset used in circular addressing
;   AR1H: length of the dbuffer in words
;   XAR2: input sample
;   XAR3: Store the cbindex temporarily
;   XAR4: Points to the argument object
;   XAR5:
;   XAR6: Points to the start of the dbuffer
;   XAR7: Points to the coefficient buffer
;==============================================================================
;; Argument structure defines
ARG_DBUFFPTR    .set    0
ARG_CBINDEX     .set    2
ARG_ORDER       .set    3
ARG_INPUT       .set    4
ARG_OUTPUT      .set    6

_FIR_FP_calc:
    .c28_amode
    ;; Context Save
    MOV32     R0H, R6H                           ; Store R6H, R7H in R0H, R1H
    MOV32     R1H, R7H
    PUSH      XAR1
    PUSH      XAR2
    PUSH      XAR3
    ZERO      R6H
    ZERO      R7H
    ZERO      R3H
    ZERO      R2H
    MOVL      XAR7, *XAR4++                      ; XAR7 -> coefficients
    MOVL      XAR6, *+XAR4[ARG_DBUFFPTR]         ; XAR6 -> dbuffer
    MOV       AL, *+XAR4[ARG_CBINDEX]            ; AL = current offset
    MOV       AH, *+XAR4[ARG_ORDER]              ; AH =  order * 2
    LSL       AH, #1                             ; We want to circle back when AR1L matches the
                                                 ; address after the end of the dbuffer
    MOVL      XAR1, ACC                          ; [AR1H : AR1L] = [end of dbuffer: current position in dbuffer]
    MOVZ      AR0, *+XAR4[ARG_ORDER]             ; AR0 = order (nTaps - 1)
    MOVL      XAR2, *+XAR4[ARG_INPUT]            ; XAR2 = x(0)

    .lp_amode
    SETC      AMODE                              ; C2xLP addressing mode to allow *+XAR6[AR1%++]`

    MOVL      *+XAR6[AR1%++], XAR2               ; Store x(0), advance AR1 to point to x(N-1)
    MOVZ      AR3, AR1                           ;
    RPT       AR0                                ; Repeat order + 1 times
 || MACF32    R7H, R3H, *+XAR6[AR1%++], *XAR7++  ; R3H = R3H + R2H | R2H = x(N-k-1) * h(k) odd cycles
                                                 ; R7H = R7H + R6H | R6H = x(N-k-1) * h(k) even cycles
    .c28_amode
    CLRC      AMODE                              ; Back to C28x addressing mode
    MOV       *+XAR4[ARG_CBINDEX], AR3           ; Store AR1 as the index for the next sample
    ADDF32    R3H, R3H, R2H                      ; Final odd accumulate
    ADDF32    R7H, R7H, R6H                      ; Final even accumulate

    ;; Restore XAR1, 2, 3, R6H while doing the final accumulate
    POP       XAR3
    POP       XAR2
    POP       XAR1
    ADDF32    R7H, R7H, R3H                      ; Final accumulate
    MOV32     R6H, R0H

    ;; Save final output and restore R7H
    MOV32     *+XAR4[ARG_OUTPUT], R7H
    MOV32     R7H, R1H

    LRETR

;;#############################################################################
;;  End of File
;;#############################################################################

