/**
 * Analyzes sine wave input and calculates RMS, average and frequency.  This macro requires the use
 * of square-root & inverse operations.  The operations were implemented using F specific
 * intrinsics & should be changed if library is to be ported to other platforms.  Use of the
 * SineAnalyzer_F_C structure is required and should be initialize with the
 * SineAnalyzer_F_C_INIT macro.
 */
//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================

#ifndef SINEANALYZER_F_C_H_
#define SINEANALYZER_F_C_H_

/**
 * SineAnalyzer_F_C structure.
 */
typedef struct {
	float Vin; 				// Sine signal
	float SampleFreq; 		// Signal sampling frequency
	float Threshold; 			// Voltage level corresponding to zero i/p
	float Vrms; 				// RMS value
	float Vavg; 				// Average value
	float SigFreq; 			// Signal frequency
	float ZCD; 				// Zero Cross detected
	float PositiveCycle;

	float Vacc_avg;
	float Vacc_rms;
	float curr_sample_norm; 	// Normalized value of current sample
	float prev_sign;
	float curr_sign;
	float nsamples; 			// Samples in half cycle mains
	float inv_nsamples;
	float inv_sqrt_nsamples;
} SineAnalyzer_F_C;

/**
 * Analyzes sine wave input & calculates average, RMS and frequency.
 * @param v - SineAnalyzer_F_C structure.
 * @return SineAnalyzer_F_C structure Vrms, Vavg & SigFreq parameters.
 */
#if !defined(__TMS320C28XX_CLA__)
#define SineAnalyzer_F_C(v)														\
		v.curr_sign = (v.Vin > v.Threshold) ? 1 : 0;								\
		v.curr_sample_norm = v.Vin;													\
		v.PositiveCycle = v.curr_sign;												\
		if((v.prev_sign != v.curr_sign) && (v.curr_sign == 1)) {					\
			v.ZCD = 1;																\
			v.inv_nsamples = __einvf32(v.nsamples);								\
			v.inv_sqrt_nsamples = __eisqrtf32(v.nsamples);							\
			v.Vavg = v.Vacc_avg * v.inv_nsamples;									\
			v.Vrms = __einvf32(__eisqrtf32(v.Vacc_rms)) * v.inv_sqrt_nsamples;	\
			v.SigFreq = v.SampleFreq * v.inv_nsamples;								\
			v.prev_sign = v.curr_sign;												\
			v.Vacc_avg = 0;															\
			v.Vacc_rms = 0;															\
			v.nsamples = 0;															\
		}																			\
		else {																		\
			++(v.nsamples);															\
			v.Vacc_avg = v.Vacc_avg + v.curr_sample_norm;							\
			v.Vacc_rms = v.Vacc_rms + (v.curr_sample_norm * v.curr_sample_norm);	\
			v.ZCD = 0;																\
			v.prev_sign = v.curr_sign;												\
		}

#else
#define SineAnalyzer_F_C(v)														\
		v.curr_sign = (v.Vin > v.Threshold) ? 1 : 0;								\
		v.curr_sample_norm = v.Vin;													\
		v.PositiveCycle = v.curr_sign;												\
		if((v.prev_sign != v.curr_sign) && (v.curr_sign == 1)) {					\
			v.ZCD = 1;																\
			v.inv_nsamples = __meinvf32(v.nsamples);								\
			v.inv_sqrt_nsamples = __meisqrtf32(v.nsamples);							\
			v.Vavg = v.Vacc_avg * v.inv_nsamples;									\
			v.Vrms = __meinvf32(__meisqrtf32(v.Vacc_rms)) * v.inv_sqrt_nsamples;	\
			v.SigFreq = v.SampleFreq * v.inv_nsamples;								\
			v.prev_sign = v.curr_sign;												\
			v.Vacc_avg = 0;															\
			v.Vacc_rms = 0;															\
			v.nsamples = 0;															\
		}																			\
		else {																		\
			++(v.nsamples);															\
			v.Vacc_avg = v.Vacc_avg + v.curr_sample_norm;							\
			v.Vacc_rms = v.Vacc_rms + (v.curr_sample_norm * v.curr_sample_norm);	\
			v.ZCD = 0;																\
			v.prev_sign = v.curr_sign;												\
		}
#endif

/**
 * Default values for SineAnalyzer structure.
 */
#define SineAnalyzer_F_C_INIT(v)			\
		v.Vin = 0;							\
		v.SampleFreq = 0;					\
		v.Threshold = 1.65;					\
		v.Vrms = 0;							\
		v.Vavg = 0;							\
		v.SigFreq = 0;						\
		v.ZCD = 0;							\
		v.PositiveCycle = 0;				\
		v.Vacc_avg = 0;						\
		v.Vacc_rms = 0;						\
		v.curr_sample_norm = 0;				\
		v.prev_sign = 1;					\
		v.curr_sign = 1;					\
		v.nsamples = 0;						\
		v.inv_nsamples = 0;					\
		v.inv_sqrt_nsamples = 0

#endif /* SINEANALYZER_F_C_H_ */
