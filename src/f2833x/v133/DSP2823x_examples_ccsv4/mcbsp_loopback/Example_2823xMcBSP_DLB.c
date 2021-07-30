//###########################################################################
//
// FILE:	Example_2823xMCBSP_FFDLB.c
//
// TITLE:	DSP2823x Device McBSP Digital Loop Back program.
//
// ASSUMPTIONS:
//
//    This program requires the DSP2823x header files.
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
//          Digital loopback tests for the McBSP peripheral.
//
//          Three different serial word sizes can be tested.
//
//          Before compiling this project:
//          * Select the serial word size (8/16/32) by using
//            the #define statements at the beginning of the code.
//

//
//          This example does not use interrupts.  Instead, a polling
//          method is used to check the receive data.  The incoming
//          data is checked for accuracy.  If an error is found the error()
//          function is called and execution stops.
//
//          This program will execute until terminated by the user.
//
//    Watch Variables:
//          sdata1
//          sdata2
//          rdata1
//          rdata2
//          rdata1_point
//          rdata2_point
//
//###########################################################################
//
// Original Author: S.S.
//
// $TI Release: 2833x/2823x Header Files and Peripheral Examples V133 $
// $Release Date: June 8, 2012 $
//###########################################################################


#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

// Choose a word size.  Uncomment one of the following lines
#define WORD_SIZE    8    // Run a loopback test in 8-bit mode
//#define WORD_SIZE 16      // Run a loopback test in 16-bit mode
//#define WORD_SIZE 32        // Run a loopback test in 32-bit mode


// Prototype statements for functions found within this file.
void mcbsp_xmit(int a, int b);
void error(void);

// Global data for this example
Uint16 sdata1 = 0x000;    // Sent Data
Uint16 rdata1 = 0x000;    // Recieved Data

Uint16 sdata2 = 0x000;    // Sent Data
Uint16 rdata2 = 0x000;    // Recieved Data

Uint16 rdata1_point;
Uint16 rdata2_point;


void main(void)
{
   Uint16 datasize;

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example
// For this example, only enable the GPIO for McBSP-A
   InitMcbspaGpio();

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

// Step 4. Initialize all the Device Peripherals:
// This function is found in DSP2833x_InitPeripherals.c
// InitPeripherals();     // Not required for this example

   datasize = WORD_SIZE;
   InitMcbspa();          // Initalize the Mcbsp-A in loopback test mode

// Step 5. User specific code, enable interrupts:

      if(datasize == 8)             // Run a loopback test in 8-bit mode
      {
          InitMcbspa8bit();
          sdata2 = 0x0000;           // value is a don't care for 8-bit mode
          sdata1 = 0x0000;           // 8-bit value to send
		  rdata2_point = 0x0000;     // value is a don't care for 8-bit mode
          rdata1_point = sdata1;
          for(;;)
          {
              mcbsp_xmit(sdata1,sdata2);
              sdata1++;
              sdata1 = sdata1 & 0x00FF;                     // Keep it to 8-bits

              while(McbspaRegs.SPCR1.bit.RRDY == 0 ) { }    // Check for receive
              rdata1 = McbspaRegs.DRR1.all;                 // read DRR1
              if(rdata1 != rdata1_point) error();
              rdata1_point++;
              rdata1_point = rdata1_point & 0x00FF;         // Keep it to 8-bits

               asm("    nop");                                   // Good place for a breakpoint
                                                                 // Check: rdatax_point = sdatax
                                                                 //        rdata1 = sdata1 - 1
          }
       }


      else if(datasize == 16)            // Run a loopback test in 16-bit mode
      {
          InitMcbspa16bit();
          sdata2 = 0x0000;           // value is a don't care for 16-bit mode
          sdata1 = 0x0000;           // 16-bit value to send
		  rdata2_point = 0x0000;     // value is a don't care for 16-bit mode
          rdata1_point = sdata1;
          for(;;)
          {
              mcbsp_xmit(sdata1,sdata2);
              sdata1++;

              while(McbspaRegs.SPCR1.bit.RRDY == 0 ) { }     // Check for receive
              rdata1 = McbspaRegs.DRR1.all;                  // read DRR1
              if(rdata1 != rdata1_point) error();
              rdata1_point++;

               asm("    nop");                                   // Good place for a breakpoint
                                                                 // Check: rdatax_point = sdatax
                                                                 //        rdata1 = sdata1 - 1
          }
       }


      else if(datasize == 32)            // Run a loopback test in 16-bit mode
      {
          InitMcbspa32bit();
          sdata1 = 0x0000;
          sdata2 = 0xFFFF;
          rdata1_point = sdata1;
          rdata2_point = sdata2;
          for(;;)
          {
              mcbsp_xmit(sdata1,sdata2);
              sdata1++;
              sdata2--;

              while(McbspaRegs.SPCR1.bit.RRDY == 0 ) { }  // Check for receive
              rdata2 = McbspaRegs.DRR2.all;
              rdata1 = McbspaRegs.DRR1.all;
              if(rdata1 != rdata1_point) error();
              if(rdata2 != rdata2_point) error();
              rdata1_point++;
              rdata2_point--;

              asm("    nop");                             // Good place for a breakpoint
                                                          // Check: rdatax_point = sdatax
                                                          //        rdata1 = sdata1 - 1
														  //        rdata2 = sdata2 + 1
           }
       }
}



// Some Useful local functions

void error(void)
{
    asm("     ESTOP0");  // test failed!! Stop!
    for (;;);
}

void mcbsp_xmit(int a, int b)
{
    McbspaRegs.DXR2.all=b;
    McbspaRegs.DXR1.all=a;
}

//===========================================================================
// No more.
//===========================================================================

