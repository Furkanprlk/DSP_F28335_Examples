//-------------------------------------------------------------------------------------
//	FILE:			PWM_PFC2PhIL_Cnf.c
//
//	Description:	Driver Config to support a 2 phase Interleaved PFC
//					with Duty balance Adjustment but Non HiRes
//
//  Target:  		TMS320F2803x 
//
// The function call is:
//
// 		PWM_PFC2PhiL_CNF(int16 n, int16 period)
//
// Function arguments defined as:
//-------------------------------
// n = 		Target ePWM module, 1,2,...16.  e.g. if n=2, then target is ePWM2
// period = PWM period in Sysclks
//
//-------------------------------------------------------------------------------------
#include "PeripheralHeaderIncludes.h"
#include "DSP2803x_EPWM_defines.h" 		// useful defines specific to EPWM 
extern volatile struct EPWM_REGS *ePWM[];

void PWM_PFC2PHIL_CNF(int16 n, Uint16 Period) {
	//Time Base SubModule Register
	(*ePWM[n]).TBCTL.bit.PRDLD = TB_IMMEDIATE; // set Immediate load
	(*ePWM[n]).TBPRD = ((Period >> 1));
	(*ePWM[n]).TBPHS.half.TBPHS = 0;
	(*ePWM[n]).TBCTR = 0;
	(*ePWM[n]).TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	(*ePWM[n]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n]).TBCTL.bit.CLKDIV = TB_DIV1;
	(*ePWM[n]).TBCTL.bit.PHSEN = TB_DISABLE;
	(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // sync "down-stream" 

	// Counter compare submodule registers
	(*ePWM[n]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	(*ePWM[n]).CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	(*ePWM[n]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	(*ePWM[n]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	(*ePWM[n]).CMPA.half.CMPA = 0; // set duty 0% initially
	(*ePWM[n]).CMPB = ((Period >> 1)); // set duty 0% initially

	// Action Qualifier SubModule Registers
	(*ePWM[n]).AQCTLA.bit.CAU = AQ_CLEAR;
	(*ePWM[n]).AQCTLA.bit.CAD = AQ_SET;
	(*ePWM[n]).AQCTLB.bit.CBU = AQ_SET;
	(*ePWM[n]).AQCTLB.bit.CBD = AQ_CLEAR;
}
