#ifndef PID_GRANDO_CLA_H_
#define PID_GRANDO_CLA_H_

//*********** Structure Definitions *******//
typedef struct {
	float32  Ref;   		// Input: reference set-point
	float32  Fbk;   		// Input: feedback
	float32  Out;   		// Output: controller output
	float32  c1;   			// Internal: derivative filter coefficient 1
	float32  c2;   			// Internal: derivative filter coefficient 2
} PID_GRANDO_CLA_TERMINALS;
// note: c1 & c2 placed here to keep structure size under 8 words

typedef struct {
	float32  Kr;			// Parameter: reference set-point weighting
	float32  Kp;			// Parameter: proportional loop gain
	float32  Ki;			// Parameter: integral gain
	float32  Kd; 		    // Parameter: derivative gain
	float32  Km; 		    // Parameter: derivative weighting
	float32  Umax;			// Parameter: upper saturation limit
	float32  Umin;			// Parameter: lower saturation limit
} PID_GRANDO_CLA_PARAMETERS;

typedef struct {
	float32  up;			// Data: proportional term
	float32  ui;			// Data: integral term
	float32  ud;			// Data: derivative term
	float32  v1;			// Data: pre-saturated controller output
	float32  i1;			// Data: integrator storage: ui(k-1)
	float32  d1;			// Data: differentiator storage: ud(k-1)
	float32  d2;			// Data: differentiator storage: d2(k-1)
	float32  w1;			// Data: saturation record: [u(k-1) - v(k-1)]
} PID_GRANDO_CLA_DATA;

typedef struct {
	PID_GRANDO_CLA_TERMINALS term;
	PID_GRANDO_CLA_PARAMETERS param;
	PID_GRANDO_CLA_DATA	data;
} PID_GRANDO_CLA;

typedef PID_GRANDO_CLA *PID_handle;

//*********** Function Declarations *******//
void PID_GRANDO_CLA_FUNC(PID_GRANDO_CLA *v);

//*********** Structure Init Function ****//
#define PID_GRANDO_CLA_init(v)	\
	v.term.Ref=0;			\
	v.term.Fbk=0;			\
	v.term.Out=0;			\
	v.term.c1=0;			\
	v.term.c2=0;			\
	v.param.Kr = (1.0);		\
	v.param.Kp = (1.0);		\
	v.param.Ki = (0.0);		\
	v.param.Kd = (0.0);		\
	v.param.Km = (1.0);		\
	v.param.Umax = (1.0);	\
	v.param.Umin = (-1.0);	\
	v.data.up = (0.0);		\
	v.data.ui = (0.0);		\
	v.data.ud = (0.0);		\
	v.data.v1 = (0.0);		\
	v.data.i1 = (0.0);		\
	v.data.d1 = (0.0);		\
	v.data.d2 = (0.0);		\
	v.data.w1 = (1.0);		\


//*********** Macro Definition ***********//
#define PID_GRANDO_CLA_MACRO(v)																		\
	/* proportional term */ 																		\
	v.data.up = (v.param.Kr* v.term.Ref) - v.term.Fbk;												\
	/* integral term */ 																			\
	v.data.ui = (v.param.Ki* (v.data.w1* (v.term.Ref - v.term.Fbk))) + v.data.i1;					\
	v.data.i1 = v.data.ui;																			\
	/* derivative term */ 																			\
	v.data.d2 = (v.param.Kd* (v.term.c1* ((v.term.Ref* v.param.Km) - v.term.Fbk))) - v.data.d2;		\
	v.data.ud = v.data.d2 + v.data.d1;																\
	v.data.d1 = (v.data.ud* v.term.c2);																\
	/* control output */ 																			\
	v.data.v1 = (v.param.Kp* (v.data.up + v.data.ui + v.data.ud));									\
	v.term.Out= __mmaxf32((__mminf32(v.param.Umax,v.data.v1)),v.param.Umin);						\
	v.data.w1 = (v.term.Out == v.data.v1) ? (1.0) : (0.0);											\
	

#endif /* PID_GRANDO_CLA_H_ */
