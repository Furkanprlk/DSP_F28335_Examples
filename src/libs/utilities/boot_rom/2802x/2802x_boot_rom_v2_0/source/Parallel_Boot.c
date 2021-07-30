// TI File $Revision: /main/3 $
// Checkin $Date: December 9, 2009   17:52:24 $
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
// $TI Release: 2802x Boot ROM V2.00 $
// $Release Date: December 10, 2009 $
//###########################################################################


#include "Boot.h"

// Private function definitions
inline void Parallel_GPIOSelect(void);
//inline Uint16 Parallel_CheckKeyVal(void);
Uint16 Parallel_GetWordData_8bit(void);
//Uint16 Parallel_GetWordData_16bit(void);
void Parallel_WaitHostRdy(void);
void Parallel_HostHandshake(void);

// External function definitions
extern void CopyData(void);
extern Uint32 GetLongData(void);
extern void ReadReservedFn(void);

#define HOST_CTRL          GPIO12  // GPIO27 is the host control signal
#define DSP_CTRL           GPIO16  // GPIO26 is the DSP's control signal

#define HOST_DATA_NOT_RDY  GpioDataRegs.GPADAT.bit.HOST_CTRL!=0
#define WAIT_HOST_ACK      GpioDataRegs.GPADAT.bit.HOST_CTRL!=1

// Set (DSP_ACK) or Clear (DSP_RDY) GPIO 17
#define DSP_ACK            GpioDataRegs.GPASET.bit.DSP_CTRL = 1;
#define DSP_RDY            GpioDataRegs.GPACLEAR.bit.DSP_CTRL = 1;
#define DATA               GpioDataRegs.GPADAT.all

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
// void Parallel_GPIOSelect(void)
//------------------------------------------
// Enable I/O pins for input GPIO 15:0.  Also 
// enable the control pins for HOST_CTRL and 
// DSP_CTRL.
//------------------------------------------

inline void Parallel_GPIOSelect()
{

    EALLOW;
    // Enable pull-ups for GPIO Port A 7:0
    // GPIO Port 7:0 are all I/O pins
    // and DSP_CTRL/HOST_CTRL
//   GpioCtrlRegs.GPAPUD.bit.GPIO7 = 0;
//   GpioCtrlRegs.GPAPUD.bit.GPIO6 = 0;
//   GpioCtrlRegs.GPAPUD.bit.GPIO5 = 0;
//   GpioCtrlRegs.GPAPUD.bit.GPIO4 = 0;    
//   GpioCtrlRegs.GPAPUD.bit.GPIO3 = 0;
//   GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;
//   GpioCtrlRegs.GPAPUD.bit.GPIO1 = 0;                            
//   GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;                            
//   GpioCtrlRegs.GPAPUD.bit.DSP_CTRL = 0;
//   GpioCtrlRegs.GPAPUD.bit.HOST_CTRL = 0;
     GpioCtrlRegs.GPAPUD.all &= 0xFFFEEF00;

    // 0 = I/O pin  1 = Peripheral pin
    GpioCtrlRegs.GPAMUX1.all = 0x0000;
    GpioCtrlRegs.GPAMUX2.bit.DSP_CTRL = 0;
    GpioCtrlRegs.GPAMUX1.bit.HOST_CTRL = 0;
 
    // HOST_CTRL is an input control 
    // from the Host 
    // to the DSP Ack/Rdy
    // DSP_CTRL is an output from the DSP Ack/Rdy
    // 0 = input   1 = output
    GpioCtrlRegs.GPADIR.bit.DSP_CTRL = 1;
    GpioCtrlRegs.GPADIR.bit.HOST_CTRL = 0;

    EDIS;
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
   
   Parallel_WaitHostRdy();
   wordData = DATA;
   Parallel_HostHandshake();
   
   // Fetch the MSB.
   
   wordData = wordData & 0x00FF;
   Parallel_WaitHostRdy();
   wordData |= (DATA << 8);
   Parallel_HostHandshake();
   return wordData;
}

//#################################################
// void Parallel_WaitHostRdy(void)
//-----------------------------------------------------
// This routine tells the host that the DSP is ready to 
// recieve data.  The DSP then waits for the host to 
// signal that data is ready on the GP I/O port.e 
//-----------------------------------------------------
void Parallel_WaitHostRdy()
{
   DSP_RDY;
   while(HOST_DATA_NOT_RDY) { }
}

//#################################################
// void Parallel_HostHandshake(void)
//-----------------------------------------------------
// This routine tells the host that the DSP has recieved
// the data.  The DSP then waits for the host to acknowledge
// the reciept before continuing.  
//-----------------------------------------------------
void Parallel_HostHandshake()
{
   DSP_ACK;
   while(WAIT_HOST_ACK) { }
}
// EOF --------
