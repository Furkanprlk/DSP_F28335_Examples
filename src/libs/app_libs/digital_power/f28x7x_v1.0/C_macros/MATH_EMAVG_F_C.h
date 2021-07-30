/**
 * Performs exponential moving average calculation.  This macro requires the use of the
 * MATH_EMAVG_F_C structure.  The structure should be initialized with the MATH_EMAVG_F_C_INIT
 * macro.
 */
//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================

#ifndef MATH_EMAVG_F_C_H_
#define MATH_EMAVG_F_C_H_

#include "DPlib.h"

/**
 * Exponential-moving average structure
 */
typedef struct {
	float In;
	float Out;
	float Multiplier;
} MATH_EMAVG_F_C;


/**
 * Performs exponential moving average calculation.
 * @param m - MATH_EMAVG_F_C structure with values.
 * @return MATH_EMAVG_F_C Out parameter.
 */
#define MATH_EMAVG_F_C(m)									\
m.Out = (((m.In - m.Out) * m.Multiplier) + m.Out)

/**
 * Initial values for MATH_EMAVG_F_C structure.
 */
#define MATH_EMAVG_F_C_INIT(v)	\
	v.In = 0;						\
	v.Out = 0;						\
	v.Multiplier = 0

#endif /* MATH_EMAVG_F_C_H_ */
