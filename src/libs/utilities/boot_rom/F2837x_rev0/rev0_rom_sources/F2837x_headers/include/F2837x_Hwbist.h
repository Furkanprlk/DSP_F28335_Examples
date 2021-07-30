//###########################################################################
//
// FILE:   F2837x_HWBIST.h
//
// TITLE:  F2837x Device HWBIST Register Definitions.
//
//###########################################################################
// $TI Release:   $
// $Release Date:   $
//###########################################################################

#ifndef F2837x_HWBIST_H
#define F2837x_HWBIST_H
#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// HWBIST Individual Register Bit Definitions:

struct CSTCGCR0_BITS {                                // bit descriptions
    Uint16  BIST_DISABLE:4;                           // 3:0 HWBIST DISABLE 
    Uint16  rsvd1:12;                                 // 15:4 Reserved 
    Uint16  rsvd2:16;                                 // 31:16 Reserved 
};

union CSTCGCR0_REG {
    Uint32  all;  
    struct  CSTCGCR0_BITS  bit;  
};

struct CSTCGCR1_BITS {                                // bit descriptions
    Uint32  MICROCFG:32;                              // 31:0 Micro Configuration 
};

union CSTCGCR1_REG {
    Uint32  all;  
    struct  CSTCGCR1_BITS  bit;  
};

struct CSTCGCR2_BITS {                                // bit descriptions
    Uint16  MACROCFG:16;                              // 15:0 Macro Configuration 
    Uint16  rsvd1:16;                                 // 31:16 Reserved 
};

union CSTCGCR2_REG {
    Uint32  all;  
    struct  CSTCGCR2_BITS  bit;  
};

struct CSTCGCR3_BITS {                                // bit descriptions
    Uint16  ILS:4;                                    // 3:0 Interrupt Logging Start 
    Uint16  rsvd1:12;                                 // 15:4 Reserved 
    Uint16  rsvd2:16;                                 // 31:16 Reserved 
};

union CSTCGCR3_REG {
    Uint32  all;  
    struct  CSTCGCR3_BITS  bit;  
};

struct CSTCGCR4_BITS {                                // bit descriptions
    Uint16  BISTGO:4;                                 // 3:0 BIST Start 
    Uint16  rsvd1:12;                                 // 15:4 Reserved 
    Uint16  rsvd2:16;                                 // 31:16 Reserved 
};

union CSTCGCR4_REG {
    Uint32  all;  
    struct  CSTCGCR4_BITS  bit;  
};

struct CSTCGCR5_BITS {                                // bit descriptions
    Uint16  RESTART:4;                                // 3:0 Restart Enable 
    Uint16  rsvd1:12;                                 // 15:4 Reserved 
    Uint16  rsvd2:15;                                 // 30:16 Reserved 
    Uint16  SOFT_RESET:1;                             // 31 Soft reset to BIST controller 
};

union CSTCGCR5_REG {
    Uint32  all;  
    struct  CSTCGCR5_BITS  bit;  
};

struct CSTCGCR6_BITS {                                // bit descriptions
    Uint16  COV:2;                                    // 1:0 COVERAGE 
    Uint16  rsvd1:14;                                 // 15:2 Reserved 
    Uint16  rsvd2:16;                                 // 31:16 Reserved 
};

union CSTCGCR6_REG {
    Uint32  all;  
    struct  CSTCGCR6_BITS  bit;  
};

struct CSTCGCR7_BITS {                                // bit descriptions
    Uint16  MCL:8;                                    // 7:0 MAX CHAIN LENGTH 
    Uint16  DC:4;                                     // 11:8 DEAD CYCLES 
    Uint16  NP:4;                                     // 15:12 NUM OF PIPELINE STAGES 
    Uint16  PST:2;                                    // 17:16 PATTERN SET TYPE 
    Uint16  SCD:2;                                    // 19:18 SHIFT_CLOCK_DIVISION 
    Uint16  rsvd1:12;                                 // 31:20 Reserved 
};

union CSTCGCR7_REG {
    Uint32  all;  
    struct  CSTCGCR7_BITS  bit;  
};

struct CSTCGCR8_BITS {                                // bit descriptions
    Uint16  BMCPC:16;                                 // 15:0 BREVE MISR COMPARE PATTERN CNT 
    Uint16  rsvd1:16;                                 // 31:16 Reserved 
};

union CSTCGCR8_REG {
    Uint32  all;  
    struct  CSTCGCR8_BITS  bit;  
};

struct CSTCPCNT_BITS {                                // bit descriptions
    Uint16  PCNT_95:16;                               // 15:0 PATTERNS FOR 95% COVERAGE 
    Uint16  PCNT_99:16;                               // 31:16 PATTERNS FOR 99% COVERAGE 
};

union CSTCPCNT_REG {
    Uint32  all;  
    struct  CSTCPCNT_BITS  bit;  
};

struct CSTCCONFIG_BITS {                              // bit descriptions
    Uint16  CFGDONE:4;                                // 3:0 Configuration done 
    Uint16  rsvd1:12;                                 // 15:4 Reserved 
    Uint16  rsvd2:16;                                 // 31:16 Reserved 
};

union CSTCCONFIG_REG {
    Uint32  all;  
    struct  CSTCCONFIG_BITS  bit;  
};

struct CSTCSADDR_REG {                                // bit descriptions
    Uint16  SAPAT:16;                                 // 15:0 PATTERN ROM Start Address 
    Uint16  SAMISR:16;                                // 31:16 MISR ROM Start Address 
};

union CSTCSADDR_GROUP {
    Uint32  all;  
    struct  CSTCSADDR_REG  half;  
};

struct CSTCTEST_BITS {                                // bit descriptions
    Uint16  TEST_TO:4;                                // 3:0 Test_ Time_Out 
    Uint16  TEST_ARIA_CMP_FAIL:4;                     // 7:4 Test Aria MISR compare fail 
    Uint16  TEST_NMI:4;                               // 11:8 Test_NMI 
    Uint32  TEST:20;                                  // 31:12 TEST Bits 
};

union CSTCTEST_REG {
    Uint32  all;  
    struct  CSTCTEST_BITS  bit;  
};

struct CSTCRET_BITS {                                 // bit descriptions
    Uint32  RETADDR:32;                               // 31:0 Return Address 
};

union CSTCRET_REG {
    Uint32  all;  
    struct  CSTCRET_BITS  bit;  
};

struct CSTCCRD_BITS {                                 // bit descriptions
    Uint16  RESTORE_DONE:4;                           // 3:0 Context Restore Done 
    Uint16  rsvd1:12;                                 // 15:4 Reserved 
    Uint16  rsvd2:16;                                 // 31:16 Reserved 
};

union CSTCCRD_REG {
    Uint32  all;  
    struct  CSTCCRD_BITS  bit;  
};

struct CSTCGSTAT_BITS {                               // bit descriptions
    Uint16  BISTDONE:1;                               // 0 HW BIST Complete 
    Uint16  MACRODONE:1;                              // 1 Macro test slot Complete 
    Uint16  NMI:1;                                    // 2 Exit due to NMI 
    Uint16  BISTFAIL:1;                               // 3 HW BIST Failure 
    Uint16  INTCMPF:1;                                // 4 Intermediate Comparison Failure 
    Uint16  TOFAIL:1;                                 // 5 Time Out Failure 
    Uint16  rsvd1:10;                                 // 15:6 Reserved 
    Uint16  rsvd2:16;                                 // 31:16 Reserved 
};

union CSTCGSTAT_REG {
    Uint32  all;  
    struct  CSTCGSTAT_BITS  bit;  
};

struct CSTCCPCR_BITS {                                // bit descriptions
    Uint16  PATCNT:16;                                // 15:0 Current Pattern Count 
    Uint16  rsvd1:16;                                 // 31:16 Reserved 
};

union CSTCCPCR_REG {
    Uint32  all;  
    struct  CSTCCPCR_BITS  bit;  
};

struct CSTCCADDR_REG {                                // bit descriptions
    Uint16  PATADDR:16;                               // 15:0 Current Pattern ROM Address 
    Uint16  MISRADDR:16;                              // 31:16 Current MISR ROM Address 
};

union CSTCCADDR_GROUP {
    Uint32  all;  
    struct  CSTCCADDR_REG  half;  
};

struct CSTCSEM_BITS {                                 // bit descriptions
    Uint32  SEMAPHORE:2;                              // 1:0 Semaphore
    Uint32  rsvd1:14;                                 // 15:2 Reserved
    Uint32  rsvd2:16;                                 // 31:16 Reserved
};

union CSTCSEM_REG {
    Uint32  all;  
    struct  CSTCSEM_BITS  bit;  
};
/*
struct HWBIST_REGS {
    union   CSTCGCR0_REG       CSTCGCR0;              // STC Global Control Register0 
    union   CSTCGCR1_REG       CSTCGCR1;              // STC Global Control Register1 
    union   CSTCGCR2_REG       CSTCGCR2;              // STC Global Control Register2 
    union   CSTCGCR3_REG       CSTCGCR3;              // STC Global Control Register3 
    union   CSTCGCR4_REG       CSTCGCR4;              // STC Global Control Register4 
    union   CSTCGCR5_REG       CSTCGCR5;              // STC Global Control Register5 
    union   CSTCGCR6_REG       CSTCGCR6;              // STC Global Control Register6 
    union   CSTCGCR7_REG       CSTCGCR7;              // STC Global Control Register7 
    union   CSTCGCR8_REG       CSTCGCR8;              // STC Global Control Register8 
    union   CSTCPCNT_REG       CSTCPCNT;              // STC Pattern Count Register 
    union   CSTCCONFIG_REG     CSTCCONFIG;            // STC Registers Configuration Status 
    union   CSTCSADDR_GROUP    CSTCSADDR;             // STC ROM Start Address 
    union   CSTCTEST_REG       CSTCTEST;              // C28 HW BIST Test Register 
    union   CSTCRET_REG        CSTCRET;               // C28 Return PC Address 
    union   CSTCCRD_REG        CSTCCRD;               // C28 Context Restore Done Register 
    Uint16                     rsvd1[4];              // Reserved 
    union   CSTCGSTAT_REG      CSTCGSTAT;             // STC Global Status Register 
    Uint16                     rsvd2[4];              // Reserved 
    union   CSTCCPCR_REG       CSTCCPCR;              // STC Current Pattern Count Register 
    union   CSTCCADDR_GROUP    CSTCCADDR;             // STC Current ROM Address Register 
    Uint32                     CSTCMISR0;             // MISR Result Register 0 
    Uint32                     CSTCMISR1;             // MISR Result Register 1 
    Uint32                     CSTCMISR2;             // MISR Result Register 2 
    Uint32                     CSTCMISR3;             // MISR Result Register 3 
    Uint32                     CSTCMISR4;             // MISR Result Register 4 
    Uint32                     CSTCMISR5;             // MISR Result Register 5 
    Uint32                     CSTCMISR6;             // MISR Result Register 6 
    Uint32                     CSTCMISR7;             // MISR Result Register 7 
    Uint32                     CSTCMISR8;             // MISR Result Register 8 
    Uint32                     CSTCMISR9;             // MISR Result Register 9 
    Uint32                     CSTCMISR10;            // MISR Result Register 10 
    Uint32                     CSTCMISR11;            // MISR Result Register 11 
    Uint32                     CSTCMISR12;            // MISR Result Register 12 
    Uint32                     CSTCMISR13;            // MISR Result Register 13 
    Uint32                     CSTCMISR14;            // MISR Result Register 14 
    Uint32                     CSTCMISR15;            // MISR Result Register 15 
    Uint16                     rsvd3[16];             // Reserved 
    union   CSTCSEM_REG        CSTCSEM;               // STC Semaphore register 
    Uint16                     rsvd4[46];             // Reserved 
};*/
struct HWBIST_REGS {
    union CSTCGCR0_REG CSTCGCR0;     // STC Global Control Register0
    Uint16 rsvd1[2];     // Reserved
    union CSTCGCR1_REG CSTCGCR1;     // STC Global Control Register1
    Uint16 rsvd2[2];     // Reserved
    union CSTCGCR2_REG CSTCGCR2;     // STC Global Control Register2
    Uint16 rsvd3[2];     // Reserved
    union CSTCGCR3_REG CSTCGCR3;     // STC Global Control Register3
    Uint16 rsvd4[2];     // Reserved
    union CSTCGCR4_REG CSTCGCR4;     // STC Global Control Register4
    Uint16 rsvd5[2];     // Reserved
    union CSTCGCR5_REG CSTCGCR5;     // STC Global Control Register5
    Uint16 rsvd6[2];     // Reserved
    union CSTCGCR6_REG CSTCGCR6;     // STC Global Control Register6
    Uint16 rsvd7[2];     // Reserved
    union CSTCGCR7_REG CSTCGCR7;     // STC Global Control Register7
    Uint16 rsvd8[2];     // Reserved
    union CSTCGCR8_REG CSTCGCR8;     // STC Global Control Register8
    Uint16 rsvd9[2];     // Reserved
    union CSTCPCNT_REG CSTCPCNT;     // STC Pattern Count Register
    Uint16 rsvd10[2];     // Reserved
    union CSTCCONFIG_REG CSTCCONFIG;     // STC Registers Configuration Status
    Uint16 rsvd11[2];     // Reserved
    union CSTCSADDR_GROUP CSTCSADDR;     // STC ROM Start Address
    Uint16 rsvd12[2];     // Reserved
    union CSTCTEST_REG CSTCTEST;     // C28 HW BIST Test Register
    Uint16 rsvd13[2];     // Reserved
    union CSTCRET_REG CSTCRET;     // C28 Return PC Address
    Uint16 rsvd14[2];     // Reserved
    union CSTCCRD_REG CSTCCRD;     // C28 Context Restore Done Register
    Uint16 rsvd15[6];     // Reserved
    union CSTCGSTAT_REG CSTCGSTAT;     // STC Global Status Register
    Uint16 rsvd16[6];     // Reserved
    union CSTCCPCR_REG CSTCCPCR;     // STC Current Pattern Count Register
    Uint16 rsvd17[2];     // Reserved
    union CSTCCADDR_GROUP CSTCCADDR;     // STC Current ROM Address Register
    Uint16 rsvd18[2];     // Reserved
    Uint32 CSTCMISR0;     // MISR Result Register 0
    Uint16 rsvd19[2];     // Reserved
    Uint32 CSTCMISR1;     // MISR Result Register 1
    Uint16 rsvd20[2];     // Reserved
    Uint32 CSTCMISR2;     // MISR Result Register 2
    Uint16 rsvd21[2];     // Reserved
    Uint32 CSTCMISR3;     // MISR Result Register 3
    Uint16 rsvd22[2];     // Reserved
    Uint32 CSTCMISR4;     // MISR Result Register 4
    Uint16 rsvd23[2];     // Reserved
    Uint32 CSTCMISR5;     // MISR Result Register 5
    Uint16 rsvd24[2];     // Reserved
    Uint32 CSTCMISR6;     // MISR Result Register 6
    Uint16 rsvd25[2];     // Reserved
    Uint32 CSTCMISR7;     // MISR Result Register 7
    Uint16 rsvd26[2];     // Reserved
    Uint32 CSTCMISR8;     // MISR Result Register 8
    Uint16 rsvd27[2];     // Reserved
    Uint32 CSTCMISR9;     // MISR Result Register 9
    Uint16 rsvd28[2];     // Reserved
    Uint32 CSTCMISR10;     // MISR Result Register 10
    Uint16 rsvd29[2];     // Reserved
    Uint32 CSTCMISR11;     // MISR Result Register 11
    Uint16 rsvd30[2];     // Reserved
    Uint32 CSTCMISR12;     // MISR Result Register 12
    Uint16 rsvd31[2];     // Reserved
    Uint32 CSTCMISR13;     // MISR Result Register 13
    Uint16 rsvd32[2];     // Reserved
    Uint32 CSTCMISR14;     // MISR Result Register 14
    Uint16 rsvd33[2];     // Reserved
    Uint32 CSTCMISR15;     // MISR Result Register 15
    Uint16 rsvd34[18];     // Reserved
    union CSTCSEM_REG CSTCSEM;     // STC Semaphore register

};
//---------------------------------------------------------------------------
// HWBIST External References & Function Declarations:
//

extern volatile struct HWBIST_REGS HwbistRegs;

#ifdef __cplusplus
}
#endif                                                /* extern "C" */


#endif                                                // end of F2837x_HWBIST_H definition
//===========================================================================
// End of file.
//===========================================================================
