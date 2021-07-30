// TI File $Revision: /main/1 $
// Checkin $Date: August 13, 2012   11:53:53 $
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
// $TI Release: F2837x Boot ROM V1.0 $
// $Release Date: October 2013 $
//###########################################################################


#include "c1_bootrom.h"


// Private function definitions
Uint16 Parallel_GetWordData_8bit(void);

// External function definitions
extern void CopyData(void);
extern Uint32 GetLongData(void);
extern void ReadReservedFn(void);

#define HOST_CTRL          GPIO70  // GPIO70 is the host control signal (will be configured as input pin)
#define DSP_CTRL           GPIO69  // GPIO26 is the DSP's control signal (will be configured as output pin)

#define HOST_DATA_NOT_RDY  GpioDataRegs.GPCDAT.bit.HOST_CTRL!=0
#define WAIT_HOST_ACK      GpioDataRegs.GPCDAT.bit.HOST_CTRL!=1

// Set (DSP_ACK) or Clear (DSP_RDY) GPIO69
#define DSP_ACK            GpioDataRegs.GPCSET.bit.DSP_CTRL = 1;
#define DSP_RDY            GpioDataRegs.GPCCLEAR.bit.DSP_CTRL = 1;
#define DATA               ((GpioDataRegs.GPBDAT.all & 0xFC000000)>>24|(GpioDataRegs.GPCDAT.bit.GPIO64<<1)|(GpioDataRegs.GPCDAT.bit.GPIO65))

void Parallel_GPIOSelect(void);

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
    Parallel_GPIOSelect();

   // Check for the key value. This version only 
   // supports 8-bit data.
   GetWordData = Parallel_GetWordData_8bit;   
   wordData = GetWordData(); 
   if(wordData != BROM_EIGHT_BIT_HEADER) return FLASH_ENTRY_POINT;
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

void Parallel_GPIOSelect(void)
{

//    GPIO58         Bit 2 (will be configured as input pin)
//    GPIO59         Bit 3 (will be configured as input pin)
//    GPIO60         Bit 4 (will be configured as input pin)
//    GPIO61         Bit 5 (will be configured as input pin)
//    GPIO62         Bit 6 (will be configured as input pin)
//    GPIO63         Bit 7 (will be configured as input pin)
//    GPIO64         Bit 1 (will be configured as input pin)
//    GPIO65         Bit 0 (will be configured as input pin)

//    GPIO70		 HOST_CTRL (will be configured as input pin)
// 	  GPIO69 		 DSP_CTRL  (will be configured as output pin)

 EALLOW;
 /* Configure GPIO58-GPIO65 as input pin */
 GpioCtrlRegs.GPBMUX2.all = 0x0; GpioCtrlRegs.GPBGMUX2.all = 0x0;
 GpioCtrlRegs.GPCMUX1.all = 0x0; GpioCtrlRegs.GPCGMUX1.all = 0x0;

/* Configure GPIO69 and GPIO70 as GPIO pin */
 GpioCtrlRegs.GPCMUX1.bit.DSP_CTRL = 0;	GpioCtrlRegs.GPCGMUX1.bit.DSP_CTRL = 0;
 GpioCtrlRegs.GPCMUX1.bit.HOST_CTRL = 0;	GpioCtrlRegs.GPCGMUX1.bit.HOST_CTRL = 0;

 // HOST_CTRL is an input control from the Host
	// to the DSP Ack/Rdy
 // - may require an external pull-up
 // DSP_CTRL is an output from the DSP Ack/Rdy
	// - may require an external pull-up for host to
	// correctly read "1" initially.
	// DSP_CTRL set to 1 initially
 // 0 = input   1 = output
 GpioCtrlRegs.GPCDIR.bit.DSP_CTRL = 1;	//GPIO69 configured as output pin
 GpioCtrlRegs.GPCDIR.bit.HOST_CTRL = 0; //GPIO70 configured as input pin

 EDIS;

}

// EOF --------



