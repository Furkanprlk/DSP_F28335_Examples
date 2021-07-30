#ifndef CNTL_2P2Z_CLA_H_
#define CNTL_2P2Z_CLA_H_

//*********** Structure Definition ********//

// Second order control law using an IIR filter structure with programmable output saturation.
// This macro uses CNTL_2P2Z_CLA structures to store coefficients & internal values.
// The structures should be initialized with the supplied CNTL_2P2Z_CLA_init macro.
// Within the structure the Max & Min parameters are the output bounds where as the IMin parameter
// is used for saturating the lower bound while keeping an internal history.  The IMin parameter
// should not be lower than -0.9.

typedef struct {
	// Coefficients
	float32 Coeff_B2;
	float32 Coeff_B1;
	float32 Coeff_B0;
	float32 Coeff_A2;
	float32 Coeff_A1;

	// Output saturation limits
	float32 Max;
	float32 IMin;
	float32 Min;
} CNTL_2P2Z_CLA_COEFFS;

typedef struct {
	// Inputs
	float32 Ref;
	float32 Fdbk;

	// Internal values
	float32 Errn;
	float32 Errn1;
	float32 Errn2;

	// Output values
	float32 Out;
	float32 Out1;
	float32 Out2;
	float32 OutPresat;
} CNTL_2P2Z_CLA_VARS;

//*********** Function Declarations *******//
void CNTL_2P2Z_CLA_FUNC(CNTL_2P2Z_CLA_COEFFS *v, CNTL_2P2Z_CLA_VARS *k);

//*********** Structure Init Macro *******//
#define CNTL_2P2Z_CLA_VARS_init(k)				\
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

#define CNTL_2P2Z_CLA_COEFFS_init(v)			\
		/* Initialize coefficients */			\
		v.Coeff_B2 = 0;							\
		v.Coeff_B1 = 0;							\
		v.Coeff_B0 = 0;							\
		v.Coeff_A2 = 0;							\
		v.Coeff_A1 = 0;							\
		/* IMin cannot be lower than -0.9 */	\
		v.IMin = (-0.9);						\
		v.Max = (1.0);							\
		v.Min = (0)

//*********** Macro Definition ***********//

// Calculates a second order control law with IIR filter and programmable output saturation.
// @param CNTL_2P2Z_CLA_Coeffs structure with proper coefficient values.
// @param CNTL_2P2Z_CLA_Vars structure with internal & output values.
// @return CNTL_2P2Z_CLA_Vars Out parameter.

#define CNTL_2P2Z_CLA_MACRO(v, k)															\
		/* Calculate error */																\
		k.Errn = k.Ref - k.Fdbk;															\
		k.OutPresat = (v.Coeff_A2*k.Out2) + (v.Coeff_A1 *k.Out1) + (v.Coeff_B2 *k.Errn2)	\
						+ (v.Coeff_B1 * k.Errn1) + (v.Coeff_B0 * k.Errn);					\
		/* Update error values */															\
		k.Errn2 = k.Errn1;																	\
		k.Errn1 = k.Errn;																	\
		/* Determine new output */															\
		k.Out = k.OutPresat;																\
		k.Out = (k.Out < v.Max) ? k.Out : v.Max;											\
		k.Out = (k.Out > v.IMin) ? k.Out : v.IMin;											\
		/* Store outputs */																	\
		k.Out2 = k.Out1;																	\
		k.Out1 = k.Out;																		\
		/* Saturated output */																\
		k.Out = ((k.Out > v.Min) ? k.Out : v.Min);


#endif /* CNTL_2P2Z_CLA_H_ */
