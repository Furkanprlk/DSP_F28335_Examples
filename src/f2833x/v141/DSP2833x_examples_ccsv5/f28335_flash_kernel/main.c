//###########################################################################
// Description:
//! \addtogroup f2833x_example_list
//! <h1>F28335 Flash Kernel (f28335_flash_kernel)</h1>
//!
//!   This example is for use with the SerialLoader2000 utility.  This
//!   application is intended to be loaded into the device's RAM via the
//!   SCI boot mode.  After successfully loaded this program implements a
//!   modified version of the SCI boot protocol that allows a user application
//!   to be programmed into flash
//
//###########################################################################
// $TI Release: F2833x/F2823x Header Files and Peripheral Examples V141 $
// $Release Date: November  6, 2015 $
// $Copyright: Copyright (C) 2007-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
extern Uint32 SCI_Boot();

void (*ApplicationPtr) (void);

Uint32 main(void)
{
	//GPIO and SCI are still setup from Sci_Boot()
	//Setup sysctl and pll
   DisableDog();
   InitPll(DSP28_PLLCR,DSP28_DIVSEL);

   DELAY_US(100);

   return SCI_Boot();
}
