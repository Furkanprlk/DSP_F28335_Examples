;******************************************************************************
;******************************************************************************
; 
; FILE: cfft_64_brev_data.asm
; 
; DESCRIPTION: Input test data for the FFT
; 
;******************************************************************************
;  $TI Release: C28x VCU Library Version v1.10 $
;  $Release Date: September 26, 2011 $
;******************************************************************************
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
;                          All Rights Reserved.
;******************************************************************************
        ;.cdecls   C,LIST,"fft.h"
;############################################################################
;
;/*! \page CFFT_64_BREV_DATA (Input test data to the FFT)
;
; The input test data is a two tone function. We run the fft on this 
; data and compare to the expected output.
;*/
;############################################################################
         .sect .econst
         .global _CFFT16_64p_brev_in_data,_CFFT16_64p_brev_out_data,_BIT_REV_64_TBL
 
; FFT input data, two-tone test          
_CFFT16_64p_brev_in_data: 
        .word   0, 2232,  0, 1930,  0, 1165,  0, 286
        .word   0, -347,  0, -560,  0, -445,  0, -286
        .word   0, -373,  0, -809,  0, -1440,  0, -1930
        .word   0, -1957,  0, -1406,  0, -445,  0, 560
        .word   0, 1237,  0, 1406,  0, 1165,  0, 809
        .word   0, 648,  0, 809,  0, 1165,  0, 1406
        .word   0, 1237,  0, 560,  0, -445,  0, -1406
        .word   0, -1957,  0, -1930,  0, -1440,  0, -809
        .word   0, -373,  0, -286,  0, -445,  0, -560
        .word   0, -347,  0, 286,  0, 1165,  0, 1930
        .word   0, 2232,  0, 1930,  0, 1165,  0, 286
        .word   0, -347,  0, -560,  0, -445,  0, -286
        .word   0, -373,  0, -809,  0, -1440,  0, -1930
        .word   0, -1957,  0, -1406,  0, -445,  0, 560
        .word   0, 1237,  0, 1406,  0, 1165,  0, 809
        .word   0, 648,  0, 809,  0, 1165,  0, 1406


; FFT output data
_CFFT16_64p_brev_out_data: 
        .word   0, 75,  17, 83,  51, 119,  383, 569
        .word   -109, -113,  -53, -40,  -37, -20,  -28, -11
        .word   -23, 390,  -19, -3,  -17, -1,  -15, 1
        .word   -13, 2,  -11, 2,  -10, 4,  -9, 4
        .word   -8, 5,  -7, 5,  -7, 5,  -6, 6
        .word   -5, 5,  -5, 5,  -5, 6,  -4, 6
        .word   -4, 6,  -3, 6,  -3, 6,  -2, 6
        .word   -1, 6,  -2, 7,  -1, 6,  0, 5
        .word   0, 7,  0, 5,  1, 6,  2, 7
        .word   1, 6,  2, 6,  3, 6,  3, 6
        .word   4, 6,  4, 6,  5, 6,  5, 5
        .word   5, 5,  6, 6,  7, 5,  7, 5
        .word   8, 5,  9, 4,  10, 4,  11, 2
        .word   13, 2,  15, 1,  17, -1,  19, -3
        .word   23, 390,  28, -11,  37, -20,  53, -40
        .word   109, -113,  -383, 569,  -51, 119,  -17, 83
        
_BIT_REV_64_TBL:
        .word  0, 64, 32, 96, 16, 80, 48, 112
        .word  8, 72, 40, 104, 24, 88, 56, 120
        .word  4, 68, 36, 100, 20, 84, 52, 116
        .word  12, 76, 44, 108, 28, 92, 60, 124
        .word  2, 66, 34, 98, 18, 82, 50, 114
        .word  10, 74, 42, 106, 26, 90, 58, 122
        .word  6, 70, 38, 102, 22, 86, 54, 118
        .word  14, 78, 46, 110, 30, 94, 62, 126
