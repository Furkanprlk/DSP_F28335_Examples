#ifndef SPLL_1ph_IQ_H_
#define SPLL_1ph_IQ_H_

#define SPLL_Q _IQ21
#define SPLL_Qmpy _IQ21mpy

//*********** Structure Definition ********//
typedef struct{
	int32	B2_notch;
	int32	B1_notch;
	int32	B0_notch;
	int32	A2_notch;
	int32	A1_notch;
}SPLL_1ph_IQ_NOTCH_COEFF; 

typedef struct{
	int32	B1_lf;
	int32	B0_lf;
	int32	A1_lf;
}SPLL_1ph_IQ_LPF_COEFF;

typedef struct{
	int32	AC_input;
	int32	theta[2];
	int32	cos[2];
	int32	sin[2];
	int32	wo;
	int32	wn;
	
	SPLL_1ph_IQ_NOTCH_COEFF notch_coeff;
	SPLL_1ph_IQ_LPF_COEFF	lpf_coeff;
		
	int32	Upd[3];
	int32	ynotch[3];
	int32	ylf[2];
	int32	delta_t;
}SPLL_1ph_IQ;

//*********** Function Declarations *******//
void SPLL_1ph_IQ_init(int Grid_freq, long DELTA_T, SPLL_1ph_IQ *spll);
void SPLL_1ph_IQ_notch_coeff_update(float delta_T, float wn,float c2, float c1, SPLL_1ph_IQ *spll_obj);
void SPLL_1ph_IQ_FUNC(SPLL_1ph_IQ *spll1);

//*********** Macro Definition ***********//
#define SPLL_1ph_IQ_MACRO(v)						 																																															\
	/* Phase Detect*/								 																																															\
	v.Upd[0]=SPLL_Qmpy(v.AC_input,v.cos[1]);		 																																															\
	/* Notch Filter*/								 																																															\
	v.ynotch[0]=-SPLL_Qmpy(v.notch_coeff.A1_notch,v.ynotch[1])-SPLL_Qmpy(v.notch_coeff.A2_notch,v.ynotch[2])+SPLL_Qmpy(v.notch_coeff.B0_notch,v.Upd[0])+SPLL_Qmpy(v.notch_coeff.B1_notch,v.Upd[1])+SPLL_Qmpy(v.notch_coeff.B2_notch,v.Upd[2]);	\
	/* Update Upd Array for future use*/			 																																															\
	v.Upd[2]=v.Upd[1];								 																																															\
	v.Upd[1]=v.Upd[0];								 																																															\
	/* LPF*/										 																																															\
	v.ylf[0]=-SPLL_Qmpy(v.lpf_coeff.A1_lf,v.ylf[1])+SPLL_Qmpy(v.lpf_coeff.B0_lf,v.ynotch[0])+SPLL_Qmpy(v.lpf_coeff.B1_lf,v.ynotch[1]);																											\
	/* Update Array for future use*/				 																																															\
	v.ynotch[2]=v.ynotch[1];						 																																															\
	v.ynotch[1]=v.ynotch[0];						 																																															\
	v.ylf[1]=v.ylf[0];								 																																															\
	/*VCO*/											 																																															\
	v.wo=v.wn+v.ylf[0];								 																																															\
	/* integration process */						 																																															\
	v.sin[0]=v.sin[1]+SPLL_Qmpy((SPLL_Qmpy(v.delta_t,v.wo)),v.cos[1]);																																											\
	v.cos[0]=v.cos[1]-SPLL_Qmpy((SPLL_Qmpy(v.delta_t,v.wo)),v.sin[1]);																																											\
	if(v.sin[0]>SPLL_Q(0.99))						 																																															\
		v.sin[0]=SPLL_Q(0.99);						 																																															\
	else if(v.sin[0]<SPLL_Q(-0.99))					 																																															\
		v.sin[0]=SPLL_Q(-0.99);						 																																															\
	if(v.cos[0]>SPLL_Q(0.99))						 																																															\
		v.cos[0]=SPLL_Q(0.99);						 																																															\
	else if(v.cos[0]<SPLL_Q(-0.99))					 																																															\
		v.cos[0]=SPLL_Q(-0.99);						 																																															\
	v.theta[0]=v.theta[1]+SPLL_Qmpy(SPLL_Qmpy(v.wo,SPLL_Q(0.159154943)),v.delta_t);																																								\
	if(v.sin[0]>SPLL_Q(0.0) && v.sin[1]<=SPLL_Q(0.0))					 																																										\
	{																	 																																										\
		v.theta[0]=SPLL_Q(0.0);											 																																										\
	}																	 																																										\
	v.theta[1]=v.theta[0];												 																																										\
	v.sin[1]=v.sin[0];													 																																										\
	v.cos[1]=v.cos[0];													 																																										\
		

#endif /* SPLL_1ph_IQ_H_ */
