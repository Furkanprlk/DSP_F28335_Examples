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
#define PHY_FSK_GSN_INTFILT16_LUT_SIZE              320 //(2+4+8+4+2)*16
#define PHY_FSK_TXSRC_COEF_LUT_SIZE                 128 // 32*4

#define PHY_DSSS_NUM_EQZ_TAPS                        16
#define PHY_DSSS_LSF_MATRIX_SIZE                     57

#define PHY_DSSS_FFTDIFFSEQ_SIZE                     64 //complex

#define PHY_DSSS_DESPRD_8_4_LUT_NUM_ROWS              8
#define PHY_DSSS_DESPRD_8_4_LUT_NUM_COLS              8

#define PHY_DSSS_DESPRD_16_4_LUT_NUM_ROWS            16
#define PHY_DSSS_DESPRD_16_4_LUT_NUM_COLS            16

#define PHY_DSSS_DESPRD_8_4_LUT_NUM_ROWS              8
#define PHY_DSSS_DESPRD_8_4_LUT_NUM_COLS              8

#define PHY_DSSS_DESPRD_16_1_LUT_NUM_COLS            16

/******************************************************************************
 * Prototypes
 *****************************************************************************/

extern const SINT16 PHY_pn9STable[PHY_PN9_LUT_SIZE];
extern const SINT16 PHY_pn9Table[PHY_PN9_LUT_SIZE];
extern const SINT16 PHY_cosinTable[PHY_COSIN_LUT_SIZE * 2];
extern const SINT16 PHY_fskGsnIntFilt59Table[PHY_FSK_GSN_INTFILT50_LUT_SIZE];
extern const SINT16 PHY_fskGsnIntFilt16Table[PHY_FSK_GSN_INTFILT16_LUT_SIZE];
extern const SINT16 PHY_fskTxSrcCoefTable[PHY_FSK_TXSRC_COEF_LUT_SIZE];
extern const ComplexShort_t PHY_dsssFftDiffSeqTable[PHY_DSSS_FFTDIFFSEQ_SIZE];
//extern SINT16 PHY_dsssLsfMatrix[PHY_DSSS_NUM_EQZ_TAPS][2*PHY_DSSS_LSF_MATRIX_SIZE];
extern const SINT16 PHY_dsssDesprd_8_4_table[PHY_DSSS_DESPRD_8_4_LUT_NUM_ROWS][PHY_DSSS_DESPRD_8_4_LUT_NUM_COLS];
extern const SINT16 PHY_dsssDesprd_16_4_table[PHY_DSSS_DESPRD_16_4_LUT_NUM_ROWS][PHY_DSSS_DESPRD_16_4_LUT_NUM_COLS];
extern const SINT16 PHY_dsssDesprd_16_1_0_table[PHY_DSSS_DESPRD_16_1_LUT_NUM_COLS];
extern const SINT16 PHY_dsssDesprd_16_1_1_table[PHY_DSSS_DESPRD_16_1_LUT_NUM_COLS];

#endif
