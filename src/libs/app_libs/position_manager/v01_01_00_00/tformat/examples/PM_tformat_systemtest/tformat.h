//----------------------------------------------------------------------------------
//	FILE:			tformat.h
//
//	Description:	Contains all the initialization, data declarations and setup
//					for tformat encoder interface. This file serves are a template for
//					using PM_tformat Library to interface and incorporates all the encoder
//					and library specific initializations and other important aspects of usage.
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
// Sep 2016  - Example project for PM T-format Library Usage
//----------------------------------------------------------------------------------

#include "PM_tformat_Include.h"

#define TFORMAT_FREQ_DIVIDER	20
//Clock Frequency = SYSCLK/(4*TFORMAT_FREQ_DIVIDER) ==> (2.5MHz)

extern void tformat_setup_GPIO(void);
extern void tformat_config_XBAR(void);
extern uint16_t tformat_exCommands(void);
extern uint16_t CheckCRC (uint16_t expectcrc5, uint16_t receivecrc5);
extern void EPWM4_Config(void);

extern interrupt void spiRxFifoIsr(void);
extern void tformat_Init(void);
extern void error();
