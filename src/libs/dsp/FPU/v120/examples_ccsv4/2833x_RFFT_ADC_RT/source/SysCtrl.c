/**********************************************************************
* File: SysCtrl.c 
* Devices: TMS320F2833x
* Author: Technical Training Organization (TTO), Texas Instruments
* History:
*   07/15/08 - original
**********************************************************************/

#include "Lab.h"						// Main include file


/**********************************************************************
* Function: InitSysCtrl()
*
* Description: Initializes the F2833x CPU
**********************************************************************/
void InitSysCtrl(void)
{
volatile Uint16 i;						// General purpose Uint16
volatile int16 dummy;					// General purpose volatile int16

	asm(" EALLOW");						// Enable EALLOW protected register access

//--- Memory Protection Configuration
	DevEmuRegs.PROTSTART = 0x0100;		// Write default value to protection start register
	DevEmuRegs.PROTRANGE = 0x00FF;		// Write default value to protection range register

//--- Configure the PLL

// Note: The DSP/BIOS configuration tool can also be used to initialize the PLL
// instead of doing the initialization here.

	// Make sure the PLL is not running in limp mode
	if (SysCtrlRegs.PLLSTS.bit.MCLKSTS != 1)
	{													// PLL is not running in limp mode
		SysCtrlRegs.PLLSTS.bit.MCLKOFF = 1;				// Turn off missing clock detect before changing PLLCR
		SysCtrlRegs.PLLSTS.bit.DIVSEL = 0;				// DIVSEL must be 0 or 1  (/4 CLKIN mode) before changing PLLCR
		SysCtrlRegs.PLLCR.bit.DIV = 0x000A;				// PLLx10/4 (because DIVSEL is /4)
   
		// Wait for PLL to lock.
		// During this time the CPU will run at OSCCLK/2 until the PLL is stable.
		// Once the PLL is stable the CPU will automatically switch to the new PLL value.
		// Code is not required to sit and wait for the PLL to lock.  However, 
		// if the code does anything that is timing critical (e.g. something that
		// relies on the CPU clock frequency to be at speed), then it is best to wait
		// until PLL lock is complete.  The watchdog should be disabled before this loop
		// (e.g., as was done above), or fed within the loop.
		while(SysCtrlRegs.PLLSTS.bit.PLLLOCKS != 1)		// Wait for PLLLOCKS bit to set
		{
			SysCtrlRegs.WDKEY = 0x0055;					// Service the watchdog while waiting
			SysCtrlRegs.WDKEY = 0x00AA;					//   in case the user enabled it.
		}

		// After the PLL has locked, we are running in PLLx10/4 mode (since DIVSEL is /4).
		// We can now enable the missing clock detect circuitry, and also change DIVSEL
		// to /2.  In this example, we will wait a bit of time to let inrush currents settle,
		// and then change DIVSEL from /4 to /2.  This is only an example.  The amount of
		// time you need to wait depends on the power supply feeding the DSP (i.e., how much
		// voltage droop occurs due to the inrush currents, and how long it takes the
		// voltage regulators to recover).
		SysCtrlRegs.PLLSTS.bit.MCLKOFF = 0;				// Enable missing clock detect circuitry
		DSP28x_usDelay(20/2);									// Wait 20 us (just an example).  Remember we're running
														// at half-speed here, so divide function argument by 2.
		SysCtrlRegs.PLLSTS.bit.DIVSEL = 0x2;			// Change to /2 mode
	}
	else
	{													// PLL is running in limp mode
	// User should replace the below with a call to an appropriate function,
	// for example shutdown the system (since something is very wrong!).
		asm(" ESTOP0");
	}

//--- Configure the clocks
	SysCtrlRegs.HISPCP.all = 0x0000;		// Hi-speed periph clock prescaler, HSPCLK=SYSCLKOUT/1
	SysCtrlRegs.LOSPCP.all = 0x0002;		// Lo-speed periph clock prescaler, LOSPCLK=SYSCLKOUT/4

	SysCtrlRegs.PCLKCR3.bit.GPIOINENCLK = 1;	// GPIO input module is clocked
	SysCtrlRegs.PCLKCR3.bit.XINTFENCLK = 1;		// XINTF module is clocked
	SysCtrlRegs.PCLKCR3.bit.DMAENCLK = 1;		// SYSCLKOUT to DMA enabled
	SysCtrlRegs.PCLKCR3.bit.CPUTIMER2ENCLK = 1;	// SYSCLKOUT to CPU Timer2 enabled
	SysCtrlRegs.PCLKCR3.bit.CPUTIMER1ENCLK = 1;	// SYSCLKOUT to CPU Timer1 enabled
	SysCtrlRegs.PCLKCR3.bit.CPUTIMER0ENCLK = 1;	// SYSCLKOUT to CPU Timer0 enabled

	SysCtrlRegs.PCLKCR1.bit.EQEP2ENCLK = 1;		// SYSCLKOUT to eQEP2 enabled
	SysCtrlRegs.PCLKCR1.bit.EQEP1ENCLK = 1;		// SYSCLKOUT to eQEP1 enabled
	SysCtrlRegs.PCLKCR1.bit.ECAP6ENCLK = 1;		// SYSCLKOUT to eCAP6 enabled
	SysCtrlRegs.PCLKCR1.bit.ECAP5ENCLK = 1;		// SYSCLKOUT to eCAP5 enabled
	SysCtrlRegs.PCLKCR1.bit.ECAP4ENCLK = 1;		// SYSCLKOUT to eCAP4 enabled
	SysCtrlRegs.PCLKCR1.bit.ECAP3ENCLK = 1;		// SYSCLKOUT to eCAP3 enabled
	SysCtrlRegs.PCLKCR1.bit.ECAP2ENCLK = 1;		// SYSCLKOUT to eCAP2 enabled
	SysCtrlRegs.PCLKCR1.bit.ECAP1ENCLK = 1;		// SYSCLKOUT to eCAP1 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM6ENCLK = 1;		// SYSCLKOUT to ePWM6 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM5ENCLK = 1;		// SYSCLKOUT to ePWM5 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM4ENCLK = 1;		// SYSCLKOUT to ePWM4 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM3ENCLK = 1;		// SYSCLKOUT to ePWM3 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM2ENCLK = 1;		// SYSCLKOUT to ePWM2 enabled
	SysCtrlRegs.PCLKCR1.bit.EPWM1ENCLK = 1;		// SYSCLKOUT to ePWM1 enabled

	SysCtrlRegs.PCLKCR0.bit.ECANBENCLK = 1;		// SYSCLKOUT/2 to eCAN-B enabled
	SysCtrlRegs.PCLKCR0.bit.ECANAENCLK = 1;		// SYSCLKOUT/2 to eCAN-A enabled
	SysCtrlRegs.PCLKCR0.bit.MCBSPAENCLK = 1;	// LSPCLK to McBSP-A enabled
	SysCtrlRegs.PCLKCR0.bit.MCBSPBENCLK = 1;	// LSPCLK to McBSP-B enabled
	SysCtrlRegs.PCLKCR0.bit.SCIBENCLK = 1;		// LSPCLK to SCI-B enabled
	SysCtrlRegs.PCLKCR0.bit.SCIAENCLK = 1;		// LSPCLK to SCI-A enabled
	SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1;		// LSPCLK to SPI-A enabled
	SysCtrlRegs.PCLKCR0.bit.SCICENCLK = 1;		// LSPCLK to SCI-C enabled
	SysCtrlRegs.PCLKCR0.bit.I2CAENCLK = 1;		// LSPCLK to I2C-A enabled
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;		// HSPCLK to ADC enabled

// The PCLKCR0.TBCLKSYNC bit is handled in the InitEPwm() function since
// it affects synchronization of the ePWM counters.

//--- Configure the low-power modes
	SysCtrlRegs.LPMCR0.all = 0x00FC;		// LPMCR0 set to default value

//--- Finish up
	asm(" EDIS");							// Disable EALLOW protected register access

} // end InitSysCtrl()


//--- end of file -----------------------------------------------------
