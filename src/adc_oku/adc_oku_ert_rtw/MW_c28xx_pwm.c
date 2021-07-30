#include "c2000BoardSupport.h"
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "DSP2833x_GlobalPrototypes.h"
#include "rtwtypes.h"
#include "adc_oku.h"
#include "adc_oku_private.h"

void config_ePWM_GPIO (void)
{
  EALLOW;

  /*-- Configure pin assignments for ePWM5 --*/
  GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;  /* Configure GPIOGPIO8 as EPWM5A*/

  /*--- Configure pin assignments for TZn ---*/
  EDIS;
}
