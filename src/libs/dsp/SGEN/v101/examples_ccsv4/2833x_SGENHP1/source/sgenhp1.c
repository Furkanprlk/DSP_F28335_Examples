// =====================================================================================
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// -------------------------------------------------------------------------------------
//          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
//                          All Rights Reserved.
//======================================================================================
/* ==============================================================================

System Name:    Signal Generator Module demo 

File Name:      SGENHP1.C

Description:    Primary System file for demonstrating the Signal Generator module

Originator:     Digital control systems Group - Texas Instruments

Target dependency:  C28x

Description:
============

   The "C" frame work, for demonstrating the signal generator module is given below
                 ___________           _____________
                |           |         |             |
                |           | X1=OUT  |   EVMDAC    |
                |  SGENHP_1 |-------->|   DLOG_4CH  |
                |           |         |   PWMDAC    |
                |___________|         |_____________|

*/
//######################################################################################
// $TI Release: C28x SGEN Library Version v1.01 $
// $Release Date: September 30, 2011 $
//######################################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include <sgen.h>

#define SIGNAL_LENGTH 512
   
/* Create an instance of Signal generator module    */
SGENHP_1 sgen = SGENHP_1_DEFAULTS;

#pragma DATA_SECTION(ipcb, "SGENipcb");
int ipcb[SIGNAL_LENGTH];
         
/* Temp variable to store the signal genr output    */   
int x1;
     
void main()
{    
	   unsigned long i;

  	   InitSysCtrl();
	   DINT;
	   InitPieCtrl();
	   IER = 0x0000;
	   IFR = 0x0000;
	   InitPieVectTable();
	   EINT;   // Enable Global interrupt INTM
	   ERTM;   // Enable Global realtime interrupt DBGM
	     
/* Signal Generator module initialisation   */ 
       sgen.offset=0;
       sgen.gain=0x7fff;        /* gain=1 in Q15                              */
       sgen.freq=0x14F8CF92;    /* freq = (Required Freq/Max Freq)*2^31       */
                                /*      = (50/305.17)*2^31 = 0x14f8cf92       */         
       sgen.step_max=0x3E7FB26; /* Max Freq= (step_max * sampling freq)/2^32 */
                                /* Max Freq = (0x3E7FB26*20k)/2^32 = 305.17  */
       sgen.alpha=536870912;    		/* phase_norm =(pi/4/(2*pi))*2^16=8192   */
            
        for(i=0;i<SIGNAL_LENGTH;i++)
        {
        	ipcb[i]=0;
        }

        for(i=0;i<SIGNAL_LENGTH;i++)
        {
            sgen.calc(&sgen);
            x1=sgen.out;
            ipcb[i]=x1;
        }   
        
        for(;;);    

} /* End: main() */

             





