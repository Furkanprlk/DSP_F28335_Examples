/* DPlib.h */

#ifndef DPLIB_C_H
#define DPLIB_C_H

// declare library initialisation routine [DPL_ISR.asm]
// this assembly function must be called before the net is initialised
extern void DPL_Init(void);	
extern void DPL_CLAInit(void);

// declare assembly Interrupt Service Routine [DPL_ISR.asm]
extern interrupt void DPL_ISR(void);

#define ADCTRIG_SOFT		0
#define ADCTRIG_CPU_TINT0	1
#define ADCTRIG_CPU_TINT1	2
#define ADCTRIG_CPU_TINT2	3
#define ADCTRIG_XINT2		4
#define ADCTRIG_EPWM1_SOCA	5
#define ADCTRIG_EPWM1_SOCB	6
#define ADCTRIG_EPWM2_SOCA	7
#define ADCTRIG_EPWM2_SOCB	8
#define ADCTRIG_EPWM3_SOCA	9
#define ADCTRIG_EPWM3_SOCB	10
#define ADCTRIG_EPWM4_SOCA	11
#define ADCTRIG_EPWM4_SOCB	12
#define ADCTRIG_EPWM5_SOCA	13
#define ADCTRIG_EPWM5_SOCB	14
#define ADCTRIG_EPWM6_SOCA	15
#define ADCTRIG_EPWM6_SOCB	16
#define ADCTRIG_EPWM7_SOCA	17
#define ADCTRIG_EPWM7_SOCB	18

//---------------------------------------------------------------------------
// Used to indirectly access all EPWM modules
volatile struct EPWM_REGS *ePWM[] = 
 				  { &EPwm1Regs,			//intentional: (ePWM[0] not used)
				  	&EPwm1Regs,
					&EPwm2Regs,
					&EPwm3Regs,
					&EPwm4Regs,
					#if (!DSP2802x_DEVICE_H)
					&EPwm5Regs,
					&EPwm6Regs,
					#if (DSP2803x_DEVICE_H || DSP2804x_DEVICE_H)
					&EPwm7Regs,
					#if (DSP2804x_DEVICE_H)
					&EPwm8Regs
					#endif 
					#endif 
					#endif
				  };

//  CNTL_2P2Z: 2-pole 2-zero control law

// 2P2Z coefficient structure definition
struct CNTL_2P2Z_CoefStruct {
	long b2;
	long b1;
	long b0;
	long a2;
	long a1;
	long max;
	long min;
	};
	
struct CNTL_2P2Z_CLACoefStruct {
	float b2;
	float b1;
	float b0;
	float a2;
	float a1;
	float max;
	float min;
	};

// 3P3Z coefficient structure definition
struct CNTL_3P3Z_CoefStruct {
	long b3;
	long b2;
	long b1;
	long b0;
	long a3;
	long a2;
	long a1;
	long max;
	long min;
	};
	
struct CNTL_3P3Z_CLACoefStruct {
	float b3;
	float b2;
	float b1;
	float b0;
	float a3;
	float a2;
	float a1;
	float max;
	float min;
	};

//---------------------------------------------------------------------------

// DLOG: data logger module 

// Initalize memory buffers
void DLOG_BuffInit(volatile int16 *buf, unsigned int buflen)
{
	int i=0;
	while(i<buflen)
	{
			buf[i++]=0;
	}
}


#endif	// DPLIB_C_H

/* end of file */
