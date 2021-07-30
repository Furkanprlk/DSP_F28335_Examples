/*
 *   Spectrum Digital Test code
 *   Copyright (c) 1997.
 *   Spectrum Digital, Inc
 *   ALL RIGHTS RESERVED
*/

/*
 * The memory mapping in this file should match the mapping in the
 * EMUINIT.CMD file in the load directory
 */

/* Change template.out and template.map to name of project */

                               /* linker commands */
-c			       /* ROM autoinitialization */
-x                             /* force rereading libraries */
-o dcmotor.out 	       /* output file */
-m dcmotor.map 	       /* map file */

 
                                       /* specify memory map */
MEMORY
{
  PAGE 0 :                                         /* program memory */
          VECS: origin = 00000h, length = 0003Fh 
          CODE: origin = 00040h, length = 00DC0h
  PAGE 1 :                                         /* data memory */
          Ext_Ram : origin = 08000h, length = 01000h
}

                                       /* specify sections */
SECTIONS
{
  vectors    :	  > VECS PAGE = 0
  .text      :    > CODE PAGE = 0
  .switch    :    > CODE PAGE = 0
  .data      :    > Ext_Ram PAGE = 1
  .bss       :    > Ext_Ram PAGE = 1
  .heap      :    > Ext_Ram PAGE = 1
  .stack     :    > Ext_Ram PAGE = 1
}

