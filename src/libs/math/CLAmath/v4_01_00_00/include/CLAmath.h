//#############################################################################
// 
// FILE: CLAmath.h
// 
// DESCRIPTION: CLA Math Library Prototypes
//
// Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
// ALL RIGHTS RESERVED
//#############################################################################
//$TI Release: CLA Math Library V4.01.00.00 $
//$Release Date: Apr 6, 2016 $
//#############################################################################

#ifndef __CLAMATH_H__
#define __CLAMATH_H__

//###########################################################################
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//###########################################################################
#ifdef __cplusplus
extern "C"
{
#endif
//###########################################################################
//
// Macro Definitions
//
//###########################################################################


//###########################################################################
//
// Structures, variables and typedefs.
//
//###########################################################################

//CLASinCosTable Variables
extern float CLAsincosTable[];
extern float CLAsinTable[];
extern float *CLAsincosTable_Sin0;
extern float CLAcosTable[];
extern float *CLAsincosTable_Cos0;
extern float *CLAsinTableEnd;
extern float *CLAcosTableEnd;
extern float *CLAsincosTableEnd;
extern float CLAsincosTable_TABLE_SIZE;
extern float CLAsincosTable_TABLE_SIZEDivTwoPi;
extern float CLAsincosTable_TwoPiDivTABLE_SIZE;
extern float CLAsincosTable_TABLE_MASK;
extern float CLAsincosTable_Coef0;
extern float CLAsincosTable_Coef1;
extern float CLAsincosTable_Coef1_pos;
extern float CLAsincosTable_Coef2;
extern float CLAsincosTable_Coef3;
extern float CLAsincosTable_Coef3_neg;

//CLAatanTable Variables
extern float CLAatan2HalfPITable[];
extern float CLAatan2Table[];
extern float *CLAatan2TableEnd;
extern float *CLAINV2PI;

//CLAacosineTable Variables
extern float CLAacosinHalfPITable[];
extern float CLAacosinTable[];
extern float *CLAacosinTableEnd;

//CLAasineTable Variables
extern float CLAasinHalfPITable[];
extern float CLAasinTable[];
extern float *CLAasinTableEnd;

//CLAexpTable Variables
extern float CLAINV1,CLAINV2,CLAINV3,CLAINV4;
extern float CLAINV5,CLAINV6,CLAINV7,CLALOG10;
extern float CLAExpTable[];
extern float *CLAExpTableEnd;

//CLAlnTable Variables
extern float CLALNV2,CLALNVe,CLALNV10,CLABIAS;
extern long CLALN_TABLE_MASK1,CLALN_TABLE_MASK2;
extern float CLALnTable[];
extern float *CLALnTableEnd;

//Linker Defined variables
extern unsigned int _cla_scratchpad_start;
extern unsigned int _cla_scratchpad_end;

//###########################################################################
//
// Function Prototypes
//
//###########################################################################
extern float CLAacos( float fVal );
extern float CLAacos_spc( float fVal );
extern float CLAasin( float fVal );
extern float CLAatan( float fVal );
extern float CLAatan2( float fVal1, float fVal2 );
extern float CLAatan2PU( float fVal1, float fVal2 );
extern float CLAcos( float fAngleRad);
extern float CLAcosPU( float fAngleRadPU ); 
extern float CLAdiv( float fNum, float fDen);
extern float CLAexp( float fVal); 
extern float CLAexp10( float fVal); 
extern float CLAexp2( float fNum, float fDen );
extern float CLAisqrt( float fVal ); 
extern float CLAln( float fVal); 
extern float CLAlog10( float fVal); 
extern float CLAsin( float fAngleRad ); 
extern float CLAsinPU( float fAngleRadPU ); 
extern float CLAsqrt( float fVal);
extern void CLAsincos(float fAngleRad, float *y_sin, float *y_cos);
extern float CLAexpN(float fVal, float N);
extern float CLAlogN(float fVal, float N);
//###########################################################################
//
//End of the C bindings section for C++ compilers.
//
//###########################################################################
#ifdef __cplusplus
}
#endif //__cplusplus

#endif // __CLAMATH_H__
