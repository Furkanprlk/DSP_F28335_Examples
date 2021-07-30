//###############################################################################
//
// FILE:   F2837x_Dcan_defines.h
//
// TITLE:  Common defines used in DCAN Test Cases
//		   Most of these map legacy Sonata naming to the new public define names
//
//###############################################################################
// $TI Release	: 
// $Release Date	: 
//###############################################################################

#ifndef F2837x_DCAN_DEFINES_H
#define F2837x_DCAN_DEFINES_H

#ifdef __cplusplus
extern "C" {
#endif

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//Note:
//Write Mask to stop writing to control critical bit
//Read  Mask for the registers which has undefined bits
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++



//===========================================================================
//	MACROS
//===========================================================================

// Reset Values
#define DCAN_RESET_VALUE_ZERO			0x00000000
#define DCAN_CTL_RESET_VALUE			0x00001401
#define DCAN_ES_RESET_VALUE				0x00000007
#define DCAN_BTR_RESET_VALUE			0x00002301
#define DCAN_REL_RESET_VALUE			0xA3170504
#define DCAN_RAM_INIT_RESET_VALUE		0x00000005
#define DCAN_IF_CMD_RESET_VALUE			0x00000001
#define DCAN_IF_MASK_RESET_VALUE		0xFFFFFFFF
///////////////////////////////////////////////////////////////////////////////

// Register value when Peripheral Clock is Disabled
#define DCAN_MODULE_CLK_DISABLE_VALUE	0x00000000

// Bit field defination of CAN_CTL register.
#define DCAN_CTL_INIT		0x00000001  // Initialization
#define DCAN_CTL_IE0        0x00000002  // Interrupt Enable 0
#define DCAN_CTL_SIE        0x00000004  // Status Interrupt Enable
#define DCAN_CTL_EIE        0x00000008  // Error Interrupt Enable
#define DCAN_CTL_DAR        0x00000020  // Disable Automatic-Retransmission
#define DCAN_CTL_CCE        0x00000040  // Configuration Change Enable
#define DCAN_CTL_TEST       0x00000080  // Test Mode Enable
#define DCAN_CTL_IDS		0x00000100	// Interruption Debug Support Enable
#define DCAN_CTL_ABO		0x00000200	// Auto-Bus On Enable
#define DCAN_CTL_PMD_S		10
#define DCAN_CTL_PMD_M		0x00003C00	// Parity/SECDED Enable
#define DCAN_CTL_SWR		0x00008000	// Software Reset Enable
#define DCAN_CTL_INITDBG	0x00010000	// Debug Mode Status
#define DCAN_CTL_IE1		0x00020000	// Interrupt Enable 1
#define DCAN_CTL_PDR		0x01000000	// Power Down Mode Request
#define DCAN_CTL_WUBA		0x02000000	// Wake Up on Bus Activity
///////////////////////////////////////////////////////////////////////////////////


// Bit field defination of CAN_IF1_CMD register.
#define DCAN_IF1_CMD_MESSNUM_S		0
#define DCAN_IF1_CMD_MESSNUM_M		0x000000FF	// Message Number
#define DCAN_IF1_CMD_BUSY			0x00008000	// Busy Flag
#define DCAN_IF1_CMD_DATAB			0x00010000	// Access Data B
#define DCAN_IF1_CMD_DATAA			0x00020000	// Access Data A
#define DCAN_IF1_CMD_TXRQSTNDAT		0x00040000	// Transmission Request Bit
#define DCAN_IF1_CMD_CLRINTPND		0x00080000	// Clear Interrupt Pending Bit
#define DCAN_IF1_CMD_CONTROL		0x00100000	// Access Control Bits
#define DCAN_IF1_CMD_ARB			0x00200000	// Access Arbitration Bits
#define DCAN_IF1_CMD_MASK			0x00400000	// Access Mask Bits
#define DCAN_IF1_CMD_WR_RD			0x00800000	// Write and Read
////////////////////////////////////////////////////////////////////////////////////

// Bit field defination of CAN_IF2_CMD register.
#define DCAN_IF2_CMD_MESSNUM_S		0
#define DCAN_IF2_CMD_MESSNUM_M		0x000000FF	// Message Number
#define DCAN_IF2_CMD_BUSY			0x00008000	// Busy Flag
#define DCAN_IF2_CMD_DATAB			0x00010000	// Access Data B
#define DCAN_IF2_CMD_DATAA			0x00020000	// Access Data A
#define DCAN_IF2_CMD_TXRQSTNDAT		0x00040000	// Transmission Request Bit
#define DCAN_IF2_CMD_CLRINTPND		0x00080000	// Clear Interrupt Pending Bit
#define DCAN_IF2_CMD_CONTROL		0x00100000	// Access Control Bits
#define DCAN_IF2_CMD_ARB			0x00200000	// Access Arbitration Bits
#define DCAN_IF2_CMD_MASK			0x00400000	// Access Mask Bits
#define DCAN_IF2_CMD_WR_RD			0x00800000	// Write and Read
////////////////////////////////////////////////////////////////////////////////////



#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F2837x_DCAN_DEFINES_H

//===========================================================================
// End of file.
//===========================================================================
