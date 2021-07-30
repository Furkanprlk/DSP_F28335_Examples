/**
 * ADC driver for the F.  Normalizes ADC results returning a floating point number
 * in the range [0.0, 1.0].  Requires ADC modules to be configured with ADC_SOC_CNF function
 * found within the ADC_SOC_Cnf.c source file.
 * @see ADC_SOC_Cnf.c
 */
//================================================================================
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
//  ALL RIGHTS RESERVED
//================================================================================

#ifndef ADCDRV_F_C_H_
#define ADCDRV_F_C_H_

#include "DPlib.h"

/**
 * ADC bit-resolution constant.
 */
#define INV_4096 ((float) 0.000244140625)

/*
 * Normalizes ADC conversions.
 * @param ADC result
 * @returns floating point normalized ADC conversion in range [0.0, 1.0]
 */
#define ADCDRV_1ch_F_C(num) ((float)(num) * INV_4096)

#endif /* ADCDRV_F_C_H_ */
