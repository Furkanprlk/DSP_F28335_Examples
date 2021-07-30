#ifndef SPLL_1ph_CLA_H_
#define SPLL_1ph_CLA_H_

//*********** Structure Definition ********//
typedef struct{
	float32	B2_notch;
	float32	B1_notch;
	float32	B0_notch;
	float32	A2_notch;
	float32	A1_notch;
}SPLL_1ph_CLA_NOTCH_COEFF;

typedef struct{
	float32	B1_lf;
	float32	B0_lf;
	float32	A1_lf;
}SPLL_1ph_CLA_LPF_COEFF;

typedef struct{
	float32	AC_input;
	float32	theta[2];
	float32	cos[2];
	float32	sin[2];
	float32 wo;
	float32	wn;
	
	SPLL_1ph_CLA_NOTCH_COEFF notch_coeff;
	SPLL_1ph_CLA_LPF_COEFF lpf_coeff;
		
	float32 Upd[3];
	float32	ynotch[3];
	float32	ylf[2];
	float32 delta_t;
}SPLL_1ph_CLA;

//*********** Function Declarations *******//
void SPLL_1ph_CLA_FUNC(SPLL_1ph_CLA *v);

//*********** Structure Init Macro *******//
#define SPLL_1ph_CLA_init(Grid_freq, DELTA_T, spll_obj)	\
	spll_obj.Upd[0]=(float32)(0.0);						\
	spll_obj.Upd[1]=(float32)(0.0);						\
	spll_obj.Upd[2]=(float32)(0.0);						\
														\
	spll_obj.ynotch[0]=(float32)(0.0);					\
	spll_obj.ynotch[1]=(float32)(0.0);					\
	spll_obj.ynotch[2]=(float32)(0.0);					\
														\
	spll_obj.ylf[0]=(float32)(0.0);						\
	spll_obj.ylf[1]=(float32)(0.0);						\
														\
	spll_obj.sin[0]=(float32)(0.0);						\
	spll_obj.sin[1]=(float32)(0.0);						\
														\
	spll_obj.cos[0]=(float32)(0.999);					\
	spll_obj.cos[1]=(float32)(0.999);					\
														\
	spll_obj.theta[0]=(float32)(0.0);					\
	spll_obj.theta[1]=(float32)(0.0);					\
														\
	spll_obj.wn=(float32)(2*3.14*Grid_freq);			\
														\
	/*loop filter coefficients for 20kHz*/ 				\
	spll_obj.lpf_coeff.B0_lf=(float32)(166.9743);		\
	spll_obj.lpf_coeff.B1_lf=(float32)(-166.266);		\
	spll_obj.lpf_coeff.A1_lf=(float32)(-1.0);			\
														\
	spll_obj.delta_t=DELTA_T; 							\

//*********** Structure Coeff Macro ******//
#define SPLL_1ph_CLA_notch_coeff_update(delta_T, wn, c2, c1, spll_obj)	\
	/* Note c2<<c1 for the notch to work */								\
	float32 x,y,z;														\
	x=(float32)(2.0*c2*wn*delta_T);										\
	y=(float32)(2.0*c1*wn*delta_T);										\
	z=(float32)(wn*delta_T*wn*delta_T);									\
																		\
	spll_obj.notch_coeff.A1_notch=(float32)(y-2);						\
	spll_obj.notch_coeff.A2_notch=(float32)(z-y+1);						\
	spll_obj.notch_coeff.B0_notch=(float32)(1.0);						\
	spll_obj.notch_coeff.B1_notch=(float32)(x-2);						\
	spll_obj.notch_coeff.B2_notch=(float32)(z-x+1);						\

//*********** Macro Definition ***********//
#define SPLL_1ph_CLA_MACRO(v)																																										\
	/* Phase Detect*/																																												\
	v.Upd[0]=(v.AC_input*v.cos[1]);																																									\
	/* Notch Filter*/																																												\
	v.ynotch[0]=-(v.notch_coeff.A1_notch*v.ynotch[1])-(v.notch_coeff.A2_notch*v.ynotch[2])+(v.notch_coeff.B0_notch*v.Upd[0])+(v.notch_coeff.B1_notch*v.Upd[1])+(v.notch_coeff.B2_notch*v.Upd[2]);	\
	/* Update Upd Array for future use*/																																							\
	v.Upd[2]=v.Upd[1];																																												\
	v.Upd[1]=v.Upd[0];																																												\
	/* LPF*/																																														\
	v.ylf[0]=-(v.lpf_coeff.A1_lf*v.ylf[1])+(v.lpf_coeff.B0_lf*v.ynotch[0])+(v.lpf_coeff.B1_lf*v.ynotch[1]);																							\
	/* Update Array for future use*/																																								\
	v.ynotch[2]=v.ynotch[1];																																										\
	v.ynotch[1]=v.ynotch[0];																																										\
	v.ylf[1]=v.ylf[0];																																												\
	/*VCO*/																																															\
	v.wo=v.wn+v.ylf[0];																																												\
	/* integration process */																																										\
	v.sin[0]=v.sin[1]+(((v.delta_t*v.wo))*v.cos[1]);																																				\
	v.cos[0]=v.cos[1]-(((v.delta_t*v.wo))*v.sin[1]);																																				\
	if(v.sin[0]>(float32)(0.99))																																									\
		v.sin[0]=(float32)(0.99);																																									\
	else if(v.sin[0]<(float32)(-0.99))																																								\
		v.sin[0]=(float32)(-0.99);																																									\
	if(v.cos[0]>(float32)(0.99))																																									\
		v.cos[0]=(float32)(0.99);																																									\
	else if(v.cos[0]<(float32)(-0.99))																																								\
		v.cos[0]=(float32)(-0.99);																																									\
	v.theta[0]=v.theta[1]+((v.wo*(float32)(0.159154943))*v.delta_t);																																\
	if(v.sin[0]>(float32)(0.0) && v.sin[1]<=(float32)(0.0))																																			\
	{																																																\
		v.theta[0]=(float32)(0.0);																																									\
	}																																																\
	v.theta[1]=v.theta[0];																																											\
	v.sin[1]=v.sin[0];																																												\
	v.cos[1]=v.cos[0];																																												\


#endif /* SPLL_1ph_H_ */
