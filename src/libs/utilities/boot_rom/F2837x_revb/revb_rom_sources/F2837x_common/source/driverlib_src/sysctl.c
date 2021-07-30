//#############################################################################
//
//! \file   driverlib_src/sysctl.c
//!
//! \brief  Contains the various functions related to the system control module
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


//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//! \param[in] 32 bit value again which the RESC register is checked for,
//! this value must be a combination of \b SYSCTL_RESC_POR, \b SYSCTL_RESC_XRSN
//! \b SYSCTL_RESC_WD, \b SYSCTL_RESC_NMIWD, \b SYSCTL_RESC_HWBIST, \b
//! SYSCTL_RESC_HIB, \b SYSCTL_RESC_SCC, \b SYSCTL_RESC_XRSN_PIN_STS,
//! \b SYSCTL_RESC_TRSTN_PIN_STS
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the bits are set or if function is asked to
//!             check invalid bits
status_t sysctl_reset_cause_check(uint32_t reset_source)
{
    //parameter check
    if(reset_source & (SYSCTL_RESC_INVALID_BITS)) {
        return false;   //invalid bits are being checked
    }

    if((sysctl_reset_cause_get()) & reset_source) {
        return true;
    }
    else {
        return false;
    }
}

//! \brief     clears the requested reset causes
//!
//! \param[in] 32 bit value again which the RESC register is checked for,
//! this value must be a combination of \b SYSCTL_RESC_POR, \b SYSCTL_RESC_XRSN
//! \b SYSCTL_RESC_WD, \b SYSCTL_RESC_NMIWD, \b SYSCTL_RESC_HWBIST, \b
//! SYSCTL_RESC_HIB, \b SYSCTL_RESC_SCC, \b SYSCTL_RESC_XRSN_PIN_STS,
//! \b SYSCTL_RESC_TRSTN_PIN_STS
//!
//! \return  false if function is asked to
//!             clear invalid bits
status_t sysctl_reset_cause_clear(uint32_t reset_source)
{
    //parameter check
    if(reset_source & (SYSCTL_RESC_INVALID_BITS)) {
        return FAIL;   //invalid bits are being checked
    }

    sysctl_reset_cause_set(reset_source);

    return SUCCESS;
}

//! \brief     clears the requested reset causes if they are set in reset cause
//! register, this is a strict version of the function, where the function would fail
//! if user is trying to clear any bit that is not set
//!
//! \param[in] 32 bit value again which the RESC register is checked for,
//! this value must be a combination of \b SYSCTL_RESC_POR, \b SYSCTL_RESC_XRSN
//! \b SYSCTL_RESC_WD, \b SYSCTL_RESC_NMIWD, \b SYSCTL_RESC_HWBIST, \b
//! SYSCTL_RESC_HIB, \b SYSCTL_RESC_SCC, \b SYSCTL_RESC_XRSN_PIN_STS,
//! \b SYSCTL_RESC_TRSTN_PIN_STS
//!
//! \return  false if any of the bits are not set or if function is asked to
//!             clear invalid bits
status_t sysctl_reset_cause_check_clear(uint32_t reset_source)
{
    //parameter check
    if(reset_source & (SYSCTL_RESC_INVALID_BITS)) {
        return false;   //invalid bits are being checked
    }

    if((sysctl_reset_cause_get()) == reset_source) {
        sysctl_reset_cause_set(reset_source);
        return true;
    }
    else {
        return false;
    }
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_por_reset_cause_check()
{
    return sysctl_reset_cause_check(SYSCTL_RESC_POR);
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_por_reset_cause_clear()
{
    return sysctl_reset_cause_clear(SYSCTL_RESC_POR);
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_por_reset_cause_check_clear()
{
    return sysctl_reset_cause_check_clear(SYSCTL_RESC_POR);
}


//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_xrsn_reset_cause_check()
{
    return sysctl_reset_cause_check(SYSCTL_RESC_XRSN);
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_xrsn_reset_cause_clear()
{
    return sysctl_reset_cause_clear(SYSCTL_RESC_XRSN);
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_xrsn_reset_cause_check_clear()
{
    return sysctl_reset_cause_check_clear(SYSCTL_RESC_XRSN);
}


//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_wdog_reset_cause_check()
{
    return sysctl_reset_cause_check(SYSCTL_RESC_WD);
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_wdog_reset_cause_clear()
{
    return sysctl_reset_cause_clear(SYSCTL_RESC_WD);
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_wdog_reset_cause_check_clear()
{
    return sysctl_reset_cause_check_clear(SYSCTL_RESC_WD);
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_nmi_wdog_reset_cause_check()
{
    return sysctl_reset_cause_check(SYSCTL_RESC_NMIWD);
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_nmi_wdog_reset_cause_clear()
{
    return sysctl_reset_cause_clear(SYSCTL_RESC_NMIWD);
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_nmi_wdog_reset_cause_check_clear()
{
    return sysctl_reset_cause_check_clear(SYSCTL_RESC_NMIWD);
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_hwbist_reset_cause_check()
{
    return sysctl_reset_cause_check(SYSCTL_RESC_HWBIST);
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_hwbist_reset_cause_clear()
{
    return sysctl_reset_cause_clear(SYSCTL_RESC_HWBIST);
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_hwbist_reset_cause_check_clear()
{
    return sysctl_reset_cause_check_clear(SYSCTL_RESC_HWBIST);
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_hib_reset_cause_check()
{
    return sysctl_reset_cause_check(SYSCTL_RESC_HIB);
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_hib_reset_cause_clear()
{
    return sysctl_reset_cause_clear(SYSCTL_RESC_HIB);
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_hib_reset_cause_check_clear()
{
    return sysctl_reset_cause_check_clear(SYSCTL_RESC_HIB);
}


//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_scc_reset_cause_check()
{
    return sysctl_reset_cause_check(SYSCTL_RESC_SCC);
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_scc_reset_cause_clear()
{
    return sysctl_reset_cause_clear(SYSCTL_RESC_SCC);
}

//! \brief     checks if the requested reset causes are set in reset cause
//!             register
//!
//! \return    true if any of the asked for bits are set
//!             false if none of the requested bits are set
status_t sysctl_scc_reset_cause_check_clear()
{
    return sysctl_reset_cause_check_clear(SYSCTL_RESC_SCC);
}

//! \brief     returns the status of xrsn pin
//!
//! \return    true if pin is high else false
status_t sysctl_check_xrsn_pin_status()
{
    return sysctl_reset_cause_check(SYSCTL_RESC_XRSN_PIN_STS);
}

//! \brief     returns the status of trstn pin
//!
//! \return    true if pin is high else false
status_t sysctl_check_trstn_pin_status()
{
    return sysctl_reset_cause_check(SYSCTL_RESC_TRSTN_PIN_STS);
}


#ifdef CPU1
//! \brief     checks if there was an error in efuse autoload logic
//!
//! \return    true if error else false
status_t sysctl_efuse_detected_error()
{
    if(DevCfgRegs.FUSEERR.all == 0x00) {
        return false;   //no error
    }

    //    //10101b or 0x000
    if(DevCfgRegs.FUSEERR.bit.ERR ==0x0) {
        if(DevCfgRegs.FUSEERR.bit.ALERR == 0x15) {
            return false;   // no error
        }
        else {
            return true;    //error
        }
    }
    else {
        return true;    //error
    }
}

//! \brief     returns the status of trstn pin
//!
//! \return    5 bits of error code
uint16_t sysctl_efuse_autoload_error_status_get()
{
    return DevCfgRegs.FUSEERR.bit.ALERR;
}


#endif //#ifdef CPU1


