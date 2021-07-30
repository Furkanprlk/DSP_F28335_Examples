//###########################################################################
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// ------------------------------------------------------------------------
//          Copyright (C) 2014 Texas Instruments, Incorporated.
//                          All Rights Reserved.
// ==========================================================================
//
// FILE:   fpu_rfft.h
//
// TITLE:  Prototypes and Definitions for the C28x FPU Library
//
//###########################################################################
// $TI Release: C28x Floating Point Unit Library V1.40.00.00 $
// $Release Date: Mar 10, 2014 $
//###########################################################################

#ifndef _FPU_RFFT_H_
#define _FPU_RFFT_H_

#include "fpu_types.h"

//! \defgroup fpu_rfft Real Fast Fourier Transforms

#ifdef __cplusplus
extern "C" {
#endif
//-----------------------------------------------------------------------------
// Definitions and Prototypes
//-----------------------------------------------------------------------------

//!
//! \addtogroup fpu_rfft
// @{

//! Structure for the Real FFT
typedef struct {
  float  *InBuf;		//!< Pointer to the input buffer
  float  *OutBuf;		//!< Pointer to the output buffer
  float  *CosSinBuf;    //!< Pointer to the twiddle factors
  float  *MagBuf;       //!< Pointer to the magnitude buffer
  float  *PhaseBuf;     //!< Pointer to the phase buffer
  uint16_t   FFTSize;   //!< Size of the FFT (number of real data points)
  uint16_t   FFTStages; //!< Number of FFT stages
} RFFT_F32_STRUCT;

//! Handle to the Real FFT object
typedef RFFT_F32_STRUCT* RFFT_F32_STRUCT_Handle;

//! Real FFT Object. The user must define this in the application
extern RFFT_F32_STRUCT RFFT_32;

//! Structure for the Real FFT with ADC input
typedef struct {
  uint16_t   *InBuf;    //!< Pointer to the input buffer
  void	   *Tail;       //!< Null pointer to the OutBuf of RFFT_F32_STRUCT
} RFFT_ADC_F32_STRUCT;

//! Handle to the Real FFT (with ADC input) structure
typedef RFFT_ADC_F32_STRUCT* RFFT_ADC_F32_STRUCT_Handle;

//! Real FFT (with ADC input) object
extern RFFT_ADC_F32_STRUCT RFFT_ADC_F32;

//! \brief Real FFT.
//!
//! This routine computes the 32-bit floating-point FFT for an N-pt (\f$ N = 2^{n}, n = 5 : 10\f$)
//! Real input by using an N/2 pt complex FFT followed by an unpacking process to give the spectrum of
//! the real input. This function will reorder the input in bit-reversed format before proceeding with
//! the FFT. The routine uses two buffers in ping-pong fashion i.e. after each FFT stage the output and
//! input buffers become the input and output buffers respectively for the next stage.
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The routine requires the use of two buffers, each of size N (32-bit), for computation; the input
//! buffer must be aligned to a memory address of 2N words (16-bit). Refer to the RFFT linker command
//! file to see an example of this.
//! -# If alignment is not possible the user can use the alternative, albeit slower, function RFFT_f32u
//! \warning This function is not re-entrant as it uses global variables to store certain parameters
//
extern void RFFT_f32(RFFT_F32_STRUCT_Handle hndRFFT_F32);                // Real FFT, aligned input

//! \brief Real FFT (Unaligned).
//!
//! This routine computes the 32-bit floating-point FFT for an N-pt (\f$ N = 2^{n}, n = 5 : 10\f$)
//! Real input by using an N/2 pt complex FFT followed by an unpacking process to give the spectrum of
//! the real input. This function will reorder the input in bit-reversed format before proceeding with
//! the FFT. The routine uses two buffers in ping-pong fashion i.e. after each FFT stage the output and
//! input buffers become the input and output buffers respectively for the next stage.
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The routine requires the use of two buffers, each of size N (32-bit), for computation; the input
//! buffer need not be aligned to a boundary
//! -# If alignment is possible it is recommended to use the faster routine, RFFT_f32
//! \warning This function is not re-entrant as it uses global variables to store certain parameters
//
extern void RFFT_f32u(RFFT_F32_STRUCT_Handle hndRFFT_F32);               // Real FFT, unaligned input

//! \brief Real FFT with ADC Input.
//!
//! This routine computes the 32-bit floating-point FFT for an N-pt (\f$ N = 2^{n}, n = 5 : 10\f$)
//! Real input from the ADC by using an N/2 pt complex FFT followed by an unpacking process to give
//! the spectrum of the real input. This function will reorder the input in bit-reversed format before
//! proceeding with the FFT. The routine uses two buffers in ping-pong fashion i.e. after each FFT
//! stage the output and input buffers become the input and output buffers respectively for the next
//! stage.
//! \param hndRFFT_ADC_F32 Pointer to the RFFT_ADC F32 object
//! \attention
//! -# The routine requires the use of two buffers, each of size N (32-bit), for computation; the input
//! buffer must be aligned to a memory address of 2N words (16-bit). Refer to the RFFT linker command
//! file to see an example of this.
//! -# If alignment is not possible the user can use the alternative, albeit slower, function RFFT_adc_f32u
//! \warning This function is not re-entrant as it uses global variables to store certain parameters
//
extern void RFFT_adc_f32(RFFT_ADC_F32_STRUCT_Handle hndRFFT_ADC_F32);        // Real FFT with adc input, aligned input

//! \brief Real FFT with ADC Input (Unaligned).
//!
//! This routine computes the 32-bit floating-point FFT for an N-pt (\f$ N = 2^{n}, n = 5 : 10\f$)
//! Real input from the ADC by using an N/2 pt complex FFT followed by an unpacking process to give
//! the spectrum of the real input. This function will reorder the input in bit-reversed format before
//! proceeding with the FFT. The routine uses two buffers in ping-pong fashion i.e. after each FFT
//! stage the output and input buffers become the input and output buffers respectively for the next
//! stage.
//! \param hndRFFT_ADC_F32 Pointer to the RFFT_ADC F32 object
//! \attention
//! -# The routine requires the use of two buffers, each of size N (32-bit), for computation; the input
//! buffer need not be aligned to any boundary.
//! -# If alignment is possible it is recommended to use the faster function RFFT_adc_f32
//! \warning This function is not re-entrant as it uses global variables to store certain parameters
//
extern void RFFT_adc_f32u(RFFT_ADC_F32_STRUCT_Handle hndRFFT_ADC_F32);		// Real FFT with adc input, unaligned input

//! \brief Real FFT Magnitude.
//!
//! This module computes the real FFT magnitude. The output from RFFT_f32_mag
//! matches the magnitude output from the FFT found in common mathematics software
//! and Code Composer Studio FFT graphs.
//! If instead a normalized magnitude like that performed by the fixed-point
//! TMS320C28x IQmath FFT library is required, then the RFFT_f32s_mag
//! function can be used. In fixed-point algorithms scaling is performed to
//! avoid overflowing data. Floating-point calculations do not need this scaling
//! to avoid overflow and therefore the RFFT_f32_mag function can be
//! used instead.
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The Magnitude buffer does not require memory alignment to a boundary
//! -# The magnitude calculation calls the sqrt function within the runtime-support
//! library. The magnitude function has not been optimized at this time.
//! -# The use of the sqrt function in the FPUfastRTS library will speed up this
//! routine. The example for the CFFT has an alternate build configuration (Debug_FASTRTS)
//! where the rts2800_fpu32_fast_supplement.lib is used in place of the standard
//! runtime library rts2800_fpu32.lib.
//
extern void RFFT_f32_mag(RFFT_F32_STRUCT_Handle hndRFFT_F32);            // Real FFT, magnitude

//! \brief Real FFT Magnitude (Scaled).
//!
//! This module computes the scaled real FFT magnitude. The scaling is
//! \f$\frac{1}{[2^{FFT\_STAGES-1}]}\f$, and is done to match the
//! normalization performed by the fixed-point TMS320C28x IQmath FFT library
//! for overflow avoidance. Floating-point calculations do not need this scaling
//! to avoid overflow and therefore the RFFT_f32_mag function can be
//! used instead. The output from RFFT_f32s_mag matches the magnitude
//! output from the FFT found in common mathematics software and Code Composer
//! Studio FFT graphs.
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The Magnitude buffer does not require memory alignment to a boundary
//! -# The magnitude calculation calls the sqrt function within the runtime-support
//! library. The magnitude function has not been optimized at this time.
//! -# The use of the sqrt function in the FPUfastRTS library will speed up this
//! routine. The example for the CFFT has an alternate build configuration (Debug_FASTRTS)
//! where the rts2800_fpu32_fast_supplement.lib is used in place of the standard
//! runtime library rts2800_fpu32.lib.
//
extern void RFFT_f32s_mag(RFFT_F32_STRUCT_Handle hndRFFT_F32);           // Real FFT, scaled magnitude

//! \brief Real FFT Phase.
//!
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The Phase buffer does not require memory alignment to a boundary
//! -# The phase function calls the atan2 function in the runtime-support library.
//! The phase function has not been optimized at this time.
//! -# The use of the atan2 function in the FPUfastRTS library will speed up this
//! routine. The example for the CFFT has an alternate build configuration (Debug_FASTRTS)
//! where the rts2800_fpu32_fast_supplement.lib is used in place of the standard
//! runtime library rts2800_fpu32.lib.
//
extern void RFFT_f32_phase(RFFT_F32_STRUCT_Handle hndRFFT_F32);          // Real FFT, phase

//! \brief Generate twiddle factors for the Real FFT.
//!
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention This function is written in C and compiled without optimization turned on.
//
extern void RFFT_f32_sincostable(RFFT_F32_STRUCT_Handle hndRFFT_F32);    // Real FFT, twiddle calculation

// @} //addtogroup

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of _FPU_RFFT_H_

//===========================================================================
// End of file.
//===========================================================================

