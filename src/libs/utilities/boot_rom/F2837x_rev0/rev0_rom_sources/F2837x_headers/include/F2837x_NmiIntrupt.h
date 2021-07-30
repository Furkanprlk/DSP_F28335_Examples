//###########################################################################
//
// FILE:   F2837x_NmiIntrupt.h
//
// TITLE:  F2837x Device NmiIntrupt Register Definitions.
//
//###########################################################################
// $TI Release:   $
// $Release Date:   $
//###########################################################################

#ifndef F2837x_NmiIntrupt_H
#define F2837x_NmiIntrupt_H
#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// NmiIntrupt Individual Register Bit Definitions:

struct NMICFG_BITS {                                  // bit descriptions
    Uint16  NMIE:1;                                   // 0 Global NMI Enable 
    Uint16  rsvd1:15;                                 // 15:1 Reserved 
};

union NMICFG_REG {
    Uint16  all;  
    struct  NMICFG_BITS  bit;  
};

struct NMIFLG_BITS {                                  // bit descriptions
    Uint16  NMIINT:1;                                 // 0 NMI Interrupt Flag 
    Uint16  CLOCKFAIL:1;                              // 1 Clock Fail Interrupt Flag 
    Uint16  RAMUNCERR:1;                              // 2 RAM Uncorrectable Error NMI Flag 
    Uint16  FLUNCERR:1;                               // 3 Flash Uncorrectable Error NMI Flag 
    Uint16  CPU1HWBISTERR:1;                          // 4 HW BIST Error NMI Flag 
    Uint16  CPU2HWBISTERR:1;                          // 5 HW BIST Error NMI Flag 
    Uint16  PIEVECTERR:1;                             // 6 PIE Vector Fetch Error Flag 
    Uint16  SYSDBGNMI:1;                              // 7 System Debug Module NMI Flag 
    Uint16  RLNMI:1;                                  // 8 Reconfigurable Logic NMI Flag 
    Uint16  CPU2WDRSn:1;                              // 9 CPU2 WDRSn Reset Indication Flag 
    Uint16  CPU2NMIWDRSn:1;                           // 10 CPU2 NMIWDRSn Reset Indication Flag 
    Uint16  OVF:1;                                    // 11 Over Voltage Fault Indication Flag 
    Uint16  rsvd1:4;                                  // 15:12 Reserved 
};

union NMIFLG_REG {
    Uint16  all;  
    struct  NMIFLG_BITS  bit;  
};

struct NMIFLGCLR_BITS {                               // bit descriptions
    Uint16  NMIINT:1;                                 // 0 NMIINT Flag Clear 
    Uint16  CLOCKFAIL:1;                              // 1 CLOCKFAIL Flag Clear 
    Uint16  RAMUNCERR:1;                              // 2 RAMUNCERR Flag Clear 
    Uint16  FLUNCERR:1;                               // 3 FLUNCERR Flag Clear 
    Uint16  CPU1HWBISTERR:1;                          // 4 CPU1HWBISTERR Flag Clear 
    Uint16  CPU2HWBISTERR:1;                          // 5 CPU2HWBISTERR Flag Clear 
    Uint16  PIEVECTERR:1;                             // 6 PIEVECTERR Flag Clear 
    Uint16  SYSDBGNMI:1;                              // 7 SYSDBGNMI Flag Clear 
    Uint16  RLNMI:1;                                  // 8 RLNMI Flag Clear 
    Uint16  CPU2WDRSn:1;                              // 9 CPU2WDRSn Flag Clear 
    Uint16  CPU2NMIWDRSn:1;                           // 10 CPU2NMIWDRSn Flag Clear 
    Uint16  OVF:1;                                    // 11 OVF Flag Clear 
    Uint16  rsvd1:4;                                  // 15:12 Reserved 
};

union NMIFLGCLR_REG {
    Uint16  all;  
    struct  NMIFLGCLR_BITS  bit;  
};

struct NMIFLGFRC_BITS {                               // bit descriptions
    Uint16  rsvd1:1;                                  // 0:0 Reserved 
    Uint16  CLOCKFAIL:1;                              // 1 CLOCKFAIL Flag Force 
    Uint16  RAMUNCERR:1;                              // 2 RAMUNCERR Flag Force 
    Uint16  FLUNCERR:1;                               // 3 FLUNCERR Flag Force 
    Uint16  CPU1HWBISTERR:1;                          // 4 CPU1HWBISTERR Flag Force 
    Uint16  CPU2HWBISTERR:1;                          // 5 CPU2HWBISTERR Flag Force 
    Uint16  PIEVECTERR:1;                             // 6 PIEVECTERR Flag Force 
    Uint16  SYSDBGNMI:1;                              // 7 SYSDBGNMI Flag Force 
    Uint16  RLNMI:1;                                  // 8 RLNMI Flag Force 
    Uint16  CPU2WDRSn:1;                              // 9 CPU2WDRSn Flag Force 
    Uint16  CPU2NMIWDRSn:1;                           // 10 CPU2NMIWDRSn Flag Force 
    Uint16  OVF:1;                                    // 11 OVF Flag Force 
    Uint16  rsvd2:4;                                  // 15:12 Reserved 
};

union NMIFLGFRC_REG {
    Uint16  all;  
    struct  NMIFLGFRC_BITS  bit;  
};

struct NMISHDFLG_BITS {                               // bit descriptions
    Uint16  rsvd1:1;                                  // 0:0 Reserved 
    Uint16  CLOCKFAIL:1;                              // 1 Shadow CLOCKFAIL Flag 
    Uint16  RAMUNCERR:1;                              // 2 Shadow RAMUNCERR Flag 
    Uint16  FLUNCERR:1;                               // 3 Shadow FLUNCERR Flag 
    Uint16  CPU1HWBISTERR:1;                          // 4 Shadow CPU1HWBISTERR Flag 
    Uint16  CPU2HWBISTERR:1;                          // 5 Shadow CPU2HWBISTERR Flag 
    Uint16  PIEVECTERR:1;                             // 6 Shadow PIEVECTERR Flag 
    Uint16  SYSDBGNMI:1;                              // 7 Shadow SYSDBGNMI Flag 
    Uint16  RLNMI:1;                                  // 8 Shadow RLNMI Flag 
    Uint16  CPU2WDRSn:1;                              // 9 Shadow CPU2WDRSn Flag 
    Uint16  CPU2NMIWDRSn:1;                           // 10 Shadow CPU2NMIWDRSn Flag 
    Uint16  OVF:1;                                    // 11 Shadow OVF Flag 
    Uint16  rsvd2:4;                                  // 15:12 Reserved 
};

union NMISHDFLG_REG {
    Uint16  all;  
    struct  NMISHDFLG_BITS  bit;  
};

struct NMI_INTRUPT_REGS {
    union   NMICFG_REG       NMICFG;                  // NMI Configuration Register 
    union   NMIFLG_REG       NMIFLG;                  // NMI Flag Register (XRSn Clear) 
    union   NMIFLGCLR_REG    NMIFLGCLR;               // NMI Flag Clear Register 
    union   NMIFLGFRC_REG    NMIFLGFRC;               // NMI Flag Force Register 
    Uint16                   NMIWDCNT;                // NMI Watchdog Counter Register 
    Uint16                   NMIWDPRD;                // NMI Watchdog Period Register 
    union   NMISHDFLG_REG    NMISHDFLG;               // NMI Shadow Flag Register 
};

//---------------------------------------------------------------------------
// NmiIntrupt External References & Function Declarations:
//

extern volatile struct NMI_INTRUPT_REGS NmiIntruptRegs;

#ifdef __cplusplus
}
#endif                                                /* extern "C" */


#endif                                                // end of F2837x_NMIINTRUPT_H definition
//===========================================================================
// End of file.
//===========================================================================
