//#############################################################################
//! /file source/reference/C/reed_solomon/reed_solomon_enc.c
//!
//! \brief  Reed-Solomon Encoder
//  \author Smart Grid Group
//  \date   Oct 4, 2012
//
//  Group: 			C2000
//  Target Family:	F2837x
//
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/ 
// ALL RIGHTS RESERVED 
//
// History
// 131018 | V.C. Modified original code to fit C2000 coding standard
//#############################################################################
//$TI Release: C28x VCU Library Version v2.10.00.00 $
//$Release Date: Mar 3, 2015 $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "reedsolomon_encoder.h"
//*****************************************************************************
// defines
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// Local function prototypes
//*****************************************************************************
static inline int16_t GF_add(int16_t op1, int16_t op2);
static inline int16_t GF_mult(int16_t op1, int16_t op2,
                              int16_t *pRS_expTable, int16_t *pRS_logTable,
                              uint16_t n );

//*****************************************************************************
// function definitions
//*****************************************************************************

// \brief Initializes the Reed Solomon Encoder object
// 
// \param[in] hndRSEncoder handle to the Reed Solomon Encoder object
// \param[in] pGenPolyIdx pointer to the code generator polynomial (Index Form)
// \param[in] pRS_expTable pointer to the lookup table that converts index to decimal form
// \param[in] pRS_logTable pointer to the lookup table that converts decimal to index form
// \param[in] pRoots Pointer to the roots, \f$a^{b_{0}+i},/ i = [1, n-k-1]\f$
//
void REEDSOLOMON_ENCODER_init(REEDSOLOMON_ENCODER_Handle hndRSEncoder, 
                int16_t *pGenPolyIdx,
                int16_t *pRS_expTable,
                int16_t *pRS_logTable)
{
    hndRSEncoder -> n = RS_BLOCK_N;
    hndRSEncoder -> k = RS_BLOCK_K;
    hndRSEncoder -> t = RS_BLOCK_T;
    hndRSEncoder -> pGenPolyIdx  = pGenPolyIdx;
    hndRSEncoder -> pRS_expTable = pRS_expTable;
    hndRSEncoder -> pRS_logTable = pRS_logTable;
}

// \brief Runs the Reed Solomon Encoder
//
// A pipelined version of polynomial division
//
// \param[in] hndRSEncoder handle to the Reed Solomon Encoder object
// \param     pData pointer to the original message or data
// \param[in] nBytes number of bytes in the input message
//
void REEDSOLOMON_ENCODER_run(REEDSOLOMON_ENCODER_Handle hndRSEncoder,
                             int16_t *pData, int16_t nBytes)
{
    int16_t i, j, temp, T, dataByte, multiplier;
    int16_t *pGenPolyEnd, *pGenPolyIter;
    int16_t R[2*RS_BLOCK_T]; // Remainder from polynomial division
    int16_t *pR;
    
    T = 2*(hndRSEncoder->t);
    pGenPolyEnd = &(hndRSEncoder->pGenPolyIdx[T-1]);
    
    // Reset all the remainder symbols
    for(i = 0; i < T; i++){
      R[i] = 0;
    }
    
    // Iterate through all bytes of the message
    for( i = 0; i < nBytes; i++){
#if WORD_2BYTES
      dataByte = __byte((int *)pData, i);
#else
      dataByte = pData[i];
#endif //WORD_2BYTES
      multiplier = GF_add(dataByte, R[T-1]);
      if(multiplier == 0){
        for(j = T-1; j > 0; j--){
          R[j] = R[j-1];
        }
        R[0] = 0;
      }else{
        //Convert multiplier to index form
        multiplier = hndRSEncoder->pRS_logTable[multiplier];
        pGenPolyIter = pGenPolyEnd;
        for( j = T-1; j > 0; j--){
          // Multiply the generator polynomial by the multiplier
          // in index form
          // \f[ \alpha^{a} \alpha^{b} = \alpha^{a+b % n} \f]
          temp = GF_mult(multiplier, *pGenPolyIter--,
                         hndRSEncoder->pRS_expTable,
                         hndRSEncoder->pRS_logTable,
                         hndRSEncoder->n);
          R[j] = GF_add(R[j-1], temp);
        }
        temp = GF_mult(multiplier, *pGenPolyIter--,
                       hndRSEncoder->pRS_expTable,
                       hndRSEncoder->pRS_logTable,
                       hndRSEncoder->n);
        R[0] = temp;
      }
    }
  //Attach n-k remainder symobols to the message
  pR = &R[T-1];
  for( i = 0; i < T; i++){
#if WORD_2BYTES
    __byte((int *)pData, nBytes + i) = *pR--;
#else
    pData[i + nBytes] = *pR--;
#endif
  }
}

// \brief Galois Field Addition
//
// Addition or subtraction in GF(2) binary and GF(2^m) extenstion fields
// are equivalent and can be carried out through a simple XOR operation
// \param[in] op1 First operand in decimal form
// \param[in] op2 Second operand in decimal form
// \return Sum (or difference) of the two operands using GF arithmetic in
//         decimal form
//
static inline int16_t GF_add(int16_t op1, int16_t op2)
{
    return ( op1 ^ op2);
}

// \brief Galois Field Multiplication
//
// \f[ \alpha^{a}.\alpha^{b} = \alpha^{(a+b)% 2^{m}-1}\f]
// We will use the index form of the operands to do the multiplication.
// 
// \param[in] op1 First operand in index form
// \param[in] op2 Second operand in index form (usually the polynomial coefficients)
// \param[in] pRS_expTable pointer to the lookup table that translates index to
//            decimal form
// \param[in] pRS_logTable pointer to the lookup table that translates decimal to
//            index form
// \param[in] Block size \f$ n = 2^{m}-1 \f$
// \return product of the two operands using GF arithmetic in decimal form
//
static inline int16_t GF_mult(int16_t op1, int16_t op2,
                              int16_t *pRS_expTable, int16_t *pRS_logTable,
                              uint16_t n )
{
    uint32_t tmp, tmp1;
    
    tmp  =  op1 + op2;
    // The __rpt_subcu intrinsic translates to RPT || SUBCU ACC, loc16 instruction
    // The SUBCU will shift the ACC left by 1 and then subtract loc16 << 16 from it
    // This is equivalent to an unsigned mod operation, it leaves the remainder in 
    // AH and the quotient in AL
    tmp1 = __rpt_subcu((tmp) << 14, n, 1);
    return(pRS_expTable[tmp1 >> 16]);
}
// End of file
