#ifndef __PI_CLA_H__
#define __PI_CLA_H__

typedef struct {  float  Ref;   			// Input: reference set-point
				  float  Fbk;   			// Input: feedback
				  float  Out;   			// Output: controller output 
				  float  Kp;				// Parameter: proportional loop gain
				  float  Ki;			    // Parameter: integral gain
				  float  Umax;			// Parameter: upper saturation limit
				  float  Umin;			// Parameter: lower saturation limit
				  float  up;				// Data: proportional term
				  float  ui;				// Data: integral term
				  float  v1;				// Data: pre-saturated controller output
				  float  i1;				// Data: integrator storage: ui(k-1)
				  float  w1;				// Data: saturation record: [u(k-1) - v(k-1)]
				} PI_CLA;


/*------------------------------------------------------------------------------
 	PI_GRANDO Macro Definition
------------------------------------------------------------------------------*/

#define PI_CLA_MACRO(v)											\
																\
	/* proportional term */ 									\
	v.up = v.Ref - v.Fbk;										\
																\
	/* integral term */ 										\
	v.ui = (v.Out == v.v1)?((v.Ki* v.up)+ v.i1) : v.i1;			\
	v.i1 = v.ui;												\
																\
	/* control output */ 										\
	v.v1 = (v.Kp* (v.up + v.ui));								\
	v.Out=__mmaxf32(__mminf32(v.v1, v.Umax),v.Umin);	
	
#define PI_CLA_INIT(v)	\
	v.Fbk=0;				\
	v.Out=0;				\
	v.Ref=0;				\
	v.i1=0;					\
	v.ui=0;					\
	v.up=0;					\
	v.v1=0;					\
	v.Kp=0;					\
	v.Ki=0;					\
	v.Umax =0;				\
	v.Umin =0;
							
#endif // __PI_H__

