// TI File $Revision: /main/1 $
// Checkin $Date: May 28, 2009   15:39:41 $
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
//   This is a basic program to exercise the CLA division macro.
//
//   All CLA tasks are used.  Each task clears the overflow and
//   underflow flags before execution.  Each task is populated
//   with the division macro.  Macro input and output are
//   through the message RAMs
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
#include "CLAShared.h"       // Shared information between C28x C and CLA assembly

//-------------------------------------------------------------
// Using DATA_SECTION pragma statements, these variables are
// placed in assembly sections that the linker .cmd file will
// allocate to the CLA message RAMs.
// These variables are used to pass input from the CPU to the CLA
// and output from the CLA to the CPU.
//-------------------------------------------------------------


#pragma DATA_SECTION(Cla1ToCpuMsg,"Cla1ToCpuMsgRAM");
struct  CLA_TO_CPU_MSG_RAM Cla1ToCpuMsg;

#pragma DATA_SECTION(CpuToCla1Msg,"CpuToCla1MsgRAM");
struct  CPU_TO_CLA_MSG_RAM CpuToCla1Msg;

//
// Global variables used in this example
//
Uint16 GOLDEN_PASS_COUNT = 27;  // Number of test in this program
Uint16 PASS_COUNT = 0;          // If all tests pass, this should equal golden value
Uint16 FAIL_COUNT = 0;          // Number of tests that failed

void main(void)
{
   union F32_I32 temp;
   DisableDog();                // Disable the watchdog
//-------------------------------------------------------------
// CLA module initialization
// 1) Enable the CLA clock
// 2) Init the CLA interrupt vectors
// 3) Allow the IACK instruction to flag a CLA interrupt/start a task
// 4) Assign CLA program memory to the CLA
// 5) Enable CLA interrupts (MIER)
//
// Note: As provided, the linker .cmd file links the CLA assembly
//       code directly to the CLA program memory.
//       This way the debugger will load the CLA assembly code
//       into the program memory.  (No need to copy the CLA code
//       during debug).
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
   asm("  RPT #3 || NOP");
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
//
// All tests are performed with rounding off (RNDF32=0)
// The task envoked sets LUF=0, LVF=0, and RNDF32=0 before
// executing the CLADiv assembly macro
//
//-------------------------------------------------------------
// Setup for Test 1a:
//-------------------------------------------------------------
   CpuToCla1Msg.Num1 = 2.77777;
   CpuToCla1Msg.Den1 = 1.33333;

   // Force Task 1 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask1andWait();

   // Check the results for test 1a
   // y1 = 2.77777/1.33333 = 2.08333271

   if(   (Cla1ToCpuMsg.y1.i32 == 0x40055552)
        & (Cla1Regs._MSTF.bit.LUF == 0)
        & (Cla1Regs._MSTF.bit.LVF == 0)
        & (Cla1Regs._MSTF.bit.NF == 0)
        & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
    else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for Test 1b:
//-------------------------------------------------------------
    CpuToCla1Msg.Num1 = -2.77777;
    CpuToCla1Msg.Den1 = 1.33333;

    // Force Task 1 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask1andWait();

    // Check the results for test 1b
    // y1 = -2.77777/1.33333 = -2.08333271

    if(   (Cla1ToCpuMsg.y1.i32 == 0xC0055552)
        & (Cla1Regs._MSTF.bit.LUF == 0)
        & (Cla1Regs._MSTF.bit.LVF == 0)
        & (Cla1Regs._MSTF.bit.NF == 1)
        & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
    else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for Test 1c:
//-------------------------------------------------------------
    CpuToCla1Msg.Num1 = 2.77777;
    CpuToCla1Msg.Den1 = -1.33333;

    // Force Task 1 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask1andWait();

    // Check the results for test 1c
    // y1 = 2.77777/-1.33333 = -2.08333271

    if(   (Cla1ToCpuMsg.y1.i32 == 0xC0055552)
        & (Cla1Regs._MSTF.bit.LUF == 0)
        & (Cla1Regs._MSTF.bit.LVF == 0)
        & (Cla1Regs._MSTF.bit.NF == 1)
        & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
    else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for test 1d:
//-------------------------------------------------------------
    CpuToCla1Msg.Num1 = -2.77777;
    CpuToCla1Msg.Den1 = -1.33333;

    // Force Task 1 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask1andWait();

    // Check the results for test 1d
    // y1 -2.77777/-1.33333 = 2.08333271

    if(   (Cla1ToCpuMsg.y1.i32 == 0x40055552)
        & (Cla1Regs._MSTF.bit.LUF == 0)
        & (Cla1Regs._MSTF.bit.LVF == 0)
        & (Cla1Regs._MSTF.bit.NF == 0)
        & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
    else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for test 2a:
//-------------------------------------------------------------
    CpuToCla1Msg.Num2 = 0.0;
    CpuToCla1Msg.Den2 = 0.0;

    // Force Task 2 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask2andWait();

    // Check the results for test 2a
    // y2 = 0.0/0.0 = +INF, Set LVF

   if(   (Cla1ToCpuMsg.y2.i32 == 0x7F800000)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 1)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for test 2b:
//-------------------------------------------------------------
   CpuToCla1Msg.Num2 = 1.0;
   CpuToCla1Msg.Den2 = 0.0;

    // Force Task 2 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask2andWait();

    // Check the results for test 2b
    // y2 = 1.0/0.0 = +INF, Set LVF

   if(   (Cla1ToCpuMsg.y2.i32 == 0x7F800000)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 1)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for test 2c:
//-------------------------------------------------------------
   CpuToCla1Msg.Num2 = -1.0;
   CpuToCla1Msg.Den2 = 0.0;

    // Force Task 2 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask2andWait();

    // Check the results for test 2c
    // y2 = -1.0/0.0 = -INF, Set LVF

   if(   (Cla1ToCpuMsg.y2.i32 == 0xFF800000)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 1)
       & (Cla1Regs._MSTF.bit.NF == 1)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for test 3a:
//-------------------------------------------------------------
   CpuToCla1Msg.Num3 = 5.24L;
   CpuToCla1Msg.Den3 = 6.49L;

    // Force Task 3 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask3andWait();

    // Check the results for test 3a
    // y3 = 0.8073959

   if(   (Cla1ToCpuMsg.y3.i32 == 0x3F4EB17F)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//   ESTOP0;

//-------------------------------------------------------------
// Setup for test 3b:
//-------------------------------------------------------------
   CpuToCla1Msg.Num3 = 5.24L;
   CpuToCla1Msg.Den3 = -6.49L;

    // Force Task 3 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask3andWait();

    // Check the results for test 3b
    // y3 = -0.8073959

   if(   (Cla1ToCpuMsg.y3.i32 == 0xBF4EB17F)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 1)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for test 3c:
//-------------------------------------------------------------
   CpuToCla1Msg.Num3 = -5.24;
   CpuToCla1Msg.Den3 = 6.49L;

    // Force Task 3 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask3andWait();

    // Check the results for test 3c
    // y3 = -0.8073959

   if(   (Cla1ToCpuMsg.y3.i32 == 0xBF4EB17F)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 1)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for test 3d:
//-------------------------------------------------------------
   CpuToCla1Msg.Num3 = -5.24;
   CpuToCla1Msg.Den3 = -6.49;

    // Force Task 3 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask3andWait();

    // Check the results for test 3d
    // y3 = 0.8073959

   if(   (Cla1ToCpuMsg.y3.i32 == 0x3F4EB17F)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for test 4a:
//-------------------------------------------------------------
   CpuToCla1Msg.Num4 = 8.34L;
   CpuToCla1Msg.Den4 = 2.36L;

    // Force Task 4 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask4andWait();

    // Check the results for test 4a
    // y4 = 3.533898

   if(   (Cla1ToCpuMsg.y4.i32 == 0x40622B64)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for test 4b:
//-------------------------------------------------------------
   CpuToCla1Msg.Num4 = -8.34L;
   CpuToCla1Msg.Den4 = 2.36L;

    // Force Task 4 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask4andWait();

    // Check the results for test 4b
    // y4 = -3.533898

   if(   (Cla1ToCpuMsg.y4.i32 == 0xC0622B64)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 1)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for test 4c:
//-------------------------------------------------------------
   CpuToCla1Msg.Num4 = 8.34L;
   CpuToCla1Msg.Den4 = -2.36L;

    // Force Task 4 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask4andWait();

    // Check the results for test 4c
    // y4 = -3.533898

   if(   (Cla1ToCpuMsg.y4.i32 == 0xC0622B64)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 1)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for test 4d:
//-------------------------------------------------------------
   CpuToCla1Msg.Num4 = -8.34L;
   CpuToCla1Msg.Den4 = -2.36L;

    // Force Task 4 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file


    Cla1ForceTask4andWait();

    // Check the results for test 4d
    // y4 = 3.533898

   if(   (Cla1ToCpuMsg.y4.i32 == 0x40622B64)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Task 5a:
//-------------------------------------------------------------
   CpuToCla1Msg.Num5 = 12.54L;
   CpuToCla1Msg.Den5 =  6.67L;

    // Force Task 5 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask5andWait();

    // Check the results for test 5a
    // y5 = 1.88006

   if(   (Cla1ToCpuMsg.y5.i32 == 0x3FF0A5CE)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Task 5b:
//-------------------------------------------------------------
   CpuToCla1Msg.Num5 = -12.54;
   CpuToCla1Msg.Den5 =   6.67;

    // Force Task 5 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask5andWait();

    // Check the results for test 5b
    // y5 = -1.88006

   if(   (Cla1ToCpuMsg.y5.i32 == 0xBFF0A5CE)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 1)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Task 5c:
//-------------------------------------------------------------
   CpuToCla1Msg.Num5 =  12.54;
   CpuToCla1Msg.Den5 =  -6.67;

    // Force Task 5 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask5andWait();

    // Check the results for test 5c
    // y5 = -1.88006

   if(   (Cla1ToCpuMsg.y5.i32 == 0xBFF0A5CE)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 1)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Task 5d:
//-------------------------------------------------------------
   CpuToCla1Msg.Num5 = -12.54;
   CpuToCla1Msg.Den5 =  -6.67;

    // Force Task 5 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask5andWait();

    // Check the results for test 5d
    // y5 = 1.88006

   if(   (Cla1ToCpuMsg.y5.i32 == 0x3FF0A5CE)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for test 6a:
//-------------------------------------------------------------
   CpuToCla1Msg.Num6 = 7.94L;
   CpuToCla1Msg.Den6 = 0.50L;

    // Force Task 6 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask6andWait();

    // Check the results for test 6a
    // y6 = 15.88

   if(   (Cla1ToCpuMsg.y6.i32 == 0x417E147B)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Task 6b:
//-------------------------------------------------------------
   CpuToCla1Msg.Num6 = -7.94L;
   CpuToCla1Msg.Den6 =  0.50L;

    // Force Task 6 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask6andWait();

    // Check the results for test 6b
    // y6 = -15.88

   if(   (Cla1ToCpuMsg.y6.i32 == 0xC17E147B)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 1)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for test 6c:
//-------------------------------------------------------------
   CpuToCla1Msg.Num6 =  7.94L;
   CpuToCla1Msg.Den6 = -0.50L;

    // Force Task 6 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask6andWait();

    // Check the results for test 6c
    // y6 = -15.88

   if(   (Cla1ToCpuMsg.y6.i32 == 0xC17E147B)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 1)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for test 6d:
//-------------------------------------------------------------
   CpuToCla1Msg.Num6 = -7.94L;
   CpuToCla1Msg.Den6 = -0.50L;

    // Force Task 6 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask6andWait();

    // Check the results for test 6d
    // y6 = 15.88

   if(   (Cla1ToCpuMsg.y6.i32 == 0x417E147B)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;


//-------------------------------------------------------------
// Task 7a:
//-------------------------------------------------------------
   CpuToCla1Msg.Num7 =  0.0;
   CpuToCla1Msg.Den7 = 12.0;

    // Force Task 7 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask7andWait();

    // Check the results for test 7a
    // y7 = 0.0, Set LUF

   if(   (Cla1ToCpuMsg.y7.i32 == 0x00000000)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 1) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for test 7b:
//-------------------------------------------------------------
   temp.i32 = 0x80000000;         // Force -0.0
   CpuToCla1Msg.Num7 = temp.f32;
   CpuToCla1Msg.Den7 = 12.0;

    // Force Task 7 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask7andWait();

    // Check the results for test 7b
    // y7 = -0.0

   if(   (Cla1ToCpuMsg.y7.i32 == 0x80000000)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 1) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for test 7c:
//-------------------------------------------------------------
   CpuToCla1Msg.Num7 = 0.0;
   CpuToCla1Msg.Den7 = -12.0;

    // Force Task 7 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask7andWait();

    // Check the results for test 7c
    // y7 = -0.0

   if(   (Cla1ToCpuMsg.y7.i32 == 0x80000000)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 1) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Setup for test 7d:
//-------------------------------------------------------------
   temp.i32 = 0x80000000;
   CpuToCla1Msg.Num7 = temp.f32;  // Force -0.0
   CpuToCla1Msg.Den7 = -12.0;

    // Force Task 7 by the IACK instruction
    // Wait for the task to complete
    // This macro is defined in the Cla_Defines.h file

    Cla1ForceTask7andWait();

    // Check the results for test 7d
    // y7 = 0.0

   if(   (Cla1ToCpuMsg.y7.i32 == 0x00000000)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 1) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;


//-------------------------------------------------------------
// End of test
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

}


//===========================================================================
// No more.
//===========================================================================
