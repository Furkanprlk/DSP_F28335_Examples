#ifndef __RAMP_GEN_CLA_H__
#define __RAMP_GEN_CLA_H__

typedef struct { float  Freq; 			// Input: Ramp frequency (pu) 	
		 	     float  StepAngleMax;	// Parameter: Maximum step angle (pu)		
	 	 	     float  Angle;			// Variable: Step angle (pu)					  
			     float  Gain;			// Input: Ramp gain (pu)
			     float  Out;  	 		// Output: Ramp signal (pu) 	
			     float  Offset;			// Input: Ramp offset (pu) 				 
	  	  	   } RAMP_GEN_CLA;	            

/*------------------------------------------------------------------------------
	RAMP(Sawtooh) Generator Macro Definition
------------------------------------------------------------------------------*/                                               

#define RAMP_GEN_CLA_MACRO(v)						\
													\
/* Compute the angle rate */						\
	v.Angle += v.StepAngleMax*v.Freq;				\
													\
/* Saturate the angle rate within (-1,1) */			\
	if (v.Angle>1.0)								\
		v.Angle -= (1.0);							\
	else if (v.Angle<(-1.0))						\
		v.Angle +=(1.0);							\
		v.Out=v.Angle;

#define RAMP_GEN_CLA_INIT(v)		\
	rg1.Angle=0.0;					\
	rg1.Freq=0;						\
	rg1.StepAngleMax=BASE_FREQ*T;	\
	rg1.Out=0.0;					\
	
#endif // __RAMPGEN_H__
