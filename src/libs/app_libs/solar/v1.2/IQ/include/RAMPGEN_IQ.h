#ifndef RAMPGEN_IQ_H
#define RAMPGEN_IQ_H

//*********** Structure Definition ********//
typedef struct {
	int32  Freq; 		// Input: Ramp frequency (pu)
	int32  StepAngleMax;// Parameter: Maximum step angle (pu)
	int32  Angle;		// Variable: Step angle (pu)
	int32  Out;  	 	// Output: Ramp signal (pu)
} RAMPGEN_IQ;

//*********** Function Declarations *******//
void RAMPGEN_IQ_init(RAMPGEN_IQ *v);
void RAMPGEN_IQ_FUNC(RAMPGEN_IQ *v);

//*********** Macro Definition ***********//
#define RAMPGEN_IQ_MACRO(v)							\
/* Compute the angle rate */						\
	v.Angle += _IQmpy(v.StepAngleMax,v.Freq);		\
/* Saturate the angle rate within (0,1) */			\
	if (v.Angle>_IQ(1.0))							\
		v.Angle -= _IQ(1.0);						\
	v.Out=v.Angle;


#endif /* RAMPGEN_IQ_H_ */
