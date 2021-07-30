// TI File $Revision: /main/1 $
// Checkin $Date: January 22, 2009   16:46:57 $
//###########################################################################
//
// FILE:   DSP2803x_LIN.h
//
// TITLE:  DSP2803x Device LIN Register Definitions.
//
//###########################################################################
// $TI Release: TMS320x2803x Boot ROM V1.0 $
// $Release Date: January 22, 2009 $
//###########################################################################

#ifndef DSP2803x_LIN_H
#define DSP2803x_LIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------------------------- */
/* LIN Registers                                       */
/* ----------------------------------------------------*/

/* Global Control Register 0 (SCIGCR0) bit definitions */
struct SCIGCR0_BITS {      // bit    description
    Uint16  RESET:1;       // 0      LIN Module reset bit
    Uint16  rsvd1:15;      // 15:1   reserved
	Uint16  rsvd2:16;      // 31:16  reserved
};

/* Allow access to the bit fields or entire register */
union SCIGCR0_REG {
   Uint32               all;
   struct SCIGCR0_BITS  bit;
};

/* Global Control Register 1 (SCIGCR1) bit definitions */
struct SCIGCR1_BITS {      // bit    description
    Uint16  COMMMODE:1;    // 0      SCI/LIN communications mode bit
    Uint16  TIMINGMODE:1;  // 1      SCI timing mode bit
    Uint16  PARITYENA:1;   // 2      Parity enable
    Uint16  PARITY:1;      // 3      SCI parity odd/even selection
    Uint16  STOP:1;        // 4      SCI number of stop bits
    Uint16  CLOCK:1;       // 5      SCI internal clock enable
    Uint16  LINMODE:1;     // 6      LIN Mode enable/disable
    Uint16  SWnRST:1;      // 7      Software reset
    Uint16  SLEEP:1;       // 8      SCI sleep (SCI compatibility mode)
    Uint16  ADAPT:1;       // 9      Automatic baudrate adjustment control(LIN mode)
    Uint16  MBUFMODE:1;    // 10     Multi-buffer mode
    Uint16  CTYPE:1;       // 11     Checksum type (LIN mode)
    Uint16  HGENCTRL:1;    // 12     Mask filtering comparison control (LIN mode)
    Uint16  STOPEXTFRAME:1;// 13     Stop extended frame communication (LIN mode)
    Uint16  rsvd1:2;       // 15:14  Reserved
    Uint16  LOOPBACK:1;    // 16     Digital loopback mode
    Uint16  CONT:1;        // 17     Continue on suspend
    Uint16  rsvd2:6;       // 23:18  reserved
    Uint16  RXENA:1;       // 24     SCI mode receiver enable
    Uint16  TXENA:1;       // 25     SCI mode transmitter enable
    Uint16  rsvd3:6;       // 31:26  reserved
};

/* Allow access to the bit fields or entire register */
union SCIGCR1_REG {
   Uint32               all;
   struct SCIGCR1_BITS  bit;
};

/* Global Control Register 2 (SCIGCR2) bit definitions */
struct SCIGCR2_BITS {      // bit    description
    Uint16  POWERDOWN:1;   // 0      Low-power mode PowerDown bit
    Uint16  rsvd1:7;       // 7:1    reserved
    Uint16  GENWU:1;       // 8      Generate Wakeup
    Uint16  rsvd2:7;       // 15:9   reserved
    Uint16  SC:1;          // 16     Send Checksum (LIN mode)
    Uint16  CC:1;          // 17     Compare Checksum (LIN mode)
    Uint16  rsvd3:14;      // 31:18  reserved
};

/* Allow access to the bit fields or entire register */
union SCIGCR2_REG {
   Uint32               all;
   struct SCIGCR2_BITS  bit;
};

/* SCI Set Interrupt Register (SCISETINT) bit definitions */
struct SCISETINT_BITS {      // bit    description
    Uint16  SETBRKDTINT:1;   // 0      Set Break-detect Interrupt (SCI compatible mode)
    Uint16  SETWAKEUPINT:1;  // 1      Set Wake-up Interrupt
    Uint16  rsvd1:2;         // 3:2    reserved
    Uint16  SETTIMEOUTINT:1; // 4      Set Timeout Interrupt (LIN only)
    Uint16  rsvd2:1;         // 5      reserved
    Uint16  SETTOAWUSINT:1;  // 6      Set Timeout After Wakeup Signal Interrupt (LIN only)
    Uint16  SETTOA3WUSINT:1; // 7      Set Timeout After 3 Wakeup Signals Interrupt (LIN only)
    Uint16  SETTXINT:1;      // 8      Set Transmitter Interrupt
    Uint16  SETRXINT:1;      // 9      Receiver Interrupt Enable
    Uint16  rsvd3:3;         // 12:10  reserved
    Uint16  SETIDINT:1;      // 13     Set Identifier Interrupt (LIN only)
    Uint16  rsvd4:2;         // 15:14  reserved
	Uint16  rsvd5:2;         // 17:16  reserved
    Uint16  SETRXDMAALL:1;   // 18     Address Frame Interrupt
    Uint16  rsvd6:5;         // 23:19  reserved
    Uint16  SETPEINT:1;      // 24     Set Parity Interrupt
    Uint16  SETOEINT:1;      // 25     Set Overrun-Error Interrupt
    Uint16  SETFEINT:1;      // 26     Set Framing-Error Interrupt
    Uint16  SETNREINT:1;     // 27     Set No-Response-Error Interrupt (LIN only)
    Uint16  SETISFEINT:1;    // 28     Set Inconsistent-Synch-Field-Error Interrupt (LIN only)
    Uint16  SETCEINT:1;      // 29     Set Checksum-error Interrupt (LIN only)
    Uint16  SETPBEINT:1;     // 30     Set Physical Bus Error Interrupt (LIN only)
    Uint16  SETBEINT:1;      // 31     Set Bit Error Interrupt (LIN only)
};

/* Allow access to the bit fields or entire register */
union SCISETINT_REG {
   Uint32                 all;
   struct SCISETINT_BITS  bit;
};

/* SCI Clear Interrupt (SCICLEARINT) Register bit definitions */
struct SCICLEARINT_BITS {    // bit    description
    Uint16  CLRBRKDTINT:1;   // 0      Clear Break-detect Interrupt (SCI compatible mode)
    Uint16  CLRWAKEUPINT:1;  // 1      Clear Wake-up Interrupt
    Uint16  rsvd1:2;         // 3:2    reserved
    Uint16  CLRTIMEOUTINT:1; // 4      Clear Timeout Interrupt (LIN only)
    Uint16  rsvd2:1;         // 5      reserved
    Uint16  CLRTOAWUSINT:1;  // 6      Clear Timeout After Wakeup Signal Interrupt (LIN only)
    Uint16  CLRTOA3WUSINT:1; // 7      Clear Timeout After 3 Wakeup Signals Interrupt (LIN only)
    Uint16  CLRTXINT:1;      // 8      Clear Transmitter Interrupt
    Uint16  CLRRXINT:1;      // 9      Clear Receiver Interrupt
    Uint16  rsvd3:3;         // 12:10  reserved
    Uint16  CLRIDINT:1;      // 13     Clear Identifier Interrupt (LIN only)
    Uint16  rsvd4:2;         // 15:14  reserved
	Uint16  rsvd5:2;         // 17:16  reserved
    Uint16  CLRRXDMAALL:1;   // 18     Clear Address Frame Interrupt
    Uint16  rsvd6:5;         // 23:19  reserved
    Uint16  CLRPEINT:1;      // 24     Clear Parity Interrupt
    Uint16  CLROEINT:1;      // 25     Clear Overrun-Error Interrupt
    Uint16  CLRFEINT:1;      // 26     Clear Framing-Error Interrupt
    Uint16  CLRNREINT:1;     // 27     Clear No-Response-Error Interrupt (LIN only)
    Uint16  CLRISFEINT:1;    // 28     Clear Inconsistent-Synch-Field-Error Interrupt (LIN only)
    Uint16  CLRCEINT:1;      // 29     Clear Checksum-error Interrupt (LIN only)
    Uint16  CLRPBEINT:1;     // 30     Clear Physical Bus Error Interrupt (LIN only)
    Uint16  CLRBEINT:1;      // 31     Clear Bit Error Interrupt (LIN only)
};

/* Allow access to the bit fields or entire register */
union SCICLEARINT_REG {
   Uint32                   all;
   struct SCICLEARINT_BITS  bit;
};

/* SCI Set Interrupt Level Register (SCISETINTLVL) bit definitions */
struct SCISETINTLVL_BITS {      // bit    description
    Uint16  SETBRKDTINTLVL:1;   // 0      Set Break-detect Interrupt Level (SCI compatible mode)
    Uint16  SETWAKEUPINTLVL:1;  // 1      Set Wake-up Interrupt Level
    Uint16  rsvd1:2;            // 3:2    reserved
    Uint16  SETTIMEOUTINTLVL:1; // 4      Set Timeout Interrupt Level (LIN only)
    Uint16  rsvd2:1;            // 5      reserved
    Uint16  SETTOAWUSINTLVL:1;  // 6      Set Timeout After Wakeup Signal Interrupt Level (LIN only)
    Uint16  SETTOA3WUSINTLVL:1; // 7      Set Timeout After 3 Wakeup Signals Interrupt Level (LIN only)
    Uint16  SETTXINTLVL:1;      // 8      Set Transmitter Interrupt Level
    Uint16  SETRXINTOVO:1;      // 9      Receiver Interrupt Enable Level
    Uint16  rsvd3:3;            // 12:10  reserved
    Uint16  SETIDINTLVL:1;      // 13     Set Identifier Interrupt Level (LIN only)
    Uint16  rsvd4:2;            // 15:14  reserved
	Uint16  rsvd5:2;            // 17:16  reserved
    Uint16  SETRXDMAALLLVL:1;   // 18     Address Frame Interrupt Level
    Uint16  rsvd6:5;            // 23:19  reserved
    Uint16  SETPEINTLVL:1;      // 24     Set Parity Interrupt Level
    Uint16  SETOEINTLVL:1;      // 25     Set Overrun-Error Interrupt Level
    Uint16  SETFEINTLVL:1;      // 26     Set Framing-Error Interrupt Level
    Uint16  SETNREINTLVL:1;     // 27     Set No-Response-Error Interrupt Level (LIN only)
    Uint16  SETISFEINTLVL:1;    // 28     Set Inconsistent-Synch-Field-Error Interrupt Level (LIN only)
    Uint16  SETCEINTLVL:1;      // 29     Set Checksum-error Interrupt Level (LIN only)
    Uint16  SETPBEINTLVL:1;     // 30     Set Physical Bus Error Interrupt Level (LIN only)
    Uint16  SETBEINTLVL:1;      // 31     Set Bit Error Interrupt Level(LIN only)
};

/* Allow access to the bit fields or entire register */
union SCISETINTLVL_REG {
   Uint32                    all;
   struct SCISETINTLVL_BITS  bit;
};

/* SCI Clear Interrupt Level (SCICLEARINTLVL) Register bit definitions */
struct SCICLEARINTLVL_BITS {    // bit    description
    Uint16  CLRBRKDTINTLVL:1;   // 0      Clear Break-detect Interrupt Level (SCI compatible mode)
    Uint16  CLRWAKEUPINTLVL:1;  // 1      Clear Wake-up Interrupt Level
    Uint16  rsvd1:2;            // 3:2    reserved
    Uint16  CLRTIMEOUTINTLVL:1; // 4      Clear Timeout Interrupt Level (LIN only)
    Uint16  rsvd2:1;            // 5      reserved
    Uint16  CLRTOAWUSINTLVL:1;  // 6      Clear Timeout After Wakeup Signal Interrupt Level (LIN only)
    Uint16  CLRTOA3WUSINTLVL:1; // 7      Clear Timeout After 3 Wakeup Signals Interrupt Level (LIN only)
    Uint16  CLRTXINTLVL:1;      // 8      Clear Transmitter Interrupt Level
    Uint16  CLRRXINTLVL:1;      // 9      Clear Receiver Interrupt Level
    Uint16  rsvd3:3;            // 12:10  reserved
    Uint16  CLRIDINTLVL:1;      // 13     Clear Identifier Interrupt Level (LIN only)
    Uint16  rsvd4:2;            // 15:14  reserved
	Uint16  rsvd5:2;            // 17:16  reserved
    Uint16  CLRRXDMAALLLVL:1;   // 18     Clear Address Frame Interrupt Level
    Uint16  rsvd6:5;            // 23:19  reserved
    Uint16  CLRPEINTLVL:1;      // 24     Clear Parity Interrupt Level
    Uint16  CLROEINTLVL:1;      // 25     Clear Overrun-Error Interrupt Level
    Uint16  CLRFEINTLVL:1;      // 26     Clear Framing-Error Interrupt Level
    Uint16  CLRNREINTLVL:1;     // 27     Clear No-Response-Error Interrupt Level (LIN only)
    Uint16  CLRISFEINTLVL:1;    // 28     Clear Inconsistent-Synch-Field-Error Interrupt Level (LIN only)
    Uint16  CLRCEINTLVL:1;      // 29     Clear Checksum-error Interrupt Level (LIN only)
    Uint16  CLRPBEINTLVL:1;     // 30     Clear Physical Bus Error Interrupt Level (LIN only)
    Uint16  CLRBEINTLVL:1;      // 31     Clear Bit Error Interrupt Level (LIN only)
};

/* Allow access to the bit fields or entire register */
union SCICLEARINTLVL_REG {
   Uint32                      all;
   struct SCICLEARINTLVL_BITS  bit;
};

/* SCI Flags Register (SCIFLR) bit definitions */
struct SCIFLR_BITS {            // bit    description
    Uint16  BRKDT:1;            // 0      Break-detect Flag (SCI compatible mode)
    Uint16  WAKEUP:1;           // 1      Wake-up Flag
    Uint16  IDLE:1;             // 2      SCI receiver in idle state (SCI compatible mode)
    Uint16  BUSY:1;             // 3      Busy Flag
    Uint16  TIMEOUT:1;          // 4      LIN Bus IDLE timeout Flag (LIN only)
    Uint16  rsvd2:1;            // 5      reserved
    Uint16  TOAWUS:1;           // 6      Timeout After Wakeup Signal Flag (LIN only)
    Uint16  TOA3WUS:1;          // 7      Timeout After 3 Wakeup Signals Flag (LIN only)
    Uint16  TXRDY:1;            // 8      Transmitter Buffer Ready Flag
    Uint16  RXRDY:1;            // 9      Receiver Buffer Ready Flag
    Uint16  TXWAKE:1;	        // 10     SCI Transmitter Wakeup Method Select
    Uint16  TXEMPTY:1;          // 11     Transmitter Empty Clag
    Uint16  RXWAKE:1;           // 12     Receiver Wakeup Detect Flag
    Uint16  IDTXFLAG:1;         // 13     Identifier On Transmit Flag (LIN only)
    Uint16  IDRXFLAG:1;         // 14     Identifier on Receive Flag
	Uint16	rsvd3:1;			// 15
    Uint16  rsvd4:8;            // 23:16  reserved
    Uint16  PE:1;               // 24     Parity Error Flag
    Uint16  OE:1;               // 25     Overrun Error Flag
    Uint16  FE:1;               // 26     Framing Error Flag
    Uint16  NRE:1;              // 27     No-Response Error Flag (LIN only)
    Uint16  ISFE:1;             // 28     Inconsistent Synch Field Error Flag (LIN only)
    Uint16  CE:1;               // 29     Checksum Error Flag (LIN only)
    Uint16  PBE:1;              // 30     Physical Bus Error Flag (LIN only)
    Uint16  BE:1;               // 31     Bit Error Flag (LIN only)
};

/* Allow access to the bit fields or entire register */
union SCIFLR_REG {
   Uint32             all;
   struct SCIFLR_BITS  bit;
};

/* SCI Interrupt Vector Offset 0 (SCIINTVECT0) bit definitions */
struct SCIINTVECT0_BITS {      // bit    description
    Uint16  INTVECT0:5;        // 4:0    Interrupt vector offset for INT0
    Uint16  rsvd1:11;          // 15:5   reserved
	Uint16  rsvd2:16;          // 31:16  reserved
};

/* Allow access to the bit fields or entire register */
union SCIINTVECT0_REG {
   Uint32               all;
   struct SCIINTVECT0_BITS  bit;
};

/* SCI Interrupt Vector Offset 1 (SCIINTVECT1) bit definitions */
struct SCIINTVECT1_BITS {      // bit    description
    Uint16  INTVECT1:5;        // 4:0    Interrupt vector offset for INT1
    Uint16  rsvd1:11;          // 15:5   reserved
	Uint16  rsvd2:16;          // 31:16  reserved
};

/* Allow access to the bit fields or entire register */
union SCIINTVECT1_REG {
   Uint32               all;
   struct SCIINTVECT1_BITS  bit;
};

/* SCI Format Control Register (SCIFORMAT) bit definitions */
struct SCIFORMAT_BITS {        // bit    description
    Uint16  CHAR:3;            // 2:0    Character Length Control Bits
    Uint16  rsvd1:13;          // 15:3   reserved
    Uint16  LENGTH:3;          // 18:16  Frame Length Control Bits
    Uint16  rsvd2:13;          // 31:19  reserved
};

/* Allow access to the bit fields or entire register */
union SCIFORMAT_REG {
   Uint32                 all;
   struct SCIFORMAT_BITS  bit;
};

/* Baud Rate Selection Register (BRSR) bit definitions */
struct BRSR_BITS {             // bit    description
	Uint16  SCI_LIN_PSL :16;   // 15:0   SCI/LIN Prescaler Low
	Uint16  SCILIN_PSH :8;     // 23:16  SCI/LIN Prescaler High
    Uint16  M:4;               // 27:24  SCI/LIN Fractional Divider Selection
    Uint16  U:3;               // 30:28  SCI/LIN Super Fractional Divider Selection
    Uint16  rsvd1:1;           // 31     reserved
};

/* Allow access to the bit fields or entire register */
union BRSR_REG {
   Uint32               all;
   struct BRSR_BITS     bit;
};

/* SCI Pin I/O Control Register 2 (SCIPIO2) bit definitions */
struct SCIPIO2_BITS {          // bit    description
    Uint16  RXIN:1;            // 0      SCIRX pin value
    Uint16  TXIN:1;            // 1      SCITX pin value
    Uint16  rsvd2:14;          // 15:2   reserved
	Uint16  rsvd3:16;          // 31:16  reserved
};

/* Allow access to the bit fields or entire register */
union SCIPIO2_REG {
   Uint32               all;
   struct SCIPIO2_BITS  bit;
};


/* LIN Compare Register (LINCOMP) bit definitions */
struct LINCOMP_BITS {          // bit    description
    Uint16  SBREAK:3;          // 2:0    Synch Break Extend
    Uint16  rsvd1:5;           // 7:3    reserved
    Uint16  SDEL:2;            // 9:8    Sync Delimiter Compare
	Uint16  rsvd2:6;           // 15:10  reserved
	Uint16  rsvd3:16;          // 31:16  reserved
};

/* Allow access to the bit fields or entire register */
union LINCOMP_REG {
   Uint32               all;
   struct LINCOMP_BITS  bit;
};


/* LIN Receive Data 0 Register (LINRD0) bit definitions */
struct LINRD0_BITS {           // bit    description
    Uint16  RD3:8;             // 7:0    Receive Buffer 3
    Uint16  RD2:8;             // 15:8   Receive Buffer 2
    Uint16  RD1:8;             // 23:16  Receive Buffer 1
    Uint16  RD0:8;             // 31:24  Receive Buffer 0
};

/* Allow access to the bit fields or entire register */
union LINRD0_REG {
   Uint32              all;
   struct LINRD0_BITS  bit;
};

/* LIN Receive Data 1 Register (LINRD1) bit definitions */
struct LINRD1_BITS {           // bit    description
    Uint16  RD7:8;             // 7:0    Receive Buffer 7
    Uint16  RD6:8;             // 15:8   Receive Buffer 6
    Uint16  RD5:8;             // 23:16  Receive Buffer 5
    Uint16  RD4:8;             // 31:24  Receive Buffer 4
};

/* Allow access to the bit fields or entire register */
union LINRD1_REG {
   Uint32              all;
   struct LINRD1_BITS  bit;
};

/* LIN Acceptance Mask Register (LINMASK) bit definitions */
struct LINMASK_BITS {          // bit    description
    Uint16  TXIDMASK:8;        // 7:0    TX ID Mask bits (LIN only)
    Uint16  rsvd1:8;           // 15:8   reserved
    Uint16  RXIDMASK:8;        // 23:16  RX ID Mask bits (LIN only)
    Uint16  rsvd2:8;           // 31:24  reserved
};

/* Allow access to the bit fields or entire register */
union LINMASK_REG {
   Uint32               all;
   struct LINMASK_BITS  bit;
};

/* LIN ID Register (LINID) bit definitions */
struct LINID_BITS {            // bit    description
    Uint16  IDBYTE:8;          // 7:0    LIN message ID (LIN only)
    Uint16  IDSLAVETASKBYTE:8; // 15:8   Received ID comparison ID (LIN only)
    Uint16  RECEIVEDID:8;      // 23:16  Current Message ID (LIN only)
    Uint16  rsvd1:8;           // 31:24  reserved
};

/* Allow access to the bit fields or entire register */
union LINID_REG {
   Uint32             all;
   struct LINID_BITS  bit;
};

/* LIN Transmit Data 0 Register (LINTD0) bit definitions */
struct LINTD0_BITS {           // bit    description
    Uint16  TD3:8;             // 7:0    Transmit Buffer 3
    Uint16  TD2:8;             // 15:8   Transmit Buffer 2
    Uint16  TD1:8;             // 23:16  Transmit Buffer 1
    Uint16  TD0:8;             // 31:24  Transmit Buffer 0
};

/* Allow access to the bit fields or entire register */
union LINTD0_REG {
   Uint32              all;
   struct LINTD0_BITS  bit;
};

/* LIN Transmit Data 1 Register (LINTD1) bit definitions */
struct LINTD1_BITS {           // bit    description
    Uint16  TD7:8;             // 7:0    Transmit Buffer 7
    Uint16  TD6:8;             // 15:8   Transmit Buffer 6
    Uint16  TD5:8;             // 23:16  Transmit Buffer 5
    Uint16  TD4:8;             // 31:24  Transmit Buffer 4
};

/* Allow access to the bit fields or entire register */
union LINTD1_REG {
   Uint32               all;
   struct LINTD1_BITS   bit;
};

/* IODFT for LIN (IODFTCTRL) bit definitions */
struct IODFTCTRL_BITS {        // bit    description
    Uint16  RXPENA:1;          // 0      Analog Loopback Via Receive Pin Enable
    Uint16  LPBENA:1;          // 1      Module Loopback Enable
    Uint16  rsvd1:6;           // 7:2    reserved
    Uint16  IODFTENA:4;        // 11:8   IO DFT Enable Key
    Uint16  rsvd2:4;           // 15:12  Reserved
    Uint16  TXSHIFT:3;         // 18:16  Transmit Delay Shift
    Uint16  PINSAMPLEMASK:2;   // 20:19  TX Pin Sample Mask
    Uint16  rsvd3:3;           // 23:21  Reserved
    Uint16  BRKDTERRENA:1;     // 24     Break Detect Error Enable (SCI compatibility mode)
    Uint16  PERRENA:1;         // 25     Parity Error Enable (SCI compatibility mode)
    Uint16  FERRENA:1;         // 26     Frame Error Enable (SCI compatibility mode)
    Uint16  rsvd:1;            // 27     reserved
    Uint16  ISFERRENA:1;       // 28     Inconsistent Synch Field Error Enable (LIN mode)
    Uint16  CERRENA:1;         // 29     Checksum Error Enable(LIN mode)
    Uint16  PBERRENA:1;        // 30     Physical Bus Error Enable (LIN mode)
    Uint16  BERRENA:1;         // 31     Bit Error Enable (LIN mode)
};

/* Allow access to the bit fields or entire register */
union IODFTCTRL_REG {
   Uint32                 all;
   struct IODFTCTRL_BITS  bit;
};


/**************************************/
/* LIN register file */
/**************************************/

struct LIN_REGS {
    union   SCIGCR0_REG         SCIGCR0;            // Global Control Register 0
	union	SCIGCR1_REG		    SCIGCR1;		    // Global Control Register 1
	union	SCIGCR2_REG		    SCIGCR2;		    // Global Control Register 2
	union	SCISETINT_REG		SCISETINT;		    // Interrupt Enable Register
	union	SCICLEARINT_REG		SCICLEARINT;		// Interrupt Disable Register
	union	SCISETINTLVL_REG	SCISETINTLVL;		// Set Interrupt Level Register
	union	SCICLEARINTLVL_REG	SCICLEARINTLVL;		// Clear Interrupt Level Register
	union	SCIFLR_REG		    SCIFLR;		        // Flag Register
	union	SCIINTVECT0_REG		SCIINTVECT0;		// Interrupt Vector Offset Register 0
	union	SCIINTVECT1_REG	 	SCIINTVECT1;	 	// Interrupt Vector Offset Register 1
	union	SCIFORMAT_REG		SCIFORMAT;		    // Length Control Register
	union	BRSR_REG			BRSR;				// Baud Rate Selection Register
	Uint32          			SCIED;				// Emulation buffer Register
	Uint32          			SCIRD;				// Receiver data buffer Register
	Uint32          			SCITD;				// Transmit data buffer Register
	Uint32                      rsvd1[2];			// reserved
	union	SCIPIO2_REG			SCIPIO2;			// Pin control Register 2
	Uint32                      rsvd2[6];           // reserved
	union	LINCOMP_REG			LINCOMP;		    // Compare register
	union	LINRD0_REG			LINRD0;				// Receive data register 0
	union	LINRD1_REG			LINRD1;				// Receive data register 1
	union	LINMASK_REG			LINMASK;		    // Acceptance mask register
	union	LINID_REG			LINID;				// LIN ID Register
	union	LINTD0_REG			LINTD0;				// Transmit Data Register 0
	union	LINTD1_REG			LINTD1;				// Transmit Data Register 1
	Uint32			            MBRSR;				// Baud Rate Selection Register
	Uint32						rsvd3[4];		    // reserved
	union   IODFTCTRL_REG		IODFTCTRL;			// IODFT for LIN
};

//---------------------------------------------------------------------------
// LIN External References & Function Declarations:
//
extern volatile struct LIN_REGS LinaRegs;

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2803x_LIN.H definition

//===========================================================================
// End of file.
//===========================================================================
