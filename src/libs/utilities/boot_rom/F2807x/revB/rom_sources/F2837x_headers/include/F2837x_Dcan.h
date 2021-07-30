//###########################################################################
//
// FILE:   F2837x_Dcan.h
//
// TITLE:  F2837x Device Dcan Register Definitions.
//
//###########################################################################
// $TI Release:   $
// $Release Date:   $
//###########################################################################

#ifndef F2837x_Dcan_H
#define F2837x_Dcan_H
#ifdef __cplusplus
extern "C" {
#endif


//---------------------------------------------------------------------------
// Dcan Individual Register Bit Definitions:

struct CAN_CTL_BITS {                                    // bit descriptions
    Uint16  Init:1;                                      // 0 Initialization 
    Uint16  IE0:1;                                       // 1 Interrupt line 0 Enable Disabled 
    Uint16  SIE:1;                                       // 2 Status Change Interrupt Enable Disabled 
    Uint16  EIE:1;                                       // 3 Error Interrupt Enable Disabled 
    Uint16  rsvd1:1;                                     // 4:4 Reserved 
    Uint16  DAR:1;                                       // 5 Disable Automatic Retransmission 
    Uint16  CCE:1;                                       // 6 Configuration Change Enable 
    Uint16  Test:1;                                      // 7 Test Mode Enable 
    Uint16  IDS:1;                                       // 8 Interruption Debug Support Enable 
    Uint16  ABO:1;                                       // 9 Auto-Bus-On Enable 
    Uint16  PMD:4;                                       // 13:10 Parity on/off 
    Uint16  rsvd2:1;                                     // 14:14 Reserved 
    Uint16  SWR:1;                                       // 15 SW Reset Enable 
    Uint16  INITDBG:1;                                   // 16 Debug Mode Status 
    Uint16  IE1:1;                                       // 17 Interrupt line 1 Enable Disabled 
    Uint16  rsvd3:6;                                     // 23:18 Reserved 
    Uint16  PDR:1;                                       // 24 Power Down Request Mode 
    Uint16  WUBA:1;                                      // 25 Wake Up on Bus Activity 
    Uint16  rsvd4:6;                                     // 31:26 Reserved 
};

union CAN_CTL_REG {
    Uint32  all;  
    struct  CAN_CTL_BITS  bit;  
};

struct CAN_ES_BITS {                                     // bit descriptions
    Uint16  LEC:3;                                       // 2:0 Last Error Code 
    Uint16  TxOk:1;                                      // 3 Transmission status 
    Uint16  RxOk:1;                                      // 4 Reception status 
    Uint16  EPass:1;                                     // 5 Error Passive State 
    Uint16  EWarn:1;                                     // 6 Warning State 
    Uint16  BOff:1;                                      // 7 Bus-Off State 
    Uint16  PER:1;                                       // 8 Parity Error Detected 
    Uint16  WakeUpPnd:1;                                 // 9 Wake Up Pending 
    Uint16  PDA:1;                                       // 10 Power down mode acknowledge 
    Uint16  rsvd1:5;                                     // 15:11 Reserved 
    Uint16  rsvd2:16;                                    // 31:16 Reserved 
};

union CAN_ES_REG {
    Uint32  all;  
    struct  CAN_ES_BITS  bit;  
};

struct CAN_ERRC_BITS {                                   // bit descriptions
    Uint16  TEC:8;                                       // 7:0 Transmit Error Counter 
    Uint16  REC:7;                                       // 14:8 Receive Error Counter 
    Uint16  RP:1;                                        // 15 Receive Error Passive 
    Uint16  rsvd1:16;                                    // 31:16 Reserved 
};

union CAN_ERRC_REG {
    Uint32  all;  
    struct  CAN_ERRC_BITS  bit;  
};

struct CAN_BTR_BITS {                                    // bit descriptions
    Uint16  BPR:6;                                       // 5:0 Baud Rate Prescaler 
    Uint16  SJW:2;                                       // 7:6 Synchronization Jump Width 
    Uint16  TSEG1:4;                                     // 11:8 Time segment 
    Uint16  TSEG2:3;                                     // 14:12 Time segment 
    Uint16  rsvd1:1;                                     // 15:15 Reserved 
    Uint16  BRPE:4;                                      // 19:16 Baud Rate Prescaler Extension 
    Uint16  rsvd2:12;                                    // 31:20 Reserved 
};

union CAN_BTR_REG {
    Uint32  all;  
    struct  CAN_BTR_BITS  bit;  
};

struct CAN_INT_BITS {                                    // bit descriptions
    Uint16  INT0ID:16;                                   // 15:0 Interrupt Identifier 
    Uint16  INT1ID:8;                                    // 23:16 Interrupt 1 Identifier 
    Uint16  rsvd1:8;                                     // 31:24 Reserved 
};

union CAN_INT_REG {
    Uint32  all;  
    struct  CAN_INT_BITS  bit;  
};

struct CAN_TEST_BITS {                                   // bit descriptions
    Uint16  rsvd1:3;                                     // 2:0 Reserved 
    Uint16  SILENT:1;                                    // 3 Silent Mode 
    Uint16  LBACK:1;                                     // 4 Loopback Mode 
    Uint16  TX:2;                                        // 6:5 CANTX Pin Control 
    Uint16  RX:1;                                        // 7 CANRX Pin Status 
    Uint16  EXL:1;                                       // 8 External Loopback Mode 
    Uint16  RDA:1;                                       // 9 RAM Direct Access Enable: 
    Uint16  rsvd2:6;                                     // 15:10 Reserved 
    Uint16  rsvd3:16;                                    // 31:16 Reserved 
};

union CAN_TEST_REG {
    Uint32  all;  
    struct  CAN_TEST_BITS  bit;  
};

struct CAN_PERR_BITS {                                   // bit descriptions
    Uint16  MSG_NUM:8;                                   // 7:0 Message Number 
    Uint16  WORD_NUM:3;                                  // 10:8 Word Number 
    Uint16  rsvd1:5;                                     // 15:11 Reserved 
    Uint16  rsvd2:16;                                    // 31:16 Reserved 
};

union CAN_PERR_REG {
    Uint32  all;  
    struct  CAN_PERR_BITS  bit;  
};

struct CAN_REL_BITS {                                    // bit descriptions
    Uint16  DAY:8;                                       // 7:0 Day 
    Uint16  MON:8;                                       // 15:8 Month 
    Uint16  YEAR:4;                                      // 19:16 Year 
    Uint16  SUBSTEP:4;                                   // 23:20 Substep 
    Uint16  STEP:4;                                      // 27:24 Step 
    Uint16  REL:4;                                       // 31:28 Release 
};

union CAN_REL_REG {
    Uint32  all;  
    struct  CAN_REL_BITS  bit;  
};

struct CAN_ECCDIAG_BITS {                                // bit descriptions
    Uint16  ECCDIAG:4;                                   // 3:0 Diagnostic Enable 
    Uint16  rsvd1:12;                                    // 15:4 Reserved 
    Uint16  rsvd2:16;                                    // 31:16 Reserved 
};

union CAN_ECCDIAG_REG {
    Uint32  all;  
    struct  CAN_ECCDIAG_BITS  bit;  
};

struct CAN_ECCDIAG_STAT_BITS {                           // bit descriptions
    Uint16  SEFLG:1;                                     // 0 Single bit error flag 
    Uint16  rsvd1:7;                                     // 7:1 Reserved 
    Uint16  DEFLG:1;                                     // 8 Double bit error flag 
    Uint16  rsvd2:7;                                     // 15:9 Reserved 
    Uint16  rsvd3:16;                                    // 31:16 Reserved 
};

union CAN_ECCDIAG_STAT_REG {
    Uint32  all;  
    struct  CAN_ECCDIAG_STAT_BITS  bit;  
};

struct CAN_RAM_INIT_BITS {                               // bit descriptions
    Uint16  KEY0:1;                                      // 0 KEY0 
    Uint16  KEY1:1;                                      // 1 KEY1 
    Uint16  KEY2:1;                                      // 2 KEY2 
    Uint16  KEY3:1;                                      // 3 KEY3 
    Uint16  CAN_RAM_INIT:1;                              // 4 Initialize CAN Mailbox RAM 
    Uint16  RAM_INIT_DONE:1;                             // 5 CAN RAM initialization complete 
    Uint16  rsvd1:10;                                    // 15:6 Reserved 
    Uint16  rsvd2:16;                                    // 31:16 Reserved 
};

union CAN_RAM_INIT_REG {
    Uint32  all;  
    struct  CAN_RAM_INIT_BITS  bit;  
};

struct CAN_GLB_INT_EN_BITS {                             // bit descriptions
    Uint16  GLBINT0_EN:1;                                // 0 Global Interrupt Enable for CAN INT0 
    Uint16  GLBINT1_EN:1;                                // 1 Global Interrupt Enable for CAN INT1 
    Uint16  rsvd1:14;                                    // 15:2 Reserved 
    Uint16  rsvd2:16;                                    // 31:16 Reserved 
};

union CAN_GLB_INT_EN_REG {
    Uint32  all;  
    struct  CAN_GLB_INT_EN_BITS  bit;  
};

struct CAN_GLB_INT_FLG_BITS {                            // bit descriptions
    Uint16  Name:1;                                      // 0 Global Interrupt Flag for CAN INT0 
    Uint16  INT1_FLG:1;                                  // 1 Global Interrupt Flag for CAN INT1 
    Uint16  rsvd1:14;                                    // 15:2 Reserved 
    Uint16  rsvd2:16;                                    // 31:16 Reserved 
};

union CAN_GLB_INT_FLG_REG {
    Uint32  all;  
    struct  CAN_GLB_INT_FLG_BITS  bit;  
};

struct CAN_GLB_INT_CLR_BITS {                            // bit descriptions
    Uint16  INT0_FLG_CLR:1;                              // 0 Global Interrupt flag clear for CAN INT0 
    Uint16  INT1_FLG_CLR:1;                              // 1 Global Interrupt flag clear for CAN INT1 
    Uint16  rsvd1:14;                                    // 15:2 Reserved 
    Uint16  rsvd2:16;                                    // 31:16 Reserved 
};

union CAN_GLB_INT_CLR_REG {
    Uint32  all;  
    struct  CAN_GLB_INT_CLR_BITS  bit;  
};

struct CAN_TXRQ_X_BITS {                                 // bit descriptions
    Uint16  TxRqstReg1:2;                                // 1:0 Transmit Request Register 1 
    Uint16  TxRqstReg2:2;                                // 3:2 Transmit Request Register 2 
    Uint16  rsvd1:12;                                    // 15:4 Reserved 
    Uint16  rsvd2:16;                                    // 31:16 Reserved 
};

union CAN_TXRQ_X_REG {
    Uint32  all;  
    struct  CAN_TXRQ_X_BITS  bit;  
};

struct CAN_NDAT_X_BITS {                                 // bit descriptions
    Uint16  NewDatReg1:2;                                // 1:0 New Data Register 1 
    Uint16  NewDatReg2:2;                                // 3:2 New Data Register 2 
    Uint16  rsvd1:12;                                    // 15:4 Reserved 
    Uint16  rsvd2:16;                                    // 31:16 Reserved 
};

union CAN_NDAT_X_REG {
    Uint32  all;  
    struct  CAN_NDAT_X_BITS  bit;  
};

struct CAN_IPEN_X_BITS {                                 // bit descriptions
    Uint16  IntPndReg1:2;                                // 1:0 Interrupt Pending Register 1 
    Uint16  IntPndReg2:2;                                // 3:2 Interrupt Pending Register 2 
    Uint16  rsvd1:12;                                    // 15:4 Reserved 
    Uint16  rsvd2:16;                                    // 31:16 Reserved 
};

union CAN_IPEN_X_REG {
    Uint32  all;  
    struct  CAN_IPEN_X_BITS  bit;  
};

struct CAN_MVAL_X_BITS {                                 // bit descriptions
    Uint16  MsgValReg1:2;                                // 1:0 Message Valid Register 1 
    Uint16  MsgValReg2:2;                                // 3:2 Message Valid Register 2 
    Uint16  rsvd1:12;                                    // 15:4 Reserved 
    Uint16  rsvd2:16;                                    // 31:16 Reserved 
};

union CAN_MVAL_X_REG {
    Uint32  all;  
    struct  CAN_MVAL_X_BITS  bit;  
};

struct CAN_IF1CMD_BITS {                                 // bit descriptions
    Uint16  MSG_NUM:8;                                   // 7:0 Message Number 
    Uint16  rsvd1:7;                                     // 14:8 Reserved 
    Uint16  Busy:1;                                      // 15 Busy Flag 
    Uint16  DATA_B:1;                                    // 16 Access Data Bytes 4-7 
    Uint16  DATA_A:1;                                    // 17 Access Data Bytes 0-3 
    Uint16  TXRQST:1;                                    // 18 Access Transmission Request Bit 
    Uint16  ClrIntPnd:1;                                 // 19 Clear Interrupt Pending Bit 
    Uint16  Control:1;                                   // 20 Access Control Bits 
    Uint16  Arb:1;                                       // 21 Access Arbitration Bits 
    Uint16  Mask:1;                                      // 22 Access Mask Bits 
    Uint16  DIR:1;                                       // 23 Write/Read Direction 
    Uint16  rsvd2:8;                                     // 31:24 Reserved 
};

union CAN_IF1CMD_REG {
    Uint32  all;  
    struct  CAN_IF1CMD_BITS  bit;  
};

struct CAN_IF2CMD_BITS {                                 // bit descriptions
    Uint16  MSG_NUM:8;                                   // 7:0 Message Number 
    Uint16  rsvd1:7;                                     // 14:8 Reserved 
    Uint16  Busy:1;                                      // 15 Busy Flag 
    Uint16  DATA_B:1;                                    // 16 Access Data Bytes 4-7 
    Uint16  DATA_A:1;                                    // 17 Access Data Bytes 0-3 
    Uint16  TxRqst:1;                                    // 18 Access Transmission Request Bit 
    Uint16  ClrIntPnd:1;                                 // 19 Clear Interrupt Pending Bit 
    Uint16  Control:1;                                   // 20 Access Control Bits 
    Uint16  Arb:1;                                       // 21 Access Arbitration Bits 
    Uint16  Mask:1;                                      // 22 Access Mask Bits 
    Uint16  DIR:1;                                       // 23 Write/Read Direction 
    Uint16  rsvd2:8;                                     // 31:24 Reserved 
};

union CAN_IF2CMD_REG {
    Uint32  all;  
    struct  CAN_IF2CMD_BITS  bit;  
};

struct CAN_IF1MSK_BITS {                                 // bit descriptions
    Uint32  Msk:29;                                      // 28:0 Identifier Mask 
    Uint16  rsvd1:1;                                     // 29:29 Reserved 
    Uint16  MDir:1;                                      // 30 Mask Message Direction 
    Uint16  MXtd:1;                                      // 31 Mask Extended Identifier 
};

union CAN_IF1MSK_REG {
    Uint32  all;  
    struct  CAN_IF1MSK_BITS  bit;  
};

struct CAN_IF2MSK_BITS {                                 // bit descriptions
    Uint32  Msk:29;                                      // 28:0 Identifier Mask 
    Uint16  rsvd1:1;                                     // 29:29 Reserved 
    Uint16  MDir:1;                                      // 30 Mask Message Direction 
    Uint16  MXtd:1;                                      // 31 Mask Extended Identifier 
};

union CAN_IF2MSK_REG {
    Uint32  all;  
    struct  CAN_IF2MSK_BITS  bit;  
};

struct CAN_IF1ARB_BITS {                                 // bit descriptions
    Uint32  ID:29;                                       // 28:0 ` 
    Uint16  Dir:1;                                       // 29 Message Direction 
    Uint16  Xtd:1;                                       // 30 Extended Identifier 
    Uint16  MsgVal:1;                                    // 31 Message Valid 
};

union CAN_IF1ARB_REG {
    Uint32  all;  
    struct  CAN_IF1ARB_BITS  bit;  
};

struct CAN_IF2ARB_BITS {                                 // bit descriptions
    Uint32  ID:29;                                       // 28:0 Message Identifier 
    Uint16  Dir:1;                                       // 29 Message Direction 
    Uint16  Xtd:1;                                       // 30 Extended Identifier 
    Uint16  MsgVal:1;                                    // 31 Message Valid 
};

union CAN_IF2ARB_REG {
    Uint32  all;  
    struct  CAN_IF2ARB_BITS  bit;  
};

struct CAN_IF1MCTL_BITS {                                // bit descriptions
    Uint16  DLC:4;                                       // 3:0 Data length code 
    Uint16  rsvd1:3;                                     // 6:4 Reserved 
    Uint16  EoB:1;                                       // 7 End of Block 
    Uint16  TxRqst:1;                                    // 8 Transmit Request 
    Uint16  RmtEn:1;                                     // 9 Remote Enable 
    Uint16  RxIE:1;                                      // 10 Receive Interrupt Enable 
    Uint16  TxIE:1;                                      // 11 Transmit Interrupt Enable 
    Uint16  UMask:1;                                     // 12 Use Acceptance Mask 
    Uint16  IntPnd:1;                                    // 13 Interrupt Pending 
    Uint16  MsgLst:1;                                    // 14 Message Lost 
    Uint16  NewDat:1;                                    // 15 New Data 
    Uint16  rsvd2:16;                                    // 31:16 Reserved 
};

union CAN_IF1MCTL_REG {
    Uint32  all;  
    struct  CAN_IF1MCTL_BITS  bit;  
};

struct CAN_IF2MCTL_BITS {                                // bit descriptions
    Uint16  DLC:4;                                       // 3:0 Data length code 
    Uint16  rsvd1:3;                                     // 6:4 Reserved 
    Uint16  EoB:1;                                       // 7 End of Block 
    Uint16  TxRqst:1;                                    // 8 Transmit Request 
    Uint16  RmtEn:1;                                     // 9 Remote Enable 
    Uint16  RxIE:1;                                      // 10 Receive Interrupt Enable 
    Uint16  TxIE:1;                                      // 11 Transmit Interrupt Enable 
    Uint16  UMask:1;                                     // 12 Use Acceptance Mask 
    Uint16  IntPnd:1;                                    // 13 Interrupt Pending 
    Uint16  MsgLst:1;                                    // 14 Message Lost 
    Uint16  NewDat:1;                                    // 15 New Data 
    Uint16  rsvd2:16;                                    // 31:16 Reserved 
};

union CAN_IF2MCTL_REG {
    Uint32  all;  
    struct  CAN_IF2MCTL_BITS  bit;  
};

struct CAN_IF1DATA_BITS {                                // bit descriptions
    Uint16  Data_0:8;                                    // 7:0 Data Byte 0 
    Uint16  Data_1:8;                                    // 15:8 Data Byte 1 
    Uint16  Data_2:8;                                    // 23:16 Data Byte 2 
    Uint16  Data_3:8;                                    // 31:24 Data Byte 3 
};

union CAN_IF1DATA_REG {
    Uint32  all;  
    struct  CAN_IF1DATA_BITS  bit;  
};

struct CAN_IF1DATB_BITS {                                // bit descriptions
    Uint16  Data_4:8;                                    // 7:0 Data Byte 4 
    Uint16  Data_5:8;                                    // 15:8 Data Byte 5 
    Uint16  Data_6:8;                                    // 23:16 Data Byte 6 
    Uint16  Data_7:8;                                    // 31:24 Data Byte 7 
};

union CAN_IF1DATB_REG {
    Uint32  all;  
    struct  CAN_IF1DATB_BITS  bit;  
};

struct CAN_IF2DATA_BITS {                                // bit descriptions
    Uint16  Data_0:8;                                    // 7:0 Data Byte 0 
    Uint16  Data_1:8;                                    // 15:8 Data Byte 1 
    Uint16  Data_2:8;                                    // 23:16 Data Byte 2 
    Uint16  Data_3:8;                                    // 31:24 Data Byte 3 
};

union CAN_IF2DATA_REG {
    Uint32  all;  
    struct  CAN_IF2DATA_BITS  bit;  
};

struct CAN_IF2DATB_BITS {                                // bit descriptions
    Uint16  Data_4:8;                                    // 7:0 Data Byte 4 
    Uint16  Data_5:8;                                    // 15:8 Data Byte 5 
    Uint16  Data_6:8;                                    // 23:16 Data Byte 6 
    Uint16  Data_7:8;                                    // 31:24 Data Byte 7 
};

union CAN_IF2DATB_REG {
    Uint32  all;  
    struct  CAN_IF2DATB_BITS  bit;  
};

struct CAN_IF3OBS_BITS {                                 // bit descriptions
    Uint16  Mask:1;                                      // 0 Mask data read observation 
    Uint16  Arb:1;                                       // 1 Arbitration data read observation 
    Uint16  Ctrl:1;                                      // 2 Ctrl read observation 
    Uint16  Data_A:1;                                    // 3 Data A read observation 
    Uint16  Data_B:1;                                    // 4 Data B read observation 
    Uint16  rsvd1:3;                                     // 7:5 Reserved 
    Uint16  IF3SM:1;                                     // 8 IF3 Status of Mask data read access 
    Uint16  IF3SA:1;                                     // 9 IF3 Status of Arbitration data read access 
    Uint16  IF3SC:1;                                     // 10 IF3 Status of Control bits read access 
    Uint16  IF3SDA:1;                                    // 11 IF3 Status of Data A read access 
    Uint16  IF3SDB:1;                                    // 12 IF3 Status of Data B read access 
    Uint16  rsvd2:2;                                     // 14:13 Reserved 
    Uint16  IF3Upd:1;                                    // 15 IF3 Update Data 
    Uint16  rsvd3:16;                                    // 31:16 Reserved 
};

union CAN_IF3OBS_REG {
    Uint32  all;  
    struct  CAN_IF3OBS_BITS  bit;  
};

struct CAN_IF3MSK_BITS {                                 // bit descriptions
    Uint32  Msk:29;                                      // 28:0 Mask 
    Uint16  rsvd1:1;                                     // 29:29 Reserved 
    Uint16  MDir:1;                                      // 30 Mask Message Direction 
    Uint16  MXtd:1;                                      // 31 Mask Extended Identifier 
};

union CAN_IF3MSK_REG {
    Uint32  all;  
    struct  CAN_IF3MSK_BITS  bit;  
};

struct CAN_IF3ARB_BITS {                                 // bit descriptions
    Uint32  ID:29;                                       // 28:0 Message Identifier 
    Uint16  Dir:1;                                       // 29 Message Direction 
    Uint16  Xtd:1;                                       // 30 Extended Identifier 
    Uint16  MsgVal:1;                                    // 31 Message Valid 
};

union CAN_IF3ARB_REG {
    Uint32  all;  
    struct  CAN_IF3ARB_BITS  bit;  
};

struct CAN_IF3MCTL_BITS {                                // bit descriptions
    Uint16  DLC:4;                                       // 3:0 Data length code 
    Uint16  rsvd1:3;                                     // 6:4 Reserved 
    Uint16  EoB:1;                                       // 7 End of Block 
    Uint16  TxRqst:1;                                    // 8 Transmit Request 
    Uint16  RmtEn:1;                                     // 9 Remote Enable 
    Uint16  RxIE:1;                                      // 10 Receive Interrupt Enable 
    Uint16  TxIE:1;                                      // 11 Transmit Interrupt Enable 
    Uint16  UMask:1;                                     // 12 Use Acceptance Mask 
    Uint16  IntPnd:1;                                    // 13 Interrupt Pending 
    Uint16  MsgLst:1;                                    // 14 Message Lost 
    Uint16  NewDat:1;                                    // 15 New Data 
    Uint16  rsvd2:16;                                    // 31:16 Reserved 
};

union CAN_IF3MCTL_REG {
    Uint32  all;  
    struct  CAN_IF3MCTL_BITS  bit;  
};

struct CAN_IF3DATA_BITS {                                // bit descriptions
    Uint16  Data_0:8;                                    // 7:0 Data Byte 0 
    Uint16  Data_1:8;                                    // 15:8 Data Byte 1 
    Uint16  Data_2:8;                                    // 23:16 Data Byte 2 
    Uint16  Data_3:8;                                    // 31:24 Data Byte 3 
};

union CAN_IF3DATA_REG {
    Uint32  all;  
    struct  CAN_IF3DATA_BITS  bit;  
};

struct CAN_IF3DATB_BITS {                                // bit descriptions
    Uint16  Data_4:8;                                    // 7:0 Data Byte 4 
    Uint16  Data_5:8;                                    // 15:8 Data Byte 5 
    Uint16  Data_6:8;                                    // 23:16 Data Byte 6 
    Uint16  Data_7:8;                                    // 31:24 Data Byte 7 
};

union CAN_IF3DATB_REG {
    Uint32  all;  
    struct  CAN_IF3DATB_BITS  bit;  
};

struct CAN_IO_CTL_TX_BITS {                              // bit descriptions
    Uint16  In:1;                                        // 0 Input value of CAN_TX pin 
    Uint16  rsvd1:2;                                     // 2:1 Reserved 
    Uint16  Func:1;                                      // 3 Functionality of CAN_TX pin 
    Uint16  rsvd2:12;                                    // 15:4 Reserved 
    Uint16  rsvd3:16;                                    // 31:16 Reserved 
};

union CAN_IO_CTL_TX_REG {
    Uint32  all;  
    struct  CAN_IO_CTL_TX_BITS  bit;  
};

struct CAN_IO_CTL_RX_BITS {                              // bit descriptions
    Uint16  In:1;                                        // 0 Input value of CAN_RX pin 
    Uint16  rsvd1:2;                                     // 2:1 Reserved 
    Uint16  Func:1;                                      // 3 Functionality of CAN_RX pin 
    Uint16  rsvd2:12;                                    // 15:4 Reserved 
    Uint16  rsvd3:16;                                    // 31:16 Reserved 
};

union CAN_IO_CTL_RX_REG {
    Uint32  all;  
    struct  CAN_IO_CTL_RX_BITS  bit;  
};

struct DCAN_REGS {
    union   CAN_CTL_REG             CAN_CTL;             // CAN Control Register 
    Uint16                          rsvd1[2];            // Reserved 
    union   CAN_ES_REG              CAN_ES;              // Error and Status Register 
    Uint16                          rsvd2[2];            // Reserved 
    union   CAN_ERRC_REG            CAN_ERRC;            // Error Counter Register 
    Uint16                          rsvd3[2];            // Reserved 
    union   CAN_BTR_REG             CAN_BTR;             // Bit Timing Register 
    Uint16                          rsvd4[2];            // Reserved 
    union   CAN_INT_REG             CAN_INT;             // Interrupt Register 
    Uint16                          rsvd5[2];            // Reserved 
    union   CAN_TEST_REG            CAN_TEST;            // Test Register 
    Uint16                          rsvd6[6];            // Reserved 
    union   CAN_PERR_REG            CAN_PERR;            // CAN Parity Error Code Register 
    Uint16                          rsvd7[2];            // Reserved 
    union   CAN_REL_REG             CAN_REL;             // CAN Core Release Register 
    Uint16                          rsvd8[2];            // Reserved 
    union   CAN_ECCDIAG_REG         CAN_ECCDIAG;         // CAN ECC Diagnostic Register 
    Uint16                          rsvd9[2];            // Reserved 
    union   CAN_ECCDIAG_STAT_REG    CAN_ECCDIAG_STAT;    // CAN ECC Diagnostic Status Register 
    Uint16                          rsvd10[22];          // Reserved 
    union   CAN_RAM_INIT_REG        CAN_RAM_INIT;        // CAN RAM Initialization Register 
    Uint16                          rsvd11[14];          // Reserved 
    union   CAN_GLB_INT_EN_REG      CAN_GLB_INT_EN;      // CAN Global Interrupt Enable Register 
    Uint16                          rsvd12[2];           // Reserved 
    union   CAN_GLB_INT_FLG_REG     CAN_GLB_INT_FLG;     // CAN Global Interrupt Flag Register 
    Uint16                          rsvd13[2];           // Reserved 
    union   CAN_GLB_INT_CLR_REG     CAN_GLB_INT_CLR;     // CAN Global Interrupt Clear Register 
    Uint16                          rsvd14[38];          // Reserved 
    Uint32                          CAN_ABOTR;           // Auto-Bus-On Time Register 
    Uint16                          rsvd15[2];           // Reserved 
    union   CAN_TXRQ_X_REG          CAN_TXRQ_X;          // CAN Transmission Request X Register 
    Uint16                          rsvd16[2];           // Reserved 
    Uint32                          CAN_TXRQ_21;         // CAN Transmission Request 2_1 Register 
    Uint16                          rsvd17[14];          // Reserved 
    union   CAN_NDAT_X_REG          CAN_NDAT_X;          // CAN New Data X Register 
    Uint16                          rsvd18[2];           // Reserved 
    Uint32                          CAN_NDAT_21;         // CAN New Data 2_1 Register 
    Uint16                          rsvd19[14];          // Reserved 
    union   CAN_IPEN_X_REG          CAN_IPEN_X;          // CAN Interrupt Pending X Register 
    Uint16                          rsvd20[2];           // Reserved 
    Uint32                          CAN_IPEN_21;         // CAN Interrupt Pending 2_1 Register 
    Uint16                          rsvd21[14];          // Reserved 
    union   CAN_MVAL_X_REG          CAN_MVAL_X;          // CAN Message Valid X Register 
    Uint16                          rsvd22[2];           // Reserved 
    Uint32                          CAN_MVAL_21;         // CAN Message Valid 2_1 Register 
    Uint16                          rsvd23[18];          // Reserved 
    Uint32                          CAN_IP_MUX21;        // CAN Interrupt Multiplexer 2_1 Register 
    Uint16                          rsvd24[38];          // Reserved 
    union   CAN_IF1CMD_REG          CAN_IF1CMD;          // IF1 Command Register 
    Uint16                          rsvd25[2];           // Reserved 
    union   CAN_IF1MSK_REG          CAN_IF1MSK;          // IF1 Mask Register 
    Uint16                          rsvd26[2];           // Reserved 
    union   CAN_IF1ARB_REG          CAN_IF1ARB;          // IF1 Arbitration Register 
    Uint16                          rsvd27[2];           // Reserved 
    union   CAN_IF1MCTL_REG         CAN_IF1MCTL;         // IF1 Message Control Register 
    Uint16                          rsvd28[2];           // Reserved 
    union   CAN_IF1DATA_REG         CAN_IF1DATA;         // IF1 Data A Register 
    Uint16                          rsvd29[2];           // Reserved 
    union   CAN_IF1DATB_REG         CAN_IF1DATB;         // IF1 Data B Register 
    Uint16                          rsvd30[10];          // Reserved 
    union   CAN_IF2CMD_REG          CAN_IF2CMD;          // IF2 Command Register 
    Uint16                          rsvd31[2];           // Reserved 
    union   CAN_IF2MSK_REG          CAN_IF2MSK;          // IF2 Mask Register 
    Uint16                          rsvd32[2];           // Reserved 
    union   CAN_IF2ARB_REG          CAN_IF2ARB;          // IF2 Arbitration Register 
    Uint16                          rsvd33[2];           // Reserved 
    union   CAN_IF2MCTL_REG         CAN_IF2MCTL;         // IF2 Message Control Register 
    Uint16                          rsvd34[2];           // Reserved 
    union   CAN_IF2DATA_REG         CAN_IF2DATA;         // IF2 Data A Register 
    Uint16                          rsvd35[2];           // Reserved 
    union   CAN_IF2DATB_REG         CAN_IF2DATB;         // IF2 Data B Register 
    Uint16                          rsvd36[10];          // Reserved 
    union   CAN_IF3OBS_REG          CAN_IF3OBS;          // IF3 Observation Register 
    Uint16                          rsvd37[2];           // Reserved 
    union   CAN_IF3MSK_REG          CAN_IF3MSK;          // IF3 Mask Register 
    Uint16                          rsvd38[2];           // Reserved 
    union   CAN_IF3ARB_REG          CAN_IF3ARB;          // IF3 Arbitration Register 
    Uint16                          rsvd39[2];           // Reserved 
    union   CAN_IF3MCTL_REG         CAN_IF3MCTL;         // IF3 Message Control Register 
    Uint16                          rsvd40[2];           // Reserved 
    union   CAN_IF3DATA_REG         CAN_IF3DATA;         // IF3 Data A Register 
    Uint16                          rsvd41[2];           // Reserved 
    union   CAN_IF3DATB_REG         CAN_IF3DATB;         // IF3 Data B Register 
    Uint16                          rsvd42[10];          // Reserved 
    Uint32                          CAN_IF3UPD;          // IF3 Update Enable Register 
    Uint16                          rsvd43[126];         // Reserved 
    union   CAN_IO_CTL_TX_REG       CAN_IO_CTL_TX;       // CAN TX I/O Control Register 
    Uint16                          rsvd44[2];           // Reserved 
    union   CAN_IO_CTL_RX_REG       CAN_IO_CTL_RX;       // CAN RX I/O Control Register 
    Uint16                          rsvd45[26];          // Reserved 
};

//---------------------------------------------------------------------------
// Dcan External References & Function Declarations:
//

extern volatile struct DCAN_REGS DcanaRegs;
extern volatile struct DCAN_REGS DcanbRegs;

#ifdef __cplusplus
}
#endif                                                   /* extern "C" */


#endif                                                   // end of F2837x_DCAN_H definition
//===========================================================================
// End of file.
//===========================================================================
