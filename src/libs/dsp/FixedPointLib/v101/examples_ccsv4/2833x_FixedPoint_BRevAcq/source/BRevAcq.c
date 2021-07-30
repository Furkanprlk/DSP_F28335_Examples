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

System Name:    Fixed Point Real FFT - Fixed Point DSP Library

File Name:      DSP2833x Device rfft.c

Description:    Primary System file for demonstrating the Fixed Point Real FFT module

Originator:     Yu Cai (ASP) - Texas Instruments

Target dependency:  x28x

Description:
============
				If users are not confidant how to define the header structrue, it is 
				recommended use header structure definition templates. For example,
				
				RFFT32_brev_RT_ACQ acq=RFFT32_brev_RT_ACQ_DEFAULTS;  

				Where RFFT32_brev_RT_ACQ is a structure defined as:
				
				typedef struct {
				        int acqflag;
				        int count;
				        long input; 
				        long *tempptr;
				        long *buffptr;
				        int size;
				        void (*update)(void *); 
				       }RFFT32_brev_RT_ACQ; 
				
				Header structure default templates are defined in fft.h
				        
Watch Variables:

			    ipcbsrc      Input/Source buffer(Q0~Q31 format)
			    ipcb		 Output buffer(same format as ipcbsrc)
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
#pragma DATA_SECTION(ipcb, "FFTipcb");			//Input/output buffer alignment
#pragma DATA_SECTION(ipcbsrc, "FFTipcbsrc");
    
long ipcbsrc[2*N];
long ipcb[2*N]; 

/* Create an instance of FFTRACQ module             */  
RFFT32_brev_RT_ACQ acq=RFFT32_brev_RT_ACQ_DEFAULTS;
    
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
		for(i=0; i < N; i++)
		{
		ipcbsrc[i]  =(long)(2147483648*(sin(Rad) + cos(Rad*2.3567))/2);          //Q31
		//ipcbsrc[i+1] = (long)(2147483648*(cos(Rad*8.345) + sin(Rad*5.789))/2);    //Q31
		Rad = Rad + RadStep;
		}

		for(i=0; i < (N*2); i=i+2)
		{
		ipcb[i]  =0;          	//Q31
		ipcb[i+1] = 0;    		//Q31
		}

		//Header structure initialization
		acq.buffptr=ipcb;				//Output buffer
		acq.tempptr=ipcb;				//Temporary buffer, normally pointing to the same as buffptr
		acq.size=N;						//Buffer size
		acq.count=N;					//Every time one element bit-reversed, count minus 1
		acq.acqflag=1;					//Acquisition flag, initialized as 1
		
		for(i=0; i < N; i++)
		{
			acq.input=ipcbsrc[i];		// Input data
			acq.update(&acq);			// Point by point bit-reversing
		}		
		
		//asm("   ESTOP0");
		for(;;);

} /* End: main() */

             


