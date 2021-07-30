// TI File $Revision: /main/4 $
// Checkin $Date: March 8, 2011   15:18:38 $
//###########################################################################
//
// FILE:    SelectMode_Boot.c
//
// TITLE:   Boot Mode selection routines
//
// Functions:
//
//      Uint32 SelectBootMode(void)
//
// Notes:
//
//###########################################################################
// $TI Release: TMS320x2806x Boot ROM V1.0 $
// $Release Date: October 21, 2010 $
//###########################################################################

#include "Boot.h"

//  External functions referenced by this file
extern Uint32 SCI_Boot(void);
extern Uint32 SPI_Boot(void);
extern Uint32 Parallel_Boot(void);
extern Uint32 I2C_Boot(void);
extern Uint32 CAN_Boot(void);
extern void WatchDogEnable(void);
extern void WatchDogDisable(void);

// Functions in this file
void   WaitBoot(void);
Uint32 SelectBootMode(void);


Uint32 SelectBootMode()
{

  Uint32 EntryAddr;
  Uint16 BootMode;

  EALLOW;

  // Watchdog Service
  SysCtrlRegs.WDKEY = 0x0055;
  SysCtrlRegs.WDKEY = 0x00AA;

  // Before waking up the flash
  // set the POR to the minimum trip point
  // If the device was configured by the factory
  // this write will have no effect.

  *BORTRIM = 0x0100;

  // At reset we are in /4 mode.  Change to /1
  // Calibrate the ADC and internal OSCs
  SysCtrlRegs.PLLSTS.bit.DIVSEL = DIVSEL_BY_1;
  SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
  (*Device_cal)();
  SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 0;

  // Init two locations used by the flash API with 0x0000
  Flash_CPUScaleFactor = 0;
  Flash_CallbackPtr = 0;
  EDIS;


  // Read the password locations - this will unlock the
  // CSM only if the passwords are erased.  Otherwise it
  // will not have an effect.
  CsmPwl.PSWD0;
  CsmPwl.PSWD1;
  CsmPwl.PSWD2;
  CsmPwl.PSWD3;
  CsmPwl.PSWD4;
  CsmPwl.PSWD5;
  CsmPwl.PSWD6;
  CsmPwl.PSWD7;

  EALLOW;

  // If GPIO37/TDO is connected to JTAG,
  // read the EMU_KEY_LOC and EMU_BOOT_LOC
  // If the key is invalid, assign WAIT to the
  // boot mode.
  if(DevEmuRegs.DEVICECNF.bit.TRSTn == 1)
  {
     if(EmuKey != 0x55AA)
     {
        BootMode = WAIT_BOOT;
     }
     else BootMode = EmuBMode;
  }
  // GPIO37/TDO is not connected to JTAG,
  // read the state of GPIO34 and GPIO37 to determine
  // the boot mode.  Store the mode in the EMU_BOOT_LOC
  // and EMU_KEY_LOC for use later when GPIO37/TDO is
  // connected to JTAG.
  else
  {
     BootMode  = GpioDataRegs.GPBDAT.bit.GPIO37 << 1;
     BootMode |= GpioDataRegs.GPBDAT.bit.GPIO34;
     EmuBMode = BootMode;
     EmuKey = 0x55AA;

  }

  EDIS;

  if(BootMode == WAIT_BOOT) WaitBoot();

  WatchDogDisable();
  if(BootMode == GET_BOOT)
  {
          BootMode = (*Get_mode)();
  }

  if(BootMode == FLASH_BOOT) EntryAddr = FLASH_ENTRY_POINT;
  else if(BootMode == OTP_BOOT) EntryAddr = OTP_ENTRY_POINT;
  else if(BootMode == RAM_BOOT) EntryAddr = RAM_ENTRY_POINT;
  else if(BootMode == SCI_BOOT) EntryAddr = SCI_Boot();
  else if(BootMode == SPI_BOOT) EntryAddr = SPI_Boot();
  else if(BootMode == I2C_BOOT) EntryAddr = I2C_Boot();
  else if(BootMode == PARALLEL_BOOT) EntryAddr = Parallel_Boot();
  else if(BootMode == CAN_BOOT) EntryAddr = CAN_Boot();
  else if(DevEmuRegs.DEVICECNF.bit.TRSTn == 0)
  {
     EntryAddr = FLASH_ENTRY_POINT;
  }
  else WaitBoot();

  // In Boot-to-Flash mode:
  // If device in 32-pin package and content at Flash Entry Point
  // = 0xFFFF (fresh, unprogrammed device), boot via Parallel I/O.
  // Otherwise boot to Flash Entry Point.

  WatchDogEnable();
  return EntryAddr;

}

void WaitBoot(void)
{
   WatchDogEnable();
   for(;;)
   {
      // If the emulator stops here
      // a) change EMU_KEY to 0x55AA
      // b) write the appropriate boot mode to EMU_BMODE
      // c) perform a debugger reset, and run
      asm("   ESTOP0");
   }
}

