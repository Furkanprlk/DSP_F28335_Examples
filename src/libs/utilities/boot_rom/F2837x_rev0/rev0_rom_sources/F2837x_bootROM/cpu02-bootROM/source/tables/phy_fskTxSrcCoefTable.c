/*****************************************************************************
* FILE PURPOSE: This file contains LUT for FSK TX resampler
*******************************************************************************
*
* FILE NAME: phy_fskTxSrcCoefTable.c
*
* DESCRIPTION:
*       This file contains LUT used for FSK TX resampler or sampling rate
*       converter (src). It converts 2.4MHz to 2.5MHz sapling rate
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

#include "PHY_sunTables.h"
/* 
 * column index: x[n - J + 1] x[n - J + 2] x[n - J + 3] x[n - J + 4] x[n - J + 5] x[n - J + 6] = x[n] (newest) 
 * row index: phase number 
 */ 
#pragma DATA_SECTION(PHY_fskTxSrcCoefTable, "sunPhyTable");
const SINT16 PHY_fskTxSrcCoefTable[PHY_FSK_TXSRC_COEF_LUT_SIZE] =
{
#include "phy_fskTxSrcCoefTable.txt"
};

