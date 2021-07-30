#ifndef SPLL_3ph_SRF_IQ_H_
#define SPLL_3ph_SRF_IQ_H_

#define SPLL_SRF_Q _IQ21
#define SPLL_SRF_Qmpy _IQ21mpy

//*********** Structure Definition ********//
typedef struct{
	int32	B1_lf;
	int32	B0_lf;
	int32	A1_lf;
}SPLL_3ph_SRF_IQ_LPF_COEFF;

typedef struct{
	int32 v_q[2];
	int32 ylf[2];
	int32 fo; // output frequency of PLL
	int32 fn; //nominal frequency
	int32 theta[2];
	int32 delta_T;
	SPLL_3ph_SRF_IQ_LPF_COEFF lpf_coeff;
}SPLL_3ph_SRF_IQ;

//*********** Function Declarations *******//
void SPLL_3ph_SRF_IQ_init(int Grid_freq, long DELTA_T, SPLL_3ph_SRF_IQ *spll);
void SPLL_3ph_SRF_IQ_FUNC(SPLL_3ph_SRF_IQ *spll_obj);

//*********** Macro Definition ***********//
#define SPLL_3ph_SRF_IQ_MACRO(spll_obj)																													\
	/*update v_q[0] before calling the routine*/																										\
	/* Loop Filter                     */																												\
	spll_obj.ylf[0]=spll_obj.ylf[1]+SPLL_SRF_Qmpy(spll_obj.lpf_coeff.B0_lf,spll_obj.v_q[0])+SPLL_SRF_Qmpy(spll_obj.lpf_coeff.B1_lf,spll_obj.v_q[1]);	\
	spll_obj.ylf[1]=spll_obj.ylf[0];																													\
	spll_obj.v_q[1]=spll_obj.v_q[0];																													\
	spll_obj.ylf[0]=(spll_obj.ylf[0]>SPLL_SRF_Q(200.0))?SPLL_SRF_Q(200.0):spll_obj.ylf[0];																\
	/* VCO                             */																												\
	spll_obj.fo=spll_obj.fn+spll_obj.ylf[0];																											\
	spll_obj.theta[0]=spll_obj.theta[1]+SPLL_SRF_Qmpy(SPLL_SRF_Qmpy(spll_obj.fo,spll_obj.delta_T),SPLL_SRF_Q(2*3.1415926));								\
	if(spll_obj.theta[0]>SPLL_SRF_Q(2*3.1415926))																										\
		spll_obj.theta[0]=spll_obj.theta[0]-SPLL_SRF_Q(2*3.1415926);																					\
	spll_obj.theta[1]=spll_obj.theta[0];																												\


#endif /* SPLL_3ph_SRF_IQ_H_ */
