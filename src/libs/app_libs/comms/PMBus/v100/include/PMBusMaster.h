/*******************************************************************************
    Filename:       PMBusMaster.h

    Copyright 2011 Texas Instruments, Inc.
*******************************************************************************/
#ifndef PMBUSMASTER_H_
#define PMBUSMASTER_H_

/*------------------------------------------------------------------------------
This function is used to implement PMBus functionality without PEC
------------------------------------------------------------------------------*/
unsigned char PMBusMaster(unsigned char PMBusMaster_CommandByte, unsigned char PMBusMaster_RWFlag,unsigned int PMBusMaster_Message,unsigned char *PMBusMaster_ReceivedValue);
/*------------------------------------------------------------------------------
This function is used to initialize PMBus master device
------------------------------------------------------------------------------*/
void PMBusMaster_Init(unsigned char PMBusMaster_SlaveAddress, unsigned char PMBusMaster_Prescale);

static unsigned char PMBusMaster_Crc8MakeBitwise(unsigned char PMBusMaster_CRC, unsigned char PMBusMaster_Poly, unsigned char *PMBusMaster_Pmsg, unsigned int PMBusMaster_MsgSize);

#endif /*PMBUSMASTER_H_*/
