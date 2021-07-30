%//#############################################################################
%//! \file /2837x_WindowedRFFT/matlab/RFFTWindowedforC28x.m
%//!
%//! \brief  MATLAB code for the Real Fast Fourier Transform (Windowed)
%//! \author Vishal Coelho
%//! \date   03/08/2015
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
clc
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

windows = ['barthannwin   ';
    'bartlett      ';
    'blackman      ';
    'blackmanharris';
    'bohmanwin     ';
    'chebwin       ';
    'flattopwin    ';
    'gausswin      ';
    'hamming       ';
    'hann          ';
    'kaiser        ';
    'nuttallwin    ';
    'parzenwin     ';
    'rectwin       ';
    'taylorwin     ';
    'triang        ';
    'tukeywin      '];
i = input('Choose window 1-17: ');
windowHandleName = regexprep(windows(i,:), '\s*', '');
W = window(windowHandleName, N)';
Rx_w = W.*Rx;

X=fft(Rx_w);
figure,plot(real(X(1: (length(X)/2) )));
grid on;

% End of file
