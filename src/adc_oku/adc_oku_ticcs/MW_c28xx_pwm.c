#include "DSP2833x_Device.h"
#include "DSP2833x_GlobalPrototypes.h"
#include "rtwtypes.h"
#include "adc_oku.h"
#include "adc_oku_private.h"

void config_ePWMRegs (volatile struct EPWM_REGS * EPwmRegs, EPWMPARAMS *
                      EPwmParams)
{
  /*-- Setup Time-Base (TB) Submodule --*/
  EPwmRegs->TBPRD = EPwmParams->TBPRD;
  EPwmRegs->TBCTL.bit.CTRMODE = EPwmParams->TBCTL_CTRMODE;
  EPwmRegs->TBCTL.bit.SYNCOSEL = EPwmParams->TBCTL_SYNCOSEL;
  EPwmRegs->TBCTL.bit.PHSEN = EPwmParams->TBCTL_PHSEN;
  EPwmRegs->TBCTL.bit.PHSDIR = EPwmParams->TBCTL_PHSDIR;
  EPwmRegs->TBPHS.half.TBPHS = EPwmParams->TBPHS;
  EPwmRegs->TBCTL.bit.HSPCLKDIV = EPwmParams->TBCTL_HSPCLKDIV;
  EPwmRegs->TBCTL.bit.CLKDIV = EPwmParams->TBCTL_CLKDIV;
  EPwmRegs->TBCTR = 0x0000;            // Clear counter

  /*-- Setup Counter_Compare (CC) Submodule --*/
  EPwmRegs->CMPCTL.bit.SHDWAMODE = CC_SHADOW;// Always enable shadow mode, no immediate mode
  EPwmRegs->CMPCTL.bit.SHDWBMODE = CC_SHADOW;// Always enable shadow mode, no immediate mode
  EPwmRegs->CMPCTL.bit.LOADAMODE = EPwmParams->CMPCTL_LOADAMODE;
  EPwmRegs->CMPCTL.bit.LOADBMODE = EPwmParams->CMPCTL_LOADBMODE;
  EPwmRegs->CMPA.half.CMPA = EPwmParams->CMPA;
  EPwmRegs->CMPB = EPwmParams->CMPB;

  /*-- Setup Action-Qualifier (AQ) Submodule --*/
  EPwmRegs->AQCTLA.all = EPwmParams->AQCTLA;
  EPwmRegs->AQCTLB.all = EPwmParams->AQCTLB;
  EPwmRegs->AQSFRC.bit.RLDCSF = EPwmParams->AQCSFRC_RLDCSF;
  EPwmRegs->AQCSFRC.bit.CSFA = EPwmParams->AQCSFRC_CSFA;
  EPwmRegs->AQCSFRC.bit.CSFB = EPwmParams->AQCSFRC_CSFB;

  /*-- Setup Dead-Band Generator (DB) Submodule --*/
  EPwmRegs->DBCTL.bit.OUT_MODE = EPwmParams->DBCTL_OUT_MODE;
  EPwmRegs->DBCTL.bit.IN_MODE = EPwmParams->DBCTL_IN_MODE;
  EPwmRegs->DBCTL.bit.POLSEL = EPwmParams->DBCTL_POLSEL;
  EPwmRegs->DBRED = EPwmParams->DBRED;
  EPwmRegs->DBFED = EPwmParams->DBFED;

  /*-- Setup Event-Trigger (ET) Submodule --*/
  EPwmRegs->ETSEL.bit.SOCAEN = EPwmParams->ETSEL_SOCAEN;
  EPwmRegs->ETSEL.bit.SOCASEL = EPwmParams->ETSEL_SOCASEL;
  EPwmRegs->ETPS.bit.SOCAPRD = EPwmParams->ETPS_SOCAPRD;
  EPwmRegs->ETSEL.bit.SOCBEN = EPwmParams->ETSEL_SOCBEN;
  EPwmRegs->ETSEL.bit.SOCBSEL = EPwmParams->ETSEL_SOCBSEL;
  EPwmRegs->ETPS.bit.SOCBPRD = EPwmParams->ETPS_SOCBPRD;
  EPwmRegs->ETSEL.bit.INTEN = EPwmParams->ETSEL_INTEN;
  EPwmRegs->ETSEL.bit.INTSEL = EPwmParams->ETSEL_INTSEL;
  EPwmRegs->ETPS.bit.INTPRD = EPwmParams->ETPS_INTPRD;

  /*-- Setup PWM-Chopper (PC) Submodule --*/
  EPwmRegs->PCCTL.bit.CHPEN = EPwmParams->PCCTL_CHPEN;
  EPwmRegs->PCCTL.bit.CHPFREQ = EPwmParams->PCCTL_CHPFREQ;
  EPwmRegs->PCCTL.bit.OSHTWTH = EPwmParams->PCCTL_OSHTWTH;
  EPwmRegs->PCCTL.bit.CHPDUTY = EPwmParams->PCCTL_CHPDUTY;

  /*-- Set up Trip-Zone (TZ) Submodule --*/
  EALLOW;
  EPwmRegs->TZSEL.all = EPwmParams->TZSEL;
  EPwmRegs->TZCTL.bit.TZA = EPwmParams->TZCTL_TZA;
  EPwmRegs->TZCTL.bit.TZB = EPwmParams->TZCTL_TZB;
  EPwmRegs->TZEINT.bit.OST = EPwmParams->TZEINT_OST;
  EPwmRegs->TZEINT.bit.CBC = EPwmParams->TZEINT_CBC;
  EDIS;
}

void config_ePWM_GPIO (void)
{
  EALLOW;

  /*-- Configure pin assignments for ePWM5 --*/
  GpioCtrlRegs.GPAPUD.bit.GPIO8 = 0;   // Enable pull-up on GPIO8 (EPWM5A)
  GpioCtrlRegs.GPAPUD.bit.GPIO9 = 0;   // Enable pull-up on GPIO9 (EPWM5B)
  GpioCtrlRegs.GPAMUX1.bit.GPIO8 = 1;  // Configure GPIO8 as EPWM5A
  GpioCtrlRegs.GPAMUX1.bit.GPIO9 = 1;  // Configure GPIO9 as EPWM5B

  /*--- Configure pin assignments for TZn ---*/
  EDIS;
}
