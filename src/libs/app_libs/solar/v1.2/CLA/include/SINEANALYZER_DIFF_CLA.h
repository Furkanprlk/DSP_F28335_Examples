#ifndef SINEANALYZER_DIFF_H_
#define SINEANALYZER_DIFF_H_

//*********** Structure Definition ********//
typedef struct {
	float32 Vin;   				// Input: Sine Signal
	float32 SampleFreq;   		// Input: Signal Sampling Freq
	float32 Threshold;   		// Input: Voltage level corresponding to zero i/p
	float32 Vrms;   			// Output: RMS Value
	float32 Vavg;   			// Output: Average Value
	float32 Vema;				// Output: Exponential Moving Average Value
	float32	SigFreq;   			// Output: Signal Freq
	uint16_t ZCD;   				// Output: Zero Cross detected
	// internal variables
	float32 Vacc_avg;
	float32 Vacc_rms;
	float32 Vacc_ema;
	float32 curr_sample_norm; 	// normalized value of current sample
	uint16_t prev_sign;
	uint16_t curr_sign;
	int32_t nsamples;			// samples in half cycle input waveform
	int32_t nsamplesMin;
	int32_t nsamplesMax;
float32 inv_nsamples;
	float32 inv_sqrt_nsamples;
} SINEANALYZER_DIFF_CLA;

//*********** Function Declarations *******//
void SINEANALYZER_DIFF_CLA_FUNC(SINEANALYZER_DIFF_CLA *v);

//*********** Structure Init Macro *******//
#define SINEANALYZER_DIFF_CLA_init(v)	\
	v.Vin=(0.0);					\
	v.SampleFreq=(0.0);				\
	v.Threshold=(0.0);				\
	v.Vrms=(0.0);					\
	v.Vavg=(0.0);					\
	v.Vema=(0.0);					\
	v.SigFreq=(0.0);				\
	v.ZCD=0;						\
	v.Vacc_avg=(0.0);				\
	v.Vacc_rms=(0.0);				\
	v.Vacc_ema=(0.0);				\
	v.curr_sample_norm=1;			\
	v.prev_sign=1;					\
	v.curr_sign=1;					\
	v.nsamples=0;					\
	v.nsamplesMin=0;				\
	v.nsamplesMax=0;				\
	v.inv_nsamples=(0.0);			\
	v.inv_sqrt_nsamples=(0.0);		\

//*********** Macro Definition ***********//
#define SINEANALYZER_DIFF_CLA_MACRO(v)										\
	if ( v.Vin > v.Threshold)												\
	{																		\
		v.curr_sample_norm = v.Vin;											\
		v.curr_sign = 1;													\
	}																		\
	else																	\
	{																		\
		v.curr_sample_norm = fabs(v.Vin);									\
		v.curr_sign = 0;													\
	}																		\
	if((v.prev_sign != v.curr_sign) && (v.curr_sign == 1))					\
	{ 																		\
    	v.ZCD=1;															\
    	v.inv_nsamples = __meinvf32(v.nsamples);							\
    	v.inv_sqrt_nsamples = __meisqrtf32(v.nsamples);						\
		if(v.nsamplesMin < v.nsamples < v.nsamplesMax)						\
		{																	\
			v.Vavg = (v.Vacc_avg* v.inv_nsamples);							\
			v.Vrms = (__meinvf32(__meisqrtf32(v.Vacc_rms))* v.inv_sqrt_nsamples);	\
			v.Vema = v.Vacc_ema;											\
		}																	\
		else																\
		{																	\
			v.Vavg = 0;														\
			v.Vrms = 0;														\
			v.Vema = 0;														\
		}																	\
		v.SigFreq = (v.SampleFreq* v.inv_nsamples); 						\
    	v.prev_sign = v.curr_sign;											\
    	v.Vacc_avg = 0;														\
    	v.Vacc_rms = 0;														\
    	v.Vacc_ema = 0;														\
    	v.nsamples=0;														\
	}																		\
	else																	\
	{																		\
		v.nsamples=v.nsamples+1;											\
		v.Vacc_avg = v.Vacc_avg+v.curr_sample_norm;							\
		v.Vacc_rms = v.Vacc_rms+(v.curr_sample_norm*v.curr_sample_norm);	\
		v.Vacc_ema = v.Vacc_ema+(0.01*(v.curr_sample_norm - v.Vacc_ema));	\
		v.ZCD=0;															\
		v.prev_sign = v.curr_sign;											\
	}																		\


#endif /* SINEANALYZER_DIFF_H_ */
