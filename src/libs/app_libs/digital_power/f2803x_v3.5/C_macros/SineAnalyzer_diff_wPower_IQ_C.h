#ifndef _SineAnalyzer_diff_wPower_IQ_C_H_
#define _SineAnalyzer_diff_wPower_IQ_C_H_

typedef struct {  _iq  Vin;   				// Input: Sine Signal
				  _iq  SampleFreq;   		// Input: Signal Sampling Freq
				  _iq  Threshold;   		// Input: Voltage level corresponding to zero i/p
				  _iq  Vrms;   				// Output: RMS Value
				  _iq  Vavg;   				// Output: Average Value
				  _iq  SigFreq;   			// Output: Signal Freq
				  _iq  Iin;   				// Input Current Signal
				  _iq  Irms;   				// Output: RMS Value of current
				  _iq  Prms;   				// Output: RMS Value of input power
				  Uint16  ZCD;   			// Output: Zero Cross detected
				  _iq15 sum_Vacc_avg;		// Internal : running sum for vacc_avg calculation over one sine cycle
				  _iq15 sum_Vacc_rms;       // Internal : running sum for vacc_rms calculation over one sine cycle
				  _iq15 sum_Iacc_rms;       // Internal : running sum for Iacc_rms calculation over one sine cycle
				  _iq15 sum_Pacc_rms;       // Internal : running sum for Pacc_rms calculation over one sine cycle
				  _iq15 curr_vin_norm; 		//Internal: Normalized value of the input voltage
				  _iq15 curr_iin_norm; 		//Internal: Normalized value of the input current
				  Uint16 prev_sign;			//Internal: Flag to detect ZCD
				  Uint16 curr_sign;         //Internal: Flag to detect ZCD
				  Uint32 nsamples;			//Internal: No of samples in one cycle of the sine wave
				  _iq inv_nsamples;			//Internal: 1/( No of samples in one cycle of the sine wave)
				  _iq inv_sqrt_nsamples;	//Internal: sqrt(1/( No of samples in one cycle of the sine wave))
				  Uint16 slew_power_update; //Internal: used to slew update of the power value
				  _iq sum_Pacc_mul;			//Internal: used to sum Pac value over multiple sine cycles (100)
				  } SineAnalyzer_diff_wPower_IQ_C;

typedef SineAnalyzer_diff_wPower_IQ_C *SineAnalyzer_diff_wPower_IQ_C_handle;

//-----------------------------------------------------------------------------
// Initalizer for the  object.
//-----------------------------------------------------------------------------                     
/*
 * Initial values for  structure.
 */
#define SineAnalyzer_diff_wPower_IQ_C_VAR_INIT(v)				\
	v.Vin=0;													\
	v.SampleFreq=0;												\
	v.Threshold=0;												\
	v.Vrms=0;													\
	v.Vavg=0;													\
	v.SigFreq=0;												\
	v.Iin=0;													\
	v.Irms=0;													\
	v.Prms=0;													\
	v.ZCD=0;													\
	v.sum_Vacc_avg=0;											\
	v.sum_Vacc_rms=0;											\
	v.sum_Iacc_rms=0;											\
	v.sum_Pacc_rms=0;											\
	v.curr_vin_norm=0;											\
	v.curr_iin_norm=0;											\
	v.prev_sign=1;												\
	v.curr_sign=1;												\
	v.nsamples=0;												\
	v.inv_nsamples=0;											\
	v.inv_sqrt_nsamples=0;										\
	v.slew_power_update=0; 										\
	v.sum_Pacc_mul=0;
                           
//------------------------------------------------------------------------------
// 	Macro Definition
//------------------------------------------------------------------------------

#define SineAnalyzer_diff_wPower_IQ_C_MACRO(v)					\
	if ( v.Vin > v.Threshold)									\
	{															\
		v.curr_vin_norm = v.Vin;								\
		v.curr_iin_norm = v.Iin;								\
		v.curr_sign = 1;										\
	}															\
	else														\
	{															\
		v.curr_vin_norm = _IQ15abs(v.Vin);						\
		v.curr_iin_norm = _IQ15abs(v.Iin);						\
		v.curr_sign = 0;										\
	}															\
	if((v.prev_sign != v.curr_sign) && (v.curr_sign == 1))		\
	{ 															\
    	v.ZCD=1;												\
    	v.inv_nsamples = _IQ15div(_IQ15(1.0), (v.nsamples<<15));\
    	v.inv_sqrt_nsamples = _IQ15isqrt(v.nsamples<<15);		\
    	v.Vavg = _IQ15mpy(v.sum_Vacc_avg, v.inv_nsamples);			\
    	v.Vrms = _IQ15mpy(_IQ15sqrt(v.sum_Vacc_rms),v.inv_sqrt_nsamples);	\
    	v.Irms = _IQ15rmpy(_IQ15sqrt(v.sum_Iacc_rms),v.inv_sqrt_nsamples);	\
    	v.slew_power_update++ ;							\
		if(v.slew_power_update >= 101)							\
		{														\
			v.slew_power_update=0;								\
			v.Prms = _IQ15mpy(v.sum_Pacc_mul, _IQ15(0.01));			\
			v.sum_Pacc_mul = 0;											\
		}														\
		else													\
		{														\
			v.sum_Pacc_mul = v.sum_Pacc_mul + _IQ15rmpy(v.sum_Pacc_rms, v.inv_nsamples);	\
		}														\
    	v.SigFreq = (_IQ15mpy(v.SampleFreq, v.inv_nsamples)>>1); \
    	v.prev_sign = v.curr_sign;								\
    	v.sum_Vacc_avg = 0;											\
    	v.sum_Vacc_rms = 0;											\
    	v.sum_Iacc_rms = 0;											\
    	v.sum_Pacc_rms = 0;											\
    	v.nsamples=0;											\
	}															\
	else														\
	{															\
		v.nsamples++;											\
		v.sum_Vacc_avg = v.sum_Vacc_avg+v.curr_vin_norm;				\
		v.sum_Vacc_rms = v.sum_Vacc_rms+_IQ15rsmpy(v.curr_vin_norm,v.curr_vin_norm);		\
		v.sum_Iacc_rms = v.sum_Iacc_rms+_IQ15rsmpy(v.curr_iin_norm,v.curr_iin_norm);		\
		v.sum_Pacc_rms = v.sum_Pacc_rms+_IQ15rsmpy(v.curr_iin_norm,v.curr_vin_norm);		\
		v.ZCD=0;												\
		v.prev_sign = v.curr_sign;								\
	}												

#endif /*SineAlanyzer_diff_wPower_IQ_C_H_*/
