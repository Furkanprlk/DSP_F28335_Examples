/* ==================================================================================
File name:      F280XBLDCPWM.H                     
Target	 : 		TMS320F280x family             
=====================================================================================*/

#ifndef __F2803X_BLDCPWM_H__
#define __F2803X_BLDCPWM_H__

#include "f2803xbmsk.h"
#include "f2803xdrvlib.h"
#include "PeripheralHeaderIncludes.h"


/*----------------------------------------------------------------------------
Initialization constant for the F2803X Time-Base Control Registers for PWM Generation. 
Sets up the timer to run free upon emulation suspend, count up mode
prescaler 1.
----------------------------------------------------------------------------*/
#define BLDCPWM_INIT_STATE ( FREE_RUN_FLAG +         \
                            PRDLD_IMMEDIATE  +       \
                            TIMER_CNT_UP +         \
                            HSPCLKDIV_PRESCALE_X_1 + \
                            CLKDIV_PRESCALE_X_1  +   \
                            PHSDIR_CNT_UP    +       \
                            CNTLD_DISABLE )

/*----------------------------------------------------------------------------
Initialization constant for the F2803X Compare Control Register. 
----------------------------------------------------------------------------*/
#define BLDCPWM_CMPCTL_INIT_STATE ( LOADAMODE_ZRO + \
                                   LOADBMODE_ZRO + \
                                   SHDWAMODE_SHADOW + \
                                   SHDWBMODE_SHADOW )

/*----------------------------------------------------------------------------
Initialization constant for the F2803X Action Qualifier Output A Register. 
----------------------------------------------------------------------------*/
#define  BLDCPWM_AQCTLA_INIT_STATE  CAU_SET

/*----------------------------------------------------------------------------
Initialization constant for the F2803X Dead-Band Control Generator register.
----------------------------------------------------------------------------*/
#define  BLDCPWM_DBCTL_INIT_STATE  BP_DISABLE

/*----------------------------------------------------------------------------
Initialization constant for the F2803X PWM Chopper Control register for PWM Generation. 
----------------------------------------------------------------------------*/
#define  BLDCPWM_PCCTL_INIT_STATE  CHPEN_DISABLE

/*----------------------------------------------------------------------------
Initialization constant for the F2803X Trip Zone Select Register 
----------------------------------------------------------------------------*/
#define  BLDCPWM_TZSEL_INIT_STATE  DISABLE_TZSEL        

/*-----------------------------------------------------------------------------
Define the structure of the PWM Driver Object 
-----------------------------------------------------------------------------*/

typedef struct {  
     	Uint16 CmtnPointer;    	// Input: Commutation (or switching) state pointer input (Q0)
   		int16  MfuncPeriod;     // Input: Duty ratio of the PWM outputs (Q15) 
   		Uint16 PeriodMax;    	// Parameter: Maximum period (Q0)
   		int16  DutyFunc;   	    // Input: PWM period modulation input (Q15)
   		Uint16 PwmActive;     	// Parameter: 0 = PWM active low, 1 = PWM active high (0 or 1)
   
       } PWMGEN;
/*
	The "PwmActive" setting depends on Power devices. 
	when PwmActive = 1 (active high) implies the power device turns ON with a HIGH gate signal. 
    PwmActive = 0 (active low) implies the power device turns ON with a LOW gate signal. 
*/
/*------------------------------------------------------------------------------
Default Initializers for the F281X PWMGEN Object 
------------------------------------------------------------------------------*/
#define F2803X_BLDC_PWM_GEN   { 0x0000, \
                                0x7FFF, \
                                0x1D4C, \
                                0x0000, \
                                0x0001, \
                              } 
#define PWMGEN_DEFAULTS 	F2803X_BLDC_PWM_GEN
/*------------------------------------------------------------------------------
	F2803XBLDCPWM Macro Definitions
------------------------------------------------------------------------------*/

#define BLDCPWM_INIT_MACRO(ch1,ch2,ch3,v)										\
         /* Setup Sync*/															\
         (*ePWM[ch1]).TBCTL.bit.SYNCOSEL = 0;                              			\
         (*ePWM[ch2]).TBCTL.bit.SYNCOSEL = 0;                              			\
         (*ePWM[ch3]).TBCTL.bit.SYNCOSEL = 0;                              			\
																					\
        /* Allow each timer to be sync'ed*/											\
         (*ePWM[ch1]).TBCTL.bit.PHSEN = 1;                                 			\
         (*ePWM[ch2]).TBCTL.bit.PHSEN = 1;                                 			\
         (*ePWM[ch3]).TBCTL.bit.PHSEN = 1;                                 			\
																					\
        /* Init Timer-Base Period Register for EPWM1-EPWM3*/						\
         (*ePWM[ch1]).TBPRD = v.PeriodMax;                                 			\
         (*ePWM[ch2]).TBPRD = v.PeriodMax;                                 			\
         (*ePWM[ch3]).TBPRD = v.PeriodMax;                                 			\
																					\
        /* Init Timer-Base Phase Register for EPWM1-EPWM3*/							\
         (*ePWM[ch1]).TBPHS.half.TBPHS = 0;                                 		\
         (*ePWM[ch2]).TBPHS.half.TBPHS = 0;                                 		\
         (*ePWM[ch3]).TBPHS.half.TBPHS = 0;                                 		\
																					\
        /* Init Timer-Base Control Register for EPWM1-EPWM3*/						\
         (*ePWM[ch1]).TBCTL.all = BLDCPWM_INIT_STATE;                              	\
         (*ePWM[ch2]).TBCTL.all = BLDCPWM_INIT_STATE;                              	\
         (*ePWM[ch3]).TBCTL.all = BLDCPWM_INIT_STATE;                              	\
																					\
        /* Init Compare Control Register for EPWM1-EPWM3	*/						\
         (*ePWM[ch1]).CMPCTL.all = BLDCPWM_CMPCTL_INIT_STATE;                       \
         (*ePWM[ch2]).CMPCTL.all = BLDCPWM_CMPCTL_INIT_STATE;                     	\
         (*ePWM[ch3]).CMPCTL.all = BLDCPWM_CMPCTL_INIT_STATE;                       \
																					\
        /* Init Action Qualifier Output A Register for EPWM1-EPWM3*/				\
         (*ePWM[ch1]).AQCTLA.all = BLDCPWM_AQCTLA_INIT_STATE;                       \
         (*ePWM[ch2]).AQCTLA.all = BLDCPWM_AQCTLA_INIT_STATE;                       \
         (*ePWM[ch3]).AQCTLA.all = BLDCPWM_AQCTLA_INIT_STATE;                       \
																					\
        /* Init Dead-Band Generator Control Register for EPWM1-EPWM3*/				\
         (*ePWM[ch1]).DBCTL.all = BLDCPWM_DBCTL_INIT_STATE;                         \
         (*ePWM[ch2]).DBCTL.all = BLDCPWM_DBCTL_INIT_STATE;                         \
         (*ePWM[ch3]).DBCTL.all = BLDCPWM_DBCTL_INIT_STATE;                         \
																					\
        /* Init PWM Chopper Control Register for EPWM1-EPWM3*/						\
         (*ePWM[ch1]).PCCTL.all = BLDCPWM_PCCTL_INIT_STATE;                         \
         (*ePWM[ch2]).PCCTL.all = BLDCPWM_PCCTL_INIT_STATE;                         \
         (*ePWM[ch3]).PCCTL.all = BLDCPWM_PCCTL_INIT_STATE;                         \
 																					\


//Make sure that the GPIO configuration is properly done in ...-DevInit_F2803x.c, like shown below\
        EALLOW;           /* Enable EALLOW */				            			\
        /* Setting six EPWM as primary output pins*/								\
         GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;                /* EPWM1A pin*/			\
         GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;                /* EPWM1B pin*/			\
         GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;                /* EPWM2A pin*/			\
         GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;                /* EPWM2B pin*/			\
         GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;                /* EPWM3A pin*/			\
         GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;                /* EPWM3B pin*/			\
         																			\
         EDIS;            /* Disable EALLOW*/ 


	int32 Tmp;
	int16 Period, GPR0_BLDC_PWM;

#define BLDCPWM_MACRO(ch1,ch2,ch3,v)				/*													*/\
/* Convert "Period" (Q15) modulation function to Q0														*/\
    Tmp = (int32)v.PeriodMax*(int32)v.MfuncPeriod;  /* Q15 = Q0xQ15										*/\
    Period = (int16)(Tmp>>15);                      /* Q15 -> Q0 (Period)								*/\
													/*													*/\
/* Check PwmActive setting																				*/\
	if (v.PwmActive==1)                   			/* PWM active high									*/\
      GPR0_BLDC_PWM = 0x7FFF - v.DutyFunc;			/*   												*/\
    									  			/*													*/\
    else if (v.PwmActive==0)              			/* PWM active low									*/\
      GPR0_BLDC_PWM = v.DutyFunc;					/*													*/\
													/*													*/\
/* Convert "DutyFunc" or "GPR0_BLDC_PWM" (Q15) duty modulation function to Q0							*/\
    Tmp = (int32)Period*(int32)GPR0_BLDC_PWM;     	/* Q15 = Q0xQ15										*/\
													/*													*/\
/* State s1: current flows to motor windings from phase A->B, de-energized phase = C					*/\
	if (v.CmtnPointer==0)							/*													*/\
    {												/*													*/\
      (*ePWM[ch1]).AQCSFRC.bit.CSFA = 0;       		/* Forcing disabledd on output A of EPWM1   		*/\
      (*ePWM[ch1]).AQCTLA.bit.CAU = 2;         		/* Set high when CTR = CMPA on UP-count				*/\
      (*ePWM[ch1]).AQCTLA.bit.ZRO = 1;         		/* Set low when CTR = Zero							*/\
      (*ePWM[ch1]).CMPA.half.CMPA = (int16)(Tmp>>15); /* PWM signal on output A of EPWM1 (Q15 -> Q0)	*/\
      (*ePWM[ch1]).AQCSFRC.bit.CSFB = 1;       		/* Forcing a continuous Low on output B of EPWM1   	*/\
													/*													*/\
      (*ePWM[ch2]).AQCSFRC.bit.CSFA = 1;       		/* Forcing a continuous Low on output A of EPWM2   	*/\
      (*ePWM[ch2]).AQCSFRC.bit.CSFB = 2;       		/* Forcing a continuous High on output B of EPWM2   */\
													/*													*/\
      (*ePWM[ch3]).AQCSFRC.bit.CSFA = 1;       		/* Forcing a continuous Low on output A of EPWM3   	*/\
      (*ePWM[ch3]).AQCSFRC.bit.CSFB = 1;       		/* Forcing a continuous Low on output B of EPWM3   	*/\
    }												/*													*/\
    												/*													*/\
/* State s2: current flows to motor windings from phase A->C, de-energized phase = B					*/\
    else if (v.CmtnPointer==1)  					/*													*/\
    {												/*													*/\
      (*ePWM[ch1]).AQCSFRC.bit.CSFA = 0;       		/* Forcing disabledd on output A of EPWM1   		*/\
      (*ePWM[ch1]).AQCTLA.bit.CAU = 2;         		/* Set high when CTR = CMPA on UP-count				*/\
      (*ePWM[ch1]).AQCTLA.bit.ZRO = 1;         		/* Set low when CTR = Zero							*/\
      (*ePWM[ch1]).CMPA.half.CMPA = (int16)(Tmp>>15); 	/* PWM signal on output A of EPWM1 (Q15 -> Q0)  */\
      (*ePWM[ch1]).AQCSFRC.bit.CSFB = 1;       		/* Forcing a continuous Low on output B of EPWM1   	*/\
													/*													*/\
      (*ePWM[ch2]).AQCSFRC.bit.CSFA = 1;       		/* Forcing a continuous Low on output A of EPWM2   	*/\
      (*ePWM[ch2]).AQCSFRC.bit.CSFB = 1;       		/* Forcing a continuous Low on output B of EPWM2   	*/\
													/*													*/\
      (*ePWM[ch3]).AQCSFRC.bit.CSFA = 1;       		/* Forcing a continuous Low on output A of EPWM3   	*/\
      (*ePWM[ch3]).AQCSFRC.bit.CSFB = 2;       		/* Forcing a continuous High on output B of EPWM3   */\
    }												/*													*/\
													/*													*/\
/* State s3: current flows to motor windings from phase B->C, de-energized phase = A					*/\
    else if (v.CmtnPointer==2)  					/*													*/\
    {												/*													*/\
      (*ePWM[ch1]).AQCSFRC.bit.CSFA = 1;       		/* Forcing a continuous Low on output A of EPWM1   	*/\
      (*ePWM[ch1]).AQCSFRC.bit.CSFB = 1;       		/* Forcing a continuous Low on output B of EPWM1   	*/\
													/*													*/\
      (*ePWM[ch2]).AQCSFRC.bit.CSFA = 0;       		/* Forcing disabled on output A of EPWM2   			*/\
      (*ePWM[ch2]).AQCTLA.bit.CAU = 2;         		/* Set high when CTR = CMPA on UP-count				*/\
      (*ePWM[ch2]).AQCTLA.bit.ZRO = 1;         		/* Set low when CTR = Zero							*/\
      (*ePWM[ch2]).CMPA.half.CMPA = (int16)(Tmp>>15); 	/* PWM signal on output A of EPWM2 (Q15 -> Q0)  */\
      (*ePWM[ch2]).AQCSFRC.bit.CSFB = 1;       		/* Forcing a continuous Low on output B of EPWM2   	*/\
													/*													*/\
      (*ePWM[ch3]).AQCSFRC.bit.CSFA = 1;       		/* Forcing a continuous Low on output A of EPWM3   	*/\
      (*ePWM[ch3]).AQCSFRC.bit.CSFB = 2;       		/* Forcing a continuous High on output B of EPWM3   */\
    }												/*													*/\
   													/*													*/\
/* State s4: current flows to motor windings from phase B->A, de-energized phase = C					*/\
    else if (v.CmtnPointer==3)  					/*													*/\
    {												/*													*/\
      (*ePWM[ch1]).AQCSFRC.bit.CSFA = 1;       		/* Forcing a continuous Low on output A of EPWM1   	*/\
      (*ePWM[ch1]).AQCSFRC.bit.CSFB = 2;       		/* Forcing a continuous High on output B of EPWM1   */\
													/*													*/\
      (*ePWM[ch2]).AQCSFRC.bit.CSFA = 0;       		/* Forcing disabled on output A of EPWM2   			*/\
      (*ePWM[ch2]).AQCTLA.bit.CAU = 2;         		/* Set high when CTR = CMPA on UP-count				*/\
      (*ePWM[ch2]).AQCTLA.bit.ZRO = 1;         		/* Set low when CTR = Zero							*/\
      (*ePWM[ch2]).CMPA.half.CMPA = (int16)(Tmp>>15); 	/* PWM signal on output A of EPWM2 (Q15 -> Q0)  */\
      (*ePWM[ch2]).AQCSFRC.bit.CSFB = 1;       		/* Forcing a continuous Low on output B of EPWM2   	*/\
													/*													*/\
      (*ePWM[ch3]).AQCSFRC.bit.CSFA = 1;       		/* Forcing a continuous Low on output A of EPWM3   	*/\
      (*ePWM[ch3]).AQCSFRC.bit.CSFB = 1;       		/* Forcing a continuous Low on output B of EPWM3   	*/\
    }												/*													*/\
													/*													*/\
/* State s5: current flows to motor windings from phase C->A, de-energized phase = B					*/\
    else if (v.CmtnPointer==4)  					/*													*/\
    {												/*													*/\
      (*ePWM[ch1]).AQCSFRC.bit.CSFA = 1;       		/* Forcing a continuous Low on output A of EPWM1   	*/\
      (*ePWM[ch1]).AQCSFRC.bit.CSFB = 2;       		/* Forcing a continuous High on output B of EPWM1   */\
													/*													*/\
      (*ePWM[ch2]).AQCSFRC.bit.CSFA = 1;       		/* Forcing a continuous Low on output A of EPWM2   	*/\
      (*ePWM[ch2]).AQCSFRC.bit.CSFB = 1;       		/* Forcing a continuous Low on output B of EPWM2   	*/\
													/*													*/\
      (*ePWM[ch3]).AQCSFRC.bit.CSFA = 0;       		/* Forcing disabled on output A of EPWM3  			*/\
      (*ePWM[ch3]).AQCTLA.bit.CAU = 2;         		/* Set high when CTR = CMPA on UP-count				*/\
      (*ePWM[ch3]).AQCTLA.bit.ZRO = 1;         		/* Set low when CTR = Zero							*/\
      (*ePWM[ch3]).CMPA.half.CMPA = (int16)(Tmp>>15); 	/* PWM signal on output A of EPWM3 (Q15 -> Q0)  */\
      (*ePWM[ch3]).AQCSFRC.bit.CSFB = 1;       		/* Forcing a continuous Low on output B of EPWM3   	*/\
    }												/*													*/\
													/*													*/\
/* State s6: current flows to motor windings from phase C->B, de-energized phase = A					*/\
    else if (v.CmtnPointer==5)  					/*													*/\
    {												/*													*/\
      (*ePWM[ch1]).AQCSFRC.bit.CSFA = 1;       		/* Forcing a continuous Low on output A of EPWM1   	*/\
      (*ePWM[ch1]).AQCSFRC.bit.CSFB = 1;       		/* Forcing a continuous Low on output B of EPWM1   	*/\
													/*													*/\
      (*ePWM[ch2]).AQCSFRC.bit.CSFA = 1;       		/* Forcing a continuous Low on output A of EPWM2   	*/\
      (*ePWM[ch2]).AQCSFRC.bit.CSFB = 2;       		/* Forcing a continuous High on output B of EPWM2   */\
													/*													*/\
      (*ePWM[ch3]).AQCSFRC.bit.CSFA = 0;       		/* Forcing disabled on output A of EPWM3  			*/\
      (*ePWM[ch3]).AQCTLA.bit.CAU = 2;         		/* Set high when CTR = CMPA on UP-count				*/\
      (*ePWM[ch3]).AQCTLA.bit.ZRO = 1;         		/* Set low when CTR = Zero							*/\
      (*ePWM[ch3]).CMPA.half.CMPA = (int16)(Tmp>>15); 	/* PWM signal on output A of EPWM3 (Q15 -> Q0)  */\
      (*ePWM[ch3]).AQCSFRC.bit.CSFB = 1;       		/* Forcing a continuous Low on output B of EPWM3   	*/\
    }
    
    #endif  // __F2803X_BLDCPWM_H__










