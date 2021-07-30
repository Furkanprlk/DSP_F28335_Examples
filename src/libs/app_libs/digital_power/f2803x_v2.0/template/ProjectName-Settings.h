//----------------------------------------------------------------------------------
//	FILE:			{ProjectName}-Settings.h
//
//	Description:    This file contains the definitions for this project, and is 
//					linked to both {ProjectName}-Main.c and {ProjectName}-DPL-ISR.asm 
//					(where X is the project name).  
//
//	Type: 			Device Independent
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2010
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description / Status
//----------------------------------------------------------------------------------
// 9 April 2010 - MB
//----------------------------------------------------------------------------------

#ifndef _PROJSETTINGS_H
#define _PROJSETTINGS_H

//**********************************************************************************
//  NOTE: WHEN CHANGING THIS FILE PLEASE REBUILD ALL
//**********************************************************************************

//==================================================================================
// Incremental Build options for System check-out
//==================================================================================
// BUILD 1 	Open Loop PWMDRV_1ch using PWM 1 on CLA, PWMDRV_CLA_1ch using PWM2 on C28x

#define INCR_BUILD 1
		
//==================================================================================
// System Settings
//----------------------------------------------------------------------------------
//Add any system specific setting below
//#define HistorySize 8
//#define DLOG_SIZE   200

//==================================================================================
// Interrupt Framework options
//==================================================================================

#define EPWMn_DPL_ISR	1	// for EPWM triggered ISR set as 1
#define ADC_DPL_ISR	    0	// for ADC triggered ISR set as 1 
#define CLAn_DPL_ISR	0	// for CLA Task n Triggered ISR set as 1

//----------------------------------------------------------------------------------
// If EPWMn_DPL_ISR = 1, then choose which module
//----------------------------------------------------------------------------------
#define EPWM1			0	// EPWM1 provides ISR trigger
#define EPWM2			1 	// EPWM2 provides ISR trigger
#define EPWM3			0	// EPWM3 provides ISR trigger
#define EPWM4			0	// EPWM4 provides ISR trigger
#define EPWM5			0	// EPWM5 provides ISR trigger
#define EPWM6			0	// EPWM6 provides ISR trigger

//----------------------------------------------------------------------------------
// If EPWM is triggering the CLAn_DPL__ISR = 1, then choose which Task is being triggered
// note the following code would clear the PWM interrupt,
// if an ADC interrupt is used to trigger the CLA leave the following all zeros
//----------------------------------------------------------------------------------
#define CLATASK1_EPWM1		1	// EPWM1 Interrupt provides CLA Task 1 trigger
#define CLATASK2_EPWM2		0	// EPWM2 Interrupt provides CLA Task 1 trigger
#define CLATASK3_EPWM3		0	// EPWM3 Interrupt provides CLA Task 1 trigger
#define CLATASK4_EPWM4		0	// EPWM4 Interrupt provides CLA Task 1 trigger
#define CLATASK5_EPWM5		0	// EPWM5 Interrupt provides CLA Task 1 trigger
#define CLATASK6_EPWM6		0	// EPWM6 Interrupt provides CLA Task 1 trigger
#define CLATASK7_EPWM7		0	// EPWM7 Interrupt provides CLA Task 1 trigger
// Task 8 is reserved for software based initialization when using DPlib

#endif //_PROJSETTINGS_H

