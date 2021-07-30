//#############################################################################
//! \file source/common/C/viterbi/viterbi_cnv_enc.c
//!
//! \brief  Viterbi Convolutional Encoders
//  \author Smart Grid Group
//  \date   Oct 4, 2012
//
//  Group: 			C2000
//  Target Family:	F2837x
//
// (C)Copyright 2012, Texas Instruments, Inc.
//
// History
// 130726 | V.C. Modified original code to fit C2000 coding standard
//#############################################################################
//$TI Release: C28x VCU Library Version v2.00.00.00 $
//$Release Date: Dec 6, 2013 $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "viterbi_encoder.h"
//*****************************************************************************
// defines
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************

//
// \brief Initialize the encoder structure by zeroing out the delay line
// \param hndVITEncoder Handle to the Viterbi Encoder Structure
//
void VITERBI_ENCODER_init(VITERBI_ENCODER_Handle hndVITEncoder)
{
	int16_t i;
	for(i = 0; i < MAX_CNV_ENC_DELAY_LEN; i++){
		hndVITEncoder->delay[0] = 0;
	}
}

//
// \brief This function performs convolution encoding in prime. It uses
// constraint length of K=7, and code rate 1/2.
// 
// The polynomials are:
// G0 = 1 + D2 + D3
// G1 = 1 + D  + D2 + D3
//                                                       
// It calculates:
// c(2k  )=u(k)+u(k-2)+u(k-3)
// c(2k+1)=u(k)+u(k-1)+u(k-2)+u(k-3)
//
// \param hndVITEncoder handle to the Viterbi encoder object whose elements are
//        nBits - number of input bits for decode                         
//        u_p   - pointer to input uncoded bits                                    
//        c_p   - pointer to output coded bits 
//                (It produces 2xnBit bits)                           
//
void VITERBI_ENCODER_runK4CR12(VITERBI_ENCODER_Handle hndVITEncoder)
{
  uint16_t *c_p, *u_p, *d_p, *uu_p, tmp;
  int16_t i;

  u_p = hndVITEncoder->u_p;
  c_p = hndVITEncoder->c_p;
  d_p = &hndVITEncoder->delay[0];

  c_p[0]  = (u_p[0] ^          d_p[1] ^ d_p[0]);
  c_p[1]  = (u_p[0] ^ d_p[2] ^ d_p[1] ^ d_p[0]);
  c_p[2]  = (u_p[1] ^          d_p[1] ^ d_p[0]);
  c_p[3]  = (u_p[1] ^ u_p[0] ^ d_p[1] ^ d_p[0]);
  c_p[4]  = (u_p[2] ^          u_p[0] ^ d_p[0]);
  c_p[5]  = (u_p[2] ^ u_p[1] ^ u_p[0] ^ d_p[0]);

  c_p = &c_p[6];

  uu_p = u_p;
  for(i=3; i < hndVITEncoder->nBits; i++)
    {
      tmp = uu_p[3] ^ uu_p[1] ^ uu_p[0];
      *c_p++ = tmp;
      *c_p++ = tmp ^ uu_p[2];
      uu_p++;
    }
  
  /* Update delays */
  u_p += (hndVITEncoder->nBits - K7_CNV_ENC_DELAY_LEN);
  for (i=0; i<K7_CNV_ENC_DELAY_LEN; i++)
    *d_p++ = *u_p++; 

}

//
// \brief This function performs convolution encoding in prime. It uses
// constraint length of K=7, and code rate 1/2.
// 
// The polynomials are:
// G0 = 1 + D + D2 +D3 + D6                                            
// G1 = 1 + D2 + D3 + D5 + D6  
//                                                       
// It calculates:
// c(2k  )=u(k)+u(k-1)+u(k-2)+u(k-3)+u(k-6)                  
// c(2k+1)=u(k)+u(k-2)+u(k-3)+u(k-5)+u(k-6)
//
// \param hndVITEncoder handle to the Viterbi encoder object whose elements are
//        nBits - number of input bits for decode                         
//        u_p   - pointer to input uncoded bits                                    
//        c_p   - pointer to output coded bits 
//                (It produces 2xnBit bits)                           
//
void VITERBI_ENCODER_runK7CR12(VITERBI_ENCODER_Handle hndVITEncoder)
{
  uint16_t *c_p, *u_p, *d_p, *uu_p, tmp;
  int16_t i;

  u_p = hndVITEncoder->u_p;
  c_p = hndVITEncoder->c_p;
  d_p = &hndVITEncoder->delay[0];

  c_p[0]  = (u_p[0] ^ d_p[5] ^ d_p[4] ^ d_p[3] ^          d_p[0]); 
  c_p[1]  = (u_p[0] ^          d_p[4] ^ d_p[3] ^ d_p[1] ^ d_p[0]); 
  c_p[2]  = (u_p[1] ^ u_p[0] ^ d_p[5] ^ d_p[4] ^          d_p[1]); 
  c_p[3]  = (u_p[1] ^          d_p[5] ^ d_p[4] ^ d_p[2] ^ d_p[1]); 
  c_p[4]  = (u_p[2] ^ u_p[1] ^ u_p[0] ^ d_p[5] ^          d_p[2]); 
  c_p[5]  = (u_p[2] ^          u_p[0] ^ d_p[5] ^ d_p[3] ^ d_p[2]); 
  c_p[6]  = (u_p[3] ^ u_p[2] ^ u_p[1] ^ u_p[0] ^          d_p[3]); 
  c_p[7]  = (u_p[3] ^          u_p[1] ^ u_p[0] ^ d_p[4] ^ d_p[3]); 
  c_p[8]  = (u_p[4] ^ u_p[3] ^ u_p[2] ^ u_p[1] ^          d_p[4]); 
  c_p[9]  = (u_p[4] ^          u_p[2] ^ u_p[1] ^ d_p[5] ^ d_p[4]); 
  c_p[10] = (u_p[5] ^ u_p[4] ^ u_p[3] ^ u_p[2] ^          d_p[5]); 
  c_p[11] = (u_p[5] ^          u_p[3] ^ u_p[2] ^ u_p[0] ^ d_p[5]); 

  c_p = &c_p[12];

  uu_p = u_p;
  for(i=6; i < hndVITEncoder->nBits; i++)
    {
      tmp = uu_p[6] ^ uu_p[4] ^ uu_p[3] ^ uu_p[0];
      *c_p++ = tmp ^ uu_p[5];
      *c_p++ = tmp ^ uu_p[1];
      uu_p++;
    }
  
  /* Update delays */
  u_p += (hndVITEncoder->nBits - K4_CNV_ENC_DELAY_LEN);
  for (i=0; i<K4_CNV_ENC_DELAY_LEN; i++)
    *d_p++ = *u_p++; 

}

//
// \brief Quantization of Encoder Bits
// \param hndVITEncoder handle to the Viterbi encoder object whose elements are
//        nBits - number of input bits to be quantized                         
//        c_p   - pointer to output coded bits 
// \param format power of 2, the bits will be quantized to +-(2^format)
//
void VITERBI_ENCODER_quantizeBits(VITERBI_ENCODER_Handle hndVITEncoder, int16_t format)
{
  int16_t i;
  int16_t value;

  value = 1 << format;

  /* quantize */
  for (i=0; i<(hndVITEncoder->nBits * hndVITEncoder->cr); i++)
  {
    if (hndVITEncoder->c_p[i] == 0)
      hndVITEncoder->c_p[i] = value;
    else
      hndVITEncoder->c_p[i] = -value;
  }
}

//
// \breif Word Unpacking to Bits
// \param[in]  nSize number of 16-bits words 
// \param[in]  in_p  pointer to input data in 16-bit words
// \param[out] out_p pointer to output data in bits 
//
void VITERBI_ENCODER_blockUnpack2Bits(uint16_t nSize, uint16_t *in_p, uint16_t *out_p)
{
  int16_t i;
  uint16_t data;

  for (i=0; i<(nSize << 1); i++)
    {
      data = __byte((int *)in_p, i);
      *out_p++ = (data >> 7) & 0x1;
      *out_p++ = (data >> 6) & 0x1;
      *out_p++ = (data >> 5) & 0x1;
      *out_p++ = (data >> 4) & 0x1;
      *out_p++ = (data >> 3) & 0x1;
      *out_p++ = (data >> 2) & 0x1;
      *out_p++ = (data >> 1) & 0x1;
      *out_p++ = (data ) & 0x1;
    }
}

// End of file
