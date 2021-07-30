/**
 * Squares the reciprocate of a scaled uni-polar input signal.  The use of the PFC_INSVQR_F_C
 * structure is required. The structure should be initialized with the PFC_INVSQR_F_C_INIT macro.
 * This macro calculates the inverse of values utilizing the __meinvf32 F C intrinsic.  Said
 * intrinsic sacrifices some floating point precision in favor of fewer clock cycles.  If greater
 * precision or a generalization is desired, change the intrinsic to the regular division operator.
 */
//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================

#ifndef PFC_INVSQR_F_C_H_
#define PFC_INVSQR_F_C_H_

#include "DPlib.h"

/**
 * PFC_INVSQR_F_C structure
 */
typedef struct {
	float32 In;
	float32 Out;
	float32 Vmin;
	float VminOverVmax;
} PFC_INVSQR_F_C;

#define HALF_PI ((float32) 1.5707)
#define LIMIT_PFC_INVSQR ((float32) 1.0)

/**
 * Calculates the reciprocate of a scaled uni-polar signal.
 * @param v - PFC_INVSQR_F_C structure
 * Updates: PFC_INVSQR_F_C Out parameter
 */
#if !defined(__TMS320C28XX_CLA__)
#define PFC_INVSQR_F_C(v)												\
	v.Out = (v.In > v.Vmin) ? v.In : v.Vmin;							\
	v.Out = __einvf32(v.Out * HALF_PI) * v.VminOverVmax;				\
	v.Out *= v.Out;														\
	v.Out = ((v.Out < LIMIT_PFC_INVSQR) ? v.Out : LIMIT_PFC_INVSQR)
#else
#define PFC_INVSQR_F_C(v)												\
	v.Out = (v.In > v.Vmin) ? v.In : v.Vmin;							\
	v.Out = __meinvf32(v.Out * HALF_PI) * v.VminOverVmax;				\
	v.Out *= v.Out;														\
	v.Out = ((v.Out < LIMIT_PFC_INVSQR) ? v.Out : LIMIT_PFC_INVSQR)
#endif

/**
 * Initial values for the PFC_INVSQR_F_C structure
 */
#define PFC_INVSQR_F_C_INIT(v)	\
		v.In = 0;					\
		v.Out = 0;					\
		v.Vmin = 0;					\
		v.VminOverVmax = 0

#endif /* PFC_INVSQR_F_C_H_ */
