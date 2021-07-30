//###########################################################################
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// ------------------------------------------------------------------------
//          Copyright (C) 2014-2015 Texas Instruments, Incorporated.
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
// $TI Release: C28x Floating Point Unit Library V1.40.00.00 $
// $Release Date: Mar 10, 2014 $
//###########################################################################

#include "fpu_vector.h"

//===========================================================================
// Function: void qsort_SP_RV(void *, uint16_t)
//===========================================================================
//
// Sorts an array of floats. This function is a partially 
// optmized version of qsort.c from the C28x cgtools lib qsort() v6.0.1.
//
// Dependencies:      none
// Useage:            qsort_SP_RV(x, N);
// Passed Parameters: void *x = input array of floats
//                    uint16_t N = size of a array
// Return value:      none
// Notes:
// 1) Performance is best with -o1, -mf3 compiler options (cgtools v6.0.1)
//
//---------------------------------------------------------------------------

inline static void swap_item(float *, float *);

//***************************************************************************
void qsort_SP_RV(void *base, uint16_t nmemb)
{
    char   *basep  = base;              /* POINTER TO ARRAY OF ELEMENTS */
    uint16_t  i      = 0;                 /* left scan index  */
    uint16_t  j      = 2*(nmemb - 1);     /* right scan index */
    uint16_t pivot = nmemb & 0xFFFE;      /* Want closest even value */
    char   *pivp   = basep + pivot;
   
    if (nmemb <= 1) return;

    while( i < j )
    {
        while(*(float*)(basep + i) < *(float*)pivp) i=i+2;
        while(*(float*)(basep + j) > *(float*)pivp) j=j-2;

        if( i < j )
        {
            swap_item((float*)(basep + i), (float*)(basep + j));
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
inline static void swap_item(float *src, float *dest)
{
    float temp;

    temp = *src;
	*src  = *dest;
	*dest = temp;

} // end of swap_item()

//===========================================================================
// End of file
//===========================================================================

