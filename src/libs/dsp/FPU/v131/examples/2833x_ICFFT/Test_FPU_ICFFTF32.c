// =====================================================================================
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// -------------------------------------------------------------------------------------
//          Copyright (C) 2011-2012 Texas Instruments, Incorporated.
//                          All Rights Reserved.
//======================================================================================
//
//  FILE:    Test_FPU_ICFFTF32.c
//
//  TITLE:   DSP2833x Device Inverse Complex FFT Test Program.   
//
//
//  ASSUMPTIONS:
//
//      This is a program which shows how to call inverse complex fft fpu function.
//
//      The test functions includes CFFT_f32,ICFFT_f32 and CFFT_f32_mag.
//      Data section allignment (#pragma ...) is necessary for testing CFFT_f32
//   
//      Minimum CFFT_Stages is 3. When CFFT_Stages are more than 9, the 
//      quantitization error would be significant and not recommended. The 
//      results can be compared with MATLAB code CFFTforC28xNew.
//
//      Where CFFT_F32_STRUCT is a structure defined as:
//
//      typedef struct {
//          float   *InPtr;
//          float   *OutPtr;
//          float   *CoefPtr;
//          float   *CurrentInPtr;
//          float   *CurrentOutPtr;
//          short   Stages;
//          Uint16  FFTSize;
//      }CFFT_F32_STRUCT;
//   
//  Watch Variables:
//
//      InPtr               Input/output or middle stage of ping-pong buffer
//      OutPtr              Output or middle stage of ping-pong buffer
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
//Result Buf  |    buf1     |   buf2      |     buf1    |..|    buf1     |      buf2
//--------------------------------------------------------------------------------------
//
//     * FFTSize must be a power of 2 (32, 64, 128, etc)
//     * FFTSize must be greater or equal to 32
//     * FFTStages must be log2(FFTSize)
//     * InPtr, OutPtr, CoefPtr, CurrentInPtr, CurrentOutPtr are FFTSize*2 in 
//       length.
//
//######################################################################################
// $TI Release: C28x Floating Point Unit Library V1.31 $
// $Release Date: Sep 10, 2012 $
//######################################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "math.h"
#include "float.h"
#include "FPU.h"

#define CFFT_STAGES 8
#define CFFT_SIZE   (1 << CFFT_STAGES) 


#pragma	DATA_SECTION(CFFTin1Buff,"CFFTdata1") 
float32	CFFTin1Buff[CFFT_SIZE*2];					// FFT input data buffer, alignment require
                                                    // Output of ICFFT overwrites input if 
                                                    //CFFT_STAGES is ODD
#pragma	DATA_SECTION(CFFToutBuff,"CFFTdata2")
float32	CFFToutBuff[CFFT_SIZE*2];					// FFT output buffer
                                                    // Output of FFT here if CFFT_STAGES is EVEN
#pragma	DATA_SECTION(CFFTmagBuff,"CFFTdata3")
float32	CFFTmagBuff[CFFT_SIZE];						// FFT output magnitude buffer
#pragma	DATA_SECTION(CFFTF32Coef,"CFFTdata4") 
float32	CFFTF32Coef[CFFT_SIZE];                 	// FFT Twiddle factor buffer

CFFT_F32_STRUCT cfft;								// Complex FFT structure

float   RadStep = 0.1963495408494f;                // Step to generate test bench waveform
float   Rad = 0.0f;

CFFT_F32_STRUCT cfft;

void main(void)
{
    Uint16  i;

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
        CFFToutBuff[i] = 0.0f;
        CFFToutBuff[i+1] = 0.0f;
        }
    
// Generate sample waveforms:
//     CFFTin1Buff[0] = real[0]
//     CFFTin1Buff[1] = imag[0]
//     CFFTin1Buff[2] = real[1]
//     ………
//     CFFTin1Buff[N] = real[N/2]
//     CFFTin1Buff[N+1] = imag[N/2]
//     ………
//     CFFTin1Buff[2N-3] = imag[N-2]
//     CFFTin1Buff[2N-2] = real[N-1]
//     CFFTin1Buff[2N-1] = imag[N-1]
            
    Rad = 0.0f;
    for(i=0; i < (CFFT_SIZE*2); i=i+2)
        {
        CFFTin1Buff[i]   = sin(Rad) + cos(Rad*2.3567);       // Real Part
        CFFTin1Buff[i+1] = cos(Rad*8.345) + sin(Rad*5.789);  // Image Part
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
    
    cfft.CoefPtr = CFFTF32Coef;             //Twiddle factor table
    cfft.InPtr = CFFTin1Buff;               //Input/output or middle stage of ping-pong buffer
    cfft.OutPtr = CFFToutBuff;              //Output or middle stage of ping-pong buffer
    cfft.Stages = CFFT_STAGES;              // FFT stages
    cfft.FFTSize = CFFT_SIZE;               // FFT size
    
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
    
    CFFT_f32(&cfft);                        // Calculate FFT

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
	cfft.CurrentInPtr=CFFToutBuff;	        // Mag function input pointer
	cfft.CurrentOutPtr=CFFTmagBuff;	        // Mag function output pointer
    CFFT_f32_mag(&cfft);                    // Calculate magnitude, result stored in CurrentOutPtr

// Magnitude Result:
//     CurrentOutPtr[0] = Mag[0]
//     CurrentOutPtr[1] = Mag[1]
//     CurrentOutPtr[2] = Mag[2]
//     ………
//     CurrentOutPtr[N-1] = Mag[N-1]

	// Perform the iCFFT to recover the input data
	cfft.InPtr = CFFToutBuff;		       // ICFFT input pointer
	cfft.OutPtr = CFFTin1Buff;		       // ICFFT output pointer
	ICFFT_f32(&cfft);				       // Calculate the ICFFT

    // Just sit and loop forever (optional):
    for(;;);

}

//===========================================================================
// End of File
//===========================================================================


