//###########################################################################
// FILE:   startup_ccs.c
// TITLE:  Startup code for use with TI's Code Composer Studio.
//###########################################################################
// $TI Release: F28M35x Support Library v110 $
// $Release Date: December 12, 2011 $
//###########################################################################
//*****************************************************************************

//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
void ResetISR(void);
static void NmiSR(void);
static void FaultISR(void);
static void IntDefaultHandler(void);
static void BusFaultISR(void); 

//*****************************************************************************
//
// External declaration for the reset handler that is to be called when the
// processor is started
//
//*****************************************************************************
extern void _c_int00(void);

//*****************************************************************************
//
// Linker variable that marks the top of the stack.
//
//*****************************************************************************
extern unsigned long __STACK_TOP;

//*****************************************************************************
//
// External declarations for the interrupt handlers used by the application.
//
//*****************************************************************************

extern void SysTickIntHandler(void);
extern void AnimTimerIntHandler(void);

extern void Timer0IntHandler(void);
extern void Timer1IntHandler(void);

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000 or at the start of
// the program if located at a start address other than 0.
//
//*****************************************************************************
#pragma DATA_SECTION(g_pfnVectors, ".intvecs")
#pragma CODE_SECTION(ResetISR, ".resetisr")
void (* const g_pfnVectors[])(void) =
{
    (void (*)(void))((unsigned long)&__STACK_TOP),
                                            // The initial stack pointer
    ResetISR,                               // The reset handler
    NmiSR,                                  // The NMI handler
    FaultISR,                               // The hard fault handler
    IntDefaultHandler,                      // The MPU fault handler
    BusFaultISR,                            // The bus fault handler
    IntDefaultHandler,                      // The usage fault handler
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    IntDefaultHandler,                      // SVCall handler
    IntDefaultHandler,                      // Debug monitor handler
    0,                                      // Reserved
    IntDefaultHandler,                      // The PendSV handler
    IntDefaultHandler,                      // The SysTick handler
    IntDefaultHandler,                      // GPIO Port A
    IntDefaultHandler,                      // GPIO Port B
    IntDefaultHandler,                      // GPIO Port C
    IntDefaultHandler,                      // GPIO Port D
    IntDefaultHandler,                      // GPIO Port E
    IntDefaultHandler,                      // UART0 Rx and Tx
    IntDefaultHandler,                      // UART1 Rx and Tx
    IntDefaultHandler,                      // SSI0 Rx and Tx
    IntDefaultHandler,                      // I2C0 Master and Slave
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                   // Watchdog timer
    IntDefaultHandler,                      // Timer 0 subtimer A
    IntDefaultHandler,                      // Timer 0 subtimer B
    IntDefaultHandler,                      // Timer 1 subtimer A
    IntDefaultHandler,                      // Timer 1 subtimer B
    IntDefaultHandler,                        // Timer 2 subtimer A
    IntDefaultHandler,                      // Timer 2 subtimer B
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // System Control
    IntDefaultHandler,                      // FLASH Control
    IntDefaultHandler,                      // GPIO Port F
    IntDefaultHandler,                      // GPIO Port G
    IntDefaultHandler,                      // GPIO Port H
    IntDefaultHandler,                      // UART2 Rx and Tx
    IntDefaultHandler,                      // SSI1 Rx and Tx
    IntDefaultHandler,                      // Timer 3 subtimer A
    IntDefaultHandler,                      // Timer 3 subtimer B
    IntDefaultHandler,                      // I2C1 Master and Slave
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // EMAC
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // USB0
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // uDMA Software Transfer
    IntDefaultHandler,                      // uDMA Error
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // Reserved
    IntDefaultHandler,                      // External Peripheral Interface
    IntDefaultHandler,                      // GPIO Port J
    IntDefaultHandler,                        // Reserved
    IntDefaultHandler,                        // Reserved
    IntDefaultHandler,                        // SSI2
    IntDefaultHandler,                        // SSI3
    IntDefaultHandler,                        // UART3
    IntDefaultHandler,                        // UART4
    IntDefaultHandler,                        // Reserved
    IntDefaultHandler,                        // Reserved
    IntDefaultHandler,                        // Reserved
    IntDefaultHandler,                        // CAN0 INT0
    IntDefaultHandler,                        // CAN0 INT1
    IntDefaultHandler,                        // CAN1 INT0
    IntDefaultHandler,                        // CAN1 INT1
    IntDefaultHandler,                        // Reserved
    IntDefaultHandler,                        // Reserved
    IntDefaultHandler,                        // Reserved
    IntDefaultHandler,                        // Reserved
    IntDefaultHandler,                        // ADCINT1
    IntDefaultHandler,                        // ADCINT2
    IntDefaultHandler,                        // ADCINT3
    IntDefaultHandler,                        // ADCINT4
    IntDefaultHandler,                        // ADCINT5
    IntDefaultHandler,                        // ADCINT6
    IntDefaultHandler,                        // ADCINT7
    IntDefaultHandler,                        // ADCINT8
    IntDefaultHandler,                        // CTOMIPC1
    IntDefaultHandler,                        // CTOMIPC2
    IntDefaultHandler,                        // CTOMIPC3
    IntDefaultHandler,                        // CTOMIPC4
    IntDefaultHandler,                        // ATOMIPC1
    IntDefaultHandler,                        // ATOMIPC2
    IntDefaultHandler,                        // ATOMIPC3
    IntDefaultHandler,                        // ATOMIPC4
    IntDefaultHandler,                        // RAM Single Error
    IntDefaultHandler,                        // System/USB PLL Out of Lock
    IntDefaultHandler,                        // M3 Flash Single Error
    IntDefaultHandler                        // Reserved
};

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.  Any fancy
// actions (such as making decisions based on the reset cause register, and
// resetting the bits in that register) are left solely in the hands of the
// application.
//
//*****************************************************************************
void
ResetISR(void)
{
    //
    // Jump to the CCS C Initialization Routine.
    //
    __asm("    .global _c_int00\n"
          "    b.w     _c_int00");
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
static void
NmiSR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
FaultISR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an 
// uncorrectable memory error.  This simply enters an infinite loop, preserving 
// the system state for examination by a debugger.
// 
//
//*****************************************************************************
static void
BusFaultISR(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
IntDefaultHandler(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}




