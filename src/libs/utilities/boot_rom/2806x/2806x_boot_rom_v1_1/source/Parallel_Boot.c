// TI File $Revision: /main/4 $
// Checkin $Date: March 8, 2011   15:18:36 $
//###########################################################################
//
// FILE:    Parallel_Boot.c    
//
// TITLE:   Parallel Port I/O boot routines
//
// Functions:
//
//       Uint32 Parallel_Boot(void)        
//       inline void Parallel_GPIOSelect(void)
//       inline Uint16 Parallel_CheckKeyVal(void)
//       Uint16 Parallel_GetWordData_8bit()
//       Uint16 Parallel_GetWordData_16bit()
//       void Parallel_WaitHostRdy(void)
//       void Parallel_HostHandshake(void)
// Notes:
//
//###########################################################################
// $TI Release: TMS320x2806x Boot ROM V1.0 $
// $Release Date: October 21, 2010 $
//###########################################################################


#include "Boot.h"

// Private function definitions
Uint16 Parallel_GetWordData_8bit(void);

// External function definitions
extern void CopyData(void);
extern Uint32 GetLongData(void);
extern void ReadReservedFn(void);

#define HOST_CTRL          AIO12  // AIO12 is the host control signal
#define DSP_CTRL           AIO6   // AIO6 is the DSP's control signal

#define HOST_DATA_NOT_RDY  GpioDataRegs.AIODAT.bit.HOST_CTRL!=0
#define WAIT_HOST_ACK      GpioDataRegs.AIODAT.bit.HOST_CTRL!=1

// Set (DSP_ACK) or Clear (DSP_RDY) AIO6
#define DSP_ACK            GpioDataRegs.AIOSET.bit.DSP_CTRL = 1;
#define DSP_RDY            GpioDataRegs.AIOCLEAR.bit.DSP_CTRL = 1;
#define DATA               ((GpioDataRegs.GPADAT.all&0x003F)|(GpioDataRegs.GPADAT.bit.GPIO31<<7)|(GpioDataRegs.GPADAT.bit.GPIO30<<6))

//#################################################
// Uint32 Parallel_Boot(void)
//--------------------------------------------
// This module is the main Parallel boot routine. 
// It will load code via GP I/Os.  
//
// This boot mode accepts 8-bit data. 
// 8-bit data is expected to be the order LSB
// followed by MSB.
//
// This function returns a entry point address back
// to the InitBoot routine which in turn calls
// the ExitBoot routine. 
//--------------------------------------------

Uint32 Parallel_Boot()
{

   Uint32 EntryAddr;
   Uint16 wordData;
   
   // Setup for Parallel boot
   // Parallel_GPIOSelect();
   //------------------------------------------
   // Enable I/O pins for input GPIO 31:30, 5:0. 
   //  Also enable the control pins for HOST_CTRL 
   // and DSP_CTRL.
   //------------------------------------------   
    EALLOW;
    // Enable pull-ups for GPIO Port A 31:30, 5:0 
    // GPIO Port 31:30, 5:0 are all I/O pins
    // and DSP_CTRL/HOST_CTRL
    //   GpioCtrlRegs.GPAPUD.bit.GPIO31 = 0;
    //   GpioCtrlRegs.GPAPUD.bit.GPIO30 = 0;
    //   GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;
    //   GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    
    //   GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;
    //   GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;
    //   GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;                            
    //   GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;                            
    //   GpioCtrlRegs.GPAPUD.bit.DSP_CTRL = 0;
    //   GpioCtrlRegs.GPAPUD.bit.HOST_CTRL = 0;
    GpioCtrlRegs.GPAPUD.all &= 0x3FFFFFC0;

    // 0 = I/O pin  1 = Peripheral pin
    GpioCtrlRegs.GPAMUX1.all = 0x0000;
    
    // GpioCtrlRegs.AIOMUX1.bit.DSP_CTRL = 0;
    // GpioCtrlRegs.AIOMUX1.bit.HOST_CTRL = 0;
	GpioCtrlRegs.AIOMUX1.all &= ~0x03003000;
 
    // HOST_CTRL is an input control from the Host 
	// to the DSP Ack/Rdy 
    // - may require an external pull-up
    // DSP_CTRL is an output from the DSP Ack/Rdy
	// - may require an external pull-up for host to
	// correctly read "1" initially.
	// DSP_CTRL set to 1 initially (no internal pull-up on AIO pins)
    // 0 = input   1 = output
	GpioDataRegs.AIOSET.bit.DSP_CTRL = 1; 
    GpioCtrlRegs.AIODIR.bit.DSP_CTRL = 1;

 //   GpioCtrlRegs.AIODIR.bit.HOST_CTRL = 0;

    EDIS;

   // Check for the key value. This version only 
   // supports 8-bit data.
   GetWordData = Parallel_GetWordData_8bit;   
   wordData = GetWordData(); 
   if(wordData != EIGHT_BIT_HEADER) return FLASH_ENTRY_POINT;
   // Read and discard the reserved words
   ReadReservedFn();
   // Get the entry point address
   EntryAddr = GetLongData(); 
   // Load the data
   CopyData();
    
   return EntryAddr;

}

//#################################################
// Uint16 Parallel_GetWordData_8bit()/  
// The _8bit function is used if the input stream is 
// an 8-bit input stream and the upper 8-bits of the 
// GP I/O port are ignored.  In the 8-bit case the 
// first fetches the LSB and then the MSB from the 
// GPIO port.  These two bytes are then put together to
// form a single 16-bit word that is then passed back
// to the host. Note that in this case, the input stream
// from the host is in the order LSB followed by MSB
//-----------------------------------------------
Uint16 Parallel_GetWordData_8bit()
{
   Uint16 wordData;
     
   // Get LSB.  
   // Parallel_WaitHostRdy();
   // This routine tells the host that the DSP is ready to 
   // recieve data.  The DSP then waits for the host to 
   // signal that data is ready on the GP I/O port. 
   DSP_RDY;
   while(HOST_DATA_NOT_RDY) { }

   wordData = DATA;
  
  // Parallel_HostHandshake();
  // This routine tells the host that the DSP has recieved
  // the data.  The DSP then waits for the host to acknowledge
  // the reciept before continuing.  
   DSP_ACK;
   while(WAIT_HOST_ACK) { }

   // Fetch the MSB.
   wordData = wordData & 0x00FF;
  
   // Parallel_WaitHostRdy();
   // This routine tells the host that the DSP is ready to 
   // recieve data.  The DSP then waits for the host to 
   // signal that data is ready on the GP I/O port. 
   DSP_RDY;
   while(HOST_DATA_NOT_RDY) { }
   
   wordData |= (DATA << 8);
      
  // Parallel_HostHandshake();
  // This routine tells the host that the DSP has recieved
  // the data.  The DSP then waits for the host to acknowledge
  // the reciept before continuing.  
   DSP_ACK;
   while(WAIT_HOST_ACK) {} 
      
   return wordData;
}

// EOF --------



