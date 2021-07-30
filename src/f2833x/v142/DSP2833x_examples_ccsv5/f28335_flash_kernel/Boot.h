//###########################################################################
//
// FILE:   Boot.h
//
// TITLE:  Boot ROM Definitions.
//
//###########################################################################
// $TI Release: F2833x/F2823x Header Files and Peripheral Examples V142 $
// $Release Date: November  1, 2016 $
// $Copyright: Copyright (C) 2007-2016 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#ifndef F2833x_BOOT_H
#define F2833X_BOOT_H

#include "DSP2833x_Device.h"     // F2833x Headerfile Include File

//Length of the programming buffer
#define PROG_BUFFER_LENGTH 0x400

//---------------------------------------------------------------------------
// Boot Modes
//
//           GPIO37    GPIO34   TRSTn
//            TDO      CMP2OUT
// Mode EMU    x         x        1      Emulator connected
// Mode 0      0         0        0      Parallel I/O
// Mode 1      0         1        0      SCI
// Mode 2      1         0        0      wait
// Mode 3      1         1        0      "Get Mode"

#define OTP_KEY             0x3D7BFE
#define OTP_BMODE           0x3D7BFF
#define KEY_VAL             0x55AA

#define PARALLEL_BOOT       0x0000
#define SCI_BOOT            0x0001
#define WAIT_BOOT           0x0002
#define GET_BOOT            0x0003

#define SPI_BOOT            0x0004
#define I2C_BOOT            0x0005
#define OTP_BOOT            0x0006
#define RAM_BOOT            0x000A
#define FLASH_BOOT          0x000B

//---------------------------------------------------------------------------
// Fixed boot entry points:
//
#define FLASH_ENTRY_POINT 0x3F7FF6
#define OTP_ENTRY_POINT   0x3D7800
#define RAM_ENTRY_POINT   0x000000

#define DIVSEL_BY_4             0
#define DIVSEL_BY_2             2
#define DIVSEL_BY_1             3

#define ERROR                   1
#define NO_ERROR                0
#define EIGHT_BIT               8
#define SIXTEEN_BIT            16
#define EIGHT_BIT_HEADER   0x08AA
#define SIXTEEN_BIT_HEADER 0x10AA

//---------------------------------------------------------------------------
//
typedef Uint16 (* uint16fptr)();
extern  uint16fptr GetWordData,GetOnlyWordData;
extern  void (*Flash_CallbackPtr) (void);
extern  Uint32 Flash_CPUScaleFactor;
extern  Uint16 EmuKey;
extern  Uint16 EmuBMode;
extern  Uint16 CsmUnlock();
#define Device_cal (void   (*)(void))0x3D7C80
#define Get_mode   (Uint16 (*)(void))0x3D7CC0

//---------------------------------------------------------------------------
// Configured by the boot ROM
//
#define BORTRIM (Uint16 *)0x0986

#endif  // end of F2833X_BOOT_H definition
