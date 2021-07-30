#ifndef _VCU2_CRC_H_
#define _VCU2_CRC_H_
//#############################################################################
//! \file include/vcu2/vcu2_crc.h
//!
//! \brief  Cyclic Redundancy Check Header File
//!
//! \date   Oct 24, 2012
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
#include "vcu2_types.h"


//!
//! \defgroup VCU2_CRC Cyclic Redundancy Check (VCU2)

//!
//! \ingroup VCU2_CRC
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define INIT_CRC8 	 	0x0			//!< Initial CRC Register Value
#define INIT_CRC16 		0x0			//!< Initial CRC Register Value
#define INIT_CRC24 		0x0			//!< Initial CRC Register Value
#define INIT_CRC32 		0x0			//!< Initial CRC Register Value

//*****************************************************************************
// typedefs
//*****************************************************************************
//! \brief Parity: the location, in a word, of the first byte of the CRC calculation
//!
typedef enum{
	PARITY_LOWBYTE=0,
	PARITY_HIGHBYTE
}Parity_e;

//! \brief CRC structure
//!
typedef struct _CRC_Obj_{
	uint32_t	seedValue;			//!< Initial value of the CRC calculation
	uint16_t	nMsgBytes;			//!< the number of bytes in the message buffer
	Parity_e	parity;				//!< the location, in a word, of the first byte for the CRC calculation
	uint32_t	crcResult;			//!< the calculated CRC
	void		*pMsgBuffer;		//!< Pointer to the message buffer
	void 		*pCrcTable;			//!< Pointer to the CRC lookup table
	void (*init)(void *);			//!< Function pointer to CRC initialization routine
	void (*run)(void *);			//!< Function pointer to CRC computation routine
}CRC_Obj;

//! \brief Handle to the CRC structure
//!
typedef CRC_Obj *CRC_Handle;


//*****************************************************************************
// globals
//*****************************************************************************
//! \brief Object of the structure CRC_Obj
//!
extern CRC_Obj CRC;

//*****************************************************************************
// function prototypes
//*****************************************************************************

//----------------------
// CRC Helper functions
//----------------------
//! \brief Bit-reverse a value
//!
//! Bit reverse a given hex value, The number of bits must be a power of 2
//!
//! \param valToReverse Value to reverse
//! \param bitWidth Bit-width of the input, must be a power of 2
//!
//! \return	bit-reversed value
//
uint32_t CRC_bitReflect(uint32_t valToReverse,int16_t bitWidth);

//
//! \brief power of 2
//!
//! recursive function to calculate a positive integer that is a power of two
//!
//! \param power The exponent of two
//!
//! \returns an integer that is a power of two
//!
//
uint16_t CRC_pow2(uint16_t power);

//! \brief Workaround to the silicon issue of first VCU calculation on power up being
//!  erroneous
//! 
//! Details Due to the internal power-up state of the VCU module, it is possible 
//! that the first CRC result will be incorrect. This condition applies to the 
//! first result from each of the eight CRC instructions. 
//! This rare condition can only occur after a power-on reset, but will not
//! necessarily occur on every power on. A warm reset will not cause this condition 
//! to reappear.
//! Workaround(s): The application can reset the internal VCU CRC logic by 
//! performing a CRC calculation of a single byte in the initialization routine. 
//! This routine only needs to perform one CRC calculation and can use any of the 
//! CRC instructions
//
void CRC_reset(void);

//----------------------
//8-bit CRC functions
//----------------------

//! \brief Initializes the CRC object
//! 
//! Clears the CRCMSGFLIP bit is cleared ensuring the input
//! is interpreted in normal bit-order
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_init8Bit(CRC_Handle hndCRC );

//! \brief Calculate the 8-bit CRC using polynomial 0x7
//!
//! Calculates the 8-bit CRC using polynomial 0x7 on the VCU.
//! Depending on the parity chosen the CRC begins at either 
//! the low byte (PARITY_LOWBYTE) or the high byte (PARITY_HIGHBYTE) 
//! of the first word.
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run8Bit(CRC_Handle hndCRC);

//! \brief Runs the 8-bit CRC routine using polynomial 0x7 
//!        with the input bits reversed
//!
//! By setting the CRCMSGFLIP bit, the input is fed through the
//! VCU 8-bit CRC calculator (polynomial 0x7) in reverse bit order
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run8BitReflected(CRC_Handle hndCRC);

//! \brief C table-lookup 8-bit CRC calculation
//!
//! The CRC is calculated using a table lookup method, where 
//! each byte of the input is an index into the table. The value
//! at that index is XOR'd into a variable called the accumulator. 
//! Once the final byte's CRC is looked up and accumulated we get
//! the CRC for the entire message block
//!
//! \param[in] hndCRC handle to the CRC object
//! \sa http://www.ross.net/crc/download/crc_v3.txt
//
void CRC_run8BitTableLookupC(CRC_Handle hndCRC);

//----------------------
//16-bit CRC functions
//----------------------

//! \brief Initializes the CRC object
//! 
//! Clears the CRCMSGFLIP bit is cleared ensuring the input
//! is interpreted in normal bit-order
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_init16Bit(CRC_Handle hndCRC);

//! \brief Runs the CRC routine using polynomial 0x8005
//!
//! Calculates the 16-bit CRC using polynomial 0x8005 on the VCU.
//! Depending on the parity chosen the CRC begins at either 
//! the low byte (PARITY_LOWBYTE) or the high byte (PARITY_HIGHBYTE) 
//! of the first word.
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run16BitPoly1(CRC_Handle hndCRC);

//! \brief Runs the CRC routine using polynomial 0x1021
//!
//! Calculates the 16-bit CRC using polynomial 0x1021 on the VCU.
//! Depending on the parity chosen the CRC begins at either 
//! the low byte (PARITY_LOWBYTE) or the high byte (PARITY_HIGHBYTE) 
//! of the first word.
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run16BitPoly2(CRC_Handle hndCRC);

//! \brief Runs the 16-bit CRC routine using polynomial 0x8005
//!        with the input bits reversed
//!
//! By setting the CRCMSGFLIP bit, the input is fed through the
//! VCU 16-bit CRC calculator (polynomial 0x8005) in reverse bit order
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run16BitPoly1Reflected(CRC_Handle hndCRC);

//! \brief Runs the 16-bit CRC routine using polynomial 0x1021
//!        with the input bits reversed
//!
//! By setting the CRCMSGFLIP bit, the input is fed through the
//! VCU 16-bit CRC calculator (polynomial 0x1021) in reverse bit order
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run16BitPoly2Reflected(CRC_Handle hndCRC);

//! \brief C table-lookup 16-bit CRC calculation
//!
//! The CRC is calculated using a table lookup method, where 
//! each byte of the input is an index into the table. The value
//! at that index is XOR'd into a variable called the accumulator. 
//! Once the final byte's CRC is looked up and accumulated we get
//! the CRC for the entire message block
//!
//! \param[in] hndCRC handle to the CRC object
//! \sa http://www.ross.net/crc/download/crc_v3.txt
//
void CRC_run16BitTableLookupC(CRC_Handle hndCRC);

//! \brief C table-lookup 16-bit CRC calculation(reflected algorithm)
//!
//! The CRC is calculated using a table lookup method, where 
//! each byte of the input is an index into the table. The value
//! at that index is XOR'd into a variable called the accumulator. 
//! Once the final byte's CRC is looked up and accumulated we get
//! the CRC for the entire message block
//!
//! \param[in] hndCRC handle to the CRC object
//! \sa http://www.ross.net/crc/download/crc_v3.txt
//
void CRC_run16BitReflectedTableLookupC(CRC_Handle hndCRC);

//----------------------
//24-bit CRC functions
//----------------------
//! \brief Initializes the CRC object
//! 
//! Clears the CRCMSGFLIP bit is cleared ensuring the input
//! is interpreted in normal bit-order
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_init24Bit(CRC_Handle hndCRC);

//! \brief Runs the CRC routine
//!
//! Calculates the 24-bit CRC using polynomial 0x5d6dcb on the VCU.
//! Depending on the parity chosen the CRC begins at either 
//! the low byte (PARITY_LOWBYTE) or the high byte (PARITY_HIGHBYTE) 
//! of the first word.
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run24Bit(CRC_Handle hndCRC);

//! \brief Runs the 24-bit CRC routine using polynomial 0x5d6dcb 
//!        with the input bits reversed
//!
//! By setting the CRCMSGFLIP bit, the input is fed through the
//! VCU 24-bit CRC calculator (polynomial 0x5d6dcb) in reverse bit order
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run24BitReflected(CRC_Handle hndCRC);

//! \brief C table-lookup 24-bit CRC calculation
//!
//! The CRC is calculated using a table lookup method, where 
//! each byte of the input is an index into the table. The value
//! at that index is XOR'd into a variable called the accumulator. 
//! Once the final byte's CRC is looked up and accumulated we get
//! the CRC for the entire message block
//!
//! \param[in] hndCRC handle to the CRC object
//! \sa http://www.ross.net/crc/download/crc_v3.txt
//
void CRC_run24BitTableLookupC(CRC_Handle hndCRC);

//! \brief C table-lookup 24-bit CRC calculation(reflected algorithm)
//!
//! The CRC is calculated using a table lookup method, where 
//! each byte of the input is an index into the table. The value
//! at that index is XOR'd into a variable called the accumulator. 
//! Once the final byte's CRC is looked up and accumulated we get
//! the CRC for the entire message block
//!
//! \param[in] hndCRC handle to the CRC object
//! \sa http://www.ross.net/crc/download/crc_v3.txt
//
void CRC_run24BitReflectedTableLookupC(CRC_Handle hndCRC);

//----------------------
//32-bit CRC functions
//----------------------

//! \brief Initializes the CRC object
//! 
//! Clears the CRCMSGFLIP bit is cleared ensuring the input
//! is interpreted in normal bit-order
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_init32Bit(CRC_Handle hndCRC);

//! \brief Runs the 32-bit CRC routine using polynomial 0x04c11db7
//!
//! Calculates the 32-bit CRC using polynomial 0x04c11db7 on the VCU.
//! Depending on the parity chosen the CRC begins at either 
//! the low byte (PARITY_LOWBYTE) or the high byte (PARITY_HIGHBYTE) 
//! of the first word.
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run32BitPoly1(CRC_Handle hndCRC);

//! \brief Runs the 32-bit CRC routine using polynomial 0x1edc6f41
//!
//! Calculates the 32-bit CRC using polynomial 0x1edc6f41 on the VCU.
//! Depending on the parity chosen the CRC begins at either 
//! the low byte (PARITY_LOWBYTE) or the high byte (PARITY_HIGHBYTE) 
//! of the first word.
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run32BitPoly2(CRC_Handle hndCRC);

//! \brief Runs the 32-bit CRC routine using polynomial 0x04c11db7
//!        with the input bits reversed
//!
//! By setting the CRCMSGFLIP bit, the input is fed through the
//! VCU 32-bit CRC calculator (polynomial 0x04c11db7) in reverse bit order
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run32BitPoly1Reflected(CRC_Handle hndCRC);

//! \brief Runs the 32-bit CRC routine using polynomial 0x1edc6f41
//!        with the input bits reversed
//!
//! By setting the CRCMSGFLIP bit, the input is fed through the
//! VCU 32-bit CRC calculator (polynomial 0x1edc6f41) in reverse bit order
//!
//! \param[in] hndCRC handle to the CRC object
//
void CRC_run32BitPoly2Reflected(CRC_Handle hndCRC);

//! \brief C table-lookup 32-bit CRC calculation
//!
//! The CRC is calculated using a table lookup method, where 
//! each byte of the input is an index into the table. The value
//! at that index is XOR'd into a variable called the accumulator. 
//! Once the final byte's CRC is looked up and accumulated we get
//! the CRC for the entire message block
//!
//! \param[in] hndCRC handle to the CRC object
//! \sa http://www.ross.net/crc/download/crc_v3.txt
//
void CRC_run32BitTableLookupC(CRC_Handle hndCRC);

//! \brief C table-lookup 32-bit CRC calculation(reflected algorithm)
//!
//! The CRC is calculated using a table lookup method, where 
//! each byte of the input is an index into the table. The value
//! at that index is XOR'd into a variable called the accumulator. 
//! Once the final byte's CRC is looked up and accumulated we get
//! the CRC for the entire message block
//! 
//! \param[in] hndCRC handle to the CRC object
//! \sa http://www.ross.net/crc/download/crc_v3.txt
//
void CRC_run32BitReflectedTableLookupC(CRC_Handle hndCRC);

#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _VCU2_CRC_H_ definition
