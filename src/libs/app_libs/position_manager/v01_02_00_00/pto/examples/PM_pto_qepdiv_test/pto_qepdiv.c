//----------------------------------------------------------------------------------
//	FILE:			qepdiv.c
//
//	Description:	Contains all the initialization, data declarations and setup
//					for qepdiv pto interface. This file serves are a template for
//					using PM_pto_qepdiv Library to interface and incorporates all the
//					library specific initializations and other important aspects of usage.
//
//	Version: 		1.0
//
//  Target:  		TMS320F28377D,
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2004-2015
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description / Status
//----------------------------------------------------------------------------------
// Mar 2017  - Example project for PM pto qepdiv Library Usage
//----------------------------------------------------------------------------------

#include "pto_qepdiv.h"

#include "F28x_Project.h"     // Device Headerfile and Examples Include File

uint16_t i=0;

// Function to initialize pto_qepdiv operation
void pto_qepdiv_Init(void)
{

	EALLOW;
//Enable clocks to PWM2, 1
	CpuSysRegs.PCLKCR2.bit.EPWM2 = 1;
	CpuSysRegs.PCLKCR2.bit.EPWM1 = 1;
	EDIS;

//Configure EPWM2 to drive default values on GPIO2 and GPIO3
	EPWM2_Config();

	pto_qepdiv_setup_GPIO();
	PM_pto_qepdiv_setupPeriph();

	DELAY_US(100L);
}

void pto_qepdiv_setup_GPIO(void)
{

	EALLOW;

//QEP inputs to be tapped from GPIO10/11/13 - via InputXBar Input4/5/6
	InputXbarRegs.INPUT4SELECT = 10;	//  QEPA
	InputXbarRegs.INPUT5SELECT = 11;	//  QEPB
	InputXbarRegs.INPUT6SELECT = 13;	//  QEPI

//QEP outputs available on GPIO2/3 - QEPA/B (over EPWM2A/B)
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1; // Configure GPIO2 (Pulse out A)
	GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1; // Configure GPIO3 (Pulse out B)
//QEP outputs Index on OUTPUTXBAR3 - on GPIO4 (users can choose any GPIO with OUTPUTXBAR3
	GpioCtrlRegs.GPAGMUX1.bit.GPIO4 = 1; // Index output - outxbar3
	GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;

	EDIS;
}

void error(void)
{
	asm("     ESTOP0");
	//Test failed!! Stop!
	for (;;);
}

void EPWM2_Config(void)
{
	EALLOW;
	EPwm2Regs.TZCTL.bit.TZA = 1;
	EPwm2Regs.TZCTL.bit.TZB = 1;
	EPwm2Regs.TZFRC.bit.OST = 1;
	EDIS;
}
