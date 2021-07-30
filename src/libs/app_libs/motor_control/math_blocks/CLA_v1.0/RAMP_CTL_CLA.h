#ifndef __RAMP_CNTL_CLA_H__
#define __RAMP_CNTL_CLA_H__

typedef struct { float  TargetValue; 	// Input: Target input 
				 int 	RampDelayMax;	// Parameter: Maximum delay rate 			
		 	 	 float  RampLowLimit;	// Parameter: Minimum limit				  
				 float  RampHighLimit;	// Parameter: Maximum limit
				 int 	RampDelayCount; // Variable: Incremental delay 	
				 float  SetpointValue;	// Output: Target output				 
				 int 	EqualFlag;		// Output: Flag output 
				 float	Tmp;			// Variable: Temp variable
		  	   } RAMP_CNTL_CLA;	            


#define RAMP_CNTL_CLA_MACRO(v)																\
	v.Tmp = v.TargetValue - v.SetpointValue;										\
/*  0.0000305 is resolution */														\
if ((v.Tmp >= (0.0000305))||(v.Tmp <= (-0.0000305)))				    			\
{																					\
	v.RampDelayCount++	;															\
		if (v.RampDelayCount >= v.RampDelayMax)										\
		{																			\
			if (v.TargetValue >= v.SetpointValue)									\
				v.SetpointValue += 0.0000305;										\
			else																	\
				v.SetpointValue -= 0.0000305;										\
																					\
			v.SetpointValue=__mminf32(v.SetpointValue,v.RampHighLimit);				\
			v.SetpointValue=__mmaxf32(v.SetpointValue,v.RampLowLimit);				\
			v.RampDelayCount = 0;													\
																					\
		}																			\
}																					\
else 																				\
{																					\
	v.EqualFlag = 1;																\
	v.SetpointValue=v.TargetValue;													\
}

#define RAMP_CNTL_CLA_INIT(v)		\
	v.EqualFlag=0;					\
	v.RampDelayCount=0;				\
	v.RampDelayMax=5;				\
	v.RampHighLimit =1.0;			\
	v.RampLowLimit = -1.0;			\
	v.SetpointValue=0;				\
	v.TargetValue = 0.3;			\
											

#endif // __RMP_CNTL_H__
