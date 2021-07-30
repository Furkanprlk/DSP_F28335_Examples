% // TI File $Revision: /main/3 $
% // Checkin $Date: November 1, 2010   13:05:07 $
% // =====================================================================================
% //  This software is licensed for use with Texas Instruments C28x
% //  family DSCs.  This license was provided to you prior to installing
% //  the software.  You may review this license by consulting a copy of
% //  the agreement in the doc directory of this library.
% // -------------------------------------------------------------------------------------
% //          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
% //                          All Rights Reserved.
% //======================================================================================
% //
% // 	FILE:    FixedRFFBRevAcq.m
% //
% // 	TITLE:   DSP2833x Device Fixed Point Real Input Point by Point Bit
% //             Reversed Test Program.   
% //
% //
% // 	ASSUMPTIONS:
% //
% //   	This matlab code is reference code for debugging FixedPoint DSP library
% //    module BRevAcq and example project 2833x_FixedPoint_BrevAcq. 
% //
% //
% //   
% //    Watch Variables:
% //
% //      x_raw_sig         Input signal (float)
% //      Rx,Ix				Bit-revesed real and imaginary part of signal
% //                        (Q31)
% //
% //######################################################################################
% // $TI Release: C28x Fixed-Point DSP Library v1.10 $
% // $Release Date: November 1, 2011 $
% //######################################################################################

clear all
close all

disp('==============================================================');
disp('input signal is stored as Q31 format');
disp('==============================================================');
disp('this is Matlab version of C28x Fixed Point RFFT code');
disp('The result is stored in array X');
disp('The signal is stored in array x_raw_sig');
disp('==============================================================');

RadStep = 0.1963495408494;

stages=input('Please enter stages (>=3) =');
N=2^stages;
halfSize=N-1;

Rad=[0:RadStep:(halfSize)*RadStep];

even_idx=0:halfSize;
odd_idx=even_idx+1;

CFFTinBuf1=zeros(1,N);

Rx=sin(Rad)+cos(Rad*2.3567);
Ix=0*(cos(Rad*8.345) + sin(Rad*5.789));

x=Rx+j*Ix;
x_raw_sig=x/2;

x_win=Rx.*hamming(N)';

fft_float=2^31*fft(x/2)/N;

%bit reverse algorithm
for i=1:N
    dr(i) = bin2dec(fliplr(dec2bin(i-1,stages)))+1;
end

dr_1=dr-1;
Rx=2^31*x(dr)/2;
Ix=2^31*Ix(dr)/2;




















