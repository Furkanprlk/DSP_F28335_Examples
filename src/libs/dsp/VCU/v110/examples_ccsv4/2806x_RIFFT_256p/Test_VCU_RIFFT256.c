/******************************************************************************
*******************************************************************************
* 
* FILE: Test_VCU_RIFFT256.c
*
* DESCRIPTION: Example showing the 256 point Inverse fft
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
cfft16_t fft = rifft16_256P_DEFAULTS;

#pragma DATA_SECTION (fft_work_buffer, ".shadow");
ComplexShort fft_work_buffer[256];

//Global Data
UINT32 err=0;
SINT16 *dataIn_p, *dataOut_p;

//Function Prototypes
void rifft16(cfft16_t *fft_hnd);
void Done(void);

void main(void)
{
  SINT16 k;
  
  /* initialize FFT object */
  fft.ipcbptr = (int *)RIFFT16_256p_in_data + 0;
  fft.workptr = (int *)fft_work_buffer + 0;
  fft.init(&fft);
  
  /* complex input IFFT */
  rifft16(&fft);

#if 1
  /* Check error */
  for (k=0; k<DATA_LENGTH; k++)
    {
      if (abs(RIFFT16_256p_out_data[k]-RIFFT16_256p_in_data[k])>2)
        err++;
    }
#endif


    Done();
}  

/*! Real IFFT routine
 *
 * \param Handle to the structure, cfft16_t
 *
 * Calculates the Real Inverse FFT
 *
 * \return none
 */
void rifft16(cfft16_t *fft_hnd)
{
  /* pack complex IFFT input */
  cifft16_pack_asm(fft_hnd);

  /* complex FFT */
  cfft16_brev(fft_hnd);
  fft_hnd->calc(fft_hnd);

  /* flip the real and imaginary and conjugate */
  cfft16_flip_re_img_conj(fft_hnd);
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
