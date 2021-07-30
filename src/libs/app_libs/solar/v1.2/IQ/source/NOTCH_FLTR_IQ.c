#include "Solar_IQ.h"

void NOTCH_FLTR_IQ_VARS_init(NOTCH_VARS_IQ *v)
{
	v->In=0;
	v->In1=0;
	v->In2=0;
	v->Out=0;
	v->Out1=0;
	v->Out2=0;
}

void NOTCH_FLTR_IQ_run(NOTCH_VARS_IQ *v,NOTCH_COEFF_IQ *w)
{
	v->Out=_IQ24mpy(w->A1_notch,v->Out1) \
			+_IQ24mpy(w->A2_notch,v->Out2)\
			+_IQ24mpy(w->B0_notch,v->In)\
			+_IQ24mpy(w->B1_notch,v->In1)\
			+_IQ24mpy(w->B2_notch,v->In2);

	v->Out2=v->Out1;
	v->Out1=v->Out;
	v->In2=v->In1;
	v->In1=v->In;
}

void NOTCH_FLTR_IQ_COEFF_Update(float32 delta_T, float32 wn,float32 c2, float32 c1, NOTCH_COEFF_IQ *notch_obj)
{
	// Note c2<<c1 for the notch to work
	float32 x,y,z;
	x=(float32)(2.0*c2*wn*delta_T);
	y=(float32)(2.0*c1*wn*delta_T);
	z=(float32)(wn*delta_T*wn*delta_T);

	notch_obj->A1_notch=-_IQ24(y-2);
	notch_obj->A2_notch=-_IQ24(z-y+1);
	notch_obj->B0_notch=_IQ24(1.0);
	notch_obj->B1_notch=_IQ24(x-2);
	notch_obj->B2_notch=_IQ24(z-x+1);
}

