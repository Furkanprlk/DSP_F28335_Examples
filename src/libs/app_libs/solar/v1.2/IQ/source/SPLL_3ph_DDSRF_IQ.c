#include "Solar_IQ.h"

//*********** Structure Init Function ****//
void SPLL_3ph_DDSRF_IQ_init(int Grid_freq, long DELTA_T, long k1, long k2, SPLL_3ph_DDSRF_IQ *spll_obj)
{
	spll_obj->d_p=SPLL_DDSRF_Q(0.0);
	spll_obj->d_n=SPLL_DDSRF_Q(0.0);

	spll_obj->q_p=SPLL_DDSRF_Q(0.0);
	spll_obj->q_n=SPLL_DDSRF_Q(0.0);

	spll_obj->d_p_decoupl=SPLL_DDSRF_Q(0.0);
	spll_obj->d_n_decoupl=SPLL_DDSRF_Q(0.0);

	spll_obj->q_p_decoupl=SPLL_DDSRF_Q(0.0);
	spll_obj->q_n_decoupl=SPLL_DDSRF_Q(0.0);

	spll_obj->d_p_decoupl_lpf=SPLL_DDSRF_Q(0.0);
	spll_obj->d_n_decoupl_lpf=SPLL_DDSRF_Q(0.0);

	spll_obj->q_p_decoupl_lpf=SPLL_DDSRF_Q(0.0);
	spll_obj->q_n_decoupl_lpf=SPLL_DDSRF_Q(0.0);

	spll_obj->y[0]=SPLL_DDSRF_Q(0.0);
	spll_obj->y[1]=SPLL_DDSRF_Q(0.0);

	spll_obj->x[0]=SPLL_DDSRF_Q(0.0);
	spll_obj->x[1]=SPLL_DDSRF_Q(0.0);

	spll_obj->w[0]=SPLL_DDSRF_Q(0.0);
	spll_obj->w[1]=SPLL_DDSRF_Q(0.0);

	spll_obj->z[0]=SPLL_DDSRF_Q(0.0);
	spll_obj->z[1]=SPLL_DDSRF_Q(0.0);

	spll_obj->k1=k1;
	spll_obj->k2=k2;

	spll_obj->v_q[0]=SPLL_DDSRF_Q(0.0);
	spll_obj->v_q[1]=SPLL_DDSRF_Q(0.0);

	spll_obj->ylf[0]=SPLL_DDSRF_Q(0.0);
	spll_obj->ylf[1]=SPLL_DDSRF_Q(0.0);

	spll_obj->fo=SPLL_DDSRF_Q(0.0);
	spll_obj->fn=SPLL_DDSRF_Q(Grid_freq);

	spll_obj->theta[0]=SPLL_DDSRF_Q(0.0);
	spll_obj->theta[1]=SPLL_DDSRF_Q(0.0);

	// loop filter coefficients for 20kHz
	spll_obj->lpf_coeff.B0_lf=_IQ22(166.9743);
	spll_obj->lpf_coeff.B1_lf=_IQ22(-166.266);
	spll_obj->lpf_coeff.A1_lf=_IQ22(-1.0);


	spll_obj->delta_T=DELTA_T;
}

//*********** Function Definition ********//
void SPLL_3ph_DDSRF_IQ_FUNC(SPLL_3ph_DDSRF_IQ *spll_obj)
{
	// before calling this routine run the ABC_DQ0_Pos_Neg and update the values for d_p,d_n,q_p,q_n
	// and update the cos_2theta and sin_2theta values with the prev angle

	//-------------------------//
	// Decoupling Network      //
	//-------------------------//
	spll_obj->d_p_decoupl=spll_obj->d_p - SPLL_DDSRF_Qmpy(spll_obj->d_n_decoupl_lpf,spll_obj->cos_2theta) - SPLL_DDSRF_Qmpy(spll_obj->q_n_decoupl,spll_obj->sin_2theta);
	spll_obj->q_p_decoupl=spll_obj->q_p + SPLL_DDSRF_Qmpy(spll_obj->d_n_decoupl_lpf,spll_obj->sin_2theta) - SPLL_DDSRF_Qmpy(spll_obj->q_n_decoupl,spll_obj->cos_2theta);

	spll_obj->d_n_decoupl=spll_obj->d_n - SPLL_DDSRF_Qmpy(spll_obj->d_p_decoupl_lpf,spll_obj->cos_2theta) + SPLL_DDSRF_Qmpy(spll_obj->q_p_decoupl,spll_obj->sin_2theta);
	spll_obj->q_n_decoupl=spll_obj->q_n - SPLL_DDSRF_Qmpy(spll_obj->d_p_decoupl_lpf,spll_obj->sin_2theta) - SPLL_DDSRF_Qmpy(spll_obj->q_p_decoupl,spll_obj->cos_2theta);

	//-------------------------//
	// Low pass filter         //
	//-------------------------//

	spll_obj->y[1]=SPLL_DDSRF_Qmpy(spll_obj->d_p_decoupl,spll_obj->k1)-SPLL_DDSRF_Qmpy(spll_obj->y[0],spll_obj->k2);
	spll_obj->d_p_decoupl_lpf=spll_obj->y[1]+spll_obj->y[0];
	spll_obj->y[0]=spll_obj->y[1];

	spll_obj->x[1]=SPLL_DDSRF_Qmpy(spll_obj->q_p_decoupl,spll_obj->k1)-SPLL_DDSRF_Qmpy(spll_obj->x[0],spll_obj->k2);
	spll_obj->q_p_decoupl_lpf=spll_obj->x[1]+spll_obj->x[0];
	spll_obj->x[0]=spll_obj->x[1];

	spll_obj->w[1]=SPLL_DDSRF_Qmpy(spll_obj->d_n_decoupl,spll_obj->k1)-SPLL_DDSRF_Qmpy(spll_obj->w[0],spll_obj->k2);
	spll_obj->d_n_decoupl_lpf=spll_obj->w[1]+spll_obj->w[0];
	spll_obj->w[0]=spll_obj->w[1];

	spll_obj->z[1]=SPLL_DDSRF_Qmpy(spll_obj->q_n_decoupl,spll_obj->k1)-SPLL_DDSRF_Qmpy(spll_obj->z[0],spll_obj->k2);
	spll_obj->q_n_decoupl_lpf=spll_obj->z[1]+spll_obj->z[0];
	spll_obj->z[0]=spll_obj->z[1];

	spll_obj->v_q[0]=spll_obj->q_p_decoupl;

	//---------------------------------//
	// Loop Filter                     //
	//---------------------------------//
	spll_obj->ylf[0]=spll_obj->ylf[1]+SPLL_DDSRF_Qmpy(spll_obj->lpf_coeff.B0_lf,spll_obj->v_q[0])+SPLL_DDSRF_Qmpy(spll_obj->lpf_coeff.B1_lf,spll_obj->v_q[1]);
	spll_obj->ylf[1]=spll_obj->ylf[0];
	spll_obj->v_q[1]=spll_obj->v_q[0];

	//---------------------------------//
	// VCO                             //
	//---------------------------------//
	spll_obj->fo=spll_obj->fn+spll_obj->ylf[0];

	spll_obj->theta[0]=spll_obj->theta[1]+SPLL_DDSRF_Qmpy(SPLL_DDSRF_Qmpy(spll_obj->fo,spll_obj->delta_T),SPLL_DDSRF_Q(2*3.1415926));
	if(spll_obj->theta[0]>SPLL_DDSRF_Q(2*3.1415926))
		spll_obj->theta[0]=spll_obj->theta[0]-SPLL_DDSRF_Q(2*3.1415926);

	spll_obj->theta[1]=spll_obj->theta[0];
}

