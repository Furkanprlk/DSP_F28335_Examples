#include "Solar_IQ.h"

//*********** Structure Init Function ****//
void ABC_DQ0_POS_IQ_init(ABC_DQ0_POS_IQ *v){
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
void ABC_DQ0_POS_IQ_FUNC(ABC_DQ0_POS_IQ *v){
	v->alpha=_IQmpy(_IQ(0.6666666667),(v->a-_IQmpy(_IQ(0.5),(v->b+v->c))));
	v->beta=_IQmpy(_IQ(0.57735026913),(v->b-v->c));
	v->z=_IQmpy(_IQ(0.3333333333),(v->a+v->b+v->c));
	v->d=_IQmpy(v->alpha,v->cos)+_IQmpy(v->beta,v->sin);
	v->q=-_IQmpy(v->alpha,v->sin)+_IQmpy(v->beta,v->cos);
}
