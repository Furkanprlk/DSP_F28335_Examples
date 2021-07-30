//###########################################################################
//
// FILE:   F2837x_Device.h
//
// TITLE:  F2837x Device Definitions.
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
//###########################################################################

#ifndef F2837x_DEVICE_H
#define F2837x_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#define   TARGET   1
//#define CPU1 1
//---------------------------------------------------------------------------
// User To Select Target Device:

#define   F28_28037x    TARGET


//---------------------------------------------------------------------------
// Common CPU Definitions:
//

extern __cregister volatile unsigned int IFR;
extern __cregister volatile unsigned int IER;

#define  EINT   __asm(" clrc INTM")
#define  DINT   __asm(" setc INTM")
#define  ERTM   __asm(" clrc DBGM")
#define  DRTM   __asm(" setc DBGM")
#define  EALLOW __asm(" EALLOW")
#define  EDIS   __asm(" EDIS")
#define  ESTOP0 __asm(" ESTOP0")

#define M_INT1  0x0001
#define M_INT2  0x0002
#define M_INT3  0x0004
#define M_INT4  0x0008
#define M_INT5  0x0010
#define M_INT6  0x0020
#define M_INT7  0x0040
#define M_INT8  0x0080
#define M_INT9  0x0100
#define M_INT10 0x0200
#define M_INT11 0x0400
#define M_INT12 0x0800
#define M_INT13 0x1000
#define M_INT14 0x2000
#define M_DLOG  0x4000
#define M_RTOS  0x8000

#define BIT0    0x0001
#define BIT1    0x0002
#define BIT2    0x0004
#define BIT3    0x0008
#define BIT4    0x0010
#define BIT5    0x0020
#define BIT6    0x0040
#define BIT7    0x0080
#define BIT8    0x0100
#define BIT9    0x0200
#define BIT10   0x0400
#define BIT11   0x0800
#define BIT12   0x1000
#define BIT13   0x2000
#define BIT14   0x4000
#define BIT15   0x8000

//---------------------------------------------------------------------------
// For Portability, User Is Recommended To Use the C99 Standard integer types
//

#include <assert.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// C99 defines boolean type to be _Bool, but this doesn't match the format of
// the other standard integer types.  bool_t has been defined to fill this gap.
typedef _Bool bool_t;

// Work around for code that might accidently use uint8_t
typedef unsigned char uint8_t;

//used for a bool function return status
typedef _Bool status_t;

#ifndef SUCCESS
#define SUCCESS     true
#endif

#ifndef FAIL
#define FAIL        false
#endif
//---------------------------------------------------------------------------
// The following data types are included for compatability with legacy code,
// they are not recommended for use in new software.  Please use the C99
// types included above
//

#ifndef F28_DATA_TYPES
#define F28_DATA_TYPES
typedef int             	int16;
typedef long            	int32;
typedef long long			int64;
typedef unsigned int    	Uint16;
typedef unsigned long   	Uint32;
typedef unsigned long long	Uint64;
typedef float           	float32;
typedef long double     	float64;
#endif


//---------------------------------------------------------------------------
// Include All Peripheral Header Files:
//


#include "F2837x_Adc.h"
#include "F2837x_AnalogSubsys.h"
#include "F2837x_Cla.h"
#include "F2837x_Cmpss.h"
#include "F2837x_CpuTimers.h"
#include "F2837x_Dac.h"
#include "F2837x_Dcan.h"
#include "F2837x_Dcsm.h"
#include "F2837x_Dma.h"
#include "F2837x_DefaultISR.h"
#include "F2837x_ECap.h"
#include "F2837x_Emif.h"
#include "F2837x_EPwm.h"                // Enhanced PWM
#include "F2837x_EQep.h"
#include "F2837x_Flash.h"
#include "F2837x_Gpio.h"                // General Purpose I/O Registers
#include "F2837x_Hwbist.h"				// HWBIST Control Registers
#include "F2837x_I2c.h"
#include "F2837x_Ipc.h"
#include "F2837x_Mcbsp.h"
#include "F2837x_MemConfig.h"
#include "F2837x_NmiIntrupt.h"          // NMI Interrupt Registers
#include "F2837x_Pbist.h"               // PBIST Control Registers
#include "F2837x_PieCtrl.h"             // PIE Control Registers
#include "F2837x_PieVect.h"
#include "F2837x_Sci.h"
#include "F2837x_Sdfm.h"
#include "F2837x_Spi.h"
#include "F2837x_SysCtrl.h"             // System Control/Power Modes
#include "F2837x_Upp.h"
#include "F2837x_Usb.h"
#include "F2837x_Xbar.h"
#include "F2837x_Xint.h"            // External Interrupts

//#if (F28_28037x)
//#define DSP28_EPWM1 1
//#define DSP28_EPWM2 1
//#define DSP28_EPWM3 1
//#define DSP28_EPWM4 1
//#define DSP28_EPWM5 1
//#define DSP28_EPWM6 1
//#define DSP28_EPWM7 1
//#define DSP28_ECAP1 1
//#define DSP28_EQEP1 1
//#define DSP28_ECANA 1
//#define DSP28_SPIA  1
//#define DSP28_SCIA  1
//#define DSP28_SCIB  1
//#define DSP28_SCIC  1
//#define DSP28_I2CA  1
//#endif

// Timer definitions based on System Clock
// 60 MHz devices 
//    #define  mSec0_5  30000             // 0.5 mS
//    #define  mSec0_75  45000            // 0.75 mS
//    #define  mSec1  60000               // 1.0 mS
//    #define  mSec2  120000              // 2.0 mS
//    #define  mSec5  300000              // 5.0 mS
//    #define  mSec7_5  450000            // 7.5 mS
//    #define  mSec10  600000             // 10 mS
//    #define  mSec20  1200000            // 20 mS
//    #define  mSec50  3000000            // 50 mS
//    #define  mSec75  4500000            // 75 mS
//    #define  mSec100  6000000           // 100 mS
//    #define  mSec200  12000000          // 200 mS
//    #define  mSec500  30000000          // 500 mS
//    #define  mSec750  45000000          // 750 mS
//    #define  mSec1000  60000000         // 1000 mS
//    #define  mSec2000  120000000        // 2000 mS
//    #define  mSec5000  300000000        // 5000 mS

#ifdef __cplusplus
}
#endif                                  /* extern "C" */

#endif                                  // end of F2837x_DEVICE_H definition

//===========================================================================
// End of file.
//===========================================================================
