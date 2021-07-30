#ifndef CLARKE_CLA_H
#define CLARKE_CLA_H

//*********** Structure Definition ********//
typedef struct{
	float32 a;
	float32 b;
	float32 c;
	float32 alpha;
	float32 beta;
	float32 zero;
}CLARKE_CLA;

//*********** Function Declarations *******//
void CLARKE_CLA_FUNC(CLARKE_CLA *v);

//*********** Structure Init Macro *******//
#define CLARKE_CLA_init(v)	\
	v.a=0;					\
	v.b=0;					\
	v.c=0;					\
	v.alpha=0;				\
	v.beta=0;				\

//*********** Macro Definition ***********//
#define CLARKE_CLA_MACRO(v) 								\
	v.alpha=((0.66666666667)*(v.a - ((0.5)*(v.b+v.c))));	\
	v.beta =((0.57735026913)*(v.b - v.c));					\
	v.zero =((0.33333333333)*(v.a + v.b + v.c));			\


#endif /* CLARKE_H_ */
