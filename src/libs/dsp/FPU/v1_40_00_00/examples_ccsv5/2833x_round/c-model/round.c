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
//  FILE:    Round.c
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

#include "Round.h"				// Main include file
#include <math.h>

/**********************************************************************
* Function: round()
*
* Description: Unbiased rounding of a floating point real number.
* 
* Benchmark: 78 cycles using C28x compiler v6.0.1
**********************************************************************/
float round(float x)
{

	return( floor(x+0.5) ); 

} // end round()

//=============================================================================
// End of file.
//=============================================================================
