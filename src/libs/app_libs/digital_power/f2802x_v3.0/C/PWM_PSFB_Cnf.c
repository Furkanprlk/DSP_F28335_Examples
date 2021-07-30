//=================================================================================
//	FILE:			PWM_PSFB_Cnf.c
//
//	Description:	Driver Config to support Phase Shifted FullBridge 
//					2 EPWM used
//
//	Version: 		3.0
//  Target:  		TMS320F2802x, TMS320F2803x 
//
// The function call is:
//
// 		PWM_PSFB_CNF(int16 n, int16 period)
//
// Function arguments defined as:
//-------------------------------
// n = 		Target ePWM module, 1,2,...16.  e.g. if n=2, then target is ePWM2
// period = PWM period in Sysclks
//
//==================================================================================
#include "PeripheralHeaderIncludes.h"
#include "DSP2802x_EPWM_defines.h" 		// useful defines specific to EPWM 

extern volatile struct EPWM_REGS *ePWM[];


void PWM_PSFB_CNF(int16 n, int16 Period)
{
	// n = the ePWM module number, i.e. selects the target module for init.
	// ePWM(n) init.  Note EPWM(n) is the Master
	
	//Time Base SubModule Register
	(*ePWM[n]).TBCTL.bit.PRDLD = TB_IMMEDIATE;		// set Immediate load
	(*ePWM[n]).TBPRD = Period-1;
	(*ePWM[n]).TBPHS.half.TBPHS = 0;
	(*ePWM[n]).TBCTR = 0;

	(*ePWM[n]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[n]).TBCTL.bit.PHSEN = TB_DISABLE;
	(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; 	//used to sync EPWM(n+1) "down-stream"
	(*ePWM[n]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n]).TBCTL.bit.CLKDIV = TB_DIV1;

	// Counter compare submodule registers
	(*ePWM[n]).CMPA.half.CMPA = Period/2;			// Fix duty at 50%
		
	// Action Qualifier SubModule Registers
	(*ePWM[n]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n]).AQCTLA.bit.CAU = AQ_CLEAR;
	
	// DeadBand Control Register
	(*ePWM[n]).DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	(*ePWM[n]).DBCTL.bit.POLSEL = DB_ACTV_HIC;		// Active Hi Complimentary
	(*ePWM[n]).DBRED = 50;							// dummy value for now
	(*ePWM[n]).DBFED = 50;							// dummy value for now

	// ePWM(n+1) init.  EPWM(n+1) is a slave

	//Time Base SubModule Register
	(*ePWM[n+1]).TBCTL.bit.PRDLD = TB_IMMEDIATE;	// set Immediate load
	(*ePWM[n+1]).TBPRD = Period;
	(*ePWM[n+1]).TBPHS.half.TBPHS = 0; 				// zero phase initially
	(*ePWM[n+1]).TBCTR = 0;

	(*ePWM[n+1]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[n+1]).TBCTL.bit.PHSEN = TB_ENABLE;
	(*ePWM[n+1]).TBCTL.bit.SYNCOSEL = TB_SYNC_IN; 	// Sync "flow through" mode
	(*ePWM[n+1]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n+1]).TBCTL.bit.CLKDIV = TB_DIV1;

	// Counter compare submodule registers
	(*ePWM[n+1]).CMPA.half.CMPA = Period/2;			// Fix duty at 50%
	
	// Action Qualifier SubModule Registers
	(*ePWM[n+1]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n+1]).AQCTLA.bit.CAU = AQ_CLEAR;
	
	(*ePWM[n+1]).DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	(*ePWM[n+1]).DBCTL.bit.POLSEL = DB_ACTV_HIC;	// Active Hi Complimentary
	(*ePWM[n+1]).DBRED = 50;						// dummy value for now
	(*ePWM[n+1]).DBFED = 50;						// dummy value for now


	// Trip Zone submodule registers 
	EALLOW;

	ePWM[n]->TZSEL.all = 0x0;
	ePWM[n]->TZSEL.bit.OSHT4 = TZ_ENABLE;			// Enable TZ4 -- FB Overcurrent Trip
	ePWM[n]->TZCTL.bit.TZA = TZ_FORCE_LO;			// Low on shutdown
	ePWM[n]->TZCTL.bit.TZB = TZ_FORCE_LO;			// Low on shutdown

	ePWM[n+1]->TZSEL.all = 0x0;
	ePWM[n+1]->TZSEL.bit.OSHT4 = TZ_ENABLE;			// Enable TZ4 -- FB Overcurrent Trip
	ePWM[n+1]->TZCTL.bit.TZA = TZ_FORCE_LO;			// Low on shutdown
	ePWM[n+1]->TZCTL.bit.TZB = TZ_FORCE_LO;			// Low on shutdown

	EDIS;

}

