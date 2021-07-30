// TI File $Revision: /main/2 $
// Checkin $Date: May 28, 2009   16:21:03 $
//###########################################################################
//
// FILE:   main.c
//
// TITLE:  CLA Macro Test Program
//
// ASSUMPTIONS:
//
//   This program requires the DSP2803x header files.
//
//   This is a basic program to exercise the CLA cosine per unit macro.
//
//   Task2 is used to clear all of the results
//   Task1 is populated with multiple instances of the cosine & cosine per unit macro.
//   Macro input and output are through the message RAMs
//   The CLAsincosTable is loaded directly into CLA RAM1
//
//   Watch Variables:
//
//      PASS_COUNT          Number of checks that have passed
//      FAIL_COUNT          Number of checks that have failed
//                          This should be 0 at the end of the
//                          program
//      GOLDEN_PASS_COUNT   This will match PASS_COUNT at the end
//                          of the program
//
//###########################################################################
// $TI Release: CLAmath Version 3.00 $
// $Release Date: Oct 15, 2010 $
//###########################################################################
#include "DSP28x_Project.h"  // Device Headerfile and Examples Include File
#include "CLAShared.h"       // Shared between C and CLA assembly

//-------------------------------------------------------------
// Using DATA_SECTION pragma statements, these variables are
// placed in assembly sections that the linker .cmd file will
// allocate to the CLA message RAMs.
// These variables are used to pass input from the CPU to the CLA
// and output from the CLA to the CPU.
//
// Note:
// The cos macro also uses the _CLAsincosTable. This table
// is in the CLAmathTables assembly section.  This
// For this example, this section is loaded directly into
// CLA data memory in the linker .cmd file.//
//-------------------------------------------------------------

#pragma DATA_SECTION(Cla1ToCpuMsg,"Cla1ToCpuMsgRAM");
struct  CLA_TO_CPU_MSG_RAM Cla1ToCpuMsg;

#pragma DATA_SECTION(CpuToCla1Msg,"CpuToCla1MsgRAM");
struct  CPU_TO_CLA_MSG_RAM CpuToCla1Msg;


// Global variables used in this example
//

Uint16 PASS_COUNT = 0;          // If all tests pass, this should equal golden value
Uint16 FAIL_COUNT = 0;          // Number of tests that failed
Uint16 GOLDEN_PASS_COUNT = 10;  // Number of test in this program
float y_cos0,y_cospu0;
float y_cos1,y_cospu1;
float y_cos2,y_cospu2;
float y_cos3,y_cospu3;
float y_cos4,y_cospu4;
float y_cos5,y_cospu5;
float y_cos6,y_cospu6;
float y_cos7,y_cospu7;
float y_cos8,y_cospu8;
float y_cos9,y_cospu9;


void main(void)
{
   DisableDog();                // Disable the watchdog

//-------------------------------------------------------------
// CLA module initialization
// 1) Enable the CLA clock
// 2) Init the CLA interrupt vectors
// 3) Allow the IACK instruction to flag a CLA interrupt/start a task
// 4) Assign CLA program and data memory to the CLA
// 5) Enable CLA interrupts (MIER)
//
// Note: As provided, the linker .cmd file links the CLA assembly
//       code directly to the CLA program memory. Likewise the
//       CLA data is copied directly to CLA data memory.
//       This way the debugger will load the CLA assembly code
//       into the program memory.  (No need to copy the CLA code
//       or data during debug).
//
//-------------------------------------------------------------
   EALLOW;
   SysCtrlRegs.PCLKCR3.bit.CLA1ENCLK = 1;
   Cla1Regs.MVECT1 = (Uint16) (&Cla1Task1 - &Cla1Prog_Start)*sizeof(Uint32);
   Cla1Regs.MVECT2 = (Uint16) (&Cla1Task2 - &Cla1Prog_Start)*sizeof(Uint32);
   Cla1Regs.MVECT3 = (Uint16) (&Cla1Task3 - &Cla1Prog_Start)*sizeof(Uint32);
   Cla1Regs.MVECT4 = (Uint16) (&Cla1Task4 - &Cla1Prog_Start)*sizeof(Uint32);
   Cla1Regs.MVECT5 = (Uint16) (&Cla1Task5 - &Cla1Prog_Start)*sizeof(Uint32);
   Cla1Regs.MVECT6 = (Uint16) (&Cla1Task6 - &Cla1Prog_Start)*sizeof(Uint32);
   Cla1Regs.MVECT7 = (Uint16) (&Cla1Task7 - &Cla1Prog_Start)*sizeof(Uint32);
   Cla1Regs.MVECT8 = (Uint16) (&Cla1Task8 - &Cla1Prog_Start)*sizeof(Uint32);
   Cla1Regs.MCTL.bit.IACKE = 1;
   Cla1Regs.MMEMCFG.bit.PROGE = 1;
   Cla1Regs.MMEMCFG.bit.RAM1E = 1;
   asm("    RPT #3 || NOP");
   Cla1Regs.MIER.bit.INT1 = 1;
   Cla1Regs.MIER.bit.INT2 = 1;
   Cla1Regs.MIER.bit.INT3 = 1;
   Cla1Regs.MIER.bit.INT4 = 1;
   Cla1Regs.MIER.bit.INT5 = 1;
   Cla1Regs.MIER.bit.INT6 = 1;
   Cla1Regs.MIER.bit.INT7 = 1;
   Cla1Regs.MIER.bit.INT8 = 1;
   EDIS;

//-------------------------------------------------------------
// Task 2: Clear all output variables
//
// Force Task 2 by the IACK instruction
// Wait for the task to complete
// This macro is defined in the Cla_Defines.h file
//-------------------------------------------------------------

    Cla1ForceTask2andWait();

//-------------------------------------------------------------
// Initialize the input data
//-------------------------------------------------------------

    CpuToCla1Msg.rad0  = -1.0;                  // -2*pi   =  1.0               !! cosPU
    CpuToCla1Msg.rad1  = -6.283185;             // -2*pi   =  1.0								
    CpuToCla1Msg.rad2  = -0.375;				// -3*pi/4 =  0.707106781187    !! cosPU
    CpuToCla1Msg.rad3  = -2.35619449020;        // -3*pi/4 =  0.707106781187
    CpuToCla1Msg.rad4  = -0.25;                 // -2*pi/4 =  0.0               !! cosPU
    CpuToCla1Msg.rad5  = -1.570796326795;       // -2*pi/4 =  0.0
    CpuToCla1Msg.rad6  = -0.125;                // -1*pi/4 =  0.707106781187    !! cosPU
    CpuToCla1Msg.rad7  = -0.7853981633975;      // -1*pi/4 =  0.707106781187
    CpuToCla1Msg.rad8  =  0.0;                  //         =  1.0               !! cosPU
    CpuToCla1Msg.rad9  =  0.0;                  //         =  1.0
    CpuToCla1Msg.rad10 =  0.125;                //  1*pi/4 =  0.707106781187    !! cosPU
    CpuToCla1Msg.rad11 =  0.7853981633975;      //  1*pi/4 =  0.707106781187
    CpuToCla1Msg.rad12 =  0.25;                 //  2*pi/4 =  0.0               !! cosPU
    CpuToCla1Msg.rad13 =  1.570796326795;       //  2*pi/4 =  0.0
    CpuToCla1Msg.rad14 =  0.50;                 //  4*pi/4 = -1.0               !! cosPU
    CpuToCla1Msg.rad15 =  3.14159265359;        //  4*pi/4 = -1.0 
    CpuToCla1Msg.rad16 =  0.375;                //  3*pi/4 =  0.707106781187    !! cosPU
    CpuToCla1Msg.rad17 =  2.356194490193;       //  3*pi/4 =  0.707106781187
    CpuToCla1Msg.rad18 =  1.0;                  //  2*pi   =  1.0               !! cosPU
    CpuToCla1Msg.rad19 =  6.28318530718;        //  2*pi   =  1.0

//-------------------------------------------------------------
// Force Task 1 by the IACK instruction
// Wait for the task to complete
// This macro is defined in the Cla_Defines.h file
//
// Note: Task 1 is setup to run the macro on rad0 - rad19
// The results of cosine per unit and cosine are stored in "y_cospu0 to y_cospu9"
// & "y_cos0 to y_cos9" respectively.
//
//-------------------------------------------------------------

    Cla1ForceTask1andWait();

//-------------------------------------------------------------
//-------------------------------------------------------------
         y_cospu0=Cla1ToCpuMsg.y0.f32;       y_cos0=Cla1ToCpuMsg.y1.f32;
         y_cospu1=Cla1ToCpuMsg.y2.f32;       y_cos1=Cla1ToCpuMsg.y3.f32;
         y_cospu2=Cla1ToCpuMsg.y4.f32;       y_cos2=Cla1ToCpuMsg.y5.f32;
         y_cospu3=Cla1ToCpuMsg.y6.f32;       y_cos3=Cla1ToCpuMsg.y7.f32;
         y_cospu4=Cla1ToCpuMsg.y8.f32;       y_cos4=Cla1ToCpuMsg.y9.f32;

         y_cospu5=Cla1ToCpuMsg.y10.f32;      y_cos5=Cla1ToCpuMsg.y11.f32;
         y_cospu6=Cla1ToCpuMsg.y12.f32;      y_cos6=Cla1ToCpuMsg.y13.f32;
         y_cospu7=Cla1ToCpuMsg.y14.f32;      y_cos7=Cla1ToCpuMsg.y15.f32;
         y_cospu8=Cla1ToCpuMsg.y16.f32;      y_cos8=Cla1ToCpuMsg.y17.f32;
         y_cospu9=Cla1ToCpuMsg.y18.f32;      y_cos9=Cla1ToCpuMsg.y19.f32;

//-------------------------------------------------------------
// When the task completes, check the results
//-------------------------------------------------------------

    if(Cla1ToCpuMsg.y0.i32 == Cla1ToCpuMsg.y1.i32)
        PASS_COUNT++;
    else
        FAIL_COUNT++;

    if(Cla1ToCpuMsg.y2.i32 ==  Cla1ToCpuMsg.y3.i32)
        PASS_COUNT++;
    else
        FAIL_COUNT++;

    if(Cla1ToCpuMsg.y4.i32 == Cla1ToCpuMsg.y5.i32)
        PASS_COUNT++;
    else
        FAIL_COUNT++;

    if(Cla1ToCpuMsg.y6.i32 == Cla1ToCpuMsg.y7.i32)
        PASS_COUNT++;
    else
        FAIL_COUNT++;

    if(Cla1ToCpuMsg.y8.i32 == Cla1ToCpuMsg.y9.i32)
        PASS_COUNT++;
    else
        FAIL_COUNT++;

	 if(Cla1ToCpuMsg.y10.i32 == Cla1ToCpuMsg.y11.i32)
        PASS_COUNT++;
    else
        FAIL_COUNT++;

    if(Cla1ToCpuMsg.y12.i32 ==  Cla1ToCpuMsg.y13.i32)
        PASS_COUNT++;
    else
        FAIL_COUNT++;

    if(Cla1ToCpuMsg.y14.i32 == Cla1ToCpuMsg.y15.i32)
        PASS_COUNT++;
    else
        FAIL_COUNT++;

    if(Cla1ToCpuMsg.y16.i32 == Cla1ToCpuMsg.y17.i32)
        PASS_COUNT++;
    else
        FAIL_COUNT++;

    if(Cla1ToCpuMsg.y18.i32 == Cla1ToCpuMsg.y19.i32)
        PASS_COUNT++;
    else
        FAIL_COUNT++;

    
//-------------------------------------------------------------
//-------------------------------------------------------------

   if(PASS_COUNT == GOLDEN_PASS_COUNT && FAIL_COUNT == 0)
   {
        // If test stopped here, it passed
        ESTOP0;
   }
   else
   {
        // If test stopped here, it failed
        ESTOP0;
   }
//-------------------------------------------------------------
// End of test
//-------------------------------------------------------------

}


//===========================================================================
// No more.
//===========================================================================
