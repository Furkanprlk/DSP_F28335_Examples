#ifndef __SPEED_EST_CLA_H__
#define __SPEED_EST_CLA_H__

typedef struct {
       float EstimatedTheta;  	// Input: Electrical angle (pu) 
       float OldEstimatedTheta;   // History: Electrical angle at previous step (pu)
       float EstimatedSpeed;      // Output: Estimated speed in per-unit  (pu)
       float BaseRpm;     		// Parameter: Base speed in rpm (Q0) - independently with global Q
       float K1;       			// Parameter: Constant for differentiator (Q21) - independently with global Q
       float K2;     				// Parameter: Constant for low-pass filter (pu)
       float K3;     				// Parameter: Constant for low-pass filter (pu)
       float EstimatedSpeedRpm; // Output : Estimated speed in rpm  (Q0) - independently with global Q
       float Temp;				// Variable : Temp variable
       } SPEED_ESTIMATION_CLA;  	// Data type created 


#define SE_DIFF_MAX_LIMIT  	0.85
#define SE_DIFF_MIN_LIMIT  	0.15
/*------------------------------------------------------------------------------
 SPEED_EST Macro Definition
------------------------------------------------------------------------------*/


#define SE_CLA_MACRO(v)																	\
if ((v.EstimatedTheta < SE_DIFF_MAX_LIMIT)&(v.EstimatedTheta > SE_DIFF_MIN_LIMIT))		\
	v.Temp = (v.K1*(v.EstimatedTheta - v.OldEstimatedTheta));							\
/*  */																					\
else v.Temp = (v.EstimatedSpeed);														\
																						\
/* Low-pass filter */																	\
/*  */																					\
	v.Temp = (v.K2*v.EstimatedSpeed)+(v.K3*v.Temp);										\
																						\
/* Saturate the output */																\
	v.Temp=(((v.Temp>1.0)?1.0:v.Temp)<-1)?-1:v.Temp;									\
	v.EstimatedSpeed = (v.Temp);														\
																						\
/* Update the electrical angle */														\
	v.OldEstimatedTheta = v.EstimatedTheta;												\
																						\
	v.EstimatedSpeedRpm = (v.BaseRpm*v.EstimatedSpeed); 


#define SE_CLA_INIT(v)		\
   	v.OldEstimatedTheta=0; 	\
   	v.EstimatedTheta=0;		\
    v.EstimatedSpeed=0;    	\
    v.EstimatedSpeedRpm=0; 	\
    v.Temp=0;				\
    v.BaseRpm=0;			\
    v.K1=0;					\
    v.K2=0;					\
    v.K3=0;					\
     




#endif // __SPEED_EST_H__


