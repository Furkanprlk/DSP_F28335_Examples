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

System Name:    Fixed Point Complex FFT - Fixed Point DSP Library

File Name:      cfft.c

Description:    Primary System file for demonstrating the Fixed Point Complex FFT module

Originator:     Yu Cai (ASP) - Texas Instruments

Target dependency:  x28x

Description:
============
				If users are not confidant how to define the header structrue, it is 
				recommended use header structure definition templates. For example,
				
				CFFT32  fft=CFFT32_32P_DEFAULTS;   

				Where CFFT32 is a structure defined as:
				
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
				        void (*izero)(void *);
				        void (*calc)(void *);
				        void (*mag)(void *);
				        void (*win)(void *);
				}CFFT32;
		
				Header structure default templates are defined in fft.h
				        
Watch Variables:

	      		ipcbsrc      Data input buffer/after calculation becomes Magnitude output
	      					 buffer	(Both of them are in Q31 format)
	      		ipcb		 Data output buffer (Q31 format)
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
#define     N   32 									// FFT size
#pragma DATA_SECTION(ipcb, "FFTipcb");				// Input/output memory allocation
#pragma DATA_SECTION(ipcbsrc, "FFTipcbsrc");     
long ipcbsrc[2*N];
long ipcb[2*N];

CFFT32  fft=CFFT32_32P_DEFAULTS;					// Header structure definition

/* Define window Co-efficient Array  and place the
.constant section in ROM memory				*/
const long win[N/2]=HAMMING32;						// Select window, not used in this example   
   
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
		for(i=0; i < (N*2); i=i+2)
		{
		ipcbsrc[i]  =(long)(2147483648*(sin(Rad) + cos(Rad*2.3567))/2);          //Q31
		ipcbsrc[i+1] = (long)(2147483648*(cos(Rad*8.345) + sin(Rad*5.789))/2);   //Q31
		Rad = Rad + RadStep;
		}

		//Clean up input/output buffer
		for(i=0; i < (N*2); i=i+2)
		{
		ipcb[i]  =0;          
		ipcb[i+1] = 0;    
		}

/*---------------------------------------------------------------------------
    Nothing running in the background at present           
----------------------------------------------------------------------------*/
		CFFT32_brev(ipcbsrc, ipcb, N);				// Real part bit-reversing
		CFFT32_brev(&ipcbsrc[1], &ipcb[1], N);		// Imaginary part bit-reversing

		fft.ipcbptr=ipcb;			/* FFT computation buffer					*/
		fft.magptr=ipcbsrc;			/* Magnitude output buffer					*/
		fft.winptr=(long *)win;     /* Window coefficient array 				*/
		fft.init(&fft);    			/* Twiddle factor pointer initialization   	*/

		fft.calc(&fft);				/* Compute the FFT							*/
		
		fft.mag(&fft);				/* Q30 format (abs(ipcbsrc)/2^16).^2 		*/

		//asm("   ESTOP0");
		for(;;);

} /* End: main() */
