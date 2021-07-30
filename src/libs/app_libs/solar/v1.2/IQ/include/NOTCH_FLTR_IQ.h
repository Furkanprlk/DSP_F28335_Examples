#ifndef NOTCH_FLTR_IQ_H_
#define NOTCH_FLTR_IQ_H_

/*********** Structure Definitions ***********/
typedef struct{
	_iq24	B2_notch;
	_iq24	B1_notch;
	_iq24	B0_notch;
	_iq24	A2_notch;
	_iq24	A1_notch;
}NOTCH_COEFF_IQ;

typedef struct{
	_iq24	Out1;
	_iq24	Out2;
	_iq24	In;
	_iq24	In1;
	_iq24 	In2;
	_iq24	Out;
}NOTCH_VARS_IQ;

//*********** Function Declarations *******//
void NOTCH_FLTR_IQ_VARS_init(NOTCH_VARS_IQ *v);
void NOTCH_FLTR_IQ_run(NOTCH_VARS_IQ *v,NOTCH_COEFF_IQ *w);
void NOTCH_FLTR_IQ_ASM(NOTCH_VARS_IQ *v,NOTCH_COEFF_IQ *w);
void NOTCH_FLTR_IQ_COEFF_Update(float32 delta_T, float32 wn,float32 c2, float32 c1, NOTCH_COEFF_IQ *notch_obj);

//*********** Macro Definition ***********//
#define NOTCH_FLTR_IQ_MACRO(v, w)		\
	v.Out=_IQ24mpy(w.A1_notch,v.Out1)+_IQ24mpy(w.A2_notch,v.Out2)+_IQ24mpy(w.B0_notch,v.In)+_IQ24mpy(w.B1_notch,v.In1)+_IQ24mpy(w.B2_notch,v.In2); \
	v.Out2=v.Out1;	\
	v.Out1=v.Out;	\
	v.In2=v.In1;	\
	v.In1=v.In;

#endif
