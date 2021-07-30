/*******************************************************************************
    Filename:       I2CMaster.h

    Copyright 2011 Texas Instruments, Inc.
*******************************************************************************/

#ifndef I2C_MASTER_H_
#define I2C_MASTER_H_

// Prototype statements for functions
void I2CMaster_Init(Uint16 I2CMaster_SlaveAddress, Uint16 I2CMaster_Prescale);
void I2CMaster_Transmit(Uint16 I2CMaster_ByteCountTx, unsigned char *I2CMaster_TxArray, Uint16 I2CMaster_ByteCountRx, unsigned char *I2CMaster_RxArray);
void I2CMaster_Wait(void);
unsigned char I2CMaster_SlavePresent(unsigned char I2CMaster_SlaveAddress);
unsigned char I2CMaster_NotReady();

interrupt void i2c_master_int1a_isr(void);
interrupt void cpu_timer0_isr(void);

#endif /*I2C_MASTER_H_*/
