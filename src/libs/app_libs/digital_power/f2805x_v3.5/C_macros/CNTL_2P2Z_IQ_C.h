//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================
/**
 * Second order control law using an IIR filter structure with programmable output saturation.
 * This macro uses CNTL_2P2Z_IQ_C structures to store coefficients & internal values.
 * The structures should be initialized with the supplied CNTL_2P2Z_IQ_C_INIT macro.
 * Within the structure the Max & Min parameters are the output bounds where as the IMin parameter
 * is used for saturating the lower bound while keeping an internal history.  The IMin parameter
 * should not be lower than -0.9.
 */

#ifndef CNTL_2P2Z_IQ_C_H_
#define CNTL_2P2Z_IQ_C_H_
#include "IQmathLib.h"

/**
 * Two-pole two-zero controller structures.
 */
typedef struct {
	// Coefficients
	long Coeff_B2;
	long Coeff_B1;
	long Coeff_B0;
	long Coeff_A2;
	long Coeff_A1;

	// Output saturation limits
	long Max;
	long IMin;
	long Min;
} CNTL_2P2Z_IQ_C_Coeffs;

typedef struct {
	// Inputs
	long Ref;
	long Fdbk;

	// Internal values
	long Errn;
	long Errn1;
	long Errn2;

	// Output values
	long Out;
	long Out1;
	long Out2;
	long OutPresat;
} CNTL_2P2Z_IQ_C_Vars;

/**
 * Calculates a second order control law with IIR filter and programmable output saturation.
 * @param CNTL_2P2Z_IQ_C_Coeffs structure with proper coefficient values.
 * @param CNTL_2P2Z_IQ_C_Vars structure with internal & output values.
 * @return CNTL_2P2Z_IQ_C_Vars Out parameter.
 */
#define CNTL_2P2Z_IQ_C(v, k)																	\
		/* Calculate error */																	\
		k.Errn = k.Ref - k.Fdbk;																\
		k.OutPresat = _IQ24mpy(v.Coeff_A2,k.Out2) + _IQ24mpy(v.Coeff_A1 , k.Out1) + _IQ24mpy(v.Coeff_B2 ,k.Errn2)	\
						+ _IQ24mpy(v.Coeff_B1 , k.Errn1) + _IQ24mpy(v.Coeff_B0 , k.Errn);						\
																								\
		/* Update error values */																\
		k.Errn2 = k.Errn1;																		\
		k.Errn1 = k.Errn;																		\
																								\
		/* Determine new output */																\
		k.Out = k.OutPresat;																	\
		k.Out = (k.Out < v.Max) ? k.Out : v.Max;												\
		k.Out = (k.Out > v.IMin) ? k.Out : v.IMin;												\
																								\
		/* Store outputs */																		\
		k.Out2 = k.Out1;																		\
		k.Out1 = k.Out;																			\
		/* Saturated output */																	\
		k.Out = ((k.Out > v.Min) ? k.Out : v.Min);

/*
 * Initial values for CNTL_2P2Z_IQ_C structures.
 */
#define CNTL_2P2Z_IQ_C_VAR_INIT(k)				\
		/* Initialize variables */				\
		k.Ref = 0;								\
		k.Fdbk = 0;								\
		k.Errn = 0;								\
		k.Errn1 = 0;							\
		k.Errn2 = 0;							\
		k.Out = 0;								\
		k.Out1 = 0;								\
		k.Out2 = 0;								\
		k.OutPresat = 0;

#define CNTL_2P2Z_IQ_C_COEFF_INIT(v)			\
		/* Initialize coefficients */			\
		v.Coeff_B2 = 0;							\
		v.Coeff_B1 = 0;							\
		v.Coeff_B0 = 0;							\
		v.Coeff_A2 = 0;							\
		v.Coeff_A1 = 0;							\
		/* IMin cannot be lower than -0.9 */	\
		v.IMin = _IQ24(-0.9);					\
		v.Max = _IQ24(1.0);						\
		v.Min = (0)

#endif /* CNTL_2P2Z_IQ_C_H_ */
