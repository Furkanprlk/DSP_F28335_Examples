// TI File $Revision: /main/2 $
// Checkin $Date: January 6, 2011   18:11:07 $
// =====================================================================================
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// -------------------------------------------------------------------------------------
//          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
//                          All Rights Reserved.
// =====================================================================================
//
// FILE:    Test_FPU_RFFTF32_ADC.c
//
// TITLE:   DSP2833x Device Real FFT Test Program.   
//
//  DESCRIPTION:
//
//    This program shows how to compute a real FFT with 12-bit ADC input and 
//    associated spectrum magnitude, phase.  The input buffer must be aligned 
//    to a multiple of the FFT size if using RFFT_adc_f32.  If you do not wish 
//    to align the input buffer then use the RFFT_adc_f32u function. In this case, 
//    the section alignment #pragma can be commented.  However, using this function 
//    will reduce cycle performance of the algorithm.
//
//
// FUNCTIONS:
//
//    void RFFT_adc_f32 (RFFT_ADC_F32_STRUCT *)
//    void RFFT_f32_mag (RFFT_F32_STRUCT *)
//    void RFFT_f32_phase (RFFT_F32_STRUCT *)
//
//    Where RFFT_ADC_F32_STRUCT is a structure defined as:
//
//	 typedef struct {
//	  	Uint16   *InBuf;
//  	void	   *Tail;
//	 } RFFT_ADC_F32_STRUCT;
//
//    Where RFFT_F32_STRUCT is a structure defined as:
//
//    typedef struct {
//      float32  *InBuf;
//      float32  *OutBuf;
//      float32  *CosSinBuf;
//      float32  *MagBuf;
//      float32  *PhaseBuf;
//      Uint16 FFTSize;
//      Uint16 FFTStages;
//    } RFFT_F32_STRUCT;
//
//  ASSUMPTIONS:
//
//	   * OutBuf of RFFT_F32_STRUCT has to be passed to Tail of 
//       RFFT_ADC_F32_STRUCT
//	   * Input signal is stored in Signal.asm
//     * FFTSize must be a power of 2 (32, 64, 128, etc)
//     * FFTSize must be greater or equal to 32
//     * FFTStages must be log2(FFTSize)
//     * InBuf, OutBuf, CosSinBuf are FFTSize in length
//     * MagBuf and PhaseBuf are FFTSize/2+1 in length
//     * MagBuf and PhaseBuf are not used by this function.
//       They are only used by the magitude and phase calculation functions.
//
//  Watch Variables:
//
//      InBuf(RFFT_ADC_F32_STRUCT)    Input buffer
//      InBuf(RFFT_F32_STRUCT)		  Not used
//		Tail						  Stored the address of OutBuf
//      OutBuf						  Output buffer
//      CosSinBuf        			  Twiddle factor buffer
//      MagBuf       				  Magnitude buffer
//      PhaseBuf                      Phase buffer
//      j							  Index of normalized digital frequency component
//      freq						  Real analog frequency of raw signal
//
//######################################################################################
// $TI Release: C28x FPU Library v1.20 $
// $Release Date: January 11, 2011 $
//######################################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "math.h"
#include "float.h"
#include "FPU.h"

#define	FFT_REAL_STAGES	9
#define	FFT_REAL_SIZE	(1 << FFT_REAL_STAGES) 

#define F_PER_SAMPLE 3125000.0L/(float)FFT_REAL_SIZE        //Assuming sampling rate is 3.125MHz

RFFT_ADC_F32_STRUCT rfft_adc;
RFFT_F32_STRUCT rfft;

#pragma DATA_SECTION(FFTReal_out,"FFTReal_Output");         //Input buffer assignment
															//If using RFFT_adc_f32, input alignment is
															//necessary; if using RFFT_adc_f32u, input 
															//alignment is optional and can be commented.
#pragma DATA_SECTION(FFTReal_CosSinTable,"FFTReal_CosSin"); //Twiddle factor buffer assignment
#pragma DATA_SECTION(FFTReal_Magnitude,"FFTReal_Magnitude");//Output buffer assignment
extern Uint16  FFTReal_in[FFT_REAL_SIZE];
float32 FFTReal_out[FFT_REAL_SIZE];
float32 FFTReal_CosSinTable[FFT_REAL_SIZE];
float32 FFTReal_Magnitude[FFT_REAL_SIZE/2+1];

void main(void)
{

   	Uint16 i,j;
   	float32 freq; 

	InitSysCtrl();
	DINT;
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM   

  
   
   	rfft_adc.Tail = &rfft.OutBuf;		//Link the RFFT_ADC_F32_STRUCT to
   										//RFFT_F32_STRUCT. Tail pointer of 
   										//RFFT_ADC_F32_STRUCT is passed to
   										//the OutBuf pointer of RFFT_F32_STRUCT 
   
   	rfft.FFTSize  = FFT_REAL_SIZE;		//FFT size
   	rfft.FFTStages = FFT_REAL_STAGES;	//FFT stages
   
   	rfft_adc.InBuf = &FFTReal_in[0];	//Input buffer with 12-bit ADC input
   	rfft.OutBuf = &FFTReal_out[0];   	//Output buffer

   	rfft.CosSinBuf = &FFTReal_CosSinTable[0]; //Twiddle factor 

   	rfft.MagBuf = &FFTReal_Magnitude[0];//Magnitude output buffer

   	RFFT_f32_sincostable(&rfft);  		//Calculate twiddle factor
 
   	for (i=0; i < FFT_REAL_SIZE; i++)
   	{
     	FFTReal_out[i] = 0;				//Clean up output buffer
   	}
   
   	for (i=0; i < FFT_REAL_SIZE/2; i++)
   	{
    	FFTReal_Magnitude[i] = 0;		//Clean up magnitude buffer
   	}   

   	RFFT_adc_f32(&rfft_adc);			//Calculate real FFT with 12-bit ADC input
   	RFFT_f32_mag(&rfft);				//Calculate spectrum magnitude
   
   	//Find out the maximum frequency component of signal frequency component signal,
   	//(this algorithm is only used for finding frequency of one component frequency 
   	//signal, for example, one freqency sinusoidal wave)
   	j = 1;
   	freq = FFTReal_Magnitude[1];
   	for(i=2;i<FFT_REAL_SIZE/2+1;i++)
   	{
   		//Looking for the maximum component of frequency spectrum
      	if(FFTReal_Magnitude[i] > freq)
      	{
          	j = i;
          	freq = FFTReal_Magnitude[i];
      	}
   	}
   
   	freq = F_PER_SAMPLE * (float)j;     //Converting normalized digital frequency to real analog frequency
      
   	asm("   ESTOP0");   
   	for(;;);

}

//===========================================================================
// No more.
//===========================================================================
