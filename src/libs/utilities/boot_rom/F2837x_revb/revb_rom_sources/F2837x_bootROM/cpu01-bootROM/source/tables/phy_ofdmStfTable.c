/*
 * ******************************************************************************
 * FILE PURPOSE: Preamble/PHR Header Generation
 * *****************************************************************************
 * DESCRIPTION: This submodule generates the preamble 
 *                and PHR (PHY header) for OFDM.
 *
 *
 *  Copyright (c) 2012 Texas Instruments Inc.
 *  All Rights Reserved This program is the confidential and proprietary
 *  product of Texas Instruments Inc.  Any Unauthorized use, reproduction or
 *  transfer of this program is strictly prohibited.
 *
 * HISTORY:
 *
 * 12/15/2012 JKunduru    Written
 *
 *
*******************************************************************************/
#include <phy_sunTables.h>

#pragma DATA_SECTION(PHY_ofdmStfPreambleTbl, "PLC_OFDMSTF");
#pragma DATA_ALIGN(PHY_ofdmStfPreambleTbl, 2);

const SINT16 PHY_ofdmStfPreambleTbl[2*PHY_OFDM_STF_TBL_SIZE] =
{
  666,        0,      653,     -259,      615,     -500,      554,     -708,
  471,     -870,      370,     -977,      255,    -1023,      130,    -1010,
    0,     -942,     -130,     -829,     -255,     -684,     -370,     -522,
 -471,     -361,     -554,     -215,     -615,      -99,     -653,      -25,
 -666,        0,     -653,      -25,     -615,      -99,     -554,     -215,
 -471,     -361,     -370,     -522,     -255,     -684,     -130,     -829,
    0,     -942,      130,    -1010,      255,    -1023,      370,     -977,
  471,     -870,      554,     -708,      615,     -500,      653,     -259,
  666,        0,      653,      259,      615,      500,      554,      708,
  471,      870,      370,      977,      255,     1023,      130,     1010,
    0,      942,     -130,      829,     -255,      684,     -370,      522,
 -471,      361,     -554,      215,     -615,       99,     -653,       25,
 -666,        0,     -653,       25,     -615,       99,     -554,      215,
 -471,      361,     -370,      522,     -255,      684,     -130,      829,
    0,      942,      130,     1010,      255,     1023,      370,      977,
  471,      870,      554,      708,      615,      500,      653,      259,
};


