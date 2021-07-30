//###########################################################################
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// ------------------------------------------------------------------------
//          Copyright (C) 2014 Texas Instruments, Incorporated.
//                          All Rights Reserved.
// ==========================================================================
//
// FILE:   fpu_types.h
//
// TITLE:  Prototypes and Definitions for the C28x FPU Library
//
//###########################################################################
// $TI Release: C28x Floating Point Unit Library V1.40.00.00 $
// $Release Date: Mar 10, 2014 $
//###########################################################################

#ifndef _FPU_TYPES_H_
#define _FPU_TYPES_H_

#include <stdint.h>
#include "float.h"

#ifdef __cplusplus
extern "C" {
#endif

//-----------------------------------------------------------------------------
// Type Definitions
//-----------------------------------------------------------------------------
#ifndef FPU_TYPES
#define FPU_TYPES

// Complex Float Data Type
typedef struct {
    float dat[2];
} complex_float;

#endif //FPU_TYPES

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of _FPU_TYPES_H_

//===========================================================================
// End of file.
//===========================================================================

