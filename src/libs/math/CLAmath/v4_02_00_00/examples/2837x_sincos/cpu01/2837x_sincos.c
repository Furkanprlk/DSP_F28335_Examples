//#############################################################################
// Description:
//
// This example calls the sine function(CLAsincos) of the CLA
// math library on a test vector and compares the result to the
// equivalent "math.h" routine
//
// Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
// ALL RIGHTS RESERVED
//#############################################################################
//$TI Release: CLA Math Library V4.02.00.00 $
//$Release Date: Oct 3, 2016 $
//#############################################################################
#include <stdint.h>
#include "F28x_Project.h"
#include "CLAShared.h"
#include "math.h"

#define EPSILON             1e-6

// Constants
#define WAITSTEP    asm(" RPT #255||NOP")

//Global Variables
extern int16_t pass, fail;

//Task 1 (C) Variables
#ifdef __cplusplus
#pragma DATA_SECTION("CpuToCla1MsgRAM")
float fAngle;
#pragma DATA_SECTION("Cla1ToCpuMsgRAM")
float fResult_s;
#pragma DATA_SECTION("Cla1ToCpuMsgRAM")
float fResult_c;
#else
#pragma DATA_SECTION(fAngle,"CpuToCla1MsgRAM")
float fAngle;
#pragma DATA_SECTION(fResult_s,"Cla1ToCpuMsgRAM")
float fResult_s;
#pragma DATA_SECTION(fResult_c,"Cla1ToCpuMsgRAM")
float fResult_c;
#endif //__cplusplus

float y_sin[BUFFER_SIZE];
float y_cos[BUFFER_SIZE];
float fError[BUFFER_SIZE];

//Golden Test Values
float test_values[BUFFER_SIZE] = {
    -3.1415927, -3.0921188, -3.0426449,-2.9931710,
    -2.9436971, -2.8942232, -2.8447493,-2.7952754,
    -2.7458015, -2.6963276, -2.6468537,-2.5973798,
    -2.5479059, -2.4984320, -2.4489581,-2.3994842,
    -2.3500103, -2.3005364, -2.2510625,-2.2015886,
    -2.1521147, -2.1026408, -2.0531669,-2.0036930,
    -1.9542191, -1.9047452, -1.8552713,-1.8057974,
    -1.7563235, -1.7068496, -1.6573757,-1.6079018,
    -1.5584279, -1.5089540, -1.4594801,-1.4100062,
    -1.3605323, -1.3110584, -1.2615845,-1.2121106,
    -1.1626367, -1.1131628, -1.0636889,-1.0142150,
    -0.9647411, -0.9152672, -0.8657933,-0.8163194,
    -0.7668455, -0.7173716, -0.6678977,-0.6184238,
    -0.5689499, -0.5194760, -0.4700021,-0.4205282,
    -0.3710543, -0.3215804, -0.2721065,-0.2226326,
    -0.1731587, -0.1236848, -0.0742109,-0.0247370,
    0.0247370,  0.0742109,  0.1236848, 0.1731587,
    0.2226326,  0.2721065,  0.3215804, 0.3710543,
    0.4205282,  0.4700021,  0.5194760, 0.5689499,
    0.6184238,  0.6678977,  0.7173716, 0.7668455,
    0.8163194,  0.8657933,  0.9152672, 0.9647411,
    1.0142150,  1.0636889,  1.1131628, 1.1626367,
    1.2121106,  1.2615845,  1.3110584, 1.3605323,
    1.4100062,  1.4594801,  1.5089540, 1.5584279,
    1.6079018,  1.6573757,  1.7068496, 1.7563235,
    1.8057974,  1.8552713,  1.9047452, 1.9542191,
    2.0036930,  2.0531669,  2.1026408, 2.1521147,
    2.2015886,  2.2510625,  2.3005364, 2.3500103,
    2.3994842,  2.4489581,  2.4984320, 2.5479059,
    2.5973798,  2.6468537,  2.6963276, 2.7458015,
    2.7952754,  2.8447493,  2.8942232, 2.9436971,
    2.9931710,  3.0426449,  3.0921188, 3.1415927,
};  

float res_sin_expected[BUFFER_SIZE]={
    -0.0000000, -0.0494537, -0.0987864,-0.1478774,
    -0.1966064, -0.2448544, -0.2925031,-0.3394361,
    -0.3855383, -0.4306971, -0.4748020,-0.5177449,
    -0.5594207, -0.5997276, -0.6385669,-0.6758435,
    -0.7114661, -0.7453477, -0.7774054,-0.8075605,
    -0.8357394, -0.8618732, -0.8858978,-0.9077544,
    -0.9273896, -0.9447554, -0.9598091,-0.9725141,
    -0.9828392, -0.9907590, -0.9962544,-0.9993117,
    -0.9999235, -0.9980884, -0.9938107,-0.9871011,
    -0.9779758, -0.9664573, -0.9525737,-0.9363590,
    -0.9178528, -0.8971006, -0.8741529,-0.8490661,
    -0.8219014, -0.7927255, -0.7616096,-0.7286299,
    -0.6938671, -0.6574063, -0.6193367,-0.5797516,
    -0.5387476, -0.4964253, -0.4528881,-0.4082426,
    -0.3625981, -0.3160663, -0.2687610,-0.2207980,
    -0.1722946, -0.1233696, -0.0741428,-0.0247344,
    0.0247344,  0.0741428,  0.1233696, 0.1722946,
    0.2207980,  0.2687610,  0.3160663, 0.3625981,
    0.4082426,  0.4528881,  0.4964253, 0.5387476,
    0.5797516,  0.6193367,  0.6574063, 0.6938671,
    0.7286299,  0.7616096,  0.7927255, 0.8219014,
    0.8490661,  0.8741529,  0.8971006, 0.9178528,
    0.9363590,  0.9525737,  0.9664573, 0.9779758,
    0.9871011,  0.9938107,  0.9980884, 0.9999235,
    0.9993117,  0.9962544,  0.9907590, 0.9828392,
    0.9725141,  0.9598091,  0.9447554, 0.9273896,
    0.9077544,  0.8858978,  0.8618732, 0.8357394,
    0.8075605,  0.7774054,  0.7453477, 0.7114661,
    0.6758435,  0.6385669,  0.5997276, 0.5594207,
    0.5177449,  0.4748020,  0.4306971, 0.3855383,
    0.3394361,  0.2925031,  0.2448544, 0.1966064,
    0.1478774,  0.0987864,  0.0494537, 0.0000000,
};

float res_cos_expected[BUFFER_SIZE]={
    -1.0000000, -0.9987764, -0.9951087,-0.9890057,
    -0.9804825, -0.9695599, -0.9562646,-0.9406291,
    -0.9226918, -0.9024965, -0.8800927,-0.8555351,
    -0.8288838, -0.8002042, -0.7695663,-0.7370452,
    -0.7027204, -0.6666759, -0.6289999,-0.5897847,
    -0.5491262, -0.5071239, -0.4638805,-0.4195020,
    -0.3740969, -0.3277762, -0.2806535,-0.2328440,
    -0.1844646, -0.1356339, -0.0864712,-0.0370969,
    0.0123682,  0.0618030,  0.1110865, 0.1600982,
    0.2087182,  0.2568273,  0.3043080, 0.3510440,
    0.3969209,  0.4418264,  0.4856508, 0.5282867,
    0.5696297,  0.6095788,  0.6480362, 0.6849077,
    0.7201031,  0.7535363,  0.7851255, 0.8147933,
    0.8424672,  0.8680795,  0.8915674, 0.9128735,
    0.9319456,  0.9487371,  0.9632069, 0.9753196,
    0.9850455,  0.9923608,  0.9972476, 0.9996941,
    0.9996941,  0.9972476,  0.9923608, 0.9850455,
    0.9753196,  0.9632069,  0.9487371, 0.9319456,
    0.9128735,  0.8915674,  0.8680795, 0.8424672,
    0.8147933,  0.7851255,  0.7535363, 0.7201031,
    0.6849077,  0.6480362,  0.6095788, 0.5696297,
    0.5282867,  0.4856508,  0.4418264, 0.3969209,
    0.3510440,  0.3043080,  0.2568273, 0.2087182,
    0.1600982,  0.1110865,  0.0618030, 0.0123682,
    -0.0370969, -0.0864712, -0.1356339,-0.1844646,
    -0.2328440, -0.2806535, -0.3277762,-0.3740969,
    -0.4195020, -0.4638805, -0.5071239,-0.5491262,
    -0.5897847, -0.6289999, -0.6666759,-0.7027204,
    -0.7370452, -0.7695663, -0.8002042,-0.8288838,
    -0.8555351, -0.8800927, -0.9024965,-0.9226918,
    -0.9406291, -0.9562646, -0.9695599,-0.9804825,
    -0.9890057, -0.9951087, -0.9987764,-1.0000000,

};
//C28 C tasks
void test_run(void)
{
    int16_t i;
    for(i=0;i<BUFFER_SIZE;i++)
    {
     fAngle = test_values[i];
     Cla1ForceTask1andWait();
     WAITSTEP;
     y_sin[i] = fResult_s; 
     y_cos[i] = fResult_c;
    }
}

void test_report(void)
{
    uint16_t i;
    float fError_s[BUFFER_SIZE], fError_c[BUFFER_SIZE];
    for(i=0;i<BUFFER_SIZE;i++){
      fError_s[i] = fabs(res_sin_expected[i]-y_sin[i]);
      fError_c[i] = fabs(res_cos_expected[i]-y_cos[i]);
      if((fError_s[i] < EPSILON) && (fError_c[i] < EPSILON)){
        pass++;
      }else{
        fail++;
      }
    }
    // if(fail) test_error(); 
}

void test_error( void )
{
    asm(" ESTOP0"); 
}
