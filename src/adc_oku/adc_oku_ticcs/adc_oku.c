/*
 * File: adc_oku.c
 *
 * Code generated for Simulink model 'adc_oku'.
 *
 * Model version                  : 1.17
 * Simulink Coder version         : 8.1 (R2011b) 08-Jul-2011
 * TLC version                    : 8.1 (Jul  9 2011)
 * C/C++ source code generated on : Wed Oct 11 09:25:39 2017
 *
 * Target selection: idelink_ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "adc_oku.h"
#include "adc_oku_private.h"

/* Block signals (auto storage) */
BlockIO_adc_oku adc_oku_B;

/* Real-time model */
RT_MODEL_adc_oku adc_oku_M_;
RT_MODEL_adc_oku *const adc_oku_M = &adc_oku_M_;

/* Model step function */
void adc_oku_step(void)
{
  /* local block i/o variables */
  real_T rtb_Switch;

  /* S-Function Block: <Root>/ADC1 (c280xadc) */
  {
    AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;  // Reset SEQ1 module
    AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;//clear INT sequencer
    AdcRegs.ADCTRL2.bit.SOC_SEQ1 = 1;  // Software Trigger
    while (AdcRegs.ADCST.bit.INT_SEQ1 == 0) {
    }                                  //Wait for Sequencer INT bit to clear

    asm(" RPT #11 || NOP");
    adc_oku_B.ADC1 = (AdcRegs.ADCRESULT0) >> 4;
  }

  /* S-Function Block: <Root>/Digital Input (c280xgpio_di) */
  {
    adc_oku_B.DigitalInput = GpioDataRegs.GPADAT.bit.GPIO0;
  }

  /* Switch: '<Root>/Switch' incorporates:
   *  Gain: '<Root>/Gain1'
   */
  if (adc_oku_B.DigitalInput >= adc_oku_P.Switch_Threshold) {
    rtb_Switch = (real_T)adc_oku_B.ADC1;
  } else {
    rtb_Switch = adc_oku_P.Gain1_Gain * (real_T)adc_oku_B.ADC1;
  }

  /* End of Switch: '<Root>/Switch' */

  /* S-Function (c280xpwm): '<Root>/ePWM' */

  /*-- Update CMPA value for ePWM5 --*/
  {
    EPwm5Regs.CMPA.half.CMPA = (uint16_T)(rtb_Switch);
  }
}

/* Model initialize function */
void adc_oku_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(adc_oku_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &adc_oku_B), 0,
                sizeof(BlockIO_adc_oku));

  /* Start for S-Function (c280xadc): '<Root>/ADC1' */
  InitAdc();
  config_ADC_A (0U, 0U, 0U, 0U, 0U);

  /* Start for S-Function (c280xgpio_di): '<Root>/Digital Input' */
  EALLOW;
  GpioCtrlRegs.GPAPUD.all = 0U;
  GpioCtrlRegs.GPAMUX1.all &= 4294967292U;
  GpioCtrlRegs.GPADIR.all &= 4294967294U;
  EDIS;

  /* Start for S-Function (c280xpwm): '<Root>/ePWM' */

  /*** Initialize ePWM5 modules ***/
  {
    EPWMPARAMS EPwm5Params;

    /*-- Setup Time-Base (TB) Submodule --*/
    EPwm5Params.TBPRD = 4096;
    EPwm5Params.TBCTL_CTRMODE = 0;
    EPwm5Params.TBCTL_SYNCOSEL = 3;
    EPwm5Params.TBCTL_PHSEN = 0;
    EPwm5Params.TBCTL_PHSDIR = 0;
    EPwm5Params.TBPHS = 0;
    EPwm5Params.TBCTL_HSPCLKDIV = 0;
    EPwm5Params.TBCTL_CLKDIV = 0;

    /*-- Setup Counter_Compare (CC) Submodule --*/
    EPwm5Params.CMPCTL_LOADAMODE = 0;
    EPwm5Params.CMPCTL_LOADBMODE = 0;
    EPwm5Params.CMPA = 32000;
    EPwm5Params.CMPB = 32000;

    /*-- Setup Action-Qualifier (AQ) Submodule --*/
    EPwm5Params.AQCTLA = 36;
    EPwm5Params.AQCTLB = 264;
    EPwm5Params.AQCSFRC_CSFA = 0;
    EPwm5Params.AQCSFRC_CSFB = 0;
    EPwm5Params.AQCSFRC_RLDCSF = 0;

    /*-- Setup Dead-Band Generator (DB) Submodule --*/
    EPwm5Params.DBCTL_OUT_MODE = 0;
    EPwm5Params.DBCTL_IN_MODE = 0;
    EPwm5Params.DBCTL_POLSEL = 0;
    EPwm5Params.DBRED = 0.0;
    EPwm5Params.DBFED = 0.0;

    /*-- Setup Event-Trigger (ET) Submodule --*/
    EPwm5Params.ETSEL_SOCAEN = 0;
    EPwm5Params.ETSEL_SOCASEL = 1;
    EPwm5Params.ETPS_SOCAPRD = 1;
    EPwm5Params.ETSEL_SOCBEN = 0;
    EPwm5Params.ETSEL_SOCBSEL = 1;
    EPwm5Params.ETPS_SOCBPRD = 1;
    EPwm5Params.ETSEL_INTEN = 0;
    EPwm5Params.ETSEL_INTSEL = 1;
    EPwm5Params.ETPS_INTPRD = 1;

    /*-- Setup PWM-Chopper (PC) Submodule --*/
    EPwm5Params.PCCTL_CHPEN = 0;
    EPwm5Params.PCCTL_CHPFREQ = 0;
    EPwm5Params.PCCTL_OSHTWTH = 0;
    EPwm5Params.PCCTL_CHPDUTY = 0;

    /*-- Setup Trip-Zone (TZ) Submodule --*/
    EPwm5Params.TZSEL = 0;
    EPwm5Params.TZCTL_TZA = 3;
    EPwm5Params.TZCTL_TZB = 3;
    EPwm5Params.TZEINT_OST = 0;
    EPwm5Params.TZEINT_CBC = 0;

    /*-- Initial ePWM5 --*/
    config_ePWMRegs(&EPwm5Regs, &EPwm5Params);
  }
}

/* Model terminate function */
void adc_oku_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
