#ifndef MATH_EMAVG_CLA_H_
#define MATH_EMAVG_CLA_H_

//*********** Structure Definition ********//

// Performs exponential moving average calculation.  This macro requires the use of the
// MATH_EMAVG_CLA structure.  The structure should be initialized with the MATH_EMAVG_CLA_INIT
// macro.

typedef struct {
	float32 In;
	float32 Out;
	float32 Multiplier;
} MATH_EMAVG_CLA;

//*********** Function Declarations *******//
void MATH_EMAVG_CLA_FUNC(MATH_EMAVG_CLA *v);

//*********** Structure Init Function ****//
#define MATH_EMAVG_CLA_init(v)	\
	v.In = 0;					\
	v.Out = 0;					\
	v.Multiplier = 0;

//*********** Macro Definition ***********//
#define MATH_EMAVG_CLA_MACRO(v)						\
	v.Out = ((v.In - v.Out)*v.Multiplier) + v.Out;	\


#endif /* MATH_EMAVG_CLA_H_ */
