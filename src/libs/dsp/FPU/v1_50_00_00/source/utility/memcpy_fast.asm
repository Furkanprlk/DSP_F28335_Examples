;;#############################################################################
;;! \file source/vector/memcpy_fast.asm
;;!
;;! \brief Optimized memory copy, src->dest.
;;! \author David M. Alter
;;! \date   07/06/11
;;
;;
;; HISTORY:
;;   07/06/11 - original (D. Alter)
;;   10/23/14 - Added note about non-interruptibility and no support for
;;              above 22 bit address. (D. Alter)
;;
;; DESCRIPTION: Optimized memory copy, src->dest.
;;
;; FUNCTION: 
;;   extern void memcpy_fast(void* dst, const void* src, Uint16 N);
;;
;; USAGE:       memcpy_fast(dst, src, N);
;;
;; PARAMETERS:  void* dst = pointer to destination
;;              const void* src = pointer to source
;;              N = number of 16-bit words to copy
;;
;; RETURNS:     none
;;
;; BENCHMARK:   1 cycle per copy + ~20 cycles of overhead (including
;;   the call and return).  This assumes src and dst are located in
;;   different internal RAM blocks.
;;
;; NOTES:
;;   1) The function checks for the case of N=0 and just returns if true.
;;   2) This function is not interruptible.  Use memcpy_fast_far instead for 
;;      interruptibility.
;;   3) This function does not support memory above 22 bits address.
;;      For input data above 22 bits address, use memcpy_fast_far instead.
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

        .global _memcpy_fast
        .text

_memcpy_fast:
        ADDB    AL, #-1                ;Repeat "N-1" times
        BF      done, NC               ;Branch if N was zero
        MOVL    XAR7, XAR5             ;XAR7 = XAR5 = dst
        RPT     @AL
    ||  PREAD   *XAR4++, *XAR7         ;Do the copy

;Finish up
done:
        LRETR                          ;return

;end of function memcpy_fast()
;*********************************************************************

       .end
;;#############################################################################
;;  End of File
;;#############################################################################
