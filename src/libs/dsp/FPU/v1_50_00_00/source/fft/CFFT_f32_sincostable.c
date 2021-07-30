//#############################################################################
//! \file CFFT_f32_sincostable.c
//!
//! \brief  32-bit floating point Complex FFT Sin/Cos Table Generation
//! \author C2000
//! \date   January 6, 2011
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


//-----------------------------------------------------------------------------
// Function To Generate Complex FFT Coefficient (twiddle) Table:
//-----------------------------------------------------------------------------
// CFFT  Stages Address  Table Value                  
// SIZE           x16
//------+------+-------+------------------------------------------------
//  256 |   8  |     0 | SIN(   0*pi/128 )                    
//      .      .       .
//      |      |   128 | SIN(  64*pi/128 ) = COS(  0*pi/128)  
//      .      .       .
//      |      |   254 | SIN( 127*pi/128 ) = COS( 63*pi/128)
//      |      |   256 | SIN( 128*pi/128 ) = COS( 64*pi/128)
//      .      .       .
//      |      |   382 | SIN( 191*pi/128 ) = COS(127*pi/128)
//------+------+-------+------------------------------------------------
//  512 |   9  |     0 | SIN(   0*pi/256 )                    
//      .      .       .
//      |      |   256 | SIN( 128*pi/256 ) = COS(  0*pi/256)  
//      .      .       .
//      |      |   510 | SIN( 255*pi/256 ) = COS(127*pi/256)
//      |      |   512 | SIN( 256*pi/256 ) = COS(128*pi/256)
//      .      .       .
//      |      |   766 | SIN( 383*pi/256 ) = COS(255*pi/256)
//------+------+-------+------------------------------------------------
// 1024 |  10  |     0 | SIN(   0*pi/512 )                   
//      .      .       .
//      |      |   512 | SIN( 256*pi/512 ) = COS(  0*pi/512)  
//      .      .       .
//      |      |  1022 | SIN( 511*pi/512 ) = COS(255*pi/512)
//      |      |  1024 | SIN( 512*pi/512 ) = COS(256*pi/512)
//      .      .       .
//      |      |  1534 | SIN( 767*pi/512 ) = COS(511*pi/512)
//------+------+-------+------------------------------------------------

#include "math.h"
#include "fpu_cfft.h"

void CFFT_f32_sincostable(CFFT_F32_STRUCT_Handle cfft)
{
    int16_t    i;
    int16_t    TableSize;
    float    Rad;
    float    RadStep;
    
    RadStep = 1.57079632795f;    // RadStep = pi/2

    Rad = 0.0f;

    for(i=0; i < (cfft->Stages - 2); i++)
    {
        RadStep = RadStep * 0.5f;
    }

    TableSize = (1 << (cfft->Stages - 1));
    TableSize = TableSize + (TableSize >> 1);
    for(i=0; i < TableSize; i++)
    {
        cfft->CoefPtr[i] = sin(Rad);  
        Rad = Rad + RadStep;
    }

}

// End of file

