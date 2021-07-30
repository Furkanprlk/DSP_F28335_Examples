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
//   This is a basic program to exercise the CLA atan2PU macro.
//
//   All CLA tasks are used.  Each task clears the overflow and
//   underflow flags before execution.  Each task is populated
//   with the atan2 & atan2PU macro.  Macro input and output are
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
Uint16 GOLDEN_PASS_COUNT = 8;   // Number of test in this program
Uint16 PASS_COUNT = 0;          // If all tests pass, this should equal golden value
Uint16 FAIL_COUNT = 0;          // Number of tests that failed

float z1_atan2pu=0.0,z1_atan2=0.0;           float z5_atan2pu=0.0,z5_atan2=0.0;
float z2_atan2pu=0.0,z2_atan2=0.0;           float z6_atan2pu=0.0,z6_atan2=0.0;
float z3_atan2pu=0.0,z3_atan2=0.0;           float z7_atan2pu=0.0,z7_atan2=0.0;
float z4_atan2pu=0.0,z4_atan2=0.0;           float z8_atan2pu=0.0,z8_atan2=0.0;

float chk1=0.0,chk2=0.0,chk3=0.0,chk4=0.0;
float chk5=0.0,chk6=0.0,chk7=0.0,chk8=0.0;

void main(void)
{
  
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
// Task 1a:
//-------------------------------------------------------------
   CpuToCla1Msg.x1 = 0.9;      
   CpuToCla1Msg.y1 = -22.0;
   // Force Task 1 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask1andWait()

  

//-------------------------------------------------------------
// Task 1b:
//-------------------------------------------------------------
  
   CpuToCla1Msg.x1 = -35;  
                                
   CpuToCla1Msg.y1 = 35 ;
   // Force Task 1 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask1andWait()

  

//-------------------------------------------------------------
// Task 2:
//-------------------------------------------------------------
   CpuToCla1Msg.x2 = 35;      
   CpuToCla1Msg.y2 = 35;
   // Force Task 2 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask2andWait()

   

//-------------------------------------------------------------
// Task 3:
//-------------------------------------------------------------
   CpuToCla1Msg.x3 = -22.33; 
   CpuToCla1Msg.y3 = -89.0;
   // Force Task 3 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask3andWait()

  

//-------------------------------------------------------------
// Task 4:
//-------------------------------------------------------------
   CpuToCla1Msg.x4 = 0.5;  
   CpuToCla1Msg.y4 = 4.0;
   // Force Task 4 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask4andWait()

   
//-------------------------------------------------------------
// Task 5:
//-------------------------------------------------------------
   CpuToCla1Msg.x5 = 12.6736; 
   CpuToCla1Msg.y5 = 0.5;  

   // Force Task 5 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask5andWait()

   

//-------------------------------------------------------------
// Task 6:
//-------------------------------------------------------------
   CpuToCla1Msg.x6 = -9.12; 
   CpuToCla1Msg.y6 = -9.12;
   // Force Task 6 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask6andWait()

  

//-------------------------------------------------------------
// Task 7:
//-------------------------------------------------------------
   CpuToCla1Msg.x7 = -12.8; 
   CpuToCla1Msg.y7 = 0.1e-1;
   // Force Task 7 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask7andWait()


//-------------------------------------------------------------
// Task 8:
//-------------------------------------------------------------
   CpuToCla1Msg.x8 = 1.0;     
   CpuToCla1Msg.y8 = 10.0;
   // Force Task 8 by the IACK instruction
   // Wait for the task to complete
   // This macro is defined in the Cla_Defines.h file

   Cla1ForceTask8andWait()
//-------------------------------------------------------------
// The values of atan2 and atan2PU are stored in "z1_atan2 to z8_atan2"
// & "z1_atan2pu to z8_atan2pu" respectively from each CLA task
//-------------------------------------------------------------

z1_atan2pu=Cla1ToCpuMsg.zpu1.f32;              z1_atan2=Cla1ToCpuMsg.z1.f32;
z2_atan2pu=Cla1ToCpuMsg.zpu2.f32;              z2_atan2=Cla1ToCpuMsg.z2.f32;
z3_atan2pu=Cla1ToCpuMsg.zpu3.f32;              z3_atan2=Cla1ToCpuMsg.z3.f32;
z4_atan2pu=Cla1ToCpuMsg.zpu4.f32;              z4_atan2=Cla1ToCpuMsg.z4.f32;
z5_atan2pu=Cla1ToCpuMsg.zpu5.f32;              z5_atan2=Cla1ToCpuMsg.z5.f32;
z6_atan2pu=Cla1ToCpuMsg.zpu6.f32;              z6_atan2=Cla1ToCpuMsg.z6.f32;
z7_atan2pu=Cla1ToCpuMsg.zpu7.f32;              z7_atan2=Cla1ToCpuMsg.z7.f32;
z8_atan2pu=Cla1ToCpuMsg.zpu8.f32;              z8_atan2=Cla1ToCpuMsg.z8.f32;

//-------------------------------------------------------------
// Start of test
// The correctness of the macro is tested by the equation:
//  tan2PU(x/y) = tan2(x/y) * 1/2pi
//-------------------------------------------------------------
chk1=z1_atan2pu - z1_atan2*0.159154943;
chk2=z2_atan2pu - z2_atan2*0.159154943;
chk3=z3_atan2pu - z3_atan2*0.159154943;
chk4=z4_atan2pu - z4_atan2*0.159154943;
chk5=z5_atan2pu - z5_atan2*0.159154943;
chk6=z6_atan2pu - z6_atan2*0.159154943;
chk7=z7_atan2pu - z7_atan2*0.159154943;
chk8=z8_atan2pu - z8_atan2*0.159154943;

if(   (chk1 >=-0.1e-04 )
       & (chk1 <=0.1e-04 )
       )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

if(   (chk2 >=-0.1e-04)
       & (chk2 <=0.1e-04)
       )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

if(   (chk3 >=-0.1e-04 )
       & (chk3 <=0.1e-04 )
       )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

if(   (chk4 >=-0.1e-04 )
       & (chk4 <=0.1e-04 )
       )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

if(   (chk5 >=-0.1e-04 )
       & (chk5 <=0.1e-04 )
       )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

if(   (chk6 >=-0.1e-04 )
       & (chk6 <=0.1e-04 )
       )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

if(   (chk7 >=-0.1e-04 )
       & (chk7 <=0.1e-04 )
       )
        PASS_COUNT++;
   else
        FAIL_COUNT++;

if(   (chk8 >=-0.1e-04 )
       & (chk8 <=0.1e-04 )
       )
        PASS_COUNT++;
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


   ESTOP0;
}


//===========================================================================
// No more.
//===========================================================================






