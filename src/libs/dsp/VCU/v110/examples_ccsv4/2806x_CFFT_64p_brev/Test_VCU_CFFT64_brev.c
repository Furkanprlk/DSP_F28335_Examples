/******************************************************************************
*******************************************************************************
* 
* FILE: Test_VCU_CFFT64_brev.c
*
* DESCRIPTION: Example showing the 64 point complex fft with bit reversal 
*  			   tables
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
#define  DATA_LENGTH    (64<<1)
cfft16_t fft = cfft16_64P_BREV_DEFAULTS;

#pragma DATA_SECTION (fft_work_buffer, ".shadow");
ComplexShort fft_work_buffer[256];

//Global Data
UINT32 err=0;
SINT16 *dataIn_p, *dataOut_p;

//Function Prototypes
void cfft16(cfft16_t *fft_hnd);
void Done(void);

void main(void)
{
  SINT16 k;
  
  /* initialize FFT object */
  fft.ipcbptr = (int *)CFFT16_64p_brev_in_data + 0;
  fft.workptr = (int *)fft_work_buffer + 0;
            
  fft.init(&fft);
  
  /* complex input FFT */
    cfft16(&fft);

#if 1
  /* Check error */
  for (k=0; k<DATA_LENGTH; k++)
    {
      if (CFFT16_64p_brev_out_data[k] != CFFT16_64p_brev_in_data[k])
        err++;
    }
#endif


    Done();
}  


/*! Complex FFT routine
 *
 * \param Handle to the structure, cfft16_t
 *
 * Rearrange the input data in bit reversed format through the table
 * lookup method and call the FFT routine to get the complex FFT
 *
 * \return none
 */
void cfft16(cfft16_t *fft_hnd)
{
  /* bit reversal */
  cfft16_tbl_brev(fft_hnd);
  /* FFT core calculation */
  fft_hnd->calc(fft_hnd);
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
