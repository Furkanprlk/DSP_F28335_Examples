/**
 * Performs data logging to a specified output buffer.  This module uses DLOG_1ch_F_C structures.
 * The structure should be initialized by the DLOG_1ch_F_C_INIT macro.
 * Data logging will occur on every 'n' module call, where the logging offset must be specified
 * in the PreScalar parameter.
 */
//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================

#ifndef DLOG_1CH_F_C_H_
#define DLOG_1CH_F_C_H_

#include "DPlib.h"

/**
 * Data logger states
 */
#define WAIT_FOR_TRIGGER ((float) 0)
#define CHECK_FOR_RISING_EDGE ((float) 1)
#define LOG_DATA ((float) 2)

/**
 * Data logger structure
 */
typedef struct {
	float CurrTask;
	float Size;
	uint16_t Cnt;
	float PreScaler;
	float SkipCnt;
	float Input;
	float TrigVal;
	volatile float *OutputBuff;
} DLOG_1ch_F_C;

/*
 * Stores data from a single Input to the buffer.
 * @param v - DLOG_1ch_F_C structure with collected data and destination buffer.
 */
#define DLOG_1ch_F_C(v)																						\
		if((v.CurrTask == WAIT_FOR_TRIGGER) && (v.Input < v.TrigVal)) {v.CurrTask = CHECK_FOR_RISING_EDGE;}		\
		if((v.CurrTask == CHECK_FOR_RISING_EDGE) && (v.Input > v.TrigVal)){v.CurrTask = LOG_DATA;}				\
		if(v.CurrTask == LOG_DATA){																				\
			++v.SkipCnt;																						\
			if(v.SkipCnt == v.PreScaler){																		\
				v.SkipCnt = 0;																					\
				v.OutputBuff[v.Cnt++] = v.Input;																\
			}																									\
			if(v.Cnt == v.Size){																				\
				v.CurrTask = WAIT_FOR_TRIGGER;																	\
				v.Cnt = 0;																						\
				v.SkipCnt = 0;																					\
			}																									\
		}																										\
		/* Ensure no invalid states */																			\
		if(v.CurrTask > LOG_DATA) {v.CurrTask = WAIT_FOR_TRIGGER;}

/**
 * Initial values for the DLOG_1ch_F_C structure.
 */
#define DLOG_1ch_F_C_INIT(v)		\
		v.CurrTask = 0;				\
		v.Size = 0;					\
		v.Cnt = 0;					\
		v.PreScaler = 0;			\
		v.SkipCnt = 0;				\
		v.Input = 0;				\
		v.TrigVal = 0;				\
		v.OutputBuff = 0

#endif /* DLOG_1CH_F_C_H_ */
