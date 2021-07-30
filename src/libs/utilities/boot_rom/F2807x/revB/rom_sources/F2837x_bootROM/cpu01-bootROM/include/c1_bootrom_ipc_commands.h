// TI File $Revision: /main/1 $
// Checkin $Date: August 13, 2012   11:53:32 $
//###########################################################################
//
// FILE:   c_bootrom_ipc_commands.h
//
// TITLE:  C-BootROM IPC command Definitions.
//
//###########################################################################
// $TI Release: F28M35x Boot ROM V1.0 $
// $Release Date: Oct 21, 2010 $
//###########################################################################


#ifndef C_BOOTROM_IPC_COMMANDS_H_
#define C_BOOTROM_IPC_COMMANDS_H_


/* C1-BootROM health status:
 * The below will be given to user in xTOCIPCDATAR[31:8], in case of an IPC NAK
 * and also always in CTOMBOOTSTS[31:8], whenever boot status is written
 */
#define C1_BOOTROM_START_BOOT               0x00000100          //set during the initialization phase of A-bootROM
#define C1_BOOTROM_IN_FLASH_BOOT            0x00000200
#define C1_BOOTROM_DCSM_INIT_DONE           0x00000400
#define C1_BOOTROM_RESC_HANDLED             0x00000800
#define C1_BOOTROM_HANDLED_HIBRESET         0x00001000          //set if C-BootROM detects an iTRAP
#define C1_BOOTROM_HANDLED_HWBISTRESET      0x00002000          //set if C-BootROM detects an iTRAP
#define C1_BOOTROM_HANDLED_XRSN             0x00004000          //set if C-BootROM detects an iTRAP
#define C1_BOOTROM_HANDLED_POR              0x00008000          //set if C-BootROM detects an iTRAP

#define C1_BOOTROM_IN_AN_ITRAP              0x00020000          //set if C-BootROM detects an iTRAP
#define C1_BOOTROM_IN_C1TOC2_BRANCH         0x00040000          //set if C-BootROM is doing a mtoc branch
#define C1_BOOTROM_GOT_A_PIEMISMATCH        0x00080000          //set if C-BootROM is starting an application after boot
#define C1_BOOTROM_GOT_A_OVF_NMI            0x00100000          //set if C-BootROM is starting an application after boot
#define C1_BOOTROM_GOT_A_CPU2NMIWDRST_NMI   0x00200000          //set if C-BootROM is starting an application after boot
#define C1_BOOTROM_GOT_A_CPU2WDRST_NMI      0x00400000          //set if C-BootROM is starting an application after boot
#define C1_BOOTROM_GOT_A_RL_NMI             0x00800000          //set if C-BootROM is starting an application after boot
#define C1_BOOTROM_GOT_A_SYSDBG_NMI         0x01000000          //set if C-BootROM is starting an application after boot
#define C1_BOOTROM_GOT_A_PIEVECTERR_NMI     0x02000000          //set if C-BootROM is starting an application after boot
#define C1_BOOTROM_GOT_A_C2BISTERR_NMI      0x04000000          //set if C-BootROM is starting an application after boot
#define C1_BOOTROM_GOT_A_C1BISTERR_NMI      0x08000000          //set if C-BootROM is starting an application after boot
#define C1_BOOTROM_GOT_A_FLASH_UNCERR_NMI   0x10000000          //set if C-BootROM is starting an application after boot
#define C1_BOOTROM_GOT_A_RAM_UNCERR_NMI     0x20000000          //set if C-BootROM is starting an application after boot
#define C1_BOOTROM_GOT_A_MCLK_NMI           0x40000000          //set if C-BootROM is starting an application after boot
#define C1_BOOTROM_BOOT_COMPLETE            0x80000000          //set if C-BootROM is starting an application after boot

/* xTOCIPCDATAR[15:0] register values, when Control system NAK's an IPC
 * xTOCIPCDATAR[31:16] register value stores the C-BootROM health status */

#define C1BROM_NAK_STATUS_INVALID_VALUE 						0x00000000				//invalid value or value when not set
#define C1BROM_NAK_STATUS_CMD_NOT_SUPPORTED					0x00000001				//NAK STATUS command not supported
#define C1BROM_NAK_STATUS_CMD_NOT_SET_PROPERLY				0x00000002				//NAK Status command not set properly , for ex: IPC1 set but IPC32 not set
#define C1BROM_NAK_STATUS_ALREADY_BUSY_WITH_YOUR_CMD			0x00000003				//NAK status when master is trying to send a second command before first one could complete
#define C1BROM_NAK_STATUS_CMD_RESULTED_IN_ERROR				0x00000004				//NAK status command execution resulted in an error
#define C1BROM_NAK_STATUS_CMD_CANNOT_BE_EXECUTED_NOW			0x00000005				//NAK status - command cannot be executed now in the current state of bootROM
#define C1BROM_NAK_STATUS_MAX_SUPPRT_VALUE					0x00000006				//one less than this value are valid values


/* C-BootROM uses the below enum values to fill in CTOMIPCCOM register*/

#define C1_BOOTROM_IPC_CTOM_COMMAND_ILLEGAL 								0x00000000		//invalid command value - default value when starting boot
#define C1_BOOTROM_IPC_CTOM_CONTROL_SYSTEM_IN_ITRAP						0xFFFFFFFE		//message tells Master that B.C28x CPU has got an iTRAP, address where iTrap occured will be in IPC ADDR register
#define C1_BOOTROM_IPC_CTOM_PIE_INTERRUPT_NOT_SUPPORTED					0xFFFFFFFD		//message tells Master that B.C28x CPU got a spurious PIE interrupt, intr no. will be in IPCDATAW register
#define C1_BOOTROM_IPC_CTOM_PIE_VECTOR_ADDRESS_MISMATCH					0xFFFFFFFC		//message tells Master that B.C28x CPU got a PIE vector mismatch error
#define C1_BOOTROM_IPC_CTOM_CONTROL_SYSTEM_IN_FLUNCERR					0xFFFFFFFB		//message tells Master that B.C28x CPU got a Flash uncorrectable error
#define C1_BOOTROM_IPC_CTOM_CONTROL_SYSTEM_IN_RAMUNCERR					0xFFFFFFFA		//message tells Master that B.C28x CPU got a RAM uncorrectable error


/*C2TOC1IPC commands
 * Below IPC commands are can be sent from C1BROM to C2BROM
 */

#define C2C1_BROM_IPC_COMMAND_ILLEGAL 			    0x00000000		//illegal command or command not set
#define C2C1_BROM_IPC_SET_BITS_16					0x00000001		//set bits(max. 16 bit wide) in a 16 bit addressable location/register
#define C2C1_BROM_IPC_SET_BITS_32					0x00000002		//set bits(max. 32 bit wide) in a 32 bit addressable location/register
#define C2C1_BROM_IPC_CLEAR_BITS_16				    0x00000003		//clear bits(max. 16 bit wide) in a 16 bit addressable location/register
#define C2C1_BROM_IPC_CLEAR_BITS_32				    0x00000004		//clear bits(max. 32 bit wide) in a 32 bit addressable location/register
#define C2C1_BROM_IPC_DATA_WRITE_16				    0x00000005		//write 16 bit data to a 16 bit addressable location/register
#define C2C1_BROM_IPC_DATA_WRITE_32				    0x00000006		//write 32 bit data to a 32 bit addressable location/register
#define C2C1_BROM_IPC_DATA_READ_16				    0x00000007		//read 16 bit data from a 16 bit addressable location/register
#define C2C1_BROM_IPC_DATA_READ_32				    0x00000008		//read 32 bit data from a 32 bit addressable location/register
#define C2C1_BROM_IPC_SET_BITS_PROTECTED_16		    0x00000009		//set bits(max. 16 bit wide) in a 16 bit addressable (EALLOW)protected location/register
#define C2C1_BROM_IPC_SET_BITS_PROTECTED_32		    0x0000000A		//set bits(max. 32 bit wide) in a 32 bit addressable (EALLOW)protected location/register
#define C2C1_BROM_IPC_CLEAR_BITS_PROTECTED_16		0x0000000B		//clear bits(max. 16 bit wide) in a 16 bit addressable (EALLOW)protected location/register
#define C2C1_BROM_IPC_CLEAR_BITS_PROTECTED_32		0x0000000C		//clear bits(max. 32 bit wide) in a 32 bit addressable (EALLOW)protected location/register
#define C2C1_BROM_IPC_DATA_WRITE_PROTECTED_16		0x0000000D		//write 16 bit data to a 16 bit addressable (EALLOW)protected location/register
#define C2C1_BROM_IPC_DATA_WRITE_PROTECTED_32		0x0000000E		//write 32 bit data to a 32 bit addressable (EALLOW)protected location/register
#define C2C1_BROM_IPC_DATA_READ_PROTECTED_16		0x0000000F		//read 16 bit data from a 16 bit addressable (EALLOW)protected location/register
#define C2C1_BROM_IPC_DATA_READ_PROTECTED_32		0x00000010		//read 32 bit data from a 32 bit addressable (EALLOW)protected location/register
#define C2C1_BROM_IPC_BRANCH_CALL					0x00000011		//master requests a branch operation
#define C2C1_BROM_IPC_FUNCTION_CALL				    0x00000012		//master requests a function call operation
#define C2C1_BROM_IPC_EXECUTE_BOOTMODE_CMD		    0x00000013		//master requests control system to execute MTOCBOOTMODE CMD
#define C2C1_BROM_IPC_MAX_SUPPORT_VALUE 			0x00000014		//one less than this value are supported/valid values


/*enum to tell the command status*/

typedef enum
{
	COMMAND_STATUS_INVALID = 0,			/*current command status is in-valid*/
	COMMAND_PENDING,					/*current ipc command is under processing*/
	COMMAND_COMPLETE_SUCCESS,			/*current ipc command has compelted successfully*/
	COMMAND_COMPLETE_FAILURE			/*current ipc command has completed, but failed*/
}command_status_t;



#endif /*C_BOOTROM_IPC_COMMANDS_H_*/
