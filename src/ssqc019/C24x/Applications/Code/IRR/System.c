/*****************************************************************************/
/*                                                                           */
/*    Functions for set-up of phase locked loop and to enable features       */
/*                                                                           */
/*****************************************************************************/
/* Derived from code supplied by Spectrum Digital */


#include "system.h"

/* Static function prototypes. Functions only used in this module */

static void set_system(void);
static void set_wait(void);
static void test_init(void);
static void set_pll(void);


/* Global Variable */

volatile unsigned int configdata;

/* Two functions used by main program */

void bad_trap(void)
{
  while(1);  /* a place to hang if illegal trap */
}


void init_system(void)
{
  set_wait();   /* set up wait states for I/O */

  set_system(); /* Turn on ADC, CAN bus and timers */

  set_pll();    /* Set up phase locked loop for m/c speed */
}

/******************************************************************************/
/*                                                                            */
/*                       Subroutines                                          */
/*                                                                            */
/******************************************************************************/

 
static void set_wait(void)
{
  configdata =	IOWSB1; 	 /* 2 waits for off chip I/O */
  OUTMAC( _WSGR, configdata);
}

/*  Subroutine used by set_pll() */

unsigned int wait_ms( volatile unsigned int delay_val )
{
	 unsigned int i;
	 unsigned int ms_ctr;


	 for ( i = 0; i < delay_val; i++ )
	 {
	ms_ctr = MS_TIME_LOOP;

	while ( ms_ctr )
	{
		 ms_ctr--;
	}
	 }

	 return( delay_val );
}

/* Setup phase locked loop to set operating speed of TMS320LF2407*/

void set_pll( void )
{
  unsigned int scsr1_val;

  scsr1_val = SCSR1;

  scsr1_val &= (~(PS2 | PS1 | PS0 ));

  scsr1_val |= (FREQIN4 & PS_MASK);

  SCSR1 = scsr1_val;

  wait_ms(200);
}


/* Turn on ADC, CAN bus, timers etc */

static void set_system(void)
{
  SCSR1|= (ADC_CLKEN | SCI_CLKEN | SPI_CLKEN | CAN_CLKEN | EVB_CLKEN | EVA_CLKEN);
}





/* End of system.c */
