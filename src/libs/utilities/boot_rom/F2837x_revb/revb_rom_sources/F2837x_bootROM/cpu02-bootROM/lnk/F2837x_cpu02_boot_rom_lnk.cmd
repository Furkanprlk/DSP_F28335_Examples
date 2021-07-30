/*
// TI File $Revision: /main/1 $
// Checkin $Date: August 13, 2012   11:53:39 $
//###########################################################################
//
// FILE:    F28M35x_C28_boot_rom_lnk.cmd
//
// TITLE:   boot rom linker command file
//
//
//###########################################################################
// $TI Release: F2837x Boot ROM V1.0 $
// $Release Date: October 2013 $
//###########################################################################
*/


MEMORY
{
PAGE 0 :
		 ROM_SIGNATURE			: origin = 0x3F8000, length = 0x000002, fill = 0xFFFF
		 SYSBIOS_ROM			: origin = 0x3F8002, length = 0x001E0E, fill = 0xFFFF
		 PLCTABLES				: origin = 0x3F9E10, length = 0x003A08, fill = 0xFFFF
		 PLCTABLES2				: origin = 0x3FD818, length = 0x000600, fill = 0xFFFF
         BOOT       			: origin = 0x3FDE18, length = 0x00211A, fill = 0xFFFF
         CRCTABLE_ROM			: origin = 0x3FFF32, length = 0x000008, fill = 0xFFFF
         BIST_SIGNATURE 		: origin = 0x3FFF3A, length = 0x000040
         VERSION    			: origin = 0x3FFF7A, length = 0x000002
         CHECKSUM   			: origin = 0x3FFF7C, length = 0x000042
         VECS       			: origin = 0x3FFFBE, length = 0x000042
		 SYSBIOS_FLASH			: origin = 0x082000, length = 0x002000

PAGE 1 :
         EBSS       			: origin = 0x002,    length = 0x00001E
         STACK      			: origin = 0x020,    length = 0x000060
         SYSBIOS_RAM			: origin = 0x780, 	 length = 0x000080
}

SECTIONS
{
		GROUP : load = PLCTABLES, 				PAGE = 0,	ALIGN(2)
		{
			 PLC_TABLE
			 PLC_PHYcosinTable
			 PLC_FSKGSNINT8TABLE
			 PLC_OFDMSTF
			 PLC_ODFMLTFBEG
			 PLC_FSKGSNINT50TABLE
			 PLC_PHYPN9TABLE
	         sunPhyTable
			 twiddleFactors
			 primeTxPreamble
			 primeRxPreamble
			 primePrefTable
		}
		 sunPhyTable1	 : load = PLCTABLES2,				PAGE = 0, 	ALIGN(2)

		 .crctable_forsecrom : load = CRCTABLE_ROM,			PAGE = 0
		 .test_signature1: load = ROM_SIGNATURE		PAGE = 0
         .InitBoot       : load = BOOT,     		PAGE = 0
         .text           : load = BOOT,     		PAGE = 0
         .CKSUMFUNCS	 : load = BOOT,				PAGE = 0,	ALIGN(2)
         .Isr            : load = BOOT,     		PAGE = 0
         .BootVecs       : load = VECS,     		PAGE = 0
         .CKSUMLOC  	 : load = CHECKSUM,  		PAGE = 0,	ALIGN(2)
         .Version        : load = VERSION,   		PAGE = 0
         .bist_signature : load = BIST_SIGNATURE	PAGE = 0
         .stack          : load = STACK,     		PAGE = 1
         .ebss           : load = EBSS,      		PAGE = 1



         SYSBIOSROM   	 : load = SYSBIOS_ROM,		PAGE = 0
         {
            -l rom.obj(.sysbios_rom)
         }

         SYSBIOSFLASH    : load = SYSBIOS_FLASH,	PAGE = 0
         {
            -l rom.obj(.sysbios_flash)
         }

         SYSBIOSRAM    : load = SYSBIOS_RAM,	PAGE = 1
         {
            -l rom.obj(.sysbios_ram)
         }

         SYSBIO_NOLOAD    : load = 0,	PAGE = 1, type = DSECT
         {
            -l rom.obj(.*)
         }

}


