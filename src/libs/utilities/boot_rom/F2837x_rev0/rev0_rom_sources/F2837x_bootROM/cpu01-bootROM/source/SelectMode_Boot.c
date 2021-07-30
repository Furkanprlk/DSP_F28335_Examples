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
// $TI Release: F2837x Boot ROM Version 0 $
// $Release Date: Oct 1, 2013 $
//###########################################################################

#include "c1_bootrom.h"

Uint16 SelectBootMode(void);

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
         //in EMUBOOT MODE we don't decode boot pins by default
         //0x82 is to emulate bootmode GPIO via EmuBmode locations
         //user can use this feature before programming the pin config in OTP
         if(((EmuKey & 0xFF00) >> 8) == EMULATE_BOOTPIN_MODE)
        {
            BootMode = c1brom_decode_bootpins(EmuBMode);
        }
        else if(((EmuKey & 0xFF00) >> 8) == EMULATE_TRUE_BOOT)    //0xFF is emulate TRUEBOOT mode)
        {
            BootMode = c1brom_decode_bootpins(c1brom_read_otp_bootpinconfig());
        }
        else
        {
            BootMode = ((EmuKey & 0xFF00) >> 8); //no need to evaluate in EMUMODE
        }
     }
  }
  else
  {

      BootMode = c1brom_decode_bootpins(c1brom_read_otp_bootpinconfig());
      EmuKey = ((BootMode << 8) | 0x5A);
  }

  EDIS;

//  sysctl_wdog_disable();
  if(BootMode == GET_BOOT)
  {
      BootMode = c1brom_read_otp_bootmode();
  }

  return BootMode;

}
