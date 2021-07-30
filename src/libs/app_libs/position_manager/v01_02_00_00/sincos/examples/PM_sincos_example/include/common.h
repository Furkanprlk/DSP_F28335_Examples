/* common.h */
// sincos "testbench" project header file

#ifndef _C_COMMON_H
#define _C_COMMON_H

/* include files */
#include "F2837xD_device.h"     		// F2837x peripheral header files
#include "F2837xD_Examples.h"			// examples support file
#include "F2837xD_ePwm_defines.h"		// ePWM bit definitions
#include "F2837xD_Pie_defines.h"		// PIE bit definitions
#include "F2837xD_GlobalPrototypes.h" 	// header function definitions
#include "sincos.h"						// sincos integration header
#include "PM_sincos_lib.h"				// sincos library

/* global variables */
extern unsigned long IdleLoopCount;
extern unsigned long AdccIsrCount;

/* global functions */
extern interrupt void adcc_isr(void);	// [PM_sincos_adcisr.c]
extern void SetDBGIER(Uint16);			// [F2837xD_DBGIER.asm]

#endif	// _C_COMMON_H

/* end of file */
