//###########################################################################
//
// FILE:   F2837x_Sdfm.h
//
// TITLE:  F2837x Device Sdfm Register Definitions.
//
//###########################################################################
// $TI Release:   $
// $Release Date:   $
//###########################################################################

#ifndef F2837x_Sdfm_H
#define F2837x_Sdfm_H
#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// Sdfm Individual Register Bit Definitions:

struct SDIFLG_BITS {     // bit descriptions
    Uint16 IFH1:1;     // 0 High-level Interrupt flag Filter 1
    Uint16 IFL1:1;     // 1 Low-Level Interrupt flag Filter 1
    Uint16 IFH2:1;     // 2 High-level Interrupt flag Filter 2
    Uint16 IFL2:1;     // 3 Low-Level Interrupt flag Filter 2
    Uint16 IFH3:1;     // 4 High-level Interrupt flag Filter 3
    Uint16 IFL3:1;     // 5 Low-Level Interrupt flag Filter 3
    Uint16 IFH4:1;     // 6 High-level Interrupt flag Filter 4
    Uint16 IFL4:1;     // 7 Low-Level Interrupt flag Filter 4
    Uint16 MF1:1;     // 8 Modulator Failure for Filter 1
    Uint16 MF2:1;     // 9 Modulator Failure for Filter 2
    Uint16 MF3:1;     // 10 Modulator Failure for Filter 3
    Uint16 MF4:1;     // 11 Modulator Failure for Filter 4
    Uint16 AF1:1;     // 12 Acknowledge flag for Filter 1
    Uint16 AF2:1;     // 13 Acknowledge flag for Filter 2
    Uint16 AF3:1;     // 14 Acknowledge flag for Filter 3
    Uint16 AF4:1;     // 15 Acknowledge flag for Filter 4
    Uint16 rsvd1:15;     // 30:16 Reserved
    Uint16 MIF:1;     // 31 Master Interrupt Flag
};

union SDIFLG_REG {
    Uint32 all;
    struct SDIFLG_BITS    bit;
};

struct SDIFLGCLR_BITS {     // bit descriptions
    Uint16 IFH1:1;     // 0 High-level Interrupt flag Filter 1
    Uint16 IFL1:1;     // 1 Low-Level Interrupt flag Filter 1
    Uint16 IFH2:1;     // 2 High-level Interrupt flag Filter 2
    Uint16 IFL2:1;     // 3 Low-Level Interrupt flag Filter 2
    Uint16 IFH3:1;     // 4 High-level Interrupt flag Filter 3
    Uint16 IFL3:1;     // 5 Low-Level Interrupt flag Filter 3
    Uint16 IFH4:1;     // 6 High-level Interrupt flag Filter 4
    Uint16 IFL4:1;     // 7 Low-Level Interrupt flag Filter 4
    Uint16 MF1:1;     // 8 Modulator Failure for Filter 1
    Uint16 MF2:1;     // 9 Modulator Failure for Filter 2
    Uint16 MF3:1;     // 10 Modulator Failure for Filter 3
    Uint16 MF4:1;     // 11 Modulator Failure for Filter 4
    Uint16 AF1:1;     // 12 Acknowledge flag for Filter 1
    Uint16 AF2:1;     // 13 Acknowledge flag for Filter 2
    Uint16 AF3:1;     // 14 Acknowledge flag for Filter 3
    Uint16 AF4:1;     // 15 Acknowledge flag for Filter 4
    Uint16 rsvd1:15;     // 30:16 Reserved
    Uint16 MIF:1;     // 31 Master Interrupt Flag
};

union SDIFLGCLR_REG {
    Uint32 all;
    struct SDIFLGCLR_BITS    bit;
};

struct SDCTL_BITS {     // bit descriptions
    Uint16 rsvd1:13;     // 12:0 Reserved
    Uint16 MIE:1;     // 13 Master Interrupt enable
    Uint16 rsvd2:2;     // 15:14 Reserved
};

union SDCTL_REG {
    Uint16 all;
    struct SDCTL_BITS    bit;
};

struct SDCLKDIV_BITS {     // bit descriptions
    Uint16 rsvd1:11;     // 10:0 Reserved
    Uint16 MFE:1;     // 11 Master Filter Enable. 
    Uint16 rsvd2:4;     // 15:12 Reserved
};

union SDCLKDIV_REG {
    Uint16 all;
    struct SDCLKDIV_BITS    bit;
};

struct SDSTATUS_BITS {     // bit descriptions
    Uint16 IO1:1;     // 0 Integrator overflow for filter module 1.
    Uint16 rsvd1:1;     // 1:1 Reserved
    Uint16 IO2:1;     // 2 Integrator overflow for filter module 2.
    Uint16 rsvd2:1;     // 3:3 Reserved
    Uint16 IO3:1;     // 4 Integrator overflow for filter module 3.
    Uint16 rsvd3:1;     // 5:5 Reserved
    Uint16 IO4:1;     // 6 Integrator overflow for filter module 4.
    Uint16 rsvd4:1;     // 7:7 Reserved
    Uint16 MAF1:1;     // 8 Manchester failure status for filter module 1.
    Uint16 MAF2:1;     // 9 Manchester failure status for filter module 2.
    Uint16 MAF3:1;     // 10 Manchester failure status for filter module 3.
    Uint16 MAF4:1;     // 11 Manchester failure status for filter module 4.
    Uint16 MAL1:1;     // 12 Manchester locked status for filter module 1.
    Uint16 MAL2:1;     // 13 Manchester locked status for filter module 2.
    Uint16 MAL3:1;     // 14 Manchester locked status for filter module 3.
    Uint16 MAL4:1;     // 15 Manchester locked status for filter module 4.
};

union SDSTATUS_REG {
    Uint16 all;
    struct SDSTATUS_BITS    bit;
};

struct SDFCTLPARM1_BITS {     // bit descriptions
    Uint16 MOD:2;     // 1:0 Delta-Sigma Modulator mode
    Uint16 rsvd1:3;     // 4:2 Reserved
    Uint16 MS:11;     // 15:5 Manchester Status
};

union SDFCTLPARM1_REG {
    Uint16 all;
    struct SDFCTLPARM1_BITS    bit;
};

struct SDFSFPARM1_BITS {     // bit descriptions
    Uint16 SOSR:8;     // 7:0 SINC Filter Oversample Ratio= SOSR+1
    Uint16 FEN:1;     // 8 Filter Enable 
    Uint16 AE:1;     // 9 Ack Enable
    Uint16 SST:2;     // 11:10 SINC Filter Structure (SincFast/1/2/3)
    Uint16 FILRESEN:1;     // 12 SINC FILTER Reset Enable
    Uint16 rsvd1:3;     // 15:13 Reserved
};

union SDFSFPARM1_REG {
    Uint16 all;
    struct SDFSFPARM1_BITS    bit;
};

struct SDFIPARM1_BITS {     // bit descriptions
    Uint16 IOSR:7;     // 6:0 Integrator Oversample Ratio= IOSR+1
    Uint16 rsvd1:1;     // 7:7 Reserved
    Uint16 IEN:1;     // 8 Integrator enable
    Uint16 DEN:1;     // 9 Demodulation enable (for Resolver apps)
    Uint16 DR:1;     // 10 Data Representation (0/1 = 16/32b 2's complement)
    Uint16 SH:5;     // 15:11 Shift Control (# bits to shift in 16b mode)
};

union SDFIPARM1_REG {
    Uint16 all;
    struct SDFIPARM1_BITS    bit;
};

struct SDFCMPH1_BITS {     // bit descriptions
    Uint16 HLT:15;     // 14:0 Reserved
    Uint16 rsvd1:1;     // 15:15 Reserved
};

union SDFCMPH1_REG {
    Uint16 all;
    struct SDFCMPH1_BITS    bit;
};

struct SDFCMPL1_BITS {     // bit descriptions
    Uint16 LLT:15;     // 14:0 Reserved
    Uint16 rsvd1:1;     // 15:15 Reserved
};

union SDFCMPL1_REG {
    Uint16 all;
    struct SDFCMPL1_BITS    bit;
};

struct SDFCPARM1_BITS {     // bit descriptions
    Uint16 COSR:5;     // 4:0 Comparator Oversample Ratio = COSR + 1
    Uint16 IEH:1;     // 5 High-level interrupt enable
    Uint16 IEL:1;     // 6 Low-level interrupt enable
    Uint16 CS1_CS0:2;     // 8:7 Comparator filter structure (Sincfast/Sinc1/Sinc2/Sinc3
    Uint16 MFIE:1;     // 9 Modulator Failure Interrupt enable
    Uint16 rsvd1:6;     // 15:10 Reserved
};

union SDFCPARM1_REG {
    Uint16 all;
    struct SDFCPARM1_BITS    bit;
};

struct SDFDATA1_REG {     // bit descriptions
    Uint16 DATA16:16;     // 15:0 16-bit Data in 16b mode, Lo-order 16b in 32b mode
    Uint16 DATA32HI:16;     // 31:16 Hi-order 16b in 32b mode
};

union SDFDATA1_GROUP {
    Uint32 all;
    struct SDFDATA1_REG    half;
};

struct SDFCTLPARM2_BITS {     // bit descriptions
    Uint16 MOD:2;     // 1:0 Delta-Sigma Modulator mode
    Uint16 rsvd1:3;     // 4:2 Reserved
    Uint16 MS:11;     // 15:5 Manchester Status
};

union SDFCTLPARM2_REG {
    Uint16 all;
    struct SDFCTLPARM2_BITS    bit;
};

struct SDFSFPARM2_BITS {     // bit descriptions
    Uint16 SOSR:8;     // 7:0 SINC Filter Oversample Ratio= SOSR+1
    Uint16 FEN:1;     // 8 Filter Enable 
    Uint16 AE:1;     // 9 Ack Enable
    Uint16 SST:2;     // 11:10 SINC Filter Structure (SincFast/1/2/3)
    Uint16 FILRESEN:1;     // 12 SINC FILTER Reset Enable
    Uint16 rsvd1:3;     // 15:13 Reserved
};

union SDFSFPARM2_REG {
    Uint16 all;
    struct SDFSFPARM2_BITS    bit;
};

struct SDFIPARM2_BITS {     // bit descriptions
    Uint16 IOSR:7;     // 6:0 Integrator Oversample Ratio= IOSR+1
    Uint16 rsvd1:1;     // 7:7 Reserved
    Uint16 IEN:1;     // 8 Integrator enable
    Uint16 DEN:1;     // 9 Demodulation enable (for Resolver apps)
    Uint16 DR:1;     // 10 Data Representation (0/1 = 16/32b 2's complement)
    Uint16 SH:5;     // 15:11 Shift Control (# bits to shift in 16b mode)
};

union SDFIPARM2_REG {
    Uint16 all;
    struct SDFIPARM2_BITS    bit;
};

struct SDFCMPH2_BITS {     // bit descriptions
    Uint16 HLT:15;     // 14:0 Reserved
    Uint16 rsvd1:1;     // 15:15 Reserved
};

union SDFCMPH2_REG {
    Uint16 all;
    struct SDFCMPH2_BITS    bit;
};

struct SDFCMPL2_BITS {     // bit descriptions
    Uint16 LLT:15;     // 14:0 Reserved
    Uint16 rsvd1:1;     // 15:15 Reserved
};

union SDFCMPL2_REG {
    Uint16 all;
    struct SDFCMPL2_BITS    bit;
};

struct SDFCPARM2_BITS {     // bit descriptions
    Uint16 COSR:5;     // 4:0 Comparator Oversample Ratio = COSR + 1
    Uint16 IEH:1;     // 5 High-level interrupt enable
    Uint16 IEL:1;     // 6 Low-level interrupt enable
    Uint16 CS1_CS0:2;     // 8:7 Comparator filter structure (Sincfast/Sinc1/Sinc2/Sinc3
    Uint16 MFIE:1;     // 9 Modulator Failure Interrupt enable
    Uint16 rsvd1:6;     // 15:10 Reserved
};

union SDFCPARM2_REG {
    Uint16 all;
    struct SDFCPARM2_BITS    bit;
};

struct SDFDATA2_REG {     // bit descriptions
    Uint16 DATA16:16;     // 15:0 16-bit Data in 16b mode, Lo-order 16b in 32b mode
    Uint16 DATA32HI:16;     // 31:16 Hi-order 16b in 32b mode
};

union SDFDATA2_GROUP {
    Uint32 all;
    struct SDFDATA2_REG    half;
};

struct SDFCTLPARM3_BITS {     // bit descriptions
    Uint16 MOD:2;     // 1:0 Delta-Sigma Modulator mode
    Uint16 rsvd1:3;     // 4:2 Reserved
    Uint16 MS:11;     // 15:5 Manchester Status
};

union SDFCTLPARM3_REG {
    Uint16 all;
    struct SDFCTLPARM3_BITS    bit;
};

struct SDFSFPARM3_BITS {     // bit descriptions
    Uint16 SOSR:8;     // 7:0 SINC Filter Oversample Ratio= SOSR+1
    Uint16 FEN:1;     // 8 Filter Enable 
    Uint16 AE:1;     // 9 Ack Enable
    Uint16 SST:2;     // 11:10 SINC Filter Structure (SincFast/1/2/3)
    Uint16 FILRESEN:1;     // 12 SINC FILTER Reset Enable
    Uint16 rsvd1:3;     // 15:13 Reserved
};

union SDFSFPARM3_REG {
    Uint16 all;
    struct SDFSFPARM3_BITS    bit;
};

struct SDFIPARM3_BITS {     // bit descriptions
    Uint16 IOSR:7;     // 6:0 Integrator Oversample Ratio= IOSR+1
    Uint16 rsvd1:1;     // 7:7 Reserved
    Uint16 IEN:1;     // 8 Integrator enable
    Uint16 DEN:1;     // 9 Demodulation enable (for Resolver apps)
    Uint16 DR:1;     // 10 Data Representation (0/1 = 16/32b 2's complement)
    Uint16 SH:5;     // 15:11 Shift Control (# bits to shift in 16b mode)
};

union SDFIPARM3_REG {
    Uint16 all;
    struct SDFIPARM3_BITS    bit;
};

struct SDFCMPH3_BITS {     // bit descriptions
    Uint16 HLT:15;     // 14:0 Reserved
    Uint16 rsvd1:1;     // 15:15 Reserved
};

union SDFCMPH3_REG {
    Uint16 all;
    struct SDFCMPH3_BITS    bit;
};

struct SDFCMPL3_BITS {     // bit descriptions
    Uint16 LLT:15;     // 14:0 Reserved
    Uint16 rsvd1:1;     // 15:15 Reserved
};

union SDFCMPL3_REG {
    Uint16 all;
    struct SDFCMPL3_BITS    bit;
};

struct SDFCPARM3_BITS {     // bit descriptions
    Uint16 COSR:5;     // 4:0 Comparator Oversample Ratio = COSR + 1
    Uint16 IEH:1;     // 5 High-level interrupt enable
    Uint16 IEL:1;     // 6 Low-level interrupt enable
    Uint16 CS1_CS0:2;     // 8:7 Comparator filter structure (Sincfast/Sinc1/Sinc2/Sinc3
    Uint16 MFIE:1;     // 9 Modulator Failure Interrupt enable
    Uint16 rsvd1:6;     // 15:10 Reserved
};

union SDFCPARM3_REG {
    Uint16 all;
    struct SDFCPARM3_BITS    bit;
};

struct SDFDATA3_REG {     // bit descriptions
    Uint16 DATA16:16;     // 15:0 16-bit Data in 16b mode, Lo-order 16b in 32b mode
    Uint16 DATA32HI:16;     // 31:16 Hi-order 16b in 32b mode
};

union SDFDATA3_GROUP {
    Uint32 all;
    struct SDFDATA3_REG    half;
};

struct SDFCTLPARM4_BITS {     // bit descriptions
    Uint16 MOD:2;     // 1:0 Delta-Sigma Modulator mode
    Uint16 rsvd1:3;     // 4:2 Reserved
    Uint16 MS:11;     // 15:5 Manchester Status
};

union SDFCTLPARM4_REG {
    Uint16 all;
    struct SDFCTLPARM4_BITS    bit;
};

struct SDFSFPARM4_BITS {     // bit descriptions
    Uint16 SOSR:8;     // 7:0 SINC Filter Oversample Ratio= SOSR+1
    Uint16 FEN:1;     // 8 Filter Enable 
    Uint16 AE:1;     // 9 Ack Enable
    Uint16 SST:2;     // 11:10 SINC Filter Structure (SincFast/1/2/3)
    Uint16 FILRESEN:1;     // 12 SINC FILTER Reset Enable
    Uint16 rsvd1:3;     // 15:13 Reserved
};

union SDFSFPARM4_REG {
    Uint16 all;
    struct SDFSFPARM4_BITS    bit;
};

struct SDFIPARM4_BITS {     // bit descriptions
    Uint16 IOSR:7;     // 6:0 Integrator Oversample Ratio= IOSR+1
    Uint16 rsvd1:1;     // 7:7 Reserved
    Uint16 IEN:1;     // 8 Integrator enable
    Uint16 DEN:1;     // 9 Demodulation enable (for Resolver apps)
    Uint16 DR:1;     // 10 Data Representation (0/1 = 16/32b 2's complement)
    Uint16 SH:5;     // 15:11 Shift Control (# bits to shift in 16b mode)
};

union SDFIPARM4_REG {
    Uint16 all;
    struct SDFIPARM4_BITS    bit;
};

struct SDFCMPH4_BITS {     // bit descriptions
    Uint16 HLT:15;     // 14:0 Reserved
    Uint16 rsvd1:1;     // 15:15 Reserved
};

union SDFCMPH4_REG {
    Uint16 all;
    struct SDFCMPH4_BITS    bit;
};

struct SDFCMPL4_BITS {     // bit descriptions
    Uint16 LLT:15;     // 14:0 Reserved
    Uint16 rsvd1:1;     // 15:15 Reserved
};

union SDFCMPL4_REG {
    Uint16 all;
    struct SDFCMPL4_BITS    bit;
};

struct SDFCPARM4_BITS {     // bit descriptions
    Uint16 COSR:5;     // 4:0 Comparator Oversample Ratio = COSR + 1
    Uint16 IEH:1;     // 5 High-level interrupt enable
    Uint16 IEL:1;     // 6 Low-level interrupt enable
    Uint16 CS1_CS0:2;     // 8:7 Comparator filter structure (Sincfast/Sinc1/Sinc2/Sinc3
    Uint16 MFIE:1;     // 9 Modulator Failure Interrupt enable
    Uint16 rsvd1:6;     // 15:10 Reserved
};

union SDFCPARM4_REG {
    Uint16 all;
    struct SDFCPARM4_BITS    bit;
};

struct SDFDATA4_REG {     // bit descriptions
    Uint16 DATA16:16;     // 15:0 16-bit Data in 16b mode, Lo-order 16b in 32b mode
    Uint16 DATA32HI:16;     // 31:16 Hi-order 16b in 32b mode
};

union SDFDATA4_GROUP {
    Uint32 all;
    struct SDFDATA4_REG    half;
};

struct SD_REGS {
    union SDIFLG_REG SDIFLG;     // Interrupt Flag Register
    union SDIFLGCLR_REG SDIFLGCLR;     // Interrupt Flag Clear Register
    union SDCTL_REG SDCTL;     // SD Control Register
    Uint16 rsvd1;     // Reserved
    union SDCLKDIV_REG SDCLKDIV;     // SD Clock Divider Register
    union SDSTATUS_REG SDSTATUS;     // SD Status Register
    Uint16 rsvd2[8];     // Reserved
    union SDFCTLPARM1_REG SDFCTLPARM1;     // Control Parameter Register for Ch1
    union SDFSFPARM1_REG SDFSFPARM1;     // Sinc Filter Parameter Register for Ch1
    union SDFIPARM1_REG SDFIPARM1;     // Integrator Parameter Register for Ch1
    union SDFCMPH1_REG SDFCMPH1;     // High-level Threshold Register for Ch1
    union SDFCMPL1_REG SDFCMPL1;     // Low-level Threshold Register for Ch1
    union SDFCPARM1_REG SDFCPARM1;     // Comparator Parameter Register for Ch1
    union SDFDATA1_GROUP SDFDATA1;     // Filter Data Register (16 or 32bit) for Ch1
    Uint16 rsvd3[8];     // Reserved
    union SDFCTLPARM2_REG SDFCTLPARM2;     // Control Parameter Register for Ch2
    union SDFSFPARM2_REG SDFSFPARM2;     // Sinc Filter Parameter Register for Ch2
    union SDFIPARM2_REG SDFIPARM2;     // Integrator Parameter Register for Ch2
    union SDFCMPH2_REG SDFCMPH2;     // High-level Threshold Register for Ch2
    union SDFCMPL2_REG SDFCMPL2;     // Low-level Threshold Register for Ch2
    union SDFCPARM2_REG SDFCPARM2;     // Comparator Parameter Register for Ch2
    union SDFDATA2_GROUP SDFDATA2;     // Filter Data Register (16 or 32bit) for Ch2
    Uint16 rsvd4[8];     // Reserved
    union SDFCTLPARM3_REG SDFCTLPARM3;     // Control Parameter Register for Ch3
    union SDFSFPARM3_REG SDFSFPARM3;     // Sinc Filter Parameter Register for Ch3
    union SDFIPARM3_REG SDFIPARM3;     // Integrator Parameter Register for Ch3
    union SDFCMPH3_REG SDFCMPH3;     // High-level Threshold Register for Ch3
    union SDFCMPL3_REG SDFCMPL3;     // Low-level Threshold Register for Ch3
    union SDFCPARM3_REG SDFCPARM3;     // Comparator Parameter Register for Ch3
    union SDFDATA3_GROUP SDFDATA3;     // Filter Data Register (16 or 32bit) for Ch3
    Uint16 rsvd5[8];     // Reserved
    union SDFCTLPARM4_REG SDFCTLPARM4;     // Control Parameter Register for Ch4
    union SDFSFPARM4_REG SDFSFPARM4;     // Sinc Filter Parameter Register for Ch4
    union SDFIPARM4_REG SDFIPARM4;     // Integrator Parameter Register for Ch4
    union SDFCMPH4_REG SDFCMPH4;     // High-level Threshold Register for Ch4
    union SDFCMPL4_REG SDFCMPL4;     // Low-level Threshold Register for Ch4
    union SDFCPARM4_REG SDFCPARM4;     // Comparator Parameter Register for Ch4
    union SDFDATA4_GROUP SDFDATA4;     // Filter Data Register (16 or 32bit) for Ch4
    Uint16 rsvd6[56];     // Reserved
};

//---------------------------------------------------------------------------
// Sdfm External References & Function Declarations:
//

extern volatile struct SD_REGS Sd1Regs;
extern volatile struct SD_REGS Sd2Regs;

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif  // end of F2837x_SDFM_H definition
//===========================================================================
// End of file.
//===========================================================================

