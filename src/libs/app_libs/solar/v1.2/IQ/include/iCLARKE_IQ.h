#ifndef ICLARKE_IQ_H_
#define ICLARKE_IQ_H_

//*********** Structure Definition ********//
typedef struct{
	int32 a;
	int32 b;
	int32 c;
	int32 alpha;
	int32 beta;
	int32 zero;
}iCLARKE_IQ;

//*********** Function Declarations *******//
void iCLARKE_IQ_init(iCLARKE_IQ *v);
void iCLARKE_IQ_FUNC(iCLARKE_IQ *v);

//*********** Macro Definition ***********//
#define iCLARKE_IQ_MACRO(v) 														\
	v.a = (v.alpha + v.zero);														\
	v.b = (_IQmpy(_IQ(0.5),-v.alpha) + _IQmpy(_IQ(0.57735026913),v.beta) + v.zero);	\
	v.c = (_IQmpy(_IQ(0.5),-v.alpha) + _IQmpy(_IQ(0.57735026913),-v.beta) + v.zero);


#endif /* iCLARKE_IQ_H_ */
