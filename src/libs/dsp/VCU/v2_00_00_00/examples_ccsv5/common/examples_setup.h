#ifndef _VCU2_EXAMPLES_SETUP_H_
#define _VCU2_EXAMPLES_SETUP_H_
//#############################################################################
//! \file /examples_ccsv5/common/examples_setup.h
//!
//! \brief  Initialization routines for the VCU2 library examples
//!
//! \date   July 16, 2013
//
//  Group: 			C2000
//  Target Family:	F2837x
//
// (C)Copyright 2012, Texas Instruments, Inc.
//#############################################################################
//$TI Release: C28x VCU Library Version v2.00.00.00 $
//$Release Date: Dec 6, 2013 $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "F28x_Project.h"

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define CPU_FRQ_200MHZ	1

//*****************************************************************************
// typedefs
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// function prototypes
//*****************************************************************************
// \brief Initialize system clocks
//
void VCU2_initSystemClocks(void);

// \brief Initialize Enhanced PIE
//
void VCU2_initEpie(void);

// \brief Initialize Flash
//
void VCU2_initFlash(void);

// \brief Disable Flash prefetch
//
extern void InitFlash_PrefetchCacheDisable(void);

// \brief Enable Flash prefetch
//
extern void InitFlash_PrefetchCacheEnable(void);

// \brief Set Flash wait states
// \param[in] waitStates The number of wait states
//
void SetupFlash(unsigned short waitStates);

#ifdef __cplusplus
}
#endif // extern "C"

#endif //end of _VCU2_EXAMPLES_SETUP_H_ definition
