#ifndef __VOLT_CALC_CLA_H__
#define __VOLT_CALC_CLA_H__

typedef struct 	{ float  DcBusVolt;		// Input: DC-bus voltage (pu)
			  	  float  MfuncV1;  		// Input: Modulation voltage phase A (pu)
		  	  	  float  MfuncV2;			// Input: Modulation voltage phase B (pu)	
		   	  	  float  MfuncV3;			// Input: Modulation voltage phase C (pu) 
                  float  OutOfPhase; 	// Parameter: Out of Phase adjustment (0 or 1)
	  	  	  	  float  VphaseA;			// Output: Phase voltage phase A (pu)
		   	  	  float  VphaseB;			// Output: Phase voltage phase B (pu) 
		  	  	  float  VphaseC;			// Output: Phase voltage phase C (pu) 
		  	  	  float  Valpha;			// Output: Stationary d-axis phase voltage (pu)
		  	  	  float  Vbeta;  			// Output: Stationary q-axis phase voltage (pu)
		  	  	  float  temp;				// Variable: temp variable
		  	  	} VOLT_CALC_CLA;	                   


/*
OutOfPhase = 1 for the out of phase correction if
* MfuncV1 is out of phase with PWM1,
* MfuncV2 is out of phase with PWM3,
* MfuncV3 is out of phase with PWM5,
otherwise, set 0 if their phases are correct.
*/

#define ONE_THIRD  (0.33333333333333)
#define TWO_THIRD  (0.66666666666667)
#define INV_SQRT3  (0.57735026918963)
/*------------------------------------------------------------------------------
 	Phase Voltage Calculation Macro Definition
------------------------------------------------------------------------------*/


#define VOLT_CALC_CLA_MACRO(v)														\
																				\
																				\
/* Scale the incomming Modulation functions with the DC bus voltage value*/		\
/* and calculate the 3 Phase voltages */										\
  v.temp 	  = (v.DcBusVolt*ONE_THIRD);									\
  v.VphaseA   = (v.temp*((v.MfuncV1*2)-v.MfuncV2-v.MfuncV3));		\
  v.VphaseB   = (v.temp*((v.MfuncV2*2)-v.MfuncV1-v.MfuncV3));		\
																				\
  if (v.OutOfPhase==0)															\
  {	  v.VphaseA=-v.VphaseA;														\
  	  v.VphaseB=-v.VphaseB;														\
  }	   																			\
/* Voltage transformation (a,b,c)  ->  (Alpha,Beta)	*/							\
  v.Valpha = v.VphaseA;															\
  v.Vbeta = ((v.VphaseA + (v.VphaseB*2))*INV_SQRT3);

// Phase C (if needed)
// v.VphaseC   = _IQmpy(v.temp,(_IQmpy2(v.MfuncV3)-v.MfuncV2-v.MfuncV1));	\

#define VOLT_CALC_INIT_MACRO(v)		\
	  v.  DcBusVolt=0;		\
  	  v.  MfuncV1=0;		\
  	  v.  MfuncV2=0;		\
  	  v.  MfuncV3=0;		\
      v.  OutOfPhase=0;		\
  	  v.  VphaseA=0;		\
  	  v.  VphaseB=0;		\
  	  v.  VphaseC=0;		\
  	  v.  Valpha=0;			\
  	  v.  Vbeta=0;			\
  	  v.  temp=0;			\

#endif // __VOLT_CALC_CLA_H__
























