/* ==================================================================================
File name:    F2805xanalogsubsys.H
Target   : 	  TMS320F2805x family
=====================================================================================*/

#ifndef __F2805X_analog_H__
#define __F2805X_analog_H__

#include "f2805xbmsk.h"
#include "f2805xdrvlib.h"

/*------------------------------------------------------------------------------
	PGA and Filter Init Macro Definitions
------------------------------------------------------------------------------*/

#define  DAC6bit(A)  (int)((float)A*63/3.3)

// =======================================================================================================
//CTRIPB7ICTL - for PFC
#define COMPPOL_M(A)      (A << 0)
#define COMPINPEN_M(A)    (A << 2)
#define CTRIPBYP_M(A)     (A << 11)
#define CTRIPOUTBYP_M(A)  (A << 12)

#define CTRIPB7ICTL_INIT  COMPPOL_M(1)    + \
		                  COMPINPEN_M(1)  + \
                          CTRIPBYP_M(0)   + \
                          CTRIPOUTBYP_M(0)
// ===============================================
// CTRIPxxICTL
#define COMPHPOL_M(A)     (A << 0)
#define COMPLPOL_M(A)     (A << 1)
#define COMPHINPEN_M(A)   (A << 2)
#define COMPLINPEN_M(A)   (A << 3)
#define CTRIPBYP_M(A)     (A << 11)
#define CTRIOUTPBYP_M(A)  (A << 12)

#define  CTRIPxxICTL_INIT   COMPHPOL_M(0)   + \
	                        COMPLPOL_M(1)   + \
	                        COMPHINPEN_M(1) + \
	                        COMPLINPEN_M(1) + \
	                        CTRIPBYP_M(0)   + \
	                        CTRIOUTPBYP_M(0)
// ===============================================
// CTRIPxxFILCTL
#define  SAMPWIN_M(A)  (A << 4)
#define  THRESH_M(A)   (A << 9)
#define  FILINIT_M(A)  (A << 15)

#define  CTRIPxxFILCTL_INIT  SAMPWIN_M(30)  +/*20 */ \
	                         THRESH_M(18)   + /*12*/ \
	                         FILINIT_M(1)
// ===============================================
#define  COMP_FILT_SETUP(CTRIPxxICTL, CTRIPxxFILCLKCTL, CTRIPxxFILCTL)     {                            \
	AnalogSubsysRegs.CTRIPxxICTL.all   = CTRIPxxICTL_INIT;		/* Enable COMPH */					    \
	AnalogSubsysRegs.CTRIPxxFILCLKCTL.bit.CLKPRESCALE = 6;	    /* clock pre-scaling */			    \
	AnalogSubsysRegs.CTRIPxxFILCTL.all = (Uint16)(CTRIPxxFILCTL_INIT);	/* Initialize sample filter */	\
}
// =======================================================================================================
// DACEN
#define  DAC1EN_M(A)  (A << 0)
#define  DAC2EN_M(A)  (A << 1)
#define  DAC5EN_M(A)  (A << 4)

#define  DACEN_INIT  DAC1EN_M(1) +   \
		             DAC2EN_M(1) +   \
		             DAC5EN_M(1)

#define  DACEN_M1_INIT  DAC1EN_M(1) +   \
		                DAC2EN_M(1)

#define  DACEN_PFC_INIT DAC5EN_M(1)

// ===============================================
// PGAEN
#define AMPA1EN_M(A)  (A << 0)
#define AMPA3EN_M(A)  (A << 1)
#define AMPB1EN_M(A)  (A << 2)
#define AMPA6EN_M(A)  (A << 3)
#define AMPB4EN_M(A)  (A << 4)
#define AMPB6EN_M(A)  (A << 5)
#define AMPB7EN_M(A)  (A << 6)

#define PGAEN_INIT    AMPA1EN_M(1) + \
                      AMPA3EN_M(1) + \
                      AMPB1EN_M(1) + \
                      AMPA6EN_M(1) + \
                      AMPB4EN_M(1) + \
                      AMPB6EN_M(1) + \
                      AMPB7EN_M(1)

#define PGAEN_M1_INIT AMPA1EN_M(1) + \
                      AMPA3EN_M(1) + \
                      AMPB1EN_M(1)

#define PGAEN_M2_INIT AMPA6EN_M(1) + \
                      AMPB4EN_M(1) + \
                      AMPB6EN_M(1)

#define PGAEN_PFC_INIT AMPB7EN_M(1)
// ===============================================
// COMPEN
#define COMPB7EN_M(A)  (A << 0)
#define COMPA1EN_M(A)  (A << 2)
#define COMPA3EN_M(A)  (A << 4)
#define COMPB1EN_M(A)  (A << 6)

#define COMPEN_M1_INIT COMPA1EN_M(1) + \
                       COMPA3EN_M(1) + \
                       COMPB1EN_M(1)

#define COMPEN_PFC_INIT COMPB7EN_M(1)

// ===============================================
// AMPM1_GAIN
#define  AMPA1GAIN_M(A)   (A << 0)
#define  AMPA3GAIN_M(A)   (A << 4)
#define  AMPB1GAIN_M(A)   (A << 8)
// Change from 1 to 0
#define  AMPM1_GAIN_INIT  AMPA1GAIN_M(1)  +  \
		                  AMPA3GAIN_M(1)  +  \
		                  AMPB1GAIN_M(1)
// ===============================================
// AMPM2_GAIN
#define  AMPA6GAIN_M(A)   (A << 0)
#define  AMPB4GAIN_M(A)   (A << 4)
#define  AMPB6GAIN_M(A)   (A << 8)

#define  AMPM2_GAIN_INIT  AMPA6GAIN_M(1)  +  \
		                  AMPB4GAIN_M(1)  +  \
		                  AMPB6GAIN_M(1)
// ===============================================
// AMPPFC_GAIN
#define  AMPB7GAIN(A)   (A << 0)

#define  AMPPFC_GAIN_INIT  AMPB7GAIN(1)
// ===============================================
// CTRIPM1OCTL
#define CTRIPA1EN_M(A)     (A << 0)
#define CTRIPA3EN_M(A)     (A << 1)
#define CTRIPB1EN_M(A)     (A << 2)
#define CTRIPA1OUTEN_M(A)  (A << 8)
#define CTRIPA3OUTEN_M(A)  (A << 9)
#define CTRIPB1OUTEN_M(A)  (A << 10)
#define CTRIPOUTPOL_M(A)   (A << 14)
#define CTRIPOUTLATEN_M(A) (A << 15)

#define CTRIPM1OCTL_INIT     CTRIPA1EN_M(1)     + \
                             CTRIPA3EN_M(1)     + \
                             CTRIPB1EN_M(1)     + \
                             CTRIPA1OUTEN_M(1)  + \
                             CTRIPA3OUTEN_M(1)  + \
                             CTRIPB1OUTEN_M(1)  + \
                             CTRIPOUTPOL_M(0)   + \
                             CTRIPOUTLATEN_M(0)
// ===============================================
//CTRIPPFCOCTL
#define CTRIPB7EN_M(A)     (A << 0)
#define CTRIPB7OUTEN_M(A)  (A << 8)
#define CTRIPOUTPOL_M(A)   (A << 14)
#define CTRIPOUTLATEN_M(A) (A << 15)

#define CTRIPPFCOCTL_INIT  CTRIPB7EN_M(1)     + \
                           CTRIPB7OUTEN_M(1)  + \
                           CTRIPOUTPOL_M(0)   + \
                           CTRIPOUTLATEN_M(0)

// ===============================================
//CTRIPM1FLGCLR
#define CTRIPA1FLGCLR_M(A)    (A << 8)
#define CTRIPA3FLGCLR_M(A)    (A << 9)
#define CTRIPB1FLGCLR_M(A)    (A << 10)
#define CTRIPOUTM1FLGCLR_M(A) (A << 15)

#define CTRIPM1FLGCLR_INIT    CTRIPA1FLGCLR_M(1) + \
                              CTRIPA3FLGCLR_M(1) + \
                              CTRIPB1FLGCLR_M(1) + \
                              CTRIPOUTM1FLGCLR_M(1)
// ===============================================
//CTRIPPFCFLGCLR
#define CTRIPB7FLGCLR_M(A)      (A << 8)
#define CTRIPOUTPFCFLGCLR_M(A)  (A << 15)

#define CTRIPPFCFLGCLR_INIT     CTRIPB7FLGCLR_M(1)      + \
                                CTRIPOUTPFCFLGCLR_M(1)
// ===============================================

// ***************************************************************************************************
#define  ANALOGSUBSYS_M1_INIT()                                                                     \
	EALLOW;																							\
																									\
	AnalogSubsysRegs.DACEN.all  |= DACEN_M1_INIT;		    /* Enables DACs for M1    */            \
	AnalogSubsysRegs.PGAEN.all  |= PGAEN_M1_INIT;           /* Enables AMPS for M1    */            \
	AnalogSubsysRegs.COMPEN.all |= COMPEN_M1_INIT;		    /* Enables COMPS for M1   */            \
																									\
	AnalogSubsysRegs.AMPM1_GAIN.all  = AMPM1_GAIN_INIT;		/* OPAMP Gain = 6 - motor 1 */		    \
																									\
	/* Initialize the DAC values */																	\
	AnalogSubsysRegs.DAC1CTL.bit.DACVAL = DAC6bit(2.65);    /* +ve phase current limit - Motor 1 */	\
	AnalogSubsysRegs.DAC2CTL.bit.DACVAL = DAC6bit(0.65);    /* -ve phase current limit - Motor 1 */	\
																									\
	/* Filter Input & function control - Motor 1*/													\
	COMP_FILT_SETUP(CTRIPA1ICTL, CTRIPA1FILCLKCTL, CTRIPA1FILCTL);      /* COMP A1 */               \
	COMP_FILT_SETUP(CTRIPA3ICTL, CTRIPA3FILCLKCTL, CTRIPA3FILCTL);      /* COMP A3 */               \
	COMP_FILT_SETUP(CTRIPB1ICTL, CTRIPB1FILCLKCTL, CTRIPB1FILCTL);      /* COMP B1 */               \
																									\
	AnalogSubsysRegs.CTRIPM1OCTL.all   = (Uint16)(CTRIPM1OCTL_INIT);	/* CTRIP M1 outuput ctrl */	\
	AnalogSubsysRegs.CTRIPM1FLGCLR.all = (Uint16)(CTRIPM1FLGCLR_INIT);	/* Clear flags */			\
																									\
    EDIS;																							\

// ***************************************************************************************************
#define  ANALOGSUBSYS_M2_INIT()                                                                     \
	EALLOW;																							\
																									\
	AnalogSubsysRegs.PGAEN.all  |= PGAEN_M2_INIT            /* Enables AMPS for M2      */          \
	AnalogSubsysRegs.AMPM2_GAIN.all  = AMPM2_GAIN_INIT;	    /* OPAMP Gain = 6 : motor 2 */		    \
																									\
    EDIS;																							\

// ***************************************************************************************************
#define  ANALOGSUBSYS_PFC_INIT()                                                                    \
	EALLOW;																							\
																									\
	AnalogSubsysRegs.DACEN.all  |= DACEN_PFC_INIT;		/* Enables DAC 1 thru 5 M1/M2/PFC DAC's */	\
	AnalogSubsysRegs.PGAEN.all  |= PGAEN_PFC_INIT;		/* Enables AMPS for PFC               */    \
	AnalogSubsysRegs.COMPEN.all |= COMPEN_PFC_INIT;		/* Enables COMPS for PFC              */    \
																									\
	AnalogSubsysRegs.AMPPFC_GAIN.all = AMPPFC_GAIN_INIT;	/* OPAMP Gain = 6 - PFC */		        \
																									\
	AnalogSubsysRegs.DAC5CTL.bit.DACVAL = DAC6bit(0.65);    /* Init DAC: -ve current limit - PFC */	\
																									\
    /*Filter Input & function control - PFC (B7)*/													\
    AnalogSubsysRegs.CTRIPB7ICTL.all    = CTRIPB7ICTL_INIT;											\
    AnalogSubsysRegs.CTRIPB7FILCLKCTL.bit.CLKPRESCALE = 0;	    /* No clock pre-scaling */			\
    AnalogSubsysRegs.CTRIPB7FILCTL.all  = (Uint16)(CTRIPxxFILCTL_INIT);   /* Init sample filter */	\
    AnalogSubsysRegs.CTRIPPFCOCTL.all   = (Uint16)(CTRIPPFCOCTL_INIT);	/* CTRIP PFC outuput ctrl */\
    AnalogSubsysRegs.CTRIPPFCFLGCLR.all = (Uint16)(CTRIPPFCFLGCLR_INIT);  /* Clear flags */			\
    EDIS;																							\

// ***************************************************************************************************
#define ANALOGSUBSYS_INIT_MACRO()															        \
	EALLOW;																							\
																									\
	AnalogSubsysRegs.DACEN.all = 0;			                /* Disable all DACs  */	                \
						              /* OFF '0' in internal gain mode, ON '1' in external gain */  \
	AnalogSubsysRegs.PGAEN.all = 0;                         /* Disable all OPAMPS  */               \
	AnalogSubsysRegs.COMPEN.all = 0;		                /* Disable all COMPS   */               \
																									\
	AnalogSubsysRegs.VREFOUTEN.bit.DACVREFOUTEN = 1;		/* VREFOUT DAC enable -- */				\
	AnalogSubsysRegs.VREFOUTCTL.bit.DACVAL = DAC6bit(1.65); /* Init DAC for 1.65V Ref Gen */	    \
	                                                                                                \
	ANALOGSUBSYS_M1_INIT();																			\
	ANALOGSUBSYS_PFC_INIT();																		\
    EDIS;																							\

// ***************************************************************************************************
// ***************************************************************************************************

#endif  // __F2805X_analog_H__
