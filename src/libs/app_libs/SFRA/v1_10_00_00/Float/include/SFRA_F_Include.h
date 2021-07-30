//###########################################################################
//  This software is licensed for use with Texas Instruments C28x
//  family Microcontrollers.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// ------------------------------------------------------------------------
//          Copyright (C) 2014 Texas Instruments, Incorporated.
//                          All Rights Reserved.
// ==========================================================================
//
// FILE:   SFRA_F_Include.h
//
// TITLE:  Prototypes and Definitions for the C28x FPU SFRA Library
//
// AUTHOR: Manish Bhardwaj (C2000 Systems Solutions, Houston , TX)
//
// DATE: August 11, 2014
//
//###########################################################################

#ifndef SFRA_IQ_INCLUDE_H
#define SFRA_IQ_INCLUDE_H

#ifndef MATH_TYPE
#define   MATH_TYPE      1   //FLOAT_MATH
#endif
#include <stdint.h>
#include "IQmathlib.h"

typedef struct{
	float *H_MagVect;     //Plant Mag FRA Vector
	float *H_PhaseVect;   //Plant Phase FRA Vector
	float *GH_MagVect;    //Open Loop Mag FRA Vector
	float *GH_PhaseVect;  //Open Loop Phase FRA Vector
	float *FreqVect;    //Frequency Vector
	float amplitude;      //Injection Amplitude
	float ISR_Freq;       //FRA ISR frequency
	float Freq_Start;
	float Freq_Step;
	int16_t start;          //Command to start FRA
	int16_t state;          //State of FRA
	int16_t status;         //Status of FRA
	int16_t Vec_Length;     // No. of Points in the FRA
	int16_t FreqIndex;      // Index of the frequency vector
}SFRA_F;

extern void SFRA_F_INIT( volatile SFRA_F *FRA_F_obj);

extern float SFRA_F_INJECT(volatile float ref);
extern void SFRA_F_COLLECT(volatile float *control_output,volatile float *feedback);

extern void SFRA_F_BACKGROUND(volatile SFRA_F *FRA_IQ_obj);

#endif
