/*******************************************************************************
 *
 * PMBusSlave.c -	This program is a software implementation of PMBus over I2C, 
 *					with the Piccolo device acting as the PMBus slave.
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
#include "DSP2803x_Device.h"     // DSP280x Headerfile Include File
#include "DSP2803x_Examples.h"   // DSP280x Examples Include File
#include "DSP2803x_I2C_defines.h"
#include "PMBusSlave.h"
#include "PMBus.h"

struct STATUS_REGS StatusRegs;

//This array contains all of the PMBus command bytes (according to the PMBus spec)
//indexed by the command indeces defined in PMBus.h
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

unsigned char PMBusSlave_ReceiveBuffer[2] = {0,0};
unsigned char PMBusSlave_TransmitBuffer[2] = {0xAB,0xCD};
unsigned char PMBusSlave_Index = 0;
unsigned char PMBusSlave_DummyCommand = 0;

////////////USER CODE////////////
//Example variables, should be changed by user to be application specific
#warn	"User should declare application specific PMBus registers or variables."
//initial values
unsigned char Temperature = 0x12;	//STATUS_TEMPERATURE command (R byte)
unsigned char Default_Code = 0;		//STORE_DEFAULT_CODE command (W byte)
unsigned char Operation = 0x34;		//OPERATION command (R/W byte)
unsigned int Status_Word = 0x5678;	//STATUS_WORD command (R word)
unsigned char Status_Byte = 0x00;	//STATUS_BYTE command (R byte)
unsigned char Status_Cml = 0x00;	//STATUS_CML command (R byte)
unsigned int Vout_Command = 0x90AB;	//VOUT_COMMAND command (R/W word)
////////////END USER CODE////////

/***************************************************************************//**
 * @brief   Initialize I2C module in slave mode.
 * @param   I2CSlave_OwnAddress The slave device's own address.
 * @return  None
 ******************************************************************************/
void I2CSlave_Init(Uint16 I2CSlave_OwnAddress)
{
	//Setup Cpu Timer 0 interrupt
	EALLOW;	// This is needed to write to EALLOW protected registers
	PieVectTable.TINT0 = &cpu_timer0_isr;
	EDIS;   // This is needed to disable write to EALLOW protected registers 
	// Enable TINT0 in the PIE: Group 1 interrupt 7
   	PieCtrlRegs.PIEIER1.bit.INTx7 = 1;
	// Enable CPU int1 which is connected to CPU-Timer 0
   	IER |= M_INT1;
   
	InitI2CGpio();
	InitCpuTimers();
	
	ConfigCpuTimer(&CpuTimer0, 60, 35000);	//CPU Timer 0 interrupt after 35 ms (at 60MHz CPU freq.)
	
	// Initialize I2C
	I2caRegs.I2COAR = I2CSlave_OwnAddress;		// Own address
	I2caRegs.I2CPSC.all = 9;		// Prescaler - need 7-12 Mhz on module clk
	I2caRegs.I2CCLKL = 10;			// NOTE: must be non zero
	I2caRegs.I2CCLKH = 5;			// NOTE: must be non zero

	I2caRegs.I2CIER.all = 0x00;		// Clear interrupts - polling based method

	I2caRegs.I2CMDR.all = 0x0020;	// Take I2C out of reset
   									// Stop I2C when suspended
	return;   
}

/***************************************************************************//**
 * @brief   Configure the C2000 device as a PMBus slave.
 * @param   PMBusSlave_DeviceAddress The slave device's own address.
 * @return  None
 ******************************************************************************/
#warn "Change the GPIOs used for Alert and Control lines to match the desired GPIOs for the application."
void PMBusSlave_Init(unsigned char PMBusSlave_DeviceAddress)
{	
	StatusRegs.StatusWord.all = 0;			//Clear status bits for the status registers we are using
	StatusRegs.StatusCml.all = 0;
	
	// Control Line functionality GPIO0
	GpioCtrlRegs.GPAPUD.bit.GPIO0 = 0;		//Enable pullup on GPIO0
	GpioDataRegs.GPASET.bit.GPIO0 = 1;		//Drive line high
	GpioCtrlRegs.GPAQSEL1.bit.GPIO0 = 0;	//SYNC to SYSCLKOUT
	GpioCtrlRegs.GPACTRL.bit.QUALPRD0 = 0;	//no qualification (SYNC to SYSCLKOUT)
	GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;		//GPIO0 = GPIO0
	GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;		//GPIO0 = input
	 
	// SMBUS Alert functionality (GPIO2 = Alert line)
	GpioCtrlRegs.GPAPUD.bit.GPIO2 = 0;		//Enable pullup on GPIO2
	GpioDataRegs.GPASET.bit.GPIO2 = 1;		//Drive line high
	GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 0;		//GPIO2 = GPIO2
	GpioCtrlRegs.GPADIR.bit.GPIO2 = 1;		//GPIO2 = output
	
	slave_address = PMBusSlave_DeviceAddress;
	I2CSlave_Init(slave_address);     // Initialize USCI module
}

/***************************************************************************//**
 * @brief   Determine what type of PMBus command was received from the master.
 * 
 * 			The function also prepares data in the transmit buffer to send to 
 * 			the master for supported READ and READ/WRITE commands. Users should modify
 * 			the code to implement their application's supported PMBus commands.
 * @param   PMBusSlave_RxCommand The command byte received from the master.
 * @return  Command group of the received command.
 ******************************************************************************/
unsigned char PMBusSlave_DecodeCommand(unsigned char PMBusSlave_RxCommand)
{
	unsigned char PMBusSlave_CommandGroup;	
	
	for(PMBusSlave_Index = 0; PMBusSlave_Index < 120; PMBusSlave_Index++)
	{
		if(PMBus_Commands[PMBusSlave_Index] == PMBusSlave_RxCommand)
			break;
	}
	
	////////////USER CODE////////////
	#warn	"User should change code to implement their application's supported PMBus commands."
	switch (PMBusSlave_Index)	//should include all user supported commands
	{
		case STATUS_TEMPERATURE:
				PMBusSlave_TransmitBuffer[0] = Temperature;
				break;
		case STORE_DEFAULT_CODE:
				break;
		case OPERATION:
				PMBusSlave_TransmitBuffer[0] = Operation;
				break;
		case STATUS_WORD:
				PMBusSlave_TransmitBuffer[0] = Status_Word;	//lower byte
				PMBusSlave_TransmitBuffer[1] = Status_Word >> 8;	//upper byte
				break;
		case VOUT_COMMAND:
				PMBusSlave_TransmitBuffer[0] = Vout_Command;	//lower byte
				PMBusSlave_TransmitBuffer[1] = Vout_Command >> 8;	//upper byte
				break;
		default:
				PMBusSlave_DummyCommand = 1;	//command not supported by this slave
				break;
	}
	////////////END USER CODE////////	
	
	if(PMBusSlave_Index == 0)//dummy byte to check if slave is present
		PMBusSlave_DummyCommand = 1;
	if(PMBusSlave_Index > 0 && PMBusSlave_Index < 13)                  //read byte from slave device
		PMBusSlave_CommandGroup = READBYTE;
	if(PMBusSlave_Index > 12 && PMBusSlave_Index < 40)                 // read word from slave device
		PMBusSlave_CommandGroup = READWORD;
	if(PMBusSlave_Index > 39 && PMBusSlave_Index < 44)                 // write byte to slave device
		PMBusSlave_CommandGroup = WRITEBYTE;
	if(PMBusSlave_Index > 43 && PMBusSlave_Index < 49)                 // send byte to slave device
		PMBusSlave_CommandGroup = SENDBYTE;
	/* Read or write one byte of data. R/W oprn. decided based on RWFlag *******/
	if(PMBusSlave_Index > 48 && PMBusSlave_Index < 69) 
	{
	    PMBusSlave_CommandGroup = RWBYTE;
	}
	/* Read or write one word of data. R/W oprn. decided based on RWFlag *******/
	if(PMBusSlave_Index > 68 && PMBusSlave_Index < 120)                // R/W Word
	{
	    PMBusSlave_CommandGroup = RWWORD;
	}
	if(PMBusSlave_Index >= 120)
		while(1);                               //illegal index - invalid command trap
		
	return PMBusSlave_CommandGroup;
}

/***************************************************************************//**
 * @brief   Receives a command from the master and performs reads and writes accordingly.
 * 
 * 			This function should be modified by the user for their application's 
 * 			supported commands to make function calls to carry out the commands
 * 			(e.g. adjusting fan speed)
 * @param   None
 * @return  None
 ******************************************************************************/
void PMBusSlave(void)
{
	unsigned char PMBusSlave_Command = 0, PMBusSlave_CommandType = 0;
	
	#if PEC
		unsigned char PMBusSlave_CrcMsgSize = 0;
	  	unsigned char PMBusSlave_CrcMsg[5];
	  	unsigned char PMBusSlave_CrcMasterGenerated = 0;
	  	unsigned char PMBusSlave_CrcSlaveGenerated = 0;
	
		PMBusSlave_CrcMsg[0] = slave_address << 1; 
	#endif
	
	//first get the command byte
	
	while(!I2caRegs.I2CSTR.bit.RRDY);		//wait until data ready
	PMBusSlave_Command = I2caRegs.I2CDRR;	//get the received data
	
	StartCpuTimer0();						// Start the timer
	//next determine the command type
	PMBusSlave_CommandType = PMBusSlave_DecodeCommand(PMBusSlave_Command);
	//send/receive according to command
	if(!PMBusSlave_DummyCommand)
	{
		switch(PMBusSlave_CommandType)
		{
			#if !PEC	//Implementation without Packet Error Checking
				case READBYTE: // master reading byte from slave
						while(!I2caRegs.I2CSTR.bit.XRDY);	//make sure I2CDXR is clear
				        I2caRegs.I2CDXR = PMBusSlave_TransmitBuffer[0];	//send the data   
				        StopCpuTimer0();				//No timeout, so stop the timer
						ReloadCpuTimer0();				//Reload the period value (35 ms timeout)  
				        break;           
				           
				case READWORD:  // master reading word from slave
				        while(!I2caRegs.I2CSTR.bit.XRDY);	//make sure I2CDXR is clear
				        I2caRegs.I2CDXR = PMBusSlave_TransmitBuffer[0];	//send the lower byte of data
				        StopCpuTimer0();				//No timeout, so stop the timer
						ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
				        while(!I2caRegs.I2CSTR.bit.XRDY);	//make sure I2CDXR is clear
				        I2caRegs.I2CDXR = PMBusSlave_TransmitBuffer[1];	//send the upper byte of data             
						break;
				          
				case WRITEBYTE: // master writing byte to slave
						while(!I2caRegs.I2CSTR.bit.RRDY);				//wait for the data
				        PMBusSlave_ReceiveBuffer[0] = I2caRegs.I2CDRR;	//get the received data
				        StopCpuTimer0();				//No timeout, so stop the timer
						ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
				        break;
				          
				case SENDBYTE:  	//we already received the command.
						StopCpuTimer0();				//No timeout, so stop the timer
						ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
				        break;	//User could insert handling code here.
				          
				case WRITEWORD:  // master writing word to slave
				        while(!I2caRegs.I2CSTR.bit.RRDY);				//wait for the data
				        PMBusSlave_ReceiveBuffer[0] = I2caRegs.I2CDRR;	//get the lower byte of received data
				        StopCpuTimer0();				//No timeout, so stop the timer
						ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
				        while(!I2caRegs.I2CSTR.bit.RRDY);				//wait for the data
				        PMBusSlave_ReceiveBuffer[1] = I2caRegs.I2CDRR;	//get the upper byte of received data
				        break;
				          
				case RWBYTE:	//read/write byte
						while(!I2caRegs.I2CSTR.bit.AAS);	//wait until addressed by master
				  		if (I2caRegs.I2CSTR.bit.SDIR == 0)	//determine if slave should send/receive
						{	//slave receiver
				  			while(!I2caRegs.I2CSTR.bit.RRDY);				//wait for the data
				         	PMBusSlave_ReceiveBuffer[0] = I2caRegs.I2CDRR;	//get the received data
				  			StopCpuTimer0();				//No timeout, so stop the timer
							ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
				  		}
				  		else	
				  		{	//slave transmitter
				  			while(!I2caRegs.I2CSTR.bit.XRDY);				//make sure I2CDXR is clear
				        	I2caRegs.I2CDXR = PMBusSlave_TransmitBuffer[0];	//send the data
				  			StopCpuTimer0();				//No timeout, so stop the timer
							ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
				  		}	  				            	
				        break;  
				          	
				case RWWORD:	//read/write word
				  		while(!I2caRegs.I2CSTR.bit.AAS);	//wait until addressed by master
				  		if (I2caRegs.I2CSTR.bit.SDIR == 0)	//determine if slave should send/receive
				  		{	//slave receiver
			  				while(!I2caRegs.I2CSTR.bit.RRDY);				//wait for the data
			            	PMBusSlave_ReceiveBuffer[0] = I2caRegs.I2CDRR;	//get the first byte of received data
			            	StopCpuTimer0();				//No timeout, so stop the timer
							ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
			            	while(!I2caRegs.I2CSTR.bit.RRDY);				//wait for the data
			            	PMBusSlave_ReceiveBuffer[1] = I2caRegs.I2CDRR;	//get the second byte of received data
			  			}
			  			else	
			  			{	//slave transmitter
			  				while(!I2caRegs.I2CSTR.bit.XRDY);				//make sure I2CDXR is clear
			            	I2caRegs.I2CDXR = PMBusSlave_TransmitBuffer[0];	//send the first byte of data
			            	StopCpuTimer0();				//No timeout, so stop the timer
							ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
			            	while(!I2caRegs.I2CSTR.bit.XRDY);				//make sure I2CDXR is clear
			            	I2caRegs.I2CDXR = PMBusSlave_TransmitBuffer[1];	//send the second byte of data
			  			}	  				            	
						break;			
			#else		//Implementation with Packet Error Checking
				case READBYTE: // master reading byte from slave
						//setup PEC byte
						PMBusSlave_CrcMsg[1] = PMBusSlave_Command;  			// store first rx byte
		            	PMBusSlave_CrcMsg[2] = (slave_address << 1) + 1;		// store slave address + R/W=1
		            	PMBusSlave_CrcMsg[3] = PMBusSlave_TransmitBuffer[0];	// store tx byte 1
		            	PMBusSlave_CrcMsgSize = 4;
						PMBusSlave_CrcSlaveGenerated = PMBusSlave_Crc8MakeBitwise(CRC8_INIT_REM, CRC8_POLY, PMBusSlave_CrcMsg, PMBusSlave_CrcMsgSize);
						
						while(!I2caRegs.I2CSTR.bit.XRDY);				//make sure I2CDXR is clear
				        I2caRegs.I2CDXR = PMBusSlave_TransmitBuffer[0];	//send the data   
				        StopCpuTimer0();				//No timeout, so stop the timer
						ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
				        while(!I2caRegs.I2CSTR.bit.XRDY);				//make sure I2CDXR is clear 
				        I2caRegs.I2CDXR = PMBusSlave_CrcSlaveGenerated;	//send the PEC byte   
				        break;           
				           
				case READWORD:  // master reading word from slave
						//setup PEC byte
				        PMBusSlave_CrcMsg[1] = PMBusSlave_Command;  			// store first rx byte
		            	PMBusSlave_CrcMsg[2] = (slave_address << 1) + 1;		// store slave address + R/W=1
		            	PMBusSlave_CrcMsg[3] = PMBusSlave_TransmitBuffer[0];	// store tx byte 1
		            	PMBusSlave_CrcMsg[4] = PMBusSlave_TransmitBuffer[1];   	// store tx byte 2
		            	PMBusSlave_CrcMsgSize = 5;
						PMBusSlave_CrcSlaveGenerated = PMBusSlave_Crc8MakeBitwise(CRC8_INIT_REM, CRC8_POLY, PMBusSlave_CrcMsg, PMBusSlave_CrcMsgSize);
						
				        while(!I2caRegs.I2CSTR.bit.XRDY);				//make sure I2CDXR is clear
				        I2caRegs.I2CDXR = PMBusSlave_TransmitBuffer[0];	//send the lower byte of data
				        StopCpuTimer0();				//No timeout, so stop the timer
						ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
				        while(!I2caRegs.I2CSTR.bit.XRDY);				//make sure I2CDXR is clear
				        I2caRegs.I2CDXR = PMBusSlave_TransmitBuffer[1];	//send the upper byte of data             
						while(!I2caRegs.I2CSTR.bit.XRDY);				//make sure I2CDXR is clear 
				        I2caRegs.I2CDXR = PMBusSlave_CrcSlaveGenerated;	//send the PEC byte 
						break;
				          
				case WRITEBYTE: // master writing byte to slave
						while(!I2caRegs.I2CSTR.bit.RRDY);					//wait for the data
				        PMBusSlave_ReceiveBuffer[0] = I2caRegs.I2CDRR;		//get the received data
	     			    StopCpuTimer0();				//No timeout, so stop the timer
						ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
	     			    while(!I2caRegs.I2CSTR.bit.RRDY);					//wait for the data
				        PMBusSlave_CrcMasterGenerated = I2caRegs.I2CDRR;	//get the received PEC byte from master
				        
				        //calculate PEC byte for comparison
			            PMBusSlave_CrcMsg[1] = PMBusSlave_Command;			// store first rx byte
			            PMBusSlave_CrcMsg[2] = PMBusSlave_ReceiveBuffer[0];	// store rx byte
			            PMBusSlave_CrcMsgSize = 3;                 			// # of bytes
			            PMBusSlave_CrcSlaveGenerated = PMBusSlave_Crc8MakeBitwise(CRC8_INIT_REM, CRC8_POLY, PMBusSlave_CrcMsg, PMBusSlave_CrcMsgSize);          
				        
				        //if the bytes do not match, respond according to the PMBus Spec.
				        if(PMBusSlave_CrcSlaveGenerated != PMBusSlave_CrcMasterGenerated)	//compare received PEC byte with calculated PEC byte
				   		{			   			
				   			//Flush the received command byte and any received data
				   			PMBusSlave_Command = 0;				//flush command byte
				   			PMBusSlave_Index = 0;				//clear index so no data is stored
				   			PMBusSlave_ReceiveBuffer[0] = 0;	//flush received data byte
				   			
				   			//Set status bits
				   			StatusRegs.StatusWord.StatusByte.bit.CML = 1;				//set the CML bit
				   			StatusRegs.StatusCml.bit.PACKET_ERROR_CHECK_FAILED = 1;		//set the PEC failed bit
				   			
				   			//signal the master via the Alert line
				   			GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;		//Drive line low
				   		}
				        break;
				          
				case SENDBYTE:  	//we already received the command.
						while(!I2caRegs.I2CSTR.bit.RRDY);					//wait for the data
				        PMBusSlave_CrcMasterGenerated = I2caRegs.I2CDRR;	//get the received PEC byte from master
						StopCpuTimer0();				//No timeout, so stop the timer
						ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
						
						//calculate PEC byte for comparison
			            PMBusSlave_CrcMsg[1] = PMBusSlave_Command;	// store first rx byte
			            PMBusSlave_CrcMsgSize = 2;                 	// # of bytes
			            PMBusSlave_CrcSlaveGenerated = PMBusSlave_Crc8MakeBitwise(CRC8_INIT_REM, CRC8_POLY, PMBusSlave_CrcMsg, PMBusSlave_CrcMsgSize);         
				        
				        //if the bytes do not match, respond according to the PMBus Spec.
				        if(PMBusSlave_CrcSlaveGenerated != PMBusSlave_CrcMasterGenerated)	//compare received PEC byte with calculated PEC byte
				   		{			   			
				   			//Flush the received command byte
				   			PMBusSlave_Command = 0;			//flush command byte
				   			PMBusSlave_Index = 0;			//clear index so no data is stored
				   			
				   			//Set status bits
				   			StatusRegs.StatusWord.StatusByte.bit.CML = 1;				//set the CML bit
				   			StatusRegs.StatusCml.bit.PACKET_ERROR_CHECK_FAILED = 1;		//set the PEC failed bit
				   			
				   			//signal the master via the Alert line
				   			GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;		//Drive line low
				   		}		        
				        break;	//User could insert handling code here.
				        
				case WRITEWORD:  // master writing word to slave
				        while(!I2caRegs.I2CSTR.bit.RRDY);					//wait for the data
				        PMBusSlave_ReceiveBuffer[0] = I2caRegs.I2CDRR;		//get the lower byte of received data
				        StopCpuTimer0();				//No timeout, so stop the timer
						ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
				        while(!I2caRegs.I2CSTR.bit.RRDY);					//wait for the data
				        PMBusSlave_ReceiveBuffer[1] = I2caRegs.I2CDRR;		//get the upper byte of received data			        
				        while(!I2caRegs.I2CSTR.bit.RRDY);					//wait for the data
				        PMBusSlave_CrcMasterGenerated = I2caRegs.I2CDRR;	//get the received PEC byte from master
				        
				        //calculate PEC byte for comparison
			            PMBusSlave_CrcMsg[1] = PMBusSlave_Command;			// store first rx byte
			            PMBusSlave_CrcMsg[2] = PMBusSlave_ReceiveBuffer[0];	// store rx byte
			            PMBusSlave_CrcMsg[3] = PMBusSlave_ReceiveBuffer[1];	// store rx byte
			            PMBusSlave_CrcMsgSize = 4;                 			// # of bytes
			            PMBusSlave_CrcSlaveGenerated = PMBusSlave_Crc8MakeBitwise(CRC8_INIT_REM, CRC8_POLY, PMBusSlave_CrcMsg, PMBusSlave_CrcMsgSize);          			        
				        
				        //if the bytes do not match, respond according to the PMBus Spec.
				        if(PMBusSlave_CrcSlaveGenerated != PMBusSlave_CrcMasterGenerated)	//compare received PEC byte with calculated PEC byte
				   		{			   			
				   			//Flush the received command byte and any received data
				   			PMBusSlave_Command = 0;				//flush command byte
				   			PMBusSlave_Index = 0;				//clear index so no data is stored
				   			PMBusSlave_ReceiveBuffer[0] = 0;	//flush received data bytes
				   			PMBusSlave_ReceiveBuffer[1] = 0;
				   			
				   			//Set status bits
				   			StatusRegs.StatusWord.StatusByte.bit.CML = 1;			//set the CML bit
				   			StatusRegs.StatusCml.bit.PACKET_ERROR_CHECK_FAILED = 1;	//set the PEC failed bit
				   			
				   			//signal the master via the Alert line
				   			GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;	//Drive line low
				   		}
				        break;
				          
				case RWBYTE:	//read/write byte
						while(!I2caRegs.I2CSTR.bit.AAS);	//wait until addressed by master
				  		if (I2caRegs.I2CSTR.bit.SDIR == 0)	//determine if slave should send/receive
						{	//slave receiver
							while(!I2caRegs.I2CSTR.bit.RRDY);					//wait for the data
					        PMBusSlave_ReceiveBuffer[0] = I2caRegs.I2CDRR;		//get the received data
					        StopCpuTimer0();				//No timeout, so stop the timer
							ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
					        while(!I2caRegs.I2CSTR.bit.RRDY);					//wait for the data
					        PMBusSlave_CrcMasterGenerated = I2caRegs.I2CDRR;	//get the received PEC byte from master
					        
					        //calculate PEC byte for comparison
				            PMBusSlave_CrcMsg[1] = PMBusSlave_Command;  		// store first rx byte
				            PMBusSlave_CrcMsg[2] = PMBusSlave_ReceiveBuffer[0];	// store tx byte
				            PMBusSlave_CrcMsgSize = 3;                 			// # of bytes
				            PMBusSlave_CrcSlaveGenerated = PMBusSlave_Crc8MakeBitwise(CRC8_INIT_REM, CRC8_POLY, PMBusSlave_CrcMsg, PMBusSlave_CrcMsgSize);          				        
					        
					        //if the bytes do not match, respond according to the PMBus Spec.
					        if(PMBusSlave_CrcSlaveGenerated != PMBusSlave_CrcMasterGenerated)	//compare received PEC byte with calculated PEC byte
					   		{			   			
					   			//Flush the received command byte and any received data
					   			PMBusSlave_Command = 0;				//flush command byte
					   			PMBusSlave_Index = 0;				//clear index so no data is stored
					   			PMBusSlave_ReceiveBuffer[0] = 0;	//flush received data byte
					   			
					   			//Set status bits
					   			StatusRegs.StatusWord.StatusByte.bit.CML = 1;				//set the CML bit
					   			StatusRegs.StatusCml.bit.PACKET_ERROR_CHECK_FAILED = 1;		//set the PEC failed bit
					   			
					   			//signal the master via the Alert line
					   			GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;		//Drive line low
					   		}
				  		}
				  		else	
				  		{	//slave transmitter
				  			//setup PEC byte
							PMBusSlave_CrcMsg[1] = PMBusSlave_Command;  			// store first rx byte
			            	PMBusSlave_CrcMsg[2] = (slave_address << 1) + 1;		// store slave address + R/W=1
			            	PMBusSlave_CrcMsg[3] = PMBusSlave_TransmitBuffer[0];   // store tx byte 1
			            	PMBusSlave_CrcMsgSize = 4;
							PMBusSlave_CrcSlaveGenerated = PMBusSlave_Crc8MakeBitwise(CRC8_INIT_REM, CRC8_POLY, PMBusSlave_CrcMsg, PMBusSlave_CrcMsgSize);
							
							while(!I2caRegs.I2CSTR.bit.XRDY);				//make sure I2CDXR is clear
					        I2caRegs.I2CDXR = PMBusSlave_TransmitBuffer[0];	//send the data   
					        StopCpuTimer0();				//No timeout, so stop the timer
							ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
					        while(!I2caRegs.I2CSTR.bit.XRDY);				//make sure I2CDXR is clear 
					        I2caRegs.I2CDXR = PMBusSlave_CrcSlaveGenerated;	//send the PEC byte  
				  		}	  				            	
				        break;  
				          	
				case RWWORD:	//read/write word
				  		while(!I2caRegs.I2CSTR.bit.AAS);	//wait until addressed by master
				  		if (I2caRegs.I2CSTR.bit.SDIR == 0)	//determine if slave should send/receive
				  		{	//slave receiver
			  				while(!I2caRegs.I2CSTR.bit.RRDY);					//wait for the data
					        PMBusSlave_ReceiveBuffer[0] = I2caRegs.I2CDRR;		//get the lower byte of received data
					        StopCpuTimer0();				//No timeout, so stop the timer
							ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
					        while(!I2caRegs.I2CSTR.bit.RRDY);					//wait for the data
					        PMBusSlave_ReceiveBuffer[1] = I2caRegs.I2CDRR;		//get the upper byte of received data			        
					        while(!I2caRegs.I2CSTR.bit.RRDY);					//wait for the data
					        PMBusSlave_CrcMasterGenerated = I2caRegs.I2CDRR;	//get the received PEC byte from master
					        
					        //calculate PEC byte for comparison
				            PMBusSlave_CrcMsg[1] = PMBusSlave_Command;			// store first rx byte
				            PMBusSlave_CrcMsg[2] = PMBusSlave_ReceiveBuffer[0];	// store rx byte
				            PMBusSlave_CrcMsg[3] = PMBusSlave_ReceiveBuffer[1];	// store rx byte
				            PMBusSlave_CrcMsgSize = 4;                 			// # of bytes
				            PMBusSlave_CrcSlaveGenerated = PMBusSlave_Crc8MakeBitwise(CRC8_INIT_REM, CRC8_POLY, PMBusSlave_CrcMsg, PMBusSlave_CrcMsgSize);          			        
					        
					        //if the bytes do not match, respond according to the PMBus Spec.
					        if(PMBusSlave_CrcSlaveGenerated != PMBusSlave_CrcMasterGenerated)	//compare received PEC byte with calculated PEC byte
					   		{			   			
					   			//Flush the received command byte and any received data
					   			PMBusSlave_Command = 0;				//flush command byte
					   			PMBusSlave_Index = 0;				//clear index so no data is stored
					   			PMBusSlave_ReceiveBuffer[0] = 0;	//flush received data bytes
					   			PMBusSlave_ReceiveBuffer[1] = 0;
					   			
					   			//Set status bits
					   			StatusRegs.StatusWord.StatusByte.bit.CML = 1;				//set the CML bit
					   			StatusRegs.StatusCml.bit.PACKET_ERROR_CHECK_FAILED = 1;		//set the PEC failed bit
					   			
					   			//signal the master via the Alert line
					   			GpioDataRegs.GPACLEAR.bit.GPIO2 = 1;		//Drive line low
					   		}	  			
			  			}
			  			else	
			  			{	//slave transmitter
			  				PMBusSlave_CrcMsg[1] = PMBusSlave_Command;  			// store first rx byte
			            	PMBusSlave_CrcMsg[2] = (slave_address << 1) + 1;		// store slave address + R/W=1
			            	PMBusSlave_CrcMsg[3] = PMBusSlave_TransmitBuffer[0];	// store tx byte 1
			            	PMBusSlave_CrcMsg[4] = PMBusSlave_TransmitBuffer[1];	// store tx byte 2
			            	PMBusSlave_CrcMsgSize = 5;
							PMBusSlave_CrcSlaveGenerated = PMBusSlave_Crc8MakeBitwise(CRC8_INIT_REM, CRC8_POLY, PMBusSlave_CrcMsg, PMBusSlave_CrcMsgSize);
							
					        while(!I2caRegs.I2CSTR.bit.XRDY);				//make sure I2CDXR is clear
					        I2caRegs.I2CDXR = PMBusSlave_TransmitBuffer[0];	//send the lower byte of data
					        StopCpuTimer0();				//No timeout, so stop the timer
							ReloadCpuTimer0();				//Reload the period value (35 ms timeout)
					        while(!I2caRegs.I2CSTR.bit.XRDY);				//make sure I2CDXR is clear
					        I2caRegs.I2CDXR = PMBusSlave_TransmitBuffer[1];	//send the upper byte of data             
							while(!I2caRegs.I2CSTR.bit.XRDY);				//make sure I2CDXR is clear 
					        I2caRegs.I2CDXR = PMBusSlave_CrcSlaveGenerated;	//send the PEC byte 
			  			}	  				            	
						break;
			#endif	
			          
			default:
			        break;
		}	
	  
		////////////USER CODE////////////
		//contains what actions to take after getting information from the master,
		//usually where to store received data and what functions to call in response
		#warn	"User should modify code to implement their application's supported PMBus commands."
		switch (PMBusSlave_Index)	//should include all user supported commands
		{
			case STATUS_TEMPERATURE:
					break;
			case STORE_DEFAULT_CODE:
					Default_Code = PMBusSlave_ReceiveBuffer[0];
					break;
			case OPERATION:
					Operation = PMBusSlave_ReceiveBuffer[0];
					break;
			case STATUS_WORD:
					break;
			case VOUT_COMMAND:
					Vout_Command = (PMBusSlave_ReceiveBuffer[1] << 8) | PMBusSlave_ReceiveBuffer[0];
					break;
			default:	//command not supported by this slave
					break;
		}
	  	////////////END USER CODE////////
	}
	else PMBusSlave_DummyCommand = 0;
}

#if PEC
/***************************************************************************//**
 * @brief   Calculate the Packet Error Checking byte.
 * @param   PMBusSlave_CRC Initial value.
 * @param	PMBusSlave_Poly The polynomial to use for the calculation.
 * @param	*PMBusSlave_PMsg Pointer to the bytes from the PMBus transaction.
 * @param	PMBusSlave_MsgSize Number of bytes in the last transaction.
 * @return  The PEC byte.
 ******************************************************************************/
static unsigned short PMBusSlave_Crc8MakeBitwise(unsigned char PMBusSlave_CRC, unsigned char PMBusSlave_Poly, unsigned char *PMBusSlave_Pmsg, unsigned int PMBusSlave_MsgSize)
{
    unsigned int i, j, carry;
    unsigned char msg;

    PMBusSlave_CRC = *PMBusSlave_Pmsg++;        	// first byte loaded in "crc"		
    for(i = 0 ; i < PMBusSlave_MsgSize-1 ; i ++)
    {
        msg = *PMBusSlave_Pmsg++;                   // next byte loaded in "msg"
        
		for(j = 0 ; j < 8 ; j++)
	    {
	  		carry = PMBusSlave_CRC & 0x80;               			// check if MSB=1			
          	PMBusSlave_CRC = (PMBusSlave_CRC << 1) | (msg >> 7);    // Shift 1 bit of next byte into crc
            if(carry) PMBusSlave_CRC ^= PMBusSlave_Poly;      		// If MSB = 1, perform XOR
			msg <<= 1;                  							// Shift left msg byte by 1
			msg &= 0x00FF;
        }
    }
	// The previous loop computes the CRC of the input bit stream. To this, 
    // 8 trailing zeros are padded and the CRC of the resultant value is 
    // computed. This gives the final CRC of the input bit stream.
	for(j = 0 ; j < 8 ; j++)
    {
		carry = PMBusSlave_CRC & 0x80;
		PMBusSlave_CRC <<= 1;
		if(carry) PMBusSlave_CRC ^= PMBusSlave_Poly;
    }	
        
    PMBusSlave_CRC &= 0x00FF;	//We only want one byte (lower)
    
    return(PMBusSlave_CRC);
}
#endif

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

