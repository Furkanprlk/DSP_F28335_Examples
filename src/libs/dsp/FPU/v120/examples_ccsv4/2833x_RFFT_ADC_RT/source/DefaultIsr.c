/**********************************************************************
* File: DefaultIsr.c
* Devices: TMS320F2833x
* Author: ASP, Yu Cai, Texas Instruments
* History:
*   09/15/10
**********************************************************************/

#include "Lab.h"							// Main include file

//---------------------------------------------------------------------
interrupt void INT13_ISR(void)					// 0x000D1A  INT13 - XINT13 or CPU Timer1
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void INT14_ISR(void)					// 0x000D1C  INT14 - CPU Timer2
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void DATALOG_ISR(void)				// 0x000D1E  DATALOG - CPU data logging interrupt
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void RTOSINT_ISR(void)				// 0x000D20  RTOSINT - CPU RTOS interrupt
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EMUINT_ISR(void) 				// 0x000D22  EMUINT - CPU emulation interrupt
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void NMI_ISR(void)					// 0x000D24  NMI - XNMI interrupt
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ILLEGAL_ISR(void)				// 0x000D26  ILLEGAL - illegal operation trap
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER1_ISR(void)					// 0x000D28  USER1 - software interrupt #1
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER2_ISR(void)					// 0x000D2A  USER2 - software interrupt #2
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER3_ISR(void)					// 0x000D2C  USER3 - software interrupt #3
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER4_ISR(void)					// 0x000D2E  USER4 - software interrupt #4
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER5_ISR(void)					// 0x000D30  USER5 - software interrupt #5
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER6_ISR(void)					// 0x000D32  USER6 - software interrupt #6
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER7_ISR(void)					// 0x000D34  USER7 - software interrupt #7
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER8_ISR(void)					// 0x000D36  USER8 - software interrupt #8
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER9_ISR(void)					// 0x000D38  USER9 - software interrupt #9
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER10_ISR(void)					// 0x000D3A  USER10 - software interrupt #10
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER11_ISR(void)					// 0x000D3C  USER11 - software interrupt #11
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void USER12_ISR(void)					// 0x000D3E  USER12 - software interrupt #12
{
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void SEQ1INT_ISR(void)				// PIE1.1 @ 0x000D40  SEQ1INT (ADC SEQ1)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void SEQ2INT_ISR(void)				// PIE1.2 @ 0x000D42  SEQ2INT (ADC SEQ2)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE1.3 @ 0x000D44 reserved

//---------------------------------------------------------------------
interrupt void XINT1_ISR(void)					// PIE1.4 @ 0x000D46  XINT1
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}     

//---------------------------------------------------------------------
interrupt void XINT2_ISR(void)					// PIE1.5 @ 0x000D48  XINT2
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ADCINT_ISR(void)					// PIE1.6 @ 0x000D4A  ADCINT (ADC)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void TINT0_ISR(void)					// PIE1.7 @ 0x000D4C  TINT0 (CPU TIMER 0)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void WAKEINT_ISR(void)				// PIE1.8 @ 0x000D4E  WAKEINT (LPM/WD)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;		// Must acknowledge the PIE group
  
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM1_TZINT_ISR(void)			// PIE2.1 @ 0x000D50  EPWM1_TZINT (EPWM1)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM2_TZINT_ISR(void)			// PIE2.2 @ 0x000D52  EPWM2_TZINT (EPWM2)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM3_TZINT_ISR(void)			// PIE2.3 @ 0x000D54  EPWM3_TZINT (EPWM3)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;		// Must acknowledge the PIE group
  
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM4_TZINT_ISR(void)			// PIE2.4 @ 0x000D56  EPWM4_TZINT (EPWM4)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;		// Must acknowledge the PIE group
  
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM5_TZINT_ISR(void)			// PIE2.5 @ 0x000D58  EPWM5_TZINT (EPWM5)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM6_TZINT_ISR(void)			// PIE2.6 @ 0x000D5A  EPWM6_TZINT (EPWM6)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP2;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE2.7 @ 0x000D5C reserved
												// PIE2.8 @ 0x000D5E reserved
     
//---------------------------------------------------------------------
interrupt void EPWM1_INT_ISR(void)				// PIE3.1 @ 0x000D60  EPWM1_INT (EPWM1)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM2_INT_ISR(void)				// PIE3.2 @ 0x000D62  EPWM2_INT (EPWM2)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM3_INT_ISR(void)				// PIE3.3 @ 0x000D64  EPWM3_INT (EPWM3)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM4_INT_ISR(void)				// PIE3.4 @ 0x000D66  EPWM4_INT (EPWM4)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM5_INT_ISR(void)				// PIE3.5 @ 0x000D68  EPWM5_INT (EPWM5)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EPWM6_INT_ISR(void)				// PIE3.6 @ 0x000D6A  EPWM6_INT (EPWM6)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE3.7 @ 0x000D6C reserved
												// PIE3.8 @ 0x000D6E reserved

//---------------------------------------------------------------------
interrupt void ECAP1_INT_ISR(void)				// PIE4.1 @ 0x000D70  ECAP1_INT (ECAP1)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ECAP2_INT_ISR(void)				// PIE4.2 @ 0x000D72  ECAP2_INT (ECAP2)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ECAP3_INT_ISR(void)				// PIE4.3 @ 0x000D74  ECAP3_INT (ECAP3)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ECAP4_INT_ISR(void)				// PIE4.4 @ 0x000D76  ECAP4_INT (ECAP4)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ECAP5_INT_ISR(void)				// PIE4.5 @ 0x000D78  ECAP5_INT (ECAP5)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ECAP6_INT_ISR(void)				// PIE4.6 @ 0x000D7A  ECAP6_INT (ECAP6)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP4;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE4.7 @ 0x000D7C reserved
												// PIE4.8 @ 0x000D7E reserved

//---------------------------------------------------------------------
interrupt void EQEP1_INT_ISR(void)				// PIE5.1 @ 0x000D80  EQEP1_INT (EQEP1)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;		// Must acknowledge the PIE group
 
// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void EQEP2_INT_ISR(void)				// PIE5.2 @ 0x000D82  EQEP2_INT (EQEP2)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP5;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE5.3 @ 0x000D84 reserved
												// PIE5.4 @ 0x000D86 reserved
												// PIE5.5 @ 0x000D88 reserved
												// PIE5.6 @ 0x000D8A reserved
												// PIE5.7 @ 0x000D8C reserved
												// PIE5.8 @ 0x000D8E reserved

//---------------------------------------------------------------------
interrupt void SPIRXINTA_ISR(void)				// PIE6.1 @ 0x000D90  SPIRXINTA (SPI-A)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void SPITXINTA_ISR(void)				// PIE6.2 @ 0x000D92  SPITXINTA (SPI-A)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void MRINTB_ISR(void)					// PIE6.3 @ 0x000D94  MRINTB (McBSP-B)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void MXINTB_ISR(void)					// PIE6.4 @ 0x000D96  MXINTB (McBSP-B)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void MRINTA_ISR(void)					// PIE6.5 @ 0x000D98  MRINTA (McBSP-A)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void MXINTA_ISR(void)					// PIE6.6 @ 0x000D9A  MXINTA (McBSP-A)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP6;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE6.7 @ 0x000D9C reserved
												// PIE6.8 @ 0x000D9E reserved

//---------------------------------------------------------------------
interrupt void DINTCH1_ISR(void)				// PIE7.1 @ 0x000DA0  DINTCH1 (DMA)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void DINTCH2_ISR(void)				// PIE7.2 @ 0x000DA2  DINTCH2 (DMA)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void DINTCH3_ISR(void)				// PIE7.3 @ 0x000DA4  DINTCH3 (DMA)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void DINTCH4_ISR(void)				// PIE7.4 @ 0x000DA6  DINTCH4 (DMA)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void DINTCH5_ISR(void)				// PIE7.5 @ 0x000DA8  DINTCH5 (DMA)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void DINTCH6_ISR(void)				// PIE7.6 @ 0x000DAA  DINTCH6 (DMA)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP7;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE7.7 @ 0x000DAC reserved
												// PIE7.8 @ 0x000DAE reserved

//---------------------------------------------------------------------
interrupt void I2CINT1A_ISR(void)				// PIE8.1 @ 0x000DB0  I2CINT1A (I2C-A)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void I2CINT2A_ISR(void)				// PIE8.2 @ 0x000DB2  I2CINT2A (I2C-A)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE8.3 @ 0x000DB4 reserved
												// PIE8.4 @ 0x000DB6 reserved

//---------------------------------------------------------------------
interrupt void SCIRXINTC_ISR(void)				// PIE8.5 @ 0x000DB8  SCIRXINTC (SCI-C)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void SCITXINTC_ISR(void)				// PIE8.6 @ 0x000DBA  SCIRXINTC (SCI-C)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP8;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE8.7 @ 0x000DBC reserved
												// PIE8.8 @ 0x000DBE reserved

//---------------------------------------------------------------------
interrupt void SCIRXINTA_ISR(void)				// PIE9.1 @ 0x000DC0  SCIRXINTA (SCI-A)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void SCITXINTA_ISR(void)				// PIE9.2 @ 0x000DC2  SCITXINTA (SCI-A)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void SCIRXINTB_ISR(void)				// PIE9.3 @ 0x000DC4  SCIRXINTB (SCI-B)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void SCITXINTB_ISR(void)				// PIE9.4 @ 0x000DC6  SCITXINTB (SCI-B)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ECAN0INTA_ISR(void)				// PIE9.5 @ 0x000DC8  ECAN0_INTA (ECAN-A)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ECAN1INTA_ISR(void)				// PIE9.6 @ 0x000DCA  ECAN1_INTA (ECAN-A)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ECAN0INTB_ISR(void)				// PIE9.7 @ 0x000DCC  ECAN0_INTB (ECAN-B)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
interrupt void ECAN1INTB_ISR(void)				// PIE9.8 @ 0x000DCE  ECAN1_INTB (ECAN-B)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP9;		// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}

//---------------------------------------------------------------------
												// PIE10.1 @ 0x000DD0 reserved
												// PIE10.2 @ 0x000DD2 reserved
												// PIE10.3 @ 0x000DD4 reserved
												// PIE10.4 @ 0x000DD6 reserved
												// PIE10.5 @ 0x000DD8 reserved
												// PIE10.6 @ 0x000DDA reserved
												// PIE10.7 @ 0x000DDC reserved
												// PIE10.8 @ 0x000DDE reserved

//---------------------------------------------------------------------
												// PIE11.1 @ 0x000DE0 reserved
												// PIE11.2 @ 0x000DE2 reserved
												// PIE11.3 @ 0x000DE4 reserved
												// PIE11.4 @ 0x000DE6 reserved
												// PIE11.5 @ 0x000DE8 reserved
												// PIE11.6 @ 0x000DEA reserved
												// PIE11.7 @ 0x000DEC reserved
												// PIE11.8 @ 0x000DEE reserved

//---------------------------------------------------------------------
interrupt void XINT3_ISR(void)					// PIE12.1 @ 0x000DF0  XINT3
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;	// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}     

//---------------------------------------------------------------------
interrupt void XINT4_ISR(void)					// PIE12.2 @ 0x000DF2  XINT4
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;	// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}     

//---------------------------------------------------------------------
interrupt void XINT5_ISR(void)					// PIE12.3 @ 0x000DF4  XINT5
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;	// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}     

//---------------------------------------------------------------------
interrupt void XINT6_ISR(void)					// PIE12.4 @ 0x000DF6  XINT6
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;	// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}     

//---------------------------------------------------------------------
interrupt void XINT7_ISR(void)					// PIE12.5 @ 0x000DF8  XINT7
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;	// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}     
//---------------------------------------------------------------------
												// PIE12.6 @ 0x000DFA reserved

//---------------------------------------------------------------------
interrupt void LVF_ISR(void)					// PIE12.7 @ 0x000DFC  LVF (FPU)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;	// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}     

//---------------------------------------------------------------------
interrupt void LUF_ISR(void)					// PIE12.8 @ 0x000DFE  LUF (FPU)
{
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP12;	// Must acknowledge the PIE group

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}     

//---------------------------------------------------------------------
interrupt void rsvd_ISR(void)					// Reserved PIE vectors
{
// This ISR is for reserved PIE vectors.  It should never be reached by
// properly executing code.  If you get here, it means something is wrong.

// Next two lines for debug only - remove after inserting your ISR
	asm (" ESTOP0");							// Emulator Halt instruction
	while(1);
}


//--- end of file -----------------------------------------------------
