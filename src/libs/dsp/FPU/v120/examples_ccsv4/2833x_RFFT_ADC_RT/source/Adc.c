/**********************************************************************
* File: Adc.c
* Devices: TMS320F2833x
* Author: Technical Training Organization (TTO), Texas Instruments
* History:
*   07/15/08 - original
**********************************************************************/

#include "Lab.h"						// Main include file


/**********************************************************************
* Function: InitAdc()
*
* Description: Initializes the ADC on the F2833x
**********************************************************************/
void InitAdc(void)
{
//--- Reset the ADC module
	AdcRegs.ADCTRL1.bit.RESET = 1;		// Reset the ADC

// Must wait 2 ADCCLK periods for the reset to take effect.  The ADC is 
// already reset after a DSP reset, but this example is just showing good
// coding practice to reset the peripheral before configuring it (as you
// never know why the DSP has started the code over again from the
// beginning).  Assuming a 12.5 MHz ADCCLK was previously configured, and
// a 150 MHz SYSCLKOUT, the wait period of 2 ADCCLK periods equates to 24
// CPU clocks.  This is the example being used below.
 
	asm(" RPT #22 || NOP");				// Must wait for ADC reset to take effect

//--- Call the ADC_cal() function located in the Boot ROM.
//    ADC_cal_func_ptr is a macro defined in the file example_nonBios.h or
//    example_BIOS.h (as may be the case for the example being used).  This
//    macro simply defines ADC_cal_func_ptr to be a function pointer to
//    the correct address in the boot ROM.
	(*ADC_cal_func_ptr)();

//--- Select the ADC reference
	AdcRegs.ADCREFSEL.bit.REF_SEL = 0;	// 0=internal, 1=external
	
//--- Power-up the ADC
	AdcRegs.ADCTRL3.all = 0x00EC;		// Power-up reference and main ADC
// bit 15-8      0's:    reserved
// bit 7-6       11:     ADCBGRFDN, reference power, 00=off, 11=on
// bit 5         1:      ADCPWDN, main ADC power, 0=off, 1=on
// bit 4-1       0110:   ADCCLKPS, clock prescaler, FCLK=HSPCLK/(2*ADCCLKPS)
// bit 0         0:      SMODE_SEL, 0=sequential sampling, 1=simultaneous sampling

	DSP28x_usDelay(5000);						// Wait 5ms before using the ADC

//--- Configure the other ADC register
	AdcRegs.ADCMAXCONV.all = 0x0000;
// bit 15-7      0's:    reserved
// bit 6-4       000:    MAX_CONV2 value
// bit 3-0       0000:   MAX_CONV1 value (0 means 1 conversion)

// For CPU servicing of ADC, we are only doing 1 conversion in the
// sequence.  So, we only need to configure the first channel
// selection in the sequence.  All other channel selection fields
// are don't cares in this example.
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0;	// Convert Channel 0

	AdcRegs.ADCTRL1.all = 0x0710;
// bit 15        0:      reserved
// bit 14        0:      RESET, 0=no action, 1=reset ADC
// bit 13-12     00:     SUSMOD, 00=ignore emulation suspend
// bit 11-8      0111:   ACQ_PS (Acquisition), 0111 = 8 x ADCCLK
// bit 7         0:      CPS (Core clock), 0: ADCCLK=FCLK/1, 1: ADCCLK=FCLK/2
// bit 6         0:      CONT_RUN, 0=start/stop mode, 1=continuous run
// bit 5         0:      SEQ_OVRD, 0=disabled, 1=enabled
// bit 4         1:      SEQ_CASC, 0=dual sequencer, 1=cascaded sequencer
// bit 3-0       0000:   reserved

	AdcRegs.ADCTRL2.all = 0x0900;
// bit 15        0:      ePWM_SOCB_SEQ, 0=no action
// bit 14        0:      RST_SEQ1, 0=no action
// bit 13        0:      SOC_SEQ1, 0=clear any pending SOCs
// bit 12        0:      reserved
// bit 11        1:      INT_ENA_SEQ1, 1=enable interrupt
// bit 10        0:      INT_MOD_SEQ1, 0=int on every SEQ1 conv
// bit 9         0:      reserved
// bit 8         1:      ePWM_SOCA_SEQ1, 1=SEQ1 start from ePWM_SOCA trigger
// bit 7         0:      EXT_SOC_SEQ1, 1=SEQ1 start from ADCSOC pin
// bit 6         0:      RST_SEQ2, 0=no action
// bit 5         0:      SOC_SEQ2, no effect in cascaded mode
// bit 4         0:      reserved
// bit 3         0:      INT_ENA_SEQ2, 0=int disabled
// bit 2         0:      INT_MOD_SEQ2, 0=int on every other SEQ2 conv
// bit 1         0:      reserved
// bit 0         0:      ePWM_SOCB_SEQ2, 0=no action


//--- Enable the ADC interrupt
	PieCtrlRegs.PIEIER1.bit.INTx6 = 1;	// Enable ADCINT in PIE group 1
	IER |= 0x0001;						// Enable INT1 in IER to enable PIE group

} // end InitAdc()


//--- end of file -----------------------------------------------------
