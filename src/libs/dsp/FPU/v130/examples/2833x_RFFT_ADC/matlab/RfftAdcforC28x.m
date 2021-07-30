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
% // 	FILE:    RFFTAdcforC28x.m
% //
% // 	TITLE:   DSP2833x Device Real FFT with 12-bit ADC input Test Program.   
% //
% //
% // 	ASSUMPTIONS:
% //
% //   	This matlab code is reference code for debugging FPU library
% //    function RFFT_adc_f32 and example project 2833x_RFFT_ADC. 
% //
% //   
% //   	Minimum CFFT_Stages is 5. The raw data with 12-bit ADC input format
% //    is stored in signal.txt file. The data is read out by matlab fscanf
% //    function and normlized with 4096. The real FFT result is stored in
% //    variable X.
% //
% //   
% //    Watch Variables:
% //
% //      S                Normalized input signal
% //      X                Output
% //
% //#######################################################################
% // $TI Release: C28x FPU Library v1.10 $
% // $Release Date: September 15, 2011 $
% //#######################################################################

close all
clear all

disp('this is Matlab version of C28x RFFT for 12-bit ADC input');
disp('The result is stored in array X');
disp('The signal is stored in signal.txt ');

stages=input('Please enter stages (>=3) =');
N=2^stages;

fid=fopen('signal.txt')

S=fscanf(fid,'%x');
S=S/4096;

X=fft(S(1:N));