clc;
clear all;
close all;

%Read the FRA Plant data from the excel sheet%
Freq=xlsread('FRAData','Sheet1','A2:A102');
Phase_H=xlsread('FRAData','Sheet1','E2:E102');
Mag_H=xlsread('FRAData','Sheet1','D2:D102');

%Convert the FRA data to a bode object in MATLAB%
Mag_H=(10.^(Mag_H./20));
Phase_H=pi.*Phase_H./180;
Plant_Bode_Obj=frd(Mag_H.*exp(i*(Phase_H)),Freq,'FrequencyUnit','Hz');

%Curve fit the data to get a transfer function%
% user may choose to fit 3p3z or any other depending on what works best%
[Hn,Hd] = invfreqs(Mag_H.*exp(i*(Phase_H)),(2*pi).*Freq,2,3);
H = tf(Hn,Hd);
 
% plot both the measured and curve fitted TF to compare accuracy
figure(1);bode(H,Plant_Bode_Obj);title('Control-to-Output Measured Vs Curve Fitted');
legend('Curve Fitted','Measured')

%call sisotool to design the compensation with the transfer function%
sisotool(H)
