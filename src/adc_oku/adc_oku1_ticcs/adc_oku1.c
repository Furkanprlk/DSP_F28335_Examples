/*
 * File: adc_oku1.c
 *
 * Code generated for Simulink model 'adc_oku1'.
 *
 * Model version                  : 1.28
 * Simulink Coder version         : 8.1 (R2011b) 08-Jul-2011
 * TLC version                    : 8.1 (Jul  9 2011)
 * C/C++ source code generated on : Wed Sep 27 11:12:40 2017
 *
 * Target selection: idelink_ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "adc_oku1.h"
#include "adc_oku1_private.h"

/* Block signals (auto storage) */
BlockIO_adc_oku1 adc_oku1_B;

/* Real-time model */
RT_MODEL_adc_oku1 adc_oku1_M_;
RT_MODEL_adc_oku1 *const adc_oku1_M = &adc_oku1_M_;

/* Model step function */
void adc_oku1_step(void)
{
  /* S-Function Block: <Root>/ADC1 (c280xadc) */
  {
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;  // Reset SEQ1 module
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;//clear INT sequencer
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;  // Software Trigger
    while (AdcRegs.ADCST.bit.INT_SEQ1 == 0) {
    }                                  //Wait for Sequencer INT bit to clear

    asm(" RPT #11 || NOP");
    adc_oku1_B.ADC1 = (AdcRegs.ADCRESULT0) >> 4;
  }

  /* RelationalOperator: '<Root>/Relational Operator' incorporates:
   *  Constant: '<Root>/Constant'
   *  Constant: '<Root>/Constant1'
   *  Gain: '<Root>/Gain'
   *  Sum: '<Root>/Add1'
   */
  adc_oku1_B.RelationalOperator = (((real_T)adc_oku1_B.ADC1 -
    adc_oku1_P.Constant_Value) * adc_oku1_P.Gain_Gain >=
    adc_oku1_P.Constant1_Value);

  /* S-Function Block: <Root>/Digital Output (c280xgpio_do) */
  {
    GpioDataRegs.GPASET.bit.GPIO0 = (adc_oku1_B.RelationalOperator != 0);
    GpioDataRegs.GPACLEAR.bit.GPIO0 = !(adc_oku1_B.RelationalOperator != 0);
  }
}

/* Model initialize function */
void adc_oku1_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(adc_oku1_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &adc_oku1_B), 0,
                sizeof(BlockIO_adc_oku1));

  /* Start for S-Function (c280xadc): '<Root>/ADC1' */
  InitAdc();
  config_ADC_A (0U, 0U, 0U, 0U, 0U);

  /* Start for S-Function (c280xgpio_do): '<Root>/Digital Output' */
  EALLOW;
  GpioCtrlRegs.GPAPUD.all = 0U;
  GpioCtrlRegs.GPAMUX1.all &= 4294967292U;
  GpioCtrlRegs.GPADIR.all |= 1U;
  EDIS;
}

/* Model terminate function */
void adc_oku1_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
