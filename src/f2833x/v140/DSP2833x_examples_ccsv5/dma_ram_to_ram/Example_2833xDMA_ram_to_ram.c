//###########################################################################
// Description:
//! \addtogroup f2833x_example_list
//! <h1> DMA Ram to Ram (dma_ram_to_ram)</h1>
//!
//! This example will perform a block copy from L5 SARAM to L4 SARAM of 1024
//! words. Transfer will be started by Timer0. Will use 32-bit data size to
//! decrease the transfer time.
//!
//! \b Watch \b Variables \n
//! - DMABuf1
//! - DMABuf2
//
//
//###########################################################################
// $TI Release: F2833x/F2823x Header Files and Peripheral Examples V140 $
// $Release Date: March  4, 2015 $
// $Copyright: Copyright (C) 2007-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File

#define BUF_SIZE   1024  // Sample buffer size

// DMA Defines
#define CH1_TOTAL               DATA_POINTS_PER_CHANNEL
#define CH1_WORDS_PER_BURST     ADC_CHANNELS_TO_CONVERT

#pragma DATA_SECTION(DMABuf1,"DMARAML4");
#pragma DATA_SECTION(DMABuf2,"DMARAML5");

volatile Uint16 DMABuf1[1024];
volatile Uint16 DMABuf2[1024];

volatile Uint16 *DMADest;
volatile Uint16 *DMASource;

__interrupt void local_DINTCH1_ISR(void);

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
// InitGpio();  // Skipped for this example

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
   EALLOW;	// Allow access to EALLOW protected registers
   PieVectTable.DINTCH1= &local_DINTCH1_ISR;
   EDIS;   // Disable access to EALLOW protected registers

   IER = M_INT7 ;	                             //Enable INT7 (7.1 DMA Ch1)
   EnableInterrupts();
   CpuTimer0Regs.TCR.bit.TSS  = 1;               //Stop Timer0 for now

//Step 5. User specific code, enable interrupts:
   // Initialize DMA
   DMAInitialize();

   // Initialize Tables
   for (i=0; i<BUF_SIZE; i++)
   {
     DMABuf1[i] = 0;
	 DMABuf2[i] = i;
   }

// Configure DMA Channel
    DMADest   = &DMABuf1[0];
	DMASource = &DMABuf2[0];
   	DMACH1AddrConfig(DMADest,DMASource);
	DMACH1BurstConfig(31,2,2);         //Will set up to use 32-bit datasize, pointers are based on 16-bit words
	DMACH1TransferConfig(31,2,2);      //so need to increment by 2 to grab the correct location
	DMACH1WrapConfig(0xFFFF,0,0xFFFF,0);
	//Use timer0 to start the x-fer.
	//Since this is a static copy use one shot mode, so only one trigger is needed
	//Also using 32-bit mode to decrease x-fer time
    DMACH1ModeConfig(DMA_TINT0,PERINT_ENABLE,ONESHOT_ENABLE,CONT_DISABLE,SYNC_DISABLE,SYNC_SRC,OVRFLOW_DISABLE,THIRTYTWO_BIT,CHINT_END,CHINT_ENABLE);

	StartDMACH1();

   //Init the timer 0
   CpuTimer0Regs.TIM.half.LSW = 512;    //load low value so we can start the DMA quickly
   CpuTimer0Regs.TCR.bit.SOFT = 1;      //Allow to free run even if halted
   CpuTimer0Regs.TCR.bit.FREE = 1;
   CpuTimer0Regs.TCR.bit.TIE  = 1;      //Enable the timer0 interrupt signal
   CpuTimer0Regs.TCR.bit.TSS  = 0;      //restart the timer 0
   for(;;){}
}

// INT7.1
__interrupt void local_DINTCH1_ISR(void)     // DMA Channel 1
{
  // To receive more interrupts from this PIE group, acknowledge this interrupt
   PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;

  // Next two lines for debug only to halt the processor here
  // Remove after inserting ISR Code
   __asm ("      ESTOP0");
   for(;;);
}



