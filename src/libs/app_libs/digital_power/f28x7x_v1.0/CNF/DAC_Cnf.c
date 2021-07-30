//----------------------------------------------------------------------------------
//	FILE:			DAC_Cnf.c
//
//	Description:	DAC configuration to support DAC usage with or without internal slope compensation
//
//	Version: 		1.00
//
//  Target:  		TMS320F2802x & TMS320F2803x
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2011
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description
//----------------------------------------------------------------------------------
//  04/19/11  | Release 1.0  		New release (HN)
//----------------------------------------------------------------------------------
// Description:
// ------------
// DAC configuration to support DAC usage with or without internal slope compensation.
// Config is targeted for on of the on-chip comparator modules
// The function call is:
// 
// DacDrvCnf(int16 n, int16 DACval, int16 DACsrc, int16 RAMPsrc)
//
// Function arguments defined as:
//-------------------------------
// n: Comparator target module number
// DACval: Provides the DAC value when internal slope compensation is not used
// DACsrc: Selects DACval or internal slope compensation as DAC source
// RAMPsrc: Selects source to synchronize internal ramp used for slope compensation
//
#include "DPlib.h"

void DacDrvCnf(int16 n, int16 DACval, int16 DACsrc, int16 RAMPsrc, int16 Slope_initial) {
	EALLOW;

	(*Cmpss[n]).COMPCTL.bit.COMPDACE = 1; // Power up Comparator locally
	(*Cmpss[n]).COMPCTL.bit.COMPHSOURCE = 0; // Connect the inverting input to internal DAC
	(*Cmpss[n]).DACHVALS.bit.DACVAL = (DACval>>3);			// Set DAC output - Input is Q15 - Convert to Q12
	(*Cmpss[n]).COMPDACCTL.bit.DACSOURCE = DACsrc; // 0 - DACVAL; 1 - Internal ramp for slope compensation
	(*Cmpss[n]).COMPCTL.bit.CTRIPHSEL = 0;				// Output = asynch comparator output

	if (DACsrc == 1) { 		// Following lines of code are used when internal slope compensation is used
//		(*Cmpss[n]).COMPCTL.bit.QUALSEL = 5; // Comparator output must be active for 4 consecutive clocks before resetting the RAMP
		(*Cmpss[n]).COMPDACCTL.bit.RAMPSOURCE = RAMPsrc; // 0 - PMW1; 1 - PWM2,...so on
		(*Cmpss[n]).RAMPDECVALS = Slope_initial;
		(*ePWM[RAMPsrc + 1]).HRPCTL.bit.PWMSYNCSEL = 1; // PWM SYNC generated at CTR = ZRO for synchronizing internal ramp
		(*Cmpss[n]).COMPCTL.bit.COMPHINV = 0; // Comparator Output passed

		(*Cmpss[n]).CTRIPHFILCTL.bit.FILINIT = 1;
		(*Cmpss[n]).COMPCTL.bit.CTRIPHSEL = 3;			// Output = OR of asynch out and latched version of it

		(*Cmpss[n]).COMPCTL.bit.ASYNCHEN = 1;			// PWMSYNC path to reset latch is enabled
		(*Cmpss[n]).COMPSTSCLR.bit.HSYNCCLREN = 1;		// Async path to reset latch is enabled
	}

	EDIS;
}
