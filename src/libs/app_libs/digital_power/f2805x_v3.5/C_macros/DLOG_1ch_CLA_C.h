//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================
/**
 * Performs data logging to a specified output buffer.  This module uses DLOG_1ch_CLA_C structures.
 * The structure should be initialized by the DLOG_1ch_CLA_C_INIT macro.
 * Data logging will occur on every 'n' module call, where the logging offset must be specified
 * in the PreScalar parameter.
 */

#ifndef DLOG_1CH_CLA_C_H_
#define DLOG_1CH_CLA_C_H_

/**
 * Data logger states
 */
#define WAIT_FOR_TRIGGER ((float32) 0)
#define CHECK_FOR_RISING_EDGE ((float32) 1)
#define LOG_DATA ((float32) 2)

/**
 * Data logger structure
 */
typedef struct {
	float32 CurrTask;
	float32 Size;
	Uint16 Cnt;
	float32 PreScaler;
	float32 SkipCnt;
	float32 Input;
	float32 TrigVal;
	volatile float32 *OutputBuff;
} DLOG_1ch_CLA_C;

/*
 * Stores data from a single Input to the buffer.
 * @param v - DLOG_1ch_CLA_C structure with collected data and destination buffer.
 */
#define DLOG_1ch_CLA_C(v)																						\
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
 * Initial values for the DLOG_1ch_CLA_C structure.
 */
#define DLOG_1ch_CLA_C_INIT(v)		\
		v.CurrTask = 0;				\
		v.Size = 0;					\
		v.Cnt = 0;					\
		v.PreScaler = 0;			\
		v.SkipCnt = 0;				\
		v.Input = 0;				\
		v.TrigVal = 0;				\
		v.OutputBuff = 0

#endif /* DLOG_1CH_CLA_C_H_ */
