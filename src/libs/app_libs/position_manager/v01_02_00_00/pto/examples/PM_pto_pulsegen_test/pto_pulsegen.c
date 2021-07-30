//----------------------------------------------------------------------------------
//	FILE:			pulsegen.c
//
//	Description:	Contains all the initialization, data declarations and setup
//					for pulsegen pto interface. This file serves are a template for
//					using PM_pto_pulsegen Library to interface and incorporates all the
//					library specific initializations and other important aspects of usage.
//
//	Version: 		1.0
//
//  Target:  		TMS320F28379D,
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2004-2015
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description / Status
//----------------------------------------------------------------------------------
// Mar 2017  - Example project for PM pto pulsegen Library Usage
//----------------------------------------------------------------------------------

#include "pto_pulsegen.h"
#include "F28x_Project.h"     // Device Headerfile and Examples Include File
uint16_t i;
uint32_t remVal;

uint16_t inumPulses1=50, iPeriod1=1000, iptoInterruptTime1=500, iptoDirection1=1, irun1=1;
uint16_t inumPulses2=50, iPeriod2=1000, iptoInterruptTime2=500, iptoDirection2=0, irun2=1;

// Function to initialize pto_pulsegen operation
void pto_pulsegen_Init(void)
{

	EALLOW;
//Enable clocks to PWM4
	CpuSysRegs.PCLKCR2.bit.EPWM4 = 1;
	EDIS;

//Configure EPWM4 to drive default values on GPIO6 and GPIO7
	EPWM4_Config();

	pto_pulsegen_setup_GPIO();
	PM_pto_pulsegen_setupPeriph();

	EALLOW;
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
	PieVectTable.PIE20_RESERVED_INT = &ptoIsr;
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
	PieCtrlRegs.PIEIER5.bit.INTx8 = 1;     // Enable PIE Group 5, INT 8 - CLB4
	IER |= 0x10;                            // Enable CPU INT5
	EINT;
	EDIS;

	DELAY_US(100000L);
}

void pto_pulsegen_setup_GPIO(void)
{

	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1; // Configure GPIO6 (Pulse out A)

//	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1; // Configure GPIO7 (Pulse out B)

	GpioCtrlRegs.GPAGMUX1.bit.GPIO15 = 1; // Configure GPIO15 as direction output - outxbar4
	GpioCtrlRegs.GPAMUX1.bit.GPIO15 = 2;

	EDIS;
}


void error(void)
{
	asm("     ESTOP0");
	//Test failed!! Stop!
	for (;;);
}

void EPWM4_Config(void)
{
	EALLOW;
	EPwm4Regs.TZCTL.bit.TZA = 1;
	EPwm4Regs.TZCTL.bit.TZB = 1;
	EPwm4Regs.TZFRC.bit.OST = 1;
	EDIS;
}

//This function can optionally used in turn to call and set parameters for PM_pto_pulsegen_runPulseGen function
//Users can choose to use the PM_pto_pulsegen_runPulseGen directly

uint32_t pto_setOptions(
		uint32_t numPulses,				// Number of pulses in the given pto period
		uint32_t Period,				// PTO period - specify in CLB clock cycles (SYSCLK/2)
		uint32_t ptoInterruptTime,		// PTO interrupt time - specify in CLB clock cycles (SYSCLK/2) - 40-60% of Period
		uint16_t ptoDirection,			// Direction output for the upcoming pto period
		uint16_t run)					// Run=1/Stop=0
{
	uint32_t pulseFreq, reminder;
	uint32_t PulseLo;
	uint32_t PulseHi;
	uint32_t ptoActivePeriod;
	uint32_t ptoFullPeriod;


	pulseFreq = Period / numPulses;
	reminder = Period - (pulseFreq * numPulses);
	PulseLo = (pulseFreq/2 );
	PulseHi = pulseFreq - PulseLo;
	ptoActivePeriod = (pulseFreq * numPulses);
	ptoFullPeriod = Period;

	PM_pto_pulsegen_runPulseGen(
			PulseLo,
			PulseHi,
			ptoActivePeriod,
			ptoFullPeriod,
			ptoInterruptTime,
			ptoDirection,
			run);
	return(reminder);
}

interrupt void ptoIsr(void)
{
//uint32_t	retval1; // can be optionally used to accumulate reminder for the next period

	if(i==0)
	{
		// pto_setOptions(numPulses, Period, ptoInterruptTime, ptoDirection, run)
		remVal = pto_setOptions(inumPulses1, iPeriod1, iptoInterruptTime1, iptoDirection1, irun1);
		i=1;
	}
	else
	{
		remVal = pto_setOptions(inumPulses2, iPeriod2, iptoInterruptTime2, iptoDirection2, irun2);
		i=0;
	}

	PieCtrlRegs.PIEACK.all|=0x10;       // Issue PIE ack

}
