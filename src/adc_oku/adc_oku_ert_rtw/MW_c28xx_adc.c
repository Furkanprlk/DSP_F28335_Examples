#include "c2000BoardSupport.h"
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "DSP2833x_GlobalPrototypes.h"
#include "rtwtypes.h"
#include "adc_oku.h"
#include "adc_oku_private.h"

void config_ADC_A(uint16_T maxConv, uint16_T adcChselSEQ1Reg, uint16_T
                  adcChselSEQ2Reg, uint16_T adcChselSEQ3Reg, uint16_T
                  adcChselSEQ4Reg)
{
  AdcRegs.ADCTRL1.bit.SUSMOD = 0x0;    /* Emulation suspend ignored*/
  AdcRegs.ADCTRL1.bit.ACQ_PS = 4;      /* Acquisition window size*/
  AdcRegs.ADCTRL1.bit.CPS = 1;         /* Core clock pre-scaler*/
  AdcRegs.ADCTRL3.bit.ADCCLKPS = 3;    /* Core clock divider*/
  AdcRegs.ADCREFSEL.bit.REF_SEL = 0 ;  /* Set Reference Voltage*/
  AdcRegs.ADCOFFTRIM.bit.OFFSET_TRIM = AdcRegs.ADCOFFTRIM.bit.OFFSET_TRIM;/* Set Offset Error Correctino Value*/
  AdcRegs.ADCTRL1.bit.CONT_RUN = 0;
                                  /* 0:Start-Stop or continuous sequencer mode*/
  AdcRegs.ADCTRL3.bit.ADCBGRFDN = 0x3; /* Bandgap and reference powered up*/
  AdcRegs.ADCTRL3.bit.SMODE_SEL = 0 ; /* 1:Simultaneous, 0:Sequential sampling*/
  AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = maxConv;
                         /* Number of conversions in CONV2 when using B module*/
  AdcRegs.ADCTRL1.bit.SEQ_CASC = 0;    /* 1:Cascaded, 0:Dual sequencer mode*/
  AdcRegs.ADCCHSELSEQ1.all = adcChselSEQ1Reg;/* Channels for conversion*/
  AdcRegs.ADCCHSELSEQ2.all = adcChselSEQ2Reg;/* Channels for conversion*/
  AdcRegs.ADCTRL2.bit.INT_MOD_SEQ1 = 0;
  AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 1;
  AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;  /* Reset SEQ1*/
}
