#include "Solar_IQ.h"

//*********** Structure Init Function *****//
void CLARKE_IQ_init(CLARKE_IQ *v){
	v->a=0;
	v->b=0;
	v->c=0;
	v->alpha=0;
	v->beta=0;
}

//*********** Function Definition *********//
void CLARKE_IQ_FUNC(CLARKE_IQ *v){
	v->alpha=_IQmpy(_IQ(0.66666666667),(v->a-_IQmpy(_IQ(0.5),(v->b+v->c))));
	v->beta =_IQmpy(_IQ(0.57735026913),(v->b-v->c));
	v->zero =_IQmpy(_IQ(0.33333333333),(v->a+v->b+v->c));
}
