/* DRIVERLIB.h */

#ifndef DRIVERLIB_C_H
#define DRIVERLIB_C_H

#include <math.h>
#include "PWM_bmsk.h"

//---------------------------------------------------------------------------
// Used to indirectly access all EPWM modules
extern volatile struct EPWM_REGS *ePWM[];

// Used to indirectly access all Comparator modules
extern volatile struct COMP_REGS *Comp[];

extern volatile struct ADC_REGS *ADC[];

#endif // DRIVERLIB_C_H
/* end of file */
