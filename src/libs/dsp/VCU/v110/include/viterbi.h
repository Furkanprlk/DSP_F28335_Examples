/******************************************************************************
*******************************************************************************
* 
* FILE: viterbi.h
* 
* DESCRIPTION: This file contains the API for the viterbi decoder
* 
*******************************************************************************
*  $TI Release: C28x VCU Library Version v1.10 $
*  $Release Date: September 26, 2011 $
*******************************************************************************
*  This software is licensed for use with Texas Instruments C28x
*  family DSCs.  This license was provided to you prior to installing
*  the software.  You may review this license by consulting a copy of
*  the agreement in the doc directory of this library.
* ------------------------------------------------------------------------
*          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
*                          All Rights Reserved.
******************************************************************************/
#ifndef __VITERBI_H__
#define __VITERBI_H__


#ifdef __cplusplus
extern "C" {
#endif
       
#include "DSP28x_Project.h"
#include <stdint.h>
#include "typedefs.h"

//###########################################################################
//
// Macro Definitions
//
//###########################################################################
#define FRAME_LEN 					128
#define CODED_LEN 					(FRAME_LEN << 1)
#define ENCODER_LEN 				7
#define STATES  					64
#define LARGE_NEG_NUMBER 			-8192

#define CNV_DEC_NUM_STATES       (1<<(G3_PHY_CNV_K -1))

/* When no overlap method is used */
/* Viterbi decodes maximum of 256 coded bits in 1 shot */
#define CNV_DEC_MAX_UBITS      128                                                      
#define CNV_DEC_MAX_CBITS      (CNV_DEC_MAX_UBITS << 1)  // CR=1/2

/* When overlap method is used */ 
/* Viterbi decodes in blocks of 128 coded bits */
#define CNV_DEC_BLK_UBITS      64           
#define CNV_DEC_BLK_CBITS      (CNV_DEC_BLK_UBITS << 1)  // CR=1/2
#define CNV_DEC_BLK_CBITS_LOG2 7

#define CNV_DEC_BLK_UWORDS     4        // 16-bits words
#define CNV_DEC_METRIC_INIT    -16384
#define G3_PHY_CNV_K               7

#define cnvDec(nBits, in_p, out_p, flag) \
        cnvDec_asm(nBits, in_p, out_p, flag)

#define cnvDecInit(nBits) \
        cnvDecInit_asm(nBits)

#define cnvDecMetricRescale() \
        cnvDecMetricRescale_asm()

//###########################################################################
//
// Structures and variables definitions.
//
//###########################################################################
/* Viterbi decode mode */
typedef enum
{
  CNV_DEC_MODE_DEC_ALL   = 0,  //!< Decodes all output bits
  CNV_DEC_MODE_OVLP_INIT = 1,  //!< Use window overlap method, 
                               //!< only metrics and transitions update
  CNV_DEC_MODE_OVLP_DEC  = 2,  //!< Use window overlap method,  
                               //!< update transitions/metrics/trace curr
                               //!< blk+prv block, decodes prv blk
  CNV_DEC_MODE_OVLP_LAST = 3   //!< last block in overlap 

}vitMode_t;

extern int16 VIT_in_data[];			//!< Input fed into the C-model encoder
extern int16 VIT_quant_data[];		//!< Output from the C-model encoder
extern int32 VIT_gold_vt_data[];	//!< Golden data to compare VT0/VT1 against
extern Uint16 VIT_frame_len;

extern UINT16 trn_tmp[CNV_DEC_MAX_UBITS];
//###########################################################################
//
// Prototypes for the APIs.
//
//###########################################################################
extern void cnvDecInit_asm(int nTranBits);
extern void cnvDec_asm(int nBits, int *in_p, int *out_p, int flag);
extern void cnvDecMetricRescale_asm();
//###########################################################################
//
// Mark the end of the C bindings section for C++ compilers.
//
//###########################################################################
#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__VITERBI_H__
