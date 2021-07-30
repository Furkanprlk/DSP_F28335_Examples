/*
//###########################################################################
//
// FILE:    F2806x_CLA_C_lnk.cmd
//
// TITLE:   Linker Command File for CLA Math library examples that run
//          on the 2806x platform
//
//          This file includes all RAM and FLASH blocks present on the
//          2806x and depending on the active build configuration(RAM or FLASH)
//          the appropriate sections will either be loaded into RAM or FLASH
//          blocks
//###########################################################################
// $TI Release: CLA Math Library for CLA C Compiler V4.00.01.00 $
// $Release Date: Apr 23, 2014 $
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
// The header linker files are found in <base>\F2806x_headers\cmd
//
// For BIOS applications add:      F2806x_Headers_BIOS.cmd
// For nonBIOS applications add:   F2806x_Headers_nonBIOS.cmd
========================================================= */

/* ======================================================
// For Code Composer Studio prior to V2.2
// --------------------------------------
// 1) Use one of the following -l statements to include the
// header linker command file in the project. The header linker
// file is required to link the peripheral structures to the proper
// locations within the memory map                                    */

/* Uncomment this line to include file only for non-BIOS applications */
/* -l F2806x_Headers_nonBIOS.cmd */

/* Uncomment this line to include file only for BIOS applications */
/* -l F2806x_Headers_BIOS.cmd */

/* 2) In your project add the path to <base>\F2806x_headers\cmd to the
   library search path under project->build options, linker tab,
   library search path (-i).
/*========================================================= */

/* Define the memory block start/length for the F2806x
   PAGE 0 will be used to organize program sections
   PAGE 1 will be used to organize data sections

   Notes:
         Memory blocks on F2806x are uniform (ie same
         physical memory) in both PAGE 0 and PAGE 1.
         That is the same memory region should not be
         defined for both PAGE 0 and PAGE 1.
         Doing so will result in corruption of program
         and/or data.

         Contiguous SARAM memory blocks can be combined
         if required to create a larger memory block.
*/


// The user must define CLA_C in the project linker settings if using the
// CLA C compiler
// Project Properties -> C2000 Linker -> Advanced Options -> Command File
// Preprocessing -> --define
--define=CLA_C=1
#if CLA_C
// Define a size for the CLA scratchpad area that will be used
// by the CLA compiler for local symbols and temps
// Also force references to the special symbols that mark the
// scratchpad are.
CLA_SCRATCHPAD_SIZE = 0x100;
--undef_sym=__cla_scratchpad_end
--undef_sym=__cla_scratchpad_start

// Since MVECTx requires an offset from the start of programming space, we declare
// a variable at the start of Cla1Prog
_Cla1Prog_Start = _Cla1ProgRunStart;
#endif //CLA_C


MEMORY
{
PAGE 0 :   /* Program Memory */
           /* Memory (RAM/FLASH/OTP) blocks can be moved to PAGE1 for data allocation */
   CLAPROGRAM  : origin = 0x009000, length = 0x001000	  /* on-chip RAM block L3 */
   RAMM0       : origin = 0x000050, length = 0x0003B0     /* on-chip RAM block M0 */
   RAML5L8     : origin = 0x00C000, length = 0x008000
   OTP         : origin = 0x3D7800, length = 0x000400     /* on-chip OTP */

   FLASHH      : origin = 0x3D8000, length = 0x004000     /* on-chip FLASH */
   FLASHG      : origin = 0x3DC000, length = 0x004000     /* on-chip FLASH */
   FLASHF      : origin = 0x3E0000, length = 0x004000     /* on-chip FLASH */
   FLASHE      : origin = 0x3E4000, length = 0x004000     /* on-chip FLASH */
   FLASHD      : origin = 0x3E8000, length = 0x004000     /* on-chip FLASH */
   FLASHC      : origin = 0x3EC000, length = 0x004000     /* on-chip FLASH */
   FLASHA      : origin = 0x3F4000, length = 0x003F80     /* on-chip FLASH */
   CSM_RSVD    : origin = 0x3F7F80, length = 0x000076     /* Part of FLASHA.  Program with all 0x0000 when CSM is in use. */
   BEGIN       : origin = 0x3F7FF6, length = 0x000002     /* Part of FLASHA.  Used for "boot to Flash" bootloader mode. */
   CSM_PWL_P0  : origin = 0x3F7FF8, length = 0x000008     /* Part of FLASHA.  CSM password locations in FLASHA */

   FPUTABLES   : origin = 0x3FD860, length = 0x0006A0	  /* FPU Tables in Boot ROM */
   IQTABLES    : origin = 0x3FDF00, length = 0x000B50     /* IQ Math Tables in Boot ROM */
   IQTABLES2   : origin = 0x3FEA50, length = 0x00008C     /* IQ Math Tables in Boot ROM */
   IQTABLES3   : origin = 0x3FEADC, length = 0x0000AA	  /* IQ Math Tables in Boot ROM */

   ROM         : origin = 0x3FF3B0, length = 0x000C10     /* Boot ROM */
   RESET       : origin = 0x3FFFC0, length = 0x000002     /* part of boot ROM  */
   VECTORS     : origin = 0x3FFFC2, length = 0x00003E     /* part of boot ROM  */

PAGE 1 :   /* Data Memory */
           /* Memory (RAM/FLASH/OTP) blocks can be moved to PAGE0 for program allocation */
           /* Registers remain on PAGE1                                                  */

   BOOT_RSVD   : origin = 0x000000, length = 0x000050     /* Part of M0, BOOT rom will use this for stack */
   RAMM1       : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */

   CLA1_MSGRAMLOW  : origin = 0x001480, length = 0x000080
   CLA1_MSGRAMHIGH : origin = 0x001500, length = 0x000080

   CLARAM0     : origin = 0x008800, length = 0x000400     /* on-chip RAM block L1 */
   CLARAM1     : origin = 0x008C00, length = 0x000400     /* on-chip RAM block L2 */
   CLARAM2     : origin = 0x008000, length = 0x000800     /* on-chip RAM block L0 */

   RAML4       : origin = 0x00A000, length = 0x002000     /* on-chip RAM block L4 */
   USB_RAM     : origin = 0x040000, length = 0x000800     /* USB RAM		  */
   FLASHB      : origin = 0x3F0000, length = 0x004000     /* on-chip FLASH */
}

/* Allocate sections to memory blocks.
   Note:
         codestart user defined section in DSP28_CodeStartBranch.asm used to redirect code
                   execution when booting to flash
         ramfuncs  user defined section to store functions that will be copied from Flash into RAM
*/


SECTIONS
{

   /* Allocate program areas: */
   codestart           : > BEGIN,      PAGE = 0
#if defined(RAM)
   .cinit              : > RAMM0,      PAGE = 0
   .pinit              : > RAMM0,      PAGE = 0
   .text               : > RAML5L8,    PAGE = 0
   ramfuncs            : > RAML5L8,    PAGE = 0
   .econst			   : > RAML5L8,    PAGE = 0
   .switch             : > RAMM0,      PAGE = 0
	IQmath             : > RAML5L8,    PAGE = 0            /* Math Code */
   Cla1Prog            : {_Cla1ProgRunStart = .;} > CLAPROGRAM,
                                       PAGE = 0
   CLA1mathTables	   : > CLARAM1,    PAGE = 1
#elif defined(_FLASH)
   .cinit              : > FLASHA,     PAGE = 0
   .pinit              : > FLASHA,     PAGE = 0
   .text               : > FLASHA,     PAGE = 0

   ramfuncs            : LOAD = FLASHD,
                         RUN = RAML5L8,
                         LOAD_START(_RamfuncsLoadStart),
                         RUN_START(_RamfuncsRunStart),
						 LOAD_SIZE(_RamfuncsLoadSize),
                         PAGE = 0
   /* Initalized sections to go in Flash */
   /* For SDFlash to program these, they must be allocated to page 0 */
   .econst             : > FLASHA,     PAGE = 0
   .switch             : > FLASHA,     PAGE = 0
   IQmath              : > FLASHA,     PAGE = 0            /* Math Code */

   Cla1Prog            : LOAD = FLASHD,
                         RUN = CLAPROGRAM,
                         LOAD_START(_Cla1ProgLoadStart),
                         LOAD_SIZE(_Cla1ProgLoadSize),
                         RUN_START(_Cla1ProgRunStart),
                         PAGE = 0

   CLA1mathTables	   : LOAD = FLASHB,
                         RUN = CLARAM1,
                         LOAD_START(_CLA1mathTablesLoadStart),
                         LOAD_SIZE(_CLA1mathTablesLoadSize),
                         RUN_START(_CLA1mathTablesRunStart),
                         PAGE = 1
#else
#error Add either "RAM" or "_FLASH" to C2000 Linker -> Advanced Options -> Command File Preprocessing -> --define
#endif //RAM

   csmpasswds          : > CSM_PWL_P0, PAGE = 0
   csm_rsvd            : > CSM_RSVD,   PAGE = 0

   /* Allocate uninitalized data sections: */
   .stack              : > RAML4,      PAGE = 1
   .ebss               : > RAML4,      PAGE = 1
   .esysmem            : > RAML4,      PAGE = 1

   /* Allocate IQ math areas: */
   IQmathTables        : > IQTABLES,   PAGE = 0, TYPE = NOLOAD

   /* Allocate FPU math areas: */
   FPUmathTables       : > FPUTABLES,  PAGE = 0, TYPE = NOLOAD

   Cla1ToCpuMsgRAM  : > CLA1_MSGRAMLOW,   PAGE = 1
   CpuToCla1MsgRAM  : > CLA1_MSGRAMHIGH,  PAGE = 1
   Cla1DataRam0		: > CLARAM0,		  PAGE = 1
   Cla1DataRam1		: > CLARAM1,		  PAGE = 1
   Cla1DataRam2		: > CLARAM2,		  PAGE = 1

   /* Allocate CLA 'C' Areas */
#ifdef CLA_C
   /* CLA C compiler sections */
   //
   // Must be allocated to memory the CLA has write access to
   //
   CLAscratch       :
                     { *.obj(CLAscratch)
                     . += CLA_SCRATCHPAD_SIZE;
                     *.obj(CLAscratch_end) } > CLARAM1,
					 PAGE = 1

   .bss_cla		    : > CLARAM2,       PAGE = 1
   .const_cla	    : > CLARAM2,       PAGE = 1
#endif //CLA_C


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

   /* .reset is a standard section used by the compiler.  It contains the */
   /* the address of the start of _c_int00 for C Code.   /*
   /* When using the boot ROM this section and the CPU vector */
   /* table is not needed.  Thus the default type is set here to  */
   /* DSECT  */
   .reset              : > RESET,      PAGE = 0, TYPE = DSECT
   vectors             : > VECTORS,    PAGE = 0, TYPE = DSECT

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/

