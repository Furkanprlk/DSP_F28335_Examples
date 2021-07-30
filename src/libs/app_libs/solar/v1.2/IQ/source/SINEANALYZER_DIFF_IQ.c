#include "Solar_IQ.h"

//*********** Structure Init Function ****//
void SINEANALYZER_DIFF_IQ_init(SINEANALYZER_DIFF_IQ *v){
	v->Vin=_IQ15(0.0);
	v->SampleFreq=_IQ15(0.0);
	v->Threshold=_IQ15(0.0);
	v->Vrms=_IQ15(0.0);
	v->Vavg=_IQ15(0.0);
	v->Vema=_IQ15(0.0);
	v->SigFreq=_IQ(0.0);
	v->ZCD=0;
	v->Vacc_avg=_IQ15(0.0);
	v->Vacc_rms=_IQ15(0.0);
	v->Vacc_ema=_IQ15(0.0);
	v->curr_sample_norm=_IQ15(0.0);
	v->prev_sign=1;
	v->curr_sign=1;
	v->nsamples=0;
	v->nsamplesMin=0;
	v->nsamplesMax=0;
	v->inv_nsamples=_IQ15(0.0);
	v->inv_sqrt_nsamples=_IQ15(0.0);
}

//*********** Function Definition ********//
void SINEANALYZER_DIFF_IQ_FUNC(SINEANALYZER_DIFF_IQ *v)
{
	if ( v->Vin > v->Threshold)
	{
		v->curr_sample_norm = v->Vin;
		v->curr_sign = 1;
	}
	else
	{
		v->curr_sample_norm = _IQ15abs(v->Vin);
		v->curr_sign = 0;
	}
	if((v->prev_sign != v->curr_sign) && (v->curr_sign == 1))
	{
    	v->ZCD=1;
		v->inv_nsamples = _IQ15div(_IQ15(1.0), (v->nsamples<<15));
		v->inv_sqrt_nsamples = _IQ15isqrt(v->nsamples<<15);
    	if(v->nsamplesMin < v->nsamples < v->nsamplesMax)
    	{
			v->Vavg = _IQ15mpy(v->Vacc_avg, v->inv_nsamples);
			v->Vrms = _IQ15mpy(_IQ15sqrt(v->Vacc_rms), _IQ15isqrt(v->nsamples<<15));
			v->Vema = v->Vacc_ema;
    	}
    	else
    	{
    		v->Vavg = 0;
    		v->Vrms = 0;
    		v->Vema = 0;
    	}
    	v->SigFreq = (_IQ15mpy(v->SampleFreq, v->inv_nsamples));
    	v->prev_sign = v->curr_sign;
    	v->Vacc_avg = 0;
    	v->Vacc_rms = 0;
    	v->Vacc_ema = 0;
    	v->nsamples=0;
	}
	else
	{
		v->nsamples++;
		v->Vacc_avg = v->Vacc_avg+v->curr_sample_norm;
		v->Vacc_rms = v->Vacc_rms+_IQ15mpy(v->curr_sample_norm,v->curr_sample_norm);
		v->Vacc_ema = v->Vacc_ema+_IQ15mpy(_IQ15(0.01), (v->curr_sample_norm - v->Vacc_ema));
		v->ZCD=0;
		v->prev_sign = v->curr_sign;
	}
}
