; =============================================================================
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2011-2012 Texas Instruments, Incorporated.
;                          All Rights Reserved.
; =============================================================================
;
; FILE:        memcpy_fast.asm
;
; AUTHOR:      David M. Alter, Texas Instruments Inc.
;
; HISTORY:
;   07/06/11 - original (D. Alter)
;
; DESCRIPTION: Optimized memory copy, src->dest.
; FUNCTION: 
;   extern void memcpy_fast(void* dst, const void* src, Uint16 N);
; USAGE:       memcpy_fast(dst, src, N);
; PARAMETERS:  void* dst = pointer to destination
;              const void* src = pointer to source
;              N = number of 16-bit words to copy
; RETURNS:     none
; BENCHMARK:   1 cycle per copy + ~20 cycles of overhead (including
;   the call and return).  This assumes src and dst are located in
;   different internal RAM blocks.
; NOTES:
;   1) The function checks for the case of N=0 and just returns if true.
;
; =============================================================================
; ###########################################################################
; $TI Release: C28x Floating Point Unit Library V1.31 $
; $Release Date: Sep 10, 2012 $
; ###########################################################################

		.global _memcpy_fast
		.text

_memcpy_fast:
		ADDB AL, #-1							;Repeat "N-1" times
		BF done, NC								;Branch if N was zero
		MOVL XAR7, XAR5							;XAR7 = XAR5 = dst
		RPT @AL
	||	PREAD *XAR4++, *XAR7					;Do the copy

;Finish up
done:
		LRETR									;return

;end of function memcpy_fast()
;*********************************************************************

       .end
;--------------------------------------------------------------------------
;            Copyright (c) 2011-2012 Texas Instruments, Incorporated.
;                           All Rights Reserved.
;===========================================================================
;===========================================================================
; End of File.
;===========================================================================
