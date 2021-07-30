// TI File $Revision: /main/1 $
// Checkin $Date: May 27, 2009   13:09:27 $
//###########################################################################
//
// FILE:   Example_2823xExternalInterrupt.c
//
// TITLE:  DSP2823x External Interrupt test program.
//
// ASSUMPTIONS:
//
//    This program requires the DSP2823x header files.
//    As supplied, this project is configured for "boot to SARAM" operation.
//
//         Connect GPIO30 to GPIO0.  GPIO0 will be assigned to Xint1
//         Connect GPIO31 to GPIO1.  GPIO1 will be assigned to XINT2
//
//         Monitor GPIO34 with an oscilloscope. GPIO34 will be high outside of the
//         ISRs and low within each ISR.
//
//    As supplied, this project is configured for "boot to SARAM"
//    operation.  The 2823x Boot Mode table is shown below.
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
// DESCRIPTION:
//
//    This program sets up GPIO0 as Xint1 and GPIO1 as XINT2.  Two other
//    GPIO signals are used to trigger the interrupt (GPIO30 triggers
//    Xint1 and GPIO31 triggers XINT2).  The user is required to
//    externally connect these signals for the program to work
//    properly.
//
//    Xint1 input is synched to SYSCLKOUT
//    XINT2 has a long qualification - 6 samples at 510*SYSCLKOUT each.
//
//    GPIO34 will go high outside of the interrupts and low within the
//    interrupts. This signal can be monitored on a scope.
//
//    Each interrupt is fired in sequence - Xint1 first and then XINT2
//
//
//    Watch Variables:
//       Xint1Count for the number of times through Xint1 interrupt
//       Xint2Count for the number of times through XINT2 interrupt
//       LoopCount for the number of times through the idle loop
//
//###########################################################################
// $TI Release: 2833x/2823x Header Files V1.32 $
// $Release Date: June 28, 2010 $
//###########################################################################


#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

// Prototype statements for functions found within this file.
interrupt void xint1_isr(void);
interrupt void xint2_isr(void);

// Global variables for this example
volatile Uint32 Xint1Count;
volatile Uint32 Xint2Count;
Uint32 LoopCount;

#define DELAY 35.700L

void main(void)
{
   Uint32 TempX1Count;
   Uint32 TempX2Count;

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example

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
   PieVectTable.XINT1 = &xint1_isr;
   PieVectTable.XINT2 = &xint2_isr;
   EDIS;   // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2833x_InitPeripherals.c
// InitPeripherals(); // Not required for this example

// Step 5. User specific code, enable interrupts:

// Clear the counters
   Xint1Count = 0; // Count Xint1 interrupts
   Xint2Count = 0; // Count XINT2 interrupts
   LoopCount = 0;  // Count times through idle loop

// Enable Xint1 and XINT2 in the PIE: Group 1 interrupt 4 & 5
// Enable int1 which is connected to WAKEINT:
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;          // Enable the PIE block
   PieCtrlRegs.PIEIER1.bit.INTx4 = 1;          // Enable PIE Gropu 1 INT4
   PieCtrlRegs.PIEIER1.bit.INTx5 = 1;          // Enable PIE Gropu 1 INT5
   IER |= M_INT1;                              // Enable CPU int1
   EINT;                                       // Enable Global Interrupts

// GPIO30 & GPIO31 are outputs, start GPIO30 high and GPIO31 low
   EALLOW;
   GpioDataRegs.GPASET.bit.GPIO30 = 1;         // Load the output latch
   GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 0;        // GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO30 = 1;         // output

   GpioDataRegs.GPACLEAR.bit.GPIO31 = 1;       // Load the output latch
   GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 0;        // GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;         // output
   EDIS;

// GPIO0 and GPIO1 are inputs
   EALLOW;
   GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 0;         // GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO0 = 0;          // input
   GpioCtrlRegs.GPAQSEL1.bit.GPIO0 = 0;        // Xint1 Synch to SYSCLKOUT only

   GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 0;         // GPIO
   GpioCtrlRegs.GPADIR.bit.GPIO1 = 0;          // input
   GpioCtrlRegs.GPAQSEL1.bit.GPIO1 = 2;        // XINT2 Qual using 6 samples
   GpioCtrlRegs.GPACTRL.bit.QUALPRD0 = 0xFF;   // Each sampling window is 510*SYSCLKOUT
   EDIS;

// GPIO0 is XINT1, GPIO1 is XINT2
   EALLOW;
   GpioIntRegs.GPIOXINT1SEL.bit.GPIOSEL = 0;   // Xint1 is GPIO0
   GpioIntRegs.GPIOXINT2SEL.bit.GPIOSEL = 1;   // XINT2 is GPIO1
   EDIS;

// Configure XINT1
   XIntruptRegs.XINT1CR.bit.POLARITY = 0;      // Falling edge interrupt
   XIntruptRegs.XINT2CR.bit.POLARITY = 1;      // Rising edge interrupt

// Enable XINT1 and XINT2
   XIntruptRegs.XINT1CR.bit.ENABLE = 1;        // Enable Xint1
   XIntruptRegs.XINT2CR.bit.ENABLE = 1;        // Enable XINT2


// GPIO34 will go low inside each interrupt.  Monitor this on a scope
   EALLOW;
   GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 0;        // GPIO
   GpioCtrlRegs.GPBDIR.bit.GPIO34 = 1;         // output
   EDIS;

// Step 6. IDLE loop:
   for(;;)
   {

      TempX1Count = Xint1Count;
      TempX2Count = Xint2Count;

      // Trigger both XINT1
      GpioDataRegs.GPBSET.bit.GPIO34 = 1;   // GPIO34 is high
      GpioDataRegs.GPACLEAR.bit.GPIO30 = 1; // Lower GPIO30, trigger Xint1
      while(Xint1Count == TempX1Count) {}

      // Trigger both XINT2

      GpioDataRegs.GPBSET.bit.GPIO34 = 1;   // GPIO34 is high
      DELAY_US(DELAY);                      // Wait for Qual period
      GpioDataRegs.GPASET.bit.GPIO31 = 1;   // Raise GPIO31, trigger XINT2
      while(Xint2Count == TempX2Count) {}

      // Check that the counts were incremented properly and get ready
      // to start over.
      if(Xint1Count == TempX1Count+1 && Xint2Count == TempX2Count+1)
      {
          LoopCount++;
          GpioDataRegs.GPASET.bit.GPIO30 = 1;   // raise GPIO30
          GpioDataRegs.GPACLEAR.bit.GPIO31 = 1; // lower GPIO31
      }
      else
      {
          asm("      ESTOP0"); // stop here
      }

   }


}


// Step 7. Insert all local Interrupt Service Routines (ISRs) and functions here:
	// If local ISRs are used, reassign vector addresses in vector table as
    // shown in Step 5

interrupt void xint1_isr(void)
{
	GpioDataRegs.GPBCLEAR.all = 0x4;   // GPIO34 is low
	Xint1Count++;

	// Acknowledge this interrupt to get more from group 1
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}

interrupt void xint2_isr(void)
{
	GpioDataRegs.GPBCLEAR.all = 0x4;   // GPIO34 is low
	Xint2Count++;

	// Acknowledge this interrupt to get more from group 1
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;
}


//===========================================================================
// No more.
//===========================================================================
