#ifndef _EXAMPLES_SETUP_H_
#define _EXAMPLES_SETUP_H_
//#############################################################################
//! \file /examples_ccsv5/common/examples_setup.h
//!
//! \brief  Initialization routines for the Fixed Point library examples
//! \date   Sep 9, 2014
//
//  Group:          C2000
//  Target Family:  C28x
//
// (C)Copyright 2014, Texas Instruments, Inc.
//#############################################################################
//$TI Release: C28x Fixed Point DSP Library V1.20.00.00 $
//$Release Date: Oct 23, 2014 $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "DSP28x_Project.h"
#include <stdint.h>
#include <float.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define CPU_FRQ_150MHZ	1

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
void FIXPT_DSP_initSystemClocks(void);

// \brief Initialize Enhanced PIE
//
void FIXPT_DSP_initEpie(void);

// \brief Initialize Flash
//
void FIXPT_DSP_initFlash(void);


#ifdef __cplusplus
}
#endif // extern "C"

#endif //end of _EXAMPLES_SETUP_H_ definition
