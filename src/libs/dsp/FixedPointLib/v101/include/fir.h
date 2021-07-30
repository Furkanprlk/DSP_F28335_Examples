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
File name   :   FIR.H                   
                    
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

#ifndef __FIR_H__
#define __FIR_H__
#define NULL    0
 
  
/*----------------------------------------------------------------
Define the structure of the FIRFILT_GEN Filter Module 
-----------------------------------------------------------------*/
typedef struct { 
    long *coeff_ptr;        /* Pointer to Filter coefficient */
    long * dbuffer_ptr;		/* Delay buffer ptr              */
    int	cbindex;			/* Circular Buffer Index         */
    int order;              /* Order of the Filter           */
    int input;              /* Latest Input sample           */ 
    int output;             /* Filter Output                 */
    void (*init)(void *);   /* Ptr to Init funtion           */
    void (*calc)(void *);   /* Ptr to calc fn                */  
    }FIR16; 
    
typedef struct { 
    long *coeff_ptr;        /* Pointer to Filter coefficient */
    long * dbuffer_ptr;		/* Delay buffer ptr              */
    int	cbindex;			/* Circular Buffer Index         */
    int order;              /* Order of the Filter           */
    int *input;              /* Latest Input sample           */ 
    int *output;             /* Filter Output                 */
    void (*init)(void *);   /* Ptr to Init funtion           */
    void (*calc)(void *);   /* Ptr to calc fn                */  
    }FIR16_BENCHMARK;    

typedef struct { 
    long *coeff_ptr;        /* Pointer to Filter coefficient */
    long * dbuffer_ptr;		/* Delay buffer ptr              */
    int	cbindex;			/* Circular Buffer Index         */
    int order;              /* Order of the Filter           */
    long input;              /* Latest Input sample           */ 
    long output;             /* Filter Output                 */
    void (*init)(void *);   /* Ptr to Init funtion           */
    void (*calc)(void *);   /* Ptr to calc fn                */  
    }FIR32; 

typedef struct { 
    long *coeff_ptr;        /* Pointer to Filter coefficient */
    long * dbuffer_ptr;		/* Delay buffer ptr              */
    int	cbindex;			/* Circular Buffer Index         */
    int order;              /* Order of the Filter           */
    long *input;              /* Latest Input sample           */ 
    long *output;             /* Filter Output                 */
    void (*init)(void *);   /* Ptr to Init funtion           */
    void (*calc)(void *);   /* Ptr to calc fn                */  
    }FIR32_BENCHMARK; 
           
/*---------------------------------------------------------------
Define a Handles for the Filter Modules
-----------------------------------------------------------------*/
typedef FIR16 	*FIR16_handle;
typedef FIR16_BENCHMARK *FIR16_benchmark_handle;
typedef FIR32 	*FIR32_handle;
typedef FIR32_BENCHMARK *FIR32_benchmark_handle;

          
#define FIR16_DEFAULTS { (long *)NULL, \
             (long *)NULL,   \
             0,            \
             6,             \
             0,				\
             0,				\
             (void (*)(void *))FIR16_init,\
             (void (*)(void *))FIR16_calc}    

#define FIR32_DEFAULTS { (long *)NULL, \
             (long *)NULL,   \
             0,            \
             6,             \
             0,				\
             0,				\
             (void (*)(void *))FIR32_init,\
             (void (*)(void *))FIR32_calc} 
             
#define FIR16_DEFAULTS_BENCHMARK { (long *)NULL, \
             (long *)NULL,   \
             0,            \
             32,             \
             (int *)NULL,	\
             (int *)NULL,	\
             (void (*)(void *))FIR16_init,\
             (void (*)(void *))FIR16_calc_benchmark}  

#define FIR32_DEFAULTS_BENCHMARK { (long *)NULL, \
             (long *)NULL,   \
             0,            \
             32,             \
             (long *)NULL,	\
             (long *)NULL,	\
             (void (*)(void *))FIR32_init,\
             (void (*)(void *))FIR32_calc_benchmark}  
                                                       
/*-------------------------------------------------------------
 Prototypes for the functions
---------------------------------------------------------------*/
void FIR16_calc(void *);
void FIR16_calc_benchmark(void *);
void FIR16_init(void *);
void FIR16_init_benchmark(void *);
void FIR32_calc(void *);
void FIR32_calc_benchmark(void *);
void FIR32_init(void *);
void FIR32_init_benchmark(void *);

/*********** Sample FIR Co-efficients **************************/
/* Even Order (50): LPF co-efficients for FIR16 module	*/

const int FIR16_LPF6_TEST[6]={-3368,    347,  17612,  17612,    347,  -3368};

const int FIR16_LPF7_TEST[7]={-891,  -4096,   9083,  21178,   9083,  -4096,   -891};


const int FIR16_LPF8_TEST[8]={-1699,  -3664,   5174,  14555,  14555,   5174,  -3664,  -1699};

const int FIR16_LPF16_TEST[16]={ -384,-774,947,1166,-1768,-2686,4783,14680,14680,\
								4783,-2686,-1768,1166,947,-774,-384};

const int FIR16_LPF32_TEST[32]={
      -31,    -61,     92,    122,   -186,   -248,    348,    449,   -607,
     -778,   1043,   1370,  -1909,  -2789,   4835,  14710,  14710,   4835,
    -2789,  -1909,   1370,   1043,   -778,   -607,    449,    348,   -248,
     -186,    122,     92,    -61,    -31
};
								
const int FIR16_LPF64_TEST[64] = {\
        0,     -1,      1,      2,     -4,     -5,      9,     12,    -18,\
      -23,     33,     42,    -58,    -73,     96,    118,   -153,   -185,\
      234,    281,   -350,   -418,    516,    619,   -765,   -931,   1173,\
     1490,  -1999,  -2863,   4872,  14729,  14729,   4872,  -2863,  -1999,\
     1490,   1173,   -931,   -765,    619,    516,   -418,   -350,    281,\
      234,   -185,   -153,    118,     96,    -73,    -58,     42,     33,\
      -23,    -18,     12,      9,     -5,     -4,      2,      1,     -1,\
        0
};

const int FIR16_LPF128_TEST[128]={\
	        0,      0,      0,      0,      0,      0,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,      0,
        1,      1,     -1,     -1,      2,      2,     -3,     -4,      5,
        7,     -9,    -10,     13,     16,    -20,    -24,     30,     35,
      -43,    -50,     60,     70,    -83,    -96,    114,    130,   -154,
     -175,    205,    233,   -271,   -308,    357,    406,   -472,   -540,
      630,    730,   -864,  -1025,   1252,   1561,  -2050,  -2905,   4894,
    14739,  14739,   4894,  -2905,  -2050,   1561,   1252,  -1025,   -864,
      730,    630,   -540,   -472,    406,    357,   -308,   -271,    233,
      205,   -175,   -154,    130,    114,    -96,    -83,     70,     60,
      -50,    -43,     35,     30,    -24,    -20,     16,     13,    -10,
       -9,      7,      5,     -4,     -3,      2,      2,     -1,     -1,
        1,      1,      0,      0,      0,      0,      0,      0,      0,
        0,      0,      0,      0,      0,      0,      0,      0,      0,
        0,      0
};

#define FIR32_LPF8_TEST{\
	    -111375369,  -240131315,   339092334,   953892485,   953892485,   339092334,\
    -240131315,  -111375369}

#define FIR32_LPF16_TEST{\
	     -25182461,   -50721385,    62039612,    76411275,  -115843051,  -176061088,\
     313474543,   962062071,   962062071,   313474543,  -176061088,  -115843051,\
      76411275,    62039612,   -50721385,   -25182461}

#define FIR32_LPF32_TEST{\
	-2013465,-3972436,     6056023,     8015159,   -12191477,   -16239507,\
	22805854,    29416457,-39784147,-51018844,68331981,89804355,-125125486,\
	-182784383,   316867161,   964016297,   964016297,   316867161,-182784383,\
	-125125486,    89804355,    68331981,   -51018844,   -39784147,29416457,\
	22805854,   -16239507,   -12191477,     8015159,     6056023,-3972436,    -2013465}
	
#define FIR32_LPF64_TEST{\
	        -18910,      -37101,       84245,      128335,     -238598,     -340733,\
        559705,      760957,    -1155143,    -1515843,     2173955,     2775512,\
      -3811543,    -4761214,     6318472,     7757046,   -10017173,   -12135127,\
      15340013,    18414170,   -22919849,   -27400773,    33814288,    40552606,\
     -50113660,   -61039555,    76903839,    97663515,  -130983784,  -187613868,\
     319323094,   965268202,   965268202,   319323094,  -187613868,  -130983784,\
      97663515,    76903839,   -61039555,   -50113660,    40552606,    33814288,\
     -27400773,   -22919849,    18414170,    15340013,   -12135127,   -10017173,\
       7757046,     6318472,    -4761214,    -3811543,     2775512,     2173955,\
      -1515843,    -1155143,      760957,      559705,     -340733,     -238598,\
        128335,       84245,      -37101,      -18910}
						
#endif 

