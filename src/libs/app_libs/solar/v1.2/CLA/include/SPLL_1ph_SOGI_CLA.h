#ifndef SPLL_1ph_SOGI_CLA_H
#define SPLL_1ph_SOGI_CLA_H

//*********** Structure Definition ********//
typedef struct{
	float32	osg_k;
	float32	osg_x;
	float32	osg_y;
	float32	osg_b0;
	float32	osg_b2;
	float32	osg_a1;
	float32	osg_a2;
	float32	osg_qb0;
	float32	osg_qb1;
	float32	osg_qb2;
}SPLL_1ph_SOGI_CLA_OSG_COEFF;

typedef struct{
	float32	B1_lf;
	float32	B0_lf;
	float32	A1_lf;
}SPLL_1ph_SOGI_CLA_LPF_COEFF;

typedef struct{
	float32	u[3];  // Ac Input
	float32   osg_u[3];
	float32   osg_qu[3];
	float32   u_Q[2];
	float32   u_D[2];
	float32   ylf[2];
	float32   fo; // output frequency of PLL
	float32   fn; //nominal frequency
	float32	theta[2];
	float32	cos;
	float32	sin;
	float32   delta_T;
	SPLL_1ph_SOGI_CLA_OSG_COEFF osg_coeff;
	SPLL_1ph_SOGI_CLA_LPF_COEFF lpf_coeff;
}SPLL_1ph_SOGI_CLA;

//*********** Function Declarations *******//
void SPLL_1ph_SOGI_CLA_FUNC(SPLL_1ph_SOGI_CLA *v);

//*********** Structure Init Macro *******//
#define SPLL_1ph_SOGI_CLA_init(Grid_freq, DELTA_T, spll_obj)	\
	spll_obj.u[0]=(float32)(0.0);								\
	spll_obj.u[1]=(float32)(0.0);								\
	spll_obj.u[2]=(float32)(0.0);								\
																\
	spll_obj.osg_u[0]=(float32)(0.0);							\
	spll_obj.osg_u[1]=(float32)(0.0);							\
	spll_obj.osg_u[2]=(float32)(0.0);							\
																\
	spll_obj.osg_qu[0]=(float32)(0.0);							\
	spll_obj.osg_qu[1]=(float32)(0.0);							\
	spll_obj.osg_qu[2]=(float32)(0.0);							\
																\
	spll_obj.u_Q[0]=(float32)(0.0);								\
	spll_obj.u_Q[1]=(float32)(0.0);								\
																\
	spll_obj.u_D[0]=(float32)(0.0);								\
	spll_obj.u_D[1]=(float32)(0.0);								\
																\
	spll_obj.ylf[0]=(float32)(0.0);								\
	spll_obj.ylf[1]=(float32)(0.0);								\
																\
	spll_obj.fo=(float32)(0.0);									\
	spll_obj.fn=(float32)(Grid_freq);							\
																\
	spll_obj.theta[0]=(float32)(0.0);							\
	spll_obj.theta[1]=(float32)(0.0);							\
																\
	spll_obj.sin=(float32)(0.0);								\
	spll_obj.cos=(float32)(0.0);								\
																\
	/*loop filter coefficients for 20kHz*/						\
	spll_obj.lpf_coeff.B0_lf=(float32)(166.9743);				\
	spll_obj.lpf_coeff.B1_lf=(float32)(-166.266);				\
	spll_obj.lpf_coeff.A1_lf=(float32)(-1.0);					\
																\
	spll_obj.delta_T=DELTA_T;									\

//*********** Structure Coeff Macro ******//
#define SPLL_1ph_SOGI_CLA_coeff_update(delta_T, wn, spll)			\
	float32 osgx,osgy,temp;											\
	spll.osg_coeff.osg_k=(float32)(0.5);							\
	osgx=(float32)(2.0*0.5*wn*delta_T);								\
	spll.osg_coeff.osg_x=(float32)(osgx);							\
	osgy=(float32)(wn*delta_T*wn*delta_T);							\
	spll.osg_coeff.osg_y=(float32)(osgy);							\
	temp=(float32)1.0/(osgx+osgy+4.0);								\
	spll.osg_coeff.osg_b0=((float32)osgx*temp);						\
	spll.osg_coeff.osg_b2=((float32)(-1.0)*spll.osg_coeff.osg_b0);	\
	spll.osg_coeff.osg_a1=((float32)(2.0*(4.0-osgy))*temp);			\
	spll.osg_coeff.osg_a2=((float32)(osgx-osgy-4)*temp);			\
	spll.osg_coeff.osg_qb0=((float32)(0.5*osgy)*temp);				\
	spll.osg_coeff.osg_qb1=(spll.osg_coeff.osg_qb0*(float32)(2.0));	\
	spll.osg_coeff.osg_qb2=spll.osg_coeff.osg_qb0;					\

//*********** Macro Definition ***********//
#define SPLL_1ph_SOGI_CLA_MACRO(v) 																																					\
	v.osg_u[0]=(v.osg_coeff.osg_b0*(v.u[0]-v.u[2])) + (v.osg_coeff.osg_a1*v.osg_u[1]) + (v.osg_coeff.osg_a2*v.osg_u[2]); 															\
	v.osg_u[2]=v.osg_u[1];																																							\
	v.osg_u[1]=v.osg_u[0];																																							\
	v.osg_qu[0]=(v.osg_coeff.osg_qb0*v.u[0]) + (v.osg_coeff.osg_qb1*v.u[1]) + (v.osg_coeff.osg_qb2*v.u[2]) + (v.osg_coeff.osg_a1*v.osg_qu[1]) + (v.osg_coeff.osg_a2*v.osg_qu[2]);	\
	v.osg_qu[2]=v.osg_qu[1];																																						\
	v.osg_qu[1]=v.osg_qu[0];																																						\
	v.u[2]=v.u[1];																																									\
	v.u[1]=v.u[0];																																									\
	v.u_Q[0]=(v.cos*v.osg_u[0]) + (v.sin*v.osg_qu[0]);																																\
	v.u_D[0]=(v.cos*v.osg_qu[0]) - (v.sin*v.osg_u[0]);																																\
	v.ylf[0]=v.ylf[1] + (v.lpf_coeff.B0_lf*v.u_Q[0]) + (v.lpf_coeff.B1_lf*v.u_Q[1]);																								\
	v.ylf[1]=v.ylf[0];																																								\
	v.u_Q[1]=v.u_Q[0];																																								\
	v.fo=v.fn + v.ylf[0]; 																																							\
	v.theta[0]=v.theta[1] + ((v.fo*v.delta_T)*(float32)(2.0*3.1415926)); 																												\
	if(v.theta[0]>(float32)(2.0*3.1415926)) 																																			\
		v.theta[0]=(float32)(0.0);																																					\
	v.theta[1]=v.theta[0]; 																																							\
	v.sin=(float32)(CLAsin(v.theta[0])); 																																			\
	v.cos=(float32)(CLAcos(v.theta[0]));																																			\


#endif /* SPLL_1ph_SOGI_CLA_H_ */
