#include "Solar_IQ.h"

//*********** Structure Init Function ****//
void DQ0_ABC_IQ_init(DQ0_ABC_IQ *v)
{
	v->a=0;
	v->b=0;
	v->c=0;
	v->alpha=0;
	v->beta=0;
	v->z=0;
	v->d=0;
	v->q=0;
}

//*********** Function Definition ********//
void DQ0_ABC_IQ_FUNC(DQ0_ABC_IQ *v)
{
	v->alpha = _IQmpy(v->d,v->cos) - _IQmpy(v->q,v->sin);
	v->beta  = _IQmpy(v->d,v->sin) + _IQmpy(v->q,v->cos);
	v->a = v->alpha;
	v->b = -_IQmpy(_IQ(0.5),v->alpha) + _IQmpy(_IQ(0.8660254),v->beta);
	v->c = -_IQmpy(_IQ(0.5),v->alpha) - _IQmpy(_IQ(0.8660254),v->beta);
}

