/*
 * File: adc_oku.h
 *
 * Code generated for Simulink model 'adc_oku'.
 *
 * Model version                  : 1.17
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Wed May 26 13:29:51 2021
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Texas Instruments->C2000
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_adc_oku_h_
#define RTW_HEADER_adc_oku_h_
#include <stddef.h>
#include <string.h>
#ifndef adc_oku_COMMON_INCLUDES_
#define adc_oku_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "c2000BoardSupport.h"
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "DSP2833x_Gpio.h"
#include "IQmathLib.h"
#endif                                 /* adc_oku_COMMON_INCLUDES_ */

#include "adc_oku_types.h"
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

extern void config_ePWM_GPIO (void);

/* Block signals (default storage) */
typedef struct {
  real32_T DigitalInput;               /* '<Root>/Digital Input' */
  uint16_T ADC1;                       /* '<Root>/ADC1' */
} BlockIO_adc_oku;

/* Parameters (default storage) */
struct Parameters_adc_oku_ {
  real_T Gain1_Gain;                   /* Expression: -1
                                        * Referenced by: '<Root>/Gain1'
                                        */
  real32_T Switch_Threshold;           /* Computed Parameter: Switch_Threshold
                                        * Referenced by: '<Root>/Switch'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_adc_oku {
  const char_T *errorStatus;
};

/* Block parameters (default storage) */
extern Parameters_adc_oku adc_oku_P;

/* Block signals (default storage) */
extern BlockIO_adc_oku adc_oku_B;

/* Model entry point functions */
extern void adc_oku_initialize(void);
extern void adc_oku_step(void);
extern void adc_oku_terminate(void);

/* Real-time Model object */
extern RT_MODEL_adc_oku *const adc_oku_M;
extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

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
