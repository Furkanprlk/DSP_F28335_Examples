/**
 * Squares the reciprocate of a scaled unipolar input signal.  The use of the PFC_InvRmsSqr_CLA_C
 * structure is required.  The structure should be initialized using the PFC_InvRmsSqr_CLA_C_INIT
 * macro.  This macro calculates the inverse of values utilizing the __meinvf32 CLA C intrinsic.
 * Said intrinsic sacrifices some floating point precision in favor of fewer clock cycles.  If
 * greater precision or a generalization is desired, change the intrinsic to the regular division
 * operator.
 */

#ifndef PFC_INVRMSSQR_CLA_C_H_
#define PFC_INVRMSSQR_CLA_C_H_

/**
 * PFC_InvRmsSqr_CLA_C structure
 */
typedef struct {
	float32 In;
	float32 Out;
	float32 Vmin;
	float32 VminOverVmax;
} PFC_InvRmsSqr_CLA_C;

#define LIMIT_PFC_INVRMSSQR ((float32) 1.0)

/**
 * Calculates the square of the reciprocate of a scaled input signal.
 * @param v - PFC_InvRmsSqr_CLA_C_Struct
 * @return Structure Out parameter.
 */
#define PFC_InvRmsSqr_CLA_C(v)												\
	v.Out = (v.Vmin > v.In) ? v.Vmin : v.In;								\
	v.Out = __meinvf32(v.Out) * v.VminOverVmax;								\
	v.Out = v.Out * v.Out;													\
	v.Out = ((v.Out <  LIMIT_PFC_INVRMSSQR) ? v.Out : LIMIT_PFC_INVRMSSQR)

/**
 * Initial values for the PFC_InvRmsSqr_CLA_C structure.
 */
#define PFC_InvRmsSqr_CLA_C_INIT(v)		\
		v.In = 0;						\
		v.Out = 0;						\
		v.Vmin = 0;						\
		v.VminOverVmax = 0

#endif /* PFC_INVRMSSQR_CLA_C_H_ */
