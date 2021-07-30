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

System Name:    32 bit Fixed Point FIR Filter - Fixed Point DSP Library

File Name:      fir32d.c

Description:    Primary System file for demonstrating the FIR Filter

Originator:     Yu Cai (ASP) - Texas Instruments

Target dependency:  C28x
Description:
============
				This module shows how to implement 32 bit FIR filter by calling optimized
				32 bit fir function. The header structure of 32 bit filter is shown
				as follows:

				typedef struct { 
				    long *coeff_ptr;        
				    long * dbuffer_ptr;		
				    int	cbindex;			
				    int order;              
				    long input;               
				    long output;             
				    void (*init)(void *);   
				    void (*calc)(void *);    
				    }FIR32; 
		
				Users can also use default templates defined within fft.h to intialize the FIR16
				header structure.
								
				FIR32  fir= FIR32_DEFAULTS;
		
				For design user specified FIR coefficients, MATLAB Filter Design and Analysis Tool 
				(FDATool) is needed to design a filter and generate coefficients header file. For 
				details, please refer to Fixed Point DSP library manual. 
				        
Watch Variables:

	      		coeff_ptr  	  	Coefficients buffer pointer
	      		dbuffer_ptr	  	Delay buffer pointer
	      		cbindex			Circular buffer pointer
	      		input			Input data (Q31)
	      		sigIn			Input data buffer (Q31)
	      		output			Output data (Q30)
	      		sigOut			Output data buffer (Q30)
*/
//######################################################################################
// $TI Release: C28x Fixed Point Library v1.01 $
// $Release Date: January 11,2011 $
//######################################################################################

#include "DSP28x_Project.h"
#include <fir.h>
#include "math.h"
#include "float.h"
 
/* Filter Symbolic Constants                        */
#define FIR_ORDER   32                                       
#define SIGNAL_LENGTH 100
                                        
/* Create an Instance of FIRFILT_GEN module and place the object in "firfilt" section       */ 
#pragma DATA_SECTION(fir, "firfilt");
FIR32  fir= FIR32_DEFAULTS;
                                            
/* Define the Delay buffer for the 50th order filterfilter and place it in "firldb" section */  
#pragma DATA_SECTION(dbuffer,"firldb");		//Delay buffer allignment
long dbuffer[FIR_ORDER+1];    

#pragma DATA_SECTION(sigIn, "sigIn");		//Input buffer alignment
#pragma DATA_SECTION(sigOut, "sigOut");     //Output buffer alignment
long sigIn[SIGNAL_LENGTH];
long sigOut[SIGNAL_LENGTH];                               
         
/* Define Constant Co-efficient Array  and place the
.constant section in ROM memory				*/ 
#pragma DATA_SECTION(coeff, "coefffilt");	//Coefficient buffer alignment
const long coeff[FIR_ORDER]=FIR32_LPF32_TEST;
float	RadStep = 0.1963495408494f;			//Simulated signal generation parameter
float	Rad = 0.0f;         
         
/* Finter Input and Output Variables                */   
long xn,yn;
     
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
	   

/* FIR Generic Filter Initialisation    */ 
       fir.order=FIR_ORDER; 
       fir.dbuffer_ptr=dbuffer;
       fir.coeff_ptr=(long *)coeff; 
       fir.init(&fir);       
        
       // Generate sample waveforms:
	   Rad = 0.0f;
	   
	   // Clean up input/output buffer
	   for(i=0; i < SIGNAL_LENGTH; i++)
		{
			sigIn[i]  =0;          
			sigOut[i] =0;
		}

	   for(i=0; i < SIGNAL_LENGTH; i++)
	   {
		xn=(long)(2147483648*(sin(Rad) + cos(Rad*2.3567))/2);     //Q31
		sigIn[i]=xn;		//Input data buffer 
		fir.input=xn;		//Input data
        fir.calc(&fir);		//FIR convolution operation
        yn=fir.output;		//Output data
        sigOut[i]=yn;		//Output data buffer
		Rad = Rad + RadStep;//Update simulated signal parameter
	   }              

/*---------------------------------------------------------------------------
    Nothing running in the background at present           
----------------------------------------------------------------------------*/

        while(1) 
        {
        }       

} /* End: main() */

             




