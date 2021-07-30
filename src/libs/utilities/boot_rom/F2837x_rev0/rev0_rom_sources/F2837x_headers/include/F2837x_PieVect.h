//###########################################################################
//
// FILE:   F2837x_PieVect.h
//
// TITLE:  F2837x Device PIE Vector Table Definitions
//
//###########################################################################
// $TI Release:   $
// $Release Date:   $
//###########################################################################

#ifndef F2837x_PIE_VECT_H
#define F2837x_PIE_VECT_H
#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
// PIE Interrupt Vector Table Definition:
// Create a user type called PINT (pointer to interrupt):

typedef __interrupt void (*PINT)(void);

// Define Vector Table:
struct PIE_VECT_TABLE {
    PINT  PIE1_RESERVED;                              // Reserved 
    PINT  PIE2_RESERVED;                              // Reserved 
    PINT  PIE3_RESERVED;                              // Reserved 
    PINT  PIE4_RESERVED;                              // Reserved 
    PINT  PIE5_RESERVED;                              // Reserved 
    PINT  PIE6_RESERVED;                              // Reserved 
    PINT  PIE7_RESERVED;                              // Reserved 
    PINT  PIE8_RESERVED;                              // Reserved 
    PINT  PIE9_RESERVED;                              // Reserved 
    PINT  PIE10_RESERVED;                             // Reserved 
    PINT  PIE11_RESERVED;                             // Reserved 
    PINT  PIE12_RESERVED;                             // Reserved 
    PINT  PIE13_RESERVED;                             // Reserved 
    PINT  T1_INT;                                     // CPU Timer 1 Interrupt 
    PINT  T2_INT;                                     // CPU Timer 2 Interrupt 
    PINT  DATALOG_INT;                                // Datalogging Interrupt 
    PINT  RTOS_INT;                                   // RTOS Interrupt 
    PINT  EMU_INT;                                    // Emulation Interrupt 
    PINT  NMI_INT;                                    // Non-Maskable Interrupt 
    PINT  ILLEGAL_INT;                                // Illegal Operation Trap 
    PINT  USER1_INT;                                  // User Defined Trap 1 
    PINT  USER2_INT;                                  // User Defined Trap 2 
    PINT  USER3_INT;                                  // User Defined Trap 3 
    PINT  USER4_INT;                                  // User Defined Trap 4 
    PINT  USER5_INT;                                  // User Defined Trap 5 
    PINT  USER6_INT;                                  // User Defined Trap 6 
    PINT  USER7_INT;                                  // User Defined Trap 7 
    PINT  USER8_INT;                                  // User Defined Trap 8 
    PINT  USER9_INT;                                  // User Defined Trap 9 
    PINT  USER10_INT;                                 // User Defined Trap 10 
    PINT  USER11_INT;                                 // User Defined Trap 11 
    PINT  USER12_INT;                                 // User Defined Trap 12 
    PINT  ADC1_CH1_INT;                               // 1.1 - ADC1 Channel 1 Interrupt 
    PINT  ADC2_CH1_INT;                               // 1.2 - ADC2 Channel 1 Interrupt 
    PINT  ADC3_CH1_INT;                               // 1.3 - ADC3 Channel 1 Interrupt 
    PINT  XINT1_INT;                                  // 1.4 - XINT1 Interrupt 
    PINT  XINT2_INT;                                  // 1.5 - XINT2 Interrupt 
    PINT  ADC4_CH1_INT;                               // 1.6 - ADC4 Channel 1 Interrupt 
    PINT  T0_INT;                                     // 1.7 - Timer 0 Interrupt 
    PINT  WAKE_INT;                                   // 1.8 - Standby and Halt Wakeup Interrupt 
    PINT  EPWM1_TZ_INT;                               // 2.1 - ePWM1 Trip Zone Interrupt 
    PINT  EPWM2_TZ_INT;                               // 2.2 - ePWM2 Trip Zone Interrupt 
    PINT  EPWM3_TZ_INT;                               // 2.3 - ePWM3 Trip Zone Interrupt 
    PINT  EPWM4_TZ_INT;                               // 2.4 - ePWM4 Trip Zone Interrupt 
    PINT  EPWM5_TZ_INT;                               // 2.5 - ePWM5 Trip Zone Interrupt 
    PINT  EPWM6_TZ_INT;                               // 2.6 - ePWM6 Trip Zone Interrupt 
    PINT  EPWM7_TZ_INT;                               // 2.7 - ePWM7 Trip Zone Interrupt 
    PINT  EPWM8_TZ_INT;                               // 2.8 - ePWM8 Trip Zone Interrupt 
    PINT  EPWM1_INT;                                  // 3.1 - ePWM1 Interrupt 
    PINT  EPWM2_INT;                                  // 3.2 - ePWM2 Interrupt 
    PINT  EPWM3_INT;                                  // 3.3 - ePWM3 Interrupt 
    PINT  EPWM4_INT;                                  // 3.4 - ePWM4 Interrupt 
    PINT  EPWM5_INT;                                  // 3.5 - ePWM5 Interrupt 
    PINT  EPWM6_INT;                                  // 3.6 - ePWM6 Interrupt 
    PINT  EPWM7_INT;                                  // 3.7 - ePWM7 Interrupt 
    PINT  EPWM8_INT;                                  // 3.8 - ePWM8 Interrupt 
    PINT  ECAP1_INT;                                  // 4.1 - eCAP1 Interrupt 
    PINT  ECAP2_INT;                                  // 4.2 - eCAP2 Interrupt 
    PINT  ECAP3_INT;                                  // 4.3 - eCAP3 Interrupt 
    PINT  ECAP4_INT;                                  // 4.4 - eCAP4 Interrupt 
    PINT  ECAP5_INT;                                  // 4.5 - eCAP5 Interrupt 
    PINT  ECAP6_INT;                                  // 4.6 - eCAP6 Interrupt 
    PINT  PIE14_RESERVED;                             // 4.7 - Reserved 
    PINT  PIE15_RESERVED;                             // 4.8 - Reserved 
    PINT  EQEP1_INT;                                  // 5.1 - eQEP1 Interrupt 
    PINT  EQEP2_INT;                                  // 5.2 - eQEP2 Interrupt 
    PINT  EQEP3_INT;                                  // 5.3 - eQEP3 Interrupt 
    PINT  PIE16_RESERVED;                             // 5.4 - Reserved 
    PINT  CLB1_INT;                                   // 5.5 - CLB1 (Reconfigurable Logic) Interrupt 
    PINT  CLB2_INT;                                   // 5.6 - CLB2 (Reconfigurable Logic) Interrupt 
    PINT  CLB3_INT;                                   // 5.7 - CLB3 (Reconfigurable Logic) Interrupt 
    PINT  CLB4_INT;                                   // 5.8 - CLB4 (Reconfigurable Logic) Interrupt 
    PINT  SPIA_RX_INT;                                // 6.1 - SPIA Receive Interrupt 
    PINT  SPIA_TX_INT;                                // 6.2 - SPIA Transmit Interrupt 
    PINT  SPIB_RX_INT;                                // 6.3 - SPIB Receive Interrupt 
    PINT  SPIB_TX_INT;                                // 6.4 - SPIB Transmit Interrupt 
    PINT  MCBSPA_RX_INT;                              // 6.5 - McBSPA Receive Interrupt 
    PINT  MCBSPA_TX_INT;                              // 6.6 - McBSPA Transmit Interrupt 
    PINT  MCBSPB_RX_INT;                              // 6.7 - McBSPB Receive Interrupt 
    PINT  MCBSPB_TX_INT;                              // 6.8 - McBSPB Transmit Interrupt 
    PINT  DMA_CH1_INT;                                // 7.1 - DMA Channel 1 Interrupt 
    PINT  DMA_CH2_INT;                                // 7.2 - DMA Channel 2 Interrupt 
    PINT  DMA_CH3_INT;                                // 7.3 - DMA Channel 3 Interrupt 
    PINT  DMA_CH4_INT;                                // 7.4 - DMA Channel 4 Interrupt 
    PINT  DMA_CH5_INT;                                // 7.5 - DMA Channel 5 Interrupt 
    PINT  DMA_CH6_INT;                                // 7.6 - DMA Channel 6 Interrupt 
    PINT  PIE17_RESERVED;                             // 7.7 - Reserved 
    PINT  PIE18_RESERVED;                             // 7.8 - Reserved 
    PINT  I2CA_R1_INT;                                // 8.1 - I2CA Interrupt 1 
    PINT  I2CA_R2_INT;                                // 8.2 - I2CA Interrupt 2 
    PINT  I2CB_R1_INT;                                // 8.3 - I2CB Interrupt 1 
    PINT  I2CB_R2_INT;                                // 8.4 - I2CB Interrupt 2 
    PINT  SCIC_RX_INT;                                // 8.5 - SCIC Receive Interrupt 
    PINT  SCIC_TX_INT;                                // 8.6 - SCIC Transmit Interrupt 
    PINT  SCID_RX_INT;                                // 8.7 - SCID Receive Interrupt 
    PINT  SCID_TX_INT;                                // 8.8 - SCID Transmit Interrupt 
    PINT  SCIA_RX_INT;                                // 9.1 - SCIA Receive Interrupt 
    PINT  SCIA_TX_INT;                                // 9.2 - SCIA Transmit Interrupt 
    PINT  SCIB_RX_INT;                                // 9.3 - SCIB Receive Interrupt 
    PINT  SCIB_TX_INT;                                // 9.4 - SCIB Transmit Interrupt 
    PINT  DCANA_1_INT;                                // 9.5 - DCANA Interrupt 1 
    PINT  DCANA_2_INT;                                // 9.6 - DCANA Interrupt 2 
    PINT  DCANB_1_INT;                                // 9.7 - DCANB Interrupt 1 
    PINT  DCANB_2_INT;                                // 9.8 - DCANB Interrupt 2 
    PINT  ADC1_EVT_INT;                               // 10.1 - ADC1 Event Interrupt 
    PINT  ADC1_CH2_INT;                               // 10.2 - ADC1 Channel 2 Interrupt 
    PINT  ADC1_CH3_INT;                               // 10.3 - ADC1 Channel 3 Interrupt 
    PINT  ADC1_CH4_INT;                               // 10.4 - ADC1 Channel 4 Interrupt 
    PINT  ADC2_EVT_INT;                               // 10.5 - ADC2 Event Interrupt 
    PINT  ADC2_CH2_INT;                               // 10.6 - ADC2 Channel 2 Interrupt 
    PINT  ADC2_CH3_INT;                               // 10.7 - ADC2 Channel 3 Interrupt 
    PINT  ADC2_CH4_INT;                               // 10.8 - ADC2 Channel 4 Interrupt 
    PINT  CLA1_1_INT;                                 // 11.1 - CLA1 Interrupt 1 
    PINT  CLA1_2_INT;                                 // 11.2 - CLA1 Interrupt 2 
    PINT  CLA1_3_INT;                                 // 11.3 - CLA1 Interrupt 3 
    PINT  CLA1_4_INT;                                 // 11.4 - CLA1 Interrupt 4 
    PINT  CLA1_5_INT;                                 // 11.5 - CLA1 Interrupt 5 
    PINT  CLA1_6_INT;                                 // 11.6 - CLA1 Interrupt 6 
    PINT  CLA1_7_INT;                                 // 11.7 - CLA1 Interrupt 7 
    PINT  CLA1_8_INT;                                 // 11.8 - CLA1 Interrupt 8 
    PINT  XINT3_INT;                                  // 12.1 - XINT3 Interrupt 
    PINT  XINT4_INT;                                  // 12.2 - XINT4 Interrupt 
    PINT  XINT5_INT;                                  // 12.3 - XINT5 Interrupt 
    PINT  PBIST_INT;                                  // 12.4 - PBIST Interrupt
    PINT  FMC_INT;                                    // 12.5 - Flash Wrapper Operation Done Interrupt 
    PINT  VCU_INT;                                    // 12.6 - VCU Interrupt 
    PINT  FPU_OFLOW_INT;                              // 12.7 - FPU Overflow Interrupt 
    PINT  FPU_UFLOW_INT;                              // 12.8 - FPU Underflow Interrupt 
    PINT  PIE20_RESERVED;                             // 1.9 - Reserved 
    PINT  PIE21_RESERVED;                             // 1.10 - Reserved 
    PINT  PIE22_RESERVED;                             // 1.11 - Reserved 
    PINT  PIE23_RESERVED;                             // 1.12 - Reserved 
    PINT  CIPC1_INT;                                  // 1.13 - IPC Interrupt 1 
    PINT  CIPC2_INT;                                  // 1.14 - IPC Interrupt 2 
    PINT  CIPC3_INT;                                  // 1.15 - IPC Interrupt 3 
    PINT  CIPC4_INT;                                  // 1.16 - IPC Interrupt 4 
    PINT  EPWM9_TZ_INT;                               // 2.9 - ePWM9 Trip Zone Interrupt 
    PINT  EPWM10_TZ_INT;                              // 2.10 - ePWM10 Trip Zone Interrupt 
    PINT  EPWM11_TZ_INT;                              // 2.11 - ePWM11 Trip Zone Interrupt 
    PINT  EPWM12_TZ_INT;                              // 2.12 - ePWM12 Trip Zone Interrupt 
    PINT  PIE24_RESERVED;                             // 2.13 - Reserved 
    PINT  PIE25_RESERVED;                             // 2.14 - Reserved 
    PINT  PIE26_RESERVED;                             // 2.15 - Reserved 
    PINT  PIE27_RESERVED;                             // 2.16 - Reserved 
    PINT  EPWM9_INT;                                  // 3.9 - ePWM9 Interrupt 
    PINT  EPWM10_INT;                                 // 3.10 - ePWM10 Interrupt 
    PINT  EPWM11_INT;                                 // 3.11 - ePWM11 Interrupt 
    PINT  EPWM12_INT;                                 // 3.12 - ePWM12 Interrupt 
    PINT  PIE28_RESERVED;                             // 3.13 - Reserved 
    PINT  PIE29_RESERVED;                             // 3.14 - Reserved 
    PINT  PIE30_RESERVED;                             // 3.15 - Reserved 
    PINT  PIE31_RESERVED;                             // 3.16 - Reserved 
    PINT  PIE32_RESERVED;                             // 4.9 - Reserved 
    PINT  PIE33_RESERVED;                             // 4.10 - Reserved 
    PINT  PIE34_RESERVED;                             // 4.11 - Reserved 
    PINT  PIE35_RESERVED;                             // 4.12 - Reserved 
    PINT  PIE36_RESERVED;                             // 4.13 - Reserved 
    PINT  PIE37_RESERVED;                             // 4.14 - Reserved 
    PINT  PIE38_RESERVED;                             // 4.15 - Reserved 
    PINT  PIE39_RESERVED;                             // 4.16 - Reserved 
    PINT  SD1_INT;                                    // 5.9  - SD1 Interrupt
    PINT  SD2_INT;                                    // 5.10 - SD2 Interrupt 
    PINT  PIE40_RESERVED;                             // 5.11 - Reserved 
    PINT  PIE41_RESERVED;                             // 5.12 - Reserved 
    PINT  PIE42_RESERVED;                             // 5.13 - Reserved 
    PINT  PIE43_RESERVED;                             // 5.14 - Reserved 
    PINT  PIE44_RESERVED;                             // 5.15 - Reserved 
    PINT  PIE45_RESERVED;                             // 5.16 - Reserved 
    PINT  SPIC_RX_INT;                                // 6.9 - SPIC Receive Interrupt 
    PINT  SPIC_TX_INT;                                // 6.10 - SPIC Transmit Interrupt 
    PINT  PIE46_RESERVED;                             // 6.11 - Reserved 
    PINT  PIE47_RESERVED;                             // 6.12 - Reserved 
    PINT  PIE48_RESERVED;                             // 6.13 - Reserved 
    PINT  PIE49_RESERVED;                             // 6.14 - Reserved 
    PINT  PIE50_RESERVED;                             // 6.15 - Reserved 
    PINT  PIE51_RESERVED;                             // 6.16 - Reserved 
    PINT  PIE52_RESERVED;                             // 7.9 - Reserved 
    PINT  PIE53_RESERVED;                             // 7.10 - Reserved 
    PINT  PIE54_RESERVED;                             // 7.11 - Reserved 
    PINT  PIE55_RESERVED;                             // 7.12 - Reserved 
    PINT  PIE56_RESERVED;                             // 7.13 - Reserved 
    PINT  PIE57_RESERVED;                             // 7.14 - Reserved 
    PINT  PIE58_RESERVED;                             // 7.15 - Reserved 
    PINT  PIE59_RESERVED;                             // 7.16 - Reserved 
    PINT  PIE60_RESERVED;                             // 8.9 - Reserved 
    PINT  PIE61_RESERVED;                             // 8.10 - Reserved 
    PINT  PIE62_RESERVED;                             // 8.11 - Reserved 
    PINT  PIE63_RESERVED;                             // 8.12 - Reserved 
    PINT  PIE64_RESERVED;                             // 8.13 - Reserved 
    PINT  PIE65_RESERVED;                             // 8.14 - Reserved 
#ifdef CPU1
    PINT  UPPA_INT;                                   // 8.15 - uPPA Interrupt 
    PINT  PIE67_RESERVED;                             // 8.16 - Reserved 
#elif defined(CPU2)
    PINT  PIE66_RESERVED;                             // 8.15 - Reserved 
    PINT  PIE68_RESERVED;                             // 8.16 - Reserved 
#endif
    PINT  PIE69_RESERVED;                             // 9.9 - Reserved 
    PINT  PIE70_RESERVED;                             // 9.10 - Reserved 
    PINT  PIE71_RESERVED;                             // 9.11 - Reserved 
    PINT  PIE72_RESERVED;                             // 9.12 - Reserved 
    PINT  PIE73_RESERVED;                             // 9.13 - Reserved 
    PINT  PIE74_RESERVED;                             // 9.14 - Reserved 
#ifdef CPU1
    PINT  USBA_INT;                                   // 9.15 - USBA Interrupt 
#elif defined(CPU2)
    PINT  PIE75_RESERVED;                             // 9.15 - Reserved 
#endif
    PINT  USBB_INT;                                   // 9.16 - USBB Interrupt 
    PINT  ADC3_EVT_INT;                               // 10.9 - ADC3 Event Interrupt 
    PINT  ADC3_CH2_INT;                               // 10.10 - ADC3 Channel 2 Interrupt 
    PINT  ADC3_CH3_INT;                               // 10.11 - ADC3 Channel 3 Interrupt 
    PINT  ADC3_CH4_INT;                               // 10.12 - ADC3 Channel 4 Interrupt 
    PINT  ADC4_EVT_INT;                               // 10.13 - ADC4 Event Interrupt 
    PINT  ADC4_CH2_INT;                               // 10.14 - ADC4 Channel 2 Interrupt 
    PINT  ADC4_CH3_INT;                               // 10.15 - ADC4 Channel 3 Interrupt 
    PINT  ADC4_CH4_INT;                               // 10.16 - ADC4 Channel 4 Interrupt 
    PINT  PIE76_RESERVED;                             // 11.9 - Reserved 
    PINT  PIE77_RESERVED;                             // 11.10 - Reserved 
    PINT  PIE78_RESERVED;                             // 11.11 - Reserved 
    PINT  PIE79_RESERVED;                             // 11.12 - Reserved 
    PINT  PIE80_RESERVED;                             // 11.13 - Reserved 
    PINT  PIE81_RESERVED;                             // 11.14 - Reserved 
    PINT  PIE82_RESERVED;                             // 11.15 - Reserved 
    PINT  PIE83_RESERVED;                             // 11.16 - Reserved 
    PINT  EMIF_ERR_INT;                               // 12.9 - EMIF Error Interrupt 
    PINT  RAM_CORRECTABLE_ERR_INT;                    // 12.10 - RAM Correctable Error Interrupt 
    PINT  FLASH_CORRECTABLE_ERR_INT;                  // 12.11 - Flash Correctable Error Interrupt 
    PINT  RAM_ACC_VIOL_INT;                           // 12.12 - RAM Access Violation Interrupt 
    PINT  SYS_PLL_SLIP_INT;                           // 12.13 - System PLL Slip Interrupt 
    PINT  AUX_PLL_SLIP_INT;                           // 12.14 - Auxiliary PLL Slip Interrupt 
    PINT  CLA_LVF_INT;                             	  // 12.15 - Reserved
    PINT  CLA_LUF_INT;                             	  // 12.16 - Reserved
};

//---------------------------------------------------------------------------
// PieVect External References & Function Declarations:
//

extern struct PIE_VECT_TABLE PieVectTable;

#ifdef __cplusplus
}
#endif                                                /* extern "C" */


#endif                                                // end of F2837x_PIEVECT_H definition
//===========================================================================
// End of file.
//===========================================================================
