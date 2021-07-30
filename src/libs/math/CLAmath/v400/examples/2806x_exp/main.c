//###########################################################################
// Description:
//
// This example calls the arc-cosine function(CLAexp) of the CLA
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
#pragma DATA_SECTION(fVal,"CpuToCla1MsgRAM")
float fVal;
#pragma DATA_SECTION(fResult,"Cla1ToCpuMsgRAM")
float fResult;

//Golden Test Values
float test_values[BUFFER_SIZE] = {
 -1.0000,  -0.9843,  -0.9685,  -0.9528,  -0.9370,  -0.9213,  -0.9055,  -0.8898,
 -0.8740,  -0.8583,  -0.8425,  -0.8268,  -0.8110,  -0.7953,  -0.7795,  -0.7638,
 -0.7480,  -0.7323,  -0.7165,  -0.7008,  -0.6850,  -0.6693,  -0.6535,  -0.6378,
 -0.6220,  -0.6063,  -0.5906,  -0.5748,  -0.5591,  -0.5433,  -0.5276,  -0.5118,
 -0.4961,  -0.4803,  -0.4646,  -0.4488,  -0.4331,  -0.4173,  -0.4016,  -0.3858,
 -0.3701,  -0.3543,  -0.3386,  -0.3228,  -0.3071,  -0.2913,  -0.2756,  -0.2598,
 -0.2441,  -0.2283,  -0.2126,  -0.1969,  -0.1811,  -0.1654,  -0.1496,  -0.1339,
 -0.1181,  -0.1024,  -0.0866,  -0.0709,  -0.0551,  -0.0394,  -0.0236,  -0.0079,
  0.0079,   0.0236,   0.0394,   0.0551,   0.0709,   0.0866,   0.1024,   0.1181,
  0.1339,   0.1496,   0.1654,   0.1811,   0.1969,   0.2126,   0.2283,   0.2441,
  0.2598,   0.2756,   0.2913,   0.3071,   0.3228,   0.3386,   0.3543,   0.3701,
  0.3858,   0.4016,   0.4173,   0.4331,   0.4488,   0.4646,   0.4803,   0.4961,
  0.5118,   0.5276,   0.5433,   0.5591,   0.5748,   0.5906,   0.6063,   0.6220,
  0.6378,   0.6535,   0.6693,   0.6850,   0.7008,   0.7165,   0.7323,   0.7480,
  0.7638,   0.7795,   0.7953,   0.8110,   0.8268,   0.8425,   0.8583,   0.8740,
  0.8898,   0.9055,   0.9213,   0.9370,   0.9528,   0.9685,   0.9843,   1.0000
};	

float res_expected[BUFFER_SIZE]={
  0.3679,   0.3737,   0.3797,   0.3857,   0.3918,   0.3980,   0.4043,   0.4108,
  0.4173,   0.4239,   0.4306,   0.4375,   0.4444,   0.4515,   0.4586,   0.4659,
  0.4733,   0.4808,   0.4884,   0.4962,   0.5041,   0.5121,   0.5202,   0.5285,
  0.5368,   0.5454,   0.5540,   0.5628,   0.5717,   0.5808,   0.5900,   0.5994,
  0.6089,   0.6186,   0.6284,   0.6384,   0.6485,   0.6588,   0.6693,   0.6799,
  0.6907,   0.7016,   0.7128,   0.7241,   0.7356,   0.7473,   0.7591,   0.7712,
  0.7834,   0.7958,   0.8085,   0.8213,   0.8343,   0.8476,   0.8610,   0.8747,
  0.8886,   0.9027,   0.9170,   0.9316,   0.9464,   0.9614,   0.9767,   0.9922,
  1.0079,   1.0239,   1.0402,   1.0567,   1.0734,   1.0905,   1.1078,   1.1254,
  1.1432,   1.1614,   1.1798,   1.1985,   1.2176,   1.2369,   1.2565,   1.2765,
  1.2967,   1.3173,   1.3382,   1.3595,   1.3810,   1.4030,   1.4252,   1.4478,
  1.4708,   1.4942,   1.5179,   1.5420,   1.5665,   1.5913,   1.6166,   1.6422,
  1.6683,   1.6948,   1.7217,   1.7490,   1.7768,   1.8050,   1.8336,   1.8627,
  1.8923,   1.9223,   1.9529,   1.9838,   2.0153,   2.0473,   2.0798,   2.1128,
  2.1464,   2.1804,   2.2151,   2.2502,   2.2859,   2.3222,   2.3591,   2.3965,
  2.4346,   2.4732,   2.5125,   2.5523,   2.5928,   2.6340,   2.6758,   2.7183
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
	 fVal = test_values[i];
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
	  if( fErrMetric < EPSILON){
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

