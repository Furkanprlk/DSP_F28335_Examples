//###########################################################################
// Description:
//! \addtogroup f2823x_example_list
//!  <h1>SCI Digital Loop Back with Interrupts (spi_loopback_interrupts)</h1>
//!
//! This program uses the internal loop back test mode of the peripheral.
//! Other then boot mode pin configuration, no other hardware configuration
//! is required. Both interrupts and the SCI FIFOs are used.
//!
//! A stream of data is sent and then compared to the received stream.
//!
//! The SCI-A sent data looks like this: \n
//!    00 01 02 03 04 05 06 07 \n
//!    01 02 03 04 05 06 07 08 \n
//!    02 03 04 05 06 07 08 09 \n
//!    .... \n
//!    FE FF 00 01 02 03 04 05 \n
//!    FF 00 01 02 03 04 05 06 \n
//!    etc..
//!
//! The SCI-B sent data looks like this: \n
//!    FF FE FD FC FB FA F9 F8 \n
//!    FE FD FC FB FA F9 F8 F7 \n
//!    FD FC FB FA F9 F8 F7 F6 \n
//!    .... \n
//!    01 00 FF FE FD FC FB FA \n
//!    00 FF FE FD FC FB FA F9 \n
//!    etc..
//!
//!    Both patterns are repeated forever.
//!
//!  \b Watch \b Variables \n
//!  - sdataA, sdataB - Data to send
//!  - rdataA, rdataB - Received data
//!  - rdata_pointA, rdata_pointB -  Used to keep track of the last position in
//!    the receive stream for error checking
//
//###########################################################################
// $TI Release: F2833x/F2823x Header Files and Peripheral Examples V141 $
// $Release Date: November  6, 2015 $
// $Copyright: Copyright (C) 2007-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

#define CPU_FREQ 	 150E6
#define LSPCLK_FREQ  CPU_FREQ/4
#define SCI_FREQ 	 100E3
#define SCI_PRD 	 (LSPCLK_FREQ/(SCI_FREQ*8))-1

// Prototype statements for functions found within this file.
__interrupt void sciaTxFifoIsr(void);
__interrupt void sciaRxFifoIsr(void);
__interrupt void scibTxFifoIsr(void);
__interrupt void scibRxFifoIsr(void);
void scia_fifo_init(void);
void scib_fifo_init(void);
void error(void);

// Global variables
Uint16 sdataA[8];    // Send data for SCI-A
Uint16 sdataB[8];    // Send data for SCI-B
Uint16 rdataA[8];    // Received data for SCI-A
Uint16 rdataB[8];    // Received data for SCI-A
Uint16 rdata_pointA; // Used for checking the received data
Uint16 rdata_pointB;

void main(void)
{
   Uint16 i;

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initialize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();
// Setup only the GP I/O only for SCI-A and SCI-B functionality
// This function is found in DSP2833x_Sci.c
   InitSciGpio();

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize PIE control registers to their default state.
// The default state is all PIE interrupts disabled and flags
// are cleared.
// This function is found in the DSP2833x_PieCtrl.c file.
   InitPieCtrl();

// Disable CPU interrupts and clear all CPU interrupt flags:
   IER = 0x0000;
   IFR = 0x0000;

// Initialize the PIE vector table with pointers to the shell Interrupt
// Service Routines (ISR).
// This will populate the entire table, even if the interrupt
// is not used in this example.  This is useful for debug purposes.
// The shell ISR routines are found in DSP2833x_DefaultIsr.c.
// This function is found in DSP2833x_PieVect.c.
   InitPieVectTable();

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
   EALLOW;	// This is needed to write to EALLOW protected registers
   PieVectTable.SCIRXINTA = &sciaRxFifoIsr;
   PieVectTable.SCITXINTA = &sciaTxFifoIsr;
   PieVectTable.SCIRXINTB = &scibRxFifoIsr;
   PieVectTable.SCITXINTB = &scibTxFifoIsr;
   EDIS;   // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2833x_InitPeripherals.c
// InitPeripherals(); // Not required for this example
   scia_fifo_init();  // Init SCI-A
   scib_fifo_init();  // Init SCI-B

// Step 5. User specific code, enable interrupts:

// Init send data.  After each transmission this data
// will be updated for the next transmission
   for(i = 0; i<8; i++)
   {
      sdataA[i] = i;
   }

   for(i = 0; i<8; i++)
   {
      sdataB[i] = 0xFF - i;
   }

   rdata_pointA = sdataA[0];
   rdata_pointB = sdataB[0];

// Enable interrupts required for this example
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
   PieCtrlRegs.PIEIER9.bit.INTx1=1;     // PIE Group 9, int1
   PieCtrlRegs.PIEIER9.bit.INTx2=1;     // PIE Group 9, INT2
   PieCtrlRegs.PIEIER9.bit.INTx3=1;     // PIE Group 9, INT3
   PieCtrlRegs.PIEIER9.bit.INTx4=1;     // PIE Group 9, INT4
   IER = 0x100;	// Enable CPU INT
   EINT;

// Step 6. IDLE loop. Just sit and loop forever (optional):
	for(;;);
}

void error(void)
{
    __asm("     ESTOP0"); // Test failed!! Stop!
    for (;;);
}

__interrupt void sciaTxFifoIsr(void)
{
    Uint16 i;
    for(i=0; i< 8; i++)
    {
 	   SciaRegs.SCITXBUF=sdataA[i];     // Send data
	}

    for(i=0; i< 8; i++)                 //Increment send data for next cycle
    {
 	   sdataA[i] = (sdataA[i]+1) & 0x00FF;
	}

	SciaRegs.SCIFFTX.bit.TXFFINTCLR=1;	// Clear SCI Interrupt flag
	PieCtrlRegs.PIEACK.all|=0x100;      // Issue PIE ACK
}

__interrupt void sciaRxFifoIsr(void)
{
    Uint16 i;
	for(i=0;i<8;i++)
	{
	   rdataA[i]=SciaRegs.SCIRXBUF.all;	 // Read data
	}
	for(i=0;i<8;i++)                     // Check received data
	{
	   if(rdataA[i] != ( (rdata_pointA+i) & 0x00FF) ) error();
	}
	rdata_pointA = (rdata_pointA+1) & 0x00FF;

	SciaRegs.SCIFFRX.bit.RXFFOVRCLR=1;   // Clear Overflow flag
	SciaRegs.SCIFFRX.bit.RXFFINTCLR=1;   // Clear Interrupt flag

	PieCtrlRegs.PIEACK.all|=0x100;       // Issue PIE ack
}

void scia_fifo_init()
{
   SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                  // No parity,8 char bits,
                                  // async mode, idle-line protocol
   SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                  // Disable RX ERR, SLEEP, TXWAKE
   SciaRegs.SCICTL2.bit.TXINTENA =1;
   SciaRegs.SCICTL2.bit.RXBKINTENA =1;
   SciaRegs.SCIHBAUD = 0x0000;
   SciaRegs.SCILBAUD = SCI_PRD;
   SciaRegs.SCICCR.bit.LOOPBKENA =1; // Enable loop back
   SciaRegs.SCIFFTX.all=0xC028;
   SciaRegs.SCIFFRX.all=0x0028;
   SciaRegs.SCIFFCT.all=0x00;

   SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
   SciaRegs.SCIFFTX.bit.TXFIFOXRESET=1;
   SciaRegs.SCIFFRX.bit.RXFIFORESET=1;


}

__interrupt void scibTxFifoIsr(void)
{
    Uint16 i;
    for(i=0; i< 8; i++)
    {
 	   ScibRegs.SCITXBUF=sdataB[i];     // Send data
	}

    for(i=0; i< 8; i++)                 //Increment send data for next cycle
    {
 	   sdataB[i] = (sdataB[i]-1) & 0x00FF;
	}

	ScibRegs.SCIFFTX.bit.TXFFINTCLR=1;  // Clear Interrupt flag
	PieCtrlRegs.PIEACK.all|=0x100;      // Issue PIE ACK
}

__interrupt void scibRxFifoIsr(void)
{
    Uint16 i;
	for(i=0;i<8;i++)
	{
	   rdataB[i]=ScibRegs.SCIRXBUF.all;	 // Read data
	}
	for(i=0;i<8;i++)                     // Check received data
	{
	   if(rdataB[i] != ( (rdata_pointB-i) & 0x00FF) ) error();
	}
	rdata_pointB = (rdata_pointB-1) & 0x00FF;

	ScibRegs.SCIFFRX.bit.RXFFOVRCLR=1;  // Clear Overflow flag
	ScibRegs.SCIFFRX.bit.RXFFINTCLR=1; 	// Clear Interrupt flag
	PieCtrlRegs.PIEACK.all|=0x100;  	// Issue PIE ack
}

void scib_fifo_init()
{
   ScibRegs.SCICCR.all =0x0007;    // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
   ScibRegs.SCICTL1.all =0x0003;   // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
   ScibRegs.SCICTL2.bit.TXINTENA =1;
   ScibRegs.SCICTL2.bit.RXBKINTENA =1;
   ScibRegs.SCIHBAUD    =0x0000;
   ScibRegs.SCILBAUD    =SCI_PRD;
   ScibRegs.SCICCR.bit.LOOPBKENA =1; // Enable loop back
   ScibRegs.SCIFFTX.all=0xC028;
   ScibRegs.SCIFFRX.all=0x0028;
   ScibRegs.SCIFFCT.all=0x00;

   ScibRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
   ScibRegs.SCIFFTX.bit.TXFIFOXRESET=1;
   ScibRegs.SCIFFRX.bit.RXFIFORESET=1;

}

//===========================================================================
// No more.
//===========================================================================

