#ifndef _SineAnalyzer_diff_H_
#define _SineAnalyzer_diff_H_

typedef struct {  _iq  Vin;   				// Input: Sine Signal
				  _iq  SampleFreq;   		// Input: Signal Sampling Freq
				  _iq  Threshold;   		// Input: Voltage level corresponding to zero i/p
				  _iq  Vrms;   				// Output: RMS Value
				  _iq  Vavg;   				// Output: Average Value
				  _iq  SigFreq;   			// Output: Signal Freq
				  Uint16  ZCD;   			// Output: Zero Cross detected
				  // internal variables
				  _iq15 Vacc_avg ;
				  _iq15 Vacc_rms ;
				  _iq15 curr_sample_norm; // normalized value of current sample
				  Uint16 prev_sign ;
				  Uint16 curr_sign ;
				  Uint32 nsamples ;			// samples in half cycle input waveform 
				  _iq15 inv_nsamples;
				  _iq15 inv_sqrt_nsamples;
				  } SineAnalyzer_diff;	            

//-----------------------------------------------------------------------------
//Default initalizer for the SineAnalyzer object.
//-----------------------------------------------------------------------------                     

#define SineAnalyzer_diff_DEFAULTS { _IQ15(0.0), 	\
                           _IQ15(0.0), 	\
                           _IQ15(0.0),	\
                           _IQ15(0.0), 	\
                           _IQ15(0.0), 	\
                           _IQ15(0.0),	\
                           0,			\
                           _IQ(0.0), 	\
                           _IQ(0.0), 	\
                           _IQ(0.0),	\
                           1,			\
                           1,			\
                           0,			\
                           _IQ(0.0), 	\
                           _IQ(0.0) }
                           
//------------------------------------------------------------------------------
// 	Sine Analyzer Macro Definition
//------------------------------------------------------------------------------

#define SineAnalyzer_diff_MACRO(v)					\
	if ( v.Vin > v.Threshold)						\
	{												\
		v.curr_sample_norm = v.Vin;					\
		v.curr_sign = 1;								\
	}												\
	else											\
	{												\
		v.curr_sample_norm = _IQ9abs(v.Vin);					\
		v.curr_sign = 0;								\
	}												\
	if((v.prev_sign != v.curr_sign) && (v.curr_sign == 1))		\
	{ 														\
    	v.ZCD=1;											\
    	v.inv_nsamples = _IQ15div(_IQ15(1.0), (v.nsamples<<15));				\
    	v.inv_sqrt_nsamples = _IQ15isqrt(v.nsamples<<15);						\
    	v.Vavg = _IQ15mpy(v.Vacc_avg, v.inv_nsamples);							\
    	v.Vrms = _IQ15mpy(_IQ15sqrt(v.Vacc_rms), _IQ15isqrt(v.nsamples<<15));	\
    	v.SigFreq = (_IQ15mpy(v.SampleFreq, v.inv_nsamples)); 			\
    	v.prev_sign = v.curr_sign;						\
    	v.Vacc_avg = 0;								\
    	v.Vacc_rms = 0;								\
    	v.nsamples=0;									\
	}												\
	else											\
	{												\
		v.nsamples++;									\
		v.Vacc_avg = v.Vacc_avg+v.curr_sample_norm;		\
		v.Vacc_rms = v.Vacc_rms+_IQ15mpy(v.curr_sample_norm,v.curr_sample_norm);		\
		v.ZCD=0;									\
		v.prev_sign = v.curr_sign;						\
	}

#endif /*SineAlanyzer_diff_INCC_H_*/
