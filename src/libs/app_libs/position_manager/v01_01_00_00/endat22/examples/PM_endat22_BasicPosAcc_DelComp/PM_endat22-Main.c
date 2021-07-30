//----------------------------------------------------------------------------------
//	FILE:			PM_endat22-Main.C
//
//	Description:	Example project for using PM EnDat22 Library.
//					Includes PM_endat22_lib library and correspoding include files.
//					Initializes the encoders and performs delay compensation.
//					Runs endat21 and endat22 command set.
//					Continuously Read position value in an infinite loop
//
//	Version: 		1.0
//
//  Target:  		TMS320F28377D,
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2004-2015
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description / Status
//----------------------------------------------------------------------------------
// Nov 2015  - Example project for PM EnDat22 Library Usage
//----------------------------------------------------------------------------------
#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "endat.h"

uint16_t crc5_self;

void main(void) {

// Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the F2837xD_SysCtrl.c file.
	InitSysCtrl();
// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
	DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F2837xD_PieCtrl.c file.
	InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
	IER = 0x0000;
	IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in F2837xD_DefaultIsr.c.
// This function is found in F2837xD_PieVect.c.
	InitPieVectTable();

//Initialization routine for endat operation - defined in endat.c
//Configures the peripherals and enables clocks for required modules
//Configures GPIO and XBar as needed for EnDat operation
//Sets up the SPI peripheral in endat data structure and enables interrupt
	EnDat_Init();

//A template for running all the EnDat21 commands
//This is optional in real applications.
//Function defined in endat_commands.c
	endat21_runCommandSet();

	if (ENCODER_TYPE == 22)
	{
//A template for running all the EnDat22 commands
//This is optional in real applications.
//Function defined in endat_commands.c

		endat22_runCommandSet();
	}

//Enables 2 additional datas in endat22 operation
//This is also optional in real applications. Function defined in endat.c

	endat22_setupAddlData();

//Peforms cable propagation delay calculation.
//This is required for long cable lengths and higher EnDat Clock frequencies
//Function defined in endat.c

	EnDat_initDelayComp();

//Switch to high frequency - 8.3MHz	(=200/4*ENDAT_RUNTIME_FREQ_DIVIDER)
	PM_endat22_setFreq(ENDAT_RUNTIME_FREQ_DIVIDER);
	DELAY_US(800L); 	//Delay 800us

	while(1)
	{
		if (ENCODER_TYPE == 22)
		{
//Read position data in EnDat22 mode with 2 additional data enabled
//earlier by endat22_setupAddlData function call.
//Function defined in endat.c
			endat22_readPositionWithAddlData();
		}
		else
		{
//Read position data in EnDat21 mode. Function defined in endat.c
			endat21_readPosition();
		}
	}
}

// End of file





