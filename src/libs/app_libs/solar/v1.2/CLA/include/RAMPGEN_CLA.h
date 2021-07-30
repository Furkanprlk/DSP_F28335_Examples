#ifndef RAMPGEN_CLA_H
#define RAMPGEN_CLA_H

//*********** Structure Definition ********//
typedef struct {
	float32  Freq; 			// Input: Ramp frequency (pu)
	float32  StepAngleMax;	// Parameter: Maximum step angle (pu)
	float32  Angle;			// Variable: Step angle (pu)
	float32  Out;  	 		// Output: Ramp signal (pu)
} RAMPGEN_CLA;

//*********** Structure Init Macro *******//
#define RAMPGEN_CLA_init(v)	\
	v.Freq=0;				\
	v.StepAngleMax=0;		\
	v.Angle=0;				\
	v.Out=0;				\

//*********** Macro Definition ***********//
#define RAMPGEN_CLA_MACRO(v)				\
/* Compute the angle rate */				\
	v.Angle += (v.StepAngleMax*v.Freq);		\
/* Saturate the angle rate within (0,1) */	\
	if (v.Angle>(1.0))						\
		v.Angle -= (1.0);					\
	v.Out=v.Angle;


#endif /* RAMPGEN_CLA_H_ */
