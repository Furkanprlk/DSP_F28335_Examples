//#############################################################################
//
//! \file   driverlib_src/sysctl.c
//!
//! \brief  Contains the various functions related to the watchdog module
//
//  Group:          C2000
//  Target Device:  TMS320F2837x
//
//  (C) Copyright 2012, Texas Instruments, Inc.
//#############################################################################
// $TI Release: $
// $Release Date: $
//#############################################################################

//*****************************************************************************
// the includes
//*****************************************************************************

#include "F2837x_Device.h"     // F2837x Headerfile Include File
#include "F2837x_Examples.h"   // F2837x Examples Include File
#include "driver_incs.h"
// **************************************************************************
// the functions


//! \brief     clears WDOVERRIDE bit so that WDDIS bit cannot be modified by user
//!
//! \param[in] none
//!
//! \return    none
void sysctl_wdog_wddis_lock_set()
{
    EALLOW;
    WdRegs.SCSR.bit.WDOVERRIDE = 1;     //write 1 clear bit
    EDIS;
}

//! \brief     returns the WDOVERRIDE status
//!
//! \param[in] none
//!
//! \return    true if WDOGDIS cannot be modified else true
bool_t sysctl_wdog_wddis_lock_status_get()
{
    if( WdRegs.SCSR.bit.WDOVERRIDE == 0) {
        return true;   //WDOG DIS bit cannot be modified
    }
    else {
        return false;    //WDOG DIS bit can be modified
    }
}

void sysctl_wdog_interrupt_enable()
{
    EALLOW;
    WdRegs.SCSR.bit.WDENINT = 1;
    EDIS;
}

void sysctl_wdog_interrupt_disable()
{
    EALLOW;
    WdRegs.SCSR.bit.WDENINT = 0;
    EDIS;
}

//returns true if interrupt is active
bool_t sysctl_wdog_interrupt_status()
{
    if(WdRegs.SCSR.bit.WDINTS == 0) {
        return true;    //interrupt is active
    }
    else {
        return false;
    }
}

//! clear WDOG counter - this could be used to keep WDOG feeding so that
//! it wont cause reset
void sysctl_wdog_counter_clear()
{
    EALLOW;
        WdRegs.WDKEY.bit.WDKEY = 0x55;
        WdRegs.WDKEY.bit.WDKEY = 0xAA;
    EDIS;
}

void sysctl_wdog_prescaler_set(uint16_t prescaler)
{
    uint16_t reg_value;
    reg_value = WdRegs.WDCR.all;

    reg_value &= ~(0x7); //clear up lsb 3 bits
    reg_value |= prescaler;

    EALLOW;
    WdRegs.WDCR.all = (reg_value | (0x5 << 3));
    EDIS;
}

//return SUCCESS if WDOG is disabled successfully, else FAIL
status_t sysctl_wdog_disable(void)
{
    if(WdRegs.WDCR.bit.WDDIS == 1) {
        return SUCCESS;     //already disabled
    }

    // not disabled, so check the lock
    if(sysctl_wdog_wddis_lock_status_get() == true)
    {
        //lock is set, so you cannot change it
        return FAIL;
    }

    EALLOW;
    WdRegs.WDCR.all |= ((1<<6) | (0x5 << 3));
    EDIS;

    return SUCCESS;
}

//return SUCCESS if WDOG is enabled successfully, else FAIL
status_t sysctl_wdog_enable(void)
{
    uint16_t reg_value;

    if(WdRegs.WDCR.bit.WDDIS == 0) {
        return SUCCESS;     //already enabled
    }

    // not enabled, so check the lock
    if(sysctl_wdog_wddis_lock_status_get() == true)
    {
        //lock is set, so you cannot change it
        return FAIL;
    }

    reg_value = WdRegs.WDCR.all;
    reg_value &= (~(1<<6));

    EALLOW;
    WdRegs.WDCR.all = (reg_value | (0x5 << 3));
    EDIS;

    return SUCCESS;
}

uint8_t sysctl_wdog_window_min_value_get()
{
    uint8_t min_window = 0;
    EALLOW;
    min_window = WdRegs.WDWCR.bit.MIN;
    EDIS;

    return min_window;
}

void sysctl_wdog_window_min_value_set(uint8_t min_window)
{
    EALLOW;
    WdRegs.WDWCR.bit.MIN = min_window;
    EDIS;
}

void sysctl_wdog_window_min_value_reset()
{
    EALLOW;
    WdRegs.WDWCR.bit.MIN = 0;
    EDIS;
}


void sysctl_wdog_interrupt_enable_clear_counter()
{
    EALLOW;
    WdRegs.SCSR.all = 0x2;                                 //Select watchdog interrupt mode while not clearing WDOVERRIDE
    WdRegs.WDKEY.all = 0x55;                          //Reset the watchdog counter
    WdRegs.WDKEY.all = 0xAA;
    WdRegs.WDCR.all = 0x28;                                            //Enable the watchdog
    EDIS;
}

//Set up for a watchdog reset
void sysctl_wdog_reset_enable_clear_counter()
{
    EALLOW;
    WdRegs.SCSR.all = 0x0;                                 //Select watchdog reset mode while not clearing WDOVERRIDE
    WdRegs.WDKEY.all = 0x55;                          //Reset the watchdog counter
    WdRegs.WDKEY.all = 0xAA;
    WdRegs.WDCR.all = 0x28;                                            //Enable the watchdog
    EDIS;
}

