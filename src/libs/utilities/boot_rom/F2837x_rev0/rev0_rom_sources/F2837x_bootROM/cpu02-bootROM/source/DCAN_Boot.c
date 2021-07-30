//DCAN boot loader functions for Soprano

#include "c2_bootrom.h"

//------CAN bit rate timing parameters------//
//WARNING: There is very little sanity checking in these calculations. See DCAN spec section 1.16
//for additional requirements. Among other things, you must ensure that one bit takes between
//8 and 25 time quanta, and that Tseg1 and Tseg2 can fit into their respective register fields.
//The main user-controllable parameters here are:
//
//Bit rate	(bits/sec)	CAN bit rate -- must match the rest of the CAN network
//SYSCLK	(hertz)		System clock frequency, which feeds the DCAN module
//BRP		-			Bit rate prescaler, which divides down SYSCLK to provide the bit clock
#define DCAN_BOOT_RATE		50000L
#define DCAN_BOOT_SYSCLK	10000000L
#define DCAN_BOOT_BRP		10L

//Other parameters are defined according to the instructions in section 1.16.2.1
//of the DCAN spec. Exception: This code rounds PhSeg1 up and PhSeg2 down since
//a later sample time works better on most networks. This is implemented by rounding
//down PhSeg2 first, then computing PhSeg1 as Tphase - PhSeg2. Calculating in this
//order also lets us limit Tseg2 to 8 so it will fit in the register.
//
//Bit clock	(hertz)		Equal to SYSCLK / BRP by definition; each bit clock is one time quantum (Tq)
//Bit time	(Tq)		Number of time quanta per bit; the ratio of bit clock frequency to bit rate
//Tsync		(Tq)		Synchronization time delay: Fixed at 1 Tq by the CAN protocol
//Tprop		(Tq)		Propagation delay: <2 microseconsd for a <1000 foot bus; assumed to be <2 Tq
//Tphase	(Tq)		Phase compensation buffer for oscillator tolerance: The remainder of the bit time
//PhSeg1	(Tq)		Phase segment 1: Pre-sample buffer; half of the phase time, rounded up (<=16)
//PhSeg2	(Tq)		Phase segment 2: Post-sample buffer; half of the phase time, rounded down (<=8)
#define DCAN_BOOT_BITCLK	(DCAN_BOOT_SYSCLK / DCAN_BOOT_BRP)
#define DCAN_BOOT_BITTIME	(DCAN_BOOT_BITCLK / DCAN_BOOT_RATE)
#if (DCAN_BOOT_BITTIME > 25)
	#error "DCAN boot loader config error: bit time cannot exceed 25 time quanta!"
#endif
#define DCAN_BOOT_TSYNC		1L
#define DCAN_BOOT_TPROP		2L
#define DCAN_BOOT_TPHASE	(DCAN_BOOT_BITTIME - (DCAN_BOOT_TSYNC + DCAN_BOOT_TPROP))
#define DCAN_BOOT_PHSEG2	((DCAN_BOOT_TPHASE / 2L <= 8) ? DCAN_BOOT_TPHASE / 2L : 8)
#define DCAN_BOOT_PHSEG1	(DCAN_BOOT_TPHASE - DCAN_BOOT_PHSEG2)

//These parameters are then converted into register values. All parameters
//are -1 in the register:
//
//Tseg1		(Tq)		Everything between sync and sample: Tprop + PhSeg1; MUST BE LESS THAN 8
//Tseg2		(Tq)		Everything between sample and next time: PhSeg2; MUST BE LESS THAN 16
//Tsjw		(Tq)		Synchronization jump width: The lesser of 4 and PhSeg1
//BRPEREG	-			Upper 4 bits of bit prescaler; SUBTRACT ONE FROM BRP BEFORE COMPUTING THIS
//BRPREG	-			Lower 6 bits of bit prescaler; SUBTRACT ONE FROM BRP BEFORE COMPUTING THIS
#define DCAN_BOOT_TSEG1		((DCAN_BOOT_PHSEG1 + DCAN_BOOT_TPROP) - 1)
#define DCAN_BOOT_TSEG2		(DCAN_BOOT_PHSEG2 - 1)
#define DCAN_BOOT_TSJW		(((DCAN_BOOT_PHSEG1 > 4L) ? 4L : DCAN_BOOT_PHSEG1) - 1)
#define DCAN_BOOT_BRPEREG	((DCAN_BOOT_BRP - 1L) / 64L)
#define DCAN_BOOT_BRPREG	((DCAN_BOOT_BRP - 1L) % 64L)
#define DCAN_BOOT_BTRREG	(DCAN_BOOT_BRPEREG<<16 | DCAN_BOOT_TSEG2<<12 | DCAN_BOOT_TSEG1<<8 | DCAN_BOOT_TSJW<<6 | DCAN_BOOT_BRPREG)


//Boot mode flag definitions
#define DCAN_BOOT_ALTGPIO	0x80		//Switch from the standard GPIO70/71 to GPIO62/63
#define DCAN_BOOT_SENDTEST	0x40		//Send two 16-bit data frames on startup for bit rate measurement


void DCAN_Boot_Gpio(Uint16 gpioSelect);
void DCAN_Boot_Init();
Uint16 DCAN_GetWordData();
void DCAN_SendWordData(Uint16 data);
extern void CopyData();
extern Uint32 GetLongData();
extern void ReadReservedFn();


Uint32 DCAN_Boot(Uint32 bootMode)
{
	Uint32 entryAddr = FLASH_ENTRY_POINT;

	//If DCAN-A is not enabled, bypass the bootloader
	#ifdef CPU1
		if (DevCfgRegs.DC11.bit.CAN_A != 1)
			return FLASH_ENTRY_POINT;
	#endif

	//Assign the DCAN data reader function to the global
	//function pointer for loading data.
	GetWordData = &DCAN_GetWordData;

	//Set up the GPIO muxes for either standard (GPIO70/71) or alternate (GPIO62/63) pinout
	#ifdef CPU1
		if (bootMode & DCAN_BOOT_ALTGPIO)
			DCAN_Boot_Gpio(6263);
		else
			DCAN_Boot_Gpio(7071);
	#endif

	//Set up the DCAN to receive data
	DCAN_Boot_Init();

	entryAddr = TI_OTP_C2BROM_ESCAPE_POINT_9;
	if((entryAddr != 0xFFFFFFFF) &&
		   (entryAddr != 0x00000000))
	{
	   /*if OTP is programmed, then call OTP function*/
	   ((void (*)(void))entryAddr)();
	}


	//Send two test frames if the OTP says so
	if (bootMode & DCAN_BOOT_SENDTEST)
	{
		DCAN_SendWordData(0x0320);
		DCAN_SendWordData(0x2837);
	}

	//The first data word should be a valid key. If it's not,
	//bypass the bootloader.
	if (DCAN_GetWordData() != 0x08AA)
		return FLASH_ENTRY_POINT;

	//Use the shared utility functions to load the data.
	ReadReservedFn();
	entryAddr = GetLongData();
	CopyData();

	return entryAddr;
}


//Select which GPIOs to use for DCAN-A
void DCAN_Boot_Gpio(Uint16 gpioSelect)
{
#ifdef CPU1
	EALLOW;
	if (gpioSelect == 6263)
	{
		//Set up the GPIO mux to bring out CANATX on GPIO63 and CANARX on GPIO62
		GpioCtrlRegs.GPBLOCK.all = 0x00000000;	//Unlock GPIOs 32-63
		GpioCtrlRegs.GPBCSEL4.bit.GPIO63 = 0x0;	//Give CPU1 control just in case
		GpioCtrlRegs.GPBGMUX2.bit.GPIO63 = 0x1;	//Set the extended mux to 0x6
		GpioCtrlRegs.GPBMUX2.bit.GPIO63 = 0x2;
		GpioCtrlRegs.GPBCSEL4.bit.GPIO63 = 0x3;	//Set qualification to async just in case

		GpioCtrlRegs.GPBCSEL4.bit.GPIO62 = 0x0;	//Give CPU1 control just in case
		GpioCtrlRegs.GPBGMUX2.bit.GPIO62 = 0x1;	//Set the extended mux to 0x6
		GpioCtrlRegs.GPBMUX2.bit.GPIO62 = 0x2;
		GpioCtrlRegs.GPBCSEL4.bit.GPIO62 = 0x3;	//Set qualification to async just in case
		GpioCtrlRegs.GPBLOCK.all = 0xFFFFFFFF;	//Lock GPIOs 32-63
	} else if (gpioSelect == 1819)
	{
		GpioCtrlRegs.GPALOCK.all = 0x00000000;	//Unlock GPIOs 0-31
		GpioCtrlRegs.GPACSEL3.bit.GPIO19 = 0x0;	//Give CPU1 control just in case
		GpioCtrlRegs.GPAGMUX2.bit.GPIO19 = 0x0;	//Set the extended mux to bring out CANATX
		GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 0x3;
		GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 0x3;	//Set qualification to async just in case

		GpioCtrlRegs.GPACSEL3.bit.GPIO18 = 0x0;	//Give CPU1 control just in case
		GpioCtrlRegs.GPAGMUX2.bit.GPIO18 = 0x0;	//Set the extended mux to bring out CANARX
		GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 0x3;
		GpioCtrlRegs.GPAQSEL2.bit.GPIO18 = 0x3;	//Set qualification to async just in case
		GpioCtrlRegs.GPALOCK.all = 0xFFFFFFFF;	//Lock GPIOs 0-31
	} else
	{
		//Set up the GPIO mux to bring out CANATX on GPIO71 and CANARX on GPIO70
		GpioCtrlRegs.GPCLOCK.all = 0x00000000;	//Unlock GPIOs 64-95
		GpioCtrlRegs.GPCCSEL1.bit.GPIO71 = 0x0;	//Give CPU1 control just in case
		GpioCtrlRegs.GPCGMUX1.bit.GPIO71 = 0x1;	//Set the extended mux to 0x5
		GpioCtrlRegs.GPCMUX1.bit.GPIO71 = 0x1;
		GpioCtrlRegs.GPCQSEL1.bit.GPIO71 = 0x3;	//Set qualification to async just in case

		GpioCtrlRegs.GPCLOCK.all = 0x00000000;	//Unlock GPIOs 64-95
		GpioCtrlRegs.GPCCSEL1.bit.GPIO70 = 0x0;	//Give CPU1 control just in case
		GpioCtrlRegs.GPCGMUX1.bit.GPIO70 = 0x1;	//Set the extended mux to bring out CANATX
		GpioCtrlRegs.GPCMUX1.bit.GPIO70 = 0x1;
		GpioCtrlRegs.GPCQSEL1.bit.GPIO70 = 0x3;	//Set qualification to async just in case
		GpioCtrlRegs.GPCLOCK.all = 0xFFFFFFFF;	//Lock GPIOs 64-95
	}

	//Set the DCAN_A clock source to SYSCLK
	ClkCfgRegs.CLKSRCCTL2.bit.CANABCLKSEL = 0x0;
	EDIS;
#endif
}


//Initialize the CAN_A module
void DCAN_Boot_Init()
{
    //Turn on the clock to the DCAN module
    EALLOW;
    CpuSysRegs.PCLKCR10.bit.CAN_A = 1;
    EDIS;

	//Issue a software reset to DCAN_A -- shut down communication via INIT, then reset via SWR
	DcanaRegs.CAN_CTL.all = 0x1;
	DcanaRegs.CAN_CTL.all = 0x8000;

	//Bit timing configuration. See the large comment at the top for details.
	DcanaRegs.CAN_CTL.all = 0x1441;					//Initialize, disable parity, and enable config register access
	DcanaRegs.CAN_BTR.all = DCAN_BOOT_BTRREG;
	DcanaRegs.CAN_CTL.all = 0x1400;					//Finish initialization and disable config register access

	//Set up a receive object via interface 1, then transfer to message RAM
	DcanaRegs.CAN_IF1ARB.all = 0x80040000;			//MsgVal set, MsgID = 1 (11-bit)
	DcanaRegs.CAN_IF1MCTL.all = 0x2;				//Data length = 2 bytes
	DcanaRegs.CAN_IF1CMD.all = 0x00F80001;			//Transfer configuration to message object 1
	while (DcanaRegs.CAN_IF1CMD.all & 0x8000) {;}	//Wait for message RAM copy

	//Set up a transmit object via interface 2 for debug
	DcanaRegs.CAN_IF2ARB.all = 0xA0080000;			//MsgVal set, MsgID = 2 (11-bit)
	DcanaRegs.CAN_IF2MCTL.all = 0x2;				//Data length = 2 bytes
	DcanaRegs.CAN_IF2CMD.all = 0x00F80002;			//Transfer configuration to message object 2
	while (DcanaRegs.CAN_IF2CMD.all & 0x8000) {;}	//Wait for message RAM copy
}


//Read 16 bits from an incoming DCAN message to ID#1
Uint16 DCAN_GetWordData()
{
	//Wait for a new CAN message to be received in mailbox 1
	while (DcanaRegs.CAN_NDAT_21 != 0x1) {;}

	//Transfer the message from IF1
	DcanaRegs.CAN_IF1CMD.all = 0x00070001;
	while (DcanaRegs.CAN_IF1CMD.all & 0x8000) {;}
	return (Uint16)DcanaRegs.CAN_IF1DATA.all;

}


//Write 16 bits for external data rate measurement
void DCAN_SendWordData(Uint16 data)
{
	DcanaRegs.CAN_IF2DATA.all = data;
	DcanaRegs.CAN_IF2CMD.all = 0x00870002;
	while (DcanaRegs.CAN_IF2CMD.all & 0x8000) {;}
	while (DcanaRegs.CAN_TXRQ_21 & 0x2) {;}
}
