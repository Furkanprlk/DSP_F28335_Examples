//----------------------------------------------------------------------------------
//	FILE:			ADC_Cnf.c
//
//	Description:	ADC module configuration which supports up to 16 conversions on 
//					Start of Conversion(SOC) on each ADC (type 4) found on F28M35x devices.  
//					Independent selection of Channel, Trigger and Acquisition Window 
//					using ChSel[], TrigSel[] and ACQPS[], respectively.
//
//  Dependencies:  Assumes the {DeviceName}-usDelay.asm is inlcuded in the project   
//	Version: 		1.0
//
//  Target:  		F28M35x 
//
//  The function call is: 
//		
//		void ADC_SOC_CNF(int AdcNum, int ChSel[], int TrigSel[], int ACQPS[])
//
// Function arguments defined as:
//-------------------------------
// AdcNum 	= 	ADC module number that is being configured.  Valid values are 1 and 2.
// ChSel[]  = 	Channel selection made via a channel # array passed as an argument
// TrigSel[]= 	Source for triggering conversion of a channel, 
//			  	selection made via a trigger # array passed as argument
// ACQPS[]  = 	AcqWidth is the S/H aperture in #ADCCLKS,# array passed as argument
//================================================================================
#include "F28M35x_Device.h"     // F28M35x Headerfile Include File
#include "DPlib.h"

//extern volatile struct ADC_REGS *ADC[];  uncomment this line to remove need to include DPlib.h

void ADC_CNF(int AdcNum, int ChSel[], int TrigSel[], int ACQPS[])
{

    extern void DSP28x_usDelay(Uint32 Count);

    // To powerup the ADC1 the ADC1ENCLK bit should be set first to enable
    // clocks, followed by powering up the bandgap, reference circuitry, and
    // ADC1 core.
    // Before the first conversion is performed a 5ms delay must be observed
    // after power up to give all analog circuits time to power up and settle

    // Please note that for the delay function below to operate correctly the
    // CPU_RATE define statement in the F28M35xA_Examples.h file must
    // contain the correct CPU clock period in nanoseconds.

    EALLOW;
    (*ADC[AdcNum]).ADCCTL1.bit.ADCBGPWD  = 1;      // Power ADC1 BG
    (*ADC[AdcNum]).ADCCTL1.bit.ADCREFPWD = 1;      // Power reference
    (*ADC[AdcNum]).ADCCTL1.bit.ADCPWDN   = 1;      // Power ADC1
    (*ADC[AdcNum]).ADCCTL1.bit.ADCENABLE = 1;      // Enable ADC1
    (*ADC[AdcNum]).ADCCTL1.bit.ADCREFSEL = 0;      // Select interal BG
    EDIS;

//    DELAY_US(ADC_usDELAY);         // Delay before converting ADC1 channels
	DSP28x_usDelay(1000);         // Delay before converting ADC channels
  	
  	EALLOW;
	// Set the acquisition window for each channel
	(*ADC[AdcNum]).ADCSOC0CTL.bit.ACQPS = ACQPS[0];
   	(*ADC[AdcNum]).ADCSOC1CTL.bit.ACQPS = ACQPS[1];
   	(*ADC[AdcNum]).ADCSOC2CTL.bit.ACQPS = ACQPS[2];
   	(*ADC[AdcNum]).ADCSOC3CTL.bit.ACQPS = ACQPS[3];
   	(*ADC[AdcNum]).ADCSOC4CTL.bit.ACQPS = ACQPS[4];
   	(*ADC[AdcNum]).ADCSOC5CTL.bit.ACQPS = ACQPS[5];
   	(*ADC[AdcNum]).ADCSOC6CTL.bit.ACQPS = ACQPS[6];
   	(*ADC[AdcNum]).ADCSOC7CTL.bit.ACQPS = ACQPS[7];
   	(*ADC[AdcNum]).ADCSOC8CTL.bit.ACQPS = ACQPS[8];
   	(*ADC[AdcNum]).ADCSOC9CTL.bit.ACQPS = ACQPS[9];
   	(*ADC[AdcNum]).ADCSOC10CTL.bit.ACQPS = ACQPS[10];
   	(*ADC[AdcNum]).ADCSOC11CTL.bit.ACQPS = ACQPS[11];
   	(*ADC[AdcNum]).ADCSOC12CTL.bit.ACQPS = ACQPS[12];
   	(*ADC[AdcNum]).ADCSOC13CTL.bit.ACQPS = ACQPS[13];
   	(*ADC[AdcNum]).ADCSOC14CTL.bit.ACQPS = ACQPS[14];
   	(*ADC[AdcNum]).ADCSOC15CTL.bit.ACQPS = ACQPS[15];
   	
   	// Set the channel to be converted when SOCx is received
	(*ADC[AdcNum]).ADCSOC0CTL.bit.CHSEL= ChSel[0];
	(*ADC[AdcNum]).ADCSOC1CTL.bit.CHSEL= ChSel[1];
	(*ADC[AdcNum]).ADCSOC2CTL.bit.CHSEL= ChSel[2];
	(*ADC[AdcNum]).ADCSOC3CTL.bit.CHSEL= ChSel[3];
	(*ADC[AdcNum]).ADCSOC4CTL.bit.CHSEL= ChSel[4];
	(*ADC[AdcNum]).ADCSOC5CTL.bit.CHSEL= ChSel[5];
	(*ADC[AdcNum]).ADCSOC6CTL.bit.CHSEL= ChSel[6];
	(*ADC[AdcNum]).ADCSOC7CTL.bit.CHSEL= ChSel[7];
	(*ADC[AdcNum]).ADCSOC8CTL.bit.CHSEL= ChSel[8];
	(*ADC[AdcNum]).ADCSOC9CTL.bit.CHSEL= ChSel[9];
	(*ADC[AdcNum]).ADCSOC10CTL.bit.CHSEL= ChSel[10];
	(*ADC[AdcNum]).ADCSOC11CTL.bit.CHSEL= ChSel[11];
	(*ADC[AdcNum]).ADCSOC12CTL.bit.CHSEL= ChSel[12];
	(*ADC[AdcNum]).ADCSOC13CTL.bit.CHSEL= ChSel[13];
	(*ADC[AdcNum]).ADCSOC14CTL.bit.CHSEL= ChSel[14];
	(*ADC[AdcNum]).ADCSOC15CTL.bit.CHSEL= ChSel[15];

	// Set the trigger for each channel
	(*ADC[AdcNum]).ADCSOC0CTL.bit.TRIGSEL= TrigSel[0];
	(*ADC[AdcNum]).ADCSOC1CTL.bit.TRIGSEL= TrigSel[1];
	(*ADC[AdcNum]).ADCSOC2CTL.bit.TRIGSEL= TrigSel[2];
	(*ADC[AdcNum]).ADCSOC3CTL.bit.TRIGSEL= TrigSel[3];
	(*ADC[AdcNum]).ADCSOC4CTL.bit.TRIGSEL= TrigSel[4];
	(*ADC[AdcNum]).ADCSOC5CTL.bit.TRIGSEL= TrigSel[5];
	(*ADC[AdcNum]).ADCSOC6CTL.bit.TRIGSEL= TrigSel[6];
	(*ADC[AdcNum]).ADCSOC7CTL.bit.TRIGSEL= TrigSel[7];
	(*ADC[AdcNum]).ADCSOC8CTL.bit.TRIGSEL= TrigSel[8];
	(*ADC[AdcNum]).ADCSOC9CTL.bit.TRIGSEL= TrigSel[9];
	(*ADC[AdcNum]).ADCSOC10CTL.bit.TRIGSEL= TrigSel[10];
	(*ADC[AdcNum]).ADCSOC11CTL.bit.TRIGSEL= TrigSel[11];
	(*ADC[AdcNum]).ADCSOC12CTL.bit.TRIGSEL= TrigSel[12];
	(*ADC[AdcNum]).ADCSOC13CTL.bit.TRIGSEL= TrigSel[13];
	(*ADC[AdcNum]).ADCSOC14CTL.bit.TRIGSEL= TrigSel[14];
	(*ADC[AdcNum]).ADCSOC15CTL.bit.TRIGSEL= TrigSel[15];

	EDIS;

	(*ADC[AdcNum]).ADCSOCFRC1.all = 0xFFFF;		// kick-start ADC
}



