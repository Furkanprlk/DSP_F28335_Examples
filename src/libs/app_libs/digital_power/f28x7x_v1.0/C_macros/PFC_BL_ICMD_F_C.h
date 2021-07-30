/**
 * Performs current command computation for PFC stage using PFC boost switch sensing.  This macro
 * requires the use of the PFC_BL_ICMD_F_C structure.  The structure should be initialized
 * using the PFC_BL_ICMD_F_C_INIT macro.  The macro calculates the inverse of values utilizing
 * the __meinvf32 F C intrinsic.  Said intrinsic sacrifices some floating point precision in
 * favor of fewer clock cycles.  If greater precision or a generalization is desired, change the
 * intrinsic to the regular division operator.
 */
//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================

#ifndef PFC_BL_ICMD_F_C_H_
#define PFC_BL_ICMD_F_C_H_

#include "DPlib.h"

/**
 * Current command PFC BL structure
 */
typedef struct {
	float Vcmd;
	float VinvSqr;
	float VacRect;
	float Duty;
	float Vpfc;
	float Out;
	float VmaxOverVmin;
	float VoutMaxOverVinMax;
} PFC_BL_ICMD_F_C;

#define LIMIT_PFC_BL_ICMD ((float) 0.005)

/**
 * Performs current command computation for PFC.
 * @param v - PFC_BL_ICMD_F_C structure.
 * @return PFC_BL_ICMD_F_C Out parameter.
 */
#if !defined(__TMS320C28XX_CLA__)
#define PFC_BL_ICMD_F_C(v)													\
	v.Out = v.Vpfc * v.VoutMaxOverVinMax * v.Duty;								\
	v.Out = (v.Out > LIMIT_PFC_BL_ICMD) ? v.Out : LIMIT_PFC_BL_ICMD;			\
	v.Out = (v.VacRect * v.VinvSqr * v.Vcmd * v.VmaxOverVmin) 					\
			* __einvf32(v.Out)	* ((v.Vpfc * v.VoutMaxOverVinMax) - v.VacRect)
#else
#define PFC_BL_ICMD_F_C(v)													\
	v.Out = v.Vpfc * v.VoutMaxOverVinMax * v.Duty;								\
	v.Out = (v.Out > LIMIT_PFC_BL_ICMD) ? v.Out : LIMIT_PFC_BL_ICMD;			\
	v.Out = (v.VacRect * v.VinvSqr * v.Vcmd * v.VmaxOverVmin) 					\
			* __meinvf32(v.Out)	* ((v.Vpfc * v.VoutMaxOverVinMax) - v.VacRect)
#endif

/**
 * Initial values for the PFC_BL_ICMD_F_C structure.
 */
#define PFC_BL_ICMD_F_C_INIT(v)	\
		v.Vcmd = 0;					\
		v.VinvSqr = 0;				\
		v.VacRect = 0;				\
		v.Duty = 0;					\
		v.Vpfc = 0;					\
		v.Out = 0;					\
		v.VmaxOverVmin = 0;			\
		v.VoutMaxOverVinMax = (0)

#endif /* PFC_BL_ICMD_F_C_H_ */
