// TI File $Revision: /main/1 $
// Checkin $Date: May 28, 2009   15:39:05 $
//###########################################################################
//
// FILE:   CLAShared.h
//
// TITLE:  CLA and CPU shared variables and constants
//
//###########################################################################
// $TI Release: CLAmath Version 3.00 $
// $Release Date: Oct 15, 2010 $
//###########################################################################


#ifndef CLA_SHARED_H
#define CLA_SHARED_H

#ifdef __cplusplus
extern "C" {
#endif

// If the project uses IQmathLib.h, then include the .h file here

#include "IQmathLib.h"


// This includes all of the peripheral header files in the project
// The CLA can use these definitions to access peripherals the ePWM,
// Comparator and ADC result registers

  #include "DSP28x_Project.h"

// Macros
//The GOTOLABELx will decide what data points to load into the test
//variables for task 7, thereby determining the execution path in that
//task
#define 	WAITSTEP 			asm(" RPT #255 || NOP") //!< Insert 255 NOPs into the code
#define		GOTOLABEL7			 1
#define		GOTOLABEL8			 0
#define		GOTOLABEL9			 0
#define		GOTOLABEL10			 0
#define		GOTOLABEL11			 0
#define		GOTOLABEL12			 0
#define		GOTOLABEL13			 0
#define		GOTOLABEL14			 0

#define 	BUFFER_SIZE			(50) 				//!< Adc Buffer size


  union F32orI32orIQ24{
  	float	    f32;
  	int32  	i32;
  	_iq		iq24;
  };
 
 // The following variables are shared between the C28x code and the CLA
// code.  The instance will be created in the C28x code and accessed by
// the CLA.  Use DATA_SECTION pragma statements in the main C28x C code
// and the linker allocation to place these variables in the proper
// memory or message RAM.
 
 
 // Globally defined structures
 
 /*
  * Externally defined structure in the CPU to CLA message RAM. It has
  * eight 32 bit variables, each of which is a union of a
  * float, integer and IQ24 number
  */
 struct CPUtoCLAMsg_t{
 	union F32orI32orIQ24 x1;
 	union F32orI32orIQ24 x2;
 	union F32orI32orIQ24 x3;
 	union F32orI32orIQ24 x4;
 	union F32orI32orIQ24 x5;
 	union F32orI32orIQ24 x6;
 	union F32orI32orIQ24 x7;
 	union F32orI32orIQ24 x8;
 };

/*
  * Externally defined structure in the CLA to CPU message RAM. It has
  * eight 32 bit variables, each of which is a union of a
  * float, integer and IQ24 number
  */
struct CLAtoCPUMsg_t{
 	union F32orI32orIQ24 y1;
 	union F32orI32orIQ24 y2;
 	union F32orI32orIQ24 y3;
 	union F32orI32orIQ24 y4;
 	union F32orI32orIQ24 y5;
 	union F32orI32orIQ24 y6;
 	union F32orI32orIQ24 y7;
 	union F32orI32orIQ24 y8; 	
  };
/*!
  * Externally defined structure in CLA Data RAM1. It has
  * eight 32 bit variables, each of which is a union of a
  * float, integer and IQ24 number
  */
 struct CLARam1Data_u{
 	union F32orI32orIQ24 u1;
 	union F32orI32orIQ24 u2;
 	union F32orI32orIQ24 u3;
 	union F32orI32orIQ24 u4;
 	union F32orI32orIQ24 u5;
 	union F32orI32orIQ24 u6;
 	union F32orI32orIQ24 u7;
 	union F32orI32orIQ24 u8; 	
 };
  /*!
  * Externally defined structure in CLA Data RAM1. It has
  * eight 32 bit variables, each of which is a union of a
  * float, integer and IQ24 number
  */
 struct CLARam1Data_v{
 	union F32orI32orIQ24 v1;
 	union F32orI32orIQ24 v2;
 	union F32orI32orIQ24 v3;
 	union F32orI32orIQ24 v4;
 	union F32orI32orIQ24 v5;
 	union F32orI32orIQ24 v6;
 	union F32orI32orIQ24 v7;
 	union F32orI32orIQ24 v8; 	
 };
 
 extern struct  CPUtoCLAMsg_t   sCPUtoCLAMsg;
 extern struct  CLAtoCPUMsg_t   sCLAtoCPUMsg;
 extern struct  CLARam1Data_u	sCLARam1Data_u;
 extern struct  CLARam1Data_v	sCLARam1Data_v;
 
// The following are symbols defined in the CLA assembly code
// Including them in the shared header file makes them
// .global and the main CPU can make use of them.

  extern Uint32 Cla1Task1;
  extern Uint32 Cla1Task2;
  extern Uint32 Cla1Task3;
  extern Uint32 Cla1Task4;
  extern Uint32 Cla1Task5;
  extern Uint32 Cla1Task6;
  extern Uint32 Cla1Task7;
  extern Uint32 Cla1Task8;
  extern Uint32 Cla1Prog_Start;
  extern Uint32 Cla1T1End;
  extern Uint32 Cla1T2End;
  extern Uint32 Cla1T3End;
  extern Uint32 Cla1T4End;
  extern Uint32 Cla1T5End;
  extern Uint32 Cla1T6End;
  extern Uint32 Cla1T7End;
  extern Uint32 Cla1T8End;

#ifdef __cplusplus
}
#endif /* extern "C" */
#endif /*CLASHARED_H_*/

