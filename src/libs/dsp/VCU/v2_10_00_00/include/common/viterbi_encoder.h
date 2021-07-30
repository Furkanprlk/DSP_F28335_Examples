#ifndef _VITERBI_ENCODER_H_
#define _VITERBI_ENCODER_H_
//#############################################################################
//! \file include/common/viterbi_encoder.h
//!
//! \brief  Viterbi Encoder header file
//!
//! \date   Aug 13, 2013
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
#include <stdint.h>

//!
//! \defgroup VITERBI_ENCODER Viterbi Encoder

//!
//! \ingroup VITERBI_ENCODER
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
//! \brief VITERBI Encoder Structure
//! The encoder is implemented in C. It is used to generate the input
//! sequence for the example
//!
typedef struct _VITERBI_ENCODER_Obj_{
  uint16_t delay[MAX_CNV_ENC_DELAY_LEN];  //!< delay line
  uint16_t *u_p;                          //!< pointer to uncoded bits buffer
  uint16_t *c_p;                          //!< pointer to coded bits buffer
  uint16_t cr;                            //!  code rate
  uint16_t nBits;                         //!< Number of uncoded bits
  void (*init)(void *);			          //!< Function pointer to Encoder initialization routine
  void (*run)(void *);			          //!< Function pointer to Encoder computation routine
  void (*quantize)(void  *, int16_t );    //!< Function pointer to Encoder quantization routine
}VITERBI_ENCODER_Obj;

//! \brief Handle to the VITERBI Encoder structure
//!
typedef VITERBI_ENCODER_Obj *VITERBI_ENCODER_Handle;

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// function prototypes
//*****************************************************************************

//! \brief Initialize the encoder structure by zeroing out the delay line
//! \param hndVITEncoder Handle to the Viterbi Encoder Structure
void VITERBI_ENCODER_init(VITERBI_ENCODER_Handle hndVITEncoder);

//!
//! \brief This function performs convolution encoding in prime. It uses
//! constraint length of K=7, and code rate 1/2.
//! 
//! The polynomials are:
//! G0 = 1 + D2 + D3
//! G1 = 1 + D  + D2 + D3
//!                                                       
//! It calculates:
//! c(2k  )=u(k)+u(k-2)+u(k-3)
//! c(2k+1)=u(k)+u(k-1)+u(k-2)+u(k-3)
//!
//! \param hndVITEncoder handle to the Viterbi encoder object whose elements are
//!        nBits - number of input bits for decode                         
//!        u_p   - pointer to input uncoded bits                                    
//!        c_p   - pointer to output coded bits 
//!                (It produces 2xnBit bits)                           
//!
void VITERBI_ENCODER_runK4CR12(VITERBI_ENCODER_Handle hndVITEncoder);

//!
//! \brief This function performs convolution encoding in prime. It uses
//! constraint length of K=7, and code rate 1/2.
//! 
//! The polynomials are:
//! G0 = 1 + D + D2 +D3 + D6                                            
//! G1 = 1 + D2 + D3 + D5 + D6  
//!                                                       
//! It calculates:
//! c(2k  )=u(k)+u(k-1)+u(k-2)+u(k-3)+u(k-6)                  
//! c(2k+1)=u(k)+u(k-2)+u(k-3)+u(k-5)+u(k-6)
//!
//! \param hndVITEncoder handle to the Viterbi encoder object whose elements are
//!        nBits - number of input bits for decode                         
//!        u_p   - pointer to input uncoded bits                                    
//!        c_p   - pointer to output coded bits 
//!                (It produces 2xnBit bits)                           
//!
void VITERBI_ENCODER_runK7CR12(VITERBI_ENCODER_Handle hndVITEncoder);

//! \brief Quantization of Encoder Bits
//! \param hndVITEncoder handle to the Viterbi encoder object whose elements are
//!        nBits - number of input bits to be quantized
//!        c_p   - pointer to output coded bits
//! \param format power of 2, the bits will be quantized to +-(2^format)
void VITERBI_ENCODER_quantizeBits(VITERBI_ENCODER_Handle hndVITEncoder, int16_t format);

//! \brief Word Unpacking to Bits
//! \param[in]  nSize number of 16-bits words 
//! \param[in]  in_p  pointer to input data in 16-bit words
//! \param[out] out_p pointer to output data in bits     
void VITERBI_ENCODER_blockUnpack2Bits(uint16_t nSize, uint16_t *in_p, uint16_t *out_p);
#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _VITERBI_ENCODER_H_ definition

// End of File
