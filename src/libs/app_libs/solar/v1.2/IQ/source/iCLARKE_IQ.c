#include "Solar_IQ.h"

//*********** Structure Init Function ****//
void iCLARKE_IQ_init(iCLARKE_IQ *v)
{
	v->a=0;
	v->b=0;
	v->c=0;
	v->alpha=0;
	v->beta=0;
}

//*********** Function Definition ********//
void iCLARKE_IQ_FUNC(iCLARKE_IQ *v)
{
	v->a = (v->alpha + v->zero);
	v->b = (-_IQmpy(_IQ(0.5),v->alpha) + _IQmpy(_IQ(0.57735026913),v->beta) + v->zero);
	v->c = (-_IQmpy(_IQ(0.5),v->alpha) + _IQmpy(-_IQ(0.57735026913),v->beta) + v->zero);
}

