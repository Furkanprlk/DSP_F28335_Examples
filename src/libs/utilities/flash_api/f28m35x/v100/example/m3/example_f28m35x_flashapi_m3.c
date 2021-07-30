//###########################################################################
// FILE:   flash_m3.c
// TITLE:  flash API example.
//###########################################################################

#include <string.h>

#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_nvic.h"
#include "inc/hw_types.h"
#include "inc/hw_sysctl.h"
#include "inc/hw_ipc.h"
#include "inc/hw_flash.h"
#include "driverlib/debug.h"
#include "driverlib/ipc.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "driverlib/flash.h"
#include "driverlib/device.h"
#include "driverlib/dcsm.h"
#include "F28M35x_FlashAPIexample_Dual_m3.h"

//*****************************************************************************
// FILE Flash API include file
//*****************************************************************************
#include "F021_CONCERTO_Cortex.h"

//*****************************************************************************
//! \addtogroup dual_example_list
//! <h1>Flash (flash)</h1>
//!
//! This example illustrates the usage of Flash API to erase and program the
//! flash.
//! Flash API functions are executed from RAM.  See linker command file for
//! details on loading the Flash API in Flash and executing it from RAM.
//!
//! To use the Flash API
//! 1.  If passwords are programmed in Flash, users are supposed to unlock the
//!     flash using the DCSMUnlockZone1CSM and DCSMUnlockZone2CSM functions with
//!     appropriate key if executing Flash API from unsecured memory.  See
//!     security chapter in TRM for details
//! 2.  Users should configure the desired system frequency
//! 3.  Users should configure waitstates for FSM operations based on desired
//!     system frequency using the formula: RWAIT = (SYSCLK/(2*24MHz))-1
//! 4.  Users should include F021_CONCERTO_Cortex.h in the application
//! 5.  Users should include Flash API library to the project
//! 6.  Watchdog is disabled in this project.  If users want to enable and
//!     service the watchdog, users have to include the watchdog service code
//!     in Fapi_UserDefinedFunctions.c file
//! 7.  This example uses F28M35x_FlashAPIexample_Dual_m3.h file
//!
//! Steps to convert code to run out of Flash instead of RAM are as follows: \n
//! 1. Change the command linker file to Flash linker file (i.e. F28M35x.cmd) \n
//! 2. Make sure initialized sections are mapped to Flash. \n
//! 3. Make sure ResetISR() or branch to starting point of your application is
//! mapped to "BOOT_TO_FLASH" address of 0x00200030. (0x13FFF0 on C28) \n
//! 4. Add security files /driverlib/dcsm_z1_secvalues.asm and/or
//! driverlib/dcsm_z2_secvalues.asm to program Z1 and Z2 security values. \n
//! 5. For best performance from the flash, modify the waitstates
//! and enable the flash pipeline as shown in this example. \n
//! Note: any code that manipulates the flash waitstate and pipeline
//! control must be run from RAM. Thus these functions are located
//! in their own memory section called ramfuncs. \n
//! 6. Code that must execute faster than Flash allows can also be
//! run from RAM (i.e. interrupt service routines). \n
//! 7. To copy code from Flash to RAM during runtime, set up .cmd file
//! appropriately and call MemCopy() function (in memcopy.c in utils) \n
//! 8. If using the IntRegister()/IntUnRegister() driverlib functions, replace
//! with IntRAMRegister()/IntRAMUnregister() functions which copy the Flash
//! interrupt vector table into RAM .vtable location. \n
//
//*****************************************************************************

//Lengths of sectors
#define Bzero_16KSector_u32length   0x1000
#define Bzero_64KSector_u32length   0x4000

//Data/Program Buffer used for testing the flash API functions
#define  BYTES_IN_FLASH_BUFFER    0xFF   // Programming data buffer, bytes
uint8    Buffer[BYTES_IN_FLASH_BUFFER];

//*****************************************************************************
// Flags that contain the current value of the interrupt indicator as displayed
// on the CSTN display.
//*****************************************************************************
unsigned long g_ulFlags;

// Structure CSMPSWKEY is defined in dcsm.h
//Users should modify this Zone1 key if the password locations in Flash are
// not all 0xFFFFFFFFs
CSMPSWDKEY Zone1KEY = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
//Users should modify this Zone2 key if the password locations in Flash are
// not all 0xFFFFFFFFs
CSMPSWDKEY Zone2KEY = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};

// These are defined by the linker (see device linker command file)
extern unsigned long RamfuncsLoadStart;
extern unsigned long RamfuncsRunStart;
extern unsigned long RamfuncsLoadSize;

//*****************************************************************************
// The error routine that is called if the driver library encounters an error.
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, unsigned long ulLine)
{
}

#endif

//******************************************************************************
// For this example, if an error is found just stop here
//******************************************************************************
#pragma CODE_SECTION(Example_Error,"ramfuncs");
void Example_Error(Fapi_StatusType status)
{
    //  Error code will be in the status parameter
        for(;;);
}


//******************************************************************************
//  For this example, once we are done just stop here
//******************************************************************************
#pragma CODE_SECTION(Example_Done,"ramfuncs");
void Example_Done(void)
{
    for(;;);
}

//******************************************************************************
//  Example_CallFlashAPI
//
//  This function will interface to the flash API.
//  Flash API functions used in this function are executed from RAM
//******************************************************************************

void Example_CallFlashAPI(void)
{
    uint32 u32Index = 0;
    uint16 i = 0;

    Fapi_StatusType            oReturnCheck;
    Fapi_LibraryInfoType       oLibInfo;
    Fapi_FlashStatusType       oFlashStatus;
    Fapi_FlashBankSectorsType  oFlashBankSectors;
    Fapi_FlashStatusWordType   oFlashStatusWord;

    // This function is required to initialize the Flash API based on System
    // frequency before any other Flash API operation can be performed
    #if CPU_FRQ_100MHZ
    oReturnCheck = Fapi_initializeAPI(F021_CPU0_BASE_ADDRESS, 100);
    #endif

    #if CPU_FRQ_75MHZ
    oReturnCheck = Fapi_initializeAPI(F021_CPU0_BASE_ADDRESS, 75);
    #endif

    #if CPU_FRQ_60MHZ
    oReturnCheck = Fapi_initializeAPI(F021_CPU0_BASE_ADDRESS, 60);
    #endif

    if(oReturnCheck |= Fapi_Status_Success)
    {
        //Check Flash API documentation for possible errors
        Example_Error(oReturnCheck);
    }

    // Fapi_getLibraryInfo function can be used to get the information
    // specific to the compiled version of the API library
    oLibInfo = Fapi_getLibraryInfo();

    // Before performing FSM operations, set the waitstates for FSM
    // operations calculated using RWAIT = (SYSCLK/(2*24MHz))-1
    // If RWAIT results in a fractional value, round it up to the nearest
    // integer.
    // Please note that RWAIT for read operation should be calculated
    // differently.  See Internal memory guide section in TRM
    #if CPU_FRQ_100MHZ
    HWREG(FLASH_CONFIG_BASE + FLASHCTRL_O_FRDCNTL) = (2 << FLASHCTRL_FRDCNTL_RWAIT_S);
    #endif

    #if CPU_FRQ_75MHZ
    HWREG(FLASH_CONFIG_BASE + FLASHCTRL_O_FRDCNTL) = (1 << FLASHCTRL_FRDCNTL_RWAIT_S);
    #endif

    #if CPU_FRQ_60MHZ
    HWREG(FLASH_CONFIG_BASE + FLASHCTRL_O_FRDCNTL) = (1 << FLASHCTRL_FRDCNTL_RWAIT_S);
    #endif

    // Fapi_setActiveFlashBank function sets the Flash bank and FMC
    // for further Flash operations to be performed on the bank
    oReturnCheck = Fapi_setActiveFlashBank(Fapi_FlashBank0);
    if(oReturnCheck |= Fapi_Status_Success)
    {
        // Check Flash API documentation for possible errors
        Example_Error(oReturnCheck);
    }

    // Fapi_getBankSectors function returns the bank starting address,
    // number of sectors, sector sizes, and bank technology type
    // Above information is returned in a structure oFlashBankSectors of type
    // Fapi_FlashBankSectorsType
    oReturnCheck = Fapi_getBankSectors(Fapi_FlashBank0,&oFlashBankSectors);
    if(oReturnCheck |= Fapi_Status_Success)
    {
        // Check Flash API documentation for possible errors
        Example_Error(oReturnCheck);
    }

    // Erase Sector L
    // Sector N has the example code so leave it programmed
    oReturnCheck = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
                   (uint32 *)Bzero_SectorL_start);

    // Wait until FSM is done with erase sector operation
    while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}

    // Verify that Sector L is erased.  The Erase step itself does a verify
    // as it goes.  This verify is a 2nd verification that can be done.
    oReturnCheck = Fapi_doBlankCheck((uint32 *)Bzero_SectorL_start,
                   Bzero_16KSector_u32length,
                   &oFlashStatusWord);
    if(oReturnCheck |= Fapi_Status_Success)
    {
        //Check Flash API documentation for possible errors
        //If Erase command fails, use Fapi_getFsmStatus() function to get
        // the FMSTAT register contents
        //to see if any of the EV bit, ESUSP bit, CSTAT bit or VOLTSTAT
        //bit is set (Refer to API documentation for more details)
        Example_Error(oReturnCheck);
    }

    // Erase Sector K
    // Sector N has the example code so leave it programmed
    oReturnCheck = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
                   (uint32 *)Bzero_SectorK_start);

    // Wait until FSM is done with erase sector operation
    while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}

    // Verify that SectorK is erased.  The Erase step itself does a verify as
    // it goes.  This verify is a 2nd verification that can be done.
    oReturnCheck = Fapi_doBlankCheck((uint32 *)Bzero_SectorK_start,
                   Bzero_16KSector_u32length,
                   &oFlashStatusWord);

    if(oReturnCheck |= Fapi_Status_Success)
    {
        // Check Flash API documentation for possible errors
        // If Erase command fails, use Fapi_getFsmStatus() function to get
        // the FMSTAT register contents
        // to see if any of the EV bit, ESUSP bit, CSTAT bit or VOLTSTAT bit is
        // set (Refer to API documentation for more details)
        Example_Error(oReturnCheck);
    }		

    // A data buffer of max 16 bytes can be supplied to the program function.
    // Each word is programmed until the whole buffer is programmed or a
    // problem is found.
    // However to program more a buffer that has more than 16 bytes,
    // program function can be called in a loop to program 16 bytes for each loop
    // iteration until the whole buffer is programmed


    // Example: Program 0xFF bytes in Flash Sector L along with auto generated ECC

    // In this case just fill a buffer with data to program into the flash.
    for(i=0;i<=BYTES_IN_FLASH_BUFFER;i++)
    {
        Buffer[i] = i;
    }


    for(i=0, u32Index = Bzero_SectorL_start;
       (u32Index < (Bzero_SectorL_start + BYTES_IN_FLASH_BUFFER))
       && (oReturnCheck == Fapi_Status_Success); i+= 16, u32Index+= 16)
    {
        oReturnCheck = Fapi_issueProgrammingCommand((uint32 *)u32Index,Buffer+i,
                       16,
                       0,
                       0,
                       Fapi_AutoEccGeneration);

        while(Fapi_checkFsmForReady() == Fapi_Status_FsmBusy);

        if(oReturnCheck |= Fapi_Status_Success)
        {
        // Check Flash API documentation for possible errors
        Example_Error(oReturnCheck);
        }

        // Read FMSTAT register contents to know the status of FSM after
        // program command for any debug
        oFlashStatus = Fapi_getFsmStatus();

        // Verify the values programmed.  The Program step itself does a verify
        // as it goes.  This verify is a 2nd verification that can be done.
        oReturnCheck = Fapi_doVerifyByByte((uint8 *)u32Index,
                       16,
                       Buffer+i,
                       &oFlashStatusWord);

        if(oReturnCheck |= Fapi_Status_Success)
        {
        // Check Flash API documentation for possible errors
        Example_Error(oReturnCheck);
        }
    }

    // Example:  Program 0xFF bytes in Flash Sector K with out ECC
    // Disable ECC so that error is not generated when reading Flash
    // contents without ECC
    HWREG(FLASH_ERROR_BASE + FLASHERR_O_ECC_ENABLE) = 0x0;

    for(i=0, u32Index = Bzero_SectorK_start;
       (u32Index < (Bzero_SectorK_start + BYTES_IN_FLASH_BUFFER))
       && (oReturnCheck == Fapi_Status_Success); i+= 16, u32Index+= 16)
    {
        oReturnCheck = Fapi_issueProgrammingCommand((uint32 *)u32Index,
                       Buffer+i,
                       16,
                       0,
                       0,
                       Fapi_DataOnly);

        while(Fapi_checkFsmForReady() == Fapi_Status_FsmBusy);

        if(oReturnCheck |= Fapi_Status_Success)
        {
        //Check Flash API documentation for possible errors
        Example_Error(oReturnCheck);
        }

        //Read FMSTAT register contents to know the status of FSM after
        // program command for any debug
        oFlashStatus = Fapi_getFsmStatus();

        // Verify the values programmed.  The Program step itself does a verify
        // as it goes.  This verify is a 2nd verification that can be done.
        oReturnCheck = Fapi_doVerifyByByte((uint8 *)u32Index,
                       16,
                       Buffer+i,
                       &oFlashStatusWord);

        if(oReturnCheck |= Fapi_Status_Success)
        {

            //Check Flash API documentation for possible errors
            Example_Error(oReturnCheck);

        }
    }	

    // Erase Sector L
    // Sector N has the example code so leave it programmed
    oReturnCheck = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
                   (uint32 *)Bzero_SectorL_start);
    // Wait until FSM is done with erase sector operation
    while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}
    // Verify that Sector L is erased.  The Erase step itself does a verify as
    // it goes.  This verify is a 2nd verification that can be done.
    oReturnCheck = Fapi_doBlankCheck((uint32 *)Bzero_SectorL_start,
                   Bzero_16KSector_u32length,
                   &oFlashStatusWord);
    if(oReturnCheck |= Fapi_Status_Success)
    {
        // Check Flash API documentation for possible errors
        // If Erase command fails, use Fapi_getFsmStatus() function
        // to get the FMSTAT register contents to see if any of the EV bit,
        // ESUSP bit, CSTAT bit or VOLTSTAT bit is set (Refer to API
        // documentation for more details)
        Example_Error(oReturnCheck);
    }

    //Erase Sector K
    //Sector N has the example code so leave it programmed
    oReturnCheck = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
                   (uint32 *)Bzero_SectorK_start);
    //Wait until FSM is done with erase sector operation
    while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}
    // Verify that SectorK is erased.  The Erase step itself does a verify as
    // it goes.  This verify is a 2nd verification that can be done.
    oReturnCheck = Fapi_doBlankCheck((uint32 *)Bzero_SectorK_start,
                   Bzero_16KSector_u32length,
                   &oFlashStatusWord);
    if(oReturnCheck |= Fapi_Status_Success)
    {
        // Check Flash API documentation for possible errors
        // If Erase command fails, use Fapi_getFsmStatus() function to get the
        // FMSTAT register contents
        // to see if any of the EV bit, ESUSP bit, CSTAT bit or VOLTSTAT bit
        // is set (Refer to API documentation for more details)
        Example_Error(oReturnCheck);
    }		

    // Enable ECC
    HWREG(FLASH_ERROR_BASE + FLASHERR_O_ECC_ENABLE) = 0xA;	

    // Leave control over pump
    FlashLeavePump();

    // Example is done here
    Example_Done();

}


//*****************************************************************************************
// This is an example code demonstrating F021 Flash API usage.  This code is all in Flash.
//*****************************************************************************************
int
main(void)
{
    // Disable Protection
    HWREG(SYSCTL_MWRALLOW) =  0xA5A5A5A5;

    // Setup main clock tree for 75MHz - M3 and 150MHz - C28x
    SysCtlClockConfigSet(SYSCTL_SYSDIV_1 | SYSCTL_M3SSDIV_2 | SYSCTL_USE_PLL |
                             (SYSCTL_SPLLIMULT_M & 0x0F));


    //  Unlock Zone1 and Zone2 CSM.
    //
    //  If the API functions are going to run in unsecured RAM
    //  then the CSM must be unlocked in order for the flash
    //  API functions to access the flash.
    //  If the flash API functions are executed from secure memory
    //  then this step is not required.

    DCSMUnlockZone1CSM (&Zone1KEY);
    DCSMUnlockZone2CSM (&Zone2KEY);

    //  Copy API Functions and required user interface functions to RAM.
    //
    //  The flash API functions MUST be run out of RAM memory.
    //  If the Flash API is already in RAM then this step
    //  can be skipped.
    //  DO NOT run the Flash API from Flash

    memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

    //  Call Flash Initialization to setup flash waitstates
    //  This function must reside in RAM
    FlashInit();

    //  Send boot command to allow the C28 application to begin execution
    //  IPC command is sent to C28 while C28 boot ROM is executing and in IDLE state.
    //  During debug, if not executing C28 code via boot ROM, comment out the below
    //  line.
    IPCMtoCBootControlSystem(CBROM_MTOC_BOOTMODE_BOOT_FROM_FLASH);

    // Disable clock supply for the watchdog modules
    SysCtlPeripheralDisable(SYSCTL_PERIPH_WDOG1);
    SysCtlPeripheralDisable(SYSCTL_PERIPH_WDOG0);

    // Gain flash pump semaphore
    // This function must reside in RAM
    FlashGainPump();

    //  Jump to RAM and call the Flash API functions
    Example_CallFlashAPI();

}





