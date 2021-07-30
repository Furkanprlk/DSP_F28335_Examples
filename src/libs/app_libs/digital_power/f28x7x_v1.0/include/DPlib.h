/**
 * Digital Power Library.  This library provides several modules to facilitate the development of
 * power systems.  The library is divided in two: C language peripheral configuration files,
 * C language header files.  While the configuration files need only be used once during
 * program execution, the modules found within the header files may be used repeatedly.
//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================
 */

#ifndef DPLIB_C_H
#define DPLIB_C_H

#include "F28x_Project.h"
/**
 * C library modules
 */

#include "ADCDRV_F_C.h"
#include "CNTL_2P2Z_F_C.h"
#include "CNTL_3P3Z_F_C.h"
#include "DACDRV_RAMP_F_C.h"
#include "DLOG_1ch_F_C.h"
#include "DLOG_4ch_F_C.h"
#include "MATH_EMAVG_F_C.h"
#include "PFC_BL_ICMD_F_C.h"
#include "PFC_ICMD_F_C.h"
#include "PFC_InvRmsSqr_F_C.h"
#include "PFC_INVSQR_F_C.h"
#include "PWMDRV_F_C.h"
#include "SineAnalyzer_F_C.h"


/**
 * ADC trigger-source definitions.
 */
#define ADCTRIG_SOFT		0
#define ADCTRIG_CPU_TINT0	1
#define ADCTRIG_CPU_TINT1	2
#define ADCTRIG_CPU_TINT2	3
#define ADCTRIG_XINT2		4
#define ADCTRIG_EPWM1_SOCA	5
#define ADCTRIG_EPWM1_SOCB	6
#define ADCTRIG_EPWM2_SOCA	7
#define ADCTRIG_EPWM2_SOCB	8
#define ADCTRIG_EPWM3_SOCA	9
#define ADCTRIG_EPWM3_SOCB	10
#define ADCTRIG_EPWM4_SOCA	11
#define ADCTRIG_EPWM4_SOCB	12
#define ADCTRIG_EPWM5_SOCA	13
#define ADCTRIG_EPWM5_SOCB	14
#define ADCTRIG_EPWM6_SOCA	15
#define ADCTRIG_EPWM6_SOCB	16
#define ADCTRIG_EPWM7_SOCA	17
#define ADCTRIG_EPWM7_SOCB	18
#define ADCTRIG_EPWM8_SOCA	17
#define ADCTRIG_EPWM8_SOCB	18
#define ADCTRIG_EPWM9_SOCA	19
#define ADCTRIG_EPWM9_SOCB	20
#define ADCTRIG_EPWM10_SOCA	21
#define ADCTRIG_EPWM10_SOCB	22
#define ADCTRIG_EPWM11_SOCA	23
#define ADCTRIG_EPWM11_SOCB	24
#define ADCTRIG_EPWM12_SOCA	25
#define ADCTRIG_EPWM12_SOCB	26

/**
 * Allows access to all ADC registers
 */
extern volatile struct ADC_REGS *ADC[];

/**
 * Allows access to all Comparator modules
 */
extern volatile struct COMP_REGS *Comp[];

/**
 * Allows access to all EPwm modules
 */
extern volatile struct EPWM_REGS *ePWM[];


extern volatile struct CMPSS_REGS *Cmpss[];

// prototypes of all the library functions
void ADC_SOC_CNF(int AdcNo,int ChSel[], int Trigsel[], int ACQPS[], int IntChSel, int mode,  Uint16 resolution, Uint16 signalmode );

void PWM_1ch_CNF(int16 n, Uint16 period, int16 mode, int16 phase);

void PWM_1ch_UpCntDB_ActivHIC_CNF(int16 n, int16 period, int16 mode, int16 phase);
void PWM_1ch_UpCntDB_ActivHIC_UpdateDB(int16 n, int16 dbRED, int16 dbFED);

void PWM_1ch_UpCntDB_CNF(int16 n, Uint16 period, int16 mode, int16 phase);
void PWM_1ch_UpCntDB_UpdateDB(int16 n, int16 dbRED, int16 dbFED);

void PWM_1ch_UpCntDB_Compl_CNF(int16 n, Uint16 period, int16 mode, int16 phase);
void PWM_1ch_UpCntDB_Compl_UpdateDB(int16 n, int16 dbRED, int16 dbFED);

void PWM_1ch_UpDwnCnt_CNF(int16 n, Uint16 period, int16 mode, int16 phase);

void PWM_1ch_UpDwnCntCompl_CNF(int16 n, Uint16 period, int16 mode, int16 phase);

void PWM_1chHiRes_CNF(int16 n, Uint16 period, int16 mode, int16 phase);

void PWM_1chHiResUpDwnCnt_CNF(int16 n, Uint16 period, int16 mode, int16 phase);

void PWM_2ch_UpCnt_CNF(int16 n, Uint16 period, int16 mode, int16 phase);

void PWM_2ch_UpDwnCnt_CNF(int16 n, int16 period, int16 mode, int16 phase);
void PWM_2ch_UpDwnCnt_UpdateDB(int16 n, int16 dbRED, int16 dbFED);

void PWM_BuckBoost_CNF(int16 n, int16 m, Uint16 period);
void PWM_BuckBoost_UpdateDB(int16 n, int16 dbRED, int16 dbFED);

void PWM_ComplPairDB_CNF(int16 n, Uint16 period, int16 mode, int16 phase);
void PWM_ComplPairDB_UpdateDB(int16 n, int16 dbRED, int16 dbFED);

void PWM_DualUpDwnCnt_CNF(int16 n, Uint16 Period, int16 Mode, int16 Phase);

void PWM_PSFB_CNF(int16 n, Uint16 Period);

void PWMDRV_PSFB_PCMC_CNF(int16 n, Uint16 period, int16 SR_Enable, int16 Comp2_Prot);

void PWM_PSFB_VMC_SR_CNF(int16 n, Uint16 period, int16 SR_Enable, int16 Comp1_Prot);



#endif	// DPLIB_C_H
