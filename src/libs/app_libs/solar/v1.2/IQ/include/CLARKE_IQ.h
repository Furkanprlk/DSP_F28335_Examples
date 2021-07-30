#ifndef CLARKE_IQ_H_
#define CLARKE_IQ_H

//*********** Structure Definition ********//
typedef struct{
	int32 a;
	int32 b;
	int32 c;
	int32 alpha;
	int32 beta;
	int32 zero;
}CLARKE_IQ;

//*********** Function Declarations *******//
void CLARKE_IQ_init(CLARKE_IQ *v);
void CLARKE_IQ_FUNC(CLARKE_IQ *v);

//*********** Macro Definition ************//
#define CLARKE_IQ_MACRO(v) 												\
	v.alpha=_IQmpy(_IQ(0.66666666667),(v.a-_IQmpy(_IQ(0.5),(v.b+v.c))));\
	v.beta =_IQmpy(_IQ(0.57735026913),(v.b-v.c));						\
	v.zero =_IQmpy(_IQ(0.33333333333),(v.a+v.b+v.c));


#endif /* CLARKE_IQ_H_ */
