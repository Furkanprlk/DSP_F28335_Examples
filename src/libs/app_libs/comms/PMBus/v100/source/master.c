//---------------------------------------------------------------------------

#include "DSP2803x_Device.h"     // DSP280x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP280x Examples Include File
#include "DSP2803x_I2C_defines.h"
#include "I2CMaster.h"
#include "PMBusMaster.h"
#include "PMBUS.h"

// Note: I2C Macros used in this example can be found in the 
// DSP280x_I2C_defines.h file

// Prototype statements for functions found within this file.
void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr);

unsigned char Temp[1] = {0};
unsigned char Oprn[1] = {0};
unsigned char Stat[2] = {0,0};
unsigned char VCmd[2] = {0,0};
unsigned int Status = 0;
unsigned int Vout_Command = 0;
unsigned char pass_fail = 0;

//the user should change these values to match those required for their application
#define I2C_SLAVE_ADDR	0x002C	//the device address of the slave
#define CLK_PRESCALE	9		//the prescale value for the I2C master frequency
								//master frequency = 60000/[(prescale+1)*25] kHz

void main(void)
{
// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP280x_SysCtrl.c file.
	InitSysCtrl();
	
// Copy time critical code and Flash setup code to RAM
// The  RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
// symbols are created by the linker. Refer to the linker files. 
	MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);

// Step 2. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts 
	DINT;   

// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.  
// This function is found in the DSP280x_PieCtrl.c file.
	InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
	IER = 0x0000;
	IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt 
// Service Routines (ISR).  
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP280x_DefaultIsr.c.
// This function is found in DSP280x_PieVect.c.
	InitPieVectTable();

// Step 3. Initialize the Device Peripherals:
	PMBusMaster_Init(I2C_SLAVE_ADDR, CLK_PRESCALE);

	EINT;

   // Application loop
	while(1)
	{
		//reads
		pass_fail = PMBusMaster(STATUS_TEMPERATURE, 1, 0, Temp);	//read byte
		pass_fail = PMBusMaster(OPERATION, 1, 0, Oprn);			//r/w byte (read)
		pass_fail = PMBusMaster(STATUS_WORD, 1, 0, Stat);		//read word
		pass_fail = PMBusMaster(VOUT_COMMAND, 1, 0, VCmd);		//r/w word (read)
		//writes
		pass_fail = PMBusMaster(STORE_DEFAULT_CODE, 0, 0xAA, 0);	//write byte
		pass_fail = PMBusMaster(OPERATION, 0, 0xBB, 0);			//r/w byte (write)				
		pass_fail = PMBusMaster(VOUT_COMMAND, 0, 0xCCDD, 0);		//r/w word (write)  
		
		Status = (Stat[1] << 8) | Stat[0];			//unpacking the two data bytes into one word
		Vout_Command = (VCmd[1] << 8) | VCmd[0];	//the lowest order byte is received first
	}
}   // end of main

// This function will copy the specified memory contents from
// one location to another. 
// 
//	Uint16 *SourceAddr        Pointer to the first word to be moved
//                          SourceAddr < SourceEndAddr
//	Uint16* SourceEndAddr     Pointer to the last word to be moved
//	Uint16* DestAddr          Pointer to the first destination word
//
// No checks are made for invalid memory locations or that the
// end address is > then the first start address.

void MemCopy(Uint16 *SourceAddr, Uint16* SourceEndAddr, Uint16* DestAddr)
{
    while(SourceAddr < SourceEndAddr)
    { 
       *DestAddr++ = *SourceAddr++;
    }
    return;
}

//===========================================================================
// No more.
//===========================================================================

