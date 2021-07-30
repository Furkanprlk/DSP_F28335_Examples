//###########################################################################
//
// FILE:   F2837x_pbist_defines.h
//
// TITLE:  #defines used in pbist examples
//
//###########################################################################
// $TI Release: F2837x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: November 30, 2011 $
//###########################################################################

#ifndef F2837x_PBIST_DEFINES_H
#define F2837x_PBIST_DEFINES_H


#ifdef __cplusplus
extern "C" {
#endif

#define PBIST_BASE_ADD 					0x0005E200

#define PBIST_INTERRUPT_FLAG_ENABLE   	0x00000CF8  // 0x8 to enable
#define PBIST_INTERRUPT_FLAG_READ   	0x00000CF9  // 0x8 to be expected.
#define PBIST_INTERRUPT_FLAG   			0x00000CF9
#define PBIST_INTERRUPT_FLAG_CLEAR 	    0x00000088

//*****************************************************************************
// Value of PBIST_ALGO for the ALGO Groups
//*****************************************************************************
#define PBIST_ALGO_TR_G1					0x00000001	// 1  Triple Read: PBIST ROM
#define PBIST_ALGO_TR_G2					0x00000002	// 2  XOR Read: Self Test 0
#define PBIST_ALGO_TR_G3					0x00000004	// 3  XOR Read: Self Test 1
#define PBIST_ALGO_TR_G4					0x00000008	// 4  XOR Read: Self Test 2
#define PBIST_ALGO_TR_G5					0x00000010	// 5  XOR Read: Self Test 3
#define PBIST_ALGO_TR_G6					0x00000020	// 6  XOR Read: Secure ROM 0
#define PBIST_ALGO_TR_G7					0x00000040	// 7  XOR Read: Secure ROM 1
#define PBIST_ALGO_TR_G8					0x00000080	// 8  XOR Read: BootROM 0
#define PBIST_ALGO_TR_G9					0x00000100	// 9  XOR Read: BootROM 1
#define PBIST_ALGO_TR_G1011					0x00000200	// 10 XOR Read: CLA ROM 0,1
#define PBIST_ALGO_TR_G12					0x00000400	// 11 XOR Read: TMU ROM 0
#define PBIST_ALGO_TR_G13					0x00000800	// 12 XOR Read: TMU ROM 1
#define PBIST_ALGO_TR_G14					0x00001000	// 13 XOR Read: TMU ROM 2
#define PBIST_ALGO_TR_G15					0x00002000	// 14 XOR Read: TMU ROM 3
#define PBIST_ALGO_TR_G16					0x00004000	// 15 XOR Read: TMU ROM 4
#define PBIST_ALGO_TR_G17					0x00008000	// 16 XOR Read: TMU ROM 5
#define PBIST_ALGO_DOWN2_SPR	  		    0x00010000	// 17 Down2: Single Port RAM
#define PBIST_ALGO_DOWN2_TPR	  		    0x00020000	// 18 Down2: Two Port RAM
#define PBIST_ALGO_MARCH13_SPR_DC			0x00040000	// 19 March 13N: Single Port RAM Distributed Compare
#define PBIST_ALGO_MARCH13_TPR_DC			0x00080000	// 20 March 13N: Two Port RAM Distributed Compare
#define PBIST_ALGO_MDI_SPR_I				0x00100000	// 21 March Disturb Inc: Single Port RAM
#define PBIST_ALGO_MDD_SPR_I				0x00200000	// 22 March Disturb Dec: Single Port RAM
#define PBIST_ALGO_MC_SPR_DC				0x00400000	// 23 Map Column: Single Port RAM Distributed Compare
#define PBIST_ALGO_PRECH_SPR_DC				0x00800000	// 24 PreCharge: Single Port RAM Distributed Compare
#define PBIST_ALGO_DTXN2_SPR_DC				0x01000000	// 25 DTXN2: Single Port RAM Distributed Compare
#define PBIST_ALGO_FLIP_SPR_DC				0x02000000	// 26 Flip 10: Single Port RAM Distributed Compare
#define PBIST_ALGO_MDI_SPR_DC				0x04000000	// 27 March Disturb Inc: Single Port RAM Distributed Compare
#define PBIST_ALGO_MDD_SPR_DC				0x08000000	// 28 March Disturb Dec: Single Port RAM Distributed Compare
#define PBIST_ALGO_PMOS1_SPR_I				0x10000000	// 29 PMOS Open Slice: Single Port RAM Distributed Compare
#define PBIST_ALGO_PMOS2_SPR_I				0x20000000	// 30 PMOS Open Slice: Single Port RAM Distributed Compare
#define PBIST_ALGO_NONE						0x00000000	// No Algorithm Selected, use ROM default

//*****************************************************************************
// Values to select the specific memory groups in PBIST_RINFOL register
//*****************************************************************************
#define PBIST_RINFOL_PBIST_ROM				0x00000001	// 1  PBIST ROM Select
#define PBIST_RINFOL_SELF_TEST0_ROM			0x00000002	// 2  Self Test 0 ROM Select
#define PBIST_RINFOL_SELF_TEST1_ROM			0x00000004	// 3  Self Test 1 ROM Select
#define PBIST_RINFOL_SELF_TEST2_ROM			0x00000008	// 4  Self Test 2 ROM Select
#define PBIST_RINFOL_SELF_TEST3_ROM			0x00000010	// 5  Self Test 3 ROM Select
#define PBIST_RINFOL_SEC_ROM1				0x00000020	// 6  SECURE ROM 1 Select
#define PBIST_RINFOL_SEC_ROM0				0x00000040	// 7  SECURE ROM 0 Select
#define PBIST_RINFOL_BOOT_ROM0				0x00000080	// 8  Boot ROM 0 Select
#define PBIST_RINFOL_BOOT_ROM1				0x00000100	// 9  Boot ROM 1 Select
#define PBIST_RINFOL_CLA_ROM0				0x00000200	// 10 CLA DATA ROM 0 Select
#define PBIST_RINFOL_CLA_ROM1				0x00000400	// 11 CLA DATA ROM 1 Select
#define PBIST_RINFOL_TMU_ROM0				0x00000800	// 12 TMU ROM 0 Select
#define PBIST_RINFOL_TMU_ROM1				0x00001000	// 13 TMU ROM 1 Select
#define PBIST_RINFOL_TMU_ROM2				0x00002000	// 14 TMU ROM 2 Select
#define PBIST_RINFOL_TMU_ROM3				0x00004000	// 15 TMU ROM 3 Select
#define PBIST_RINFOL_TMU_ROM4				0x00008000	// 16 TMU ROM 4 Select
#define PBIST_RINFOL_TMU_ROM5				0x00010000	// 17 TMU ROM 5 Select
#define PBIST_RINFOL_GS0_1					0x00020000	// 18 GS0 GS1 Shared Memory Select
#define PBIST_RINFOL_GS4_7_9				0x00040000	// 19 GS4 GS7 GS9 Shared Memory Select
#define PBIST_RINFOL_GS2_3_5				0x00080000	// 20 GS2 GS3 GS5 Shared Memory Select
#define PBIST_RINFOL_GS6_8_10_11			0x00100000	// 21 GS6 GS8 GS10 GS11 Shared Memory Select
#define PBIST_RINFOL_GS12_13_14_15			0x00200000	// 22 GS12 GS13 GS14 GS15 Shared Memory Select
#define PBIST_RINFOL_CPU1_LS0_1_2_3_4_5		0x00400000	// 23 CPU1 LS0 LS1 LS2 LS3 LS4 LS5 Local Shared Memory Select
#define PBIST_RINFOL_CPU2_LS0_1_2_3_4_5		0x00800000	// 24 CPU2 LS0 LS1 LS2 LS3 LS4 LS5 Local Shared Memory Select
#define PBIST_RINFOL_CPUMSG0_1				0x01000000	// 25 CPU MSG 0 and 1 Select
#define PBIST_RINFOL_CLAMSG0_1				0x02000000	// 26 CLA MSG 0 and 1 Select
#define PBIST_RINFOL_CLAMSG2_3				0x04000000	// 27 CLA MSG 2 and 3 Select
#define PBIST_RINFOL_CPU1_D0_D1				0x08000000	// 28 CPU1 D0 D1 Dedicated RAM Select
#define PBIST_RINFOL_CPU2_D0_D1				0x10000000	// 29 CPU2 D0 D1 Dedicated RAM Select
#define PBIST_RINFOL_CPU1_M0_M1				0x20000000	// 30 CPU1 M0 M1 Select
#define PBIST_RINFOL_CPU2_M0_M1				0x40000000	// 31 CPU2 M0 M1 Select
#define PBIST_RINFOL_PIE_MEM0_1				0x80000000	// 32 PIE MEM0 and 1 Select
#define PBIST_RINFOL_NONE 					0x00000000  // 00 RINFOL register not set

//*****************************************************************************
// Values to select the specific memory groups in PBIST_RINFOL register
//*****************************************************************************
#define PBIST_RINFOU_PIE_MEM2_3				0x00000001	// 33 PIE MEM2 and 3 Select
#define PBIST_RINFOU_USB					0x00000002	// 34 USB RAM Select
#define PBIST_RINFOU_UPP_MEM_0_1			0x00000004	// 35 uPP FIFO & Message RAM Select - Two Port
#define PBIST_RINFOU_UPP_MEM_2_3_4_5		0x00000008	// 36 uPP FIFO & Message RAM Select - Two Port
#define PBIST_RINFOU_DCAN_MEM0_1_2			0x00000010	// 37 DCAN 0,1,2 Select
#define PBIST_RINFOU_DCAN_MEM3_4_5			0x00000020	// 38 DCAN 3,4,5 Select
#define PBIST_RINFOU_GS_0_3_DC				0x00000040	// 39 Shared Memory 0,1,2,3 Select Distributed Compare
#define PBIST_RINFOU_GS_4_7_DC				0x00000080	// 40 Shared Memory 4,5,6,7 Select Distributed Compare
#define PBIST_RINFOU_GS_8_11_DC				0x00000100	// 41 Shared Memory 8,9,10,11 Select Distributed Compare
#define PBIST_RINFOU_GS_12_15_DC			0x00000200	// 42 Shared Memory 12,13,14,15 Select Distributed Compare
#define PBIST_RINFOU_CPU1_LS_0_2_DC			0x00000400	// 43 Local Shared Memory 0,1,2 Distributed Compare
#define PBIST_RINFOU_CPU1_LS_3_5_DC			0x00000800	// 44 Local Shared Memory 3,4,5 Distributed Compare
#define PBIST_RINFOU_CPU2_LS_0_2_DC			0x00001000	// 45 Local Shared Memory 0,1,2 Distributed Compare
#define PBIST_RINFOU_CPU2_LS_3_5_DC			0x00002000	// 46 Local Shared Memory 3,4,5 Distributed Compare
#define PBIST_RINFOU_CPU_MSG_0_1_DC			0x00004000	// 47 CPU MSG RAM Select Distributed Compare
#define PBIST_RINFOU_CLA_MSG_0_1_DC			0x00008000	// 48 CLA MSG 0 and 1 Select Distributed Compare
#define PBIST_RINFOU_CLA_MSG_2_3_DC			0x00010000	// 49 CLA MSG 2 and 3 Select Distributed Compare
#define PBIST_RINFOU_CPU1_D0_D1_DC			0x00020000	// 50 CPU1 Dedicated RAM Select Distributed Compare
#define PBIST_RINFOU_CPU2_D0_D1_DC			0x00040000	// 51 CPU2 Dedicated RAM Select Distributed Compare
#define PBIST_RINFOU_CPU1_M0_M1_DC			0x00080000	// 52 CPU1 M0 M1 RAM Select Distributed Compare
#define PBIST_RINFOU_CPU2_M0_M1_DC			0x00100000	// 53 CPU2 M0 M1 RAM Select Distributed Compare
#define PBIST_RINFOU_PIE_MEM_0_1_DC			0x00200000	// 54 PIE RAM Select Distributed Compare
#define PBIST_RINFOU_PIE_MEM_2_3_DC			0x00400000	// 55 PIE RAM Select Distributed Compare
#define PBIST_RINFOU_USB_DC					0x00800000	// 56 USB Select Distributed Compare
#define PBIST_RINFOU_UPP_MEM_0_1_DC			0x01000000	// 57 uPP FIFO & Message RAM Select Distributed Compare
#define PBIST_RINFOU_UPP_MEM_2_5_DC			0x02000000	// 58 uPP FIFO & Message RAM Select Distributed Compare
#define PBIST_RINFOU_DCAN_MEM_0_2_DC		0x04000000	// 59 Select Distributed Compare
#define PBIST_RINFOU_DCAN_MEM_3_5_DC		0x08000000	// 60 Select Distributed Compare
#define PBIST_RINFOU_NONE 					0x00000000  // 00 RINFOU register not set


//*****************************************************************************
// The following are defines for the PBIST register offsets.
//*****************************************************************************
#define PBIST_ADDRESS_L0					0x00000110  // L0 Address
#define PBIST_RAMT							0x00000160	// RAM Configuration Register
#define PBIST_DLR							0x00000164	// Datalogger Register
#define PBIST_STR							0x0000016C	// Program Control Register
#define PBIST_PACT          				0x00000180	// PBIST Activate/ROM Clock Enable Register
#define PBIST_OVER							0x00000188	// Override Register
#define PBIST_FSRF0							0x00000190	// Fail Status Fail Register 0
#define PBIST_FSRF1							0x00000194	// Fail Status Fail Register 1
#define PBIST_FSRC0							0x00000198	// Fail Status Count Register 0
#define PBIST_FSRC1							0x0000019C	// Fail Status Count Register 1
#define PBIST_FSRA0 						0x000001A0	// Fail Status Address Register 0
#define PBIST_FSRA1 						0x000001A4	// Fail Status Address Register 1
#define PBIST_FSRDL0 						0x000001A8	// Fail Status Data Register 0
#define PBIST_FSRDL1						0x000001B0	// Fail Status Data Register 1
#define PBIST_ALGO		    				0x000001C4	// Algorithm Mask Register
#define PBIST_RINFOL						0x000001C8	// RAM Info Mask Lower Register
#define PBIST_RINFOU						0x000001CC	// RAM Info Mask Upper Register

//*****************************************************************************
// The following are defines for the bit fields in the PBIST_RAMT register.
//*****************************************************************************
#define PBIST_RAMT_RGS_M					0xFF000000	// RAM Group Select Mask
#define PBIST_RAMT_RGS_S					24
#define PBIST_RAMT_RDS_M					0x00FF0000	// Return Data Select Mask
#define PBIST_RAMT_RDS_S					16


//*****************************************************************************
// The following are defines for the bit fields in the PBIST_DLR register.
//*****************************************************************************
#define PBIST_DLR_ROM						0x00000004	// ROM-Based Testing Mode
#define PBIST_DLR_CPUAM						0x00000010	// CPU Access Mode
#define PBIST_DLR_GNG						0x00000200	// GO/NO-GO Testing Mode

//*****************************************************************************
// The following are defines for the bit fields in the PBIST_STR register.
//*****************************************************************************
#define PBIST_STR_RESUME					0x00000002	// Resume PBIST until complete
#define PBIST_STR_RESUME_S					1
#define PBIST_STR_STOP						0x00000004	// Stop PBIST
#define PBIST_STR_STOP_S					2

//*****************************************************************************
// The following are defines for the bit fields in the PBIST_PACT register.
//*****************************************************************************
#define PBIST_PACT_CLKEN					0x00000001	// PBIST controller Clock Enable

//*****************************************************************************
// The following are defines for the bit fields in the PBIST_OVER register.
//*****************************************************************************
#define PBIST_OVER_RINFO					0x00000001	// RINFO Override
#define PBIST_OVER_ALGO						0x00000008	// Algorithm Override

//*****************************************************************************
// The following are defines for the bit fields in the PBIST_FSRF0 register.
//*****************************************************************************
#define PBIST_FSRF0_FS0						0x00000001	// Fail Status Port 0

//*****************************************************************************
// The following are defines for the bit fields in the PBIST_FSRF1 register.
//*****************************************************************************
#define PBIST_FSRF1_FS1						0x00000001	// Fail Status Port 1

//*****************************************************************************
// The following are defines for the bit fields in the PBIST_FSRC0 register.
//*****************************************************************************
#define PBIST_FSRC0_C0						0x000000FF	// Fail Count Port 0
#define PBIST_FSRC0_C0_S					0

//*****************************************************************************
// The following are defines for the bit fields in the PBIST_FSRC1 register.
//*****************************************************************************
#define PBIST_FSRC1_C1						0x000000FF	// Fail Count Port 1
#define PBIST_FSRC1_C1_S					0

//*****************************************************************************
// The following are defines for the bit fields in the PBIST_FSRA0 register.
//*****************************************************************************
#define PBIST_FSRA0_FSA0					0x0000FFFF	// Fail Status Address Port 0
#define PBIST_FSRA0_FSA0_S					0

//*****************************************************************************
// The following are defines for the bit fields in the PBIST_FSRA1 register.
//*****************************************************************************
#define PBIST_FSRA1_FSA1					0x0000FFFF	// Fail Status Address Port 1
#define PBIST_FSRA1_FSA1_S					0

//*****************************************************************************
// The following are defines for the bit fields in the PBIST_FSRDL0 register.
//*****************************************************************************
#define PBIST_FSRDL0_FD0					0xFFFFFFFF	// Failure Data Port 0
#define PBIST_FSRDL0_FD0_S					0

//*****************************************************************************
// The following are defines for the bit fields in the PBIST_FSRDL1 register.
//*****************************************************************************
#define PBIST_FSRDL1_FD1					0xFFFFFFFF	// Failure Data Port 1
#define PBIST_FSRDL1_FD1_S					0


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F2837x_PBIST_DEFINES_H

//===========================================================================
// End of file.
//===========================================================================
