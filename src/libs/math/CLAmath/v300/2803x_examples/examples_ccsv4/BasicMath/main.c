// TI File $Revision: /main/1 $
// Checkin $Date: Oct 15, 2010   13:38:00 $
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
//   This is a basic program to exercise the CLAmathBasic library macros.
//
//   All CLA tasks are used.  Each task clears the overflow and
//   underflow flags before execution.  Each task is populated
//   with macros from the library.  Macro input and output are
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
#pragma DATA_SECTION(sCLAtoCPUMsg,"Cla1ToCpuMsgRAM");
struct  CLAtoCPUMsg_t   sCLAtoCPUMsg;

#pragma DATA_SECTION(sCPUtoCLAMsg,"CpuToCla1MsgRAM");
struct  CPUtoCLAMsg_t   sCPUtoCLAMsg;

#pragma DATA_SECTION(sCLARam1Data_u,"Cla1Ram1")
struct  CLARam1Data_u	sCLARam1Data_u;
 
#pragma DATA_SECTION(sCLARam1Data_v,"Cla1Ram1")
struct  CLARam1Data_v	sCLARam1Data_v;

//Global Variables
Uint16 GOLDEN_PASS_COUNT = 41;   // Number of test in this program
Uint16 PASS_COUNT = 0;          // If all tests pass, this should equal golden value
Uint16 FAIL_COUNT = 0;          // Number of tests that failed

//User defined functions
void vInitDataForTask1();
void vInitDataForTask2();
void vInitDataForTask3();
void vInitDataForTask4();
void vInitDataForTask5();
void vInitDataForTask6();
void vInitDataForTask7();
void vInitDataForTask8();


// User defined interrupt service routines
interrupt void cla_task1_isr( void);
interrupt void cla_task2_isr( void);
interrupt void cla_task3_isr( void);
interrupt void cla_task4_isr( void);
interrupt void cla_task5_isr( void);
interrupt void cla_task6_isr( void);
interrupt void cla_task7_isr( void);
interrupt void cla_task8_isr( void);
interrupt void NEW_ILLEGAL_ISR(void);

//! Main Function
void main(void)
{
	//! Step 1: Setup the system clock
	InitSysCtrl();

//! Step 2: Initialize PIE control
	/*! Intialize PIE control, disable all interrupts and
	 * then copy over the PIE Vector table from BootROM to RAM
	 */
	DINT;
	InitPieCtrl();
	IER = 0x00000000;
	IFR = 0x00000000;
	InitPieVectTable();
	
	/*! Assign user defined ISR to the PIE vector table */
	EALLOW;
	PieVectTable.CLA1_INT1  = &cla_task1_isr;
	PieVectTable.CLA1_INT2  = &cla_task2_isr;
	PieVectTable.CLA1_INT3  = &cla_task3_isr;
	PieVectTable.CLA1_INT4  = &cla_task4_isr;
	PieVectTable.CLA1_INT5  = &cla_task5_isr;
	PieVectTable.CLA1_INT6  = &cla_task6_isr;
	PieVectTable.CLA1_INT7  = &cla_task7_isr;
	PieVectTable.CLA1_INT8  = &cla_task8_isr;
	PieVectTable.ILLEGAL   = &NEW_ILLEGAL_ISR;
	EDIS;
	
	
	
	/*! Compute all CLA task vectors */ 
    EALLOW;
    Cla1Regs.MVECT1 = (Uint16) (&Cla1Task1 - &Cla1Prog_Start)*sizeof(Uint32);
    Cla1Regs.MVECT2 = (Uint16) (&Cla1Task2 - &Cla1Prog_Start)*sizeof(Uint32);
    Cla1Regs.MVECT3 = (Uint16) (&Cla1Task3 - &Cla1Prog_Start)*sizeof(Uint32);
    Cla1Regs.MVECT4 = (Uint16) (&Cla1Task4 - &Cla1Prog_Start)*sizeof(Uint32);
    Cla1Regs.MVECT5 = (Uint16) (&Cla1Task5 - &Cla1Prog_Start)*sizeof(Uint32);
    Cla1Regs.MVECT6 = (Uint16) (&Cla1Task6 - &Cla1Prog_Start)*sizeof(Uint32);
    Cla1Regs.MVECT7 = (Uint16) (&Cla1Task7 - &Cla1Prog_Start)*sizeof(Uint32);
    Cla1Regs.MVECT8 = (Uint16) (&Cla1Task8 - &Cla1Prog_Start)*sizeof(Uint32);    
    EDIS;
   
   	//! Step 3 : Mapping CLA tasks
    /*! All tasks are enabled and will be started by an ePWM trigger
     *  Map CLA program memory to the CLA and enable software breakpoints
     */
    EALLOW;
	Cla1Regs.MPISRCSEL1.bit.PERINT1SEL 	= CLA_INT1_NONE;
	Cla1Regs.MPISRCSEL1.bit.PERINT2SEL 	= CLA_INT2_NONE;
	Cla1Regs.MPISRCSEL1.bit.PERINT3SEL 	= CLA_INT3_NONE;
	Cla1Regs.MPISRCSEL1.bit.PERINT4SEL 	= CLA_INT4_NONE;
	Cla1Regs.MPISRCSEL1.bit.PERINT5SEL 	= CLA_INT5_NONE;
	Cla1Regs.MPISRCSEL1.bit.PERINT6SEL 	= CLA_INT6_NONE;
	Cla1Regs.MPISRCSEL1.bit.PERINT7SEL 	= CLA_INT7_NONE;
	Cla1Regs.MPISRCSEL1.bit.PERINT8SEL 	= CLA_INT8_NONE;
	Cla1Regs.MIER.all 		 		    				= 0x00FF;
	EDIS;		
    
      /*! Enable CLA interrupts at the group and subgroup levels */
	PieCtrlRegs.PIEIER11.all       = 0xFFFF;
	IER = (M_INT11);
	EINT;          						    // Enable Global interrupt INTM
   	ERTM;          						    // Enable Global realtime interrupt DBGM

	/*!Switch the CLA program space to the CLA and enable software forcing
	 * Also switch over CLA data ram 0 and 1
	 */
	
   	EALLOW;
   	Cla1Regs.MMEMCFG.bit.PROGE 		= 1;
   	Cla1Regs.MMEMCFG.bit.RAM1E		= 1;			
   	Cla1Regs.MCTL.bit.IACKE			= 1;
   	EDIS;
   	
/*-----------------------------------------------------------------------------
 * CLA Task 1: Does additions and subtractions
 * --------------------------------------------------------------------------*/
 	vInitDataForTask1();
   	Cla1ForceTask1andWait();
   	WAITSTEP;
   	(sCLAtoCPUMsg.y1.i32 == 0x40EED289)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y2.i32 == 0xC0E64DD2)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y3.i32 == 0xC000FDF3)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y4.i32 == 0xC12444D0)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y5.i32 == 0xC09FD07C)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y6.i32 == 0x413738EE)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y7.i32 == 0xC1072A99)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y8.i32 == 0xC07F0068)? PASS_COUNT++ : FAIL_COUNT++;						

/*-----------------------------------------------------------------------------
 * CLA Task 2: Multiplication and inverse
 * --------------------------------------------------------------------------*/
   	vInitDataForTask2();
   	Cla1ForceTask2andWait();
   	WAITSTEP;
   	(sCLAtoCPUMsg.y1.i32 == 0x40F60EFF)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y2.i32 == 0xC19EACED)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y3.i32 == 0xC1869C0B)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y4.i32 == 0x41B31040)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y5.i32 == 0x3F4F5F13)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y6.i32 == 0x3E246678)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y7.i32 == 0x3EF0B127)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y8.i32 == 0xBDDBA4BD)? PASS_COUNT++ : FAIL_COUNT++;
/*-----------------------------------------------------------------------------
 * CLA Task 3: Saturate upto either minimum or maximum values
 * --------------------------------------------------------------------------*/
   	vInitDataForTask3();
   	Cla1ForceTask3andWait();
   	WAITSTEP;
   	(sCLAtoCPUMsg.y1.i32 == 0x3F9E0419)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y2.i32 == 0xC1152FEC)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y3.i32 == 0xC0A76A16)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y4.i32 == 0xC0E404EA)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y5.i32 == 0x40C75183)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y6.i32 == 0x4008240B)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y7.i32 == 0x404DD639)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y8.i32 == 0xC049096C)? PASS_COUNT++ : FAIL_COUNT++;
/*-----------------------------------------------------------------------------
 * CLA Task 4: Saturate beyond a lower or upper bound
 * --------------------------------------------------------------------------*/
   	vInitDataForTask4();
   	Cla1ForceTask4andWait();
   	WAITSTEP;
   	(sCLAtoCPUMsg.y1.i32 == 0x3F9E0419)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y2.i32 == 0x00000000)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y3.i32 == 0x40082C3D)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y4.i32 == 0xC1220275)? PASS_COUNT++ : FAIL_COUNT++;
  
/*-----------------------------------------------------------------------------
 * CLA Task 5: Offset subtraction with zero saturation and absolute values
 * --------------------------------------------------------------------------*/
   	vInitDataForTask5();
   	Cla1ForceTask5andWait();
   	WAITSTEP;
   	(sCLAtoCPUMsg.y1.i32 == 0x3F9E075F)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y2.i32 == 0x3DFC84B6)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y3.i32 == 0x4047F62B)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y4.i32 == 0x3CA30553)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y5.i32 == 0x3F8E3F13)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y6.i32 == 0x00000000)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y7.i32 == 0x00000000)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y8.i32 == 0x40900000)? PASS_COUNT++ : FAIL_COUNT++;
/*-----------------------------------------------------------------------------
 * CLA Task 6: IQ24 to float with some arithmetic and then back to IQ24
 * --------------------------------------------------------------------------*/
   	vInitDataForTask6();
   	Cla1ForceTask6andWait();
   	WAITSTEP;
   	(sCLAtoCPUMsg.y1.i32 == 0x015B9F54)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y2.i32 == 0xFCDB0F2C)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y3.i32 == 0x0A5821B0)? PASS_COUNT++ : FAIL_COUNT++;
   	(sCLAtoCPUMsg.y4.i32 == 0x00000000)? PASS_COUNT++ : FAIL_COUNT++;
	
/*-----------------------------------------------------------------------------
 * CLA Task 7: Conditional execution. Setting the GOTOLABELx macros in the
 * 				CLAShared.h file will cause the execution in this task to go 
 * 				to label x.
 * 				NOTE: If setting GOTOLABELx to 1 set the other macros (GOTOLABELy)
 * 				to 0
 * --------------------------------------------------------------------------*/
   	vInitDataForTask7();
   	Cla1ForceTask7andWait();
   	WAITSTEP;
#if		GOTOLABEL7
	(sCLAtoCPUMsg.y1.f32 == 7.0)? PASS_COUNT++ : FAIL_COUNT++;
#endif
#if		GOTOLABEL8
	(sCLAtoCPUMsg.y1.f32 == 6.0)? PASS_COUNT++ : FAIL_COUNT++;
#endif
#if		GOTOLABEL9
	(sCLAtoCPUMsg.y1.f32 == 5.0)? PASS_COUNT++ : FAIL_COUNT++;
#endif
#if		GOTOLABEL10
	(sCLAtoCPUMsg.y1.f32 == 4.0)? PASS_COUNT++ : FAIL_COUNT++;
#endif
#if		GOTOLABEL11
	(sCLAtoCPUMsg.y1.f32 == 3.0)? PASS_COUNT++ : FAIL_COUNT++;
#endif
#if		GOTOLABEL12
	(sCLAtoCPUMsg.y1.f32 == 2.0)? PASS_COUNT++ : FAIL_COUNT++;
#endif
#if		GOTOLABEL13
	(sCLAtoCPUMsg.y1.f32 == 1.0)? PASS_COUNT++ : FAIL_COUNT++;
#endif
#if		GOTOLABEL14
	(sCLAtoCPUMsg.y1.f32 == 0.0)? PASS_COUNT++ : FAIL_COUNT++;
#endif
/*-----------------------------------------------------------------------------
 * CLA Task 8: 
 * --------------------------------------------------------------------------*/
   	vInitDataForTask8();
   	Cla1ForceTask8andWait();
   	WAITSTEP;

   asm(" ESTOP0");
}
/*-----------------------------------------------------------------------------
 * End of Main
 * --------------------------------------------------------------------------*/

//User defined functions
//
/*
 * Function 	: vInitDataForTask1
 * Arguments 	: None
 * Returns 		: None
 * Description 	: Initializes data points that will be used in Task 1 of the CLA
 */
void vInitDataForTask1()
{
	sCPUtoCLAMsg.x1.f32 = 1.2345;		sCPUtoCLAMsg.x2.f32 = 6.2287;
	sCPUtoCLAMsg.x3.f32 = 2.1272;		sCPUtoCLAMsg.x4.f32 = -9.3242;
	sCPUtoCLAMsg.x5.f32 = -5.2317;		sCPUtoCLAMsg.x6.f32 = 3.2162;
	sCPUtoCLAMsg.x7.f32 = -7.1256;		sCPUtoCLAMsg.x8.f32 = -3.1412;
}

/*
 * Function 	: vInitDataForTask2
 * Arguments 	: None
 * Returns 		: None
 * Description 	: Initializes data points that will be used in Task 2 of the CLA
 */
void vInitDataForTask2()
{
	sCPUtoCLAMsg.x1.f32 = 1.2345;		sCPUtoCLAMsg.x2.f32 = 6.2287;
	sCPUtoCLAMsg.x3.f32 = 2.1272;		sCPUtoCLAMsg.x4.f32 = -9.3242;
	sCPUtoCLAMsg.x5.f32 = -5.2317;		sCPUtoCLAMsg.x6.f32 = 3.2162;
	sCPUtoCLAMsg.x7.f32 = -7.1256;		sCPUtoCLAMsg.x8.f32 = -3.1412;
}

/*
 * Function 	: vInitDataForTask3
 * Arguments 	: None
 * Returns 		: None
 * Description 	: Initializes data points that will be used in Task 3 of the CLA
 */
void vInitDataForTask3()
{
	sCPUtoCLAMsg.x1.f32 = 1.2345;		sCPUtoCLAMsg.x2.f32 = 6.2287;
	sCPUtoCLAMsg.x3.f32 = 2.1272;		sCPUtoCLAMsg.x4.f32 = -9.3242;
	sCPUtoCLAMsg.x5.f32 = -5.2317;		sCPUtoCLAMsg.x6.f32 = 3.2162;
	sCPUtoCLAMsg.x7.f32 = -7.1256;		sCPUtoCLAMsg.x8.f32 = -3.1412;
}

/*
 * Function 	: vInitDataForTask4
 * Arguments 	: None
 * Returns 		: None
 * Description 	: Initializes data points that will be used in Task 4 of the CLA
 */
void vInitDataForTask4()
{
	sCPUtoCLAMsg.x1.f32 = 1.2346;		sCPUtoCLAMsg.x2.f32 = 0.1233 ;
	sCPUtoCLAMsg.x3.f32 = 3.1244;		sCPUtoCLAMsg.x4.f32 = 0.0000;
	sCPUtoCLAMsg.x5.f32 = 3.2162;		sCPUtoCLAMsg.x6.f32 = 2.1277;
	sCPUtoCLAMsg.x7.f32 = -10.1256;		sCPUtoCLAMsg.x8.f32 = -13.1412;
}

/*
 * Function 	: vInitDataForTask5
 * Arguments 	: None
 * Returns 		: None
 * Description 	: Initializes data points that will be used in Task 5 of the CLA
 */
void vInitDataForTask5()
{
	sCPUtoCLAMsg.x1.f32 = 1.2346;		sCPUtoCLAMsg.x2.f32 = 0.1233 ;
	sCPUtoCLAMsg.x3.f32 = -3.1244;		sCPUtoCLAMsg.x4.f32 = 0.0199;
	sCPUtoCLAMsg.x5.f32 = 3.2162;		sCPUtoCLAMsg.x6.f32 = 3.2163;
	sCPUtoCLAMsg.x7.f32 = 0.0000;		sCPUtoCLAMsg.x8.f32 = -1.5000;
}

/*
 * Function 	: vInitDataForTask6
 * Arguments 	: None
 * Returns 		: None
 * Description 	: Initializes data points that will be used in Task 6 of the CLA
 */
void vInitDataForTask6()
{
	sCPUtoCLAMsg.x1.iq24 = _IQ(1.2346);		sCPUtoCLAMsg.x2.iq24 = _IQ(0.1233);
	sCPUtoCLAMsg.x3.iq24 = _IQ(-3.1244);	sCPUtoCLAMsg.x4.iq24 = _IQ(0.0199);
	sCPUtoCLAMsg.x5.iq24 = _IQ(3.2162);		sCPUtoCLAMsg.x6.iq24 = _IQ(3.2163);
	sCPUtoCLAMsg.x7.iq24 = _IQ(0.0000);		sCPUtoCLAMsg.x8.iq24 = _IQ(-1.5000);
}

/*
 * Function 	: vInitDataForTask7
 * Arguments 	: None
 * Returns 		: None
 * Description 	: Initializes data points that will be used in Task 7 of the CLA
 */
void vInitDataForTask7()
{
//;A set of 8 values x1,x2 ....x8 are subjected to conditional
//;tests to check that branching occurs as expected
//;Y - binary 1, N - binary 0
//;A path with two Y and a N i.e. YYN is 110 in binary or 6
//; 									  Y->{L7 ->111,7}
//;						  Y->L3:{x7~=x8}->
//;						  |               N->{L8 ->110,6]
//;		   Y->L1:{x3<x4}->			
//;        |              |				  Y->{L9 ->101,5}
//;        |			  N->L4:{x7==x8}-> 
//;        |							  N->{L10->100,4}
//;{x1>x2}->
//;		   |                              Y->{L11->011,3}
//;        |              Y->L5:{x5>=x6}->
//;        |              |               N->{L12->010,2}
//;		   N->L2:{x4<x3}->
//;						  |               Y->{L13->001,1}
//;						  N->L6:{x5<=x6}->
//;                                       N->{L14->000,0}
#if		GOTOLABEL7
	sCPUtoCLAMsg.x1.f32 = 1.2346;		sCPUtoCLAMsg.x2.f32 = 0.1233 ;
	sCPUtoCLAMsg.x3.f32 = -3.1244;		sCPUtoCLAMsg.x4.f32 = 0.0199;
	sCPUtoCLAMsg.x5.f32 = 3.2162;		sCPUtoCLAMsg.x6.f32 = 3.2163;
	sCPUtoCLAMsg.x7.f32 = 0.0000;		sCPUtoCLAMsg.x8.f32 = -1.5000;
#endif
#if		GOTOLABEL8
	sCPUtoCLAMsg.x1.f32 = 1.2346;		sCPUtoCLAMsg.x2.f32 = 0.1233 ;
	sCPUtoCLAMsg.x3.f32 = -3.1244;		sCPUtoCLAMsg.x4.f32 = 0.0199;
	sCPUtoCLAMsg.x5.f32 = 3.2162;		sCPUtoCLAMsg.x6.f32 = 3.2163;
	sCPUtoCLAMsg.x7.f32 = -1.5233;		sCPUtoCLAMsg.x8.f32 = -1.5233;
#endif			
#if		GOTOLABEL9
	sCPUtoCLAMsg.x1.f32 = 1.2346;		sCPUtoCLAMsg.x2.f32 = 0.1233 ;
	sCPUtoCLAMsg.x3.f32 = -3.1244;		sCPUtoCLAMsg.x4.f32 = -4.0199;
	sCPUtoCLAMsg.x5.f32 = 3.2162;		sCPUtoCLAMsg.x6.f32 = 3.2163;
	sCPUtoCLAMsg.x7.f32 = 0.0001;		sCPUtoCLAMsg.x8.f32 = 0.0001;
#endif			 
#if		GOTOLABEL10
	sCPUtoCLAMsg.x1.f32 = 1.2346;		sCPUtoCLAMsg.x2.f32 = 0.1233 ;
	sCPUtoCLAMsg.x3.f32 = -3.1244;		sCPUtoCLAMsg.x4.f32 = -4.0199;
	sCPUtoCLAMsg.x5.f32 = 3.2162;		sCPUtoCLAMsg.x6.f32 = 3.2163;
	sCPUtoCLAMsg.x7.f32 = 0.0001;		sCPUtoCLAMsg.x8.f32 = 0.0002;
#endif			 
#if		GOTOLABEL11
	sCPUtoCLAMsg.x1.f32 = 1.2346;		sCPUtoCLAMsg.x2.f32 = 2.1233 ;
	sCPUtoCLAMsg.x3.f32 = -3.1244;		sCPUtoCLAMsg.x4.f32 = -4.0199;
	sCPUtoCLAMsg.x5.f32 = 3.2162;		sCPUtoCLAMsg.x6.f32 = 3.2161;
	sCPUtoCLAMsg.x7.f32 = 0.0000;		sCPUtoCLAMsg.x8.f32 = -1.5000;
#endif			 
#if		GOTOLABEL12
	sCPUtoCLAMsg.x1.f32 = 1.2346;		sCPUtoCLAMsg.x2.f32 = 2.1233 ;
	sCPUtoCLAMsg.x3.f32 = -3.1244;		sCPUtoCLAMsg.x4.f32 = -4.0199;
	sCPUtoCLAMsg.x5.f32 = 3.2162;		sCPUtoCLAMsg.x6.f32 = 3.2163;
	sCPUtoCLAMsg.x7.f32 = 0.0000;		sCPUtoCLAMsg.x8.f32 = -1.5000;
#endif			
#if		GOTOLABEL13
	sCPUtoCLAMsg.x1.f32 = 1.2346;		sCPUtoCLAMsg.x2.f32 = 2.1233 ;
	sCPUtoCLAMsg.x3.f32 = -3.1244;		sCPUtoCLAMsg.x4.f32 = -2.0199;
	sCPUtoCLAMsg.x5.f32 = 3.2163;		sCPUtoCLAMsg.x6.f32 = 3.2163;
	sCPUtoCLAMsg.x7.f32 = 0.0000;		sCPUtoCLAMsg.x8.f32 = -1.5000;
#endif			 
#if		GOTOLABEL14
	sCPUtoCLAMsg.x1.f32 = 1.2346;		sCPUtoCLAMsg.x2.f32 = 2.1233 ;
	sCPUtoCLAMsg.x3.f32 = -3.1244;		sCPUtoCLAMsg.x4.f32 = -2.0199;
	sCPUtoCLAMsg.x5.f32 = 3.2166;		sCPUtoCLAMsg.x6.f32 = 3.2163;
	sCPUtoCLAMsg.x7.f32 = 0.0000;		sCPUtoCLAMsg.x8.f32 = -1.5000;
#endif				
}

/*
 * Function 	: vInitDataForTask8
 * Arguments 	: None
 * Returns 		: None
 * Description 	: Initializes data points that will be used in Task 8 of the CLA
 */
void vInitDataForTask8()
{
	
}


//User defined ISRs
interrupt void cla_task1_isr( void)
{
	PieCtrlRegs.PIEACK.bit.ACK11 = 1;	
}

interrupt void cla_task2_isr( void)
{
	PieCtrlRegs.PIEACK.bit.ACK11 = 1;	
}

interrupt void cla_task3_isr( void)
{
	PieCtrlRegs.PIEACK.bit.ACK11 = 1;	
}

interrupt void cla_task4_isr( void)
{
	PieCtrlRegs.PIEACK.bit.ACK11 = 1;	
}

interrupt void cla_task5_isr( void)
{
	PieCtrlRegs.PIEACK.bit.ACK11 = 1;	
}

interrupt void cla_task6_isr( void)
{
	PieCtrlRegs.PIEACK.bit.ACK11 = 1;	
}

interrupt void cla_task7_isr( void)
{
	PieCtrlRegs.PIEACK.bit.ACK11 = 1;	
}

interrupt void cla_task8_isr( void)
{
	PieCtrlRegs.PIEACK.bit.ACK11 = 1;	
}

interrupt void NEW_ILLEGAL_ISR(void)
{
	 FAIL_COUNT++;
    asm("          ESTOP0");
    for(;;);
}

/*-----------------------------------------------------------------------------
 * End of File 
 * --------------------------------------------------------------------------*/
