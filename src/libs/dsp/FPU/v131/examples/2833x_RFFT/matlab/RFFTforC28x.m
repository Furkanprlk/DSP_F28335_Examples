% // TI File $Revision: /main/3 $
% // Checkin $Date: September 15, 2010   13:05:07 $
% // ======================================================================
% //  This software is licensed for use with Texas Instruments C28x
% //  family DSCs.  This license was provided to you prior to installing
% //  the software.  You may review this license by consulting a copy of
% //  the agreement in the doc directory of this library.
% //-----------------------------------------------------------------------
% //          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
% //                          All Rights Reserved.
% //=======================================================================
% //
% // 	FILE:    RFFTforC28x.m
% //
% // 	TITLE:   DSP2833x Device Real FFT Test Program.   
% //
% //
% // 	ASSUMPTIONS:
% //
% //   	This matlab code is reference code for debugging FPU library
% //    function RFFT_f32 and example project 2833x_RFFT. 
% //
% //   
% //   	Minimum RFFT_Stages is 5.
% //
% //   
% //    Watch Variables:
% //
% //      Rx                Input signal
% //      X                 Output
% //
% //#######################################################################
% // $TI Release: C28x FPU Library v1.10 $
% // $Release Date: September 15, 2011 $
% //#######################################################################

clear all
close all

disp('this is Matlab version of C28x RFFT code');
disp('The result is stored in array X');
disp('The signal is stored in array Rx');

RadStep = 0.1963495408494;

stages=input('Please enter stages (>=3) =');
N=2^stages;
halfSize=N-1;

Rad=[0:RadStep:(halfSize)*RadStep];

Rx=sin(Rad)+cos(Rad*2.3567);

X=fft(Rx);
figure,plot(real(X(1: (length(X)/2) )));
grid on;