//----------------------------------------------------------------------------------
//	FILE:			tformat.c
//
//	Description:	Contains all the initialization, data declarations and setup
//					for tformat encoder interface. This file serves are a template for
//					using PM_tformat Library to interface and incorporates all the encoder
//					and library specific initializations and other important aspects of usage.
//
//	Version: 		1.0
//
//  Target:  		TMS320F28379D,
//
//----------------------------------------------------------------------------------
//  Copyright Texas Instruments © 2004-2015
//----------------------------------------------------------------------------------
//  Revision History:
//----------------------------------------------------------------------------------
//  Date	  | Description / Status
//----------------------------------------------------------------------------------
// 26 Sep 2016  - Example project for PM tformat Library Usage
//----------------------------------------------------------------------------------

#include "tformat.h"

#include "F28x_Project.h"     // Device Headerfile and Examples Include File

uint16_t tformatCRCtable[SIZEOF_TFORMAT_CRCTABLE];	// Declare CRC table for tformat CRC calculations

TFORMAT_DATA_STRUCT tformatData;		//PM tformat data structure

// Function to initialize tformat operation
void tformat_Init(void) {

	EALLOW;
//Enable clocks to PWM4
	CpuSysRegs.PCLKCR2.bit.EPWM4 = 1;
	EDIS;

//Configure EPWM4 to drive default values on GPIO6 and GPIO7
	EPWM4_Config();

// Generate table for tformat Polynomial defied as POLY1
 	PM_tformat_generateCRCTable(NBITS_POLY1, POLY1, tformatCRCtable);
//GPIO configuration for tformat operation
 	tformat_setup_GPIO();
//XBAR configuration for tformat operation
	tformat_config_XBAR();

	tformatData.spi = &SpibRegs;
	PM_tformat_setupPeriph();

	EALLOW;
// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
	PieVectTable.SPIB_RX_INT = &spiRxFifoIsr;
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
	PieCtrlRegs.PIEIER6.bit.INTx3 = 1;     // Enable PIE Group 6, INT 9
	IER |= 0x20;                            // Enable CPU INT6
	EINT;
	EDIS;

	// Power up tformat 5v supply through GPIO32
	GpioDataRegs.GPBDAT.bit.GPIO32 = 1;
	DELAY_US(100000L);

	PM_tformat_setFreq(TFORMAT_FREQ_DIVIDER);
}

void tformat_setup_GPIO(void) {

	EALLOW;
	GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 1; // Configure GPIO7 as SPI Clk slave

	GpioCtrlRegs.GPAGMUX2.bit.GPIO24 = 1;
	GpioCtrlRegs.GPAGMUX2.bit.GPIO25 = 1;
	GpioCtrlRegs.GPAGMUX2.bit.GPIO26 = 1;
	GpioCtrlRegs.GPAGMUX2.bit.GPIO27 = 1;

	GpioCtrlRegs.GPAMUX2.bit.GPIO24 = 2; // Configure GPIO24 as SPISIMOB
	GpioCtrlRegs.GPAMUX2.bit.GPIO25 = 2; // Configure GPIO25 as SPISOMIB
	GpioCtrlRegs.GPAMUX2.bit.GPIO26 = 2; // Configure GPIO26 as SPICLKB
	GpioCtrlRegs.GPAMUX2.bit.GPIO27 = 2; // Configure GPIO27 as SPISTEB

	GpioCtrlRegs.GPAQSEL2.bit.GPIO24 = 3; // Asynch input GPIO24 (SPISIMOB)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO25 = 3; // Asynch input GPIO25 (SPISOMIB)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO26 = 3; // Asynch input GPIO26 (SPICLKB)
	GpioCtrlRegs.GPAQSEL2.bit.GPIO27 = 3; // Asynch input GPIO27 (SPISTEB)

	GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 1; // Configure GPIO34 as tformat TxEN

	GpioCtrlRegs.GPBDIR.bit.GPIO32 = 1; // Configure GPIO32 as tformat Pwr Ctl

	EDIS;
}

void tformat_config_XBAR(void)
{
	EALLOW;

//Choose SPISIMO GPIO as InputXbar Input1 - SPISIMO (B) on GPIO24 in this case
	InputXbarRegs.INPUT1SELECT = 24;	// GPTRIP XBAR TRIP1 -> GPIO24
	EDIS;
}


void error(void) {
	asm("     ESTOP0");
	//Test failed!! Stop!
	for (;;);
}

interrupt void spiRxFifoIsr(void)
{
	uint16_t i;
    for (i=0;i<=tformatData.fifo_level;i++){tformatData.rdata[i]= tformatData.spi->SPIRXBUF;}
	tformatData.spi->SPIFFRX.bit.RXFFOVFCLR=1;  // Clear Overflow flag
    tformatData.spi->SPIFFRX.bit.RXFFINTCLR=1;  // Clear Interrupt flag
    PieCtrlRegs.PIEACK.all|=0x20;       // Issue PIE ack
    tformatData.dataReady=1;
}


void EPWM4_Config(void) {
// Set the PWMA and B high as default values of tformat clk.
	EALLOW;
	EPwm4Regs.TZCTL.bit.TZA = 1;
	EPwm4Regs.TZCTL.bit.TZB = 1;
	EPwm4Regs.TZFRC.bit.OST = 1;
	EDIS;
}

uint16_t CheckCRC (uint16_t expectcrc5, uint16_t receivecrc5) {
	if (expectcrc5 == receivecrc5) {
		return 1;
	}
	else {
		return 0;
	}
}

uint16_t tformat_exCommands(void)
{

	uint16_t retval1;		//used for function return val storage and checks
	uint32_t address, address_tmp, data, data_tmp;
	uint32_t crcResult;

	retval1 = PM_tformat_setupCommand (DATAID2, 0, 0, 0);
	PM_tformat_startOperation();
	while (tformatData.dataReady != 1) {}
	retval1 = PM_tformat_receiveData(DATAID2);

	crcResult = PM_tformat_getCRC(0, 24, 8, (uint16_t *)&tformatData.rxPkts, tformatCRCtable, 3);
	crcResult = crcResult ^ (0xFF);
	 if (!CheckCRC(crcResult,tformatData.crc))
	 {
			 ESTOP0;
	 }
	 DELAY_US(200L); 	//Delay 200us

	retval1 = PM_tformat_setupCommand (DATAID0, 0, 0, 0);
	PM_tformat_startOperation();
	while (tformatData.dataReady != 1) {}
	retval1 = PM_tformat_receiveData(DATAID0);

	crcResult = PM_tformat_getCRC(0, 40, 8, (uint16_t *)&tformatData.rxPkts, tformatCRCtable, 5);
	crcResult = crcResult ^ (0xFF);
	 if (!CheckCRC(crcResult,tformatData.crc))
	 {
			 ESTOP0;
	 }
	 DELAY_US(200L); 	//Delay 200us

	retval1 = PM_tformat_setupCommand (DATAID1, 0, 0, 0);
	PM_tformat_startOperation();
	while (tformatData.dataReady != 1) {}
	retval1 = PM_tformat_receiveData(DATAID1);

	crcResult = PM_tformat_getCRC(0, 40, 8, (uint16_t *)&tformatData.rxPkts, tformatCRCtable, 5);
	crcResult = crcResult ^ (0xFF);
	 if (!CheckCRC(crcResult,tformatData.crc))
	 {
			 ESTOP0;
	 }
	 DELAY_US(200L); 	//Delay 200us

	address = 1;
	address_tmp = (__flip32(address) >> 24) & 0xFE;	// includes busy "0"
	tformatData.rxPkts[0] = ((((uint32_t) DATAIDD) | 0x40) << 8) | (uint32_t) address_tmp;
	crcResult = PM_tformat_getCRC(0, 16, 8, (uint16_t *)&tformatData.rxPkts, tformatCRCtable, 2);
	crcResult = (crcResult) ^ (0xFF);

	retval1 = PM_tformat_setupCommand (DATAIDD, address, 0, crcResult);
	PM_tformat_startOperation();
	while (tformatData.dataReady != 1) {}
	retval1 = PM_tformat_receiveData(DATAIDD);

	crcResult = PM_tformat_getCRC(0, 32, 8, (uint16_t *)&tformatData.rxPkts, tformatCRCtable, 4);
	crcResult = crcResult ^ (0xFF);
	 if (!CheckCRC(crcResult,tformatData.crc))
	 {
			 ESTOP0;
	 }
	 DELAY_US(200L); 	//Delay 200us

	address = 1; data = 35;
	address_tmp = (__flip32(address) >> 24) & 0xFE;	// includes busy "0"
	data_tmp = (__flip32(data) >> 24) & 0xFF;
	tformatData.rxPkts[0] = ((((uint32_t) DATAID6) | 0x40) << 16) | (((uint32_t) address_tmp) << 8) | ((uint32_t) data_tmp);
	crcResult = PM_tformat_getCRC(0, 24, 8, (uint16_t *)&tformatData.rxPkts, tformatCRCtable, 3);
	crcResult = (crcResult) ^ (0xFF);

	retval1 = PM_tformat_setupCommand (DATAID6, address, data, crcResult);
	PM_tformat_startOperation();
	while (tformatData.dataReady != 1) {}
	retval1 = PM_tformat_receiveData(DATAID6);

	crcResult = PM_tformat_getCRC(0, 32, 8, (uint16_t *)&tformatData.rxPkts, tformatCRCtable, 4);
	crcResult = crcResult ^ (0xFF);
	 if (!CheckCRC(crcResult,tformatData.crc))
	 {
			 ESTOP0;
	 }
	 DELAY_US(200L); 	//Delay 200us

	address = 1;
	address_tmp = (__flip32(address) >> 24) & 0xFE;	// includes busy "0"
	tformatData.rxPkts[0] = ((((uint32_t) DATAIDD) | 0x40) << 8) | (uint32_t) address_tmp;
	crcResult = PM_tformat_getCRC(0, 16, 8, (uint16_t *)&tformatData.rxPkts, tformatCRCtable, 2);
	crcResult = (crcResult) ^ (0xFF);

	retval1 = PM_tformat_setupCommand (DATAIDD, address, 0, crcResult);
	PM_tformat_startOperation();
	while (tformatData.dataReady != 1) {}
	retval1 = PM_tformat_receiveData(DATAIDD);

	crcResult = PM_tformat_getCRC(0, 32, 8, (uint16_t *)&tformatData.rxPkts, tformatCRCtable, 4);
	crcResult = crcResult ^ (0xFF);
	 if (!CheckCRC(crcResult,tformatData.crc))
	 {
			 ESTOP0;
	 }
	 DELAY_US(200L); 	//Delay 200us

	 return (retval1);

}
//***************************************************************************
// End of file
// **************************************************************************
