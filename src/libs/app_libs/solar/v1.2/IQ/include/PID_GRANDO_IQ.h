#ifndef PID_GRANDO_IQ_H_
#define PID_GRANDO_IQ_H_

//*********** Structure Definitions *******//
typedef struct {
	int32  Ref;  		// Input: reference set-point
	int32  Fbk;   		// Input: feedback
	int32  Out;   		// Output: controller output
	int32  c1;   		// Internal: derivative filter coefficient 1
	int32  c2;   		// Internal: derivative filter coefficient 2
} PID_GRANDO_IQ_TERMINALS;
// note: c1 & c2 placed here to keep structure size under 8 words

typedef struct {
	int32  Kr;			// Parameter: reference set-point weighting
	int32  Kp;			// Parameter: proportional loop gain
	int32  Ki;			// Parameter: integral gain
	int32  Kd; 		    // Parameter: derivative gain
	int32  Km; 		    // Parameter: derivative weighting
	int32  Umax;			// Parameter: upper saturation limit
	int32  Umin;			// Parameter: lower saturation limit
} PID_GRANDO_IQ_PARAMETERS;

typedef struct {
	int32  up;			// Data: proportional term
	int32  ui;			// Data: integral term
	int32  ud;			// Data: derivative term
	int32  v1;			// Data: pre-saturated controller output
	int32  i1;			// Data: integrator storage: ui(k-1)
	int32  d1;			// Data: differentiator storage: ud(k-1)
	int32  d2;			// Data: differentiator storage: d2(k-1)
	int32  w1;			// Data: saturation record: [u(k-1) - v(k-1)]
} PID_GRANDO_IQ_DATA;

typedef struct {
	PID_GRANDO_IQ_TERMINALS term;
	PID_GRANDO_IQ_PARAMETERS param;
	PID_GRANDO_IQ_DATA	data;
} PID_GRANDO_IQ_CONTROLLER;

typedef PID_GRANDO_IQ_CONTROLLER	*PID_handle;

//*********** Function Declarations *******//
void PID_GRANDO_IQ_init(PID_GRANDO_IQ_CONTROLLER *v);
void PID_GRANDO_IQ_FUNC(PID_GRANDO_IQ_CONTROLLER *v);

//*********** Macro Definition ***********//
#define PID_GRANDO_IQ_MACRO(v)																						\
																													\
	/* proportional term */ 																						\
	v.data.up = _IQmpy(v.param.Kr, v.term.Ref) - v.term.Fbk;														\
																													\
	/* integral term */ 																							\
	v.data.ui = _IQmpy(v.param.Ki, _IQmpy(v.data.w1, (v.term.Ref - v.term.Fbk))) + v.data.i1;						\
	v.data.i1 = v.data.ui;																							\
																													\
	/* derivative term */ 																							\
	v.data.d2 = _IQmpy(v.param.Kd, _IQmpy(v.term.c1, (_IQmpy(v.term.Ref, v.param.Km) - v.term.Fbk))) - v.data.d2;	\
	v.data.ud = v.data.d2 + v.data.d1;																				\
	v.data.d1 = _IQmpy(v.data.ud, v.term.c2);																		\
																													\
	/* control output */ 																							\
	v.data.v1 = _IQmpy(v.param.Kp, (v.data.up + v.data.ui + v.data.ud));											\
	v.term.Out= _IQsat(v.data.v1, v.param.Umax, v.param.Umin);														\
	v.data.w1 = (v.term.Out == v.data.v1) ? _IQ(1.0) : _IQ(0.0);													\
	

#endif /* PID_GRANDO_IQ_H_ */
