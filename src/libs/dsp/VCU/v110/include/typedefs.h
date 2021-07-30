/******************************************************************************
*******************************************************************************
* 
* FILE: typedefs.h
* 
* DESCRIPTION: This file contains common data type definitions
* 
*******************************************************************************
*  $TI Release: C28x VCU Library Version v1.10 $
*  $Release Date: September 26, 2011 $
*******************************************************************************
*  This software is licensed for use with Texas Instruments C28x
*  family DSCs.  This license was provided to you prior to installing
*  the software.  You may review this license by consulting a copy of
*  the agreement in the doc directory of this library.
* ------------------------------------------------------------------------
*          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
*                          All Rights Reserved.
******************************************************************************/
#ifndef __TYPEDEFS_H__
#define __TYPEDEFS_H__

//###########################################################################
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//###########################################################################
#ifdef __cplusplus
extern "C"
{
#endif

#include <limits.h>

//###########################################################################
//
// Macro Definitions
//
//###########################################################################
#ifndef TRUE
#define TRUE                    (1)
#define FALSE                   (0)
#endif //TRUE

#define PARITY(a) ((a) % 2)

#define ALIGN16(len)    (((len) + 1) & ~1)

/* size of, in octets */
#define OCTETS(x)   ((sizeof(x)) * (CHAR_BIT >> 3))

#define SIZEOF_SINT16         2
#define SIZEOF_UINT16         2
#define SIZEOF_SINT32         4
#define SIZEOF_UINT32         4


//###########################################################################
//
// Structures, variables and typedefs
//
//###########################################################################

typedef enum {
  EVEN = 0,
  ODD = 1
} parity_t;

//typedef unsigned char      uint8;
typedef unsigned int       uint16;
typedef unsigned long      uint32;
typedef unsigned long long uint64;

#ifndef DSP28_DATA_TYPES
#define DSP28_DATA_TYPES

typedef int                int16;
typedef long               int32;
typedef long long          int64;

#ifndef STD_
typedef unsigned int       Uint16;
typedef unsigned long      Uint32;
#endif //STD_

typedef unsigned long long Uint64;
typedef float              float32;
typedef long double        float64;
#endif //DSP28_DATA_TYPES

typedef long               RCODE;
typedef unsigned long      bool;

// Read-Write Data Types
typedef signed int            SINT16;     // Signed 16-bit integer (15-bit magnitude)
typedef unsigned int          UINT16;     // Unsigned 16-bit integer
typedef signed long           SINT32;     // Signed 32-bit integer (31-bit magnitude)
typedef unsigned long         UINT32;     // Unsigned 32-bit integer
typedef signed long long      SINT64;     // Signed 64-bit integer
typedef unsigned long long    UINT64;     // Unsigned 64-bit integer
typedef int                   BOOL;       // Only TRUE/FALSE applied

// All pointers are 32 bits long
typedef SINT16                *PSINT16;   // Pointer to SINT16
typedef UINT16                *PUINT16;   // Pointer to UINT16
typedef SINT32                *PSINT32;   // Pointer to SINT32
typedef UINT32                *PUINT32;   // Pointer to UINT32
//----------------------------------------------------------------------------
//                      Complex data Typedef Declarations
//----------------------------------------------------------------------------
typedef struct
{
  SINT16 real;
  SINT16 imag;

}cplx16, ComplexShort;

//----------------------------------------------------------------------------
//                      Circular buffer Typedef Declarations
//----------------------------------------------------------------------------
typedef struct
{
  SINT16 *buf_p;   // buffer base addr
  UINT16 rdIdx;    // read index
  UINT16 wtIdx;    // write index
  UINT16 bufSize;  // buf size in 16-bits words

}Buffer_t;

//###########################################################################
//
// Mark the end of the C bindings section for C++ compilers.
//
//###########################################################################
#ifdef __cplusplus
}
#endif //__cplusplus

#endif // __TYPEDEFS_H__
