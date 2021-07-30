#ifndef SPLL_3ph_DDSRF_CLA_H_
#define SPLL_3ph_DDSRF_CLA_H_

//*********** Structure Definition ********//
typedef struct{
	float32	B1_lf;
	float32	B0_lf;
	float32	A1_lf;
}SPLL_3ph_DDSRF_CLA_LPF_COEFF;

typedef struct{
	float32 d_p;
	float32 d_n;
	float32 q_p;
	float32 q_n;

	float32 d_p_decoupl;
	float32 d_n_decoupl;
	float32 q_p_decoupl;
	float32 q_n_decoupl;

	float32 cos_2theta;
	float32 sin_2theta;

	float32 y[2];
	float32 x[2];
	float32 w[2];
	float32 z[2];
	float32 k1;
	float32 k2;
	float32 d_p_decoupl_lpf;
	float32 d_n_decoupl_lpf;
	float32 q_p_decoupl_lpf;
	float32 q_n_decoupl_lpf;

	float32 v_q[2];
	float32 theta[2];
	float32 ylf[2];
	float32 fo;
	float32 fn;
	float32 delta_T;
	SPLL_3ph_DDSRF_CLA_LPF_COEFF lpf_coeff;
}SPLL_3ph_DDSRF_CLA;

//*********** Function Declarations *******//
void SPLL_3ph_DDSRF_CLA_FUNC(SPLL_3ph_DDSRF_CLA *v);

//*********** Structure Init Macro ********//
#define SPLL_3ph_DDSRF_CLA_init(Grid_freq, DELTA_T, k_1, k_2, spll_obj)	\
	spll_obj.d_p=(float32)(0.0);										\
	spll_obj.d_n=(float32)(0.0);										\
	spll_obj.q_p=(float32)(0.0);										\
	spll_obj.q_n=(float32)(0.0);										\
	spll_obj.d_p_decoupl=(float32)(0.0);								\
	spll_obj.d_n_decoupl=(float32)(0.0);								\
	spll_obj.q_p_decoupl=(float32)(0.0);								\
	spll_obj.q_n_decoupl=(float32)(0.0);								\
	spll_obj.d_p_decoupl_lpf=(float32)(0.0);							\
	spll_obj.d_n_decoupl_lpf=(float32)(0.0);							\
	spll_obj.q_p_decoupl_lpf=(float32)(0.0);							\
	spll_obj.q_n_decoupl_lpf=(float32)(0.0);							\
	spll_obj.y[0]=(float32)(0.0);										\
	spll_obj.y[1]=(float32)(0.0);										\
	spll_obj.x[0]=(float32)(0.0);										\
	spll_obj.x[1]=(float32)(0.0);										\
	spll_obj.w[0]=(float32)(0.0);										\
	spll_obj.w[1]=(float32)(0.0);										\
	spll_obj.z[0]=(float32)(0.0);										\
	spll_obj.z[1]=(float32)(0.0);										\
	spll_obj.k1=k_1;													\
	spll_obj.k2=k_2;													\
	spll_obj.v_q[0]=(float32)(0.0);										\
	spll_obj.v_q[1]=(float32)(0.0);										\
	spll_obj.ylf[0]=(float32)(0.0);										\
	spll_obj.ylf[1]=(float32)(0.0);										\
	spll_obj.fo=(float32)(0.0);											\
	spll_obj.fn=(float32)(Grid_freq);									\
	spll_obj.theta[0]=(float32)(0.0);									\
	spll_obj.theta[1]=(float32)(0.0);									\
	/*loop filter coefficients for 20kHz*/								\
	spll_obj.lpf_coeff.B0_lf=(float32)(166.9743);						\
	spll_obj.lpf_coeff.B1_lf=(float32)(-166.266);						\
	spll_obj.lpf_coeff.A1_lf=(float32)(-1.0);							\
	spll_obj.delta_T=DELTA_T;											\

//*********** Macro Definition ***********//
#define SPLL_3ph_DDSRF_CLA_MACRO(spll_obj)																								\
	spll_obj.d_p_decoupl = spll_obj.d_p - (spll_obj.d_n_decoupl_lpf*spll_obj.cos_2theta) - (spll_obj.q_n_decoupl*spll_obj.sin_2theta);	\
	spll_obj.q_p_decoupl = spll_obj.q_p + (spll_obj.d_n_decoupl_lpf*spll_obj.sin_2theta) - (spll_obj.q_n_decoupl*spll_obj.cos_2theta);	\
	spll_obj.d_n_decoupl = spll_obj.d_n - (spll_obj.d_p_decoupl_lpf*spll_obj.cos_2theta) + (spll_obj.q_p_decoupl*spll_obj.sin_2theta);	\
	spll_obj.q_n_decoupl = spll_obj.q_n - (spll_obj.d_p_decoupl_lpf*spll_obj.sin_2theta) - (spll_obj.q_p_decoupl*spll_obj.cos_2theta);	\
	spll_obj.y[1]=(spll_obj.d_p_decoupl*spll_obj.k1) - (spll_obj.y[0]*spll_obj.k2);														\
	spll_obj.d_p_decoupl_lpf=spll_obj.y[1] + spll_obj.y[0];																				\
	spll_obj.y[0]=spll_obj.y[1];																										\
	spll_obj.x[1]=(spll_obj.q_p_decoupl*spll_obj.k1) - (spll_obj.x[0]*spll_obj.k2);														\
	spll_obj.q_p_decoupl_lpf=spll_obj.x[1] + spll_obj.x[0];																				\
	spll_obj.x[0]=spll_obj.x[1];																										\
	spll_obj.w[1]=(spll_obj.d_n_decoupl*spll_obj.k1) - (spll_obj.w[0]*spll_obj.k2);														\
	spll_obj.d_n_decoupl_lpf=spll_obj.w[1] + spll_obj.w[0];																				\
	spll_obj.w[0]=spll_obj.w[1];																										\
	spll_obj.z[1]=(spll_obj.q_n_decoupl*spll_obj.k1) - (spll_obj.z[0]*spll_obj.k2);														\
	spll_obj.q_n_decoupl_lpf=spll_obj.z[1] + spll_obj.z[0];																				\
	spll_obj.z[0]=spll_obj.z[1];																										\
	spll_obj.v_q[0]=spll_obj.q_p_decoupl;																								\
	spll_obj.ylf[0]=spll_obj.ylf[1] + (spll_obj.lpf_coeff.B0_lf*spll_obj.v_q[0]) + (spll_obj.lpf_coeff.B1_lf*spll_obj.v_q[1]);			\
	spll_obj.ylf[1]=spll_obj.ylf[0];																									\
	spll_obj.v_q[1]=spll_obj.v_q[0];																									\
	spll_obj.fo=spll_obj.fn+spll_obj.ylf[0];																							\
	spll_obj.theta[0]=spll_obj.theta[1] + ((spll_obj.fo*spll_obj.delta_T)*(float32)(2.0*3.1415926));									\
	if(spll_obj.theta[0]>(float32)(2.0*3.1415926))																						\
		spll_obj.theta[0]=spll_obj.theta[0] - (float32)(2.0*3.1415926);																	\
	spll_obj.theta[1]=spll_obj.theta[0];																								\


#endif /* SPLL_3ph_DDSRF_CLA_H_ */
