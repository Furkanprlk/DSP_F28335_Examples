#ifndef CNTL_PI_CLA_H_
#define CNTL_PI_CLA_H_

//*********** Structure Definition ********//

// PI control law with programmable output saturation.
// This macro uses CNTL_PI_CLA structures to store coefficients & internal values.
// The structures should be initialized with the supplied CNTL_PI_CLA_init macro.
// Within the structure the Max & Min parameters are the output bounds

typedef struct {
	float32  Ref;   			// Input: reference set-point
	float32  Fbk;   			// Input: feedback
	float32  Out;   			// Output: controller output
	float32  Kp;				// Parameter: proportional loop gain
	float32  Ki;			    // Parameter: integral gain
	float32  Umax;				// Parameter: upper saturation limit
	float32  Umin;				// Parameter: lower saturation limit
	float32  up;				// Data: proportional term
	float32  ui;				// Data: integral term
	float32  v1;				// Data: pre-saturated controller output
	float32  i1;				// Data: integrator storage: ui(k-1)
	float32  w1;				// Data: saturation record: [u(k-1) - v(k-1)]
} CNTL_PI_CLA;

//*********** Function Declarations *******//
void CNTL_PI_CLA_FUNC(CNTL_PI_CLA *v);

//*********** Structure Init Macro *******//
#define CNTL_PI_CLA_init(k)			\
	/* Initialize variables */		\
	k.Ref = 0;						\
	k.Fbk = 0;						\
	k.Out = 0;						\
	k.Kp = 0;						\
	k.Ki = 0;						\
	k.Umax = (1.0);					\
	k.Umin = (0.0);					\
	k.up = 0;						\
	k.ui = 0;						\
	k.v1 = 0;						\
	k.i1 = 0;						\
	k.w1 = 0;

//*********** Macro Definition ***********//
#define CNTL_PI_CLA_MACRO(v)							\
	/* proportional term */ 							\
	v.up = ((v.Ref - v.Fbk)*v.Kp);						\
	/* integral term */ 								\
	v.ui = (v.Out == v.v1)?((v.Ki* v.up)+ v.i1) : v.i1;	\
	v.i1 = v.ui;										\
	/* control output */ 								\
	v.v1 = (v.up + v.ui);								\
	v.Out= (v.v1> v.Umax)?v.Umax:v.v1;					\
	v.Out= (v.Out< v.Umin)?v.Umin:v.Out;				\
	

#endif /* CNTL_PI_CLA_H_ */
