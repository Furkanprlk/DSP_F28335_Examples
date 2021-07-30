//----------------------------------------------------------------------------------
//	FILE:			qepdiv.h
//
//	Description:	Contains all the initialization, data declarations and setup
//					for PM QepDiv interface. This file serves are a template for
//					using PM_pto_qepdiv Library to interface and incorporates all the
//					library specific initializations and other important aspects of usage.
//
//	Version: 		1.0
//
//  Target:  		TMS320F28377D,
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2004-2015
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description / Status
//----------------------------------------------------------------------------------
// Mar 2017  - Example project for PM PTO QepDiv Library Usage
//----------------------------------------------------------------------------------
#ifndef QEPDIV_INCLUDE_H_
#define QEPDIV_INCLUDE_H_

#include "PM_pto_qepdiv_Include.h"

extern void pto_qepdiv_setup_GPIO(void);
extern void EPWM2_Config(void);
extern void pto_qepdiv_Init(void);
extern void error();

#endif
