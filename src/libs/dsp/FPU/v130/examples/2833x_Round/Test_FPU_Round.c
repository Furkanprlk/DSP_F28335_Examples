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
//  FILE:    Test_FPU_Round.c
//
//  TITLE:   Rounding test
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

#define N   6

void main(void)
{
volatile float32 x[N] = {4.4, -4.4, 4.5, -4.5, 4.6, -4.6};
volatile float32 y[N] = {0,0,0,0,0,0};
Uint16 i;
    
//--- CPU Initialization
    InitSysCtrl();                      // Initialize the CPU
    DINT;
    InitPieCtrl();                      // Initialize and enable the PIE
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();
    EINT;                               // Enable Global interrupt INTM
    ERTM;                               // Enable Global realtime interrupt DBGM

//--- round() test
    for(i=0; i<N; i++)
    {
        asm(" NOP");
        y[i] = rnd_SP_RS(x[i]);
        asm(" NOP");
    }

//--- Main Loop
	while(1)							// Dummy loop.  Wait for an interrupt.
	{
		asm(" NOP");
	}

} // end of main()

//===========================================================================
// End of File
//===========================================================================
