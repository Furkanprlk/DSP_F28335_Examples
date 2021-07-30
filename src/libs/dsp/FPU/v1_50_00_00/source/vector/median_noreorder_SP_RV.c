//#############################################################################
//! \file median_noreorder_SP_RV.c
//!
//! \brief  Median of a real valued array of floats (no reordering).
//! \author David M. Alter
//! \date   07/01/11
//
//  Group:             C2000
//  Target Family:     C28x+FPU32
//
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/ 
// ALL RIGHTS RESERVED 
//#############################################################################
//$TI Release: C28x Floating Point Unit Library V1.50.00.00 $
//$Release Date: Jun 2, 2015 $
//#############################################################################

#include "fpu_vector.h"

//===========================================================================
// Function: float median_noreorder_SP_RV(const float *, uint16_t)
//===========================================================================
//
// Median of a real valued array of floats. Input array is preserved.
//
// Dependencies:      median_SP_RV(), memcpy_fast()
// Usage:             z = median_noreorder_SP_CV(x, N);
// Passed Parameters: float *x = pointer to array of real input values
//                    uint16_t N = size of x array
// Return value:      float z = the median of x[]
// Notes:
// 1) This function simply makes a local copy of the input array, and then
//    calls median_SP_CV() using the copy.
// 2) The length of the copy of the input array is allocated at compile time
//    by the constant 'K' defined in the code.  If the passed parameter N
//    is greater than K, memory corruption will result.  A better way to do
//    this is to dynamically allocate the copy array at run time using
//    malloc().  This is work for the future. 
//
//---------------------------------------------------------------------------

#define        K    256         // WARNING: K must be at least as large as N.

//***************************************************************************
float median_noreorder_SP_RV(const float *x, uint16_t N)
{
    float x_copy[K], y;

    memcpy_fast(x_copy, x, N<<1);     // Copy 2*N 16-bit words on C28x
    y = median_SP_RV(x_copy, N);      // Call median()
    return(y);
} // end of median_noreorder_SP_RV()

// End of file
