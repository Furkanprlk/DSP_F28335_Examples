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

File Name:      SGENTI3.C

Description:    Primary System file for demonstrating the Signal Generator module

Originator:     Digital control systems Group - Texas Instruments

Target dependency:  x2407/x241/2/3

Description:
============

   The "C" frame work, for demonstrating the signal generator module is given below
                             ___________________                   ______________
                            |                   |     x1=out1     |              |
                            |                   |------o--------->|  EVMDAC      |
         gain   o---------->|                   |     x2=out2     |  PWMDAC      |
         offset o---------->|     SGENTI_3      |------o--------->|              |
         freq   o---------->|                   |     x3=out3     |  DLOG_4CH    |
                            |                   |------o--------->|              | 
                            |___________________|                 |______________|

*/
//######################################################################################
// $TI Release: C28x SGEN Library Version v1.01 $
// $Release Date: September 30, 2011 $
//######################################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include <sgen.h>

#define SIGNAL_LENGTH 512
    
/* Create an instance of Signal generator module    */
SGENTI_3 sgen = SGENTI_3_DEFAULTS;

#pragma DATA_SECTION(ipcb1, "ipcb1");
#pragma DATA_SECTION(ipcb2, "ipcb2");
#pragma DATA_SECTION(ipcb3, "ipcb3");
int ipcb1[SIGNAL_LENGTH];
int ipcb2[SIGNAL_LENGTH];
int ipcb3[SIGNAL_LENGTH];
         
/* Temp variable to store the signal genr output    */   
int x1,x2,x3;
     
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
       sgen.freq=5369;          /* freq = (Required Freq/Max Freq)*2^15       */
                                /*      = (50/305.17)*2^15 = 5369             */         
       sgen.step_max=1000;      /* Max Freq= (step_max * sampling freq)/65536 */
                                /* Max Freq = (1000*20k)/65536 = 305.17       */
       

       for(i=0;i<SIGNAL_LENGTH;i++)
       {
        	ipcb1[i]=0;
        	ipcb2[i]=0;
        	ipcb3[i]=0;
       }                

/*---------------------------------------------------------------------------
    Nothing running in the background at present           
----------------------------------------------------------------------------*/

        for(i=0;i<SIGNAL_LENGTH;i++)
        {
            sgen.calc(&sgen);
            x1=sgen.out1; 
            x2=sgen.out2;
            x3=sgen.out3;
            ipcb1[i]=x1;
            ipcb2[i]=x2;
            ipcb3[i]=x3;
        }       
        
        for(;;); 

} /* End: main() */

             





