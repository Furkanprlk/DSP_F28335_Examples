//#############################################################################
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// ----------------------------------------------------------------------------
//          Copyright (C) 2010 Texas Instruments, Incorporated.
//                          All Rights Reserved.
// ============================================================================
//
// FILE:   icabs_vec.h
//
//#############################################################################
// $TI Release: C28x Floating Point Unit Library V1.31 $
// $Release Date: Sep 10, 2012 $
//#############################################################################

#ifndef ICABS_VEC_H
#define ICABS_VEC_H


#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Float32 Definitions and Prototypes
//-----------------------------------------------------------------------------
typedef struct {
	float32 dat[2];
} complex_float;

void icabs_vec(const complex_float* , float32* , const Uint16 )

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of ICABS_VEC_H

//=============================================================================
// End of file.
//=============================================================================
