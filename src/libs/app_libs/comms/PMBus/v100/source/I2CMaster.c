/*******************************************************************************
 *
 * I2CMaster.c - Code for using a F2803x as an I2C master
 *
 * Copyright (c) 2011 Texas Instruments Incorporated.  All rights reserved.
 * Software License Agreement
 * 
 * Texas Instruments (TI) is supplying this software for use solely and
 * exclusively on TI's microcontroller products. The software is owned by
 * TI and/or its suppliers, and is protected under applicable copyright
 * laws. You may not combine this software with "viral" open-source
 * software in order to form a larger program.
 * 
 * THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
 * NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
 * NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
 * CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
 * DAMAGES, FOR ANY REASON WHATSOEVER.
 * 
 ******************************************************************************/

/***************************************************************************//**
 * @file       I2CMaster.c
 * @addtogroup I2CMaster
 * @{
 ******************************************************************************/
#include "DSP2803x_Device.h"     // DSP280x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP280x Examples Include File
#include "DSP2803x_I2C_defines.h"
#include "I2CMaster.h"

static unsigned char *I2CMaster_ReceiveField;
static unsigned char *I2CMaster_TransmitField;

/***************************************************************************//**
 * @brief   Initialize I2C module in master mode
 * @param   I2CMaster_SlaveAddress The address of the slave device
 * @param	I2CMaster_Prescale The prescale value to set master communication speed.
 * 				Master frequency = 60000/[(prescale+1)*25] MHz
 * @return  None
 ******************************************************************************/
void I2CMaster_Init(Uint16 I2CMaster_SlaveAddress, Uint16 I2CMaster_Prescale)
{
	//Setup I2C interrupts and Cpu Timer 0 interrupt
	EALLOW;	// This is needed to write to EALLOW protected registers
	PieVectTable.I2CINT1A = &i2c_master_int1a_isr;
	PieVectTable.TINT0 = &cpu_timer0_isr;
	EDIS;   // This is needed to disable write to EALLOW protected registers 
	// Enable I2C interrupt 1 in the PIE: Group 8 interrupt 1
	PieCtrlRegs.PIEIER8.bit.INTx1 = 1;
	// Enable TINT0 in the PIE: Group 1 interrupt 7
   	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
	// Enable CPU INT8 which is connected to PIE group 8
	IER |= M_INT8;
	// Enable CPU int1 which is connected to CPU-Timer 0
   	IER |= M_INT1;
   
	InitI2CGpio();
	InitCpuTimers();
	
	ConfigCpuTimer(&CpuTimer0, 60, 35000);			//CPU Timer 0 interrupt after 35 ms (at 60MHz CPU freq.)
	
    // Initialize I2C
	I2caRegs.I2CSAR = I2CMaster_SlaveAddress;		// Slave Address.
	I2caRegs.I2COAR = 0x002D;       				// address as Master.
	I2caRegs.I2CPSC.all = I2CMaster_Prescale;		// Prescaler - need 7-12 Mhz on module clk
	I2caRegs.I2CCLKL = 10;							// NOTE: must be non zero
	I2caRegs.I2CCLKH = 5;							// NOTE: must be non zero
    I2caRegs.I2CIER.all = 0x2C;						// Enable SCD & ARDY interrupts

    I2caRegs.I2CMDR.bit.IRS = 1;					// Take I2C out of reset
   													// Stop I2C when suspended

    I2caRegs.I2CFFTX.all = 0x6000;					// Enable FIFO mode and TXFIFO

	return;   
}

/***************************************************************************//**
 * @brief   Performs transmit and receive transactions in master mode
 * @param   I2CMaster_ByteCountTx The number of bytes to transmit.
 * @param	*I2CMaster_TxArray Pointer to the data to transmit.
 * @param	I2CMaster_ByteCountRx The number of bytes to receive.
 * @param	*I2CMaster_RxArray Pointer to structure to store received data.
 * @return  None
 ******************************************************************************/
void I2CMaster_Transmit(Uint16 I2CMaster_ByteCountTx, unsigned char *I2CMaster_TxArray, Uint16 I2CMaster_ByteCountRx, unsigned char *I2CMaster_RxArray)
{
	/***************Write******************/
	if(I2CMaster_ByteCountTx != 0)
	{
		I2CMaster_TransmitField = I2CMaster_TxArray;

		I2caRegs.I2CCNT = I2CMaster_ByteCountTx;
		while(I2CMaster_ByteCountTx > 0)	//check that there are still bytes to send
		{	
			I2caRegs.I2CDXR = *I2CMaster_TransmitField;
			I2CMaster_TransmitField++;
			I2CMaster_ByteCountTx--;		
		}	
		
	    I2caRegs.I2CMDR.all = 0x2E20;   // Set up the control register:
		                                // bit 14 FREE = 1
										// bit 13 STT = 1  (Start condition)
										
										// bit 11 STP = 1  (Stop condition after 
										//                transfer of bytes.)
										// bit 10 MST = 1  Master
										// bit  9 TRX = 1  Transmit
										
										// bit  5 IRS = 1 to Reset I2C bus.
										
		StartCpuTimer0();				// Start the timer
		I2CMaster_Wait();				// Wait for I2C bus to clear
		StopCpuTimer0();				//No timeout, so stop the timer
		ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
	}
	/****************Read*******************/
	if(I2CMaster_ByteCountRx != 0)
	{
		I2CMaster_ReceiveField = I2CMaster_RxArray;
		
		I2caRegs.I2CCNT = I2CMaster_ByteCountRx;  
		I2caRegs.I2CMDR.all = 0x2C20;			// Send "repeated" Start with Read (TRX off)
		                                		// and Stop.
		                                		
		StartCpuTimer0();						// Start the timer
		
		I2CMaster_Wait();						// Wait for I2C bus to clear
	}
}

/***************************************************************************//**
 * @brief   Wait for previous I2C transaction to clear.
 * @param   None
 * @return  None
 ******************************************************************************/
void I2CMaster_Wait(void)
{
   // Wait until the STP bit is cleared from any previous master communication.
   // Clearing of this bit by the module is delayed until after the SCD bit is
   // set. If this bit is not checked prior to initiating a new message, the
   // I2C could get confused.

    while (I2caRegs.I2CMDR.bit.STP == 1); // Wait for Stop condition bit to be zero.
	
	while (I2caRegs.I2CSTR.bit.BB == 1);  // Wait for Bus Busy to be zero.
 
}

/***************************************************************************//**
 * @brief   Checks if a slave is present and operational on the I2C lines.
 * @param   I2CMaster_SlaveAddress The slave we are checking.
 * @return  Slave presence (1 if present, 0 if not)
 ******************************************************************************/
unsigned char I2CMaster_SlavePresent(unsigned char I2CMaster_SlaveAddress)
{
  unsigned char ACKStatus;
  I2caRegs.I2CSAR = I2CMaster_SlaveAddress;   
  I2caRegs.I2CCNT = 0x01; 					//prepare to send a dummy byte
  I2caRegs.I2CDXR = 0x00;					//dummy byte to be written
  I2caRegs.I2CMDR.all = 0x2E20;     		// I2C TX, start condition
  while (I2caRegs.I2CMDR.bit.STP == 1);     // wait for STOP condition 
                     
  ACKStatus = !I2caRegs.I2CSTR.bit.NACK;
  return ACKStatus;                         // return whether or not 
                                            // a NACK occured
}

/***************************************************************************//**
 * @brief   See if the I2C master is ready to communicate.
 * @param   None
 * @return  Busy Bit (Busy = 1, Free = 0)
 ******************************************************************************/
unsigned char I2CMaster_NotReady()
{
  return I2caRegs.I2CSTR.bit.BB;
}

/***************************************************************************//**
 * @brief   Handles I2C interrupts.
 * @param   None
 * @return  None
 ******************************************************************************/
interrupt void i2c_master_int1a_isr(void)     // I2C-A
{
	Uint16 I2CMaster_IntSource;

   // Read interrupt source
	I2CMaster_IntSource = I2caRegs.I2CISRC.bit.INTCODE & 0x7;
	
	switch(I2CMaster_IntSource)
	{
		case I2C_NO_ISRC:   // =0
			break;

		case I2C_ARB_ISRC:  // =1
			break;

		case I2C_NACK_ISRC: // =2
			break;

		case I2C_ARDY_ISRC: // =3
			break;

		case I2C_RX_ISRC:   // =4
			StopCpuTimer0();		//No timeout, so stop the timer
			ReloadCpuTimer0();		//Reload the period value (35 ms timeout)
			*I2CMaster_ReceiveField = I2caRegs.I2CDRR;
			I2CMaster_ReceiveField++;
			break;

		case I2C_TX_ISRC:   // =5
			break;

		case I2C_SCD_ISRC:  // =6
			break;

		case I2C_AAS_ISRC:  // =7
			break;
	
		default:
			asm("   ESTOP0"); // Halt on invalid number.
	}

   // Enable future I2C (PIE Group 8) interrupts
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;
}

/***************************************************************************//**
 * @brief   Handles timeouts. Triggered if clock held low > 35ms.
 * @param   None
 * @return  None
 ******************************************************************************/
interrupt void cpu_timer0_isr(void)
{
	// Timed out. Reset module.
	I2caRegs.I2CMDR.bit.IRS = 0;	//reset
   	// Acknowledge this interrupt to receive more interrupts from group 1
   	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

