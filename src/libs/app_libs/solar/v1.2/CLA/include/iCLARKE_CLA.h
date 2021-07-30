#ifndef ICLARKE_CLA_H_
#define ICLARKE_CLA_H_

//*********** Structure Definition ********//
typedef struct{
	float32 a;
	float32 b;
	float32 c;
	float32 alpha;
	float32 beta;
	float32 zero;
}iCLARKE_CLA;

//*********** Function Declarations *******//
void iCLARKE_CLA_FUNC(iCLARKE_CLA *v);

//*********** Structure Init Macro *******//
#define iCLARKE_CLA_init(v)	\
	v.a=0;					\
	v.b=0;					\
	v.c=0;					\
	v.alpha=0;				\
	v.beta=0;				\

//*********** Macro Definition ***********//
#define iCLARKE_CLA_MACRO(v)							\
	v.a = v.alpha + 0.5*v.zero;							\
	v.b = -0.5*v.alpha + 0.8660254*v.beta + 0.5*v.zero;	\
	v.c = -0.5*v.alpha - 0.8660254*v.beta + 0.5*v.zero;	\


#endif /* iCLARKE_CLA_H_ */
