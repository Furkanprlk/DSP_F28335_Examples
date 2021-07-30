/******************************************************************************
*******************************************************************************
* 
* FILE: Test_VCU_RFFT512.c
*
* DESCRIPTION: Example showing the 512 point Real fft
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
#include "fft.h"

// Global defintions
#define  DATA_LENGTH    (256<<1)
cfft16_t fft = rfft16_512P_DEFAULTS;

#pragma DATA_SECTION (fft_work_buffer, ".shadow");
ComplexShort fft_work_buffer[256];

//Global Data
UINT32 err=0;
SINT16 *dataIn_p, *dataOut_p;

//Function Prototypes
void rfft16(cfft16_t *fft_hnd);
void Done(void);

void main(void)
{
  SINT16 k;
  
  /* initialize FFT object */
  fft.ipcbptr = (int *)RFFT16_512p_in_data + 0;
  fft.workptr = (int *)fft_work_buffer + 0;
  fft.init(&fft);
  
  /* complex input FFT */
  rfft16(&fft);

#if 1
  /* Check error */
  /* LSB could be different due to rounding */
  for (k=0; k<DATA_LENGTH; k++)
    {
      if (abs(RFFT16_512p_out_data[k]-RFFT16_512p_in_data[k])>1)
        err++;
    }
#endif


    Done();
}  


/*! Real FFT routine
 *
 * \param Handle to the structure, cfft16_t
 *
 * This function reinterprets the N pt data as N/2 pt complex data
 * and flips the real and imaginary parts before calling the bit
 * reversal function. An N/2 pt complex FFT is used on the data and
 * the result is unpacked to get the real FFT
 *
 * \return none
 */
void rfft16(cfft16_t *fft_hnd)
{
  /* flip real and imaginary, VCCP real part is at high word */
  cfft16_flip_re_img(fft_hnd);
  
  /* bit reversal */
  cfft16_brev(fft_hnd);
  
  /* FFT core calculation */
  fft_hnd->calc(fft_hnd);
  
  /* unpack the complex FFT output */ 
	cfft16_unpack(fft_hnd);
   
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
