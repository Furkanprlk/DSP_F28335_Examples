//###########################################################################
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// ------------------------------------------------------------------------
//          Copyright (C) 2014-2015 Texas Instruments, Incorporated.
//                          All Rights Reserved.
// ========================================================================
//
// FILE:    FPU_CFFTF32.c
//
// TITLE:   32-bit floating point Complex FFT Sin/Cos Table Generaton
//
//###########################################################################
// $TI Release: C28x Floating Point Unit Library V1.40.00.00 $
// $Release Date: Mar 10, 2014 $
//###########################################################################

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

//#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "math.h"
#include "fpu_cfft.h"

void CFFT_f32_sincostable(CFFT_F32_STRUCT *cfft)
{
	int16_t	i;
	int16_t	TableSize;
	float	Rad;
	float	RadStep;
	
	RadStep = 1.57079632795f;	// RadStep = pi/2

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

//===========================================================================
// End of file
//===========================================================================

