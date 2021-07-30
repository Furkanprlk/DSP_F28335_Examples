// TI File $Revision: /main/1 $
// Checkin $Date: May 28, 2009   15:37:33 $
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

// #include "IQmathLib.h"


// This includes all of the peripheral header files in the project
// The CLA can use these definitions to access peripherals the ePWM,
// Comparator and ADC result registers

  #include "DSP28x_Project.h"


// CLAmath library header file

  #include "CLAmath_type0.h"

// The following variables are shared between the C28x code and the CLA
// code.  The instance will be created in the C28x code and accessed by
// the CLA.  Use DATA_SECTION pragma statements in the main C28x C code
// and the linker allocation to place these variables in the proper
// memory or message RAM.

union   F32_I32 {
    float   f32;
    long    i32;
};


struct CLA_TO_CPU_MSG_RAM {
    union   F32_I32 y1;
    union   F32_I32 y2;
    union   F32_I32 y3;
    union   F32_I32 y4;
    union   F32_I32 y5;
    union   F32_I32 y6;
    union   F32_I32 y7;
    union   F32_I32 y8;
};

struct CPU_TO_CLA_MSG_RAM {
    float   x1;
    float   x2;
    float   x3;
    float   x4;
    float   x5;
    float   x6;
    float   x7;
    float   x8;
};


extern struct CLA_TO_CPU_MSG_RAM Cla1ToCpuMsg;
extern struct CPU_TO_CLA_MSG_RAM CpuToCla1Msg;





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
#endif  // end of CLA_SHARED definition
