#ifndef ABC_DQ0_POS_IQ_H
#define ABC_DQ0_POS_IQ_H

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
}ABC_DQ0_POS_IQ;

//*********** Function Declarations *******//
void ABC_DQ0_POS_IQ_init(ABC_DQ0_POS_IQ *v);
void ABC_DQ0_POS_IQ_FUNC(ABC_DQ0_POS_IQ *v);

//*********** Macro Definition ************//
#define ABC_DQ0_POS_IQ_MACRO(v) 										\
	v.alpha=_IQmpy(_IQ(0.6666666667),(v.a-_IQmpy(_IQ(0.5),(v.b+v.c))));	\
	v.beta=_IQmpy(_IQ(0.57735026913),(v.b-v.c));						\
	v.z=_IQmpy(_IQ(0.33333333333),(v.a+v.b+v.c));						\
	v.d=_IQmpy(v.alpha,v.cos)+_IQmpy(v.beta,v.sin);						\
	v.q=-_IQmpy(v.alpha,v.sin)+_IQmpy(v.beta,v.cos);


#endif /* ABC_DQ0_POS_IQ_H_ */
