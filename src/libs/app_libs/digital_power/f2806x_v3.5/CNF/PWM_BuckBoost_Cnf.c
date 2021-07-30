//----------------------------------------------------------------------------------
//	FILE:			PWM_BuckBoost_CNF.c
//
//	Description:	PWM configuration function for Buck Boost stage 
//					with dead band
//
//  Target: 		TMS320F2806x, 
//
// The function call is:
//
// 		PWM_BuckBoost_CNF(int16 n, int16 m, int16 period)
//
// Function arguments defined as:
//-------------------------------
// n = 		Target ePWM module, 1,2,...16.  
// m =		(n+1) always
// e.g. if n=1, then m= (n+1) = 2, i.e. Module configures EPwm1 and EPwm2  
// period = PWM period in Sysclks
//--------------------------------------------------------------------------------
#include "PeripheralHeaderIncludes.h"
#include "F2806x_EPwm_defines.h"

extern volatile struct EPWM_REGS *ePWM[];

void PWM_BuckBoost_CNF(int16 n, int16 m, Uint16 period) {
	// Time Base SubModule Registers
	(*ePWM[n]).TBCTL.bit.PRDLD = TB_IMMEDIATE; // set Immediate load
	(*ePWM[n]).TBPRD = period - 1; // PWM frequency = 1 / period
	(*ePWM[n]).TBPHS.half.TBPHS = 0;
	(*ePWM[n]).TBCTR = 0;

	(*ePWM[n]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[n]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n]).TBCTL.bit.CLKDIV = TB_DIV1;

	// Counter Compare Submodule Registers
	(*ePWM[n]).CMPA.half.CMPA = 0; // set duty 0% initially
	(*ePWM[n]).CMPB = 0; // set duty 0% initially
	(*ePWM[n]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	(*ePWM[n]).CMPCTL.bit.LOADAMODE = CC_CTR_PRD;

	// Action Qualifier SubModule Registers
	(*ePWM[n]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n]).AQCTLA.bit.CAU = AQ_CLEAR;

	(*ePWM[n]).AQCTLB.bit.ZRO = AQ_NO_ACTION;
	(*ePWM[n]).AQCTLB.bit.CAU = AQ_NO_ACTION;
	(*ePWM[n]).AQCTLB.bit.PRD = AQ_NO_ACTION;

	// Active high complementary PWMs - Setup the deadband
	(*ePWM[n]).DBCTL.bit.IN_MODE = DBA_ALL;
	(*ePWM[n]).DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	(*ePWM[n]).DBCTL.bit.POLSEL = DB_ACTV_HIC;
	(*ePWM[n]).DBRED = 0;
	(*ePWM[n]).DBFED = 0;

	// Configure EPwm:n to issue a sync pulse on counter equals zero 
	(*ePWM[n]).TBCTL.bit.PHSEN = TB_DISABLE;
	(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // sync "down-stream" 

	// Time Base SubModule Registers	
	(*ePWM[m]).TBCTL.bit.PRDLD = TB_IMMEDIATE; // set Immediate load
	(*ePWM[m]).TBPRD = period - 1; // PWM frequency = 1 / period
	(*ePWM[m]).TBPHS.half.TBPHS = 0;
	(*ePWM[m]).TBCTR = 0;

	(*ePWM[m]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[m]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[m]).TBCTL.bit.CLKDIV = TB_DIV1;
	// Configure EPWM:m: to recieve the sync from EPWm:n:
	(*ePWM[m]).TBCTL.bit.PHSEN = TB_ENABLE;
	(*ePWM[m]).TBCTL.bit.SYNCOSEL = TB_SYNC_IN;

	//For PWM:m: and PWM:n: to be synced, account for the one cycle delay in the sync pulse
	(*ePWM[m]).TBPHS.half.TBPHS = 1;

	// Counter Compare Submodule Registers
	(*ePWM[m]).CMPA.half.CMPA = 0; // set duty 0% initially
	(*ePWM[m]).CMPB = 0; // set duty 0% initially
	(*ePWM[m]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	(*ePWM[m]).CMPCTL.bit.LOADAMODE = CC_CTR_PRD;

	// Action Qualifier SubModule Registers
	(*ePWM[m]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[m]).AQCTLA.bit.CAU = AQ_CLEAR;

	(*ePWM[m]).AQCTLB.bit.ZRO = AQ_NO_ACTION;
	(*ePWM[m]).AQCTLB.bit.CAU = AQ_NO_ACTION;
	(*ePWM[m]).AQCTLB.bit.PRD = AQ_NO_ACTION;

	// Active high complementary PWMs - Setup the deadband
	(*ePWM[m]).DBCTL.bit.IN_MODE = DBA_ALL;
	(*ePWM[m]).DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	(*ePWM[m]).DBCTL.bit.POLSEL = DB_ACTV_HIC;
	(*ePWM[m]).DBRED = 0;
	(*ePWM[m]).DBFED = 0;
}

void PWM_BuckBoost_UpdateDB(int16 n, int16 dbRED, int16 dbFED) {
	(*ePWM[n]).DBFED = dbRED;
	(*ePWM[n]).DBRED = dbFED;
}
