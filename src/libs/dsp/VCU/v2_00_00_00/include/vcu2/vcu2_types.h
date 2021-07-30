#ifndef _VCU2_TYPES_H_
#define _VCU2_TYPES_H_
//#############################################################################
//! \file   include/vcu2/vcu2_types.h
//!
//! \brief  Type definitions for the VCU2 algorithms
//!
//! \date   Nov 15, 2012
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
#include <stdint.h>

//!
//! \defgroup VCU2_DEFINITIONS VCU2 Type Defintions


//!
//! \ingroup VCU2_DEFINITIONS
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define NULL            	0
#define	TRUE				1
#define	FALSE				0

//*****************************************************************************
// typedefs
//*****************************************************************************

#ifndef VCU2_TYPES
#define VCU2_TYPES

//! \brief Boolean enumeration
//!
typedef enum{
	BOOL_FALSE=0,
	BOOL_TRUE
}Bool_e;

//! \brief Complex data (CPACK = 0)
//!
//! On reset the CPACK bit is 0, therefore, this is the
//! default complex structure
//
typedef struct{
	int16_t	real; 			//!< Real Part
	int16_t imag; 			//!< Imaginary Part
}complexShort_t;


typedef union{
//! \brief Complex data (CPACK = 1)
//!
	struct{
		int16_t imag; 			//!< Real Part
		int16_t	real; 			//!< Imaginary Part
	}cplx;
	uint32_t ui32;
}complexCPACKON_t;


typedef union{
//! \brief Complex data (CPACK = 0)
//!
	struct{
		int16_t	real; 			//!< Real Part
		int16_t imag; 			//!< Imaginary Part
	}cplx;
	uint32_t ui32;
}complexCPACKOFF_t;

#endif //VCU2_TYPES

#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _VCU2_TYPES_H_ definition
