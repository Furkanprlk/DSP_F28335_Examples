/**
 * Performs computation of the current command for power factor correction.  This macro utilizes
 * the PFC_ICMD_F_C structure which should be initialized using the PFC_ICMD_F_C_INIT macro.
 */
//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================

#ifndef PFC_ICMD_F_C_H_
#define PFC_ICMD_F_C_H_

#include "DPlib.h"

/**
 * Current command PFC structure
 */
typedef struct {
	float Vcmd;
	float VinvSqr;
	float VacRect;
	float Out;
	float VmaxOverVmin;
} PFC_ICMD_F_C;

/**
 * Calculates current command for power factor correction.
 * @param v - PFC_ICMD_F_C structure.
 * @return PFC_ICMD_F_C Out parameter
 */
#define PFC_ICMD_F_C(v)										\
	v.Out = (v.Vcmd * v.VinvSqr * v.VacRect * v.VmaxOverVmin)

/**
 * Initial values for the PFC_ICMD_F_C structure.
 */
#define PFC_ICMD_F_C_INIT(v)		\
		v.Vcmd = 0;					\
		v.VinvSqr = 0;				\
		v.VacRect = 0;				\
		v.Out = 0;					\
		v.VmaxOverVmin = 0

#endif /* PFC_ICMD_F_C_H_ */
