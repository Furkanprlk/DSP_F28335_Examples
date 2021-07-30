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
//  FILE:    complex_mult.c
//
//  AUTHOR:  David M. Alter, Texas Instruments Inc.
//
//  HISTORY: 
//      06/07/11 - original (D. Alter)
//
//#############################################################################
// $TI Release: C28x Floating Point Unit Library V1.40.00.00 $
// $Release Date: Mar 10, 2014 $
//#############################################################################

#include "complex_mult.h"				// Main include file

/**********************************************************************
* Function: complex_mult()
*
* Description: Complex multiply of two floating point complex numbers.
**********************************************************************/
complex_float complex_mult(complex_float a, complex_float b)
{
complex_float z;

	z.dat[0] = a.dat[0]*b.dat[0] - a.dat[1]*b.dat[1];		// real 
	z.dat[1] = a.dat[0]*b.dat[1] + a.dat[1]*b.dat[0];		// imag 

	return( z ); 

} // end complex_mult()

//=============================================================================
// End of file.
//=============================================================================
