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

#pragma DATA_SECTION(PHY_ofdmLtfBegFreqs,   "PLC_ODFMLTFBEG");

const SINT32 PHY_ofdmLtfBegFreqs[16] =
  {
   LTF_NEG_VAL, LTF_NEG_VAL, LTF_VAL, LTF_NEG_VAL,  LTF_VAL, LTF_VAL,
   LTF_NEG_VAL, LTF_NEG_VAL, LTF_VAL, LTF_VAL, LTF_NEG_VAL, LTF_NEG_VAL, LTF_VAL
  };

