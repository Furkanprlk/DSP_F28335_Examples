#ifndef PARK_IQ_H
#define PARK_IQ_H

//*********** Structure Definition ********//
typedef struct{
	int32 alpha;
	int32 beta;
	int32 zero;
	int32 sin;
	int32 cos;
	int32 d;
	int32 q;
	int32 z;
}PARK_IQ;

//*********** Function Declarations *******//
void PARK_IQ_init(PARK_IQ *v);
void PARK_IQ_FUNC(PARK_IQ *v);

//*********** Macro Definition ***********//
#define PARK_IQ_MACRO(v) 							\
	v.z =(v.zero);									\
	v.d=_IQmpy(v.alpha,v.cos)+_IQmpy(v.beta,v.sin);	\
	v.q=-_IQmpy(v.alpha,v.sin)+_IQmpy(v.beta,v.cos);


#endif /* PARK_IQ_H_ */
