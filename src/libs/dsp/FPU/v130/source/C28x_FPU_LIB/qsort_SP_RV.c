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
// FILE:    qsort_SP_RV.c
//
// TITLE:   Sorts an array of floats.
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
// Function: void qsort_SP_RV(void *, Uint16)
//===========================================================================
//
// Sorts an array of floats. This function is a partially 
// optmized version of qsort.c from the C28x cgtools lib qsort() v6.0.1.
//
// Dependencies:      none
// Useage:            qsort_SP_RV(x, N);
// Passed Parameters: void *x = input array of floats
//                    Uint16 N = size of a array
// Return value:      none
// Notes:
// 1) Performance is best with -o1, -mf3 compiler options (cgtools v6.0.1)
//
//---------------------------------------------------------------------------

inline static void swap_item(float32 *, float32 *);

//***************************************************************************
void qsort_SP_RV(void *base, Uint16 nmemb)
{
    char   *basep  = base;              /* POINTER TO ARRAY OF ELEMENTS */
    Uint16  i      = 0;                 /* left scan index  */
    Uint16  j      = 2*(nmemb - 1);     /* right scan index */
    Uint16 pivot = nmemb & 0xFFFE;      /* Want closest even value */
    char   *pivp   = basep + pivot;
   
    if (nmemb <= 1) return;

    while( i < j )
    {
        while(*(float32*)(basep + i) < *(float32*)pivp) i=i+2;
        while(*(float32*)(basep + j) > *(float32*)pivp) j=j-2;

        if( i < j )
        {
            swap_item((float32*)(basep + i), (float32*)(basep + j));
            if ( pivot == i ) { pivot = j; pivp = basep + pivot; }
            else if( pivot == j ) { pivot = i; pivp = basep + pivot; }
            i=i+2; j=j-2;
        }
        else if ( i == j ) { i=i+2; j=j-2;  break; }
    }

    if(j > 0) qsort_SP_RV(basep, (j>>1) + 1);
    if((i>>1) < nmemb-1) qsort_SP_RV(basep + i, nmemb - (i>>1));

} // end of qsort_SP_RV()


//***************************************************************************
inline static void swap_item(float32 *src, float32 *dest)
{
    float32 temp;

    temp = *src;
	*src  = *dest;
	*dest = temp;

} // end of swap_item()

//===========================================================================
// End of file
//===========================================================================

