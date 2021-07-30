// =====================================================================================
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// -------------------------------------------------------------------------------------
//          Copyright (C) 2014-2015 Texas Instruments, Incorporated.
//                          All Rights Reserved.
//======================================================================================
//
//  FILE:    Test_FPU_ComplexAbsVec.c
//
//  TITLE:   Absolute value of a complex vector test (TMU0)
//
//  AUTHOR:  David M. Alter, Texas Instruments Inc.
//
//  HISTORY: 
//      12/18/07 - original (D. Alter)
//
//######################################################################################
// $TI Release: C28x Floating Point Unit Library V1.40.00.00 $
// $Release Date: Mar 10, 2014 $
//######################################################################################

#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "fpu_vector.h"		  // Main include file

// Global variables for the test
#define N 10
#define M 4
float y[N]={0,0,0,0,0,0,0,0,0,0};
float q[M]={0,0,0,0};
complex_float x[N], p[M];

void main(void)
{
//--- CPU Initialization
	InitSysCtrl();						// Initialize the CPU
    DINT;
	InitPieCtrl();						// Initialize and enable the PIE
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
    x[4].dat[0] = 0.0;                 // x_re
    x[4].dat[1] = 0.0;                 // x_im
    x[5].dat[0] =  7.3;                 // x_re
    x[5].dat[1] = -1.1;                 // x_im
    x[6].dat[0] =  7.3;                 // x_re
    x[6].dat[1] = -1.1;                 // x_im
    x[7].dat[0] = 0.0;                 // x_re
    x[7].dat[1] = 0.0;                 // x_im
    x[8].dat[0] = 0.0;                 // x_re
    x[8].dat[1] = 0.0;                 // x_im
    x[9].dat[0] = 0.0;                 // x_re
    x[9].dat[1] = 0.0;                 // x_im

// Absolute value of a complex vector test
// Exected result: y = [3.60555, 3.16228, 4.83011, 7.38241
//                      0.0      7.38241, 7.38241, 0.0
//                      0.0,     0.0]
    asm(" NOP");
	abs_SP_CV(y, x, N);			 	    // complex absolute value
    asm(" NOP");

    asm(" NOP");
    abs_SP_CV_2(y, x, N);               // complex absolute value (TMU0)
    asm(" NOP");

    // Create some dummy test data
	p[0].dat[0] =  2.0;    				// x_re
	p[0].dat[1] =  3.0;					// x_im
    p[1].dat[0] = -1.0;                 // x_re
    p[1].dat[1] = -3.0;                 // x_im
    p[2].dat[0] = -4.3;                 // x_re
    p[2].dat[1] =  2.2;                 // x_im
    p[3].dat[0] =  7.3;                 // x_re
    p[3].dat[1] = -1.1;                 // x_im

// Inverse absolute value of a complex vector test
// Exected result: q = [0.2773501, 0.3162278, 0.2070345, 0.1354571]
    asm(" NOP");
	iabs_SP_CV(q, p, M);			 	// inverse complex absolute value
    asm(" NOP");

    asm(" NOP");
    iabs_SP_CV_2(q, p, M);              // inverse complex absolute value  (TMU0)
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
