// TI File $Revision: /main/1 $
// Checkin $Date: August 13, 2012   11:54:06 $
//###########################################################################
//
// FILE:    phy_primprefTable.c
//
// TITLE:   PHY_primePrefTable (size 64, 32bit words) 
//
// DESCRIPTION:
//       This file contains data relevant to PRIME scrambling sequence table
//
//  Copyright (c) 2009 Texas Instruments Inc.
//  All Rights Reserved This program is the confidential and proprietary
//  product of Texas Instruments Inc.  Any Unauthorized use, reproduction or
//  transfer of this program is strictly prohibited.
//
// HISTORY:
//
//
// LIST OF FUNCTION PROTOTYPES:
//
//
// Notes: 
//   
//
//###########################################################################
// $TI Release: F2837x Boot ROM Version 0 $
// $Release Date: Oct 1, 2013 $
//###########################################################################


#include "c1_bootrom.h"


#define UINT32	const Uint32

#pragma DATA_SECTION(PHY_primePrefTable,"primePrefTable");

UINT32 PHY_primePrefTable[64] = {
	0x00000000,   0x00000000,   0x00010001,   0x00000001,   0x00010001,   0x00010001,   0x00000000,
	0x00000001,   0x00010001,   0x00000000,   0x00000001,   0x00010000,   0x00000000,   0x00000000,
	0x00000000,   0x00000001,   0x00000000,   0x00000001,   0x00010000,   0x00000001,   0x00000000,
	0x00000001,   0x00010001,   0x00000001,   0x00000001,   0x00010001,   0x00010000,   0x00000001,
	0x00000000,   0x00000000,   0x00010001,   0x00000000,   0x00010001,   0x00010000,   0x00010000,
	0x00000000,   0x00010001,   0x00000001,   0x00010000,   0x00010001,   0x00000001,   0x00010001,
	0x00010000,   0x00000000,   0x00000000,   0x00000001,   0x00000001,   0x00000001,   0x00010001,
	0x00010001,   0x00000001,   0x00000001,   0x00010000,   0x00010000,   0x00000000,   0x00010000,
	0x00000001,   0x00010001,   0x00000001,   0x00000000,   0x00010001,   0x00010001,   0x00010001,
	0x00000001
};

#undef UINT32

