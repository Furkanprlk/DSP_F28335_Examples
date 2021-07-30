// ========================================================================
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// ------------------------------------------------------------------------
//          Copyright (C) 2011-2012 Texas Instruments, Incorporated.
//                          All Rights Reserved.
// ========================================================================
//
//
//  FILE:    Test_FPU_FastSqrt.c
//
//  TITLE:   DSP2833x Device Fast Square Root Test Program.   
//
//
//  DESCRIPTION:
//
//	
//	This software demonstrates the fast square root routine
//
//  FUNCTIONS:
//
//    float32 __ffsqrtf(float32 fInput)
//
//    Where fInput is the input variable
//
//  ASSUMPTIONS:
//
//     * sigIn and sigOut are of length SIGNAL_LENGTH
//     * N is 32, i.e. 32 tap filter
//	   * order = N - 1 = 31
//     * implementation of an equiripple FIR filter
//
//  Watch Variables:
//
//      fOutput             Output Variable
//      fInput				Input Variable
//
//
//###########################################################################
// $TI Release: C28x Floating Point Unit Library V1.31 $
// $Release Date: Sep 10, 2012 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "FPU.h"                // Main include file


// Global variables for __ffsqrtf() test
float32 fInput1, fInput2;
float32 fOutput1, fOutput2;
// The variable is declared as volatile to prevent the compiler 
// from optimizing them by storing them in registers. This allows
// the user to view the results in the watch window
volatile float32 fOutput3;

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
    fInput1 = 16777216.0;
    fInput2 = 5184.0;
    
// Back to Back calls of __ffsqrtf()
// Expected result: 4096 and 72
// Compiler optimization (-o2) should interleave the instructions of the back-to-back
// calls, completing both operations in 22 cycles. The variables will be optimized out
// and the FPU registers will be used instead. The user can check this in the disassembly
// view
    asm(" NOP");
	fOutput1 = __ffsqrtf(fInput1);
    fOutput2 = __ffsqrtf(fInput2);
    asm(" NOP");
    
    fOutput3 = fOutput1 + fOutput2;
    
    if(fOutput3 != 4168.0){
        asm(" ESTOP0");
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






