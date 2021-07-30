#ifndef _IIR_H_
#define _IIR_H_
//#############################################################################
//! \file include/iir.h
//!
//! \brief  Header file containing  object definitions, prototype declaration 
//! and default object initializers for IIR modules.
//!
//! \date   Mar 20, 2000
//! 
//
//  Group:            C2000
//  Target Family:    C28x
//
// (C)Copyright 2014, Texas Instruments, Inc.
//#############################################################################
//$TI Release: C28x Fixed Point DSP Library V1.20.00.00 $
//$Release Date: Oct 23, 2014 $
//#############################################################################
  
//*****************************************************************************
// the includes
//*****************************************************************************
#include <stdint.h>

//! 
//! \defgroup IIR Infinite Impulse Response Filters

//!
//! \ingroup IIR
//@{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
//defines
//*****************************************************************************
#define NULL    0         

//! \brief Initialization defaults for the 16-bit IIR filter
//!
#define IIR5BIQ16_DEFAULTS {            \
    (void (*)(void *))IIR5BIQ16_init,   \
    (void (*)(void *))IIR5BIQ16_calc,   \
    (int16_t *)NULL,                    \
    (int16_t *)NULL,                    \
    0,                                  \
    0,                                  \
    0,                                  \
    0,                                  \
    0}    

//! \brief Initialization defaults for the 32-bit IIR filter
//!
#define IIR5BIQ32_DEFAULTS {            \
    (void (*)(void *))IIR5BIQ32_init,   \
    (void (*)(void *))IIR5BIQ32_calc,   \
    (int32_t *)NULL,                    \
    (int32_t *)NULL,                    \
    0,                                  \
    0,                                  \
    0,                                  \
    0,                                  \
    0,                                  \
    0}                    
//*****************************************************************************
// typedefs
//*****************************************************************************
//! \brief 16-bit IIR filter structure
//!
typedef struct { 
    void (*init)(void *);   //!< Pointer to initialization function           
    void (*calc)(void *);   //!< Pointer to calculation function                  
    int16_t *coeff_ptr;     //!< Pointer to filter coefficients
    int16_t *dbuffer_ptr;   //!< Delay buffer Pointer             
    uint16_t nbiq;          //!< Number of biquads
    int16_t input;          //!< Latest input sample          
    int16_t isf;            //!< Input scale factor            
    uint16_t qfmat;         //!< Q format of coefficients            
    int16_t output;         //!< Filter output                
}IIR5BIQ16;    

//! \brief Handle to the IIR16 object
//!
typedef IIR5BIQ16 *IIR5BIQ16_Handle;

//! \brief 32-bit IIR filter structure
//!
typedef struct {
    void (*init)(void *);   //!< Pointer to initialization function 
    void (*calc)(void *);   //!< Pointer to calculation function    
    int32_t *coeff_ptr;     //!< Pointer to filter coefficients
    int32_t *dbuffer_ptr;   //!< Delay buffer Pointer             
    uint16_t nbiq;          //!< Number of biquads
    int32_t input;          //!< Latest input sample
    int32_t isf;            //!< Input scale factor            
    int32_t output32;       //!< Filter output (Q30) 
    int16_t output16;       //!< Filter Output (Q15)
    uint16_t qfmat;         //!< Q format of coefficients  
}IIR5BIQ32;            

//! \brief Handle to the IIR32 object
//!
typedef IIR5BIQ32 *IIR5BIQ32_Handle;

                                                       
//*****************************************************************************
// the function prototypes
//*****************************************************************************
//! \brief 16-bit IIR initialization routine
//! \param pointer (handle) to IIR5BIQ16 object
//! This routine zeros out the delay elements in all the biquads
void IIR5BIQ16_init(IIR5BIQ16 *);

//! \brief 16-bit IIR calculation routine
//! \param pointer (handle) to IIR5BIQ16 object
//! This routine implements the IIR filter using cascade biquad structure
void IIR5BIQ16_calc(void *);

//! \brief 32-bit IIR initialization routine
//! \param pointer (handle) to IIR5BIQ16 object
//! This routine zeros out the delay elements in all the biquads
void IIR5BIQ32_init(IIR5BIQ32 *);

//! \brief 32-bit IIR calculation routine
//! \param pointer (handle) to IIR5BIQ32 object
//! This routine implements the IIR filter using cascade biquad structure
void IIR5BIQ32_calc(void *);

//*****************************************************************************
// Sample FIR Co-efficients
//*****************************************************************************
// LPF co-efficients for IIR16 module
#define IIR16_LPF_COEFF {       \
    0,3794,0,307,307,           \
    -2159,7894,668,1335,668,    \
    -3483,8904,541,1082,541,    \
    -6131,10923,13364,26729,13364}

#define IIR16_LPF_ISF     4398
#define IIR16_LPF_NBIQ    4
#define IIR16_LPF_QFMAT   13

// LPF co-efficients for IIR32 module
#define IIR32_LPF_COEFF {                               \
    0,248624377,0,20118017,20118017,                    \
    -141524868,517372703,43749199,87498398,43749199,    \
    -228291242,583544331,35450657,70901314,35450657,    \
    -401770939,715847129,875854244,1751708488,875854244}

#define IIR32_LPF_ISF   288246535
#define IIR32_LPF_NBIQ  4
#define IIR32_LPF_QFMAT 29

#ifdef __cplusplus
{
#endif // extern "C"
//@}  // ingroup

#endif //_IIR_H_

