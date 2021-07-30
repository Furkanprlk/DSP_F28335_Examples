// TI File $Revision: /main/2 $
// Checkin $Date: Thu Jan  6 15:14:02 2011 $
// =====================================================================================
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// -------------------------------------------------------------------------------------
//          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
//                          All Rights Reserved.
//======================================================================================
/* ==============================================================================

System Name:    Windowed Real FFT - Fixed Point DSP Library

File Name:      winrfft.c

Description:    Primary System file for demonstrating the Windowed input Real FFT module

Originator:     Yu Cai (ASP) - Texas Instruments

Target dependency:  x28x

Description:
============
				If users are not confidant how to define the header structrue, it is 
				recommended use header structure definition templates. For example,
				
				RFFT32  fft=RFFT32_32P_DEFAULTS;   

				Where RFFT32 is a structure defined as:
				
				typedef struct {   
				        long *ipcbptr;
				        long *tfptr;               
				        int size;
				        int nrstage;             
				        long *magptr;
				        long *winptr; 
				        long peakmag;
				        int peakfrq;
						int ratio;
				        void (*init)(void *);
				        void (*calc)(void *);
				        void (*mag)(void *);
				        void (*win)(void *);
				 }RFFT32;
				
				Header structure default templates are defined in fft.h
				        
Watch Variables:

			    ipcbsrc      Data input buffer/after calculation becomes Magnitude output 
			      			 buffer(Both of them are in Q31 format)
			    ipcb		 Windowed data input/data output buffer (Q31 format)
			    fft          fft header structure
*/
//######################################################################################
// $TI Release: C28x Fixed Point Library v1.01 $
// $Release Date: January 11,2011 $
//######################################################################################

#include "DSP28x_Project.h"
#include <fft.h>
#include "math.h"
#include "float.h"
   
/* Create an Instance of FFT module                 */
#define     N   32 
#pragma DATA_SECTION(ipcb, "FFTipcb");				//Input/output buffer alignment
#pragma DATA_SECTION(ipcbsrc, "FFTipcbsrc");    
long ipcbsrc[2*N];
long ipcb[2*N];  

RFFT32  fft=RFFT32_32P_DEFAULTS; 					//FFT header structure initialization

/* Define window Co-efficient Array  and place the
.constant section in ROM memory				*/
const long win[N/2]=HAMMING32;   					// 32 bit Hamming window initialization
   
int xn,yn;

float	RadStep = 0.1963495408494f;
float	Rad = 0.0f;

void main()
{    
	    unsigned long i;
	     
	    InitSysCtrl();
		DINT;
		InitPieCtrl();
		IER = 0x0000;
		IFR = 0x0000;
		InitPieVectTable();
		EINT;   // Enable Global interrupt INTM
		ERTM;   // Enable Global realtime interrupt DBGM
	          
        	// Generate sample waveforms:
		Rad = 0.0f;		

		//Clean up input/output buffer
		for(i=0; i < (N*2); i=i+2)
		{
		ipcb[i]  =0;          
		ipcb[i+1] = 0;    
		}
	
		//Generate simulation signal
		for(i=0; i < N; i++)
		{
		ipcbsrc[i]  =(long)(2147483648*(sin(Rad) + cos(Rad*2.3567))/2);          //Q31
		Rad = Rad + RadStep;
		}

/*---------------------------------------------------------------------------
    	FFT Calculation           
----------------------------------------------------------------------------*/
		RFFT32_brev(ipcbsrc, ipcb, N);  //Real FFT bit reversing function

		fft.ipcbptr=ipcb;			/* FFT computation buffer		*/
		fft.magptr=ipcbsrc;
		fft.winptr=(long *)win;     /* Window coefficient array */
		fft.init(&fft);    			/* Twiddle factor pointer initialization   	*/
		
		fft.win(&fft); 				/* Window the input data */

		fft.calc(&fft);				/* Compute the FFT			*/
		
		fft.mag(&fft);         		/* Q31 format (abs(ipcbsrc)/2^16).^2 */
		
		//asm("   ESTOP0");
		for(;;);

} /* End: main() */

             


