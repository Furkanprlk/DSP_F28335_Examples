//###########################################################################
//
// FILE:   F2837x_Emif_defines.h
//
// TITLE:  #defines used in EMIF examples
//
//###########################################################################
// $TI Release: F2837x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: November 30, 2011 $
//###########################################################################

#ifndef F2837x_EMIF_DEFINES_H
#define F2837x_EMIF_DEFINES_H


#ifdef __cplusplus
extern "C" {
#endif

#define EMIF1LOCK_REG 0x5F480
#define EMIF1COMMIT_REG 0x5F482
#define EMIF1MSEL_REG 0x5F484
#define EMIF1ACCPROT_REG 0x5F488

//cpu1 to cpu2 message for handshaking
#define CPU1_CPU2_MSG       0x3fd00
//cpu2_to_cpu1 message ram for handshaking
#define CPU2_CPU1_MSG       0x3fb00


#define EMIF2LOCK_REG 0x5F4A0
#define EMIF2COMMIT_REG 0x5F4A2
#define EMIF2MSEL_REG 0x5F4A4
#define EMIF2ACCPROT_REG 0x5F4A8
#define EMIF2PROGE_REG 0x5F4A6
#define MSEL_EMIF1_CPU1 0x93A5CE71
#define MSEL_EMIF1_CPU2 0x93A5CE72
#define MSEL_DEF_3 0x93A5CE73
#define MSEL_DEF_0 0x93A5CE70
#define MSEL_DEF_1 0x93A5CE71
#define MSEL_DEF_2 0x93A5CE72

#define EMIF_SOFT_PRES_REG 0x5D084 //soft reset bit register
#define EMIF_DEV_DC_REG 0x5D014    //Device capability/EMIF customization register

// Read mask for the registers which has reserved bits. 
#define ASYNC_WCCR_RDMASK             0xF0FF00FF
#define SDRAM_CR_RDMASK                 0xE3FF7F7F
#define SDRAM_RCR_RDMASK               0x00071FFF
#define SDRAM_TR_RDMASK                 0xFF77FF70
#define SDR_EXT_TMNG_RDMASK         0x1F
#define INT_RAW_RDMASK                   0x3F
#define INT_MASK_RDMASK                  0x3F
#define IO_CTRL_RDMASK_RDMASK       0xFFFF
#define IO_STAT_RDMASK_RDMASK       0xF
#define NAND_FLASH_CTRL_RDMASK      0x3F3F
#define NAND_FLASH_STAT_RDMASK     0x30F0F
#define IODFT_TLECR_REG_RDMASK      0xFFFF
#define IODFT_TLGCR_REG_RDMASK      0x71FF
#define IODFT_TLAMR_REG_RDMASK     0x0FFFFFFF
#define IODFT_TLDCMR_REG_RDMASK    0x3fff3f07
#define  MODEL_REL_NUM_REG_RDMASK   0xFF
#define NAND_FLASH_4BIT_ECCLR_RDMASK   0x3F
#define  NAND_FLASH_4BIT_ECCx_RDMASK    0x03ff03ff
#define NAND_FLASH_ERR_ADDRx_RDMASK    0x03ff03ff
#define NAND_FLASH_ERR_VALx_RDMASK      0x03ff03ff

//Write Mask to stop writing to control critical bit 
//None


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F2837x_EMIF_DEFINES_H

//===========================================================================
// End of file.
//===========================================================================
