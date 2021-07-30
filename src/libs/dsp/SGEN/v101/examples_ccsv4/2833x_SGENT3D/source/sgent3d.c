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

File Name:      SGENT3D.C

Description:    Primary System file for demonstrating the Signal Generator module

Originator:     Digital control systems Group - Texas Instruments

Target dependency:  C28x

Description:
============

   The "C" frame work, for demonstrating the signal generator module is given below
                             ___________________                     __________________
                            |                   |     x11=OUT11     |                  |
                            |                   |------o----------->|                  |
                            |                   |     x12=OUT12     |                  |
        phase   o---------->|                   |------o----------->|                  |
                            |                   |     x13=OUT13     |   PWMDAC         |
        gain    o---------->|                   |------o----------->|                  |
                            |                   |                   |   EVMDAC         |
        offset  o---------->|     SGENT_3D      |     x21=OUT21     |                  |
                            |                   |----o------------->|   DLOG_4CH       |
        freq    o---------->|                   |     x22=OUT22     |                  |
                            |                   |----o------->      |                  |
                            |                   |     x23=OUT23     |                  |
                            |                   |----o------->      |                  |
                            |                   |                   |                  |
                            |___________________|                   |__________________|

*/
//######################################################################################
// $TI Release: C28x SGEN Library Version v1.01 $
// $Release Date: September 30, 2011 $
//######################################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include <sgen.h>

#define SIGNAL_LENGTH 512
   
/* Create an instance of Signal generator module    */
SGENT_3D sgen = SGENT_3D_DEFAULTS;

#pragma DATA_SECTION(ipcb1, "ipcb1");
#pragma DATA_SECTION(ipcb2, "ipcb2");
#pragma DATA_SECTION(ipcb3, "ipcb3");
#pragma DATA_SECTION(ipcb4, "ipcb4");
#pragma DATA_SECTION(ipcb5, "ipcb5");
#pragma DATA_SECTION(ipcb6, "ipcb6");
int ipcb1[SIGNAL_LENGTH];
int ipcb2[SIGNAL_LENGTH];
int ipcb3[SIGNAL_LENGTH];
int ipcb4[SIGNAL_LENGTH];
int ipcb5[SIGNAL_LENGTH];
int ipcb6[SIGNAL_LENGTH];
         
/* Temp variable to store the signal genr output */   
int x11,x12,x13,x21,x22,x23 ;
     
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
       sgen.phase=0x4000;       /* Phase= (required Phase)/180 in Q15 format  */    
                                /*      =  (+90/180) in Q15 = 4000h           */
        
       for(i=0;i<SIGNAL_LENGTH;i++)
       {
        	ipcb1[i]=0;
        	ipcb2[i]=0;
        	ipcb3[i]=0;
        	ipcb4[i]=0;
        	ipcb5[i]=0;
        	ipcb6[i]=0;
       }     
              

/*---------------------------------------------------------------------------
    Nothing running in the background at present           
----------------------------------------------------------------------------*/

        for(i=0;i<SIGNAL_LENGTH;i++) 
        {
            sgen.calc(&sgen);
            x11=sgen.out11; 
            x12=sgen.out12;
            x13=sgen.out13;
            x21=sgen.out21; 
            x22=sgen.out22;
            x23=sgen.out23;
            ipcb1[i]=x11;
            ipcb2[i]=x12;
            ipcb3[i]=x13;
            ipcb4[i]=x21;
            ipcb5[i]=x22;
            ipcb6[i]=x23;
        }  
        
        for(;;);      

} /* End: main() */

             





