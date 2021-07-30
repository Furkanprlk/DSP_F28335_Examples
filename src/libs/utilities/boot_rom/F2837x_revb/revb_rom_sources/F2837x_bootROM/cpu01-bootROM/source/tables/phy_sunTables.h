/*****************************************************************************
* FILE PURPOSE: Header file for 802.15.4G (SUN) PHY ROM Tables
*******************************************************************************
*
* FILE NAME: phy_sunTables.h
*
* DESCRIPTION:
*       Header file for SUN PHY ROM Tables
*
*  Copyright (c) 2012 Texas Instruments Inc.
*  All Rights Reserved This program is the confidential and proprietary
*  product of Texas Instruments Inc.  Any Unauthorized use, reproduction or
*  transfer of this program is strictly prohibited.
*
* HISTORY:
*
* 01/13/2013 Written
*
*
******************************************************************************/
#ifndef _PHY_SUN_TABLES_H
#define _PHY_SUN_TABLES_H

#include <typedefs.h>

/******************************************************************************
 * Definitions
 *****************************************************************************/

#define PHY_PN9_LUT_SIZE                            512
#define PHY_COSIN_LUT_SIZE                         1024

#define PHY_FSK_GSN_INTFILT50_LUT_SIZE             1000 //(2+4+8+4+2)*50
#define PHY_FSK_GSN_INTFILT8_LUT_SIZE               160 //(2+4+8+4+2)*8  --> NEW SIZE, from 320 to 160
#define PHY_FSK_TXSRC_COEF_LUT_SIZE                 192 // 32*6          --> NEW SIZE, from 128 to 192

#define PHY_OFDM_CHEST_FIR_SIZE                       9
#define PHY_OFDM_CHFIR_TR_ODD_SIZE                    5
#define PHY_OFDM_CHFIR_TR_EVEN_SIZE                   4
#define PHY_OFDM_INTLV_MCS5_6_SIZE                   96
#define PHY_OFDM_STF_TBL_SIZE                        64

#define PHY_OFDM_IFFT_SIZE                          256

#define LTF_VAL             0x7fff
#define LTF_NEG_VAL         0x8000

/******************************************************************************
 * Prototypes
 *****************************************************************************/

extern const SINT16 PHY_pn9Table[PHY_PN9_LUT_SIZE];
extern const SINT16 PHY_cosinTable[PHY_COSIN_LUT_SIZE * 2];
extern const SINT16 PHY_fskGsnIntFilt50Table[PHY_FSK_GSN_INTFILT50_LUT_SIZE];
extern const SINT16 PHY_fskGsnIntFilt8Table[PHY_FSK_GSN_INTFILT8_LUT_SIZE];
extern const SINT16 PHY_fskTxSrcCoefTable[PHY_FSK_TXSRC_COEF_LUT_SIZE];

extern const SINT16 PHY_ofdmLtfRxTable[52];
extern const SINT16 PHY_ofdmChEstFir[3][3*3*2*PHY_OFDM_CHEST_FIR_SIZE];
extern const SINT16 PHY_ofdmchEstFirTracking[3][3*2*(2*PHY_OFDM_CHFIR_TR_ODD_SIZE + PHY_OFDM_CHFIR_TR_EVEN_SIZE) + 4];
extern const UINT16 PHY_ofdmIlvMCS5_6_LUT[PHY_OFDM_INTLV_MCS5_6_SIZE/2];
extern const UINT16 PHY_ofdmDeIlvMCS5_6_LUT[PHY_OFDM_INTLV_MCS5_6_SIZE/2];
extern const SINT16 PHY_ofdmStfPreambleTbl[2*PHY_OFDM_STF_TBL_SIZE];
extern const SINT32 PHY_ofdmLtfBegFreqs[16];
extern const SINT32 PHY_ofdmLtfEndFreqs[15];

/* The following should be in new section */
extern const ComplexShort_t PHY_ofdmLtfm4freq[3][PHY_OFDM_IFFT_SIZE];
#endif
