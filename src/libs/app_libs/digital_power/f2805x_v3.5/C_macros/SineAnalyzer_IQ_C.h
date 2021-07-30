//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================
#ifndef _SineAnalyzer_H_
#define _SineAnalyzer_H_

typedef struct {  _iq  Vin;   				// Input: Sine Signal
				  _iq  SampleFreq;   		// Input: Signal Sampling Freq
				  _iq  Threshold;   		// Input: Voltage level corresponding to zero i/p
				  _iq  Vrms;   				// Output: RMS Value
				  _iq  Vavg;   				// Output: Average Value
				  _iq  SigFreq;   			// Output: Signal Freq
				  Uint16  ZCD;   			// Output: Zero Cross detected
				  Uint16  PositiveCycle;    // Output: Positive cycle
				  } SineAnalyzer;	            

typedef SineAnalyzer *SineAnalyzer_handle;

//-----------------------------------------------------------------------------
//Default initalizer for the SineAnalyzer object.
//-----------------------------------------------------------------------------                     

#define SineAnalyzer_DEFAULTS { _IQ(0.0), 	\
                           _IQ(0.0), 	\
                           _IQ(1.65),	\
                           _IQ(0.0), 	\
                           _IQ(0.0), 	\
                           _IQ(0.0),	\
                           0,			\
                           0,			\
                           }
                           
//------------------------------------------------------------------------------
// 	Sine Analyser Macro Definition
//------------------------------------------------------------------------------

_iq15 Vacc_avg ;
_iq15 Vacc_rms ;
_iq15 curr_sample_norm; // normalized value of current sample
Uint16 prev_sign =1;
Uint16 curr_sign =1;
Uint32 nsamples =0;	// samples in half cycle mains 
_iq15 inv_nsamples;
_iq15 inv_sqrt_nsamples;

#define SineAnalyzer_MACRO(v)					\
	if ( v.Vin > v.Threshold)						\
	{												\
		/*curr_sample_norm = v.Vin - v.Threshold;*/	\
		curr_sample_norm = v.Vin;					\
		curr_sign = 1;								\
	}												\
	else											\
	{												\
	/*	curr_sample_norm =  v.Threshold - v.Vin;*/	\
		curr_sample_norm = v.Vin;					\
		curr_sign = 0;								\
	}												\
	v.PositiveCycle = curr_sign;					\
	if((prev_sign != curr_sign) && (curr_sign == 1))		\
	{ 														\
    	v.ZCD=1;											\
    	inv_nsamples = _IQ15div(_IQ15(1.0), (nsamples<<15));				\
    	inv_sqrt_nsamples = _IQ15isqrt(nsamples<<15);						\
    	v.Vavg = _IQ15mpy(Vacc_avg, inv_nsamples);							\
    	v.Vrms = _IQ15mpy(_IQ15sqrt(Vacc_rms), _IQ15isqrt(nsamples<<15));	\
    	v.SigFreq = (_IQ15mpy(v.SampleFreq, inv_nsamples)>>1); \
    	prev_sign = curr_sign;						\
    	Vacc_avg = 0;								\
    	Vacc_rms = 0;								\
    	nsamples=0;									\
	}												\
	else											\
	{												\
		nsamples++;									\
		Vacc_avg = Vacc_avg+curr_sample_norm;		\
		Vacc_rms = Vacc_rms+_IQ15mpy(curr_sample_norm,curr_sample_norm);		\
		v.ZCD=0;									\
		prev_sign = curr_sign;						\
	}

#endif /*SineAnalyzer_INCC_H_*/
