//----------------------------------------------------------------------------------
//	FILE:			PWM_PSFB_VMC_SR_Cnf.c
//
//	Description:	EPWM Interface driver configuration to support a Phase Shifted Full bridge
//					topology controlled in Voltage Mode Control (VMC).  3x EPWM modules used
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
//  05/04/11  | Release 1.0  		New release (HN)
//----------------------------------------------------------------------------------
//============================================================================
//	PWMDRV_PSFB_VMC_SR_CNF(...)  configuration function for FullBridgePS_DRV macro
//============================================================================
//
//						SyncIn
//						   |
//				___________|___________
//				|  FullBridgePS_CNF   |
//				|~~~~~~~~~~~~~~~~~~~~~|
//			 -->| phase		   EPWMnA |--> (Upper switch of legs with Active --> Passive transitions)
//			 -->| dbLeft  	   EPWMnB |--> (Lower switch of legs with Active --> Passive transitions)
//			 -->| dbRight  EPWM(n+1)A |--> (Upper switch of legs with Passive --> Active transitions)
//			 	| 		   EPWM(n+1)B |--> (Lower switch of legs with Passive --> Active transitions)
//				|   	   EPWM(n+3)A |--> (SR-B switch. Note: SR switch PWM selections should be properly made based on the full bridge PWM selections)
//			 	| 		   EPWM(n+3)B |--> (SR-A switch. Note: SR switch PWM selections should be properly made based on the full bridge PWM selections)
//				|_____________________|
//						   |
//						   |
//						SyncOut
//
// Description:
// ------------
// PWM peripheral Driver Configuration for Phase Shifted Full Bridge modulation in VMC mode.
// Config is targeted to any consecutive pairs of ePWM modules
// The function call is:
// 
// FullBridgePS_CNF(int16 n, int16 period, int16 SR_Enable, int16 Comp1_Prot)
//
// Function arguments defined as:
//-------------------------------
// n: 1st ePWM target module (i.e. Master)
// Period: defines the PWM period or frequency
// SR_Enable: Configure PWMs to drive synchronous rectifiers
// Comp1_Prot: Enable catastrophic protection based on Comparator1
//
#include "PeripheralHeaderIncludes.h"
#include "DSP2802x_EPWM_defines.h" 		// useful defines specific to EPWM 

extern volatile struct EPWM_REGS *ePWM[];

//---------------------------------------------------------------------------
void PWM_PSFB_VMC_SR_CNF(int16 n, Uint16 period, int16 SR_Enable, int16 Comp1_Prot)
{	
// n = the ePWM module number, i.e. selects the target module for init.
// ePWM(n) init.  Note EPWM(n) is the Master
	(*ePWM[n]).TBCTL.bit.PRDLD = TB_IMMEDIATE;			// set Immediate load	
	(*ePWM[n]).TBPRD = period;
	(*ePWM[n]).CMPA.half.CMPA = period/2;				// Fix duty at 50%	
	(*ePWM[n]).TBPHS.half.TBPHS = 0;
	(*ePWM[n]).TBCTR = 0;

	(*ePWM[n]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[n]).TBCTL.bit.PHSEN = TB_DISABLE;
	(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_CTR_ZERO; 		//used to sync EPWM(n+1) "down-stream"
	(*ePWM[n]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n]).TBCTL.bit.CLKDIV = TB_DIV1;

	(*ePWM[n]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n]).AQCTLA.bit.CAU = AQ_CLEAR;
	
	(*ePWM[n]).DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	(*ePWM[n]).DBCTL.bit.POLSEL = DB_ACTV_HIC;			// Active Hi Complimentary
	(*ePWM[n]).DBRED = 20;								// dummy value for now
	(*ePWM[n]).DBFED = 20;								// dummy value for now

// ePWM(n+1) init.  EPWM(n+1) is a slave
	(*ePWM[n+1]).TBCTL.bit.PRDLD = TB_IMMEDIATE;		// set Immediate load
	(*ePWM[n+1]).TBPRD = (period-1);					
	(*ePWM[n+1]).CMPA.half.CMPA = period/2;				// Fix duty at 50%
	(*ePWM[n+1]).TBPHS.half.TBPHS = 0; 					// zero phase initially
	(*ePWM[n+1]).TBCTR = 0;

	(*ePWM[n+1]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[n+1]).TBCTL.bit.PHSEN = TB_ENABLE;
	(*ePWM[n+1]).TBCTL.bit.SYNCOSEL = TB_SYNC_IN; 		// Sync "flow through" mode
	(*ePWM[n+1]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n+1]).TBCTL.bit.CLKDIV = TB_DIV1;

	(*ePWM[n+1]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n+1]).AQCTLA.bit.CAU = AQ_CLEAR;
	
	(*ePWM[n+1]).DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	(*ePWM[n+1]).DBCTL.bit.POLSEL = DB_ACTV_HIC;		// Active Hi Complimentary
	(*ePWM[n+1]).DBRED = 20;							// dummy value for now
	(*ePWM[n+1]).DBFED = 20;							// dummy value for now


if (SR_Enable == 1)	// PWM configuration for synchronous rectification 
 {
	(*ePWM[n+2]).TBCTL.bit.SYNCOSEL = TB_SYNC_IN;	// Pass the Sync signal through to (*ePWM[n+3])

//Configure EPWM(n+3) for synchronous rectifier drive
	//Time Base SubModule Register
	(*ePWM[n+3]).TBCTL.bit.PRDLD = TB_IMMEDIATE;	// Set Immediate load
	(*ePWM[n+3]).TBPRD = period/2 - 1;				// 100 kHz - up-down count mode
	(*ePWM[n+3]).TBPHS.half.TBPHS = 8;				// Accounts for syncing delays down between PWM modules
	(*ePWM[n+3]).TBCTR = 0;

	(*ePWM[n+3]).TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	(*ePWM[n+3]).TBCTL.bit.PHSEN = TB_ENABLE;		// Enabled for SR
	(*ePWM[n+3]).TBCTL.bit.PHSDIR = TB_UP;
	(*ePWM[n+3]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n+3]).TBCTL.bit.CLKDIV = TB_DIV1;
	
	// Counter compare submodule registers
	(*ePWM[n+3]).CMPA.half.CMPA = period/2 - 6;	// Initial value
	(*ePWM[n+3]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	(*ePWM[n+3]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	(*ePWM[n+3]).CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	(*ePWM[n+3]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;
	
	// Action Qualifier SubModule Registers
	// SR Mode 0 Config - below config code is common to all 3 modes
	(*ePWM[n+3]).AQCTLA.bit.PRD = AQ_CLEAR;
	(*ePWM[n+3]).AQCTLB.bit.ZRO = AQ_CLEAR;

	// SR Mode 1 Config
/*	(*ePWM[n+3]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n+3]).AQCTLA.bit.CBU = AQ_CLEAR; 
	(*ePWM[n+3]).AQCTLB.bit.PRD = AQ_SET;
	(*ePWM[n+3]).AQCTLB.bit.CAD = AQ_CLEAR;*/

// SR Mode 2 Config - Default 
	(*ePWM[n+3]).AQCTLA.bit.PRD = AQ_CLEAR;
	(*ePWM[n+3]).AQCTLA.bit.CAD = AQ_SET; 
	(*ePWM[n+3]).AQCTLB.bit.ZRO = AQ_CLEAR;
	(*ePWM[n+3]).AQCTLB.bit.CBU = AQ_SET; 

 }	// End SR PWM configuration

// Over current shutdown mechanism configuration - using comparator 2
//===========================================================================
if (Comp1_Prot == 1)
 {
	EALLOW;	
//===========================================================================
// Define an event (DCAEVT2) based on Comparator 1 Output
	(*ePWM[n]).DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP1OUT; 	// DCAH = Comparator 1 output
	(*ePWM[n+1]).DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP1OUT; 	// DCAH = Comparator 1 output
	(*ePWM[n]).TZDCSEL.bit.DCAEVT1 = TZ_DCAH_HI; 			// DCAEVT1 = DCAH high(will become active
	(*ePWM[n+1]).TZDCSEL.bit.DCAEVT1 = TZ_DCAH_HI; 			// DCAEVT1 = DCAH high(will become active
															// as Comparator output goes high)
	(*ePWM[n]).DCACTL.bit.EVT1SRCSEL = DC_EVT1; 			// DCAEVT1 = DCAEVT1 (not filtered)
	(*ePWM[n]).DCACTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC;	// Take async path
	(*ePWM[n+1]).DCACTL.bit.EVT1SRCSEL = DC_EVT1; 			// DCAEVT1 = DCAEVT1 (not filtered)
	(*ePWM[n+1]).DCACTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC;	// Take async path

// Enable DCAEVT1 and DCBEVT1 as a one-shot source
// Note: DCxEVT1 events can be defined as one-shot.
// DCxEVT2 events can be defined as cycle-by-cycle.
	(*ePWM[n]).TZSEL.bit.DCAEVT1 = 1;
	(*ePWM[n+1]).TZSEL.bit.DCAEVT1 = 1;
// What do we want the DCAEVT1 and DCBEVT1 events to do?
	(*ePWM[n]).TZCTL.bit.TZA = TZ_FORCE_LO; 				// EPWMxA will go low 
	(*ePWM[n]).TZCTL.bit.TZB = TZ_FORCE_LO; 				// EPWMxB will go low 
	(*ePWM[n+1]).TZCTL.bit.TZA = TZ_FORCE_LO; 				// EPWMxA will go low 
	(*ePWM[n+1]).TZCTL.bit.TZB = TZ_FORCE_LO; 				// EPWMxB will go low  

	EDIS;
 }

//===========================================================================
// ADC SOC generation
//===========================================================================
// SOC generation using PWM(n+1)
	(*ePWM[n+1]).ETSEL.bit.SOCAEN  =  1;
	(*ePWM[n+1]).ETSEL.bit.SOCASEL =  ET_CTRU_CMPB; 		// Use CBU event as trigger 
    (*ePWM[n+1]).ETPS.bit.SOCAPRD = 1; 	         			// Generate pulse on 1st event 

	(*ePWM[n+1]).CMPB = ((*ePWM[n+1]).TBPRD)/2;				// Intialize CMPB3 

// SOC generation using PWM(n)
/*	(*ePWM[n]).ETSEL.bit.SOCAEN  =  1;
	(*ePWM[n]).ETSEL.bit.SOCASEL =  ET_CTRU_CMPB; 			// Use CBU event as trigger 
    (*ePWM[n]).ETPS.bit.SOCAPRD = 1; 	         			// Generate pulse on 1st event 
	(*ePWM[n]).CMPB = 275;									// Intialize CMPB3 
*/	
}	// END


