#ifndef MATH_EMAVG_IQ_H_
#define MATH_EMAVG_IQ_H_

//*********** Structure Definition ********//

// Performs exponential moving average calculation.  This macro requires the use of the
// MATH_EMAVG_IQ structure.  The structure should be initialized with the MATH_EMAVG_IQ_INIT
// macro.

typedef struct {
	int32 In;
	int32 Out;
	int32 Multiplier;
} MATH_EMAVG_IQ;

//*********** Function Declarations *******//
void MATH_EMAVG_IQ_init(MATH_EMAVG_IQ *v);
void MATH_EMAVG_IQ_FUNC(MATH_EMAVG_IQ *v);

//*********** Macro Definition ***********//
#define MATH_EMAVG_IQ_MACRO(v)								\
	v.Out = (_IQmpy((v.In - v.Out), v.Multiplier) + v.Out);	\

#endif /* MATH_EMAVG_IQ_H_ */
