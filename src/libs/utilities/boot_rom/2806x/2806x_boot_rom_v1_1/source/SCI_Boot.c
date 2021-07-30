// TI File $Revision: /main/4 $
// Checkin $Date: March 8, 2011   15:18:37 $
//###########################################################################
//
// FILE:    SCI_Boot.c
//
// TITLE:   SCI Boot mode routines
//
// Functions:
//
//     Uint32 SCI_Boot(void)
//     inline void SCIA_Init(void)
//     inline void SCIA_AutobaudLock(void)
//     Uint32 SCIA_GetWordData(void)
//
// Notes:
//
//###########################################################################
// $TI Release: TMS320x2806x Boot ROM V1.0 $
// $Release Date: October 21, 2010 $
//###########################################################################

#include "Boot.h"

// Private functions
Uint16 SCIA_GetWordData(void);

// External functions
extern void CopyData(void);
Uint32 GetLongData(void);
extern void ReadReservedFn(void);


//#################################################
// Uint32 SCI_Boot(void)
//--------------------------------------------
// This module is the main SCI boot routine.
// It will load code via the SCI-A port.
//
// It will return a entry point address back
// to the InitBoot routine which in turn calls
// the ExitBoot routine.
//--------------------------------------------

Uint32 SCI_Boot()
{
   Uint32 EntryAddr;
   Uint16 byteData;
   // Asign GetWordData to the SCI-A version of the
   // function.  GetWordData is a pointer to a function.
   GetWordData = SCIA_GetWordData;

    // SCIA_Init();
	//----------------------------------------------
    // Initialize the SCI-A port for communications
    // with the host.
    //----------------------------------------------

    // Enable the SCI-A clocks
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.SCIAENCLK=1;
    SysCtrlRegs.LOSPCP.all = 0x0002;
    SciaRegs.SCIFFTX.all=0x8000;
    // 1 stop bit, No parity, 8-bit character
    // No loopback
    SciaRegs.SCICCR.all = 0x0007;
    // Enable TX, RX, Use internal SCICLK
    SciaRegs.SCICTL1.all = 0x0003;
    // Disable RxErr, Sleep, TX Wake,
    // Diable Rx Interrupt, Tx Interrupt
    SciaRegs.SCICTL2.all = 0x0000;
    // Relinquish SCI-A from reset
    SciaRegs.SCICTL1.all = 0x0023;
    // Enable pull-ups on SCI-A pins
    // GpioCtrlRegs.GPAPUD.bit.GPIO28 = 0;
    // GpioCtrlRegs.GPAPUD.bit.GPIO29 = 0;
    GpioCtrlRegs.GPAPUD.all &= 0xCFFFFFFF;
    // Enable the SCI-A pins
    // GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 1;
    // GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 1;
    GpioCtrlRegs.GPAMUX2.all |= 0x05000000;
    // Input qual for SCI-A RX is asynch
    GpioCtrlRegs.GPAQSEL2.bit.GPIO28 = 3;
    EDIS;

    //SCIA_AutobaudLock();
    //------------------------------------------------
    // Perform autobaud lock with the host.
    // Note that if autobaud never occurs
    // the program will hang in this routine as there
    // is no timeout mechanism included.
    //------------------------------------------------

    // Must prime baud register with >= 1
    SciaRegs.SCILBAUD = 1;
    // Prepare for autobaud detection
    // Set the CDC bit to enable autobaud detection
    // and clear the ABD bit
    SciaRegs.SCIFFCT.bit.CDC = 1;
    SciaRegs.SCIFFCT.bit.ABDCLR = 1;
    // Wait until we correctly read an
    // 'A' or 'a' and lock
    while(SciaRegs.SCIFFCT.bit.ABD != 1) {}
    // After autobaud lock, clear the ABD and CDC bits
    SciaRegs.SCIFFCT.bit.ABDCLR = 1;
    SciaRegs.SCIFFCT.bit.CDC = 0;
    while(SciaRegs.SCIRXST.bit.RXRDY != 1) { }
    byteData = SciaRegs.SCIRXBUF.bit.RXDT;
    SciaRegs.SCITXBUF = byteData;

   // If the KeyValue was invalid, abort the load
   // and return the flash entry point.
   if (SCIA_GetWordData() != 0x08AA) return FLASH_ENTRY_POINT;

   ReadReservedFn();

   EntryAddr = GetLongData();

   CopyData();

   return EntryAddr;
}

//#################################################
// Uint16 SCIA_GetWordData(void)
//-----------------------------------------------
// This routine fetches two bytes from the SCI-A
// port and puts them together to form a single
// 16-bit value.  It is assumed that the host is
// sending the data in the order LSB followed by MSB.
//-----------------------------------------------


Uint16 SCIA_GetWordData()
{
   Uint16 wordData;
   Uint16 byteData;

   wordData = 0x0000;
   byteData = 0x0000;

   // Fetch the LSB and verify back to the host
   while(SciaRegs.SCIRXST.bit.RXRDY != 1) { }
   wordData =  (Uint16)SciaRegs.SCIRXBUF.bit.RXDT;
   SciaRegs.SCITXBUF = wordData;

   // Fetch the MSB and verify back to the host
   while(SciaRegs.SCIRXST.bit.RXRDY != 1) { }
   byteData =  (Uint16)SciaRegs.SCIRXBUF.bit.RXDT;
   SciaRegs.SCITXBUF = byteData;

   // form the wordData from the MSB:LSB
   wordData |= (byteData << 8);

   return wordData;
}

// EOF-------

