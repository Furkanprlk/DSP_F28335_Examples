//###########################################################################
//
// FILE:   F2837x_Dac.h
//
// TITLE:  F2837x Device Dac Register Definitions.
//
//###########################################################################
// $TI Release:   $
// $Release Date:   $
//###########################################################################

#ifndef F2837x_Dac_H
#define F2837x_Dac_H
#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// Dac Individual Register Bit Definitions:

struct DACREV_BITS {                                  // bit descriptions
    Uint16  REV:8;                                    // 7:0 DAC Revision Register 
    Uint16  rsvd1:8;                                  // 15:8 Reserved 
};

union DACREV_REG {
    Uint16  all;  
    struct  DACREV_BITS  bit;  
};

struct DACCTL_BITS {                                  // bit descriptions
    Uint16  DACREFSEL:1;                              // 0 DAC Reference Select 
    Uint16  MODE:1;                                   // 1 DAC Mode Select 
    Uint16  LOADMODE:1;                               // 2 DACVALA Load Mode 
    Uint16  rsvd1:1;                                  // 3 Reserved 
    Uint16  SYNCSEL:4;                                // 7:4 DAC PWMSYNC Select 
    Uint16  rsvd2:8;                                  // 15:8 Reserved 
};

union DACCTL_REG {
    Uint16  all;  
    struct  DACCTL_BITS  bit;  
};

struct DACVALA_BITS {                                 // bit descriptions
    Uint16  DACVALA:12;                               // 11:0 DAC Active Output Code 
    Uint16  rsvd1:4;                                  // 15:12 Reserved 
};

union DACVALA_REG {
    Uint16  all;  
    struct  DACVALA_BITS  bit;  
};

struct DACVALS_BITS {                                 // bit descriptions
    Uint16  DACVALS:12;                               // 11:0 DAC Shadow Output Code 
    Uint16  rsvd1:4;                                  // 15:12 Reserved 
};

union DACVALS_REG {
    Uint16  all;  
    struct  DACVALS_BITS  bit;  
};

struct DACOUTEN_BITS {                                // bit descriptions
    Uint16  DACOUTEN:1;                               // 0 DAC Output Code 
    Uint16  rsvd1:15;                                 // 15:1 Reserved 
};

union DACOUTEN_REG {
    Uint16  all;  
    struct  DACOUTEN_BITS  bit;  
};

struct DACLOCK_BITS {                                 // bit descriptions
    Uint16  DACCTLLOCK:1;                             // 0 DAC Control Register Lock 
    Uint16  DACVALLOCK:1;                             // 1 DAC Value Register Lock 
    Uint16  DACOUTENLOCK:1;                           // 2 DAC Output Enable Register Lock 
    Uint16  rsvd1:13;                                 // 15:3 Reserved 
};

union DACLOCK_REG {
    Uint16  all;  
    struct  DACLOCK_BITS  bit;  
};

struct DACTRIM_BITS {                                 // bit descriptions
    Uint16  OFFSET_TRIM:8;                            // 7:0 DAC Offset Trim 
    Uint16  GAIN_TRIM:4;                              // 11:8 DAC Gain Trim 
    Uint16  rsvd1:4;                                  // 15:12 Reserved 
};

union DACTRIM_REG {
    Uint16  all;  
    struct  DACTRIM_BITS  bit;  
};

struct DACCONFIG_BITS {                               // bit descriptions
    Uint16  CONFIG:16;                                // 15:0 DAC Configuration 
};

union DACCONFIG_REG {
    Uint16  all;  
    struct  DACCONFIG_BITS  bit;  
};

struct DAC_REGS {
    union   DACREV_REG       DACREV;                  // DAC Revision Register 
    union   DACCTL_REG       DACCTL;                  // DAC Control Register 
    union   DACVALA_REG      DACVALA;                 // DAC Value Register - Active 
    union   DACVALS_REG      DACVALS;                 // DAC Value Register - Shadow 
    union   DACOUTEN_REG     DACOUTEN;                // DAC Output Enable Register 
    union   DACLOCK_REG      DACLOCK;                 // DAC Lock Register 
    union   DACTRIM_REG      DACTRIM;                 // DAC Trim Register 
    union   DACCONFIG_REG    DACCONFIG;               // DAC Configuration Register 
};

//---------------------------------------------------------------------------
// Dac External References & Function Declarations:
//

extern volatile struct DAC_REGS Dac1Regs;
extern volatile struct DAC_REGS Dac2Regs;
extern volatile struct DAC_REGS Dac3Regs;

#ifdef __cplusplus
}
#endif                                                /* extern "C" */


#endif                                                // end of F2837x_DAC_H definition
//===========================================================================
// End of file.
//===========================================================================
