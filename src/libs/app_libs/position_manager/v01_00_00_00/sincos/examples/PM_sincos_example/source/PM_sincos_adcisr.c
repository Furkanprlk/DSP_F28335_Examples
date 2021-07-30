/* PM_sincos_adcisr.c */

#include "common.h"
#include "sincos.h"

unsigned long AdccIsrCount = 0;


// ADC-C interrupt service routine, triggered by ADC-C EOC, ADC-C triggered by EPWM1 SOCA @ 16 kHz
interrupt void adcc_isr(void)
{
	// re-initialise interrupt
	AdccRegs.ADCINTFLGCLR.bit.ADCINT1 = 1; 			// clear INT1 flag
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;			// acknowledge PIE group 1 to enable further interrupts

	sincos();										// call sincos calculation

	AdccIsrCount++;									// increment ISR counter
}


/* end of file */
