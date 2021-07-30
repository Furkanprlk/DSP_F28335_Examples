#ifndef __ACI_SE_CONST_CLA_H__
#define __ACI_SE_CONST_CLA_H__

typedef struct 	{ float32  Rr;				// Input: Rotor resistance (ohm) 
				  float32  Lr;				// Input: Rotor inductance (H) 	
				  float32  Tr;				// Variable: Rotor time constant 			
				  float32  fb;              // Input: Base electrical frequency (Hz)
				  float32  Wb;              // Variable: Base angular speed (rad/s)
                  float32  fc;              // Input: Cut-off frequency of lowpass filter (Hz)
                  float32  Tc;              // Variable: Time constant (sec)
				  float32  Ts;				// Input: Sampling period in sec 
			      float32  K1;				// Output: constant using in rotor flux calculation 
			      float32  K2;				// Output: constant using in rotor flux calculation 
			      float32  K3;				// Output: constant using in rotor flux calculation 
			      float32  K4;				// Output: constant using in stator current calculation 
				} ACI_SE_CONST_CLA;

/*------------------------------------------------------------------------------
	ACI_SE_CONST macro definition  
------------------------------------------------------------------------------*/


#define PI 3.14159265358979  

#define ACI_SE_CONST_CLA_MACRO(v)				\
											\
/* Rotor time constant (sec) */				\
	v.Tr = v.Lr/v.Rr;						\
											\
/* Lowpass filter time constant (sec) */	\
	v.Tc = 1/(2*PI*v.fc);					\
											\
	v.Wb = 2*PI*v.fb;						\
	v.K1 = 1/(v.Wb*v.Tr);					\
	v.K2 = 1/(v.fb*v.Ts);					\
	v.K3 = v.Tc/(v.Tc+v.Ts);				\
	v.K4 = v.Ts/(v.Tc+v.Ts); 

#define	ACI_SE_CONST_INIT_MACRO(v)		  \
      v.Rr=0;                             \
      v.Lr=0;                             \
      v.Tr=0;                             \
      v.fb=0;                             \
      v.Wb=0;                             \
      v.fc=0;                             \
      v.Tc=0;                             \
      v.Ts=0;                             \
      v.K1=0;                             \
      v.K2=0;                             \
      v.K3=0;                             \
      v.K4=0;       

#endif

