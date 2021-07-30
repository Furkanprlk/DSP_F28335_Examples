#ifndef _FPU_RFFT_H_
#define _FPU_RFFT_H_
//#############################################################################
//! \file   include/fpu_rfft.h
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
//! \defgroup fpu_rfft Real Fast Fourier Transforms

//!
//! \ingroup fpu_rfft
// @{
    
#ifdef __cplusplus
extern "C" {
#endif
//*****************************************************************************
// typedefs
//*****************************************************************************

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

//! Structure for the Real FFT with ADC input
typedef struct {
  uint16_t   *InBuf;    //!< Pointer to the input buffer
  void	   *Tail;       //!< Null pointer to the OutBuf of RFFT_F32_STRUCT
} RFFT_ADC_F32_STRUCT;

//! Handle to the Real FFT (with ADC input) structure
typedef RFFT_ADC_F32_STRUCT* RFFT_ADC_F32_STRUCT_Handle;

//*****************************************************************************
// globals
//*****************************************************************************
//! \brief Twiddle Factor Table for a 2048-pt (max) Real FFT
//!
extern float RFFT_f32_twiddleFactors[1020];
//*****************************************************************************
// function prototypes
//*****************************************************************************
//! \brief Real Fast Fourier Transform (RFFT).
//!
//! This routine computes the 32-bit floating-point FFT for an N-pt 
//! (\f$ N = 2^{n}, n = 5 : 10\f$)
//! Real input by using an N/2 pt complex FFT followed by an unpacking process 
//! to give the spectrum of the real input. This function will reorder the 
//! input in bit-reversed format before proceeding with the FFT. The routine 
//! uses two buffers in ping-pong fashion i.e. after each FFT stage the output 
//! and input buffers become the input and output buffers respectively for the 
//! next stage.
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The routine requires the use of two buffers, each of size N (32-bit), 
//! for computation; the input buffer must be aligned to a memory address of 
//! 2N words (16-bit). Refer to the RFFT linker command file to see an example 
//! of this.
//! -# If alignment is not possible the user can use the alternative, albeit 
//! slower, function RFFT_f32u
//! \warning This function is not re-entrant as it uses global variables to 
//! store certain parameters
//
extern void RFFT_f32(RFFT_F32_STRUCT_Handle hndRFFT_F32);

//! \brief Real FFT (Unaligned).
//!
//! This routine computes the 32-bit floating-point FFT for an N-pt 
//! (\f$ N = 2^{n}, n = 5 : 10\f$)
//! Real input by using an N/2 pt complex FFT followed by an unpacking process 
//! to give the spectrum of the real input. This function will reorder the 
//! input in bit-reversed format before proceeding with the FFT. The routine 
//! uses two buffers in ping-pong fashion i.e. after each FFT stage the output 
//! and input buffers become the input and output buffers respectively for the 
//! next stage.
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The routine requires the use of two buffers, each of size N (32-bit), 
//! for computation; the input buffer need not be aligned to a boundary
//! -# If alignment is possible it is recommended to use the faster routine, 
//! RFFT_f32
//! \warning This function is not re-entrant as it uses global variables to 
//! store certain parameters
//
extern void RFFT_f32u(RFFT_F32_STRUCT_Handle hndRFFT_F32);

//! \brief Real FFT with ADC Input.
//!
//! This routine computes the 32-bit floating-point FFT for an N-pt 
//! (\f$ N = 2^{n}, n = 5 : 10\f$)
//! Real input from the ADC by using an N/2 pt complex FFT followed by an 
//! unpacking process to give the spectrum of the real input. This function 
//! will reorder the input in bit-reversed format before proceeding with the 
//! FFT. The routine uses two buffers in ping-pong fashion i.e. after each FFT
//! stage the output and input buffers become the input and output buffers 
//! respectively for the next stage.
//! \param hndRFFT_ADC_F32 Pointer to the RFFT_ADC F32 object
//! \attention
//! -# The routine requires the use of two buffers, each of size N (32-bit), 
//! for computation; the input buffer must be aligned to a memory address of 
//! 2N words (16-bit). Refer to the RFFT linker command file to see an example 
//! of this.
//! -# If alignment is not possible the user can use the alternative, albeit 
//! slower, function RFFT_adc_f32u
//! \warning This function is not re-entrant as it uses global variables to 
//! store certain parameters
//
extern void RFFT_adc_f32(RFFT_ADC_F32_STRUCT_Handle hndRFFT_ADC_F32);

//! \brief Real FFT with ADC Input (Unaligned).
//!
//! This routine computes the 32-bit floating-point FFT for an N-pt 
//! (\f$ N = 2^{n}, n = 5 : 10\f$)
//! Real input from the ADC by using an N/2 pt complex FFT followed by an 
//! unpacking process to give the spectrum of the real input. This function 
//! will reorder the input in bit-reversed format before proceeding with the 
//! FFT. The routine uses two buffers in ping-pong fashion i.e. after each FFT
//! stage the output and input buffers become the input and output buffers 
//! respectively for the next stage.
//! \param hndRFFT_ADC_F32 Pointer to the RFFT_ADC F32 object
//! \attention
//! -# The routine requires the use of two buffers, each of size N (32-bit), 
//! for computation; the input buffer need not be aligned to any boundary.
//! -# If alignment is possible it is recommended to use the faster function 
//! RFFT_adc_f32
//! \warning This function is not re-entrant as it uses global variables to 
//! store certain parameters
//
extern void RFFT_adc_f32u(RFFT_ADC_F32_STRUCT_Handle hndRFFT_ADC_F32);

//! \brief Windowing function for the 32-bit real FFT 
//! \param pBuffer , pointer to the buffer that needs to be windowed
//! \param pWindow , pointer to the windowing table
//! \param size    , size of the buffer
//! This function applies the window to a 2N point real data buffer that
//! has already been reordered in the bit-reversed format
extern void RFFT_f32_win(float *pBuffer, float *pWindow, uint16_t size);

//! \brief Real FFT Magnitude.
//!
//! This module computes the real FFT magnitude. The output from RFFT_f32_mag
//! matches the magnitude output from the FFT found in common mathematics 
//! software and Code Composer Studio FFT graphs.
//! If instead a normalized magnitude like that performed by the fixed-point
//! TMS320C28x IQmath FFT library is required, then the RFFT_f32s_mag
//! function can be used. In fixed-point algorithms scaling is performed to
//! avoid overflowing data. Floating-point calculations do not need this 
//! scaling to avoid overflow and therefore the RFFT_f32_mag function can be
//! used instead.
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The Magnitude buffer does not require memory alignment to a boundary
//! -# For C28x devices that have the TMU0 (or higher) module, use
//! RFFT_f32_mag_TMU0() instead for better performance.
//
extern void RFFT_f32_mag(RFFT_F32_STRUCT_Handle hndRFFT_F32);

//! \brief Real FFT Magnitude (Scaled).
//!
//! This module computes the scaled real FFT magnitude. The scaling is
//! \f$\frac{1}{[2^{FFT\_STAGES-1}]}\f$, and is done to match the
//! normalization performed by the fixed-point TMS320C28x IQmath FFT library
//! for overflow avoidance. Floating-point calculations do not need this
//! scaling to avoid overflow and therefore the RFFT_f32_mag function can be
//! used instead. The output from RFFT_f32s_mag matches the magnitude
//! output from the FFT found in common mathematics software and Code Composer
//! Studio FFT graphs.
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The Magnitude buffer does not require memory alignment to a boundary
//! -# For C28x devices that have the TMU0 (or higher) module, use
//! RFFT_f32s_mag_TMU0() instead for better performance.
//
extern void RFFT_f32s_mag(RFFT_F32_STRUCT_Handle hndRFFT_F32);

//! \brief Real FFT Phase.
//!
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The Phase buffer does not require memory alignment to a boundary
//! -# For C28x devices that have the TMU0 (or higher) module, use
//! RFFT_f32_phase_TMU0() instead for better performance.
//
extern void RFFT_f32_phase(RFFT_F32_STRUCT_Handle hndRFFT_F32);

#if defined(__TMS320C28XX_TMU__)
//! \brief Real FFT Magnitude using the TMU0 module.
//!
//! This module computes the real FFT magnitude. The output from RFFT_f32_mag
//! matches the magnitude output from the FFT found in common mathematics 
//! software and Code Composer Studio FFT graphs.
//! If instead a normalized magnitude like that performed by the fixed-point
//! TMS320C28x IQmath FFT library is required, then the RFFT_f32s_mag
//! function can be used. In fixed-point algorithms scaling is performed to
//! avoid overflowing data. Floating-point calculations do not need this 
//! scaling to avoid overflow and therefore the RFFT_f32_mag function can be
//! used instead.
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The Magnitude buffer does not require memory alignment to a boundary
//! -# This function requires a C28x device with TMU0 or higher module.
//! For devices without the TMU, use RFFT_f32_mag() instead.
//
extern void RFFT_f32_mag_TMU0(RFFT_F32_STRUCT_Handle hndRFFT_F32);

//! \brief Real FFT Magnitude using the TMU0 module (Scaled).
//!
//! This module computes the scaled real FFT magnitude. The scaling is
//! \f$\frac{1}{[2^{FFT\_STAGES-1}]}\f$, and is done to match the
//! normalization performed by the fixed-point TMS320C28x IQmath FFT library
//! for overflow avoidance. Floating-point calculations do not need this 
//! scaling to avoid overflow and therefore the RFFT_f32_mag function can be
//! used instead. The output from RFFT_f32s_mag matches the magnitude
//! output from the FFT found in common mathematics software and Code Composer
//! Studio FFT graphs.
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The Magnitude buffer does not require memory alignment to a boundary
//! -# This function requires a C28x device with TMU0 or higher module.
//! For devices without the TMU, use RFFT_f32s_mag() instead.
//
extern void RFFT_f32s_mag_TMU0(RFFT_F32_STRUCT_Handle hndRFFT_F32);

//! \brief Real FFT Phase using TMU0 module.
//!
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention
//! -# The Phase buffer does not require memory alignment to a boundary
//! -# This function requires a C28x device with TMU0 or higher module.
//! For devices without the TMU, use RFFT_f32_phase() instead.
//
extern void RFFT_f32_phase_TMU0(RFFT_F32_STRUCT_Handle hndRFFT_F32);
#endif //__TMS320C28XX_TMU__

//! \brief Generate twiddle factors for the Real FFT.
//!
//! \param hndRFFT_F32 Pointer to the RFFT_F32 object
//! \attention This function is written in C and compiled without optimization 
//! turned on.
//
extern void RFFT_f32_sincostable(RFFT_F32_STRUCT_Handle hndRFFT_F32);

// @} //addtogroup

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of _FPU_RFFT_H_

// End of File

