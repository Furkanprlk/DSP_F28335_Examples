#ifndef NOTCH_FLTR_CLA_H_
#define NOTCH_FLTR_CLA_H_

/*********** Structure Definitions ***********/
typedef struct{
	float32	B2_notch;
	float32	B1_notch;
	float32	B0_notch;
	float32	A2_notch;
	float32	A1_notch;
}NOTCH_COEFF_CLA;

typedef struct{
	float32	Out1;
	float32	Out2;
	float32	In;
	float32	In1;
	float32 In2;
	float32	Out;
}NOTCH_VARS_CLA;

//*********** Function Declarations *******//
void NOTCH_FLTR_CLA_VARS_init(NOTCH_VARS_CLA *v);
void NOTCH_FLTR_CLA_run(NOTCH_VARS_CLA *v,NOTCH_COEFF_CLA *w);

//*********** Macro Definition ***********//
#define NOTCH_FLTR_CLA_MACRO(v, w)		\
	v.Out=(w.A1_notch*v.Out1)+(w.A2_notch*v.Out2)+(w.B0_notch*v.In)+(w.B1_notch*v.In1)+(w.B2_notch*v.In2); \
	v.Out2=v.Out1;	\
	v.Out1=v.Out;	\
	v.In2=v.In1;	\
	v.In1=v.In;

#define NOTCH_FLTR_CLA_VARS_init_MACRO(v)	\
	v.In=0;						\
	v.In1=0;						\
	v.In2=0;						\
	v.Out=0;						\
	v.Out1=0;						\
	v.Out2=0;

// Note c2<<c1 for the notch to work
#define NOTCH_FLTR_F_COEFF_Update_MACRO(delta_T, wn,c2, c1, notch_obj,x,y,z)	\
	x=(float32)(2.0*c2*wn*delta_T);			\
	y=(float32)(2.0*c1*wn*delta_T);			\
	z=(float32)(wn*delta_T*wn*delta_T);		\
	notch_obj.A1_notch=-(y-2);				\
	notch_obj.A2_notch=-(z-y+1);			\
	notch_obj.B0_notch=(1.0);				\
	notch_obj.B1_notch=(x-2);				\
	notch_obj.B2_notch=(z-x+1);

#endif
