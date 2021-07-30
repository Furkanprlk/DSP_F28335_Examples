//#############################################################################
//
// FILE:    F2837x_CLA_C_lnk.cmd
//
// TITLE:   Linker Command File for CLA Math library examples that run 
//          on the 2837x platform
//
//          This file includes all RAM and FLASH blocks present on the
//          2837x and depending on the active build configuration(RAM or FLASH)
//          the appropriate sections will either be loaded into RAM or FLASH 
//          blocks
//
//#############################################################################
// $TI Release: CLA Math Library V4.01.00.00 $
// $Release Date: Apr 6, 2016 $
//#############################################################################
// NOTES:
// 1. In addition to this memory linker command file, add the header linker 
//    command file directly to the project. The header linker command file is 
//    required to link the peripheral structures to the proper locations within
//    the memory map.
//    
//    The header linker files are found in 
//    controlSUITE\device_support\f2837x\F2837x_headers\cmd
//    
//    For BIOS applications add:      F2837x_Headers_BIOS_cpuX.cmd
//    For nonBIOS applications add:   F2837x_Headers_nonBIOS_cpuX.cmd
//
// 2. On reset all RAMGSx blocks are under the mastership of CPU1. The user
//     must configure the appropriate control registers to transfer mastership
//     of a RAMGSx block over to CPU2
//
// 3. Memory blocks on F2837x are uniform (ie same physical memory) in both 
//    PAGE 0 and PAGE 1. That is the same memory region should not be defined 
//    for both PAGE 0 and PAGE 1. Doing so will result in corruption of program
//    and/or data.
//    
//    Contiguous SARAM memory blocks can be combined if required to create a 
//    larger memory block.
//
//#############################################################################

// The user may define CLA_C in the project linker settings if using the
// CLA C compiler,
//   Project Properties -> C2000 Linker -> Advanced Options -> Command File 
//   Preprocessing -> --define
// or here in the linker file as shown below. If writing CLA code in assembly
// only set the value to 0 (or comment it) as the user is not required to use 
// the compiler specific sections
--define=CLA_C=1

// Set this variable to 1 to use the CLA Math Tables in the CLA Data ROM
// If set to 0, make sure the right CLA Math library is used in the project
--define=CLA_MATH_TABLES_IN_ROM=0

MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */

   BEGIN           : origin = 0x000000, length = 0x000002
   
   RAMM0           : origin = 0x000002, length = 0x0003FE
   RAMM1           : origin = 0x000400, length = 0x000400
   
   RAMD0		   : origin = 0x00B000, length = 0x000800
   RAMD1		   : origin = 0x00B800, length = 0x000800
   
   RAMLS0_1        : origin = 0x008000, length = 0x001000
   
   RAMGS0_1		   : origin = 0x00C000, length = 0x002000
   
   RAMGS8		   : origin = 0x014000, length = 0x001000
   RAMGS9		   : origin = 0x015000, length = 0x001000
   RAMGS10		   : origin = 0x016000, length = 0x001000
   RAMGS11		   : origin = 0x017000, length = 0x001000
   
   RESET           : origin = 0x3FFFC0, length = 0x000002
   
   IQTABLES        : origin = 0x3FE000, length = 0x000B50     /* IQ Math Tables in Boot ROM */
   IQTABLES2       : origin = 0x3FEB50, length = 0x00008C     
   IQTABLES3       : origin = 0x3FEBDC, length = 0x0000AA	  
   
   FLASHN          : origin = 0x80000,  length = 0x002000
   FLASHM          : origin = 0x82000,  length = 0x002000
   FLASHL          : origin = 0x84000,  length = 0x002000
   FLASHK          : origin = 0x86000,  length = 0x002000
   FLASHJ          : origin = 0x88000,  length = 0x008000
   FLASHI          : origin = 0x90000,  length = 0x008000
   FLASHH          : origin = 0x98000,  length = 0x008000
   FLASHG          : origin = 0xA0000,  length = 0x008000
   FLASHF          : origin = 0xA8000,  length = 0x008000
   FLASHE          : origin = 0xB0000,  length = 0x008000
   FLASHD          : origin = 0xB8000,  length = 0x002000

PAGE 1 :
   BOOT_RSVD       : origin = 0x000002, length = 0x00004E     /* Part of M0, BOOT rom will use this for stack */
   
   CLA1_MSGRAMLOW  : origin = 0x001480, length = 0x000080
   CLA1_MSGRAMHIGH : origin = 0x001500, length = 0x000080
   
   RAMLS2_3        : origin = 0x009000, length = 0x001000
   RAMLS4_5        : origin = 0x00A000, length = 0x001000

   RAMGS2		   : origin = 0x00E000, length = 0x001000
   RAMGS3_4		   : origin = 0x00F000, length = 0x002000
   RAMGS5_6		   : origin = 0x011000, length = 0x002000
   RAMGS7		   : origin = 0x013000, length = 0x001000
   
   RAMGS12		   : origin = 0x018000, length = 0x001000
   RAMGS13		   : origin = 0x019000, length = 0x001000
   RAMGS14		   : origin = 0x01A000, length = 0x001000
   RAMGS15		   : origin = 0x01B000, length = 0x001000

   FLASHC          : origin = 0xBA000,  length = 0x002000
   FLASHB          : origin = 0xBC000,  length = 0x002000
   
}


SECTIONS
{
   codestart        : > BEGIN,                    PAGE = 0
#if defined(RAM)                                  
   ramfuncs         : > RAMM0,                    PAGE = 0
   .text            :>> RAMM1 | RAMD0 | RAMD1,    PAGE = 0
   .cinit           : > RAMGS0_1,                 PAGE = 0
                                                  
   .pinit           : > RAMGS0_1,                 PAGE = 0
   .switch          : > RAMGS0_1,                 PAGE = 0
   .econst          : > RAMGS3_4,                 PAGE = 1
#if !(CLA_MATH_TABLES_IN_ROM)
   CLA1mathTables   : > RAMLS4_5,                 PAGE = 1
#endif //CLA_MATH_TABLES_IN_ROM
   Cla1Prog         : > RAMLS0_1,                 PAGE = 0
#elif defined(_FLASH)
   ramfuncs         :  LOAD = FLASHD,
                       RUN = RAMGS0_1,
                       RUN_START(_RamfuncsRunStart),
                       LOAD_START(_RamfuncsLoadStart),
                       LOAD_SIZE(_RamfuncsLoadSize),
                       PAGE = 0

   .text            : > FLASHN,    PAGE = 0
   .cinit           : > FLASHM,    PAGE = 0

   .pinit           : > FLASHM,    PAGE = 0
   .switch          : > FLASHM,    PAGE = 0
   .econst          : > FLASHC,    PAGE = 1

#if  !(CLA_MATH_TABLES_IN_ROM)
   //Load tables to Flash and copy over to RAM
   /* CLA Math Tables in ROM*/
   CLA1mathTables   :  LOAD = FLASHB,
                       RUN = RAMLS4_5,
                       RUN_START(_CLA1mathTablesRunStart),
                       LOAD_START(_CLA1mathTablesLoadStart),
                       LOAD_SIZE(_CLA1mathTablesLoadSize),
                       PAGE = 1
#endif //CLA_MATH_TABLES_IN_ROM
                       
   Cla1Prog         :  LOAD = FLASHD,
                       RUN = RAMLS0_1,
                       RUN_START(_Cla1ProgRunStart),
                       LOAD_START(_Cla1ProgLoadStart),
                       LOAD_SIZE(_Cla1ProgLoadSize),
                       PAGE = 0
                      
#else
#error Add either "RAM" or "_FLASH" to C2000 Linker -> Advanced Options -> Command File Preprocessing -> --define
#endif //RAM

   Cla1ToCpuMsgRAM  : > CLA1_MSGRAMLOW,   PAGE = 1
   CpuToCla1MsgRAM  : > CLA1_MSGRAMHIGH,  PAGE = 1
   
#ifdef CLA_C
   /* CLA C compiler sections */
   //
   // Must be allocated to memory the CLA has write access to
   //
   .scratchpad      : > RAMLS4_5,       PAGE = 1
   .bss_cla		    : > RAMLS4_5,       PAGE = 1
   .const_cla	    : > RAMLS4_5,       PAGE = 1
#endif //CLA_C

   /* Test specific sections */
   IOBuffer         : > RAMLS2_3,         PAGE = 1
                                          
   .reset           : > RESET,            PAGE = 0, TYPE = DSECT /* not used, */
                                          
   .cio             : > RAMGS7,           PAGE = 1
   .sysmem          : > RAMGS7,           PAGE = 1
                                          
   .stack           : > RAMGS2,           PAGE = 1 /* Needs to be in lower 64K memory */
   .ebss            : > RAMGS5_6,         PAGE = 1
   .esysmem         : > RAMGS7,           PAGE = 1
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
