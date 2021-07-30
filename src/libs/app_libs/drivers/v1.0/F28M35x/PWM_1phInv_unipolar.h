//-------------------------------------------------------------------------------------
//	FILE:			PWMDRV_1phInv_Unipolar.h
//
//	Description:	Driver Config to support a 1 phase inverter with unipolar modulation
//	Version: 		1.0
//  Target:  		
//
// Function arguments defined as:
//-------------------------------
// n = 		Target ePWM module, 1,2,...16.  e.g. if n=2, then target is ePWM2
// period = PWM period in Sysclks
//
//-------------------------------------------------------------------------------------
#ifndef _PWMDRV_1phInv_unipol_H_
#define _PWMDRV_1phInv_unipol_H_
 
//------------------------------------------------------------------------------
// 	PWM CNF function for unipolar single phase modulation
//------------------------------------------------------------------------------

#define PWM_1phInv_unipolar_CNF(n,period,deadband_rising,deadband_falling)								\
	EALLOW;																									\
	/* 	---------------------- Init EPWM n ------------------------------------------------ */				\
	(*ePWM[n]).TBPRD 		   			= period;     		/* Set timer period */							\
	(*ePWM[n]).TBCTL.bit.CTRMODE   		= TB_COUNT_UPDOWN;	/* Symmetric wave*/								\
	(*ePWM[n]).TBCTL.bit.PHSEN     		= TB_DISABLE;      	/* Disable phase loading*/						\
	(*ePWM[n]).TBCTL.bit.HSPCLKDIV 		= 0;          		/* Clock ratio to SYSCLKOUT*/					\
	(*ePWM[n]).TBCTL.bit.CLKDIV    		= 0;				/* SYSCLKOUT / 1*/								\
	(*ePWM[n]).TBCTL.bit.SYNCOSEL  		= TB_CTR_ZERO;		/* Sync with Sync in signal*/					\
	(*ePWM[n]).TBCTL.bit.PRDLD 			= TB_SHADOW;		/* Shadow load for PRD*/						\
	/* Setup shadowing*/																					\
	(*ePWM[n]).CMPCTL.bit.SHDWAMODE 	= CC_SHADOW;		/* Shadow Mode*/								\
	(*ePWM[n]).CMPCTL.bit.SHDWBMODE 	= CC_SHADOW;		/* Shadow Mode*/								\
	(*ePWM[n]).CMPCTL.bit.LOADAMODE 	= CC_CTR_ZERO;  	/* Load A on Zero*/								\
	(*ePWM[n]).CMPCTL.bit.LOADBMODE 	= CC_CTR_ZERO; 		/* Load B on Zero*/								\
	/* Set Actions */																						\
	(*ePWM[n]).AQCTLA.bit.CAD 			= AQ_SET;															\
	(*ePWM[n]).AQCTLA.bit.CAU			= AQ_CLEAR;															\
	(*ePWM[n]).AQCTLA.bit.ZRO 			= AQ_NO_ACTION;														\
	/* Set Dead Band*/																						\
	(*ePWM[n]).DBCTL.bit.OUT_MODE 		= DB_FULL_ENABLE;	/* Rising Delay on 1A & Falling Delay on 1B*/	\
	(*ePWM[n]).DBCTL.bit.POLSEL 		= DB_ACTV_HIC;		/* Active Hi complementary mode (EPWMxA is inverted)*/	\
	(*ePWM[n]).DBCTL.bit.IN_MODE 		= DBA_ALL; 			/* 2A for Rising Falling */						\
	(*ePWM[n]).DBRED 					= deadband_rising;	/* Delay at Rising edge*/						\
	(*ePWM[n]).DBFED 					= deadband_falling;	/* Delay at Falling edge*/						\
	/* 	---------------------- End Init EPWM n --------------------------------------------*/				\
	/* 	---------------------- Init EPWM n+1 ----------------------------------------------*/				\
	(*ePWM[n+1]).TBPRD 		   			= period;     		/* Set timer period */							\
	(*ePWM[n+1]).TBCTL.bit.CTRMODE  	= TB_COUNT_UPDOWN;	/* Symmetric wave*/								\
	(*ePWM[n+1]).TBCTL.bit.PHSEN    	= TB_ENABLE;      	/* Enable phase loading*/						\
	(*ePWM[n+1]).TBCTL.bit.HSPCLKDIV 	= 0;          		/* Clock ratio to SYSCLKOUT*/					\
	(*ePWM[n+1]).TBCTL.bit.CLKDIV    	= 0;				/* SYSCLKOUT / 1*/								\
	(*ePWM[n+1]).TBCTL.bit.SYNCOSEL  	= TB_SYNC_IN;		/* pass the sync in signal forward*/			\
	(*ePWM[n+1]).TBCTL.bit.PRDLD 		= TB_SHADOW;		/* Shadow load for PRD*/						\
	(*ePWM[n+1]).TBCTL.bit.PHSDIR 		= TB_UP;            /* Sync the phase in up direction*/				\
	(*ePWM[n+1]).TBPHS.half.TBPHS =2;                		/* synch phase with 2, account for logic delay*/\
	/* Setup shadowing*/																					\
	(*ePWM[n+1]).CMPCTL.bit.SHDWAMODE 	= CC_SHADOW;		/* Shadow Mode*/								\
	(*ePWM[n+1]).CMPCTL.bit.SHDWBMODE 	= CC_SHADOW;		/* Shadow Mode*/								\
	(*ePWM[n+1]).CMPCTL.bit.LOADAMODE 	= CC_CTR_ZERO;      /* Load A on PRD*/								\
	(*ePWM[n+1]).CMPCTL.bit.LOADBMODE 	= CC_CTR_ZERO; 		/* Load B on Zero*/								\
	/* Set Actions */																						\
	(*ePWM[n+1]).AQCTLA.bit.CAD 		= AQ_SET;															\
	(*ePWM[n+1]).AQCTLA.bit.CAU			= AQ_CLEAR;															\
	(*ePWM[n+1]).AQCTLA.bit.ZRO 		= AQ_NO_ACTION;														\
	/* Set Dead Band for PWM1*/																				\
	(*ePWM[n+1]).DBCTL.bit.OUT_MODE 	= DB_FULL_ENABLE;	/* Rising Delay on 1A & Falling Delay on 1B*/	\
	(*ePWM[n+1]).DBCTL.bit.POLSEL 		= DB_ACTV_HIC;		/* Active high complementary mode (EPWMxA is inverted)*/	\
	(*ePWM[n+1]).DBCTL.bit.IN_MODE 		= DBA_ALL; 			/* 1A for Rising& Falling*/						\
	(*ePWM[n+1]).DBRED 					= deadband_rising;	/* Delay at Rising edge*/						\
	(*ePWM[n+1]).DBFED 					= deadband_falling;	/* Delay at Falling edge*/						\
	/* 	---------------------- End Init EPWM n+1 ----------------------------------------*/					\
	/* Clear TB counter*/																					\
	(*ePWM[n]).TBCTR            		= 0x0;         		/* Clear counter*/								\
	(*ePWM[n+1]).TBCTR            		= 0x0;         		/* Clear counter*/								\
	/* ADC SOC for Inverter Control*/														   				\
	(*ePWM[n]).ETSEL.bit.SOCAEN	= 1;						/* Enable SOC on A group*/						\
	(*ePWM[n]).ETSEL.bit.SOCASEL	= ET_CTR_ZERO ;			/* Select SOC from counter at ctr = 0*/			\
	(*ePWM[n]).ETPS.bit.SOCAPRD 	= ET_1ST;				/* Generate pulse on 1st even*/					\
	(*ePWM[n+1]).ETSEL.bit.SOCAEN	= 1;					/* Enable SOC on A group*/						\
	(*ePWM[n+1]).ETSEL.bit.SOCASEL	= ET_CTR_ZERO ;	/* Select SOC from counter at ctr = 0*/					\
	(*ePWM[n+1]).ETPS.bit.SOCAPRD 	= ET_1ST;			/* Generate pulse on 1st event*/					\
	SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 1;																	\
	EDIS;																									


#define PWMDRV_1phInv_unipolar(n,p,v) 							\
	if ( v >= 0.0)												\
	{															\
		(*ePWM[n]).CMPA.half.CMPA	= 0 ;						\
		(*ePWM[n+1]).CMPA.half.CMPA	= (int)((float)p*fabs(v));	\
	}															\
	else														\
	{															\
		(*ePWM[n]).CMPA.half.CMPA	= (int)((float)p*fabs(v));	\
		(*ePWM[n+1]).CMPA.half.CMPA	= 0 ;						\
	}																					
#endif
