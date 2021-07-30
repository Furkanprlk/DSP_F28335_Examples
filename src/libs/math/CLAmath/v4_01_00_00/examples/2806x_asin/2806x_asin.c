//#############################################################################
// Description:
//
// This example calls the arc-sine function(CLAasin) of the CLA
// math library on a test vector and compares the result to the
// equivalent "math.h" routine
//
// Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
// ALL RIGHTS RESERVED
//#############################################################################
//$TI Release: CLA Math Library V4.01.00.00 $
//$Release Date: Apr 6, 2016 $
//#############################################################################
#include <stdint.h>
#include "DSP28x_Project.h"
#include "CLAShared.h"
#include "math.h"

#define EPSILON             1e-1

// Constants
#define WAITSTEP    asm(" RPT #255||NOP")

//Global Variables
extern int16_t pass, fail;

//Task 1 (C) Variables
#ifdef __cplusplus
#pragma DATA_SECTION("CpuToCla1MsgRAM")
float fVal;
#pragma DATA_SECTION("Cla1ToCpuMsgRAM")
float fResult;
#else
#pragma DATA_SECTION(fVal,"CpuToCla1MsgRAM")
float fVal;
#pragma DATA_SECTION(fResult,"Cla1ToCpuMsgRAM")
float fResult;
#endif //__cplusplus

float y[BUFFER_SIZE];
float fError[BUFFER_SIZE];
    
//Golden Test Values
float test_values[BUFFER_SIZE] ={
  0.0000,   0.0495,   0.0988,   0.1479,   0.1966,   0.2449,   0.2925,   0.3394,
  0.3855,   0.4307,   0.4748,   0.5177,   0.5594,   0.5997,   0.6386,   0.6758,
  0.7115,   0.7453,   0.7774,   0.8076,   0.8357,   0.8619,   0.8859,   0.9078,
  0.9274,   0.9448,   0.9598,   0.9725,   0.9828,   0.9908,   0.9963,   0.9993,
  0.9999,   0.9981,   0.9938,   0.9871,   0.9780,   0.9665,   0.9526,   0.9364,
  0.9179,   0.8971,   0.8742,   0.8491,   0.8219,   0.7927,   0.7616,   0.7286,
  0.6939,   0.6574,   0.6193,   0.5798,   0.5387,   0.4964,   0.4529,   0.4082,
  0.3626,   0.3161,   0.2688,   0.2208,   0.1723,   0.1234,   0.0741,   0.0247,
 -0.0247,  -0.0741,  -0.1234,  -0.1723,  -0.2208,  -0.2688,  -0.3161,  -0.3626,
 -0.4082,  -0.4529,  -0.4964,  -0.5387,  -0.5798,  -0.6193,  -0.6574,  -0.6939,
 -0.7286,  -0.7616,  -0.7927,  -0.8219,  -0.8491,  -0.8742,  -0.8971,  -0.9179,
 -0.9364,  -0.9526,  -0.9665,  -0.9780,  -0.9871,  -0.9938,  -0.9981,  -0.9999,
 -0.9993,  -0.9963,  -0.9908,  -0.9828,  -0.9725,  -0.9598,  -0.9448,  -0.9274,
 -0.9078,  -0.8859,  -0.8619,  -0.8357,  -0.8076,  -0.7774,  -0.7453,  -0.7115,
 -0.6758,  -0.6386,  -0.5997,  -0.5594,  -0.5177,  -0.4748,  -0.4307,  -0.3855,
 -0.3394,  -0.2925,  -0.2449,  -0.1966,  -0.1479,  -0.0988,  -0.0495,  -0.0000
};

float res_expected[BUFFER_SIZE]={
  0.0000,   0.0495,   0.0989,   0.1484,   0.1979,   0.2474,   0.2968,   0.3463,
  0.3958,   0.4453,   0.4947,   0.5442,   0.5937,   0.6432,   0.6926,   0.7421,
  0.7916,   0.8411,   0.8905,   0.9400,   0.9895,   1.0390,   1.0884,   1.1379,
  1.1874,   1.2368,   1.2863,   1.3358,   1.3853,   1.4347,   1.4842,   1.5337,
  1.5584,   1.5090,   1.4595,   1.4100,   1.3605,   1.3111,   1.2616,   1.2121,
  1.1626,   1.1132,   1.0637,   1.0142,   0.9647,   0.9153,   0.8658,   0.8163,
  0.7668,   0.7174,   0.6679,   0.6184,   0.5689,   0.5195,   0.4700,   0.4205,
  0.3711,   0.3216,   0.2721,   0.2226,   0.1732,   0.1237,   0.0742,   0.0247,
 -0.0247,  -0.0742,  -0.1237,  -0.1732,  -0.2226,  -0.2721,  -0.3216,  -0.3711,
 -0.4205,  -0.4700,  -0.5195,  -0.5689,  -0.6184,  -0.6679,  -0.7174,  -0.7668,
 -0.8163,  -0.8658,  -0.9153,  -0.9647,  -1.0142,  -1.0637,  -1.1132,  -1.1626,
 -1.2121,  -1.2616,  -1.3111,  -1.3605,  -1.4100,  -1.4595,  -1.5090,  -1.5584,
 -1.5337,  -1.4842,  -1.4347,  -1.3853,  -1.3358,  -1.2863,  -1.2368,  -1.1874,
 -1.1379,  -1.0884,  -1.0390,  -0.9895,  -0.9400,  -0.8905,  -0.8411,  -0.7916,
 -0.7421,  -0.6926,  -0.6432,  -0.5937,  -0.5442,  -0.4947,  -0.4453,  -0.3958,
 -0.3463,  -0.2968,  -0.2474,  -0.1979,  -0.1484,  -0.0989,  -0.0495,  -0.0000
};

//C28 C tasks
void test_run(void)
{
    int i;
    
    for(i=0;i<BUFFER_SIZE;i++)
    {
     fVal= test_values[i];
     Cla1ForceTask1andWait();
     WAITSTEP;
     y[i] = fResult; 
    }   
}

void test_report(void)
{
    unsigned int i;
    float fErrMetric;
    for(i=0;i<BUFFER_SIZE;i++){
      fError[i] = fabs(res_expected[i]-y[i]);
      fErrMetric = fError[i];
      if( fErrMetric < EPSILON){
        pass++;
      }else{
        fail++;
      }
    }
    //if(fail) test_error(); 
}

void test_error( void )
{
    asm(" ESTOP0"); 
}
