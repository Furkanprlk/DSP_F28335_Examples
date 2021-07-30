//----------------------------------------------------------------------------------
//	FILE:			PM_bissc-SystemTest.C
//
//	Description:	Example project for using PM BiSS-C Library.
//					Includes PM_bissc_lib library and correspoding include files.
//					Initializes the encoders and performs delay compensation.
//					Continuously reads position value in an infinite loop
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
// Nov 2015  - Example project for PM BiSS-C Library Usage
//----------------------------------------------------------------------------------

#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "bissc.h"

int16_t bissCDCounter = 1000;


void main(void)
{

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

	bissc_init();

	// Enable global Interrupts and higher priority real-time debug events:
    EINT;  // Enable Global interrupt INTM
    ERTM;  // Enable Global realtime interrupt DBGM


	while(1)
	{

		#if BISS_ENCODER_HAS_CD_INTERFACE
		//every so often, do a CD transaction
		if(bissCDCounter < 0)
		{
			//for Lika HS58S18/I7, addr 0x7E (ManuID MSB) should contain 0x4C (CRC on packet should be 0xF)
			bissc_data_struct.cd_register_xfer_address = 0x7E;
			bissc_data_struct.cd_register_xfer_is_write = 0;
			bissc_data_struct.cd_status = 0;  //arm new
			bissCDCounter = 1000;
		}
		else
		{
			bissCDCounter--;
		}
		#endif


		// BISS_DATA_CLOCKS
		//  for Lika HS58S18/I7-P9-RM2 it is 34 ==> 32 (pos+E+W+posCRC) + CDS + Start
		//  for Kuebler 8.F5863.1426.C423 it is 36 ==> 34 (pos+E+W+posCRC) + CDS + Start
		PM_bissc_setupNewSCDTransfer(BISS_DATA_CLOCKS, SPI_FIFO_WIDTH);

		#if BISS_ENCODER_HAS_CD_INTERFACE
		if(bissc_doCDTasks() == 0)
		{
			ESTOP0; //most likely the BiSS CD CRC did not match
		}
		#endif

		PM_bissc_startOperation();

		while (bissc_data_struct.dataReady != 1) {}

		// fill and receive SCD data (including position) and putting it into the BiSS data structure
		if(bissc_receivePosition(BISS_POSITION_BITS, BISS_POSITION_CRC_BITS) == 0)
		{
			ESTOP0; //BiSS SCD CRC did not match
		}

		DELAY_US(10000L); 	//Delay 10ms
	}

}


//===========================================================================
// No more.
//===========================================================================
