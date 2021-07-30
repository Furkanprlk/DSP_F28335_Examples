//----------------------------------------------------------------------------------
//	FILE:			PWM_1chHiRes_config.c
//
//	Description:	Single (A output) channel PWM configuration function
//					Configures the PWM channel in UP Count mode. 
//
//  Target:  		TMS320F2803x, 
//
// The function call is:
//
// 		PWM_1chHiRes_config(int16 n, int16 period, int16 mode, int16 phase)
//
// Function arguments defined as:
//-------------------------------
// n = 		Target ePWM module, 1,2,...16.  e.g. if n=2, then target is ePWM2
// period = PWM period in Sysclks
// mode =	Master/Slave mode, e.g. mode=1 for master, mode=0 for slave
// phase =	phase offset from upstream master in Sysclks,
//			applicable only if mode=0, i.e. slave
//--------------------------------------------------------------------------------
#include "PeripheralHeaderIncludes.h"
#include "DSP2803x_EPWM_defines.h"

extern volatile struct EPWM_REGS *ePWM[];

void PWM_1chHiResUpDwnCnt_CNF(int16 n, Uint16 period, int16 mode, int16 phase) {
	// Time Base SubModule Registers	
	(*ePWM[n]).TBCTL.bit.PRDLD = TB_IMMEDIATE; // set Immediate load
	(*ePWM[n]).TBPRD = period >> 1; // PWM frequency = 1 / period
	(*ePWM[n]).TBPHS.half.TBPHS = 0;
	(*ePWM[n]).TBCTR = 0;
	(*ePWM[n]).TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	(*ePWM[n]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n]).TBCTL.bit.CLKDIV = TB_DIV1;

	if (mode == 1) {		// config as a Master
		(*ePWM[n]).TBCTL.bit.PHSEN = TB_DISABLE;
		(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // sync "down-stream" 
	}
	if (mode == 0) {		// config as a Slave (Note: Phase+2 value used to compensate for logic delay)
		(*ePWM[n]).TBCTL.bit.PHSEN = TB_ENABLE;
		(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_SYNC_IN;

		if ((0 <= phase) && (phase <= 2)) {
			(*ePWM[n]).TBPHS.half.TBPHS = (2 - phase);
			(*ePWM[n]).TBCTL.bit.PHSDIR = TB_UP; // set to count up after sync
		}
		else if ((2 < phase) && (phase <= period / 2)) {
			(*ePWM[n]).TBPHS.half.TBPHS = (phase - 2);
			(*ePWM[n]).TBCTL.bit.PHSDIR = TB_DOWN; // set to count down after sync
		}
		else if ((period / 2 < phase) && (phase <= period)) {
			(*ePWM[n]).TBPHS.half.TBPHS = (period - phase + 2);
			(*ePWM[n]).TBCTL.bit.PHSDIR = TB_UP; // set to count up after sync
		}
	}
	// Counter Compare Submodule Registers
	(*ePWM[n]).CMPA.half.CMPA = 0; // set duty 0% initially
	(*ePWM[n]).CMPB = 0; // set duty 0% initially
	(*ePWM[n]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	(*ePWM[n]).CMPCTL.bit.LOADAMODE = CC_CTR_PRD;

	// Action Qualifier SubModule Registers
	(*ePWM[n]).AQCTLA.bit.CAD = AQ_SET;
	(*ePWM[n]).AQCTLA.bit.CAU = AQ_CLEAR;

	(*ePWM[n]).AQCTLB.bit.ZRO = AQ_NO_ACTION;
	(*ePWM[n]).AQCTLB.bit.CAU = AQ_NO_ACTION;
	(*ePWM[n]).AQCTLB.bit.PRD = AQ_NO_ACTION;

	//	Enable HiRes option
	EALLOW;
	(*ePWM[n]).HRCNFG.all = 0x0;
	(*ePWM[n]).HRCNFG.bit.EDGMODE = HR_FEP;
	(*ePWM[n]).HRCNFG.bit.CTLMODE = HR_CMP;
	(*ePWM[n]).HRCNFG.bit.HRLOAD = HR_CTR_PRD;
	//(*ePWM[n]).HRCNFG.bit.HRLOAD = HR_CTR_ZERO;

	//  ePWM Type 1 can auto convert the value in CMPAHR,
	//  TBPHSHR or TBPRDHR to a scaled micro-edge dealy
	//  value.

#if defined(DSP2803x_DEVICE_H) || defined(DSP2802x_DEVICE_H)
	(*ePWM[n]).HRCNFG.bit.AUTOCONV = 1;
#endif

	EDIS;
}
