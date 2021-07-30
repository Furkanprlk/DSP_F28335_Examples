/* ==================================================================================
File name:        F2803xPWM.H                                         
Target   : 		  TMS320F2803x family
=====================================================================================*/

#ifndef __F2803X_PWM_H__
#define __F2803X_PWM_H__

#include "f2803xbmsk.h"
#include "f2803xdrvlib.h"
				  
/*----------------------------------------------------------------------------
Initialization constant for the F2803X Time-Base Control Registers for PWM Generation. 
Sets up the timer to run free upon emulation suspend, count up-down mode
prescaler 1.
----------------------------------------------------------------------------*/
#define PWM_INIT_STATE ( FREE_RUN_FLAG +         \
                         PRDLD_IMMEDIATE  +       \
                         TIMER_CNT_UPDN +         \
                         HSPCLKDIV_PRESCALE_X_1 + \
                         CLKDIV_PRESCALE_X_1  +   \
                         PHSDIR_CNT_UP    +       \
                         CNTLD_DISABLE )

/*----------------------------------------------------------------------------
Initialization constant for the F2803X Compare Control Register. 
----------------------------------------------------------------------------*/
#define CMPCTL_INIT_STATE ( LOADAMODE_ZRO + \
                            LOADBMODE_ZRO + \
                            SHDWAMODE_SHADOW + \
                            SHDWBMODE_SHADOW )

/*----------------------------------------------------------------------------
Initialization constant for the F2803X Action Qualifier Output A Register. 
----------------------------------------------------------------------------*/
#define AQCTLA_INIT_STATE ( CAD_SET + CAU_CLEAR )

/*----------------------------------------------------------------------------
Initialization constant for the F2803X Dead-Band Generator registers for PWM Generation. 
Sets up the dead band for PWM and sets up dead band values.
----------------------------------------------------------------------------*/
#define DBCTL_INIT_STATE  (BP_ENABLE + POLSEL_ACTIVE_HI_CMP)

#define DBCNT_INIT_STATE   100   // 100 counts = 1.66 usec (delay) * 100 count/usec (for TBCLK = SYSCLK/1)

/*----------------------------------------------------------------------------
Initialization constant for the F2803X PWM Chopper Control register for PWM Generation. 
----------------------------------------------------------------------------*/
#define  PCCTL_INIT_STATE  CHPEN_DISABLE

/*----------------------------------------------------------------------------
Initialization constant for the F2803X Trip Zone Select Register 
----------------------------------------------------------------------------*/
#define  TZSEL_INIT_STATE  DISABLE_TZSEL
              
/*-----------------------------------------------------------------------------
	Define the structure of the PWM Driver Object 
-----------------------------------------------------------------------------*/
typedef struct {   
        Uint16 PeriodMax;   // Parameter: PWM Half-Period in CPU clock cycles (Q0)
        Uint16 HalfPerMax;  // Parameter: Half of PeriodMax 				  (Q0)
        Uint16 Deadband;    // Parameter: PWM deadband in CPU clock cycles    (Q0) 
        _iq MfuncC1;        // Input: EPWM1 A&B Duty cycle ratio (Q24)
        _iq MfuncC2;        // Input: EPWM2 A&B Duty cycle ratio (Q24)
        _iq MfuncC3;        // Input: EPWM3 A&B Duty cycle ratio (Q24)
        } PWMGEN ;    

/*------------------------------------------------------------------------------
	Default Initializers for the F2803X PWMGEN Object 
------------------------------------------------------------------------------*/
#define F2803X_FC_PWM_GEN   {  1000,  	 \
                                 100,    \
                              0x4000,    \
                              0x4000,    \
                              0x4000,    \
                             }
                             

#define PWMGEN_DEFAULTS 	F2803X_FC_PWM_GEN
/*------------------------------------------------------------------------------
	PWM Init & PWM Update Macro Definitions
------------------------------------------------------------------------------*/

 

#define PWM_INIT_MACRO(ch1,ch2,ch3,v)										\
	     /* Setup Sync*/													\
         (*ePWM[ch1]).TBCTL.bit.SYNCOSEL = 0;       /* Pass through*/		\
		 (*ePWM[ch2]).TBCTL.bit.SYNCOSEL = 0;       /* Pass through*/		\
		 (*ePWM[ch3]).TBCTL.bit.SYNCOSEL = 0;       /* Pass through*/		\
		 																	\
         /* Allow each timer to be sync'ed*/								\
         (*ePWM[ch1]).TBCTL.bit.PHSEN = 1;									\
         (*ePWM[ch2]).TBCTL.bit.PHSEN = 1;									\
         (*ePWM[ch3]).TBCTL.bit.PHSEN = 1;									\
         																	\
         /* Init Timer-Base Period Register for EPWM1-EPWM3*/				\
         (*ePWM[ch1]).TBPRD = v.PeriodMax;									\
         (*ePWM[ch2]).TBPRD = v.PeriodMax;									\
         (*ePWM[ch3]).TBPRD = v.PeriodMax;									\
																			\
         /* Init Timer-Base Phase Register for EPWM1-EPWM3*/				\
         (*ePWM[ch1]).TBPHS.half.TBPHS = 0;									\
         (*ePWM[ch2]).TBPHS.half.TBPHS = 0;									\
         (*ePWM[ch3]).TBPHS.half.TBPHS = 0;									\
																			\
         /* Init Timer-Base Control Register for EPWM1-EPWM3*/				\
         (*ePWM[ch1]).TBCTL.all = PWM_INIT_STATE;							\
		 (*ePWM[ch2]).TBCTL.all = PWM_INIT_STATE;							\
		 (*ePWM[ch3]).TBCTL.all = PWM_INIT_STATE;							\
																			\
         /* Init Compare Control Register for EPWM1-EPWM3*/					\
         (*ePWM[ch1]).CMPCTL.all = CMPCTL_INIT_STATE;						\
         (*ePWM[ch2]).CMPCTL.all = CMPCTL_INIT_STATE;						\
         (*ePWM[ch3]).CMPCTL.all = CMPCTL_INIT_STATE;						\
																			\
         /* Init Action Qualifier Output A Register for EPWM1-EPWM3*/		\
         (*ePWM[ch1]).AQCTLA.all = AQCTLA_INIT_STATE;						\
         (*ePWM[ch2]).AQCTLA.all = AQCTLA_INIT_STATE;						\
         (*ePWM[ch3]).AQCTLA.all = AQCTLA_INIT_STATE;						\
																			\
         /* Init Dead-Band Generator Control Register for EPWM1-EPWM3*/		\
         (*ePWM[ch1]).DBCTL.all = DBCTL_INIT_STATE;							\
         (*ePWM[ch2]).DBCTL.all = DBCTL_INIT_STATE;							\
         (*ePWM[ch3]).DBCTL.all = DBCTL_INIT_STATE;							\
																			\
         /* Init Dead-Band Generator for EPWM1-EPWM3*/						\
         (*ePWM[ch1]).DBFED = v.Deadband;									\
         (*ePWM[ch1]).DBRED = v.Deadband;									\
         (*ePWM[ch2]).DBFED = v.Deadband;									\
         (*ePWM[ch2]).DBRED = v.Deadband;									\
         (*ePWM[ch3]).DBFED = v.Deadband;									\
         (*ePWM[ch3]).DBRED = v.Deadband;									\
																			\
         /* Init PWM Chopper Control Register for EPWM1-EPWM3*/				\
         (*ePWM[ch1]).PCCTL.all = PCCTL_INIT_STATE;							\
         (*ePWM[ch2]).PCCTL.all = PCCTL_INIT_STATE;							\
         (*ePWM[ch3]).PCCTL.all = PCCTL_INIT_STATE;							\
          																	\
         EALLOW;                       /* Enable EALLOW */					\
																			\
         /* Init Trip Zone Select Register*/								\
         (*ePWM[ch1]).TZSEL.all = TZSEL_INIT_STATE;							\
         (*ePWM[ch2]).TZSEL.all = TZSEL_INIT_STATE;							\
         (*ePWM[ch3]).TZSEL.all = TZSEL_INIT_STATE;							\
																			\
         EDIS;                         /* Disable EALLOW*/			



#define PWM_MACRO(ch1,ch2,ch3,m)													\
																					\
/*  Mfuncx range is (-1,1)														*/	\
/*  The code below changes PeriodMax*Mfuncx range ....  						*/	\
/*  from (-PeriodMax,PeriodMax) to (0,PeriodMax) where HalfPerMax=PeriodMax/2	*/	\
	 																				\
	 (*ePWM[ch1]).CMPA.half.CMPA = _IQmpy(m.HalfPerMax,m.MfuncC1)+ m.HalfPerMax;	\
	 (*ePWM[ch2]).CMPA.half.CMPA = _IQmpy(m.HalfPerMax,m.MfuncC2)+ m.HalfPerMax;	\
	 (*ePWM[ch3]).CMPA.half.CMPA = _IQmpy(m.HalfPerMax,m.MfuncC3)+ m.HalfPerMax;	\

#endif  // __F2803X_PWM_H__


