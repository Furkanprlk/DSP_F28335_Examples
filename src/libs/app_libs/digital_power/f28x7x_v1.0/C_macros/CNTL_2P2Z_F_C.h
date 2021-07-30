/**
 * Second order control law using an IIR filter structure with programmable output saturation.
 * This macro uses CNTL_2P2Z_F_C structures to store coefficients & internal values.
 * The structures should be initialized with the supplied CNTL_2P2Z_F_C_INIT macro.
 * Within the structure the Max & Min parameters are the output bounds where as the IMin parameter
 * is used for saturating the lower bound while keeping an internal history.  The IMin parameter
 * should not be lower than -0.9.
 */
//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================

#ifndef CNTL_2P2Z_F_C_H_
#define CNTL_2P2Z_F_C_H_

#include "DPlib.h"

/**
 * Two-pole two-zero controller structures.
 */
typedef struct {
	// Coefficients
	float Coeff_B2;
	float Coeff_B1;
	float Coeff_B0;
	float Coeff_A2;
	float Coeff_A1;

	// Output saturation limits
	float Max;
	float IMin;
	float Min;
} CNTL_2P2Z_F_C_Coeffs;

typedef struct {
	// Inputs
	float Ref;
	float Fdbk;

	// Internal values
	float Errn;
	float Errn1;
	float Errn2;

	// Output values
	float Out;
	float Out1;
	float Out2;
	float OutPresat;
} CNTL_2P2Z_F_C_Vars;

/**
 * Calculates a second order control law with IIR filter and programmable output saturation.
 * @param CNTL_2P2Z_F_C_Coeffs structure with proper coefficient values.
 * @param CNTL_2P2Z_F_C_Vars structure with internal & output values.
 * @return CNTL_2P2Z_F_C_Vars Out parameter.
 */
#define CNTL_2P2Z_F_C(v, k)																	\
		/* Calculate error */																	\
		k.Errn = k.Ref - k.Fdbk;																\
		k.OutPresat = (v.Coeff_A2 * k.Out2) + (v.Coeff_A1 * k.Out1) + (v.Coeff_B2 * k.Errn2)	\
						+ (v.Coeff_B1 * k.Errn1) + (v.Coeff_B0 * k.Errn);						\
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
 * Initial values for CNTL_2P2Z_F_C structures.
 */
#define CNTL_2P2Z_F_C_VAR_INIT(k)				\
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

#define CNTL_2P2Z_F_C_COEFF_INIT(v)			\
		/* Initialize coefficients */			\
		v.Coeff_B2 = 0;							\
		v.Coeff_B1 = 0;							\
		v.Coeff_B0 = 0;							\
		v.Coeff_A2 = 0;							\
		v.Coeff_A1 = 0;							\
		/* IMin cannot be lower than -0.9 */	\
		v.IMin = -0.9;							\
		v.Max = 1;								\
		v.Min = (0);

#endif /* CNTL_2P2Z_F_C_H_ */
