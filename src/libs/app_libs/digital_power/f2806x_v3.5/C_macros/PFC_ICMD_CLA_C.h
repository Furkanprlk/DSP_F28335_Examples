/**
 * Performs computation of the current command for power factor correction.  This macro utilizes
 * the PFC_ICMD_CLA_C structure which should be initialized using the PFC_ICMD_CLA_C_INIT macro.
 */

#ifndef PFC_ICMD_CLA_C_H_
#define PFC_ICMD_CLA_C_H_

/**
 * Current command PFC structure
 */
typedef struct {
	float32 Vcmd;
	float32 VinvSqr;
	float32 VacRect;
	float32 Out;
	float32 VmaxOverVmin;
} PFC_ICMD_CLA_C;

/**
 * Calculates current command for power factor correction.
 * @param v - PFC_ICMD_CLA_C structure.
 * @return PFC_ICMD_CLA_C Out parameter
 */
#define PFC_ICMD_CLA_C(v)										\
	v.Out = (v.Vcmd * v.VinvSqr * v.VacRect * v.VmaxOverVmin)

/**
 * Initial values for the PFC_ICMD_CLA_C structure.
 */
#define PFC_ICMD_CLA_C_INIT(v)		\
		v.Vcmd = 0;					\
		v.VinvSqr = 0;				\
		v.VacRect = 0;				\
		v.Out = 0;					\
		v.VmaxOverVmin = 0

#endif /* PFC_ICMD_CLA_C_H_ */
