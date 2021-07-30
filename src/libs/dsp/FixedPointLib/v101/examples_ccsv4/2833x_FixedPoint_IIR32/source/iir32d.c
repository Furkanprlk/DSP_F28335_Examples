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

System Name:    32 bit Fixed Point IIR Filter - Fixed Point DSP Library

File Name:      iir32d.c

Description:    Primary System file for demonstrating the 32 bit IIR Filter

Originator:     Yu Cai (ASP) - Texas Instruments

Target dependency:  C28x
Description:
============

				typedef struct {
				    void (*init)(void *);   
				    void (*calc)(void *);    
				    long *coeff_ptr;       
				    long *dbuffer_ptr;      
				    long nbiq;               
				    long input;              
				    long isf;               
				    long output32;          
				    int output16;           
				    int qfmat;              
				    }IIR5BIQ32;   
				    
Watch Variables:
	      		sigIn      	Data input buffer (Q31)
	      		sigOut		Data output buffer (Q31)
	      		coeff       coefficient buffer (for data structure, please refer to 
	      					fixed point DSP library manual)
	      		input 		Data input (Q31)
	      		output32	Data output (Q31)
	      		output16    Data output (Q14)
	      		dbuffer		delay buffer (for data structure, please refer to fixed
	      					point DSP library manual) 
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
#define SIGNAL_LENGTH 1000 
    
/* Create an Instance of IIR5BIQD32 module and place the object in "iirfilt" section    */ 
#pragma DATA_SECTION(iir, "iirfilt");
IIR5BIQ32  iir=IIR5BIQ32_DEFAULTS;

/* =============================================================================
Modify the delay buffer size to comensurate with the no of biquads in the filter
Size of the Delay buffer=4*nbiq
==============================================================================*/ 
/* Define the Delay buffer for the cascaded 6 biquad IIR filter and place it in "iirfilt" section */
#pragma DATA_SECTION(dbuffer,"iirfilt");
long dbuffer[2*IIR32_LPF_NBIQ];

#pragma DATA_SECTION(sigIn, "sigIn");
#pragma DATA_SECTION(sigOut, "sigOut");     
long sigIn[SIGNAL_LENGTH];
long sigOut[SIGNAL_LENGTH]; 

/* Define Constant Co-efficient Array  and place the
.constant section in ROM memory				*/ 
const long coeff[5*IIR32_LPF_NBIQ]=IIR32_LPF_COEFF;
         
         
float	RadStep = 0.1963495408494f;
float	Rad = 0.0f;         
         
/* Finter Input and Output Variables                */   
long xn;
long yn;
     
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

		/* IIR Filter Initialisation         */ 
       iir.dbuffer_ptr=dbuffer;
       iir.coeff_ptr=(long *)coeff; 
       iir.qfmat=IIR32_LPF_QFMAT;
       iir.nbiq=IIR32_LPF_NBIQ; 
       iir.isf=IIR32_LPF_ISF; 
       iir.init(&iir);
              
	   for(i=0; i < SIGNAL_LENGTH; i++)
	   {
		xn=(long)(2147483648*(sin(Rad) + cos(Rad*2.3567))/2);          //Q31
		sigIn[i]=xn;
		iir.input=xn;           
        iir.calc(&iir);
        yn=iir.output32;
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

             




