/******************************************************************************
* FILE PURPOSE: This file contains the cos/sin table
*******************************************************************************
*
* FILE NAME: phy_cosinTable.c
*
* DESCRIPTION:  COS and SIN Lookup Table, Length 1024
*
*  Copyright (c) 2012 Texas Instruments Inc.
*  All Rights Reserved This program is the confidential and proprietary
*  product of Texas Instruments Inc.  Any Unauthorized use, reproduction or
*  transfer of this program is strictly prohibited.
*
* HISTORY:
*
* 01/13/2013    Written
*
*
*
*******************************************************************************/

#include <phy_sunTables.h>

//#pragma DATA_SECTION(PHY_cosinTable,    "sunPhyTable");
#pragma DATA_SECTION(PHY_cosinTable,"sunPhyTable");

/* Length 1024 COS/SIN table, arranged in COS(1), SIN(1), COS(2), SIN(2), ...
 * in Q14 format */
const SINT16 PHY_cosinTable[PHY_COSIN_LUT_SIZE * 2] =
{
  #include "PHY_cosinTable_1024.txt"
};

