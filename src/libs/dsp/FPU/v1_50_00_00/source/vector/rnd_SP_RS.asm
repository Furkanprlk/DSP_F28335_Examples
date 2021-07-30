;;#############################################################################
;;! \file source/vector/rnd_SP_RS.asm
;;!
;;! \brief  C-Callable unbiased rounding of a floating point scalar
;;! \author David M. Alter
;;! \date   07/20/11
;;! 
;; FUNCTION:    extern float32 rnd_SP_RS(float32 x);
;;
;; USAGE:       y = rnd_SP_RS(x);
;;
;; PARAMETERS:  float32 x = input value
;;
;; RETURNS:     float32 y = result
;;
;; BENCHMARK:   18 cycles (including the call and return)
;;
;; NOTES:
;;   1) numerical examples:
;;      rnd_SP_RS(+4.4) = +4.0
;;      rnd_SP_RS(-4.4) = -4.0
;;      rnd_SP_RS(+4.5) = +5.0
;;      rnd_SP_RS(-4.5) = -5.0
;;      rnd_SP_RS(+4.6) = +5.0
;;      rnd_SP_RS(-4.6) = -5.0
;;   2) The C version of this, y = floor(x+0.5) takes 78 cycles using
;;      the rts2800_fpu32 library in c28x cgtools v6.0.1.
;;
;; Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/ 
;; ALL RIGHTS RESERVED
;;#############################################################################
;;$TI Release: C28x Floating Point Unit Library V1.50.00.00 $
;;$Release Date: Jun 2, 2015 $
;;#############################################################################
        .global _rnd_SP_RS
        .text

_rnd_SP_RS:
        CMPF32  R0H, #0.0         ;determine if x is positive or negative
        MOVST0  NF                ;copy NF flag to N bit in ST0
        BF      negative, LT      ;branch if x is negative

;x is positive
        ADDF32  R0H, #0.5, R0H    ;add 0.5 to x
        NOP                       ;delay slot for ADDF32
        FRACF32 R1H, R0H          ;R1H = fraction of R0H
        NOP                       ;delay slot for FRACF32
        SUBF32  R0H, R0H, R1H     ;subtract the fraction from x+0.5
        LRETR                     ;return

;x is negative
negative:
        ADDF32  R0H, #-0.5, R0H   ;subtract 0.5 from x
        NOP                       ;delay slot for ADDF32
        FRACF32 R1H, R0H          ;R1H = fraction of R0H
        NOP                       ;delay slot for FRACF32
        SUBF32  R0H, R0H, R1H     ;subtract the fraction from x+0.5
        LRETR                     ;return

;end of function rnd_SP_RS()
;*********************************************************************

       .end
       

;;#############################################################################
;;  End of File
;;#############################################################################
