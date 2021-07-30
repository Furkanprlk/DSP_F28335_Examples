/*FFT8.C-MAIN FFT.RECTANGULAR INPUT DATA.CALLS FFT.C*/

#include "fftcmplx.h"  /*complex structure definition*/
#include <stdio.h>

extern void FFT(COMPLEX *Y, int N); /* FFT Function */

volatile int out_addr1, out_addr2;

void main(void)
  {             /*complex input samples */

  COMPLEX y[8]= {{8191,0},{8191,0},{8191,0},{8191,0},
						{0,0},{0,0},{0,0},{0,0}};
  int i, n=8;

  FFT(y,n);          /*calls generic FFT function*/
  for (i=0; i<n; i++)
	 {
	 out_addr1 = (y[i]).real;
	 out_addr2 = (y[i]).imag;
	 printf("\nreal %d imaginary %d", out_addr1, out_addr2);
	 }
  }



















