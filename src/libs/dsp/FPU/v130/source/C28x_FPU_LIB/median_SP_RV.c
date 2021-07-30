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
// FILE:    median_SP_RV.c
//
// TITLE:   Median of a real array of floats
//
// AUTHOR:  David M. Alter   Texas Instruments, Inc.
//
// HISTORY:
//   07/20/11 - original (D. Alter) 
//
//###########################################################################
// $TI Release: C28x Floating Point Unit Library V1.30 $
// $Release Date: January 04, 2012 $
//###########################################################################

#include "FPU.h"

//===========================================================================
// Function: float32 median_SP_RV(float32 *, Uint16)
//===========================================================================
//
// Median of a real array of floats.  Input array is NOT
// preserved. This function calls qsort_SP_CV(), which is an optimized
// version of the RTS library qsort() for floats.
//
// Dependencies:      qsort_SP_RV()
// Useage:            z = median_SP_RV(x, N);
// Passed Parameters: float32 *x = input array
//                    Uint16 N = length of x array
// Return value:      float32 z = result
//
// Notes:
// 1) This function is destructive to the input array x in that it will be
//    sorted during function execution.  If this is not allowable, use
//    median_noreorder_SP_CV().
//
//---------------------------------------------------------------------------


//***************************************************************************
float32 median_SP_RV(float32 *x, Uint16 N)
{
	qsort_SP_RV(x, N);

	if(N%2==0) return (x[N/2]+x[N/2-1])/2;
	else return x[N/2];

} // end of median_SP_RV()

//===========================================================================
// End of file
//===========================================================================

