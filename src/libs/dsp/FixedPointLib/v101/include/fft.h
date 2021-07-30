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
File name   :   FFT.H                   
                    
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

#ifndef __FFT_H__
#define __FFT_H__ 


#define NULL    0         
typedef struct {   
        long *ipcbptr;
        long *tfptr;               
        int size;
        int nrstage;             
        long *magptr;
        long *winptr; 
        long peakmag;
        int peakfrq;
		int ratio;
        void (*init)(void *);
        void (*izero)(void *);
        void (*calc)(void *);
        void (*mag)(void *);
        void (*win)(void *);
        }CFFT32;

typedef struct {
        int acqflag;
        int count;
        long input; 
        long *tempptr;
        long *buffptr;
        int size;
        void (*update)(void *); 
       }RFFT32_brev_RT_ACQ; 
       
typedef struct {   
        long *ipcbptr;
        long *tfptr;               
        int size;
        int nrstage;             
        long *magptr;
        long *winptr; 
        long peakmag;
        int peakfrq;
		int ratio;
        void (*init)(void *);
        void (*calc)(void *);
        void (*mag)(void *);
        void (*win)(void *);
        }RFFT32;


typedef struct {
        int acqflag;
        int count;
        long input; 
        long *tempptr;
        long *buffptr;
        int size;
        void (*update)(void *); 
        }RFFT32_ACQ;  

typedef CFFT32  CFFT32_handle;
typedef RFFT32 *RFFT32_handle;

#define CFFT32_8P_DEFAULTS    { (long *)NULL,\
        (long *)NULL,\
        8,\
        3,\
        (long *)NULL,\
        (long *)NULL,\
        0,\
        0,\
        128,\
        (void (*)(void *))FFT32_init,\
        (void (*)(void *))FFT32_izero,\
        (void (*)(void *))FFT32_calc,\
        (void (*)(void *))FFT32_mag,\
        (void (*)(void *))FFT32_win} 
        
#define CFFT32_16P_DEFAULTS    { (long *)NULL,\
        (long *)NULL,\
        16,\
        4,\
        (long *)NULL,\
        (long *)NULL,\
        0,\
        0,\
        256,\
        (void (*)(void *))FFT32_init,\
        (void (*)(void *))FFT32_izero,\
        (void (*)(void *))FFT32_calc,\
        (void (*)(void *))FFT32_mag,\
        (void (*)(void *))FFT32_win} 
//   ratio 256=4096/16    

#define CFFT32_32P_DEFAULTS    { (long *)NULL,\
        (long *)NULL,\
        32,\
        5,\
        (long *)NULL,\
        (long *)NULL,\
        0,\
        0,\
        128,\
        (void (*)(void *))FFT32_init,\
        (void (*)(void *))FFT32_izero,\
        (void (*)(void *))FFT32_calc,\
        (void (*)(void *))FFT32_mag,\
        (void (*)(void *))FFT32_win} 
//   ratio 128=4096/32  

#define CFFT32_64P_DEFAULTS    { (long *)NULL,\
        (long *)NULL,\
        64,\
        6,\
        (long *)NULL,\
        (long *)NULL,\
        0,\
        0,\
        64,\
        (void (*)(void *))FFT32_init,\
        (void (*)(void *))FFT32_izero,\
        (void (*)(void *))FFT32_calc,\
        (void (*)(void *))FFT32_mag,\
        (void (*)(void *))FFT32_win} 
//   ratio 64=4096/64
   
#define CFFT32_128P_DEFAULTS    { (long *)NULL,\
        (long *)NULL,\
        128,\
        7,\
        (long *)NULL,\
        (long *)NULL,\
        0,\
        0,\
        32,\
        (void (*)(void *))FFT32_init,\
        (void (*)(void *))FFT32_izero,\
        (void (*)(void *))FFT32_calc,\
        (void (*)(void *))FFT32_mag,\
        (void (*)(void *))FFT32_win} 
 
 
#define CFFT32_256P_DEFAULTS    { (long *)NULL,\
        (long *)NULL,\
        256,\
        8,\
        (long *)NULL,\
        (long *)NULL,\
        0,\
        0,\
        16,\
        (void (*)(void *))FFT32_init,\
        (void (*)(void *))FFT32_izero,\
        (void (*)(void *))FFT32_calc,\
        (void (*)(void *))FFT32_mag,\
        (void (*)(void *))FFT32_win} 
        
        
#define CFFT32_512P_DEFAULTS    { (long *)NULL,\
        (long *)NULL,\
        512,\
        9,\
        (long *)NULL,\
        (long *)NULL,\
        0,\
        0,\
        8,\
        (void (*)(void *))FFT32_init,\
        (void (*)(void *))FFT32_izero,\
        (void (*)(void *))FFT32_calc,\
        (void (*)(void *))FFT32_mag,\
        (void (*)(void *))FFT32_win}  
        
#define CFFT32_1024P_DEFAULTS    { (long *)NULL,\
        (long *)NULL,\
        1024,\
        10,\
        (long *)NULL,\
        (long *)NULL,\
        0,\
        0,\
        4,\
        (void (*)(void *))FFT32_init,\
        (void (*)(void *))FFT32_izero,\
        (void (*)(void *))FFT32_calc,\
        (void (*)(void *))FFT32_mag,\
        (void (*)(void *))FFT32_win}   
  

#define RFFT32_brev_RT_ACQ_DEFAULTS    { 1,\
        0,\
        0,\
        (long *)NULL,\
        (long *)NULL,\
        0,\
        (void (*)(void *))RFFT32_brev_RT}

#define RFFT32_32P_DEFAULTS    { (long *)NULL,\
        (long *)NULL,\
        32,\
        5,\
        (long *)NULL,\
        (long *)NULL,\
        0,\
        0,\
        128,\
        (void (*)(void *))FFT32_init,\
        (void (*)(void *))FFT32_calc,\
        (void (*)(void *))FFT32_mag,\
        (void (*)(void *))FFT32_win}        
        
#define RFFT32_64P_DEFAULTS    { (long *)NULL,\
        (long *)NULL,\
        64,\
        6,\
        (long *)NULL,\
        (long *)NULL,\
        0,\
        0,\
        64,\
        (void (*)(void *))FFT32_init,\
        (void (*)(void *))FFT32_calc,\
        (void (*)(void *))FFT32_mag,\
        (void (*)(void *))FFT32_win}  

#define RFFT32_128P_DEFAULTS    { (long *)NULL,\
        (long *)NULL,\
        128,\
        7,\
        (long *)NULL,\
        (long *)NULL,\
        0,\
        0,\
        32,\
        (void (*)(void *))FFT32_init,\
        (void (*)(void *))FFT32_calc,\
        (void (*)(void *))FFT32_mag,\
        (void (*)(void *))FFT32_win} 

#define RFFT32_256P_DEFAULTS    { (long *)NULL,\
        (long *)NULL,\
        256,\
        8,\
        (long *)NULL,\
        (long *)NULL,\
        0,\
        0,\
        16,\
        (void (*)(void *))FFT32_init,\
        (void (*)(void *))FFT32_calc,\
        (void (*)(void *))FFT32_mag,\
        (void (*)(void *))FFT32_win} 

#define RFFT32_512P_DEFAULTS    { (long *)NULL,\
        (long *)NULL,\
        512,\
        9,\
        (long *)NULL,\
        (long *)NULL,\
        0,\
        0,\
        8,\
        (void (*)(void *))FFT32_init,\
        (void (*)(void *))FFT32_calc,\
        (void (*)(void *))FFT32_mag,\
        (void (*)(void *))FFT32_win} 

#define RFFT32_1024P_DEFAULTS    { (long *)NULL,\
        (long *)NULL,\
        1024,\
        10,\
        (long *)NULL,\
        (long *)NULL,\
        0,\
        0,\
        4,\
        (void (*)(void *))FFT32_init,\
        (void (*)(void *))FFT32_calc,\
        (void (*)(void *))FFT32_mag,\
        (void (*)(void *))FFT32_win} 


#define RFFT32_4096P_DEFAULTS    { (long *)NULL,\
        (long *)NULL,\
        2048,\
        11,\
        (long *)NULL,\
        (long *)NULL,\
        0,\
        0,\
        2,\
        (void (*)(void *))FFT32_init,\
        (void (*)(void *))FFT32_calc,\
        (void (*)(void *))FFT32_mag,\
        (void (*)(void *))FFT32_win} 


#define FFTRACQ_DEFAULTS    { 1,\
        0,\
        0,\
        (long *)NULL,\
        (long *)NULL,\
        0,\
        (void (*)(void *))RFFT32_acq}

    
//-----------------------------------------------------------------------------
// Prototypes for the functions
//-----------------------------------------------------------------------------
void RFFT32_brev_RT(void *); 
void RFFT32_brev(long *src, long *dst, int size);
void CFFT32_brev(long *src, long *dst, int size); 
void FFT32_izero(void *);
void FFT32_win(void *); 
void FFT32_mag(void *);
void FFT32_calc(void *); 

void FFT32_init(void *);

#define HAMMING32 {\
		171798691,192019885,251855608,348856178,479050381,637108051,816558288,1010054378,1209674570,1407246388,\
		1594681219,1764305460,1909174674,2023357897,2102180457,2142415347}                     

#endif

