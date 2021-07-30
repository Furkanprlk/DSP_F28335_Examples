;;#############################################################################
;;! \file source/vector/add_SP_CSxCV.asm
;;!
;;! \brief  C-Callable addition of a complex scalar from a complex vector
;;! \author David M. Alter
;;! \date   07/15/11
;;
;; HISTORY:
;;   07/15/11 - original (D. Alter)
;;
;; DESCRIPTION: C-Callable addition of a complex scalar from a complex vector
;;              y_re[i] = x_re[i] + c_re
;;              y_im[i] = x_im[i] + c_im
;;
;; FUNCTION: 
;;   extern void add_SP_CSxCV(complex_float *y, const complex_float *x, const complex_float c, const Uint16 N)
;;
;; USAGE:        add_SP_CVxCV(y, w, c, N);
;;
;; PARAMETERS:  complex_float *y = result complex array
;;              complex_float *x = input complex array
;;              complex_float  c = input complex scalar
;;              Uint16 N = length of x and y arrays
;;
;; RETURNS:        none
;;
;; BENCHMARK:   4*N + 18 cycles (including the call and return)
;;
;; NOTES:
;;   1) N must be at least 2.
;;   2) The inputs and return value are of type 'complex_float':
;;
;;      typedef struct {
;;         float32 dat[2];
;;      } complex_float;
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

        .global _add_SP_CSxCV
        .text
        .word 0                       ;needed for RPTB alignment
_add_SP_CSxCV:                      
        MOVL        XAR6, *-SP[4]     ;XAR6 = &c
        MOV32       *SP++, R4H        ;save R4H on stack
        ADDB        AL, #-2           ;subtract 2 from N since RPTB is 'n-1' 
                                      ;times and last iteration done separately
                                    
        MOV32       R2H, *XAR6++      ;R0H = c_re
        MOV32       R3H, *XAR6        ;R1H = c_im
                                    
        MOV32       R4H, *XAR5++      ;load first x_re[i]
                                    
;---Main loop                       
        RPTB        end_loop, @AL   
                                    
        ADDF32      R0H, R4H, R2H     ;y_re[i] = x_re[i] + c_re
        || MOV32    R4H, *XAR5++      ;load next x_im[i]
                                    
        ADDF32      R1H, R4H, R3H     ;y_im[i] = x_im[i] + c_im
        || MOV32    R4H, *XAR5++      ;load next x_re[i]
                                    
        MOV32       *XAR4++, R0H      ;store y_re[i]
        MOV32       *XAR4++, R1H      ;store y_im[i]

end_loop:

;--- Last iteration done separately to avoid possible pointer overrun into 
;    undefined memory
        ADDF32      R0H, R4H, R2H     ;y_re[i] = x_re[i] + c_re
        || MOV32    R4H, *XAR5        ;load next x_im[i]

        ADDF32      R1H, R4H, R3H     ;y_im[i] = x_im[i] + c_im
        || MOV32    R4H, *--SP        ;restore R4H from stack

        MOV32       *XAR4++, R0H      ;store y_re[i]
        MOV32       *XAR4, R1H        ;store y_im[i]

;Finish up
        LRETR                         ;return

;end of function _add_SP_CSxCV()
;*********************************************************************

       .end
;;#############################################################################
;;  End of File
;;#############################################################################
