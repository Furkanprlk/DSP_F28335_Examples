// TI File $Revision: /main/1 $
// Checkin $Date: August 13, 2012   11:53:30 $
//###########################################################################
//
// FILE:   c2_bootrom.h
//
// TITLE:  C2-BootROM Definitions.
//
//###########################################################################
// $TI Release: F2837x Boot ROM Version 0 $
// $Release Date: Oct 1, 2013 $
//###########################################################################


#ifndef C_BOOTROM_H_
#define C_BOOTROM_H_

#include "F2837x_Device.h"
#include "driver_incs.h"
#include "c2_bootrom_ipc_commands.h"

/* some defines used by C-BootROM*/

#ifndef IS_TRUE
#define IS_TRUE		1
#endif

#ifndef IS_FALSE
#define IS_FALSE	0
#endif

#ifndef IS_SUCCESS
#define	IS_SUCCESS	IS_TRUE
#endif

#ifndef IS_FAILURE
#define IS_FAILURE	IS_FALSE
#endif

extern  Uint16 EmuKey;
extern  Uint16 EmuBMode;

#define KEY_VAL             0x5A


#define STAND_ALONE_BOOT_TYPE   1
#define EMU_BOOT_TYPE           2
#define HIB_BOOT_TYPE           3

#define EMULATE_TRUE_BOOT		0xFF 		// follow stand-alone boot with emulator connected


#define PARALLEL_BOOT           0x0
#define SCI_BOOT                0x1
#define WAIT_BOOT               0x2
#define GET_BOOT                0x3
#define SPI_BOOT                0x4
#define I2C_BOOT                0x5
//#define OTP_BOOT                0x6
#define CAN_BOOT                0x7
#define CAN_BOOT_TEST           0x47        //enables tx of two packets for bit rate calcs

#define RAM_BOOT                0xA
#define FLASH_BOOT              0xB

#define USB_BOOT                0xC


//---------------------------------------------------------------------------
// Fixed boot entry points:
//
#define FLASH_ENTRY_POINT 0x080000	/**/
#define RAM_ENTRY_POINT   0x000000	/*M0 start address*/

#define ERROR                   1
#define NO_ERROR                0

#define BROM_EIGHT_BIT_HEADER   		0x08AA

//---------------------------------------------------------------------------
//
#define TI_OTP_PARTID_L					*(volatile uint32_t *)(0x70200)
#define TI_OTP_PARTID_H					*(volatile uint32_t *)(0x70202)
typedef Uint16 (* uint16fptr)();
extern  uint16fptr GetWordData;

#define OTP_CPU_ID_VERSION				(Uint16)(*(volatile Uint16 *)(0x7026D))
#define OTP_BOOT_CONFIGURE_WORD			(Uint32)(*(volatile Uint32 *)(Uint32)(0x703EE)) // bit 1,0 = 01 means enable PLL, else don't

#define OTP_BOOT_ESCAPE_TABLE_END		0x703EC

//extern void otp_func_refs();
#define TI_OTP_C2BROM_ESCAPE_POINT_15			(Uint32)(*(volatile Uint32 *)((Uint32)(OTP_BOOT_ESCAPE_TABLE_END)-28))
#define TI_OTP_C2BROM_ESCAPE_POINT_14			(Uint32)(*(volatile Uint32 *)((Uint32)(OTP_BOOT_ESCAPE_TABLE_END)-26))
#define TI_OTP_C2BROM_ESCAPE_POINT_13			(Uint32)(*(volatile Uint32 *)((Uint32)(OTP_BOOT_ESCAPE_TABLE_END)-24))
#define TI_OTP_C2BROM_ESCAPE_POINT_12			(Uint32)(*(volatile Uint32 *)((Uint32)(OTP_BOOT_ESCAPE_TABLE_END)-22))
#define TI_OTP_C2BROM_ESCAPE_POINT_11			(Uint32)(*(volatile Uint32 *)((Uint32)(OTP_BOOT_ESCAPE_TABLE_END)-20))
#define TI_OTP_C2BROM_ESCAPE_POINT_10			(Uint32)(*(volatile Uint32 *)((Uint32)(OTP_BOOT_ESCAPE_TABLE_END)-18))
#define TI_OTP_C2BROM_ESCAPE_POINT_9			(Uint32)(*(volatile Uint32 *)((Uint32)(OTP_BOOT_ESCAPE_TABLE_END)-16))
#define TI_OTP_C2BROM_ESCAPE_POINT_8			(Uint32)(*(volatile Uint32 *)((Uint32)(OTP_BOOT_ESCAPE_TABLE_END)-14))
#define TI_OTP_C2BROM_ESCAPE_POINT_7			(Uint32)(*(volatile Uint32 *)((Uint32)(OTP_BOOT_ESCAPE_TABLE_END)-12))
#define TI_OTP_C2BROM_ESCAPE_POINT_6			(Uint32)(*(volatile Uint32 *)((Uint32)(OTP_BOOT_ESCAPE_TABLE_END)-10))
#define TI_OTP_C2BROM_ESCAPE_POINT_5			(Uint32)(*(volatile Uint32 *)((Uint32)(OTP_BOOT_ESCAPE_TABLE_END)-8))
#define TI_OTP_C2BROM_ESCAPE_POINT_4			(Uint32)(*(volatile Uint32 *)((Uint32)(OTP_BOOT_ESCAPE_TABLE_END)-6))
#define TI_OTP_C2BROM_ESCAPE_POINT_3			(Uint32)(*(volatile Uint32 *)((Uint32)(OTP_BOOT_ESCAPE_TABLE_END)-4))
#define TI_OTP_C2BROM_ESCAPE_POINT_2			(Uint32)(*(volatile Uint32 *)((Uint32)(OTP_BOOT_ESCAPE_TABLE_END)-2))
#define TI_OTP_C2BROM_ESCAPE_POINT_1			(Uint32)(*(volatile Uint32 *)(Uint32)(OTP_BOOT_ESCAPE_TABLE_END))


/*internal Macors used by C-BootROM*/

/* MACRO to ACK IPC command
 */
#define C2BROM_C1C2_IPC_COMMAND_ACK					IpcRegs.IPCACK.all = 0x80000001


/* MACROS to NAK asn IPC command with error code 
 * Aria will acknowledge only IPC Flag1 if the command is invalid/resulted in error or cannot be executed
 */

#define C2BROM_C1C2_IPC_COMMAND_NAK(error_code)		IpcRegs.IPCACK.bit.IPC0 = 0x01; \
													IpcRegs.IPCLOCALREPLY = (Uint32)error_code;

/*Macros to ACK PIE IPC interrupt*/

#define C2BROM_C1C2_IPC_INT1_ACK					PieCtrlRegs.PIEACK.all = PIEACK_GROUP1

/*macros to check if IPC flags are set properly*/

#define C2BROM_CHECK_C1C2_IPC_COMMAND_FLAGS_SET		((IpcRegs.IPCSTS.bit.IPC0) && (IpcRegs.IPCSTS.bit.IPC31))

//typedefs

/*below data structure stores the current ipc command being processed by C2-BootROM*/

typedef struct current_c1c2_ipc_status
{
	command_status_t			status;		/*status of the current command*/
	uint32_t						command;	/*current command value*/
}cur_c1c2_ipc_cmd_sts_t;



typedef void (*c2brom_ipc_branch_t)(void);
typedef uint32_t  (*c2brom_ipc_func_call_t)(uint32_t data);


/*function prototypes*/
extern command_status_t c2brom_c1c2_ipc_set_bits_16(void);
extern command_status_t c2brom_c1c2_ipc_set_bits_32(void);
extern command_status_t c2brom_c1c2_ipc_clear_bits_16(void);
extern command_status_t c2brom_c1c2_ipc_clear_bits_32(void);
extern command_status_t c2brom_c1c2_ipc_write_data_16(void);
extern command_status_t c2brom_c1c2_ipc_write_data_32(void);
extern command_status_t c2brom_c1c2_ipc_read_data_16(void);
extern command_status_t c2brom_c1c2_ipc_read_data_32(void);

extern command_status_t c2brom_c1c2_ipc_set_bits_protected_16(void);
extern command_status_t c2brom_c1c2_ipc_set_bits_protected_32(void);
extern command_status_t c2brom_c1c2_ipc_clear_bits_protected_16(void);
extern command_status_t c2brom_c1c2_ipc_clear_bits_protected_32(void);
extern command_status_t c2brom_c1c2_ipc_write_data_protected_16(void);
extern command_status_t c2brom_c1c2_ipc_write_data_protected_32(void);
extern command_status_t c2brom_c1c2_ipc_read_data_protected_16(void);
extern command_status_t c2brom_c1c2_ipc_read_data_protected_32(void);

extern Uint32 c2brom_c1c2_ipc_func_call_command(void);
 

extern Uint32 c2brom_send_ipc_to_c1(Uint32 command, Uint32 addr, Uint32 data_w);
extern void c2brom_set_c2c1_boot_status(Uint32 status);

void c2brom_init_pie_control(void);
void c2brom_init_pie_vect_table(void);

extern interrupt void c2brom_itrap_isr(void);
extern interrupt void c2brom_c1c2_ipc_int1_isr(void);
extern interrupt void c2brom_handle_nmi();
extern void c2brom_pie_vect_mismatch_handler();
extern void c2brom_handle_nmi_at_start();



//  External functions referenced by this file
extern Uint32 SCI_Boot(void);
extern Uint32 SPI_Boot(void);
extern Uint32 Parallel_Boot(void);
extern Uint32 I2C_Boot(void);
extern Uint32 DCAN_Boot(Uint32 bootMode);


extern uint16_t c2brom_read_otp_bootmode();
extern uint16_t c2brom_evaluate_bootmode(uint16_t bootmode, uint16_t bootmode_type);




// Functions in this file
//void   WaitBoot(void);
extern Uint16 SelectBootMode(void);


#endif /*C_BOOTROM_H_*/
