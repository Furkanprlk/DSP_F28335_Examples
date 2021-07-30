// TI File $Revision: /main/1 $
// Checkin $Date: August 13, 2012   11:53:49 $
//###########################################################################
//
// FILE:    ccore_bootrom_ipc_commands.c    
//
// TITLE:   C-BootROM ipc commands utility function
//
// Functions:
//
// Notes:
//
//###########################################################################
// $TI Release: F2837x Boot ROM V1.0 $
// $Release Date: October 2013 $
//###########################################################################

#include "c2_bootrom.h"

/*function prototypes*/
command_status_t c2brom_c1c2_ipc_set_bits_16(void);
command_status_t c2brom_c1c2_ipc_set_bits_32(void);
command_status_t c2brom_c1c2_ipc_clear_bits_16(void);
command_status_t c2brom_c1c2_ipc_clear_bits_32(void);
command_status_t c2brom_c1c2_ipc_write_data_16(void);
command_status_t c2brom_c1c2_ipc_write_data_32(void);
command_status_t c2brom_c1c2_ipc_read_data_16(void);
command_status_t c2brom_c1c2_ipc_read_data_32(void);

command_status_t c2brom_c1c2_ipc_set_bits_protected_16(void);
command_status_t c2brom_c1c2_ipc_set_bits_protected_32(void);
command_status_t c2brom_c1c2_ipc_clear_bits_protected_16(void);
command_status_t c2brom_c1c2_ipc_clear_bits_protected_32(void);
command_status_t c2brom_c1c2_ipc_write_data_protected_16(void);
command_status_t c2brom_c1c2_ipc_write_data_protected_32(void);
command_status_t c2brom_c1c2_ipc_read_data_protected_16(void);
command_status_t c2brom_c1c2_ipc_read_data_protected_32(void);

Uint32 c2brom_c1c2_ipc_func_call_command(void);
 

Uint32 c2brom_send_ipc_to_c1(Uint32 command, Uint32 addr, Uint32 data_w);
void c2brom_set_c2c1_boot_status(Uint32 status);

extern Uint32 c2brom_status;

/*
	Function to set CTOMBOOTSTS register
 */

void c2brom_set_c2c1_boot_status(Uint32 status)
{
	/*top word  (bits 31-16) is reserved for boot rom health status - bits 15:0 are for boot status*/
	IpcRegs.IPCBOOTSTS = ((Uint32)c2brom_status | (Uint32)status);
}
/*
	Function called to send an IPC message/command to master
*/

Uint32 c2brom_send_ipc_to_c1(Uint32 command, Uint32 addr, Uint32 data_w)
{

	if((IpcRegs.IPCFLG.bit.IPC0) || (IpcRegs.IPCFLG.bit.IPC31))
	{
		/*if IPC flags from prev. command are not cleared yet, then ignore the current command*/
		return IS_FAILURE;
	}

	IpcRegs.IPCSENDCOM = command;
	IpcRegs.IPCSENDADDR = addr;
	IpcRegs.IPCSENDDATA = data_w;
	IpcRegs.IPCSET.all = 0x80000001;	//set bit 31 and bit 0

	return IS_SUCCESS;
}

/****************************************************************************************
 * 
 *  Functions to handle MTOC IPC commands
 * 
 ***************************************************************************************/


/*
	Function called to handle MASTER_IPC_MTOC_SET_BITS_16 command
*/

command_status_t c2brom_c1c2_ipc_set_bits_16(void)
{
		*((Uint16 *)(IpcRegs.IPCRECVADDR)) |= (Uint16)(IpcRegs.IPCRECVDATA);
		IpcRegs.IPCLOCALREPLY = *((Uint16 *)(IpcRegs.IPCRECVADDR));
		return COMMAND_COMPLETE_SUCCESS;
}

/*
	Function called to handle MASTER_IPC_MTOC_SET_BITS_32 command
*/

command_status_t c2brom_c1c2_ipc_set_bits_32(void)
{
		*((Uint32 *)(IpcRegs.IPCRECVADDR)) |= (Uint32)(IpcRegs.IPCRECVDATA);
		IpcRegs.IPCLOCALREPLY = *((Uint32 *)(IpcRegs.IPCRECVADDR));
		return COMMAND_COMPLETE_SUCCESS; 
}

/*
	Function called to handle MASTER_IPC_MTOC_CLEAR_BITS_16 command
*/

command_status_t c2brom_c1c2_ipc_clear_bits_16(void)
{
		*((Uint16 *)(IpcRegs.IPCRECVADDR)) &= (Uint16)(~(IpcRegs.IPCRECVDATA));
		IpcRegs.IPCLOCALREPLY = *((Uint16 *)(IpcRegs.IPCRECVADDR));
		return COMMAND_COMPLETE_SUCCESS;
}

/*
	Function called to handle MASTER_IPC_MTOC_CLEAR_BITS_32 command
*/
command_status_t c2brom_c1c2_ipc_clear_bits_32(void)
{
		*((Uint32 *)(IpcRegs.IPCRECVADDR)) &= (Uint32)(~(IpcRegs.IPCRECVDATA));
		IpcRegs.IPCLOCALREPLY = *((Uint32 *)(IpcRegs.IPCRECVADDR));
		return COMMAND_COMPLETE_SUCCESS; 
}

/*
	Function called to handle MASTER_IPC_MTOC_DATA_WRITE_16 command
*/
command_status_t c2brom_c1c2_ipc_write_data_16(void)
{
		*((Uint16 *)(IpcRegs.IPCRECVADDR)) = (Uint16)(IpcRegs.IPCRECVDATA);
		IpcRegs.IPCLOCALREPLY = *((Uint16 *)(IpcRegs.IPCRECVADDR));
		return COMMAND_COMPLETE_SUCCESS;
}

/*
	Function called to handle MASTER_IPC_MTOC_DATA_WRITE_32 command
*/
command_status_t c2brom_c1c2_ipc_write_data_32(void)
{
		*((Uint32 *)(IpcRegs.IPCRECVADDR)) = (Uint32)(IpcRegs.IPCRECVDATA);
		IpcRegs.IPCLOCALREPLY = *((Uint32 *)(IpcRegs.IPCRECVADDR));
		return COMMAND_COMPLETE_SUCCESS;
}


/*
	Function called to handle MASTER_IPC_MTOC_DATA_READ_16 command
*/
command_status_t c2brom_c1c2_ipc_read_data_16(void)
{
		IpcRegs.IPCLOCALREPLY = *((Uint16 *)(IpcRegs.IPCRECVADDR));
		return COMMAND_COMPLETE_SUCCESS; 
}

/*
	Function called to handle MASTER_IPC_MTOC_DATA_READ_32 command
*/
command_status_t c2brom_c1c2_ipc_read_data_32(void)
{
		IpcRegs.IPCLOCALREPLY = *((Uint32 *)(IpcRegs.IPCRECVADDR));
		return COMMAND_COMPLETE_SUCCESS; 
}


/*
	Function called to handle MASTER_IPC_MTOC_SET_BITS_PROTECTED_16 command
*/
command_status_t c2brom_c1c2_ipc_set_bits_protected_16(void)
{
	EALLOW;
		*((Uint16 *)(IpcRegs.IPCRECVADDR)) |= (Uint16)IpcRegs.IPCRECVDATA;
		IpcRegs.IPCLOCALREPLY = *((Uint16 *)(IpcRegs.IPCRECVADDR));
	EDIS;
	return COMMAND_COMPLETE_SUCCESS;
}

/*
	Function called to handle MASTER_IPC_MTOC_SET_BITS_PROTECTED_32 command
*/
command_status_t c2brom_c1c2_ipc_set_bits_protected_32(void)
{
	EALLOW;
		*((Uint32 *)(IpcRegs.IPCRECVADDR)) |= (Uint32)IpcRegs.IPCRECVDATA;
		IpcRegs.IPCLOCALREPLY = *((Uint32 *)(IpcRegs.IPCRECVADDR));
	EDIS;
	return COMMAND_COMPLETE_SUCCESS;
}

/*
	Function called to handle MASTER_IPC_MTOC_CLEAR_BITS_PROTECTED_16 command
*/
command_status_t c2brom_c1c2_ipc_clear_bits_protected_16(void)
{
	EALLOW;
		*((Uint16 *)(IpcRegs.IPCRECVADDR)) &= (Uint16)(~(IpcRegs.IPCRECVDATA));
		IpcRegs.IPCLOCALREPLY = *((Uint16 *)(IpcRegs.IPCRECVADDR));
	EDIS;
	return COMMAND_COMPLETE_SUCCESS;
}

/*
	Function called to handle MASTER_IPC_MTOC_CLEAR_BITS_PROTECTED_32 command
*/
command_status_t c2brom_c1c2_ipc_clear_bits_protected_32(void)
{
	EALLOW;
		*((Uint32 *)(IpcRegs.IPCRECVADDR)) &= (Uint32)(~(IpcRegs.IPCRECVDATA));
		IpcRegs.IPCLOCALREPLY = *((Uint32 *)(IpcRegs.IPCRECVADDR));
	EDIS;
	return COMMAND_COMPLETE_SUCCESS;
}

/*
	Function called to handle MASTER_IPC_MTOC_DATA_WRITE_PROTECTED_16 command
*/
command_status_t c2brom_c1c2_ipc_write_data_protected_16(void)
{
	EALLOW;
		*((Uint16 *)(IpcRegs.IPCRECVADDR)) = (Uint16)(IpcRegs.IPCRECVDATA);
		IpcRegs.IPCLOCALREPLY = *((Uint16 *)(IpcRegs.IPCRECVADDR));
	EDIS;
	return COMMAND_COMPLETE_SUCCESS;
}

/*
	Function called to handle MASTER_IPC_MTOC_DATA_WRITE_PROTECTED_32 command
*/
command_status_t c2brom_c1c2_ipc_write_data_protected_32(void)
{
	EALLOW;
		*((Uint32 *)(IpcRegs.IPCRECVADDR)) = (Uint32)(IpcRegs.IPCRECVDATA);
		IpcRegs.IPCLOCALREPLY = *((Uint32 *)(IpcRegs.IPCRECVADDR));
	EDIS;
	return COMMAND_COMPLETE_SUCCESS;
}


/*
	Function called to handle MASTER_IPC_MTOC_DATA_READ_PROTECTED_16 command
*/
command_status_t c2brom_c1c2_ipc_read_data_protected_16(void)
{
	EALLOW;
	    IpcRegs.IPCLOCALREPLY = *((Uint16 *)(IpcRegs.IPCRECVADDR));
	EDIS;
	return COMMAND_COMPLETE_SUCCESS;
}

/*
	Function called to handle MASTER_IPC_MTOC_DATA_READ_PROTECTED_32 command
*/
command_status_t c2brom_c1c2_ipc_read_data_protected_32(void)
{
	EALLOW;
	IpcRegs.IPCLOCALREPLY = *((Uint32 *)(IpcRegs.IPCRECVADDR));
	EDIS;
	return COMMAND_COMPLETE_SUCCESS; 
}



/*
	Function called to handle MASTER_IPC_MTOC_FUNCTION_CALL command
*/
Uint32 c2brom_c1c2_ipc_func_call_command(void)
{
		Uint32 param = IpcRegs.IPCRECVDATA;
		c2brom_ipc_func_call_t c1c2_func_call = (c2brom_ipc_func_call_t)IpcRegs.IPCRECVADDR;
		return c1c2_func_call(param);
}

