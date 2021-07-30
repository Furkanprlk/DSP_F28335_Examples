#include "Solar_IQ.h"

//*********** Structure Init Function ****//
void CNTL_PI_IQ_init(CNTL_PI_IQ *k){
	/* Initialize variables */
	k->Ref = 0;
	k->Fbk = 0;
	k->Out = 0;
	k->Kp = 0;
	k->Ki = 0;
	k->Umax = _IQ(1.0);
	k->Umin = _IQ(0.0);
	k->up = 0;
	k->ui = 0;
	k->v1 = 0;
	k->i1 = 0;
	k->w1 = 0;
}

//*********** Function Definition ********//
void CNTL_PI_IQ_FUNC(CNTL_PI_IQ *v){
	/* proportional term */
	v->up = _IQmpy((v->Ref - v->Fbk),v->Kp);

	/* integral term */
	v->ui = (v->Out == v->v1)?(_IQmpy(v->Ki, v->up)+ v->i1) : v->i1;
	v->i1 = v->ui;

	/* control output */
	v->v1 = (v->up + v->ui);
	v->Out= _IQsat(v->v1, v->Umax, v->Umin);
	/*v->w1 = (v->Out == v->v1) ? _IQ(1.0) : _IQ(0.0);*/
}

