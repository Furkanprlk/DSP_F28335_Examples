// TI File $Revision: /main/3 $
// Checkin $Date: December 9, 2009   17:51:15 $
//###########################################################################
//
// FILE:   DSP2802x_DevEmu.h
//
// TITLE:  DSP2802x Device Emulation Register Definitions.
//
//###########################################################################
// $TI Release: 2802x Boot ROM V2.00 $
// $Release Date: December 10, 2009 $
//###########################################################################

#ifndef DSP2802x_DEV_EMU_H
#define DSP2802x_DEV_EMU_H

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// Device Emulation Register Bit Definitions:
//
// Device Configuration Register Bit Definitions
struct DEVICECNF_BITS  {     // bits  description
   Uint16 rsvd1:3;           // 2:0   reserved
   Uint16 VMAPS:1;           // 3     VMAP Status
   Uint16 rsvd2:1;           // 4     reserved
   Uint16 XRSn:1;            // 5     XRSn Signal Status
   Uint16 rsvd3:10;          // 15:6  reserved
   Uint16 rsvd4:3;           // 18:16 reserved
   Uint16 ENPROT:1;          // 19    Enable/Disable pipeline protection
   Uint16 MONPRIV:1;         // 20    MONPRIV enable bit
   Uint16 rsvd5:6;           // 26:21 reserved
   Uint16 TRSTn:1;           // 27    Status of TRSTn signal
   Uint16 rsvd6:4;           // 31:28 reserved
};

union DEVICECNF_REG {
   Uint32                 all;
   struct DEVICECNF_BITS  bit;
};

// PARTID
struct PARTID_BITS   {      // bits  description
   Uint16 PARTNO:8;         // 7:0   Part Number
   Uint16 PARTTYPE:8;       // 15:8  Part Type
};

union PARTID_REG {
   Uint16              all;
   struct PARTID_BITS  bit;
};


struct DEV_EMU_REGS {
   union DEVICECNF_REG DEVICECNF;  // device configuration
   union PARTID_REG    PARTID;     // Part ID
   Uint16              REVID;      // Device ID
   Uint16              rsvd1[2];   // reserved
   Uint16              rsvd2[378];
};

//---------------------------------------------------------------------------
// Device Emulation Register References & Function Declarations:
//
extern volatile struct DEV_EMU_REGS DevEmuRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2802x_DEV_EMU_H definition

//===========================================================================
// End of file.
//===========================================================================
