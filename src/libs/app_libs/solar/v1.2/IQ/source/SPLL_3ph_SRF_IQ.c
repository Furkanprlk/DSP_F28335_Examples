#include "Solar_IQ.h"

//*********** Structure Init Function ****//
void SPLL_3ph_SRF_IQ_init(int Grid_freq, long DELTA_T, SPLL_3ph_SRF_IQ *spll_obj)
{
	spll_obj->v_q[0]=SPLL_SRF_Q(0.0);
	spll_obj->v_q[1]=SPLL_SRF_Q(0.0);

	spll_obj->ylf[0]=SPLL_SRF_Q(0.0);
	spll_obj->ylf[1]=SPLL_SRF_Q(0.0);

	spll_obj->fo=SPLL_SRF_Q(0.0);
	spll_obj->fn=SPLL_SRF_Q(Grid_freq);

	spll_obj->theta[0]=SPLL_SRF_Q(0.0);
	spll_obj->theta[1]=SPLL_SRF_Q(0.0);

	// loop filter coefficients for 20kHz
	spll_obj->lpf_coeff.B0_lf=_IQ21(166.9743);
	spll_obj->lpf_coeff.B1_lf=_IQ21(-166.266);
	spll_obj->lpf_coeff.A1_lf=_IQ21(-1.0);

	spll_obj->delta_T=DELTA_T;
}

//*********** Function Definition ********//
void SPLL_3ph_SRF_IQ_FUNC(SPLL_3ph_SRF_IQ *spll_obj)
{
	//update v_q[0] before calling the routine
	//---------------------------------//
	// Loop Filter                     //
	//---------------------------------//
	spll_obj->ylf[0]=spll_obj->ylf[1]+SPLL_SRF_Qmpy(spll_obj->lpf_coeff.B0_lf,spll_obj->v_q[0])+SPLL_SRF_Qmpy(spll_obj->lpf_coeff.B1_lf,spll_obj->v_q[1]);
	spll_obj->ylf[1]=spll_obj->ylf[0];
	spll_obj->v_q[1]=spll_obj->v_q[0];

	spll_obj->ylf[0]=(spll_obj->ylf[0]>SPLL_SRF_Q(200.0))?SPLL_SRF_Q(200.0):spll_obj->ylf[0];
	//---------------------------------//
	// VCO                             //
	//---------------------------------//
	spll_obj->fo=spll_obj->fn+spll_obj->ylf[0];

	spll_obj->theta[0]=spll_obj->theta[1]+SPLL_SRF_Qmpy(SPLL_SRF_Qmpy(spll_obj->fo,spll_obj->delta_T),SPLL_SRF_Q(2*3.1415926));
	if(spll_obj->theta[0]>SPLL_SRF_Q(2*3.1415926))
		spll_obj->theta[0]=spll_obj->theta[0]-SPLL_SRF_Q(2*3.1415926);

	spll_obj->theta[1]=spll_obj->theta[0];
}

