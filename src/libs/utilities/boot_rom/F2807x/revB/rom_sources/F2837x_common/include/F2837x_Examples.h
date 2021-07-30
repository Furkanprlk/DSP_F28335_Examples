//###########################################################################
//
// FILE:   F2837x_Examples.h
//
// TITLE:  F2837x Device Definitions.
//
//###########################################################################
// $TI Release:  $
// $Release Date: $
//###########################################################################

#ifndef F2837x_EXAMPLES_H
#define F2837x_EXAMPLES_H

#ifdef __cplusplus
extern "C" {
#endif

/*-----------------------------------------------------------------------------
      Specify the PLL control register (PLLCR) and divide select (DIVSEL) value.
-----------------------------------------------------------------------------*/

//#define F28_DIVSEL   0 // Enable /4 for SYSCLKOUT
//#define F28_DIVSEL   1 // Disable /4 for SYSCKOUT
#define F28_DIVSEL   2 // Enable /2 for SYSCLKOUT
//#define F28_DIVSEL   3 // Enable /1 for SYSCLKOUT


#define F28_PLLCR   40    // Uncomment for 200 MHz devices [200 MHz = (10MHz * 40)/2]
//#define F28_PLLCR   38
//#define F28_PLLCR   36
//#define F28_PLLCR    34
//#define F28_PLLCR    32
//#define F28_PLLCR    30  // Uncomment for 150 MHz devices [150 MHz = (10MHz * 30)/2]
//#define F28_PLLCR    28
//#define F28_PLLCR    26
//#define F28_PLLCR    24
//#define F28_PLLCR    22
//#define F28_PLLCR    20
//#define F28_PLLCR    0  // PLL is bypassed in this mode
//----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
      Specify the clock rate of the CPU (SYSCLKOUT) in nS.

      Take into account the input clock frequency and the PLL multiplier
      selected in step 1.

      Use one of the values provided, or define your own.
      The trailing L is required tells the compiler to treat
      the number as a 64-bit value.

      Only one statement should be uncommented.

      Example:   200 MHz devices:
                 CLKIN is a 10 MHz crystal or internal 10 MHz oscillator

                 In step 1 the user specified the PLL multiplier = 40 for a
                 200 MHz CPU clock (SYSCLKOUT = 200 MHz).

                 In this case, the CPU_RATE will be 5.000L
                 Uncomment the line: #define CPU_RATE 5.000L

-----------------------------------------------------------------------------*/

//#define CPU_RATE   5.00L   // for a 200MHz CPU clock speed (SYSCLKOUT)
#define CPU_RATE 20.0L
//#define CPU_RATE   5.263L   // for a 190MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   5.556L   // for a 180MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   5.882L   // for a 170MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   6.250L   // for a 160MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   6.667L   // for a 150MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   7.143L   // for a 140MHz CPU clock speed  (SYSCLKOUT)
//#define CPU_RATE   7.692L   // for a 130MHz CPU clock speed  (SYSCLKOUT)

//----------------------------------------------------------------------------

// The following pointer to a function call calibrates the ADC and internal oscillators
#define Device_cal (void   (*)(void))0x000000

//---------------------------------------------------------------------------
// Include Example Header Files:
//

#include "F2837x_GlobalPrototypes.h"         // Prototypes for global functions within the
                                               // .c files.
#include "F2837x_Cla_defines.h"              // Macros used for CLA examples.
#include "F2837x_EPwm_defines.h"             // Macros used for PWM examples.
#include "F2837x_Gpio_defines.h"             // Macros used for GPIO support code
#include "F2837x_I2c_defines.h"              // Macros used for I2C examples.
#include "F2837x_Ipc_defines.h"              // Macros used for IPC support code.
#include "F2837x_Pie_defines.h"              // Macros used for PIE examples.
#include "F2837x_Dma_defines.h"              // Macros used for DMA examples.
#include "F2837x_SysCtrl_defines.h"          // Macros used for LPM support code
#include "F2837x_Pbist_defines.h"			 // Macros used for PBIST examples.



#define   PARTNO_2837xPACKAGEHERE 0x00

// Include files not used with F/BIOS
#ifndef F28_BIOS
#include "F2837x_DefaultISR.h"
#endif

extern void F28x_usDelay(long LoopCount);
// DO NOT MODIFY THIS LINE.
#define DELAY_US(A)  F28x_usDelay(((((long double) A * 1000.0L) / (long double)CPU_RATE) - 9.0L) / 5.0L)

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of F2837x_EXAMPLES_H definition

//===========================================================================
// End of file.
//===========================================================================
