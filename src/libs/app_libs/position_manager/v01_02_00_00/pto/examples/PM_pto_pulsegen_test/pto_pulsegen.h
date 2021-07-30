//----------------------------------------------------------------------------------
//	FILE:			pulsegen.h
//
//	Description:	Contains all the initialization, data declarations
//					This file serves are a template for
//					using PM_pulsegen Library to interface and incorporates all the
//					library specific initializations and other important aspects of usage.
//
//	Version: 		1.0
//
//  Target:  		TMS320F28379D,
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2004-2015
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description / Status
//----------------------------------------------------------------------------------
// Dec 2016  - Example project for PM PTO PulseGen Library Usage
//----------------------------------------------------------------------------------
#ifndef PULSEGEN_INCLUDE_H_
#define PULSEGEN_INCLUDE_H_

#include "PM_pto_pulsegen_Include.h"

extern void pto_pulsegen_setup_GPIO(void);
extern void EPWM4_Config(void);
extern void pto_pulsegen_Init(void);
extern void error();
extern interrupt void ptoIsr(void);
extern uint32_t remVal;
uint32_t pto_setOptions(
		uint32_t numPulses,
		uint32_t Period,
		uint32_t ptoInterruptTime,
		uint16_t ptoDirection,
		uint16_t run);

#endif
