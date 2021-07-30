;;#############################################################################
;;! \file source/vector/mpy_SP_RSxRVxRV_2.asm
;;!
;;! \brief  C-Callable multiplication of a real scalar, a real vector, and a 
;;!         real vector
;;! \author David M. Alter
;;! \date   07/15/11
;;
;; HISTORY:
;;   07/15/11 - original (D. Alter)
;;
;; DESCRIPTION: C-Callable multiplication of a real scalar, a real vector, 
;;              and a real vector
;;              y[i] = c*w[i]*x[i]
;;
;; FUNCTION: 
;;   extern void mpy_SP_RSxRVxRV_2(float32 *y, const float32 *w, 
;;                          const float32 *x, const float32 c, const Uint16 N)
;;
;; USAGE:       mpy_SP_RSxRVxRV_2(y, w, x, c, N);
;;
;; PARAMETERS:  float32 *y = result real array
;;              float32 *w = input real array #1
;;              float32 *x = input real array #2
;;              float32  c = input real scalar
;;              Uint16   N = length of w, x and y arrays
;;
;; RETURNS:     none
;;
;; BENCHMARK:   3*N + 22 cycles (including the call and return)
;;
;; NOTES:
;;   1) N must be even and at least 4.
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

        .global _mpy_SP_RSxRVxRV_2
        .text
_mpy_SP_RSxRVxRV_2:
        MOVL        XAR6, *-SP[4]    ;XAR6 = &x
                                     
        MOV32       *SP++, R4H       ;save R4H on stack
        MOV32       *SP++, R5H       ;save R5H on stack
        MOV32       *SP++, R6H       ;save R6H on stack
                                     
        LSR         AL, #1           ;divide N by 2
        ADDB        AL, #-2          ;subtract 2 from N since RPTB is 'n-1' 
                                     ;times and last iteration done separately
                                     
        MOV32       R6H, *XAR5++     ;load first w[i]
        MOV32       R2H, *XAR6++     ;load first x[i]
                                     
        MOV32       R4H, *XAR5++     ;load first w[i+1]
        MOV32       R5H, *XAR6++     ;load first x[i+1]
                                     
;---Main loop                        
        RPTB        end_loop, @AL    
                                     
        MPYF32      R3H, R6H, R2H    ;y[i] = w[i]*x[i]
        || MOV32    R6H, *XAR5++     ;load next w[i]
                                     
        MPYF32      R1H, R4H, R5H    ;y[i+1] = w[i+1]*x[i+1]
        || MOV32    R4H, *XAR5++     ;load next w[i+1]
                                     
        MPYF32      R3H, R3H, R0H    ;y[i] = c*w[i]*x[i]
        || MOV32    R2H, *XAR6++     ;load next x[i]
                                     
        MPYF32      R1H, R1H, R0H    ;y[i+1] = c*w[i+1]*x[i+1]
        || MOV32    R5H, *XAR6++     ;load next x[i+1]
                                     
        MOV32       *XAR4++, R3H     ;store y[i]
        MOV32       *XAR4++, R1H     ;store y[i+1]

end_loop:

;--- Last iteration done separately to avoid possible pointer overrun into 
;    undefined memory
        MPYF32      R3H, R6H, R2H    ;y[i] = w[i]*x[i]
        || MOV32    R6H, *--SP       ;restore R6H from stack
        MPYF32      R1H, R4H, R5H    ;y[i+1] = w[i+1]*x[i+1]
        || MOV32    R5H, *--SP       ;restore R5H from stack
        MPYF32      R3H, R3H, R0H    ;y[i] = c*w[i]*x[i]
        || MOV32    R4H, *--SP       ;restore R4H from stack
        MPYF32      R1H, R1H, R0H    ;y[i+1] = c*w[i+1]*x[i+1]
        MOV32       *XAR4++, R3H     ;store y[i]
        MOV32       *XAR4, R1H       ;store y[i+1]
                                     
;Finish up                           
        LRETR                        ;return

;end of function _mpy_SP_RSxRVxRV_2()
;*********************************************************************

       .end
;;#############################################################################
;;  End of File
;;#############################################################################
