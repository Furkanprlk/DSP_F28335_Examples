/**
 * Performs data logging to a specified output buffers.  This module uses DLOG_4ch_F_C structures.
 * The structure should be initialized by the DLOG_4ch_F_C_INIT macro.  Data logging will occur
 * on every 'n' module call, where the logging offset must be specified in the PreScaler field.
 */
//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================

#ifndef DLOG_4CH_F_C_H_
#define DLOG_4CH_F_C_H_

#include "DPlib.h"

/**
 * Data logger states
 */
#define WAIT_FOR_TRIGGER ((float) 0)
#define CHECK_FOR_RISING_EDGE ((float) 1)
#define LOG_DATA ((float) 2)

/**
 * Data logger structure.
 */
typedef struct {
	float CurrTask;
	float Size;
	uint16_t Cnt;
	float PreScaler;
	float SkipCnt;
	float Input1;
	float Input2;
	float Input3;
	float Input4;
	float TrigVal;
	float *OutputBuffer1;
	float *OutputBuffer2;
	float *OutputBuffer3;
	float *OutputBuffer4;
} DLOG_4ch_F_C;

/**
 * Stores data from 4 Inputs to their respective buffers.
 * @param v - DLOG_4ch_F_C structure with collected data and destination buffers.
 */
#define DLOG_4ch_F_C(v)																						\
		if((v.CurrTask == WAIT_FOR_TRIGGER) && (v.Input1 < v.TrigVal)){v.CurrTask = CHECK_FOR_RISING_EDGE;}		\
		if((v.CurrTask == CHECK_FOR_RISING_EDGE) && (v.Input1 > v.TrigVal)){v.CurrTask = LOG_DATA;}				\
		if(v.CurrTask == LOG_DATA) {																			\
			v.SkipCnt++;																						\
			if(v.SkipCnt == v.PreScaler) {																		\
				v.SkipCnt = 0;																					\
				v.OutputBuffer1[v.Cnt] = v.Input1;																\
				v.OutputBuffer2[v.Cnt] = v.Input2;																\
				v.OutputBuffer3[v.Cnt] = v.Input3;																\
				v.OutputBuffer4[v.Cnt++] = v.Input4;															\
			}																									\
			if(v.Cnt == v.Size) {																				\
				v.CurrTask = WAIT_FOR_TRIGGER;																	\
				v.Cnt = 0;																						\
				v.SkipCnt = 0;																					\
			}																									\
		}																										\
		/* Ensure no invalid states */																			\
		if(v.CurrTask > LOG_DATA){v.CurrTask = WAIT_FOR_TRIGGER;}

/**
 * Initial values for DLOG_4ch_F_C structure.
 */
#define DLOG_4ch_F_C_INIT(v)		\
		v.CurrTask = 0;				\
		v.Size = 0;					\
		v.Cnt = 0;					\
		v.PreScaler = 0;			\
		v.SkipCnt = 0;				\
		v.Input1 = 0;				\
		v.Input2 = 0;				\
		v.Input3 = 0;				\
		v.Input4 = 0;				\
		v.TrigVal = 0;				\
		v.OutputBuffer1 = 0;		\
		v.OutputBuffer2 = 0;		\
		v.OutputBuffer3 = 0;		\
		v.OutputBuffer4 = 0

#endif /* DLOG_4CH_F_C_H_ */
