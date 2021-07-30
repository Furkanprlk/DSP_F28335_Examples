/* DCL.h - C2000 Digital Controller Library Header File */
// version 1.0, August 2015

#ifndef _C_DCL_H
#define _C_DCL_H

/*** PID controller ***/

typedef volatile struct {
	float Kp;		// proportional gain
	float Ki;		// integral gain
	float Kd;		// derivative gain
	float Kr;		// set point weight
	float c1;		// D filter coefficient 1
	float c2;		// D filter coefficient 2
	float d2;		// D filter storage 1
	float d3;		// D filter storage 2
	float i10;		// I storage
	float i14;		// sat storage
	float Umax;		// upper saturation limit
	float Umin;		// lower saturation limit
} PID;

#define	PID_DEFAULTS { 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, -1.0f }

extern float DCL_runPID(PID *p, float rk, float yk, float lk);
extern float DCL_runPIDc(PID *p, float rk, float yk, float lk);


/*** PI controller ***/

typedef volatile struct {
	float Kp;		// [0] proportional gain
 	float Ki;		// [2] integral gain
 	float i10;		// [4] I storage
	float Umax;		// [6] upper saturation limit
	float Umin;		// [8] lower saturation limit
	float i6;		// [A] saturation storage
} PI;

#define	PI_DEFAULTS { 1.0f, 0.0f, 0.0f, 1.0f, -1.0f, 1.0f }

extern float DCL_runPI(PI *p, float rk, float yk);
extern float DCL_runPIc(PI *p, float rk, float yk);


/*** Direct Form 1 - 3rd order ***/

typedef volatile struct {
	// coefficients
	float b0;	// [0] b0
	float b1;	// [2] b1
	float b2;	// [4] b2
	float b3;	// [6] b3
	float a0;	// [8] a0
	float a1;	// [A] a1
	float a2;	// [C] a2
	float a3;	// [E] a3

	//data
	float d0;	// [10] e(k)
	float d1;	// [12] e(k-1)
	float d2;	// [14] e(k-2)
	float d3;	// [16] e(k-3)
	float d4;	// [18] u(k)
	float d5;	// [1A] u(k-1)
	float d6;	// [1C] u(k-2)
	float d7;	// [1E] u(k-3)
} DF13;

#define	DF13_DEFAULTS {	0.25f, 0.25f, 0.25f, 0.25f, 0.0f, 0.0f, 0.0f, 0.0f, \
						0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f 		\
						}

extern float DCL_runDF13(DF13 *p, float ek);
extern float DCL_runDF13i(DF13 *p, float ek, float vk);
extern float DCL_runDF13p(DF13 *p, float ek, float uk);
extern float DCL_runDF13c(DF13 *p, float ek);
extern float DCL_runDF13ic(DF13 *p, float ek, float vk);
extern float DCL_runDF13pc(DF13 *p, float ek, float uk);


/*** Direct Form 2 - 2nd order ***/

typedef volatile struct {
	float b0;	// [0] b0
	float b1;	// [2] b1
	float b2;	// [4] b2
	float a1;	// [6] a1
	float a2;	// [8] a2
	float x1;	// [A] x1
	float x2;	// [C] x2
} DF22;

#define	DF22_DEFAULTS { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }

extern float DCL_runDF22(DF22 *p, float ek);
extern float DCL_runDF22i(DF22 *p, float ek);
extern void DCL_runDF22p(DF22 *p, float ek, float uk);
extern float DCL_runDF22c(DF22 *p, float ek);
extern float DCL_runDF22ic(DF22 *p, float ek);
extern void DCL_runDF22pc(DF22 *p, float ek, float uk);


/*** Direct Form 2 - 3rd order ***/

typedef volatile struct {
	float b0;	// [0] b0
	float b1;	// [2] b1
	float b2;	// [4] b2
	float b3;	// [6] b3
	float a1;	// [8] a1
	float a2;	// [A] a2
	float a3;	// [C] a3
	float x1;	// [E] x1
	float x2;	// [10] x2
	float x3;	// [12] x3
} DF23;

#define	DF23_DEFAULTS { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }

extern float DCL_runDF23(DF23 *p, float ek);
extern float DCL_runDF23i(DF23 *p, float ek);
extern void DCL_runDF23p(DF23 *p, float ek, float uk);
extern float DCL_runDF23c(DF23 *p, float ek);
extern float DCL_runDF23ic(DF23 *p, float ek);
extern void DCL_runDF23pc(DF23 *p, float ek, float uk);


#endif // _C_DCL_H

/* end of file */
