/**********************************************************************
* File: Watchdog.c 
* Devices: TMS320F2833x
* Author: Technical Training Organization (TTO), Texas Instruments
* History:
*   07/15/08 - original
**********************************************************************/

#include "Lab.h"						// Main include file


/**********************************************************************
* Function: InitWatchdog()
*
* Description: Initializes Watchdog Timer for C28x workshop labs
**********************************************************************/
void InitWatchdog(void)
{
	asm(" EALLOW");						// Enable EALLOW protected register access

//--- Disable the Watchdog Timer
	SysCtrlRegs.WDCR = 0x00E8;
// bit 15-8      0's:    reserved
// bit 7         1:      WDFLAG, write 1 to clear
// bit 6         1:      WDDIS, 1=disable WD
// bit 5-3       101:    WDCHK, WD check bits, always write as 101b
// bit 2-0       000:    WDPS, WD prescale bits, 000: WDCLK=OSCCLK/512/1

//--- System and Control Register
	SysCtrlRegs.SCSR = 0x0000;
// bit 15-3      0's:    reserved
// bit 2         0:      WDINTS, WD interrupt status bit (read-only)
// bit 1         0:      WDENINT, 0=WD causes reset, 1=WD causes WDINT
// bit 0         0:      WDOVERRIDE, write 1 to disable disabling of the WD (clear-only)

	asm(" EDIS");						// Disable EALLOW protected register access

//--- Enable the Watchdog interrupt
	PieCtrlRegs.PIEIER1.bit.INTx8 = 1;	// Enable WAKEINT (LPM/WD) in PIE group #1
	IER |= 0x0001;						// Enable INT1 in IER to enable PIE group 1

} // end of InitWatchdog()


//--- end of file -----------------------------------------------------
