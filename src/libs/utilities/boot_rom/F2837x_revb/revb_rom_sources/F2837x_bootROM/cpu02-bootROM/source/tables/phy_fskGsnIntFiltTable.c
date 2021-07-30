/*****************************************************************************
* FILE PURPOSE: This file contains LUT for FSK Gaussian interpolator filter
*******************************************************************************
*
* FILE NAME: phy_fskGsnIntFiltTable.c
*
* DESCRIPTION:
*       This file contains LUT used for the Gaussian interpolator filter.
*       The upsampling ratio is 16 for 150kbps and 50 for 50kbps modes
*
*  Copyright (c) 2012 Texas Instruments Inc.
*  All Rights Reserved This program is the confidential and proprietary
*  product of Texas Instruments Inc.  Any Unauthorized use, reproduction or
*  transfer of this program is strictly prohibited.
*
* HISTORY:
* 01/13/2013 Written
*
* LIST OF FUNCTIONS:
*
******************************************************************************/

#include <phy_sunTables.h>

#pragma DATA_SECTION(PHY_fskGsnIntFilt50Table,    "PLC_FSKGSNINT50TABLE");
#pragma DATA_SECTION(PHY_fskGsnIntFilt8Table,    "PLC_FSKGSNINT8TABLE");
#pragma DATA_ALIGN(PHY_fskGsnIntFilt50Table, 2)
#pragma DATA_ALIGN(PHY_fskGsnIntFilt8Table, 2)

/* LUT for 50x upsampling ratio */
const SINT16 PHY_fskGsnIntFilt50Table[PHY_FSK_GSN_INTFILT50_LUT_SIZE] =
{
  #include "phy_fskGsnIntFilt50Table.txt"
};

/* LUT for 16x upsampling ratio */
const SINT16 PHY_fskGsnIntFilt8Table[PHY_FSK_GSN_INTFILT8_LUT_SIZE] =
{
  #include "phy_fskGsnIntFilt8Table.txt"
};
