/**********************************************************************
* File: rfft_adc_rt.cmd 
* Devices: TMS320F28335
* Author: Technical Training Organization (TTO), Texas Instruments
* History:
*   07/15/08 - original
**********************************************************************/

MEMORY
{
PAGE 0:         /* Program Memory */
   BEGIN_M0        : origin = 0x000000, length = 0x000002     /* Part of M0SARAM.  Used for "Boot to M0" bootloader mode. */
   L0123SARAM      : origin = 0x008000, length = 0x004000     /* SARAM, L0 through L3 combined.  CSM secure */
   ADC_CAL    	   : origin = 0x380080, length = 0x000009
   RESET           : origin = 0x3FFFC0, length = 0x000002     /* Part of Boot ROM */
   IQTABLES   	   : origin = 0x3FE000, length = 0x000b50

 PAGE 1:        /* Data Memory */
   M0SARAM         : origin = 0x000002, length = 0x0003FE     /* 1Kw M0 SARAM */
   M1SARAM         : origin = 0x000400, length = 0x000400     /* 1Kw M1 SARAM */
   L4SARAM         : origin = 0x00C000, length = 0x001000     /* 4Kw L4 SARAM, DMA accessible */
   L5SARAM         : origin = 0x00D000, length = 0x001000     /* 4Kw L5 SARAM, DMA accessible */
   L6SARAM         : origin = 0x00E000, length = 0x001000     /* 4Kw L6 SARAM, DMA accessible, 1 WS prog access */
   L7SARAM         : origin = 0x00F000, length = 0x001000     /* 4Kw L7 SARAM, DMA accessible 1 WS prog access */
}

 
SECTIONS
{
/*** Compiler Required Sections ***/

  /* Program memory (PAGE 0) sections */
   .text             : > L0123SARAM,            PAGE = 0
   .cinit            : > L0123SARAM,            PAGE = 0
   .const            : > L0123SARAM,            PAGE = 0
   .econst           : > L0123SARAM,            PAGE = 0      
   .pinit            : > L0123SARAM,            PAGE = 0
   .reset            : > RESET,                 PAGE = 0, TYPE = DSECT  /* Not using the .reset section */
   .switch           : > L0123SARAM,            PAGE = 0

  /* Data Memory (PAGE 1) sections */
   .bss              : > L4SARAM,               PAGE = 1
   .ebss             : > L4SARAM,               PAGE = 1
   .cio              : > M0SARAM,               PAGE = 1
   .stack            : > M1SARAM,               PAGE = 1
   .sysmem           : > L4SARAM,               PAGE = 1
   .esysmem          : > L4SARAM,               PAGE = 1
   
   
   IQmath            : > L0123SARAM,     		PAGE = 0
   IQmathTables      : > IQTABLES,  			PAGE = 0, TYPE = NOLOAD 

/*** User Defined Sections ***/
   codestart         : > BEGIN_M0,              PAGE = 0                /* Used by file CodeStartBranch.asm */
   ramfuncs     	 : > L0123SARAM,          PAGE = 0    
    /* Allocate ADC_cal function (pre-programmed by factory into TI reserved memory) */
   .adc_cal     : load = ADC_CAL,   PAGE = 0, TYPE = NOLOAD

}

/******************* end of file ************************/
