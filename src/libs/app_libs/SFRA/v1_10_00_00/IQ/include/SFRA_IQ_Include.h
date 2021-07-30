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
// FILE:   SFRA_IQ_Include.h
//
// TITLE:  Prototypes and Definitions for the C28x FPU IQ Library
//
// AUTHOR: Manish Bhardwaj (C2000 Systems Solutions, Houston , TX)
//
// DATE: August 11, 2014
//
//###########################################################################
#ifndef SFRA_IQ_INCLUDE_H
#define SFRA_IQ_INCLUDE_H

#ifndef MATH_TYPE
#define   MATH_TYPE      0   //IQ_MATH
#endif
#include "IQmathlib.h"
#include <stdint.h>

typedef struct{
	int32_t *H_MagVect;     //Plant Mag SFRA Vector
	int32_t *H_PhaseVect;   //Plant Phase SFRA Vector
	int32_t *GH_MagVect;    //Open Loop Mag SFRA Vector
	int32_t *GH_PhaseVect;  //Open Loop Phase SFRA Vector
	float *FreqVect;    //Frequency Vector
	int32_t amplitude;      //Injection Amplitude
	int32_t ISR_Freq;       //SFRA ISR frequency
	float Freq_Start;
	float Freq_Step;
	int16_t start;          //Command to start SFRA
	int16_t state;          //State of SFRA
	int16_t status;         //Status of SFRA
	int16_t Vec_Length;     // No. of Points in the SFRA
	int16_t FreqIndex;      // Index of the frequency vector
}SFRA_IQ;

extern void SFRA_IQ_INIT( volatile SFRA_IQ *SFRA_IQ_obj);

extern int32_t SFRA_IQ_INJECT(volatile int32_t ref);
extern void SFRA_IQ_COLLECT(volatile int32_t *control_output,volatile int32_t *feedback);

extern void SFRA_IQ_BACKGROUND(volatile SFRA_IQ *SFRA_IQ_obj);

#endif
