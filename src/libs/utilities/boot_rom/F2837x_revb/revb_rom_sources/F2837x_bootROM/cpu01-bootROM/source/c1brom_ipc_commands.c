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

#include "c1_bootrom.h"

/*function prototypes*/
command_status_t c1brom_c2c1_ipc_set_bits_16(void);
command_status_t c1brom_c2c1_ipc_set_bits_32(void);
command_status_t c1brom_c2c1_ipc_clear_bits_16(void);
command_status_t c1brom_c2c1_ipc_clear_bits_32(void);
command_status_t c1brom_c2c1_ipc_write_data_16(void);
command_status_t c1brom_c2c1_ipc_write_data_32(void);
command_status_t c1brom_c2c1_ipc_read_data_16(void);
command_status_t c1brom_c2c1_ipc_read_data_32(void);

command_status_t c1brom_c2c1_ipc_set_bits_protected_16(void);
command_status_t c1brom_c2c1_ipc_set_bits_protected_32(void);
command_status_t c1brom_c2c1_ipc_clear_bits_protected_16(void);
command_status_t c1brom_c2c1_ipc_clear_bits_protected_32(void);
command_status_t c1brom_c2c1_ipc_write_data_protected_16(void);
command_status_t c1brom_c2c1_ipc_write_data_protected_32(void);
command_status_t c1brom_c2c1_ipc_read_data_protected_16(void);
command_status_t c1brom_c2c1_ipc_read_data_protected_32(void);

extern uint32_t c1brom_status;

/****************************************************************************************
 * 
 *  Functions to handle C2C1 IPC commands
 * 
 ***************************************************************************************/


/*
	Function called to handle MASTER_IPC_MTOC_SET_BITS_16 command
*/

command_status_t c1brom_c2c1_ipc_set_bits_16(void)
{
    *((uint16_t *)(IpcRegs.IPCRECVADDR)) |= (uint16_t)(IpcRegs.IPCRECVDATA);
    IpcRegs.IPCLOCALREPLY = *((uint16_t *)(IpcRegs.IPCRECVADDR));
    return COMMAND_COMPLETE_SUCCESS;
}

/*
	Function called to handle MASTER_IPC_MTOC_SET_BITS_32 command
*/

command_status_t c1brom_c2c1_ipc_set_bits_32(void)
{
    *((Uint32 *)(IpcRegs.IPCRECVADDR)) |= (Uint32)(IpcRegs.IPCRECVDATA);
    IpcRegs.IPCLOCALREPLY = *((Uint32 *)(IpcRegs.IPCRECVADDR));
    return COMMAND_COMPLETE_SUCCESS;
}

/*
	Function called to handle MASTER_IPC_MTOC_CLEAR_BITS_16 command
*/

command_status_t c1brom_c2c1_ipc_clear_bits_16(void)
{
    *((Uint16 *)(IpcRegs.IPCRECVADDR)) &= (Uint16)(~(IpcRegs.IPCRECVDATA));
    IpcRegs.IPCLOCALREPLY = *((Uint16 *)(IpcRegs.IPCRECVADDR));
    return COMMAND_COMPLETE_SUCCESS;
}

/*
	Function called to handle MASTER_IPC_MTOC_CLEAR_BITS_32 command
*/
command_status_t c1brom_c2c1_ipc_clear_bits_32(void)
{
    *((Uint32 *)(IpcRegs.IPCRECVADDR)) &= (Uint32)(~(IpcRegs.IPCRECVDATA));
    IpcRegs.IPCLOCALREPLY = *((Uint32 *)(IpcRegs.IPCRECVADDR));
    return COMMAND_COMPLETE_SUCCESS;
}

/*
	Function called to handle MASTER_IPC_MTOC_DATA_WRITE_16 command
*/
command_status_t c1brom_c2c1_ipc_write_data_16(void)
{
    *((Uint16 *)(IpcRegs.IPCRECVADDR)) = (Uint16)(IpcRegs.IPCRECVDATA);
    IpcRegs.IPCLOCALREPLY = *((Uint16 *)(IpcRegs.IPCRECVADDR));
    return COMMAND_COMPLETE_SUCCESS;
}

/*
	Function called to handle MASTER_IPC_MTOC_DATA_WRITE_32 command
*/
command_status_t c1brom_c2c1_ipc_write_data_32(void)
{
    *((Uint32 *)(IpcRegs.IPCRECVADDR)) = (Uint32)(IpcRegs.IPCRECVDATA);
    IpcRegs.IPCLOCALREPLY = *((Uint32 *)(IpcRegs.IPCRECVADDR));
    return COMMAND_COMPLETE_SUCCESS;
}


/*
	Function called to handle MASTER_IPC_MTOC_DATA_READ_16 command
*/
command_status_t c1brom_c2c1_ipc_read_data_16(void)
{
    IpcRegs.IPCLOCALREPLY = *((Uint16 *)(IpcRegs.IPCRECVADDR));
    return COMMAND_COMPLETE_SUCCESS;
}

/*
	Function called to handle MASTER_IPC_MTOC_DATA_READ_32 command
*/
command_status_t c1brom_c2c1_ipc_read_data_32(void)
{
    IpcRegs.IPCLOCALREPLY = *((Uint32 *)(IpcRegs.IPCRECVADDR));
    return COMMAND_COMPLETE_SUCCESS;
}


/*
	Function called to handle MASTER_IPC_MTOC_SET_BITS_PROTECTED_16 command
*/
command_status_t c1brom_c2c1_ipc_set_bits_protected_16(void)
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
command_status_t c1brom_c2c1_ipc_set_bits_protected_32(void)
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
command_status_t c1brom_c2c1_ipc_clear_bits_protected_16(void)
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
command_status_t c1brom_c2c1_ipc_clear_bits_protected_32(void)
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
command_status_t c1brom_c2c1_ipc_write_data_protected_16(void)
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
command_status_t c1brom_c2c1_ipc_write_data_protected_32(void)
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
command_status_t c1brom_c2c1_ipc_read_data_protected_16(void)
{
    EALLOW;
        IpcRegs.IPCLOCALREPLY = *((Uint16 *)(IpcRegs.IPCRECVADDR));
    EDIS;
    return COMMAND_COMPLETE_SUCCESS;
}

/*
	Function called to handle MASTER_IPC_MTOC_DATA_READ_PROTECTED_32 command
*/
command_status_t c1brom_c2c1_ipc_read_data_protected_32(void)
{
    EALLOW;
    IpcRegs.IPCLOCALREPLY = *((Uint32 *)(IpcRegs.IPCRECVADDR));
    EDIS;
    return COMMAND_COMPLETE_SUCCESS;
}

