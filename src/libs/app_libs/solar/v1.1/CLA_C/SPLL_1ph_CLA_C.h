/**
 * Software phase lock loop for calculating the instanteneous phase of a single phase grid.
 */

#ifndef SPLL_1PH_CLA_C_H_
#define SPLL_1PH_CLA_C_H_

/**
 * SPLL_NOTCH_COEFF internal structure.
 */
typedef struct {
	float32	B2_notch;
	float32	B1_notch;
	float32	B0_notch;
	float32	A2_notch;
	float32	A1_notch;
} SPLL_NOTCH_COEFF;

/**
 * SPLL_LPF_COEFF internal structure.
 */
typedef struct {
	float32 B1_lf;
	float32 B0_lf;
	float32 A1_lf;
} SPLL_LPF_COEFF;

/**
 * SPLL_1ph_CLA_C structure.
 */
typedef struct {
	// Inputs
	float32	AC_input;				// 1ph AC Signal measured
	float32	wn;						// Grid Frequency in cycles/s

	// Outputs
	float32	theta0;					// Grid phase angle
	float32 theta1;
	float32	cos0;					// COS (grid phase angle)
	float32 cos1;
	float32 sin0;					// SIN (grid phase angle)
	float32 sin1;

	// Internal
	float32 wo;						// Instantaneous Grid Frequency in cycles/s
	SPLL_NOTCH_COEFF notch_coeff;	// Notch Filter Coefficients
	SPLL_LPF_COEFF	 lpf_coeff;		// Loop Filer Coefficients
	float32 Upd0;					// Internal Data Buffer for phase detect output
	float32 Upd1;
	float32 Upd2;
	float32 ynotch0;				// Internal Data Buffer for the notch output
	float32 ynotch1;
	float32 ynotch2;
	float32 ylf0;					// Internal Data Buffer for Loop Filter output
	float32 ylf1;
	float32 delta_t;				// 1/Frequency of calling the PLL routine
} SPLL_1ph_CLA_C;

#define TWO_PI ((float32) 6.2831853071)
#define LIMIT ((float32) 0.99)
#define SPLL_1ph_CONST_1 ((float32) (0.00000795))

/**
 * Default values for SPLL_1ph_CLA_C structure.
 */
#define SPLL_1ph_CLA_C_INIT(v, Grid_freq, DELTA_T)	\
	/* Internal variables */						\
	v.Upd0 = 0.0;									\
	v.Upd1 = 0.0;									\
	v.Upd2 = 0.0;									\
	v.ynotch0 = 0.0;								\
	v.ynotch1 = 0.0;								\
	v.ynotch2 = 0.0;								\
	v.ylf0 = 0.0;									\
	v.ylf1 = 0.0;									\
	v.delta_t = DELTA_T;							\
	/* Outputs */									\
	v.sin0 = 0.0;									\
	v.sin1 = 0.0;									\
	v.cos0 = 0.999;									\
	v.cos1 = 0.999;									\
	v.theta0 = 0.0;									\
	v.theta1 = 0.0;									\
	/* Inputs */									\
	v.wn = (TWO_PI * Grid_freq);					\
	/* Notch filter coefficients */					\
	/* Grid frequency @ 50Hz */						\
	if(Grid_freq == 50) {							\
		v.notch_coeff.B2_notch = 0.972;				\
		v.notch_coeff.B1_notch = -1.9402;			\
		v.notch_coeff.B0_notch = 0.972;				\
		v.notch_coeff.A2_notch = 0.944;				\
		v.notch_coeff.A1_notch = -1.9402;			\
	}												\
	/* Grid frequency @ 60Hz */						\
	else if (Grid_freq == 60) {						\
		v.notch_coeff.B2_notch = 0.9969;			\
		v.notch_coeff.B1_notch = -1.9923;			\
		v.notch_coeff.B0_notch = 0.9969;			\
		v.notch_coeff.A2_notch = 0.9937;			\
		v.notch_coeff.A1_notch = -1.9923;			\
	}												\
	/* Loop filter coefficients */					\
	v.lpf_coeff.B1_lf = -247.8;						\
	v.lpf_coeff.B0_lf = 250.0;						\
	v.lpf_coeff.A1_lf = (-1.0)

/**
 * Software phase lock loop implementation.
 * @param v - SPLL_1ph_CLA_C structure.
 */
#define SPLL_1ph_CLA_C(v) 																				\
	/* Phase Detect*/																					\
	v.Upd0 = (v.AC_input * v.cos1);																		\
	/* Notch Filter*/																					\
	v.ynotch0 = -(v.notch_coeff.A1_notch * v.ynotch1) - (v.notch_coeff.A2_notch * v.ynotch2) 			\
				+ (v.notch_coeff.B0_notch * v.Upd0) + (v.notch_coeff.B1_notch * v.Upd1)					\
				+ (v.notch_coeff.B2_notch * v.Upd2);													\
	/* Update Upd Array for future use*/																\
	v.Upd2 = v.Upd1;																					\
	v.Upd1 = v.Upd0;																					\
	/* LPF*/																							\
	v.ylf0 = -(v.lpf_coeff.A1_lf * v.ylf1) + (v.lpf_coeff.B0_lf * v.ynotch0)							\
				+ (v.lpf_coeff.B1_lf * v.ynotch1);														\
	/* Update Array for future use*/																	\
	v.ynotch2 = v.ynotch1;																				\
	v.ynotch1 = v.ynotch0;																				\
	v.ylf1 = v.ylf0;																					\
	/*VCO*/																								\
	v.wo = v.wn + v.ylf0;																				\
	/* Integration process */																			\
	v.sin0 = v.sin1 + (((v.delta_t * v.wo)) * v.cos1);													\
	v.cos0 = v.cos1 - (((v.delta_t * v.wo)) * v.sin1);													\
																										\
	v.sin0 = (v.sin0 < LIMIT) ? v.sin0 : LIMIT;															\
	v.sin0 = (v.sin0 > -LIMIT) ? v.sin0 : -LIMIT;														\
																										\
	v.cos0 = (v.cos0 < LIMIT) ? v.cos0 : LIMIT;															\
	v.cos0 = (v.cos0 > -LIMIT) ? v.cos0 : -LIMIT;														\
																										\
	v.theta0 = v.theta1 + (v.wn * SPLL_1ph_CONST_1);													\
	if((v.sin0 > (0.0)) && (v.sin1 <= (0.0))) {v.theta0 = (0.0);}										\
																										\
	v.theta1 = v.theta0;																				\
	v.sin1 = v.sin0;																					\
	v.cos1 = (v.cos0)

#endif /* SPLL_1PH_CLA_C_H_ */
