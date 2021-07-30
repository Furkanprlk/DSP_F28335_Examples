/* ==================================================================================
File name: F2833XCAP.H                     
Target	 : TMS320F2833X family
              
===================================================================================*/

#ifndef __F2833X_CAP_H__
#define __F2833X_CAP_H__

#include "f2833xbmsk.h"
#include "f2833xdrvlib.h"

/*-----------------------------------------------------------------------------
    Initialization states for ECAP Control Registers 1 and 2 for ECAP1
------------------------------------------------------------------------------*/
#define ECCTL1_INIT_STATE   ( CAP1POL_RISING_EDGE +  \
                              CAPLDEN_ENABLE + \
                              CTRRST1_DIFFERENCE_TS + \
                              EVTFLTPS_X_1 + \
                              EMULATION_FREE  )

#define ECCTL2_INIT_STATE   ( CONTINUOUS_MODE + \
                              TSCNTSTP_FREE + \
                              SYNCI_DISABLE + \
                              SYNCO_DISABLE + \
                              CAPTURE_MODE )

/*-----------------------------------------------------------------------------
Define the structure of the Capture Driver Object 
------------------------------------------------------------------------------*/
typedef struct { int32 EventPeriod;    // Output: Timer value difference between two edges detected (Q0) 
               	 Uint16 CapReturn;
               } CAPTURE;

/*------------------------------------------------------------------------------
Default Initializer for the F2833X CAPTURE Object
------------------------------------------------------------------------------*/
#define F2833XCAP1       {1,0 \
                         }

/*------------------------------------------------------------------------------
Target Independent Default Initializer CAPTURE Object
------------------------------------------------------------------------------*/
#define CAPTURE_DEFAULTS  F2833XCAP1

/*------------------------------------------------------------------------------
	CAP_INIT & CAP Macro Definitions
------------------------------------------------------------------------------*/                                             

#define CAP_INIT_MACRO(n)											\
    /* Init ECAP Control Registers 1 and 2 for ECAP1*/				\
    (*eCAP[n]).ECCTL1.all = ECCTL1_INIT_STATE;						\
    (*eCAP[n]).ECCTL2.all = ECCTL2_INIT_STATE;						\
																	\
    EALLOW;                       /* Enable EALLOW */				\

//Make sure that the GPIO configuration is properly done in ...-DevInit_F2803x.c file as shown below\
    /* Set up the ECAP1 pin to primary function*/					\
    GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 1;  /* GPIO24 is ECAP1 */		\
    EDIS;                         /* Disable EALLOW	*/				

	
	
#define CAP_MACRO(n,v)																					\
    if((*eCAP[n]).ECFLG.bit.CEVT1 != 0)/* Check status of one entry of first event of ECAP1 pin */		\
    {																									\
    v.EventPeriod = (*eCAP[n]).CAP1;  /* Stamp the timer counter difference between two edges detected*/	\
    v.CapReturn=0;                   /* Then, return zero*/												\
    } 																									\
    else																								\
    {																									\
    v.CapReturn=1;                   /* Else, return one */												\
    }


#endif //  __F2833X_CAP_H__




