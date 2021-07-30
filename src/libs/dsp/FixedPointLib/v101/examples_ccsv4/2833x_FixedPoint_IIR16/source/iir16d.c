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

System Name:    16 bit Fixed Point IIR Filter - Fixed Point DSP Library

File Name:      iir16d.c

Description:    Primary System file for demonstrating the 16 bit IIR Filter

Originator:     Yu Cai (ASP) - Texas Instruments

Target dependency:  C28x

Description:
============

				typedef struct { 
			    	void (*init)(void *);  
			    	void (*calc)(void *);  
			    	int *coeff_ptr;         
			    	int *dbuffer_ptr;       
			    	int nbiq;               
			    	int input;            
			    	int isf;                
			    	int qfmat;              
			    	int output;             
			    }IIR5BIQ16;  
 
*/
//######################################################################################
// $TI Release: C28x Fixed Point Library v1.01 $
// $Release Date: January 11,2011 $
//######################################################################################

#include "DSP28x_Project.h"
#include <filter.h>
#include "math.h"
#include "float.h"

/* Filter Symbolic Constants                        */                                       
#define SIGNAL_LENGTH 100
     
/* Create an Instance of IIR5BIQD16 module and place the object in "iirfilt" section    */ 
#pragma DATA_SECTION(iir, "iirfilt");
IIR5BIQ16  iir=IIR5BIQ16_DEFAULTS;
                                                                  
/* =============================================================================
Modify the delay buffer size to comensurate with the no of biquads in the filter
Size of the Delay buffer=2*nbiq
==============================================================================*/ 
/* Define the Delay buffer for the cascaded 6 biquad IIR filter and place it in "iirfilt" section */
#pragma DATA_SECTION(dbuffer,"iirldb");
int dbuffer[2*IIR16_LPF_NBIQ];

#pragma DATA_SECTION(sigIn, "sigIn");
#pragma DATA_SECTION(sigOut, "sigOut");     
int sigIn[SIGNAL_LENGTH];
int sigOut[SIGNAL_LENGTH];  

/* =============================================================================
Modify the array size and symbolic constant to suit your filter requiremnt.
Size of the coefficient array=5*nbiq
==============================================================================*/
/* Define the Delay buffer for the cascaded 6 biquad IIR filter and place it in "iirfilt" section */
       
const int coeff[5*IIR16_LPF_NBIQ]=IIR16_LPF_COEFF;

float	RadStep = 0.1963495408494f;
float	Rad = 0.0f;         
         
/* Finter Input and Output Variables                */   
int xn,yn;
     
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
	   
		for(i=0; i < SIGNAL_LENGTH; i++)
		{
			sigIn[i]  =0;          //
			sigOut[i] =0;
		}
		
		/* IIR Filter Initialisation                                */ 
		iir.dbuffer_ptr=dbuffer;
		iir.coeff_ptr=(int *)coeff; 
		iir.qfmat=IIR16_LPF_QFMAT;
		iir.nbiq=IIR16_LPF_NBIQ; 
		iir.isf=IIR16_LPF_ISF; 
	    iir.init(&iir);
	   
	   for(i=0; i < SIGNAL_LENGTH; i++)
	   {
		xn=(int)(32768*(sin(Rad) + cos(Rad*2.3567))/2);          //Q15
		sigIn[i]=xn;
		iir.input=xn;           
        iir.calc(&iir);
        yn=iir.output;
        sigOut[i]=yn;
		Rad = Rad + RadStep;
	   }                   

/*---------------------------------------------------------------------------
    Nothing running in the background at present           
----------------------------------------------------------------------------*/

        while(1) 
        {
        }       

} /* End: main() */

             




