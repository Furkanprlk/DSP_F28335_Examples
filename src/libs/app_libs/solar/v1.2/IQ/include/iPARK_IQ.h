#ifndef IPARK_IQ_H_
#define IPARK_IQ_H_

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
}iPARK_IQ;

//*********** Function Declarations *******//
void iPARK_IQ_init(iPARK_IQ *v);
void iPARK_IQ_FUNC(iPARK_IQ *v);

//*********** Macro Definition ***********//
#define iPARK_IQ_MACRO(v) 								\
	v.alpha = (_IQmpy(v.d,v.cos) - _IQmpy(v.q,v.sin));	\
	v.beta  = (_IQmpy(v.d,v.sin) + _IQmpy(v.q,v.cos));	\
	v.zero  = v.z;


#endif /* iPARK_IQ_H_ */
