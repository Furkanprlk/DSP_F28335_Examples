#ifndef _FPU_VECTOR_H_
#define _FPU_VECTOR_H_
//#############################################################################
//! \file   include/fpu_vector.h
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
//! \defgroup fpu_vector Vector Operations

//!
//! \addtogroup fpu_vector
// @{
    
#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#ifdef _TMS320C28XX_TMU0__
    #define abs_SP_CV  abs_SP_CV_TMU0
    #define iabs_SP_CV iabs_SP_CV_TMU0
#else
    #define abs_SP_CV  abs_SP_CV
    #define iabs_SP_CV iabs_SP_CV
#endif //_TMS320C28XX_TMU0__

//*****************************************************************************
// function prototypes
//*****************************************************************************
//! \brief Absolute Value of a Complex Vector.
//!
//! This module computes the absolute value of a complex vector. If N is even,
//! use abs_SP_CV_2() for better performance.
//! \f[y[i]&=& \sqrt(x_{re}[i]^{2} + x_{im}[i]^{2}) \f]
//! \param y pointer to the output vector
//! \param x pointer to the input vector
//! \param N length of the x and y vectors
//
extern void abs_SP_CV(float *y, const complex_float *x, const uint16_t N);

//! \brief Absolute Value of an Even Length Complex Vector.
//!
//! This module computes the absolute value of an even length complex vector.
//! \f[ y[i]&=& \sqrt(x_{re}[i]^{2} + x_{im}[i]^{2})\f]
//! \param y pointer to the output vector
//! \param x pointer to the input vector
//! \param N length of the x and y vectors
//! \attention N must be even
//
extern void abs_SP_CV_2(float *y, const complex_float *x, const uint16_t N);

//! \brief Absolute Value of a Complex Vector (TMU0).
//!
//! This module computes the absolute value of a complex vector. It uses
//! the TMU Type 0 accelerator to speed up the calculation of square roots.
//! \f[y[i]&=& \sqrt(x_{re}[i]^{2} + x_{im}[i]^{2}) \f]
//! \param y pointer to the output vector
//! \param x pointer to the input vector
//! \param N length of the x and y vectors
//! \attention 
//! -# This function is optimized for N>=8.  It is less cycle efficient
//!  when N<8.  For very small N (e.g., N=1, 2, maybe 3) the user might
//!  consider using the TMU intrinsics in the compiler instead of this
//!  function.
//
extern void abs_SP_CV_TMU0(float *y, const complex_float *x, const uint16_t N);

//! \brief Addition (Element-Wise) of a Complex Scalar to a Complex Vector.
//!
//! This module adds a complex scalar element-wise to a complex vector.
//! \f[y_{re}[i]&=& x_{re}[i] + c_{re}\f]
//! \f[y_{im}[i]&=& x_{im}[i] + c_{im}\f]
//! \param y pointer to the complex output vector
//! \param x pointer to the complex input vector
//! \param c pointer to the complex input scalar
//! \param N length of the x and y vectors
//
extern void add_SP_CSxCV(complex_float *y, const complex_float *x, 
                         const complex_float c, const uint16_t N);

//! \brief Addition of Two Complex Vectors.
//!
//! This module adds two complex vectors.
//! \f[y_{re}[i]&=& w_{re}[i] + x_{re}[i]\f]
//! \f[y_{im}[i]&=& w_{im}[i] + x_{im}[i]\f]
//! \param y pointer to the complex output vector
//! \param w pointer to the first complex input vector
//! \param x pointer to the second complex input vector
//! \param N length of the w, x and y vectors
//
extern void add_SP_CVxCV(complex_float *y, const complex_float *w,
                         const complex_float *x, const uint16_t N);

//! \brief Inverse Absolute Value of a Complex Vector.
//!
//! This module computes the inverse absolute value of a complex vector.
//! \f[y[i]&=& \frac{1}{\sqrt(x_{re}[i]^{2} + x_{im}[i]^{2})}\f]
//! \param y pointer to the output vector
//! \param x pointer to the input vector
//! \param N length of the x and y vectors
//! \attention N must be at least 2
//
extern void iabs_SP_CV(float *y, const complex_float *x, const uint16_t N);

//! \brief Inverse Absolute Value of an Even Length Complex Vector.
//!
//! This module calculates the inverse absolute value of an even
//! length complex vector.
//! \f[y[i]&=& \frac{1}{\sqrt(x_{re}[i]^{2} + x_{im}[i]^{2})}\f]
//! \param y pointer to the output vector
//! \param x pointer to the input vector
//! \param N length of the x and y vectors
//! \attention N must be even
//
extern void iabs_SP_CV_2(float *y, const complex_float *x, const uint16_t N);

//! \brief Inverse Absolute Value of a Complex Vector (TMU0).
//!
//! This module computes the inverse absolute value of a complex vector.
//! It uses the TMU Type 0 accelerator to speed up the calculation 
//! of square roots.
//! \f[y[i]&=& \frac{1}{\sqrt(x_{re}[i]^{2} + x_{im}[i]^{2})}\f]
//! \param y pointer to the output vector
//! \param x pointer to the input vector
//! \param N length of the x and y vectors
//! \attention 
//! -# This function is optimized for N>=8.  It is less cycle efficient
//! when N<8.  For very small N (e.g., N=1, 2, maybe 3) the user might
//! consider using the TMU intrinsics in the compiler instead of this
//! function.
//
extern void iabs_SP_CV_TMU0(float *y, const complex_float *x,
                            const uint16_t N);

//! \brief Multiply-and-Accumulate of a Real Vector and a Complex Vector.
//!
//! This module multiplies and accumulates a real vector and a complex vector.
//! \f[y_{re} &=& \sum(x[i]*w_{re}[i]) \f]
//! \f[y_{im} &=& \sum(x[i]*w_{im}[i]) \f]
//! \param y complex result
//! \param w pointer to the complex input vector
//! \param x pointer to the real input vector
//! \param N length of the w and x vectors
//! \attention N must be a minimum of 5
//
extern complex_float mac_SP_RVxCV(const complex_float *w,
                         const float *x, const uint16_t N);

//! \brief Multiply-and-Accumulate of a Real Vector and a Complex Vector.
//!
//! This module multiplies and accumulates a 16-bit integer real vector and a
//! floating pt. complex vector.
//! \f[y_{re} &=& sum(x[i]*w_{re}[i]) \f]
//! \f[y_{im} &=& sum(x[i]*w_{im}[i]) \f]
//! \param w pointer to the complex input vector
//! \param x pointer to the real input vector
//! \param N length of the w and x vectors
//! \return complex floating pt. accumulation result
//! \attention N must be a minimum of 5
//
extern complex_float mac_SP_i16RVxCV(const complex_float *w, const int16_t *x,
		const uint16_t N);

//! \brief Index of Maximum Value of an Even Length Real Array.
//!
//! \param x pointer to the input vector
//! \param N length of the x vector
//! \attention
//! -# N must be even
//! -# If more than one instance of the max value exists in x[], the
//! function will return the index of the first occurrence (lowest index
//! value)
//
extern uint16_t maxidx_SP_RV_2(float *x, uint16_t N);

//! \brief Mean of Real and Imaginary Parts of a Complex Vector.
//!
//! This module calculates the mean of real and imaginary parts of a
//! complex vector.
//! \f[y_{re} &=& \frac{\Sigma x_{re}}{N} \f]
//! \f[y_{im} &=& \frac{\Sigma x_{im}}{N} \f]
//! \param x pointer to the input vector
//! \param N length of the x vector
//! \attention N must be even and a minimum of 4
//
extern complex_float mean_SP_CV_2(const complex_float *x, const uint16_t N);

//! \brief Median of a Real Valued Array of Floats (Preserved Inputs).
//!
//! This module computes the median of a real valued array of
//! floats. The input array is preserved. If input array preservation is not 
//! required, use median_SP_RV() for better performance. This function calls 
//! median_SP_RV() and memcpy_fast().
//! \param x pointer to the real input vector
//! \param N length of the x vector
//! \attention This function simply makes a local copy of the input array, and
//! then calls median_SP_CV() using the copy
//! \attention The length of the copy of the input array is allocated at 
//! compile time by the constant "K" defined in the code. If the passed 
//! parameter N is greater than K, memory corruption will result.  Be sure to 
//! recompile the library with an appropriate value \f$K >= N\f$ before
//! executing this code.
//! The library uses K = 256 as the default value.
//! \attention The first stage of this function (memory copy) is not
//! interruptible.
//! \return median of the vector x
//
extern float median_noreorder_SP_RV(const float *x, uint16_t N);

//! \brief Median of a real array of floats.
//!
//! This module computes the median of a real array of floats.
//! The Input array is NOT preserved. If input array preservation
//! is required, use median_noreorder_SP_RV().
//! \param x pointer to the real input vector
//! \param N length of the x vector
//! \attention
//! -#  This function is destructive to the input array x in that it
//! will be sorted during function execution.  If this is not allowable,
//! use median_noreorder_SP_CV().
//! -# This function should be compiled with -o4, -mf5, and no -g compiler
//! options for best performance.
//! \return median of the vector x
//
extern float median_SP_RV(float *x, uint16_t N);

//! \brief Optimized Memory Copy.
//!
//! \param src pointer to the source buffer
//! \param dst pointer to the destination buffer
//! \param N size (16-bits) of the buffer to be copied
//! \attention The function checks for the case of N=0 and just returns if true
//! \attention This function is not interruptible.  Use memcpy_fast_far instead
//! for interruptibility.
//! \attention This function does not support memory above 22 bits address.
//! For input data above 22 bits address, use memcpy_fast_far instead.
//
extern void memcpy_fast(void *dst, const void *src, uint16_t N);

//! \brief Optimized Memory Set.
//!
//! \param dst pointer to the destination buffer
//! \param value value to write to all the buffer locations
//! \param N size (16-bits) of the buffer to be written
//! \attention The function checks for the case of N=0 and just returns if true
//! \attention This function is not interruptible
//
extern void memset_fast(void* dst, int16_t value, uint16_t N);

//! \brief Complex Multiply of Two Floating Point Numbers.
//!
//! This module multiplies two floating point complex values.
//! \f[y_{re} &=& w_{re}*x_{re} - w_{im}*x_{im}\f]
//! \f[y_{im} &=& w_{re}*x_{im} + w_{im}*x_{re}\f]
//! \param w First complex input
//! \param x Second complex input
//! \return complex product of the first and second complex input
//
extern complex_float mpy_SP_CSxCS(complex_float w, complex_float x);

//! \brief Complex Multiply of Two Complex Vectors.
//!
//! This module performs complex multiplication on two input complex vectors.
//! \f[y_{re}[i] &=& w_{re}[i]*x_{re}[i] - w_{im}[i]*x_{im}[i] \f]
//! \f[y_{im}[i] &=& w_{re}[i]*x_{im}[i] + w_{im}[i]*x_{re}[i] \f]
//! \param y pointer to the complex product of the first and second complex
//! vectors
//! \param w pointer to the first complex input vector
//! \param x pointer to the second complex input vector
//! \param N length of the w, x and y vectors
//
extern void mpy_SP_CVxCV(complex_float *y, const complex_float *w, 
                         const complex_float *x, const uint16_t N);

//! \brief Multiplication of a Complex Vector and the Complex Conjugate of 
//! another Vector.
//!
//! This module multiplies a complex vector (w) and the complex conjugate of 
//! another complex vector (x).
//! \f[x^{*}_{re}[i] &=& x_{re}[i]\f]
//! \f[x^{*}_{im}[i] &=& - x_{im}[i]\f]
//! \f[y_{re}[i] &=& w_{re}[i]*x_{re}[i] - w_{im}[i]*x^{*}_{im}[i]\f]
//! \f[y_{im}[i] &=& w_{re}[i]*x^{*}_{im}[i] + w_{im}[i]*x_{re}[i]\f]
//! \param y pointer to the complex product of the first and second complex
//! vectors
//! \param w pointer to the first complex input vector
//! \param x pointer to the second complex input vector
//! \param N length of the w, x and y vectors
//
extern void mpy_SP_CVxCVC(complex_float *y, const complex_float *w,
                          const complex_float *x, const uint16_t N);

//! \brief Multiplication of a Real scalar and a Real Vector.
//!
//! This module multiplies a real scalar and a real vector.
//! \f[y[i] &=& c*x[i] \f]
//! \param y pointer to the product of the scalar and a real vector
//! \param x pointer to the real input vector
//! \param c scalar multiplier
//! \param N length of the x and y vectors
//! \attention N must be even and a minimum of 4.
//
extern void mpy_SP_RSxRV_2(float *y, const float *x, const float c,
                           const uint16_t N);

//! \brief Multiplication of a Real Scalar, a Real Vector, and another Real
//! Vector.
//!
//! This module multiplies a real scalar with a real vector and another real
//! vector.
//! \f[y[i] &=& c*w[i]*x[i] \f]
//! \param y pointer to the product of the scalar and two real vectors
//! \param w pointer to the first real input vector
//! \param x pointer to the second real input vector
//! \param c scalar multiplier
//! \param N length of the w, x and y vectors
//! \attention N must be even and a minimum of 4.
//
extern void mpy_SP_RSxRVxRV_2(float *y, const float *w, const float *x,
                              const float c, const uint16_t N);

//! \brief Multiplication of a Real Vector and a Complex Vector.
//!
//! This module multiplies a real vector and a complex vector.
//! \f[y_{re}[i] &=& x[i]*w_{re}[i] \f]
//! \f[y_{im}[i] &=& x[i]*w_{im}[i] \f]
//! \param y pointer to the product of the real and complex vectors
//! \param w pointer to the complex input vector
//! \param x pointer to the real input vector
//! \param N length of the w, x and y vectors
//! \attention N must be at least 2
//
extern void mpy_SP_RVxCV(complex_float *y, const complex_float *w,
                         const float *x, const uint16_t N);

//! \brief Multiplication of a Real Vector and a Real Vector.
//!
//! This module multiplies two real vectors.
//! \f[y[i] &=& w[i]*x[i]\f]
//! \param y pointer to the product of two real vectors
//! \param w pointer to the first real input vector
//! \param x pointer to the second real input vector
//! \param N length of the w, x and y vectors
//! \attention N must be even and a minimum of 4.
//
extern void mpy_SP_RVxRV_2(float *y, const float *w, const float *x,
                           const uint16_t N);

//! \brief Sort an Array of Floats.
//!
//! This module sorts an array of floats. This function is a partially
//! optimized
//! version of qsort.c from the C28x cgtools lib qsort() v6.0.1.
//! \param x pointer to the input array
//! \param N size of the input array
//! \attention Performance is best with -o1, -mf3 compiler options
//! (cgtools v6.0.1)
//
extern void qsort_SP_RV(void *x, uint16_t N);

//! \brief Rounding (Unbiased) of a Floating Point Scalar.
//!
//! numerical examples:
//! rnd_SP_RS(+4.4) = +4.0 \\
//! rnd_SP_RS(-4.4) = -4.0 \\
//! rnd_SP_RS(+4.5) = +5.0 \\
//! rnd_SP_RS(-4.5) = -5.0 \\
//! rnd_SP_RS(+4.6) = +5.0 \\
//! rnd_SP_RS(-4.6) = -5.0 \\
//! \param x input value
//! \return rounded
//
extern float rnd_SP_RS(float x);

//! \brief Subtraction of a Complex Scalar from a Complex Vector.
//!
//! This module subtracts a complex scalar from a complex vector.
//! \f[y_{re}[i] &=& x_{re}[i] - c_{re} \f]
//! \f[y_{im}[i] &=& x_{im}[i] - c_{im} \f]
//! \param y pointer to the difference of a complex scalar from a complex
//! vector
//! \param x pointer to the complex input vector
//! \param c pointer to the complex input scalar
//! \param N length of the x and y vectors
//! \attention N must be at least 2
//
extern void sub_SP_CSxCV(complex_float *y, const complex_float *x,
                         const complex_float c, const uint16_t N);

//! \brief Subtraction of a Complex Vector and another Complex Vector.
//!
//! This module subtracts a complex vector from another complex vector.
//! \f[y_{re}[i] &=& w_{re}[i] - x_{re}[i] \f]
//! \f[y_{im}[i] &=& w_{im}[i] - x_{im}[i] \f]
//! \param y pointer to the difference of two complex vectors
//! \param w pointer to the first complex input vector
//! \param x pointer to the second complex input vector
//! \param N length of the w, x and y vectors
//! \attention N must be at least 2
//
extern void sub_SP_CVxCV(complex_float *y, const complex_float *w,
                         const complex_float *x, const uint16_t N);

// @} //addtogroup

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of _FPU_VECTOR_H_

// End of File
