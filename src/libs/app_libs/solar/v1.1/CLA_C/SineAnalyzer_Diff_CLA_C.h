/**
 * Software module for sine wave analysis.  This module is currently released using the
 * CLAmath library.  Lower execution cycles and code size can be achieved by commenting/un-commenting
 * two lines within the macro and removing the CLAmath library include from the file and the project.
 * There is a trade off: reduce cycles but also reduce result precision.
 */
#ifndef SINEANALYZER_DIFF_CLA_C_H_
#define SINEANALYZER_DIFF_CLA_C_H_

#include "CLAmath.h"

/**
 * SineAnalyzer_Diff_CLA_C structure.
 */
typedef struct {
	// Inputs
	float32 Vin; 				// Sine signal
	float32 SampleFreq; 		// Signal sampling frequency
	float32 Threshold; 			// Voltage level corresponding to zero i/p

	// Outputs
	float32 Vrms; 				// RMS value
	float32 Vavg; 				// Average value
	float32 SigFreq; 			// Signal frequency
	float32 ZCD; 				// Zero Cross detected

	// Internal variables
	float32 Vacc_avg;
	float32 Vacc_rms;
	float32 curr_sample_norm; 	// Normalized value of current sample
	float32 prev_sign;
	float32 curr_sign;
	Uint32 nsamples; 			// Samples in half cycle input waveform
	float32 inv_nsamples;
	float32 inv_sqrt_nsamples;
} SineAnalyzer_Diff_CLA_C;

/**
 * Default values for SineAnalyzerDiff_CLA_C structure.
 */
#define SineAnalyzer_Diff_CLA_C_INIT(v)		\
	v.Vin = 0.0;							\
	v.SampleFreq = 0.0;						\
	v.Threshold = 0.0;						\
	v.Vrms = 0.0;							\
	v.Vavg = 0.0;							\
	v.SigFreq = 0.0;						\
	v.ZCD = 0;								\
	v.Vacc_avg = 0.0;						\
	v.Vacc_rms = 0.0;						\
	v.curr_sample_norm = 0.0;				\
	v.prev_sign = 1;						\
	v.curr_sign = 1;						\
	v.nsamples = 0;							\
	v.inv_nsamples = 0.0;					\
	v.inv_sqrt_nsamples = 0.0

#define SineAnalyzer_Diff_CLA_C(v)													\
	if(v.Vin > v.Threshold) {														\
		v.curr_sample_norm = v.Vin;													\
		v.curr_sign = 1;															\
	}																				\
	else {																			\
		v.curr_sample_norm = fabs(v.Vin);											\
		v.curr_sign = 0;															\
	}																				\
																					\
	if((v.prev_sign != v.curr_sign) && (v.curr_sign == 1)) {						\
    	v.ZCD = 1;																	\
    	v.inv_nsamples = 1.0 / v.nsamples;											\
    																				\
    	/* To reduce cycles comment/un-comment (switch) the following lines: */		\
    	v.inv_sqrt_nsamples = 1.0 / CLAsqrt(v.nsamples);							\
    	/* v.inv_sqrt_nsamples = __meisqrtf32(v.nsamples); */						\
    																				\
    	v.Vavg = v.Vacc_avg * v.inv_nsamples;										\
    																				\
    	/* To reduce cycles comment/un-comment (switch) the following lines: */		\
    	v.Vrms = CLAsqrt(v.Vacc_rms) * v.inv_sqrt_nsamples;							\
    	/* v.Vrms = __meinvf32(__meisqrtf32(v.Vacc_rms)) * v.inv_sqrt_nsamples;	*/	\
																					\
    	v.SigFreq = v.SampleFreq * v.inv_nsamples; 									\
    	v.prev_sign = v.curr_sign;													\
    	v.Vacc_avg = 0;																\
    	v.Vacc_rms = 0;																\
    	v.nsamples = 0;																\
	}																				\
	else {																			\
		v.nsamples++;																\
		v.Vacc_avg = v.Vacc_avg + v.curr_sample_norm;								\
		v.Vacc_rms = v.Vacc_rms + (v.curr_sample_norm * v.curr_sample_norm);		\
		v.ZCD = 0;																	\
		v.prev_sign = v.curr_sign;													\
	}

#endif /* SINEANALYZER_DIFF_CLA_C_H_ */
