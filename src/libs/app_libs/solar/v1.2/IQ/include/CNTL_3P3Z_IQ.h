#ifndef CNTL_3P3Z_IQ_H_
#define CNTL_3P3Z_IQ_H_

//*********** Structure Definition ********//

// Third order control law using an IIR filter structure with programmable output saturation.
// This macro uses CNTL_3P3Z_IQ structures to store coefficients & internal values.
// The structures should be initialized with the supplied CNTL_3P3Z_IQ_init function.
// Within the structure the Max & Min parameters are the output bounds where as the IMin parameter
// is used for saturating the lower bound while keeping an internal history.  The IMin parameter
// should not be lower than -0.9.

typedef struct {
	// Coefficients
	int32 Coeff_B3;
	int32 Coeff_B2;
	int32 Coeff_B1;
	int32 Coeff_B0;
	int32 Coeff_A3;
	int32 Coeff_A2;
	int32 Coeff_A1;

	// Output saturation limits
	int32 Max;
	int32 IMin;
	int32 Min;
} CNTL_3P3Z_IQ_COEFFS;

typedef struct {
	int32 Out1;
	int32 Out2;
	int32 Out3;
	// Internal values
	int32 Errn;
	int32 Errn1;
	int32 Errn2;
	int32 Errn3;
	// Inputs
	int32 Ref;
	int32 Fdbk;
	// Output values
	int32 Out;
} CNTL_3P3Z_IQ_VARS;

//*********** Function Declarations *******//
void CNTL_3P3Z_IQ_VARS_init(CNTL_3P3Z_IQ_VARS *k);
void CNTL_3P3Z_IQ_COEFFS_init(CNTL_3P3Z_IQ_COEFFS *v);
void CNTL_3P3Z_IQ_FUNC(CNTL_3P3Z_IQ_COEFFS *v, CNTL_3P3Z_IQ_VARS *k);
void CNTL_3P3Z_IQ_ASM(CNTL_3P3Z_IQ_COEFFS *v, CNTL_3P3Z_IQ_VARS *k);

//*********** Macro Definition ***********//
#define CNTL_3P3Z_IQ_MACRO(v, k)																											\
	/* Calculate error */																											\
	k.Errn = k.Ref - k.Fdbk;																										\
	k.Out = _IQ24mpy(v.Coeff_A3,k.Out3)+_IQ24mpy(v.Coeff_A2,k.Out2) + _IQ24mpy(v.Coeff_A1 , k.Out1) 							\
	+ _IQ24mpy(v.Coeff_B3 ,k.Errn3)+_IQ24mpy(v.Coeff_B2 ,k.Errn2) + _IQ24mpy(v.Coeff_B1 , k.Errn1) + _IQ24mpy(v.Coeff_B0 , k.Errn);	\
																																	\
	/* Update error values */																										\
	k.Errn3 = k.Errn2;																												\
	k.Errn2 = k.Errn1;																												\
	k.Errn1 = k.Errn;																												\
																																	\
	/* Determine new output */																										\
	k.Out = (k.Out < v.Max) ? k.Out : v.Max;																						\
	k.Out = (k.Out > v.IMin) ? k.Out : v.IMin;																						\
																																	\
	/* Store outputs */																												\
	k.Out3 = k.Out2;																												\
	k.Out2 = k.Out1;																												\
	k.Out1 = k.Out;																													\
	/* Saturated output */																											\
	k.Out = ((k.Out > v.Min) ? k.Out : v.Min);


#endif /* CNTL_3P3Z_IQ_H_ */
