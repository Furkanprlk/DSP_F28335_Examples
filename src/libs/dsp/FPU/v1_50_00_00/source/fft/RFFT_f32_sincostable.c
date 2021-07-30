//#############################################################################
//! \file RFFT_f32_sincostable.c
//!
//! \brief  32-bit floating point Real FFT Sin/Cos Table Generation
//! \author C2000
//
//  Group:             C2000
//  Target Family:     C28x+FPU32
//
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/ 
// ALL RIGHTS RESERVED 
//#############################################################################
//$TI Release: C28x Floating Point Unit Library V1.50.00.00 $
//$Release Date: Jun 2, 2015 $
//#############################################################################

#include "math.h"
#include "fpu_rfft.h"

//===========================================================================
// Function: void RFFT_f32_sincostable(RFFT_F32_STRUCT *fft)
//===========================================================================
//
// Sin/Cos table contains the following entries:
//
//     +-------------------+
//   0 | COS( 1*2*PI/8)    | Stages 1,2,3
//   1 | SIN( 1*2*PI/8)    |
//   2 |        0.0        |
//   3 |        1.0        |
//     +-------------------+
//   4 | COS( 1*2*PI/16)   |
//   5 | SIN( 1*2*PI/16)   |
//   6 | COS( 2*2*PI/16)   | Stage 4
//   7 | SIN( 2*2*PI/16)   |
//   8 | COS( 3*2*PI/16)   |
//   9 | SIN( 3*2*PI/16)   |
//  10 |        0.0        |
//  11 |        1.0        |
//     +-------------------+
//  12 | COS( 1*2*PI/32)   |
//  13 | SIN( 1*2*PI/32)   |
//  14 | COS( 2*2*PI/32)   |
//  15 | SIN( 2*2*PI/32)   |
//  16 | COS( 3*2*PI/32)   |
//  17 | SIN( 3*2*PI/32)   |
//  18 | COS( 4*2*PI/32)   | Stage 5
//  19 | SIN( 4*2*PI/32)   |
//  20 | COS( 5*2*PI/32)   |
//  21 | SIN( 5*2*PI/32)   |
//  22 | COS( 6*2*PI/32)   |
//  23 | SIN( 6*2*PI/32)   |
//  24 | COS( 7*2*PI/32)   |
//  25 | SIN( 7*2*PI/32)   |
//  26 |        0.0        |
//  27 |        1.0        |
//     +-------------------+
//  28 . COS( N*2*PI/64)   . Stage 6  (N = 1 to 15)
//     . SIN( N*2*PI/64)   .
//     |        0.0        |
//     |        1.0        |
//     +-------------------+
//     . COS( N*2*PI/128)  . Stage 7  (N = 1 to 31)
//     . SIN( N*2*PI/128)  .
//     |        0.0        |
//     |        1.0        |
//     +-------------------+
//     . COS( N*2*PI/256)  . Stage 8  (N = 1 to 63)
//     . SIN( N*2*PI/256)  .
//     |        0.0        |
//     |        1.0        |
//     +-------------------+
//     . COS( N*2*PI/512)  . Stage 9  (N = 1 to 127)
//     . SIN( N*2*PI/512)  .
//     |        0.0        |
//     |        1.0        |
//     +-------------------+
//     . COS( N*2*PI/1024) . Stage 10 (N = 1 to 255)
//     . SIN( N*2*PI/1024) .
//     |        0.0        |
//     |        1.0        |
//     +-------------------+
//
// Note: Table size for 1K FFT Real = 990 entries
//---------------------------------------------------------------------------

void RFFT_f32_sincostable(RFFT_F32_STRUCT_Handle fft)
{
    float  tempPI, temp;
    uint16_t i, j, k, l, N;

    tempPI = 0.7853981633975;   // pi/4
    k = 1;
    l = 0;
    for(i = 3; i <= fft->FFTStages; i++)
    {
        N = 1;
        for(j=1; j <= k; j ++)
        {
            temp = (float)N * tempPI;
            fft->CosSinBuf[l++] = cos(temp);
            fft->CosSinBuf[l++] = sin(temp);
            N++;
        }
        fft->CosSinBuf[l++] = 0.0;
        fft->CosSinBuf[l++] = 1.0;
        k = (k * 2) + 1;
        tempPI = tempPI * 0.5;
    }
}

// End of file

