% // TI File $Revision: /main/3 $
% // Checkin $Date: November 09, 2010   13:05:07 $
% // =====================================================================================
% //  This software is licensed for use with Texas Instruments C28x
% //  family DSCs.  This license was provided to you prior to installing
% //  the software.  You may review this license by consulting a copy of
% //  the agreement in the doc directory of this library.
% // -------------------------------------------------------------------------------------
% //          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
% //                          All Rights Reserved.
% //======================================================================================
% /* ==============================================================================
% 
% System Name:    Signal Generator Module demo 
% 
% File Name:      SGENTI3.m
% 
% Description:    Primary System file for demonstrating the Signal Generator module
% 
% Originator:     Digital control systems Group - Texas Instruments
% 
% Target dependency:  x2407/x241/2/3
% 
% Description:
% ============
% 
%    The "C" frame work, for demonstrating the signal generator module is given below
%                              ___________________                   ______________
%                             |                   |     x1=out1     |              |
%                             |                   |------o--------->|  EVMDAC      |
%          gain   o---------->|                   |     x2=out2     |  PWMDAC      |
%          offset o---------->|     SGENTI_3      |------o--------->|              |
%          freq   o---------->|                   |     x3=out3     |  DLOG_4CH    |
%                             |                   |------o--------->|              | 
%                             |___________________|                 |______________|
% 
% */
% //######################################################################################
% // $TI Release: C28x SGEN Library v1.00 $
% // $Release Date: November 09, 2011 $
% //######################################################################################

close all
clear all

N=input('Please enter signal length N =');

t=1:N;

step_max=1000;

gain=1;
f=50;
fs=20000;

fmax=step_max*fs/65536
freq=2^15*f/fmax

f_norm=163.84;             %f_norm is normalized frequency in Q16 format, f/fs*2^16
phase_norm=0;        %normalized phase offset phase_norm=(pi/4/(2*pi))*2^16=8192
                        %here phase offset=pi/4
                        
phase=0;

output2=gain*sin(2*pi*(f_norm*t/2^16+phase_norm/2^16)+4*pi/3);
                        
output1=gain*sin(2*pi*(f_norm*t/2^16+phase_norm/2^16)+2*pi/3);

output0=gain*sin(2*pi*(f_norm*t/2^16+phase_norm/2^16));

output2=output2*2^15;     %Q15 format

output1=output1*2^15;     %Q15 format

output0=output0*2^15;     %Q15 format

plot(output2)
hold on
plot(output0,'r')
plot(output1,'g')