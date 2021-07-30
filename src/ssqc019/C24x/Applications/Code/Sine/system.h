/************************************************************/
/*                   
   system.h    
   Header file for hardware initialisation  
/*                                           
/************************************************************/

/* Derived from routines supplied by Spectrum Digital */

/* System configuration. Used to turn on ADC, timers etc */

#define SCSR1 *(volatile unsigned int*)	0x7018

#define ADC_CLKEN    0x0080
#define SCI_CLKEN    0x0040
#define SPI_CLKEN    0x0020
#define CAN_CLKEN    0x0010
#define EVB_CLKEN    0x0008
#define EVA_CLKEN    0x0004


/* Wait State Bits */

#define PSWSB0	0x0001
#define PSWSB1	0x0002
#define PSWSB2	0x0004
#define DSWSB0	0x0008
#define DSWSB1	0x0010
#define DSWSB2	0x0020
#define IOWSB0	0x0048
#define IOWSB1	0x0080
#define IOWSB2	0x0100

#define MS_TIME_LOOP   0x0680

#define   PS2	    0x0800
#define   PS1	    0x0400
#define   PS0	    0x0200
#define   PS_MASK   0x0E00

#define   FREQIN4	    ( ( 0 )                     )
#define   FREQIN2	    ( ( PS0)                    )
#define   FREQIN1_33	( ( PS1)                    )
#define   FREQIN1	    ( ( PS1) | ( PS0)           )
#define   FREQIN_8	    ( ( PS2)                    )
#define   FREQIN_66	    ( ( PS2) |          ( PS0)  )
#define   FREQIN_57	    ( ( PS2) | ( PS1)           )
#define   FREQIN_50	    ( ( PS2) | ( PS1) | ( PS0)  )

/*
  Macro Expansion Declarations
*/
#define _WSGR	   0FFFFh      /* wait state generator reg in I/O space */

#define STR(x) #x

#define OUTMAC(address,data)  \
 asm("        LDPK    _"STR(data));  \
 asm("        OUT     _"STR(data) "," STR(address))

#define INMAC(address,data)   \
 asm("        LDPK    _"STR(data));  \
 asm("        IN      _"STR(data) "," STR(address))

/* Function prototypes of functions available to main program */

void bad_trap(void);
void init_system(void);

/* End of system.h */
