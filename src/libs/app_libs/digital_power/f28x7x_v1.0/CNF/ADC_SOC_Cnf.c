//----------------------------------------------------------------------------------
//	FILE:			ADC_SOC_CNF.c.c
//
//	Description:	ADC configuration to support up to 16 conversions on 
//					Start of Conversion(SOC) based ADCs (type 3) found on F2802x and 
// 					F3803x devices.  Independent selection of Channel, Trigger and 
// 					acquisition window using ChSel[],TrigSel[] and ACQPS[].
//
//  Dependencies:  Assumes the {DeviceName}-usDelay.asm is inlcuded in the project   
//	Version: 		3.0
//
//  Target:  		f28x7x
//
//  The function call is: 
//		
//		void ADC_SOC_CNF(int ChSel[], int Trigsel[], int ACQPS[], int IntChSel, int mode)
//
// Function arguments defined as:
//-------------------------------
// ChSel[]  = 	Channel selection made via a channel # array passed as an argument
// TrigSel[]= 	Source for triggering conversion of a channel, 
//			  	selection made via a trigger # array passed as argument
// ACQPS[]  = 	AcqWidth is the S/H aperture in #ADCCLKS,# array passed as argument
// IntChSel = 	Channel number that would trigger an ADC Interrupt 1 on completion(EOC)
//			    if no channel triggers ADC interrupt pass value > 15
// Mode 	= 	Operating mode: 	0 = Start / Stop mode, needs trigger event
//                             		1 = Continuous mode, no trigger needed
//									2 = CLA Mode, start stop mode with auto clr INT Flag
//	resolution	0 for 12 bit mode
//				1 for 16 bit mode
//	signalmode	0 for single ended mode
//				1 for differential mode
//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================
//-------------------------------------------------------------------------------------

#include "DPlib.h"

void ADC_SOC_CNF(int AdcNo,int ChSel[], int Trigsel[], int ACQPS[], int IntChSel, int mode,  Uint16 resolution, Uint16 signalmode )
{

	extern void DSP28x_usDelay(Uint32 Count);

 
	EALLOW;

	(*ADC[AdcNo]).ADCCTL2.bit.PRESCALE = 6; //set ADCCLK divider to /4
	(*ADC[AdcNo]).ADCCTL2.bit.RESOLUTION = resolution;
	(*ADC[AdcNo]).ADCCTL2.bit.SIGNALMODE = signalmode;

	//Set pulse positions to late
	(*ADC[AdcNo]).ADCCTL1.bit.INTPULSEPOS = 1;

	//power up the ADC
	(*ADC[AdcNo]).ADCCTL1.bit.ADCPWDNZ = 1;

	//delay for 1ms to allow ADC time to power up
	DELAY_US(1000);

	(*ADC[AdcNo]).ADCSOC0CTL.bit.ACQPS = ACQPS[0];
   	(*ADC[AdcNo]).ADCSOC1CTL.bit.ACQPS = ACQPS[1];
   	(*ADC[AdcNo]).ADCSOC2CTL.bit.ACQPS = ACQPS[2];
   	(*ADC[AdcNo]).ADCSOC3CTL.bit.ACQPS = ACQPS[3];
   	(*ADC[AdcNo]).ADCSOC4CTL.bit.ACQPS = ACQPS[4];
   	(*ADC[AdcNo]).ADCSOC5CTL.bit.ACQPS = ACQPS[5];
   	(*ADC[AdcNo]).ADCSOC6CTL.bit.ACQPS = ACQPS[6];
   	(*ADC[AdcNo]).ADCSOC7CTL.bit.ACQPS = ACQPS[7];
   	(*ADC[AdcNo]).ADCSOC8CTL.bit.ACQPS = ACQPS[8];
   	(*ADC[AdcNo]).ADCSOC9CTL.bit.ACQPS = ACQPS[9];
   	(*ADC[AdcNo]).ADCSOC10CTL.bit.ACQPS = ACQPS[10];
   	(*ADC[AdcNo]).ADCSOC11CTL.bit.ACQPS = ACQPS[11];
   	(*ADC[AdcNo]).ADCSOC12CTL.bit.ACQPS = ACQPS[12];
   	(*ADC[AdcNo]).ADCSOC13CTL.bit.ACQPS = ACQPS[13];
   	(*ADC[AdcNo]).ADCSOC14CTL.bit.ACQPS = ACQPS[14];
   	(*ADC[AdcNo]).ADCSOC15CTL.bit.ACQPS = ACQPS[15];

	(*ADC[AdcNo]).ADCINTSEL1N2.bit.INT1SEL = IntChSel;		// IntChSel causes ADCInterrupt 1

	if (mode == 0)		// Start-Stop conv mode
	{
		(*ADC[AdcNo]).ADCINTFLG.bit.ADCINT1 = 0;  // clear interrupt flag for ADCINT1
	    (*ADC[AdcNo]).ADCINTFLGCLR.bit.ADCINT1 = 1; //make sure INT1 flag is cleared
		(*ADC[AdcNo]).ADCINTSEL1N2.bit.INT1CONT = 0;	// clear ADCINT1 flag to begin a new set of conversions
	   	(*ADC[AdcNo]).ADCINTSOCSEL1.all=0x0000;	// No ADCInterrupt will trigger SOCx
	   	(*ADC[AdcNo]).ADCINTSOCSEL2.all=0x0000;
	}
	if (mode == 1)		// Continuous conv mode
	{
		(*ADC[AdcNo]).ADCINTSEL1N2.bit.INT1CONT = 1;	// set ADCInterrupt 1 to auto clr
		(*ADC[AdcNo]).ADCINTSOCSEL1.all=0xFF;// ADCInterrupt 1 will trigger SOCx, TrigSel is ignored
		(*ADC[AdcNo]).ADCINTSOCSEL2.all=0xFF;
	}

	if (mode == 2)		// CLA mode, Start Stop ADC with auto clr ADC Flag
	{
		(*ADC[AdcNo]).ADCINTFLG.bit.ADCINT1 = 0;  // clear interrupt flag for ADCINT1
		(*ADC[AdcNo]).ADCINTSEL1N2.bit.INT1CONT = 1;	// set ADCInterrupt 1 to auto clr
		(*ADC[AdcNo]).ADCINTSOCSEL1.all=0x0000;	// No ADCInterrupt will trigger SOCx
	   	(*ADC[AdcNo]).ADCINTSOCSEL2.all=0x0000;
	}

	if(IntChSel<15)
		(*ADC[AdcNo]).ADCINTSEL1N2.bit.INT1E = 1;		// enable ADC interrupt 1
	else
		(*ADC[AdcNo]).ADCINTSEL1N2.bit.INT1E = 0;		// disable the ADC interrupt 1

// Select the channel to be converted when SOCx is received
	(*ADC[AdcNo]).ADCSOC0CTL.bit.CHSEL= ChSel[0];
	(*ADC[AdcNo]).ADCSOC1CTL.bit.CHSEL= ChSel[1];
	(*ADC[AdcNo]).ADCSOC2CTL.bit.CHSEL= ChSel[2];
	(*ADC[AdcNo]).ADCSOC3CTL.bit.CHSEL= ChSel[3];
	(*ADC[AdcNo]).ADCSOC4CTL.bit.CHSEL= ChSel[4];
	(*ADC[AdcNo]).ADCSOC5CTL.bit.CHSEL= ChSel[5];
	(*ADC[AdcNo]).ADCSOC6CTL.bit.CHSEL= ChSel[6];
	(*ADC[AdcNo]).ADCSOC7CTL.bit.CHSEL= ChSel[7];
	(*ADC[AdcNo]).ADCSOC8CTL.bit.CHSEL= ChSel[8];
	(*ADC[AdcNo]).ADCSOC9CTL.bit.CHSEL= ChSel[9];
	(*ADC[AdcNo]).ADCSOC10CTL.bit.CHSEL= ChSel[10];
	(*ADC[AdcNo]).ADCSOC11CTL.bit.CHSEL= ChSel[11];
	(*ADC[AdcNo]).ADCSOC12CTL.bit.CHSEL= ChSel[12];
	(*ADC[AdcNo]).ADCSOC13CTL.bit.CHSEL= ChSel[13];
	(*ADC[AdcNo]).ADCSOC14CTL.bit.CHSEL= ChSel[14];
	(*ADC[AdcNo]).ADCSOC15CTL.bit.CHSEL= ChSel[15];


	(*ADC[AdcNo]).ADCSOC0CTL.bit.TRIGSEL= Trigsel[0];
	(*ADC[AdcNo]).ADCSOC1CTL.bit.TRIGSEL= Trigsel[1];
	(*ADC[AdcNo]).ADCSOC2CTL.bit.TRIGSEL= Trigsel[2];
	(*ADC[AdcNo]).ADCSOC3CTL.bit.TRIGSEL= Trigsel[3];
	(*ADC[AdcNo]).ADCSOC4CTL.bit.TRIGSEL= Trigsel[4];
	(*ADC[AdcNo]).ADCSOC5CTL.bit.TRIGSEL= Trigsel[5];
	(*ADC[AdcNo]).ADCSOC6CTL.bit.TRIGSEL= Trigsel[6];
	(*ADC[AdcNo]).ADCSOC7CTL.bit.TRIGSEL= Trigsel[7];
	(*ADC[AdcNo]).ADCSOC8CTL.bit.TRIGSEL= Trigsel[8];
	(*ADC[AdcNo]).ADCSOC9CTL.bit.TRIGSEL= Trigsel[9];
	(*ADC[AdcNo]).ADCSOC10CTL.bit.TRIGSEL= Trigsel[10];
	(*ADC[AdcNo]).ADCSOC11CTL.bit.TRIGSEL= Trigsel[11];
	(*ADC[AdcNo]).ADCSOC12CTL.bit.TRIGSEL= Trigsel[12];
	(*ADC[AdcNo]).ADCSOC13CTL.bit.TRIGSEL= Trigsel[13];
	(*ADC[AdcNo]).ADCSOC14CTL.bit.TRIGSEL= Trigsel[14];
	(*ADC[AdcNo]).ADCSOC15CTL.bit.TRIGSEL= Trigsel[15];
	EDIS;

	(*ADC[AdcNo]).ADCSOCFRC1.all = 0xFFFF;		// kick-start ADC

}
