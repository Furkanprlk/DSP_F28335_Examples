#ifndef ABC_DQ0_NEG_CLA_H
#define ABC_DQ0_NEG_CLA_H

//*********** Structure Definition ********//
typedef struct{
	float32 a;
	float32 b;
	float32 c;
	float32 alpha;
	float32 beta;
	float32 sin;
	float32 cos;
	float32 d;
	float32 q;
	float32 z;
}ABC_DQ0_NEG_CLA;

//*********** Function Declarations ********//
void ABC_DQ0_NEG_CLA_FUNC(ABC_DQ0_NEG_CLA *v);

//*********** Structure Init Macro *******//
#define ABC_DQ0_NEG_CLA_init(v)	\
	v.a=0;						\
	v.b=0;						\
	v.c=0;						\
	v.alpha=0;					\
	v.beta=0;					\
	v.z=0;						\
	v.d=0;						\
	v.q=0;						\

//*********** Macro Definition ***********//
#define ABC_DQ0_NEG_CLA_MACRO(v) 					\
	v.alpha=(0.6666666667)*(v.a - 0.5*(v.b + v.c));	\
	v.beta=(0.57735026913)*(v.b - v.c);				\
	v.z =0.57735026913*(v.a + v.b + v.c);			\
	v.d=v.alpha*v.cos - v.beta*v.sin;				\
	v.q=v.alpha*v.sin + v.beta*v.cos;				\


#endif /* ABC_DQ0_NEG_CLA_H_ */
