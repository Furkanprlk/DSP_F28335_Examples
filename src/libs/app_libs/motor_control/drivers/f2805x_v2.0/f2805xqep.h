/* =================================================================================
File name:        F2805XQEP.H
Target   : 		  F2805x family
===================================================================================*/

#ifndef __F2805X_QEP_H__
#define __F2805X_QEP_H__

#include "f2805xbmsk.h"
#include "f2805xdrvlib.h"


/*-----------------------------------------------------------------------------
    Initialization states for EQEP Decode Control Register
------------------------------------------------------------------------------*/
#define QDECCTL_INIT_STATE     ( XCR_X2 + QSRC_QUAD_MODE )

/*-----------------------------------------------------------------------------
    Initialization states for EQEP Control Register
------------------------------------------------------------------------------*/
#define QEPCTL_INIT_STATE      ( QEP_EMULATION_FREE + \
                                 PCRM_INDEX + \
                                 IEI_RISING + \
                                 IEL_RISING + \
                                 QPEN_ENABLE + \
                                 QCLM_TIME_OUT + \
                                 UTE_ENABLE )  

/*-----------------------------------------------------------------------------
    Initialization states for EQEP Position-Compare Control Register
------------------------------------------------------------------------------*/
#define QPOSCTL_INIT_STATE      PCE_DISABLE 

/*-----------------------------------------------------------------------------
    Initialization states for EQEP Capture Control Register
------------------------------------------------------------------------------*/
#define QCAPCTL_INIT_STATE     ( UPPS_X32 + \
                                 CCPS_X128 + \
                                 CEN_ENABLE )

/*-----------------------------------------------------------------------------
Define the structure of the QEP (Quadrature Encoder) Driver Object 
-----------------------------------------------------------------------------*/
typedef struct {int32 ElecTheta;        // Output: Motor Electrical angle (Q24)
                int32 MechTheta;        // Output: Motor Mechanical Angle (Q24) 
                Uint16 DirectionQep;    // Output: Motor rotation direction (Q0)
                Uint16 QepPeriod;       // Output: Capture period of QEP signal in number of EQEP capture timer (QCTMR) period  (Q0)
                Uint32 QepCountIndex;   // Variable: Encoder counter index (Q0) 
                 int32 RawTheta;        // Variable: Raw angle from EQEP Postiion counter (Q0)
                Uint32 MechScaler;      // Parameter: 0.9999/total count (Q30) 
                Uint16 LineEncoder;     // Parameter: Number of line encoder (Q0) 
                Uint16 PolePairs;       // Parameter: Number of pole pairs (Q0) 
                 int32 CalibratedAngle; // Parameter: Raw angular offset between encoder index and phase a (Q0)
                Uint16 IndexSyncFlag;   // Output: Index sync status (Q0) 
                }  QEP;

/*-----------------------------------------------------------------------------
Default initializer for the QEP Object.
-----------------------------------------------------------------------------*/
#define QEP_DEFAULTS { 0x0,0x0,0x0,0x0,0x0,0x0,0x00020000,0x0,2,0,0x0}   

/*-----------------------------------------------------------------------------
	QEP Init and QEP Update Macro Definitions                                 
-----------------------------------------------------------------------------*/

#define QEP_INIT_MACRO(m,v)																	\
																								\
     (*eQEP[m]).QDECCTL.all = QDECCTL_INIT_STATE;												\
     (*eQEP[m]).QEPCTL.all = QEPCTL_INIT_STATE;													\
     (*eQEP[m]).QPOSCTL.all = QPOSCTL_INIT_STATE;												\
     (*eQEP[m]).QUPRD = 600000;		        	/* Unit Timer for 100Hz*/						\
     (*eQEP[m]).QCAPCTL.all = QCAPCTL_INIT_STATE;												\
     (*eQEP[m]).QPOSMAX = 4*v.LineEncoder;														\
																								
//Make sure that the pin configuration is properly done in ...-DevInit_F2805x.c file like below
/*   EALLOW;                        		Enable EALLOW											
     GpioCtrlRegs.GPAMUX2.bit.GPIO20 = 1;   GPIO20 is EQEP1A 								
     GpioCtrlRegs.GPAMUX2.bit.GPIO21 = 1;   GPIO21 is EQEP1B 								
     GpioCtrlRegs.GPAMUX2.bit.GPIO23 = 1;   GPIO23 is EQEP1I  								
  	 EDIS;                          		Disable EALLOW							
*/ 

#define QEP_MACRO(m,v)																		\
																								\
/* Check the rotational direction */															\
     v.DirectionQep = (*eQEP[m]).QEPSTS.bit.QDF;												\
																								\
/* Check the position counter for EQEP1 */														\
     v.RawTheta = (*eQEP[m]).QPOSCNT + v.CalibratedAngle;										\
     																							\
     if (v.RawTheta < 0)																		\
       v.RawTheta = v.RawTheta + (*eQEP[m]).QPOSMAX;											\
     else if (v.RawTheta > (*eQEP[m]).QPOSMAX)													\
       v.RawTheta = v.RawTheta - (*eQEP[m]).QPOSMAX;											\
       																							\
/* Compute the mechanical angle in Q24 */														\
     v.MechTheta = __qmpy32by16(v.MechScaler,(int16)v.RawTheta,31);  /* Q15 = Q30*Q0 */			\
     v.MechTheta &= 0x7FFF;                                          /* Wrap around 0x07FFF*/	\
     v.MechTheta <<= 9;                                              /* Q15 -> Q24 */			\
																								\
/* Compute the electrical angle in Q24 */														\
     v.ElecTheta = v.PolePairs*v.MechTheta;            /* Q24 = Q0*Q24 */						\
     v.ElecTheta &= 0x00FFFFFF;                        /* Wrap around 0x00FFFFFF*/				\
																								\
/* Check an index occurrence*/																	\
     if ((*eQEP[m]).QFLG.bit.IEL == 1)    														\
     {  																						\
     	v.IndexSyncFlag = 0x00F0;																\
        v.QepCountIndex = (*eQEP[m]).QPOSILAT;													\
    	(*eQEP[m]).QCLR.bit.IEL = 1;	/* Clear interrupt flag */								\
     }																							\

// ================== Use the code sbippet below for low speed operation =======================\
																								\
/* Check unit Time out-event for speed calculation: */											\
/* Unit Timer is configured for 100Hz in INIT function*/										\
	if((*eQEP[m]).QFLG.bit.UTO == 1)															\
    {																							\
     		/***** Low Speed Calculation   ****/												\
   		if(((*eQEP[m]).QEPSTS.bit.COEF || (*eQEP[m]).QEPSTS.bit.CDEF))							\
  		{	/* Capture Counter overflowed, hence do no compute speed*/							\
  			(*eQEP[m]).QEPSTS.all = 0x000C;														\
   		}																						\
   		else if((*eQEP[m]).QCPRDLAT!=0xffff)													\
   			/* Compute lowspeed using capture counter value*/									\
   			v.QepPeriod = (*eQEP[m]).QCPRDLAT;													\
    }

#endif // __F2805X_QEP_H__




