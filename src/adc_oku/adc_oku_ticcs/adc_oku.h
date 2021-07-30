/*
 * File: adc_oku.h
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

#ifndef RTW_HEADER_adc_oku_h_
#define RTW_HEADER_adc_oku_h_
#ifndef adc_oku_COMMON_INCLUDES_
# define adc_oku_COMMON_INCLUDES_
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "DSP2833x_Gpio.h"
#include "IQmathLib.h"
#endif                                 /* adc_oku_COMMON_INCLUDES_ */

#include "adc_oku_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((void*) 0)
#endif

/*** PWM Parameter Structure ***/
typedef struct _EPWMPARAMS {
  /*-- Time-Base (TB) Submodule --*/
  Uint16 TBPRD;
  Uint16 TBCTL_CTRMODE;
  Uint16 TBCTL_SYNCOSEL;
  Uint16 TBCTL_PHSEN;
  Uint16 TBCTL_PHSDIR;
  Uint16 TBPHS;
  Uint16 TBCTL_HSPCLKDIV;
  Uint16 TBCTL_CLKDIV;

  /*-- Counter_Compare (CC) Submodule --*/
  Uint16 CMPCTL_LOADAMODE;
  Uint16 CMPCTL_LOADBMODE;
  Uint16 CMPA;
  Uint16 CMPB;

  /*-- Action-Qualifier (AQ) Submodule --*/
  Uint16 AQCTLA;
  Uint16 AQCTLB;
  Uint16 AQCSFRC_CSFA;
  Uint16 AQCSFRC_CSFB;
  Uint16 AQCSFRC_RLDCSF;

  /*-- Dead-Band Generator (DB) Submodule --*/
  Uint16 DBCTL_OUT_MODE;
  Uint16 DBCTL_IN_MODE;
  Uint16 DBCTL_POLSEL;
  Uint16 DBRED;
  Uint16 DBFED;

  /*-- Event-Trigger (ET) Submodule --*/
  Uint16 ETSEL_SOCAEN;
  Uint16 ETSEL_SOCASEL;
  Uint16 ETPS_SOCAPRD;
  Uint16 ETSEL_SOCBEN;
  Uint16 ETSEL_SOCBSEL;
  Uint16 ETPS_SOCBPRD;
  Uint16 ETSEL_INTEN;
  Uint16 ETSEL_INTSEL;
  Uint16 ETPS_INTPRD;

  /*-- PWM-Chopper (PC) Submodule --*/
  Uint16 PCCTL_CHPEN;
  Uint16 PCCTL_CHPFREQ;
  Uint16 PCCTL_OSHTWTH;
  Uint16 PCCTL_CHPDUTY;

  /*-- Trip-Zone (TZ) Submodule --*/
  Uint16 TZSEL;
  Uint16 TZCTL_TZA;
  Uint16 TZCTL_TZB;
  Uint16 TZEINT_OST;
  Uint16 TZEINT_CBC;
} EPWMPARAMS;

/* Block signals (auto storage) */
typedef struct {
  real_T DigitalInput;                 /* '<Root>/Digital Input' */
  uint16_T ADC1;                       /* '<Root>/ADC1' */
} BlockIO_adc_oku;

/* Parameters (auto storage) */
struct Parameters_adc_oku_ {
  real_T Gain1_Gain;                   /* Expression: -1
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real_T Switch_Threshold;             /* Expression: 1
                                        * Referenced by: '<Root>/Switch'
                                        */
};

/* Real-time Model Data Structure */
struct RT_MODEL_adc_oku {
  const char_T *errorStatus;
};

/* Block parameters (auto storage) */
extern Parameters_adc_oku adc_oku_P;

/* Block signals (auto storage) */
extern BlockIO_adc_oku adc_oku_B;

/* Model entry point functions */
extern void adc_oku_initialize(void);
extern void adc_oku_step(void);
extern void adc_oku_terminate(void);

/* Real-time Model object */
extern struct RT_MODEL_adc_oku *const adc_oku_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'adc_oku'
 * '<S1>'   : 'adc_oku/Target Preferences'
 */
#endif                                 /* RTW_HEADER_adc_oku_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
