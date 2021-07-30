// TI File $Revision: /main/1 $
// Checkin $Date: May 28, 2009   15:38:32 $
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
//   This is a basic program to exercise the CLA arccosine macro.
//
//   Task1 & 3 are populated with multiple instances of the cosine & arccosine macro.
//   Macro input and output are through the message RAMs
//   The CLAsincosTable & arccosine table  are loaded directly into CLA RAM1
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
//-------------------------------------------------------------

#pragma DATA_SECTION(Cla1ToCpuMsg,"Cla1ToCpuMsgRAM");
struct  CLA_TO_CPU_MSG_RAM Cla1ToCpuMsg;

#pragma DATA_SECTION(CpuToCla1Msg,"CpuToCla1MsgRAM");
struct  CPU_TO_CLA_MSG_RAM CpuToCla1Msg;

// Global variables used in this example
Uint16 GOLDEN_PASS_COUNT = 8;  // Number of test in this program
Uint16 PASS_COUNT = 0;          // If all tests pass, this should equal golden value
Uint16 FAIL_COUNT = 0;          // Number of tests that failed

float chk1,chk2,chk3,chk4,chk5,chk6,chk7,chk8;

float y_cos0;
float y_cos1;
float y_cos2;
float y_cos3;
float y_cos4;
float y_cos5;
float y_cos6;
float y_cos7;

float y_ang0=0.0;
float y_ang1=0.0;
float y_ang2=0.0;
float y_ang3=0.0;
float y_ang4=0.0;
float y_ang5=0.0;
float y_ang6=0.0;
float y_ang7=0.0;
float y_ang8=0.0;
float y_ang9=0.0;
float y_ang10=0.0;
float y_ang11=0.0;
float y_ang12=0.0;
float y_ang13=0.0;
float y_ang14=0.0;
float y_ang15=0.0;

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
   asm("   RPT #3 || NOP");
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
// Initialize the input data for arccos task...
//-------------------------------------------------------------
	
	CpuToCla1Msg.cos0  =  0.0;                //  0.0             =   pi/2
	CpuToCla1Msg.cos1  =  0.25;               //  0.25            =  1.3181160716
    CpuToCla1Msg.cos2  =  0.707106781187;	  //  0.707106781187  =   pi/4
    CpuToCla1Msg.cos3  =  0.5;                //  0.5             =   pi/3  
    CpuToCla1Msg.cos4  =  0.65;               //  0.65            =  0.863211890
    CpuToCla1Msg.cos5  =  0.707106781187;	  //  0.707106781187  =   pi/4
    CpuToCla1Msg.cos6  =  0.866;              //  0.866           =  0.523649580
	CpuToCla1Msg.cos7  =  1.0;                //  1.0             =  0.0  
    CpuToCla1Msg.cos8  =  0.0;                //  0.0             =   pi/2
	CpuToCla1Msg.cos9  = -0.25;               // -0.25            =  1.823476581
    CpuToCla1Msg.cos10 = -0.707106781187;     // -0.707106781187  =  3*pi/4
    CpuToCla1Msg.cos11 = -0.5;                // -0.5             =  2*pi/3
    CpuToCla1Msg.cos12 = -0.65;               // -0.65            =  2.278380763 
    CpuToCla1Msg.cos13 = -0.707106781187;     // -0.707106781187  =  3*pi/4   
    CpuToCla1Msg.cos14 = -0.866;              // -0.866           =  2.617943072
	CpuToCla1Msg.cos15 = -1.0;                // -1.0             =   pi
//-------------------------------------------------------------
// Force Task 3 by the IACK instruction
// Wait for the task to complete
// This macro is defined in the Cla_Defines.h file
//
// Note: Task 3 is setup to run the macro on cos0 - cos19
// The results will be stored in in y_ang0-y_ang19
//
//-------------------------------------------------------------

    Cla1ForceTask3andWait();

	y_ang0=Cla1ToCpuMsg.ang0.f32;                     
    y_ang1=Cla1ToCpuMsg.ang1.f32;                     
    y_ang2=Cla1ToCpuMsg.ang2.f32;                     
    y_ang3=Cla1ToCpuMsg.ang3.f32;                     
    y_ang4=Cla1ToCpuMsg.ang4.f32;                     
    y_ang5=Cla1ToCpuMsg.ang5.f32;                     
    y_ang6=Cla1ToCpuMsg.ang6.f32;                     
    y_ang7=Cla1ToCpuMsg.ang7.f32;                     
    y_ang8=Cla1ToCpuMsg.ang8.f32;
    y_ang9=Cla1ToCpuMsg.ang9.f32;
    y_ang10=Cla1ToCpuMsg.ang10.f32;
    y_ang11=Cla1ToCpuMsg.ang11.f32;
    y_ang12=Cla1ToCpuMsg.ang12.f32;
    y_ang13=Cla1ToCpuMsg.ang13.f32;
    y_ang14=Cla1ToCpuMsg.ang14.f32;
    y_ang15=Cla1ToCpuMsg.ang15.f32;
//-------------------------------------------------------------
// Initialize the input data for cos task...
//-------------------------------------------------------------

    CpuToCla1Msg.rad0  = y_ang0;                // load test data...
    CpuToCla1Msg.rad1  = y_ang2;                // load test data...
    CpuToCla1Msg.rad2  = y_ang4;                // load test data...
    CpuToCla1Msg.rad3  = y_ang6;                // load test data...
    CpuToCla1Msg.rad4  = y_ang8;             	// load test data...
    CpuToCla1Msg.rad5  = y_ang10;            	// load test data...
    CpuToCla1Msg.rad6  = y_ang12;            	// load test data...
    CpuToCla1Msg.rad7  = y_ang14;            	// load test data...
    

//-------------------------------------------------------------
// Force Task 1 by the IACK instruction
// Wait for the task to complete
// This macro is defined in the Cla_Defines.h file
//
// Note: Task 1 is setup to run the macro on rad0 - rad19
// The results will be stored in in y0-y19
//
//-------------------------------------------------------------

    Cla1ForceTask1andWait();

	y_cos0=Cla1ToCpuMsg.y0.f32;
    y_cos1=Cla1ToCpuMsg.y1.f32;
    y_cos2=Cla1ToCpuMsg.y2.f32;
    y_cos3=Cla1ToCpuMsg.y3.f32;
    y_cos4=Cla1ToCpuMsg.y4.f32;
    y_cos5=Cla1ToCpuMsg.y5.f32;
    y_cos6=Cla1ToCpuMsg.y6.f32;
    y_cos7=Cla1ToCpuMsg.y7.f32;
//------------------------------------------------------------
//          Start of testing
//------------------------------------------------------------ 
    chk1=y_cos0 - CpuToCla1Msg.cos0;
 	chk2=y_cos1 - CpuToCla1Msg.cos2;
 	chk3=y_cos2 - CpuToCla1Msg.cos4;
 	chk4=y_cos3 - CpuToCla1Msg.cos6;
   	chk5=y_cos4 - CpuToCla1Msg.cos8;
   	chk6=y_cos5 - CpuToCla1Msg.cos10;
   	chk7=y_cos6 - CpuToCla1Msg.cos12;
   	chk8=y_cos7 - CpuToCla1Msg.cos14;

   if(chk1>=-0.1e-4 & chk1<=0.1e-4)
	   PASS_COUNT++;          
    else
       FAIL_COUNT++;
   if(chk2>=-0.1e-4 & chk2<=0.1e-4)
	   PASS_COUNT++;          
    else
       FAIL_COUNT++;
   if(chk3>=-0.1e-4 & chk3<=0.1e-4)
	   PASS_COUNT++;          
    else
       FAIL_COUNT++;
   if(chk4>=-0.1e-4 & chk4<=0.1e-4)
       PASS_COUNT++;          
    else
       FAIL_COUNT++;
   if(chk5>=-0.1e-4 & chk5<=0.1e-4)
       PASS_COUNT++;          
    else
       FAIL_COUNT++;
   if(chk6>=-0.1e-4 & chk6<=0.1e-4)
	   PASS_COUNT++;          
    else
       FAIL_COUNT++;
   if(chk7>=-0.1e-4 & chk7<=0.1e-4)
	   PASS_COUNT++;          
    else
       FAIL_COUNT++;
  
	if(chk8>=-0.1e-4 & chk8<=0.1e-4)
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

}


//===========================================================================
// No more.
//===========================================================================
