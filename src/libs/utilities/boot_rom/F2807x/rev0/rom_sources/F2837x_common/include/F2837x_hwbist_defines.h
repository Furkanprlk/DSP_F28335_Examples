//###########################################################################
// FILE:   F2837x_Hwbist_defines.h
// TITLE:  Defines/Prototypes for the HWBIST driver.
//###########################################################################
// $TI Release: F2837x Support Library v110 $
// $Release Date: Tue Nov  6 08:49:15 CST 2012 $
//###########################################################################

#ifndef F2837x_HWBISTFUNCS_H
#define F2837x_HWBISTFUNCS_H

//*****************************************************************************
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
// Coverage configuration options for HWBISTSelfTestInit(...)
//*****************************************************************************
#define HWBIST_CONFIG_COV_99PERCENT   0x00000000
#define HWBIST_CONFIG_COV_95PERCENT   0x00000001

//*****************************************************************************
// CPU configuration options for Semaphore Access
//*****************************************************************************
#define HWBIST_CPU1   0x00000002
#define HWBIST_CPU2   0x00000001
#define HWBIST_CPU3   0x00000003

//*****************************************************************************
// Memory addresses for the 95% coverage MISR
//*****************************************************************************
#define HWBIST_95PERCENT_MISR   0x003FFF6A
#define HWBIST_95PERCENT_MISR0  (HWBIST_95PERCENT_MISR + 0x1E)
#define HWBIST_95PERCENT_MISR1  (HWBIST_95PERCENT_MISR + 0x1C)
#define HWBIST_95PERCENT_MISR2  (HWBIST_95PERCENT_MISR + 0x1A)
#define HWBIST_95PERCENT_MISR3  (HWBIST_95PERCENT_MISR + 0x18)
#define HWBIST_95PERCENT_MISR4  (HWBIST_95PERCENT_MISR + 0x16)
#define HWBIST_95PERCENT_MISR5  (HWBIST_95PERCENT_MISR + 0x14)
#define HWBIST_95PERCENT_MISR6  (HWBIST_95PERCENT_MISR + 0x12)
#define HWBIST_95PERCENT_MISR7  (HWBIST_95PERCENT_MISR + 0x10)
#define HWBIST_95PERCENT_MISR8  (HWBIST_95PERCENT_MISR + 0xE)
#define HWBIST_95PERCENT_MISR9  (HWBIST_95PERCENT_MISR + 0xC)
#define HWBIST_95PERCENT_MISR10  (HWBIST_95PERCENT_MISR + 0xA)
#define HWBIST_95PERCENT_MISR11  (HWBIST_95PERCENT_MISR + 0x8)
#define HWBIST_95PERCENT_MISR12  (HWBIST_95PERCENT_MISR + 0x6)
#define HWBIST_95PERCENT_MISR13  (HWBIST_95PERCENT_MISR + 0x4)
#define HWBIST_95PERCENT_MISR14  (HWBIST_95PERCENT_MISR + 0x2)
#define HWBIST_95PERCENT_MISR15  (HWBIST_95PERCENT_MISR)

//*****************************************************************************
// Memory addresses for the 99% coverage MISR
//*****************************************************************************
#define HWBIST_99PERCENT_MISR   0x003FFF72
#define HWBIST_99PERCENT_MISR0  (HWBIST_99PERCENT_MISR + 0x1E)
#define HWBIST_99PERCENT_MISR1  (HWBIST_99PERCENT_MISR + 0x1C)
#define HWBIST_99PERCENT_MISR2  (HWBIST_99PERCENT_MISR + 0x1A)
#define HWBIST_99PERCENT_MISR3  (HWBIST_99PERCENT_MISR + 0x18)
#define HWBIST_99PERCENT_MISR4  (HWBIST_99PERCENT_MISR + 0x16)
#define HWBIST_99PERCENT_MISR5  (HWBIST_99PERCENT_MISR + 0x14)
#define HWBIST_99PERCENT_MISR6  (HWBIST_99PERCENT_MISR + 0x12)
#define HWBIST_99PERCENT_MISR7  (HWBIST_99PERCENT_MISR + 0x10)
#define HWBIST_99PERCENT_MISR8  (HWBIST_99PERCENT_MISR + 0xE)
#define HWBIST_99PERCENT_MISR9  (HWBIST_99PERCENT_MISR + 0xC)
#define HWBIST_99PERCENT_MISR10  (HWBIST_99PERCENT_MISR + 0xA)
#define HWBIST_99PERCENT_MISR11  (HWBIST_99PERCENT_MISR + 0x8)
#define HWBIST_99PERCENT_MISR12  (HWBIST_99PERCENT_MISR + 0x6)
#define HWBIST_99PERCENT_MISR13  (HWBIST_99PERCENT_MISR + 0x4)
#define HWBIST_99PERCENT_MISR14  (HWBIST_99PERCENT_MISR + 0x2)
#define HWBIST_99PERCENT_MISR15  (HWBIST_99PERCENT_MISR)

//*****************************************************************************
// Shift clock divider configuration options for HWBISTShiftClockSet(...)
//*****************************************************************************
#define HWBIST_CONFIG_SHIFTCLOCKDIV_1    0x00000000
#define HWBIST_CONFIG_SHIFTCLOCKDIV_2    0x00000001
#define HWBIST_CONFIG_SHIFTCLOCKDIV_4    0x00000002

//*****************************************************************************
// Return bit masks for HWBISTResultGet()
//*****************************************************************************
#define HWBIST_RESULT_BISTDONE   0x1     // HWBIST Test Complete
#define HWBIST_RESULT_NMI        0x4     // Early exit due to NMI
#define HWBIST_RESULT_BISTFAIL   0x8     // HWBIST Failure
#define HWBIST_RESULT_INTCMPF    0x10    // Intermediate Comparison Failure
#define HWBIST_RESULT_TOFAIL     0x20    // Time Out Failure

//*****************************************************************************
// Multiple Input Signature Register 128-bit Type
// Use this struct to pass MISR signatures between functions and the app
//*****************************************************************************
typedef struct
{
    unsigned long Misr0;
    unsigned long Misr1;
    unsigned long Misr2;
    unsigned long Misr3;
    unsigned long Misr4;
    unsigned long Misr5;
    unsigned long Misr6;
    unsigned long Misr7;
    unsigned long Misr8;
    unsigned long Misr9;
    unsigned long Misr10;
    unsigned long Misr11;
    unsigned long Misr12;
    unsigned long Misr13;
    unsigned long Misr14;
    unsigned long Misr15;
}
tMisr;

void HWBISTSelfTestInit(unsigned long ulMicroInterval,
                       unsigned long ulCoverage,
                       unsigned long ucShiftClock);
void HWBISTSemEn(unsigned long ulCoreEn);
int HWBISTSelfTestMicroRun(void);
int HWBISTSelfTestFullRun(void);
void HWBISTSelfTestRestart(void);
void HWBISTTestLogicSet(unsigned long ulLogicError);
void HWBISTTestNmiSet(int bEnable);
void HWBISTTestTimeoutSet(int bEnable);
void HWBISTShiftClockSet(unsigned long ucShiftClock);
unsigned long HWBISTResultGet(void);
int HWBISTResultBasicGet(void);
tMisr HWBISTMisrGet(void);
tMisr HWBISTMisrGoldenGet(void);
int HWBISTCompareMisr(tMisr m1, tMisr m2);


//*****************************************************************************
// Mark the end of the C bindings section for C++ compilers.
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif // F2837x_HWBISTFUNCS_H
