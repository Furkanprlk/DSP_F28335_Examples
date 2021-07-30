//USB boot loader functions for Soprano


#include "c1_bootrom.h"
#include "USB_Boot_Funcs.h"



void USB_Boot_Init();
Uint16 USB_GetWordData();
extern void CopyData();
extern Uint32 GetLongData();
extern void ReadReservedFn();

extern Uint16 *g_UsbRxBuffer;
extern Uint16 g_UsbRxDataLength;
extern Uint16 g_UsbRxPacketLength;


Uint32 USB_Boot(Uint16 bootMode)
{
	uint32_t entryAddr = FLASH_ENTRY_POINT;
	uint32_t EntryAddr = 0xFFFFFFFF;

	//If the USB module is not enabled, bypass the bootloader
	if (DevCfgRegs.DC12.bit.USB_A == 0)
		return FLASH_ENTRY_POINT;

	//Assign the USB data reader function to the global
	//function pointer for loading data.
	GetWordData = &USB_GetWordData;

	//Set up the USB to receive data
	USB_Boot_Init();

    EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_13;
    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }

	//The first data word should be a valid key. If it's not,
	//bypass the bootloader.
	if (USB_GetWordData() != 0x08AA)
		return FLASH_ENTRY_POINT;

	//Use the shared utility functions to load the data.
	ReadReservedFn();
	entryAddr = GetLongData();
	CopyData();

	//Disconnect from the bus, disable USB interrupts, and
	//reset the USB module.
	USBREG8(USB_O_POWER) &= ~USB_POWER_SOFTCONN;
	EALLOW;
	PieCtrlRegs.PIEIER9.bit.INTx15 = 0;
	IER &= ~M_INT9;
	DevCfgRegs.SOFTPRES11.bit.USB_A = 1;
	DevCfgRegs.SOFTPRES11.bit.USB_A = 0;
	EDIS;

	//Bypass and disable the main PLL
	EALLOW;
	ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0;
	ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 0;
	EDIS;

    EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_13;
    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }


	return entryAddr;
}


//Initialize the USB module
void USB_Boot_Init()
{
	uint32_t EntryAddr = 0xFFFFFFFF;
	//Soprano
	//Lock the main PLL< aux PLL and enable the USB module clock
	//
	//USBCLK = 120 MHz / 2, sourced from INTOSC
	//(the /2 comes from AUXCLKDIVSEL, which is assumed to be at its reset value)
	//
	//SYSCLK must be greater than USBCLK / 2, according to Design. At this
	//point it should already be using INTOSC2 as a source. The PLL minimum
	//Fout is 110 MHz, so let's use the same multiplier as the aux PLL and
	//keep PLLSYSCLKDIV set to 1. This gives 120 MHz.
	EALLOW;
	ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 1;				//Enable the main PLL
	ClkCfgRegs.SYSPLLMULT.all = 12;						//Set IMULT to 12, clear FMULT
	while (ClkCfgRegs.SYSPLLSTS.bit.LOCKS != 1) {;}		//Wait for the PLL to lock
	ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 1;				//Turn off the main PLL bypass

	ClkCfgRegs.CLKSRCCTL2.bit.AUXOSCCLKSRCSEL = 0x0;	//Use INTOSC2 (10 MHz) as the aux PLL clock source
	ClkCfgRegs.AUXPLLCTL1.bit.PLLEN = 1;				//Enable the aux PLL
	ClkCfgRegs.AUXPLLMULT.all = 12;						//Set IMULT to 12, clear FMULT
	ClkCfgRegs.AUXCLKDIVSEL.bit.AUXPLLDIV = 2/2;		//Set AUXPLLDIV to 2
	while (ClkCfgRegs.AUXPLLSTS.bit.LOCKS != 1) {;}		//Wait for the PLL to lock
	ClkCfgRegs.AUXPLLCTL1.bit.PLLCLKEN = 1;				//Turn off aux PLL bypass
	CpuSysRegs.PCLKCR11.bit.USB_A = 1;					//Enable the clock to the USB module
	EDIS;

	c1brom_enable_pie_in_boot(0);

	//Register the USB interrupt handler and enable CPU interrupts
	EALLOW;
	PieVectTable.USBA_INT = &UsbIntHandler;
	PieCtrlRegs.PIEIER9.bit.INTx15 = 1;
	EDIS;
	IER |= M_INT9;
	EINT;

    EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_13;
    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }

	//Octave
	//Lock the aux PLL: USBCLK = 120 MHz / 2, sourced from INTOSC
/*	InitPll2(0, 12, 0);

	//Register the USB interrupt handler
	EALLOW;
    PieVectTable.USB0_INT = &UsbIntHandler;
    PieCtrlRegs.PIEIER5.bit.INTx8 = 1;
    EDIS;
    IER |= M_INT5;

    //Enable the USB module and CPU interrupts
	EALLOW;
    SysCtrlRegs.PCLKCR3.bit.USB0ENCLK = 1;
    GpioCtrlRegs.GPACTRL2.bit.USB0IOEN = 1;
    EDIS;
    EINT;
*/


    //Reset the USB driver's global variables
    ResetUsbDriver();

	//The USB module is in device mode on reset, so we shouldn't need to do much configuration
	//Clear active interrupts
	USBREG16(USB_O_TXIS);
	USBREG16(USB_O_RXIS);
	USBREG8(USB_O_IS);

	//Enable USB interrupts for endpoint 0 transmit, disconnection, and reset
	USBREG16(USB_O_TXIE) = 0x0001;
	USBREG8(USB_O_IE) = (USB_IE_DISCON | USB_IE_RESET);

	//Attach the USB PHY to the bus
	USBREG8(USB_O_POWER) |= USB_POWER_SOFTCONN;
}


//Read 16 bits from an incoming USB message
Uint16 USB_GetWordData()
{
	Uint16 retVal;

	//Wait for the USB receive buffer to be refilled
	while (g_UsbRxBuffer == 0) {;}

	//Read the next data value, update the buffer pointer and length,
	//and do end-of-packet handling.
	retVal = *g_UsbRxBuffer++;
	g_UsbRxPacketLength -= 2;
	if (g_UsbRxPacketLength == 0)
	{
		g_UsbRxBuffer = 0;
		if (g_UsbRxDataLength == 0)
			AckEp0(USB_END_DATA);
		else
			AckEp0(USB_MORE_DATA);
	}

	return retVal;
}

//Acknowledge the USB interrupt. Defining a separate function for this keeps the
//driver library device-independent.
void AckUsbInterrupt()
{
	//Soprano
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

	//Octave
//	PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;
}
