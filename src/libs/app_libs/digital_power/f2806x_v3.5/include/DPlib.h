/**
 * Digital Power Library.  This library provides several modules to facilitate the development of
 * power systems.  The library is divided in two: C language peripheral configuration files,
 * C language header files.  While the configuration files need only be used once during
 * program execution, the modules found within the header files may be used repeatedly.
 */

#ifndef DPLIB_C_H
#define DPLIB_C_H

/**
 * CLA C library modules
 */
//#include "ADCDRV_CLA_C.h"
//#include "CNTL_2P2Z_CLA_C.h"
//#include "CNTL_3P3Z_CLA_C.h"
//#include "DACDRV_RAMP_CLA_C.h"
//#include "DLOG_1ch_CLA_C.h"
//#include "DLOG_4ch_CLA_C.h"
//#include "MATH_EMAVG_CLA_C.h"
//#include "PFC_BL_ICMD_CLA_C.h"
//#include "PFC_ICMD_CLA_C.h"
//#include "PFC_InvRmsSqr_CLA_C.h"
//#include "PFC_INVSQR_CLA_C.h"
//#include "PWMDRV_CLA_C.h"
//#include "SineAnalyzer_CLA_C.h"

/**
 * Digital power initialization function prototypes.
 * Call all required peripheral initialization functions.
 */
extern void DPL_Init(void);
extern void DPL_CLAInit(void);

// declare assembly Interrupt Service Routine [DPL_ISR.asm]
extern interrupt void DPL_ISR(void);

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

//  CNTL_2P2Z: 2-pole 2-zero control law
// 2P2Z coefficient structure definition
struct CNTL_2P2Z_CoefStruct {
	long b2;
	long b1;
	long b0;
	long a2;
	long a1;
	long max;
	long i_min;
	long min;
	};

// 3P3Z coefficient structure definition
struct CNTL_3P3Z_CoefStruct {
	long b3;
	long b2;
	long b1;
	long b0;
	long a3;
	long a2;
	long a1;
	long max;
	long i_min;
	long min;
	};


struct CNTL_2P2Z_CLACoefStruct {
	float b2;
	float b1;
	float b0;
	float a2;
	float a1;
	float max;
	float i_min;
	float min;
	};

struct CNTL_3P3Z_CLACoefStruct {
	float b3;
	float b2;
	float b1;
	float b0;
	float a3;
	float a2;
	float a1;
	float max;
	float i_min;
	float min;
	};

#endif	// DPLIB_C_H
