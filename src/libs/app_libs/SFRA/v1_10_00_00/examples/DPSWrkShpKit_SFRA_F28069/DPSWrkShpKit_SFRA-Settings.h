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

#define INCR_BUILD 2

#define BUCK_PWM_PERIOD 400
#define VOUT_MAX 9.76
#define Inv_VOUT_MAX (1.0/9.76)
#define ADC_PU_SCALING	(1.0/4096.0)
		
//==================================================================================
// System Settings
//----------------------------------------------------------------------------------
//Add any system specific setting below
#define HistorySize 	8	// Number of samples averaged for use in GUI
#define DLOG_SIZE   	400

//==================================================================================
// Interrupt Framework options
//==================================================================================

#define EPWMn_DPL_ISR	1	// for EPWM triggered ISR set as 1
#define ADC_DPL_ISR	    0	// for ADC INT 1 triggered ISR set as 1 
#define CLAn_DPL_ISR	0	// for CLA Task n Triggered ISR set as 1

//----------------------------------------------------------------------------------
// If EPWMn_DPL_ISR = 1, then choose which module
//----------------------------------------------------------------------------------
#define EPWM1			1	// EPWM1 provides ISR trigger
#define EPWM2			1 	// EPWM2 provides ISR trigger
#define EPWM3			0	// EPWM3 provides ISR trigger
#define EPWM4			0	// EPWM4 provides ISR trigger
#define EPWM5			0	// EPWM5 provides ISR trigger
#define EPWM6			0	// EPWM6 provides ISR trigger

// Following #defines are used for configuring the ADC
#define ADCTRIG_SOFT		0
#define ADCTRIG_CPU_TINT0	1
#define ADCTRIG_CPU_TINT1	2
#define ADCTRIG_CPU_TINT2	3
#define ADCTRIG_XINT2		4
#define ADCTRIG_EPWM1_SOCA	5
#define ADCTRIG_EPWM1_SOCB	6
#define ADCTRIG_EPWM2_SOCA	7
#define ADCTRIG_EPWM2_SOCB	8
#define ADCTRIG_EPWM3_SOCA	9
#define ADCTRIG_EPWM3_SOCB	10
#define ADCTRIG_EPWM4_SOCA	11
#define ADCTRIG_EPWM4_SOCB	12
#define ADCTRIG_EPWM5_SOCA	13
#define ADCTRIG_EPWM5_SOCB	14
#define ADCTRIG_EPWM6_SOCA	15
#define ADCTRIG_EPWM6_SOCB	16
#define ADCTRIG_EPWM7_SOCA	17
#define ADCTRIG_EPWM7_SOCB	18

#endif //_PROJSETTINGS_H

