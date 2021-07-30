//###########################################################################
// Description:
//
// This example calls the cosine function(CLAcos) of the CLA
// math library on a test vector and compares the result to the
// equivalent "math.h" routine
//
//###########################################################################
// $TI Release: CLA Math Library for CLA C Compiler V4.00 $
// $Release Date: December 10, 2011 $
//###########################################################################

#include "DSP28x_Project.h"
#include "CLAShared.h"
#include "math.h"

#define CLA1_RAM0_ENABLE	0
#define CLA1_RAM1_ENABLE	1

#define EPSILON				1e-2

// Constants
#define WAITSTEP	asm(" RPT #255||NOP")

//Global Variables
//Task 1 (C) Variables
float y[BUFFER_SIZE];
#pragma DATA_SECTION(fAngle,"CpuToCla1MsgRAM")
float fAngle;
#pragma DATA_SECTION(fResult,"Cla1ToCpuMsgRAM")
float fResult;

//Golden Test Values
float test_values[BUFFER_SIZE] = {
 -1.5708,  -1.5461,  -1.5213,  -1.4966,  -1.4718,  -1.4471,  -1.4224,  -1.3976,
 -1.3729,  -1.3482,  -1.3234,  -1.2987,  -1.2740,  -1.2492,  -1.2245,  -1.1997,
 -1.1750,  -1.1503,  -1.1255,  -1.1008,  -1.0761,  -1.0513,  -1.0266,  -1.0018,
 -0.9771,  -0.9524,  -0.9276,  -0.9029,  -0.8782,  -0.8534,  -0.8287,  -0.8040,
 -0.7792,  -0.7545,  -0.7297,  -0.7050,  -0.6803,  -0.6555,  -0.6308,  -0.6061,
 -0.5813,  -0.5566,  -0.5318,  -0.5071,  -0.4824,  -0.4576,  -0.4329,  -0.4082,
 -0.3834,  -0.3587,  -0.3339,  -0.3092,  -0.2845,  -0.2597,  -0.2350,  -0.2103,
 -0.1855,  -0.1608,  -0.1361,  -0.1113,  -0.0866,  -0.0618,  -0.0371,  -0.0124,
  0.0124,   0.0371,   0.0618,   0.0866,   0.1113,   0.1361,   0.1608,   0.1855,
  0.2103,   0.2350,   0.2597,   0.2845,   0.3092,   0.3339,   0.3587,   0.3834,
  0.4082,   0.4329,   0.4576,   0.4824,   0.5071,   0.5318,   0.5566,   0.5813,
  0.6061,   0.6308,   0.6555,   0.6803,   0.7050,   0.7297,   0.7545,   0.7792,
  0.8040,   0.8287,   0.8534,   0.8782,   0.9029,   0.9276,   0.9524,   0.9771,
  1.0018,   1.0266,   1.0513,   1.0761,   1.1008,   1.1255,   1.1503,   1.1750,
  1.1997,   1.2245,   1.2492,   1.2740,   1.2987,   1.3234,   1.3482,   1.3729,
  1.3976,   1.4224,   1.4471,   1.4718,   1.4966,   1.5213,   1.5461,   1.5708
};	
	
float res_expected[BUFFER_SIZE]={
  0.0000,   0.0247,   0.0495,   0.0741,   0.0988,   0.1234,   0.1479,   0.1723,
  0.1966,   0.2208,   0.2449,   0.2688,   0.2925,   0.3161,   0.3394,   0.3626,
  0.3855,   0.4082,   0.4307,   0.4529,   0.4748,   0.4964,   0.5177,   0.5387,
  0.5594,   0.5798,   0.5997,   0.6193,   0.6386,   0.6574,   0.6758,   0.6939,
  0.7115,   0.7286,   0.7453,   0.7616,   0.7774,   0.7927,   0.8076,   0.8219,
  0.8357,   0.8491,   0.8619,   0.8742,   0.8859,   0.8971,   0.9078,   0.9179,
  0.9274,   0.9364,   0.9448,   0.9526,   0.9598,   0.9665,   0.9725,   0.9780,
  0.9828,   0.9871,   0.9908,   0.9938,   0.9963,   0.9981,   0.9993,   0.9999,
  0.9999,   0.9993,   0.9981,   0.9963,   0.9938,   0.9908,   0.9871,   0.9828,
  0.9780,   0.9725,   0.9665,   0.9598,   0.9526,   0.9448,   0.9364,   0.9274,
  0.9179,   0.9078,   0.8971,   0.8859,   0.8742,   0.8619,   0.8491,   0.8357,
  0.8219,   0.8076,   0.7927,   0.7774,   0.7616,   0.7453,   0.7286,   0.7115,
  0.6939,   0.6758,   0.6574,   0.6386,   0.6193,   0.5997,   0.5798,   0.5594,
  0.5387,   0.5177,   0.4964,   0.4748,   0.4529,   0.4307,   0.4082,   0.3855,
  0.3626,   0.3394,   0.3161,   0.2925,   0.2688,   0.2449,   0.2208,   0.1966,
  0.1723,   0.1479,   0.1234,   0.0988,   0.0741,   0.0495,   0.0247,   0.0000
};

//Linker defined vars
extern Uint16 Cla1Prog_Start;

//CLA ISRs
interrupt void cla1_task1_isr( void );


//! Main Function
void main(void)
{
   //! Step 1: Setup the system clock
   /*! Disable the watchdog timer, initialize the system clock,
    *  PLL and configure the peripheral clock.
    */
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
    PieVectTable.CLA1_INT1  = &cla1_task1_isr;
	EDIS;

    /*! Compute all CLA task vectors */ 
    EALLOW;
    Cla1Regs.MVECT1 = ((Uint16)Cla1Task1 - (Uint16)&Cla1Prog_Start);
    EDIS;
   
    //! Step 3 : Mapping CLA tasks
    /*! All tasks are enabled and will be started by an ePWM trigger
     *  Map CLA program memory to the CLA and enable software breakpoints
     */
    EALLOW;
	Cla1Regs.MPISRCSEL1.bit.PERINT1SEL 	= CLA_INT1_NONE;
	Cla1Regs.MIER.all 		 		    = 0x00FF;
	EDIS;	
    
 
    /*! Enable CLA interrupts at the group and subgroup levels */
    PieCtrlRegs.PIEIER11.all       = 0xFFFF;
    IER = (M_INT11 );
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    /*!Switch the CLA program space to the CLA and enable software forcing
     * Also switch over CLA data ram 0 and 1
     */
    EALLOW;
    Cla1Regs.MMEMCFG.bit.PROGE 	= 1;
    Cla1Regs.MCTL.bit.IACKE	= 1;
    Cla1Regs.MMEMCFG.bit.RAM0E	= CLA1_RAM0_ENABLE;
    Cla1Regs.MMEMCFG.bit.RAM1E	= CLA1_RAM1_ENABLE;
    EDIS;	

    // Invoke Task(s)
    test_run();

    // Report Results
    test_report();

	//Forever loop
	while(1){
	 asm(" NOP");
	}

}

//C28 C tasks
void test_run(void)
{
	int i;
	for(i=0;i<BUFFER_SIZE;i++)
	{
	 fAngle = test_values[i];
	 Cla1ForceTask1andWait();
     WAITSTEP;
	 y[i] = fResult; 
	}
}

void test_report(void)
{
	unsigned int i;
	unsigned int pass_count=0;
	unsigned int fail_count=0;
	float fError[BUFFER_SIZE];
	float fErrMetric;
	for(i=0;i<BUFFER_SIZE;i++){
	  fError[i] = fabs(res_expected[i]-y[i]);
	  fErrMetric = fError[i];
	  if( fErrMetric < 1e-4){
		pass_count++;
	  }else{
		fail_count++;
	  }
	}
	if(fail_count) test_error(); 
}

void test_error( void )
{
	asm(" ESTOP0");	
}



//CLA ISR's
interrupt void cla1_task1_isr( void)
{
        PieCtrlRegs.PIEACK.bit.ACK11 = 1;
}

