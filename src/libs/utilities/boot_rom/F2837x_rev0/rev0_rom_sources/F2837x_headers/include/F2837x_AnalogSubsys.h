//###########################################################################
//
// FILE:   F2837x_ANALOGSUBSYS.h
//
// TITLE:  F2837x Device ANALOGSUBSYS Register Definitions.
//
//###########################################################################
// $TI Release:   $
// $Release Date:   $
//###########################################################################

#ifndef F2837x_ANALOGSUBSYS_H
#define F2837x_ANALOGSUBSYS_H
#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// ANALOGSUBSYS Individual Register Bit Definitions:

struct INTOSC1TRIM_BITS {                             // bit descriptions
    Uint16  VALFINETRIM:12;                           // 11:0 Oscillator Value Fine Trim Bits 
    Uint16  rsvd1:4;                                  // 15:12 Reserved 
    Uint16  SLOPETRIM:8;                              // 23:16 Oscillator Slope Trim Bits 
    Uint16  rsvd2:8;                                  // 31:24 Reserved 
};

union INTOSC1TRIM_REG {
    Uint32  all;  
    struct  INTOSC1TRIM_BITS  bit;  
};

struct INTOSC2TRIM_BITS {                             // bit descriptions
    Uint16  VALFINETRIM:12;                           // 11:0 Oscillator Value Fine Trim Bits 
    Uint16  rsvd1:4;                                  // 15:12 Reserved 
    Uint16  SLOPETRIM:8;                              // 23:16 Oscillator Slope Trim Bits 
    Uint16  rsvd2:8;                                  // 31:24 Reserved 
};

union INTOSC2TRIM_REG {
    Uint32  all;  
    struct  INTOSC2TRIM_BITS  bit;  
};

struct TSNSCTL_BITS {                                 // bit descriptions
    Uint16  ENABLE:1;                                 // 0 Temperature Sensor Enable 
    Uint16  rsvd1:15;                                 // 15:1 Reserved 
};

union TSNSCTL_REG {
    Uint16  all;  
    struct  TSNSCTL_BITS  bit;  
};

struct ANAREFCTL_BITS {                               // bit descriptions
    Uint16  ANAREF1SEL:1;                             // 0 Analog Reference 1 Select 
    Uint16  ANAREF2SEL:1;                             // 1 Analog Reference 2 Select 
    Uint16  ANAREF3SEL:1;                             // 2 Analog Reference 3 Select 
    Uint16  ANAREF4SEL:1;                             // 3 Analog Reference 4 Select 
    Uint16  rsvd1:12;                                 // 15:4 Reserved 
};

union ANAREFCTL_REG {
    Uint16  all;  
    struct  ANAREFCTL_BITS  bit;  
};

struct VMONCTL_BITS {                                 // bit descriptions
    Uint16  OVMONENZ:1;                               // 0 Over Voltage Monitor Enable Low 
    Uint16  OVFNMIEN:1;                               // 1 Over Voltage Fault NMI Enable 
    Uint16  VMON2ENZ:1;                               // 2 Voltage Monitor 2 Enable Low 
    Uint16  rsvd1:13;                                 // 15:3 Reserved 
};

union VMONCTL_REG {
    Uint16  all;  
    struct  VMONCTL_BITS  bit;  
};

struct VMONSTS_BITS {                                 // bit descriptions
    Uint16  OVF:1;                                    // 0 Over Voltage Fault 
    Uint16  VMON2FLT:1;                               // 1 Voltage Monitor 2 Fault 
    Uint16  VMON2STS:1;                               // 2 Voltage Monitor 2 Status 
    Uint16  rsvd1:13;                                 // 15:3 Reserved 
};

union VMONSTS_REG {
    Uint16  all;  
    struct  VMONSTS_BITS  bit;  
};

struct VMONCLR_BITS {                                 // bit descriptions
    Uint16  OVF:1;                                    // 0 Over Voltage Fault Clear 
    Uint16  VMON2FLT:1;                               // 1 Voltage Monitor 2 Fault Clear 
    Uint16  rsvd1:14;                                 // 15:2 Reserved 
};

union VMONCLR_REG {
    Uint16  all;  
    struct  VMONCLR_BITS  bit;  
};

struct VREGCTL_BITS {                                 // bit descriptions
    Uint16  VREG2ENZ:1;                               // 0 Voltage Regulator 2 Enable Active Low 
    Uint16  VSINKEN:1;                                // 1 Voltage Sink Regulator Enable 
    Uint16  rsvd1:14;                                 // 15:2 Reserved 
};

union VREGCTL_REG {
    Uint16  all;  
    struct  VREGCTL_BITS  bit;  
};

struct LOCK_BITS {                                    // bit descriptions
    Uint16  INTOSC1TRIM:1;                            // 0 Internal Oscillator 1 Trim Register Lock 
    Uint16  INTOSC2TRIM:1;                            // 1 Internal Oscillator 2 Trim Register Lock 
    Uint16  INTERNALTESTCTL:1;                        // 2 Internal Test Node Control Register Lock 
    Uint16  TSNSCTL:1;                                // 3 Temperature Sensor Control Register Lock 
    Uint16  ANAREFCTL:1;                              // 4 Analog Reference Control Register Lock 
    Uint16  VMONCTL:1;                                // 5 Voltage Monitor Control Register Lock 
    Uint16  VREGCTL:1;                                // 6 Voltage Regulator Control Register Lock 
    Uint16  rsvd1:13;                                 // 19:7 Reserved 
    Uint16  INTOSC1CSR:1;                             // 20 Internal Oscillator 1 Control and Status Register Lock 
    Uint16  INTOSC2CSR:1;                             // 21 Internal Oscillator 2 Control and Status Register Lock 
    Uint16  TSNSCFG:1;                                // 22 Temperature Sensor Config Register Lock 
    Uint16  OSCREFTRIM:1;                             // 23 Oscillator Reference Trim Register Lock 
    Uint16  ANAREFTRIM1:1;                            // 24 Analog Reference 1 Trim Register Lock 
    Uint16  ANAREFTRIM2:1;                            // 25 Analog Reference 2 Trim Register Lock 
    Uint16  ANAREFTRIM3:1;                            // 26 Analog Reference 3 Trim Register Lock 
    Uint16  ANAREFTRIM4:1;                            // 27 Analog Reference 4 Trim Register Lock 
    Uint16  PMMREFTRIM:1;                             // 28 Power Management Module Reference Trim Register Lock 
    Uint16  PMMTRIM:1;                                // 29 Power Management Module Trim Register Lock 
    Uint16  PMMCSR:1;                                 // 30 Power Management Module Control and Status Register Lock 
    Uint16  TESTANACTL:1;                             // 31 Analog Test Control Register Lock 
};

union LOCK_REG {
    Uint32  all;  
    struct  LOCK_BITS  bit;  
};

struct INTOSC1CSR_BITS {                              // bit descriptions
    Uint16  OSCCONFIG:12;                             // 11:0 Internal Oscillator 1 Config Bits 
    Uint16  OSCSTATUS:4;                              // 15:12 Internal Oscillator 1 Status Bits 
};

union INTOSC1CSR_REG {
    Uint16  all;  
    struct  INTOSC1CSR_BITS  bit;  
};

struct INTOSC2CSR_BITS {                              // bit descriptions
    Uint16  OSCCONFIG:12;                             // 11:0 Internal Oscillator 2 Config Bits 
    Uint16  OSCSTATUS:4;                              // 15:12 Internal Oscillator 2 Status Bits 
};

union INTOSC2CSR_REG {
    Uint16  all;  
    struct  INTOSC2CSR_BITS  bit;  
};

struct OSCREFTRIM_BITS {                              // bit descriptions
    Uint16  BGVALTRIM:6;                              // 5:0 Bandgap Value Trim 
    Uint16  BGSLOPETRIM:5;                            // 10:6 Bandgap Slope Trim 
    Uint16  IREFTRIM:5;                               // 15:11 Reference Current Trim 
    Uint16  COARSETRIM:10;                            // 25:16 Coarse Frequency Trim 
    Uint16  rsvd1:6;                                  // 31:26 Reserved 
};

union OSCREFTRIM_REG {
    Uint32  all;  
    struct  OSCREFTRIM_BITS  bit;  
};

struct ANAREFTRIM1_BITS {                             // bit descriptions
    Uint16  BGVALTRIM:6;                              // 5:0 Bandgap Value Trim 
    Uint16  BGSLOPETRIM:5;                            // 10:6 Bandgap Slope Trim 
    Uint16  IREFTRIM:5;                               // 15:11 Reference Current Trim 
    Uint16  CONFIG:8;                                 // 23:16 Configuration Bits 
    Uint16  rsvd1:8;                                  // 31:24 Reserved 
};

union ANAREFTRIM1_REG {
    Uint32  all;  
    struct  ANAREFTRIM1_BITS  bit;  
};

struct ANAREFTRIM2_BITS {                             // bit descriptions
    Uint16  BGVALTRIM:6;                              // 5:0 Bandgap Value Trim 
    Uint16  BGSLOPETRIM:5;                            // 10:6 Bandgap Slope Trim 
    Uint16  IREFTRIM:5;                               // 15:11 Reference Current Trim 
    Uint16  CONFIG:8;                                 // 23:16 Configuration Bits 
    Uint16  rsvd1:8;                                  // 31:24 Reserved 
};

union ANAREFTRIM2_REG {
    Uint32  all;  
    struct  ANAREFTRIM2_BITS  bit;  
};

struct ANAREFTRIM3_BITS {                             // bit descriptions
    Uint16  BGVALTRIM:6;                              // 5:0 Bandgap Value Trim 
    Uint16  BGSLOPETRIM:5;                            // 10:6 Bandgap Slope Trim 
    Uint16  IREFTRIM:5;                               // 15:11 Reference Current Trim 
    Uint16  CONFIG:8;                                 // 23:16 Configuration Bits 
    Uint16  rsvd1:8;                                  // 31:24 Reserved 
};

union ANAREFTRIM3_REG {
    Uint32  all;  
    struct  ANAREFTRIM3_BITS  bit;  
};

struct ANAREFTRIM4_BITS {                             // bit descriptions
    Uint16  BGVALTRIM:6;                              // 5:0 Bandgap Value Trim 
    Uint16  BGSLOPETRIM:5;                            // 10:6 Bandgap Slope Trim 
    Uint16  IREFTRIM:5;                               // 15:11 Reference Current Trim 
    Uint16  CONFIG:8;                                 // 23:16 Configuration Bits 
    Uint16  rsvd1:8;                                  // 31:24 Reserved 
};

union ANAREFTRIM4_REG {
    Uint32  all;  
    struct  ANAREFTRIM4_BITS  bit;  
};

struct PMMREFTRIM_BITS {                              // bit descriptions
    Uint16  BGVALTRIM:6;                              // 5:0 Bandgap Value Trim 
    Uint16  BGSLOPETRIM:5;                            // 10:6 Bandgap Slope Trim 
    Uint16  IREFTRIM:5;                               // 15:11 Reference Current Trim 
};

union PMMREFTRIM_REG {
    Uint32  all;  
    struct  PMMREFTRIM_BITS  bit;  
};

struct PMMVREGTRIM_BITS {                             // bit descriptions
    Uint16  VREGTRIM:8;                               // 7:0 Core VDD Voltage Regulator Trim 
    Uint16  VREG2TRIM:6;                              // 13:8 1.8V Voltage Regulator Trim 
    Uint16  rsvd1:2;                                  // 15:14 Reserved 
    Uint16  VSINKTRIM:4;                              // 19:16 Voltage Sink Regulator Trim 
    Uint16  rsvd2:12;                                 // 31:20 Reserved 
};

union PMMVREGTRIM_REG {
    Uint32  all;  
    struct  PMMVREGTRIM_BITS  bit;  
};

struct PMMVMONTRIM_BITS {                             // bit descriptions
    Uint16  VDDIOMONTRIM:4;                           // 3:0 VDDIO 3.3V Monitor Trim 
    Uint16  VDDMONTRIM:4;                             // 7:4 VDD 1.2V Monitor Trim 
    Uint16  VDD2MONTRIM:4;                            // 11:8 VDD2 1.8V Monitor Trim 
    Uint16  VDDOVFMONTRIM:4;                          // 15:12 VDD 1.2V Overvoltage Monitor Trim 
    Uint16  rsvd1:16;                                 // 31:16 Reserved 
};

union PMMVMONTRIM_REG {
    Uint32  all;  
    struct  PMMVMONTRIM_BITS  bit;  
};

struct PMMCSR_BITS {                                  // bit descriptions
    Uint32  PMMCONFIG:28;                             // 27:0 Power Management Module Config Bits 
    Uint16  PMMSTATUS:4;                              // 31:28 Power Management Module Status Bits 
};

union PMMCSR_REG {
    Uint32  all;  
    struct  PMMCSR_BITS  bit;  
};

struct TESTANACTL_BITS {                              // bit descriptions
    Uint16  TESTSEL0:4;                               // 3:0 Test Select 0 
    Uint16  rsvd1:4;                                  // 7:4 Reserved 
    Uint16  TESTSEL1:4;                               // 11:8 Test Select 1 
    Uint16  rsvd2:4;                                  // 15:12 Reserved 
    Uint16  KEY:16;                                   // 31:16 Write Key 
};

union TESTANACTL_REG {
    Uint32  all;  
    struct  TESTANACTL_BITS  bit;  
};

#ifdef CPU1
struct ANALOG_SUBSYS_REGS {
	Uint16                     rsvd1[32];
    union   INTOSC1TRIM_REG    INTOSC1TRIM;           // Internal Oscillator 1 Trim Register 
    union   INTOSC2TRIM_REG    INTOSC2TRIM;           // Internal Oscillator 2 Trim Register
    Uint32                     INTERNALTESTCTL;       // INTERNALTEST Node Control Register
    union   TSNSCTL_REG        TSNSCTL;               // Temperature Sensor Control Register
    union   ANAREFCTL_REG      ANAREFCTL;             // Analog Reference Control Register
    union   VMONCTL_REG        VMONCTL;               // Voltage Monitor Control Register
    union   VMONSTS_REG        VMONSTS;               // Voltage Monitor Status Register
    union   VMONCLR_REG        VMONCLR;               // Voltage Monitor Clear Register
    union   VREGCTL_REG        VREGCTL;               // Voltage Regulator Control Register
    union   LOCK_REG           LOCK;                  // Lock Register
    union   INTOSC1CSR_REG     INTOSC1CSR;            // Internal Oscillator 1 Control and Status Register
    union   INTOSC2CSR_REG     INTOSC2CSR;            // Internal Oscillator 2 Control and Status Register
    Uint16                     TSNSCFG;               // Temperature Sensor Config Register
    union   OSCREFTRIM_REG     OSCREFTRIM;            // Internal Oscillator Reference Trim Register
    union   ANAREFTRIM1_REG    ANAREFTRIM1;           // Analog Reference Trim 1 Register
    union   ANAREFTRIM2_REG    ANAREFTRIM2;           // Analog Reference Trim 2 Register
    union   ANAREFTRIM3_REG    ANAREFTRIM3;           // Analog Reference Trim 3 Register
    union   ANAREFTRIM4_REG    ANAREFTRIM4;           // Analog Reference Trim 4 Register
    union   PMMREFTRIM_REG     PMMREFTRIM;            // Power Management Module Reference Trim Register
    union   PMMVREGTRIM_REG    PMMVREGTRIM;           // Power Management Module VREG Trim Register
    union   PMMVMONTRIM_REG    PMMVMONTRIM;           // Power Management Module VMON Trim Register
    union   PMMCSR_REG         PMMCSR;                // Power Management Module Control and Status Register
    union   TESTANACTL_REG     TESTANACTL;            // Analog Test Control Register
    Uint16 rsvd[30];
};
#endif

//---------------------------------------------------------------------------
// ANALOGSUBSYS External References & Function Declarations:
//

#ifdef CPU1
extern volatile struct ANALOG_SUBSYS_REGS AnalogSubsysRegs;
#endif

#ifdef __cplusplus
}
#endif                                                /* extern "C" */


#endif                                                // end of F2837x_ANALOGSUBSYS_H definition
//===========================================================================
// End of file.
//===========================================================================
