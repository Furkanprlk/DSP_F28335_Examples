//###########################################################################
//
// FILE:   F2837x_Xbar.h
//
// TITLE:  F2837x Device Xbar Register Definitions.
//
//###########################################################################
// $TI Release:   $
// $Release Date:   $
//###########################################################################

#ifndef F2837x_Xbar_H
#define F2837x_Xbar_H
#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// Xbar Individual Register Bit Definitions:

struct GPTRIPLOCK_BITS {                                           // bit descriptions
    Uint16  GPTRIP1SEL:1;                                          // 0 Lock bit for GPTRIP1SEL Register 
    Uint16  GPTRIP2SEL:1;                                          // 1 Lock bit for GPTRIP2SEL Register 
    Uint16  GPTRIP3SEL:1;                                          // 2 Lock bit for GPTRIP3SEL Register 
    Uint16  GPTRIP4SEL:1;                                          // 3 Lock bit for GPTRIP4SEL Register 
    Uint16  GPTRIP5SEL:1;                                          // 4 Lock bit for GPTRIP5SEL Register 
    Uint16  GPTRIP6SEL:1;                                          // 5 Lock bit for GPTRIP7SEL Register 
    Uint16  GPTRIP7SEL:1;                                          // 6 Lock bit for GPTRIP8SEL Register 
    Uint16  GPTRIP8SEL:1;                                          // 7 Lock bit for GPTRIP9SEL Register 
    Uint16  GPTRIP9SEL:1;                                          // 8 Lock bit for GPTRIP10SEL Register 
    Uint16  GPTRIP10SEL:1;                                         // 9 Lock bit for GPTRIP11SEL Register 
    Uint16  GPTRIP11SEL:1;                                         // 10 Lock bit for GPTRIP11SEL Register 
    Uint16  GPTRIP12SEL:1;                                         // 11 Lock bit for GPTRIP12SEL Register 
    Uint16  GPTRIP13SEL:1;                                         // 12 Lock bit for GPTRIP13SEL Register 
    Uint16  GPTRIP14SEL:1;                                         // 13 Lock bit for GPTRIP14SEL Register 
    Uint16  GPTRIP15SEL:1;                                         // 14 Lock bit for GPTRIP15SEL Register 
    Uint16  GPTRIP16SEL:1;                                         // 15 Lock bit for GPTRIP16SEL Register 
    Uint16  rsvd1:16;                                              // 31:16 Reserved 
};

union GPTRIPLOCK_REG {
    Uint32  all;  
    struct  GPTRIPLOCK_BITS  bit;  
};

struct XBARILAT1_BITS {                                            // bit descriptions
    Uint16  CMPSS0_CTRIPL:1;                                       // 0 Input Latch for CMPSS0.CTRIPL Signal 
    Uint16  CMPSS0_CTRIPH:1;                                       // 1 Input Latch for CMPSS0.CTRIPH Signal 
    Uint16  CMPSS1_CTRIPL:1;                                       // 2 Input Latch for CMPSS1.CTRIPL Signal 
    Uint16  CMPSS1_CTRIPH:1;                                       // 3 Input Latch for CMPSS1.CTRIPH Signal 
    Uint16  CMPSS2_CTRIPL:1;                                       // 4 Input Latch for CMPSS2.CTRIPL Signal 
    Uint16  CMPSS2_CTRIPH:1;                                       // 5 Input Latch for CMPSS2.CTRIPH Signal 
    Uint16  CMPSS3_CTRIPL:1;                                       // 6 Input Latch for CMPSS3.CTRIPL Signal 
    Uint16  CMPSS3_CTRIPH:1;                                       // 7 Input Latch for CMPSS3.CTRIPH Signal 
    Uint16  CMPSS4_CTRIPL:1;                                       // 8 Input Latch for CMPSS4.CTRIPL Signal 
    Uint16  CMPSS4_CTRIPH:1;                                       // 9 Input Latch for CMPSS4.CTRIPH Signal 
    Uint16  CMPSS5_CTRIPL:1;                                       // 10 Input Latch for CMPSS5.CTRIPL Signal 
    Uint16  CMPSS5_CTRIPH:1;                                       // 11 Input Latch for CMPSS5.CTRIPH Signal 
    Uint16  CMPSS6_CTRIPL:1;                                       // 12 Input Latch for CMPSS6.CTRIPL Signal 
    Uint16  CMPSS6_CTRIPH:1;                                       // 13 Input Latch for CMPSS6.CTRIPH Signal 
    Uint16  CMPSS7_CTRIPL:1;                                       // 14 Input Latch for CMPSS7.CTRIPL Signal 
    Uint16  CMPSS7_CTRIPH:1;                                       // 15 Input Latch for CMPSS7.CTRIPH Signal 
    Uint16  CMPSS0_CTRIPOUTL:1;                                    // 16 Input Latch for CMPSS0.CTRIPOUTL Signal 
    Uint16  CMPSS0_CTRIPOUTH:1;                                    // 17 Input Latch for CMPSS0.CTRIPOUTH Signal 
    Uint16  CMPSS1_CTRIPOUTL:1;                                    // 18 Input Latch for CMPSS1.CTRIPOUTL Signal 
    Uint16  CMPSS1_CTRIPOUTH:1;                                    // 19 Input Latch for CMPSS1.CTRIPOUTH Signal 
    Uint16  CMPSS2_CTRIPOUTL:1;                                    // 20 Input Latch for CMPSS2.CTRIPOUTL Signal 
    Uint16  CMPSS2_CTRIPOUTH:1;                                    // 21 Input Latch for CMPSS2.CTRIPOUTH Signal 
    Uint16  CMPSS3_CTRIPOUTL:1;                                    // 22 Input Latch for CMPSS3.CTRIPOUTL Signal 
    Uint16  CMPSS3_CTRIPOUTH:1;                                    // 23 Input Latch for CMPSS3.CTRIPOUTH Signal 
    Uint16  CMPSS4_CTRIPOUTL:1;                                    // 24 Input Latch for CMPSS4.CTRIPOUTL Signal 
    Uint16  CMPSS4_CTRIPOUTH:1;                                    // 25 Input Latch for CMPSS4.CTRIPOUTH Signal 
    Uint16  CMPSS5_CTRIPOUTL:1;                                    // 26 Input Latch for CMPSS5.CTRIPOUTL Signal 
    Uint16  CMPSS5_CTRIPOUTH:1;                                    // 27 Input Latch for CMPSS5.CTRIPOUTH Signal 
    Uint16  CMPSS6_CTRIPOUTL:1;                                    // 28 Input Latch for CMPSS6.CTRIPOUTL Signal 
    Uint16  CMPSS6_CTRIPOUTH:1;                                    // 29 Input Latch for CMPSS6.CTRIPOUTH Signal 
    Uint16  CMPSS7_CTRIPOUTL:1;                                    // 30 Input Latch for CMPSS7.CTRIPOUTL Signal 
    Uint16  CMPSS7_CTRIPOUTH:1;                                    // 31 Input Latch for CMPSS7.CTRIPOUTH Signal 
};

union XBARILAT1_REG {
    Uint32  all;  
    struct  XBARILAT1_BITS  bit;  
};

struct XBARILAT2_BITS {                                            // bit descriptions
    Uint16  GPTRIP1:1;                                             // 0 Input Latch for GPTRIP1 Signal 
    Uint16  GPTRIP2:1;                                             // 1 Input Latch for GPTRIP2 Signal 
    Uint16  GPTRIP3:1;                                             // 2 Input Latch for GPTRIP3 Signal 
    Uint16  GPTRIP4:1;                                             // 3 Input Latch for GPTRIP4 Signal 
    Uint16  GPTRIP5:1;                                             // 4 Input Latch for GPTRIP5 Signal 
    Uint16  GPTRIP7:1;                                             // 5 Input Latch for GPTRIP7 Signal 
    Uint16  ADCSOCA:1;                                             // 6 Input Latch for ADCSOCA Signal 
    Uint16  ADCSOCB:1;                                             // 7 Input Latch for ADCSOCB Signal 
    Uint16  CLB1_4_1:1;                                            // 8 Input Latch for CLB1_4.1 Signal 
    Uint16  CLB1_5_1:1;                                            // 9 Input Latch for CLB1_5.1 Signal 
    Uint16  CLB2_4_1:1;                                            // 10 Input Latch for CLB2_4.1 Signal 
    Uint16  CLB2_5_1:1;                                            // 11 Input Latch for CLB2_5.1 Signal 
    Uint16  CLB3_4_1:1;                                            // 12 Input Latch for CLB3_4.1 Signal 
    Uint16  CLB3_5_1:1;                                            // 13 Input Latch for CLB3_5.1 Signal 
    Uint16  CLB4_4_1:1;                                            // 14 Input Latch for CLB4_4.1 Signal 
    Uint16  CLB4_5_1:1;                                            // 15 Input Latch for CLB4_5.1 Signal 
    Uint16  ECAP1_OUT:1;                                           // 16 Input Latch for ECAP1.OUT Signal 
    Uint16  ECAP2_OUT:1;                                           // 17 Input Latch for ECAP2.OUT Signal 
    Uint16  ECAP3_OUT:1;                                           // 18 Input Latch for ECAP3.OUT Signal 
    Uint16  ECAP4_OUT:1;                                           // 19 Input Latch for ECAP4.OUT Signal 
    Uint16  ECAP5_OUT:1;                                           // 20 Input Latch for ECAP5.OUT Signal 
    Uint16  ECAP6_OUT:1;                                           // 21 Input Latch for ECAP6.OUT Signal 
    Uint16  EXTSYNCOUT:1;                                          // 22 Input Latch for EXTSYNCOUT Signal 
    Uint16  ADCAEVT1:1;                                            // 23 Input Latch for ADCAEVT1 Signal 
    Uint16  ADCAEVT2:1;                                            // 24 Input Latch for ADCAEVT2 Signal 
    Uint16  ADCAEVT3:1;                                            // 25 Input Latch for ADCAEVT3 Signal 
    Uint16  ADCAEVT4:1;                                            // 26 Input Latch for ADCAEVT4 Signal 
    Uint16  ADCBEVT1:1;                                            // 27 Input Latch for ADCBEVT1 Signal 
    Uint16  ADCBEVT2:1;                                            // 28 Input Latch for ADCBEVT2 Signal 
    Uint16  ADCBEVT3:1;                                            // 29 Input Latch for ADCBEVT3 Signal 
    Uint16  ADCBEVT4:1;                                            // 30 Input Latch for ADCBEVT4 Signal 
    Uint16  ADCCEVT1:1;                                            // 31 Input Latch for ADCCEVT1 Signal 
};

union XBARILAT2_REG {
    Uint32  all;  
    struct  XBARILAT2_BITS  bit;  
};

struct XBARILAT3_BITS {                                            // bit descriptions
    Uint16  ADCCEVT2:1;                                            // 0 Input Latch for ADCCEVT2 Signal 
    Uint16  ADCCEVT3:1;                                            // 1 Input Latch for ADCCEVT3 Signal 
    Uint16  ADCCEVT4:1;                                            // 2 Input Latch for ADCCEVT4 Signal 
    Uint16  ADCDEVT1:1;                                            // 3 Input Latch for ADCDEVT1 Signal 
    Uint16  ADCDEVT2:1;                                            // 4 Input Latch for ADCDEVT2 Signal 
    Uint16  ADCDEVT3:1;                                            // 5 Input Latch for ADCDEVT3 Signal 
    Uint16  ADCDEVT4:1;                                            // 6 Input Latch for ADCDEVT4 Signal 
    Uint16  SD1FLT1_COMPL:1;                                       // 7 Input Latch for SD1FLT1.COMPL Signal 
    Uint16  SD1FLT1_COMPH:1;                                       // 8 Input Latch for SD1FLT1.COMPH Signal 
    Uint16  SD1FLT2_COMPL:1;                                       // 9 Input Latch for SD1FLT2.COMPL Signal 
    Uint16  SD1FLT2_COMPH:1;                                       // 10 Input Latch for SD1FLT2.COMPH Signal 
    Uint16  SD1FLT3_COMPL:1;                                       // 11 Input Latch for SD1FLT3.COMPL Signal 
    Uint16  SD1FLT3_COMPH:1;                                       // 12 Input Latch for SD1FLT3.COMPH Signal 
    Uint16  SD1FLT4_COMPL:1;                                       // 13 Input Latch for SD1FLT4.COMPL Signal 
    Uint16  SD1FLT4_COMPH:1;                                       // 14 Input Latch for SD1FLT4.COMPH Signal 
    Uint16  SD2FLT1_COMPL:1;                                       // 15 Input Latch for SD2FLT1.COMPL Signal 
    Uint16  SD2FLT1_COMPH:1;                                       // 16 Input Latch for SD2FLT1.COMPH Signal 
    Uint16  SD2FLT2_COMPL:1;                                       // 17 Input Latch for SD2FLT2.COMPL Signal 
    Uint16  SD2FLT2_COMPH:1;                                       // 18 Input Latch for SD2FLT2.COMPH Signal 
    Uint16  SD2FLT3_COMPL:1;                                       // 19 Input Latch for SD2FLT3.COMPL Signal 
    Uint16  SD2FLT3_COMPH:1;                                       // 20 Input Latch for SD2FLT3.COMPH Signal 
    Uint16  SD2FLT4_COMPL:1;                                       // 21 Input Latch for SD2FLT4.COMPL Signal 
    Uint16  SD2FLT4_COMPH:1;                                       // 22 Input Latch for SD2FLT4.COMPH Signal 
    Uint16  rsvd1:9;                                               // 31:23 Reserved 
};

union XBARILAT3_REG {
    Uint32  all;  
    struct  XBARILAT3_BITS  bit;  
};

struct XBARILATCLR1_BITS {                                         // bit descriptions
    Uint16  CMPSS0_CTRIPL:1;                                       // 0 Input Latch Clear for CMPSS0.CTRIPL Signal 
    Uint16  CMPSS0_CTRIPH:1;                                       // 1 Input Latch Clear for CMPSS0.CTRIPH Signal 
    Uint16  CMPSS1_CTRIPL:1;                                       // 2 Input Latch Clear for CMPSS1.CTRIPL Signal 
    Uint16  CMPSS1_CTRIPH:1;                                       // 3 Input Latch Clear for CMPSS1.CTRIPH Signal 
    Uint16  CMPSS2_CTRIPL:1;                                       // 4 Input Latch Clear for CMPSS2.CTRIPL Signal 
    Uint16  CMPSS2_CTRIPH:1;                                       // 5 Input Latch Clear for CMPSS2.CTRIPH Signal 
    Uint16  CMPSS3_CTRIPL:1;                                       // 6 Input Latch Clear for CMPSS3.CTRIPL Signal 
    Uint16  CMPSS3_CTRIPH:1;                                       // 7 Input Latch Clear for CMPSS3.CTRIPH Signal 
    Uint16  CMPSS4_CTRIPL:1;                                       // 8 Input Latch Clear for CMPSS4.CTRIPL Signal 
    Uint16  CMPSS4_CTRIPH:1;                                       // 9 Input Latch Clear for CMPSS4.CTRIPH Signal 
    Uint16  CMPSS5_CTRIPL:1;                                       // 10 Input Latch Clear for CMPSS5.CTRIPL Signal 
    Uint16  CMPSS5_CTRIPH:1;                                       // 11 Input Latch Clear for CMPSS5.CTRIPH Signal 
    Uint16  CMPSS6_CTRIPL:1;                                       // 12 Input Latch Clear for CMPSS6.CTRIPL Signal 
    Uint16  CMPSS6_CTRIPH:1;                                       // 13 Input Latch Clear for CMPSS6.CTRIPH Signal 
    Uint16  CMPSS7_CTRIPL:1;                                       // 14 Input Latch Clear for CMPSS7.CTRIPL Signal 
    Uint16  CMPSS7_CTRIPH:1;                                       // 15 Input Latch Clear for CMPSS7.CTRIPH Signal 
    Uint16  CMPSS0_CTRIPOUTL:1;                                    // 16 Input Latch Clear for CMPSS0.CTRIPOUTL Signal 
    Uint16  CMPSS0_CTRIPOUTH:1;                                    // 17 Input Latch Clear for CMPSS0.CTRIPOUTH Signal 
    Uint16  CMPSS1_CTRIPOUTL:1;                                    // 18 Input Latch Clear for CMPSS1.CTRIPOUTL Signal 
    Uint16  CMPSS1_CTRIPOUTH:1;                                    // 19 Input Latch Clear for CMPSS1.CTRIPOUTH Signal 
    Uint16  CMPSS2_CTRIPOUTL:1;                                    // 20 Input Latch Clear for CMPSS2.CTRIPOUTL Signal 
    Uint16  CMPSS2_CTRIPOUTH:1;                                    // 21 Input Latch Clear for CMPSS2.CTRIPOUTH Signal 
    Uint16  CMPSS3_CTRIPOUTL:1;                                    // 22 Input Latch Clear for CMPSS3.CTRIPOUTL Signal 
    Uint16  CMPSS3_CTRIPOUTH:1;                                    // 23 Input Latch Clear for CMPSS3.CTRIPOUTH Signal 
    Uint16  CMPSS4_CTRIPOUTL:1;                                    // 24 Input Latch Clear for CMPSS4.CTRIPOUTL Signal 
    Uint16  CMPSS4_CTRIPOUTH:1;                                    // 25 Input Latch Clear for CMPSS4.CTRIPOUTH Signal 
    Uint16  CMPSS5_CTRIPOUTL:1;                                    // 26 Input Latch Clear for CMPSS5.CTRIPOUTL Signal 
    Uint16  CMPSS5_CTRIPOUTH:1;                                    // 27 Input Latch Clear for CMPSS5.CTRIPOUTH Signal 
    Uint16  CMPSS6_CTRIPOUTL:1;                                    // 28 Input Latch Clear for CMPSS6.CTRIPOUTL Signal 
    Uint16  CMPSS6_CTRIPOUTH:1;                                    // 29 Input Latch Clear for CMPSS6.CTRIPOUTH Signal 
    Uint16  CMPSS7_CTRIPOUTL:1;                                    // 30 Input Latch Clear for CMPSS7.CTRIPOUTL Signal 
    Uint16  CMPSS7_CTRIPOUTH:1;                                    // 31 Input Latch Clear for CMPSS7.CTRIPOUTH Signal 
};

union XBARILATCLR1_REG {
    Uint32  all;  
    struct  XBARILATCLR1_BITS  bit;  
};

struct XBARILATCLR2_BITS {                                         // bit descriptions
    Uint16  GPTRIP1:1;                                             // 0 Input Latch Clear for GPTRIP1 Signal 
    Uint16  GPTRIP2:1;                                             // 1 Input Latch Clear for GPTRIP2 Signal 
    Uint16  GPTRIP3:1;                                             // 2 Input Latch Clear for GPTRIP3 Signal 
    Uint16  GPTRIP4:1;                                             // 3 Input Latch Clear for GPTRIP4 Signal 
    Uint16  GPTRIP5:1;                                             // 4 Input Latch Clear for GPTRIP5 Signal 
    Uint16  GPTRIP7:1;                                             // 5 Input Latch Clear for GPTRIP7 Signal 
    Uint16  ADCSOCA:1;                                             // 6 Input Latch Clear for ADCSOCA Signal 
    Uint16  ADCSOCB:1;                                             // 7 Input Latch Clear for ADCSOCB Signal 
    Uint16  CLB1_4_1:1;                                            // 8 Input Latch Clear for CLB1_4.1 Signal 
    Uint16  CLB1_5_1:1;                                            // 9 Input Latch Clear for CLB1_5.1 Signal 
    Uint16  CLB2_4_1:1;                                            // 10 Input Latch Clear for CLB2_4.1 Signal 
    Uint16  CLB2_5_1:1;                                            // 11 Input Latch Clear for CLB2_5.1 Signal 
    Uint16  CLB3_4_1:1;                                            // 12 Input Latch Clear for CLB3_4.1 Signal 
    Uint16  CLB3_5_1:1;                                            // 13 Input Latch Clear for CLB3_5.1 Signal 
    Uint16  CLB4_4_1:1;                                            // 14 Input Latch Clear for CLB4_4.1 Signal 
    Uint16  CLB4_5_1:1;                                            // 15 Input Latch Clear for CLB4_5.1 Signal 
    Uint16  ECAP1_OUT:1;                                           // 16 Input Latch Clear for ECAP1.OUT Signal 
    Uint16  ECAP2_OUT:1;                                           // 17 Input Latch Clear for ECAP2.OUT Signal 
    Uint16  ECAP3_OUT:1;                                           // 18 Input Latch Clear for ECAP3.OUT Signal 
    Uint16  ECAP4_OUT:1;                                           // 19 Input Latch Clear for ECAP4.OUT Signal 
    Uint16  ECAP5_OUT:1;                                           // 20 Input Latch Clear for ECAP5.OUT Signal 
    Uint16  ECAP6_OUT:1;                                           // 21 Input Latch Clear for ECAP6.OUT Signal 
    Uint16  EXTSYNCOUT:1;                                          // 22 Input Latch Clear for EXTSYNCOUT Signal 
    Uint16  ADCAEVT1:1;                                            // 23 Input Latch Clear for ADCAEVT1 Signal 
    Uint16  ADCAEVT2:1;                                            // 24 Input Latch Clear for ADCAEVT2 Signal 
    Uint16  ADCAEVT3:1;                                            // 25 Input Latch Clear for ADCAEVT3 Signal 
    Uint16  ADCAEVT4:1;                                            // 26 Input Latch Clear for ADCAEVT4 Signal 
    Uint16  ADCBEVT1:1;                                            // 27 Input Latch Clear for ADCBEVT1 Signal 
    Uint16  ADCBEVT2:1;                                            // 28 Input Latch Clear for ADCBEVT2 Signal 
    Uint16  ADCBEVT3:1;                                            // 29 Input Latch Clear for ADCBEVT3 Signal 
    Uint16  ADCBEVT4:1;                                            // 30 Input Latch Clear for ADCBEVT4 Signal 
    Uint16  ADCCEVT1:1;                                            // 31 Input Latch Clear for ADCCEVT1 Signal 
};

union XBARILATCLR2_REG {
    Uint32  all;  
    struct  XBARILATCLR2_BITS  bit;  
};

struct XBARILATCLR3_BITS {                                         // bit descriptions
    Uint16  ADCCEVT2:1;                                            // 0 Input Latch Clear for ADCCEVT2 Signal 
    Uint16  ADCCEVT3:1;                                            // 1 Input Latch Clear for ADCCEVT3 Signal 
    Uint16  ADCCEVT4:1;                                            // 2 Input Latch Clear for ADCCEVT4 Signal 
    Uint16  ADCDEVT1:1;                                            // 3 Input Latch Clear for ADCDEVT1 Signal 
    Uint16  ADCDEVT2:1;                                            // 4 Input Latch Clear for ADCDEVT2 Signal 
    Uint16  ADCDEVT3:1;                                            // 5 Input Latch Clear for ADCDEVT3 Signal 
    Uint16  ADCDEVT4:1;                                            // 6 Input Latch Clear for ADCDEVT4 Signal 
    Uint16  SD1FLT1_COMPL:1;                                       // 7 Input Latch Clear for SD1FLT1.COMPL Signal 
    Uint16  SD1FLT1_COMPH:1;                                       // 8 Input Latch Clear for SD1FLT1.COMPH Signal 
    Uint16  SD1FLT2_COMPL:1;                                       // 9 Input Latch Clear for SD1FLT2.COMPL Signal 
    Uint16  SD1FLT2_COMPH:1;                                       // 10 Input Latch Clear for SD1FLT2.COMPH Signal 
    Uint16  SD1FLT3_COMPL:1;                                       // 11 Input Latch Clear for SD1FLT3.COMPL Signal 
    Uint16  SD1FLT3_COMPH:1;                                       // 12 Input Latch Clear for SD1FLT3.COMPH Signal 
    Uint16  SD1FLT4_COMPL:1;                                       // 13 Input Latch Clear for SD1FLT4.COMPL Signal 
    Uint16  SD1FLT4_COMPH:1;                                       // 14 Input Latch Clear for SD1FLT4.COMPH Signal 
    Uint16  SD2FLT1_COMPL:1;                                       // 15 Input Latch Clear for SD2FLT1.COMPL Signal 
    Uint16  SD2FLT1_COMPH:1;                                       // 16 Input Latch Clear for SD2FLT1.COMPH Signal 
    Uint16  SD2FLT2_COMPL:1;                                       // 17 Input Latch Clear for SD2FLT2.COMPL Signal 
    Uint16  SD2FLT2_COMPH:1;                                       // 18 Input Latch Clear for SD2FLT2.COMPH Signal 
    Uint16  SD2FLT3_COMPL:1;                                       // 19 Input Latch Clear for SD2FLT3.COMPL Signal 
    Uint16  SD2FLT3_COMPH:1;                                       // 20 Input Latch Clear for SD2FLT3.COMPH Signal 
    Uint16  SD2FLT4_COMPL:1;                                       // 21 Input Latch Clear for SD2FLT4.COMPL Signal 
    Uint16  SD2FLT4_COMPH:1;                                       // 22 Input Latch Clear for SD2FLT4.COMPH Signal 
    Uint16  rsvd1:9;                                               // 31:23 Reserved 
};

union XBARILATCLR3_REG {
    Uint32  all;  
    struct  XBARILATCLR3_BITS  bit;  
};

struct SYNCSEL_BITS {                                              // bit descriptions
    Uint16  EPWM4SYNCIN:3;                                         // 2:0 Selects Sync Input Source for EPWM4 
    Uint16  EPWM7SYNCIN:3;                                         // 5:3 Selects Sync Input Source for EPWM7 
    Uint16  EPWM10SYNCIN:3;                                        // 8:6 Selects Sync Input Source for EPWM10 
    Uint16  ECAP1SYNCIN:3;                                         // 11:9 Selects Sync Input Source for ECAP1 
    Uint16  ECAP4SYNCIN:3;                                         // 14:12 Selects Sync Input Source for ECAP4 
    Uint16  rsvd1:1;                                               // 15 Reserved 
    Uint16  rsvd2:11;                                              // 26:16 Reserved 
    Uint16  SYNCOUT:2;                                             // 28:27 Select Syncout Source 
    Uint16  rsvd3:3;                                               // 31:29 Reserved 
};

union SYNCSEL_REG {
    Uint32  all;  
    struct  SYNCSEL_BITS  bit;  
};

struct EXTADCSOCSEL_BITS {                                         // bit descriptions
    Uint16  PWM1SOCAEN:1;                                          // 0 PWM1SOCAEN Enable for ADCSOCAOn 
    Uint16  PWM2SOCAEN:1;                                          // 1 PWM2SOCAEN Enable for ADCSOCAOn 
    Uint16  PWM3SOCAEN:1;                                          // 2 PWM3SOCAEN Enable for ADCSOCAOn 
    Uint16  PWM4SOCAEN:1;                                          // 3 PWM4SOCAEN Enable for ADCSOCAOn 
    Uint16  PWM5SOCAEN:1;                                          // 4 PWM5SOCAEN Enable for ADCSOCAOn 
    Uint16  PWM6SOCAEN:1;                                          // 5 PWM6SOCAEN Enable for ADCSOCAOn 
    Uint16  PWM7SOCAEN:1;                                          // 6 PWM7SOCAEN Enable for ADCSOCAOn 
    Uint16  PWM8SOCAEN:1;                                          // 7 PWM8SOCAEN Enable for ADCSOCAOn 
    Uint16  PWM9SOCAEN:1;                                          // 8 PWM9SOCAEN Enable for ADCSOCAOn 
    Uint16  PWM10SOCAEN:1;                                         // 9 PWM10SOCAEN Enable for ADCSOCAOn 
    Uint16  PWM11SOCAEN:1;                                         // 10 PWM11SOCAEN Enable for ADCSOCAOn 
    Uint16  PWM12SOCAEN:1;                                         // 11 PWM12SOCAEN Enable for ADCSOCAOn 
    Uint16  rsvd1:4;                                               // 15:12 Reserved 
    Uint16  PWM1SOCBEN:1;                                          // 16 PWM1SOCBEN Enable for ADCSOCBOn 
    Uint16  PWM2SOCBEN:1;                                          // 17 PWM2SOCBEN Enable for ADCSOCBOn 
    Uint16  PWM3SOCBEN:1;                                          // 18 PWM3SOCBEN Enable for ADCSOCBOn 
    Uint16  PWM4SOCBEN:1;                                          // 19 PWM4SOCBEN Enable for ADCSOCBOn 
    Uint16  PWM5SOCBEN:1;                                          // 20 PWM5SOCBEN Enable for ADCSOCBOn 
    Uint16  PWM6SOCBEN:1;                                          // 21 PWM6SOCBEN Enable for ADCSOCBOn 
    Uint16  PWM7SOCBEN:1;                                          // 22 PWM7SOCBEN Enable for ADCSOCBOn 
    Uint16  PWM8SOCBEN:1;                                          // 23 PWM8SOCBEN Enable for ADCSOCBOn 
    Uint16  PWM9SOCBEN:1;                                          // 24 PWM9SOCBEN Enable for ADCSOCBOn 
    Uint16  PWM10SOBAEN:1;                                         // 25 PWM10SOBAEN Enable for ADCSOCBOn 
    Uint16  PWM11SOBAEN:1;                                         // 26 PWM11SOBAEN Enable for ADCSOCBOn 
    Uint16  PWM12SOBAEN:1;                                         // 27 PWM12SOBAEN Enable for ADCSOCBOn 
    Uint16  rsvd2:4;                                               // 31:28 Reserved 
};

union EXTADCSOCSEL_REG {
    Uint32  all;  
    struct  EXTADCSOCSEL_BITS  bit;  
};

struct SYNCSOCLOCK_BITS {                                          // bit descriptions
    Uint16  SYNCSEL:1;                                             // 0 SYNCSEL Register Lock bit 
    Uint16  EXTADCSOCSEL:1;                                        // 1 EXTADCSOCSEL Register Lock bit 
    Uint16  rsvd1:14;                                              // 15:2 Reserved 
    Uint16  rsvd2:16;                                              // 31:16 Reserved 
};

union SYNCSOCLOCK_REG {
    Uint32  all;  
    struct  SYNCSOCLOCK_BITS  bit;  
};

struct TRIP4MUX0TO15CFG_BITS {                                     // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for TRIP4 of EPwmXbar 
};

union TRIP4MUX0TO15CFG_REG {
    Uint32  all;  
    struct  TRIP4MUX0TO15CFG_BITS  bit;  
};

struct TRIP5MUX0TO15CFG_BITS {                                     // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for TRIP5 of EPwmXbar 
};

union TRIP5MUX0TO15CFG_REG {
    Uint32  all;  
    struct  TRIP5MUX0TO15CFG_BITS  bit;  
};

struct TRIP7MUX0TO15CFG_BITS {                                     // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for TRIP7 of EPwmXbar 
};

union TRIP7MUX0TO15CFG_REG {
    Uint32  all;  
    struct  TRIP7MUX0TO15CFG_BITS  bit;  
};

struct TRIP8MUX0TO15CFG_BITS {                                     // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for TRIP8 of EPwmXbar 
};

union TRIP8MUX0TO15CFG_REG {
    Uint32  all;  
    struct  TRIP8MUX0TO15CFG_BITS  bit;  
};

struct TRIP9MUX0TO15CFG_BITS {                                     // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for TRIP9 of EPwmXbar 
};

union TRIP9MUX0TO15CFG_REG {
    Uint32  all;  
    struct  TRIP9MUX0TO15CFG_BITS  bit;  
};

struct TRIP10MUX0TO15CFG_BITS {                                    // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for TRIP10 of EPwmXbar 
};

union TRIP10MUX0TO15CFG_REG {
    Uint32  all;  
    struct  TRIP10MUX0TO15CFG_BITS  bit;  
};

struct TRIP11MUX0TO15CFG_BITS {                                    // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for TRIP11 of EPwmXbar 
};

union TRIP11MUX0TO15CFG_REG {
    Uint32  all;  
    struct  TRIP11MUX0TO15CFG_BITS  bit;  
};

struct TRIP12MUX0TO15CFG_BITS {                                    // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for TRIP12 of EPwmXbar 
};

union TRIP12MUX0TO15CFG_REG {
    Uint32  all;  
    struct  TRIP12MUX0TO15CFG_BITS  bit;  
};

struct TRIP4MUXENABLE_BITS {                                       // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive TRIP4 of EPwmXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive TRIP4 of EPwmXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive TRIP4 of EPwmXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive TRIP4 of EPwmXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive TRIP4 of EPwmXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive TRIP4 of EPwmXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive TRIP4 of EPwmXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive TRIP4 of EPwmXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive TRIP4 of EPwmXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive TRIP4 of EPwmXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive TRIP4 of EPwmXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive TRIP4 of EPwmXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive TRIP4 of EPwmXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive TRIP4 of EPwmXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive TRIP4 of EPwmXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive TRIP4 of EPwmXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive TRIP4 of EPwmXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive TRIP4 of EPwmXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive TRIP4 of EPwmXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive TRIP4 of EPwmXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive TRIP4 of EPwmXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive TRIP4 of EPwmXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive TRIP4 of EPwmXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive TRIP4 of EPwmXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive TRIP4 of EPwmXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive TRIP4 of EPwmXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive TRIP4 of EPwmXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive TRIP4 of EPwmXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive TRIP4 of EPwmXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive TRIP4 of EPwmXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive TRIP4 of EPwmXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive TRIP4 of EPwmXbar 
};

union TRIP4MUXENABLE_REG {
    Uint32  all;  
    struct  TRIP4MUXENABLE_BITS  bit;  
};

struct TRIP5MUXENABLE_BITS {                                       // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive TRIP5 of EPwmXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive TRIP5 of EPwmXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive TRIP5 of EPwmXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive TRIP5 of EPwmXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive TRIP5 of EPwmXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive TRIP5 of EPwmXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive TRIP5 of EPwmXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive TRIP5 of EPwmXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive TRIP5 of EPwmXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive TRIP5 of EPwmXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive TRIP5 of EPwmXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive TRIP5 of EPwmXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive TRIP5 of EPwmXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive TRIP5 of EPwmXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive TRIP5 of EPwmXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive TRIP5 of EPwmXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive TRIP5 of EPwmXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive TRIP5 of EPwmXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive TRIP5 of EPwmXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive TRIP5 of EPwmXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive TRIP5 of EPwmXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive TRIP5 of EPwmXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive TRIP5 of EPwmXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive TRIP5 of EPwmXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive TRIP5 of EPwmXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive TRIP5 of EPwmXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive TRIP5 of EPwmXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive TRIP5 of EPwmXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive TRIP5 of EPwmXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive TRIP5 of EPwmXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive TRIP5 of EPwmXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive TRIP5 of EPwmXbar 
};

union TRIP5MUXENABLE_REG {
    Uint32  all;  
    struct  TRIP5MUXENABLE_BITS  bit;  
};

struct TRIP7MUXENABLE_BITS {                                       // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive TRIP7 of EPwmXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive TRIP7 of EPwmXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive TRIP7 of EPwmXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive TRIP7 of EPwmXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive TRIP7 of EPwmXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive TRIP7 of EPwmXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive TRIP7 of EPwmXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive TRIP7 of EPwmXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive TRIP7 of EPwmXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive TRIP7 of EPwmXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive TRIP7 of EPwmXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive TRIP7 of EPwmXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive TRIP7 of EPwmXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive TRIP7 of EPwmXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive TRIP7 of EPwmXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive TRIP7 of EPwmXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive TRIP7 of EPwmXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive TRIP7 of EPwmXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive TRIP7 of EPwmXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive TRIP7 of EPwmXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive TRIP7 of EPwmXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive TRIP7 of EPwmXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive TRIP7 of EPwmXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive TRIP7 of EPwmXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive TRIP7 of EPwmXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive TRIP7 of EPwmXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive TRIP7 of EPwmXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive TRIP7 of EPwmXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive TRIP7 of EPwmXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive TRIP7 of EPwmXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive TRIP7 of EPwmXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive TRIP7 of EPwmXbar 
};

union TRIP7MUXENABLE_REG {
    Uint32  all;  
    struct  TRIP7MUXENABLE_BITS  bit;  
};

struct TRIP8MUXENABLE_BITS {                                       // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive TRIP8 of EPwmXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive TRIP8 of EPwmXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive TRIP8 of EPwmXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive TRIP8 of EPwmXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive TRIP8 of EPwmXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive TRIP8 of EPwmXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive TRIP8 of EPwmXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive TRIP8 of EPwmXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive TRIP8 of EPwmXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive TRIP8 of EPwmXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive TRIP8 of EPwmXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive TRIP8 of EPwmXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive TRIP8 of EPwmXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive TRIP8 of EPwmXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive TRIP8 of EPwmXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive TRIP8 of EPwmXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive TRIP8 of EPwmXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive TRIP8 of EPwmXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive TRIP8 of EPwmXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive TRIP8 of EPwmXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive TRIP8 of EPwmXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive TRIP8 of EPwmXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive TRIP8 of EPwmXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive TRIP8 of EPwmXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive TRIP8 of EPwmXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive TRIP8 of EPwmXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive TRIP8 of EPwmXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive TRIP8 of EPwmXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive TRIP8 of EPwmXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive TRIP8 of EPwmXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive TRIP8 of EPwmXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive TRIP8 of EPwmXbar 
};

union TRIP8MUXENABLE_REG {
    Uint32  all;  
    struct  TRIP8MUXENABLE_BITS  bit;  
};

struct TRIP9MUXENABLE_BITS {                                       // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive TRIP9 of EPwmXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive TRIP9 of EPwmXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive TRIP9 of EPwmXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive TRIP9 of EPwmXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive TRIP9 of EPwmXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive TRIP9 of EPwmXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive TRIP9 of EPwmXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive TRIP9 of EPwmXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive TRIP9 of EPwmXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive TRIP9 of EPwmXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive TRIP9 of EPwmXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive TRIP9 of EPwmXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive TRIP9 of EPwmXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive TRIP9 of EPwmXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive TRIP9 of EPwmXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive TRIP9 of EPwmXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive TRIP9 of EPwmXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive TRIP9 of EPwmXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive TRIP9 of EPwmXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive TRIP9 of EPwmXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive TRIP9 of EPwmXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive TRIP9 of EPwmXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive TRIP9 of EPwmXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive TRIP9 of EPwmXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive TRIP9 of EPwmXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive TRIP9 of EPwmXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive TRIP9 of EPwmXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive TRIP9 of EPwmXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive TRIP9 of EPwmXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive TRIP9 of EPwmXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive TRIP9 of EPwmXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive TRIP9 of EPwmXbar 
};

union TRIP9MUXENABLE_REG {
    Uint32  all;  
    struct  TRIP9MUXENABLE_BITS  bit;  
};

struct TRIP10MUXENABLE_BITS {                                      // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive TRIP10 of EPwmXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive TRIP10 of EPwmXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive TRIP10 of EPwmXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive TRIP10 of EPwmXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive TRIP10 of EPwmXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive TRIP10 of EPwmXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive TRIP10 of EPwmXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive TRIP10 of EPwmXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive TRIP10 of EPwmXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive TRIP10 of EPwmXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive TRIP10 of EPwmXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive TRIP10 of EPwmXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive TRIP10 of EPwmXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive TRIP10 of EPwmXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive TRIP10 of EPwmXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive TRIP10 of EPwmXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive TRIP10 of EPwmXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive TRIP10 of EPwmXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive TRIP10 of EPwmXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive TRIP10 of EPwmXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive TRIP10 of EPwmXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive TRIP10 of EPwmXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive TRIP10 of EPwmXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive TRIP10 of EPwmXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive TRIP10 of EPwmXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive TRIP10 of EPwmXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive TRIP10 of EPwmXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive TRIP10 of EPwmXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive TRIP10 of EPwmXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive TRIP10 of EPwmXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive TRIP10 of EPwmXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive TRIP10 of EPwmXbar 
};

union TRIP10MUXENABLE_REG {
    Uint32  all;  
    struct  TRIP10MUXENABLE_BITS  bit;  
};

struct TRIP11MUXENABLE_BITS {                                      // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive TRIP11 of EPwmXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive TRIP11 of EPwmXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive TRIP11 of EPwmXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive TRIP11 of EPwmXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive TRIP11 of EPwmXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive TRIP11 of EPwmXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive TRIP11 of EPwmXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive TRIP11 of EPwmXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive TRIP11 of EPwmXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive TRIP11 of EPwmXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive TRIP11 of EPwmXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive TRIP11 of EPwmXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive TRIP11 of EPwmXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive TRIP11 of EPwmXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive TRIP11 of EPwmXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive TRIP11 of EPwmXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive TRIP11 of EPwmXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive TRIP11 of EPwmXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive TRIP11 of EPwmXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive TRIP11 of EPwmXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive TRIP11 of EPwmXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive TRIP11 of EPwmXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive TRIP11 of EPwmXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive TRIP11 of EPwmXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive TRIP11 of EPwmXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive TRIP11 of EPwmXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive TRIP11 of EPwmXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive TRIP11 of EPwmXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive TRIP11 of EPwmXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive TRIP11 of EPwmXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive TRIP11 of EPwmXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive TRIP11 of EPwmXbar 
};

union TRIP11MUXENABLE_REG {
    Uint32  all;  
    struct  TRIP11MUXENABLE_BITS  bit;  
};

struct TRIP12MUXENABLE_BITS {                                      // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive TRIP12 of EPwmXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive TRIP12 of EPwmXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive TRIP12 of EPwmXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive TRIP12 of EPwmXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive TRIP12 of EPwmXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive TRIP12 of EPwmXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive TRIP12 of EPwmXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive TRIP12 of EPwmXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive TRIP12 of EPwmXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive TRIP12 of EPwmXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive TRIP12 of EPwmXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive TRIP12 of EPwmXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive TRIP12 of EPwmXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive TRIP12 of EPwmXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive TRIP12 of EPwmXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive TRIP12 of EPwmXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive TRIP12 of EPwmXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive TRIP12 of EPwmXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive TRIP12 of EPwmXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive TRIP12 of EPwmXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive TRIP12 of EPwmXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive TRIP12 of EPwmXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive TRIP12 of EPwmXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive TRIP12 of EPwmXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive TRIP12 of EPwmXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive TRIP12 of EPwmXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive TRIP12 of EPwmXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive TRIP12 of EPwmXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive TRIP12 of EPwmXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive TRIP12 of EPwmXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive TRIP12 of EPwmXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive TRIP12 of EPwmXbar 
};

union TRIP12MUXENABLE_REG {
    Uint32  all;  
    struct  TRIP12MUXENABLE_BITS  bit;  
};

struct TRIPOUTINV_BITS {                                           // bit descriptions
    Uint16  OUT0:1;                                                // 0 Selects polarity for TRIP4 of EPwmXbar 
    Uint16  OUT1:1;                                                // 1 Selects polarity for TRIP5 of EPwmXbar 
    Uint16  OUT2:1;                                                // 2 Selects polarity for TRIP7 of EPwmXbar 
    Uint16  OUT3:1;                                                // 3 Selects polarity for TRIP8 of EPwmXbar 
    Uint16  OUT4:1;                                                // 4 Selects polarity for TRIP9 of EPwmXbar 
    Uint16  OUT5:1;                                                // 5 Selects polarity for TRIP10 of EPwmXbar 
    Uint16  OUT6:1;                                                // 6 Selects polarity for TRIP11 of EPwmXbar 
    Uint16  OUT7:1;                                                // 7 Selects polarity for TRIP12 of EPwmXbar 
    Uint16  rsvd1:8;                                               // 15:8 Reserved 
    Uint16  rsvd2:16;                                              // 31:16 Reserved 
};

union TRIPOUTINV_REG {
    Uint32  all;  
    struct  TRIPOUTINV_BITS  bit;  
};

struct TRIPLOCK_BITS {                                             // bit descriptions
    Uint16  LOCK:1;                                                // 0 Locks the configuration for EPwmXbar 
    Uint16  rsvd1:15;                                              // 15:1 Reserved 
    Uint16  KEY:16;                                                // 31:16 Write protection KEY 
};

union TRIPLOCK_REG {
    Uint32  all;  
    struct  TRIPLOCK_BITS  bit;  
};

struct AUXSIG0MUX0TO15CFG_BITS {                                   // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for AUXSIG0 of ClbXbar 
};

union AUXSIG0MUX0TO15CFG_REG {
    Uint32  all;  
    struct  AUXSIG0MUX0TO15CFG_BITS  bit;  
};

struct AUXSIG1MUX0TO15CFG_BITS {                                   // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for AUXSIG1 of ClbXbar 
};

union AUXSIG1MUX0TO15CFG_REG {
    Uint32  all;  
    struct  AUXSIG1MUX0TO15CFG_BITS  bit;  
};

struct AUXSIG2MUX0TO15CFG_BITS {                                   // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for AUXSIG2 of ClbXbar 
};

union AUXSIG2MUX0TO15CFG_REG {
    Uint32  all;  
    struct  AUXSIG2MUX0TO15CFG_BITS  bit;  
};

struct AUXSIG3MUX0TO15CFG_BITS {                                   // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for AUXSIG3 of ClbXbar 
};

union AUXSIG3MUX0TO15CFG_REG {
    Uint32  all;  
    struct  AUXSIG3MUX0TO15CFG_BITS  bit;  
};

struct AUXSIG4MUX0TO15CFG_BITS {                                   // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for AUXSIG4 of ClbXbar 
};

union AUXSIG4MUX0TO15CFG_REG {
    Uint32  all;  
    struct  AUXSIG4MUX0TO15CFG_BITS  bit;  
};

struct AUXSIG5MUX0TO15CFG_BITS {                                   // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for AUXSIG5 of ClbXbar 
};

union AUXSIG5MUX0TO15CFG_REG {
    Uint32  all;  
    struct  AUXSIG5MUX0TO15CFG_BITS  bit;  
};

struct AUXSIG6MUX0TO15CFG_BITS {                                   // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for AUXSIG6 of ClbXbar 
};

union AUXSIG6MUX0TO15CFG_REG {
    Uint32  all;  
    struct  AUXSIG6MUX0TO15CFG_BITS  bit;  
};

struct AUXSIG7MUX0TO15CFG_BITS {                                   // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for AUXSIG7 of ClbXbar 
};

union AUXSIG7MUX0TO15CFG_REG {
    Uint32  all;  
    struct  AUXSIG7MUX0TO15CFG_BITS  bit;  
};

struct AUXSIG0MUXENABLE_BITS {                                     // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive AUXSIG0 of ClbXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive AUXSIG0 of ClbXbar 
};

union AUXSIG0MUXENABLE_REG {
    Uint32  all;  
    struct  AUXSIG0MUXENABLE_BITS  bit;  
};

struct AUXSIG1MUXENABLE_BITS {                                     // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive AUXSIG1 of ClbXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive AUXSIG1 of ClbXbar 
};

union AUXSIG1MUXENABLE_REG {
    Uint32  all;  
    struct  AUXSIG1MUXENABLE_BITS  bit;  
};

struct AUXSIG2MUXENABLE_BITS {                                     // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive AUXSIG2 of ClbXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive AUXSIG2 of ClbXbar 
};

union AUXSIG2MUXENABLE_REG {
    Uint32  all;  
    struct  AUXSIG2MUXENABLE_BITS  bit;  
};

struct AUXSIG3MUXENABLE_BITS {                                     // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive AUXSIG3 of ClbXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive AUXSIG3 of ClbXbar 
};

union AUXSIG3MUXENABLE_REG {
    Uint32  all;  
    struct  AUXSIG3MUXENABLE_BITS  bit;  
};

struct AUXSIG4MUXENABLE_BITS {                                     // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive AUXSIG4 of ClbXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive AUXSIG4 of ClbXbar 
};

union AUXSIG4MUXENABLE_REG {
    Uint32  all;  
    struct  AUXSIG4MUXENABLE_BITS  bit;  
};

struct AUXSIG5MUXENABLE_BITS {                                     // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive AUXSIG5 of ClbXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive AUXSIG5 of ClbXbar 
};

union AUXSIG5MUXENABLE_REG {
    Uint32  all;  
    struct  AUXSIG5MUXENABLE_BITS  bit;  
};

struct AUXSIG6MUXENABLE_BITS {                                     // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive AUXSIG6 of ClbXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive AUXSIG6 of ClbXbar 
};

union AUXSIG6MUXENABLE_REG {
    Uint32  all;  
    struct  AUXSIG6MUXENABLE_BITS  bit;  
};

struct AUXSIG7MUXENABLE_BITS {                                     // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive AUXSIG7 of ClbXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive AUXSIG7 of ClbXbar 
};

union AUXSIG7MUXENABLE_REG {
    Uint32  all;  
    struct  AUXSIG7MUXENABLE_BITS  bit;  
};

struct AUXSIGOUTINV_BITS {                                         // bit descriptions
    Uint16  OUT0:1;                                                // 0 Selects polarity for AUXSIG0 of ClbXbar 
    Uint16  OUT1:1;                                                // 1 Selects polarity for AUXSIG1 of ClbXbar 
    Uint16  OUT2:1;                                                // 2 Selects polarity for AUXSIG2 of ClbXbar 
    Uint16  OUT3:1;                                                // 3 Selects polarity for AUXSIG3 of ClbXbar 
    Uint16  OUT4:1;                                                // 4 Selects polarity for AUXSIG4 of ClbXbar 
    Uint16  OUT5:1;                                                // 5 Selects polarity for AUXSIG5 of ClbXbar 
    Uint16  OUT6:1;                                                // 6 Selects polarity for AUXSIG6 of ClbXbar 
    Uint16  OUT7:1;                                                // 7 Selects polarity for AUXSIG7 of ClbXbar 
    Uint16  rsvd1:8;                                               // 15:8 Reserved 
    Uint16  rsvd2:16;                                              // 31:16 Reserved 
};

union AUXSIGOUTINV_REG {
    Uint32  all;  
    struct  AUXSIGOUTINV_BITS  bit;  
};

struct AUXSIGLOCK_BITS {                                           // bit descriptions
    Uint16  LOCK:1;                                                // 0 Locks the configuration for ClbXbar 
    Uint16  rsvd1:15;                                              // 15:1 Reserved 
    Uint16  KEY:16;                                                // 31:16 Write Protection KEY 
};

union AUXSIGLOCK_REG {
    Uint32  all;  
    struct  AUXSIGLOCK_BITS  bit;  
};

struct XTRIPOUT1MUX0TO15CFG_BITS {                                 // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for XTRIPOUT1 of GpioOutXbar 
};

union XTRIPOUT1MUX0TO15CFG_REG {
    Uint32  all;  
    struct  XTRIPOUT1MUX0TO15CFG_BITS  bit;  
};

struct XTRIPOUT2MUX0TO15CFG_BITS {                                 // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for XTRIPOUT2 of GpioOutXbar 
};

union XTRIPOUT2MUX0TO15CFG_REG {
    Uint32  all;  
    struct  XTRIPOUT2MUX0TO15CFG_BITS  bit;  
};

struct XTRIPOUT3MUX0TO15CFG_BITS {                                 // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for XTRIPOUT3 of GpioOutXbar 
};

union XTRIPOUT3MUX0TO15CFG_REG {
    Uint32  all;  
    struct  XTRIPOUT3MUX0TO15CFG_BITS  bit;  
};

struct XTRIPOUT4MUX0TO15CFG_BITS {                                 // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for XTRIPOUT4 of GpioOutXbar 
};

union XTRIPOUT4MUX0TO15CFG_REG {
    Uint32  all;  
    struct  XTRIPOUT4MUX0TO15CFG_BITS  bit;  
};

struct XTRIPOUT5MUX0TO15CFG_BITS {                                 // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for XTRIPOUT5 of GpioOutXbar 
};

union XTRIPOUT5MUX0TO15CFG_REG {
    Uint32  all;  
    struct  XTRIPOUT5MUX0TO15CFG_BITS  bit;  
};

struct XTRIPOUT6MUX0TO15CFG_BITS {                                 // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for XTRIPOUT6 of GpioOutXbar 
};

union XTRIPOUT6MUX0TO15CFG_REG {
    Uint32  all;  
    struct  XTRIPOUT6MUX0TO15CFG_BITS  bit;  
};

struct XTRIPOUT7MUX0TO15CFG_BITS {                                 // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for XTRIPOUT7 of GpioOutXbar 
};

union XTRIPOUT7MUX0TO15CFG_REG {
    Uint32  all;  
    struct  XTRIPOUT7MUX0TO15CFG_BITS  bit;  
};

struct XTRIPOUT8MUX0TO15CFG_BITS {                                 // bit descriptions
    Uint16  Mux0:2;                                                // 1:0 Mux0 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux1:2;                                                // 3:2 Mux1 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux2:2;                                                // 5:4 Mux2 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux3:2;                                                // 7:6 Mux3 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux4:2;                                                // 9:8 Mux4 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux5:2;                                                // 11:10 Mux5 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux6:2;                                                // 13:12 Mux6 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux7:2;                                                // 15:14 Mux7 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux8:2;                                                // 17:16 Mux8 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux9:2;                                                // 19:18 Mux9 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux10:2;                                               // 21:20 Mux10 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux11:2;                                               // 23:22 Mux11 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux12:2;                                               // 25:24 Mux12 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux13:2;                                               // 27:26 Mux13 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux14:2;                                               // 29:28 Mux14 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux15:2;                                               // 31:30 Mux15 Configuration for XTRIPOUT8 of GpioOutXbar 
};

union XTRIPOUT8MUX0TO15CFG_REG {
    Uint32  all;  
    struct  XTRIPOUT8MUX0TO15CFG_BITS  bit;  
};

struct XTRIPOUT1MUXENABLE_BITS {                                   // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive XTRIPOUT1 of GpioOutXbar 
};

union XTRIPOUT1MUXENABLE_REG {
    Uint32  all;  
    struct  XTRIPOUT1MUXENABLE_BITS  bit;  
};

struct XTRIPOUT2MUXENABLE_BITS {                                   // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive XTRIPOUT2 of GpioOutXbar 
};

union XTRIPOUT2MUXENABLE_REG {
    Uint32  all;  
    struct  XTRIPOUT2MUXENABLE_BITS  bit;  
};

struct XTRIPOUT3MUXENABLE_BITS {                                   // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive XTRIPOUT3 of GpioOutXbar 
};

union XTRIPOUT3MUXENABLE_REG {
    Uint32  all;  
    struct  XTRIPOUT3MUXENABLE_BITS  bit;  
};

struct XTRIPOUT4MUXENABLE_BITS {                                   // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive XTRIPOUT4 of GpioOutXbar 
};

union XTRIPOUT4MUXENABLE_REG {
    Uint32  all;  
    struct  XTRIPOUT4MUXENABLE_BITS  bit;  
};

struct XTRIPOUT5MUXENABLE_BITS {                                   // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive XTRIPOUT5 of GpioOutXbar 
};

union XTRIPOUT5MUXENABLE_REG {
    Uint32  all;  
    struct  XTRIPOUT5MUXENABLE_BITS  bit;  
};

struct XTRIPOUT6MUXENABLE_BITS {                                   // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive XTRIPOUT6 of GpioOutXbar 
};

union XTRIPOUT6MUXENABLE_REG {
    Uint32  all;  
    struct  XTRIPOUT6MUXENABLE_BITS  bit;  
};

struct XTRIPOUT7MUXENABLE_BITS {                                   // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive XTRIPOUT7 of GpioOutXbar 
};

union XTRIPOUT7MUXENABLE_REG {
    Uint32  all;  
    struct  XTRIPOUT7MUXENABLE_BITS  bit;  
};

struct XTRIPOUT8MUXENABLE_BITS {                                   // bit descriptions
    Uint16  Mux0:1;                                                // 0 Selects the output of mux0 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux1:1;                                                // 1 Selects the output of Mux1 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux2:1;                                                // 2 Selects the output of Mux2 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux3:1;                                                // 3 Selects the output of Mux3 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux4:1;                                                // 4 Selects the output of Mux4 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux5:1;                                                // 5 Selects the output of Mux5 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux6:1;                                                // 6 Selects the output of Mux6 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux7:1;                                                // 7 Selects the output of Mux7 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux8:1;                                                // 8 Selects the output of Mux8 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux9:1;                                                // 9 Selects the output of Mux9 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux10:1;                                               // 10 Selects the output of Mux10 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux11:1;                                               // 11 Selects the output of Mux11 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux12:1;                                               // 12 Selects the output of Mux12 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux13:1;                                               // 13 Selects the output of Mux13 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux14:1;                                               // 14 Selects the output of Mux14 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux15:1;                                               // 15 Selects the output of Mux15 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux16:1;                                               // 16 Selects the output of Mux16 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux17:1;                                               // 17 Selects the output of Mux17 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux18:1;                                               // 18 Selects the output of Mux18 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux19:1;                                               // 19 Selects the output of Mux19 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux20:1;                                               // 20 Selects the output of Mux20 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux21:1;                                               // 21 Selects the output of Mux21 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux22:1;                                               // 22 Selects the output of Mux22 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux23:1;                                               // 23 Selects the output of Mux23 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux24:1;                                               // 24 Selects the output of Mux24 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux25:1;                                               // 25 Selects the output of Mux25 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux26:1;                                               // 26 Selects the output of Mux26 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux27:1;                                               // 27 Selects the output of Mux27 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux28:1;                                               // 28 Selects the output of Mux28 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux29:1;                                               // 29 Selects the output of Mux29 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux30:1;                                               // 30 Selects the output of Mux30 to drive XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux31:1;                                               // 31 Selects the output of Mux31 to drive XTRIPOUT8 of GpioOutXbar 
};

union XTRIPOUT8MUXENABLE_REG {
    Uint32  all;  
    struct  XTRIPOUT8MUXENABLE_BITS  bit;  
};

struct XTRIPOUTINV_BITS {                                          // bit descriptions
    Uint16  OUT0:1;                                                // 0 Selects polarity for XTRIPOUT1 of GpioOutXbar 
    Uint16  OUT1:1;                                                // 1 Selects polarity for XTRIPOUT2 of GpioOutXbar 
    Uint16  OUT2:1;                                                // 2 Selects polarity for XTRIPOUT3 of GpioOutXbar 
    Uint16  OUT3:1;                                                // 3 Selects polarity for XTRIPOUT4 of GpioOutXbar 
    Uint16  OUT4:1;                                                // 4 Selects polarity for XTRIPOUT5 of GpioOutXbar 
    Uint16  OUT5:1;                                                // 5 Selects polarity for XTRIPOUT6 of GpioOutXbar 
    Uint16  OUT6:1;                                                // 6 Selects polarity for XTRIPOUT7 of GpioOutXbar 
    Uint16  OUT7:1;                                                // 7 Selects polarity for XTRIPOUT8 of GpioOutXbar 
    Uint16  rsvd1:8;                                               // 15:8 Reserved 
    Uint16  rsvd2:16;                                              // 31:16 Reserved 
};

union XTRIPOUTINV_REG {
    Uint32  all;  
    struct  XTRIPOUTINV_BITS  bit;  
};

struct XTRIPLOCK_BITS {                                            // bit descriptions
    Uint16  LOCK:1;                                                // 0 Locks the configuration for GpioOutXbar 
    Uint16  rsvd1:15;                                              // 15:1 Reserved 
    Uint16  KEY:16;                                                // 31:16 Write Protection KEY 
};

union XTRIPLOCK_REG {
    Uint32  all;  
    struct  XTRIPLOCK_BITS  bit;  
};

struct XTRIPOUTLATCH_BITS {                                        // bit descriptions
    Uint16  OUT0:1;                                                // 0 Records the XTRIPOUT1 of GpioOutXbar 
    Uint16  OUT1:1;                                                // 1 Records the XTRIPOUT2 of GpioOutXbar 
    Uint16  OUT2:1;                                                // 2 Records the XTRIPOUT3 of GpioOutXbar 
    Uint16  OUT3:1;                                                // 3 Records the XTRIPOUT4 of GpioOutXbar 
    Uint16  OUT4:1;                                                // 4 Records the XTRIPOUT5 of GpioOutXbar 
    Uint16  OUT5:1;                                                // 5 Records the XTRIPOUT6 of GpioOutXbar 
    Uint16  OUT6:1;                                                // 6 Records the XTRIPOUT7 of GpioOutXbar 
    Uint16  OUT7:1;                                                // 7 Records the XTRIPOUT8 of GpioOutXbar 
    Uint16  rsvd1:8;                                               // 15:8 Reserved 
    Uint16  rsvd2:16;                                              // 31:16 Reserved 
};

union XTRIPOUTLATCH_REG {
    Uint32  all;  
    struct  XTRIPOUTLATCH_BITS  bit;  
};

struct XTRIPOUTLATCHCLR_BITS {                                     // bit descriptions
    Uint16  OUT0:1;                                                // 0 Clears the Output-Latch for XTRIPOUT1 of GpioOutXbar 
    Uint16  OUT1:1;                                                // 1 Clears the Output-Latch for XTRIPOUT2 of GpioOutXbar 
    Uint16  OUT2:1;                                                // 2 Clears the Output-Latch for XTRIPOUT3 of GpioOutXbar 
    Uint16  OUT3:1;                                                // 3 Clears the Output-Latch for XTRIPOUT4 of GpioOutXbar 
    Uint16  OUT4:1;                                                // 4 Clears the Output-Latch for XTRIPOUT5 of GpioOutXbar 
    Uint16  OUT5:1;                                                // 5 Clears the Output-Latch for XTRIPOUT6 of GpioOutXbar 
    Uint16  OUT6:1;                                                // 6 Clears the Output-Latch for XTRIPOUT7 of GpioOutXbar 
    Uint16  OUT7:1;                                                // 7 Clears the Output-Latch for XTRIPOUT8 of GpioOutXbar 
    Uint16  rsvd1:8;                                               // 15:8 Reserved 
    Uint16  rsvd2:16;                                              // 31:16 Reserved 
};

union XTRIPOUTLATCHCLR_REG {
    Uint32  all;  
    struct  XTRIPOUTLATCHCLR_BITS  bit;  
};

struct XTRIPOUTLATCHFRC_BITS {                                     // bit descriptions
    Uint16  OUT0:1;                                                // 0 Sets the Output-Latch for XTRIPOUT1 of GpioOutXbar 
    Uint16  OUT1:1;                                                // 1 Sets the Output-Latch for XTRIPOUT2 of GpioOutXbar 
    Uint16  OUT2:1;                                                // 2 Sets the Output-Latch for XTRIPOUT3 of GpioOutXbar 
    Uint16  OUT3:1;                                                // 3 Sets the Output-Latch for XTRIPOUT4 of GpioOutXbar 
    Uint16  OUT4:1;                                                // 4 Sets the Output-Latch for XTRIPOUT5 of GpioOutXbar 
    Uint16  OUT5:1;                                                // 5 Sets the Output-Latch for XTRIPOUT6 of GpioOutXbar 
    Uint16  OUT6:1;                                                // 6 Sets the Output-Latch for XTRIPOUT7 of GpioOutXbar 
    Uint16  OUT7:1;                                                // 7 Sets the Output-Latch for XTRIPOUT8 of GpioOutXbar 
    Uint16  rsvd1:8;                                               // 15:8 Reserved 
    Uint16  rsvd2:16;                                              // 31:16 Reserved 
};

union XTRIPOUTLATCHFRC_REG {
    Uint32  all;  
    struct  XTRIPOUTLATCHFRC_BITS  bit;  
};

struct XTRIPOUTLATCHENABLE_BITS {                                  // bit descriptions
    Uint16  OUT0:1;                                                // 0 Selects the output latch to drive XTRIPOUT1 for GpioOutXbar 
    Uint16  OUT1:1;                                                // 1 Selects the output latch to drive output1 for GpioOutXbar 
    Uint16  OUT2:1;                                                // 2 Selects the output latch to drive output2 for GpioOutXbar 
    Uint16  OUT3:1;                                                // 3 Selects the output latch to drive output3 for GpioOutXbar 
    Uint16  OUT4:1;                                                // 4 Selects the output latch to drive output4 for GpioOutXbar 
    Uint16  OUT5:1;                                                // 5 Selects the output latch to drive output5 for GpioOutXbar 
    Uint16  OUT6:1;                                                // 6 Selects the output latch to drive output6 for GpioOutXbar 
    Uint16  OUT7:1;                                                // 7 Selects the output latch to drive output7 for GpioOutXbar 
    Uint16  rsvd1:8;                                               // 15:8 Reserved 
    Uint16  rsvd2:16;                                              // 31:16 Reserved 
};

union XTRIPOUTLATCHENABLE_REG {
    Uint32  all;  
    struct  XTRIPOUTLATCHENABLE_BITS  bit;  
};

struct TRIP4MUX16TO31CFG_BITS {                                    // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for TRIP4 of EPwmXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for TRIP4 of EPwmXbar 
};

union TRIP4MUX16TO31CFG_REG {
    Uint32  all;  
    struct  TRIP4MUX16TO31CFG_BITS  bit;  
};

struct TRIP5MUX16TO31CFG_BITS {                                    // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for TRIP5 of EPwmXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for TRIP5 of EPwmXbar 
};

union TRIP5MUX16TO31CFG_REG {
    Uint32  all;  
    struct  TRIP5MUX16TO31CFG_BITS  bit;  
};

struct TRIP7MUX16TO31CFG_BITS {                                    // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for TRIP7 of EPwmXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for TRIP7 of EPwmXbar 
};

union TRIP7MUX16TO31CFG_REG {
    Uint32  all;  
    struct  TRIP7MUX16TO31CFG_BITS  bit;  
};

struct TRIP8MUX16TO31CFG_BITS {                                    // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for TRIP8 of EPwmXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for TRIP8 of EPwmXbar 
};

union TRIP8MUX16TO31CFG_REG {
    Uint32  all;  
    struct  TRIP8MUX16TO31CFG_BITS  bit;  
};

struct TRIP9MUX16TO31CFG_BITS {                                    // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for TRIP9 of EPwmXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for TRIP9 of EPwmXbar 
};

union TRIP9MUX16TO31CFG_REG {
    Uint32  all;  
    struct  TRIP9MUX16TO31CFG_BITS  bit;  
};

struct TRIP10MUX16TO31CFG_BITS {                                   // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for TRIP10 of EPwmXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for TRIP10 of EPwmXbar 
};

union TRIP10MUX16TO31CFG_REG {
    Uint32  all;  
    struct  TRIP10MUX16TO31CFG_BITS  bit;  
};

struct TRIP11MUX16TO31CFG_BITS {                                   // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for TRIP11 of EPwmXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for TRIP11 of EPwmXbar 
};

union TRIP11MUX16TO31CFG_REG {
    Uint32  all;  
    struct  TRIP11MUX16TO31CFG_BITS  bit;  
};

struct TRIP12MUX16TO31CFG_BITS {                                   // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for TRIP12 of EPwmXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for TRIP12 of EPwmXbar 
};

union TRIP12MUX16TO31CFG_REG {
    Uint32  all;  
    struct  TRIP12MUX16TO31CFG_BITS  bit;  
};

struct AUXSIG0MUX16TO31CFG_BITS {                                  // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for AUXSIG0 of ClbXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for AUXSIG0 of ClbXbar 
};

union AUXSIG0MUX16TO31CFG_REG {
    Uint32  all;  
    struct  AUXSIG0MUX16TO31CFG_BITS  bit;  
};

struct AUXSIG1MUX16TO31CFG_BITS {                                  // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for AUXSIG1 of ClbXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for AUXSIG1 of ClbXbar 
};

union AUXSIG1MUX16TO31CFG_REG {
    Uint32  all;  
    struct  AUXSIG1MUX16TO31CFG_BITS  bit;  
};

struct AUXSIG2MUX16TO31CFG_BITS {                                  // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for AUXSIG2 of ClbXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for AUXSIG2 of ClbXbar 
};

union AUXSIG2MUX16TO31CFG_REG {
    Uint32  all;  
    struct  AUXSIG2MUX16TO31CFG_BITS  bit;  
};

struct AUXSIG3MUX16TO31CFG_BITS {                                  // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for AUXSIG3 of ClbXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for AUXSIG3 of ClbXbar 
};

union AUXSIG3MUX16TO31CFG_REG {
    Uint32  all;  
    struct  AUXSIG3MUX16TO31CFG_BITS  bit;  
};

struct AUXSIG4MUX16TO31CFG_BITS {                                  // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for AUXSIG4 of ClbXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for AUXSIG4 of ClbXbar 
};

union AUXSIG4MUX16TO31CFG_REG {
    Uint32  all;  
    struct  AUXSIG4MUX16TO31CFG_BITS  bit;  
};

struct AUXSIG5MUX16TO31CFG_BITS {                                  // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for AUXSIG5 of ClbXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for AUXSIG5 of ClbXbar 
};

union AUXSIG5MUX16TO31CFG_REG {
    Uint32  all;  
    struct  AUXSIG5MUX16TO31CFG_BITS  bit;  
};

struct AUXSIG6MUX16TO31CFG_BITS {                                  // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for AUXSIG6 of ClbXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for AUXSIG6 of ClbXbar 
};

union AUXSIG6MUX16TO31CFG_REG {
    Uint32  all;  
    struct  AUXSIG6MUX16TO31CFG_BITS  bit;  
};

struct AUXSIG7MUX16TO31CFG_BITS {                                  // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for AUXSIG7 of ClbXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for AUXSIG7 of ClbXbar 
};

union AUXSIG7MUX16TO31CFG_REG {
    Uint32  all;  
    struct  AUXSIG7MUX16TO31CFG_BITS  bit;  
};

struct XTRIPOUT1MUX16TO31CFG_BITS {                                // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for XTRIPOUT1 of GpioOutXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for XTRIPOUT1 of GpioOutXbar 
};

union XTRIPOUT1MUX16TO31CFG_REG {
    Uint32  all;  
    struct  XTRIPOUT1MUX16TO31CFG_BITS  bit;  
};

struct XTRIPOUT2MUX16TO31CFG_BITS {                                // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for XTRIPOUT2 of GpioOutXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for XTRIPOUT2 of GpioOutXbar 
};

union XTRIPOUT2MUX16TO31CFG_REG {
    Uint32  all;  
    struct  XTRIPOUT2MUX16TO31CFG_BITS  bit;  
};

struct XTRIPOUT3MUX16TO31CFG_BITS {                                // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for XTRIPOUT3 of GpioOutXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for XTRIPOUT3 of GpioOutXbar 
};

union XTRIPOUT3MUX16TO31CFG_REG {
    Uint32  all;  
    struct  XTRIPOUT3MUX16TO31CFG_BITS  bit;  
};

struct XTRIPOUT4MUX16TO31CFG_BITS {                                // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for XTRIPOUT4 of GpioOutXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for XTRIPOUT4 of GpioOutXbar 
};

union XTRIPOUT4MUX16TO31CFG_REG {
    Uint32  all;  
    struct  XTRIPOUT4MUX16TO31CFG_BITS  bit;  
};

struct XTRIPOUT5MUX16TO31CFG_BITS {                                // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for XTRIPOUT5 of GpioOutXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for XTRIPOUT5 of GpioOutXbar 
};

union XTRIPOUT5MUX16TO31CFG_REG {
    Uint32  all;  
    struct  XTRIPOUT5MUX16TO31CFG_BITS  bit;  
};

struct XTRIPOUT6MUX16TO31CFG_BITS {                                // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for XTRIPOUT6 of GpioOutXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for XTRIPOUT6 of GpioOutXbar 
};

union XTRIPOUT6MUX16TO31CFG_REG {
    Uint32  all;  
    struct  XTRIPOUT6MUX16TO31CFG_BITS  bit;  
};

struct XTRIPOUT7MUX16TO31CFG_BITS {                                // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for XTRIPOUT7 of GpioOutXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for XTRIPOUT7 of GpioOutXbar 
};

union XTRIPOUT7MUX16TO31CFG_REG {
    Uint32  all;  
    struct  XTRIPOUT7MUX16TO31CFG_BITS  bit;  
};

struct XTRIPOUT8MUX16TO31CFG_BITS {                                // bit descriptions
    Uint16  Mux16:2;                                               // 1:0 Mux16 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux17:2;                                               // 3:2 Mux17 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux18:2;                                               // 5:4 Mux18 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux19:2;                                               // 7:6 Mux19 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux20:2;                                               // 9:8 Mux20 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux21:2;                                               // 11:10 Mux21 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux22:2;                                               // 13:12 Mux22 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux23:2;                                               // 15:14 Mux23 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux24:2;                                               // 17:16 Mux24 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux25:2;                                               // 19:18 Mux25 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux26:2;                                               // 21:20 Mux26 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux27:2;                                               // 23:22 Mux27 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux28:2;                                               // 25:24 Mux28 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux29:2;                                               // 27:26 Mux29 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux30:2;                                               // 29:28 Mux30 Configuration for XTRIPOUT8 of GpioOutXbar 
    Uint16  Mux31:2;                                               // 31:30 Mux31 Configuration for XTRIPOUT8 of GpioOutXbar 
};

union XTRIPOUT8MUX16TO31CFG_REG {
    Uint32  all;  
    struct  XTRIPOUT8MUX16TO31CFG_BITS  bit;  
};

#ifdef CPU1
struct TRIG_REGS {
    Uint16                               GPTRIP1SEL;               // GPTRIP1 Input Select Register (GPIO0 to x) 
    Uint16                               GPTRIP2SEL;               // GPTRIP2 Input Select Register (GPIO0 to x) 
    Uint16                               GPTRIP3SEL;               // GPTRIP3 Input Select Register (GPIO0 to x) 
    Uint16                               GPTRIP4SEL;               // GPTRIP4 Input Select Register (GPIO0 to x) 
    Uint16                               GPTRIP5SEL;               // GPTRIP5 Input Select Register (GPIO0 to x) 
    Uint16                               GPTRIP6SEL;               // GPTRIP7 Input Select Register (GPIO0 to x) 
    Uint16                               GPTRIP7SEL;               // GPTRIP8 Input Select Register (GPIO0 to x) 
    Uint16                               GPTRIP8SEL;               // GPTRIP9 Input Select Register (GPIO0 to x) 
    Uint16                               GPTRIP9SEL;               // GPTRIP10 Input Select Register (GPIO0 to x) 
    Uint16                               GPTRIP10SEL;              // GPTRIP11 Input Select Register (GPIO0 to x) 
    Uint16                               GPTRIP11SEL;              // GPTRIP11 Input Select Register (GPIO0 to x) 
    Uint16                               GPTRIP12SEL;              // GPTRIP12 Input Select Register (GPIO0 to x) 
    Uint16                               GPTRIP13SEL;              // GPTRIP13 Input Select Register (GPIO0 to x) 
    Uint16                               GPTRIP14SEL;              // GPTRIP14 Input Select Register (GPIO0 to x) 
    Uint16                               GPTRIP15SEL;              // GPTRIP15 Input Select Register (GPIO0 to x) 
    Uint16                               GPTRIP16SEL;              // GPTRIP16 Input Select Register (GPIO0 to x) 
    Uint16                               rsvd1[14];                // Reserved 
    union   GPTRIPLOCK_REG               GPTRIPLOCK;               // GPTRIP Input Select Lock Register 
    union   XBARILAT1_REG                XBARILAT1;                // X-Bar Input Latch Register-1 
    union   XBARILAT2_REG                XBARILAT2;                // X-Bar Input Latch Register-2 
    union   XBARILAT3_REG                XBARILAT3;                // X-Bar Input Latch Register-3 
    Uint16                               rsvd2[2];                 // Reserved 
    union   XBARILATCLR1_REG             XBARILATCLR1;             // X-Bar Input Latch Clear Register-1 
    union   XBARILATCLR2_REG             XBARILATCLR2;             // X-Bar Input Latch Clear Register-2 
    union   XBARILATCLR3_REG             XBARILATCLR3;             // X-Bar Input Latch Clear Register-3 
    Uint16                               rsvd3[18];                // Reserved 
    union   SYNCSEL_REG                  SYNCSEL;                  // Sync Input and Output Select Register 
    union   EXTADCSOCSEL_REG             EXTADCSOCSEL;             // External ADCSOC Select Register 
    union   SYNCSOCLOCK_REG              SYNCSOCLOCK;              // SYNCSEL and EXTADCSOC Select Lock register 
};
#endif

#ifdef CPU1
struct EPWM_XBAR_REGS {
    union   TRIP4MUX0TO15CFG_REG         TRIP4MUX0TO15CFG;         // EPwmXbar (XTRIP X-Bar) Group Select Register-1 for Output-0 
    union   TRIP4MUX16TO31CFG_REG        TRIP4MUX16TO31CFG;        // EPwmXbar (XTRIP X-Bar) Group Select Register-1 for Output-0 (Reserved) 
    union   TRIP5MUX0TO15CFG_REG         TRIP5MUX0TO15CFG;         // EPwmXbar (XTRIP X-Bar) Group Select Register-1 for Output-1 
    union   TRIP5MUX16TO31CFG_REG        TRIP5MUX16TO31CFG;        // EPwmXbar (XTRIP X-Bar) Group Select Register-1 for Output-1 (Reserved) 
    union   TRIP7MUX0TO15CFG_REG         TRIP7MUX0TO15CFG;         // EPwmXbar (XTRIP X-Bar) Group Select Register-1 for Output-2 
    union   TRIP7MUX16TO31CFG_REG        TRIP7MUX16TO31CFG;        // EPwmXbar (XTRIP X-Bar) Group Select Register-1 for Output-2 (Reserved) 
    union   TRIP8MUX0TO15CFG_REG         TRIP8MUX0TO15CFG;         // EPwmXbar (XTRIP X-Bar) Group Select Register-1 for Output-3 
    union   TRIP8MUX16TO31CFG_REG        TRIP8MUX16TO31CFG;        // EPwmXbar (XTRIP X-Bar) Group Select Register-1 for Output-3 (Reserved) 
    union   TRIP9MUX0TO15CFG_REG         TRIP9MUX0TO15CFG;         // EPwmXbar (XTRIP X-Bar) Group Select Register-1 for Output-4 
    union   TRIP9MUX16TO31CFG_REG        TRIP9MUX16TO31CFG;        // EPwmXbar (XTRIP X-Bar) Group Select Register-1 for Output-4 (Reserved) 
    union   TRIP10MUX0TO15CFG_REG        TRIP10MUX0TO15CFG;        // EPwmXbar (XTRIP X-Bar) Group Select Register-1 for Output-5 
    union   TRIP10MUX16TO31CFG_REG       TRIP10MUX16TO31CFG;       // EPwmXbar (XTRIP X-Bar) Group Select Register-1 for Output-5 (Reserved) 
    union   TRIP11MUX0TO15CFG_REG        TRIP11MUX0TO15CFG;        // EPwmXbar (XTRIP X-Bar) Group Select Register-1 for Output-6 
    union   TRIP11MUX16TO31CFG_REG       TRIP11MUX16TO31CFG;       // EPwmXbar (XTRIP X-Bar) Group Select Register-1 for Output-6 (Reserved) 
    union   TRIP12MUX0TO15CFG_REG        TRIP12MUX0TO15CFG;        // EPwmXbar (XTRIP X-Bar) Group Select Register-1 for Output-7 
    union   TRIP12MUX16TO31CFG_REG       TRIP12MUX16TO31CFG;       // EPwmXbar (XTRIP X-Bar) Group Select Register-1 for Output-7 (Reserved) 
    union   TRIP4MUXENABLE_REG           TRIP4MUXENABLE;           // EPwmXbar (XTRIP X-Bar) Mux Enable Register for Output-0 
    union   TRIP5MUXENABLE_REG           TRIP5MUXENABLE;           // EPwmXbar (XTRIP X-Bar) Mux Enable Register for Output-1 
    union   TRIP7MUXENABLE_REG           TRIP7MUXENABLE;           // EPwmXbar (XTRIP X-Bar) Mux Enable Register for Output-2 
    union   TRIP8MUXENABLE_REG           TRIP8MUXENABLE;           // EPwmXbar (XTRIP X-Bar) Mux Enable Register for Output-3 
    union   TRIP9MUXENABLE_REG           TRIP9MUXENABLE;           // EPwmXbar (XTRIP X-Bar) Mux Enable Register for Output-4 
    union   TRIP10MUXENABLE_REG          TRIP10MUXENABLE;          // EPwmXbar (XTRIP X-Bar) Mux Enable Register for Output-5 
    union   TRIP11MUXENABLE_REG          TRIP11MUXENABLE;          // EPwmXbar (XTRIP X-Bar) Mux Enable Register for Output-6 
    union   TRIP12MUXENABLE_REG          TRIP12MUXENABLE;          // EPwmXbar (XTRIP X-Bar) Mux Enable Register for Output-7 
    Uint16                               rsvd1[8];                 // Reserved 
    union   TRIPOUTINV_REG               TRIPOUTINV;               // EPwmXbar (XTRIP X-Bar) Output Inversion Register 
    Uint16                               rsvd2[4];                 // Reserved 
    union   TRIPLOCK_REG                 TRIPLOCK;                 // EPwmXbar Configuration Lock register 
};
#endif

#ifdef CPU1
struct CLB_XBAR_REGS {
    union   AUXSIG0MUX0TO15CFG_REG       AUXSIG0MUX0TO15CFG;       // ClbXbar (CLB X-Bar) Group Select Register-1 for Output-0 
    union   AUXSIG0MUX16TO31CFG_REG      AUXSIG0MUX16TO31CFG;      // ClbXbar (CLB X-Bar) Group Select Register-1 for Output-0 (Reserved) 
    union   AUXSIG1MUX0TO15CFG_REG       AUXSIG1MUX0TO15CFG;       // ClbXbar (CLB X-Bar) Group Select Register-1 for Output-1 
    union   AUXSIG1MUX16TO31CFG_REG      AUXSIG1MUX16TO31CFG;      // ClbXbar (CLB X-Bar) Group Select Register-1 for Output-1 (Reserved) 
    union   AUXSIG2MUX0TO15CFG_REG       AUXSIG2MUX0TO15CFG;       // ClbXbar (CLB X-Bar) Group Select Register-1 for Output-2 
    union   AUXSIG2MUX16TO31CFG_REG      AUXSIG2MUX16TO31CFG;      // ClbXbar (CLB X-Bar) Group Select Register-1 for Output-2 (Reserved) 
    union   AUXSIG3MUX0TO15CFG_REG       AUXSIG3MUX0TO15CFG;       // ClbXbar (CLB X-Bar) Group Select Register-1 for Output-3 
    union   AUXSIG3MUX16TO31CFG_REG      AUXSIG3MUX16TO31CFG;      // ClbXbar (CLB X-Bar) Group Select Register-1 for Output-3 (Reserved) 
    union   AUXSIG4MUX0TO15CFG_REG       AUXSIG4MUX0TO15CFG;       // ClbXbar (CLB X-Bar) Group Select Register-1 for Output-4 
    union   AUXSIG4MUX16TO31CFG_REG      AUXSIG4MUX16TO31CFG;      // ClbXbar (CLB X-Bar) Group Select Register-1 for Output-4 (Reserved) 
    union   AUXSIG5MUX0TO15CFG_REG       AUXSIG5MUX0TO15CFG;       // ClbXbar (CLB X-Bar) Group Select Register-1 for Output-5 
    union   AUXSIG5MUX16TO31CFG_REG      AUXSIG5MUX16TO31CFG;      // ClbXbar (CLB X-Bar) Group Select Register-1 for Output-5 (Reserved) 
    union   AUXSIG6MUX0TO15CFG_REG       AUXSIG6MUX0TO15CFG;       // ClbXbar (CLB X-Bar) Group Select Register-1 for Output-6 
    union   AUXSIG6MUX16TO31CFG_REG      AUXSIG6MUX16TO31CFG;      // ClbXbar (CLB X-Bar) Group Select Register-1 for Output-6 (Reserved) 
    union   AUXSIG7MUX0TO15CFG_REG       AUXSIG7MUX0TO15CFG;       // ClbXbar (CLB X-Bar) Group Select Register-1 for Output-7 
    union   AUXSIG7MUX16TO31CFG_REG      AUXSIG7MUX16TO31CFG;      // ClbXbar (CLB X-Bar) Group Select Register-1 for Output-7 (Reserved) 
    union   AUXSIG0MUXENABLE_REG         AUXSIG0MUXENABLE;         // ClbXbar (CLB X-Bar) Mux Enable Register for Output-0 
    union   AUXSIG1MUXENABLE_REG         AUXSIG1MUXENABLE;         // ClbXbar (CLB X-Bar) Mux Enable Register for Output-1 
    union   AUXSIG2MUXENABLE_REG         AUXSIG2MUXENABLE;         // ClbXbar (CLB X-Bar) Mux Enable Register for Output-2 
    union   AUXSIG3MUXENABLE_REG         AUXSIG3MUXENABLE;         // ClbXbar (CLB X-Bar) Mux Enable Register for Output-3 
    union   AUXSIG4MUXENABLE_REG         AUXSIG4MUXENABLE;         // ClbXbar (CLB X-Bar) Mux Enable Register for Output-4 
    union   AUXSIG5MUXENABLE_REG         AUXSIG5MUXENABLE;         // ClbXbar (CLB X-Bar) Mux Enable Register for Output-5 
    union   AUXSIG6MUXENABLE_REG         AUXSIG6MUXENABLE;         // ClbXbar (CLB X-Bar) Mux Enable Register for Output-6 
    union   AUXSIG7MUXENABLE_REG         AUXSIG7MUXENABLE;         // ClbXbar (CLB X-Bar) Mux Enable Register for Output-7 
    Uint16                               rsvd1[8];                 // Reserved 
    union   AUXSIGOUTINV_REG             AUXSIGOUTINV;             // ClbXbar (CLB X-Bar) Output Inversion Register 
    Uint16                               rsvd2[4];                 // Reserved 
    union   AUXSIGLOCK_REG               AUXSIGLOCK;               // ClbXbar Configuration Lock register 
};
#endif

#ifdef CPU1
struct GPIO_OUT_XBAR_REGS {
    union   XTRIPOUT1MUX0TO15CFG_REG     XTRIPOUT1MUX0TO15CFG;     // GpioOutXbar (XTRIPOUT X-Bar) Group Select Register-1 for Output-0 
    union   XTRIPOUT1MUX16TO31CFG_REG    XTRIPOUT1MUX16TO31CFG;    // GpioOutXbar (XTRIPOUT X-Bar) Group Select Register-1 for Output-0 (Reserved) 
    union   XTRIPOUT2MUX0TO15CFG_REG     XTRIPOUT2MUX0TO15CFG;     // GpioOutXbar (XTRIPOUT X-Bar) Group Select Register-1 for Output-1 
    union   XTRIPOUT2MUX16TO31CFG_REG    XTRIPOUT2MUX16TO31CFG;    // GpioOutXbar (XTRIPOUT X-Bar) Group Select Register-1 for Output-1 (Reserved) 
    union   XTRIPOUT3MUX0TO15CFG_REG     XTRIPOUT3MUX0TO15CFG;     // GpioOutXbar (XTRIPOUT X-Bar) Group Select Register-1 for Output-2 
    union   XTRIPOUT3MUX16TO31CFG_REG    XTRIPOUT3MUX16TO31CFG;    // GpioOutXbar (XTRIPOUT X-Bar) Group Select Register-1 for Output-2 (Reserved) 
    union   XTRIPOUT4MUX0TO15CFG_REG     XTRIPOUT4MUX0TO15CFG;     // GpioOutXbar (XTRIPOUT X-Bar) Group Select Register-1 for Output-3 
    union   XTRIPOUT4MUX16TO31CFG_REG    XTRIPOUT4MUX16TO31CFG;    // GpioOutXbar (XTRIPOUT X-Bar) Group Select Register-1 for Output-3 (Reserved) 
    union   XTRIPOUT5MUX0TO15CFG_REG     XTRIPOUT5MUX0TO15CFG;     // GpioOutXbar (XTRIPOUT X-Bar) Group Select Register-1 for Output-4 
    union   XTRIPOUT5MUX16TO31CFG_REG    XTRIPOUT5MUX16TO31CFG;    // GpioOutXbar (XTRIPOUT X-Bar) Group Select Register-1 for Output-4 (Reserved) 
    union   XTRIPOUT6MUX0TO15CFG_REG     XTRIPOUT6MUX0TO15CFG;     // GpioOutXbar (XTRIPOUT X-Bar) Group Select Register-1 for Output-5 
    union   XTRIPOUT6MUX16TO31CFG_REG    XTRIPOUT6MUX16TO31CFG;    // GpioOutXbar (XTRIPOUT X-Bar) Group Select Register-1 for Output-5 (Reserved) 
    union   XTRIPOUT7MUX0TO15CFG_REG     XTRIPOUT7MUX0TO15CFG;     // GpioOutXbar (XTRIPOUT X-Bar) Group Select Register-1 for Output-6 
    union   XTRIPOUT7MUX16TO31CFG_REG    XTRIPOUT7MUX16TO31CFG;    // GpioOutXbar (XTRIPOUT X-Bar) Group Select Register-1 for Output-6 (Reserved) 
    union   XTRIPOUT8MUX0TO15CFG_REG     XTRIPOUT8MUX0TO15CFG;     // GpioOutXbar (XTRIPOUT X-Bar) Group Select Register-1 for Output-7 
    union   XTRIPOUT8MUX16TO31CFG_REG    XTRIPOUT8MUX16TO31CFG;    // GpioOutXbar (XTRIPOUT X-Bar) Group Select Register-1 for Output-7 (Reserved) 
    union   XTRIPOUT1MUXENABLE_REG       XTRIPOUT1MUXENABLE;       // GpioOutXbar (XTRIPOUT X-Bar) Mux Enable Register for Output-0 
    union   XTRIPOUT2MUXENABLE_REG       XTRIPOUT2MUXENABLE;       // GpioOutXbar (XTRIPOUT X-Bar) Mux Enable Register for Output-1 
    union   XTRIPOUT3MUXENABLE_REG       XTRIPOUT3MUXENABLE;       // GpioOutXbar (XTRIPOUT X-Bar) Mux Enable Register for Output-2 
    union   XTRIPOUT4MUXENABLE_REG       XTRIPOUT4MUXENABLE;       // GpioOutXbar (XTRIPOUT X-Bar) Mux Enable Register for Output-3 
    union   XTRIPOUT5MUXENABLE_REG       XTRIPOUT5MUXENABLE;       // GpioOutXbar (XTRIPOUT X-Bar) Mux Enable Register for Output-4 
    union   XTRIPOUT6MUXENABLE_REG       XTRIPOUT6MUXENABLE;       // GpioOutXbar (XTRIPOUT X-Bar) Mux Enable Register for Output-5 
    union   XTRIPOUT7MUXENABLE_REG       XTRIPOUT7MUXENABLE;       // GpioOutXbar (XTRIPOUT X-Bar) Mux Enable Register for Output-6 
    union   XTRIPOUT8MUXENABLE_REG       XTRIPOUT8MUXENABLE;       // GpioOutXbar (XTRIPOUT X-Bar) Mux Enable Register for Output-7 
    union   XTRIPOUTLATCH_REG            XTRIPOUTLATCH;            // GpioOutXbar (XTRIPOUT X-Bar) Output Latch Register 
    union   XTRIPOUTLATCHCLR_REG         XTRIPOUTLATCHCLR;         // GpioOutXbar (XTRIPOUT X-Bar) Output Latch Clear register 
    union   XTRIPOUTLATCHFRC_REG         XTRIPOUTLATCHFRC;         // GpioOutXbar (XTRIPOUT X-Bar) Output Latch Clear register 
    union   XTRIPOUTLATCHENABLE_REG      XTRIPOUTLATCHENABLE;      // GpioOutXbar (XTRIPOUT X-Bar) Output Latch Enable Register 
    union   XTRIPOUTINV_REG              XTRIPOUTINV;              // GpioOutXbar (XTRIPOUT X-Bar) Output Inversion Register 
    Uint16                               rsvd1[4];                 // Reserved 
    union   XTRIPLOCK_REG                XTRIPLOCK;                // GpioOutXbar Configuration Lock register 
};
#endif

//---------------------------------------------------------------------------
// Xbar External References & Function Declarations:
//

#ifdef CPU1
extern volatile struct TRIG_REGS TrigRegs;
#endif
#ifdef CPU1
extern volatile struct EPWM_XBAR_REGS EPwmXbarRegs;
#endif
#ifdef CPU1
extern volatile struct CLB_XBAR_REGS ClbXbarRegs;
#endif
#ifdef CPU1
extern volatile struct GPIO_OUT_XBAR_REGS GpioOutXbarRegs;
#endif

#ifdef __cplusplus
}
#endif                                                             /* extern "C" */


#endif                                                             // end of F2837x_XBAR_H definition
//===========================================================================
// End of file.
//===========================================================================
