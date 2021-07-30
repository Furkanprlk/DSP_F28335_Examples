// TI File $Revision: /main/1 $
// Checkin $Date: January 22, 2009   16:48:34 $
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
// $TI Release: TMS320x2803x Boot ROM V1.0 $
// $Release Date: January 22, 2009 $
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
  if (DevEmuRegs.DEVICECNF.bit.PINOUTSELSTS==0) {  // If 32-pin package:

  	  // GPIO13-17, 20-27 - inputs with pull-ups disabled */
	  GpioCtrlRegs.GPAPUD.all &= 0xF00C1FFF;  // Enable pull-ups on all unbonded pins.
	  GpioCtrlRegs.GPADIR.all &= 0xF00C1FFF;  // Unused pins configured as inputs.
      // GPIO32-33, 39-44 - inputs with pull-ups disabled */
	  GpioCtrlRegs.GPBPUD.all &= 0xFFFFE07C;  // Enable pull-ups on all unbonded pins
      GpioCtrlRegs.GPBDIR.all &= 0xFFFFE07C;  // Unused pins configured as inputs.
	  // AIO2, 10 - outputs driving low
	  GpioCtrlRegs.AIOMUX1.all &= 0xFFCFFFCF; // Configured as Digital IO
	  GpioCtrlRegs.AIODIR.all |= 0x0404;      // Unused pins configured as outputs (=1)
	  GpioDataRegs.AIODAT.all &= 0xFBFB;      // Unused pins driven low

  }


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
	 if (DevEmuRegs.DEVICECNF.bit.PINOUTSELSTS==0) {   // If 32-pin package
         BootMode |= 0x0001;  // Set BootMode bit corresponding to GPIO34 to 1.
	 }

     EmuBMode = BootMode;
     EmuKey = 0x55AA;

  }

  EDIS;

  if(BootMode == WAIT_BOOT) WaitBoot();

  WatchDogDisable();
  if(BootMode == GET_BOOT)
  {
      // If 32-pin package AND ROM device, boot to ROM 
	  // Otherwise call Get_mode function
      if ((DevEmuRegs.DEVICECNF.bit.PINOUTSELSTS==0)&&
          (DevEmuRegs.CLASSID.bit.PARTTYPE == 0x00FF))
	  {
          EntryAddr = ROM_ENTRY_POINT;
		  WatchDogEnable();
          return EntryAddr;
      } else
      {
          BootMode = (*Get_mode)();
	  }
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

  if (EntryAddr == FLASH_ENTRY_POINT) {
      if ((DevEmuRegs.DEVICECNF.bit.PINOUTSELSTS==0)&&
          (*(Uint16 *)FLASH_ENTRY_POINT == 0xFFFF))
	  {
	      EntryAddr = Parallel_Boot();
	  }
  }

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

