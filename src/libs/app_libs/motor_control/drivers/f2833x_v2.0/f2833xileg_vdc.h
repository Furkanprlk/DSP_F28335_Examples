/* ==================================================================================
File name: F2833XILEG_VDC.H
Target	 : TMS320F2833X family
              
===================================================================================*/

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

#define ADC_MACRO_INIT(ChSel,Trigsel,ACQPS)														\
																								\
	EALLOW;																						\
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;														\
	ADC_cal();																					\
	EDIS;																						\
																								\
	AdcRegs.ADCTRL3.all = 0x00E0;  /* Power up bandgap/reference/ADC circuits*/					\
    DELAY_US(ADC_usDELAY);         /* Delay before converting ADC channels*/					\
    																							\
 	AdcRegs.ADCTRL1.bit.ACQ_PS = ACQPS[0];														\
	AdcRegs.ADCTRL1.bit.CPS = 1;																\
	AdcRegs.ADCTRL3.bit.ADCCLKPS =  0;															\
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 0;        /* 0x0 Dual Sequencer Mode, 0x1 Cascaded Mode*/	\
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0x0;														\
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;															\
	AdcRegs.ADCTRL2.bit.RST_SEQ2 = 0x1;															\
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1=0x1; /* enable SOC from EPWMA trigger*/                  \
																								\
																								\
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = ChSel[0];													\
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = ChSel[1];											        \
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = ChSel[2];													\
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = ChSel[3];													\
	AdcRegs.ADCCHSELSEQ2.bit.CONV04 = ChSel[4];													\
	AdcRegs.ADCCHSELSEQ2.bit.CONV05 = ChSel[5];													\
	AdcRegs.ADCCHSELSEQ2.bit.CONV06 = ChSel[6];													\
	AdcRegs.ADCCHSELSEQ2.bit.CONV07 = ChSel[7];													\
																								\
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 7;   													\
	EDIS;																						\
																								\
    /* Set up Event Trigger with CNT_zero enable for Time-base of EPWM1 */						\
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;     /* Enable SOCA */										\
    EPwm1Regs.ETSEL.bit.SOCASEL = 2;    /* Enable period event for SOCA */						\
    EPwm1Regs.ETPS.bit.SOCAPRD = 1;     /* Generate SOCA on the 1st event */					\
	EPwm1Regs.ETCLR.bit.SOCA = 1;       /* Clear SOCA flag */


#endif // __F2833XILEG_VDC_H__
