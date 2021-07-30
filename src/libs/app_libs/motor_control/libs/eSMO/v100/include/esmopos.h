/* =================================================================================
File name:       ESMOPOS.H
==================================================================================*/
#ifndef __ESMOPOS_H__
#define __ESMOPOS_H__

#include "IQmathLib.h"
#include "pi.h"

typedef struct {  _iq  Valpha;   	// Input: Stationary alfa-axis stator voltage 
                  _iq  Ealpha;   	// Variable: Stationary alfa-axis back EMF 
                  _iq  Zalpha;      // Output: Stationary alfa-axis sliding control 
                  _iq  Gsmopos;    	// Parameter: Motor dependent control gain 
                  _iq  EstIalpha;   // Variable: Estimated stationary alfa-axis stator current 
                  _iq  Fsmopos;    	// Parameter: Motor dependent plant matrix 
                  _iq  Vbeta;   	// Input: Stationary beta-axis stator voltage 
                  _iq  Ebeta;  		// Variable: Stationary beta-axis back EMF 
                  _iq  Zbeta;      	// Output: Stationary beta-axis sliding control 
                  _iq  EstIbeta;    // Variable: Estimated stationary beta-axis stator current 
                  _iq  Ialpha;  	// Input: Stationary alfa-axis stator current 
                  _iq  IalphaError; // Variable: Stationary alfa-axis current error                 
                  _iq  Kslide;     	// Parameter: Sliding control gain 
                  _iq  Ibeta;  		// Input: Stationary beta-axis stator current 
                  _iq  IbetaError;  // Variable: Stationary beta-axis current error                 
                  _iq  Kslf;       	// Parameter: Sliding control filter gain 
                  _iq  Theta;     	// Output: Compensated rotor angle
                  _iq  E0;			// Parameter: 0.5

                  _iq  smoFreq;     // smo filter frequency
                  _iq  smoShift;    // phase shift due to smo filter
                  _iq  runSpeed;    // running electrical speed of motor
                  _iq  cmdSpeed;    // commanded speed of motor

                  _iq  base_wTs;    // base_wTs = BASE_FREQ * T ,for lib
				 } ESMOPOS;

typedef    ESMOPOS *  ESMOPOS_HANDLE;

/*-----------------------------------------------------------------------------
Default initalizer for the SMOPOS object.
-----------------------------------------------------------------------------*/
#define ESMOPOS_DEFAULTS {  0,0,0,0,0,0,0,0,0,0,0,  \
	                        0,0,0,0,0,0,_IQ(0.5),   \
	                        0,0,0,0,                \
	                        0 		                \
              			 }

 /*------------------------------------------------------------------------------
 Prototypes for the functions in SMOPOS.C
 ------------------------------------------------------------------------------*/

void eSMO_MODULE(ESMOPOS *v);
_iq  angleFilter(PI_CONTROLLER *v, ESMOPOS *s);

#endif

