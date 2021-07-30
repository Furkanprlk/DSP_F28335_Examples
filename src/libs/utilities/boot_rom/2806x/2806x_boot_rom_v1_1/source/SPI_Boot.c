// TI File $Revision: /main/4 $
// Checkin $Date: March 8, 2011   15:18:38 $
//###########################################################################
//
// FILE:    SPI_Boot.c
//
// TITLE:   SPI Boot mode routines
//
// Functions:
//
//     Uint32 SPI_Boot(void)
//     Uint16 SPIA_SetAddress_KeyChk(void)
//     inline void SPIA_Transmit(u16 cmdData)
//     inline void SPIA_ReservedFn(void);
//     Uint32 SPIA_GetWordData(void)
//
// Notes:
//
//###########################################################################
// $TI Release: TMS320x2806x Boot ROM V1.0 $
// $Release Date: October 21, 2010 $
//###########################################################################

#include "Boot.h"

// Private functions
inline Uint16 SPIA_Transmit(Uint16 cmdData);
inline void SPIA_ReservedFn(void);
Uint16 SPIA_GetWordData(void);
Uint16 SPIA_SetAddress_KeyChk(void);

// External functions
extern void CopyData(void);
Uint32 GetLongData(void);

//#################################################
// Uint32 SPI_Boot(void)
//--------------------------------------------
// This module is the main SPI boot routine.
// It will load code via the SPI-A port.
//
// It will return a entry point address back
// to the ExitBoot routine.
//--------------------------------------------

Uint32 SPI_Boot()
{
   Uint32 EntryAddr;

   // Asign GetWordData to the SPI-A version of the
   // function.  GetWordData is a pointer to a function.
   GetWordData = SPIA_GetWordData;
   // 1. Init SPI-A and set
   //    EEPROM chip enable - low

   // SPIA_Init();
   //----------------------------------------------
   // Initialize the SPI-A port for communications
   // with the host.
   //----------------------------------------------

   // Enable SPI-A clocks
    EALLOW;
    SysCtrlRegs.PCLKCR0.bit.SPIAENCLK = 1;
    SysCtrlRegs.LOSPCP.all = 0x0002;
    // Enable FIFO reset bit only
    SpiaRegs.SPIFFTX.all=0x8000;
    // 8-bit character
    SpiaRegs.SPICCR.all = 0x0007;
    // Use internal SPICLK master mode and Talk mode
    SpiaRegs.SPICTL.all = 0x000E;
    // Use the slowest baud rate
    SpiaRegs.SPIBRR     = 0x007f;
    // Relinquish SPI-A from reset
    SpiaRegs.SPICCR.all = 0x0087;
    // Enable SPISIMO/SPISOMI/SPICLK pins
    // Enable pull-ups on SPISIMO/SPISOMI/SPICLK/SPISTE pins
    // GpioCtrlRegs.GPAPUD.bit.GPIO16 = 0;
    // GpioCtrlRegs.GPAPUD.bit.GPIO17 = 0;
    // GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;
    // GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;
    GpioCtrlRegs.GPAPUD.all &= 0xFFF0FFFF;
    // GpioCtrlRegs.GPAMUX2.bit.GPIO16 = 1;
    // GpioCtrlRegs.GPAMUX2.bit.GPIO17 = 1;
    // GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 1;
    GpioCtrlRegs.GPAMUX2.all |= 0x00000015;
    // SPI-A pins are asynch
    // GpioCtrlRegs.GPAQSEL2.bit.GPIO16 = 3;
    // GpioCtrlRegs.GPAQSEL2.bit.GPIO17 = 3;
    // GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 3;
    GpioCtrlRegs.GPAQSEL2.all |= 0x0000003F;
    // IOPORT as output pin instead of SPISTE
    GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0;
    GpioCtrlRegs.GPADIR.bit.GPIO19 = 1;
    // Chip enable - low
    GpioDataRegs.GPACLEAR.bit.GPIO19 = 1;
    EDIS;

   // 2. Enable EEPROM and send EEPROM Read Command
   SPIA_Transmit(0x0300);
   // 3. Send Starting Address for Serial EEPROM (16-bit - 0x0000,0000)
   //    or Serial Flash (24-bit - 0x0000,0000,0000)
   //    Then check for 0x08AA data header, else go to flash
   if(SPIA_SetAddress_KeyChk() != 0x08AA) return FLASH_ENTRY_POINT;
   // 4.Check for Clock speed change and reserved words
   SPIA_ReservedFn();
   // 5. Get point of entry address after load
   EntryAddr = GetLongData();
   // 6. Receive and copy one or more code sections to  destination addresses
   CopyData();
   // 7. Disable EEPROM chip enable - high
   //    Chip enable - high
   GpioDataRegs.GPASET.bit.GPIO19 = 1;

   return EntryAddr;
}

//#################################################
// Uint16 SPIA_SetAddress_KeyChk(void)
//-----------------------------------------------
// This routine sends either a 16-bit address to
// Serial EEPROM or a 24-bit address to Serial
// FLASH. It then fetches the 2 bytes that make
// up the key value  from the SPI-A port and
// puts them together to form a single
// 16-bit value.  It is assumed that the host is
// sending the data in the form MSB:LSB.
//-----------------------------------------------

Uint16 SPIA_SetAddress_KeyChk()
{
   Uint16 keyValue;
   // Transmit first byte of Serial Memory address
   SPIA_Transmit(0x0000);
   // Transmit second byte of  Serial Memory address
   SPIA_Transmit(0x0000);
  // Transmit third byte of  Serial Memory address (0x00) if using Serial Flash
  // or receive first byte of key value if using Serial EEPROM.
  keyValue = SPIA_Transmit(0x0000);
  // If previously received LSB of key value (Serial EEPROM), then fetch MSB of key value
   if (keyValue == 0x00AA)
   {
       keyValue |= (SPIA_Transmit(0x0000)<<8);
   }
   else
   {
   // Serial Flash is being used - keyValue will be received after 24-bit address in the next 2 bytes
   // Fetch Key Value LSB (after 24-bit addressing)
       keyValue = SPIA_Transmit(0x0000);
   // Fetch Key Value MSB (after 24-bit addressing)
       keyValue |= (SPIA_Transmit(0x0000)<<8);
   }
   return keyValue;
}


//#################################################
// Uint16 SPIA_Transmit(Uint16 cmdData)
//------------------------------------------------
// Send a byte/words through SPI transmit channel
//------------------------------------------------

inline Uint16 SPIA_Transmit(Uint16 cmdData)
{
    Uint16 recvData;
    // Send Read command/dummy word to EEPROM to fetch a byte
    SpiaRegs.SPITXBUF = cmdData;
    while( (SpiaRegs.SPISTS.bit.INT_FLAG) !=1);
    // Clear SPIINT flag and capture received byte
    recvData = SpiaRegs.SPIRXBUF;
    return recvData;
}

//#################################################
// void SPIA_ReservedFn(void)
//-------------------------------------------------
// This function reads 8 reserved words in the header.
// The first word has parameters for LOSPCP
// and SPIBRR register 0xMSB:LSB, LSB = is a three
// bit field for LOSPCP change MSB = is a 6bit field
// for SPIBRR register update
//
// If either byte is the default value of the register
// then no speed change occurs.  The default values
// are LOSPCP = 0x02 and SPIBRR = 0x7F
// The remaining reserved words are read and discarded
// and then returns to the main routine.
//-------------------------------------------------

inline void SPIA_ReservedFn()
{
    Uint16 speedData;
    Uint16 i;

    // update LOSPCP register
    speedData = SPIA_Transmit((Uint16)0x0000);
    EALLOW;
    SysCtrlRegs.LOSPCP.all = speedData;
    EDIS;
    asm("   RPT #0x0F ||NOP");

    // update SPIBRR register
    speedData = SPIA_Transmit((Uint16)0x0000);
    SpiaRegs.SPIBRR  = speedData;
    asm("   RPT #0x0F ||NOP");

    // Read and discard the next 7 reserved words.
    for(i = 1; i <= 7; i++)
    {
       SPIA_GetWordData();
    }
    return;
}

//#################################################
// Uint16 SPIA_GetWordData(void)
//-----------------------------------------------
// This routine fetches two bytes from the SPI-A
// port and puts them together to form a single
// 16-bit value.  It is assumed that the host is
// sending the data in the form MSB:LSB.
//-----------------------------------------------

Uint16 SPIA_GetWordData()
{
   Uint16 wordData;
   // Fetch the LSB
   wordData =  SPIA_Transmit(0x0000);
   // Fetch the MSB
   wordData |= (SPIA_Transmit(0x0000) << 8);
   return wordData;
}


