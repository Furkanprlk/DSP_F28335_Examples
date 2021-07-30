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
//  FILE:    Test_FPU_VectorMath.c
//
//  TITLE:   Matrix and Vector Arithmetic Tests
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

// Global variables
#define N 4
float32 x1[N], x2[N], y[N];
complex_float w1[N], w2[N], z[N];
float32 c;

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

//--- mpy_SP_RSxRV_2() test
    x1[0] = -8.1;
    x1[1] =  2.2;
    x1[2] =  7.3;
    x1[3] = -1.1;
    y[0] =  0.0;
    y[1] =  0.0;
    y[2] =  0.0;
    y[3] =  0.0;
    c = 2.0;

    asm(" NOP");
	mpy_SP_RSxRV_2(y, x1, c, N);
    asm(" NOP");

//--- mpy_SP_RVxCV() test
    x1[0] =  2.0;
    x1[1] =  3.0;
    x1[2] = -1.0;
    x1[3] = -4.0;
    w1[0].dat[0] = 1.0;
    w1[0].dat[1] = 2.0;
    w1[1].dat[0] = 3.0;
    w1[1].dat[1] = 4.0;
    w1[2].dat[0] = 5.0;
    w1[2].dat[1] = 6.0;
    w1[3].dat[0] = 7.0;
    w1[3].dat[1] = 8.0;
    z[0].dat[0] = 0.0;
    z[0].dat[1] = 0.0;
    z[1].dat[0] = 0.0;
    z[1].dat[1] = 0.0;
    z[2].dat[0] = 0.0;
    z[2].dat[1] = 0.0;
    z[3].dat[0] = 0.0;
    z[3].dat[1] = 0.0;

    asm(" NOP");
    mpy_SP_RVxCV(z, w1, x1, N);
    asm(" NOP");

//--- mpy_SP_RVxRV_2() test
    x1[0] =  2.0;
    x1[1] =  3.0;
    x1[2] = -1.0;
    x1[3] = -4.0;
    x2[0] = -3.5;
    x2[1] =  2.0;
    x2[2] =  4.0;
    x2[3] = -5.0;
    y[0] =  0.0;
    y[1] =  0.0;
    y[2] =  0.0;
    y[3] =  0.0;

    asm(" NOP");
    mpy_SP_RVxRV_2(y, x1, x2, N);
    asm(" NOP");

//--- mpy_SP_RSxRVxRV_2() test
    x1[0] =  2.0;
    x1[1] =  3.0;
    x1[2] = -1.0;
    x1[3] = -4.0;
    x2[0] = -3.5;
    x2[1] =  2.0;
    x2[2] =  4.0;
    x2[3] = -5.0;
    y[0] =  0.0;
    y[1] =  0.0;
    y[2] =  0.0;
    y[3] =  0.0;
    c = 2.0;

    asm(" NOP");
    mpy_SP_RSxRVxRV_2(y, x1, x2, c, N);
    asm(" NOP");

//--- mpy_SP_CVxCV() test
    w1[0].dat[0] = 1.0;
    w1[0].dat[1] = 2.0;
    w1[1].dat[0] = 3.0;
    w1[1].dat[1] = 4.0;
    w1[2].dat[0] = 1.0;
    w1[2].dat[1] = 2.0;
    w1[3].dat[0] = 3.0;
    w1[3].dat[1] = 4.0;

    w2[0].dat[0] = -1.0;
    w2[0].dat[1] = -2.0;
    w2[1].dat[0] = -3.0;
    w2[1].dat[1] = -4.0;
    w2[2].dat[0] = -1.0;
    w2[2].dat[1] = -2.0;
    w2[3].dat[0] = -3.0;
    w2[3].dat[1] = -4.0;

//Result should be: (3-4j), (7-24j), (3-4j), (7-24j) 

    z[0].dat[0] = 0.0;
    z[0].dat[1] = 0.0;
    z[1].dat[0] = 0.0;
    z[1].dat[1] = 0.0;
    z[2].dat[0] = 0.0;
    z[2].dat[1] = 0.0;
    z[3].dat[0] = 0.0;
    z[3].dat[1] = 0.0;

    asm(" NOP");
    mpy_SP_CVxCV(z, w1, w2, N);
    asm(" NOP");

//--- sub_SP_CVxCV() and add_SP_CVxCV() test
    w1[0].dat[0] = 5.0;
    w1[0].dat[1] = 6.0;
    w1[1].dat[0] = 7.0;
    w1[1].dat[1] = 8.0;
    w1[2].dat[0] = 5.0;
    w1[2].dat[1] = 6.0;
    w1[3].dat[0] = 7.0;
    w1[3].dat[1] = 8.0;

    w2[0].dat[0] = -1.0;
    w2[0].dat[1] = -2.0;
    w2[1].dat[0] = -3.0;
    w2[1].dat[1] = -4.0;
    w2[2].dat[0] = -1.0;
    w2[2].dat[1] = -2.0;
    w2[3].dat[0] = -3.0;
    w2[3].dat[1] = -4.0;

    z[0].dat[0] = 0.0;
    z[0].dat[1] = 0.0;
    z[1].dat[0] = 0.0;
    z[1].dat[1] = 0.0;
    z[2].dat[0] = 0.0;
    z[2].dat[1] = 0.0;
    z[3].dat[0] = 0.0;
    z[3].dat[1] = 0.0;

    asm(" NOP");
    sub_SP_CVxCV(z, w1, w2, N);
    asm(" NOP");

    asm(" NOP");
    add_SP_CVxCV(z, w1, w2, N);
    asm(" NOP");

//--- sub_SP_CSxCV() and add_SP_CSxCV() test
    w1[0].dat[0] = 5.0;
    w1[0].dat[1] = 6.0;
    w1[1].dat[0] = 7.0;
    w1[1].dat[1] = 8.0;
    w1[2].dat[0] = 5.0;
    w1[2].dat[1] = 6.0;
    w1[3].dat[0] = 7.0;
    w1[3].dat[1] = 8.0;

    w2[0].dat[0] = 1.0;
    w2[0].dat[1] = -2.0;

    z[0].dat[0] = 0.0;
    z[0].dat[1] = 0.0;
    z[1].dat[0] = 0.0;
    z[1].dat[1] = 0.0;
    z[2].dat[0] = 0.0;
    z[2].dat[1] = 0.0;
    z[3].dat[0] = 0.0;
    z[3].dat[1] = 0.0;

    asm(" NOP");
    sub_SP_CSxCV(z, w1, w2[0], N);
    asm(" NOP");

    asm(" NOP");
    add_SP_CSxCV(z, w1, w2[0], N);
    asm(" NOP");


//--- Main Loop
	while(1)
	{
		asm(" NOP");
	}

} // end of main()

//===========================================================================
// End of File
//===========================================================================
