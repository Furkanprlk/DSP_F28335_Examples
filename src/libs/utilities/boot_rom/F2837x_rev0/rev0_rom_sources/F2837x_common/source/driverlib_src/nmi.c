//#############################################################################
//
//! \file   driverlib_src/nmi.c
//!
//! \brief  Contains the various functions related to the peripheral interrupt
//!         expansion (PIE) object
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

status_t nmi_global_mask_status(void)
{

    return NmiIntruptRegs.NMICFG.bit.NMIE;
}

status_t nmi_global_mask_disable(void)
{
    EALLOW;
    NmiIntruptRegs.NMICFG.bit.NMIE |= 0x01;      //enable NMI
    EDIS;

    return SUCCESS;    //for success
}

status_t nmi_global_mask_enable(void)
{
    //NMI cannot be disabled on F2837x device, so return true if it is already disabled
    EALLOW;
    NmiIntruptRegs.NMICFG.bit.NMIE &= 0x00;      //disable NMI
    EDIS;

//    if (nmi_config_status() == false) {
//        return SUCCESS;
//    }
//    else {
//        return FAIL;
//    }
    return SUCCESS;
}

//! \brief     get the current status of interrupt in question
//! \param[in] nmi_id  nmi id of the interrupt that the user is checking for
//! \return    returns true if the flag for nmi is set else returns false
status_t nmi_interrupt_status_get(uint16_t nmi_id)
{
    //check if any invalid bits are being passed in param
    //comment the check if too strict
    if(nmi_id & NMI_INT_INVALID) {
        return FAIL;
    }


    if((NmiIntruptRegs.NMIFLG.all & nmi_id) == nmi_id){
        return true;
    }
    else {
        return false;
    }
}

//! \brief      get the current status of nmi interrupt from shadow register
//! \param[in]  nmi_id nmi id of the interrupt that the user is checking for
//! \return     returns true if the flag for nmi is set in the shadow flag
//!             register else returns false
status_t nmi_shadow_interrupt_status_get(uint16_t nmi_id)
{
    //check if any invalid bits are being passed in param
    //comment the check if too strict
    if(nmi_id & NMI_INT_INVALID) {
        return false;
    }

    if((NmiIntruptRegs.NMISHDFLG.all & (nmi_id)) == nmi_id) {
        return true;
    }
    else {
        return false;
    }
}

//! \brief      trigger an NMI interrupt by forcing it
//!             the function will fail if trying to force NMI_INT_FLG or any
//!             reserved interrupt
//! \param[in]  nmi_id  nmi id of the interrupt that the user is checking for
//! \return     success if the nmi is forced, returns fail if not
status_t nmi_interrupt_force_set(uint16_t nmi_id)
{
    //check if any invalid bits are being passed in param
    //comment the check if too strict
    if(nmi_id & NMI_INT_INVALID) {
        return FAIL;
    }
    if(nmi_id & NMI_INT_FLG)    //cannot set bit 0 of NMI_INT_FLG
        return FAIL;

    EALLOW;
    NmiIntruptRegs.NMIFLGFRC.all |= nmi_id;
    EDIS;

    return SUCCESS;
}

//! \brief      clear the NMI interrupt or acknowledge the interrupt
//!             the function will fail if trying to acknowledge an interrupt
//!             that is not active. This function clears only the interrupt,
//!             it doesn't clear the global interrupt flag (NMI_INT_FLG)
//!             except when explicitly asked for, by passing in NMI_INT_FLG
//!             as the parameter. However if user tries to clear NMI_INT_FLG
//!             before clearing active interrupts the flag wont be cleared and
//!             in such case the function returns FAIL, else it returns SUCCESS
//! \param[in]  nmi_id  nmi id of the interrupt that the user is checking for
//! \return     return FAIL if interrupt doesn't get cleared, else SUCCESS
status_t nmi_interrupt_clear(uint16_t nmi_id)
{
    //check if any invalid bits are being passed in param
    //comment the check if too strict
    if(nmi_id & NMI_INT_INVALID) {
        return FAIL;
    }
    //check if the interrupt(s) in question is/are active
    if((nmi_interrupt_status_get(nmi_id)) == false) {
        return FAIL;
    }

    EALLOW;
    (NmiIntruptRegs.NMIFLGCLR.all) |= (nmi_id);
    EDIS;

    //check if all the flags are cleared
    if((nmi_interrupt_status_get(nmi_id)) == false) {
        return SUCCESS;
    }
    else {
        return FAIL;
    }

}

