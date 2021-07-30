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

File Name:      SGENT2.C

Description:    Primary System file for demonstrating the Signal Generator module

Originator:     Digital control systems Group - Texas Instruments

Target dependency:  C28x

Description:
============

   The "C" frame work, for demonstrating the signal generator module is given below
                             ___________________                _____________
                            |                   |     x1=out1  |             |
         gain   o---------->|                   |------o------>|  EVMDAC     |
         offset o---------->|       SGENT_2     |     x2=out2  |  PWMDAC     |
        freq    o---------->|                   |------o------>|  DLOG_4CH   |
                            |___________________|              |_____________|

*/
//######################################################################################
// $TI Release: C28x SGEN Library Version v1.01 $
// $Release Date: September 30, 2011 $
//######################################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include <sgen.h>

#define SIGNAL_LENGTH 512
   
/* Create an instance of Signal generator module    */
SGENT_2 sgen = SGENT_2_DEFAULTS;

#pragma DATA_SECTION(ipcb, "SGENipcb");
#pragma DATA_SECTION(ipcbsrc, "SGENipcbsrc");
int ipcb[SIGNAL_LENGTH];
int ipcbsrc[SIGNAL_LENGTH];
         
/* Temp variable to store the signal genr output    */   
int x1,x2;
     
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

/* Signal Generator module initialisation           */ 
       sgen.offset=0;
       sgen.gain=0x7fff;        /* gain=1 in Q15                              */
       sgen.freq=5369;          /* freq = (Required Freq/Max Freq)*2^15       */
                                /*      = (50/305.17)*2^15 = 5369             */         
       sgen.step_max=1000;      /* Max Freq= (step_max * sampling freq)/65536 */
                                /* Max Freq = (1000*20k)/65536 = 305.17       */
       sgen.phase=0x4000;       /* Phase= (required Phase)/180 in Q15 format  */    
                                /*      =  (+90/180) in Q15 = 4000h           */
       sgen.alpha=8192;    		/* phase_norm =(pi/4/(2*pi))*2^16=8192   */
              
       for(i=0;i<SIGNAL_LENGTH;i++)
       {
        	ipcb[i]=0;
        	ipcbsrc[i]=0;
       }

       for(i=0;i<SIGNAL_LENGTH;i++)
       {
            sgen.calc(&sgen);
            x1=sgen.out1; 
            x2=sgen.out2;
            ipcb[i]=x1;
            ipcbsrc[i]=x2;            
       } 
        
       for(;;);         

} /* End: main() */

             





