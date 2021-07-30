// TI File $Revision: /main/1 $
// Checkin $Date: August 14, 2012   12:51:30 $
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
// $TI Release: F2837x Boot ROM V1.0 $
// $Release Date: October 2013 $
//###########################################################################

#include "c2_bootrom.h"

//  External functions referenced by this file
extern Uint32 SCI_Boot(void);
extern Uint32 SPI_Boot(void);
extern Uint32 Parallel_Boot(void);
extern Uint32 I2C_Boot(void);
extern Uint32 CAN_Boot(void);
extern void WatchDogEnable(void);
extern void WatchDogDisable(void);

// Functions in this file
//void   WaitBoot(void);
Uint16 SelectBootMode(void);
//void DeviceConfigure(void);

Uint16 SelectBootMode()
{
  Uint16 BootMode;

//  EALLOW;
//
//  // Watchdog Service
//  SysCtrlRegs.WDKEY = 0x0055;
//  SysCtrlRegs.WDKEY = 0x00AA;



  EALLOW;

  // If GPIO37/TDO is connected to JTAG,
  // read the EMU_KEY_LOC and EMU_BOOT_LOC
  // If the key is invalid, assign WAIT to the
  // boot mode.
  if(CpuSysRegs.RESC.bit.TRSTn_pin_status == 1)
  {
      //EMUKEY.bits7:0 = KEY
      //EMUKEY.bits15:8 = BMODE
      //EMUBMODE.bits7:0 = BOOTPIN0
      //EMUBMODE.bits15:8 = BOOTPIN1
     if((EmuKey & 0xFF) != 0x5A)
     {
         //bad key
        BootMode = WAIT_BOOT;
     }
     else
     {
         if(((EmuKey & 0xFF00) >> 8) == EMULATE_TRUE_BOOT)
         {
             BootMode = c2brom_read_otp_bootmode();
             BootMode = c2brom_evaluate_bootmode (BootMode, STAND_ALONE_BOOT_TYPE);
         }
         else if (((EmuKey & 0xFF00) >> 8) == GET_BOOT)
         {
             BootMode = c2brom_read_otp_bootmode();
             //since we allow only FLASHBOOT mode from OTP, just look for that
             //this mode is same as EMULATE TRUE BOOT on CPU2
             BootMode = c2brom_evaluate_bootmode (BootMode, EMU_BOOT_TYPE);
         }
         else
         {
            BootMode = ((EmuKey & 0xFF00) >> 8); //no need to evaluate in EMUMODE
         }
      }
  }
  else
  {

      BootMode = c2brom_read_otp_bootmode();
      BootMode = c2brom_evaluate_bootmode (BootMode, STAND_ALONE_BOOT_TYPE);

      EmuKey = ((BootMode << 8) | 0x5A);
  }

  EDIS;

  return BootMode;
}


