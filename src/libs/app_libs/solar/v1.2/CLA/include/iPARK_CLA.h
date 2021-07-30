#ifndef IPARK_CLA_H_
#define IPARK_CLA_H_

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
}iPARK_CLA;

//*********** Function Declarations *******//
void iPARK_CLA_FUNC(iPARK_CLA *v);

//*********** Structure Init Macro *******//
#define iPARK_CLA_init(v)	\
	v.alpha=0;				\
	v.beta=0;				\
	v.zero=0;				\
	v.d=0;					\
	v.q=0;					\
	v.z=0;					\

//*********** Macro Definition ***********//
#define iPARK_CLA_MACRO(v) 			\
	v.alpha = v.d*v.cos - v.q*v.sin;\
	v.beta  = v.d*v.sin + v.q*v.cos;\
	v.zero  = v.z;					\


#endif /* iPARK_CLA_H_ */
