#ifndef _NMI_H_
#define _NMI_H_

//#############################################################################
//
//! \file   driverlib_inc/nmi.h
//!
//! \brief  Contains public interface to various functions related to the
//!         analog-to-digital converter (ADC) object
//
//  Group:          C2000
//  Target Device:  TMS320F2837x
//
//  (C) Copyright 2012, Texas Instruments, Inc.
//#############################################################################
// $TI Release: $
// $Release Date: $
//#############################################################################

// **************************************************************************
// the includes

#include "F2837x_Device.h"     // F2837x Headerfile Include File
#include "F2837x_Examples.h"   // F2837x Examples Include File

// drivers


//!
//! \defgroup NMI

//!
//! \ingroup System Control
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines
#define NMI_INT_FLG             0x0001          //!< Denotes bit 0 of NMIINTFLG register
#define NMI_INT_CLOCKFAIL       0x0002          //!< Denotes CLOCKFAIL error
#define NMI_INT_RAMUNCERR       0x0004          //!< Denotes RAM uncorrectable error
#define NMI_INT_FLUNCERR        0x0008          //!< Denotes flash uncorrectable error
#define NMI_INT_CPU1HWBISTERR   0x0010          //!< Denotes cpu1 hwbist error
#define NMI_INT_CPU2HWBISTERR   0x0020          //!< Denotes cpu2 hwbist error
#define NMI_INT_PIEVECTERR      0x0040          //!< Denotes pievect error
#define NMI_INT_SYSDBG          0x0080          //!< Denotes sys debug nmi
#define NMI_INT_RL              0x0100          //!< Denotes reconfigurable logic nmi
#define NMI_INT_CPU2WDRST       0x0200          //!< Denotes CPU2 WDOG reset error
#define NMI_INT_CPU2NMIWDRST    0x0400          //!< Denotes CPU2 NMIWDOG reset error
#define NMI_INT_OVF             0x0800          //!< Denotes Over voltage detection
#define NMI_INT_ALLVALID        0x0FFF          //!< Valid NMI bits
#define NMI_INT_INVALID         0xF000          //~(0x0FFF) //!< inValid NMI bits


//! \brief
// **************************************************************************

// the typedefs

// **************************************************************************
// the globals


// **************************************************************************
// the function prototypes

extern status_t nmi_global_mask_status(void);
extern status_t nmi_global_mask_disable(void);
extern status_t nmi_global_mask_enable(void);
extern status_t nmi_interrupt_status_get(uint16_t nmi_id);
extern status_t nmi_shadow_interrupt_status_get(uint16_t nmi_id);
extern status_t nmi_interrupt_force_set(uint16_t nmi_id);
extern status_t nmi_interrupt_clear(uint16_t nmi_id);


//! \brief     get current value of nmi watchdog period
//! \return    16 bit value of the watchdog period register
inline uint16_t nmi_watchdog_period_get(void)
{
    return (NmiIntruptRegs.NMIWDPRD);
}

//! \brief     set nmi watchdog period
//! \param[in] iterations -number of iterations the nmi must be activated
//! \return    none
inline void errornmi_watchdog_period_set1(uint16_t period)
{
    EALLOW;
    NmiIntruptRegs.NMIWDPRD = period;
    EDIS;
}


//! \brief     get current value of nmi watchdog counter
//! \return    16 bit value of the watchdog counter register
inline uint16_t errornmi_watchdog_counter_get(void)
{
    return (NmiIntruptRegs.NMIWDCNT);
}



#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup


#endif // end of _NMI_H_ definition

