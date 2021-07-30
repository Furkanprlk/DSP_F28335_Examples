/* ==================================================================================
File name:       F2805XILEG_VDC.H
Target	 :		 F2805x family
=====================================================================================*/

#ifndef __F2805XILEG_VDC_H__
#define __F2805XILEG_VDC_H__

#include "f2805xbmsk.h"

/*------------------------------------------------------------------------------
 ADC Initialization Macro Definition 
------------------------------------------------------------------------------*/


#define CPU_CLOCK_SPEED      16.666L   // 10.000L for a 100MHz CPU clock speed
#define ADC_usDELAY 10000L
#define DELAY_US(A)  DSP28x_usDelay(((((long double) A * 1000.0L) / (long double)CPU_CLOCK_SPEED) - 9.0L) / 5.0L)
#define SETUP_SOCx(ADCSOCxCTL,ChSel,Trigsel,Acqps,x)   {                           \
	AdcRegs.ADCSOCxCTL.bit.CHSEL   = ChSel[x];							\
	AdcRegs.ADCSOCxCTL.bit.TRIGSEL = Trigsel[x];						\
	AdcRegs.ADCSOCxCTL.bit.ACQPS   = Acqps[x];                          \
}

extern void DSP28x_usDelay(unsigned long Count);


#define ADC_MACRO_INIT(ChSel,Trigsel,Acqps)		{												\
																								\
 DELAY_US(ADC_usDELAY);																			\
    AdcRegs.ADCCTL1.all=ADC_RESET_FLAG;															\
	asm(" NOP ");																				\
	asm(" NOP ");    																			\
																								\
	EALLOW;																						\
	 AdcRegs.ADCCTL1.bit.ADCBGPWD	= 1;	/* Power up band gap */								\
																								\
	DELAY_US(ADC_usDELAY);					/* Delay before powering up rest of ADC */			\
																								\
	AdcRegs.ADCCTL1.bit.ADCREFSEL	= 0;														\
   	AdcRegs.ADCCTL1.bit.ADCREFPWD	= 1;	/* Power up reference */							\
   	AdcRegs.ADCCTL1.bit.ADCPWDN 	= 1;	/* Power up rest of ADC */							\
	AdcRegs.ADCCTL1.bit.ADCENABLE	= 1;	/* Enable ADC */									\
																								\
	asm(" RPT#100 || NOP");																		\
																								\
	AdcRegs.ADCCTL1.bit.INTPULSEPOS=1;															\
	AdcRegs.ADCCTL1.bit.TEMPCONV=0;																\
																								\
	DELAY_US(ADC_usDELAY);																		\
																								\
	/******* CHANNEL SELECT *******/															\
																								\
    SETUP_SOCx(ADCSOC0CTL,ChSel,Trigsel,Acqps,0)		/* Set SOC0 trigger on EPWMx-A based on Trigsel*/	\
                                                        /* Set SOC0 S/H Window to 12+1 ADC Clock Cycles */  \
    SETUP_SOCx(ADCSOC1CTL,ChSel,Trigsel,Acqps,1)													        \
    SETUP_SOCx(ADCSOC2CTL,ChSel,Trigsel,Acqps,2)													        \
    SETUP_SOCx(ADCSOC3CTL,ChSel,Trigsel,Acqps,3)													        \
    SETUP_SOCx(ADCSOC4CTL,ChSel,Trigsel,Acqps,4)													        \
    SETUP_SOCx(ADCSOC5CTL,ChSel,Trigsel,Acqps,5)													        \
    SETUP_SOCx(ADCSOC6CTL,ChSel,Trigsel,Acqps,6)													        \
    SETUP_SOCx(ADCSOC7CTL,ChSel,Trigsel,Acqps,7)													        \
    SETUP_SOCx(ADCSOC8CTL,ChSel,Trigsel,Acqps,8)													        \
    SETUP_SOCx(ADCSOC9CTL,ChSel,Trigsel,Acqps,9)													        \
    SETUP_SOCx(ADCSOC10CTL,ChSel,Trigsel,Acqps,10)													        \
    SETUP_SOCx(ADCSOC11CTL,ChSel,Trigsel,Acqps,11)													        \
    SETUP_SOCx(ADCSOC12CTL,ChSel,Trigsel,Acqps,12)													        \
    SETUP_SOCx(ADCSOC13CTL,ChSel,Trigsel,Acqps,13)													        \
    SETUP_SOCx(ADCSOC14CTL,ChSel,Trigsel,Acqps,14)													        \
    SETUP_SOCx(ADCSOC15CTL,ChSel,Trigsel,Acqps,15)													        \
																								\
	EDIS;																						\
	}
#endif // __F2805XILEG_VDC_H__
