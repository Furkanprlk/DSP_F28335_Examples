#ifndef _FPU_CFFT_H_
#define _FPU_CFFT_H_
//#############################################################################
//! \file   include/fpu_cfft.h
//!
//! \brief  Prototypes and Definitions for the C28x FPU Library
//! \author Vishal Coelho
//! \date   n/a
//
//  Group: 			C2000
//  Target Family:	F2837x
//
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/ 
// ALL RIGHTS RESERVED 
//#############################################################################
//$TI Release: C28x Floating Point Unit Library V1.50.00.00 $
//$Release Date: Jun 2, 2015 $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "fpu_types.h"

//!
//! \defgroup fpu_cfft Complex Fast Fourier Transforms

//!
//! \addtogroup fpu_cfft
// @{
    
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// typedefs
//*****************************************************************************
//! Complex FFT structure
typedef struct {
	float	*InPtr;			//!< Pointer to the input buffer
	float	*OutPtr;		//!< Pointer to the output buffer
	float	*CoefPtr;		//!< Pointer to the twiddle factors
	float	*CurrentInPtr;  //!< Points to input buffer at each FFT stage
	float	*CurrentOutPtr; //!< Points to output buffer at each FFT stage
	uint16_t	Stages;     //!< Number of FFT stages
	uint16_t  FFTSize;      //!< Size of the FFT (number of complex data points)
}CFFT_F32_STRUCT;

//! Handle to the CFFT_F32 structure
//
typedef CFFT_F32_STRUCT* CFFT_F32_STRUCT_Handle;

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief Twiddle Factor Table for a 1024-pt (max) Complex FFT
//!
extern float CFFT_f32_twiddleFactors[1536];

//*****************************************************************************
// function prototypes
//*****************************************************************************
//! \brief Complex Fast Fourier Transform.
//! 
//! This routine computes the 32-bit floating-point FFT for an N-pt 
//! (\f$ N = 2^{n}, n = 5 : 10\f$) complex input. This function will reorder 
//! the input in bit-reversed format before proceeding with the FFT. The 
//! routine uses two buffers in ping-pong fashion i.e. after each FFT stage the
//! output and input buffers become the input and output buffers respectively 
//! for the next stage. The CFFT_F32 object uses two pointers, CurrentInPtr 
//! and CurrentOutPtr to keep track of the switching. The user can determine
//! the address of the final output by looking at the CurrentOutPtr.
//! \param hndCFFT_F32 Pointer to the CFFT_F32 object
//! \attention
//! -# The routine requires the use of two buffers, each of size 2N (32-bit), 
//! for computation; the input buffer must be aligned to a memory address of
//! 4N words (16-bit). Refer to the CFFT linker command file to see an example
//! of this.
//! -# If alignment is not possible the user can use the alternative, albeit 
//! slower, function CFFT_f32u
//! \warning This function is not re-entrant as it uses global variables to
//! store certain parameters
//
extern void CFFT_f32(CFFT_F32_STRUCT_Handle hndCFFT_F32);

//! \brief Complex Fast Fourier Transform using a statically generated twiddle
//! factor table
//!
//! This routine computes the 32-bit floating-point FFT for an N-pt
//! (\f$ N = 2^{n}, n = 5 : 10\f$) complex input. This function will reorder
//! the input in bit-reversed format before proceeding with the FFT. The
//! routine uses two buffers in ping-pong fashion i.e. after each FFT stage the
//! output and input buffers become the input and output buffers respectively
//! for the next stage. The CFFT_F32 object uses two pointers, CurrentInPtr
//! and CurrentOutPtr to keep track of the switching. The user can determine
//! the address of the final output by looking at the CurrentOutPtr.
//! \param hndCFFT_F32 Pointer to the CFFT_F32 object
//! \attention
//! -# The routine requires the use of two buffers, each of size 2N (32-bit),
//! for computation; the input buffer must be aligned to a memory address of
//! 4N words (16-bit). Refer to the CFFT linker command file to see an example
//! of this.
//! -# If alignment is not possible the user can use the alternative, albeit
//! slower, function CFFT_f32u
//! \warning This function is not re-entrant as it uses global variables to
//! store certain parameters
//
extern void CFFT_f32t(CFFT_F32_STRUCT_Handle hndCFFT_F32);

//! \brief Complex Fast Fourier Transform (Unaligned).
//!
//! This routine computes the 32-bit floating-point FFT for an N-pt
//! (\f$ N = 2^{n}, n = 5 : 10\f$) complex input. This function will reorder
//! the input in bit-reversed format before proceeding with the FFT. The
//! routine uses two buffers in ping-pong fashion i.e. after each FFT stage the
//! output and input buffers become the input and output buffers respectively
//! for the next stage. The CFFT_F32 object uses two pointers, CurrentInPtr
//! and CurrentOutPtr to keep track of the switching. The user can determine
//! the address of the final output by looking at the CurrentOutPtr.
//! \param hndCFFT_F32 Pointer to the CFFT_F32 object
//! \attention
//! -# The routine requires the use of two buffers, each of size 2N (32-bit),
//! for computation; the input buffer need not be aligned to any boundary.
//! -# If alignment is possible the user can use the faster routine, CFFT_f32
//! \warning This function is not re-entrant as it uses global variables to
//! store certain parameters
//
extern void CFFT_f32u(CFFT_F32_STRUCT_Handle hndCFFT_F32);

//! \brief Complex Fast Fourier Transform (Unaligned) using a statically
//! generated twiddle factor table.
//!
//! This routine computes the 32-bit floating-point FFT for an N-pt
//! (\f$ N = 2^{n}, n = 5 : 10\f$) complex input. This function will reorder
//! the input in bit-reversed format before proceeding with the FFT. The
//! routine uses two buffers in ping-pong fashion i.e. after each FFT stage the
//! output and input buffers become the input and output buffers respectively
//! for the next stage. The CFFT_F32 object uses two pointers, CurrentInPtr
//! and CurrentOutPtr to keep track of the switching. The user can determine
//! the address of the final output by looking at the CurrentOutPtr.
//! \param hndCFFT_F32 Pointer to the CFFT_F32 object
//! \attention
//! -# The routine requires the use of two buffers, each of size 2N (32-bit),
//! for computation; the input buffer need not be aligned to any boundary.
//! -# If alignment is possible the user can use the faster routine, CFFT_f32
//! \warning This function is not re-entrant as it uses global variables to
//! store certain parameters
//
extern void CFFT_f32ut(CFFT_F32_STRUCT_Handle hndCFFT_F32);

//! \brief Generate twiddle factors for the Complex FFT
//!
//! \param hndCFFT_F32 Pointer to the CFFT_F32 object
//! \attention This function is written in C and compiled without optimization 
//! turned on.
//
extern void CFFT_f32_sincostable(CFFT_F32_STRUCT_Handle hndCFFT_F32);

//! \brief Windowing function for the 32-bit complex FFT 
//! \param pBuffer , pointer to the buffer that needs to be windowed
//! \param pWindow , pointer to the windowing table
//! \param size    , size of the buffer
//! This function applies the window to only the real portion of the N point
//! complex buffer that has already been reordered in the bit-reversed format
extern void CFFT_f32_win(float *pBuffer, float *pWindow, uint16_t size); 

//! \brief Windowing function for the 32-bit complex FFT 
//! \param pBuffer , pointer to the buffer that needs to be windowed
//! \param pWindow , pointer to the windowing table
//! \param size    , size of the buffer
//! This function applies the window to both the real and imaginary parts of
//! the input complex buffer that has already been reordered in the 
//! bit-reversed format
extern void CFFT_f32_win_dual(float *pBuffer, float *pWindow, uint16_t size); 

//! \brief Complex FFT Magnitude.
//!
//! This module computes the complex FFT magnitude. The output from 
//! CFFT_f32_mag matches the magnitude output from the FFT found in common 
//! mathematics software and Code Composer Studio FFT graphs.
//! If instead a normalized magnitude like that performed by the fixed-point
//! TMS320C28x IQmath FFT library is required, then the CFFT_f32s_mag function
//! can be used. In fixed-point algorithms scaling is performed to avoid 
//! overflowing data.
//! Floating-point calculations do not need this scaling to avoid overflow and 
//! therefore the CFFT_f32_mag function can be used instead.
//! \param hndCFFT_F32 Pointer to the CFFT_F32 object
//! \attention
//! -# The Magnitude buffer does not require memory alignment to a boundary
//! -# For C28x devices that have the TMU0 (or higher) module, use
//! CFFT_f32_mag_TMU0() instead for better performance.
//
extern void CFFT_f32_mag(CFFT_F32_STRUCT_Handle hndCFFT_F32);

//! \brief Complex FFT Magnitude (Scaled).
//!
//! This module computes the scaled complex FFT magnitude. The scaling is
//! \f$\frac{1}{[2^{FFT\_STAGES-1}]}\f$, and is done to match the normalization
//! performed by the fixed-point TMS320C28x IQmath FFT library for overflow
//! avoidance. Floating-point calculations do not need this scaling to avoid
//! overflow and therefore the CFFT_f32_mag function can be used instead. The
//! output from CFFT_f32s_mag matches the magnitude output from the FFT found
//! in common mathematics software and Code Composer Studio FFT graphs.
//! \param hndCFFT_F32 Pointer to the CFFT_F32 object
//! \attention
//! -# The Magnitude buffer does not require memory alignment to a boundary
//! -# For C28x devices that have the TMU0 (or higher) module, use
//! CFFT_f32s_mag_TMU0() instead for better performance.
//
extern void CFFT_f32s_mag(CFFT_F32_STRUCT_Handle hndCFFT_F32);

//! \brief Complex FFT Phase.
//!
//! \param hndCFFT_F32 Pointer to the CFFT_F32 object
//! \attention
//! -# The Phase buffer does not require memory alignment to a boundary
//! -# The phase function calls the atan2 function in the runtime-support
//! library. The phase function has not been optimized at this time.
//! -# The use of the atan2 function in the FPUfastRTS library will speed up
//! this routine. The example for the CFFT has an alternate build configuration
//! (Debug_FASTRTS) where the rts2800_fpu32_fast_supplement.lib is used in
//! place of the standard runtime library rts2800_fpu32.lib.
//! -# For C28x devices that have the TMU0 (or higher) module, use
//! CFFT_f32_phase_TMU0() instead for better performance.
//
extern void CFFT_f32_phase(CFFT_F32_STRUCT_Handle hndCFFT_F32);

#if defined(__TMS320C28XX_TMU__)
//! \brief Complex FFT Magnitude using the TMU0 module.
//!
//! This module computes the complex FFT magnitude. The output from 
//! CFFT_f32_mag matches the magnitude output from the FFT found in common 
//! mathematics software and Code Composer Studio FFT graphs.
//! If instead a normalized magnitude like that performed by the fixed-point
//! TMS320C28x IQmath FFT library is required, then the CFFT_f32s_mag function
//! can be used. In fixed-point algorithms scaling is performed to avoid 
//! overflowing data.
//! Floating-point calculations do not need this scaling to avoid overflow and 
//! therefore the CFFT_f32_mag function can be used instead.
//! \param hndCFFT_F32 Pointer to the CFFT_F32 object
//! \attention
//! -# The Magnitude buffer does not require memory alignment to a boundary
//! -# This function requires a C28x device with TMU0 or higher module.
//! For devices without the TMU, use CFFT_f32_mag() instead.
//
extern void CFFT_f32_mag_TMU0(CFFT_F32_STRUCT_Handle hndCFFT_F32);

//! \brief Complex FFT Magnitude using the TMU0 module (Scaled).
//!
//! This module computes the scaled complex FFT magnitude. The scaling is
//! \f$\frac{1}{[2^{FFT\_STAGES-1}]}\f$, and is done to match the normalization
//! performed by the fixed-point TMS320C28x IQmath FFT library for overflow 
//! avoidance. Floating-point calculations do not need this scaling to avoid 
//! overflow and therefore the CFFT_f32_mag function can be used instead. The 
//! output from CFFT_f32s_mag matches the magnitude output from the FFT found 
//! in common mathematics software and Code Composer Studio FFT graphs.
//! \param hndCFFT_F32 Pointer to the CFFT_F32 object
//! \attention
//! -# The Magnitude buffer does not require memory alignment to a boundary
//! -# The magnitude calculation calls the sqrt function within the 
//! runtime-support library. The magnitude function has not been optimized at 
//! this time.
//! -# The use of the sqrt function in the FPUfastRTS library will speed up 
//! this routine. The example for the CFFT has an alternate build configuration 
//! (Debug_FASTRTS) where the rts2800_fpu32_fast_supplement.lib is used in 
//! place of the standard runtime library rts2800_fpu32.lib.
//! -# This function requires a C28x device with TMU0 or higher module.
//! For devices without the TMU, use CFFT_f32s_mag() instead.
//
extern void CFFT_f32s_mag_TMU0(CFFT_F32_STRUCT_Handle hndCFFT_F32);

//! \brief Complex FFT Phase using the TMU0 module.
//!
//! \param hndCFFT_F32 Pointer to the CFFT_F32 object
//! \attention
//! -# The Phase buffer does not require memory alignment to a boundary
//! -# The phase function calls the atan2 function in the runtime-support 
//! library. The phase function has not been optimized at this time.
//! -# The use of the atan2 function in the FPUfastRTS library will speed up 
//! this routine. The example for the CFFT has an alternate build configuration 
//! (Debug_FASTRTS) where the rts2800_fpu32_fast_supplement.lib is used in 
//! place of the standard runtime library rts2800_fpu32.lib.
//! -# This function requires a C28x device with TMU0 or higher module.
//! For devices without the TMU, use CFFT_f32_phase() instead.
//
extern void CFFT_f32_phase_TMU0(CFFT_F32_STRUCT_Handle hndCFFT_F32);
#endif // __TMS320C28XX_TMU__

//! \example Test_FPU_CFFTF32.c An example showing the initialization of the 
//! structures and execution of the complex FFT routine (along with magnitude 
//! and phase) available in this library

//! \brief Inverse Complex FFT.
//!
//! This routine computes the 32-bit floating-point Inverse FFT for an N-pt 
//! (\f$ N = 2^{n}, n = 5 : 10\f$) complex input. It uses the forward FFT to do
//!  this by first swapping the real and imaginary parts of the input, running
//! the forward FFT and then swapping the real and imaginary parts of the
//! output to get the final answer. The routine uses two buffers in ping-pong
//! fashion i.e. after each FFT stage the output and input buffers become the
//! input and output buffers respectively for the next stage. The CFFT_F32
//! object uses two pointers, CurrentInPtr and CurrentOutPtr to keep track of
//! the switching. The user can determine the address of the final output by
//! looking at the CurrentOutPtr.
//! \param hndCFFT_F32 Pointer to the CFFT_F32 object
//! \attention
//! -# The routine requires the use of two buffers, each of size 2N (32-bit), 
//! for computation; the input buffer must be aligned to a memory address of
//! 4N words (16-bit). Refer to the ICFFT linker command file to see an
//! example of this.
//
extern void ICFFT_f32(CFFT_F32_STRUCT_Handle hndCFFT_F32);

//! \brief Inverse Complex FFT using a statically generated twiddle
//! factor table
//!
//! This routine computes the 32-bit floating-point Inverse FFT for an N-pt
//! (\f$ N = 2^{n}, n = 5 : 10\f$) complex input. It uses the forward FFT to do
//!  this by first swapping the real and imaginary parts of the input, running
//! the forward FFT and then swapping the real and imaginary parts of the
//! output to get the final answer. The routine uses two buffers in ping-pong
//! fashion i.e. after each FFT stage the output and input buffers become the
//! input and output buffers respectively for the next stage. The CFFT_F32
//! object uses two pointers, CurrentInPtr and CurrentOutPtr to keep track of
//! the switching. The user can determine the address of the final output by
//! looking at the CurrentOutPtr.
//! \param hndCFFT_F32 Pointer to the CFFT_F32 object
//! \attention
//! -# The routine requires the use of two buffers, each of size 2N (32-bit),
//! for computation; the input buffer must be aligned to a memory address of
//! 4N words (16-bit). Refer to the ICFFT linker command file to see an
//! example of this.
//
extern void ICFFT_f32t(CFFT_F32_STRUCT_Handle hndCFFT_F32);

// @} //addtogroup

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of _FPU_CFFT_H_

// End of File

