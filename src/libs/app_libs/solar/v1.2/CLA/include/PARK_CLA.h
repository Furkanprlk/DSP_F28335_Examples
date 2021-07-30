#ifndef PARK_CLA_H
#define PARK_CLA_H

//*********** Structure Definition ********//
typedef struct{
	float32 alpha;
	float32 beta;
	float32 zero;
	float32 sin;
	float32 cos;
	float32 d;
	float32 q;
	float32 z;
}PARK_CLA;

//*********** Function Declarations *******//
void PARK_CLA_FUNC(PARK_CLA *v);

//*********** Structure Init Macro *******//
#define PARK_CLA_init(v)	\
	v.alpha=0;				\
	v.beta=0;				\
	v.zero=0;				\
	v.d=0;					\
	v.q=0;					\
	v.z=0;					\

//*********** Macro Definition ***********//
#define PARK_CLA_MACRO(v) 				\
	v.d= v.alpha*v.cos + v.beta*v.sin;	\
	v.q=-v.alpha*v.sin + v.beta*v.cos;	\
	v.z=v.zero;


#endif /* PARK_CLA_H_ */
