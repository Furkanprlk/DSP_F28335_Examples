#ifndef _SYSCTL_H_
#define _SYSCTL_H_

//#############################################################################
//
//! \file   driverlib_inc/sysctl.h
//!
//! \brief  Contains public interface to various system control funcs
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
//! \defgroup main

//!
//! \ingroup System Control
//@{


#ifdef __cplusplus
extern "C" {
#endif


// **************************************************************************
// the defines
#define SYSCTL_RESC_POR                 0x00000001  //!< Denotes reset because
                                                    //! of POR
#define SYSCTL_RESC_XRSN                0x00000002  //!< Denotes reset because
                                                    //! of XRSn
#define SYSCTL_RESC_WD                  0x00000004  //!< Denotes reset because
                                                    //! of WDOG
#define SYSCTL_RESC_NMIWD               0x00000008  //!< Denotes reset because
                                                    //! of NMIWD
#define SYSCTL_RESC_HWBIST              0x00000020  //!< Denotes reset because
                                                    //! of HWBIST
#define SYSCTL_RESC_HIB                 0x00000040  //!< Denotes reset because
                                                    //! of Hibernate reset cause
#define SYSCTL_RESC_SCC                 0x00000100  //!< Denotes reset because
                                                    // of Security module

#define SYSCTL_RESC_XRSN_PIN_STS        0x40000000  //!< Denotes current status
                                                    //! of XRSn pin
#define SYSCTL_RESC_TRSTN_PIN_STS       0x80000000  //!< Denotes current status
                                                    //! of TRSTn pin
#define SYSCTL_RESC_VALID_BITS          0xC000016F  //!< Denotes all the valid
                                                    //! bits of RESC register

#define SYSCTL_RESC_INVALID_BITS        0x3FFFFE90//!< Denotes all the in-valid
                                                  //! bits of RESC register


//! \brief
// **************************************************************************

// the typedefs

// **************************************************************************
// the globals


// **************************************************************************
// the function prototypes

//! \brief     get the current vaue of reset cause register
//! \param[in] none
//! \return    32 bit value of the reset cause register
inline uint32_t sysctl_reset_cause_get(void)
{
    return CpuSysRegs.RESC.all;
}

//! \brief     set the current vaue of reset cause register
//! \param[in] none
//! \return    32 bit value of the reset cause register
inline void sysctl_reset_cause_set(uint32_t value)
{
    CpuSysRegs.RESC.all = value;
}


//! \brief     set nmi watchdog period
//! \param[in] iterations -number of iterations the nmi must be activated
//! \return    none
inline void nmi_watchdog_period_set(uint16_t period)
{
    NmiIntruptRegs.NMIWDPRD = period;
}


//! \brief     get current value of nmi watchdog counter
//! \return    16 bit value of the watchdog counter register
inline uint16_t nmi_watchdog_counter_get(void)
{
    return (NmiIntruptRegs.NMIWDCNT);
}

extern void sysctl_wdog_wddis_lock_set();
extern bool_t sysctl_wdog_wddis_lock_status_get();
extern void sysctl_wdog_interrupt_enable();
extern void sysctl_wdog_interrupt_disable();
extern bool_t sysctl_wdog_interrupt_status();
extern void sysctl_wdog_counter_clear();
extern void sysctl_wdog_prescaler_set(uint16_t prescaler);
extern status_t sysctl_wdog_disable(void);
extern status_t sysctl_wdog_enable(void);
extern uint8_t sysctl_wdog_window_min_value_get();
extern void sysctl_wdog_window_min_value_set(uint8_t min_window);
extern void sysctl_wdog_window_min_value_reset();
extern void sysctl_wdog_interrupt_enable_clear_counter();
extern void sysctl_wdog_reset_enable_clear_counter();














#ifdef __cplusplus
}
#endif // extern "C"

//@}  // ingroup


#endif // end of _SYSCTL_H_ definition

