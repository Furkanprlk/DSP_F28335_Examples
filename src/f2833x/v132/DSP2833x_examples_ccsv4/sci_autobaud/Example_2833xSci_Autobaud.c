// TI File $Revision: /main/2 $
// Checkin $Date: July 30, 2009   18:45:30 $
//###########################################################################
//
// FILE:	Example_2833xSci_Autobaud_.c
//
// TITLE:	DSP2833x SCI Autobaud detect example
//
// ASSUMPTIONS:
//
//    This program requires the DSP2833x header files.
//
//    Test requires the following hardware connections:
//
//          GPIO29/SCITXDA <-> GPIO19/SCIRXDB
//          GPIO28/SCIRXDA <-> GPIO18/SCITXDB
//
//
//    As supplied, this project is configured for "boot to SARAM"
//    operation.  The 2833x Boot Mode table is shown below.
//    For information on configuring the boot mode of an eZdsp,
//    please refer to the documentation included with the eZdsp,
//
//       $Boot_Table:
//
//         GPIO87   GPIO86     GPIO85   GPIO84
//          XA15     XA14       XA13     XA12
//           PU       PU         PU       PU
//        ==========================================
//            1        1          1        1    Jump to Flash
//            1        1          1        0    SCI-A boot
//            1        1          0        1    SPI-A boot
//            1        1          0        0    I2C-A boot
//            1        0          1        1    eCAN-A boot
//            1        0          1        0    McBSP-A boot
//            1        0          0        1    Jump to XINTF x16
//            1        0          0        0    Jump to XINTF x32
//            0        1          1        1    Jump to OTP
//            0        1          1        0    Parallel GPIO I/O boot
//            0        1          0        1    Parallel XINTF boot
//            0        1          0        0    Jump to SARAM	    <- "boot to SARAM"
//            0        0          1        1    Branch to check boot mode
//            0        0          1        0    Boot to flash, bypass ADC cal
//            0        0          0        1    Boot to SARAM, bypass ADC cal
//            0        0          0        0    Boot to SCI-A, bypass ADC cal
//                                              Boot_Table_End$
//
//
//    This test will perform autobaud lock at a variety of baud rates, including
//    very high baud rates.
//
//    For this test to properly run, connect the SCI-A pins to the
//    SCI-B pins without going through a transciever.
//
//    At higher baud rates, the slew rate of the incoming data bits can be
//    affected by transceiver and connector performance. This slew rate may
//    limit reliable autobaud detection at higher baud rates.
//
//    SCIA: Slave, autobaud locks, receives characters and
//          echos them back to the host.  Uses the RX interrupt
//          to receive characters.
//
//    SCIB: Host, known baud rate, sends characters to the slave
//          and checks that they are echoed back.
//
// DESCRIPTION:
//
//    Internal Loopback test for ever through SCIA using interrupts,
//	  FIFOs are disabled.
//
//    Watch Variables: BRRVal - current BRR value used for SCIB
//                     ReceivedAChar - character received by SCIA
//                     ReceivedBChar - character received by SCIB
//                     SendChar      - character being sent by SCIB
//                     SciaRegs.SCILBAUD - SCIA baud registers - set
//                     SciaRegs.SCIHBAUD   by autobaud lock
//
//
//###########################################################################
// $TI Release: 2833x/2823x Header Files V1.32 $
// $Release Date: June 28, 2010 $
//###########################################################################


#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

#define BAUDSTEP 100            // Amount BRR will be incremented between each
                                // autobaud lock

// Prototype statements for functions found within this file.
void scia_init(void);
void scib_init(void);
void scia_xmit(int a);
void scib_xmit(int a);
void scia_AutobaudLock(void);
void error();
interrupt void rxaint_isr(void);


// Global counts used in this example
Uint16 LoopCount;
//Uint16 xmitCount;
Uint16 ReceivedCount;
Uint16 ErrorCount;
Uint16 SendChar;
Uint16 ReceivedAChar;   // scia received character
Uint16 ReceivedBChar;   // scib received character
Uint16 BRRVal;
Uint16 Buff[10] = {0x55, 0xAA, 0xF0, 0x0F, 0x00, 0xFF, 0xF5, 0x5F, 0xA5, 0x5A};

void main(void)
{
   Uint16 i;

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example

   InitSciGpio();

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
   EALLOW;	    // This is needed to write to EALLOW protected registers
   PieVectTable.SCIRXINTA = &rxaint_isr;
   EDIS;       // This is needed to disable write to EALLOW protected register

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2833x_InitPeripherals.c
// InitPeripherals(); // Not required for this example
   scia_init();       // Initalize SCIA
   scib_init();       // Initalize SCIB

// Step 5. User specific code, enable interrupts:

   LoopCount = 0;
   ErrorCount = 0;

// Enable interrupts
   PieCtrlRegs.PIEIER9.all = 0x0001; // Enable all SCIA RXINT interrupt
   IER |= 0x0100;			         // enable PIEIER9, and INT9
   EINT;

    // Start with BRR = 1, work through each baud rate setting
    // incrementing BRR by BAUDSTEP
    for (BRRVal = 0x0000; BRRVal < (Uint32)0xFFFF; BRRVal+=BAUDSTEP)
    {

        // SCIB has a known baud rate.  SCIA will autobaud to match
	    ScibRegs.SCIHBAUD = (BRRVal >> 8);
	    ScibRegs.SCILBAUD = (BRRVal);

	    // Initiate an autobaud lock with scia.  Check
	    // returned character against baud lock character 'A'
	    scia_AutobaudLock();
	    while(ScibRegs.SCIRXST.bit.RXRDY != 1) { }
	    ReceivedBChar = 0;
	    ReceivedBChar =  ScibRegs.SCIRXBUF.bit.RXDT;
	    if(ReceivedBChar != 'A')
	    {
	        error(0);
	    }

	    // Send/echoback characters
	    // 55 AA F0 0F 00 FF F5 5F A5 5A
	    for(i= 0; i<=9; i++)
	    {
	      SendChar = Buff[i];
	      scib_xmit(SendChar);			    // Initiate interrupts and xmit data in isr
	      // Wait to get the character back and check
	      // against the sent character.
	      while(ScibRegs.SCIRXST.bit.RXRDY != 1)
	      {
	          asm("   NOP");
	      }
	      ReceivedBChar = 0;
	      ReceivedBChar =  ScibRegs.SCIRXBUF.bit.RXDT;
	      if(ReceivedBChar != SendChar) error(1);
	    }

    } // Repeat for next BRR setting

    // Stop here, no more
    for(;;)
    {
       asm("    NOP");
    }


}


/* --------------------------------------------------- */
/* ISR for PIE INT9.1                                  */
/* Connected to RXAINT  SCI-A                          */
/* ----------------------------------------------------*/

interrupt void rxaint_isr(void)     // SCI-A
{
  // Insert ISR Code here

   PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;

   // If autobaud detected, we must clear CDC
   if(SciaRegs.SCIFFCT.bit.ABD == 1)
   {
      SciaRegs.SCIFFCT.bit.ABDCLR = 1;
      SciaRegs.SCIFFCT.bit.CDC = 0;
      // Check received character - should be 'A'
      ReceivedAChar = 0;
      ReceivedAChar = SciaRegs.SCIRXBUF.all;
      if(ReceivedAChar != 'A')
      {
         error(2);
      }
      else scia_xmit(ReceivedAChar);
   }

   // This was not autobaud detect
   else
   {
      // Check received character against sendchar
      ReceivedAChar = 0;
      ReceivedAChar = SciaRegs.SCIRXBUF.all;
      if(ReceivedAChar != SendChar)
      {
         error(3);
      }
      else scia_xmit(ReceivedAChar);
   }

   SciaRegs.SCIFFRX.bit.RXFFINTCLR = 1;	// clear Receive interrupt flag
   ReceivedCount++;
}


void error()
{
      ErrorCount++;
      asm("     ESTOP0");  	       // Uncomment to stop the test here
      for (;;);

}

// SCIA  8-bit word, baud rate 0x000F, default, 1 STOP bit, no parity
void scia_init()
{
    // Note: Clocks were turned on to the SCIA peripheral
    // in the InitSysCtrl() function

    // Reset FIFO's
    SciaRegs.SCIFFTX.all=0x8000;

    SciaRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                   // No parity,8 char bits,
                                   // async mode, idle-line protocol
    SciaRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                   // Disable RX ERR, SLEEP, TXWAKE
    SciaRegs.SCICTL2.all =0x0003;
    SciaRegs.SCICTL2.bit.RXBKINTENA =1;
    SciaRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset


}

// SCIB  8-bit word, baud rate 0x000F, default, 1 STOP bit, no parity

void scib_init()
{
    // Reset FIFO's
    ScibRegs.SCIFFTX.all=0x8000;

    // 1 stop bit, No parity, 8-bit character
    // No loopback
    ScibRegs.SCICCR.all = 0x0007;

    // Enable TX, RX, Use internal SCICLK
    ScibRegs.SCICTL1.all = 0x0003;

    // Disable RxErr, Sleep, TX Wake,
    // Diable Rx Interrupt, Tx Interrupt
    ScibRegs.SCICTL2.all = 0x0000;

    // Relinquish SCI-A from reset
    ScibRegs.SCICTL1.all = 0x0023;

    return;
}




// Transmit a character from the SCI-A'
void scia_xmit(int a)
{
    SciaRegs.SCITXBUF=a;
}

// Transmit a character from the SCI-B'
void scib_xmit(int a)
{
    ScibRegs.SCITXBUF=a;
}


//------------------------------------------------
// Perform autobaud lock with the host.
// Note that if autobaud never occurs
// the program will hang in this routine as there
// is no timeout mechanism included.
//------------------------------------------------

void scia_AutobaudLock()
{

    SciaRegs.SCICTL1.bit.SWRESET = 0;
    SciaRegs.SCICTL1.bit.SWRESET = 1;

    // Must prime baud register with >= 1
    SciaRegs.SCIHBAUD = 0;
    SciaRegs.SCILBAUD = 1;

    // Prepare for autobaud detection
    // Make sure the ABD bit is clear by writing a 1 to ABDCLR
    // Set the CDC bit to enable autobaud detection
    SciaRegs.SCIFFCT.bit.ABDCLR = 1;
    SciaRegs.SCIFFCT.bit.CDC = 1;

    // Wait until we correctly read an
    // 'A' or 'a' and lock
	//
	// As long as Autobaud calibration is enabled (CDC = 1),
	// SCI-B (host) will continue transmitting 'A'. This will
	// continue until interrupted by the SCI-A RX ISR, where
	// SCI-A RXBUF receives 'A', autobaud-locks (ABDCLR=1
	// CDC=0),and returns an 'A' back to the host. Then control
	// is returned to this loop and the loop is exited.
	//
	// NOTE: ABD will become set sometime between
	//       scib_xmit and the DELAY_US loop, and
	//       the SCI-A RX ISR will be triggered.
    //       Upon returning and reaching the if-statement,
	//       ABD will have been cleared again by the ISR.

    while(SciaRegs.SCIFFCT.bit.CDC== 1)
    {
       // Note the lower the baud rate the longer
       // this delay has to be to allow the other end
       // to echo back a character (about 4 characters long)
       // Make this really long since we are going through all
       // the baud rates.
       DELAY_US(280000L);

       if(SciaRegs.SCIFFCT.bit.CDC == 1)
           scib_xmit('A');  // host transmits 'A'

   }

    return;
}



//===========================================================================
// No more.
//===========================================================================

