//-------------------------------------------------------------------------------------
//	FILE:			PWM_DualUpDwnCnt_Cnf.c
//
//	Description:	Driver Config to support independent duty contol on chA and chB of the PWM
//
//  Target:  		TMS320F2802x 
//
// The function call is:
//
// 		PWM_DualUPDwnCnt_CNF(int16 n, int16 period)
//
// Function arguments defined as:
//-------------------------------
// n = 		Target ePWM module, 1,2,...16.  e.g. if n=2, then target is ePWM2
// Period = PWM period in Sysclks
// Mode =	Master/Slave mode, e.g. mode=1 for master, mode=0 for slave
// Phase =	phase offset from upstream master in Sysclks,
//			applicable only if mode=0, i.e. slave
//
//-------------------------------------------------------------------------------------
#include "PeripheralHeaderIncludes.h"
#include "DSP2802x_EPWM_defines.h" 		// useful defines specific to EPWM 

extern volatile struct EPWM_REGS *ePWM[];


void PWM_DualUpDwnCnt_CNF(int16 n, Uint16 Period, int16 Mode, int16 Phase)
{
	//Time Base SubModule Register
	(*ePWM[n]).TBCTL.bit.PRDLD = TB_IMMEDIATE;	// set Immediate load
	(*ePWM[n]).TBPRD=((Period>>1));
	(*ePWM[n]).TBPHS.half.TBPHS =0;
	(*ePWM[n]).TBCTR = 0;
	(*ePWM[n]).TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	(*ePWM[n]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n]).TBCTL.bit.CLKDIV = TB_DIV1;
	
	if(Mode == 1) // config as a Master
	{
		(*ePWM[n]).TBCTL.bit.PHSEN = TB_DISABLE;
		(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; // sync "down-stream" 
	}
	if(Mode == 0) // config as a Slave (Note: Phase+2 value used to compensate for logic delay)
	{
		(*ePWM[n]).TBCTL.bit.PHSEN = TB_ENABLE;
		(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_SYNC_IN;

		if( (0 <= Phase)&&(Phase <= 2))	
		{
			(*ePWM[n]).TBPHS.half.TBPHS = (2-Phase);
			(*ePWM[n]).TBCTL.bit.PHSDIR = TB_UP;	// set to count up after sync
		}
		else if ((2 < Phase)&&(Phase <= Period/2))
		{
			(*ePWM[n]).TBPHS.half.TBPHS = (Phase-2);
			(*ePWM[n]).TBCTL.bit.PHSDIR = TB_DOWN;	// set to count down after sync
		}
		else if ((Period/2 < Phase)&&(Phase <= Period))
		{
			(*ePWM[n]).TBPHS.half.TBPHS = (Period-Phase+2);
			(*ePWM[n]).TBCTL.bit.PHSDIR = TB_UP;	// set to count up after sync
		}
	}
	
	(*ePWM[n]).CMPA.half.CMPA = 0;				// set duty 0% initially
	(*ePWM[n]).CMPB = (*ePWM[n]).TBPRD;		// set duty 0% initially
	
	// Counter compare submodule registers
	(*ePWM[n]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	(*ePWM[n]).CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	(*ePWM[n]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	(*ePWM[n]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;

	// Action Qualifier SubModule Registers
	(*ePWM[n]).AQCTLA.bit.CAU = AQ_CLEAR;
	(*ePWM[n]).AQCTLA.bit.CAD = AQ_SET;
	(*ePWM[n]).AQCTLB.bit.CBU = AQ_SET;
	(*ePWM[n]).AQCTLB.bit.CBD = AQ_CLEAR;

}

