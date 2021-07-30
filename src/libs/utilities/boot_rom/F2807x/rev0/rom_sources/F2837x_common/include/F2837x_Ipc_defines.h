//###########################################################################
//
// FILE:	F2837x_Ipc_defines.h
//
// TITLE:	2837x IPC support definitions
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
//###########################################################################

#ifndef F2837x_IPC_DEFINES_H
#define F2837x_IPC_DEFINES_H

//--------------------------------------------
// Defines
//--------------------------------------------

#define C1TOC2_MSG_RAM ((void *)0x3FC00)
#define C2TOC1_MSG_RAM ((void *)0x3F800)

#if defined(CPU1)
	#define SEND_MSG_RAM C1TOC2_MSG_RAM
	#define RECV_MSG_RAM C2TOC1_MSG_RAM
#elif defined(CPU2)
	#define SEND_MSG_RAM C2TOC1_MSG_RAM
	#define RECV_MSG_RAM C1TOC2_MSG_RAM
#endif
#define MSG_RAM_SIZE 0x400

//Used with SendIpcData() and SendIpcCommand() to avoid setting a flag
#define NO_IPC_FLAG 32

//Key value used for write access to the flash pump semaphore register
#define IPC_PUMP_KEY 0x5a5a0000

#endif  // end of F2837x_IPC_DEFINES_H definition

//===========================================================================
// End of file.
//===========================================================================
