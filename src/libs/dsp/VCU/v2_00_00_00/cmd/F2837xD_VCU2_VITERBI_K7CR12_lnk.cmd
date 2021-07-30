//#############################################################################
//
// FILE:    F2837x_VCU2_VITERBI_K7CR12_lnk.cmd
//
// TITLE:   Linker Command File for VCU-II library examples that run 
//          on the 2837x platform
//
//          This file includes all RAM and FLASH blocks present on the
//          2837x and depending on the active build configuration(RAM or FLASH)
//          the appropriate sections will either be loaded into RAM or FLASH 
//          blocks
//
//#############################################################################
// $TI Release: C28x VCU Library Version v2.00.00.00 $
// $Release Date: Dec 6, 2013 $
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

   
MEMORY
{
PAGE 0 :
   /* BEGIN is used for the "boot to SARAM" bootloader mode   */

   BEGIN           : origin = 0x000000, length = 0x000002
   
   RAMM0           : origin = 0x000002, length = 0x0003FE
   RAMM1           : origin = 0x000400, length = 0x000400
   
   RAMD0		   : origin = 0x00B000, length = 0x000800
   RAMD1		   : origin = 0x00B800, length = 0x000800
   
   RAMLS0          : origin = 0x008000, length = 0x000800
   RAMLS1          : origin = 0x008800, length = 0x000800
   RAMLS2          : origin = 0x009000, length = 0x000800
   
   RAMGS0		   : origin = 0x00C000, length = 0x001000
   RAMGS1		   : origin = 0x00D000, length = 0x001000
   RAMGS2		   : origin = 0x00E000, length = 0x001000
   RAMGS3		   : origin = 0x00F000, length = 0x001000
   
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
   FLASHC          : origin = 0xBA000,  length = 0x002000

PAGE 1 :
   BOOT_RSVD       : origin = 0x000002, length = 0x00004E     /* Part of M0, BOOT rom will use this for stack */

   RAMLS3          : origin = 0x009800, length = 0x000800
   RAMLS4          : origin = 0x00A000, length = 0x000800
   RAMLS5          : origin = 0x00A800, length = 0x000800
   
   RAMGS4		   : origin = 0x010000, length = 0x001000
   RAMGS5		   : origin = 0x011000, length = 0x001000
   RAMGS6		   : origin = 0x012000, length = 0x001000
   RAMGS7		   : origin = 0x013000, length = 0x001000
   
   RAMGS12		   : origin = 0x018000, length = 0x001000
   RAMGS13		   : origin = 0x019000, length = 0x001000
   RAMGS14		   : origin = 0x01A000, length = 0x001000
   RAMGS15		   : origin = 0x01B000, length = 0x001000

   FLASHB          : origin = 0xBC000,  length = 0x002000
}


SECTIONS
{
   codestart        : > BEGIN,     PAGE = 0
#if defined(RAM)
   ramfuncs         : > RAMM0,     PAGE = 0
   .text            :>> RAMM1 | RAMD0 | RAMD1 | RAMLS0,  PAGE = 0
   .cinit           : > RAMLS1,    PAGE = 0
   
   .pinit           : > RAMLS1,    PAGE = 0
   .switch          : > RAMLS1,    PAGE = 0
   .econst          : > RAMLS4,    PAGE = 1
#elif defined(FLASH)
   ramfuncs         :  LOAD = FLASHC,
                       RUN = RAMLS1,
                       RUN_START(_RamfuncsRunStart),
                       LOAD_START(_RamfuncsLoadStart),
                       LOAD_SIZE(_RamfuncsLoadSize),
                       PAGE = 0

   .text            : > FLASHN,    PAGE = 0
   .cinit           : > FLASHM,    PAGE = 0

   .pinit           : > FLASHM,    PAGE = 0
   .switch          : > FLASHM,    PAGE = 0
   .econst          : > FLASHB,    PAGE = 1
#else
#error Add either "RAM" or "FLASH" to C2000 Linker -> Advanced Options -> Command File Preprocessing -> --define
#endif //RAM

   /* Test specific sections */
   testInput		: > RAMGS4, PAGE = 1
   decodedBits		: > RAMGS5, PAGE = 1
   receivedBits     : > RAMGS6, PAGE = 1
   transitionBits   : > RAMGS7, PAGE = 1

   .reset           : > RESET,     PAGE = 0, TYPE = DSECT /* not used, */

   .cio             : > RAMLS3,    PAGE = 1
   .sysmem          : > RAMLS3,    PAGE = 1

   .stack           : > RAMLS3,    PAGE = 1
   .ebss            : > RAMLS3,    PAGE = 1
   .esysmem         : > RAMLS4,    PAGE = 1
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
