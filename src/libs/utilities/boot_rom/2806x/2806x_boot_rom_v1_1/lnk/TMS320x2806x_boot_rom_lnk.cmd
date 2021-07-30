/*
// TI File $Revision: /main/2 $
// Checkin $Date: October 15, 2010   14:58:09 $
//###########################################################################
//
// FILE:    TMS320x2806x_boot_rom_lnk.cmd
//
// TITLE:   boot rom linker command file
//
//
//###########################################################################
// $TI Release: TMS320x2806x Boot ROM V1.0 $
// $Release Date: January 22, 2009 $
//###########################################################################
*/


MEMORY
{
PAGE 0 :
	 RESERVED		: origin = 0x3F8000, length = 0x004460, fill = 0xFFFF
	 RESERVED_INTERNAL	: origin = 0x3FC460, length = 0x001400
	 FPUTABLES  	: origin = 0x3FD860, length = 0x0006A0
         IQTABLES   	: origin = 0x3FDF00, length = 0x000b50
         IQTABLES2  	: origin = 0x3FEA50, length = 0x00008C
         IQTABLES3  	: origin = 0x3FEADC, length = 0x0000AA
         IQMATH     	: origin = 0x3FEB86, length = 0x00082A
         BOOT       	: origin = 0x3FF3B0, length = 0x000422, fill = 0xFFFF
 	 FLASH_API  	: origin = 0x3FF7D2, length = 0x0006E7, fill = 0xFFFF
 	 ROM_APITABLE 	: origin = 0x3FFEB9, length = 0x000100, fill = 0xFFFF
         FLASH_CHK  	: origin = 0x3FFFB9, length = 0x000001
         VERSION    	: origin = 0x3FFFBA, length = 0x000002
         CHECKSUM   	: origin = 0x3FFFBC, length = 0x000004
         VECS       	: origin = 0x3FFFC0, length = 0x000040  

PAGE 1 :
         EBSS       	: origin = 0x002,    length = 0x000002
         STACK      	: origin = 0x004,    length = 0x000200
}

SECTIONS
{
         FPUmathTables	 : load = FPUTABLES, 	PAGE = 0
         IQmathTables    : load = IQTABLES,  	PAGE = 0
         IQmathTables2   : load = IQTABLES2, 	PAGE = 0
         {
            IQNexpTable.obj (IQmathTablesRam)
         }
	 IQmathTables3   : load = IQTABLES3, 	PAGE = 0
	 {
		    IQNasinTable.obj (IQmathTablesRam)       
         }
	 IQmath          : load = IQMATH,    	PAGE = 0
	 FlashAPI        : load = FLASH_API  	PAGE = 0
	 {
	    -lFlash2806x_API_V100.lib(.text)
	    -lFlash2806x_API_V100.lib(.econst)
	 }
	 .romApiTable	 : load = ROM_APITABLE, PAGE = 0
         .InitBoot       : load = BOOT,      	PAGE = 0
         .text           : load = BOOT,      	PAGE = 0
         .Isr            : load = BOOT,      	PAGE = 0
         .Flash          : load = FLASH_CHK  	PAGE = 0
         .BootVecs       : load = VECS,      	PAGE = 0
         .Checksum       : load = CHECKSUM,  	PAGE = 0
         .Version        : load = VERSION,   	PAGE = 0
         .stack          : load = STACK,     	PAGE = 1
         .ebss           : load = EBSS,      	PAGE = 1

}


