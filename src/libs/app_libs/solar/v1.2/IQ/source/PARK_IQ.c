#include "Solar_IQ.h"

//*********** Structure Init Function ****//
void PARK_IQ_init(PARK_IQ *v)
{
	v->alpha=0;
	v->beta=0;
	v->zero=0;
	v->d=0;
	v->q=0;
	v->z=0;
}

//*********** Function Definition ********//
void PARK_IQ_FUNC(PARK_IQ *v)
{
	v->z =v->zero;
	v->d=_IQmpy(v->alpha,v->cos)+_IQmpy(v->beta,v->sin);
	v->q=-_IQmpy(v->alpha,v->sin)+_IQmpy(v->beta,v->cos);
}
