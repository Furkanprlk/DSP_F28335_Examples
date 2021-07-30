//###########################################################################
// Description:
//
// Declare shared variables
//
//###########################################################################
// $TI Release: CLA Math Library for CLA C Compiler V4.00 $
// $Release Date: December 10, 2011 $
//###########################################################################

#ifndef _CLASHARED_H_
#define _CLASHARED_H_

#ifdef __cplusplus
extern "C" {
#endif

//Task 1 (C) Variables
#define BUFFER_SIZE 	        128
#define PI						3.14159
#define TWO_PI					2.0*PI
#define	FREQ_S					100000.0
#define FREQ_1					1000.0
#define	K1						FREQ_1/FREQ_S
extern float y[];
extern float fAngle;
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
interrupt void Cla1Task1();
interrupt void Cla1Task2();
interrupt void Cla1Task3();
interrupt void Cla1Task4();
interrupt void Cla1Task5();
interrupt void Cla1Task6();
interrupt void Cla1Task7();
interrupt void Cla1Task8();

//C28 C Tasks
void test_report(void);
void test_run(void);
void test_error(void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif /*_CLASHARED_H_*/
