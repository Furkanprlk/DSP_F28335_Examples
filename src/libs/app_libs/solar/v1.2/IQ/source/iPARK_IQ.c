#include "Solar_IQ.h"

//*********** Structure Init Function ****//
void iPARK_IQ_init(iPARK_IQ *v)
{
	v->alpha=0;
	v->beta=0;
	v->zero=0;
	v->d=0;
	v->q=0;
	v->z=0;
}

//*********** Function Definition ********//
void iPARK_IQ_FUNC(iPARK_IQ *v)
{
	v->alpha = (_IQmpy(v->d,v->cos) - _IQmpy(v->q,v->sin));
	v->beta  = (_IQmpy(v->d,v->sin) + _IQmpy(v->q,v->cos));
	v->zero  = v->z;
}

