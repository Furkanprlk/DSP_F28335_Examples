// =====================================================================================
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// -------------------------------------------------------------------------------------
//          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
//                          All Rights Reserved.
//======================================================================================
//
// 	FILE:    Test_FPU_CFFTF32.c
//
// 	TITLE:   DSP2833x Device Complex FFT Test Program.   
//
//
// 	ASSUMPTIONS:
//
//   	This is a program which shows how to call complex fft fpu function.
//
//   	The test functions includes CFFT_f32u,CFFT_f32_mag and CFFT_f32_phase.
//   	Data section allignment (#pragma ...) is not necessary for CFFT_f32u 
//   	but necessary for testing CFFT_f32.
//
//   
//   	Minimum CFFT_Stages is 3. When CFFT_Stages are more than 9, the 
//   	quantitization error would be significant and not recommended. The 
//   	results can be compared with MATLAB code CFFTforC28xNew.
//
//   	Where CFFT_F32_STRUCT is a structure defined as:
//
//	 	typedef struct {
//			float	*InPtr;
//			float	*OutPtr;
//			float	*CoefPtr;
//			float	*CurrentInPtr;
//			float	*CurrentOutPtr;
//			short	Stages;
//			Uint16  FFTSize;
//	    }CFFT_F32_STRUCT;
//   
//  Watch Variables:
//
//      InPtr               Input/output or middle stage of ping-pong buffer
//      OutPtr				Output or middle stage of ping-pong buffer
//      CurrentInPtr        Output buffer for CFFT result
//      CurrentOutPtr       N-1 stage CFFT result/Magnitude/Phase output buffer
//      CoefPtr             Twiddel factor buffer
//
//--------------------------------------------------------------------------------------
//            | Stage 3     | Stage 4     | Stage5      |..| StageN(odd) | StageN(even)
//--------------------------------------------------------------------------------------
//InPtr(buf1) |CurrentInPtr |CurrentOutPtr|CurrentInPtr |..|CurrentInPtr |CurrentOutPtr
//--------------------------------------------------------------------------------------
//OutPtr(buf2)|CurrentOutPtr|CurrentInPtr |CurrentOutPtr|..|CurrentOutPtr|CurrentInPtr
//--------------------------------------------------------------------------------------
//Result Buf  |    buf1		|	buf2	  |		buf1	|..|	buf1	 |		buf2
//--------------------------------------------------------------------------------------
//
//     * FFTSize must be a power of 2 (32, 64, 128, etc)
//     * FFTSize must be greater or equal to 32
//     * FFTStages must be log2(FFTSize)
//     * InPtr, OutPtr, CoefPtr, CurrentInPtr, CurrentOutPtr are FFTSize*2 in 
//       length.
//
//######################################################################################
// $TI Release: C28x Floating Point Unit Library V1.30 $
// $Release Date: January 04, 2012 $
//######################################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "math.h"
#include "float.h"
#include "FPU.h"

#define	CFFT_STAGES	7
#define	CFFT_SIZE	(1 << CFFT_STAGES) 

#pragma	DATA_SECTION(CFFTin1Buff,"CFFTdata1");  //Buffer alignment for the input array,
float   CFFTin1Buff[CFFT_SIZE*2];               //CFFT_f32u(optional), CFFT_f32(required)
                                                //Output of FFT overwrites input if 
                                                //CFFT_STAGES is ODD

#pragma	DATA_SECTION(CFFTin2Buff,"CFFTdata2");  
float	CFFTin2Buff[CFFT_SIZE*2];               //Additional Buffer used in Magnitude calc

#pragma	DATA_SECTION(CFFToutBuff,"CFFTdata3");	
float	CFFToutBuff[CFFT_SIZE*2];               //Output of FFT here if CFFT_STAGES is EVEN

#pragma	DATA_SECTION(CFFTF32Coef,"CFFTdata4"); 
float	CFFTF32Coef[CFFT_SIZE];                 //Twiddle buffer

float	RadStep = 0.1963495408494f;             // Step to generate test bench waveform
float	Rad = 0.0f;

CFFT_F32_STRUCT cfft;

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
	for(i=0; i < (CFFT_SIZE*2); i=i+2)
		{
		CFFTin1Buff[i] = 0.0f;
		CFFTin1Buff[i+1] = 0.0f;
		CFFTin2Buff[i] = 0.0f;
		CFFTin2Buff[i+1] = 0.0f;
		CFFToutBuff[i] = 0.0f;
		CFFToutBuff[i+1] = 0.0f;
		}
	
// Generate sample waveforms:
//	   CFFTin1Buff[0] = real[0]
//	   CFFTin1Buff[1] = imag[0]
//	   CFFTin1Buff[2] = real[1]
//	   ………
//	   CFFTin1Buff[N] = real[N/2]
//	   CFFTin1Buff[N+1] = imag[N/2]
//	   ………
//	   CFFTin1Buff[2N-3] = imag[N-2]
//	   CFFTin1Buff[2N-2] = real[N-1]
//	   CFFTin1Buff[2N-1] = imag[N-1]
			
	Rad = 0.0f;
	for(i=0; i < (CFFT_SIZE*2); i=i+2)
		{
		CFFTin1Buff[i]   = sin(Rad) + cos(Rad*2.3567);       // Real Part
		CFFTin1Buff[i+1] = cos(Rad*8.345) + sin(Rad*5.789);  // Image Part
		CFFTin2Buff[i]   = CFFTin1Buff[i];					 // Not used in calculation
		CFFTin2Buff[i+1] = CFFTin1Buff[i+1];				 // Not used in calculation
		Rad = Rad + RadStep;
		}

//
// Comment Out Following Code To Run CFFT Between Ping-Pong Buffers:
//
// Note: In this version, CFFTin1Buff and CFFToutBuff are used in
//       ping-pong fashion. The input data is first stored in CFFTin1Buff.
//       The FFT is then calculated, including bit reversing, and
//       when done, the cfft.CurrentInPtr pointer points to
//       buffer which has the result. Depending on the FFT size,
//       it will either be in CFFTin1Buff or CFFToutBuff.
	
	cfft.CoefPtr = CFFTF32Coef;				//Twiddle factor table
	cfft.InPtr   = CFFTin1Buff;				//Input/output or middle stage of ping-pong buffer
	cfft.OutPtr  = CFFToutBuff;				//Output or middle stage of ping-pong buffer
	cfft.Stages  = CFFT_STAGES;				// FFT stages
	cfft.FFTSize = CFFT_SIZE;				// FFT size
	
	CFFT_f32_sincostable(&cfft);            // Calculate twiddle factor
	
//===========================================================================
// CFFT result:
//     CurrentInPtr[0] = real[0]
//     CurrentInPtr[1] = imag[0]
//     CurrentInPtr[2] = real[1]
//     ………
//     CurrentInPtr[N] = real[N/2]
//     CurrentInPtr[N+1] = imag[N/2]
//     ………
//     CurrentInPtr[2N-3] = imag[N-2]
//     CurrentInPtr[2N-2] = real[N-1]
//     CurrentInPtr[2N-1] = imag[N-1]
//
//=============================================================================
	
	CFFT_f32(&cfft);						// Calculate FFT

//
// Note: To calculate magnitude, the input data is pointed by cfft.CurrentInPtr.
//       The calculated magnitude is stored in the memory pointed by
//       cfft.CurrentOutPtr. If not changing cfft.CurrentOutPtr after called
//       magnitude calculation function, the output buffer would be overwrite
//       right after phase calculation function called.
//
//       If Stages is ODD, the currentInPtr=CFFTin1Buff, currentOutPtr=CFFToutBuff
//       If Stages is Even, the currentInPtr=CFFToutBuff, currentOutPtr=CFFTin1Buff
//

	// Calculate Magnitude:
	CFFT_f32_mag(&cfft);					// Calculate magnitude, result stored in CurrentOutPtr

// Magnitude Result:
//	   CurrentOutPtr[0] = Mag[0]
//	   CurrentOutPtr[1] = Mag[1]
//	   CurrentOutPtr[2] = Mag[2]
//	   ………
//	   CurrentOutPtr[N-1] = Mag[N-1]

	// Calculate Phase:
    cfft.CurrentOutPtr=CFFTin2Buff;			// To avoid overwrite magnitude, changed the output of phase
    										// to CFFTin2Buff
	CFFT_f32_phase(&cfft); 					// Calculate phase, result stored in CurrentOutPtr
	
// Phase Result:
//	   CurrentOutPtr[0] = Phase[0]
//	   CurrentOutPtr[1] = Phase[1]
//	   CurrentOutPtr[2] = Phase[2]
//	   ………
//	   CurrentOutPtr[N-1] = Phase[N-1]

	// Just sit and loop forever (optional):
   	for(;;);

}

//===========================================================================
// End of File
//===========================================================================
