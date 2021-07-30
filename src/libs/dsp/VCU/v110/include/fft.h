/******************************************************************************
*******************************************************************************
* 
* FILE: fft.h
* 
* DESCRIPTION: This file contains the API for the complex and real fft routines
*              in the VCU library
* 
*******************************************************************************
*  $TI Release: C28x VCU Library Version v1.10 $
*  $Release Date: September 26, 2011 $
*******************************************************************************
*  This software is licensed for use with Texas Instruments C28x
*  family DSCs.  This license was provided to you prior to installing
*  the software.  You may review this license by consulting a copy of
*  the agreement in the doc directory of this library.
* ------------------------------------------------------------------------
*          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
*                          All Rights Reserved.
******************************************************************************/
#ifndef __FFT_H__
#define __FFT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "DSP28x_Project.h"
#include <stdint.h>
#include "typedefs.h"

//###########################################################################
//
// Macro Definitions
//
//###########################################################################
#define NULL    0
#define  rfft16_unpack (fft_hnd)  rfft16_unpack_asm (fft_hnd)

#define cfft16_64P_DEFAULTS    { (int *)NULL,\
        (int *)NULL,\
        (int *)NULL,\
        64,\
        6,\
		8,\
		(int *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_64p_calc}
        
#define cfft16_64P_BREV_DEFAULTS    { (int *)NULL,\
        (int *)NULL,\
        (int *)NULL,\
        64,\
        6,\
		8,\
		BIT_REV_64_TBL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_64p_calc}

#define cfft16_128P_DEFAULTS    { (int *)NULL,\
        (int *)NULL,\
        (int *)NULL,\
        128,\
        7,\
		4,\
		(int *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_128p_calc}


#define cfft16_256P_DEFAULTS    { (int *)NULL,\
        (int *)NULL,\
        (int *)NULL,\
        256,\
        8,\
		2,\
		(int *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_256p_calc}
        
#define rfft16_128P_DEFAULTS    { (int *)NULL,\
        (int *)NULL,\
        (int *)NULL,\
		64,\
		6,\
		4,\
		(int *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_64p_calc}


#define rfft16_256P_DEFAULTS    { (int *)NULL,\
        (int *)NULL,\
        (int *)NULL,\
        128,\
        7,\
		4,\
		(int *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_128p_calc}
        
#define rfft16_512P_DEFAULTS    { (int *)NULL,\
        (int *)NULL,\
        (int *)NULL,\
        256,\
        8,\
		1,\
		(int *)NULL,\
        (void (*)(void *))cfft16_init,\
        (void (*)(void *))cfft16_256p_calc}
        
#define rifft16_64P_DEFAULTS   \
        cfft16_64P_DEFAULTS
        
#define rifft16_128P_DEFAULTS   \
        cfft16_128P_DEFAULTS
        
#define rifft16_256P_DEFAULTS   \
        cfft16_256P_DEFAULTS        
        
#define cfft16_pack(fft_hnd)	\
		cfft16_pack_asm(fft_hnd)
		
#define cfft16_unpack(fft_hnd)	\
		cfft16_unpack_asm(fft_hnd)
//###########################################################################
//
// Structures and variables definitions.
//
//###########################################################################
extern SINT16 CFFT16_64p_in_data[];				//!< Input fed into the simulator
extern SINT16 CFFT16_64p_out_data[];			//!< Output from the simulator
extern SINT16 CFFT16_64p_brev_in_data[];		//!< Input fed into the simulator
extern SINT16 CFFT16_64p_brev_out_data[];		//!< Output from the simulator
extern SINT16 CFFT16_128p_in_data[];			//!< Input fed into the simulator
extern SINT16 CFFT16_128p_out_data[];			//!< Output from the simulator
extern SINT16 CFFT16_256p_in_data[];			//!< Input fed into the simulator
extern SINT16 CFFT16_256p_out_data[];			//!< Output from the simulator
extern SINT16 RFFT16_128p_in_data[];			//!< Input fed into the simulator
extern SINT16 RFFT16_128p_out_data[];			//!< Output from the simulator
extern SINT16 RFFT16_256p_in_data[];			//!< Input fed into the simulator
extern SINT16 RFFT16_256p_out_data[];			//!< Output from the simulator
extern SINT16 RFFT16_512p_in_data[];			//!< Input fed into the simulator
extern SINT16 RFFT16_512p_out_data[];			//!< Output from the simulator
extern SINT16 RIFFT16_64p_in_data[];           //!< Input fed into the simulator
extern SINT16 RIFFT16_64p_out_data[];          //!< Output from the simulator
extern SINT16 RIFFT16_128p_in_data[];           //!< Input fed into the simulator
extern SINT16 RIFFT16_128p_out_data[];          //!< Output from the simulator
extern SINT16 RIFFT16_256p_in_data[];           //!< Input fed into the simulator
extern SINT16 RIFFT16_256p_out_data[];          //!< Output from the simulator

extern SINT16 CFFT16_TF[256];					//!< Twiddle Factor Table
extern SINT16 BIT_REV_64_TBL[64];				//!<

//! Complex FFT data structure
typedef struct {
        int *ipcbptr;                       //!< input buffer pointer
        int *workptr;                       //!< work buffer pointer
        int *tfptr;                         //!< twiddle factor table pointer
        int size;							//!< Number of data points
        int nrstage;						//!< Number of FFT stages
        int step;							//!< Twiddle factor table search step
        int *brevptr;						//!< Bit reversal table pointer
        void (*init)(void *);				//!< Function pointer to initialization routine
        void (*calc)(void *);				//!< Function pointer to calculation routine
        }cfft16_t;

typedef cfft16_t  cfft16_handle_s;			//!< Handle to structure
//###########################################################################
//
// Prototypes for the APIs.
//
//###########################################################################
extern void cfft16_init(void *);
extern void cfft16_brev(void *);
extern void cfft16_tbl_brev(void *);
extern void cfft16_flip_re_img(void *);
extern void cfft16_flip_re_img_conj(void *);
extern void cfft16_unpack_asm(void *);
extern void cifft16_pack_asm(void *);

extern void cfft16_64p_calc(void *);
extern void cfft16_128p_calc(void *);
extern void cfft16_256p_calc(void *);

//###########################################################################
//
// Mark the end of the C bindings section for C++ compilers.
//
//###########################################################################
#ifdef __cplusplus
}
#endif //__cplusplus

#endif //__FFT_H__
