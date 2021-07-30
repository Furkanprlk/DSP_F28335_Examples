//#############################################################################
//! \file  2837x_MaxIndex/C-model/maxidx.c
//!
//! \brief  Unbiased rounding of a floating point real number
//! \author David M. Alter
//! \date   06/27/11
//
//  Group:             C2000
//  Target Family:     F2837x
//
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/ 
// ALL RIGHTS RESERVED 
//#############################################################################
//$TI Release: C28x Floating Point Unit Library V1.50.00.00 $
//$Release Date: Jun 2, 2015 $
//#############################################################################

#include "maxidx.h"                        // Main include file

uint16_t maxidx(float *x, uint16_t n)
{
    uint16_t i, index;
    float max;

    max = x[0];                         // start with x[0] as maximum
    index = 0;                          // start with 0 as index of maximum
    for(i=1; i<n; i++)
    {
        if(x[i] > max)
        {
            max = x[i];
            index = i;
        }
    }

    return index;

} // end of maxidx()

// End of file
