#include "DSP2833x_Device.h"
#include "DSP2833x_GlobalPrototypes.h"
#include "rtwtypes.h"
#include "adc_oku1.h"
#include "adc_oku1_private.h"

void rt_OneStep(void);

/*-----------------------------------------------------------------------------
 * void config_schedulerTimer(void)
 *
 * Abstract:
 *      This function configures scheduler timer
 */
void config_schedulerTimer(void)
{
  InitCpuTimers();

  /* Configure CPU-Timer 0 to interrupt every 0.0001 sec. */
  /* Parameters:  Timer Pointer, CPU Freq in MHz, Period in usec. */
  ConfigCpuTimer(&CpuTimer0, 150.0, 0.0001 * 1000000);
  StartCpuTimer0();
}

void disableWatchdog(void)
{
  int *WatchdogWDCR = (void *) 0x7029;
  asm(" EALLOW ");
  *WatchdogWDCR = 0x0068;
  asm(" EDIS ");
}

interrupt void TINT0_isr(void)
{
  volatile unsigned int PIEIER1_stack_save = PieCtrlRegs.PIEIER1.all;
  PieCtrlRegs.PIEIER1.all &= ~64;      //disable group1 lower/equal priority interrupts
  asm(" RPT #5 || NOP");               //wait 5 cycles
  IFR &= ~1;                           //eventually disable lower/equal priority pending interrupts
  PieCtrlRegs.PIEACK.all = 1;          //ACK to allow other interrupts from the same group to fire
  IER |= 1;
  EINT;                                //global interrupt enable
  rt_OneStep();
  DINT;                                // disable global interrupts during context switch, CPU will enable global interrupts after exiting ISR
  PieCtrlRegs.PIEIER1.all = PIEIER1_stack_save;//restore PIEIER register that was modified
}

void enable_interrupts()
{
  EALLOW;
  PieVectTable.TINT0 = &TINT0_isr;     // Hook interrupt to the ISR
  EDIS;
  PieCtrlRegs.PIEIER1.bit.INTx7 = 1;   // Enable interrupt TINT0
  IER |= M_INT1;

  // Enable global Interrupts and higher priority real-time debug events:
  EINT;                                // Enable Global interrupt INTM
  ERTM;                                // Enable Global realtime interrupt DBGM
}

void disable_interrupts()
{
  IER &= M_INT1;                       // Disable Global INT1 (CPU Interrupt 1)
  DINT;                                // Disable Global interrupt INTM
}
