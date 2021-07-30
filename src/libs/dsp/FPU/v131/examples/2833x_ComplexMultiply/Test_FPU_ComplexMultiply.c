// =====================================================================================
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// -------------------------------------------------------------------------------------
//          Copyright (C) 2011-2012 Texas Instruments, Incorporated.
//                          All Rights Reserved.
//======================================================================================
//
//  FILE:    Test_FPU_ComplexMultiply.c
//
//  TITLE:   Complex Multiplication Test   
//
//  AUTHOR:  David M. Alter, Texas Instruments Inc.
//
//  HISTORY: 
//      12/18/07 - original (D. Alter)
//
//######################################################################################
// $TI Release: C28x Floating Point Unit Library V1.31 $
// $Release Date: Sep 10, 2012 $
//######################################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "FPU.h"                // Main include file

// Global variables for complex multiply test
complex_float w,x,y;


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

// Complex multiply test
	x.dat[0]=2.0;						// x_re
	x.dat[1]=3.0;						// x_im
	w.dat[0]=4.0;						// w_re
	w.dat[1]=5.0;						// w_im
	y.dat[0]=0;
	y.dat[1]=0;
// Result is y = -7 + j*22

    asm(" NOP");
	y = mpy_SP_CSxCS(w,x);				// complex multiply
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

