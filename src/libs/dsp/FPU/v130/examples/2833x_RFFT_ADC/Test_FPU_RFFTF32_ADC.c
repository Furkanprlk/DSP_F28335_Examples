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
// $TI Release: C28x Floating Point Unit Library V1.30 $
// $Release Date: January 04, 2012 $
//######################################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "math.h"
#include "float.h"
#include "FPU.h"

#define RFFT_STAGES  9
#define RFFT_SIZE   (1 << RFFT_STAGES) 

#define F_PER_SAMPLE 3125000.0L/(float)RFFT_SIZE        //Assuming sampling rate is 3.125MHz

RFFT_ADC_F32_STRUCT rfft_adc;
RFFT_F32_STRUCT rfft;

extern Uint16 RFFTin1Buff[RFFT_SIZE];           //Buffer alignment for the input array,
                                                //RFFT_adc_f32u(optional) RFFT_adc_f32(required)
                                                //Output of FFT overwrites input if 
                                                //RFFT_STAGES is ODD
#pragma DATA_SECTION(RFFToutBuff,"RFFTdata2"); 
float32 RFFToutBuff[RFFT_SIZE];                 //Output of FFT here if RFFT_STAGES is EVEN

#pragma DATA_SECTION(RFFTmagBuff,"RFFTdata3");
float32 RFFTmagBuff[RFFT_SIZE/2+1];             //Additional Buffer used in Magnitude calc
 
#pragma DATA_SECTION(RFFTF32Coef,"RFFTdata4");
float32 RFFTF32Coef[RFFT_SIZE];                 //Twiddle buffer

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
   
   	rfft.FFTSize  = RFFT_SIZE;		//FFT size
   	rfft.FFTStages = RFFT_STAGES;	//FFT stages
   
   	rfft_adc.InBuf = &RFFTin1Buff[0];	//Input buffer with 12-bit ADC input
   	rfft.OutBuf = &RFFToutBuff[0];   	//Output buffer

   	rfft.CosSinBuf = &RFFTF32Coef[0]; //Twiddle factor 

   	rfft.MagBuf = &RFFTmagBuff[0];//Magnitude output buffer

   	RFFT_f32_sincostable(&rfft);  		//Calculate twiddle factor
 
   	for (i=0; i < RFFT_SIZE; i++)
   	{
     	RFFToutBuff[i] = 0;				//Clean up output buffer
   	}
   
   	for (i=0; i < RFFT_SIZE/2; i++)
   	{
    	RFFTmagBuff[i] = 0;		//Clean up magnitude buffer
   	}   

   	RFFT_adc_f32(&rfft_adc);			//Calculate real FFT with 12-bit ADC input
   	RFFT_f32_mag(&rfft);				//Calculate spectrum magnitude
   
   	//Find out the maximum frequency component of signal frequency component signal,
   	//(this algorithm is only used for finding frequency of one component frequency 
   	//signal, for example, one freqency sinusoidal wave)
   	j = 1;
   	freq = RFFTmagBuff[1];
   	for(i=2;i<RFFT_SIZE/2+1;i++)
   	{
   		//Looking for the maximum component of frequency spectrum
      	if(RFFTmagBuff[i] > freq)
      	{
          	j = i;
          	freq = RFFTmagBuff[i];
      	}
   	}
   
   	freq = F_PER_SAMPLE * (float)j;     //Converting normalized digital frequency to real analog frequency
      
   	asm("   ESTOP0");   
   	for(;;);

} //end of main()

//===========================================================================
// End of File
//===========================================================================
