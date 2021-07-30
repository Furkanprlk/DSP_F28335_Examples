//###########################################################################
//
// FILE:    TMS320x2805x_cla_data_rom_lnk.cmd
//
// TITLE:   CLA data rom linker command file
//
//###########################################################################
// $TI Release:  $ 
// $Release Date:  $ 
//###########################################################################

MEMORY
{
PAGE 1 :
   CLA1_DATAROM_RESERVED	: origin = 0x01001000, length = 0x000070, fill = 0xFFFF
   CLA1_FFT_TABLES			: origin = 0x01001070, length = 0x000800, fill = 0xFFFF
   CLA1_DATAROM         	: origin = 0x01001870, length = 0x00078a, fill = 0xFFFF
   CROM_VERSION    			: origin = 0x01001FFA, length = 0x000006, fill = 0xFFFF
   
/*   CLA1_DATAROM         : origin = 0x01001000, length = 0x001000*/
}


SECTIONS
{
	.CLA1fftTables		: load = CLA1_FFT_TABLES, PAGE = 1, ALIGN(2)
	CLA1mathTables	: load = CLA1_DATAROM,	  	PAGE = 1
	.CROMVersion        : load = CROM_VERSION,   	PAGE = 1

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
