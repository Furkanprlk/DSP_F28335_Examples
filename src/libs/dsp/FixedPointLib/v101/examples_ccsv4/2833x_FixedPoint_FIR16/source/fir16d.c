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

System Name:    16 bit Fixed Point FIR Filter - Fixed Point DSP Library

File Name:      fir16d.c

Description:    Primary System file for demonstrating the FIR Filter

Originator:     Yu Cai (ASP) - Texas Instruments

Target dependency:  C28x
Description:
============
				This module shows how to implement 16 bit FIR filter by calling optimized
				16 bit fir function. The header structure of 16 bit filter is shown
				as follows:

				typedef struct { 
				    long *coeff_ptr;        
				    long * dbuffer_ptr;		
				    int	cbindex;			
				    int order;              
				    int input;               
				    int output;             
				    void (*init)(void *);   
				    void (*calc)(void *);    
				    }FIR16; 
		
				Users can also use default templates defined within fft.h to intialize the FIR16
				header structure.
								
				FIR16  fir= FIR16_DEFAULTS;
		
				For design user specified FIR coefficients, MATLAB Filter Design and Analysis Tool 
				(FDATool) is needed to design a filter and generate coefficients header file. For 
				details, please refer to Fixed Point DSP library manual. 
				        
Watch Variables:

	      		coeff_ptr  	  	Coefficients buffer pointer
	      		dbuffer_ptr	  	Delay buffer pointer
	      		cbindex			Circular buffer pointer
	      		input			Input data (Q15)
	      		sigIn			Input data buffer (Q15)
	      		output			Output data (Q15)
	      		sigOut			Output data buffer (Q15)
 
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
FIR16  fir= FIR16_DEFAULTS;
                                            
/* Define the Delay buffer for the 50th order filterfilter and place it in "firldb" section */  
#pragma DATA_SECTION(dbuffer,"firldb");					// Delay buffer alignment
long dbuffer[(FIR_ORDER+3)/2];    

#pragma DATA_SECTION(sigIn, "sigIn");					// Input/output buffer alignment
#pragma DATA_SECTION(sigOut, "sigOut");     
int sigIn[SIGNAL_LENGTH];
int sigOut[SIGNAL_LENGTH];                               
         
/* Define Constant Co-efficient Array  and place the
.constant section in ROM memory				*/ 
#pragma DATA_SECTION(coeff, "coefffilt");				// Coefficients buffer alignment
long const coeff[(FIR_ORDER+3)/2];

int FIR16_LPF_TEST[FIR_ORDER+1];						// Temporary buffer for adjust odd order FIR
														// coefficients

float	RadStep = 0.1963495408494f;
float	Rad = 0.0f;         
         
/* Finter Input and Output Variables     */   
int xn,yn;
     
void main()
{    
	   unsigned long i;
	   int *p;
	   
	   int FIR_ORDER_REV;
	   
	   InitSysCtrl();
	   DINT;
	   InitPieCtrl();
	   IER = 0x0000;
	   IFR = 0x0000;
	   InitPieVectTable();
	   EINT;   // Enable Global interrupt INTM
	   ERTM;   // Enable Global realtime interrupt DBGM
	   
	   
	   p=(int *)coeff;
	   
	   FIR_ORDER_REV=FIR_ORDER;
	   
	   // FIR16_LPF_TEST initialization
	   //This buffer is only used to adjust odd order FIR filter to even order.
	   for(i=0;i<sizeof(FIR16_LPF32_TEST);i++)
       {	
			FIR16_LPF_TEST[i]=FIR16_LPF32_TEST[i];	//Put coefficients into FIR16_LPF_TEST buffer													
       }
	   
	   if(FIR_ORDER_REV%2!=0)				  		// If ODD Order FIR
	   {
	   		FIR16_LPF_TEST[FIR_ORDER_REV]=0; 		// Added one zero to the end of the coefficient
	   	    FIR_ORDER_REV=FIR_ORDER_REV+1;	  		// order=order+1; order now becomes even number
	   }

/* FIR Generic Filter Initialisation    */ 
       fir.order=FIR_ORDER_REV; 
       fir.dbuffer_ptr=dbuffer;
       fir.coeff_ptr=(long *)coeff; 
       fir.init(&fir);
       
	   //Clean up coeff buffer
       for(i=0;i<FIR_ORDER_REV*2;i=i+2)	
       {	
			*(p+i)=0;
			*(p+i+1)=0;  
       }
       
       //Clean up delay buffer
       for(i=0;i<FIR_ORDER_REV*2;i=i+1)	
       {	
			dbuffer[i]=0;
       }
       
       //Reorganize coefficient table
       //If user would like to reorgainze the order of the coefficients outside this
	   //project, for example, in matlab and stored the reorganized coefficients in 
	   //header file beforehand, this part is not necessarily.
       //More details, please refer to Fixed Point DSP library manual
       for(i=0;i<FIR_ORDER_REV;i=i+2)		
       {
       		*(p+FIR_ORDER_REV-i-2)=FIR16_LPF_TEST[i/2];
       		*(p+FIR_ORDER_REV-i-1)=FIR16_LPF_TEST[i/2+FIR_ORDER_REV/2];	
       }
        
        
       // Generate sample waveforms:
	   Rad = 0.0f;
	   
	   	for(i=0; i < SIGNAL_LENGTH; i++)
		{
			sigIn[i]  =0;          //
			sigOut[i] =0;
		}
	   
	   //FIR calculation
	   for(i=0; i < SIGNAL_LENGTH; i++)
	   {
			xn=(int)(32768*(sin(Rad) + cos(Rad*2.3567))/2);          //Q15
			sigIn[i]=xn;
			fir.input=xn;//0.5 Q15 format
	        fir.calc(&fir);
	        yn=fir.output;
	        sigOut[i]=yn;
			Rad = Rad + RadStep;
	   }              

        while(1) 
        {
        }       

} /* End: main() */

             




