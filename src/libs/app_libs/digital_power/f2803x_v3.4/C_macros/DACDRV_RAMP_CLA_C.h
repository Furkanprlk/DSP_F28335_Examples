/**
 * DAC ramp generator interface which can be used for slope compensation if not already provided.
 * Requires the DAC to be configured with the DacDrvCnf function found in the DAC_Cnf.c source file.
 * @see DAC_Cnf.c
 */

#ifndef DACDRV_RAMP_CLA_C_H_
#define DACDRV_RAMP_CLA_C_H_

/**
 * Drives the DAC output.
 * @param CompRegs - Comparator configuration registers of the DAC.
 * @param RampIn - New DAC output value.
 */
#define DACDRV_RAMP_CLA_C(CompRegs, RampIn)		\
	CompRegs.RAMPMAXREF_SHDW = RampIn;			\
	CompRegs.DACVAL.bit.DACVAL = RampIn

#endif /* DACDRV_RAMP_CLA_C_H_ */
