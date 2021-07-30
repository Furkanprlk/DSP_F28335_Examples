/*******************************************************************************
    Filename:       PMBusSlave.h

    Copyright 2011 Texas Instruments, Inc.
*******************************************************************************/
#ifndef PMBUSSLAVE_H_
#define PMBUSSLAVE_H_

void I2CSlave_Init(Uint16 Own_Address);
void PMBusSlave_Init(unsigned char PMBusSlave_DeviceAddress);
unsigned char PMBusSlave_DecodeCommand(unsigned char PMBusSlave_RxCommand);
void PMBusSlave(void);

static unsigned short PMBusSlave_Crc8MakeBitwise(unsigned char PMBusSlave_CRC, unsigned char PMBusSlave_Poly, unsigned char *PMBusSlave_Pmsg, unsigned int PMBusSlave_MsgSize);
interrupt void cpu_timer0_isr(void);

#endif /*PMBUSSLAVE_H_*/
