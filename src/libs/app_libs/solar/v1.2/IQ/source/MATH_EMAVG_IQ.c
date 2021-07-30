#include "Solar_IQ.h"

//*********** Structure Init Function ****//
void MATH_EMAVG_IQ_init(MATH_EMAVG_IQ *v){
	v->In = 0;
	v->Out = 0;
	v->Multiplier = 0;
}

//*********** Function Definition ********//
void MATH_EMAVG_IQ_FUNC(MATH_EMAVG_IQ *v){
	v->Out = (_IQmpy((v->In - v->Out), v->Multiplier) + v->Out);
}

