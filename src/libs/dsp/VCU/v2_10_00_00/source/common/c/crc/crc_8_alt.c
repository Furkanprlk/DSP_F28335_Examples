//#############################################################################
//! \file source/common/C/crc/crc_8_alt.c
//!
//! \brief  8-bit CRC
//  \author Vishal Coelho
//  \date   Apr 7, 2011
//
// o CRC implementation is based on tables. If the tables
//   are calculated on the fly, the macro GEN_CRC_TABLES shall be defined
//   and genCRC8Tables() shall be called during 
//   initialization. If the macro is not defined, pre-calculated tables will
//   will be used. Using the latter option can put the tables to flash.
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
#include "VCU0_CRC.h"
//  Generate the CRC lookup table using the polynomial 0x7
// 
// \param none
//  
// This function is to generate the CRC8 table for every possible byte
// i.e. 2^8 = 256 table values, using the CRC8_PRIME polynomial 0x07. It
// expects a global array, crc8_table, to be defined in the application
// code
// 
// \return none
// 
void genCRC8Table()
{ 
  register uint16 i;
  register uint16 j;
  register uint16 crc8_accum;


  for ( i = 0; i < 256;  i++ )
  { 
    crc8_accum = i;
    for ( j = 0; j < 8;  j++ )
    { 
      if ( crc8_accum & 0x80L )
        crc8_accum = ( (crc8_accum << 1) & 0xff ) ^ POLYNOMIAL8;
      else
        crc8_accum = ( crc8_accum << 1 ) & 0xff; 
    }
    crc8_table[i] = crc8_accum;
  }
}

//  C- function to get the 8-bit CRC
// 
// \param The initial value of crc, in case the message has been
//  chopped into several parts, you can use the crc8 of the previous
//  segment as the init value for the current segment crc8 calculation
//  until the final crc is derived.
// \param Address of the message buffer
// \param Parity of the first message byte, i.e. whether its on an even
//  or odd address
// \param Length of the message in bytes
//  
// Calculate the 8-bit CRC of a message buffer by using the lookup table,
// crc8_table to get the CRC of each byte.
// 
// \return CRC result
// 
uint16 getCRC8_cpu (uint16 input_crc8_accum, uint16 * msg, CRC_parity_e parity,
    uint16 rxLen)
{
  register uint16 i;
  register uint16 j;
  uint16 crc8_accum;
  SINT16 *pdata;

  crc8_accum = input_crc8_accum;
  pdata = (SINT16 *)msg;

  for (j = 0; j < rxLen; j++, parity++)
  {
    i = crc8_accum ^ (__byte(pdata, parity));
    crc8_accum = crc8_table[i];
  }

  return (uint16)crc8_accum; 
}

// End of file
