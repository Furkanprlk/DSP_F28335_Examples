//###########################################################################
// Description:
//
// This example calls the arc-tangent function(CLAatan) of the CLA
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
float test_values[BUFFER_SIZE] ={
 -1.0000,  -0.9756,  -0.9517,  -0.9284,  -0.9056,  -0.8834,  -0.8616,  -0.8403,
 -0.8194,  -0.7989,  -0.7789,  -0.7592,  -0.7399,  -0.7209,  -0.7023,  -0.6839,
 -0.6659,  -0.6482,  -0.6308,  -0.6137,  -0.5968,  -0.5801,  -0.5637,  -0.5475,
 -0.5315,  -0.5158,  -0.5002,  -0.4848,  -0.4697,  -0.4546,  -0.4398,  -0.4251,
 -0.4106,  -0.3962,  -0.3820,  -0.3679,  -0.3539,  -0.3400,  -0.3263,  -0.3127,
 -0.2991,  -0.2857,  -0.2724,  -0.2591,  -0.2460,  -0.2329,  -0.2199,  -0.2070,
 -0.1941,  -0.1813,  -0.1685,  -0.1558,  -0.1432,  -0.1306,  -0.1180,  -0.1055,
 -0.0930,  -0.0806,  -0.0681,  -0.0557,  -0.0433,  -0.0309,  -0.0186,  -0.0062,
  0.0062,   0.0186,   0.0309,   0.0433,   0.0557,   0.0681,   0.0806,   0.0930,
  0.1055,   0.1180,   0.1306,   0.1432,   0.1558,   0.1685,   0.1813,   0.1941,
  0.2070,   0.2199,   0.2329,   0.2460,   0.2591,   0.2724,   0.2857,   0.2991,
  0.3127,   0.3263,   0.3400,   0.3539,   0.3679,   0.3820,   0.3962,   0.4106,
  0.4251,   0.4398,   0.4546,   0.4697,   0.4848,   0.5002,   0.5158,   0.5315,
  0.5475,   0.5637,   0.5801,   0.5968,   0.6137,   0.6308,   0.6482,   0.6659,
  0.6839,   0.7023,   0.7209,   0.7399,   0.7592,   0.7789,   0.7989,   0.8194,
  0.8403,   0.8616,   0.8834,   0.9056,   0.9284,   0.9517,   0.9756,   1.0000
};

float res_expected[BUFFER_SIZE]={
 -0.7854,  -0.7730,  -0.7607,  -0.7483,  -0.7359,  -0.7236,  -0.7112,  -0.6988,
 -0.6865,  -0.6741,  -0.6617,  -0.6493,  -0.6370,  -0.6246,  -0.6122,  -0.5999,
 -0.5875,  -0.5751,  -0.5628,  -0.5504,  -0.5380,  -0.5257,  -0.5133,  -0.5009,
 -0.4886,  -0.4762,  -0.4638,  -0.4514,  -0.4391,  -0.4267,  -0.4143,  -0.4020,
 -0.3896,  -0.3772,  -0.3649,  -0.3525,  -0.3401,  -0.3278,  -0.3154,  -0.3030,
 -0.2907,  -0.2783,  -0.2659,  -0.2536,  -0.2412,  -0.2288,  -0.2164,  -0.2041,
 -0.1917,  -0.1793,  -0.1670,  -0.1546,  -0.1422,  -0.1299,  -0.1175,  -0.1051,
 -0.0928,  -0.0804,  -0.0680,  -0.0557,  -0.0433,  -0.0309,  -0.0186,  -0.0062,
  0.0062,   0.0186,   0.0309,   0.0433,   0.0557,   0.0680,   0.0804,   0.0928,
  0.1051,   0.1175,   0.1299,   0.1422,   0.1546,   0.1670,   0.1793,   0.1917,
  0.2041,   0.2164,   0.2288,   0.2412,   0.2536,   0.2659,   0.2783,   0.2907,
  0.3030,   0.3154,   0.3278,   0.3401,   0.3525,   0.3649,   0.3772,   0.3896,
  0.4020,   0.4143,   0.4267,   0.4391,   0.4514,   0.4638,   0.4762,   0.4886,
  0.5009,   0.5133,   0.5257,   0.5380,   0.5504,   0.5628,   0.5751,   0.5875,
  0.5999,   0.6122,   0.6246,   0.6370,   0.6493,   0.6617,   0.6741,   0.6865,
  0.6988,   0.7112,   0.7236,   0.7359,   0.7483,   0.7607,   0.7730,   0.7854
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
	 fVal= test_values[i];
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

