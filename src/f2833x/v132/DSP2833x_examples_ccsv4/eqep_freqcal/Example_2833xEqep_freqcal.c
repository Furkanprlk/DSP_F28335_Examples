// TI File $Revision: /main/3 $
// Checkin $Date: June 5, 2010   14:08:52 $
//###########################################################################
//
// FILE:	Example_2833xEqep_freqcal.c
//
// TITLE:	Frequency measurement using EQEP peripheral
//
// ASSUMPTIONS:
//
//    This program requires the DSP2833x header files.
//    As supplied, this project is configured for "boot to SARAM" operation.
//
//    Test requires the following hardware connections
//
//    GPIO20/EQEP1A <- External input - connect to GPIO0/EPWM1A
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
//    This test will provide frequency measurement using capture unit (freqhz_pr)
//    and unit time out (freqhz_fr). The EPWM1A frequency will be measured by the EQEP.
//
//    By default, EPWM1A is configured to generate a frequency of 5 kHz - measured
//    frequency found in freqhz_pr and freqhz_fr should be 5000.
//
//    See DESCRIPTION in Example_freqcal.c for more details on the frequency calculation
//    performed in this example.
//
//    In addition to this file, the following files must be included in this project:
//    Example_freqcal.c - includes all eQEP functions
//    Example_EPwmSetup.c - sets up EPWM1A for use with this example
//    Example_freqcalh - includes initialization values for frequency structure.
//
//    * Maximum frequency is configured to 10Khz (BaseFreq)
//    * Minimum frequency is assumed at 50Hz for capture pre-scalar selection
//
//    SPEED_FR: High Frequency Measurement is obtained by counting the external input pulses
//              for 10ms (unit timer set to 100Hz).
//
// 	  SPEED_FR = { (Count Delta)/10ms }
//
//
//    SPEED_PR: Low Frequency Measurement is obtained by measuring time period of input edges.
//              Time measurement is averaged over 64edges for better results and
//              capture unit performs the time measurement using pre-scaled SYSCLK
//
//              Note that pre-scaler for capture unit clock is selected such that
//              capture timer does not overflow at the required minimum frequency
//
//              This example runs forever until the user stops it.
//
//
//    Watch Variables: freq.freqhz_fr - Frequency measurement using position counter/unit time out
//                     freq.freqhz_pr - Frequency measurement using capture unit
//
//###########################################################################
// Original Author: SD
//
// $TI Release: 2833x/2823x Header Files V1.32 $
// $Release Date: June 28, 2010 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "Example_freqcal.h"    // Example specific include file

void EPwmSetup(void);
interrupt void prdTick(void);

FREQCAL freq=FREQCAL_DEFAULTS;

void main(void)
{

// Step 1. Initialize System Control:
// PLL, WatchDog, enable Peripheral Clocks
// This example function is found in the DSP2833x_SysCtrl.c file.
   InitSysCtrl();

// Step 2. Initalize GPIO:
// This example function is found in the DSP2833x_Gpio.c file and
// illustrates how to set the GPIO to it's default state.
// InitGpio();  // Skipped for this example

// Only init the GPIO for EQep1 and EPwm1 in this case
// This function is found in DSP2833x_EQep.c
   InitEQep1Gpio();
   InitEPwm1Gpio();

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
   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.EPWM1_INT= &prdTick;
   EDIS;    // This is needed to disable write to EALLOW protected registers

// Step 4. Initialize all the Device Peripherals:
// Example specific ePWM setup.  This function is found
// in Example_EPwmSetup.c
   EPwmSetup();

// Step 5. User specific code, enable interrupts:
// Enable CPU INT1 which is connected to CPU-Timer 0:
   IER |= M_INT3;

// Enable TINT0 in the PIE: Group 3 interrupt 1
   PieCtrlRegs.PIEIER3.bit.INTx1 = 1;

// Enable global Interrupts and higher priority real-time debug events:
   EINT;   // Enable Global interrupt INTM
   ERTM;   // Enable Global realtime interrupt DBGM

   freq.init(&freq);         // Initializes eQEP for frequency calculation in
                             // FREQCAL_Init(void)function in Example_EPwmSetup.c
	for(;;)
	{
	}

}

interrupt void prdTick(void) // Interrupts once per ePWM period
{
   freq.calc(&freq); // Checks for event and calculates frequency in FREQCAL_Calc(FREQCAL *p)
                     // function in Example_EPwmSetup.c
   // Acknowledge this interrupt to receive more interrupts from group 1
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
   EPwm1Regs.ETCLR.bit.INT=1;
}

