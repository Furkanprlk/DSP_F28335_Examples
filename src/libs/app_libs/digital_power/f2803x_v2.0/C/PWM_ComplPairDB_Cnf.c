//----------------------------------------------------------------------------------
//	FILE:			PWM_ComplPairDB_config.c
//
//	Description:	PWM configuration function for complimentary waveform on A & B
//					with dead band
//
//	Version: 		2.0
//
//  Target:  		TMS320F2802x, 
//					TMS320F2803x, 
//
// The function call is:
//
// 		PWM_ComplPairDB_CNF(int16 n, int16 period)
//
// Function arguments defined as:
//-------------------------------
// n = 		Target ePWM module, 1,2,...16.  e.g. if n=2, then target is ePWM2
// period = PWM period in Sysclks
//--------------------------------------------------------------------------------
#include "PeripheralHeaderIncludes.h"
#include "DSP2803x_EPWM_defines.h"

extern volatile struct EPWM_REGS *ePWM[];

void PWM_ComplPairDB_CNF(int16 n, int16 period)
{
	// Time Base SubModule Registers	
	(*ePWM[n]).TBCTL.bit.PRDLD = TB_IMMEDIATE;	// set Immediate load
	(*ePWM[n]).TBPRD = period;					// PWM frequency = 1 / period
	(*ePWM[n]).TBPHS.half.TBPHS = 0;
	(*ePWM[n]).TBCTR = 0;
	
	(*ePWM[n]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[n]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n]).TBCTL.bit.CLKDIV = TB_DIV1;

	// Counter Compare Submodule Registers
	(*ePWM[n]).CMPA.half.CMPA = 0;				// set duty 0% initially
	(*ePWM[n]).CMPB = 0;						// set duty 0% initially
	(*ePWM[n]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	(*ePWM[n]).CMPCTL.bit.LOADAMODE = CC_CTR_PRD;
	
	// Action Qualifier SubModule Registers
	(*ePWM[n]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n]).AQCTLA.bit.CAU = AQ_CLEAR;

	(*ePWM[n]).AQCTLB.bit.ZRO = AQ_NO_ACTION;
	(*ePWM[n]).AQCTLB.bit.CAU = AQ_NO_ACTION;
	(*ePWM[n]).AQCTLB.bit.PRD = AQ_NO_ACTION;
    
     // Active high complementary PWMs - Setup the deadband
     (*ePWM[n]).DBCTL.bit.IN_MODE=DBA_ALL;
     (*ePWM[n]).DBCTL.bit.OUT_MODE= DB_FULL_ENABLE;
     (*ePWM[n]).DBCTL.bit.POLSEL = DB_ACTV_HIC;
     (*ePWM[n]).DBRED = 0;
   	 (*ePWM[n]).DBFED = 0;
   	 
}

void PWM_ComplPairDB_UpdateDB(int16 n, int16 dbRED, int16 dbFED)
{
	(*ePWM[n]).DBFED=dbRED;
	(*ePWM[n]).DBRED=dbFED;
}

