// TI File $Revision: /main/1 $
// Checkin $Date: July 10, 2008   10:34:12 $
//############################################################################
//
// FILE:    fastRTS.c
//
// TITLE:   fastRTS Program
//
//############################################################################
// $TI Release: FastRTS library V1.00$
// $Release Date: June 15, 2010 $
//###########################################################################


// Include The Following Definition Files:
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "C28x_FPU_FastRTS.h"

void done(void);
//
// Specify the data logging size:
//
#define DATA_LOG_SIZE   64

//
// Define constants used:
//
#define PI2             1.570796327
#define PI              3.141592654
#define STEP_X_SIZE     0.314159265
#define STEP_Y_SIZE     0.314159265

//
// Allocate data log buffers:
//
struct  DATA_LOG_C {
    float   SINwaveform[DATA_LOG_SIZE];
    float   COSwaveform[DATA_LOG_SIZE];
    float   ATANwaveform[DATA_LOG_SIZE];
    long    Phase[DATA_LOG_SIZE];
    float   Mag[DATA_LOG_SIZE];
} Dlog;

//
// Define waveform global variables:
//
struct  STEP {
    float   Xsize;
    float   Ysize;
    float   Yoffset;
    float   X;
    float   Y;
    float   Z;
    float   GainX;
    float   GainY;
    float   FreqX;
    float   FreqY;
} Step;

//----------------------------------------------------------------------------
// Main code:
//----------------------------------------------------------------------------
int main(void)
{
    unsigned int  i;

    float tempX, tempY, tempM, tempMmax;
    int *WatchdogWDCR = (void *) 0x7029; 

    // Disable the watchdog:
    asm(" EALLOW ");
    *WatchdogWDCR = 0x0068;
    asm(" EDIS ");
    
    tempX = 

    Step.Xsize = STEP_X_SIZE;
    Step.Ysize = STEP_Y_SIZE;
    Step.Yoffset = 0;
    Step.X = 0;
    Step.Y = Step.Yoffset;

    // Fill the buffers with some initial value
    for(i=0; i < DATA_LOG_SIZE; i++)
    {
        Dlog.SINwaveform[i] = 0.0;
        Dlog.COSwaveform[i] = 0.0;
        Dlog.ATANwaveform[i] = 0.0;
        Dlog.Mag[i] = 0.0;
        Dlog.Phase[i] = 0.0;
    }

    Step.GainX = 1.5;
    Step.FreqX = .5;
    Step.GainY = 2.5;
    Step.FreqY = 1.0;    

    // Calculate maximum magnitude value:
    tempMmax = sqrt(Step.GainX*Step.GainX + Step.GainY*Step.GainY);

    for(i=0; i < DATA_LOG_SIZE; i++)
    {
    	//
        // Create a sin and cos waveform
        //
        Dlog.SINwaveform[i] = tempX = (sin(Step.X) * Step.GainX);
        Dlog.COSwaveform[i] = tempY = (cos(Step.Y) * Step.GainY);

        // Calculate:
        //
        // Mag = sqrt(X^2 + Y^2)/sqrt(GainX^2 + GainY^2);
        
        tempM = sqrt(tempX*tempX * tempY*tempY);
        Dlog.Mag[i] = tempM/tempMmax;


        // Update Step:
        Step.X = Step.X + (Step.Xsize * Step.FreqX);
        if( Step.X > (2.0*PI) )
        {      
        	Step.X -= (2.0*PI);
        }

        Step.Y = Step.Y + (Step.Ysize * Step.FreqY);
        if( Step.Y > (2.0*PI) )
        {      
        	Step.Y -= (2.0*PI);
        }

    }
   
   //
   // Create an atan waveform 
   //
   Step.Z = -10.0;
   for(i=0; i < DATA_LOG_SIZE; i++)
   {
        Dlog.ATANwaveform[i] = atan(Step.Z);
        Step.Z += 20.0/DATA_LOG_SIZE;
    }    
    
    
    done();
}

void done()
{
   asm("   ESTOP0");
}

//############################################################################
// No more.
//############################################################################
