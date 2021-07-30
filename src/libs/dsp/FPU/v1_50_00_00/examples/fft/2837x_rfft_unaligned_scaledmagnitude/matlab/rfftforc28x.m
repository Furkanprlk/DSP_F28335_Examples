%//#############################################################################
%//! \file /2837x_RFFT/matlab/RFFTforC28x.m
%//!
%//! \brief  MATLAB code for the Real Fast Fourier Transform (unalgined)
%//! with scaled magnitude
%//! \author C2000
%//
%//  Group:             C2000
%//  Target Family:     x86
%//
%// Copyright (C) $YEAR$ Texas Instruments Incorporated - http://www.ti.com/ 
%// ALL RIGHTS RESERVED 
%//#############################################################################
%//$TI Release: $
%//$Release Date: $
%//#############################################################################

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

Magnitude = abs(X)./(2^(stages-1));
Phase = angle(X);

% End of file
