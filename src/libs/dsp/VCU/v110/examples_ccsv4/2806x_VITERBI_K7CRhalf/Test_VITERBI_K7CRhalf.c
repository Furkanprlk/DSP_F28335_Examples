/******************************************************************************
*******************************************************************************
* 
* FILE: Test_VITERBI_K7CRhalf.c
*
* DESCRIPTION: Example showing the viterbi decoder
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
#include "viterbi.h"


// Global defintions
#define DATA_PACK_LEN        128
#define DATA_BITS_LEN        (DATA_PACK_LEN << 4)     

//Global Data
#pragma DATA_SECTION(data_out,"buffer_out")
UINT16 data_out[255];

/* Data packed for test case 1 */
UINT16 data_pack[DATA_PACK_LEN] = 
{
  0x0100, 0x0302, 0x0504, 0x0706,
  0x0908, 0x0B0A, 0x0D0C, 0x0F0E,
  0x1110, 0x1312, 0x1514, 0x1716,
  0x1918, 0x1B1A, 0x1D1C, 0x1F1E,
  0x2120, 0x2322, 0x2524, 0x2726,
  0x2928, 0x2B2A, 0x2D2C, 0x2F2E,
  0x3130, 0x3332, 0x3534, 0x3736,
  0x3938, 0x3B3A, 0x3D3C, 0x3F3E,
  0x4140, 0x4342, 0x4544, 0x4746,
  0x4948, 0x4B4A, 0x4D4C, 0x4F4E,
  0x5150, 0x5352, 0x5554, 0x5756,
  0x5958, 0x5B5A, 0x5D5C, 0x5F5E,
  0x6160, 0x6362, 0x6564, 0x6766,
  0x6968, 0x6B6A, 0x6D6C, 0x6F6E,
  0x7170, 0x7372, 0x7574, 0x7776,
  0x7978, 0x7B7A, 0x7D7C, 0x7F7E,

  0x0100, 0x0302, 0x0504, 0x0706,
  0x0908, 0x0B0A, 0x0D0C, 0x0F0E,
  0x1110, 0x1312, 0x1514, 0x1716,
  0x1918, 0x1B1A, 0x1D1C, 0x1F1E,
  0x2120, 0x2322, 0x2524, 0x2726,
  0x2928, 0x2B2A, 0x2D2C, 0x2F2E,
  0x3130, 0x3332, 0x3534, 0x3736,
  0x3938, 0x3B3A, 0x3D3C, 0x3F3E,
  0x4140, 0x4342, 0x4544, 0x4746,
  0x4948, 0x4B4A, 0x4D4C, 0x4F4E,
  0x5150, 0x5352, 0x5554, 0x5756,
  0x5958, 0x5B5A, 0x5D5C, 0x5F5E,
  0x6160, 0x6362, 0x6564, 0x6766,
  0x6968, 0x6B6A, 0x6D6C, 0x6F6E,
  0x7170, 0x7372, 0x7574, 0x7776,
  0x7978, 0x7B7A, 0x7D7C, 0x407E,

};

UINT32 err=0;

SINT16 *dataIn_p, *dataOut_p;
int vblk = 0;
int nBits = 0;

//Function Prototypes
void Error(void);
void Done(void);


void main(void)
{
  SINT16 k;
  
 /* init viterbi */
  cnvDecInit((int)CNV_DEC_BLK_CBITS);

  dataIn_p = VIT_quant_data;
  dataOut_p = data_out;

  /* first blk */
  nBits = DATA_BITS_LEN << 1;
                 
  cnvDec(CNV_DEC_BLK_CBITS,
             dataIn_p,
             dataOut_p,
             CNV_DEC_MODE_OVLP_INIT);
  vblk = 1;

  dataIn_p += CNV_DEC_BLK_CBITS;
  nBits -= CNV_DEC_BLK_CBITS;

  while (nBits >= CNV_DEC_BLK_CBITS)
    {
      cnvDec(CNV_DEC_BLK_CBITS,
                 dataIn_p,
                 dataOut_p,
                 CNV_DEC_MODE_OVLP_DEC);
      
      dataIn_p    += CNV_DEC_BLK_CBITS;
      dataOut_p   += (CNV_DEC_BLK_UBITS >> 4);
      nBits       -= CNV_DEC_BLK_CBITS;
      vblk++;


      /* rescale every 4 blks  */
      if ((vblk & 0x3) == 0)
        cnvDecMetricRescale();

    }

    cnvDec(nBits,
                 dataIn_p,
                 dataOut_p+((CNV_DEC_BLK_UBITS+nBits) >> 4),
                 CNV_DEC_MODE_OVLP_LAST);



#if 1
  /* Check error */
  for (k=0; k<(DATA_BITS_LEN>>4); k++)
    {
      if (data_pack[k] != data_out[k])
        err++;
    }
#endif

  Done();
} 

/*! Error Handler
 *
 * \param none
 *
 * call the ESTOP0 routine
 *
 * \return none
 */
void Error(void)
{
    asm("   ESTOP0");
}

/*! End of Main routine
 *
 * \param none
 *
 * call the ESTOP0 routine
 *
 * \return none
 */
void Done(void)
{
    asm("   ESTOP0");
}
