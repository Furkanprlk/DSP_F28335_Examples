//###########################################################################
// Description:
//
// This example calls the divide function(CLAdiv) of the CLA
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

// Constants
#define WAITSTEP	asm(" RPT #255||NOP")

//Global Variables
//Task 1 (C) Variables
float y[BUFFER_SIZE];
#pragma DATA_SECTION(fVal1,"CpuToCla1MsgRAM")
float fVal1;
#pragma DATA_SECTION(fVal2,"CpuToCla1MsgRAM")
float fVal2;
#pragma DATA_SECTION(fResult,"Cla1ToCpuMsgRAM")
float fResult;

//Golden Test Values
float test_num[BUFFER_SIZE] = {
-1.224647e-16, -0.04945372, -0.09878642, -0.1478774, -0.1966064, 
-0.2448544, -0.2925031, -0.3394361, -0.3855383, -0.4306971, 
-0.4748020, -0.5177448, -0.5594208, -0.5997276, -0.6385669, 
-0.6758435, -0.7114661, -0.7453477, -0.7774054, -0.8075605, 
-0.8357394, -0.8618732, -0.8858978, -0.9077544, -0.9273896,
-0.9447554, -0.9598091, -0.9725141, -0.9828392, -0.9907590, 
-0.9962543, -0.9993117, -0.9999235, -0.9980884, -0.9938107, 
-0.9871011, -0.9779758, -0.9664573, -0.9525737, -0.9363590, 
-0.9178528, -0.8971006, -0.8741529, -0.8490661, -0.8219014, 
-0.7927254, -0.7616096, -0.7286299, -0.6938671, -0.6574063, 
-0.6193367, -0.5797516, -0.5387476, -0.4964253, -0.4528881, 
-0.4082426, -0.3625982, -0.3160663, -0.2687610, -0.2207980, 
-0.1722946, -0.1233696, -0.07414275, -0.02473443, 0.02473443, 
0.07414275, 0.1233696, 0.1722946, 0.2207980, 0.2687610, 
0.3160663, 0.3625982, 0.4082426, 0.4528881, 0.4964253, 
0.5387476, 0.5797516, 0.6193367, 0.6574063, 0.6938671, 
0.7286299, 0.7616096, 0.7927254, 0.8219014, 0.8490661, 
0.8741529, 0.8971006, 0.9178528, 0.9363590, 0.9525737, 
0.9664573, 0.9779758, 0.9871011, 0.9938107, 0.9980884, 
0.9999235, 0.9993117, 0.9962543, 0.9907590, 0.9828392, 
0.9725141, 0.9598091, 0.9447554, 0.9273896, 0.9077544, 
0.8858978, 0.8618732, 0.8357394, 0.8075605, 0.7774054, 
0.7453477, 0.7114661, 0.6758435, 0.6385669, 0.5997276, 
0.5594208, 0.5177448, 0.4748020, 0.4306971, 0.3855383, 
0.3394361, 0.2925031, 0.2448544, 0.1966064, 0.1478774, 
0.09878642, 0.04945372, 1.224647e-16	
};

float test_den[BUFFER_SIZE] = {
-1, -0.9987764, -0.9951087, -0.9890057, -0.9804825, 
-0.9695598, -0.9562646, -0.9406291, -0.9226918, -0.9024965, 
-0.8800927, -0.8555351, -0.8288838, -0.8002042, -0.7695663, 
-0.7370452, -0.7027203, -0.6666759, -0.6289999, -0.5897847, 
-0.5491262, -0.5071239, -0.4638805, -0.4195020, -0.3740968, 
-0.3277763, -0.2806535, -0.2328440, -0.1844646, -0.1356339, 
-0.08647120, -0.03709691, 0.01236816, 0.06180296, 0.1110865, 
0.1600982, 0.2087182, 0.2568273, 0.3043080, 0.3510439, 
0.3969209, 0.4418264, 0.4856508, 0.5282866, 0.5696297, 
0.6095788, 0.6480362, 0.6849077, 0.7201031, 0.7535363, 
0.7851254, 0.8147933, 0.8424672, 0.8680794, 0.8915673, 
0.9128734, 0.9319456, 0.9487371, 0.9632069, 0.9753196, 
0.9850455, 0.9923608, 0.9972476, 0.9996940, 0.9996940, 
0.9972476, 0.9923608, 0.9850455, 0.9753196, 0.9632069, 
0.9487371, 0.9319456, 0.9128734, 0.8915673, 0.8680794, 
0.8424672, 0.8147933, 0.7851254, 0.7535363, 0.7201031, 
0.6849077, 0.6480362, 0.6095788, 0.5696297, 0.5282866, 
0.4856508, 0.4418264, 0.3969209, 0.3510439, 0.3043080, 
0.2568273, 0.2087182, 0.1600982, 0.1110865, 0.06180296, 
0.01236816, -0.03709691, -0.08647120, -0.1356339, -0.1844646, 
-0.2328440, -0.2806535, -0.3277763, -0.3740968, -0.4195020, 
-0.4638805, -0.5071239, -0.5491262, -0.5897847, -0.6289999, 
-0.6666759, -0.7027203, -0.7370452, -0.7695663, -0.8002042, 
-0.8288838, -0.8555351, -0.8800927, -0.9024965, -0.9226918, 
-0.9406291, -0.9562646, -0.9695598, -0.9804825, -0.9890057, 
-0.9951087, -0.9987764, -1
};

float res_expected[BUFFER_SIZE]={
1.224647e-16, 0.04951430, 0.09927199, 0.1495212, 0.2005201, 
0.2525418, 0.3058810, 0.3608607, 0.4178409, 0.4772286, 
0.5394909, 0.6051708, 0.6749085, 0.7494682, 0.8297750, 
0.9169635, 1.012446, 1.118006, 1.235939, 1.369246, 
1.521944, 1.699532, 1.909754, 2.163886, 2.479009, 
2.882318, 3.419908, 4.176677, 5.328063, 7.304658, 
11.52123, 26.93787, -80.84659, -16.14952, -8.946276, 
-6.165596, -4.685629, -3.763063, -3.130295, -2.667356, 
-2.312433, -2.030437, -1.799962, -1.607207, -1.442870, 
-1.300448, -1.175258, -1.063837, -0.9635663, -0.8724282, 
-0.7888379, -0.7115321, -0.6394879, -0.5718662, -0.5079685, 
-0.4472062, -0.3890765, -0.3331442, -0.2790273, -0.2263852, 
-0.1749103, -0.1243193, -0.07434738, -0.02474200, 0.02474200, 
0.07434738, 0.1243193, 0.1749103, 0.2263852, 0.2790273, 
0.3331442, 0.3890765, 0.4472062, 0.5079685, 0.5718662, 
0.6394879, 0.7115321, 0.7888379, 0.8724282, 0.9635663, 
1.063837, 1.175258, 1.300448, 1.442870, 1.607207, 
1.799962, 2.030437, 2.312433, 2.667356, 3.130295, 
3.763063, 4.685629, 6.165596, 8.946276, 16.14952, 
80.84659, -26.93787, -11.52123, -7.304658, -5.328063, 
-4.176677, -3.419908, -2.882318, -2.479009, -2.163886, 
-1.909754, -1.699532, -1.521944, -1.369246, -1.235939, 
-1.118006, -1.012446, -0.9169635, -0.8297750, -0.7494682, 
-0.6749085, -0.6051708, -0.5394909, -0.4772286, -0.4178409, 
-0.3608607, -0.3058810, -0.2525418, -0.2005201, -0.1495212, 
-0.09927199, -0.04951430, -1.224647e-16
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
	 fVal1 = test_num[i];
	 fVal2 = test_den[i];
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
	for(i=0;i<BUFFER_SIZE;i++){
		fError[i] = fabs(res_expected[i]-y[i]);
		if( fError[i] < 1e-4){
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

