/**********************************************************************
* File: EPwm.c
* Devices: TMS320F2833x
* Author: Technical Training Organization (TTO), Texas Instruments
* History:
*   07/15/08 - original
**********************************************************************/

#include "Lab.h"						// Main include file


/**********************************************************************
* Function: InitEPwm()
*
* Description: Initializes the Enhanced PWM modules on the F2833x
**********************************************************************/
void InitEPwm(void)
{
//---------------------------------------------------------------------
//--- Must disable the clock to the ePWM modules if you       
//--- want all ePMW modules synchronized.
//---------------------------------------------------------------------
	asm(" EALLOW");						// Enable EALLOW protected register access
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
	asm(" EDIS");						// Disable EALLOW protected register access


//---------------------------------------------------------------------
//--- Configure ePWM2 to trigger the ADC at 48 kHz rate
//---------------------------------------------------------------------
	EPwm2Regs.TBCTL.bit.CTRMODE = 0x3;		// Disable the timer

	EPwm2Regs.TBCTL.all = 0xC033;			// Configure timer control register
// bit 15-14     11:     FREE/SOFT, 11 = ignore emulation suspend
// bit 13        0:      PHSDIR, 0 = count down after sync event
// bit 12-10     000:    CLKDIV, 000 => TBCLK = HSPCLK/1
// bit 9-7       000:    HSPCLKDIV, 000 => HSPCLK = SYSCLKOUT/1
// bit 6         0:      SWFSYNC, 0 = no software sync produced
// bit 5-4       11:     SYNCOSEL, 11 = sync-out disabled
// bit 3         0:      PRDLD, 0 = reload PRD on counter=0
// bit 2         0:      PHSEN, 0 = phase control disabled
// bit 1-0       11:     CTRMODE, 11 = timer stopped (disabled)

	EPwm2Regs.TBCTR = 0x0000;				// Clear timer counter
	EPwm2Regs.TBPRD = ADC_SAMPLE_PERIOD;	// Set timer period
	EPwm2Regs.TBPHS.half.TBPHS = 0x0000;	// Set timer phase

	EPwm2Regs.ETPS.all = 0x0100;			// Configure SOCA
// bit 15-14     00:     EPWMxSOCB, read-only
// bit 13-12     00:     SOCBPRD, don't care
// bit 11-10     00:     EPWMxSOCA, read-only
// bit 9-8       01:     SOCAPRD, 01 = generate SOCA on first event
// bit 7-4       0000:   reserved
// bit 3-2       00:     INTCNT, don't care
// bit 1-0       00:     INTPRD, don't care

	EPwm2Regs.ETSEL.all = 0x0A00;			// Enable SOCA to ADC
// bit 15        0:      SOCBEN, 0 = disable SOCB
// bit 14-12     000:    SOCBSEL, don't care
// bit 11        1:      SOCAEN, 1 = enable SOCA
// bit 10-8      010:    SOCASEL, 010 = SOCA on PRD event
// bit 7-4       0000:   reserved
// bit 3         0:      INTEN, 0 = disable interrupt
// bit 2-0       000:    INTSEL, don't care

	EPwm2Regs.TBCTL.bit.CTRMODE = 0x0;		// Enable the timer in count up mode


//---------------------------------------------------------------------
//--- Enable the clocks to the ePWM module.                   
//--- Note: this should be done after all ePWM modules are configured
//--- to ensure synchronization between the ePWM modules.
//---------------------------------------------------------------------
	asm(" EALLOW");							// Enable EALLOW protected register access
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;	// HSPCLK to ePWM modules enabled
	asm(" EDIS");							// Disable EALLOW protected register access

} // end InitEPwm()


//--- end of file -----------------------------------------------------
