/* ==================================================================================
File name:        F2805xPWM.H
Target   : 		  TMS320F2805x family
=====================================================================================*/

#ifndef __F2805X_PWM_H__
#define __F2805X_PWM_H__

#include "f2805xbmsk.h"
#include "f2805xdrvlib.h"
				  
/*----------------------------------------------------------------------------
Initialization constant for the F2805X Time-Base Control Registers for PWM Generation.
Sets up the timer to run free upon emulation suspend, count up-down mode
prescaler 1.
----------------------------------------------------------------------------*/
#define PWM_INIT_STATE ( FREE_RUN_FLAG +         \
                         PRDLD_SHADOW  +          \
                         TIMER_CNT_UPDN +         \
                         HSPCLKDIV_PRESCALE_X_1 + \
                         CLKDIV_PRESCALE_X_1  +   \
                         PHSDIR_CNT_UP    +       \
                         CNTLD_DISABLE  +         \
                         SYNCOSEL_EPWMSYNCI   )

/*----------------------------------------------------------------------------
Initialization constant for the F2805X Compare Control Register.
----------------------------------------------------------------------------*/
#define CMPCTL_INIT_STATE ( LOADAMODE_ZRO + \
                            LOADBMODE_ZRO + \
                            SHDWAMODE_SHADOW + \
                            SHDWBMODE_SHADOW )

/*----------------------------------------------------------------------------
Initialization constant for the F2805X Action Qualifier Output A Register.
----------------------------------------------------------------------------*/
#define AQCTLA_INIT_STATE ( CAD_SET + CAU_CLEAR )

/*----------------------------------------------------------------------------
Initialization constant for the F2805X Dead-Band Generator registers for PWM Generation.
Sets up the dead band for PWM and sets up dead band values.
----------------------------------------------------------------------------*/
#define DBCTL_INIT_STATE  (BP_ENABLE + POLSEL_ACTIVE_HI_CMP)

#define DBCNT_INIT_STATE   100   // 100 counts = 1.66 usec (delay) * 100 count/usec (for TBCLK = SYSCLK/1)

/*----------------------------------------------------------------------------
Initialization constant for the F2805X PWM Chopper Control register for PWM Generation.
----------------------------------------------------------------------------*/
#define  PCCTL_INIT_STATE  CHPEN_DISABLE

/*----------------------------------------------------------------------------
Initialization constant for the F2805X Trip Zone Select Register
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

/*-----------------------------------------------------------------------------
    Define the structure of the Dead Band Compensator (DBC) Object
-----------------------------------------------------------------------------*/
typedef struct {
        _iq  Kdtc,                // constant K
             Ith,                 // phase current threshold
             scale,               // ratio of deabdand count to current threshold
             gain;                // scale to adjust dead time compensation
        } DBC;

/*------------------------------------------------------------------------------
	Default Initializers for the F2805X PWMGEN Object
------------------------------------------------------------------------------*/
#define F2805X_FC_PWM_GEN   {  1000,  	 \
                                 100,    \
                              0x4000,    \
                              0x4000,    \
                              0x4000,    \
                             }
                             

#define PWMGEN_DEFAULTS 	F2805X_FC_PWM_GEN
/*------------------------------------------------------------------------------
    Default Initializers for the DBC Object
------------------------------------------------------------------------------*/
#define  DBC_DEFAULTS {              \
		_IQ(0.0),                    \
		_IQ(0.001),                  \
		_IQ(0.0),                    \
		_IQ(0.0)  /* _IQ(0.5) */     \
     }



/*------------------------------------------------------------------------------
	PWM Init & PWM Update Macro Definitions
------------------------------------------------------------------------------*/
#define  TBCLKSYNC_ASSIGN(x)                                                \
        EALLOW;                                                             \
          SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = x;                            \
        EDIS;

#define  TBCLKSYNC_DISABLE()      TBCLKSYNC_ASSIGN(0)
#define  TBCLKSYNC_ENABLE()       TBCLKSYNC_ASSIGN(1)

void  PWMx_INIT_MACRO(volatile struct EPWM_REGS * ePWMx, PWMGEN v)
{
    /* Init Timer-Base Control Register for EPWMx */
    (*ePWMx).TBCTL.all = PWM_INIT_STATE;

    /* Init Timer-Base Period Register EPWMx */
    (*ePWMx).TBPRD = v.PeriodMax;

    /* Init Timer-Base Phase Register for EPWMx */
    (*ePWMx).TBPHS.half.TBPHS = 0;

    /* Init Compare Control Register for EPWMx */
    (*ePWMx).CMPCTL.all = CMPCTL_INIT_STATE;

    /* Init Action Qualifier Output A Register for EPWMx */
    (*ePWMx).AQCTLA.all = AQCTLA_INIT_STATE;

    /* Init Dead-Band Generator Control Register for EPWMx */
    (*ePWMx).DBCTL.all = DBCTL_INIT_STATE;

    /* Init Dead-Band Generator for EPWMx */
    (*ePWMx).DBFED = v.Deadband;
    (*ePWMx).DBRED = v.Deadband;

    /* Init PWM Chopper Control Register for EPWMx */
    (*ePWMx).PCCTL.all = PCCTL_INIT_STATE;

    EALLOW;                       /* Enable EALLOW */
       /* Init Trip Zone Select Register*/
       (*ePWMx).TZSEL.all = TZSEL_INIT_STATE;
         EDIS;                         /* Disable EALLOW*/			
}

#define PWM_INIT_MACRO_SHADOW(ch1,ch2,ch3,v)								\
{                                                                           \
		PWMx_INIT_MACRO(ePWM[ch1],v);                                             \
		PWMx_INIT_MACRO(ePWM[ch2],v);                                             \
		PWMx_INIT_MACRO(ePWM[ch3],v);                                             \
}

/************************************************************************
*  PWM Gen Macro
************************************************************************/
#define PWM_MACRO(ch1,ch2,ch3,m)													\
																					\
/*  Mfuncx range is (-1,1)														*/	\
/*  The code below changes PeriodMax*Mfuncx range ....  						*/	\
/*  from (-PeriodMax,PeriodMax) to (0,PeriodMax) where HalfPerMax=PeriodMax/2	*/	\
	 																				\
	 (*ePWM[ch1]).CMPA.half.CMPA = _IQmpy(m.HalfPerMax,m.MfuncC1)+ m.HalfPerMax;	\
	 (*ePWM[ch2]).CMPA.half.CMPA = _IQmpy(m.HalfPerMax,m.MfuncC2)+ m.HalfPerMax;	\
	 (*ePWM[ch3]).CMPA.half.CMPA = _IQmpy(m.HalfPerMax,m.MfuncC3)+ m.HalfPerMax;	\


/************************************************************************
 *  PWM Gen w Dead Band Compensation Macro
 *     if curA > 0   Ta = Ta + Tdt
 *     else          Ta = Ta - Tdt
 ************************************************************************/
#define PWMwDBC_MACRO(ch1,ch2,ch3,m,i,d)											 \
     (*ePWM[ch1]).CMPA.half.CMPA = _IQmpy(m.HalfPerMax,m.MfuncC1)+ m.HalfPerMax + 	 \
                                   _IQmpy(_IQsat(i.As, d.Ith, -d.Ith), d.Kdtc);      \
     (*ePWM[ch2]).CMPA.half.CMPA = _IQmpy(m.HalfPerMax,m.MfuncC2)+ m.HalfPerMax +    \
                                   _IQmpy(_IQsat(i.Bs, d.Ith, -d.Ith), d.Kdtc);      \
     (*ePWM[ch3]).CMPA.half.CMPA = _IQmpy(m.HalfPerMax,m.MfuncC3)+ m.HalfPerMax +    \
                                   _IQmpy(_IQsat(i.Cs, d.Ith, -d.Ith), d.Kdtc);

#endif  // __F2805X_PWM_H__


