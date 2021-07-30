/* sincos.c */
// sincos library integration source file

#include "common.h"
#include "sincos.h"

SINCOS mySincos;


// initialize F28377D peripherals for SinCos input on IDDK
void sincos_init(void)
{
	// Configure GPIOs as OUTPUTXBARs so that CTRIPHOUTH can be output from chip GPIO14,15,59:
	GPIO_SetupPinMux(14, GPIO_MUX_CPU1, 6);			//OUTPUTXBAR3 - A
	GPIO_SetupPinMux(15, GPIO_MUX_CPU1, 6);			//OUTPUTXBAR4 - B
	GPIO_SetupPinMux(59, GPIO_MUX_CPU1, 5);			//OUTPUTXBAR2 - R

    // PwrEn on R2.2 IDDK:
    EALLOW;
    GpioCtrlRegs.GPBMUX1.bit.GPIO32 = 0;
    GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1;
    GpioDataRegs.GPBSET.bit.GPIO32 = 1;        		// Load the output latch (high)
    DELAY_US(50000);								// Delay to stabilize signal

    // configure GPIOs 54 & 55 for QEP input
    GpioCtrlRegs.GPBGMUX2.bit.GPIO54 = 1;			// QEP2-A
    GpioCtrlRegs.GPBGMUX2.bit.GPIO55 = 1;			// QEP2-B
    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 1;			// QEP2-I
    GpioCtrlRegs.GPBMUX2.bit.GPIO54 = 1;
    GpioCtrlRegs.GPBMUX2.bit.GPIO55 = 1;
    GpioCtrlRegs.GPBMUX2.bit.GPIO57 = 1;

    GpioCtrlRegs.GPBQSEL2.bit.GPIO54 = 2;       	// Glitchfilter for QEP A
    GpioCtrlRegs.GPBQSEL2.bit.GPIO55 = 2;       	// Glitchfilter for QEP B
    GpioCtrlRegs.GPBQSEL2.bit.GPIO56 = 2;      		// Glitchfilter for QEP S
    GpioCtrlRegs.GPBQSEL2.bit.GPIO57 = 2;      		// Glitchfilter for QEP I
    GpioCtrlRegs.GPBCTRL.bit.QUALPRD3 = 3;      	// Qualification period

    // initialize PWM
	EPwm1Regs.ETSEL.bit.SOCAEN	= 1;	        	// enable SOC on A group
	EPwm1Regs.ETSEL.bit.SOCASEL	= 4;	        	// Select SOC on CMPA up-count match
	EPwm1Regs.ETSEL.bit.INTEN = 1;					// enable interrupt generation
	EPwm1Regs.ETSEL.bit.INTSEL = 6;					// interrupt on CMPB in up-count mode
	EPwm1Regs.ETPS.bit.INTPRD = 1;					// generate interrupt on 1st event
	EPwm1Regs.ETPS.bit.SOCAPRD = 1;		        	// generate SOC on 1st event
	EPwm1Regs.TBPRD = SINCOS_INT_PRD;	        	// Set PWM period
	EPwm1Regs.CMPA.bit.CMPA = (SINCOS_INT_PRD / 2); // Set compare A value to 50% duty [0x0C35]
	EPwm1Regs.CMPB.bit.CMPB = (SINCOS_INT_PRD / 2);	// CMPB = CMPA
	EPwm1Regs.TBCTL.bit.CTRMODE = 3;            	// freeze counter
	EPwm1Regs.TBCTL.bit.HSPCLKDIV = 0;				// TBCLK pre-scaler = /1
	EPwm1Regs.TBCTL.bit.FREE_SOFT = 3;				// free run on emulation suspend
	EPwm1Regs.AQCTLA.bit.CAU = 2;					// high on compare A match
	EPwm1Regs.AQCTLA.bit.PRD = 1;					// low on period match

    // configure ADCs
    // Enable ADCC and ADCD
    AdcSetMode(ADC_ADCC, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE); 	// 400/2 MHz = 200 MHz
    AdcSetMode(ADC_ADCD, ADC_RESOLUTION_12BIT, ADC_SIGNALMODE_SINGLE);  // 400/2 MHz = 200 MHz

    // configure ADCC
    AdccRegs.ADCCTL2.bit.PRESCALE = 2; 					// set ADCCCLK divider to /4
    AdccRegs.ADCCTL1.bit.INTPULSEPOS = 0;       		// ADCCINT1 trips at begin of conversion
    AdccRegs.ADCINTSEL1N2.bit.INT1E = 1;        		// Enabled ADCCINT1
    AdccRegs.ADCINTSEL1N2.bit.INT1CONT = 0;     		// Disable ADCCINT1 Continuous mode
    AdccRegs.ADCINTSEL1N2.bit.INT1SEL = 0;      		// setup EOC0 to trigger ADCCINT1 to fire
    AdccRegs.ADCSOC0CTL.bit.CHSEL = 14;     			// set SOC0 channel select to ADCINC0
    AdccRegs.ADCSOC0CTL.bit.TRIGSEL = 5;        		// set SOC0 start trigger on EPWM1 SOCA
    AdccRegs.ADCSOC0CTL.bit.ACQPS = ADC_AQPS - 1;       // set SOC0 S/H Window (SYSCLK cycles plus 1)

    // configure ADCD
    AdcdRegs.ADCCTL2.bit.PRESCALE = 2; 					// set ADCDCLK divider to /4
    AdcdRegs.ADCCTL1.bit.INTPULSEPOS = 0;       		// ADCDINT1 trips at begin of conversion
    AdcdRegs.ADCINTSEL1N2.bit.INT1E = 1;        		// Enabled ADCDINT1
    AdcdRegs.ADCINTSEL1N2.bit.INT1CONT = 0;     		// Disable ADCDINT1 Continuous mode
    AdcdRegs.ADCINTSEL1N2.bit.INT1SEL = 0;      		// setup EOC0 to trigger ADCDINT1 to fire
    AdcdRegs.ADCSOC0CTL.bit.CHSEL = 0;       			// set SOC0 channel select to ADCIND0
    AdcdRegs.ADCSOC0CTL.bit.TRIGSEL = 5;        		// set SOC0 start trigger on EPWM1 SOCB
    AdcdRegs.ADCSOC0CTL.bit.ACQPS = ADC_AQPS - 1;      	// set SOC0 S/H Window (SYSCLK cycles plus 1)

    // Power up the ADCs
    AdccRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    AdcdRegs.ADCCTL1.bit.ADCPWDNZ = 1;
    DELAY_US(1000);

    // configure CMPSS4 for sine input
    Cmpss4Regs.COMPCTL.bit.COMPDACE = 1;				// Enable CMPSS
    Cmpss4Regs.COMPCTL.bit.COMPHSOURCE = 0;				// NEG signal comes from DAC
    Cmpss4Regs.COMPDACCTL.bit.SELREF = 0;				// Use VDDA as the reference for DAC
    Cmpss4Regs.COMPDACCTL.bit.SWLOADSEL = 0;			// DAC update on SYSCLK
    Cmpss4Regs.COMPDACCTL.bit.FREESOFT = 3;				// free run on emulation suspend
    Cmpss4Regs.DACHVALS.bit.DACVAL = 2048;				// Use VDDA as the reference for DAC
    Cmpss4Regs.COMPHYSCTL.bit.COMPHYS = 2; 				// Delay for signal noise
    Cmpss4Regs.COMPCTL.bit.CTRIPHSEL = 0;				// Asynch output feeds CTRIPH and CTRIPOUTH
    Cmpss4Regs.COMPCTL.bit.CTRIPOUTHSEL = 0;

    OutputXbarRegs.OUTPUT3MUX0TO15CFG.bit.MUX6 = 0; 	// Set OUTPUTXBAR3's MUX6 as CMPSS4.CTRIPOUTH
    OutputXbarRegs.OUTPUT3MUXENABLE.bit.MUX6 = 1; 		// Enable MUX6

    // configure CMPSS7 for cosine input
    Cmpss7Regs.COMPCTL.bit.COMPDACE = 1;				// Enable CMPSS
    Cmpss7Regs.COMPCTL.bit.COMPHSOURCE = 0;				// NEG signal comes from DAC
    Cmpss7Regs.COMPDACCTL.bit.SELREF = 0;				// Use VDDA as the reference for DAC
    Cmpss7Regs.COMPDACCTL.bit.SWLOADSEL = 0;			// DAC update on SYSCLK
    Cmpss7Regs.COMPDACCTL.bit.FREESOFT = 3;				// free run on emulation suspend
    Cmpss7Regs.DACHVALS.bit.DACVAL = 2048;				// Set DAC to midpoint for arbitrary reference
    Cmpss7Regs.COMPHYSCTL.bit.COMPHYS = 2; 				// Delay for signal noise
    Cmpss7Regs.COMPCTL.bit.CTRIPHSEL = 0;				// Asynch output feeds CTRIPH and CTRIPOUTH
    Cmpss7Regs.COMPCTL.bit.CTRIPOUTHSEL = 0;

    OutputXbarRegs.OUTPUT4MUX0TO15CFG.bit.MUX12 = 0;   	// Set OUTPUTXBAR4's MUX12 as CMPSS7.CTRIPOUTH
    OutputXbarRegs.OUTPUT4MUXENABLE.bit.MUX12 = 1;    	// Enable MUX12

    // configure CMPSS 8 for index pulse input
    Cmpss8Regs.COMPCTL.bit.COMPDACE = 1;				// Enable CMPSS
    Cmpss8Regs.COMPCTL.bit.COMPHSOURCE = 0;				// NEG signal comes from DAC
    Cmpss8Regs.COMPDACCTL.bit.SELREF = 0;				// Use VDDA as the reference for DAC
    Cmpss8Regs.DACHVALS.bit.DACVAL = 1024;				// Set DAC to midpoint for arbitrary reference [2048]
    Cmpss8Regs.COMPHYSCTL.bit.COMPHYS = 2; 				// Delay for signal noise
    Cmpss8Regs.COMPCTL.bit.CTRIPHSEL = 0;				// Asynch output feeds CTRIPH and CTRIPOUTH
    Cmpss8Regs.COMPCTL.bit.CTRIPOUTHSEL = 0;

    OutputXbarRegs.OUTPUT2MUX0TO15CFG.bit.MUX14 = 0;    // Set OUTPUTXBAR2's MUX14 as CMPSS1.CTRIPOUTH
    OutputXbarRegs.OUTPUT2MUXENABLE.bit.MUX14 = 1;    	// Enable MUX14

    // QEP initialized in PM library
    mySincos.qep = &EQep2Regs;							// assign QEP instance to sincos library

    EDIS;

}


// read inputs & compute shaft angle - called from sincos ISR
void sincos(void)
{
	// read ADC channels
#ifndef SWAP_CHANNELS
	mySincos.sindata = AdccResultRegs.ADCRESULT0;
	mySincos.cosdata = AdcdResultRegs.ADCRESULT0;
#else
	mySincos.cosdata = AdccResultRegs.ADCRESULT0;
	mySincos.sindata = AdcdResultRegs.ADCRESULT0;
#endif

	// cal ready: update CMPSS offsets
	if (mySincos.qcflg == 1)
	{
		Cmpss4Regs.DACHVALS.bit.DACVAL = mySincos.ch0offs;
		Cmpss7Regs.DACHVALS.bit.DACVAL = mySincos.ch1offs;
		mySincos.qcflg = 0;
	}

	PM_sincos_calcAngle(&mySincos);				// SinCos transducer function

}

/* end of file */
