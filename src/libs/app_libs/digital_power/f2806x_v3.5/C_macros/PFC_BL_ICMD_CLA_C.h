/**
 * Performs current command computation for PFC stage using PFC boost switch sensing.  This macro
 * requires the use of the PFC_BL_ICMD_CLA_C structure.  The structure should be initialized
 * using the PFC_BL_ICMD_CLA_C_INIT macro.  The macro calculates the inverse of values utilizing
 * the __meinvf32 CLA C intrinsic.  Said intrinsic sacrifices some floating point precision in
 * favor of fewer clock cycles.  If greater precision or a generalization is desired, change the
 * intrinsic to the regular division operator.
 */

#ifndef PFC_BL_ICMD_CLA_C_H_
#define PFC_BL_ICMD_CLA_C_H_

/**
 * Current command PFC BL structure
 */
typedef struct {
	float32 Vcmd;
	float32 VinvSqr;
	float32 VacRect;
	float32 Duty;
	float32 Vpfc;
	float32 Out;
	float32 VmaxOverVmin;
	float32 VoutMaxOverVinMax;
} PFC_BL_ICMD_CLA_C;

#define LIMIT_PFC_BL_ICMD ((float32) 0.005)

/**
 * Performs current command computation for PFC.
 * @param v - PFC_BL_ICMD_CLA_C structure.
 * @return PFC_BL_ICMD_CLA_C Out parameter.
 */
#define PFC_BL_ICMD_CLA_C(v)													\
	v.Out = v.Vpfc * v.VoutMaxOverVinMax * v.Duty;								\
	v.Out = (v.Out > LIMIT_PFC_BL_ICMD) ? v.Out : LIMIT_PFC_BL_ICMD;			\
	v.Out = (v.VacRect * v.VinvSqr * v.Vcmd * v.VmaxOverVmin) 					\
			* __meinvf32(v.Out)	* ((v.Vpfc * v.VoutMaxOverVinMax) - v.VacRect)

/**
 * Initial values for the PFC_BL_ICMD_CLA_C structure.
 */
#define PFC_BL_ICMD_CLA_C_INIT(v)	\
		v.Vcmd = 0;					\
		v.VinvSqr = 0;				\
		v.VacRect = 0;				\
		v.Duty = 0;					\
		v.Vpfc = 0;					\
		v.Out = 0;					\
		v.VmaxOverVmin = 0;			\
		v.VoutMaxOverVinMax = (0)

#endif /* PFC_BL_ICMD_CLA_C_H_ */
