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
//   This is a basic program to exercise the CLA  Exp10 macro.
//
//   All CLA tasks are used.  Each task clears the overflow and
//   underflow flags before execution.  The tasks 1-5 are populated
//   with the Exp10 macro.  Macro input and output are
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
Uint16 GOLDEN_PASS_COUNT = 5;   // Number of test in this program
Uint16 PASS_COUNT = 0;          // If all tests pass, this should equal golden value
Uint16 FAIL_COUNT = 0;          // Number of tests that failed

float y_x1=0.0,y_x2=0.0,y_x3=0.0,y_x4=0.0,y_x5=0.0;
float chk1,chk2,chk3,chk4,chk5;

void main(void)
{
 //  union F32_I32 temp;
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
// Test 1:
//-------------------------------------------------------------
   	CpuToCla1Msg.x1 = 0.0;      

   // Force Task 1 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   	Cla1ForceTask1andWait()
	y_x1=Cla1ToCpuMsg.y1.f32;
  

//-------------------------------------------------------------
// Test 2:
//-------------------------------------------------------------
   
   	CpuToCla1Msg.x2 = 5;  
                                

   // Force Task 2 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   	Cla1ForceTask2andWait()
	y_x2=Cla1ToCpuMsg.y2.f32;
   
//-------------------------------------------------------------
// Test 3:
//-------------------------------------------------------------
          // Force +0.0
   	CpuToCla1Msg.x3 = 1.1;  
                                

   // Force Task 3 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   	Cla1ForceTask3andWait()
	y_x3=Cla1ToCpuMsg.y3.f32;  
//-------------------------------------------------------------
// Test 4:
//-------------------------------------------------------------
 
	CpuToCla1Msg.x4 = -2.9;  
                                

   // Force Task 4 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   	Cla1ForceTask4andWait()
	y_x4=Cla1ToCpuMsg.y4.f32;  
//-------------------------------------------------------------
// Test 5:
//-------------------------------------------------------------

	CpuToCla1Msg.x5 = 35.111;  
                                

   // Force Task 5 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   	Cla1ForceTask5andWait()
	y_x5=Cla1ToCpuMsg.y5.f32;  
//-------------------------------------------------------------
// start of test
//-------------------------------------------------------------
   chk1=1- y_x1;           
   chk2=(100000 - y_x2)/100000;
   chk3=12.589254118 - y_x3;    
   chk4=0.001258925411-y_x4;
   chk5=1.2912192736 - (y_x5/1e+35);

   if(chk1>=-10e-5 & chk1<=10e-5)
	   PASS_COUNT++;          // If all tests pass, this should equal golden value
    else
       FAIL_COUNT++;
   if(chk2>=-10e-5 & chk2<=10e-5)
	   PASS_COUNT++;          // If all tests pass, this should equal golden value
    else
       FAIL_COUNT++;
   if(chk3>=-10e-5 & chk3<=10e-5)
	   PASS_COUNT++;          // If all tests pass, this should equal golden value
    else
       FAIL_COUNT++;
   if(chk4>=-10e-5 & chk4<=10e-5)
       PASS_COUNT++;          // If all tests pass, this should equal golden value
    else
       FAIL_COUNT++;
   if(chk5>=-10e-5 & chk5<=10e-5)
       PASS_COUNT++;          // If all tests pass, this should equal golden value
    else
       FAIL_COUNT++;

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
