/*
 * File: adc_oku1.h
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

#ifndef RTW_HEADER_adc_oku1_h_
#define RTW_HEADER_adc_oku1_h_
#ifndef adc_oku1_COMMON_INCLUDES_
# define adc_oku1_COMMON_INCLUDES_
#include <stddef.h>
#include <string.h>
#include "rtwtypes.h"
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "DSP2833x_Gpio.h"
#endif                                 /* adc_oku1_COMMON_INCLUDES_ */

#include "adc_oku1_types.h"

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

/* Block signals (auto storage) */
typedef struct {
  uint16_T ADC1;                       /* '<Root>/ADC1' */
  boolean_T RelationalOperator;        /* '<Root>/Relational Operator' */
} BlockIO_adc_oku1;

/* Parameters (auto storage) */
struct Parameters_adc_oku1_ {
  real_T Constant_Value;               /* Expression: 2090
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T Gain_Gain;                    /* Expression: 0.225
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T Constant1_Value;              /* Expression: 0
                                        * Referenced by: '<Root>/Constant1'
                                        */
};

/* Real-time Model Data Structure */
struct RT_MODEL_adc_oku1 {
  const char_T *errorStatus;
};

/* Block parameters (auto storage) */
extern Parameters_adc_oku1 adc_oku1_P;

/* Block signals (auto storage) */
extern BlockIO_adc_oku1 adc_oku1_B;

/* Model entry point functions */
extern void adc_oku1_initialize(void);
extern void adc_oku1_step(void);
extern void adc_oku1_terminate(void);

/* Real-time Model object */
extern struct RT_MODEL_adc_oku1 *const adc_oku1_M;

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
 * '<Root>' : 'adc_oku1'
 * '<S1>'   : 'adc_oku1/Target Preferences'
 */
#endif                                 /* RTW_HEADER_adc_oku1_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
