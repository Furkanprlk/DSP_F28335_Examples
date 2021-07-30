#include "Solar_IQ.h"

//*********** Structure Init Function ****//
void RAMPGEN_IQ_init(RAMPGEN_IQ *v)
{
	v->Freq=0;
	v->StepAngleMax=0;
	v->Angle=0;
	v->Out=0;
}

//*********** Function Definition ********//
void RAMPGEN_IQ_FUNC(RAMPGEN_IQ *v)
{
	/* Compute the angle rate */
		v->Angle += _IQmpy(v->StepAngleMax,v->Freq);
	/* Saturate the angle rate within (0,1) */
		if (v->Angle>_IQ(1.0))
			v->Angle -= _IQ(1.0);
		v->Out=v->Angle;
}
