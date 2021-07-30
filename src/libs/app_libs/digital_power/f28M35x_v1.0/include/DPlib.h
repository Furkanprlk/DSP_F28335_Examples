/* DPlib.h */

#ifndef DPLIB_C_H
#define DPLIB_C_H
#include "F28M35x_Device.h" 
#include "F28M35x_EPwm_defines.h"
// declare library initialisation routine [DPL_ISR.asm]
// this assembly function must be called before the net is initialised
extern void DPL_Init(void);	
extern void DPL_CLAInit(void);

// declare assembly Interrupt Service Routine [DPL_ISR.asm]
extern interrupt void DPL_ISR(void);

#define ADCTRIG_SOFT		0
#define ADCTRIG_CPU_TINT0	1
#define ADCTRIG_CPU_TINT1	2
#define ADCTRIG_CPU_TINT2	3
#define ADCTRIG_XINT2		4
#define ADCTRIG_EPWM1_SOCA	5
#define ADCTRIG_EPWM1_SOCB	6
#define ADCTRIG_EPWM1_SYNC  7
#define ADCTRIG_EPWM2_SOCA	8
#define ADCTRIG_EPWM2_SOCB	9
#define ADCTRIG_EPWM2_SYNC  10
#define ADCTRIG_EPWM3_SOCA	11
#define ADCTRIG_EPWM3_SOCB	12
#define ADCTRIG_EPWM3_SYNC  13
#define ADCTRIG_EPWM4_SOCA	14
#define ADCTRIG_EPWM4_SOCB	15
#define ADCTRIG_EPWM4_SYNC  16
#define ADCTRIG_EPWM5_SOCA	17
#define ADCTRIG_EPWM5_SOCB	18
#define ADCTRIG_EPWM5_SYNC  19
#define ADCTRIG_EPWM6_SOCA	20
#define ADCTRIG_EPWM6_SOCB	21
#define ADCTRIG_EPWM6_SYNC  22
#define ADCTRIG_EPWM7_SOCA	23
#define ADCTRIG_EPWM7_SOCB	24
#define ADCTRIG_EPWM7_SYNC  25
#define ADCTRIG_EPWM8_SOCA	26
#define ADCTRIG_EPWM8_SOCB	27
#define ADCTRIG_EPWM8_SYNC  28
#define ADCTRIG_EPWM9_SOCA	29
#define ADCTRIG_EPWM9_SOCB	30
#define ADCTRIG_EPWM9_SYNC  31

//---------------------------------------------------------------------------
// Used to indirectly access all EPWM modules
extern volatile struct EPWM_REGS *ePWM[];

// Used to indirectly access all Comparator modules
extern volatile struct COMP_REGS *Comp[];

extern volatile struct ADC_REGS *ADC[];

//  CNTL_2P2Z: 2-pole 2-zero control law

// 2P2Z coefficient structure definition
struct CNTL_2P2Z_CoefStruct {
	float b2;
	float b1;
	float b0;
	float a2;
	float a1;
	float max;
	float min;
	};

// 3P3Z coefficient structure definition
struct CNTL_3P3Z_CoefStruct {
	float b3;
	float b2;
	float b1;
	float b0;
	float a3;
	float a2;
	float a1;
	float max;
	float min;
	};

//---------------------------------------------------------------------------

#endif	// DPLIB_C_H

/* end of file */
