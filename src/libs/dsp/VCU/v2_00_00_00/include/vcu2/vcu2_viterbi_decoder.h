#ifndef _VCU2_VITERBI_DECODER_H_
#define _VCU2_VITERBI_DECODER_H_
//#############################################################################
//! \file include/vcu2/VCU2_VITERBI.h
//!
//! \brief  Viterbi Decoder header file
//!
//! \date   Nov 15, 2012
//
//  Group: 			C2000
//  Target Family:	F2837x
//
// (C)Copyright 2012, Texas Instruments, Inc.
//#############################################################################
//$TI Release: C28x VCU Library Version v2.00.00.00 $
//$Release Date: Dec 6, 2013 $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "vcu2_types.h"

//!
//! \defgroup VCU2_VITERBI_DECODER Viterbi Decoding (VCU2)

//!
//! \ingroup VCU2_VITERBI_DECODER
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define MIN_K                    4
#define MAX_K					 7
#define MAX_CNV_ENC_DELAY_LEN	 (MAX_K - 1)
#define K4_CNV_ENC_DELAY_LEN	 4
#define K7_CNV_ENC_DELAY_LEN	 7
//*****************************************************************************
// typedefs
//*****************************************************************************

//! \brief The Viterbi mode enumerator
//!
typedef enum{
	VITERBIMODE_DECODEALL = 0,	//!< Decodes all output bits, upto a max of 256, at once
	VITERBIMODE_OVERLAPINIT,    //!< Use window overlap method, This is used for the first block
                                //!< where state metrics and transition history is updated but
								//!< no traceback is performed
	VITERBIMODE_OVERLAPDECODE,  //!< Use window overlap method, update transitions/metrics for the current
								//!< block (ith block), run a traceback using the ith and (i-1)st block's
								//!< transition history but only decode the (i-1)st block
	VITERBIMODE_OVERLAPLAST     //!< Trace back and decode the last block in overlap window method
}VITERBIMODE_e;

//! \brief VITERBI Decoder Structure
//!
typedef struct _VITERBI_DECODER_Obj_{
	int16_t	      *pInBuffer;	      //!< Input buffer pointer
	uint16_t      *pOutBuffer;		  //!< Output buffer pointer
	uint16_t      *pTransitionHistory;//!< Transition History pointer
	const int32_t *pBMSELInit; 		  //!< Initialization value for the BMSEL register
	int16_t		  stateMetricInit;    //!< Initialization value for the state metrics
	int16_t		  nBits;	     	  //!< Total number of bits to be decoded
	int16_t 	  constraintLength;	  //!< Constraint Length, i.e. K
	int16_t		  nStates;			  //!< number of states = \f$ 2^{K - 1} \f$
	int16_t		  codeRate;			  //!< The symbol code rate
	VITERBIMODE_e mode;               //!< Viterbi mode enumerator
	uint16_t 	  *pTransitionStart1; //!< Points to the start of the tranistion history buffer
	uint16_t 	  *pTransitionStart2; //!< Points to the mid of the tranistion history buffer
	uint16_t 	  *pTransitionWrap1;  //!< Points to the mid of the tranistion history buffer
	uint16_t 	  *pTransitionWrap2;  //!< Points to the end of the tranistion history buffer
	uint16_t 	  *pTransitionTemp;   //!< Points to a temporary(scratch) tranistion history buffer
	void (*init)(void *);			  //!< Function pointer to VITERBI initialization routine
	void (*run)(void *);			  //!< Function pointer to VITERBI computation routine
	void (*rescale)(void *);          //!< Function pointer to VITERBI rescale routine
}VITERBI_DECODER_Obj;

//! \brief Handle to the VITERBI Decoder structure
//!
typedef VITERBI_DECODER_Obj *VITERBI_DECODER_Handle;

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief VITERBI Decoder Object
//!
extern VITERBI_DECODER_Obj VITERBI_DECODER;

//*****************************************************************************
// function prototypes
//*****************************************************************************

//! \brief Initializes the VITERBI object (constraint length 4, code rate 1/2)
//!
//! Sets the constraint length of the viterbi object and initialized
//! the state metrcs to the object element, stateMetricInit
//!
//! \param[in] hndVITDecoder handle to the VITERBI object
//
void VITERBI_DECODER_initK4CR12(VITERBI_DECODER_Handle hndVITDecoder);

//! \brief Runs the VITERBI decoder for constraint length 4, code rate 1/2
//!
//! The viterbi decode is done using a window overlap method with 4 modes
//! of operation :
//! -# VITERBIMODE_DECODEALL, a one-shot decode mode typically used for header
//!                           information where the entire block of data is processed
//!                           through the trellis and decoded
//! -# VITERBIMODE_OVERLAPINIT, window overlap method -- this is used for the first block
//!                             where state metrics and transition history is updated but
//! 							no traceback is performed
//! -# VITERBIMODE_OVERLAPDECODE, window overlap method -- update transitions/metrics for the current
//! 							  block (ith block), run a traceback using the ith and (i-1)st block's
//! 							  transition history but only decode the (i-1)st block
//! -# VITERBIMODE_OVERLAPLAST, window overlap method-- trace back and decode the last block
//! 
//! The window overlap method requires the transition history of two successive blocks to
//! be recorded. The transition history buffer is used in a circular fashion and requires
//! 5 pointers:
//! - pTransitionHistory(hist_p): start of the transition history buffer
//! - pTransitionStart1(S1_p): points to where the transition update should start
//! - pTransitionStart2(S2_p: points to the mid point of the overlap(S1_p + 4*nUnencodedBits)
//! - pTransitionWrap1(W1_p): points to where trace overlap 2 should go (wrap, S1_p + 4*nUnencodedBits)
//! - pTransitionWrap2(W2_p): points to the end of the overlap(S1_p + 2*4*nUnencodedBits)
//! \verbatim
//!  CBITS  = 128(coded bits per block)
//!  UBITS  = CBITS/2 = 64(uncoded bits per block)
//!  UWORDS = 4 (4 words required to store UBITS)
//! 
//!  Transition history(bits per stage)--->
//!               <-------64 bits----->
//!               +----+----+----+----+   ^
//! S1_p->hist_p->|    |    |    |    |   |
//!         ^     |    |    |    |    |   |
//!         |     |    |    |    |    |   |
//!         |     |    |    |    |    |   |
//!     4*UBITS   |    |    |    |    |   |
//!         |     |    |    |    |    |   |
//!         |     |    |    |    |    |   |
//!         |     |    |    |    |    |   |
//!         v     |    |    |    |    |   |
//!   S2_p->W1_p->|    |    |    |    | 128 stages
//!         ^     |    |    |    |    |   |
//!         |     |    |    |    |    |   |
//!         |     |    |    |    |    |   |
//!     4*UBITS   |    |    |    |    |   |
//!         |     |    |    |    |    |   |
//!         |     |    |    |    |    |   |
//!         |     |    |    |    |    |   |
//!         v     |    |    |    |    |   |
//!         W2_p->|    |    |    |    |   |
//!               +----+----+----+----+   v
//! \endverbatim
//! \param[in] hndVITDecoder handle to the VITERBI object
//
void VITERBI_DECODER_runK4CR12(VITERBI_DECODER_Handle hndVITDecoder);

//! \brief Rescales the viterbi state metrics (constraint length 4, code rate 1/2)
//! 
//! Rescale the state metrics by finding the lowest metric and dividing the
//! rest by it. This prevents overflow between successive decoder stages.
//!
//! \param[in] hndVITDecoder handle to the VITERBI object
//
void VITERBI_DECODER_rescaleK4CR12(VITERBI_DECODER_Handle hndVITDecoder);

//! \brief Initializes the VITERBI object (constraint length 7, code rate 1/2)
//!
//! Sets the constraint length of the viterbi object and initialized
//! the state metrcs to the object element, stateMetricInit
//!
//! \note This function uses a global variable to save off the metric registers
//!       and is, therefore, non re-entrant
//!
//! \param[in] hndVITDecoder handle to the VITERBI object
//
void VITERBI_DECODER_initK7CR12(VITERBI_DECODER_Handle hndVITDecoder);

//! \brief Runs the VITERBI decoder for constraint length 7, code rate 1/2
//! \param[in] hndVITDecoder handle to the VITERBI object
//! \sa VITERBI_DECODER_runK4CR12 for a description of the window overlap method
void VITERBI_DECODER_runK7CR12(VITERBI_DECODER_Handle hndVITDecoder);

//! \brief Rescales the viterbi state metrics (constraint length 7, code rate 1/2)
//! 
//! Rescale the state metrics by finding the lowest metric and dividing the
//! rest by it. This prevents overflow between successive decoder stages.
//!
//! \param[in] hndVITDecoder handle to the VITERBI object
//
void VITERBI_DECODER_rescaleK7CR12(VITERBI_DECODER_Handle hndVITDecoder);

#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _VCU2_VITERBI_DECODER_H_ definition
