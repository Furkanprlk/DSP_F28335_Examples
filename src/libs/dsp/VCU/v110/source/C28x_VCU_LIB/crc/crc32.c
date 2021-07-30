/******************************************************************************
*******************************************************************************
* 
* FILE: crc32.c
*
* DESCRIPTION: This file contains the functions to do the CRC32
*
* Notes: 
*
*  o CRC implementation is based on tables. If the tables
*    are calculated on the fly, the macro GEN_CRC_TABLES shall be defined
*    and genCRC32Tables() shall be called during 
*    initialization. If the macro is not defined, pre-calculated tables will
*    will be used. Using the latter option can put the tables to flash.
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
#include "crc.h"

/*! Generate the CRC lookup table using the polynomial 0x04c11db7
 *
 * \param none
 *  
 * This function is to generate the CRC32 table for every possible byte
 * i.e. 2^8 = 256 table values, using the CRC32_PRIME polynomial 0x04c11db7. 
 * It expects a global array, crc32_table, to be defined in the application
 * code
 * 
 * \return none
 */
 void genCRC32Table()
 /* generate the table of CRC remainders for all possible bytes */
{ 
  register uint16 i, j;  
  register uint32 crc32_accum;
  for ( i = 0;  i < 256;  i++ )
  { 
    // myindex = i;
    crc32_accum = ( (uint32) i << 24 );
    for ( j = 0;  j < 8;  j++ )
    { 
      if ( crc32_accum & 0x80000000L )
        crc32_accum = ( crc32_accum << 1 ) ^ POLYNOMIAL32;
      else
        crc32_accum = ( crc32_accum << 1 ); 
    }
    crc32_table[i] = crc32_accum; 
  }
}

/*! C- function to get the 32-bit CRC
 *
 * \param The initial value of crc, in case the message has been
 *  chopped into several parts, you can use the crc32 of the previous
 *  segment as the init value for the current segment crc32 calculation
 *  until the final crc is derived.
 * \param Address of the message buffer
 * \param Parity of the first message byte, i.e. whether its on an even
 *  or odd address
 * \param Length of the message in bytes
 *  
 * Calculate the 32-bit CRC of a message buffer by using the lookup table,
 * crc32_table based on the polynomial 0x04c11db7
 * 
 * \return CRC result
 */
uint32 getCRC32_cpu (uint32 input_crc32_accum, uint16 * msg, parity_t parity, 
    uint16 rxLen)
{
  register uint16 i;
  register uint16 j;
  uint32 crc32_accum;
  
  SINT16 *pdata;

  crc32_accum = input_crc32_accum;
  pdata = (SINT16 *) msg;

  for (j = 0; j < rxLen; j++, parity++)
  {
    i = ( crc32_accum >> 24 ) ^ (__byte(pdata, parity));
    crc32_accum = ( crc32_accum << 8 ) ^ crc32_table[i];
  }
  return crc32_accum; 
}


