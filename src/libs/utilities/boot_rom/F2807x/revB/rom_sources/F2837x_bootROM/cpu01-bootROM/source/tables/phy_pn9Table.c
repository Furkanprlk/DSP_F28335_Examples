/******************************************************************************
* FILE PURPOSE: This file contains the PN9 table
*******************************************************************************
*
* FILE NAME: phy_pn9Table.c
*
* DESCRIPTION:  PN9 Sequence Lookup Table
*
*  Copyright (c) 2012 Texas Instruments Inc.
*  All Rights Reserved This program is the confidential and proprietary
*  product of Texas Instruments Inc.  Any Unauthorized use, reproduction or
*  transfer of this program is strictly prohibited.
*
* HISTORY:
*
* 07/31/2012 JKunduru    Written
*
*
*
*******************************************************************************/
#include <phy_sunTables.h>

#pragma DATA_SECTION(PHY_pn9Table, "PLC_PHYPN9TABLE");
#pragma DATA_ALIGN(PHY_pn9Table, 2)

/* PN9 sequence in unsigned (1/0) format, seed 111111111 */
const SINT16 PHY_pn9Table[PHY_PN9_LUT_SIZE] =
{
#include "phy_pn9Table.txt"
};
