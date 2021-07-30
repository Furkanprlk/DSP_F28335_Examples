#ifndef _VCU2_REEDSOLOMON_DECODER_H_
#define _VCU2_REEDSOLOMON_DECODER_H_
//#############################################################################
//! \file include/vcu2/vcu2_reedsolomon_decoder.h
//!
//! \brief  Reed Solomon Decoder header file
//!
//! \date   Oct 15, 2013
//
//  Group: 			C2000
//  Target Family:	F2837x
//
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/ 
// ALL RIGHTS RESERVED 
//#############################################################################
//$TI Release: C28x VCU Library Version v2.10.00.00 $
//$Release Date: Mar 3, 2015 $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "vcu2_types.h"

//!
//! \defgroup VCU2_REEDSOLOMON_DECODER Reed Solomon Decoder (VCU2)

//!
//! \ingroup VCU2_REEDSOLOMON_DECODER
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define RS_BLOCK_N         255     //!< Encoded block size
#define RS_BLOCK_K         239     //!< Message size
#define RS_BLOCK_T         ((RS_BLOCK_N - RS_BLOCK_K)/2) //!< number of correctable errors
#define RS_NROOTS          (RS_BLOCK_N - RS_BLOCK_K)     //!< Number of code generator polynomial roots
//*****************************************************************************
// typedefs
//*****************************************************************************
typedef struct _ERROR_LOCVAL_Obj_{
    uint16_t    pos;                 //!< Error position
    int16_t     val;                 //!< Error value
}ERROR_LOCVAL_Obj;

//! \brief Reed-Solomon Decoder structure
//!
typedef struct _REEDSOLOMON_DECODER_Obj_{
    uint16_t         _n;                  //!< number of codeword symbols (bytes) in a block
    uint16_t         _k;                  //!< number of message symbols (bytes) in a block
    uint16_t         _t;                  //!< number of correctable errors in the block
    uint16_t         nRoots;              //!< number of roots for the code generator polynomial
    int16_t          *pSyndrome;          //!< pointer to the syndromes
    int16_t          *pLambda;            //!< pointer to the Lambdas
    int16_t          *pOmega;             //!< pointer to the Omega
    int16_t          *pPackedAlpha;       //!< Pointer to the roots of the code generator polynomial
    int16_t          *pPackedBeta;        //!< Pointer to the first 2t elements of the Galois Field
    int16_t          *pRS_expTable;       //!< Pointer to the lookup table (roots of the extension Galois Field) that converts index to decimal form
    int16_t          *pRS_logTable;       //!< Pointer to the lookup table (roots of the extension Galois Field) that converts decimal to index form
    ERROR_LOCVAL_Obj *pErrorLoc;          //!< Pointer to the error (location, value) pairs
    void (*init)(void *, 
                int16_t *,
                int16_t *,
                int16_t *,
                int16_t *,
                int16_t *,
                int16_t *,
                int16_t *,
                ERROR_LOCVAL_Obj *);      //!< Function pointer to Reed Solomon Decoder initialization routine
	void (*run)(void *,
			    int16_t*,
			    int16_t );       		  //!< Function pointer to Reed Solomon Decoder computation routine
}REEDSOLOMON_DECODER_Obj;

//! \brief Handle to the Reed-Solomon Decoder structure
//!
typedef REEDSOLOMON_DECODER_Obj *REEDSOLOMON_DECODER_Handle;

//*****************************************************************************
// globals
//*****************************************************************************


//*****************************************************************************
// function prototypes
//*****************************************************************************
//! \brief Initializes the Reed Solomon Decoder object (n,k = 255, 239)
//! 
//! \param[in] hndRSDecoder handle to the Reed Solomon Decoder object
//! \param[in] pSyndrome    Pointer to the syndromes
//! \param[in] pLambda      Pointer to the error locator polynomial coefficients
//! \param[in] pOmega       Pointer to the error magnitude polynomial coefficients
//! \param[in] pPackedAlpha Pointer to the roots of the generator polynomial \f$ x + \alpha^{i}\f$
//! \param[in] pPackedBeta  Pointer to the roots of the generator polynomial \f$ x + \beta^{i}\f$
//! \param[in] pRS_expTable Pointer to the lookup table that converts index to decimal form
//! \param[in] pRS_logTable Pointer to the lookup table that converts decimal to index form
//! \param[in] pErrorLoc    Pointer to the error (location, value) pairs
//! \note Requires the data array to be even aligned
//
void REEDSOLOMON_DECODER_initN255K239(REEDSOLOMON_DECODER_Handle hndRSDecoder,
                                      int16_t *pSyndrome, int16_t *pLambda, int16_t *pOmega,
                                      int16_t *pPackedAlpha, int16_t *pPackedBeta, int16_t *pRS_expTable,
                                      int16_t *pRS_logTable, ERROR_LOCVAL_Obj *pErrorLoc);

//! \brief Runs the Reed Solomon Decoder (n,k = 255, 239)
//! 
//! \param[in] hndRSDecoder handle to the Reed Solomon Decoder object
//! \param[in] pData pointer to the received message block
//! \param[in] nBytes number of bytes in the message block
void REEDSOLOMON_DECODER_runN255K239(REEDSOLOMON_DECODER_Handle hndRSDecoder,
                                     int16_t *pData, int16_t nBytes);

//! \brief Syndrome calculation function (Horner's Method)
//!
//! \param[in] hndRSDecoder handle to the Reed Solomon Decoder object
//! \param[in] pData  pointer to the data
//! \param[in] nBytes number of bytes in the message block
//! \note Requires the syndrome array to be even aligned
//
void REEDSOLOMON_DECODER_calcSyndrome(REEDSOLOMON_DECODER_Handle hndRSDecoder,
                                      int16_t *pData, int16_t nBytes);
                                      
//! \brief Error locator polynomial calculation (inversionless Berlekamp Massey Method)
//!
//! \param[in] hndRSDecoder handle to the Reed Solomon Decoder object
//! \note Requires the lambda array to be even aligned
//
void REEDSOLOMON_DECODER_berlekampMassey(REEDSOLOMON_DECODER_Handle hndRSDecoder);

//! \brief caculate error locations using Chien search and magnitude
//!        using Forney's algorithm
//!
//! \param[in] hndRSDecoder handle to the Reed Solomon Decoder object
//! \param[in] nBytes number of bytes in the message block
//! \note Requires the omega and error location arrays to be even aligned
//
void REEDSOLOMON_DECODER_chienForney(REEDSOLOMON_DECODER_Handle hndRSDecoder,
		                             int16_t nBytes);

#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _VCU2_REEDSOLOMON_DECODER_H_ definition

// End of File
