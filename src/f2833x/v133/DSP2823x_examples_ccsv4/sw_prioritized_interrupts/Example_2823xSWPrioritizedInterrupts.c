//###########################################################################
//
// FILE:   Example_2823xSWPrioritizedInterrupts.c
//
// TITLE:  DSP2823x Software Prioritized Interrupt Example.
//
// ASSUMPTIONS:
//
//    This program requires the DSP2823x header files.
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
//    For most applications, the hardware prioritization of the
//    the PIE module is sufficient.  For applications that need custom
//    prioritization, this example illustrates an example of
//    how this can be done through software.
//
//    For more information on F2823x interrupt priorities, refer to the
//    Example_2823xISRPriorities.pdf file included with the DSP2823x/doc directory.
//
//    This program simulates interrupt conflicts by writing to the
//    PIEIFR registers.  This will simulate multiple interrupts coming into
//    the PIE block at the same time.
//
//    The interrupt service routine routines are software prioritized
//    by the table found in the DSP2833x_SWPrioritizedIsrLevels.h file.
//
//       1) Before compiling you must set the Global and Group interrupt priorities
//          in the DSP2833x_SWPrioritizedIsrLevels.h file.
//
//       2) Then select which test you want to run with the #define TEST directive
//          at the top of this file (select a test between 1 and 10)
//
//       3) Compile the code, load, and run
//
//       4) At the end of each test there is a hard coded breakpoint (ESTOP0).  When code
//          stops at the breakpoint, examine the ISRTrace buffer to see the order
//          in which the ISR's completed.    All PIE interrupts will add to the
//          ISRTrace.
//
//          The ISRTrace will consist of a list of hex values as shown:
//
//              0x00wx    <- PIE Group w interrup x finished first
//              0x00yz    <- PIE Group y interrupt z finished next
//
//       5) If desired, set a new set of Global and Group interrupt priorites
//          and repeat the test to see the change.
//
//
//       Watch Variables:
//                ISRTrace[50]           Trace of ISR's in the order they complete
//                                       After each test, examine this buffer
//                                       to determine if the ISR's completed in
//                                       the order desired.
//
//###########################################################################
// $TI Release: 2833x/2823x Header Files and Peripheral Examples V133 $
// $Release Date: June 8, 2012 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "DSP2833x_SWPrioritizedIsrLevels.h"

#define TEST 1 // Select a test number: 1 through 10

// Define which interrupts are used in the PIE for each group.
#define ISRS_GROUP1  (M_INT1|M_INT2|M_INT4|M_INT5|M_INT6|M_INT7|M_INT8)
#define ISRS_GROUP2  (M_INT1|M_INT2|M_INT3|M_INT4|M_INT5|M_INT6)
#define ISRS_GROUP3  (M_INT1|M_INT2|M_INT3|M_INT4|M_INT5|M_INT6)
#define ISRS_GROUP4  (M_INT1|M_INT2|M_INT3|M_INT4|M_INT5|M_INT6)
#define ISRS_GROUP5  (M_INT1|M_INT2)
#define ISRS_GROUP6  (M_INT1|M_INT2|M_INT3|M_INT4|M_INT5|M_INT6)
#define ISRS_GROUP7  (M_INT1|M_INT2|M_INT3|M_INT4|M_INT5|M_INT6)
#define ISRS_GROUP8  (M_INT1|M_INT2|M_INT5|M_INT6)
#define ISRS_GROUP9  (M_INT1|M_INT2|M_INT3|M_INT4|M_INT5|M_INT6|M_INT7|M_INT8)
#define ISRS_GROUP12 (M_INT1|M_INT2|M_INT3|M_INT4|M_INT5|M_INT7|M_INT8)


// This array will be used as a trace to check the order that the
// interrupts were serviced
Uint16  ISRTrace[50];
Uint16  ISRTraceIndex;  // used to update an element in the trace buffer

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
// InitPeripherals(); // Not required for this example

// Step 5. User specific code, enable interrupts:

#if (TEST==1)
//     Force all group 1 interrupts at once by writing to the PIEIFR1 register

       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
	   DINT;
	   for(i = 0; i < 50; i++) ISRTrace[i] = 0;
	   ISRTraceIndex = 0;
       InitPieCtrl();
       IER = 0;
       IFR &= 0;

       // Enable the PIE block
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       // Enable PIE group 1 interrupt 1-8
       PieCtrlRegs.PIEIER1.all = 0x00FF;

       // Make sure PIEACK for group 1 is clear (default after reset)
       PieCtrlRegs.PIEACK.all = M_INT1;

       // Enable CPU INT1
       IER |= M_INT1;

       // Force all valid interrupts for Group 1
       PieCtrlRegs.PIEIFR1.all = ISRS_GROUP1;

       // Enable global Interrupts CPU level:
	   EINT;   // Enable Global interrupt INTM

	   // Wait for all Group 1 interrupts to be serviced
	   while(PieCtrlRegs.PIEIFR1.all != 0x0000 ){}

       // Stop here and check the ISRTrace to determine which order the
       // ISR Routines completed.  The order is dependant on the priority
       // assigned in the DSP2833x_SWPrioritizedIsrLevels.h file
       //
       // The ISRTrace will contain a list of values corresponding to the
       // interrupts serviced in the order they were serviced.
	   // For example if the ISRTrace looks like this
	   //        0x0014     ISR Group 1 interrupt 4
	   //        0x0017     ISR Group 1 interrupt 7
	   //        0x0016     ISR Group 1 interrupt 6
	   //        0x0015     ISR Group 1 interrupt 5
	   //        0x0018     ISR Group 1 interrupt 8
	   //        0x0012     ISR Group 1 interrupt 2
	   //        0x0011     ISR Group 1 interrupt 1
	   //        0x0000     end of trace
	   asm("        ESTOP0");
#endif
#if (TEST == 2)
// CASE 2:
//     Force all group 2 interrupts at once by writing to the PIEIFR2 register

       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
	   DINT;
	   for(i = 0; i < 50; i++) ISRTrace[i] = 0;
	   ISRTraceIndex = 0;
       InitPieCtrl();
       IER = 0;
       IFR &= 0;

       // Enable the PIE block
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       // Enable PIE group 2 interrupts 1-8
       PieCtrlRegs.PIEIER2.all = 0x00FF;

       // Enable CPU INT2
       IER |= (M_INT2);

	   // Make sure PIEACK for group 2 is clear (default after reset)
       PieCtrlRegs.PIEACK.all = M_INT2;

       // Force all valid interrupts for Group 2
       PieCtrlRegs.PIEIFR2.all = ISRS_GROUP2;

	   // Enable Global interrupts
	   EINT;


	   // Wait for all group 2 interrupts to be serviced
	   while(PieCtrlRegs.PIEIFR2.all != 0x0000 ){}

       // Stop here and check the order the ISR's were serviced in the
       // ISRTrace
	   asm("        ESTOP0");

#endif
#if (TEST == 3)
// CASE 3:
//     Force all group 3 interrupts at once by writing to the PIEIFR3 register

       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
	   DINT;
	   for(i = 0; i < 50; i++) ISRTrace[i] = 0;
	   ISRTraceIndex = 0;
       InitPieCtrl();
       IER = 0;
       IFR &= 0;

       // Enable the PIE block
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       // Enable PIE group 3 interrupts 1-8
       PieCtrlRegs.PIEIER3.all = 0x00FF;

	   // Make sure PIEACK for group 3 is clear (default after reset)
       PieCtrlRegs.PIEACK.all = M_INT3;

       // Enable CPU INT3
       IER |= (M_INT3);

       // Force all valid interrupts for Group 3
       PieCtrlRegs.PIEIFR3.all = ISRS_GROUP3;

	   // Enable Global interrupts
	   EINT;

	   // Wait for all group 3 interrupts to be serviced
	   while(PieCtrlRegs.PIEIFR3.all != 0x0000 ){}

       // Stop here and check the order the ISR's were serviced in the
       // ISRTrace
	   asm("        ESTOP0");
#endif
#if (TEST == 4)
// CASE 4:
//     Force all group 4 interrupts at once by writing to the PIEIFR4 register

       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
	   DINT;
	   for(i = 0; i < 50; i++) ISRTrace[i] = 0;
	   ISRTraceIndex = 0;
       InitPieCtrl();
       IER = 0;
       IFR &= 0;

       // Enable the PIE block
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       // Enable PIE group 4 interrupts 1-8
       PieCtrlRegs.PIEIER4.all = 0x00FF;

	   // Make sure PIEACK for group 3 is clear (default after reset)
       PieCtrlRegs.PIEACK.all = M_INT4;

       // Enable CPU INT4
       IER |= (M_INT4);

       // Force all valid interrupts for Group 4
       PieCtrlRegs.PIEIFR4.all = ISRS_GROUP4;

	   // Enable Global interrupts
	   EINT;

	   // Wait for all group 4 interrupts to be serviced
	   while(PieCtrlRegs.PIEIFR4.all != 0x0000 ){}

       // Stop here and check the order the ISR's were serviced in the
       // ISRTrace
	   asm("        ESTOP0");
#endif
#if (TEST == 5)
// CASE 5:
//     Force all group 5 interrupts at once by writing to the PIEIFR5 register

       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
	   DINT;
	   for(i = 0; i < 50; i++) ISRTrace[i] = 0;
	   ISRTraceIndex = 0;
       InitPieCtrl();
       IER = 0;
       IFR &= 0;

       // Enable the PIE block
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       // Enable PIE group 5 interrupts 1-8
       PieCtrlRegs.PIEIER5.all = 0x00FF;

	   // Make sure PIEACK for group 5 is clear (default after reset)
       PieCtrlRegs.PIEACK.all = M_INT5;

       // Enable CPU INT5
       IER |= (M_INT5);

       // Force all valid interrupts for Group 5
       PieCtrlRegs.PIEIFR5.all = ISRS_GROUP5;

	   // Enable Global interrupts
	   EINT;

	   // Wait for all group 5 interrupts to be serviced
	   while(PieCtrlRegs.PIEIFR5.all != 0x0000 ){}

       // Stop here and check the order the ISR's were serviced in the
       // ISRTrace
	   asm("        ESTOP0");
#endif
#if (TEST == 6)

// CASE 6:
//     Force all group 6 interrupts at once by writing to the PIEIFR6 register

       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
	   DINT;
	   for(i = 0; i < 50; i++) ISRTrace[i] = 0;
	   ISRTraceIndex = 0;
       InitPieCtrl();
       IER = 0;
       IFR &= 0;

       // Enable the PIE block
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       // Enable PIE group 6 interrupts 1-8
       PieCtrlRegs.PIEIER6.all = 0x00FF;

	   // Make sure PIEACK for group 6 is clear (default after reset)
       PieCtrlRegs.PIEACK.all = M_INT6;

       // Enable CPU INT6
       IER |= (M_INT6);

       // Force all valid interrupts for Group 6
       PieCtrlRegs.PIEIFR6.all = ISRS_GROUP6;

	   // Enable Global interrupts
	   EINT;


	   // Wait for all group 6 interrupts to be serviced
	   while(PieCtrlRegs.PIEIFR6.all != 0x0000 ){}

       // Stop here and check the order the ISR's were serviced in the
       // ISRTrace
	   asm("        ESTOP0");

#endif
#if (TEST == 7)
// CASE 7:
//     Force all group 9 interrupts at once by writing to the PIEIFR4 register

       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
	   DINT;
	   for(i = 0; i < 50; i++) ISRTrace[i] = 0;
	   ISRTraceIndex = 0;
       InitPieCtrl();
       IER = 0;
       IFR &= 0;

       // Enable the PIE block
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       // Enable PIE group 9 interrupts 1-8
       PieCtrlRegs.PIEIER9.all = 0x00FF;

	   // Make sure PIEACK for group 9 is clear (default after reset)
       PieCtrlRegs.PIEACK.all = M_INT9;

       // Enable CPU INT9
       IER |= (M_INT9);

       // Force all valid interrupts for Group 9
       PieCtrlRegs.PIEIFR9.all = ISRS_GROUP9;

	   // Enable Global interrupts
	   EINT;

	   // Wait for all group 9 interrupts to be serviced
	   while(PieCtrlRegs.PIEIFR9.all != 0x0000 ){}

       // Stop here and check the order the ISR's were serviced in the
       // ISRTrace
	   asm("        ESTOP0");

#endif
#if (TEST == 8)
// CASE 8:
//     Force all group 1 and group 2 interrupts at once

       // Setup next test - fire interrupts from Group 1 and Group 2

       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
	   DINT;
	   for(i = 0; i < 50; i++) ISRTrace[i] = 0;
	   ISRTraceIndex = 0;
       InitPieCtrl();
       IER = 0;
       IFR &= 0;

       // Enable the PIE block
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       // Enable PIE group 1 and group 2 interrupts 1-8
       PieCtrlRegs.PIEIER1.all = 0x00FF;
       PieCtrlRegs.PIEIER2.all = 0x00FF;

	   // Make sure PIEACK for group 1 & 2 are clear (default after reset)
       PieCtrlRegs.PIEACK.all = (M_INT3 | M_INT2);

       // Enable CPU INT1 and INT2
       IER |= (M_INT1|M_INT2);

       // Force all valid interrupts for Group 1 and from Group 2
       PieCtrlRegs.PIEIFR1.all = ISRS_GROUP1;
       PieCtrlRegs.PIEIFR2.all = ISRS_GROUP2;

	   // Enable Global interrupts
	   EINT;

	   // Wait for all group 1 and group 2 interrupts to be serviced
	   while(PieCtrlRegs.PIEIFR1.all != 0x0000
	      || PieCtrlRegs.PIEIFR2.all != 0x0000 ){}

	   // Check the ISRTrace to determine which order the ISR Routines completed
	   asm("        ESTOP0");

#endif
#if (TEST == 9)
// CASE 9:
//     Force all group 1 and group 2 and group 3 interrupts at once

       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
	   DINT;
	   for(i = 0; i < 50; i++) ISRTrace[i] = 0;
	   ISRTraceIndex = 0;
       InitPieCtrl();
       IER = 0;
       IFR &= 0;

       // Enable the PIE block
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       // Enable PIE group 1, 2 and 3 interrupts 1-8
       PieCtrlRegs.PIEIER1.all = 0x00FF;
       PieCtrlRegs.PIEIER2.all = 0x00FF;
       PieCtrlRegs.PIEIER3.all = 0x00FF;

	   // Make sure PIEACK for group 1, 2 & 3 are clear (default after reset)
       PieCtrlRegs.PIEACK.all = (M_INT3|M_INT2|M_INT3);

       // Enable CPU INT1, INT2 & INT3
       IER |= (M_INT1|M_INT2|M_INT3);

       // Force all valid interrupts for Group1, 2 and 3
       PieCtrlRegs.PIEIFR1.all = ISRS_GROUP1;
       PieCtrlRegs.PIEIFR2.all = ISRS_GROUP2;
       PieCtrlRegs.PIEIFR3.all = ISRS_GROUP3;

	   // Enable Global interrupts
	   EINT;

	   // Wait for all group 1 and group 2 and group 3 interrupts to be serviced
	   while(PieCtrlRegs.PIEIFR1.all != 0x0000
	      || PieCtrlRegs.PIEIFR2.all != 0x0000
	      || PieCtrlRegs.PIEIFR3.all != 0x0000 ) {}

	   // Check the ISRTrace to determine which order the ISR Routines completed
	   asm("        ESTOP0");

#endif
#if (TEST == 10)
// CASE 10:
//     Force all used PIE interrupts at once

       // Prepare for the test:
	   // Disable interrupts
	   // Clear the trace buffer, PIE Control Register, CPU IER and IFR registers
	   DINT;
	   for(i = 0; i < 50; i++) ISRTrace[i] = 0;
	   ISRTraceIndex = 0;
       InitPieCtrl();
       IER = 0;
       IFR &= 0;

       // Enable the PIE block
       PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

       // Enable all PIE group interrupts 1-8
       PieCtrlRegs.PIEIER1.all = 0x00FF;
       PieCtrlRegs.PIEIER2.all = 0x00FF;
       PieCtrlRegs.PIEIER3.all = 0x00FF;
       PieCtrlRegs.PIEIER4.all = 0x00FF;
       PieCtrlRegs.PIEIER5.all = 0x00FF;
       PieCtrlRegs.PIEIER6.all = 0x00FF;
       PieCtrlRegs.PIEIER9.all = 0x00FF;

	   // Make sure PIEACK for group 1, 2, 3, 4, 5, 6 and 9 are clear (default after reset)
       PieCtrlRegs.PIEACK.all = (M_INT1|M_INT2|M_INT3|M_INT4|M_INT5|M_INT6|M_INT9);

       // Enable CPU INT1, INT2, INT3, INT4, INT5, INT6 and INT9
       IER |= (M_INT1|M_INT2|M_INT3|M_INT4|M_INT5|M_INT6|M_INT9);

       // Force all valid interrupts for all PIE groups
       PieCtrlRegs.PIEIFR1.all = ISRS_GROUP1;
       PieCtrlRegs.PIEIFR2.all = ISRS_GROUP2;
       PieCtrlRegs.PIEIFR3.all = ISRS_GROUP3;
       PieCtrlRegs.PIEIFR4.all = ISRS_GROUP4;
       PieCtrlRegs.PIEIFR5.all = ISRS_GROUP5;
       PieCtrlRegs.PIEIFR6.all = ISRS_GROUP6;
       PieCtrlRegs.PIEIFR9.all = ISRS_GROUP9;

	   // Enable Global interrupts - CPU level
	   EINT;

	   // Wait for all group interrupts to be serviced
	   while(PieCtrlRegs.PIEIFR1.all != 0x0000
	      || PieCtrlRegs.PIEIFR2.all != 0x0000
	      || PieCtrlRegs.PIEIFR3.all != 0x0000
          || PieCtrlRegs.PIEIFR4.all != 0x0000
	      || PieCtrlRegs.PIEIFR5.all != 0x0000
	      || PieCtrlRegs.PIEIFR6.all != 0x0000
	      || PieCtrlRegs.PIEIFR9.all != 0x0000 ) {}

	   // Check the ISRTrace to determine which order the ISR Routines completed
	   asm("        ESTOP0");
#endif
}
//===========================================================================
// No more.
//===========================================================================
