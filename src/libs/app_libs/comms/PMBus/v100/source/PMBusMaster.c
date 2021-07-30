/*******************************************************************************
 *
 * PMBusMaster.c -	This program is a software implementation of PMBus over I2C, 
 *					with the Piccolo device acting as the PMBus master.
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
 * @file       PMBusMaster.c
 * @addtogroup PMBusMaster
 * @{
 ******************************************************************************/
#include "DSP2803x_Device.h"     // DSP280x Headerfile Include File
#include "I2CMaster.h"
#include "PMBusMaster.h"
#include "PMBUS.h"

/* This is the PMBus command look-up table. Do not modify---------------------*/
const unsigned char PMBus_Commands[120] = 
{
	0x00, // dummy byte  
	0x19,0x78,0x7A,0x7B,0x7C,0x7D,0x7E,0x7F,0x80,0x81,0x82,0x98,
	0x79,0x88,0x89,0x8A,0x8B,0x8C,0x8D,0x8E,0x8F,0x90,0x91,0x92,
	0x93,0x94,0x95,0x96,0x97,0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6,
	0xA7,0xA8,0xA9,0x13,0x14,0x17,0x18,0x3 ,0x11,0x12,0x15,0x16,
	0x0 ,0x1 ,0x2 ,0x4 ,0x10,0x20,0x3A,0x3D,0x41,0x45,0x47,0x49,
	0x4C,0x50,0x54,0x56,0x5A,0x5C,0x63,0x69,0x21,0x22,0x23,0x24,
	0x25,0x26,0x27,0x28,0x29,0x2A,0x31,0x32,0x33,0x35,0x36,0x37,
	0x38,0x39,0x3B,0x3C,0x3E,0x3F,0x40,0x42,0x43,0x44,0x46,0x48,
	0x4A,0x4B,0x4F,0x51,0x52,0x53,0x55,0x57,0x58,0x59,0x5B,0x5D,
	0x5E,0x5F,0x60,0x61,0x62,0x64,0x65,0x66,0x68,0x6A,0x6B
};

static unsigned char slave_address;
unsigned char alert = 0;

/***************************************************************************//**
 * @brief   Configure the C2000 device as a PMBus master
 * @param   PMBusMaster_SlaveAddress The address of the slave device
 * @param	PMBusMaster_Prescale The prescale value to set master communication speed.
 * 				Master frequency = 60000/[(prescale+1)*25] MHz
 * @return  None
 ******************************************************************************/
#warn "Change the GPIOs used for Alert and Control lines to match the desired GPIOs for the application."
void PMBusMaster_Init(unsigned char PMBusMaster_SlaveAddress, unsigned char PMBusMaster_Prescale)
{
	// Control Line functionality GPIO0
	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;	//Enable pullup on GPIO0
	GpioDataRegs.GPASET.bit.GPIO0 = 1;	//Drive line high
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;	//GPIO0 = GPIO0
	GpioCtrlRegs.GPADIR.bit.GPIO0 = 1;	//GPIO0 = output
	  
	// SMBUS Alert functionality (GPIO2 = Alert line)
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;		//Enable pullup on GPIO2
	GpioDataRegs.GPASET.bit.GPIO2 = 1;		//Drive line high
	GpioCtrlRegs.GPAQSEL1.bit.GPIO2 = 0;	//SYNC to SYSCLKOUT
	GpioCtrlRegs.GPACTRL.bit.QUALPRD0 = 0;	//no qualification (SYNC to SYSCLKOUT)
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;		//GPIO2 = GPIO2
	GpioCtrlRegs.GPADIR.bit.GPIO2 = 0;		//GPIO2 = input
	  
	//setup interrupt triggered by Alert line 
	EALLOW;									// This is needed to write to EALLOW protected registers
	PieVectTable.XINT1 = &xint1_isr;
	EDIS;									// This is needed to disable write to EALLOW protected registers 
	GpioIntRegs.GPIOXINT1SEL.all = 2;		//Make GPIO2 input source for XINT1
	XIntruptRegs.XINT1CR.bit.POLARITY = 2;	//XINT1 triggered by falling edge (high-to-low-transition)
	  
	slave_address = PMBusMaster_SlaveAddress;
	I2CMaster_Init(PMBusMaster_SlaveAddress, PMBusMaster_Prescale);		// Initialize USCI module
	while(!I2CMaster_SlavePresent(slave_address));		//check if slave device present
	 
	// Enable Alert line interrupt
	XIntruptRegs.XINT1CR.bit.ENABLE = 1;	//Enable XINT1 interrupt  
	// Enable XINT1 interrupt in the PIE: Group 1 interrupt 4
	PieCtrlRegs.PIEIER1.bit.INTx4 = 1;
	// Enable CPU INT1 which is connected to PIE group 1
	IER |= M_INT1;
	  
	while (I2CMaster_NotReady());           // Is the bus free?
}

/***************************************************************************//**
 * @brief   Perform a PMBus transaction as a master.
 * @param   PMBusMaster_CommandByte PMBus command index.
 * @param	PMBusMaster_RWFlag The Read/Write flag (R = 1, W = 0)
 * @param	PMBusMaster_Message The message to write, if any.
 * @param	*PMBusMaster_ReceivedValue Pointer to structure to store received data.
 * @return  Success/Failure (Success = 1, Failure = 0)
 ******************************************************************************/
unsigned char PMBusMaster(unsigned char PMBusMaster_CommandByte, unsigned char PMBusMaster_RWFlag, unsigned int PMBusMaster_Message,unsigned char *PMBusMaster_ReceivedValue)
{	  
	unsigned char PMBusMaster_TransmitBuffer[4];
	unsigned char PMBusMaster_ReceiveBuffer[5];
	unsigned char PMBusMaster_RxCount = 0;
	unsigned int PMBusMaster_Temp = 0;
	unsigned char PMBusMaster_Index;
	unsigned char PMBusMaster_CommandGroup;
	
	#if PEC  //PEC variables
		unsigned char PMBusMaster_CrcMsgSize = 0;
		unsigned char PMBusMaster_CrcMsg[5];
		unsigned char PMBusMaster_CrcMasterGenerated = 0;
		unsigned char PMBusMaster_CrcSlaveGenerated = 0;
		unsigned char PMBusMaster_Result = 0;
		
		PMBusMaster_CrcMsg[0] = slave_address << 1;		// 1st CRC byte = slave address...
	#endif
	  
	PMBusMaster_Index = PMBusMaster_CommandByte;                     	// Store PMBus command byte as ...
	PMBusMaster_TransmitBuffer[0] = PMBus_Commands[PMBusMaster_Index];	//...1st byte in Tx buffer	
	PMBusMaster_Temp = PMBusMaster_Message;
	  
	PMBusMaster_TransmitBuffer[1] = PMBusMaster_Message & 0x00FF;	//store lower byte of message
	PMBusMaster_Temp = (PMBusMaster_Message) >> 8;
	PMBusMaster_TransmitBuffer[2] = PMBusMaster_Temp;				// store higher byte of message
	
	if(PMBusMaster_Index > 0 && PMBusMaster_Index < 13)			//read byte from slave device
	    PMBusMaster_CommandGroup = READBYTE;
	if(PMBusMaster_Index > 12 && PMBusMaster_Index < 40)		// read word from slave device
	    PMBusMaster_CommandGroup = READWORD;
	if(PMBusMaster_Index > 39 && PMBusMaster_Index < 44)		// write byte to slave device
	    PMBusMaster_CommandGroup = WRITEBYTE;
	if(PMBusMaster_Index > 43 && PMBusMaster_Index < 49)		// send byte to slave device
	    PMBusMaster_CommandGroup = SENDBYTE;
	/* Read or write one byte of data. R/W oprn. decided based on RWFlag *******/
	if(PMBusMaster_Index > 48 && PMBusMaster_Index < 69) 
	{
		if (PMBusMaster_RWFlag == 0)				// write byte
			PMBusMaster_CommandGroup = WRITEBYTE;
		else										// read byte
			PMBusMaster_CommandGroup = READBYTE;
	}
	/* Read or write one word of data. R/W oprn. decided based on RWFlag *******/
	if(PMBusMaster_Index > 68 && PMBusMaster_Index < 120)		// R/W Word
	{
		if (PMBusMaster_RWFlag == 0)             	// write word (new command group)
	    	PMBusMaster_CommandGroup = WRITEWORD;
	    else                                    	// read word
	    	PMBusMaster_CommandGroup = READWORD; 
    }
	if(PMBusMaster_Index >= 120)
		while(1);						//illegal index - invalid command trap
	
	switch(PMBusMaster_CommandGroup)
	{
		#if !PEC
			case READBYTE: // read byte
	        		PMBusMaster_RxCount = 1;
	        		while (I2CMaster_NotReady());
	        		I2CMaster_Transmit(1,PMBusMaster_TransmitBuffer,1,PMBusMaster_ReceiveBuffer);      
	        		break;           
	           
			case READWORD:  // read word
					PMBusMaster_RxCount = 2;
					while (I2CMaster_NotReady());
					I2CMaster_Transmit(1,PMBusMaster_TransmitBuffer,2,PMBusMaster_ReceiveBuffer);                         
			        break;
			        
			case WRITEBYTE: // write byte
					while (I2CMaster_NotReady() );
					I2CMaster_Transmit(2,PMBusMaster_TransmitBuffer,0,0);        
			        break;
			case SENDBYTE:  // send byte   
					while (I2CMaster_NotReady());
					I2CMaster_Transmit(1,PMBusMaster_TransmitBuffer,0,0);       
			        break;
			case WRITEWORD:  // write word
					while (I2CMaster_NotReady());
					I2CMaster_Transmit(3,PMBusMaster_TransmitBuffer,0,0);      
			        break;
		#else
			case READBYTE:					// read byte
		            PMBusMaster_RxCount = 1;
		            while (I2CMaster_NotReady());
		            I2CMaster_Transmit(1,PMBusMaster_TransmitBuffer,2,PMBusMaster_ReceiveBuffer);  
		            
		            /* Assembling bit stream for CRC check*/
		            PMBusMaster_CrcMsg[1] = PMBusMaster_TransmitBuffer[0];  		// store first tx byte
		            PMBusMaster_CrcMsg[2] = (slave_address << 1) + 1;				// store slave addres + R/W=1
		            PMBusMaster_CrcMsg[3] = PMBusMaster_ReceiveBuffer[0];   		// store rx byte 1
		            PMBusMaster_CrcSlaveGenerated = PMBusMaster_ReceiveBuffer[1]; 	//store PEC byte from slave
		            PMBusMaster_CrcMsgSize = 4;                 					// # of bytes
		            
		            /* CRC function call, generate CRC byte to compare with slave CRC*/
		            PMBusMaster_CrcMasterGenerated = PMBusMaster_Crc8MakeBitwise(CRC8_INIT_REM,CRC8_POLY,PMBusMaster_CrcMsg,PMBusMaster_CrcMsgSize);
		            if (PMBusMaster_CrcMasterGenerated == PMBusMaster_CrcSlaveGenerated)	//compare the PEC bytes
		            	PMBusMaster_Result = PEC_PASS;            // PEC byte was validated
		            else
		            	PMBusMaster_Result = PEC_FAIL;            // failed PEC test   
					break;           
	           
	  		case READWORD:						// read word
		            PMBusMaster_RxCount = 2;
		            while (I2CMaster_NotReady());
		            I2CMaster_Transmit(1,PMBusMaster_TransmitBuffer,3,PMBusMaster_ReceiveBuffer);  
		            
		            /* Assembling bit stream for CRC check*/
		            PMBusMaster_CrcMsg[1] = PMBusMaster_TransmitBuffer[0];
		            PMBusMaster_CrcMsg[2] = (slave_address << 1) + 1;				// store slave address + R/W=1
		            PMBusMaster_CrcMsg[3] = PMBusMaster_ReceiveBuffer[0];
		            PMBusMaster_CrcMsg[4] = PMBusMaster_ReceiveBuffer[1];
		            PMBusMaster_CrcSlaveGenerated = PMBusMaster_ReceiveBuffer[2];	//store PEC byte from slave
		            PMBusMaster_CrcMsgSize = 5;
		            
		            /* CRC function call, generate CRC byte to compare with slave CRC*/
		            PMBusMaster_CrcMasterGenerated = PMBusMaster_Crc8MakeBitwise(CRC8_INIT_REM,CRC8_POLY,PMBusMaster_CrcMsg,PMBusMaster_CrcMsgSize);	            
		            if (PMBusMaster_CrcMasterGenerated == PMBusMaster_CrcSlaveGenerated)
		                 PMBusMaster_Result = PEC_PASS;
		            else
		                 PMBusMaster_Result = PEC_FAIL;                       
					break;
	          
			case WRITEBYTE:						// write byte
		  			/* CRC function call, generate CRC byte to transmit to slave device*/
		            PMBusMaster_CrcMsg[1] = PMBusMaster_TransmitBuffer[0];
		            PMBusMaster_CrcMsg[2] = PMBusMaster_TransmitBuffer[1];
		            PMBusMaster_CrcMsgSize = 3;
		            PMBusMaster_CrcMasterGenerated = PMBusMaster_Crc8MakeBitwise(CRC8_INIT_REM,CRC8_POLY,PMBusMaster_CrcMsg,PMBusMaster_CrcMsgSize);
		            PMBusMaster_TransmitBuffer[2] = PMBusMaster_CrcMasterGenerated;
		            
		            while (I2CMaster_NotReady() );
		            I2CMaster_Transmit(3,PMBusMaster_TransmitBuffer,0,0); 
		            
		            //check if the slave verified the PEC byte
		            if(alert == 0)	
		            	PMBusMaster_Result = PEC_PASS;
		            else
		            	PMBusMaster_Result = PEC_FAIL;              
					break;
	          
	  		case SENDBYTE:						// send byte  
		  			/* CRC function call, generate CRC byte to transmit to slave device*/
		            PMBusMaster_CrcMsg[1] = PMBusMaster_TransmitBuffer[0];
		            PMBusMaster_CrcMsgSize = 2;
		            PMBusMaster_CrcMasterGenerated = PMBusMaster_Crc8MakeBitwise(CRC8_INIT_REM,CRC8_POLY,PMBusMaster_CrcMsg,PMBusMaster_CrcMsgSize);
		            PMBusMaster_TransmitBuffer[1] = PMBusMaster_CrcMasterGenerated; 
		            
		            while (I2CMaster_NotReady());
		            I2CMaster_Transmit(2,PMBusMaster_TransmitBuffer,0,0);  
	 
		            //check if the slave verified the PEC byte
		            if(alert == 0)	
		            	PMBusMaster_Result = PEC_PASS;
		            else
		            	PMBusMaster_Result = PEC_FAIL; 
					break;
	          
			case WRITEWORD:						// write word
		  			/* CRC function call, generate CRC byte to transmit to slave device*/
		            PMBusMaster_CrcMsg[1] = PMBusMaster_TransmitBuffer[0];
		            PMBusMaster_CrcMsg[2] = PMBusMaster_TransmitBuffer[1];
		            PMBusMaster_CrcMsg[3] = PMBusMaster_TransmitBuffer[2];
		            PMBusMaster_CrcMsgSize = 4;
		            PMBusMaster_CrcMasterGenerated = PMBusMaster_Crc8MakeBitwise(CRC8_INIT_REM,CRC8_POLY,PMBusMaster_CrcMsg,PMBusMaster_CrcMsgSize);
		            PMBusMaster_TransmitBuffer[3] = PMBusMaster_CrcMasterGenerated;
		            
		            while (I2CMaster_NotReady());
		            I2CMaster_Transmit(4,PMBusMaster_TransmitBuffer,0,0);
		            
		            //check if the slave verified the PEC byte
		            if(alert == 0)	
		            	PMBusMaster_Result = PEC_PASS;
		            else
		            	PMBusMaster_Result = PEC_FAIL; 
					break;
		#endif
			    
		default:
				break;
	}
	if (PMBusMaster_ReceivedValue !=0)
	{
		*PMBusMaster_ReceivedValue++ = PMBusMaster_ReceiveBuffer[0];
		if (PMBusMaster_RxCount > 1)
			*PMBusMaster_ReceivedValue = PMBusMaster_ReceiveBuffer[1];
	}
	#if PEC
		return PMBusMaster_Result;	//When PEC is implemented, return the result of the packet error checking (0 = failure, 1 = success)
	#else
		return 1;	//When PEC is not implemented, return a 1 for completed communication
	#endif
}

#if PEC
/***************************************************************************//**
 * @brief   Calculate the Packet Error Checking byte.
 * @param   PMBusMaster_CRC Initial value.
 * @param	PMBusMaster_Poly The polynomial to use for the calculation.
 * @param	*PMBusMaster_PMsg Pointer to the bytes from the PMBus transaction.
 * @param	PMBusMaster_MsgSize Number of bytes in the last transaction.
 * @return  The PEC byte.
 ******************************************************************************/
static unsigned char PMBusMaster_Crc8MakeBitwise(unsigned char PMBusMaster_CRC, unsigned char PMBusMaster_Poly, unsigned char *PMBusMaster_Pmsg, unsigned int PMBusMaster_MsgSize)
{
    unsigned int i, j, carry;
    unsigned char msg;

    PMBusMaster_CRC = *PMBusMaster_Pmsg++;			// first byte loaded in "crc"		
    for(i = 0 ; i < PMBusMaster_MsgSize-1 ; i ++)
    {
        msg = *PMBusMaster_Pmsg++;					// next byte loaded in "msg"
        
		for(j = 0 ; j < 8 ; j++)
    	{
	    	carry = PMBusMaster_CRC & 0x80;								// check if MSB=1			
	        PMBusMaster_CRC = (PMBusMaster_CRC << 1) | (msg >> 7);		// Shift 1 bit of next byte into crc
	        if(carry) PMBusMaster_CRC ^= PMBusMaster_Poly;      		// If MSB = 1, perform XOR
				msg <<= 1;                  							// Shift left msg byte by 1
				msg &= 0x00FF;
        }
    }
	// The previous loop computes the CRC of the input bit stream. To this, 
    // 8 trailing zeros are padded and the CRC of the resultant value is 
    // computed. This gives the final CRC of the input bit stream.
	for(j = 0 ; j < 8 ; j++)
    {
		carry = PMBusMaster_CRC & 0x80;
		PMBusMaster_CRC <<= 1;
		if(carry) PMBusMaster_CRC ^= PMBusMaster_Poly;
    }
    
    PMBusMaster_CRC &= 0x00FF;		//We only want one byte (lower)
    
    return(PMBusMaster_CRC);
}
#endif

/***************************************************************************//**
 * @brief   Handles the Alert line interrupt.
 * 			Code should be altered by user to implement application-appropriate fault handling
 * @param   None
 * @return  None
 ******************************************************************************/
#warn "The user should alter the ISR to implement application-appropriate fault handling."
interrupt void xint1_isr(void)
{
	alert = 1;	//received an alert
	XIntruptRegs.XINT1CR.bit.ENABLE = 0;		//Disable XINT1 interrupt 
	while(1);	//Trap for fault. User can add code to service the fault instead, according to their application
}



