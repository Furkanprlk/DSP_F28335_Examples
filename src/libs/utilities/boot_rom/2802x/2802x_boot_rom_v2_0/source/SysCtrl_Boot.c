// TI File $Revision: /main/3 $
// Checkin $Date: December 9, 2009   17:52:28 $
//###########################################################################
//
// FILE:    SysCtrl_Boot.c
//
// TITLE:   Boot Rom System Control Routines
//
// Functions:
//
//     void WatchDogDisable(void)
//     void WatchDogEnable(void)
//
// Notes:
//
//###########################################################################
// $TI Release: 2802x Boot ROM V2.00 $
// $Release Date: December 10, 2009 $
//###########################################################################


#include "Boot.h"

//---------------------------------------------------------------
// This module disables the watchdog timer.
//---------------------------------------------------------------

void  WatchDogDisable()
{
   EALLOW;
   SysCtrlRegs.WDCR = 0x0068;               // Disable watchdog module
   EDIS;
}

//---------------------------------------------------------------
// This module enables the watchdog timer.
//---------------------------------------------------------------

void  WatchDogEnable()
{
   EALLOW;
   SysCtrlRegs.WDCR = 0x0028;               // Enable watchdog module
   SysCtrlRegs.WDKEY = 0x55;                // Clear the WD counter
   SysCtrlRegs.WDKEY = 0xAA;
   EDIS;
}

//---------------------------------------------------------------
// This module services the watchdog timer.
//---------------------------------------------------------------
void WatchDogService(void)
{
    EALLOW;
    SysCtrlRegs.WDKEY = 0x0055;
    SysCtrlRegs.WDKEY = 0x00AA;
    EDIS;
}




// EOF --------

