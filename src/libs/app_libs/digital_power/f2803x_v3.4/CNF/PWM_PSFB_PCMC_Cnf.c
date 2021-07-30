//----------------------------------------------------------------------------------
//	FILE:			PWM_PSFB_PCMC_Cnf.c
//
//	Description:	EPWM Interface driver configuration to support a Phase Shifted Full bridge
//					topology controlled in Peak Current Mode Control (PCMC).  2 x EPWM modules used
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
//============================================================================
//	FullBridgePS_CNF(...)  configuration function for FullBridgePS_DRV macro
//============================================================================
//
//						SyncIn
//						   |
//				___________|___________
//				|  FullBridgePS_CNF   |
//				|~~~~~~~~~~~~~~~~~~~~~|
//			 	| 			   EPWMnA |--> (Upper switch of legs with Passive --> Active transitions)
//			 -->| dbAtoP  	   EPWMnB |--> (Lower switch of legs with Passive --> Active transitions)
//			 -->| dbPtoA   EPWM(n+1)A |--> (Upper switch of legs with Active --> Passive transitions)
//			 	| 		   EPWM(n+1)B |--> (Lower switch of legs with Active --> Passive transitions)
//				|   	   EPWM(n+3)A |--> (SR-A switch. Note: SR switch PWM selections should be properly made based on the full bridge PWM selections)
//			 	| 		   EPWM(n+3)B |--> (SR-B switch. Note: SR switch PWM selections should be properly made based on the full bridge PWM selections)
//				|_____________________|
//						   |
//						   |
//						SyncOut
//
// Description:
// ------------
// PWM peripheral Driver Configuration for Phase Shifted Full Bridge modulation in PCMC mode.
// Config is targeted to any consecutive pairs of ePWM modules
// The function call is:
// 
// FullBridgePS_CNF(int16 n, int16 period, int16 SR_Enable, int16 Comp2_Prot)
//
// Function arguments defined as:
//-------------------------------
// n: 1st ePWM target module (i.e. Master)
// Period: defines the PWM period or frequency
// SR_Enable: Configure PWMs to drive synchronous rectifiers
// Comp2_Prot: Enable catastrophic protection based on Comparator2
//
#include "PeripheralHeaderIncludes.h"
#include "DSP2803x_EPWM_defines.h" 		// useful defines specific to EPWM 
extern volatile struct EPWM_REGS *ePWM[];

void PWMDRV_PSFB_PCMC_CNF(int16 n, Uint16 period, int16 SR_Enable, int16 Comp2_Prot) {
	// n = the ePWM module number, i.e. selects the target module for init.
	// ePWM(n) init.  Note EPWM(n) is the Master

	//Time Base SubModule Register
	(*ePWM[n]).TBCTL.bit.PRDLD = TB_IMMEDIATE; // Set Immediate load
	(*ePWM[n]).TBPRD = period;
	(*ePWM[n]).TBPHS.half.TBPHS = 0;
	(*ePWM[n]).TBCTR = 0;

	(*ePWM[n]).TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	(*ePWM[n]).TBCTL.bit.PHSEN = TB_DISABLE;
	(*ePWM[n]).TBCTL.bit.SYNCOSEL = TB_CTR_CMPB; // Used to sync EPWM(n+1) "down-stream"
	(*ePWM[n]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n]).TBCTL.bit.CLKDIV = TB_DIV1;

	// Counter compare submodule registers
	(*ePWM[n]).CMPCTL.bit.SHDWAMODE = CC_IMMEDIATE;
	(*ePWM[n]).CMPCTL.bit.SHDWBMODE = CC_IMMEDIATE;
	(*ePWM[n]).CMPA.half.CMPA = period - 68;
	(*ePWM[n]).CMPB = period;

	// Action Qualifier SubModule Registers
	(*ePWM[n]).AQCTLA.bit.ZRO = AQ_SET;
	(*ePWM[n]).AQCTLA.bit.PRD = AQ_CLEAR;

	// DeadBand Control Register
	(*ePWM[n]).DBCTL.bit.OUT_MODE = DB_FULL_ENABLE;
	(*ePWM[n]).DBCTL.bit.POLSEL = DB_ACTV_HIC; // Active Hi Complimentary
	(*ePWM[n]).DBRED = 20; // Initial value
	(*ePWM[n]).DBFED = 20; // Initial value

	// ePWM(n+1) init.  EPWM(n+1) is a slave

	//Time Base SubModule Register
	(*ePWM[n + 1]).TBCTL.bit.PRDLD = TB_SHADOW;
	(*ePWM[n + 1]).TBPRD = period - 1;
	(*ePWM[n + 1]).TBPHS.half.TBPHS = 0;
	(*ePWM[n + 1]).TBCTR = 0;

	(*ePWM[n + 1]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[n + 1]).TBCTL.bit.PHSEN = TB_ENABLE;
	(*ePWM[n + 1]).TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // Sync "flow through" mode
	(*ePWM[n + 1]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n + 1]).TBCTL.bit.CLKDIV = TB_DIV1;

	// Counter compare submodule registers
	(*ePWM[n + 1]).CMPA.half.CMPA = period + 10; // Initial value
	(*ePWM[n + 1]).CMPB = 20; // Initial value
	(*ePWM[n + 1]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	(*ePWM[n + 1]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	(*ePWM[n + 1]).CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	(*ePWM[n + 1]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;

	// Action Qualifier SubModule Registers
	(*ePWM[n + 1]).AQCTLA.bit.CAU = AQ_SET;
	(*ePWM[n + 1]).AQCTLA.bit.CBU = AQ_CLEAR;
	(*ePWM[n + 1]).AQCTLA.bit.ZRO = AQ_CLEAR;
	(*ePWM[n + 1]).AQCTLA.bit.PRD = AQ_CLEAR;

	(*ePWM[n + 1]).AQCTLB.bit.CBU = AQ_SET;
	(*ePWM[n + 1]).AQCTLB.bit.CAU = AQ_CLEAR;
	(*ePWM[n + 1]).AQCTLB.bit.ZRO = AQ_CLEAR;
	(*ePWM[n + 1]).AQCTLB.bit.PRD = AQ_CLEAR;

	// Cycle-by-cycle shutdown mechanism configuration

	EALLOW;
	//===========================================================================
	// Define an event (DCAEVT1) based on Comparator 1 Output
	(*ePWM[n + 1]).DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP1OUT; // DCAH = Comparator 1 output
	(*ePWM[n + 1]).TZDCSEL.bit.DCAEVT1 = TZ_DCAH_HI; // DCAEVT1 = DCAH high(will become active
	// as Comparator output goes high)
	(*ePWM[n + 1]).DCACTL.bit.EVT1SRCSEL = DC_EVT_FLT; // DCAEVT1 = DC_EVT_FLT (filtered)
	(*ePWM[n + 1]).DCACTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC; // Take async path

	// Enable DCAEVT1 as a one-shot source
	(*ePWM[n + 1]).TZSEL.bit.DCAEVT1 = 1; // Enable One-Shot Trip

	// Following code for the sync mechanism based on the same trigger event - COMPxOUT
	(*ePWM[n + 1]).DCACTL.bit.EVT1SYNCE = 1; // Sync enabled

	// What do we want the DCAEVT1 event to do? - Initial Configuration
	(*ePWM[n + 1]).TZCTL.bit.TZA = TZ_NO_CHANGE; // EPWMxA - no change
	(*ePWM[n + 1]).TZCTL.bit.TZB = TZ_FORCE_LO; // EPWMxB - go low

	//===========================================================================
	// Event Filtering Configuration
	(*ePWM[n + 1]).DCFCTL.bit.SRCSEL = DC_SRC_DCAEVT1;
	(*ePWM[n + 1]).DCFCTL.bit.BLANKE = DC_BLANK_ENABLE;
	(*ePWM[n + 1]).DCFCTL.bit.PULSESEL = DC_PULSESEL_ZERO;

	(*ePWM[n + 1]).DCFOFFSET = 2; // Blanking Window Offset = CMPA(n+1)
	(*ePWM[n + 1]).DCFWINDOW = 4; // Blanking window length - initial value
	//===========================================================================
	EDIS;

	//Configure EPWM(n+2) time base for ADC SOC generation and syncing the DAC

	//Time Base SubModule Register
	(*ePWM[n + 2]).TBCTL.bit.PRDLD = TB_IMMEDIATE;
	(*ePWM[n + 2]).TBPRD = period - 1;
	(*ePWM[n + 2]).TBPHS.half.TBPHS = period - 35;
	(*ePWM[n + 2]).TBCTR = 0;

	(*ePWM[n + 2]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
	(*ePWM[n + 2]).TBCTL.bit.PHSEN = TB_ENABLE;
	(*ePWM[n + 2]).TBCTL.bit.PHSDIR = TB_UP;
	(*ePWM[n + 2]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
	(*ePWM[n + 2]).TBCTL.bit.CLKDIV = TB_DIV1;

	(*ePWM[n + 2]).TBCTL.bit.SYNCOSEL = TB_SYNC_IN; // Pass the Sync signal through to ePWM4

	if (SR_Enable == 1) { // PWM configuration for synchronous rectification
		//Configure EPWM(n+3) for synchronous rectifier drive
		//Time Base SubModule Register
		(*ePWM[n + 3]).TBCTL.bit.PRDLD = TB_IMMEDIATE; // Set Immediate load
		(*ePWM[n + 3]).TBPRD = period - 1;
		(*ePWM[n + 3]).TBPHS.half.TBPHS = 0;
		(*ePWM[n + 3]).TBCTR = 0;

		(*ePWM[n + 3]).TBCTL.bit.CTRMODE = TB_COUNT_UP;
		(*ePWM[n + 3]).TBCTL.bit.PHSEN = TB_ENABLE; // Enabled for SR
		(*ePWM[n + 3]).TBCTL.bit.PHSDIR = TB_UP;
		(*ePWM[n + 3]).TBCTL.bit.HSPCLKDIV = TB_DIV1;
		(*ePWM[n + 3]).TBCTL.bit.CLKDIV = TB_DIV1;

		// Counter compare submodule registers
		(*ePWM[n + 3]).CMPB = 20; // Initial value
		(*ePWM[n + 3]).CMPA.half.CMPA = period + 10; // Initial value
		(*ePWM[n + 3]).CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
		(*ePWM[n + 3]).CMPCTL.bit.SHDWAMODE = CC_SHADOW;
		(*ePWM[n + 3]).CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
		(*ePWM[n + 3]).CMPCTL.bit.SHDWBMODE = CC_SHADOW;

		// Action Qualifier SubModule Registers
		(*ePWM[n + 3]).AQCTLA.bit.ZRO = AQ_CLEAR;
		(*ePWM[n + 3]).AQCTLA.bit.CAU = AQ_CLEAR;
		(*ePWM[n + 3]).AQCTLB.bit.ZRO = AQ_SET;
		(*ePWM[n + 3]).AQCTLB.bit.CBU = AQ_CLEAR;

		// Cycle-by-cycle syncing mechanism configuration

		EALLOW;
		//===========================================================================
		// Define an event (DCAEVT1) based on Comparator 1 Output
		(*ePWM[n + 3]).DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP1OUT; // DCAH = Comparator 1 output
		(*ePWM[n + 3]).TZDCSEL.bit.DCAEVT1 = TZ_DCAH_HI; // DCAEVT1 = DCAH high(will become active
		// as Comparator output goes high)
		(*ePWM[n + 3]).TZCTL.bit.DCAEVT1 = 3; // No action at the output on DCAEVT1
		(*ePWM[n + 3]).DCACTL.bit.EVT1SRCSEL = DC_EVT_FLT; // DCAEVT1 = DC_EVT_FLT (filtered)
		(*ePWM[n + 3]).DCACTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC; // Take async path

		// Following code for the sync mechanism off of the same trigger event - COMPxOUT
		(*ePWM[n + 3]).DCACTL.bit.EVT1SYNCE = 1; // Sync enabled

		// Event Filtering Config
		(*ePWM[n + 3]).DCFCTL.bit.SRCSEL = DC_SRC_DCAEVT1;
		(*ePWM[n + 3]).DCFCTL.bit.BLANKE = DC_BLANK_ENABLE;
		(*ePWM[n + 3]).DCFCTL.bit.PULSESEL = DC_PULSESEL_ZERO;

		(*ePWM[n + 3]).DCFOFFSET = 2; // Blanking Window Offset = CMPA(n+3)
		(*ePWM[n + 3]).DCFWINDOW = 4; // Blanking window length - initial value

		EDIS;
	} // End SR PWM configuration

	// Over current shutdown mechanism configuration - using comparator 2
	//===========================================================================
	if (Comp2_Prot == 1) {
		EALLOW;
		// Define an event (DCAEVT1) based on Comparator 1 Output
		(*ePWM[n]).DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP2OUT; // DCAH = Comparator 2 output
		(*ePWM[n]).TZDCSEL.bit.DCAEVT1 = TZ_DCAH_HI; // DCAEVT1 = DCAH high(will become active
		// as Comparator output goes high)
		(*ePWM[n]).DCACTL.bit.EVT1SRCSEL = DC_EVT1; // DCAEVT1 = DCAEVT1 (not filtered)
		(*ePWM[n]).DCACTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC; // Take async path

		// Enable DCAEVT1 as a one-shot source
		(*ePWM[n]).TZSEL.bit.DCAEVT1 = 1;

		// What do we want the DCAEVT1 event to do?
		(*ePWM[n]).TZCTL.bit.TZA = TZ_FORCE_LO; // EPWMxA will go low
		(*ePWM[n]).TZCTL.bit.TZB = TZ_FORCE_LO; // EPWMxB will go low
		EDIS;
	}
	//===========================================================================

	// ADC SOC generation
	//===========================================================================
	// SOC generation using PWM(n) - 1st of 4 Vout conversions in one half cycle
	(*ePWM[n]).ETSEL.bit.SOCAEN = 1;
	(*ePWM[n]).ETSEL.bit.SOCASEL = ET_CTR_PRDZERO; // Use ZRO and PRD events as trigger
	(*ePWM[n]).ETPS.bit.SOCAPRD = 1; // Generate pulse on 1st event

	// SOC generation using PWM(n+1) - Iout conversion
	(*ePWM[n + 1]).ETSEL.bit.SOCAEN = 1;
	(*ePWM[n + 1]).ETSEL.bit.SOCASEL = ET_CTR_ZERO; // Use ZRO event as trigger
	(*ePWM[n + 1]).ETPS.bit.SOCAPRD = ET_2ND; // Generate pulse on 1st event

	// SOC generation using PWM(n+2) - 2nd, 3rd and 4th Vout conversions in one half cycle; Vin and Ipri conversions
	(*ePWM[n + 2]).ETSEL.bit.SOCAEN = 1;
	(*ePWM[n + 2]).ETSEL.bit.SOCASEL = ET_CTRU_CMPA; // Use CAU event as trigger
	(*ePWM[n + 2]).ETPS.bit.SOCAPRD = 1; // Generate pulse on 1st event
	(*ePWM[n + 2]).CMPA.half.CMPA = 40; // Note: This value is based on 100 KHz switching frequency

	(*ePWM[n + 2]).ETSEL.bit.SOCBEN = 1;
	(*ePWM[n + 2]).ETSEL.bit.SOCBSEL = ET_CTRU_CMPB; // Use CBU event as trigger
	(*ePWM[n + 2]).ETPS.bit.SOCBPRD = 1; // Generate pulse on 1st event
	(*ePWM[n + 2]).CMPB = 165; // Note: This value is based on 100 KHz switching frequency

}
