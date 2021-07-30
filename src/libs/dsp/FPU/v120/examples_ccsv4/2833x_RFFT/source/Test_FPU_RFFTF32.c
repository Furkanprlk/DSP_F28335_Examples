// TI File $Revision: /main/2 $
// Checkin $Date: January 6, 2011   18:11:04 $
// ========================================================================
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// ------------------------------------------------------------------------
//          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
//                          All Rights Reserved.
// ========================================================================
//
//
//  FILE:    Test_FPU_RFFTF32.c
//
//  TITLE:   DSP2833x Device FIR Test Program.   
//
//
//  DESCRIPTION:
//
//    This program shows how to compute a real FFT and associated spectrum 
//    magnitude, phase.  The input buffer must be aligned to a multiple of the 
//    FFT size if using RFFT_f32.  If you do not wish to align the input buffer
//    then use the RFFT_f32u function. In this case, the section alignment #pragma
//    can be commented.  However, using this function will reduce cycle performance 
//    of the algorithm.
//
//  FUNCTIONS:
//
//    void RFFT_f32 (FFT_REAL *)
//    void RFFT_f32_mag (FFT_REAL *)
//    void RFFT_f32_phase (FFT_REAL *)
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
//      InBuf               Input buffer
//      OutBuf				Output buffer
//      CosSinBuf        	Twiddle factor buffer
//      MagBuf       		Magnitude buffer
//      PhaseBuf            Phase buffer
//
//--------------------------------------------------------------------------
//  Input buffer structure:
//   	InBuf[0] = input[0]
//   	InBuf[1] = input[1]
//   	InBuf[2] = input[2]
//   	………
//   	InBuf[N/2] = input[N/2]
//   	InBuf[N/2+1] = input[N/2+1]
//   	………
//   	InBuf[N-3] = input[N-3]
//   	InBuf[N-2] = input[N-2]
//   	InBuf[N-1] = input[N-1]
//
//
//###########################################################################
// $TI Release: C28x FPU Library v1.20 $
// $Release Date: January 11, 2011 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "math.h"
#include "float.h"
#include "FPU.h"

#define	FFT_REAL_STAGES	5
#define	FFT_REAL_SIZE	(1 << FFT_REAL_STAGES) 

#pragma DATA_SECTION(FFTReal_in,"FFTReal_Input");           //Input buffer alignment
#pragma DATA_SECTION(FFTReal_out,"FFTReal_Output");         //If using RFFT_f32u, this
#pragma DATA_SECTION(FFTReal_CosSinTable,"FFTReal_CosSin"); //part (started by #prama 
#pragma DATA_SECTION(FFTReal_Magnitude,"FFTReal_Magnitude");//can be commented.

float32 FFTReal_in[FFT_REAL_SIZE];
float32 FFTReal_out[FFT_REAL_SIZE];
float32 FFTReal_CosSinTable[FFT_REAL_SIZE];
float32 FFTReal_Magnitude[FFT_REAL_SIZE/2+1];

float	RadStep = 0.1963495408494f;
float	Rad = 0.0f;

RFFT_F32_STRUCT rfft;

void main(void)
{
	Uint16	i;

	InitSysCtrl();
	DINT;
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();
	EINT;   // Enable Global interrupt INTM
	ERTM;   // Enable Global realtime interrupt DBGM   

	// Clear input buffers:
	for(i=0; i < FFT_REAL_SIZE; i++)
	{
		FFTReal_in[i] = 0.0f;
	}
	
	// Generate sample waveforms:
	Rad = 0.0f;
	for(i=0; i < FFT_REAL_SIZE; i++)
	{
		FFTReal_in[i]   = sin(Rad) + cos(Rad*2.3567); //Real input signal
		//FFTImag_in[i] = cos(Rad*8.345) + sin(Rad*5.789);		
		Rad = Rad + RadStep;
	}
   
    rfft.FFTSize  = FFT_REAL_SIZE;
    rfft.FFTStages = FFT_REAL_STAGES;   
    rfft.InBuf = &FFTReal_in[0];               //Input buffer
    rfft.OutBuf = &FFTReal_out[0];             //Output buffer
    rfft.CosSinBuf = &FFTReal_CosSinTable[0];  //Twiddle factor buffer
    rfft.MagBuf = &FFTReal_Magnitude[0];	   //Magnitude buffer

    RFFT_f32_sincostable(&rfft);  		//Calculate twiddle factor
 
    for (i=0; i < FFT_REAL_SIZE; i++)
    {
      	FFTReal_out[i] = 0;			    //Clean up output buffer
    }

    for (i=0; i < FFT_REAL_SIZE/2; i++) 
    {
     	FFTReal_Magnitude[i] = 0;		//Clean up magnitude buffer
    }   

    RFFT_f32(&rfft);					//Calculate real FFT
    
//   OutBuf[0] = real[0]
//   OutBuf[1] = real[1]
//   OutBuf[2] = real[2]
//   ………
//   OutBuf[N/2] = real[N/2]
//   OutBuf[N/2+1] = imag[N/2-1]
//   ………
//   OutBuf[N-3] = imag[3]
//   OutBuf[N-2] = imag[2]
//   OutBuf[N-1] = imag[1]
//    
    
    RFFT_f32_mag(&rfft);				//Calculate magnitude
    
//   MagBuf[0] = magnitude[0]
//   MagBuf[1] = magnitude[1]
//   MagBuf[2] = magnitude[2]
//   ………
//   MagBuf[N/2] = magnitude[N/2]
//   MagBuf[N/2+1] = magnitude[N/2+1]
    
//    RFFT_f32_phase(&rfft);		   	//Calculate phase

	// Just sit and loop forever (optional):
    for(;;);

}

//===========================================================================
// No more.
//===========================================================================
