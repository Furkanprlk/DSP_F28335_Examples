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

#include "c1_bootrom.h"

Uint16 SelectBootMode(void);

Uint16 OverlaySciBootWithUsbBoot(Uint16 mode)
{
    Uint32 EntryAddr;

    EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_14;  //
    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }

    //if bit 12 of PARTIDL == 1 , then boot mode pin config (GPIO 71 ==0, GPIO4 == 1) == 1 selects SCI BOOT
    // if bit 12 of PARTIDL == 0, then boot mode pin config (GPIO 71 ==0, GPIO4 == 1) == 0 selects USB BOOT
    if((DevCfgRegs.PARTIDL & 0x00001000))
    {
        //this is an SCI BOOT PART (SLOW SPEED BOOT) - do nothing
        return  mode;
    }
    //if here means this is a HIGH SPEED BOOT PART- USB BOOT needs to be supported
    //if decoded boot mode is not SCI, then return - we don;t care
    if(mode != SCI_BOOT)
    {
        return mode;
    }

    //here means this is a HIGHSPEED BOOT PART and selected boot mode is SCIBOOT
    //so Overlay with USBBOOT
    return USB_BOOT;
}


Uint16 SelectBootMode()
{
  Uint16 BootModeLocal;

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
        BootModeLocal = WAIT_BOOT;
     }
     else
     {
         //in EMUBOOT MODE we don't decode boot pins by default
         //0x82 is to emulate bootmode GPIO via EmuBmode locations
         //user can use this feature before programming the pin config in OTP
         if(((EmuKey & 0xFF00) >> 8) == EMULATE_BOOTPIN_MODE)
        {
            BootModeLocal = c1brom_decode_bootpins(EmuBMode);
            BootModeLocal = OverlaySciBootWithUsbBoot(BootModeLocal);
        }
        else if(((EmuKey & 0xFF00) >> 8) == EMULATE_TRUE_BOOT)    //0xFF is emulate TRUEBOOT mode)
        {
            BootModeLocal = c1brom_decode_bootpins(c1brom_read_otp_bootpinconfig());
            BootModeLocal = OverlaySciBootWithUsbBoot(BootModeLocal);
        }
        else
        {
            BootModeLocal = ((EmuKey & 0xFF00) >> 8); //no need to evaluate in EMUMODE
        }
     }
  }
  else
  {

      BootModeLocal = c1brom_decode_bootpins(c1brom_read_otp_bootpinconfig());
      BootModeLocal = OverlaySciBootWithUsbBoot(BootModeLocal);
      EmuKey = ((BootModeLocal << 8) | 0x5A);
  }

  EDIS;

//  sysctl_wdog_disable();
  if(BootModeLocal == GET_BOOT)
  {
      BootModeLocal = c1brom_read_otp_bootmode();
  }

  return BootModeLocal;

}
