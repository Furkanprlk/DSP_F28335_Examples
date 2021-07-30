// ============================================================================
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// ----------------------------------------------------------------------------
//          Copyright (C) 2011-2012 Texas Instruments, Incorporated.
//                          All Rights Reserved.
//=============================================================================
//
//  FILE:    cabs_vec.c
//
//  AUTHOR:  David M. Alter, Texas Instruments Inc.
//
//  HISTORY: 
//      06/27/11 - original (D. Alter)
//
//#############################################################################
// $TI Release: C28x Floating Point Unit Library V1.40.00.00 $
// $Release Date: Mar 10, 2014 $
//#############################################################################

#include "maxidx.h"						// Main include file

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

//=============================================================================
// End of file.
//=============================================================================
