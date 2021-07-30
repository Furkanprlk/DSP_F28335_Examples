/* PM_sincos_main.c */

#include "common.h"

unsigned long IdleLoopCount = 0;


void main(void)
{
	// initialise system control
    InitSysCtrl();
    EALLOW;
    ClkCfgRegs.PERCLKDIVSEL.bit.EPWMCLKDIV = 1; // clkdiv = /2, max PWM clock = 100MHz
    EDIS;

    // initialise GPIO
    InitGpio(); 								// configure default GPIO
    EALLOW;
    GpioCtrlRegs.GPADIR.bit.GPIO31 = 1;			// drives LED LD2 on controlCARD
    GpioDataRegs.GPADAT.bit.GPIO31 = 1;			// turn off LED
    EDIS;

	// sincos specific initialisation
	sincos_init();
	PM_sincos_initLib(&mySincos);

    // clear all interrupts and initialise PIE vector table
    DINT;
    InitPieCtrl();
    IER = 0x0000;
    IFR = 0x0000;
    InitPieVectTable();

    // map ISR functions
    EALLOW;
    PieVectTable.ADCC1_INT = &adcc_isr;			// ISR for ADC-C interrupt 1
    EDIS;

    // enable global Interrupts and higher priority real-time debug events
    PieCtrlRegs.PIEIER1.bit.INTx3 = 1;			// ADCC1 PIE interrupt enable
    IER |= M_INT1; 								// enable group 1 interrupts
    SetDBGIER(0x0001);							// configure DBGIER register
    EINT;  										// enable global interrupt INTM
    ERTM;  										// enable global realtime interrupt DBGM
    EPwm1Regs.TBCTL.bit.CTRMODE = 0; 			// release PWM1 TB counter in up-count mode

    do {
    	IdleLoopCount++;
    } while(1);
}

 /* end of file */
