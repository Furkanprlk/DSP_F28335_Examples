// TI File $Revision: /main/2 $
// Checkin $Date: Thu Jan  6 15:14:02 2011 $
// =====================================================================================
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// -------------------------------------------------------------------------------------
//          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
//                          All Rights Reserved.
//======================================================================================
/*===================================================================
File name   :   IIR.H                   
                    
Originator  :   YU CAI (ASP)
                Texas Instruments
Description:  
Header file containing  object definitions, proto type declaration and 
default object initializers for FFT modules.
===================================================================
History:
-------------------------------------------------------------------
20-3-2000   Release Rev 1.0                                                  
--------------------------------------------------------------------*/
//######################################################################################
// $TI Release: C28x Fixed Point Library v1.01 $
// $Release Date: January 11,2011 $
//######################################################################################

#ifndef __IIR_H__
#define __IIR_H__
#define     NULL    0

 
/*----------------------------------------------------------------
Define the structure of the IIR5BIQ16 Filter Module 
-----------------------------------------------------------------*/
typedef struct { 
    void (*init)(void *);   /* Ptr to Init funtion           */
    void (*calc)(void *);   /* Ptr to calc fn                */  
    int *coeff_ptr;         /* Pointer to Filter coefficient */
    int *dbuffer_ptr;       /* Delay buffer ptr              */
    int nbiq;               /* No of biquad                  */
    int input;              /* Latest Input sample           */
    int isf;                /* Input Scale Factor            */ 
    int qfmat;              /* Q format of coeff             */
    int output;             /* Filter Output                 */
    }IIR5BIQ16;    


/*---------------------------------------------------------------
Define the structure of the IIR5BIQ32 Filter Module
-----------------------------------------------------------------*/
typedef struct {
    void (*init)(void *);   /* Ptr to init fn                */
    void (*calc)(void *);   /* Ptr to calc fn                */ 
    long *coeff_ptr;        /* Pointer to Filter coefficient */
    long *dbuffer_ptr;      /* Delay buffer ptr              */
    long nbiq;               /* No of biquad                  */
    long input;              /* Latest Input sample           */
    long isf;               /* Input Scale Factor            */ 
    long output32;          /* Filter Output (Q30)           */
    int output16;           /* Filter Output (Q14)           */
    int qfmat;              /* Q format of coeff             */
    }IIR5BIQ32;            
 
/*---------------------------------------------------------------
Define a Handles for the Filter Modules
-----------------------------------------------------------------*/
typedef IIR5BIQ16     *IIR5BIQ16_handle;
typedef IIR5BIQ32     *IIR5BIQ32_handle;    
        
          
#define IIR5BIQ16_DEFAULTS { (void (*)(void *))IIR5BIQ16_init,\
             (void (*)(void *))IIR5BIQ16_calc,\
             (int *)NULL,   \
             (int *)NULL,   \
             0,             \
             0,             \
             0,             \
             0,             \
             0}    

#define IIR5BIQ32_DEFAULTS { (void (*)(void *))IIR5BIQ32_init,\
             (void (*)(void *))IIR5BIQ32_calc, \
             (long *)NULL,   \
             (long *)NULL,   \
             0,             \
             0,             \
             0,             \
             0,             \
             0,             \
             0}                           


/*-------------------------------------------------------------
 Prototypes for the functions
---------------------------------------------------------------*/
void IIR5BIQ16_calc(void *);
void IIR5BIQ32_calc(void *);

/******** Sample IIR co-efficients ****************************/
 
void IIR5BIQ16_init(IIR5BIQ16 *);
void IIR5BIQ32_init(IIR5BIQ32 *);

/* LPF co-efficients for IIR16 module	*/
// these coefficients are good
#define IIR16_LPF_COEFF {\
            0,3794,0,307,307,\
            -2159,7894,668,1335,668,\
            -3483,8904,541,1082,541,\
            -6131,10923,13364,26729,13364}

#define IIR16_LPF_ISF     4398
#define IIR16_LPF_NBIQ    4
#define IIR16_LPF_QFMAT   13

/* LPF co-efficients for IIR32 module	*/
#define IIR32_LPF_COEFF {\
            0,248624377,0,20118017,20118017,\
            -141524868,517372703,43749199,87498398,43749199,\
            -228291242,583544331,35450657,70901314,35450657,\
            -401770939,715847129,875854244,1751708488,875854244}

#define IIR32_LPF_ISF   288246535
#define IIR32_LPF_NBIQ  4
#define IIR32_LPF_QFMAT 29
 
#endif 

