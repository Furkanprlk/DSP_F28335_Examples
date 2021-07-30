#ifndef _VCU0_TYPES_H_
#define _VCU0_TYPES_H_
//#############################################################################
//! \file   include/vcu0/vcu0_types.h
//!
//! \brief  Type definitions for the VCU0 algorithms
//!
//! \date   Apr 7, 2011
//
//  Group: 			C2000
//  Target Family:	F2837x
//
// (C)Copyright 2012, Texas Instruments, Inc.
//#############################################################################
//$TI Release: C28x VCU Library Version v2.00.00.00 $
//$Release Date: Dec 6, 2013 $
//#############################################################################


//*****************************************************************************
// includes
//*****************************************************************************
//#include <string.h>
#include <limits.h>
#include <stdint.h>
#include <stdbool.h>

//!
//! \defgroup VCU0_DEFINITIONS VCU0 Type Defintions


//!
//! \ingroup VCU0_DEFINITIONS
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
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


//*****************************************************************************
// typedefs
//*****************************************************************************
//! \brief Parity enumeration
//!
//! The parity is used by the CRC algorithm to determine whether to begin
//! calculations from the low byte (EVEN) or from the high byte (ODD) of the
//! first word in the message.
//
typedef enum {
  EVEN = 0,
  ODD = 1
} parity_t;

//typedef unsigned char      uint8;
typedef unsigned int       uint16;
typedef unsigned long      uint32;
typedef unsigned long long uint64;

#ifndef F28_DATA_TYPES
#define F28_DATA_TYPES
typedef int             	int16;
typedef long            	int32;
typedef long long			int64;
typedef unsigned int    	Uint16;
typedef unsigned long   	Uint32;
typedef unsigned long long	Uint64;
typedef float           	float32;
typedef long double     	float64;
#endif //F28_DATA_TYPES

#ifndef VCU0_TYPES
#define VCU0_TYPES
typedef long               RCODE;

#ifndef _STDBOOL
#define _STDBOOL
typedef unsigned long      bool;
#endif /* _STDBOOL */

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
//! \brief Complex data
//!
typedef struct
{
  SINT16 real; 			//!< Real Part
  SINT16 imag; 			//!< Imaginary Part

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

#endif //VCU0_TYPES

#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _VCU0_TYPES_H_ definition
