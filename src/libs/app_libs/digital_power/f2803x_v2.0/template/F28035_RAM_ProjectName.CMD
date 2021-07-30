/*
// TI File $Revision: /main/1 $
// Checkin $Date: March 18, 2009   09:16:06 $
//###########################################################################
//
// FILE:    F28035_RAM_ProjectName.cmd
//
// TITLE:   Linker Command File For 28035 examples that run out of RAM
//
//          This ONLY includes all SARAM blocks on the 28035 device.
//          This does not include flash or OTP.
//
//          Keep in mind that L0,L1,L2, and L3 are protected by the code
//          security module.
//
//          What this means is in most cases you will want to move to
//          another memory map file which has more memory defined.
//
//###########################################################################
// $TI Release: 2803x C/C++ Header Files V1.21 $
// $Release Date: December 1, 2009 $
//###########################################################################
*/

/* ======================================================
// For Code Composer Studio V2.2 and later
// ---------------------------------------
// In addition to this memory linker command file,
// add the header linker command file directly to the project.
// The header linker command file is required to link the
// peripheral structures to the proper locations within
// the memory map.
//
// The header linker files are found in <base>\DSP2803x_headers\cmd
//
// For BIOS applications add:      DSP2803x_Headers_BIOS.cmd
// For nonBIOS applications add:   DSP2803x_Headers_nonBIOS.cmd
========================================================= */

/* ======================================================
// For Code Composer Studio prior to V2.2
// --------------------------------------
// 1) Use one of the following -l statements to include the
// header linker command file in the project. The header linker
// file is required to link the peripheral structures to the proper
// locations within the memory map                                    */

/* Uncomment this line to include file only for non-BIOS applications */
/* -l DSP2803x_Headers_nonBIOS.cmd */

/* Uncomment this line to include file only for BIOS applications */
/* -l DSP2803x_Headers_BIOS.cmd */

/* 2) In your project add the path to <base>\DSP2803x_headers\cmd to the
   library search path under project->build options, linker tab,
   library search path (-i).
/*========================================================= */

/* Define the memory block start/length for the DSP2803x
   PAGE 0 will be used to organize program sections
   PAGE 1 will be used to organize data sections

   Notes:
         Memory blocks on F28035 are uniform (ie same
         physical memory) in both PAGE 0 and PAGE 1.
         That is the same memory region should not be
         defined for both PAGE 0 and PAGE 1.
         Doing so will result in corruption of program
         and/or data.

         L0 block is mirrored - that is it
         can be accessed in high memory or low memory.
         For simplicity only one instance is used in this
         linker file.

         Contiguous SARAM memory blocks can be combined
         if required to create a larger memory block.
*/

MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */

   BEGIN                : origin = 0x000000, length = 0x000002
   RAMM1                : origin = 0x000480, length = 0x000380     /* on-chip RAM block M1 */
   RAML0L1              : origin = 0x008000, length = 0x000C00
   RAML3                : origin = 0x009000, length = 0x001000
   RESET                : origin = 0x3FFFC0, length = 0x000002
   IQTABLES             : origin = 0x3FE000, length = 0x000B50     /* IQ Math Tables in Boot ROM */
   IQTABLES2            : origin = 0x3FEB50, length = 0x00008C     /* IQ Math Tables in Boot ROM */
   IQTABLES3            : origin = 0x3FEBDC, length = 0x0000AA	 /* IQ Math Tables in Boot ROM */

   BOOTROM              : origin = 0x3FF27C, length = 0x000D44


PAGE 1 :

   BOOT_RSVD            : origin = 0x000002, length = 0x00004E     /* Part of M0, BOOT rom will use this for stack */
   RAMM0                : origin = 0x000050, length = 0x0003B0
   dataRAM              : origin = 0x008C00, length = 0x000400		/* RAML2 */
   CLA_CPU_MSGRAM      	: origin = 0x001480, length = 0x000080
   CPU_CLA_MSGRAM      	: origin = 0x001500, length = 0x000080
}


SECTIONS
{
   /* Setup for "boot to SARAM" mode:
      The codestart section (found in DSP28_CodeStartBranch.asm)
      re-directs execution to the start of user code.  */
   codestart        : > BEGIN,     PAGE = 0
   ramfuncs         : > RAMM1      PAGE = 0
   .text            : > RAML0L1,   PAGE = 0 /* default code section */  
   .cinit           : > RAMM1,     PAGE = 0 /* initialised variables */
   .pinit           : > RAMM1,     PAGE = 0 /* global constructor table */
   .switch          : > RAMM1,     PAGE = 0
   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */

   .stack           : > RAMM0,     	 PAGE = 1 align(2) /* stack: even word alignment */
   .ebss            : > dataRAM,     PAGE = 1
   .econst          : > dataRAM,     PAGE = 1
   .esysmem         : > dataRAM,     PAGE = 1
   
   IQmath           : > RAML0L1,   PAGE = 0
   IQmathTables     : > IQTABLES,  PAGE = 0, TYPE = NOLOAD

   Cla1Prog         : LOAD = RAML3, /* Note for running from RAM the load and RUN can be the same */
                      RUN = RAML3,
                      LOAD_START(_Cla1funcsLoadStart),
                      LOAD_END(_Cla1funcsLoadEnd),
                      RUN_START(_Cla1funcsRunStart),
                      PAGE = 0

   Cla1ToCpuMsgRAM  : > CLA_CPU_MSGRAM,   PAGE = 1
   CpuToCla1MsgRAM  : > CPU_CLA_MSGRAM,  PAGE = 1

  /* Uncomment the section below if calling the IQNexp() or IQexp()
      functions from the IQMath.lib library in order to utilize the
      relevant IQ Math table in Boot ROM (This saves space and Boot ROM
      is 1 wait-state). If this section is not uncommented, IQmathTables2
      will be loaded into other memory (SARAM, Flash, etc.) and will take
      up space, but 0 wait-state is possible.
   */
   /*
   IQmathTables2    : > IQTABLES2, PAGE = 0, TYPE = NOLOAD
   {

              IQmath.lib<IQNexpTable.obj> (IQmathTablesRam)

   }
   */
   /* Uncomment the section below if calling the IQNasin() or IQasin()
      functions from the IQMath.lib library in order to utilize the
      relevant IQ Math table in Boot ROM (This saves space and Boot ROM
      is 1 wait-state). If this section is not uncommented, IQmathTables2
      will be loaded into other memory (SARAM, Flash, etc.) and will take
      up space, but 0 wait-state is possible.
   */
   /*
   IQmathTables3    : > IQTABLES3, PAGE = 0, TYPE = NOLOAD
   {

              IQmath.lib<IQNasinTable.obj> (IQmathTablesRam)

   }
   */

}


SECTIONS
{
	/*************       DPLIB Sections C28x      ************************/
	/* ADCDRV_1ch section */
	ADCDRV_1ch_Section				: > dataRAM				PAGE = 1
	
	/* ADCDRV_4ch section */
	ADCDRV_4ch_Section				: > dataRAM				PAGE = 1

	/* CNTL_2P2Z section */
	CNTL_2P2Z_Section				: > dataRAM				PAGE = 1
	CNTL_2P2Z_InternalData			: > dataRAM				PAGE = 1
	CNTL_2P2Z_Coef					: > dataRAM				PAGE = 1
	
	/* CNTL_3P3Z section */
	CNTL_3P3Z_Section				: > dataRAM				PAGE = 1
	CNTL_3P3Z_InternalData			: > dataRAM				PAGE = 1
	CNTL_3P3Z_Coef					: > dataRAM				PAGE = 1
	
	
	/*DLOG_4CH section */
	DLOG_4CH_Section				: > dataRAM				PAGE = 1
	DLOG_BUFF						: > dataRAM				PAGE = 1
	
	/*MATH_EMAVG section */
	MATH_EMAVG_Section				: > dataRAM				PAGE = 1
	
	/*PFC_ICMD section*/
	PFC_ICMD_Section				: > dataRAM				PAGE = 1
	
	/*PFC_INVSQR section*/
	PFC_INVSQR_Section				: > dataRAM				PAGE = 1
	
	/* PWMDRV_1ch driver section */
	PWMDRV_1ch_Section				: > dataRAM				PAGE = 1
	
	/* PWMDRV_1chHiRes driver section */
	PWMDRV_1chHiRes_Section			: > dataRAM				PAGE = 1
	
	/* PWMDRV_PFC2PhiL driver section */
	PWMDRV_PFC2PhiL_Section			: > dataRAM				PAGE = 1
	
 	/* PWMDRV_PSFB driver section */
	PWMDRV_PSFB_Section				: > dataRAM				PAGE = 1
	
	/* PWMDRV_DualUpDwnCnt driver section */
	PWMDRV_DualUpDwnCnt_Section		: > dataRAM				PAGE = 1
	
	/* PWMDRV_ComplPairDB driver section */
	PWMDRV_ComplPairDB_Section		: > dataRAM				PAGE = 1
	
	/* ZeroNet_Section  */
	ZeroNet_Section					: > dataRAM				PAGE = 1
	
	/*************       DPLIB Sections CLA      ************************/
	/* ADCDRV_1ch_CLA section */	
	ADCDRV_1ch_CLA_Section    		: > CPU_CLA_MSGRAM 	PAGE = 1
	
	/* ADCDRV_4ch_CLA section */	
	ADCDRV_4ch_CLA_Section    		: > CPU_CLA_MSGRAM 	PAGE = 1
	
	/* CNTL_2P2Z_CLA controller sections */
	CNTL_2P2Z_CLA_Section     		: > CPU_CLA_MSGRAM 		PAGE = 1  
	CNTL_2P2Z_CLA_InternalData 	    : > CLA_CPU_MSGRAM  	PAGE = 1
	CNTL_2P2Z_CLA_Coef				: >	CPU_CLA_MSGRAM		PAGE = 1
	
	/* CNTL_3P3Z_CLA controller sections */
	CNTL_3P3Z_CLA_Section     		: > CPU_CLA_MSGRAM 		PAGE = 1  
	CNTL_3P3Z_CLA_InternalData 	    : > CLA_CPU_MSGRAM  	PAGE = 1
	CNTL_3P3Z_CLA_Coef				: >	CPU_CLA_MSGRAM		PAGE = 1
	
	/*MATH_EMAVG_CLA sections */
	MATH_EMAVG_CLA_Section			: > CPU_CLA_MSGRAM		PAGE = 1
	MATH_EMAVG_CLA_InternalData		: > CPU_CLA_MSGRAM		PAGE = 1

	/*PFC_ICMD_CLA sections*/
	PFC_ICMD_CLA_Section			: > CPU_CLA_MSGRAM		PAGE = 1
	PFC_ICMD_CLA_InternalData		: > CPU_CLA_MSGRAM		PAGE = 1
	
	/*PFC_INVSQR_CLA sections*/
	PFC_INVSQR_CLA_Section			: > CPU_CLA_MSGRAM		PAGE = 1
	PFC_INVSQR_CLA_InternalData		: > CPU_CLA_MSGRAM		PAGE = 1
	
	/* PWMDRV_1ch_CLA driver section */
	PWMDRV_1ch_CLA_Section    		: > CPU_CLA_MSGRAM 	PAGE = 1

	/* PWMDRV_1chHiRes_CLA driver section */
	PWMDRV_1chHiRes_CLA_Section		: > CPU_CLA_MSGRAM 	PAGE = 1
	
 	/* PWMDRV_PFC2PhiL driver section */
	PWMDRV_PFC2PhiL_CLA_Section		: > CPU_CLA_MSGRAM 	PAGE = 1
	
 	/* PWMDRV_PSFB_CLA driver section */
	PWMDRV_PSFB_CLA_Section	 		: > CPU_CLA_MSGRAM 	PAGE = 1

	/* PWMDRV_DualUpDwnCnt_CLA driver section */
	PWMDRV_DualUpDwnCnt_CLA_Section	 : > CPU_CLA_MSGRAM		PAGE = 1
	
	/* PWMDRV_ComplPairDB_CLA driver section */
	PWMDRV_ComplPairDB_CLA_Section	 : > CPU_CLA_MSGRAM		PAGE = 1
	
	/* ZeroNetCLA_Section  */
	ZeroNetCLA_Section				 : > CPU_CLA_MSGRAM 	PAGE = 1


}


/*
//===========================================================================
// End of file.
//===========================================================================
*/
