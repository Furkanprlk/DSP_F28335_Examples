;;#############################################################################
;;! \file source/vector/memset_fast.asm
;;!
;;! \brief Optimized memory set, int->dest
;;! \author David M. Alter
;;! \date   07/15/11
;;
;; HISTORY:
;;   07/15/11 - original (D. Alter)
;;
;; DESCRIPTION: Optimized memory set, int->dest.
;;
;; FUNCTION:    extern void memset_fast(void*, int16, Uint16);
;;
;; USAGE:       memset_fast(dst, value, N);
;;
;; PARAMETERS:  void* dst = pointer to destination
;;              int16 value = initialization value
;;              N = number of 16-bit words to initialize
;;
;; RETURNS:     none
;;
;; BENCHMARK:   1 cycle per copy + ~20 cycles of overhead (including
;;   the call and return).  This assumes src and dst are located in
;;   different internal RAM blocks.
;;
;; NOTES:
;;   1) The function checks for the case of N=0 and just returns if true.
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

        .global _memset_fast
        .text

_memset_fast:
        ADDB        AH, #-1         ;Repeat "N-1" times
        BF          done, NC        ;Branch if N was zero
        RPT         @AH
    ||  MOV         *XAR4++, AL     ;Initialize the memory

;Finish up
done:
        LRETR                       ;return

;end of function memset_fast()
;*********************************************************************

       .end
;;#############################################################################
;;  End of File
;;#############################################################################
