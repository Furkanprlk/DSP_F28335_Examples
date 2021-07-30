/**
 * Squares the reciprocate of a scaled unipolar input signal.  The use of the PFC_InvRmsSqr_F_C
 * structure is required.  The structure should be initialized using the PFC_InvRmsSqr_F_C_INIT
 * macro.  This macro calculates the inverse of values utilizing the __meinvf32 F C intrinsic.
 * Said intrinsic sacrifices some floating point precision in favor of fewer clock cycles.  If
 * greater precision or a generalization is desired, change the intrinsic to the regular division
 * operator.
 */
//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================

#ifndef PFC_INVRMSSQR_F_C_H_
#define PFC_INVRMSSQR_F_C_H_

#include "DPlib.h"

/**
 * PFC_InvRmsSqr_F_C structure
 */
typedef struct {
	float In;
	float Out;
	float Vmin;
	float VminOverVmax;
} PFC_InvRmsSqr_F_C;

#define LIMIT_PFC_INVRMSSQR ((float) 1.0)

/**
 * Calculates the square of the reciprocate of a scaled input signal.
 * @param v - PFC_InvRmsSqr_F_C_Struct
 * @return Structure Out parameter.
 */
#if !defined(__TMS320C28XX_CLA__)
#define PFC_InvRmsSqr_F_C(v)												\
	v.Out = (v.Vmin > v.In) ? v.Vmin : v.In;								\
	v.Out = __meinvf32(v.Out) * v.VminOverVmax;								\
	v.Out = v.Out * v.Out;													\
	v.Out = ((v.Out <  LIMIT_PFC_INVRMSSQR) ? v.Out : LIMIT_PFC_INVRMSSQR)
#else
#define PFC_InvRmsSqr_F_C(v)												\
	v.Out = (v.Vmin > v.In) ? v.Vmin : v.In;								\
	v.Out = __einvf32(v.Out) * v.VminOverVmax;								\
	v.Out = v.Out * v.Out;													\
	v.Out = ((v.Out <  LIMIT_PFC_INVRMSSQR) ? v.Out : LIMIT_PFC_INVRMSSQR)
#endif

/**
 * Initial values for the PFC_InvRmsSqr_F_C structure.
 */
#define PFC_InvRmsSqr_F_C_INIT(v)		\
		v.In = 0;						\
		v.Out = 0;						\
		v.Vmin = 0;						\
		v.VminOverVmax = 0

#endif /* PFC_INVRMSSQR_F_C_H_ */
