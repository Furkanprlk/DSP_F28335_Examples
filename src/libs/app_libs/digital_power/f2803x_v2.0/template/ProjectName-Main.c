//----------------------------------------------------------------------------------
//	FILE:			ProjectName-Main.C
//
//	Description:	Sample Template file to edit
//					The file drives duty on PWM1A using CLA and PWM2 using C28x
//					These can be deleted and modifed by the user
//					CLA Task is triggered by the PWM 1 interrupt
//					C28x ISR is triggered by the PWM 2 interrupt  
//
//	Version: 		1.0
//
//  Target:  		TMS320F2803x(PiccoloB), 
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2004-2010
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description / Status
//----------------------------------------------------------------------------------
// June 29 , 2010  - Sample template project (MB)
//----------------------------------------------------------------------------------
//
// PLEASE READ - Useful notes about this Project

// Although this project is made up of several files, the most important ones are:
//	 "{ProjectName}-Main.C"	- this file
//		- Application Initialization, Peripheral config,
//		- Application management
//		- Slower background code loops and Task scheduling
//	 "{ProjectName}-DevInit_F28xxx.C
//		- Device Initialization, e.g. Clock, PLL, WD, GPIO mapping
//		- Peripheral clock enables
//		- DevInit file will differ per each F28xxx device series, e.g. F280x, F2833x,
//	 "{ProjectName}-DPL-ISR.asm
//		- Assembly level library Macros and any cycle critical functions are found here
//	 "{ProjectName}-DPL-CLA.asm"
//		- Init code for DPlib CLA Macros run by C28x
//		- CLA Task code
//	 "{ProjectName}-Settings.h"
//		- Global defines (settings) project selections are found here
//		- This file is referenced by both C and ASM files.
//	 "{ProjectName}-CLAShared.h.h"
//		- Variable defines and header includes that are shared b/w CLA and C28x 
//
// Code is made up of sections, e.g. "FUNCTION PROTOTYPES", "VARIABLE DECLARATIONS" ,..etc
//	each section has FRAMEWORK and USER areas.
//  FRAMEWORK areas provide useful ready made "infrastructure" code which for the most part
//	does not need modification, e.g. Task scheduling, ISR call, GUI interface support,...etc
//  USER areas have functional example code which can be modified by USER to fit their appl.
//
// Code can be compiled with various build options (Incremental Builds IBx), these
//  options are selected in file "{ProjectName}-Settings.h".  Note: "Rebuild All" compile
//  tool bar button must be used if this file is modified.
//----------------------------------------------------------------------------------
#include "ProjectName-Settings.h"
#include "PeripheralHeaderIncludes.h"
#include "DSP2803x_EPWM_defines.h"		
#include "ProjectName-CLAShared.h"  
		
#include "DPlib.h"	
#include "IQmathLib.h"

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// FUNCTION PROTOTYPES
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Add protoypes of functions being used in the project here 
void DeviceInit(void);
#ifdef FLASH		
	void InitFlash();
#endif
void MemCopy();
void CLA_Init();
//-------------------------------- DPLIB --------------------------------------------
void PWM_1ch_CNF(int16 n, int16 period, int16 mode, int16 phase);

// -------------------------------- FRAMEWORK --------------------------------------
// State Machine function prototypes
//----------------------------------------------------------------------------------
// Alpha states
void A0(void);	//state A0
void B0(void);	//state B0
void C0(void);	//state C0

// A branch states
void A1(void);	//state A1
void A2(void);	//state A2
void A3(void);	//state A3
void A4(void);	//state A4

// B branch states
void B1(void);	//state B1
void B2(void);	//state B2
void B3(void);	//state B3
void B4(void);	//state B4

// C branch states
void C1(void);	//state C1
void C2(void);	//state C2
void C3(void);	//state C3
void C4(void);	//state C4

// Variable declarations
void (*Alpha_State_Ptr)(void);	// Base States pointer
void (*A_Task_Ptr)(void);		// State pointer A branch
void (*B_Task_Ptr)(void);		// State pointer B branch
void (*C_Task_Ptr)(void);		// State pointer C branch
//----------------------------------------------------------------------------------

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// VARIABLE DECLARATIONS - GENERAL
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// -------------------------------- FRAMEWORK --------------------------------------

int16	VTimer0[4];					// Virtual Timers slaved off CPU Timer 0
int16	VTimer1[4];					// Virtual Timers slaved off CPU Timer 1
int16	VTimer2[4];					// Virtual Timers slaved off CPU Timer 2

// Used for running BackGround in flash, and ISR in RAM
extern Uint16 *RamfuncsLoadStart, *RamfuncsLoadEnd, *RamfuncsRunStart;
// Used for copying CLA code from load location to RUN location 
extern Uint16 Cla1funcsLoadStart, Cla1funcsLoadEnd, Cla1funcsRunStart;

// Used for ADC Configuration 
int 	ChSel[16] =   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int		TrigSel[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int     ACQPS[16] =   {7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7};
// ---------------------------------- USER -----------------------------------------
// ---------------------------- DPLIB Net Pointers ---------------------------------
// Declare net pointers that are used to connect the DP Lib Macros  here 

// PWMDRV_1ch
extern volatile long *PWMDRV_1ch_In2;		// instance #2, EPWM2

// PWMDRV_1ch_CLA
extern volatile long *PWMDRV_1ch_CLA_In1;	// instance #1, EPWM1

// ---------------------------- DPLIB Variables ---------------------------------
// Declare the net variables being used by the DP Lib Macro here 
//Two Phase Interleaved PFC PWM Driver CLA
#if (INCR_BUILD == 1) 
#pragma DATA_SECTION(Duty1A, 		"CpuToCla1MsgRAM");
#endif 

volatile long Duty1A; 
volatile long Duty2A;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// VARIABLE DECLARATIONS - CCS WatchWindow / GUI support
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// -------------------------------- FRAMEWORK --------------------------------------

//GUI support variables
// sets a limit on the amount of external GUI controls - increase as necessary
int16 	*varSetTxtList[16];					//16 textbox controlled variables
int16 	*varSetBtnList[16];					//16 button controlled variables
int16 	*varSetSldrList[16];				//16 slider controlled variables
int16 	*varGetList[16];					//16 variables sendable to GUI
int16 	*arrayGetList[16];					//16 arrays sendable to GUI	
int16  LedBlinkCnt;

// ---------------------------------- USER -----------------------------------------

// Monitor ("Get")						// Display as:

// Configure ("Set")

// History arrays are used for Running Average calculation (boxcar filter)
// Used for CCS display and GUI only, not part of control loop processing

//Scaling Constants (values found via spreadsheet; exact value calibrated per board)

// Variables for background support only (no need to access)
int16	i;								// common use incrementer
Uint32	HistPtr, temp_Scratch; 			// Temp here means Temporary

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// MAIN CODE - starts here
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void main(void)
{
//=================================================================================
//	INITIALISATION - General
//=================================================================================

	// The DeviceInit() configures the clocks and pin mux registers 
	// The function is declared in {ProjectName}-DevInit_F2803/2x.c,
	// Please ensure/edit that all the desired components pin muxes 
	// are configured properly that clocks for the peripherals used
	// are enabled, for example the individual PWM clock must be enabled 
	// along with the Time Base Clock 

	DeviceInit();	// Device Life support & GPIO

//-------------------------------- FRAMEWORK --------------------------------------

// Only used if running from FLASH
// Note that the variable FLASH is defined by the compiler with -d FLASH

#ifdef FLASH		
// Copy time critical code and Flash setup code to RAM
// The  RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
// symbols are created by the linker. Refer to the linker files. 
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);

// Call Flash Initialization to setup flash waitstates
// This function must reside in RAM
	InitFlash();	// Call the flash wrapper init function
#endif //(FLASH)


// Timing sync for background loops
// Timer period definitions found in PeripheralHeaderIncludes.h
	CpuTimer0Regs.PRD.all =  mSec1;		// A tasks
	CpuTimer1Regs.PRD.all =  mSec10;	// B tasks
	CpuTimer2Regs.PRD.all =  mSec100;	// C tasks

// Tasks State-machine init
	Alpha_State_Ptr = &A0;
	A_Task_Ptr = &A1;
	B_Task_Ptr = &B1;
	C_Task_Ptr = &C1;

	VTimer0[0] = 0;	
	VTimer1[0] = 0;
	VTimer2[0] = 0;
	LedBlinkCnt = 5;

// ---------------------------------- USER -----------------------------------------
//  put common initialization/variable definitions here


//===============================================================================
//	INITIALISATION - GUI connections
//=================================================================================
// Use this section only if you plan to "Instrument" your application using the 
// Microsoft C# freeware GUI Template provided by TI
/*
	//"Set" variables
	//---------------------------------------
	// assign GUI variable Textboxes to desired "setable" parameter addresses
	varSetTxtList[0] = &Gui_TxtListVar;
	varSetTxtList[1] = &Gui_TxtListVar;
	varSetTxtList[2] = &Gui_TxtListVar;
	varSetTxtList[3] = &Gui_TxtListVar;
	varSetTxtList[4] = &Gui_TxtListVar;
	varSetTxtList[5] = &Gui_TxtListVar;
	varSetTxtList[6] = &Gui_TxtListVar;
	varSetTxtList[7] = &Gui_TxtListVar;
	varSetTxtList[8] = &Gui_TxtListVar;
	varSetTxtList[9] = &Gui_TxtListVar;
	varSetTxtList[10] = &Gui_TxtListVar;
	varSetTxtList[11] = &Gui_TxtListVar;

	// assign GUI Buttons to desired flag addresses
	varSetBtnList[0] = &Gui_BtnListVar;
    varSetBtnList[1] = &Gui_BtnListVar;
	varSetBtnList[2] = &Gui_BtnListVar;
	varSetBtnList[3] = &Gui_BtnListVar;
	varSetBtnList[4] = &Gui_BtnListVar;

	// assign GUI Sliders to desired "setable" parameter addresses
	varSetSldrList[0] = &Gui_SldrListVar;
	varSetSldrList[1] = &Gui_SldrListVar;
	varSetSldrList[2] = &Gui_SldrListVar;
	varSetSldrList[3] = &Gui_SldrListVar;
	varSetSldrList[4] = &Gui_SldrListVar;

	//"Get" variables
	//---------------------------------------
	// assign a GUI "getable" parameter address
	varGetList[0] = &Gui_GetListVar;
	varGetList[1] = &Gui_GetListVar;
	varGetList[2] = &Gui_GetListVar;
	varGetList[3] = &Gui_GetListVar;
	varGetList[4] = &Gui_GetListVar;
	varGetList[5] = &Gui_GetListVar;
	varGetList[6] = &Gui_GetListVar;
	varGetList[7] = &Gui_GetListVar;
	varGetList[8] = &Gui_GetListVar;
	varGetList[9] = &Gui_GetListVar;
	varGetList[10] = &Gui_GetListVar;
	varGetList[11] = &Gui_GetListVar;
	varGetList[12] = &Gui_GetListVar;
	varGetList[13] = &Gui_GetListVar;
	varGetList[14] = &Gui_GetListVar;
	varGetList[15] = &Gui_GetListVar;

	// assign a GUI "getable" parameter array address
	arrayGetList[0] = &DBUFF1;  	//only need to set initial position of array,
	arrayGetList[1] = &DBUFF2;		//  program will run through it accordingly
	arrayGetList[2] = &DBUFF3;
	arrayGetList[3] = &DBUFF4;
*/

//==================================================================================
//	INCREMENTAL BUILD OPTIONS - NOTE: selected via {ProjectName-Settings.h
//==================================================================================
// ---------------------------------- USER -----------------------------------------

//----------------------------------------------------------------------
#if (INCR_BUILD == 1) 	// Open Loop Two Phase Interleaved PFC PWM Driver
//----------------------------------------------------------------------
	
	// Configure PWM1 for 200Khz switching Frequency 
	PWM_1ch_CNF(1, 300,1,0); 
	
	// Configure PWM2 for 150Khz switching Frequency 
	PWM_1ch_CNF(2, 300,1,0); 
   	
	// Digital Power CLA(DP) library initialisation 
	DPL_CLAInit();
	DPL_Init();
	
	// Lib Module connection to "nets" 
	//----------------------------------------
	// Connect the PWM Driver input to an input variable, Open Loop System
	PWMDRV_1ch_CLA_In1 = &Duty1A;
	
	PWMDRV_1ch_In2     = &Duty2A;
	
	// Initialize the net variables
	Duty1A =_IQ24(0.4);
	Duty2A =_IQ24(0.2);
		
	CLA_Init();
	
#endif // (INCR_BUILD == 1)

//====================================================================================
// INTERRUPTS & ISR INITIALIZATION (best to run this section after other initialization)
//====================================================================================

// Set Up CLA Task

// Task 1 has the option to be started by either EPWM1_INT or ADCINT1 
// In this case we will allow ADCINT1 to start CLA Task 1
    EALLOW;
    
	// Configure PWM1 to issue interrupts
	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;  	// INT on PRD event
   	EPwm1Regs.ETSEL.bit.INTEN = 1;              // Enable INT
    EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;         // Generate INT on every event
	
	Cla1Regs.MPISRCSEL1.bit.PERINT1SEL = CLA_INT1_EPWM1INT ;		// 0=ADCINT1    1=none    2=EPWM1INT
	
	// Configure the interrupt that woud occur each control cycles
    Cla1Regs.MIER.all = M_INT1;
  
	asm("   RPT #3 || NOP"); 
	
	EDIS;
	
// Set up C28x Interrupt

//Also Set the appropriate # define's in the {ProjectName}-Settings.h 
//to enable interrupt management in the ISR
	EALLOW;
    PieVectTable.EPWM2_INT = &DPL_ISR;      	// Map Interrupt
   	PieCtrlRegs.PIEIER3.bit.INTx2 = 1;      	// PIE level enable, Grp3 / Int2
   	EPwm2Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;  	// INT on PRD event
   	EPwm2Regs.ETSEL.bit.INTEN = 1;              // Enable INT
    EPwm2Regs.ETPS.bit.INTPRD = ET_1ST;         // Generate INT on every event

    IER |= M_INT3;                          	// Enable CPU INT3 connected to EPWM1-6 INTs:
    EINT;                                   	// Enable Global interrupt INTM
    ERTM;                                   	// Enable Global realtime interrupt DBGM
	EDIS;      

//=================================================================================
//	BACKGROUND (BG) LOOP
//=================================================================================

//--------------------------------- FRAMEWORK -------------------------------------
	for(;;)  //infinite loop
	{
		// State machine entry & exit point
		//===========================================================
		(*Alpha_State_Ptr)();	// jump to an Alpha state (A0,B0,...)
		//===========================================================



	}
} //END MAIN CODE



//=================================================================================
//	STATE-MACHINE SEQUENCING AND SYNCRONIZATION
//=================================================================================

//--------------------------------- FRAMEWORK -------------------------------------
void A0(void)
{
	// loop rate synchronizer for A-tasks
	if(CpuTimer0Regs.TCR.bit.TIF == 1)
	{
		CpuTimer0Regs.TCR.bit.TIF = 1;	// clear flag

		//-----------------------------------------------------------
		(*A_Task_Ptr)();		// jump to an A Task (A1,A2,A3,...)
		//-----------------------------------------------------------

		VTimer0[0]++;			// virtual timer 0, instance 0 (spare)
	}

	Alpha_State_Ptr = &B0;		// Comment out to allow only A tasks
}

void B0(void)
{
	// loop rate synchronizer for B-tasks
	if(CpuTimer1Regs.TCR.bit.TIF == 1)
	{
		CpuTimer1Regs.TCR.bit.TIF = 1;				// clear flag

		//-----------------------------------------------------------
		(*B_Task_Ptr)();		// jump to a B Task (B1,B2,B3,...)
		//-----------------------------------------------------------
		VTimer1[0]++;			// virtual timer 1, instance 0 (spare)
	}

	Alpha_State_Ptr = &C0;		// Allow C state tasks
}

void C0(void)
{
	// loop rate synchronizer for C-tasks
	if(CpuTimer2Regs.TCR.bit.TIF == 1)
	{
		CpuTimer2Regs.TCR.bit.TIF = 1;				// clear flag

		//-----------------------------------------------------------
		(*C_Task_Ptr)();		// jump to a C Task (C1,C2,C3,...)
		//-----------------------------------------------------------
		VTimer2[0]++;			//virtual timer 2, instance 0 (spare)
	}

	Alpha_State_Ptr = &A0;	// Back to State A0
}


//=================================================================================
//	A - TASKS
//=================================================================================
//--------------------------------------------------------
void A1(void) 
//--------------------------------------------------------
{
	
	//-------------------
	//the next time CpuTimer0 'counter' reaches Period value go to A2
	A_Task_Ptr = &A2;
	//-------------------
}

//-----------------------------------------------------------------
void A2(void) 
//-----------------------------------------------------------------
{	 
	//-------------------
	//the next time CpuTimer0 'counter' reaches Period value go to A1
	A_Task_Ptr = &A3;
	//-------------------
}

//-----------------------------------------
void A3(void)	
//-----------------------------------------
{
	
	//-----------------
	//the next time CpuTimer0 'counter' reaches Period value go to A1
	A_Task_Ptr = &A4;
	//-----------------
}


//----------------------------------------------------------
void A4(void) 
//---------------------------------------------------------
{
	//-----------------
	//the next time CpuTimer0 'counter' reaches Period value go to A1
	A_Task_Ptr = &A1;
	//-----------------
}


//=================================================================================
//	B - TASKS
//=================================================================================

//----------------------------------- USER ----------------------------------------

//----------------------------------------
void B1(void)
//----------------------------------------
{		
	//-----------------
	//the next time CpuTimer1 'counter' reaches Period value go to B2
	B_Task_Ptr = &B2;	
	//-----------------
}

//----------------------------------------
void B2(void) // Blink LED on the control CArd
//----------------------------------------
{
	if(LedBlinkCnt==0)
		{
			GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;	//turn on/off LD3 on the controlCARD
			LedBlinkCnt=5;
		}
	else
			LedBlinkCnt--;
			
	//-----------------
	//the next time CpuTimer1 'counter' reaches Period value go to B3
	B_Task_Ptr = &B3;
	//-----------------
}

//----------------------------------------
void B3(void)  
//----------------------------------------
{
	//-----------------
	//the next time CpuTimer1 'counter' reaches Period value go to B4
	B_Task_Ptr = &B4;	
	//-----------------
}

//----------------------------------------
void B4(void) //  SPARE
//----------------------------------------
{
	//-----------------
	//the next time CpuTimer1 'counter' reaches Period value go to B1
	B_Task_Ptr = &B1;	
	//-----------------
}


//=================================================================================
//	C - TASKS
//=================================================================================

//--------------------------------- USER ------------------------------------------

//------------------------------------------------------
void C1(void) 	 
//------------------------------------------------------
{

	//-----------------
	//the next time CpuTimer2 'counter' reaches Period value go to C2
	C_Task_Ptr = &C2;	
	//-----------------

}

//----------------------------------------
void C2(void) 
//----------------------------------------
{

	//-----------------
	//the next time CpuTimer2 'counter' reaches Period value go to C3
	C_Task_Ptr = &C3;	
	//-----------------
}


//-----------------------------------------
void C3(void) 
//-----------------------------------------
{

	//-----------------
	//the next time CpuTimer2 'counter' reaches Period value go to C4
	C_Task_Ptr = &C4;	
	//-----------------
}


//-----------------------------------------
void C4(void) //  SPARE
//-----------------------------------------
{

	//-----------------
	//the next time CpuTimer2 'counter' reaches Period value go to C1
	C_Task_Ptr = &C1;	
	//-----------------
}



