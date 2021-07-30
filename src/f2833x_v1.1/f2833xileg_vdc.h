/* ==================================================================================
File name:       F2833XILEG_VDC.H
                    
Originator:	Digital Control Systems Group
			Texas Instruments

Description: This header file contains macro definition for ADC initilization 
			 ADCs are used for leg current and DC-bus measurement.
			 ADC mapping is done according to HVDMC Kit.

Target: TMS320F2833X family
              
=====================================================================================
History:
-------------------------------------------------------------------------------------
 03-15-2010	Version 1.0: 
------------------------------------------------------------------------------------*/

#ifndef __F2833XILEG_VDC_H__
#define __F2833XILEG_VDC_H__

/*------------------------------------------------------------------------------
 ADC Initialization Macro Definition 
------------------------------------------------------------------------------*/

extern void DSP28x_usDelay(unsigned long Count);
extern void ADC_cal();
#define CPU_CLOCK_SPEED      15.000L   // 10.000L for a 100MHz CPU clock speed
#define ADC_usDELAY 50000L
#define DELAY_US(A)  DSP28x_usDelay(((((long double) A * 1000.0L) / (long double)CPU_CLOCK_SPEED) - 9.0L) / 5.0L)

#define ADC_MACRO_INIT()																		\
																								\
	EALLOW;																						\
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;														\
	ADC_cal();																					\
	EDIS;																						\
																								\
	AdcRegs.ADCTRL3.all = 0x00E0;  /* Power up bandgap/reference/ADC circuits*/					\
    DELAY_US(ADC_usDELAY);         /* Delay before converting ADC channels*/					\
    																							\
 	AdcRegs.ADCTRL1.bit.ACQ_PS = 6;																\
	AdcRegs.ADCTRL1.bit.CPS = 1;																\
	AdcRegs.ADCTRL3.bit.ADCCLKPS =  0;															\
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 0;        /* 0x0 Dual Sequencer Mode, 0x1 Cascaded Mode*/	\
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0x0;														\
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;															\
	AdcRegs.ADCTRL2.bit.RST_SEQ2 = 0x1;															\
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1=0x1; /* enable SOC from EPWMA trigger*/                  \
																								\
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 12;	/* ChSelect: ADC B4-> Phase A Current */            \
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = 14;	/* ChSelect: ADC B6-> Phase B Current */			\
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = 1;	/* ChSelect: ADC A1-> DC Bus Voltage */				\
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = 11;	/* ChSelect: ADC B3-> V Phase A */					\
	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = 10;	/* ChSelect: ADC B2-> V Phase B */					\
	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = 9;	/* ChSelect: ADC B1-> V Phase C */					\
	AdcRegs.ADCCHSELSEQ2.bit.CONV06 = 4;    /* ChSelect: ADC A4-> Low Side DC Bus Return Cur.*/	\
	AdcRegs.ADCCHSELSEQ2.bit.CONV07 = 4;														\
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 7;   													\
	EDIS;																						\
																								\
    /* Set up Event Trigger with CNT_zero enable for Time-base of EPWM1 */						\
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;     /* Enable SOCA */										\
    EPwm1Regs.ETSEL.bit.SOCASEL = 1;    /* Enable CNT_zero event for SOCA */					\
    EPwm1Regs.ETPS.bit.SOCAPRD = 1;     /* Generate SOCA on the 1st event */					\
	EPwm1Regs.ETCLR.bit.SOCA = 1;       /* Clear SOCA flag */


#endif // __F2833XILEG_VDC_H__
