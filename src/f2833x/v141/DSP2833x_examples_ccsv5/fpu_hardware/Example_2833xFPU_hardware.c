//###########################################################################
// Description:
//! \addtogroup f2833x_example_list
//! <h1>Floating Point Unit (fpu_hardware)</h1>
//!
//! The code calculates two y=mx+b equations.  The variables are all
//! 32-bit floating-point.
//!
//! The compiler will generate floating point instructions to do these calculations.
//! To compile the project for floating point, the following Build Options were used:
//! -# Project->Properties-> C/C++ Build window-> Basic Settings->
//! C2000 Compiler Vx.x \n
//! In All Options textbox: add "--float_support=fpu32" . \n
//! OR in Runtime Model Options, under "Specify floating point support
//! (--float_support) pull-down menu: Select "fpu32".
//! -# Project->Properties-> C/C++ Build window-> Basic Settings->
//! C2000 Linker Vx.x-> File Search Path \n
//! In "Include linker file or command file as input (--library, -l)"
//! box, click green plus sign and add  rts2800_fpu32.lib
//! (run-time support library).
//! -# Not included in this example: If the project includes any other libraries,
//! they must also be compiled with floating point instructions.
//!
//! \b Watch \b Variables \n
//! - y1
//! - y2
//! - FPU registers (optional)
//
//###########################################################################
// $TI Release: F2833x/F2823x Header Files and Peripheral Examples V141 $
// $Release Date: November  6, 2015 $
// $Copyright: Copyright (C) 2007-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

float y1, y2;
float m1, m2;
float x1, x2;
float b1, b2;

void main(void)
{
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initialize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2833x_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2833x_DefaultIsr.c.
// This function is found in DSP2833x_PieVect.c.
   InitPieVectTable();

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.


// Step 5. User specific code, enable interrupts:
// Calculate two y=mx+b equations.

   y1 = 0;
   y2 = 0;
   m1 = .5;
   m2 = .6;
   x1 = 3.4;
   x2 = 7.3;
   b1 = 4.2;
   b2 = 8.9;

   y1 = m1*x1 + b1;
   y2 = m2*x2 + b2;


   ESTOP0;  // This is a software breakpoint
}


//===========================================================================
// No more.
//===========================================================================
