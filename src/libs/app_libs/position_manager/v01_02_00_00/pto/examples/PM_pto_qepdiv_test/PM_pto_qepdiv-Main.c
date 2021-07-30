//----------------------------------------------------------------------------------
//	FILE:			PM_pto_qepdiv-Main.C
//
//	Description:	Example project for using PM pto_qepdiv Library.
//					Includes PM_pto_qepdiv_lib library and correspoding include files.
//
//	Version: 		1.0
//
//  Target:  		TMS320F28379D
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2004-2015
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description / Status
//----------------------------------------------------------------------------------
// Mar 2017  - Example project for PM QepDiv Library Usage
//----------------------------------------------------------------------------------
// Test Usage: This test can be run on the controlCard (F28379D) - refer to PTO library
// document for details of the connections needed.
// This test uses EPWM module as a way of simulating QEP input for test purposes.
// Users can change the PWM frequency to test the operation and also change the divider values as needed

#include "F28x_Project.h"    // Device Headerfile and Examples Include File

#include "pto_qepdiv.h"		 // Include file for pto_qepdiv interface
uint16_t retval1;
#define EPWM4_PRD 100
#define EPWM5_PRD 100
#define EPWM4_CMPA 50
#define EPWM4_CMPB 70
#define EPWM5_CMPA 50
void InitEPwm4Example(void);
void InitEPwm5Example(void);
void InitGPIO_Testing(void);

uint16_t divVal=4, divValnext=4, indexWidth=10;
uint16_t pwmperiod=100; //50000;
uint16_t pwmcmpa= 50; //25000;
uint16_t pwmcmpb= 70; //35000;

void main(void) {

// Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
	InitSysCtrl();
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
	DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
	InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
	IER = 0x0000;
	IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
	InitPieVectTable();

//Initialization routine for pto_qepdiv operation - defined in pto_qepdiv.c
//Configures the peripherals and enables clocks for required modules
//Configures GPIO and XBar as needed for pto_qepdiv operation
// Test setup on docking station -
//	EPWM4A (GPIO6)-> EQEPA (GPIO10)
//	EPWM5A (GPIO8)-> EQEPB (GPIO11)
//  EPWM4B (GPIO7)-> Index (GPIO13)
// These are just for test purposes and do not correspond to real time usage

	EALLOW;
	CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	EDIS;

//Test Code - PWMs used as test stimulus to emulate QEP inputs
	InitEPwm4Example();
	InitEPwm5Example();
	InitGPIO_Testing();
//Test Code - End

	CpuSysRegs.PCLKCR2.bit.EPWM1=1;
    CpuSysRegs.PCLKCR2.bit.EPWM2=1;
    CpuSysRegs.PCLKCR2.bit.EPWM3=1;

	pto_qepdiv_Init();
	DELAY_US(800L); 	//Delay 800us

	EALLOW;
	CpuSysRegs.PCLKCR0.bit.TBCLKSYNC = 1;
	EDIS;


// 2 => indicates the /4, change the number as needed - should be 2^N Ex:/2, /4, /8, /16... etc.
// Frequency of the output QEPA or QEPB = Frequency of input QEPA or QEPB / (2* divVal)
// Index output comes when there is raising edge detected on Index input
// Index output pulse width = indexWidth * (SYSCLK * 2) cycles

	retval1 = PM_pto_qepdiv_config(divVal, indexWidth);
	PM_pto_qepdiv_startOperation(1);

//Infinite loop
	while(1)
	{

		if(divVal != divValnext)
		{
			PM_pto_qepdiv_reset();
			DELAY_US(10L);
			divVal = divValnext;
			retval1 = PM_pto_qepdiv_config(divVal, indexWidth);
			PM_pto_qepdiv_startOperation(1);
		}

		asm(" NOP");
		asm(" NOP");
		asm(" NOP");
		asm(" NOP");
	}
}

// Test code - EPWMs used as stimulus to emulate QEP inputs
// Not needed in customer application
void InitEPwm4Example()
{
    //
    // Setup TBCLK
    //
    EPwm4Regs.TBPRD = pwmperiod;       // Set timer period 801 TBCLKs
    EPwm4Regs.TBPHS.bit.TBPHS = 0x0000;        // Phase is 0
    EPwm4Regs.TBCTR = 0x0000;                  // Clear counter

    //
    // Set Compare values
    //
    EPwm4Regs.CMPA.bit.CMPA = pwmcmpa;    // Set compare A value
    EPwm4Regs.CMPB.bit.CMPB = pwmcmpb;    // Set compare A value
    //
    // Setup counter mode
    //
    EPwm4Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up and down
    EPwm4Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm4Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm4Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    //
    // Setup shadowing
    //
    EPwm4Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm4Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // Load on Zero
    EPwm4Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Set actions
    //
//    EPwm4Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on event A, up count
//    EPwm4Regs.AQCTLA.bit.CAD = AQ_CLEAR;          // Clear PWM1A on event A,
    EPwm4Regs.AQCTLA.bit.ZRO = AQ_SET;
    EPwm4Regs.AQCTLA.bit.PRD = AQ_CLEAR;
    EPwm4Regs.AQCTLB.bit.CBU = AQ_SET;            // Set PWM1A on event A, up count
    EPwm4Regs.AQCTLB.bit.CBD = AQ_CLEAR;          // Clear PWM1A on event A,

}

//
// InitEPwm5Example - Initialize EPWM2 configuration
//
void InitEPwm5Example()
{
    //
    // Setup TBCLK
    //
    EPwm5Regs.TBPRD = pwmperiod;         // Set timer period 801 TBCLKs
    EPwm5Regs.TBPHS.bit.TBPHS = 0x0000;          // Phase is 0
    EPwm5Regs.TBCTR = 0x0000;                    // Clear counter

    //
    // Set Compare values
    //
    EPwm5Regs.CMPA.bit.CMPA = pwmcmpa;    // Set compare A value
    //
    // Setup counter mode
    //
    EPwm5Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN; // Count up and down
    EPwm5Regs.TBCTL.bit.PHSEN = TB_DISABLE;        // Disable phase loading
    EPwm5Regs.TBCTL.bit.HSPCLKDIV = TB_DIV1;       // Clock ratio to SYSCLKOUT
    EPwm5Regs.TBCTL.bit.CLKDIV = TB_DIV1;

    //
    // Setup shadowing
    //
    EPwm5Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;
    EPwm5Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO; // Load on Zero
    EPwm5Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;

    //
    // Set actions
    //
//    EPwm5Regs.AQCTLA.bit.ZRO = AQ_SET;
//    EPwm5Regs.AQCTLA.bit.PRD = AQ_CLEAR;
    EPwm5Regs.AQCTLA.bit.CAU = AQ_SET;            // Set PWM1A on event A, up count
    EPwm5Regs.AQCTLA.bit.CAD = AQ_CLEAR;          // Clear PWM1A on event A,
}

// For Testing only
void InitGPIO_Testing()
{
	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1;
	GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;
	EDIS;
}
// Test Code - End
// End of file
