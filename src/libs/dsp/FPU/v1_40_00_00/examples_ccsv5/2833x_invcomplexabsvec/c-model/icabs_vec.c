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
//  FILE:    icabs_vec.c
//
//  AUTHOR:  David M. Alter, Texas Instruments Inc.
//
//  HISTORY: 
//      06/28/11 - original (D. Alter)
//
//#############################################################################
// $TI Release: C28x Floating Point Unit Library V1.40.00.00 $
// $Release Date: Mar 10, 2014 $
//#############################################################################

#include "icabs_vec.h"				// Main include file
#include <math.h>                   // Needed for sqrt()

/**********************************************************************
* Function: icabs_vec()
*
* Description: Inverse absolute value of a complex vector
**********************************************************************/
void icabs_vec(const complex_float* x, float* y, const uint16_t N)
{
    uint16_t i;

    for(i=0; i<N; i++)
    {
        y[i] = 1.0/sqrt(x[i].dat[0]*x[i].dat[0] + x[i].dat[1]*x[i].dat[1]);
    }

} // end of icabs_vec()

//=============================================================================
// End of file.
//=============================================================================
