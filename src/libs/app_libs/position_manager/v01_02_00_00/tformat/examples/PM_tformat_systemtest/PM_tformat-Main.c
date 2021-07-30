//----------------------------------------------------------------------------------
//	FILE:			PM_tformat-Main.C
//
//	Description:	Example project for using PM tformat Library.
//					Includes PM_tformat_lib library and correspoding include files.
//					Initializes the encoders and performs delay compensation.
//					Runs tformat command set.
//					Continuously Read position value in an infinite loop
//
//	Version: 		1.0
//
//  Target:  		TMS320F28379D
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2004-2015
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description / Status
//----------------------------------------------------------------------------------
// Apr 2016  - Example project for PM T-Format Library Usage
//----------------------------------------------------------------------------------
#include "F28x_Project.h"    // Device Headerfile and Examples Include File
#include "tformat.h"		 // Include file for tformat interface

uint32_t crcResult;
uint16_t retval1;		//used for function return val storage and checks
uint32_t position, turns;

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

//Initialization routine for tformat operation - defined in tformat.c
//Configures the peripherals and enables clocks for required modules
//Configures GPIO and XBar as needed for t-format operation
//Sets up the SPI peripheral in tformat data structure and enables interrupt

	tformat_Init();
	DELAY_US(800L); 	//Delay 800us

//Optional function exercising several tformat commands including eeprom accesses
	retval1 = tformat_exCommands();

//Infinite loop to read position using DATAID3 command - returns position and turns information
	while(1)
	{
		retval1 = PM_tformat_setupCommand (DATAID3, 0, 0, 0);
		PM_tformat_startOperation();
		while (tformatData.dataReady != 1) {}
		retval1 = PM_tformat_receiveData(DATAID3);

		crcResult = PM_tformat_getCRC(0, 80, 8, (uint16_t *)&tformatData.rxPkts, tformatCRCtable, 10);
		crcResult = crcResult ^ (0xFF);
		 if (!CheckCRC(crcResult,tformatData.crc))
		 {
				 ESTOP0;
		 }

		 //Invert the received bit sequence for position and turns for actual data
		 position = ((__flip32((uint32_t) tformatData.dataField0) >> 24 ) & 0xFF)|
				    ((__flip32((uint32_t) tformatData.dataField1) >> 16 ) & 0xFF00)|
					((__flip32((uint32_t) tformatData.dataField2) >> 8 )  & 0xFF0000);

		 turns = ((__flip32((uint32_t) tformatData.dataField4) >> 24 ) & 0xFF)|
					((__flip32((uint32_t) tformatData.dataField5) >> 16 ) & 0xFF00)|
					((__flip32((uint32_t) tformatData.dataField6) >> 8 )  & 0xFF0000);

		 DELAY_US(200L);
	}
}

// End of file
