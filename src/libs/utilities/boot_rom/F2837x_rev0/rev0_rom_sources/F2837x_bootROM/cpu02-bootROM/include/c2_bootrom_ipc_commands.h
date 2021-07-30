// TI File $Revision: /main/1 $
// Checkin $Date: August 13, 2012   11:53:32 $
//###########################################################################
//
// FILE:   c_bootrom_ipc_commands.h
//
// TITLE:  C-BootROM IPC command Definitions.
//
//###########################################################################
// $TI Release: F2837x Boot ROM Version 0 $
// $Release Date: Oct 1, 2013 $
//###########################################################################


#ifndef C_BOOTROM_IPC_COMMANDS_H_
#define C_BOOTROM_IPC_COMMANDS_H_

/* C2-BootROM health status:
 * The below will be given to user in xTOCIPCDATAR[31:12], in case of an IPC NAK
 * and also always in CTOMBOOTSTS[31:12], whenever boot status is written
 */
#define C2_BOOTROM_START_BOOT               0x00000100          //set during the initialization phase of C2-bootROM
#define C2_BOOTROM_IN_FLASH_BOOT            0x00000200			//set if boot to flash is detected
#define C2_BOOTROM_DCSM_INIT_DONE           0x00000400			//set after DCSM is initialized
#define C2_BOOTROM_RESC_HANDLED             0x00000800			//set after all RESC is handled
#define C2_BOOTROM_HANDLED_HIBRESET         0x00001000          //set if HIB reset is detected
#define C2_BOOTROM_HANDLED_HWBISTRESET      0x00002000          //set if HWBIST reset is detected
#define C2_BOOTROM_HANDLED_XRSN             0x00004000          //set if XRSn is detected
#define C2_BOOTROM_HANDLED_POR              0x00008000          //set if POR is serviced
#define C2_BOOTROM_IN_AN_ITRAP              0x00020000          //set if C-BootROM detects an iTRAP
#define C2_BOOTROM_IN_C1TOC2_BRANCH         0x00040000          //set if C-BootROM is doing a mtoc branch
#define C2_BOOTROM_GOT_A_PIEMISMATCH        0x00080000          //set if pie mismatch handler is called
#define C2_BOOTROM_GOT_A_OVF_NMI            0x00100000          //set if ovf nmi is detected
#define C2_BOOTROM_GOT_A_CPU2NMIWDRST_NMI   0x00200000          // - should never be set
#define C2_BOOTROM_GOT_A_CPU2WDRST_NMI      0x00400000          // - should never be set
#define C2_BOOTROM_GOT_A_RL_NMI             0x00800000          //set if RL NMI is detected
#define C2_BOOTROM_GOT_A_SYSDBG_NMI         0x01000000          //set if sysdbg nmi is detected
#define C2_BOOTROM_GOT_A_PIEVECTERR_NMI     0x02000000          //set if pievect err nmi is detected
#define C2_BOOTROM_GOT_A_C2BISTERR_NMI      0x04000000          //set if c2-bist error nmi is detected
#define C2_BOOTROM_GOT_A_C1BISTERR_NMI      0x08000000          //set if c1-bist error nmi is detected
#define C2_BOOTROM_GOT_A_FLASH_UNCERR_NMI   0x10000000          //set if flash uncerr nmi is detected
#define C2_BOOTROM_GOT_A_RAM_UNCERR_NMI     0x20000000          //set if ran uncerr nmi is detected
#define C2_BOOTROM_GOT_A_MCLK_NMI           0x40000000          //set if missing clock nmi is detected
#define C2_BOOTROM_BOOT_COMPLETE            0x80000000          //set if C-BootROM is starting an application after boot

/* xTOCIPCDATAR[11:0] register values, when Control system NAK's an IPC
 * xTOCIPCDATAR[31:12] register value stores the C-BootROM health status */
#define C2_BOOTROM_NAK_STATUS_INVALID_VALUE 					0x00000000				//invalid value or value when not set
#define C2_BOOTROM_NAK_STATUS_CMD_NOT_SUPPORTED					0x00000001				//NAK STATUS command not supported
#define C2_BOOTROM_NAK_STATUS_CMD_NOT_SET_PROPERLY				0x00000002				//NAK Status command not set properly , for ex: IPC1 set but IPC32 not set
#define C2_BOOTROM_NAK_STATUS_ALREADY_BUSY_WITH_YOUR_CMD		0x00000003				//NAK status when master is trying to send a second command before first one could complete
#define C2_BOOTROM_NAK_STATUS_CMD_RESULTED_IN_ERROR				0x00000004				//NAK status command execution resulted in an error
#define C2_BOOTROM_NAK_STATUS_CMD_CANNOT_BE_EXECUTED_NOW		0x00000005				//NAK status - command cannot be executed now in the current state of bootROM
#define C2_BOOTROM_NAK_STATUS_MAX_SUPPRT_VALUE					0x00000006				//one less than this value are valid values

/* CTOMBOOTSTS[11:0] register values will be one of the following all the time.
 * these enums are used to communicate the status of control to Master system
 */ 
#define	C2_BOOTROM_BOOTSTS_CTOM_IGNORE									0x00000000		//invalid status - tells master system that Aria has not filled in a valid value yet
#define C2_BOOTROM_BOOTSTS_SYSTEM_START_BOOT				            0x00000001		//tells master system that Control system has started to boot, but not completed the boot process yet
#define C2_BOOTROM_BOOTSTS_SYSTEM_READY					                0x00000002		//tells master system that Control system has completed the boot and is running
#define C2_BOOTROM_BOOTSTS_CTOM_BOOT_CMD_ACK							0x00000003		//tells master system that C-BootROM ACKs the command in MTOCBOOTMODE register
#define C2_BOOTROM_BOOTSTS_CTOM_BOOT_CMD_NAK_STATUS_NOT_SUPPORTED		0x00000004		//tells master system that C-BootROM doesn't support the command in MTOCBOOTMODE register
#define C2_BOOTROM_BOOTSTS_CTOM_BOOT_CMD_NAK_STATUS_BUSY_WITH_BOOT		0x00000005		//tells master system that C-BootROM NAKs the current boot command in MTOCBOOTMODE register
#define C2_BOOTROM_BOOTSTS_CTOM_MAX_SUPPORT_VALUE						0x00000006		//one less than this value are valid values.

/* C-BootROM uses the below enum values to fill in CTOMIPCCOM register*/

#define C2_BOOTROM_IPC_CTOM_COMMAND_ILLEGAL 							0x00000000		//invalid command value - default value when starting boot
#define C2_BOOTROM_IPC_CTOM_CONTROL_SYSTEM_IN_ITRAP						0xFFFFFFFE		//message tells Master that B.C28x CPU has got an iTRAP, address where iTrap occured will be in IPC ADDR register
#define C2_BOOTROM_IPC_CTOM_PIE_INTERRUPT_NOT_SUPPORTED					0xFFFFFFFD		//message tells Master that B.C28x CPU got a spurious PIE interrupt, intr no. will be in IPCDATAW register
#define C2_BOOTROM_IPC_CTOM_PIE_VECTOR_ADDRESS_MISMATCH					0xFFFFFFFC		//message tells Master that B.C28x CPU got a PIE vector mismatch error
#define C2_BOOTROM_IPC_CTOM_CONTROL_SYSTEM_IN_FLUNCERR					0xFFFFFFFB		//message tells Master that B.C28x CPU got a Flash uncorrectable error
#define C2_BOOTROM_IPC_CTOM_CONTROL_SYSTEM_IN_RAMUNCERR					0xFFFFFFFA		//message tells Master that B.C28x CPU got a RAM uncorrectable error

/* C1TOC2IPC commands
 * Below IPC commands are sent from CPU1 system to CPU2 system
 */

#define C1C2_BROM_IPC_COMMAND_ILLEGAL 			    0x00000000		//illegal command or command not set
#define C1C2_BROM_IPC_SET_BITS_16					0x00000001		//set bits(max. 16 bit wide) in a 16 bit addressable location/register
#define C1C2_BROM_IPC_SET_BITS_32					0x00000002		//set bits(max. 32 bit wide) in a 32 bit addressable location/register
#define C1C2_BROM_IPC_CLEAR_BITS_16				    0x00000003		//clear bits(max. 16 bit wide) in a 16 bit addressable location/register
#define C1C2_BROM_IPC_CLEAR_BITS_32				    0x00000004		//clear bits(max. 32 bit wide) in a 32 bit addressable location/register
#define C1C2_BROM_IPC_DATA_WRITE_16				    0x00000005		//write 16 bit data to a 16 bit addressable location/register
#define C1C2_BROM_IPC_DATA_WRITE_32				    0x00000006		//write 32 bit data to a 32 bit addressable location/register
#define C1C2_BROM_IPC_DATA_READ_16				    0x00000007		//read 16 bit data from a 16 bit addressable location/register
#define C1C2_BROM_IPC_DATA_READ_32				    0x00000008		//read 32 bit data from a 32 bit addressable location/register
#define C1C2_BROM_IPC_SET_BITS_PROTECTED_16		    0x00000009		//set bits(max. 16 bit wide) in a 16 bit addressable (EALLOW)protected location/register
#define C1C2_BROM_IPC_SET_BITS_PROTECTED_32		    0x0000000A		//set bits(max. 32 bit wide) in a 32 bit addressable (EALLOW)protected location/register
#define C1C2_BROM_IPC_CLEAR_BITS_PROTECTED_16        0x0000000B		//clear bits(max. 16 bit wide) in a 16 bit addressable (EALLOW)protected location/register
#define C1C2_BROM_IPC_CLEAR_BITS_PROTECTED_32        0x0000000C		//clear bits(max. 32 bit wide) in a 32 bit addressable (EALLOW)protected location/register
#define C1C2_BROM_IPC_DATA_WRITE_PROTECTED_16        0x0000000D		//write 16 bit data to a 16 bit addressable (EALLOW)protected location/register
#define C1C2_BROM_IPC_DATA_WRITE_PROTECTED_32        0x0000000E		//write 32 bit data to a 32 bit addressable (EALLOW)protected location/register
#define C1C2_BROM_IPC_DATA_READ_PROTECTED_16         0x0000000F		//read 16 bit data from a 16 bit addressable (EALLOW)protected location/register
#define C1C2_BROM_IPC_DATA_READ_PROTECTED_32	        0x00000010		//read 32 bit data from a 32 bit addressable (EALLOW)protected location/register
#define C1C2_BROM_IPC_BRANCH_CALL				    0x00000011		//master requests a branch operation
#define C1C2_BROM_IPC_FUNCTION_CALL				    0x00000012		//master requests a function call operation
#define C1C2_BROM_IPC_EXECUTE_BOOTMODE_CMD		    0x00000013		//master requests control system to execute MTOCBOOTMODE CMD
#define C1C2_BROM_IPC_MAX_SUPPORT_VALUE 			    0x00000014		//one less than this value are supported/valid values

/*Below are the values programmed into MTOCBOOTMODE register*/
#define C1C2_BROM_BOOTMODE_COMMAND_ILLEGAL                     0xFFFFFFFF

#define C1C2_BROM_BOOTMODE_BOOT_FROM_PARALLEL                  0x00000000
#define C1C2_BROM_BOOTMODE_BOOT_FROM_SCI                       0x00000001
#define C1C2_BROM_BOOTMODE_BOOT_FROM_SPI                       0x00000004
#define C1C2_BROM_BOOTMODE_BOOT_FROM_I2C                       0x00000005
#define C1C2_BROM_BOOTMODE_BOOT_FROM_CAN                       0x00000007
#define C1C2_BROM_BOOTMODE_BOOT_FROM_RAM                       0x0000000A
#define C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH                     0x0000000B

#define C1C2_BROM_BOOTMODE_BOOT_COMMAND_MAX_SUPPORT_VALUE      0x0000000C

#define PARALLEL_BOOT           0x0
#define SCI_BOOT                0x1
#define WAIT_BOOT               0x2
#define GET_BOOT                0x3
#define SPI_BOOT                0x4
#define I2C_BOOT                0x5
//#define OTP_BOOT                0x6
#define CAN_BOOT                0x7
#define RAM_BOOT                0xA
#define FLASH_BOOT              0xB

#define USB_BOOT                0xC


/*enum to tell the command status*/
typedef enum
{
	COMMAND_STATUS_INVALID = 0,			/*current command status is in-valid*/
	COMMAND_PENDING,					/*current ipc command is under processing*/
	COMMAND_COMPLETE_SUCCESS,			/*current ipc command has compelted successfully*/
	COMMAND_COMPLETE_FAILURE			/*current ipc command has completed, but failed*/
}command_status_t;

#endif /*C_BOOTROM_IPC_COMMANDS_H_*/
