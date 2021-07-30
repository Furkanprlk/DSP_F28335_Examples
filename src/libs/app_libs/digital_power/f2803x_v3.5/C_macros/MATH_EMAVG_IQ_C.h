/**
 * Performs exponential moving average calculation.  This macro requires the use of the
 * MATH_EMAVG_IQ_C structure.  The structure should be initialized with the MATH_EMAVG_IQ_C_INIT
 * macro.
 */

#ifndef MATH_EMAVG_IQ_C_H_
#define MATH_EMAVG_IQ_C_H_

/**
 * Exponential-moving average structure
 */
typedef struct {
	int32 In;
	int32 Out;
	int32 Multiplier;
} MATH_EMAVG_IQ_C;


/**
 * Performs exponential moving average calculation.
 * @param m - MATH_EMAVG_IQ_C structure with values.
 * @return MATH_EMAVG_IQ_C Out parameter.
 */
#define MATH_EMAVG_IQ_C(In,Out,Multiplier)									\
Out = (_IQmpy((In - Out) , Multiplier) + Out)

/**
 * Initial values for MATH_EMAVG_IQ_C structure.
 */
#define MATH_EMAVG_IQ_C_INIT(v)	\
	v.In = 0;						\
	v.Out = 0;						\
	v.Multiplier = 0

#endif /* MATH_EMAVG_IQ_C_H_ */
