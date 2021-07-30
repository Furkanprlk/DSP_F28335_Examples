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
% File Name:      PROFILE.m
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
%                  ___________           _____________
%                 |           |         |             |
%                 |           | X1=OUT  |   EVMDAC    |
%                 | PROFILE   |-------->|   DLOG_4CH  |
%                 |           |         |   PWMDAC    |
%                 |___________|         |_____________|
% 
% */
% //######################################################################################
% // $TI Release: C28x SGEN Library v1.00 $
% // $Release Date: November 09, 2011 $
% //######################################################################################

close all
clear all


T=400;

signal=zeros(1,T);

startPhase=20;

signal(1:40-startPhase)=-32767*ones(1,40-startPhase);         %0.1*T=40
signal((41:120)-startPhase)=-32767+(1:80)*65536/80;  %0.1*T+0.2*T=120
signal((121:240)-startPhase)=32767*ones(1,120);      %0.1*T+0.2*T+0.3*T=240
signal((241:400)-startPhase)=32767-(1:160)*65536/160;
signal((400-startPhase+1):400)=-32767*ones(1,40-startPhase);

figure(2)
plot(signal)