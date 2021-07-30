// TI File $Revision: /main/1 $
// Checkin $Date: May 28, 2009   15:37:27 $
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
//   This is a basic program to exercise the CLA  atan macro.
//
//   All CLA tasks are used.  Each task clears the overflow and
//   underflow flags before execution.  Each task is populated
//   with the atan macro.  Macro input and output are
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
#include "CLAShared.h"       // Shared between C28x C and CLA assembly

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
Uint16 GOLDEN_PASS_COUNT = 10;   // Number of test in this program
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
   Cla1Regs.MMEMCFG.bit.RAM1E = 1;
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
// All tests performed with rounding off (RNDF32=0)
//-------------------------------------------------------------

//-------------------------------------------------------------
// Task 1a:
//-------------------------------------------------------------
   CpuToCla1Msg.x1 = 0.9;      

   // Force Task 1 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask1andWait()

   if(   (Cla1ToCpuMsg.y1.i32 == 0x3f3b99c2)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Task 1b:
//-------------------------------------------------------------
   temp.i32 = 0x80000000;       // Force -0.0
   CpuToCla1Msg.x1 = temp.f32;  
                                

   // Force Task 1 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask1andWait()

   if(   (Cla1ToCpuMsg.y1.i32 == 0x00000000)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 1) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;
//-------------------------------------------------------------
// Task 1c:
//-------------------------------------------------------------
   temp.i32 = 0x00000000;       // Force +0.0
   CpuToCla1Msg.x1 = temp.f32;  
                                

   // Force Task 1 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask1andWait()

   if(   (Cla1ToCpuMsg.y1.i32 == 0x00000000)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 1) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;
//-------------------------------------------------------------
// Task 2:
//-------------------------------------------------------------
   CpuToCla1Msg.x2 = 1.0;      

   // Force Task 2 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask2andWait()

   if(   (Cla1ToCpuMsg.y2.i32 == 0x3f490fda)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;


//-------------------------------------------------------------
// Task 3:
//-------------------------------------------------------------
   CpuToCla1Msg.x3 = 33.33333L; 

   // Force Task 3 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask3andWait()

   if(   (Cla1ToCpuMsg.y3.i32 == 0x3fc5391c)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Task 4:
//-------------------------------------------------------------
   CpuToCla1Msg.x4 = -1.0;  

   // Force Task 4 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask4andWait()

   if(   (Cla1ToCpuMsg.y4.i32 == 0xbf490fda)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 1)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;


//-------------------------------------------------------------
// Task 5:
//-------------------------------------------------------------
   temp.i32 = 0x7f000000;       // Force value of order e38
   CpuToCla1Msg.x5 = temp.f32 ;


   // Force Task 5 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask5andWait()

   if(   (Cla1ToCpuMsg.y5.i32 == 0x3fc90fdb)
       & (Cla1Regs._MSTF.bit.LUF == 1)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 0)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;


//-------------------------------------------------------------
// Task 6:
//-------------------------------------------------------------
   temp.i32 = 0xff000000;       //  Force value of order -e38
   CpuToCla1Msg.x6 = temp.f32 ;

   // Force Task 6 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask6andWait()

   if(   (Cla1ToCpuMsg.y6.i32 == 0xbfc90fdb)
       & (Cla1Regs._MSTF.bit.LUF == 1)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 1)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

//-------------------------------------------------------------
// Task 7:
//-------------------------------------------------------------
   CpuToCla1Msg.x7 = -12.87L; // y7 = bfbf22e2

   // Force Task 7 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask7andWait()

   if(   (Cla1ToCpuMsg.y7.i32 == 0xbfbf22e2)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 1)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
        PASS_COUNT++;
   else
        FAIL_COUNT++;


//-------------------------------------------------------------
// Task 8:
//-------------------------------------------------------------
   CpuToCla1Msg.x8 = -0.25;     // y8 = bf490fda

   // Force Task 8 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask8andWait()

   if(   (Cla1ToCpuMsg.y8.i32 == 0xbe7adbaf)
       & (Cla1Regs._MSTF.bit.LUF == 0)
       & (Cla1Regs._MSTF.bit.LVF == 0)
       & (Cla1Regs._MSTF.bit.NF == 1)
       & (Cla1Regs._MSTF.bit.ZF == 0) )
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
