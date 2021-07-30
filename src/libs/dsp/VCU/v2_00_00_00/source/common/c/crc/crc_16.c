//#############################################################################
//! \file source/common/C/crc/crc_16.c
//!
//! \brief  16-bit CRC
//  \author Vishal Coelho
//  \date   Oct 4, 2012
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
#include "vcu2_crc.h"

//*****************************************************************************
// defines
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************

void CRC_run16BitTableLookupC(CRC_Handle hndCRC)
{
	uint16_t i;
	uint16_t tableIndex;
	uint16_t parity        = (uint16_t)hndCRC->parity;
	uint16_t accumulator   = hndCRC->seedValue;
	uint16_t *pInputVector = (uint16_t *)hndCRC->pMsgBuffer;
	uint16_t *pCrcTable    = (uint16_t *)hndCRC->pCrcTable;

	// The assumption is the message bytes are packed into 16-bit words
	// and the calculation starts from either the high or low byte
	// The memory arrangement is as follows:
	// Address|_LB__|_HB__|
	// 0x0000 |_D0L_|_D0H_|
	// 0x0001 |_D1L_|_D1H_|
	// 0x0002 |_D2L_|_D2H_|
	// 0x0003 |_D3L_|_D3H_|
	// 0x0004 |_D4L_|_D4H_|
	// ...

	for(i = 0; i < hndCRC->nMsgBytes; i++, parity++){
		// __byte selects either the low(0) or high(1) byte in a word
		// the initial selection provided by the enumeration parity
		// the table index is calculated from the high byte of the accumulator
		// XOR'd with the low and high bytes of each word in the input vector
		tableIndex  = (accumulator >> 8) ^ __byte((int *)pInputVector, parity);
		accumulator = (accumulator << 8) ^ pCrcTable[tableIndex];
	}

	// Save the CRC result
	hndCRC->crcResult = (uint32_t)accumulator;
}

void CRC_run16BitReflectedTableLookupC(CRC_Handle hndCRC)
{
	uint16_t i;
	uint16_t tableIndex;
	uint16_t parity        = (uint16_t)hndCRC->parity;
	uint16_t accumulator   = hndCRC->seedValue;
	uint16_t *pInputVector = (uint16_t *)hndCRC->pMsgBuffer;
	uint16_t *pCrcTable    = (uint16_t *)hndCRC->pCrcTable;

	// The assumption is the message bytes are packed into 16-bit words
	// and the calculation starts from either the high or low byte
	// The memory arrangement is as follows:
	// Address|_LB__|_HB__|
	// 0x0000 |_D0L_|_D0H_|
	// 0x0001 |_D1L_|_D1H_|
	// 0x0002 |_D2L_|_D2H_|
	// 0x0003 |_D3L_|_D3H_|
	// 0x0004 |_D4L_|_D4H_|
	// ...

	for(i = 0; i < hndCRC->nMsgBytes; i++, parity++){
		// __byte selects either the low(0) or high(1) byte in a word
		// the initial selection provided by the enumeration parity
		// the table index is calculated from the low byte of the accumulator
		// XOR'd with the low and high bytes of each word in the input vector
		tableIndex  = (accumulator & 0x00FF) ^ __byte((int *)pInputVector, parity);
		accumulator = (accumulator >> 8) ^ pCrcTable[tableIndex];
	}

	// Save the CRC result
	hndCRC->crcResult = (uint32_t)accumulator;
}

// End of file
