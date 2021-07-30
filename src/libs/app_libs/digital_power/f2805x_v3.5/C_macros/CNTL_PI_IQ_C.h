//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================
/**
 * PI control law with programmable output saturation.
 * This macro uses CNTL_PI_IQ_C structures to store coefficients & internal values.
 * The structures should be initialized with the supplied CNTL_PI_IQ_C_INIT macro.
 * Within the structure the Max & Min parameters are the output bounds 
 */

#ifndef __CNTL_PI_IQ_H__
#define __CNTL_PI_IQ_H__

typedef struct {  _iq  Ref;   			// Input: reference set-point
				  _iq  Fbk;   			// Input: feedback
				  _iq  Out;   			// Output: controller output 
				  _iq  Kp;				// Parameter: proportional loop gain
				  _iq  Ki;			    // Parameter: integral gain
				  _iq  Umax;			// Parameter: upper saturation limit
				  _iq  Umin;			// Parameter: lower saturation limit
				  _iq  up;				// Data: proportional term
				  _iq  ui;				// Data: integral term
				  _iq  v1;				// Data: pre-saturated controller output
				  _iq  i1;				// Data: integrator storage: ui(k-1)
				  _iq  w1;				// Data: saturation record: [u(k-1) - v(k-1)]
				} CNTL_PI_IQ_C;

/*
 * Initial values for CNTL_PI_IQ structures.
 */
#define CNTL_PI_IQ_C_INIT(k)				\
		/* Initialize variables */				\
		k.Ref = 0;								\
		k.Fbk = 0;								\
		k.Out = 0;								\
		k.Kp = 0;							\
		k.Ki = 0;							\
		k.Umax = _IQ(1.0);								\
		k.Umin = _IQ(0.0);								\
		k.up = 0;								\
		k.ui = 0;						\
		k.v1 = 0;							\
		k.i1 = 0;							\
		k.w1 = 0;

/**
 * Calculates PI control law 
 */
 
#define CNTL_PI_IQ_C(v)												\
																\
	/* proportional term */ 									\
	v.up = _IQmpy((v.Ref - v.Fbk),v.Kp);						\
																\
	/* integral term */ 										\
	v.ui = (v.Out == v.v1)?(_IQmpy(v.Ki, v.up)+ v.i1) : v.i1;	\
	v.i1 = v.ui;												\
																\
	/* control output */ 										\
	v.v1 = (v.up + v.ui);										\
	v.Out= _IQsat(v.v1, v.Umax, v.Umin);						\
	//v.w1 = (v.Out == v.v1) ? _IQ(1.0) : _IQ(0.0);				\
	
#endif // __CNTL_PI_H__

