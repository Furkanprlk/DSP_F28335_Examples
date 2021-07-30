//----------------------------------------------------------------------------------
//	FILE:			endat_commands.c
//
//	Description:	Has funciton definitions to run	Runs endat21 and endat22 command set.
//					These functions are called inside PM_endat22-Main.c
//
//	Version: 		1.0
//
//  Target:  		TMS320F28377D,
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2004-2015
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description / Status
//----------------------------------------------------------------------------------
// Nov 2015  - Example project for PM EnDat22 Library Usage
//----------------------------------------------------------------------------------

#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "endat.h"

uint16_t crc5_result1;	//variable for calculated crc result checking
uint16_t retval;		//used for function return val storage and checks

void endat21_runCommandSet(void) {

//ENCODER_SEND_POSITION_VALUES	0x7		//0b000111
//SELECTION_OF_MEMORY_AREA		0xE		//0b001110
//ENCODER_SEND_PARAMETER			0x23	//0b100011
//ENCODER_RECEIVE_PARAMETER		0x1C	//0b011100
//ENCODER_RECEIVE_TEST_COMMAND	0x31	//0b110001
//ENCODER_SEND_TEST_VALUES		0x15	//0b010101

////************************ ENCODER_SEND_POSITION_VALUES *****************************************////
//	PM_endat22_setupCommand (
//			ENCODER_SEND_POSITION_VALUES, 	- Command
//			0, 								- NA
//			0, 								- NA
//			0);								- no. of additional data : 0 for EnDat21
	retval = PM_endat22_setupCommand (ENCODER_SEND_POSITION_VALUES, 0, 0, 0);
	PM_endat22_startOperation();
//Wait for spiRxFifoIsr to be triggered where dataReady is set to 1
	while (endat22Data.dataReady != 1) {}
//	PM_endat22_receiveData(					- Unpack the received data and populate endat22Data according to the command
//	ENCODER_SEND_POSITION_VALUES, 			- Command
//	0);										- no. of additional data : 0 for EnDat21
	retval = PM_endat22_receiveData(ENCODER_SEND_POSITION_VALUES, 0);
//Calculate CRC for the received data
	crc5_result1 =  PM_endat22_getCrcPos(endat22Data.position_clocks, ENDAT21, endat22Data.position_lo,
					endat22Data.position_hi, endat22Data.error1, endat22Data.error2, endat22CRCtable);
//Check calculated CRC vs received CRC and STOP if they are not matching
	if (!CheckCRC(crc5_result1,endat22Data.data_crc))
	{
		    ESTOP0;
	}
	 DELAY_US(200L); 	//Delay 200us

////************************ SELECTION_OF_MEMORY_AREA *****************************************////
//	PM_endat22_setupCommand (
//			SELECTION_OF_MEMORY_AREA, 		- Command
//			0xA1,							- MRS Code A1 - Select Parameters of Encoder Manufacturer
//			0x5555,							- Any
//			0);								- no. of additional data : 0 for EnDat21
	 retval = PM_endat22_setupCommand (SELECTION_OF_MEMORY_AREA, 0xA1, 0x5555, 0);  //data1=MRS; data2=any
	 PM_endat22_startOperation();
//Wait for spiRxFifoIsr to be triggered where dataReady is set to 1
	 while (endat22Data.dataReady != 1) {}
//	PM_endat22_receiveData(					- Unpack the received data and populate endat22Data according to the command
//	SELECTION_OF_MEMORY_AREA, 				- Command
//	0);										- no. of additional data : 0 for EnDat21
	 retval = PM_endat22_receiveData(SELECTION_OF_MEMORY_AREA, 0);
//Calculate CRC for the received data
	 crc5_result1 =  PM_endat22_getCrcNorm(endat22Data.address, endat22Data.data, endat22CRCtable);
//Check calculated CRC vs received CRC and STOP if they are not matching
	 if (!CheckCRC(crc5_result1,endat22Data.data_crc))
	 {
		     ESTOP0;
	 }

	 DELAY_US(200L); 	//Delay 200us

////************************ ENCODER_SEND_PARAMETER *****************************************////
 //	PM_endat22_setupCommand (
 //			ENCODER_SEND_PARAMETER, 		- Command
 //			0xD,							- Address 0xD - Returns no.of clock pulses needed to shift out position data
 //			0xAAAA,							- Any
 //			0);								- no. of additional data : 0 for EnDat21
	 retval = PM_endat22_setupCommand (ENCODER_SEND_PARAMETER, 0xD, 0xAAAA, 0);	//data1=address; data2=any
	 PM_endat22_startOperation();
//Wait for spiRxFifoIsr to be triggered where dataReady is set to 1
	 while (endat22Data.dataReady != 1) {}
 //	PM_endat22_receiveData(					- Unpack the received data and populate endat22Data according to the command
 //	ENCODER_SEND_PARAMETER, 				- Command
 //	0);										- no. of additional data : 0 for EnDat21
	 retval = PM_endat22_receiveData(ENCODER_SEND_PARAMETER, 0);
//Calculate CRC for the received data
	 crc5_result1 =  PM_endat22_getCrcNorm(endat22Data.address, endat22Data.data, endat22CRCtable);
//Check calculated CRC vs received CRC and STOP if they are not matching
	 if (!CheckCRC(crc5_result1,endat22Data.data_crc))
	 {
		     ESTOP0;
	 }
	 DELAY_US(200L); 	//Delay 200us

////************************ ENCODER_RECEIVE_PARAMETER *****************************************////
 //	PM_endat22_setupCommand (
 //			ENCODER_RECEIVE_PARAMETER, 		- Command
 //			0x0,							- Address 0 - Place the address needed - this is just a template
 //			0x0,							- Place the value of parameter to be sent
 //			0);								- no. of additional data : 0 for EnDat21

	 retval = PM_endat22_setupCommand (ENCODER_RECEIVE_PARAMETER, 0x0, 0x0, 0);  //data1=MRS; data2=any
	 PM_endat22_startOperation();
//Wait for spiRxFifoIsr to be triggered where dataReady is set to 1
	 while (endat22Data.dataReady != 1) {}
 //	PM_endat22_receiveData(					- Unpack the received data and populate endat22Data according to the command
 //	ENCODER_RECEIVE_PARAMETER, 				- Command
 //	0);										- no. of additional data : 0 for EnDat21
	 retval = PM_endat22_receiveData(ENCODER_RECEIVE_PARAMETER, 0);
//Calculate CRC for the received data
	 crc5_result1 =  PM_endat22_getCrcNorm(endat22Data.address, endat22Data.data, endat22CRCtable);
//Check calculated CRC vs received CRC and STOP if they are not matching
	 if (!CheckCRC(crc5_result1,endat22Data.data_crc))
	 {
		     ESTOP0;
	 }
	 DELAY_US(200L); 	//Delay 200us

////************************ ENCODER_RECEIVE_TEST_COMMAND *****************************************////
// Template for sending test command to the encoder - refer to library documentation for details
// Usage similar to the functions described above.
	 retval = PM_endat22_setupCommand (ENCODER_RECEIVE_TEST_COMMAND, 0x1, 0x0, 0);  //data1=MRS; data2=any
	 PM_endat22_startOperation();
	 while (endat22Data.dataReady != 1) {}
	 retval = PM_endat22_receiveData(ENCODER_RECEIVE_TEST_COMMAND, 0);
	 crc5_result1 =  PM_endat22_getCrcNorm(endat22Data.address, endat22Data.data, endat22CRCtable);
	 if (!CheckCRC(crc5_result1,endat22Data.data_crc))
	 {
		     ESTOP0;
	 }
	 DELAY_US(200L); 	//Delay 200us

////************************ ENCODER_SEND_TEST_VALUES *****************************************////
// Template for receiving test values (40-bits) from the encoder - refer to library documentation for details
// Usage similar to the functions described above.
// Note the CRC function used for calculating the CRC of the received test data
	 retval = PM_endat22_setupCommand (ENCODER_SEND_TEST_VALUES, 0x0, 0x0, 0);  //data1=MRS; data2=any
	 PM_endat22_startOperation();
	 while (endat22Data.dataReady != 1) {}
	 retval = PM_endat22_receiveData(ENCODER_SEND_TEST_VALUES, 0);
	 crc5_result1 =  PM_endat22_getCrcTest(endat22Data.test_lo, endat22Data.test_hi, endat22Data.error1, endat22CRCtable);
	 if (!CheckCRC(crc5_result1,endat22Data.data_crc))
	 {
		     ESTOP0;
	 }
	 DELAY_US(200L); 	//Delay 200us
}

void endat22_runCommandSet(void) {
//ENCODER_SEND_POSITION_VALUES_AND_SELECTION_OF_THE_MEMORY_AREA	0x9		//0b001001
//ENCODER_SEND_POSITION_VALUES_AND_RECEIVE_TEST_COMMAND			0x36	//0b110110
//ENCODER_SEND_POSITION_VALUES_AND_RECEIVE_PARAMETER			0x1B	//0b011011
//ENCODER_SEND_POSITION_VALUES_AND_SEND_PARAMETER				0x24	//0b100100
//ENCODER_SEND_POSITION_VALUES_WITH_ADDITIONAL_DATA				0x38	//0b111000
//ENCODER_SEND_POSITION_VALUES_AND_RECEIVE_ERROR_RESET			0x2D	//0b101101
	//ENCODER_RECEIVE_COMMUNICATION_COMMAND							0x12	//0b010010

////**************** ENCODER_SEND_POSITION_VALUES_AND_SELECTION_OF_THE_MEMORY_AREA *******************////
// Template for EnDat22 Command reading position values and performing selection of memory area
// 0xA1 MRS code for selection of encoder manufacturer parameters
// Additional data enabled at this time is 0
	retval = PM_endat22_setupCommand (ENCODER_SEND_POSITION_VALUES_AND_SELECTION_OF_THE_MEMORY_AREA, 0xA1, 0, 0);
	PM_endat22_startOperation();
	while (endat22Data.dataReady != 1) {}
	retval = PM_endat22_receiveData(ENCODER_SEND_POSITION_VALUES_AND_SELECTION_OF_THE_MEMORY_AREA, 0);
	crc5_result1 =  PM_endat22_getCrcPos(endat22Data.position_clocks, ENDAT22, endat22Data.position_lo,
					endat22Data.position_hi, endat22Data.error1, endat22Data.error2, endat22CRCtable);
	if (!CheckCRC(crc5_result1,endat22Data.data_crc))
	 {
	     ESTOP0;
	 }
	 DELAY_US(200L); 	//Delay 200us

////**************** ENCODER_SEND_POSITION_VALUES_AND_RECEIVE_TEST_COMMAND *******************////
// Template for EnDat22 Command reading position values and sending a test command to encoder
// Refer to Heidenhain EnDat22 documentation for details of this command
// Additional data enabled at this time is 0
	retval = PM_endat22_setupCommand (ENCODER_SEND_POSITION_VALUES_AND_RECEIVE_TEST_COMMAND, 0x0, 0, 0);
	PM_endat22_startOperation();
	while (endat22Data.dataReady != 1) {}
	retval = PM_endat22_receiveData(ENCODER_SEND_POSITION_VALUES_AND_RECEIVE_TEST_COMMAND, 0);

	crc5_result1 =  PM_endat22_getCrcPos(endat22Data.position_clocks, ENDAT22, endat22Data.position_lo,
					endat22Data.position_hi, endat22Data.error1, endat22Data.error2, endat22CRCtable);
	if (!CheckCRC(crc5_result1,endat22Data.data_crc))
	 {
	     ESTOP0;
	 }
	 DELAY_US(200L); 	//Delay 200us

////**************** ENCODER_SEND_POSITION_VALUES_AND_RECEIVE_PARAMETER *******************////
// Template for EnDat22 Command reading position values and sending a parameter to encoder
// Refer to Heidenhain EnDat22 documentation for details of this command
// Additional data enabled at this time is 0
	retval = PM_endat22_setupCommand (ENCODER_SEND_POSITION_VALUES_AND_RECEIVE_PARAMETER, 0x0, 0, 0);
	PM_endat22_startOperation();
	while (endat22Data.dataReady != 1) {}
	retval = PM_endat22_receiveData(ENCODER_SEND_POSITION_VALUES_AND_RECEIVE_PARAMETER, 0);

	crc5_result1 =  PM_endat22_getCrcPos(endat22Data.position_clocks, ENDAT22, endat22Data.position_lo,
					endat22Data.position_hi, endat22Data.error1, endat22Data.error2, endat22CRCtable);
	if (!CheckCRC(crc5_result1,endat22Data.data_crc))
	 {
	     ESTOP0;
	 }
	 DELAY_US(200L); 	//Delay 200us

////**************** ENCODER_SEND_POSITION_VALUES_AND_SEND_PARAMETER *******************////
// Template for EnDat22 Command reading position values and receving a parameter from the encoder
// Refer to Heidenhain EnDat22 documentation for details of this command
// Additional data enabled at this time is 0
		retval = PM_endat22_setupCommand (ENCODER_SEND_POSITION_VALUES_AND_SELECTION_OF_THE_MEMORY_AREA, 0xA1, 0, 0);
		PM_endat22_startOperation();
		while (endat22Data.dataReady != 1) {}
		retval = PM_endat22_receiveData(ENCODER_SEND_POSITION_VALUES_AND_SELECTION_OF_THE_MEMORY_AREA, 0);
		crc5_result1 =  PM_endat22_getCrcPos(endat22Data.position_clocks, ENDAT22, endat22Data.position_lo,
						endat22Data.position_hi, endat22Data.error1, endat22Data.error2, endat22CRCtable);
		if (!CheckCRC(crc5_result1,endat22Data.data_crc))
		 {
		     ESTOP0;
		 }
		 DELAY_US(200L); 	//Delay 200us

// Template for EnDat22 Command reading position values and sending a parameter to encoder
// Send 0xD parameter address - will select no. of clock pulses to shift out position value
// Additional data enabled at this time is 0

	retval = PM_endat22_setupCommand (ENCODER_SEND_POSITION_VALUES_AND_SEND_PARAMETER, 0xD, 0, 0);
	PM_endat22_startOperation();
	while (endat22Data.dataReady != 1) {}
	retval = PM_endat22_receiveData(ENCODER_SEND_POSITION_VALUES_AND_SEND_PARAMETER, 0);

	crc5_result1 =  PM_endat22_getCrcPos(endat22Data.position_clocks, ENDAT22, endat22Data.position_lo,
					endat22Data.position_hi, endat22Data.error1, endat22Data.error2, endat22CRCtable);
	if (!CheckCRC(crc5_result1,endat22Data.data_crc))
	 {
	     ESTOP0;
	 }
	 DELAY_US(200L); 	//Delay 200us

////**************** ENCODER_SEND_POSITION_VALUES_WITH_ADDITIONAL_DATA *******************////
// Enable Additional data 1 - to read out no. of  clock pulses to shift out position value
// MRS code 0x45	- Acknowledge memory content LSB
	retval = PM_endat22_setupCommand (ENCODER_SEND_POSITION_VALUES_AND_SELECTION_OF_THE_MEMORY_AREA, 0x45, 0, 0);
	PM_endat22_startOperation();
	while (endat22Data.dataReady != 1) {}
	retval = PM_endat22_receiveData(ENCODER_SEND_POSITION_VALUES_AND_SELECTION_OF_THE_MEMORY_AREA, 0);

	crc5_result1 =  PM_endat22_getCrcPos(endat22Data.position_clocks, ENDAT22, endat22Data.position_lo,
					endat22Data.position_hi, endat22Data.error1, endat22Data.error2, endat22CRCtable);
	if (!CheckCRC(crc5_result1,endat22Data.data_crc))
	 {
	     ESTOP0;
	 }
	 DELAY_US(200L); 	//Delay 200us

// Enable Additional data 2 - to read out Operating status and error sources
// MRS code 0x59	- operating status on additional data 2
// Additional data enabled at this time is 1
	retval = PM_endat22_setupCommand (ENCODER_SEND_POSITION_VALUES_AND_SELECTION_OF_THE_MEMORY_AREA, 0x59, 0, 1);
	PM_endat22_startOperation();
	while (endat22Data.dataReady != 1) {}
	retval = PM_endat22_receiveData(ENCODER_SEND_POSITION_VALUES_AND_SELECTION_OF_THE_MEMORY_AREA, 1);

// CRC check for Position Data
	crc5_result1 =  PM_endat22_getCrcPos(endat22Data.position_clocks, ENDAT22, endat22Data.position_lo,
					endat22Data.position_hi, endat22Data.error1, endat22Data.error2, endat22CRCtable);
	if (!CheckCRC(crc5_result1,endat22Data.data_crc))
	 {
	 ESTOP0;
	 }
// CRC check for Additional Data 1
	crc5_result1 =  PM_endat22_getCrcNorm((endat22Data.additional_data1 >> 16), endat22Data.additional_data1, endat22CRCtable);
	if (!CheckCRC(crc5_result1,endat22Data.additional_data1_crc))
	 {
	 ESTOP0;
	 }
	 DELAY_US(200L); 	//Delay 200us

// Read out position value with 2 additional data previously enabled
// Additional data enabled at this time is 2
	retval = PM_endat22_setupCommand (ENCODER_SEND_POSITION_VALUES_WITH_ADDITIONAL_DATA, 0, 0, 2);
	PM_endat22_startOperation();
	while (endat22Data.dataReady != 1) {}
	retval = PM_endat22_receiveData(ENCODER_SEND_POSITION_VALUES_WITH_ADDITIONAL_DATA, 2);

// CRC check for Position Data
	crc5_result1 =  PM_endat22_getCrcPos(endat22Data.position_clocks, ENDAT22, endat22Data.position_lo,
					endat22Data.position_hi, endat22Data.error1, endat22Data.error2, endat22CRCtable);
	if (!CheckCRC(crc5_result1,endat22Data.data_crc))
	 {
	 ESTOP0;
	 }
// CRC check for Additional Data 1
	crc5_result1 =  PM_endat22_getCrcNorm((endat22Data.additional_data1 >> 16), endat22Data.additional_data1, endat22CRCtable);
	if (!CheckCRC(crc5_result1,endat22Data.additional_data1_crc))
	 {
	 ESTOP0;
	 }
// CRC check for Additional Data 2
	crc5_result1 =  PM_endat22_getCrcNorm((endat22Data.additional_data2 >> 16), endat22Data.additional_data2, endat22CRCtable);
	if (!CheckCRC(crc5_result1,endat22Data.additional_data2_crc))
	 {
	 ESTOP0;
	 }
	 DELAY_US(200L); 	//Delay 200us

////**************** ENCODER_RECEIVE_COMMUNICATION_COMMAND *******************////
// May not be supported by all encoders. Hence this portion is removed to avoid unexpected fails

//	retval = PM_endat22_setupCommand (ENCODER_RECEIVE_COMMUNICATION_COMMAND, 0, 0, 0);
//	PM_endat22_startOperation();
//	while (endat22Data.dataReady != 1) {}
//	retval = PM_endat22_receiveData(ENCODER_RECEIVE_COMMUNICATION_COMMAND, 0);
//	crc5_result1 =  PM_endat22_getCrcNorm(endat22Data.address, endat22Data.data, endat22CRCtable);
//	if (!CheckCRC(crc5_result1,endat22Data.data_crc))
//	{
//		    ESTOP0;
//	}
//	DELAY_US(200L); 	//Delay 200us

}

//***************************************************************************
// End of file
// **************************************************************************
