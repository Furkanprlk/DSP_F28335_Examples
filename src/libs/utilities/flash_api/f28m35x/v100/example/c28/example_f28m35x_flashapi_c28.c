//###########################################################################
//
// FILE:    flash_c28.c
//
//!    This example runs the Flash API usage example from flash by copying
//!    the API into RAM
//!
//    1) Build the project
//    2) Flash the .out file into the device.
//    3) Set the hardware jumpers to boot to Flash
//
//   Steps that were taken to convert the example from RAM
//    to Flash execution:
//
//    - Change the linker cmd file to reflect the flash memory map.
//    - Make sure any initialized sections are mapped to Flash.
//    - Make sure there is a branch instruction from the entry to Flash
//      at 0x13FFF0 to the beginning of code execution. This example
//      uses the DSP28x_CodeStartBranch.asm file to accomplish this.
//    - Set boot mode Jumpers to "boot to Flash"
//    - For best performance from the flash, modify the waitstates
//      and enable the flash pipeline as shown in this example.
//      Note: any code that manipulates the flash waitstate and pipeline
//      control must be run from RAM. Thus these functions are located
//      in their own memory section called ramfuncs.
//
//###########################################################################


#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

#include <string.h>

//Include Flash API example header file
#include "F28M35x_FlashAPIexample_Dual_C28x.h"

//*****************************************************************************
// FILE Flash API include file
//*****************************************************************************
#include "F021_Concerto_C28x.h"

//Data/Program Buffer used for testing the flash API functions
#define  WORDS_IN_FLASH_BUFFER    0xFF  // Programming data buffer, words
uint16   Buffer[WORDS_IN_FLASH_BUFFER];
uint32   *Buffer32 = (uint32 *)Buffer;

//*****************************************************************************
// Prototype of the functions used in this example
//*****************************************************************************
void Example_Error(Fapi_StatusType status);
void Example_Done(void);
void Example_CallFlashAPI(void);

//*****************************************************************************
// This is an example code demonstrating F021 Flash API usage.
// This code is in Flash
//*****************************************************************************
void main(void)
{
// Step 1. Initialize System Control:
// Enable Peripheral Clocks
// This example function is found in the F28M35x_SysCtrl.c file.
    InitSysCtrl();

//  Unlock CSM
//
//  If the API functions are going to run in unsecured RAM
//  then the CSM must be unlocked in order for the flash
//  API functions to access the flash.
//  If the flash API functions are executed from secure memory
//  then this step is not required.
    CsmUnlock();

// Step 2. Initalize GPIO:
// This example function is found in the F28M35x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
    DINT;

// Initialize the PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the F28M35x_PieCtrl.c file.
    InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2802x_DefaultIsr.c.
// This function is found in F28M35x_PieVect.c.
    InitPieVectTable();

// Copy time critical code and Flash setup code to RAM
// This includes InitFlash(), Flash API functions and any functions that are
// assigned to ramfuncs section.
// The  RamfuncsLoadStart, RamfuncsLoadEnd, and RamfuncsRunStart
// symbols are created by the linker. Refer to the device .cmd file.

   memcpy(&RamfuncsRunStart, &RamfuncsLoadStart, (size_t)&RamfuncsLoadSize);

// Call Flash Initialization to setup flash waitstates
// This function must reside in RAM
    InitFlash();

//  Gain pump semaphore
    FlashGainPump();

//  Jump to RAM and call the Flash API functions
    Example_CallFlashAPI();

}

//*****************************************************************************
//  Example_CallFlashAPI
//
//  This function will interface to the flash API.
//  Flash API functions used in this function are executed from RAM
//*****************************************************************************

void Example_CallFlashAPI(void)
{
    uint32 u32Index = 0;
    uint16 i = 0;

    Fapi_StatusType            oReturnCheck;
    Fapi_LibraryInfoType       oLibInfo;
    Fapi_FlashStatusType       oFlashStatus;
    Fapi_FlashBankSectorsType  oFlashBankSectors;
    Fapi_FlashStatusWordType   oFlashStatusWord;

    // Disable ECC.  ECC does not have to be disabled to do FSM operations like
    // program and erase.
    // However, on Sonata Rev. 0 silicon, due to an OTP ECC errata,
    // disable ECC to avoid ECC errors while using Flash API functions that
    // read TI-OTP
    EALLOW;
    FlashEccRegs.ECC_ENABLE.bit.ENABLE = 0x0;
    EDIS;

    EALLOW;

    // This function is required to initialize the Flash API based on System
    // frequency before any other Flash API operation can be performed
    #if CPU_FRQ_150MHZ
    oReturnCheck = Fapi_initializeAPI(F021_CPU0_BASE_ADDRESS, 150);
    #endif

    #if CPU_FRQ_100MHZ
    oReturnCheck = Fapi_initializeAPI(F021_CPU0_BASE_ADDRESS, 100);
    #endif

    #if CPU_FRQ_60MHZ
    oReturnCheck = Fapi_initializeAPI(F021_CPU0_BASE_ADDRESS, 60);
    #endif

    if(oReturnCheck |= Fapi_Status_Success)
    {
        // Check Flash API documentation for possible errors
        Example_Error(oReturnCheck);
    }
    
    // Fapi_getLibraryInfo function can be used to get the information specific
    // to the compiled version of the API library
    oLibInfo = Fapi_getLibraryInfo();

    // Before performing FSM operations, set the waitstates for FSM operations
    // calculated using RWAIT = (SYSCLK/(2*24MHz))-1
    // If RWAIT results in a fractional value, round it up to the nearest
    // integer.
    // Please note that RWAIT for read operation should be calculated
    // differently.  See Internal Memory guide section in TRM for more details.

       #if CPU_FRQ_150MHZ
       FlashCtrlRegs.FRDCNTL.bit.RWAIT = 0x3;
       #endif

       #if CPU_FRQ_100MHZ
       FlashCtrlRegs.FRDCNTL.bit.RWAIT = 0x2;
       #endif

       #if CPU_FRQ_60MHZ
       FlashCtrlRegs.FRDCNTL.bit.RWAIT = 0x1;
       #endif

    // Fapi_setActiveFlashBank function sets the Flash bank and FMC for further
    // Flash operations to be performed on the bank
    oReturnCheck = Fapi_setActiveFlashBank(Fapi_FlashBank0);
    if(oReturnCheck |= Fapi_Status_Success)
    {
        // Check Falsh API documentation for possible errors
        Example_Error(oReturnCheck);
    }

    // Fapi_getBankSectors function returns the bank starting address, number of
    // sectors, sector sizes, and bank technology type
    // Above information is returned in a structure oFlashBankSectors of type
    // Fapi_FlashBankSectorsType
    oReturnCheck = Fapi_getBankSectors(Fapi_FlashBank0,&oFlashBankSectors);
    if(oReturnCheck |= Fapi_Status_Success)
    {
        //Check Falsh API documentation for possible errors
        Example_Error(oReturnCheck);
    }

    // Erase Sector C
    // Sectors A and D have the example code so leave them programmed
    oReturnCheck = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
                   (uint32 *)Bzero_SectorC_start);
    
    // Wait until FSM is done with erase sector operation
    while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}
    
    // Verify that SectorL is erased.  The Erase step itself does a
    // verify as it goes.  This verify is a 2nd verification that can be done.
    oReturnCheck = Fapi_doBlankCheck((uint32 *)Bzero_SectorC_start,
                   Bzero_16KSector_u32length,
                   &oFlashStatusWord);
    
    if(oReturnCheck |= Fapi_Status_Success)
    {
        // Check Falsh API documentation for possible errors
        // If Erase command fails, use Fapi_getFsmStatus() function to get the
        // FMSTAT register contents to see if any of the EV bit, ESUSP bit,
        // CSTAT bit or VOLTSTAT bit is set (Refer to API documentation for
        // more details)
        Example_Error(oReturnCheck);
    }
    
    // Erase Sector B
    // Sector N has the example code so leave it programmed
    oReturnCheck = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
                   (uint32 *)Bzero_SectorB_start);
    
    // Wait until FSM is done with erase sector operation
    while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}
    // Verify that SectorK is erased.  The Erase step itself does a verify as
    // it goes.  This verify is a 2nd verification that can be done.
    oReturnCheck = Fapi_doBlankCheck((uint32 *)Bzero_SectorB_start,
                   Bzero_16KSector_u32length,
                   &oFlashStatusWord);
    
    if(oReturnCheck |= Fapi_Status_Success)
    {
        // Check Flash API documentation for possible errors
        // If Erase command fails, use Fapi_getFsmStatus() function
        // to get the FMSTAT register contents
        // to see if any of the EV bit, ESUSP bit, CSTAT bit or VOLTSTAT
        // bit is set (Refer to API documentation for more details)
        Example_Error(oReturnCheck);
    }		


    // A data buffer of max 8 words can be supplied to the program function.
    // Each word is programmed until the whole buffer is programmed or a
    // problem is found. However to program a buffer that has more than 8
    // words, program function can be called in a loop to program 8 words for
    // each loop iteration until the whole buffer is programmed


    // Example: Program 0xFF bytes in Flash Sector C along with auto-
    // generated ECC

    // In this case just fill a buffer with data to program into the flash.
    for(i=0;i<=WORDS_IN_FLASH_BUFFER;i++)
    {
        Buffer[i] = i;
    }


    for(i=0, u32Index = Bzero_SectorC_start;
       (u32Index < (Bzero_SectorC_start + WORDS_IN_FLASH_BUFFER))
       && (oReturnCheck == Fapi_Status_Success); i+= 8, u32Index+= 8)
    {
        oReturnCheck = Fapi_issueProgrammingCommand((uint32 *)u32Index,Buffer+i,
                       8,
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
        oReturnCheck = Fapi_doVerify((uint32 *)u32Index,
                       4,
                       Buffer32+(i/2),
                       &oFlashStatusWord);
        if(oReturnCheck |= Fapi_Status_Success)
        {
        // Check Flash API documentation for possible errors
        Example_Error(oReturnCheck);
        }
    }
    
    // Example:  Program 0xFF bytes in Flash Sector B with out ECC
    // Disable ECC so that error is not generated when reading Flash contents
    // without ECC
    FlashEccRegs.ECC_ENABLE.bit.ENABLE = 0x0;
    
    for(i=0, u32Index = Bzero_SectorB_start;
       (u32Index < (Bzero_SectorB_start + WORDS_IN_FLASH_BUFFER))
       && (oReturnCheck == Fapi_Status_Success); i+= 8, u32Index+= 8)
    {
        oReturnCheck = Fapi_issueProgrammingCommand((uint32 *)u32Index,
                       Buffer+i,
                       8,
                       0,
                       0,
                       Fapi_DataOnly);
        while(Fapi_checkFsmForReady() == Fapi_Status_FsmBusy);

        if(oReturnCheck |= Fapi_Status_Success)
        {
        // Check Flash API documentation for possible errors
        Example_Error(oReturnCheck);
        }

        // Read FMSTAT register contents to know the status of FSM
        // after program command for any debug
        oFlashStatus = Fapi_getFsmStatus();

        // Verify the values programmed.  The Program step itself does a verify
        // as it goes.  This verify is a 2nd verification that can be done.
        oReturnCheck = Fapi_doVerify((uint32 *)u32Index,
                       4,
                       Buffer32+(i/2),
                       &oFlashStatusWord);
        if(oReturnCheck |= Fapi_Status_Success)
        {
        // Check Flash API documentation for possible errors
        Example_Error(oReturnCheck);
        }
    }	
    
    // Erase the sectors that we have programmed above	
    // Erase Sector C
    // Sectors A and D have the example code so leave them programmed
    oReturnCheck = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
                   (uint32 *)Bzero_SectorC_start);

    // Wait until FSM is done with erase sector operation
    while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}

    // Verify that SectorL is erased.  The Erase step itself does a verify as
    // it goes.
    // This verify is a 2nd verification that can be done.
    oReturnCheck = Fapi_doBlankCheck((uint32 *)Bzero_SectorC_start,
                   Bzero_16KSector_u32length,
                   &oFlashStatusWord);

    if(oReturnCheck |= Fapi_Status_Success)
    {
        // Check Falsh API documentation for possible errors
        // If Erase command fails, use Fapi_getFsmStatus() function to get the
        // FMSTAT register contents
        // to see if any of the EV bit, ESUSP bit, CSTAT bit or VOLTSTAT bit is
        // set (Refer to API documentation for more details)
        Example_Error(oReturnCheck);
    }
    
    // Erase Sector B
    // Sector N has the example code so leave it programmed
    oReturnCheck = Fapi_issueAsyncCommandWithAddress(Fapi_EraseSector,
                   (uint32 *)Bzero_SectorB_start);
    // Wait until FSM is done with erase sector operation
    while (Fapi_checkFsmForReady() != Fapi_Status_FsmReady){}
    // Verify that SectorK is erased.  The Erase step itself does a verify
    // as it goes.  This verify is a 2nd verification that can be done.
    oReturnCheck = Fapi_doBlankCheck((uint32 *)Bzero_SectorB_start,
                   Bzero_16KSector_u32length,
                   &oFlashStatusWord);

    if(oReturnCheck |= Fapi_Status_Success)
    {
        // Check Flash API documentation for possible errors
        // If Erase command fails, use Fapi_getFsmStatus() function to get
        // the FMSTAT register contents to see if any of the EV bit, ESUSP bit,
        // CSTAT bit or VOLTSTAT bit is set (Refer to API documentation
        // for more details)
        Example_Error(oReturnCheck);
    }		
    
    // Enable ECC
    FlashEccRegs.ECC_ENABLE.bit.ENABLE = 0xA;	
    
    EDIS;
    
    // Leave control over flash pump
    FlashLeavePump();
    
    // Example is done here
    Example_Done();

}


//******************************************************************************
// For this example, if an error is found just stop here
//******************************************************************************
#pragma CODE_SECTION(Example_Error,"ramfuncs");
void Example_Error(Fapi_StatusType status)
{
    //  Error code will be in the status parameter
        asm("    ESTOP0");
}


//******************************************************************************
//  For this example, once we are done just stop here
//******************************************************************************
#pragma CODE_SECTION(Example_Done,"ramfuncs");
void Example_Done(void)
{
    asm("    ESTOP0");
}

