/*
//###########################################################################
//
// FILE:	Example_Flash28069_API.cmd
//
// TITLE:	Linker Command File For F28069 Device Flash API
//
//###########################################################################
// $TI Release: F2806x Flash API Release V1.00 $
// $Release Date: March 31, 2011 $
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
// For nonBIOS applications add:   F2806x_Headers_nonBIOS.cmd
========================================================= */


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


MEMORY
{
PAGE 0:    /* Program Memory */
           /* Memory (RAM/FLASH/OTP) blocks can be moved to PAGE1 for data allocation */

   PRAML0      : origin = 0x008000, length = 0x000800     /* on-chip RAM block L0 */
   OTP         : origin = 0x3D7800, length = 0x000400     /* on-chip OTP */
   FLASHD      : origin = 0x3E8000, length = 0x004000     /* on-chip FLASH */
   FLASHC      : origin = 0x3EC000, length = 0x004000     /* on-chip FLASH */
   FLASHA      : origin = 0x3F4000, length = 0x003F80     /* on-chip FLASH */
   CSM_RSVD    : origin = 0x3F7F80, length = 0x000076     /* Part of FLASHA.  Program with all 0x0000 when CSM is in use. */
   BEGIN       : origin = 0x3F7FF6, length = 0x000002     /* Part of FLASHA.  Used for "boot to Flash" bootloader mode. */
   CSM_PWL_PROG: origin = 0x3F7FF8, length = 0x000008     /* Part of FLASHA.  CSM password locations in FLASHA */
   
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
   RAMM0       : origin = 0x000050, length = 0x0003B0     /* on-chip RAM block M0 */
   RAMM1       : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */

   DRAML1      : origin = 0x008800, length = 0x000400     /* on-chip RAM block L1 */  

   RAML2       : origin = 0x008C00, length = 0x000400     /* on-chip RAM block L2 */
   RAML3       : origin = 0x009000, length = 0x001000	  /* on-chip RAM block L3 */
   RAML4       : origin = 0x00A000, length = 0x002000     /* on-chip RAM block L4 */
   RAML5       : origin = 0x00C000, length = 0x002000     /* on-chip RAM block L5 */
   RAML6       : origin = 0x00E000, length = 0x002000     /* on-chip RAM block L6 */
   RAML7       : origin = 0x010000, length = 0x002000     /* on-chip RAM block L7 */
   RAML8       : origin = 0x012000, length = 0x002000     /* on-chip RAM block L8 */   


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
   /* The Flash API functions can be grouped together as shown below.
      The defined symbols _Flash28_API_LoadStart, _Flash28_API_LoadEnd
      and _Flash28_API_RunStart are used to copy the API functions out
      of flash memory and into SARAM */

/******************************************************************/
/* For Piccolo we dont need to copy the API from Flash as it is */
/* present in BOOT ROM											  */
/******************************************************************/
   Flash28_API: // Applicable only when API is not in BootROM
   {
   		-lFlash2806x_API_V100.lib(.econst)
        -lFlash2806x_API_V100.lib(.text)
   }                   LOAD = FLASHD, 
                       RUN = PRAML0,  
                       LOAD_START(_Flash28_API_LoadStart),
                       LOAD_END(_Flash28_API_LoadEnd),
                       RUN_START(_Flash28_API_RunStart),
                       PAGE = 0

   .cinit              : > FLASHA       PAGE = 0
   .pinit              : > FLASHA,      PAGE = 0
   .text               : > FLASHA       PAGE = 0
   codestart           : > BEGIN        PAGE = 0
   ramfuncs            : LOAD = FLASHA, 
                         RUN = PRAML0, 
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_END(_RamfuncsLoadEnd),
                         RUN_START(_RamfuncsRunStart),
                         PAGE = 0

   csmpasswds          : > CSM_PWL_PROG PAGE = 0
   csm_rsvd            : > CSM_RSVD     PAGE = 0
   
   /* Allocate uninitalized data sections: */
   .stack              : > RAMM0        PAGE = 1
   .ebss               : > DRAML1       PAGE = 1
   .esysmem            : > DRAML1       PAGE = 1

   /* Initalized sections go in Flash */
   /* For SDFlash to program these, they must be allocated to page 0 */
   .econst             : > FLASHA       PAGE = 0
   .switch             : > FLASHA       PAGE = 0      

   /* Allocate IQ math areas: */
   IQmath              : > FLASHA       PAGE = 0            /* Math Code */
   IQmathTables        : > IQTABLES,    PAGE = 0, TYPE = NOLOAD 
   /* Allocate FPU math areas: */
   FPUmathTables       : > FPUTABLES,  PAGE = 0, TYPE = NOLOAD
 
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
   vectors             : > VECTORS     PAGE = 0, TYPE = DSECT
   
}

/*
//===========================================================================
// End of file.
//===========================================================================
*/

