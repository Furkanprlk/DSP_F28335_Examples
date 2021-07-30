#ifndef DQ0_ABC_IQ_H
#define DQ0_ABC_IQ_H

//*********** Structure Definition ********//
typedef struct{
	int32 a;
	int32 b;
	int32 c;
	int32 alpha;
	int32 beta;
	int32 sin;
	int32 cos;
	int32 d;
	int32 q;
	int32 z;
}DQ0_ABC_IQ;

//*********** Function Declarations *******//
void DQ0_ABC_IQ_init(DQ0_ABC_IQ *v);
void DQ0_ABC_IQ_FUNC(DQ0_ABC_IQ *v);

//*********** Macro Definition ***********//
#define DQ0_ABC_IQ_MACRO(v) 										\
	v.alpha = _IQmpy(v.d,v.cos) - _IQmpy(v.q,v.sin);				\
	v.beta  = _IQmpy(v.d,v.sin) + _IQmpy(v.q,v.cos);				\
	v.a = v.alpha;													\
	v.b = -_IQmpy(_IQ(0.5),v.alpha) + _IQmpy(_IQ(0.8660254),v.beta);\
	v.c = -_IQmpy(_IQ(0.5),v.alpha) - _IQmpy(_IQ(0.8660254),v.beta);


#endif /* DQ0_ABC_IQ_H_ */
