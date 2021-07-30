//#############################################################################
//! \file  /examples/common/2806x_examples_setup.c
//!
//! \brief  Initialization routines for the CLA Math library examples
//! \date   March 17, 2014
//
//  Group:             C2000
//  Target Family:     F2806x
//
// (C)Copyright 2014, Texas Instruments, Inc.
//#############################################################################
//$TI Release: CLA Math Library for CLA C Compiler V4.00.01.00 $
//$Release Date: Apr 23, 2014 $
//#############################################################################

#include <stdint.h>
#include "DSP28x_Project.h"
#include "CLAShared.h"

#define CLA1_RAM0_ENABLE	1
#define CLA1_RAM1_ENABLE	1

//Linker defined vars
extern uint16_t Cla1Prog_Start;
extern uint16_t Cla1ProgRunStart, Cla1ProgLoadStart, Cla1ProgLoadSize;
extern uint16_t CLA1mathTablesRunStart, CLA1mathTablesLoadStart, CLA1mathTablesLoadSize;

//! Main Function
void main(void)
{
   //! Step 1: Setup the system clock
   /*! Disable the watchdog timer, initialize the system clock,
    *  PLL and configure the peripheral clock.
    */
	InitSysCtrl();

#ifdef _FLASH
	// Copy time critical code and Flash setup code to RAM
	// The  RamfuncsLoadStart, RamfuncsLoadSize, and RamfuncsRunStart
	// symbols are created by the linker. Refer to the F28069.cmd file.
	//
	   memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (Uint32)&RamfuncsLoadSize);

	// Copy CLA code from flash to RAM
	   memcpy(&Cla1ProgRunStart, &Cla1ProgLoadStart, (Uint32)&Cla1ProgLoadSize);

	// Copy CLA math tabes from flash to RAM
	   memcpy(&CLA1mathTablesRunStart, &CLA1mathTablesLoadStart, (Uint32)&CLA1mathTablesLoadSize);

	// Call Flash Initialization to setup flash waitstates
	// This function must reside in RAM
	//
	   InitFlash();
#endif //FLASH

   //! Step 2: Initialize PIE control
   /*! Intialize PIE control, disable all interrupts and
    * then copy over the PIE Vector table from BootROM to RAM
    */
   DINT;
   InitPieCtrl();
   IER = 0x00000000;
   IFR = 0x00000000;
   InitPieVectTable();

   /*! Compute all CLA task vectors */ 
    EALLOW;
    Cla1Regs.MVECT1 = (uint16_t)((uint32_t)&Cla1Task1 - (uint32_t)&Cla1Prog_Start);
    Cla1Regs.MVECT2 = (uint16_t)((uint32_t)&Cla1Task2 - (uint32_t)&Cla1Prog_Start);
    Cla1Regs.MVECT3 = (uint16_t)((uint32_t)&Cla1Task3 - (uint32_t)&Cla1Prog_Start);
    Cla1Regs.MVECT4 = (uint16_t)((uint32_t)&Cla1Task4 - (uint32_t)&Cla1Prog_Start);
    Cla1Regs.MVECT5 = (uint16_t)((uint32_t)&Cla1Task5 - (uint32_t)&Cla1Prog_Start);
    Cla1Regs.MVECT6 = (uint16_t)((uint32_t)&Cla1Task6 - (uint32_t)&Cla1Prog_Start);
    Cla1Regs.MVECT7 = (uint16_t)((uint32_t)&Cla1Task7 - (uint32_t)&Cla1Prog_Start);
    Cla1Regs.MVECT8 = (uint16_t)((uint32_t)&Cla1Task8 - (uint32_t)&Cla1Prog_Start);
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
	Cla1Regs.MIER.all 		 		    = 0x00FF;
	EDIS;	
    
 
    // Optional: If enabling interrupts, be sure to copy the ISR addresses
    // into the PIE vector table
	// Enable CLA interrupts at the group and subgroup levels
	// PieCtrlRegs.PIEIER11.all  = 0xFFFF;
	// IER |= (M_INT11 );
    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    /*!Switch the CLA program space to the CLA and enable software forcing
     * Also switch over CLA data ram 0 and 1
     */
    EALLOW;
    Cla1Regs.MMEMCFG.bit.PROGE 	= 1;
    Cla1Regs.MCTL.bit.IACKE	    = 1;
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
