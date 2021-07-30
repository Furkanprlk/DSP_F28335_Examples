%//#############################################################################
%//! \file /2837x_RFFT_ADC/matlab/RFFTAdcforC28x.m
%//!
%//! \brief  MATLAB code for the Real Fast Fourier Transform (real-time ADC)
%//! \author C2000
%//!  This matlab code is reference code for debugging FPU library
%//!  function RFFT_adc_f32
%//!   
%//!  Minimum CFFT_Stages is 5. The raw data with 12-bit ADC input format
%//!  is stored in "signal.txt". The data is read out by the matlab fscanf
%//!  function and normalized to the range of 0.0 to 0.1 by dividing by 4096. 
%//!  The real FFT result is stored in the variable X.
%//!
%//!  Watch Variables:
%//!    S               Normalized input signal
%//!    X               Output
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

disp('this is Matlab version of C28x RFFT for 12-bit ADC input');
disp('The result is stored in array X');
disp('The signal is stored in signal.txt ');

stages=input('Please enter stages (>=3) =');
N=2^stages;

fid=fopen('signal.txt')

S=fscanf(fid,'%x');
S=S/4096;

X=fft(S(1:N));


% End of file
