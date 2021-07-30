/* DRIVERLIB.h */

#ifndef DRIVERLIB_C_H
#define DRIVERLIB_C_H

#include <math.h>
#include "PWM_bmsk.h"

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

#endif // DRIVERLIB_C_H
/* end of file */
