//USB boot loader functions for Soprano


#include "c1_bootrom.h"
#include "USB_Boot_Funcs.h"


void UsbLoaderRev0Fix();
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
	uint32_t disconnectDelay;

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

    EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_13;
    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }

	//Disconnect from the bus, disable USB interrupts, and
	//reset the USB module. But first, wait for any ongoing
    //transfers to complete.
    for (disconnectDelay = 0; disconnectDelay < 10000; disconnectDelay++) {;}
	USBREG8(USB_O_POWER) &= ~USB_POWER_SOFTCONN;
	EALLOW;
	PieCtrlRegs.PIEIER9.bit.INTx15 = 0;
	IER &= ~M_INT9;
	DevCfgRegs.SOFTPRES11.bit.USB_A = 1;
	DevCfgRegs.SOFTPRES11.bit.USB_A = 0;
	EDIS;

	//Bypass and disable the main and aux PLLs
	EALLOW;
	ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0;
	ClkCfgRegs.SYSPLLMULT.bit.IMULT = 0;
	ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 0;
	ClkCfgRegs.AUXPLLCTL1.bit.PLLCLKEN = 0;
	ClkCfgRegs.AUXPLLMULT.bit.IMULT = 0;
	ClkCfgRegs.AUXPLLCTL1.bit.PLLEN = 0;
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
	//USBCLK = 120 MHz / 2, sourced from the external oscillator for precision
	//
	//SYSCLK must be greater than USBCLK / 2, according to Design. The PLL minimum
	//Fout is 110 MHz, so let's set the multiplier to give 120 MHz and keep the
	//output divider at 1.
	EALLOW;
	ClkCfgRegs.CLKSRCCTL1.bit.OSCCLKSRCSEL = 0x0;       //Use INTOSC2 (~10 MHz) as the main PLL clock source
    ClkCfgRegs.SYSPLLMULT.all = 12;                     //Set IMULT to 12, clear FMULT
	ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 1;                //Enable the main PLL
	ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = 0;       //Set PLLSYSCLKDIV to 1
    while (ClkCfgRegs.SYSPLLSTS.bit.LOCKS != 1) {;}     //Wait for the PLL to lock
    ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 1;             //Turn off the main PLL bypass

    ClkCfgRegs.CLKSRCCTL2.bit.AUXOSCCLKSRCSEL = 0x1;    //Use XTAL (20 MHz) as the aux PLL clock source
    ClkCfgRegs.AUXPLLMULT.all = 6;                      //Set IMULT to 6, clear FMULT - 120MHz
    ClkCfgRegs.AUXPLLCTL1.bit.PLLEN = 1;                //Enable the aux PLL
    ClkCfgRegs.AUXCLKDIVSEL.bit.AUXPLLDIV = 2/2;        //Set AUXPLLDIV to 2
    while (ClkCfgRegs.AUXPLLSTS.bit.LOCKS != 1) {;}     //Wait for the PLL to lock
    ClkCfgRegs.AUXPLLCTL1.bit.PLLCLKEN = 1;             //Turn off aux PLL bypass
	CpuSysRegs.PCLKCR11.bit.USB_A = 1;                  //Enable the clock to the USB module

    EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_13;
    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }


    //Connect the PHY to the GPIO pins by setting the GPBAMSEL
    //bits for GPIOs 42 and 43. VBUS and ID are now de-spec'd
    //due to the lack of a 5V fail-safe ESD structure, so
    //GPIOs 46 and 47 are not muxed out.
    GpioCtrlRegs.GPBAMSEL.bit.GPIO42 = 1;
    GpioCtrlRegs.GPBAMSEL.bit.GPIO43 = 1;
	EDIS;


	//Register the USB interrupt handler and enable CPU interrupts
	c1brom_enable_pie_in_boot(0);
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

    //Reset the USB driver's global variables
    ResetUsbDriver();

    //Force USB device mode by setting DEVMODOTG and DEVMOD
	USBREG32(USB_O_GPCS) = 0x3;

	//Clear active interrupts
	USBREG16(USB_O_TXIS);
	USBREG16(USB_O_RXIS);
	USBREG8(USB_O_IS);

	//Set up endpoint 1 for bulk transfers with a 64-byte FIFO
	USBREG8(USB_O_EPIDX) = 1;
	USBREG8(USB_O_RXFIFOSZ) = 0x03;
	USBREG16(USB_O_RXFIFOADD) = 0x100;
	USBREG8(USB_O_RXCSRH1) = 0x40;

	//Enable USB interrupts for EP0 transmit/receive, EP1 receive, disconnection, and reset
	USBREG16(USB_O_TXIE) = 0x0001;
	USBREG16(USB_O_RXIE) = 0x0002;
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
		AckEp1();
	}

	return retVal;
}

//Acknowledge the USB interrupt. Defining a separate function for this keeps the
//driver library device-independent.
void AckUsbInterrupt()
{
	//Soprano
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;
}
