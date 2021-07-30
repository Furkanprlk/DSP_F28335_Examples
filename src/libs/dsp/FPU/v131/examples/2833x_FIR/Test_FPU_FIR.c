// ========================================================================
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// ------------------------------------------------------------------------
//          Copyright (C) 2011-2012 Texas Instruments, Incorporated.
//                          All Rights Reserved.
// ========================================================================
//
//
//  FILE:    Test_FPU_FIR.c
//
//  TITLE:   DSP2833x Device Real FFT Test Program.   
//
//
//  DESCRIPTION:
//
//	
//	This software demonstrates the FIR Filter Usage
//	
//	   The frame work, for demonstrating the FILTER is given below
//	   
//	   
//	   CH0  |--------------|           |------------|               |-----------|
//	   ---->|              |           |            |               |           |
//	   CH0  |              |           |            |               |           |         
//	   ---->|              |     input |            | Output        |  EVMDAC   |
//	   CH0  |   ADC04U_DRV |-----|---->|    FIR     |-------------->|  PWMDAC   |
//	   ---->|              |     |     |   FILTER   |               |  DATALOG  |
//	   CH0  |              |     |     |            |          |--->|           |
//	   --|->|              |     |     |            |          |    |           |
//	        |--------------|     |     |------------|          |    |-----------|
//	                             |                             |
//	                             |-----------------------------|
//
//  FUNCTIONS:
//
//    void FIR_FP_calc(FIR_FP_handle) 
//
//    Where FIR_FP is a structure defined as:
//
//	  typedef struct { 
//    float *coeff_ptr;       /*  0 Pointer to Filter co-efficient array */
//    float *dbuffer_ptr;     /*  2 Delay buffer pointer                 */ 
//    int   cbindex;          /*  4 Circular Buffer Index                */
//    int   order;            /*  5 Order of the filter                  */
//    float input;            /*  6 Input data                           */
//    float output;           /*  8 Output data                          */ 
//    void  (*init)(void *)   /* 10 Pointer to init fun                  */  
//    void  (*calc)(void *);  /* 12 Pointer to the calculation function  */
//    }FIR_FP; 
//
//  ASSUMPTIONS:
//
//     * sigIn and sigOut are of length SIGNAL_LENGTH
//     * N is 32, i.e. 32 tap filter
//	   * order = N - 1 = 31
//     * implementation of an equiripple FIR filter
//
//  Watch Variables:
//
//      sigIn               Input buffer
//      sigOut				Output buffer
//
//
//###########################################################################
// $TI Release: C28x Floating Point Unit Library V1.31 $
// $Release Date: Sep 10, 2012 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "FPU.h"
#include "math.h"
#include "float.h"
 
/* Filter Symbolic Constants                        */
#define FIR_ORDER   	63	/* ORDER = NUM_TAPS - 1 */     
#define SIGNAL_LENGTH (FIR_ORDER+1)* 4 
                                     
                                        
/* Create an Instance of FIRFILT_GEN module and place the object in "firfilt" section       */ 
#pragma DATA_SECTION(firFP, "firfilt")
//#pragma DATA_SECTION(firFP_c, "firfilt")
FIR_FP  firFP = FIR_FP_DEFAULTS;
                                            
/* Define the Delay buffer for the 50th order filterfilter and place it in "firldb" section */  
#pragma DATA_SECTION(dbuffer, "firldb")
float dbuffer[FIR_ORDER+1];

#pragma DATA_SECTION(sigIn, "sigIn");
#pragma DATA_SECTION(sigOut, "sigOut");  
float sigIn[SIGNAL_LENGTH];
float sigOut[SIGNAL_LENGTH];
         
/* Define Constant Co-efficient Array  and place the
.constant section in ROM memory                */
#pragma DATA_SECTION(coeff, "coefffilt");
float const coeff[FIR_ORDER+1]= FIR_FP_LPF64;

/*
 * Calculating a digital frequency
 * Let sampling frequency = 1MHz
 * primary signal @ 10KHz and a secondary signal @ 40KHz
 * Therefore k1 = 1K/100k = 0.01
 *           k2 = 33K/100k = 0.33
 * composite signal = 1/2(sin(2*pi*i*k1) + sin(2*pi*i*k2))
 *                  = 1/2(sin(0.062831853071 * i) + sin(2.073451151*i))
 */
float	RadStep = 0.062831853071f; 	
float   RadStep2 = 2.073451151f;
float	Rad = 0.0f;
float 	Rad2 = 0.0f;

/* Filter Input and Output Variables                */   
float xn,yn;
int count = 0;

     
void main()
{
	unsigned int i;
	
	//Initalize sys clocks and PIE table
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
		sigIn[i]=0;
        sigOut[i]=0;
    }   
	
	/* FIR Generic Filter Initialisation    */ 
	firFP.order=FIR_ORDER; 
	firFP.dbuffer_ptr=dbuffer;
	firFP.coeff_ptr=(float *)coeff; 
	firFP.init(&firFP);
	
	
   	for(i=0; i < SIGNAL_LENGTH; i++)
  	{
  		xn=0.5*sin(Rad) + 0.5*sin(Rad2); //Q15
		sigIn[i]=xn;
        firFP.input= xn;
        firFP.calc(&firFP);
        yn = firFP.output;
        sigOut[i]=yn;
		Rad = Rad + RadStep;
		Rad2 = Rad2 + RadStep2;
   	}   
	
	while(1) 
	{
	
	}       

} /* End: main() */

//===========================================================================
// End of File
//===========================================================================





