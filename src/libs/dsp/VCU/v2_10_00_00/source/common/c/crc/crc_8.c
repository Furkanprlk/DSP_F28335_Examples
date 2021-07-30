//#############################################################################
//! \file source/common/C/crc/crc_8.c
//!
//! \brief  8-bit CRC
//  \author Vishal Coelho
//  \date   Oct 4, 2012
//
//  Group: 			C2000
//  Target Family:	F2837x
//
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/ 
// ALL RIGHTS RESERVED 
//#############################################################################
//$TI Release: C28x VCU Library Version v2.10.00.00 $
//$Release Date: Mar 3, 2015 $
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

void CRC_run8BitTableLookupC(CRC_Handle hndCRC)
{
	uint32_t i;
	uint16_t tableIndex;
	uint16_t accumulator   = hndCRC->seedValue;
	uint16_t parity        = (uint16_t)hndCRC->parity;
	uint16_t *pInputVector = (uint16_t *)hndCRC->pMsgBuffer;
	uint16_t *pCrcTable    = (uint16_t *)hndCRC->pCrcTable;

	// The assumption is the message bytes are packed into 16-bit words
	// and the calculation starts from from either the high or low byte
	// The memory arrangement is as follows
	// Address|__LB__|__HB__|
	// 0x0000 |__D0__|__D1__|
	// 0x0001 |__D2__|__D3__|
	// 0x0002 |__D4__|__D5__|
	// 0x0003 |__D6__|__D7__|
	// 0x0004 |__D8__|__D9__|
    // ...

	for(i = 0; i < hndCRC->nMsgBytes; i++, parity++){
		// __byte selects either the low(0) or high(1) byte in a word
		// the initial selection provided by the enumeration parity
		tableIndex = accumulator ^ __byte((int *)pInputVector, parity);
		accumulator = pCrcTable[tableIndex];
	}

	// Save the CRC result
	hndCRC->crcResult = (uint32_t)(accumulator & 0x00FF);
}

// End of file
