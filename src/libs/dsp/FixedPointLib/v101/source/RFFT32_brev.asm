; TI File $Revision: /main/2 $
; Checkin $Date: Thu Jan  6 15:14:02 2011 $
; ========================================================================
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
;                          All Rights Reserved.
; ========================================================================
;========================================================================
;
; File Name     : RFFT32_brev.asm
; 
; Originator    : Advanced Embeeded Control 
;                 Texas Instruments 
; 
; Description   : This file contains source code to bit reverse the N-point real-data sequence
;                 stored in contiguous  memory locations 
;               
; Date          : 26/2/2002
;======================================================================
; 
; Routine Type  : C Callable
; 
; Usage :
; void RFFT32_brev(int *src, int *dst, ushort size) 
; This function bit reverses the N-point real sequence stored in contiguous memory locations
; to perform N-point Complex FFT computation. If src=dst, then it performs in-place bit reversal.
; The destination array must be aligned to 2N words
;====================================================================
; INPUT ARRAY
;         |Xr(0)|
;         |Xr(1)|
;         |Xr(2)|
;         |Xr(3)|
;            :
;            :
;======================================================================
; ###########################################################################
; $TI Release: C28x Fixed Point Library v1.01 $
; $Release Date: January 11,2011 $
; ###########################################################################

                .def _RFFT32_brev
 
_RFFT32_brev:  
            MOVL    XAR0,XAR4       ; XAR0->src
            NOP     *,ARP5
            
            CMPR    0               ; TC=1, if src==dst
            BF      off_place,NTC   ; If not equal, jump to off place bit rev

; IN-PLACE BIT-REVERSAL
            MOVZ    AR6,AL          ; AR6=size
            SFR     ACC,#1          ; ACC=size/2
            MOVZ    AR7,AL          ; AR7=size/2
            SUBB    XAR7,#1         ; XAR7=(size/2)-1
            
            MOVL    ACC,XAR4        ; ACC=src
            
even_data: 
            MOVL    XT,*XAR4        ; XT=*src
            MOVL    P,*XAR5         ; P=*dst
            MOVL    XAR0,XAR4       ; XAR0=src
            CMPR    2               ; check src<dst
            BF      noswap,TC       ; if src<dst, do not swap *src & *dst
            
            MOVL    *XAR4,P         ; *src=*dst
            MOVL    *XAR5,XT        ; *dst=*src             
                           
noswap:     
            ADDB    XAR4,#4         ; XAR4=src+2
            MOVZ    AR0,AR6         ; AR0=size
            NOP     *BR0++          ; dst=br(dst+size)
            BANZ    even_data,AR7-- ; ARP=AR3, AR3->src+2, AR7=AR7-1

            MOVL    XAR4,ACC        ; XAR4=src
            ADDL    ACC,XAR0
            ADDL    ACC,XAR0        ; ACC=src+2*size
            MOVL    XAR5,ACC        ; XAR5=dst=src+2*size
            ADDB    XAR4,#2         ; XAR4=src+1
            
            MOV     ACC,AR6         ; ACC=size
            SFR     ACC,#1          ; ACC=size/2
            MOVZ    AR7,AL          ; AR7=size/2
            SUBB    XAR7,#1         ; XAR7=(size/2)-1
            
odd_data:  
            MOVL    XT,*XAR4        ; XT=*(src+1)                  
            ADDB    XAR4,#4         ; XAR4=src+3
            MOVL    *XAR5,XT        ; 
            NOP     *BR0++          
            BANZ    odd_data,AR7--      
            LRETR

; OFF-PLACE BIT-REVERSAL  
off_place:  
            MOVZ    AR7,AL          ; AR0=size
            SUBB    XAR7,#1         ; XAR7=size-1
            LSL     ACC,#1          ; ACC=2*size
            MOVZ    AR0,AL          ; AR0=2*size
            
next_data2: MOVL    ACC,*XAR4++     ; XAR4=src+1, ACCL=*src
            NOP     *,ARP5          ; ARP=XAR5
            MOVL    *BR0++,ACC      ; XAR5=br(dst+size)
            BANZ    next_data2,AR7--                 
            LRETR

