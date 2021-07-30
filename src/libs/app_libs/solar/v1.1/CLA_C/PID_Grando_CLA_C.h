/**
 * Basic summing junction and PID control law.
 */

#ifndef PID_GRANDO_CLA_C_H_
#define PID_GRANDO_CLA_C_H_

/**
 * PID_GRANDO_TERMINALS internal structure.
 */
typedef struct {
	// Inputs
	float32 Ref;		// Reference set-point
	float32 Fbk;		// Feedback

	// Output
	float32 Out;		// Controller output

	// Internal
	// Note: c1 & c2 placed here to keep structure size under 8 words
	float32 c1;			// Derivative filter coefficient 1
	float32 c2;			// Derivative filter coefficient 2
} PID_GRANDO_TERMINALS;

/**
 * PID_GRANDO_PARAMETERS internal structure.
 */
typedef struct {
	float32 Kr;				// Reference set-point weighting
	float32 Kp;				// Proportional loop gain
	float32 Ki;			    // Integral gain
	float32 Kd;				// Derivative gain
	float32 Km;				// Derivative weighting
	float32 Umax;			// Upper saturation limit
	float32 Umin;			// Lower saturation limit
} PID_GRANDO_PARAMETERS;

/**
 * PID_GRANDO_DATA internal structure.
 */
typedef struct {
	float32 up;				// Proportional term
	float32 ui;				// Integral term
	float32 ud;				// Derivative term
	float32 v1;				// Pre-saturated controller output
	float32 i1;				// Integrator storage: ui(k-1)
	float32 d1;				// Differentiator storage: ud(k-1)
	float32 d2;				// Differentiator storage: d2(k-1)
	float32 w1;				// Saturation record: [u(k-1) - v(k-1)]
} PID_GRANDO_DATA;

/**
 * PID_GRANDO_TERMINALS structure.
 */
typedef struct {
	PID_GRANDO_TERMINALS term;
	PID_GRANDO_PARAMETERS param;
	PID_GRANDO_DATA data;
} PID_GRANDO_CNTLR_CLA_C;

/**
 * Default values for the PID_GRANDO structures
 */
#define PID_GRANDO_CNTLR_CLA_C_INIT(v)								\
	v.term.Ref = 0;		/* Reference */								\
	v.term.Fbk = 0; 	/* Feedback */								\
	v.term.Out = 0; 	/* Controller output */						\
	v.term.c1 = 0;		/* Derivative filter coefficient 1 */		\
	v.term.c2 = 0;		/* Derivative filter coefficient 2 */		\
																	\
	v.param.Kr = 1.0;		/* Reference set-point weighting */		\
	v.param.Kp = 1.0;		/* Proportional loop gain */			\
	v.param.Ki = 0.0;		/* Integral gain */						\
	v.param.Kd = 0.0;		/* Derivative gain */					\
	v.param.Km = 1.0;		/* Derivative weighting */				\
	v.param.Umax = 1.0;		/* Upper saturation limit */			\
	v.param.Umin = -1.0;	/* Lower saturation limit */			\
																	\
	v.data.up = 0.0;	/* Proportional term */						\
	v.data.ui = 0.0;	/* Integral term */							\
	v.data.ud = 0.0;	/* Derivative term */						\
	v.data.v1 = 0.0;	/* Pre-saturated controller output */		\
	v.data.i1 = 0.0;	/* Integrator storage */					\
	v.data.d1 = 0.0;	/* Differentiator storage: ud(k - 1) */		\
	v.data.d2 = 0.0;	/* Differentiator storage: d2(k - 1) */		\
	v.data.w1 = 1.0;	/* Saturation record: [u(k-1) - v(k-1)] */

/**
 * PID Grando junction summing and PID implementation.
 */
#define PID_GRANDO_CLA_C(v)																			\
	/* Proportional term */ 																		\
	v.data.up = (v.param.Kr * v.term.Ref) - v.term.Fbk;												\
																									\
	/* Integral term */ 																			\
	v.data.ui = (v.param.Ki * (v.data.w1 * (v.term.Ref - v.term.Fbk))) + v.data.i1;					\
	v.data.i1 = v.data.ui;																			\
																									\
	/* Derivative term */ 																			\
	v.data.d2 = (v.param.Kd * (v.term.c1 * ((v.term.Ref * v.param.Km) - v.term.Fbk))) - v.data.d2;	\
	v.data.ud = v.data.d2 + v.data.d1;																\
	v.data.d1 = (v.data.ud * v.term.c2);															\
																									\
	/* Control output */ 																			\
	v.data.v1 = (v.param.Kp * (v.data.up + v.data.ui + v.data.ud));									\
	v.term.Out = (v.param.Umax < v.data.v1) ? v.param.Umax : v.data.v1;								\
	v.term.Out = (v.term.Out > v.param.Umin) ? v.term.Out : v.param.Umin;							\
	v.data.w1 = (v.term.Out == v.data.v1) ? (1.0) : (0.0)

#endif /* PID_GRANDO_CLA_C_H_ */
