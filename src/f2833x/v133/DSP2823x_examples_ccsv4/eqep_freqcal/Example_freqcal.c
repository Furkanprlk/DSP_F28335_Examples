//###########################################################################
//
// FILE:	Example_freqcal.c
//
// TITLE:	Frequency measurement using EQEP peripheral
//
// DESCRIPTION:
//
// This file includes the EQEP initialization and frequency calcuation
// functions called by Example_2823xEqep_freqcal.c.  The frequency calculation
// steps performed by FREQCAL_Calc()at  SYSCLKOUT = 150 MHz and 100 MHz are
// described below:
//
// For 150 MHz Operation:
// ----------------------
//
// 1. This program calculates: **freqhz_fr**
//    freqhz_fr or v = (x2-x1)/T                                                 - Equation 1
//
// If max/base freq = 10kHz:   10kHz = (x2-x1)/(2/100Hz)                         - Equation 2
//                      max (x2-x1) = 200 counts = freqScaler_fr
//		Note: T = 2/100Hz. 2 is from (x2-x1)/2 - because QPOSCNT counts 2 edges per cycle
//		                                         (rising and falling)
//
// If both sides of Equation 2 are divided by 10 kHz, then:
//                            1 = (x2-x1)/[10kHz*(2/100Hz)] where [10kHz* (2/100Hz)] = 200
//							Because (x2-x1) must be <200 (max),
//						    (x2-x1)/200 < 1 for all frequencies less than max
//							freq_fr = (x2-x1)/200 or (x2-x1)/[10kHz*(2/100Hz)]    - Equation 3
//
// To get back to original velocity equation, Equation 1, multiply Equation 3 by 10 kHz
//                           freqhz_fr (or velocity) = 10kHz*(x2-x1)/[10kHz*(2/100Hz)]
//						                           = (x2-x1)/(2/100Hz)           - Final equation
//
// 2. min freq = 1 count/(2/100Hz) = 50 Hz
//
// 3. **freqhz_pr**
//    freqhz_pr or v = X/(t2-t1)                                                 - Equation 4
//
// If max/base freq = 10kHz:  10kHz = (4/2)/T = 4/2T
//    where 4 = QCAPCTL [UPPS] (Unit timeout - once every 4 edges)
//		    2 = divide by 2 because QPOSCNT counts 2 edges per cycle (rising and falling)
//		    T = time in seconds
//            = t2-t1/(150MHz/128),  t2-t1= # of QCAPCLK cycles, and
//		                  1 QCAPCLK cycle = 1/(150MHz/128)
//										  = QCPRDLAT
//
//		        So: 10 kHz = 4(150MHz/128)/2(t2-t1)
//		             t2-t1 = 4(150MHz/128)/(10kHz*2) = (150MHz/128)/(2*10kHz/4)  - Equation 5
//		                   = 234 QCAPCLK cycles = maximum (t2-t1) = freqScaler_pr
//
// Divide both sides by (t2-t1), and:
//                   1 = 234/(t2-t1) = [150MHz/128)/(2*10kHz/4)]/(t2-t1)
//				     Because (t2-t1) must be <234 (max).
//				     234/(t2-t1) < 1 for all frequencies less than max
//					 freq_pr = 234/(t2-t1) or [150MHz/128)/(2*10kHz/4)]/(t2-t1)  - Equation 6
// Now within velocity limits, to get back to original velocity equation, Equation 1,
// multiply Equation 6 by 10 kHz:
//                  freqhz_fr (or velocity) = 10kHz*[150MHz/128)/(2*10kHz/4)]/(t2-t1)
//							                = (105MHz/128)*4/[2(t2-t1)]
//                                            or 4/[2*(t2-t1)(QCPRDLAT)]        - Final Equation
//
//
// For 100 MHz Operation:
// ----------------------
//
// The same calculations as above are performed, but with 100 MHz
// instead of 150MHz when calculating freqhz_pr, and at UPPS of 8 instead of 4.
// The value for freqScaler_pr becomes: (100MHz/128)/(2*10kHz/8) = 313
// More detailed calculation results can be found in the Example_freqcal.xls
// spreadsheet included in the example folder.
//
//
// This file contains source for the freq calculation module
//
//###########################################################################
// Original Author: SD
//
// $TI Release: 2833x/2823x Header Files and Peripheral Examples V133 $
// $Release Date: June 8, 2012 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Example_freqcal.h"    // Example specific include file

void  FREQCAL_Init(void)
{
    #if (CPU_FRQ_150MHZ)
	  EQep1Regs.QUPRD=1500000;			// Unit Timer for 100Hz at 150MHz SYSCLKOUT
	#endif
    #if (CPU_FRQ_100MHZ)
	  EQep1Regs.QUPRD=1000000;			// Unit Timer for 100Hz at 100MHz SYSCLKOUT
	#endif

	EQep1Regs.QDECCTL.bit.QSRC=2;		// Up count mode (freq. measurement)
	EQep1Regs.QDECCTL.bit.XCR=0;        // 2x resolution (cnt falling and rising edges)

	EQep1Regs.QEPCTL.bit.FREE_SOFT=2;
	EQep1Regs.QEPCTL.bit.PCRM=00;		// QPOSCNT reset on index evnt
	EQep1Regs.QEPCTL.bit.UTE=1; 		// Unit Timer Enable
	EQep1Regs.QEPCTL.bit.QCLM=1; 		// Latch on unit time out
	EQep1Regs.QPOSMAX=0xffffffff;
	EQep1Regs.QEPCTL.bit.QPEN=1; 		// QEP enable

	#if (CPU_FRQ_150MHZ)
	  EQep1Regs.QCAPCTL.bit.UPPS=2;   	// 1/4 for unit position at 150MHz SYSCLKOUT
	#endif
	#if (CPU_FRQ_100MHZ)
	  EQep1Regs.QCAPCTL.bit.UPPS=3;   	// 1/8 for unit position at 100MHz SYSCLKOUT
	#endif

	EQep1Regs.QCAPCTL.bit.CCPS=7;		// 1/128 for CAP clock
	EQep1Regs.QCAPCTL.bit.CEN=1; 		// QEP Capture Enable

}

void FREQCAL_Calc(FREQCAL *p)
{
     unsigned long tmp;
   	 _iq newp,oldp;


//**** Freq Calcultation using QEP position counter ****//
// Check unit Time out-event for speed calculation:
// Unit Timer is configured for 100Hz in INIT function

// For a more detailed explanation of the calculation, read
// the description at the top of this file

	if(EQep1Regs.QFLG.bit.UTO==1)                  // Unit Timeout event
	{
		/** Differentiator	**/
	 	newp=EQep1Regs.QPOSLAT;                    // Latched POSCNT value
		oldp=p->oldpos;

    	if (newp>oldp)
      		tmp = newp - oldp;                     // x2-x1 in v=(x2-x1)/T equation
    	else
      		tmp = (0xFFFFFFFF-oldp)+newp;

		p->freq_fr = _IQdiv(tmp,p->freqScaler_fr); // p->freq_fr = (x2-x1)/(T*10KHz)
		tmp=p->freq_fr;

		if (tmp>=_IQ(1))          // is freq greater than max freq (10KHz for this example)?
	 		p->freq_fr = _IQ(1);
		else
	 		p->freq_fr = tmp;

		p->freqhz_fr = _IQmpy(p->BaseFreq,p->freq_fr); 	// Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q
		                                                // p->freqhz_fr = (p->freq_fr)*10kHz = (x2-x1)/T

		// Update position counter
    	p->oldpos = newp;
		//=======================================

		EQep1Regs.QCLR.bit.UTO=1;					// Clear interrupt flag
	}

//**** Freq Calcultation using QEP capture counter ****//
	if(EQep1Regs.QEPSTS.bit.UPEVNT==1)              // Unit Position Event
	{
		if(EQep1Regs.QEPSTS.bit.COEF==0)            // No Capture overflow
			tmp=(unsigned long)EQep1Regs.QCPRDLAT;
		else							            // Capture overflow, saturate the result
			tmp=0xFFFF;

		p->freq_pr = _IQdiv(p->freqScaler_pr,tmp);  // p->freq_pr = X/[(t2-t1)*10KHz]
		tmp=p->freq_pr;

		if (tmp>_IQ(1))
	 		p->freq_pr = _IQ(1);
		else
	 		p->freq_pr = tmp;

		p->freqhz_pr = _IQmpy(p->BaseFreq,p->freq_pr); 	// Q0 = Q0*GLOBAL_Q => _IQXmpy(), X = GLOBAL_Q
	                                                    // p->freqhz_pr =( p->freq_pr)*10kHz = X/(t2-t1)
		EQep1Regs.QEPSTS.all=0x88;					    // Clear Unit position event flag
												     	// Clear overflow error flag
	}


}


