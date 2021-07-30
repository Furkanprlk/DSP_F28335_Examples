//#############################################################################
//! \file  /examples/common/2837x_examples_setup.c
//!
//! \brief  Initialization routines for the CLA Math library examples
//! \date   Mar 18, 2014
//
//  Group:             C2000
//  Target Family:     F2837x
//
// (C)Copyright 2014, Texas Instruments, Inc.
//#############################################################################
//$TI Release: CLA Math Library for CLA C Compiler V4.00.01.00 $
//$Release Date: Apr 23, 2014 $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "F28x_Project.h"
#include "F2837xD_Cla_defines.h"
#include "CLAShared.h"

//*****************************************************************************
// defines
//*****************************************************************************
#define CPU_FRQ_200MHZ	1
//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// Function Prototypes
//*****************************************************************************
// \brief Initialize system clocks
//
void CLA_MATH_initSystemClocks(void);

// \brief Initialize Enhanced PIE
//
void CLA_MATH_initEpie(void);

// \brief Configure CLA memory space
//
void CLA_MATH_configClaMemory(void);

// \brief Intialize the MVECT registers for the CLA
//
void CLA_MATH_initCpu1Cla1(void);

//*****************************************************************************
// main
//*****************************************************************************
int main( void )
{
	CLA_MATH_initSystemClocks();

	CLA_MATH_initEpie();
	
    CLA_MATH_configClaMemory();

    CLA_MATH_initCpu1Cla1();

    // Step 1: Run the test
    test_run();

    // Step 2: Verify the result
	test_report();

    return 1;
}
// End of main

//*****************************************************************************
// function definitions
//*****************************************************************************

void CLA_MATH_initSystemClocks()
{
	InitSysCtrl();				//Enable peripheral clocks

	ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = 0x00;
}

void CLA_MATH_initEpie()
{
	DINT;						//Globally disable maskable CPU interrupts
	InitPieCtrl();				//Clear and disable all PIE interrupts
	IER = 0x0000;				//Individually disable maskable CPU interrupts
	IFR = 0x0000;				//Clear all CPU interrupt flags
	InitPieVectTable();			//Populate the PIE interrupt vector table with shell ISRs
}


void CLA_MATH_configClaMemory(void)
{
	extern uint32_t Cla1ProgRunStart, Cla1ProgLoadStart, Cla1ProgLoadSize;
	extern uint32_t CLA1mathTablesRunStart, CLA1mathTablesLoadStart, CLA1mathTablesLoadSize;

	EALLOW;
#ifdef CPU1
	// Enable CPU1.CLA1
	DevCfgRegs.DC1.bit.CPU1_CLA1 = 1;
#endif //CPU1

#ifdef _FLASH
	// Copy over code and tables from FLASH to RAM
	memcpy((uint32_t *)&Cla1ProgRunStart, (uint32_t *)&Cla1ProgLoadStart,
			(uint32_t)&Cla1ProgLoadSize);

#ifndef CLA_MATH_TABLES_IN_ROM
	memcpy((uint32_t *)&CLA1mathTablesRunStart, (uint32_t *)&CLA1mathTablesLoadStart,
			(uint32_t)&CLA1mathTablesLoadSize);
#endif //CLA_MATH_TABLES_IN_ROM

#endif //_FLASH

	// Initialize and wait for CLA1ToCPUMsgRAM
	MemCfgRegs.MSGxINIT.bit.INIT_CLA1TOCPU = 1;
	while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CLA1TOCPU != 1){};

	// Initialize and wait for CPUToCLA1MsgRAM
	MemCfgRegs.MSGxINIT.bit.INIT_CPUTOCLA1 = 1;
	while(MemCfgRegs.MSGxINITDONE.bit.INITDONE_CPUTOCLA1 != 1){};

	// Select LS0RAM to be the programming space for the CLA
	// First configure the CLA to be the master for LS0 and then
	// set the space to be a program block
	MemCfgRegs.LSxMSEL.bit.MSEL_LS0 = 1;
	MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS0 = 1;

	//Next configure LS1-LS5RAM as data spaces for the CLA
	// First configure the CLA to be the master for LSx and then
    // set the spaces to be code blocks
	MemCfgRegs.LSxMSEL.bit.MSEL_LS1 = 1;
	MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS1 = 0;

	MemCfgRegs.LSxMSEL.bit.MSEL_LS2 = 1;
	MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS2 = 0;

	MemCfgRegs.LSxMSEL.bit.MSEL_LS3 = 1;
	MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS3 = 0;

	MemCfgRegs.LSxMSEL.bit.MSEL_LS4 = 1;
	MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS4 = 0;

	MemCfgRegs.LSxMSEL.bit.MSEL_LS5 = 1;
	MemCfgRegs.LSxCLAPGM.bit.CLAPGM_LS5 = 0;

	EDIS;
}

void CLA_MATH_initCpu1Cla1(void)
{
	//  Compute all CLA task vectors
	// On Type-1 CLAs the MVECT registers accept full 16-bit task addresses as
	// opposed to offsets used on older Type-0 CLAs
	EALLOW;
	Cla1Regs.MVECT1 = (uint16_t)(&Cla1Task1);
	Cla1Regs.MVECT2 = (uint16_t)(&Cla1Task2);
	Cla1Regs.MVECT3 = (uint16_t)(&Cla1Task3);
	Cla1Regs.MVECT4 = (uint16_t)(&Cla1Task4);
	Cla1Regs.MVECT5 = (uint16_t)(&Cla1Task5);
	Cla1Regs.MVECT6 = (uint16_t)(&Cla1Task6);
	Cla1Regs.MVECT7 = (uint16_t)(&Cla1Task7);
	Cla1Regs.MVECT8 = (uint16_t)(&Cla1Task8);

	// Enable IACK instruction to start a task on CLA in software
	// for all  8 CLA tasks
	asm("   RPT #3 || NOP");
    Cla1Regs.MCTL.bit.IACKE = 1;
    Cla1Regs.MIER.all 	= 0x00FF;

    // Optional: If enabling interrupts, be sure to copy the ISR addresses
    // into the PIE vector table
	// Enable CLA interrupts at the group and subgroup levels
	// PieCtrlRegs.PIEIER11.all  = 0xFFFF;
	// IER |= (M_INT11 );

}
// End of file
