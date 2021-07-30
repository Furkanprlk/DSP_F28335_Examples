/**********************************************************************
* File: lab.h
* Device: TMS320F2833x
* Author: Technical Training Organization (TTO), Texas Instruments
* Description: Include file for C28x workshop labs.  Include this
*   file in all C-source files.
* History:
*   07/15/08 - original
**********************************************************************/

#ifndef LAB_H
#define LAB_H


//---------------------------------------------------------------------------
// Include Standard C Language Header Files
//
#include <string.h>


//---------------------------------------------------------------------------
// Include any other Header Files
//
#include "DSP2833x_Device.h"                   // DSP2833x header file peripheral address definitions
#include "DSP2833x_DefaultIsr.h"               // ISR definitions 
#include "math.h"
#include "float.h"
#include "FPU.h"

#define	FFT_REAL_STAGES	9
#define	FFT_REAL_SIZE	(1 << FFT_REAL_STAGES) 

//---------------------------------------------------------------------------
// Constant Definitions
//
#define ADC_BUF_LEN			FFT_REAL_SIZE	// ADC buffer length
#define ADC_SAMPLE_PERIOD	3124			// 3124 = (3125-1) = 48 KHz sampling w/ 150 MHz SYSCLKOUT
#define PWM_HALF_PERIOD		37500			// period/2 for 2 kHz symmetric PWM
#define PWM_DUTY_CYCLE		28125			// 25% duty cycle
#define FILTER_LEN			5				// filter length

#if MATH_TYPE == IQ_MATH
	#define ADC_FS_VOLTAGE	_IQ(3.0)		// ADC full scale voltage
#else        // MATH_TYPE is FLOAT_MATH
	#define ADC_FS_VOLTAGE	_IQ(3.0/4096.0)	// ADC full scale voltage, scaled for 12 bit ADC
#endif


//---------------------------------------------------------------------------
// Function Prototypes
//
extern void DSP28x_usDelay(Uint16);
extern void InitAdc(void);
extern void InitDma(void);
extern void InitECap(void);
extern void InitEPwm(void);
extern void InitFlash(void);
extern void InitGpio(void);
extern void InitPieCtrl(void);
extern void InitSysCtrl(void);
extern void InitWatchdog(void);
extern void SetDBGIER(Uint16);
extern void UserInit(void);


//---------------------------------------------------------------------------
// Global symbols defined in the linker command file
//
extern Uint16 secureRamFuncs_loadstart;
extern Uint16 secureRamFuncs_loadsize;
extern Uint16 secureRamFuncs_runstart;
extern Uint16 hwi_vec_loadstart;
extern Uint16 hwi_vec_loadsize;
extern Uint16 hwi_vec_runstart;
extern Uint16 trcdata_loadstart;
extern Uint16 trcdata_loadsize;
extern Uint16 trcdata_runstart;


//---------------------------------------------------------------------------
// Global Variables References

extern Uint32 PwmDuty;
extern Uint32 PwmPeriod;
extern Uint16 AdcBuf[ADC_BUF_LEN];		// 
extern Uint16 AdcBufRaw[2*ADC_BUF_LEN];
extern Uint16 DEBUG_TOGGLE;
extern Uint16 DEBUG_FILTER;
extern const struct PIE_VECT_TABLE PieVectTableInit;	// PieVectTableInit is always extern


//---------------------------------------------------------------------------
// Macros
//
#define ADC_cal_func_ptr (void (*)(void))0x380080


//---------------------------------------------------------------------------
#endif  // end of LAB_H definition


//--- end of file -----------------------------------------------------
