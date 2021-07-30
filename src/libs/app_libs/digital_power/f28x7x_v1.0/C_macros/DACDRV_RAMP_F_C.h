/**
 * DAC ramp generator interface which can be used for slope compensation if not already provided.
 * Requires the DAC to be configured with the DacDrvCnf function found in the DAC_Cnf.c source file.
 * @see DAC_Cnf.c
 */
//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================

#ifndef DACDRV_RAMP_F_C_H_
#define DACDRV_RAMP_F_C_H_

#include "DPlib.h"

/**
 * Drives the DAC output.
 * @param CompRegs - Comparator configuration registers of the DAC.
 * @param RampIn - New DAC output value.
 */
#define DACDRV_RAMP_F_C(CompRegs, RampIn)		\
	CompRegs.RAMPMAXREF_SHDW = RampIn;			\
	CompRegs.DACVAL.bit.DACVAL = RampIn

#endif /* DACDRV_RAMP_F_C_H_ */
