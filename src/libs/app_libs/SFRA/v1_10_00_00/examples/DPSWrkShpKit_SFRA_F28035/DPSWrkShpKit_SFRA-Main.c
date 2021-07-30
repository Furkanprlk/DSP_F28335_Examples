//----------------------------------------------------------------------------------
//	FILE:			DPSWrkShpKit_SFRA-Main.C
//
//	Description:	Project for F28035 to run of DPS Workshop Board
//					Configures Buck 1 on the board to regulate in voltage mode control
//					Runs Frequency Response Analysis and can be used with GUI to display
//					the results
//
//	Version: 		1.0
//
//  Target:  		TMS320F2803x(PiccoloB), 
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2004-2014
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description / Status
//----------------------------------------------------------------------------------
// August 2014  - DPS Board Project for SFRA Demo (Manish Bhardwaj)
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
#include "DPSWrkShpKit_SFRA-Settings.h"
#include "PeripheralHeaderIncludes.h"
#include "DSP2803x_EPWM_defines.h"		

#define   MATH_TYPE      0   //IQ_MATH
#include "IQmathLib.h"
#include "math.h"
#include "Solar_IQ.h"
#include "DPlib.h"

#include "SFRA_IQ_Include.h"
#define SFRA_ISR_FREQ 200000
#define SFRA_FREQ_START 100
#define SFRA_FREQ_LENGTH 100
//SFRA step Multiply = 10^(1/No of steps per decade(40))
#define FREQ_STEP_MULTIPLY (float)1.059253

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// FUNCTION PROTOTYPES
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Add protoypes of functions being used in the project here 
void DeviceInit(void);
void SerialHostComms();
void SCIA_Init(long SCI_VBUS_CLOCKRATE, long SCI_BAUDRATE);
#ifdef FLASH		
	void InitFlash();
#endif
void MemCopy();

//-------------------------------- DPLIB --------------------------------------------
void PWM_1ch_CNF(int16 n, int16 period, int16 mode, int16 phase);

#pragma CODE_SECTION(PWM_ISR,"ramfuncs")
extern interrupt void PWM_ISR(void);

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


// B branch states
void B1(void);	//state B1
void B2(void);	//state B2
void B3(void);	//state B3
void B4(void);	//state B4

// C branch states
void C1(void);	//state C1


// Variable declarations
void (*Alpha_State_Ptr)(void);	// Base States pointer
void (*A_Task_Ptr)(void);		// State pointer A branch
void (*B_Task_Ptr)(void);		// State pointer B branch
void (*C_Task_Ptr)(void);		// State pointer C branch
//----------------------------------------------------------------------------------

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// VARIABLE DECLARATIONS - GENERAL
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Used to indirectly access all EPWM modules
volatile struct EPWM_REGS *ePWM[] =
   { &EPwm1Regs,                                              //intentional: (ePWM[0] not used)
	 &EPwm1Regs,
	 &EPwm2Regs,
	 &EPwm3Regs,
	 &EPwm4Regs,
	 #if (!DSP2802x_DEVICE_H)
 	 &EPwm5Regs,
	 &EPwm6Regs,
	 #if (DSP2803x_DEVICE_H || DSP2804x_DEVICE_H)
	 &EPwm7Regs,
	 #if (DSP2804x_DEVICE_H)
	 &EPwm8Regs
	 #endif
	 #endif
	 #endif
   };

// Used to indirectly access all Comparator modules
volatile struct COMP_REGS *Comp[] =
   { &Comp1Regs,                                               //intentional: (Comp[0] not used)
 	 &Comp1Regs,
	 &Comp2Regs,
	 #if (DSP2803x_DEVICE_H)
	 &Comp3Regs
	 #endif
   };

Uint16 Active_load_PRD = 60000;
// -------------------------------- FRAMEWORK --------------------------------------

int16	VTimer0[4];					// Virtual Timers slaved off CPU Timer 0
int16	VTimer1[4];					// Virtual Timers slaved off CPU Timer 1
int16	VTimer2[4];					// Virtual Timers slaved off CPU Timer 2
int16	SerialCommsTimer;
int16 	CommsOKflg;


// Used for running BackGround in flash, and ISR in RAM
extern Uint16 *RamfuncsLoadStart, *RamfuncsLoadEnd, *RamfuncsRunStart;

// Used for ADC Configuration 
int 	ChSel[16] =   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int		TrigSel[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int     ACQPS[16] =   {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8};

// ---------------------------------- USER -----------------------------------------
// ---------------------------- DPLIB Net Pointers ---------------------------------
// Declare net pointers that are used to connect the DP Lib Macros  here 
void ADC_SOC_CNF(int ChSel[], int Trigsel[], int ACQPS[], int IntChSel, int mode);
extern void DacDrvCnf(int16 n, int16 DACval, int16 DACsrc, int16 RAMPsrc, int16 Slope_initial);

// System Flags
int16	FaultFlg1 = 0;			// Fault flag set on over current condition
int16 	ClearFault1 = 0;
int16	Active_LD1_EN = 0;
int16 Itrip1 = _IQ15(0.8);

volatile long Vref1 = 0;			// Output Set Voltage
volatile long Vout1_slew_temp = 0;		// Temp variable: used only if implementing
										// slew rate control in the slower state machine
volatile long Vout1SetSlewed = 2093568;	// Slewed set point for the FB voltage loop - start from 4V
volatile long Vout1SetSlewed_With_Inject=0;
volatile long Vout1SlewRate = 25600;			// FB Slew rate adjustment

// DECLARE THE 3P3Z OBJECT
#pragma DATA_SECTION(cntl3p3z_vars1,"cntl_var_RAM")
#pragma DATA_SECTION(cntl3p3z_coeff1,"cntl_coeff_RAM")
CNTL_3P3Z_IQ_VARS cntl3p3z_vars1;
CNTL_3P3Z_IQ_COEFFS cntl3p3z_coeff1;

volatile int32 Vout1_Read;
volatile int32 Duty_pu,Duty_pu_DC,Duty_pwm;
// Measurement Offsets
_iq24 offset_Vout;
//Offset filter coefficient K1: 0.05/(T+0.05);
_iq K1 = _IQ(0.998);
//Offset filter coefficient K2: T/(T+0.05)
_iq K2 = _IQ(0.001999);
int16 OffsetCalCounter;

// SFRA lib Object
SFRA_IQ SFRA1;
// SFRA Variables
int32 Plant_MagVect[SFRA_FREQ_LENGTH];
int32 Plant_PhaseVect[SFRA_FREQ_LENGTH];
int32 OL_MagVect[SFRA_FREQ_LENGTH];
int32 OL_PhaseVect[SFRA_FREQ_LENGTH];
float32 FreqVect[SFRA_FREQ_LENGTH];

//Flag for reinitializing SFRA variables
int16 initializationFlag;

//extern to access tables in ROM
extern long IQsinTable[];

// Transient Check
DLOG_1CH_IQ dlog_1ch1;
int16 DBUFF_1CH1[100];
int16 dval1;


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
int32 	*arrayGetList[16];					//16 arrays sendable to GUI
Uint32   *dataSetList[16];					//16 32-bit textbox or label controlled variables

int16  	LedBlinkCnt;

// ---------------------------------- USER -----------------------------------------

// Monitor ("Get")						// Display as:
int16	Gui_Vin;							// Q5
int16	Gui_IL1;							// Q12
int16	Gui_Vout1;							// Q10


// Configure ("Set")
int16	Gui_VSet1 = 0;						// Q11 




//Scaling Constants (values found via spreadsheet; exact value calibrated per board)
int16	K_Vin;								// Q15
int16	K_IL1;								// Q15

int16	K_Vout1;							// Q15 


int16	iK_IL1;								// Q14

int16	iK_Vout1;							// Q14


// Variables for background support only (no need to access)
int16	i;								// common use incrementer
Uint32	HistPtr, temp_Scratch; 			// Temp here means Temporary

// History arrays are used for Running Average calculation (boxcar filter)
// Used for CCS display and GUI only, not part of control loop processing
int16	Hist_Vin[HistorySize];
int16	Hist_IL1[HistorySize];
int16	Hist_Vout1[HistorySize];


int32 delayStart;

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// MAIN CODE - starts here
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void main(void)
{


//=================================================================================
//	INITIALIZATION - General
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
	SCIA_Init(15000000, 57600); // 15000000 is the LSPCLK or the Clock used for the SCI Module
								// 57600 is the Baudrate desired of the SCI module
#endif //(FLASH)

// Timing sync for background loops
// Timer period definitions found in PeripheralHeaderIncludes.h
	CpuTimer0Regs.PRD.all =  mSec0_5;		// A tasks
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

#ifdef	FLASH
	CommsOKflg = 0;
	SerialCommsTimer = 0;
	//"Set" variables
	// assign GUI Buttons to desired flag addresses
	varSetBtnList[0] = (int16*)&initializationFlag;

	//"Get" variables
	//---------------------------------------
	// assign a GUI "getable" parameter address
	varGetList[0] = (int16*)&(SFRA1.Vec_Length);			//int16
	varGetList[1] = (int16*)&(SFRA1.status);			    //int16
	varGetList[2] = (int16*)&(SFRA1.FreqIndex);					//int16

	//"Setable" variables
	//----------------------------------------
	// assign GUI "setable" by Text parameter address
	dataSetList[0] = (Uint32*)&(SFRA1.Freq_Start);      //Float 32
	dataSetList[1] = (Uint32*)&(SFRA1.amplitude);	   //Int32
	dataSetList[2] = (Uint32*)&(SFRA1.Freq_Step);	   //Float32

	// assign a GUI "getable" parameter array address
	arrayGetList[0] = (int32*)FreqVect;			        //Float 32
	arrayGetList[1] = (int32*)OL_MagVect;			    //
	arrayGetList[2] = (int32*)OL_PhaseVect;		        //
	arrayGetList[3] = (int32*)Plant_MagVect;			//
	arrayGetList[4] = (int32*)Plant_PhaseVect;			//
	arrayGetList[5] = (int32*)&(SFRA1.Freq_Start);      //Float 32
	arrayGetList[6] = (int32*)&(SFRA1.amplitude);	   //Int32
	arrayGetList[7] = (int32*)&(SFRA1.Freq_Step);	   //Float32
#endif

	HistPtr = 0;
	
// ---------------------------------- USER -----------------------------------------
//  put common initialization/variable definitions here

//Configure Scaling Constants
	K_Vin = 27238;									// 0.831 in Q15 (see excel spreadsheet)
	K_IL1 = 22528;									// 0.688 in Q15 (see excel spreadsheet)
	K_Vout1 = 19994;								// 0.610 in Q15 (see excel spreadsheet)
	
	iK_Vout1 = 26852;								// 1.639 in Q14 (see excel spreadsheet)


	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0; 
	EDIS;

//==================================================================================
//	INCREMENTAL BUILD OPTIONS - NOTE: selected via {ProjectName-Settings.h
//==================================================================================
// ---------------------------------- USER -----------------------------------------

// "Raw" (R) ADC measurement name defines
#define		Vout1R			AdcResult.ADCRESULT1	//
#define		IL1R			AdcResult.ADCRESULT2	//
#define		VinR	 		AdcResult.ADCRESULT3	//

// Channel Selection for Cascaded Sequencer
	ChSel[0] = 6;				// A6 -  Vout1 - Dummy
	ChSel[1] = 6;				// A6 -  Vout1
	ChSel[2] = 1;				// A1 -  IL1
	ChSel[3] = 9;				// B1 -  Vin

	TrigSel[0] = ADCTRIG_EPWM1_SOCA;	// Vout1 sampling triggered by EPWM1 SOCA - Dummy
	TrigSel[1] = ADCTRIG_EPWM1_SOCA; 	// Vout1 sampling triggered by EPWM1 SOCA
	TrigSel[2] = ADCTRIG_EPWM1_SOCA;	// IL1 inductor current sampling triggered by EPWM1 SOCA
	TrigSel[3] = ADCTRIG_EPWM1_SOCA;	// Vin sampling triggered by EPWM3 SOCA

	// Configure PWM1 for 200Khz switching Frequency 
	//Period Count= 60Mhz/200Khz = 300
	PWM_1ch_CNF(1, 300,1,0); 

	// Configure ADC  
	ADC_SOC_CNF(ChSel,TrigSel,ACQPS, 16, 0);// ACQPS=8, No ADC channel triggers an interrupt IntChSel > 15, Mode= Start/Stop (0) 
  
	EPwm1Regs.ETSEL.bit.SOCAEN  =  1;
	EPwm1Regs.ETSEL.bit.SOCASEL =  ET_CTR_ZERO; // Use CTR = ZRO events as trigger 
    EPwm1Regs.ETPS.bit.SOCAPRD = 1; 	        // Generate pulse on 1st event  

	EPwm2Regs.ETSEL.bit.SOCAEN  =  1;
	EPwm2Regs.ETSEL.bit.SOCASEL =  ET_CTR_ZERO; // Use CTR = ZRO events as trigger 
    EPwm2Regs.ETPS.bit.SOCAPRD = 1; 	        // Generate pulse on 1st event  


//----------------------------------------------------------------------

    CNTL_3P3Z_IQ_VARS_init(&cntl3p3z_vars1);
    CNTL_3P3Z_IQ_COEFFS_init(&cntl3p3z_coeff1);

    /* 2.5 Khz Coeff */
    cntl3p3z_coeff1.Coeff_A1=_IQ24(1.1201983);
	cntl3p3z_coeff1.Coeff_A2=_IQ24(-0.1201983);
	cntl3p3z_coeff1.Coeff_A3=_IQ24(0.0);
	cntl3p3z_coeff1.Coeff_B0=_IQ24(1.1951143);
	cntl3p3z_coeff1.Coeff_B1=_IQ24(-1.1571392);
	cntl3p3z_coeff1.Coeff_B2=_IQ24(-0.0060149);
	cntl3p3z_coeff1.Coeff_B3=_IQ24(0.0);
	cntl3p3z_coeff1.IMin=_IQ24(-0.1);
	cntl3p3z_coeff1.Max=_IQ24(0.9);
	cntl3p3z_coeff1.Min=_IQ24(0.0);

	// Do SFRA Object Initialization here

	//SFRA Object Initialization
	//Specify the injection amplitude
	SFRA1.amplitude=_IQ26(0.01);
	//Specify the length of SFRA
	SFRA1.Vec_Length=SFRA_FREQ_LENGTH;
	//Specify the SFRA ISR Frequency
	SFRA1.ISR_Freq=SFRA_ISR_FREQ;
	//Specify the Start Frequency of the SFRA analysis
	SFRA1.Freq_Start=SFRA_FREQ_START;
	//Specify the Frequency Step
	SFRA1.Freq_Step=FREQ_STEP_MULTIPLY;
	//Assign array location to Pointers in the SFRA object
	SFRA1.FreqVect=FreqVect;
	SFRA1.GH_MagVect=OL_MagVect;
	SFRA1.GH_PhaseVect=OL_PhaseVect;
	SFRA1.H_MagVect=Plant_MagVect;
	SFRA1.H_PhaseVect=Plant_PhaseVect;

	initializationFlag = 0; /**** TEST: Attempt to cause initialization of SFRA_IQ before sweep ****/

	SFRA_IQ_INIT(&SFRA1);

	// Transient Tuning
	DLOG_1CH_IQ_init(&dlog_1ch1);
	dlog_1ch1.input_ptr = &dval1; //data value
	dlog_1ch1.output_ptr = &DBUFF_1CH1[0];
	dlog_1ch1.size = 100;
	dlog_1ch1.pre_scalar = 5;
	dlog_1ch1.trig_value = _IQ15(0.1);
	dlog_1ch1.status = 2;


	//
	Duty_pwm=0;
	Duty_pu_DC=0;
	Duty_pu=0;
	Vout1_Read=0;

	delayStart=5000;


// Configure PWM1, Comparator1 and DAC for over current protection for channel 1
	EALLOW;	
// Define an event (DCAEVT1) based on Comparator 1 Output
	EPwm1Regs.DCTRIPSEL.bit.DCAHCOMPSEL = DC_COMP1OUT; 	// DCAH = Comparator 1 output
	EPwm1Regs.TZDCSEL.bit.DCAEVT1 = TZ_DCAH_HI; 		// DCAEVT1 = DCAH high(will become active
														// as Comparator output goes high)
	EPwm1Regs.DCACTL.bit.EVT1SRCSEL = DC_EVT1; 			// DCAEVT1 = DCAEVT1 (not filtered)
	EPwm1Regs.DCACTL.bit.EVT1FRCSYNCSEL = DC_EVT_ASYNC;	// Take async path

// Enable DCAEVT1 as a one-shot source
	EPwm1Regs.TZSEL.bit.DCAEVT1 = 1;

// What do we want the DCAEVT1 event to do?
	EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO; 				// EPWMxA will go low 
	EDIS;

	DacDrvCnf(1, Itrip1, 0, 2, 0);		// Comp1, DACval = Itrip1, DAC Source is DACval, Ramp Source = don't care, Slope = don't care
//===========================================================================
//Active load PWM drive configuration
//===========================================================================
	//Time Base SubModule Register
	EPwm3Regs.TBCTL.bit.PRDLD = TB_IMMEDIATE;	// set Immediate load
	EPwm3Regs.TBPRD = Active_load_PRD;
	EPwm3Regs.TBCTL.bit.CTRMODE = TB_COUNT_UPDOWN;
	EPwm3Regs.TBCTL.bit.HSPCLKDIV = TB_DIV4;
	EPwm3Regs.TBCTL.bit.CLKDIV = TB_DIV4;
	EPwm3Regs.TBCTL.bit.PHSEN = TB_DISABLE;
	EPwm3Regs.TBCTL.bit.SYNCOSEL = TB_SYNC_IN; 		// sync "down-stream" 
	
	// Counter compare submodule registers
	EPwm3Regs.CMPCTL.bit.LOADAMODE = CC_CTR_ZERO;
	EPwm3Regs.CMPCTL.bit.LOADBMODE = CC_CTR_ZERO;
	EPwm3Regs.CMPCTL.bit.SHDWAMODE = CC_SHADOW;
	EPwm3Regs.CMPCTL.bit.SHDWBMODE = CC_SHADOW;

	// Action Qualifier SubModule Registers
	EPwm3Regs.AQCTLA.bit.CAD = AQ_SET;
	EPwm3Regs.AQCTLA.bit.CAU = AQ_CLEAR;
	EPwm3Regs.AQCTLB.bit.CBD = AQ_SET;
	EPwm3Regs.AQCTLB.bit.CBU = AQ_CLEAR;

//====================================================================================
// INTERRUPTS & ISR INITIALIZATION (best to run this section after other initialization)
//====================================================================================

	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1; 
	EPwm1Regs.ETSEL.bit.INTSEL = ET_CTR_PRD;  	// INT on PRD event
	EPwm1Regs.ETSEL.bit.INTEN = 1;              // Enable INT
	EPwm1Regs.ETPS.bit.INTPRD = ET_1ST;         // Generate INT on every event
	EDIS;
	
	/********* Run Calibration for offset in grid and panel current ******/
	//TODO Run Calibration Task
	OffsetCalCounter=0;
	offset_Vout=0;
	while(OffsetCalCounter<10000)
	{
		if(EPwm1Regs.ETFLG.bit.INT==1)
		{
			offset_Vout= _IQmpy(K1,offset_Vout)+_IQmpy(K2,_IQ12toIQ(Vout1R));
			OffsetCalCounter++;
			EPwm1Regs.ETCLR.bit.INT=1;
		}
	}


// Set up C28x Interrupt

//Also Set the appropriate # define's in the {ProjectName}-Settings.h 
//to enable interrupt management in the ISR
	EALLOW;
	// Configure PWM1 to issue interrupts
    PieVectTable.EPWM1_INT = &PWM_ISR;      	// Map Interrupt
   	PieCtrlRegs.PIEIER3.bit.INTx1 = 1;      	// PIE level enable, Grp3 / Int1
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

		if(initializationFlag == 1)
		{
			SFRA_IQ_INIT(&SFRA1);
			initializationFlag = 0;
			SFRA1.start = 1;
		}
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
		SerialCommsTimer++;		// used by DSP280x_SciCommsGui_edit.c Uncomment for FLASH w/GUI
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

	SFRA_IQ_BACKGROUND(&SFRA1);
	//-------------------
	//the next time CpuTimer0 'counter' reaches Period value go to A2
	A_Task_Ptr = &A2;
	//-------------------
}

//-----------------------------------------------------------------
void A2(void)   // Slew Rate
//-----------------------------------------------------------------
{	 
	// This is an example code for implementing the slew rate control in
	// a slower state machine instead of implementing it in the ISR.
	// VoutXSlewRate should be set as a positive value
	Vout1_slew_temp = Vref1 - Vout1SetSlewed;

	if (Vout1_slew_temp >= Vout1SlewRate) // Positive Command
	{
		Vout1SetSlewed = Vout1SetSlewed + Vout1SlewRate;
	}
	else
	{
		if ((-1)*(Vout1_slew_temp) >= Vout1SlewRate) // Negative Command
			{
			Vout1SetSlewed = Vout1SetSlewed - Vout1SlewRate;
			}
		else	Vout1SetSlewed = Vref1;
	}

	SerialHostComms();	// Uncomment for FLASH config

	//-------------------
	//the next time CpuTimer0 'counter' reaches Period value go to A1
	A_Task_Ptr = &A3;
	//-------------------
}

//-----------------------------------------
void A3(void)	// Active Load Enable/Disable
//-----------------------------------------
{
	
	if (Active_LD1_EN == 1)
	{
			EPwm3Regs.CMPA.half.CMPA = Active_load_PRD;
	}		
	else
	{
			EPwm3Regs.CMPA.half.CMPA = 0;
	}				
	

	if(delayStart==0)
	{

#if INCR_BUILD==2
		Gui_VSet1=_IQ11(2.0);
#endif

	}
	else
		delayStart--;

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

// Voltage measurement calculated by:
//	Gui_Vin = VinAvg * K_Vin, where VfbinAvg = sum of 8 Vfb_inR samples
//	Gui_Voutx = VoutAvg * K_Vout, where VfboutAvg = sum of 8 Vfb_outR samples
 
	HistPtr++;
	if (HistPtr >= 8)	HistPtr = 0;

// BoxCar Averages - Input Raw samples into History arrays
//----------------------------------------------------------------
	Hist_Vin[HistPtr] =VinR; 		// Raw ADC result (Q12)

	temp_Scratch=0;
	for(i=0; i<HistorySize; i++)	temp_Scratch = temp_Scratch + Hist_Vin[i]; // Q12 * 8 = Q15
	Gui_Vin = ( (long) temp_Scratch * (long) K_Vin ) >> 15; // (Q15 * Q15)>>15 = Q15

// BoxCar Averages - Input Raw samples into History arrays
//----------------------------------------------------------------   
	Hist_Vout1[HistPtr] = _IQsat((Vout1R - (offset_Vout>>12)),_IQ12(1.0),_IQ12(0.0));  // Raw ADC result (Q12)

	temp_Scratch=0;
	for(i=0; i<HistorySize; i++)	temp_Scratch = temp_Scratch + Hist_Vout1[i]; // Q12 * 8 = Q15
	Gui_Vout1 = ( (long) temp_Scratch * (long) K_Vout1 ) >> 15; // (Q15 * Q15)>>15 = Q15

		
// Current measurement calculated by:
//	Gui_Ifb = IfbAvg * K_Ifb, where IfbAvg = sum of 8 IfbR samples
//BoxCar Averages - Input Raw samples into History arrays 
	
	Hist_IL1[HistPtr] = IL1R; // Raw ADC result (Q12)

	temp_Scratch=0;
	for(i=0; i<HistorySize; i++)	temp_Scratch = temp_Scratch + Hist_IL1[i]; // Q12 * 8 = Q15
	if (temp_Scratch > 1549)	temp_Scratch = temp_Scratch - 1549;	//offset adjust
	else temp_Scratch  = 0;
	Gui_IL1 = ( (long) temp_Scratch * (long) K_IL1 ) >> 15; // (Q15 * Q15)>>15 = Q15


// Voltage setting calculated by:
// VrefX = Gui_VSetX * iK_VoutX, where iK_VoutX = 1/K_VoutX (i.e. inverse K_VoutX)
// view and set following variable in Watch Window as:
//	Gui_VSet1 = Q10 (Used as Q15 below) 
	Vref1 = ( (long) Gui_VSet1 * (long) iK_Vout1) >> 5; // (Q15 * Q14) >> 5 = Q24


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
void C1(void) 	 // Fault Management
//------------------------------------------------------
{
	//TODO

	if (ClearFault1 == 1)
	{
		EALLOW;
		(*ePWM[1]).TZCLR.bit.OST = 1;
		EDIS;		
		ClearFault1 = 0;
	}

	if ( (*ePWM[1]).TZFLG.bit.OST == 1 )
		FaultFlg1 = 1; 
	else FaultFlg1 = 0;  
	//-----------------
	//the next time CpuTimer2 'counter' reaches Period value go to C2
	C_Task_Ptr = &C1;
	//-----------------

}



interrupt void PWM_ISR(void)
{
	//TODO PWM ISR

#if (INCR_BUILD==1)
	//Read ADC and computer Fbk Value
	Vout1_Read= _IQsat((((int32)Vout1R<<12)-offset_Vout),_IQ24(1.0),_IQ24(0.0)); //(int32)Vout1R<<12;

	//Add SFRA injection into the duty cycle for the open loop converter
	Duty_pu=SFRA_IQ_INJECT(Duty_pu_DC);

	//Update PWM value
	EPwm1Regs.CMPA.half.CMPA=_IQ24mpy((long)(BUCK_PWM_PERIOD),Duty_pu);

	SFRA_IQ_COLLECT(&Duty_pu,&Vout1_Read);
#endif

#if (INCR_BUILD==2)

	//Read ADC and computer Fbk Value
	cntl3p3z_vars1.Fdbk= _IQsat((((int32)Vout1R<<12)-offset_Vout),_IQ24(1.0),_IQ24(0.0));

	//Add SFRA injection into the reference of the controller
	cntl3p3z_vars1.Ref= SFRA_IQ_INJECT(Vout1SetSlewed);

	// Call the controller
	CNTL_3P3Z_IQ_ASM(&cntl3p3z_coeff1,&cntl3p3z_vars1);

	//Update PWM value
	EPwm1Regs.CMPA.half.CMPA=_IQ24mpy((long)(BUCK_PWM_PERIOD),cntl3p3z_vars1.Out);

	SFRA_IQ_COLLECT(&cntl3p3z_vars1.Out,&cntl3p3z_vars1.Fdbk);

#endif

	dval1=_IQtoIQ15(Vout1SetSlewed);
	DLOG_1CH_IQ_FUNC(&dlog_1ch1);


	EPwm1Regs.ETCLR.bit.INT=1;
	PieCtrlRegs.PIEACK.bit.ACK3=0x1;
}
