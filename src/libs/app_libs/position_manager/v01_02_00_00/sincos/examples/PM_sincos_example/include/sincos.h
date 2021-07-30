/* sincos.h */
// sincos integration header file

#ifndef _C_SINCOS_H
#define _C_SINCOS_H

/* include files */
#include "PM_sincos_lib.h"				// sincos library


/* sincoe definitions */
#define SWAP_CHANNELS
#define CPU_CLK   			(IMULT_20/2)*20e6
#define PWM_CLK   			16e3             		// 16kHz => EPWM1 frequency
#define SINCOS_INT_PRD		CPU_CLK/PWM_CLK			// [0x186A]
#define ADC_AQPS 			14						// AQPS in SYSCLK cycles


/* global variables */
extern SINCOS mySincos;


/* global functions */
extern void sincos_init(void);
extern void sincos(void);

#endif	// _C_SINCOS_H

/* end of file  */
