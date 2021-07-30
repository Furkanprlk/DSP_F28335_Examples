/* ==================================================================================
File name:        F2805xanalogsubsys.H
Target   : 	  TMS320F2805x family
=====================================================================================*/

#ifndef __F2805X_analog_H__
#define __F2805X_analog_H__

#include "f2805xbmsk.h"
#include "f2805xdrvlib.h"

/*------------------------------------------------------------------------------
	PGA and Filter Init Macro Definitions
------------------------------------------------------------------------------*/

#define ANALOGSUBSYS_INIT_MACRO()																		\
		EALLOW;																							\
																										\
		/* Enables for DAC 1 thru 5 M1/M2/PFC DAC's */													\
		AnalogSubsysRegs.DACEN.bit.DAC1EN = 1;															\
		AnalogSubsysRegs.DACEN.bit.DAC2EN = 1;															\
		AnalogSubsysRegs.DACEN.bit.DAC3EN = 1; 															\
		AnalogSubsysRegs.DACEN.bit.DAC4EN = 1;															\
		AnalogSubsysRegs.DACEN.bit.DAC5EN = 1;															\
		AnalogSubsysRegs.VREFOUTEN.bit.DACVREFOUTEN = 1;												\
		/* VREFOUT DAC enable -- OFF '0' in internal gain mode ON '1' in external gain */				\
																										\
		/* Enables for AMPS 1 thru 7 M1/M2/PFC AMP's */													\
		AnalogSubsysRegs.PGAEN.bit.AMPA1EN = 1;															\
		AnalogSubsysRegs.PGAEN.bit.AMPA3EN = 1;															\
		AnalogSubsysRegs.PGAEN.bit.AMPB1EN = 1;															\
		AnalogSubsysRegs.PGAEN.bit.AMPA6EN = 1;															\
		AnalogSubsysRegs.PGAEN.bit.AMPB4EN = 1;															\
		AnalogSubsysRegs.PGAEN.bit.AMPB6EN = 1;															\
		AnalogSubsysRegs.PGAEN.bit.AMPB7EN = 1;															\
																										\
		/* Enables for COMPS 1 thru 13 M1/M2/PFC COMP's */												\
		AnalogSubsysRegs.COMPEN.bit.COMPA1EN = 1;														\
		AnalogSubsysRegs.COMPEN.bit.COMPA3EN = 1;														\
		AnalogSubsysRegs.COMPEN.bit.COMPB1EN = 1;														\
		AnalogSubsysRegs.COMPEN.bit.COMPA6EN = 1;														\
		AnalogSubsysRegs.COMPEN.bit.COMPB4EN = 1;														\
		AnalogSubsysRegs.COMPEN.bit.COMPB6EN = 1;														\
		AnalogSubsysRegs.COMPEN.bit.COMPB7EN = 1;														\
																										\
		/* Initialize the op-amp gains */																\
		AnalogSubsysRegs.AMPM1_GAIN.bit.AMPA1GAIN = 1;			/* Gain = 6 */							\
		AnalogSubsysRegs.AMPM1_GAIN.bit.AMPA3GAIN = 1;													\
		AnalogSubsysRegs.AMPM1_GAIN.bit.AMPB1GAIN = 1;													\
																										\
		/* Initialize the DAC values */																	\
		AnalogSubsysRegs.VREFOUTCTL.bit.DACVAL = 31;													\
		AnalogSubsysRegs.DAC1CTL.bit.DACVAL = 50;				/* 2.65V */								\
		AnalogSubsysRegs.DAC2CTL.bit.DACVAL = 12;				/* 0.65V */								\
																										\
		/* Filter Input & function control */															\
		/* COMP A1 */																					\
		AnalogSubsysRegs.CTRIPA1ICTL.bit.COMPHINPEN = 1;		/* Enable COMPH */						\
		AnalogSubsysRegs.CTRIPA1ICTL.bit.COMPLINPEN = 1;		/* Enable COMPL */						\
		AnalogSubsysRegs.CTRIPA1ICTL.bit.COMPHPOL = 0;			/* Disable inverted polarity */			\
		AnalogSubsysRegs.CTRIPA1ICTL.bit.COMPLPOL = 1;			/* Invert polarity */					\
		AnalogSubsysRegs.CTRIPA1ICTL.bit.CTRIPBYP = 0;			/* Filtered trip signals */				\
		AnalogSubsysRegs.CTRIPA1ICTL.bit.CTRIPOUTBYP = 0;												\
																										\
		AnalogSubsysRegs.CTRIPA1FILCLKCTL.bit.CLKPRESCALE = 0;	/* No clock pre-scaling */				\
		AnalogSubsysRegs.CTRIPA1FILCTL.bit.SAMPWIN = 20; 		/* Filter sample window size*/			\
		AnalogSubsysRegs.CTRIPA1FILCTL.bit.THRESH = 12;			/* Threshold; SAMPWIN/2 or greater */	\
		AnalogSubsysRegs.CTRIPA1FILCTL.bit.FILINIT = 1;			/* Initialize sample filter */			\
																										\
		/* COMP A3 */																					\
		AnalogSubsysRegs.CTRIPA3ICTL.bit.COMPHINPEN = 1;		/* Enable COMPH */						\
		AnalogSubsysRegs.CTRIPA3ICTL.bit.COMPLINPEN = 1;		/* Enable COMPL */						\
		AnalogSubsysRegs.CTRIPA3ICTL.bit.COMPHPOL = 0;			/* Disable inverted polarity */			\
		AnalogSubsysRegs.CTRIPA3ICTL.bit.COMPLPOL = 1;			/* Invert polarity */					\
		AnalogSubsysRegs.CTRIPA1ICTL.bit.CTRIPBYP = 0;			/* Filtered trip signals */				\
		AnalogSubsysRegs.CTRIPA1ICTL.bit.CTRIPOUTBYP = 0;												\
																										\
		AnalogSubsysRegs.CTRIPA3FILCLKCTL.bit.CLKPRESCALE = 0;	/* No clock pre-scaling */				\
		AnalogSubsysRegs.CTRIPA3FILCTL.bit.SAMPWIN = 20; 		/* Filter sample window size*/			\
		AnalogSubsysRegs.CTRIPA3FILCTL.bit.THRESH = 12;			/* Threshold; SAMPWIN/2 or greater */	\
		AnalogSubsysRegs.CTRIPA3FILCTL.bit.FILINIT = 1;			/* Initialize sample filter */			\
																										\
		/* COMP B1 */																					\
		AnalogSubsysRegs.CTRIPB1ICTL.bit.COMPHINPEN = 1;		/* Enable COMPH */						\
		AnalogSubsysRegs.CTRIPB1ICTL.bit.COMPLINPEN = 1;		/* Enable COMPL */						\
		AnalogSubsysRegs.CTRIPB1ICTL.bit.COMPHPOL = 0;			/* Disable inverted polarity */			\
		AnalogSubsysRegs.CTRIPB1ICTL.bit.COMPLPOL = 1;			/* Invert polarity */					\
		AnalogSubsysRegs.CTRIPA1ICTL.bit.CTRIPBYP = 0;			/* Filtered trip signals */				\
		AnalogSubsysRegs.CTRIPA1ICTL.bit.CTRIPOUTBYP = 0;												\
																										\
		AnalogSubsysRegs.CTRIPB1FILCLKCTL.bit.CLKPRESCALE = 0;	/* No clock pre-scaling */				\
		AnalogSubsysRegs.CTRIPB1FILCTL.bit.SAMPWIN = 20; 		/* Filter sample window size*/			\
		AnalogSubsysRegs.CTRIPB1FILCTL.bit.THRESH = 12;			/* Threshold; SAMPWIN/2 or greater */	\
		AnalogSubsysRegs.CTRIPB1FILCTL.bit.FILINIT = 1;			/* Initialize sample filter */			\
																										\
		/* CTRIP M1 */																					\
		AnalogSubsysRegs.CTRIPM1OCTL.bit.CTRIPA1EN = 1;													\
		AnalogSubsysRegs.CTRIPM1OCTL.bit.CTRIPA3EN = 1;													\
		AnalogSubsysRegs.CTRIPM1OCTL.bit.CTRIPB1EN = 1;													\
		AnalogSubsysRegs.CTRIPM1OCTL.bit.CTRIPA1OUTEN = 1;												\
		AnalogSubsysRegs.CTRIPM1OCTL.bit.CTRIPA3OUTEN = 1;												\
		AnalogSubsysRegs.CTRIPM1OCTL.bit.CTRIPB1OUTEN = 1;												\
		AnalogSubsysRegs.CTRIPM1OCTL.bit.CTRIPOUTPOL = 0;		/* Default polarity */					\
		AnalogSubsysRegs.CTRIPM1OCTL.bit.CTRIPOUTLATEN = 0;		/* Select raw status */					\
																										\
		/* Clear flags */																				\
		AnalogSubsysRegs.CTRIPM1FLGCLR.bit.CTRIPA1FLGCLR = 1;											\
		AnalogSubsysRegs.CTRIPM1FLGCLR.bit.CTRIPA3FLGCLR = 1;											\
		AnalogSubsysRegs.CTRIPM1FLGCLR.bit.CTRIPB1FLGCLR = 1;											\
		AnalogSubsysRegs.CTRIPM1FLGCLR.bit.CTRIPOUTM1FLGCLR = 1;										\
																										\
		EDIS;																							\

#endif  // __F2805X_analog_H__
