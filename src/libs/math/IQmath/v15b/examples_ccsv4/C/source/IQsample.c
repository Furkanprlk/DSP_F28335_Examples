// TI File $Revision: /main/1 $
// Checkin $Date: July 10, 2008   10:34:12 $
//############################################################################
//
// FILE:    IQsample.c
//
// TITLE:   IQ Math Sample Program In C (for V1.5 of the IQmath library)
//
//############################################################################
// $TI Release: IQmath V1.5a $
// $Release Date: June 2, 2009 $
//###########################################################################

// Select the global Q value to use:
#define GLOBAL_Q    24
long GlobalQ = GLOBAL_Q;      // Used for legacy GEL & Graph Debug.

// Include The Following Definition Files:
#include <stdio.h>
#include <stdlib.h>
#include "IQmathLib.h"

// Specify the data logging size:
#define DATA_LOG_SIZE   64

// Define constants used:
#define PI2             1.570796327
#define PI              3.141592654
#define STEP_X_SIZE     0.314159265
#define STEP_Y_SIZE     0.314159265

// Allocate data log buffers:
struct  DATA_LOG_C {
    _iq   Xwaveform[DATA_LOG_SIZE];
    _iq   Ywaveform[DATA_LOG_SIZE];
    long  Phase[DATA_LOG_SIZE];
    _iq   Mag[DATA_LOG_SIZE];
    _iq   Exp[DATA_LOG_SIZE];
} Dlog;

// Define waveform global variables:
struct  STEP {
    _iq   Xsize;
    _iq   Ysize;
    _iq   Yoffset;
    _iq   X;
    _iq   Y;
    _iq   GainX;
    _iq   GainY;
    _iq   FreqX;
    _iq   FreqY;
} Step;

//----------------------------------------------------------------------------
// Main code:
//----------------------------------------------------------------------------
int main(void)
{
    unsigned int  i;

    _iq tempX, tempY, tempP, tempM, tempMmax;
    char buffer[20];

    int *WatchdogWDCR = (void *) 0x7029;

    // Disable the watchdog:
    asm(" EALLOW ");
    *WatchdogWDCR = 0x0068;
    asm(" EDIS ");

    Step.Xsize = _IQ(STEP_X_SIZE);
    Step.Ysize = _IQ(STEP_Y_SIZE);
    Step.Yoffset = 0;
    Step.X = 0;
    Step.Y = Step.Yoffset;

    // Fill the buffers with some initial value
    for(i=0; i < DATA_LOG_SIZE; i++)
    {
        Dlog.Xwaveform[i] = _IQ(0.0);
        Dlog.Ywaveform[i] = _IQ(0.0);
        Dlog.Mag[i] = _IQ(0.0);
        Dlog.Phase[i] = _IQ(0.0);
        Dlog.Exp[i] = _IQ(0.0);
    }

    // Get user input for gain for X and Y waveform:
    puts("\nEnter waveform X gain (default = 1.0)= ");
    gets(buffer);
    Step.GainX = _atoIQ(buffer);
    if( Step.GainX == 0 )
        Step.GainX = _IQ(1.0);

    puts("\nEnter waveform X freq (default = 1.0)= ");
    gets(buffer);
    Step.FreqX = _atoIQ(buffer);
    if( Step.FreqX == 0 )
        Step.FreqX = _IQ(1.0);

    puts("\nEnter waveform Y gain (default = 1.0)= ");
    gets(buffer);
    Step.GainY = _atoIQ(buffer);
    if( Step.GainY == 0 )
        Step.GainY = _IQ(1.0);

    puts("\nEnter waveform Y freq (default = 1.0)= ");
    gets(buffer);
    Step.FreqY = _atoIQ(buffer);
    if( Step.FreqY == 0 )
        Step.FreqY = _IQ(1.0);

    // Calculate maximum magnitude value:
    tempMmax = _IQmag(Step.GainX, Step.GainY);

    for(i=0; i < DATA_LOG_SIZE; i++)
    {
        // Calculate waveforms:
        Step.X = Step.X + _IQmpy(Step.Xsize, Step.FreqX);
        if( Step.X > _IQ(2*PI) )
            Step.X -= _IQ(2*PI);

        Step.Y = Step.Y + _IQmpy(Step.Ysize, Step.FreqY);
        if( Step.Y > _IQ(2*PI) )
            Step.Y -= _IQ(2*PI);

        Dlog.Xwaveform[i] = tempX = _IQmpy(_IQsin(Step.X), Step.GainX);
        Dlog.Ywaveform[i] = tempY = _IQmpy(_IQabs(_IQsin(Step.Y)), Step.GainY);

        // Calculate normalized magnitude:
        //
        // Mag = sqrt(X^2 + Y^2)/sqrt(GainX^2 + GainY^2);
        tempM = _IQmag(tempX, tempY);
        Dlog.Mag[i] = _IQdiv(tempM, tempMmax);

        // Calculate normalized phase:
        //
        // Phase = (long) (atan2PU(X,Y) * 360);
        tempP = _IQatan2PU(tempY,tempX);
        Dlog.Phase[i] = _IQmpyI32int(tempP, 360);

        // Use the exp function
        Dlog.Exp[i] = _IQexp(_IQmpy(_IQ(.075L),_IQ(i)));
    }
}

//############################################################################
// No more.
//############################################################################
