//#############################################################################
//! \file /2837x_CFFT/main.c
//!
//! \brief  Demo code for the Fast Square Root 
//! \author Vishal Coelho (Modified the original)
//! \date   03/26/2015
//! 
//! This software demonstrates the fast square root intrinsic
//!
//
//  Group:             C2000
//  Target Family:     F2837x
//
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/ 
// ALL RIGHTS RESERVED 
//#############################################################################
//$TI Release: C28x Floating Point Unit Library V1.50.00.00 $
//$Release Date: Jun 2, 2015 $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "fpu_math.h"
#include "math.h"
#include "examples_setup.h"

//!
//! \addtogroup MATH_EXAMPLES Fast Square Root

// @{
    
//*****************************************************************************
// defines
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************
float fOutput3;

uint16_t pass = 0;
uint16_t fail = 0;

//*****************************************************************************
// Function Prototypes
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************
//!
//! \brief main routine for the Fast Square Root example
//! \return returns a 1
//!

//!
int16_t main(void)
{
    // Locals
    uint16_t i;
    float fInput1, fInput2;
    float fOutput1, fOutput2;
    
#ifdef FLASH
    EALLOW;
    Flash0EccRegs.ECC_ENABLE.bit.ENABLE = 0;
    memcpy((uint32_t *)&RamfuncsRunStart, (uint32_t *)&RamfuncsLoadStart,
            (uint32_t)&RamfuncsLoadSize );
    FPU_initFlash();
#endif //FLASH
    
    FPU_initSystemClocks();
    
    FPU_initEpie();
    
    // Create some dummy test data
    fInput1 = 16777216.0;
    fInput2 = 5184.0;
    
    // Back to Back calls of __ffsqrtf()
    // Expected result: 4096 and 72
    // Declaring the inputs and outputs to the ffsqrt() locally allows the
    // compiler to optimize back-to-back calls to ffsqrt() (when optimization
    // is set to o2) as follows:
    //    MOVIZ     R1H,#19328            ; [CPU_] |96| 
    //    MOVIZ     R0H,#17826            ; [CPU_] |96| 
    //    EISQRTF32 R1H,R1H               ; [CPU_] |96| 
    //    EISQRTF32 R0H,R0H               ; [CPU_] |96| 
    //    MPYF32    R3H,R1H,R1H           ; [CPU_] |96| 
    //    MPYF32    R2H,R0H,R0H           ; [CPU_] |96| 
    //    MPYF32    R3H,R3H,#19200        ; [CPU_] |96| 
    //    MPYF32    R2H,R2H,#17698        ; [CPU_] |96| 
    //    SUBF32    R3H,#16320,R3H        ; [CPU_] |96| 
    //    SUBF32    R2H,#16320,R2H        ; [CPU_] |96| 
    //    MPYF32    R1H,R1H,R3H           ; [CPU_] |96| 
    //    MPYF32    R0H,R0H,R2H           ; [CPU_] |96| 
    //    MPYF32    R2H,R1H,#19200        ; [CPU_] |96| 
    //    MPYF32    R3H,R0H,#17698        ; [CPU_] |96| 
    //    MPYF32    R2H,R1H,R2H           ; [CPU_] |96| 
    //    MPYF32    R3H,R0H,R3H           ; [CPU_] |96| 
    //    SUBF32    R2H,#16320,R2H        ; [CPU_] |96| 
    //    SUBF32    R3H,#16320,R3H        ; [CPU_] |96| 
    //    MPYF32    R1H,R1H,R2H           ; [CPU_] |96| 
    //    MPYF32    R0H,R0H,R3H           ; [CPU_] |96| 
    //    MPYF32    R1H,R1H,#19328        ; [CPU_] |96| 
    //    MPYF32    R0H,R0H,#17826        ; [CPU_] |96| 
    // The compiler will interleave the instructions of the 
    // back-to-back calls, completing both operations in 22 cycles. The 
    // variables will be optimized out and the FPU registers will be used 
    // instead. The user can check this in the disassembly view, or as in the
    // case of this example, the assembly file generated for main.c
    //
    // The __asm(" NOP") intrinsics around the back-to-back calls serve as 
    // boundaries for compiler optimization
    //
    __asm(" NOP");
    fOutput1 = __ffsqrtf(fInput1);
    fOutput2 = __ffsqrtf(fInput2);
    __asm(" NOP");
    
    fOutput3 = fOutput1 + fOutput2;
    
    if(fOutput3 != 4168.0){
        fail++;
    }else{
        pass++;
    }
    
    // End of test
    done();
    // Execution never reaches this point
    return 1;
}

// End of main

// @} //addtogroup

// End of file

