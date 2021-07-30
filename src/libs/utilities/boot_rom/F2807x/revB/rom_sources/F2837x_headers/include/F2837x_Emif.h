//###########################################################################
//
// FILE:   F2837x_Emif.h
//
// TITLE:  F2837x Device Emif Register Definitions.
//
//###########################################################################
// $TI Release:   $
// $Release Date:   $
//###########################################################################

#ifndef F2837x_Emif_H
#define F2837x_Emif_H
#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// Emif Individual Register Bit Definitions:

struct RCSR_BITS {                                                 // bit descriptions
    Uint16  MINOR_REVISION:8;                                      // 7:0 Minor Revision. 
    Uint16  MAJOR_REVISION:8;                                      // 15:8 Major Revision. 
    Uint16  MODULE_ID:14;                                          // 29:16 EMIF module ID. 
    Uint16  FR:1;                                                  // 30 EMIF is running in full rate or half rate. 
    Uint16  BE:1;                                                  // 31 EMIF endian mode. 
};

union RCSR_REG {
    Uint32  all;  
    struct  RCSR_BITS  bit;  
};

struct ASYNC_WCCR_BITS {                                           // bit descriptions
    Uint16  MAX_EXT_WAIT:8;                                        // 7:0 Maximum Extended Wait cycles. 
    Uint16  rsvd1:8;                                               // 15:8 Reserved 
    Uint16  CS2_WAIT:2;                                            // 17:16 Maps the wait signal for chip select 2. 
    Uint16  CS3_WAIT:2;                                            // 19:18 Maps the wait signal for chip select 3. 
    Uint16  CS4_WAIT:2;                                            // 21:20 Maps the wait signal for chip select 4. 
    Uint16  CS5_WAIT:2;                                            // 23:22 Maps the wait signal for chip select 5. 
    Uint16  rsvd2:4;                                               // 27:24 Reserved 
    Uint16  WP0:1;                                                 // 28 Wait Polarity for pad_wait_i[0]. 
    Uint16  WP1:1;                                                 // 29 Wait Polarity for pad_wait_i[1]. 
    Uint16  WP2:1;                                                 // 30 Wait Polarity for pad_wait_i[2]. 
    Uint16  WP3:1;                                                 // 31 Wait Polarity for pad_wait_i[3]. 
};

union ASYNC_WCCR_REG {
    Uint32  all;  
    struct  ASYNC_WCCR_BITS  bit;  
};

struct SDRAM_CR_BITS {                                             // bit descriptions
    Uint16  PAGESIGE:3;                                            // 2:0 Page Size. 
    Uint16  EBANK:1;                                               // 3 External chip select setup. 
    Uint16  IBANK:3;                                               // 6:4 Internal Bank setup of SDRAM devices. 
    Uint16  rsvd1:1;                                               // 7:7 Reserved 
    Uint16  BIT_11_9_LOCK:1;                                       // 8 Bits 11 to 9 can only be written if this bit is set to 1. 
    Uint16  CL:3;                                                  // 11:9 CAS Latency. 
    Uint16  BIT_13_LOCK:1;                                         // 12 Bits 13 can only be written if this bit is set to 1. 
    Uint16  DISABLE_DDR_DLL:1;                                     // 13 Disable DLL select for DDR1 SDRAM. 
    Uint16  NM:1;                                                  // 14 Narrow Mode. 
    Uint16  rsvd2:1;                                               // 15:15 Reserved 
    Uint16  BIT_25_17_LOCK:1;                                      // 16 Bits 25 to 17 can only be written if this bit is set to 1. 
    Uint16  SDRAM_DRIVE:2;                                         // 18:17 SDRAM drive strength. 
    Uint16  IBANK_POS:1;                                           // 19 Internal bank position. 
    Uint16  ROWSIZE:3;                                             // 22:20 Row Size. 
    Uint16  PASR:3;                                                // 25:23 Partial Array Self Refresh. 
    Uint16  rsvd3:3;                                               // 28:26 Reserved 
    Uint16  PDWR:1;                                                // 29 Perform refreshes during Power Down. 
    Uint16  PD:1;                                                  // 30 Power Down. 
    Uint16  SR:1;                                                  // 31 Self Refresh. 
};

union SDRAM_CR_REG {
    Uint32  all;  
    struct  SDRAM_CR_BITS  bit;  
};

struct SDRAM_RCR_BITS {                                            // bit descriptions
    Uint16  REFRESH_RATE:13;                                       // 12:0 Refresh Rate. 
    Uint16  rsvd1:3;                                               // 15:13 Reserved 
    Uint16  DDR_REF_THRESH:3;                                      // 18:16 DDR Refresh Threshold. 
    Uint16  rsvd2:13;                                              // 31:19 Reserved 
};

union SDRAM_RCR_REG {
    Uint32  all;  
    struct  SDRAM_RCR_BITS  bit;  
};

struct ASYNC_CS2_CR_BITS {                                         // bit descriptions
    Uint16  ASIZE:2;                                               // 1:0 Asynchronous Memory Size. 
    Uint16  TA:2;                                                  // 3:2 Turn Around cycles. 
    Uint16  R_HOLD:3;                                              // 6:4 Read Strobe Hold cycles. 
    Uint16  R_STROBE:6;                                            // 12:7 Read Strobe Duration cycles. 
    Uint32  R_SETUP:4;                                             // 16:13 Read Strobe Setup cycles. 
    Uint16  W_HOLD:3;                                              // 19:17 Write Strobe Hold cycles. 
    Uint16  W_STROBE:6;                                            // 25:20 Write Strobe Duration cycles. 
    Uint16  W_SETUP:4;                                             // 29:26 Write Strobe Setup cycles. 
    Uint16  EW:1;                                                  // 30 Extend Wait mode. 
    Uint16  SS:1;                                                  // 31 Select Strobe mode. 
};

union ASYNC_CS2_CR_REG {
    Uint32  all;  
    struct  ASYNC_CS2_CR_BITS  bit;  
};

struct ASYNC_CS3_CR_BITS {                                         // bit descriptions
    Uint16  ASIZE:2;                                               // 1:0 Asynchronous Memory Size. 
    Uint16  TA:2;                                                  // 3:2 Turn Around cycles. 
    Uint16  R_HOLD:3;                                              // 6:4 Read Strobe Hold cycles. 
    Uint16  R_STROBE:6;                                            // 12:7 Read Strobe Duration cycles. 
    Uint32  R_SETUP:4;                                             // 16:13 Read Strobe Setup cycles. 
    Uint16  W_HOLD:3;                                              // 19:17 Write Strobe Hold cycles. 
    Uint16  W_STROBE:6;                                            // 25:20 Write Strobe Duration cycles. 
    Uint16  W_SETUP:4;                                             // 29:26 Write Strobe Setup cycles. 
    Uint16  EW:1;                                                  // 30 Extend Wait mode. 
    Uint16  SS:1;                                                  // 31 Select Strobe mode. 
};

union ASYNC_CS3_CR_REG {
    Uint32  all;  
    struct  ASYNC_CS3_CR_BITS  bit;  
};

struct ASYNC_CS4_CR_BITS {                                         // bit descriptions
    Uint16  ASIZE:2;                                               // 1:0 Asynchronous Memory Size. 
    Uint16  TA:2;                                                  // 3:2 Turn Around cycles. 
    Uint16  R_HOLD:3;                                              // 6:4 Read Strobe Hold cycles. 
    Uint16  R_STROBE:6;                                            // 12:7 Read Strobe Duration cycles. 
    Uint32  R_SETUP:4;                                             // 16:13 Read Strobe Setup cycles. 
    Uint16  W_HOLD:3;                                              // 19:17 Write Strobe Hold cycles. 
    Uint16  W_STROBE:6;                                            // 25:20 Write Strobe Duration cycles. 
    Uint16  W_SETUP:4;                                             // 29:26 Write Strobe Setup cycles. 
    Uint16  EW:1;                                                  // 30 Extend Wait mode. 
    Uint16  SS:1;                                                  // 31 Select Strobe mode. 
};

union ASYNC_CS4_CR_REG {
    Uint32  all;  
    struct  ASYNC_CS4_CR_BITS  bit;  
};

struct ASYNC_CS5_CR_BITS {                                         // bit descriptions
    Uint16  ASIZE:2;                                               // 1:0 Asynchronous Memory Size. 
    Uint16  TA:2;                                                  // 3:2 Turn Around cycles. 
    Uint16  R_HOLD:3;                                              // 6:4 Read Strobe Hold cycles. 
    Uint16  R_STROBE:6;                                            // 12:7 Read Strobe Duration cycles. 
    Uint32  R_SETUP:4;                                             // 16:13 Read Strobe Setup cycles. 
    Uint16  W_HOLD:3;                                              // 19:17 Write Strobe Hold cycles. 
    Uint16  W_STROBE:6;                                            // 25:20 Write Strobe Duration cycles. 
    Uint16  W_SETUP:4;                                             // 29:26 Write Strobe Setup cycles. 
    Uint16  EW:1;                                                  // 30 Extend Wait mode. 
    Uint16  SS:1;                                                  // 31 Select Strobe mode. 
};

union ASYNC_CS5_CR_REG {
    Uint32  all;  
    struct  ASYNC_CS5_CR_BITS  bit;  
};

struct SDRAM_TR_BITS {                                             // bit descriptions
    Uint16  rsvd1:4;                                               // 3:0 Reserved 
    Uint16  T_RRD:3;                                               // 6:4 Activate to Activate timing for different bank. 
    Uint16  rsvd2:1;                                               // 7:7 Reserved 
    Uint16  T_RC:4;                                                // 11:8 Activate to Activate timing . 
    Uint16  T_RAS:4;                                               // 15:12 Activate to Precharge timing. 
    Uint16  T_WR:3;                                                // 18:16 Last Write to Precharge timing. 
    Uint16  rsvd3:1;                                               // 19:19 Reserved 
    Uint16  T_RCD:3;                                               // 22:20 Activate to Read/Write timing. 
    Uint16  rsvd4:1;                                               // 23:23 Reserved 
    Uint16  T_RP:3;                                                // 26:24 Precharge to Activate/Refresh timing. 
    Uint16  T_RFC:5;                                               // 31:27 Refresh/Load Mode to Refresh/Activate timing 
};

union SDRAM_TR_REG {
    Uint32  all;  
    struct  SDRAM_TR_BITS  bit;  
};

struct SDRAM_SR_BITS {                                             // bit descriptions
    Uint16  DDR:1;                                                 // 0 Double Data Rate. 
    Uint16  MSDRAM:1;                                              // 1 Mobile SDR SDRAM mode. 
    Uint16  rsvd1:1;                                               // 2:2 Reserved 
    Uint16  PHY_DLL_READY:1;                                       // 3 DDR PHY Ready. 
    Uint16  rsvd2:12;                                              // 15:4 Reserved 
    Uint16  rsvd3:16;                                              // 31:16 Reserved 
};

union SDRAM_SR_REG {
    Uint32  all;  
    struct  SDRAM_SR_BITS  bit;  
};

struct SDR_EXT_TMNG_BITS {                                         // bit descriptions
    Uint16  T_XS:5;                                                // 4:0 Self Refresh exit to new command timing. 
    Uint16  rsvd1:11;                                              // 15:5 Reserved 
    Uint16  rsvd2:16;                                              // 31:16 Reserved 
};

union SDR_EXT_TMNG_REG {
    Uint32  all;  
    struct  SDR_EXT_TMNG_BITS  bit;  
};

struct INT_RAW_BITS {                                              // bit descriptions
    Uint16  AT:1;                                                  // 0 Asynchronous Timeout. 
    Uint16  LT:1;                                                  // 1 Line Trap. 
    Uint16  WR:4;                                                  // 5:2 Wait Rise. 
    Uint16  rsvd1:10;                                              // 15:6 Reserved 
    Uint16  rsvd2:16;                                              // 31:16 Reserved 
};

union INT_RAW_REG {
    Uint32  all;  
    struct  INT_RAW_BITS  bit;  
};

struct INT_MSK_BITS {                                              // bit descriptions
    Uint16  AT_MASKED:1;                                           // 0 Asynchronous Timeout. 
    Uint16  LT_MASKED:1;                                           // 1 Line Trap. 
    Uint16  WR_MASKED:4;                                           // 5:2 Wait Rise. 
    Uint16  rsvd1:10;                                              // 15:6 Reserved 
    Uint16  rsvd2:16;                                              // 31:16 Reserved 
};

union INT_MSK_REG {
    Uint32  all;  
    struct  INT_MSK_BITS  bit;  
};

struct INT_MSK_SET_BITS {                                          // bit descriptions
    Uint16  AT_MASK_SET:1;                                         // 0 Asynchronous Timeout. 
    Uint16  LT_MASK_SET:1;                                         // 1 Line Trap. 
    Uint16  WR_MASK_SET:4;                                         // 5:2 Wait Rise. 
    Uint16  rsvd1:10;                                              // 15:6 Reserved 
    Uint16  rsvd2:16;                                              // 31:16 Reserved 
};

union INT_MSK_SET_REG {
    Uint32  all;  
    struct  INT_MSK_SET_BITS  bit;  
};

struct INT_MSK_CLR_BITS {                                          // bit descriptions
    Uint16  AT_MASK_CLR:1;                                         // 0 Asynchronous Timeout. 
    Uint16  LT_MASK_CLR:1;                                         // 1 Line Trap. 
    Uint16  WR_MASK_CLR:4;                                         // 5:2 Wait Rise. 
    Uint16  rsvd1:10;                                              // 15:6 Reserved 
    Uint16  rsvd2:16;                                              // 31:16 Reserved 
};

union INT_MSK_CLR_REG {
    Uint32  all;  
    struct  INT_MSK_CLR_BITS  bit;  
};

struct IO_CTRL_BITS {                                              // bit descriptions
    Uint16  IO_CTRL:16;                                            // 15:0 VTP calibration control for the IOs 
    Uint16  rsvd1:16;                                              // 31:16 Reserved 
};

union IO_CTRL_REG {
    Uint32  all;  
    struct  IO_CTRL_BITS  bit;  
};

struct IO_STAT_BITS {                                              // bit descriptions
    Uint16  IO_STAT:16;                                            // 15:0 VTP calibration status of the IOs 
    Uint16  rsvd1:16;                                              // 31:16 Reserved 
};

union IO_STAT_REG {
    Uint32  all;  
    struct  IO_STAT_BITS  bit;  
};

struct ONENAND_FLASH_CTRL_BITS {                                   // bit descriptions
    Uint16  CS2_USE_1NAND:1;                                       // 0 OneNAND Flash mode for chip select 2. 
    Uint16  CS3_USE_1NAND:1;                                       // 1 OneNAND Flash mode for chip select 3. 
    Uint16  CS4_USE_1NAND:1;                                       // 2 OneNAND Flash mode for chip select 4. 
    Uint16  CS5_USE_1NAND:1;                                       // 3 OneNAND Flash mode for chip select 5. 
    Uint16  CS2_SYNC_RD:1;                                         // 4 OneNAND Flash synchronous read mode for chip select 2. 
    Uint16  CS3_SYNC_RD:1;                                         // 5 OneNAND Flash synchronous read mode for chip select 3. 
    Uint16  CS4_SYNC_RD:1;                                         // 6 OneNAND Flash synchronous read mode for chip select 4. 
    Uint16  CS5_SYNC_RD:1;                                         // 7 OneNAND Flash synchronous read mode for chip select 5. 
    Uint16  RD_LATENCY:3;                                          // 10:8 OneNAND Flash read latency in synchronous read mode. 
    Uint16  rsvd1:5;                                               // 15:11 Reserved 
    Uint16  rsvd2:16;                                              // 31:16 Reserved 
};

union ONENAND_FLASH_CTRL_REG {
    Uint32  all;  
    struct  ONENAND_FLASH_CTRL_BITS  bit;  
};

struct NAND_FLASH_CTRL_BITS {                                      // bit descriptions
    Uint16  CS2_USE_NAND:1;                                        // 0 NAND Flash mode for chip select 2. 
    Uint16  CS3_USE_NAND:1;                                        // 1 NAND Flash mode for chip select 3. 
    Uint16  CS4_USE_NAND:1;                                        // 2 NAND Flash mode for chip select 4. 
    Uint16  CS5_USE_NAND:1;                                        // 3 NAND Flash mode for chip select 5. 
    Uint16  ECC_4BIT_SEL:2;                                        // 5:4 NAND Flash 4-bit ECC chip select selection. 
    Uint16  rsvd1:2;                                               // 7:6 Reserved 
    Uint16  CS2_ECC_START:1;                                       // 8 NAND Flash 1-bit ECC start for chip select 2. 
    Uint16  CS3_ECC_START:1;                                       // 9 NAND Flash 1-bit ECC start for chip select 3. 
    Uint16  CS4_ECC_START:1;                                       // 10 NAND Flash 1-bit ECC start for chip select 4. 
    Uint16  CS5_ECC_START:1;                                       // 11 NAND Flash 1-bit ECC start for chip select 5. 
    Uint16  ECC_4BIT_START:1;                                      // 12 NAND Flash 4-bit ECC start for the selected chip select. 
    Uint16  ADDR_CALC_ST:1;                                        // 13 NAND Flash 4-bit ECC error address and error value calculation start. 
    Uint16  rsvd2:2;                                               // 15:14 Reserved 
    Uint16  rsvd3:16;                                              // 31:16 Reserved 
};

union NAND_FLASH_CTRL_REG {
    Uint32  all;  
    struct  NAND_FLASH_CTRL_BITS  bit;  
};

struct NAND_FLASH_STATUS_BITS {                                    // bit descriptions
    Uint16  WAIT_STAT:4;                                           // 3:0 Status of wait input signals. 
    Uint16  rsvd1:4;                                               // 7:4 Reserved 
    Uint16  CORR_STATE:4;                                          // 11:8 4Bit ECC State Value. 
    Uint16  rsvd2:4;                                               // 15:12 Reserved 
    Uint16  ERR_NUM:2;                                             // 17:16 4-bit ECC error number. 
    Uint16  rsvd3:14;                                              // 31:18 Reserved 
};

union NAND_FLASH_STATUS_REG {
    Uint32  all;  
    struct  NAND_FLASH_STATUS_BITS  bit;  
};

struct PAGE_MODE_CONTROL_BITS {                                    // bit descriptions
    Uint16  CS2_PG_MD_EN:1;                                        // 0 Page Mode enable for NOR Flash connected on CS2. 
    Uint16  CS2_PG_SIZE:1;                                         // 1 Page Size for NOR Flash connected on CS2. 
    Uint16  CS2_PG_DEL:6;                                          // 7:2 Page access delay for NOR Flash connected on CS2. 
    Uint16  CS3_PG_MD_EN:1;                                        // 8 Page Mode enable for NOR Flash connected on CS3. 
    Uint16  CS3_PG_SIZE:1;                                         // 9 Page Size for NOR Flash connected on CS3. 
    Uint16  CS3_PG_DEL:6;                                          // 15:10 Page access delay for NOR Flash connected on CS3. 
    Uint16  CS4_PG_MD_EN:1;                                        // 16 Page Mode enable for NOR Flash connected on CS4. 
    Uint16  CS4_PG_SIZE:1;                                         // 17 Page Size for NOR Flash connected on CS4. 
    Uint16  CS4_PG_DEL:6;                                          // 23:18 Page access delay for NOR Flash connected on CS4. 
    Uint16  CS5_PG_MD_EN:1;                                        // 24 Page Mode enable for NOR Flash connected on CS5. 
    Uint16  CS5_PG_SIZE:1;                                         // 25 Page Size for NOR Flash connected on CS5. 
    Uint16  CS5_PG_DEL:6;                                          // 31:26 Page access delay for NOR Flash connected on CS5. 
};

union PAGE_MODE_CONTROL_REG {
    Uint32  all;  
    struct  PAGE_MODE_CONTROL_BITS  bit;  
};

struct NAND_FLASH_CS2_1BECC_BITS {                                 // bit descriptions
    Uint16  P1E:1;                                                 // 0 1-Bit ECC Code. 
    Uint16  P2E:1;                                                 // 1 1-Bit ECC Code. 
    Uint16  P4E:1;                                                 // 2 1-Bit ECC Code. 
    Uint16  P8E:1;                                                 // 3 1-Bit ECC Code. 
    Uint16  P16E:1;                                                // 4 1-Bit ECC Code. 
    Uint16  P32E:1;                                                // 5 1-Bit ECC Code. 
    Uint16  P64E:1;                                                // 6 1-Bit ECC Code. 
    Uint16  P128E:1;                                               // 7 1-Bit ECC Code. 
    Uint16  P256E:1;                                               // 8 1-Bit ECC Code. 
    Uint16  P512E:1;                                               // 9 1-Bit ECC Code. 
    Uint16  P1024E:1;                                              // 10 1-Bit ECC Code. 
    Uint16  P2048E:1;                                              // 11 1-Bit ECC Code. 
    Uint16  rsvd1:4;                                               // 15:12 Reserved 
    Uint16  P1O:1;                                                 // 16 1-Bit ECC Code. 
    Uint16  P2O:1;                                                 // 17 1-Bit ECC Code. 
    Uint16  P4O:1;                                                 // 18 1-Bit ECC Code. 
    Uint16  P8O:1;                                                 // 19 1-Bit ECC Code. 
    Uint16  P16O:1;                                                // 20 1-Bit ECC Code. 
    Uint16  P32O:1;                                                // 21 1-Bit ECC Code. 
    Uint16  P64O:1;                                                // 22 1-Bit ECC Code. 
    Uint16  P128O:1;                                               // 23 1-Bit ECC Code. 
    Uint16  P256O:1;                                               // 24 1-Bit ECC Code. 
    Uint16  P512O:1;                                               // 25 1-Bit ECC Code. 
    Uint16  P1024O:1;                                              // 26 1-Bit ECC Code. 
    Uint16  P2048O:1;                                              // 27 1-Bit ECC Code. 
    Uint16  rsvd2:4;                                               // 31:28 Reserved 
};

union NAND_FLASH_CS2_1BECC_REG {
    Uint32  all;  
    struct  NAND_FLASH_CS2_1BECC_BITS  bit;  
};

struct NAND_FLASH_CS3_1BECC_BITS {                                 // bit descriptions
    Uint16  P1E:1;                                                 // 0 1-Bit ECC Code. 
    Uint16  P2E:1;                                                 // 1 1-Bit ECC Code. 
    Uint16  P4E:1;                                                 // 2 1-Bit ECC Code. 
    Uint16  P8E:1;                                                 // 3 1-Bit ECC Code. 
    Uint16  P16E:1;                                                // 4 1-Bit ECC Code. 
    Uint16  P32E:1;                                                // 5 1-Bit ECC Code. 
    Uint16  P64E:1;                                                // 6 1-Bit ECC Code. 
    Uint16  P128E:1;                                               // 7 1-Bit ECC Code. 
    Uint16  P256E:1;                                               // 8 1-Bit ECC Code. 
    Uint16  P512E:1;                                               // 9 1-Bit ECC Code. 
    Uint16  P1024E:1;                                              // 10 1-Bit ECC Code. 
    Uint16  P2048E:1;                                              // 11 1-Bit ECC Code. 
    Uint16  rsvd1:4;                                               // 15:12 Reserved 
    Uint16  P1O:1;                                                 // 16 1-Bit ECC Code. 
    Uint16  P2O:1;                                                 // 17 1-Bit ECC Code. 
    Uint16  P4O:1;                                                 // 18 1-Bit ECC Code. 
    Uint16  P8O:1;                                                 // 19 1-Bit ECC Code. 
    Uint16  P16O:1;                                                // 20 1-Bit ECC Code. 
    Uint16  P32O:1;                                                // 21 1-Bit ECC Code. 
    Uint16  P64O:1;                                                // 22 1-Bit ECC Code. 
    Uint16  P128O:1;                                               // 23 1-Bit ECC Code. 
    Uint16  P256O:1;                                               // 24 1-Bit ECC Code. 
    Uint16  P512O:1;                                               // 25 1-Bit ECC Code. 
    Uint16  P1024O:1;                                              // 26 1-Bit ECC Code. 
    Uint16  P2048O:1;                                              // 27 1-Bit ECC Code. 
    Uint16  rsvd2:4;                                               // 31:28 Reserved 
};

union NAND_FLASH_CS3_1BECC_REG {
    Uint32  all;  
    struct  NAND_FLASH_CS3_1BECC_BITS  bit;  
};

struct NAND_FLASH_CS4_1BECC_BITS {                                 // bit descriptions
    Uint16  P1E:1;                                                 // 0 1-Bit ECC Code. 
    Uint16  P2E:1;                                                 // 1 1-Bit ECC Code. 
    Uint16  P4E:1;                                                 // 2 1-Bit ECC Code. 
    Uint16  P8E:1;                                                 // 3 1-Bit ECC Code. 
    Uint16  P16E:1;                                                // 4 1-Bit ECC Code. 
    Uint16  P32E:1;                                                // 5 1-Bit ECC Code. 
    Uint16  P64E:1;                                                // 6 1-Bit ECC Code. 
    Uint16  P128E:1;                                               // 7 1-Bit ECC Code. 
    Uint16  P256E:1;                                               // 8 1-Bit ECC Code. 
    Uint16  P512E:1;                                               // 9 1-Bit ECC Code. 
    Uint16  P1024E:1;                                              // 10 1-Bit ECC Code. 
    Uint16  P2048E:1;                                              // 11 1-Bit ECC Code. 
    Uint16  rsvd1:4;                                               // 15:12 Reserved 
    Uint16  P1O:1;                                                 // 16 1-Bit ECC Code. 
    Uint16  P2O:1;                                                 // 17 1-Bit ECC Code. 
    Uint16  P4O:1;                                                 // 18 1-Bit ECC Code. 
    Uint16  P8O:1;                                                 // 19 1-Bit ECC Code. 
    Uint16  P16O:1;                                                // 20 1-Bit ECC Code. 
    Uint16  P32O:1;                                                // 21 1-Bit ECC Code. 
    Uint16  P64O:1;                                                // 22 1-Bit ECC Code. 
    Uint16  P128O:1;                                               // 23 1-Bit ECC Code. 
    Uint16  P256O:1;                                               // 24 1-Bit ECC Code. 
    Uint16  P512O:1;                                               // 25 1-Bit ECC Code. 
    Uint16  P1024O:1;                                              // 26 1-Bit ECC Code. 
    Uint16  P2048O:1;                                              // 27 1-Bit ECC Code. 
    Uint16  rsvd2:4;                                               // 31:28 Reserved 
};

union NAND_FLASH_CS4_1BECC_REG {
    Uint32  all;  
    struct  NAND_FLASH_CS4_1BECC_BITS  bit;  
};

struct NAND_FLASH_CS5_1BECC_BITS {                                 // bit descriptions
    Uint16  P1E:1;                                                 // 0 1-Bit ECC Code. 
    Uint16  P2E:1;                                                 // 1 1-Bit ECC Code. 
    Uint16  P4E:1;                                                 // 2 1-Bit ECC Code. 
    Uint16  P8E:1;                                                 // 3 1-Bit ECC Code. 
    Uint16  P16E:1;                                                // 4 1-Bit ECC Code. 
    Uint16  P32E:1;                                                // 5 1-Bit ECC Code. 
    Uint16  P64E:1;                                                // 6 1-Bit ECC Code. 
    Uint16  P128E:1;                                               // 7 1-Bit ECC Code. 
    Uint16  P256E:1;                                               // 8 1-Bit ECC Code. 
    Uint16  P512E:1;                                               // 9 1-Bit ECC Code. 
    Uint16  P1024E:1;                                              // 10 1-Bit ECC Code. 
    Uint16  P2048E:1;                                              // 11 1-Bit ECC Code. 
    Uint16  rsvd1:4;                                               // 15:12 Reserved 
    Uint16  P1O:1;                                                 // 16 1-Bit ECC Code. 
    Uint16  P2O:1;                                                 // 17 1-Bit ECC Code. 
    Uint16  P4O:1;                                                 // 18 1-Bit ECC Code. 
    Uint16  P8O:1;                                                 // 19 1-Bit ECC Code. 
    Uint16  P16O:1;                                                // 20 1-Bit ECC Code. 
    Uint16  P32O:1;                                                // 21 1-Bit ECC Code. 
    Uint16  P64O:1;                                                // 22 1-Bit ECC Code. 
    Uint16  P128O:1;                                               // 23 1-Bit ECC Code. 
    Uint16  P256O:1;                                               // 24 1-Bit ECC Code. 
    Uint16  P512O:1;                                               // 25 1-Bit ECC Code. 
    Uint16  P1024O:1;                                              // 26 1-Bit ECC Code. 
    Uint16  P2048O:1;                                              // 27 1-Bit ECC Code. 
    Uint16  rsvd2:4;                                               // 31:28 Reserved 
};

union NAND_FLASH_CS5_1BECC_REG {
    Uint32  all;  
    struct  NAND_FLASH_CS5_1BECC_BITS  bit;  
};

struct IODFT_TLECR_BITS {                                          // bit descriptions
    Uint16  TLEC:16;                                               // 15:0 Number of cycle that the MISR signature will be accumulated. 
    Uint16  rsvd1:16;                                              // 31:16 Reserved 
};

union IODFT_TLECR_REG {
    Uint32  all;  
    struct  IODFT_TLECR_BITS  bit;  
};

struct IODFT_TLGCR_BITS {                                          // bit descriptions
    Uint16  TM:1;                                                  // 0 Functional mode enable. 
    Uint16  _PC:3;                                                  // 3:1 Pattern Code.
    Uint16  MC:2;                                                  // 5:4 MISR State. 
    Uint16  TOEN:1;                                                // 6 Test output enable control. 
    Uint16  ESEL:1;                                                // 7 Output enable select. 
    Uint16  MMS:1;                                                 // 8 Chooses the source of the MISR input. 
    Uint16  rsvd1:3;                                               // 11:9 Reserved 
    Uint16  OPG_LD:1;                                              // 12 Load pattern generators initial value. 
    Uint16  ACT_CAP_EN:1;                                          // 13 Active cycles capture enable. 
    Uint16  MT:1;                                                  // 14 MISR on/off trigger command. 
    Uint16  rsvd2:1;                                               // 15 Reserved 
    Uint16  rsvd3:16;                                              // 31:16 Reserved 
};

union IODFT_TLGCR_REG {
    Uint32  all;  
    struct  IODFT_TLGCR_BITS  bit;  
};

struct IODFT_TLAMR_BITS {                                          // bit descriptions
    Uint32  ADDR_TLMR:28;                                          // 27:0 MISR result for address. 
    Uint16  rsvd1:4;                                               // 31:28 Reserved 
};

union IODFT_TLAMR_REG {
    Uint32  all;  
    struct  IODFT_TLAMR_BITS  bit;  
};

struct IODFT_TLDCMR_BITS {                                         // bit descriptions
    Uint16  DATA_TLMR_MSB:3;                                       // 2:0 MSB of MISR result for data pins. 
    Uint16  rsvd1:5;                                               // 7:3 Reserved 
    Uint16  DQM_TLMR:6;                                            // 13:8 MISR result for DQM pins. 
    Uint16  rsvd2:2;                                               // 15:14 Reserved 
    Uint16  CTL_TLMR:14;                                           // 29:16 MISR result for control pins. 
    Uint16  rsvd3:2;                                               // 31:30 Reserved 
};

union IODFT_TLDCMR_REG {
    Uint32  all;  
    struct  IODFT_TLDCMR_BITS  bit;  
};

struct MODEL_REL_NUM_BITS {                                        // bit descriptions
    Uint16  RELEASE_NUM:8;                                         // 7:0 Release Number. 
    Uint16  rsvd1:8;                                               // 15:8 Reserved 
    Uint16  rsvd2:16;                                              // 31:16 Reserved 
};

union MODEL_REL_NUM_REG {
    Uint32  all;  
    struct  MODEL_REL_NUM_BITS  bit;  
};

struct NAND_FLASH_4BIT_ECCLR_BITS {                                // bit descriptions
    Uint16  ECC_LOAD:10;                                           // 9:0 4-Bit ECC Load. 
    Uint16  rsvd1:6;                                               // 15:10 Reserved 
    Uint16  rsvd2:16;                                              // 31:16 Reserved 
};

union NAND_FLASH_4BIT_ECCLR_REG {
    Uint32  all;  
    struct  NAND_FLASH_4BIT_ECCLR_BITS  bit;  
};

struct NAND_FLASH_4BIT_ECC1_BITS {                                 // bit descriptions
    Uint16  ECC_VAL1:10;                                           // 9:0 4-Bit ECC or syndrome value-1 for write. 
    Uint16  rsvd1:6;                                               // 15:10 Reserved 
    Uint16  ECC_VAL2:10;                                           // 25:16 4-Bit ECC or syndrome value-2 for write. 
    Uint16  rsvd2:6;                                               // 31:26 Reserved 
};

union NAND_FLASH_4BIT_ECC1_REG {
    Uint32  all;  
    struct  NAND_FLASH_4BIT_ECC1_BITS  bit;  
};

struct NAND_FLASH_4BIT_ECC2_BITS {                                 // bit descriptions
    Uint16  ECC_VAL3:10;                                           // 9:0 4-Bit ECC or syndrome value-3 for write. 
    Uint16  rsvd1:6;                                               // 15:10 Reserved 
    Uint16  ECC_VAL4:10;                                           // 25:16 4-Bit ECC or syndrome value-4 for write. 
    Uint16  rsvd2:6;                                               // 31:26 Reserved 
};

union NAND_FLASH_4BIT_ECC2_REG {
    Uint32  all;  
    struct  NAND_FLASH_4BIT_ECC2_BITS  bit;  
};

struct NAND_FLASH_4BIT_ECC3_BITS {                                 // bit descriptions
    Uint16  ECC_VAL5:10;                                           // 9:0 4-Bit ECC or syndrome value-5 for write. 
    Uint16  rsvd1:6;                                               // 15:10 Reserved 
    Uint16  ECC_VAL6:10;                                           // 25:16 4-Bit ECC or syndrome value-6 for write. 
    Uint16  rsvd2:6;                                               // 31:26 Reserved 
};

union NAND_FLASH_4BIT_ECC3_REG {
    Uint32  all;  
    struct  NAND_FLASH_4BIT_ECC3_BITS  bit;  
};

struct NAND_FLASH_4BIT_ECC4_BITS {                                 // bit descriptions
    Uint16  ECC_VAL7:10;                                           // 9:0 4-Bit ECC or syndrome value-7 for write. 
    Uint16  rsvd1:6;                                               // 15:10 Reserved 
    Uint16  ECC_VAL8:10;                                           // 25:16 4-Bit ECC or syndrome value-8 for write. 
    Uint16  rsvd2:6;                                               // 31:26 Reserved 
};

union NAND_FLASH_4BIT_ECC4_REG {
    Uint32  all;  
    struct  NAND_FLASH_4BIT_ECC4_BITS  bit;  
};

struct NAND_FLASH_ERR_ADDR1_BITS {                                 // bit descriptions
    Uint16  ERR_ADDR1:10;                                          // 9:0 4-bit ECC error address 1. 
    Uint16  rsvd1:6;                                               // 15:10 Reserved 
    Uint16  ERR_ADDR2:10;                                          // 25:16 4-bit ECC error address 2. 
    Uint16  rsvd2:6;                                               // 31:26 Reserved 
};

union NAND_FLASH_ERR_ADDR1_REG {
    Uint32  all;  
    struct  NAND_FLASH_ERR_ADDR1_BITS  bit;  
};

struct NAND_FLASH_ERR_ADDR2_BITS {                                 // bit descriptions
    Uint16  ERR_ADDR3:10;                                          // 9:0 4-bit ECC error address 3. 
    Uint16  rsvd1:6;                                               // 15:10 Reserved 
    Uint16  ERR_ADDR4:10;                                          // 25:16 4-bit ECC error address 4. 
    Uint16  rsvd2:6;                                               // 31:26 Reserved 
};

union NAND_FLASH_ERR_ADDR2_REG {
    Uint32  all;  
    struct  NAND_FLASH_ERR_ADDR2_BITS  bit;  
};

struct NAND_FLASH_ERR_VAL1_BITS {                                  // bit descriptions
    Uint16  ERR_VAL1:10;                                           // 9:0 4-bit ECC error value 1. 
    Uint16  rsvd1:6;                                               // 15:10 Reserved 
    Uint16  ERR_VAL2:10;                                           // 25:16 4-bit ECC error value 2. 
    Uint16  rsvd2:6;                                               // 31:26 Reserved 
};

union NAND_FLASH_ERR_VAL1_REG {
    Uint32  all;  
    struct  NAND_FLASH_ERR_VAL1_BITS  bit;  
};

struct NAND_FLASH_ERR_VAL2_BITS {                                  // bit descriptions
    Uint16  ERR_VAL3:10;                                           // 9:0 4-bit ECC error value 3. 
    Uint16  rsvd1:6;                                               // 15:10 Reserved 
    Uint16  ERR_VAL4:10;                                           // 25:16 4-bit ECC error value 4. 
    Uint16  rsvd2:6;                                               // 31:26 Reserved 
};

union NAND_FLASH_ERR_VAL2_REG {
    Uint32  all;  
    struct  NAND_FLASH_ERR_VAL2_BITS  bit;  
};

struct EMIF_REGS {
    union   RCSR_REG                     RCSR;                     // Revision Code and Status Register 
    union   ASYNC_WCCR_REG               ASYNC_WCCR;               // Async Wait Cycle Config Register 
    union   SDRAM_CR_REG                 SDRAM_CR;                 // SDRAM (pad_cs_o_n[0]/pad_cs_o_n[1]) Config Register 
    union   SDRAM_RCR_REG                SDRAM_RCR;                // SDRAM Refresh Control Register 
    union   ASYNC_CS2_CR_REG             ASYNC_CS2_CR;             // Async 1 (pad_cs_o_n[2]) Config Register 
    union   ASYNC_CS3_CR_REG             ASYNC_CS3_CR;             // Async 2 (pad_cs_o_n[3]) Config Register 
    union   ASYNC_CS4_CR_REG             ASYNC_CS4_CR;             // Async 3 (pad_cs_o_n[4]) Config Register 
    union   ASYNC_CS5_CR_REG             ASYNC_CS5_CR;             // Async 4 (pad_cs_o_n[5]) Config Register 
    union   SDRAM_TR_REG                 SDRAM_TR;                 // SDRAM Timing Register 
    union   SDRAM_SR_REG                 SDRAM_SR;                 // SDRAM Status Register 
    Uint16                               rsvd1[4];                 // Reserved 
    Uint32                               TOTAL_SDRAM_AR;           // Total SDRAM Accesses Register 
    Uint32                               TOTAL_SDRAM_ACTR;         // Total SDRAM Activate Register 
    Uint16                               rsvd2[2];                 // Reserved 
    union   SDR_EXT_TMNG_REG             SDR_EXT_TMNG;             // SDRAM SR/PD Exit Timing Register 
    union   INT_RAW_REG                  INT_RAW;                  // Interrupt Raw Register 
    union   INT_MSK_REG                  INT_MSK;                  // Interrupt Masked Register 
    union   INT_MSK_SET_REG              INT_MSK_SET;              // Interrupt Mask Set Register 
    union   INT_MSK_CLR_REG              INT_MSK_CLR;              // Interrupt Mask Clear Register 
    union   IO_CTRL_REG                  IO_CTRL;                  // IO Control Register 
    union   IO_STAT_REG                  IO_STAT;                  // IO Status Register 
    Uint16                               rsvd3[4];                 // Reserved 
    union   NAND_FLASH_CTRL_REG          NAND_FLASH_CTRL;          // NAND Flash Control Register 
    union   NAND_FLASH_STATUS_REG        NAND_FLASH_STATUS;        // NAND Flash Status Register 
    union   PAGE_MODE_CONTROL_REG        PAGE_MODE_CONTROL;        // Page Mode Control Register 
    Uint16                               rsvd4[2];                 // Reserved 
    union   NAND_FLASH_CS2_1BECC_REG     NAND_FLASH_CS2_1BECC;     // NAND Flash CS2 1-Bit ECC Register (for pad_cs_o_n[2]) 
    union   NAND_FLASH_CS3_1BECC_REG     NAND_FLASH_CS3_1BECC;     // NAND Flash CS3 1-Bit ECC Register (for pad_cs_o_n[3]) 
    union   NAND_FLASH_CS4_1BECC_REG     NAND_FLASH_CS4_1BECC;     // NAND Flash CS4 1-Bit ECC Register (for pad_cs_o_n[4]) 
    union   NAND_FLASH_CS5_1BECC_REG     NAND_FLASH_CS5_1BECC;     // NAND Flash CS5 1-Bit ECC Register (for pad_cs_o_n[5]) 
    Uint16                               rsvd5[2];                 // Reserved 
    union   IODFT_TLECR_REG              IODFT_TLECR;              // IODFT Test Logic Execution Counter Register 
    union   IODFT_TLGCR_REG              IODFT_TLGCR;              // IODFT Test Logic Global Control Register 
    Uint16                               rsvd6[2];                 // Reserved 
    union   IODFT_TLAMR_REG              IODFT_TLAMR;              // IODFT Test Logic Address MISR Result Register 
    Uint32                               IODFT_TLDMR;              // IODFT Test Logic Data MISR Result Register 
    union   IODFT_TLDCMR_REG             IODFT_TLDCMR;             // IODFT Test Logic Data and Control MISR Result Register 
    Uint16                               rsvd7[10];                 // Reserved : Shantha modified it. old value rsvd7[8]
    union   MODEL_REL_NUM_REG            MODEL_REL_NUM;            // Module Release Number Register 
    Uint16                               rsvd8[4];                 // Reserved : Shantha modified it old value rsvd8[6]
    union   NAND_FLASH_4BIT_ECCLR_REG    NAND_FLASH_4BIT_ECCLR;    // NAND Flash 4-Bit ECC Load Register 
    union   NAND_FLASH_4BIT_ECC1_REG     NAND_FLASH_4BIT_ECC1;     // NAND Flash 4-Bit ECC 1 Register 
    union   NAND_FLASH_4BIT_ECC2_REG     NAND_FLASH_4BIT_ECC2;     // NAND Flash 4-Bit ECC 2 Register 
    union   NAND_FLASH_4BIT_ECC3_REG     NAND_FLASH_4BIT_ECC3;     // NAND Flash 4-Bit ECC 3 Register 
    union   NAND_FLASH_4BIT_ECC4_REG     NAND_FLASH_4BIT_ECC4;     // NAND Flash 4-Bit ECC 4 Register 
    union   NAND_FLASH_ERR_ADDR1_REG     NAND_FLASH_ERR_ADDR1;     // NAND Flash Error Address 1 Register 
    union   NAND_FLASH_ERR_ADDR2_REG     NAND_FLASH_ERR_ADDR2;     // NAND Flash Error Address 2 Register 
    union   NAND_FLASH_ERR_VAL1_REG      NAND_FLASH_ERR_VAL1;      // NAND Flash Error Value 1 Register 
    union   NAND_FLASH_ERR_VAL2_REG      NAND_FLASH_ERR_VAL2;      // NAND Flash Error Value 2 Register 
};

//---------------------------------------------------------------------------
// Emif External References & Function Declarations:
//

extern volatile struct EMIF_REGS EMif1Regs;
extern volatile struct EMIF_REGS EMif2Regs;

#ifdef __cplusplus
}
#endif                                                             /* extern "C" */


#endif                                                             // end of F2837x_EMIF_H definition
//===========================================================================
// End of file.
//===========================================================================
