/******************************************************************************
* FILE PURPOSE: Interleaver/Deinterleaver
* *****************************************************************************
* DESCRIPTION: This submodule provides the de/interleaver for OFDM mode.
* *****************************************************************************
*
*  Copyright (c) 2012 Texas Instruments Inc.
*  All Rights Reserved This program is the confidential and proprietary
*  product of Texas Instruments Inc.  Any Unauthorized use, reproduction or
*  transfer of this program is strictly prohibited.
*
* HISTORY:
*
* 12/12/2012 JKunduru    Written
*
*
* LIST OF FUNCTIONS:
*******************************************************************************/
#include <phy_sunTables.h>

#pragma DATA_SECTION(PHY_ofdmIlvMCS5_6_LUT, "sunPhyTable");
#pragma DATA_SECTION(PHY_ofdmDeIlvMCS5_6_LUT, "sunPhyTable");
#pragma DATA_ALIGN(PHY_ofdmIlvMCS5_6_LUT, 2)
#pragma DATA_ALIGN(PHY_ofdmDeIlvMCS5_6_LUT, 2)

const UINT16 PHY_ofdmIlvMCS5_6_LUT[PHY_OFDM_INTLV_MCS5_6_SIZE/2] =
{
  0x0c00,   0x2418,   0x3c30,   0x5448,   0x010d,   0x1925,   0x313d,   0x4955,
  0x0e02,   0x261a,   0x3e32,   0x564a,   0x030f,   0x1b27,   0x333f,   0x4b57,
  0x1004,   0x281c,   0x4034,   0x584c,   0x0511,   0x1d29,   0x3541,   0x4d59,
  0x1206,   0x2a1e,   0x4236,   0x5a4e,   0x0713,   0x1f2b,   0x3743,   0x4f5b,
  0x1408,   0x2c20,   0x4438,   0x5c50,   0x0915,   0x212d,   0x3945,   0x515d,
  0x160a,   0x2e22,   0x463a,   0x5e52,   0x0b17,   0x232f,   0x3b47,   0x535f,
};


const UINT16 PHY_ofdmDeIlvMCS5_6_LUT[PHY_OFDM_INTLV_MCS5_6_SIZE/2] =
{
  0x0900,   0x1910,   0x2920,   0x3930,   0x4940,   0x5950,   0x0801,   0x1811,
  0x2821,   0x3831,   0x4841,   0x5851,   0x0b02,   0x1b12,   0x2b22,   0x3b32,
  0x4b42,   0x5b52,   0x0a03,   0x1a13,   0x2a23,   0x3a33,   0x4a43,   0x5a53,
  0x0d04,   0x1d14,   0x2d24,   0x3d34,   0x4d44,   0x5d54,   0x0c05,   0x1c15,
  0x2c25,   0x3c35,   0x4c45,   0x5c55,   0x0f06,   0x1f16,   0x2f26,   0x3f36,
  0x4f46,   0x5f56,   0x0e07,   0x1e17,   0x2e27,   0x3e37,   0x4e47,   0x5e57,
};

