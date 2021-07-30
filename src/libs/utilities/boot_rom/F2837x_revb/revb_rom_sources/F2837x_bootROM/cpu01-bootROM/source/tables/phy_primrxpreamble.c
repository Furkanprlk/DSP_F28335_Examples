// TI File $Revision: /main/1 $
// Checkin $Date: August 13, 2012   11:54:09 $
//###########################################################################
//
// FILE:    phy_primetxpreamble.c
//
// TITLE:   PHY_primeRXPreamable (size 256, 32bit words) 
//
// DESCRIPTION:
//       This file contains data relevant to PRIME RX preamble sequence table
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
// $TI Release: F2837x Boot ROM V1.0 $
// $Release Date: October 2013 $
//###########################################################################


#include "c1_bootrom.h"


#define UINT32	const Uint32

#pragma DATA_SECTION(PHY_primeRXPreamble,"primeRxPreamble");

UINT32 PHY_primeRXPreamble[256] = {
	0x00800080,   0xFFE1FFE1,   0xFF68FF68,   0x00A600A6,   0x001E001E,   0xFF40FF40,   0x00580058,
	0x00940094,   0xFF60FF60,   0xFFABFFAB,   0x00BE00BE,   0x00260026,   0xFF39FF39,   0xFFF0FFF0,
	0x00C800C8,   0x00180018,   0xFF3CFF3C,   0xFFC4FFC4,   0x00B300B3,   0x00770077,   0xFF7EFF7E,
	0xFF4EFF4E,   0x001F001F,   0x00C100C1,   0x00650065,   0xFF8FFF8F,   0xFF42FF42,   0xFFC7FFC7,
	0x00830083,   0x00BA00BA,   0x00480048,   0xFF9DFF9D,   0xFF47FF47,   0xFF7AFF7A,   0x00050005,
	0x00860086,   0x00B500B5,   0x00850085,   0x001B001B,   0xFFABFFAB,   0xFF62FF62,   0xFF52FF52,
	0xFF76FF76,   0xFFBBFFBB,   0x00090009,   0x004F004F,   0x00820082,   0x009F009F,   0x00A800A8,
	0x00A200A2,   0x00930093,   0x007F007F,   0x006B006B,   0x00590059,   0x004B004B,   0x00420042,
	0x003E003E,   0x00400040,   0x00480048,   0x00550055,   0x00660066,   0x007A007A,   0x008E008E,
	0x009F009F,   0x00A800A8,   0x00A300A3,   0x008B008B,   0x005D005D,   0x001B001B,   0xFFCDFFCD,
	0xFF84FF84,   0xFF57FF57,   0xFF59FF59,   0xFF95FF95,   0xFFFEFFFE,   0x006F006F,   0x00B100B1,
	0x009A009A,   0x00280028,   0xFF97FF97,   0xFF47FF47,   0xFF7CFF7C,   0x001D001D,   0x00AB00AB,
	0x00A100A1,   0xFFF9FFF9,   0xFF52FF52,   0xFF67FF67,   0x00300030,   0x00C200C2,   0x00590059,
	0xFF73FF73,   0xFF54FF54,   0x003A003A,   0x00C600C6,   0x000C000C,   0xFF3BFF3B,   0xFFCCFFCC,
	0x00BF00BF,   0x003F003F,   0xFF41FF41,   0xFFD2FFD2,   0x00C500C5,   0x00000000,   0xFF3DFF3D,
	0x004A004A,   0x009E009E,   0xFF65FF65,   0xFFC0FFC0,   0x00C000C0,   0xFFB3FFB3,   0xFF83FF83,
	0x00B500B5,   0xFFD2FFD2,   0xFF7FFF7F,   0x00B100B1,   0xFFB9FFB9,   0xFFABFFAB,   0x00AA00AA,
	0xFF7AFF7A,   0x00100010,   0x00660066,   0xFF61FF61,   0x00870087,   0xFFC8FFC8,   0xFFDBFFDB,
	0x006D006D,   0xFF80FF80,   0xFFD9FFD9,   0xFF5BFF5B,   0x00740074,   0x005E005E,   0xFF41FF41,
	0x00240024,   0x00AE00AE,   0xFF7CFF7C,   0xFF8DFF8D,   0x00B400B4,   0x00390039,   0xFF3CFF3C,
	0xFFEAFFEA,   0x00C800C8,   0x000F000F,   0xFF39FF39,   0xFFDAFFDA,   0x00BF00BF,   0x00570057,
	0xFF60FF60,   0xFF6AFF6A,   0x00570057,   0x00C300C3,   0x00220022,   0xFF59FF59,   0xFF62FF62,
	0x00220022,   0x00B700B7,   0x008C008C,   0xFFDBFFDB,   0xFF52FF52,   0xFF60FF60,   0xFFEBFFEB,
	0x007F007F,   0x00B800B8,   0x007D007D,   0xFFFFFFFF,   0xFF89FF89,   0xFF50FF50,   0xFF64FF64,
	0xFFB1FFB1,   0x00130013,   0x00690069,   0x009E009E,   0x00AC00AC,   0x00980098,   0x006E006E,
	0x003A003A,   0x00050005,   0xFFD7FFD7,   0xFFB1FFB1,   0xFF95FF95,   0xFF81FF81,   0xFF74FF74,
	0xFF6CFF6C,   0xFF68FF68,   0xFF67FF67,   0xFF67FF67,   0xFF6BFF6B,   0xFF71FF71,   0xFF7DFF7D,
	0xFF8EFF8E,   0xFFA8FFA8,   0xFFCCFFCC,   0xFFF8FFF8,   0x002C002C,   0x00610061,   0x008F008F,
	0x00A900A9,   0x00A500A5,   0x007B007B,   0x002C002C,   0xFFCAFFCA,   0xFF74FF74,   0xFF4EFF4E,
	0xFF72FF72,   0xFFDDFFDD,   0x00600060,   0x00B300B3,   0x00990099,   0x00150015,   0xFF7CFF7C,
	0xFF46FF46,   0xFFADFFAD,   0x00650065,   0x00C000C0,   0x00550055,   0xFF89FF89,   0xFF43FF43,
	0xFFE7FFE7,   0x00AF00AF,   0x008B008B,   0xFF9CFF9C,   0xFF42FF42,   0x00140014,   0x00C800C8,
	0x00230023,   0xFF3EFF3E,   0xFFC4FFC4,   0x00BE00BE,   0x00390039,   0xFF3DFF3D,   0xFFE7FFE7,
	0x00C700C7,   0xFFDCFFDC,   0xFF4AFF4A,   0x00750075,   0x00750075,   0xFF49FF49,   0x00070007,
	0x00AD00AD,   0xFF71FF71,   0xFFD3FFD3,   0x00B200B2,   0xFF7DFF7D,   0xFFDEFFDE,   0x00A200A2,
	0xFF66FF66,   0x00220022,   0x00670067,   0xFF5AFF5A,   0x00810081,   0xFFE4FFE4,   0xFFB2FFB2,
	0x008F008F,   0xFF6EFF6E,   0x00640064,   0xFFF5FFF5
};

#undef UINT32
