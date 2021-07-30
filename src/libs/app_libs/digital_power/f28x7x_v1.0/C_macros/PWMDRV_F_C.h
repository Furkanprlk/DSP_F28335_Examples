/**
 * PWM driver library.
 */
//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================

#include "DPlib.h"

/**
 * PWMDRV_PSFB_VMC_SR_C structure.
 */
typedef struct {
	// Internal values
	float	temp;
	float temp2;

	// Inputs
	float phase;
	float dbPtoA;
	float dbAtoP;
} PWMDRV_PSFB_VMC_SR_F_C;

/**
 * PWM macro constants.
 */
#define ONE ((float) 1.0)
#define ONE_HALF ((float) 0.5)
#define HI_RES_SHIFT ((float) 65536.0)
#define LLC_ComplPairDB_SHIFT ((float) 1024.0)
#define LLC_UpCntDB_Compl_CONST ((float) 13.0)
#define PSFB_VMC_SR_CONST_1 ((float) 10.0)
#define PSFB_VMC_SR_CONST_2 ((float) 5.0)
#define LLC_MAX_PERIOD ((float) 1024.0)

/**
 * Single channel PWM driver.  Requires PWM peripheral to be
 * configured with PWM_1ch_CNF function.
 * @see PWMDRV_1ch_Cnf.c
 */
#define PWMDRV_1ch_F_C(EPwmRegs, period, duty)														\
	EPwmRegs.CMPA.bit.CMPA = (duty) * (period);														\
	EPwmRegs.CMPB.bit.CMPB = (EPwmRegs.CMPA.bit.CMPA * ONE_HALF)

/**
 * Single channel PWM driver using Hi Res feature.  Requires PWM
 * peripheral to be configured with PWM_1chHiRes_CNF function.
 * @see PWM_1chHiRes_Cnf.c
 */
#define PWMDRV_1chHiRes_F_C(EPwmRegs, period, duty)													\
	EPwmRegs.CMPA.all = (duty) * HI_RES_SHIFT * (period);												\
	EPwmRegs.CMPB.bit.CMPB = (EPwmRegs.CMPA.bit.CMPA * ONE_HALF)

/**
 * Single channel PWM driver using HiRes feature.  Requires PWM
 * peripheral to be configured with PWM_1chHiResUpDwnCnt_CNF
 * function.
 * @see PWM_1chHiresUpDwnCnt_Cnf.c
 */
#define PWMDRV_1chHiRes_UpDwnCnt_F_C(EPwmRegs, period, duty)											\
	EPwmRegs.CMPA.all = (period * duty);																\
	EPwmRegs.CMPB.bit.CMPB = (EPwmRegs.CMPA.bit.CMPA * ONE_HALF)

/**
 * PWM driver for two phase interleaved PFC.  Requires PWM peripheral
 * to be configured with PWM_PFC2PHIL_CNF function.
 * @see PWM_PFC2PhiL_Cnf.c
 */
#define PWMDRV_PFC2PhiL_F_C(EPwmRegs, period, duty, adj)												\
	EPwmRegs.CMPA.bit.CMPA = (duty) * (period);														\
	EPwmRegs.CMPB.bit.CMPB = ((ONE - (adj) - (duty)) * (period))

/**
 * PWM driver for phase shifted full bridge.  Requires PWM peripheral
 * to be configured with PWM_PSFB_CNF function
 * @see PWM_PSFB_Cnf.c
 */
#define PWMDRV_PSFB_F_C(EPwmRegsN, EPwmRegsM, phase, dbLeft, dbRight)									\
	EPwmRegsM.TBPHS.bit.TBPHS = (EPwmRegsN.TBPRD * (phase) * ONE_HALF);								\
	EPwmRegsN.DBRED = dbRight;																			\
	EPwmRegsN.DBFED = dbRight;																			\
	EPwmRegsM.DBRED = dbLeft;																			\
	EPwmRegsM.DBFED = dbLeft

/**
 * PWM driver for complementary two channel PWM.  Requires PWM peripheral
 * to be configured with PWM_ComplPairDB_CNF function.
 * @see PWM_ComplPairDB_Cnf.c
 */
#define PWMDRV_ComplPairDB_F_C(EPwmRegs, period, duty)												\
	EPwmRegs.CMPA.bit.CMPA = (duty) * (period);														\
	EPwmRegs.CMPB.bit.CMPB = (EPwmRegs.CMPA.bit.CMPA * ONE_HALF)

/**
 * Updates complementary two channel PWM dead band.
 * @see PWMDRV_ComplPairDB_C
 */
#define PWMDRV_ComplPairDB_F_C_UpdateDB(EPwmRegs, dbRed, dbFed)										\
	EPwmRegs.DBRED = dbRed;																				\
	EPwmRegs.DBFED = dbFed

/**
 * Drives the channels on a PWM independently.  Requires PWM peripheral
 * to be configure with PWM_DualUpDwnCnt_CNF function.
 * @see PWM_DualUpDwnCnt_Cnf.c
 */
#define PWMDRV_DualUpDwnCnt_F_C(EPwmRegs, period, dutyA, dutyB)										\
	EPwmRegs.CMPA.bit.CMPA = (dutyA) * (period);														\
	EPwmRegs.CMPB.bit.CMPB = ((ONE - dutyB) * (period))

/**
 * Driver for complementary period modulation.  Requires PWM peripheral
 * to be configured with PWM_ComplPairDB_CNF function.
 * @see PWM_ComplPairDB_Cnf.c
 */
#define PWMDRV_LLC_UpCnt_ComplPairDB_F_C(EPwmRegs, period, duty)										\
	EPwmRegs.TBPRD = LLC_MAX_PERIOD * period;															\
	EPwmRegs.CMPA.bit.CMPA = EPwmRegs.TBPRD * (duty);													\
	EPwmRegs.CMPB.bit.CMPB = (EPwmRegs.CMPA.bit.CMPA * ONE_HALF)

/**
 * Updates the complementary period modulation dead bands.
 * @see PWMDRV_LLC_UpCnt_ComplPairDB_C
 */
#define PWMDRV_LLC_UpCnt_ComplPairDB_F_C_UpdateDB(EPwmRegs, dbRed, dbFed)								\
	EPwmRegs.DBRED = dbRed;																				\
	EPwmRegs.DBFED = (dbFed)

/**
 * Drives PWM on channel A and a complementary PWM on channel B with dead band.
 * Requires PWM peripherals to be configured with PWM_BuckBoost_CNF function.
 * @see PWM_BuckBoost_Cnf.c
 */
#define PWMDRV_BuckBoost_F_C(EPwmRegsA, EPwmRegsB, period, duty)										\
	EPwmRegsA.CMPA.bit.CMPA = (duty) * (period);														\
	EPwmRegsA.CMPB.bit.CMPB = (EPwmRegsA.CMPA.bit.CMPA * ONE_HALF);												\
	EPwmRegsB.CMPA.bit.CMPA = (EPwmRegsA.CMPA.bit.CMPA)

/**
 * Updates ePWM dead-band for PWMDRV_BuckBoost_C.
 * @see PWMDRV_BuckBoost_C
 */
#define PWMDRV_BuckBoost_F_C_UpdateDB(EPwmRegs, dbRed, dbFed)											\
	EPwmRegs.DBRED = dbRed;																				\
	EPwmRegs.DBFED = dbFed

/**
 * Drives two independent duties on channels A and B on a single PWM module.
 * Requires PWM peripheral to be configured with PWM_2ch_UpCnt_CNF function.
 * @see PWM_2ch_UpCnt_Cnf.c
 */
#define PWMDRV_2ch_UpCnt_F_C(EPwmRegs, period, dutyA, dutyB)											\
	EPwmRegs.CMPA.bit.CMPA = (dutyA) * (period);														\
	EPwmRegs.CMPB.bit.CMPB = ((dutyB) * (period))

/**
 * Drives PWM duty centered at zero.  Requires PWM peripheral to be configured
 * with PWM_1ch_UpDwnCnt_CNF function.
 * @see PWM_1ch_UpDwnCnt_Cnf.c
 */
#define PWMDRV_1ch_UpDwnCnt_F_C(EPwmRegs, period, duty)												\
	EPwmRegs.CMPA.bit.CMPA = ((duty) * (period))

/**
 * Drives complementary PWM duty centered at zero.  Requires PWM peripheral
 * to be configured with PWM_1ch_UpDwnCntCompl_CNF function.
 * @see PWM_1ch_UpDwnCntCompl_Cnf.c
 */
#define PWMDRV_1ch_UpDwnCntCompl_F_C(EPwmRegs, period, duty)											\
	EPwmRegs.CMPA.bit.CMPA = ((ONE - duty) * (period))

/**
 * Default values for PWMDRV_PSFB_VMC_SR_C structure.
 */
#define PWMDRV_PSFB_VMC_SR_F_C_INIT(v)																\
	/* Internal values */																				\
	v.temp = 0;																							\
	v.temp2 = 0;																						\
	/* Inputs */																						\
	v.phase = 0;																						\
	v.dbPtoA = 0;																						\
	v.dbAtoP = (0)

/**
 * Driver for VMC controlled PSFB with SR.  To ensure efficiency this macro
 * requires the use of the PWMDRV_PSFB_VMC_SR_C structure.  The structure
 * should be initialized with the PWMDRV_PSFB_VMC_SR_INIT macro.  PWM peripherals
 * must be configured with PWM_PSFB_VMC_SR_CNF function.
 * @see PWM_PSFB_VMC_SR_Cnf.c
 */
#define PWMDRV_PSFB_VMC_SR_F_C(v, EPwmRegsN, EPwmRegsM, EPwmRegsP)									\
	v.temp = EPwmRegsM.TBPRD * v.phase;																	\
	EPwmRegsM.TBPHS.bit.TBPHS = v.temp;																\
	EPwmRegsP.TBPHS.bit.TBPHS = v.temp;																\
	v.temp = (v.temp + v.dbPtoA + PSFB_VMC_SR_CONST_1);													\
	v.temp2 = EPwmRegsP.TBPRD;																			\
	if(v.temp > v.temp2){																				\
		v.temp = (v.temp2 - PSFB_VMC_SR_CONST_2);														\
	}																									\
	EPwmRegsP.CMPA.bit.CMPA = v.temp2 - v.temp;														\
	EPwmRegsN.DBRED = v.dbAtoP;																			\
	EPwmRegsN.DBFED = v.dbAtoP;																			\
	EPwmRegsM.DBRED = v.dbPtoA;																			\
	EPwmRegsM.DBFED = (v.dbPtoA)

/**
 * Drives duty on PWM with edge shifting.  Uses dead-band module to generate RES and FES.
 * Requires PWM peripheral to be configured with PWM_1ch_UpCntDB_CNF function.
 * @see PWM_1ch_UpCntDB_Cnf.c
 */
#define PWMDRV_LLC_1ch_UpCntDB_F_C(EPwmRegs, period, duty)											\
	EPwmRegs.TBPRD = period;																			\
	EPwmRegs.CMPA.bit.CMPA = ((period) * (duty)) - EPwmRegs.DBFED;										\
	EPwmRegs.CMPB.bit.CMPB = (EPwmRegs.CMPA.bit.CMPA * ONE_HALF)

/**
 * Updates PWM dead-band for PWMDRV_LLC_1ch_UpCntDB_C.
 * @see PWMDRV_LLC_1ch_UpCntDB_C
 */
#define PWMDRV_LLC_1ch_UpCntDB_F_C_UpdateDB(EPwmRegs, dbRed, dbFed)									\
	EPwmRegs.DBRED = dbRed;																				\
	EPwmRegs.DBFED = dbFed

/**
 * Complementary edge shifting PWM driver wit RES and FES.  Requires PWM peripheral
 * to be configured with PWM_1ch_UpDwnCntCompl_CNF function.
 * @see PWM_1ch_UpCnt_DB_Compl_Cnf.c
 */
#define PWMDRV_LLC_1ch_UpCntDB_F_C_Compl(EPwmRegs, period, duty)										\
	EPwmRegs.TBPRD = period;																			\
	EPwmRegs.CMPA.bit.CMPA = (period) * (ONE - duty);													\
	/* Subtract 13 to compensate for 1st sample bug */													\
	EPwmRegs.CMPB.bit.CMPB = EPwmRegs.CMPA.bit.CMPA + (((duty)*(period))*ONE_HALF) - LLC_UpCntDB_Compl_CONST;	\
	/* Update period with Falling Edge Margin (FEM) */													\
	EPwmRegs.TBPRD = (EPwmRegs.TBPRD - EPwmRegs.DBFED)

/**
 * Updates PWM dead-band for PWMDRV_LLC_1ch_UpCntDB_Compl_C.
 * @see PWMDRV_LLC_1ch_UpCntDB_Compl_C
 */
#define PWMDRV_LLC_1ch_UpCntDB_Compl_F_C_UpdateDB(EPwmRegs, dbRed, dbFed)								\
	EPwmRegs.DBRED = dbRed;																				\
	EPwmRegs.DBFED = dbFed

