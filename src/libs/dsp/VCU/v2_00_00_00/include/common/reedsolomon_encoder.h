#ifndef _REEDSOLOMON_ENCODER_H_
#define _REEDSOLOMON_ENCODER_H_
//#############################################################################
//! \file include/common/reedsolomon_encoder.h
//!
//! \brief  Reed Solomon Encoder header file
//!
//! \date   Oct 15, 2013
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
#include <stdint.h>

//!
//! \defgroup REEDSOLOMON_ENCODER Reed Solomon Encoder

//!
//! \ingroup REEDSOLOMON_ENCODER
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define RS_BLOCK_N      255     //!< Encoded block size
#define RS_BLOCK_K      239     //!< Message size
#define RS_BLOCK_T      ((RS_BLOCK_N - RS_BLOCK_K)/2) //!< number of correctable errors
#define WORD_2BYTES   	1       //!< Encoder can either operate on 2 bytes/word or 1 byte/word
//*****************************************************************************
// typedefs
//*****************************************************************************

//! \brief Reed-Solomon Encoder structure
//!
typedef struct _REEDSOLOMON_ENCODER_Obj_{
    uint16_t    n;                  //!< number of codeword symbols (bytes) in a block
    uint16_t    k;                  //!< number of message symbols (bytes) in a block
    uint16_t    t;                  //!< number of correctable errors in the block
    int16_t     *pGenPolyIdx;       //!< Pointer to the Code Generator Polynomial with coefficients in index form
    int16_t     *pRS_expTable;      //!< Pointer to the lookup table (roots of the extension Galois Field)
                                    //!  that converts index to decimal form
    int16_t     *pRS_logTable;      //!< Pointer to the lookup table (roots of the extension Galois Field)
                                    //!  that converts decimal to index form
	void (*init)(void *, 
                int16_t *,
                int16_t *,
                int16_t *);         //!< Function pointer to Reed Solomon Encoder initialization routine
	void (*run)(void *, 
                int16_t *,
                int16_t  );         //!< Function pointer to Reed Solomon Encoder computation routine
}REEDSOLOMON_ENCODER_Obj;

//! \brief Handle to the Reed-Solomon Encoder structure
//!
typedef REEDSOLOMON_ENCODER_Obj *REEDSOLOMON_ENCODER_Handle;

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief Reed Solomon Encoder Object
//!
extern REEDSOLOMON_ENCODER_Obj REEDSOLOMON_ENCODER;

//*****************************************************************************
// function prototypes
//*****************************************************************************
//! \brief Initializes the Reed Solomon Encoder object
//!
//! \param[in] hndRSEncoder handle to the Reed Solomon Encoder object
//! \param[in] pGenPolyIdx pointer to the code generator polynomial (Index Form)
//! \param[in] pRS_expTable pointer to the lookup table that converts index to decimal form
//! \param[in] pRS_logTable pointer to the lookup table that converts decimal to index form
//
void REEDSOLOMON_ENCODER_init(REEDSOLOMON_ENCODER_Handle hndRSEncoder, 
                int16_t *pGenPolyIdx,
                int16_t *pRS_expTable,
                int16_t *pRS_logTable);

//! \brief Runs the Reed Solomon Encoder
//! 
//! \param[in] hndRSEncoder handle to the Reed Solomon Encoder object
//! \param     pData pointer to the original message or data
//! \param[in] nBytes number of bytes in the input message
//
void REEDSOLOMON_ENCODER_run(REEDSOLOMON_ENCODER_Handle hndRSEncoder,
                             int16_t *pData, int16_t nBytes);

#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup


#endif //end of _REEDSOLOMON_ENCODER_H_ definition
