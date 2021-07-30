// ============================================================================
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// ----------------------------------------------------------------------------
//          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
//                          All Rights Reserved.
//=============================================================================
//
//  FILE:    mean_complex.c
//
//  AUTHOR:  David M. Alter, Texas Instruments Inc.
//
//  HISTORY: 
//      07/08/11 - original (D. Alter)
//
//#############################################################################
// $TI Release: C28x Floating Point Unit Library V1.30 $
// $Release Date: January 04, 2012 $
//#############################################################################

#include "mean_complex.h"				// Main include file
#include <math.h>                       // Needed for sqrt()


/**********************************************************************
* Function: mean_complex()
*
* Description: Mean of real and imaginary parts of a complex vector
**********************************************************************/
complex_float mean_complex(complex_float* x, Uint16 N)
{
    complex_float y;
    Uint16 i;

    y.dat[0] = 0;                        // zero the real part
    y.dat[1] = 0;                        // zero the imag part

    for(i=0; i<N; i++)
    {
        y.dat[0] = y.dat[0] + x[i].dat[0];
        y.dat[1] = y.dat[1] + x[i].dat[1];
    }

    y.dat[0] = y.dat[0]/N;
    y.dat[1] = y.dat[1]/N;

    return(y);

} // end of mean_complex()

//=============================================================================
// End of file.
//=============================================================================

