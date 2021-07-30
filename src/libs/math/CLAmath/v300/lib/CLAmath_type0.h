// TI File $Revision: /main/1 $
// Checkin $Date: May 21, 2009   11:15:46 $
//###########################################################################
//
// FILE:   CLAmath_type0.h
//
// TITLE:  CLA Math Library Symbols
//
//###########################################################################
// $TI Release: CLAmath Version 3.00 $
// $Release Date: Oct 15, 2010 $
//###########################################################################


#ifndef CLA_MATH_TYPE0_H
#define CLA_MATH_TYPE0_H

#ifdef __cplusplus
extern "C" {
#endif


// These symbols are defined in the CLAsincosTable_type0 assembly file.
// Include this header file in the C28x and CLA shared header file.

    extern  unsigned long *CLAsinTable;
    extern  unsigned long *CLAcosTable;
    extern  unsigned long *CLAsinTableEnd;
    extern  unsigned long *CLAcosTableEnd;

   extern  unsigned long *CLAatan2HalfPITable ;
   extern  unsigned long *CLAatan2Table ;
   extern  unsigned long *CLAatan2TableEnd ;

   extern  unsigned long *CLAasinHalfPITable ;
   extern  unsigned long *CLAasinTable ;
   extern  unsigned long *CLAasinTableEnd ;

   extern  unsigned long *CLAacosinHalfPITable ;
   extern  unsigned long *CLAacosinTable ;
   extern  unsigned long *CLAacosinTableEnd ;

   extern  unsigned long *CLAExpTable;
   extern  unsigned long *CLAExpTableEnd;

   extern  unsigned long *CLALnTable;
   extern  unsigned long *CLALnTableEnd;

    extern  float CLAsincosTable_Sin0;
    extern  float CLAsincosTable_Cos0;
    extern  float CLAsincosTable_TABLE_SIZEDivTwoPi;
    extern  float CLAsincosTable_TABLE_SIZE;																		//DivTwo;
    extern  float CLAsincosTable_TwoPiDivTABLE_SIZE;
    extern  unsigned long CLAsincosTable_TABLE_MASK;
    extern  float CLAsincosTable_Coef0;
    extern  float CLAsincosTable_Coef1;
    extern  float CLAsincosTable_Coef1_pos;
    extern  float CLAsincosTable_Coef2;
    extern  float CLAsincosTable_Coef3;
    extern  float CLAsincosTable_Coef3_neg;
	extern  float CLAINV2PI;
	extern  float CLAINV1;
	extern  float CLAINV2;
	extern  float CLAINV3;
	extern  float CLAINV4;
	extern  float CLAINV5;
	extern  float CLAINV6;
	extern  float CLAINV7;
	extern  float CLALOG10;
	extern  unsigned long CLALN_TABLE_MASK1;
	extern  unsigned long CLALN_TABLE_MASK2;
	extern  float CLALNV2;
	extern  float CLALNVe;
	extern  float CLABIAS;
	extern  float CLALNV10;

// The following definitions are useful if the
// CLA is converting from IQ to float and from
// float to IQ.
//
// To use these definitions, #include IQmathLib.h
// in this file.  The value for GLOBAL_Q will determine
// the IQ_CONV (IQ conversion) value.

#ifdef GLOBAL_Q
#ifndef IQ_CONV

#if GLOBAL_Q == 30
#define   IQ_CONV 1073741824.0L
#endif
#if GLOBAL_Q == 29
#define   IQ_CONV  536870912.0L
#endif
#if GLOBAL_Q == 28
#define   IQ_CONV  268435456.0L
#endif
#if GLOBAL_Q == 27
#define   IQ_CONV 134217728.0L
#endif
#if GLOBAL_Q == 26
#define   IQ_CONV 67108864.0L
#endif
#if GLOBAL_Q == 25
#define   IQ_CONV 33554432.0L
#endif
#if GLOBAL_Q == 24
#define   IQ_CONV 16777216.0L
#endif
#if GLOBAL_Q == 23
#define   IQ_CONV 8388608.0L
#endif
#if GLOBAL_Q == 22
#define  IQ_CONV  4194304.0L
#endif
#if GLOBAL_Q == 21
#define   IQ_CONV 2097152.0L
#endif
#if GLOBAL_Q == 20
#define   IQ_CONV 1048576.0L
#endif
#if GLOBAL_Q == 19
#define   IQ_CONV 524288.0L
#endif
#if GLOBAL_Q == 18
#define   IQ_CONV 262144.0L
#endif
#if GLOBAL_Q == 17
#define   IQ_CONV 131072.0L
#endif
#if GLOBAL_Q == 16
#define   IQ_CONV 65536.0L
#endif
#if GLOBAL_Q == 15
#define   IQ_CONV 32768.0L
#endif
#if GLOBAL_Q == 14
#define   IQ_CONV 16384.0L
#endif
#if GLOBAL_Q == 13
#define   IQ_CONV 8192.0L
#endif
#if GLOBAL_Q == 12
#define   IQ_CONV 4096.0L
#endif
#if GLOBAL_Q == 11
#define   IQ_CONV 2048.0L
#endif
#if GLOBAL_Q == 10
#define   IQ_CONV 1024.0L
#endif
#if GLOBAL_Q == 9
#define   IQ_CONV 512.0L
#endif
#if GLOBAL_Q == 8
#define   IQ_CONV 256.0L
#endif
#if GLOBAL_Q == 7
#define   IQ_CONV 128.0L
#endif
#if GLOBAL_Q == 6
#define   IQ_CONV 64.0L
#endif
#if GLOBAL_Q == 5
#define   IQ_CONV 32.0L
#endif
#if GLOBAL_Q == 4
#define   IQ_CONV 16.0L
#endif
#if GLOBAL_Q == 3
#define   IQ_CONV 8.0L
#endif
#if GLOBAL_Q == 2
#define   IQ_CONV 4.0L
#endif
#if GLOBAL_Q == 1
#define   IQ_CONV 2.0L
#endif

#endif
#endif

#ifdef __cplusplus
}
#endif /* extern "C" */
#endif  // end of CLA_MATH_TYPE0_H definition
