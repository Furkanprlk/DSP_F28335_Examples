#ifndef _TYPEDEFS_H
#define _TYPEDEFS_H

/*******************************************************************************
*  FILE PURPOSE: Define data types for C
********************************************************************************
*
* FILE NAME: typedefs.h
*
* DESCRIPTION:
*       This file contains common data type definitions
*
*  Copyright (c) 2009 Texas Instruments Inc.
*  All Rights Reserved This program is the confidential and proprietary
*  product of Texas Instruments Inc.  Any Unauthorized use, reproduction or
*  transfer of this program is strictly prohibited.
*
* HISTORY:
*
* 10/26/2004 S.Yim             Written
* 09/13/2006 U.Dasgupta        Added defines to help division by 3.
* 11/10/2006 S.Yim             Change the definitions of WIMAX_status_t to align
*                              withe M2P I/F
* 09/11/2007 S.Yim             Added MAC types.h here 
* 11/11/2008 R.Liang	       port to DSP/BIOS
*
* LIST OF FUNCTION PROTOTYPES:
*
******************************************************************************/

#include <limits.h>

//----------------------------------------------------------------------------
//                      Global Macro Declarations
//----------------------------------------------------------------------------
#ifndef TRUE
#define TRUE                    (1)
#define FALSE                   (0)
#endif

typedef enum {
  EVEN = 0,
  ODD = 1
} parity_t;
#define PARITY(a) ((a) % 2)

#define ALIGN16(len)    (((len) + 1) & ~1)

#if defined (CM3)
// Cortex CM3  
typedef unsigned char      uint8;
typedef unsigned short     uint16;
typedef signed short       sint16;
typedef unsigned int       uint32;
typedef signed int         sint32;
typedef int                bool;

typedef unsigned char         UINT8;
// Read-Write Data Types
typedef signed short          SINT16;     // Signed 16-bit integer (15-bit magnitude)
typedef unsigned short        UINT16;     // Unsigned 16-bit integer
typedef signed int            SINT32;     // Signed 32-bit integer (31-bit magnitude)
typedef unsigned int          UINT32;     // Unsigned 32-bit integer
//typedef int                   BOOL;       // Only TRUE/FALSE applied

// All pointers are 32 bits long
typedef SINT16                *PSINT16;   // Pointer to SINT16
typedef UINT16                *PUINT16;   // Pointer to UINT16
typedef SINT32                *PSINT32;   // Pointer to SINT32
typedef UINT32                *PUINT32;   // Pointer to UINT32

#else

//----------------------------------------------------------------------------
//                      Global Typedef Declarations
//----------------------------------------------------------------------------

/* size of, in octets */
#define OCTETS(x)   ((sizeof(x)) * (CHAR_BIT >> 3))

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
#ifndef _TI_STD_TYPES
typedef unsigned int       Uint16;
typedef unsigned long      Uint32;
#endif
#endif

typedef unsigned long long Uint64;
typedef float              float32;
typedef long double        float64;
#endif

typedef long               RCODE;
//typedef unsigned long      bool;

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

#endif

#define SIZEOF_SINT16         2
#define SIZEOF_UINT16         2
#define SIZEOF_SINT32         4
#define SIZEOF_UINT32         4


//----------------------------------------------------------------------------
//                      Complex data Typedef Declarations
//----------------------------------------------------------------------------
typedef struct
{
  SINT16 real;
  SINT16 imag;

}cplx16, ComplexShort, ComplexShort_t;

// VCU uses reverse order 
typedef struct
{
  SINT16 imag;
  SINT16 real;
}cplx16vcu, ComplexShortVCU;

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

#endif //_TYPEDEFS_H




