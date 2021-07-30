#ifndef _SineAnalyzer_diff_H_
#define _SineAnalyzer_diff_H_

typedef struct {  float  Vin;   				// Input: Sine Signal
				  float  SampleFreq;   		// Input: Signal Sampling Freq
				  float  Threshold;   		// Input: Voltage level corresponding to zero i/p
				  float  Vrms;   				// Output: RMS Value
				  float  Vavg;   				// Output: Average Value
				  float  SigFreq;   			// Output: Signal Freq
				  Uint16  ZCD;   			// Output: Zero Cross detected
				  // internal variables
				  float Vacc_avg ;
				  float Vacc_rms ;
				  float curr_sample_norm; // normalized value of current sample
				  Uint16 prev_sign ;
				  Uint16 curr_sign ;
				  Uint32 nsamples ;			// samples in half cycle input waveform 
				  float inv_nsamples;
				  float inv_sqrt_nsamples;
				  } SineAnalyzer_diff;	            

//-----------------------------------------------------------------------------
//Default initalizer for the SineAnalyzer object.
//-----------------------------------------------------------------------------                     

#define SineAnalyzer_diff_DEFAULTS { (0.0), 	\
                           (0.0), 				\
                           (0.0),				\
                           (0.0), 				\
                           (0.0), 				\
                           (0.0),				\
                           0,					\
                           (0.0), 				\
                           (0.0), 				\
                           (0.0),				\
                           1,					\
                           1,					\
                           0,					\
                           (0.0), 				\
                           (0.0) }
                           
//------------------------------------------------------------------------------
// 	Sine Analyser Macro Definition
//------------------------------------------------------------------------------

#define SineAnalyzer_diff_MACRO(v)							\
	if ( v.Vin > v.Threshold)								\
	{														\
		v.curr_sample_norm = v.Vin;							\
		v.curr_sign = 1;									\
	}														\
	else													\
	{														\
		v.curr_sample_norm = fabs(v.Vin);					\
		v.curr_sign = 0;									\
	}														\
	if((v.prev_sign != v.curr_sign) && (v.curr_sign == 1))	\
	{ 														\
    	v.ZCD=1;											\
    	v.inv_nsamples = ((1.0)/ (v.nsamples));				\
    	v.inv_sqrt_nsamples = _IQisqrt(v.nsamples);			\
    	v.Vavg = (v.Vacc_avg* v.inv_nsamples);				\
    	v.Vrms = (sqrt(v.Vacc_rms)* v.inv_sqrt_nsamples);	\
    	v.SigFreq = (v.SampleFreq* v.inv_nsamples); 		\
    	v.prev_sign = v.curr_sign;							\
    	v.Vacc_avg = 0;										\
    	v.Vacc_rms = 0;										\
    	v.nsamples=0;										\
	}														\
	else													\
	{														\
		v.nsamples=v.nsamples+1;							\
		v.Vacc_avg = v.Vacc_avg+v.curr_sample_norm;			\
		v.Vacc_rms = v.Vacc_rms+(v.curr_sample_norm*v.curr_sample_norm);		\
		v.ZCD=0;											\
		v.prev_sign = v.curr_sign;							\
	}

#endif /*SineAlanyzer_diff_H_*/
