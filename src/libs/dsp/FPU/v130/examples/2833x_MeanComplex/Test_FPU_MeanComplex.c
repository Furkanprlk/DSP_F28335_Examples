// =====================================================================================
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// -------------------------------------------------------------------------------------
//          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
//                          All Rights Reserved.
//======================================================================================
//
//  FILE:    Test_FPU_MeanComplex.c
//
//  TITLE:   Mean of complex vector test
//
//  AUTHOR:  David M. Alter, Texas Instruments Inc.
//
//  HISTORY: 
//      12/18/07 - original (D. Alter)
//
//######################################################################################
// $TI Release: C28x Floating Point Unit Library V1.30 $
// $Release Date: January 04, 2012 $
//######################################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "FPU.h"                // Main include file


// Global variables for complex_mean() test
#define N 4
complex_float y;
complex_float x[4];

void main(void)
{
//--- CPU Initialization
    InitSysCtrl();                      // Initialize the CPU
    DINT;
    InitPieCtrl();                      // Initialize and enable the PIE
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();
    EINT;                               // Enable Global interrupt INTM
    ERTM;                               // Enable Global realtime interrupt DBGM

// Create some dummy test data
	x[0].dat[0] =  2.0;    				// x_re
	x[0].dat[1] =  3.0;					// x_im
    x[1].dat[0] = -1.0;                 // x_re
    x[1].dat[1] = -3.0;                 // x_im
    x[2].dat[0] = -4.3;                 // x_re
    x[2].dat[1] =  2.2;                 // x_im
    x[3].dat[0] =  7.3;                 // x_re
    x[3].dat[1] = -1.1;                 // x_im

// Mean of complex vector test
// Exected result: mean.dat[0] = 1.0; mean.dat[1] = 0.275
    y.dat[0] = 0.0;
    y.dat[1] = 0.0;

    asm(" NOP");
	y = mean_SP_CV_2(x, N);
    asm(" NOP");

//--- Main Loop
	while(1)							// Dummy loop.  Wait for an interrupt.
	{
		asm(" NOP");
	}

} // end of main()

//===========================================================================
// End of File
//===========================================================================
