//###########################################################################
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// ------------------------------------------------------------------------
//          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
//                          All Rights Reserved.
// ========================================================================
//
// FILE:    median_noreorder_SP_RV.c
//
// TITLE:   Median of a real valued array of floats.
//
// AUTHOR:  David M. Alter   Texas Instruments, Inc.
//
// HISTORY:
//   07/01/11 - original (D. Alter) 
//
//###########################################################################
// $TI Release: C28x Floating Point Unit Library V1.30 $
// $Release Date: January 04, 2012 $
//###########################################################################

#include "FPU.h"

//===========================================================================
// Function: float32 median_noreorder_SP_RV(const float32 *, Uint16)
//===========================================================================
//
// Median of a real valued array of floats. Input array is preserved.
//
// Dependencies:      median_SP_RV(), memcpy_fast()
// Useage:            z = median_noreorder_SP_CV(x, N);
// Passed Parameters: float32 *x = pointer to array of real input values
//                    Uint16 N = size of x array
// Return value:      float32 z = the median of x[]
// Notes:
// 1) This function simply makes a local copy of the input array, and then
//    calls median_SP_CV() using the copy.
// 2) The length of the copy of the input array is allocated at compile time
//    by the constant 'K' defined in the code.  If the passed parameter N
//    is greated than K, memory corruption will result.  A better way to do
//    this is to dynamically allocate the copy array at run time using
//    malloc().  This is work for the future. 
//
//---------------------------------------------------------------------------

#define		K	256			// WARNING: K must be at least as large as N.

//***************************************************************************
float32 median_noreorder_SP_RV(const float32 *x, Uint16 N)
{
	float32 x_copy[K], y;

	memcpy_fast(x_copy, x, N<<1);	  // Copy 2*N 16-bit words on C28x
	y = median_SP_RV(x_copy, N);      // Call median()
	return(y);
} // end of median_noreorder_SP_RV()

//===========================================================================
// End of file
//===========================================================================

