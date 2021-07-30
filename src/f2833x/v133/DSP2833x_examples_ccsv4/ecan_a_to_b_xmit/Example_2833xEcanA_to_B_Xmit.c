//###########################################################################
// Filename: Example_28xEcan_A_to_B_Xmit.c
//
// Description: eCAN-A To eCAN-B TXLOOP - Transmit loop
//
// ASSUMPTIONS:
//
//    This program requires the DSP2833x header files.
//
//    Both CAN ports of the 2833x DSP need to be connected
//    to each other (via CAN transceivers)
//
//       eCANA is on GPIO31 (CANTXA)  and
//                   GPIO30 (CANRXA)
//
//       eCANB is on GPIO8  (CANTXB)  and
//                   GPIO10 (CANRXB)
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
// DESCRIPTION:
//
//    This example TRANSMITS data to another CAN module using MAILBOX5
//    This program could either loop forever or transmit "n" # of times,
//    where "n" is the TXCOUNT value.
//
//    This example can be used to check CAN-A and CAN-B. Since CAN-B is
//    initialized in DSP2833x_ECan.c, it will acknowledge all frames
//    transmitted by the node on which this code runs. Both CAN ports of
//    the 2833x DSP need to be connected to each other (via CAN transceivers)
//
//###########################################################################
// Original Author: HJ
//
// $TI Release: 2833x/2823x Header Files and Peripheral Examples V133 $
// $Release Date: June 8, 2012 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

#define TXCOUNT  100  // Transmission will take place (TXCOUNT) times..

// Globals for this example
long      i;
long 	  loopcount = 0;


void main()
{

/* Create a shadow register structure for the CAN control registers. This is
 needed, since, only 32-bit access is allowed to these registers. 16-bit access
 to these registers could potentially corrupt the register contents. This is
 especially true while writing to a bit (or group of bits) among bits 16 - 31 */

   struct ECAN_REGS ECanaShadow;

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example

   // Just initalize eCAN pins for this example
   // This function is in DSP2833x_ECan.c
   InitECanGpio();

// Step 3. Clear all interrupts and initialize PIE vector table:
// Disable CPU interrupts
   DINT;

// Initialize the PIE control registers to their default state.
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

// No interrupts used in this example.

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2833x_InitPeripherals.c
// InitPeripherals(); // Not required for this example

   // In this case just initalize eCAN-A and eCAN-B
   // This function is in DSP2833x_ECan.c
   InitECan();

// Step 5. User specific code:

/* Write to the MSGID field  */

   ECanaMboxes.MBOX25.MSGID.all = 0x95555555; // Extended Identifier

/* Configure Mailbox under test as a Transmit mailbox */

   ECanaShadow.CANMD.all = ECanaRegs.CANMD.all;
   ECanaShadow.CANMD.bit.MD25 = 0;
   ECanaRegs.CANMD.all = ECanaShadow.CANMD.all;

/* Enable Mailbox under test */

   ECanaShadow.CANME.all = ECanaRegs.CANME.all;
   ECanaShadow.CANME.bit.ME25 = 1;
   ECanaRegs.CANME.all = ECanaShadow.CANME.all;

/* Write to DLC field in Master Control reg */

   ECanaMboxes.MBOX25.MSGCTRL.bit.DLC = 8;

/* Write to the mailbox RAM field */

   ECanaMboxes.MBOX25.MDL.all = 0x55555555;
   ECanaMboxes.MBOX25.MDH.all = 0x55555555;

/* Begin transmitting */


   for(i=0; i < TXCOUNT; i++)
   {
       ECanaShadow.CANTRS.all = 0;
       ECanaShadow.CANTRS.bit.TRS25 = 1;             // Set TRS for mailbox under test
       ECanaRegs.CANTRS.all = ECanaShadow.CANTRS.all;

       do
    	{
      	ECanaShadow.CANTA.all = ECanaRegs.CANTA.all;
    	} while(ECanaShadow.CANTA.bit.TA25 == 0 );   // Wait for TA5 bit to be set..


       ECanaShadow.CANTA.all = 0;
       ECanaShadow.CANTA.bit.TA25 = 1;     	         // Clear TA5
       ECanaRegs.CANTA.all = ECanaShadow.CANTA.all;

       loopcount ++;
    }
     asm(" ESTOP0");  // Stop here
}


