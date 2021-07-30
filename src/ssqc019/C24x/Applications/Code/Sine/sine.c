/*****************************************************************************/
/*                                                                           */
/* 	                      Sine.c                                             */
/*                                                                           */
/*****************************************************************************/

/*
  Generating sine and cosine outputs using tables.

  Uses 16 kHz output on T1PWM to produce a 500 Hz sine wave. 
                        T2PWM to produce a 500 Hz cosine wave.
  
*/


#include "system.h"
#include "eva.h"
#include "io2407.h"

unsigned int sine[32] = {460, 550, 637, 716, 786, 843, 886, 912, 
                         921, 912, 886, 843, 786, 716, 637, 550,
                         460, 371, 284, 205, 135, 78, 35, 9, 
                         0, 9, 35, 78, 135, 205, 284, 371 };

unsigned int cosine[32] = {921, 912, 886, 843, 786, 716, 637, 550,
                           460, 371, 284, 205, 135, 78, 35, 9,
                           0, 9, 35, 78, 135, 205, 284, 371, 
                           460, 550, 637, 716, 786, 843, 886, 912};
                           

/* Initialise General Purpose Timer 1. */

void init_GPT1(void)
{
 MCRA   |= T1PWM;   /* Turn on T1PWM */
 T1CON   = 0x8142;  /* Turn off GPT1 */
 GPTCONA |= 0x0042;
 T1PR    = 921;     /* Period = 921 + 1 decimal. 16 kHz */
 T1CMPR  = 460;     /* Duty = 50% */
 T1CNT   = 0xFFFE;  /* Set to -2 */
 T1CON   = 0x9142;  /* Start timer 1 */
}

/* Initialise General Purpose Timer 2 */

void init_GPT2(void)
{
 MCRA   |= T2PWM;   /* Turn on T2PWM */
 T2CON   = 0x8142;  /* Turn off GPT2 */
 GPTCONA |= 0x0088; /* Controlled from GPT1 */
 T2PR    = 921;     /* Period = 921 + 1 decimal. 16 kHz */
 T2CMPR  = 640;     /* Duty cycle 50% decimal */
 T2CNT   = 0xFFFE;  /* Set to -2 */
 T2CON   = 0x9142;  /* Start timer 2 */
}


unsigned int x;   /* General purpose variable */

void main(void)
{
  init_system();  /* Initialize variables and hardware */

  init_GPT1();    /* Turn on timer 1 */
  init_GPT2();    /* Turn on timer 2 */
  
 
 EVAIMRA |= T1PINT_FLAG; /* Enable Timer 1 interrupt flag */
 
 x = 0;
 
 for ( ; ; )
  {
   
   if ( EVAIFRA & T1PINT_FLAG)
    { 
      EVAIFRA = T1PINT_FLAG; /* Reset timer 1 interrupt flag */  
	  
	  T1CMPR = sine[x];  /* Set duty cycle to table value */
	  T2CMPR = cosine[x]; 
	  	  
	  if ( x < 31)
	    x++;
	  else
	    x = 0;
	}

  }

}

 /* End of sine1.c */
