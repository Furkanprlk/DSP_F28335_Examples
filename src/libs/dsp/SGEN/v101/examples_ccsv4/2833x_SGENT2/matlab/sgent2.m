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
% File Name:      SGENT2.m
% 
% Description:    Primary System file for demonstrating the Signal Generator module
% 
% Originator:     Digital control systems Group - Texas Instruments
% 
% Target dependency:  C28x
% 
% Description:
% ============
% 
%    The "C" frame work, for demonstrating the signal generator module is given below
%                              ___________________                _____________
%                             |                   |     x1=out1  |             |
%          gain   o---------->|                   |------o------>|  EVMDAC     |
%          offset o---------->|       SGENT_2     |     x2=out2  |  PWMDAC     |
%         freq    o---------->|                   |------o------>|  DLOG_4CH   |
%                             |___________________|              |_____________|
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
phase_norm=8192;        %normalized phase offset phase_norm=(pi/4/(2*pi))*2^16=8192
                        %here phase offset=pi/4
                        
phase=16384/2^15;
                        
output=gain*sin(2*pi*(f_norm*t/2^16+phase_norm/2^16)+phase*pi);

output0=gain*sin(2*pi*(f_norm*t/2^16+phase_norm/2^16));

output=output*2^15;     %Q15 format

output0=output0*2^15;     %Q15 format

plot(output)
hold on
plot(output0,'r')