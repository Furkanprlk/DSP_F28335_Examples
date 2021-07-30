#ifndef SPLL_1ph_SOGI_IQ_H_
#define SPLL_1ph_SOGI_IQ_H_

#define SPLL_SOGI_Q _IQ23
#define SPLL_SOGI_Qmpy _IQ23mpy
#define SPLL_SOGI_SINE _IQ23sin
#define SPLL_SOGI_COS  _IQ23cos

//*********** Structure Definition ********//
typedef struct{
	int32	osg_k;
	int32	osg_x;
	int32	osg_y;
	int32	osg_b0;
	int32	osg_b2;
	int32	osg_a1;
	int32	osg_a2;
	int32	osg_qb0;
	int32	osg_qb1;
	int32	osg_qb2;
}SPLL_1ph_SOGI_IQ_OSG_COEFF;

typedef struct{
	int32	B1_lf;
	int32	B0_lf;
	int32	A1_lf;
}SPLL_1ph_SOGI_IQ_LPF_COEFF;

typedef struct{
	int32	u[3];  // Ac Input
	int32   osg_u[3]; 
	int32   osg_qu[3];
	int32   u_Q[2];
	int32   u_D[2];
	int32   ylf[2];
	int32   fo; // output frequency of PLL
	int32   fn; //nominal frequency
	int32	theta[2];
	int32	cos;
	int32	sin;
	int32   delta_T;
	SPLL_1ph_SOGI_IQ_OSG_COEFF osg_coeff;
	SPLL_1ph_SOGI_IQ_LPF_COEFF lpf_coeff;
}SPLL_1ph_SOGI_IQ;

//*********** Function Declarations *******//
void SPLL_1ph_SOGI_IQ_init(int Grid_freq, long DELTA_T, SPLL_1ph_SOGI_IQ *spll);
void SPLL_1ph_SOGI_IQ_coeff_update(float delta_T, float wn, SPLL_1ph_SOGI_IQ *spll);
void SPLL_1ph_SOGI_IQ_FUNC(SPLL_1ph_SOGI_IQ *spll1);

//*********** Macro Definition ***********//
#define SPLL_1ph_SOGI_IQ_MACRO(v) 																																																				\
	v.osg_u[0]=SPLL_SOGI_Qmpy(v.osg_coeff.osg_b0,(v.u[0]-v.u[2]))+SPLL_SOGI_Qmpy(v.osg_coeff.osg_a1,v.osg_u[1])+SPLL_SOGI_Qmpy(v.osg_coeff.osg_a2,v.osg_u[2]); 																					\
	v.osg_u[2]=v.osg_u[1];																																																						\
	v.osg_u[1]=v.osg_u[0];																																																						\
	v.osg_qu[0]=SPLL_SOGI_Qmpy(v.osg_coeff.osg_qb0,v.u[0])+SPLL_SOGI_Qmpy(v.osg_coeff.osg_qb1,v.u[1])+SPLL_SOGI_Qmpy(v.osg_coeff.osg_qb2,v.u[2])+SPLL_SOGI_Qmpy(v.osg_coeff.osg_a1,v.osg_qu[1])+SPLL_SOGI_Qmpy(v.osg_coeff.osg_a2,v.osg_qu[2]); \
	v.osg_qu[2]=v.osg_qu[1];																																																					\
	v.osg_qu[1]=v.osg_qu[0];																																																					\
	v.u[2]=v.u[1];																																																								\
	v.u[1]=v.u[0];																																																								\
	v.u_Q[0]=SPLL_SOGI_Qmpy(v.cos,v.osg_u[0])+SPLL_SOGI_Qmpy(v.sin,v.osg_qu[0]);																																								\
	v.u_D[0]=SPLL_SOGI_Qmpy(v.cos,v.osg_qu[0])-SPLL_SOGI_Qmpy(v.sin,v.osg_u[0]);																																								\
	v.ylf[0]=v.ylf[1]+SPLL_SOGI_Qmpy(v.lpf_coeff.B0_lf,v.u_Q[0])+SPLL_SOGI_Qmpy(v.lpf_coeff.B1_lf,v.u_Q[1]);																																	\
	v.ylf[1]=v.ylf[0];																																																							\
	v.u_Q[1]=v.u_Q[0];																																																							\
	v.fo=v.fn+v.ylf[0]; 																																																						\
	v.theta[0]=v.theta[1]+SPLL_SOGI_Qmpy(SPLL_SOGI_Qmpy(v.fo,v.delta_T),SPLL_SOGI_Qmpy(SPLL_SOGI_Q(2.0),SPLL_SOGI_Q(3.1415926))); 																																				\
	if(v.theta[0]>SPLL_SOGI_Qmpy(SPLL_SOGI_Q(2.0),SPLL_SOGI_Q(3.1415926))) 																																																	\
		v.theta[0]=SPLL_SOGI_Q(0.0); 																																																			\
	v.theta[1]=v.theta[0]; 																																																						\
	v.sin=SPLL_SOGI_SINE(v.theta[0]); 																																																			\
	v.cos=SPLL_SOGI_COS(v.theta[0]);


#endif /* SPLL_1ph_SOGI_IQ_H_ */
