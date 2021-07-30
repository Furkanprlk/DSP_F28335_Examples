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
// FILE:   maxidx.h
//
//#############################################################################
// $TI Release: C28x Floating Point Unit Library V1.40.00.00 $
// $Release Date: Mar 10, 2014 $
//#############################################################################

#ifndef MAXIDX_H
#define MAXIDX_H

#include <stdint.h>                 // C-99 Integer Types

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Float32 Definitions and Prototypes
//-----------------------------------------------------------------------------
typedef struct {
	float dat[2];
} complex_float;

uint16_t maxidx(float *, uint16_t );

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of MAXIDX_H

//=============================================================================
// End of file.
//=============================================================================
