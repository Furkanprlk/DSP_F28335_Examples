//#############################################################################
// Description:
//
// Declare shared variables
//
// Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
// ALL RIGHTS RESERVED
//#############################################################################
//$TI Release: CLA Math Library V4.02.00.00 $
//$Release Date: Oct 3, 2016 $
//#############################################################################

#ifndef _CLASHARED_H_
#define _CLASHARED_H_

#ifdef __cplusplus
extern "C" {
#endif

//Task 1 (C) Variables
#define BUFFER_SIZE     128
extern float y[];
extern float fVal;
extern float fResult;

//Task 2 (C) Variables

//Task 3 (C) Variables

//Task 4 (C) Variables

//Task 5 (C) Variables

//Task 6 (C) Variables

//Task 7 (C) Variables

//Task 8 (C) Variables

//Common (C) Variables

//CLA C Tasks
__attribute__((interrupt)) void Cla1Task1();
__attribute__((interrupt)) void Cla1Task2();
__attribute__((interrupt)) void Cla1Task3();
__attribute__((interrupt)) void Cla1Task4();
__attribute__((interrupt)) void Cla1Task5();
__attribute__((interrupt)) void Cla1Task6();
__attribute__((interrupt)) void Cla1Task7();
__attribute__((interrupt)) void Cla1Task8();

//C28 C Tasks
void test_report(void);
void test_run(void);
void test_error(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /*_CLASHARED_H_*/
