/*****************************************************************************/
/*                                                                           */
/* 	                      template.c                                              */
/*                                                                           */
/*****************************************************************************/

/*
  Project template.
  Can be used as a starting point for a DSP application.
  Sets up General Purpose Timer 1 to generate events at 10 kHz. 
  Will produce 10 kHz output on T1PWM and T1PWM pins.
*/

#include "system.h"
#include "eva.h"
#include "io2407.h"
#include "adc.h"

/* Initialise General Purpose Timer 1. */

void init_GPT1(void)
{
 MCRA   |= T1PWM;   /* Turn on T1PWM */
 T1CON   = 0x8142;  /* Turn off GPT1 */
 GPTCONA |= 0x0141; /* Active low. PR starts ADC */
 T1PR    = 1475;    /* Sample at 10 kHz */
 T1CMPR  = 1475/2;  /* Duty = 50% */
 T1CNT   = 0xFFFE;  /* Set to -2 */
 T1CON   = 0x9142;  /* Start timer 1 */     
}

/* Initialise General Purpose Timer 2 */

void init_GPT2(void)
{
 MCRA   |= T2PWM;   /* Turn on T2PWM */
 T2CON   = 0x8142;  /* Turn off GPT2 */
 GPTCONA |= 0x0088; /* Controlled from GPT1 */
 T2PR    = 1475;    /* 10 kHz */
 T2CMPR  = 1475/2;  /* Duty cycle 50% decimal */
 T2CNT   = 0xFFFE;  /* Set to -2 */
 T2CON   = 0x9142;  /* Start timer 2 */
}

void init_ADC()
{
  /* Non Cascade for 8 measurements. */    
  /* Will affect RESULT0 to RESULT7 only */
  
  ADCCTRL1 = (ADC_SOFT|ADC_CPS|ADC_ACQ_PS3|ADC_ACQ_PS2|ADC_ACQ_PS1|ADC_ACQ_PS0);

  CHSELSEQ1 = 0x0210; /* 8 measurements on Channels 0,1,2 */
  CHSELSEQ2 = 0x0000;
  CHSELSEQ3 = 0xFFFF;
  CHSELSEQ4 = 0xFFFF;
  MAX_CONV  = 0x0007; /* 8 measurements */
                                     
  /* Reset sequence at zero and EVA to start conversion */                                   
                                     
  ADCCTRL2 = (RST_SEQ1 | EVA_SOC_SEQ1); 
} 

/***********************************************************/
/*
  Read ADC0.
  RESULT 0 will lie in range 0 to FFC0h.
  Shift right one place to make room for sign bit.
  Returned value will be in range 0 to 7FE0h.
*/
   
volatile signed int read_ADC(void)
{
 return(RESULT0 >> 1); /* Make room for sign bit */
}   

/***********************************************************/



void main(void)
{
  signed int x;   /* General purpose variable. */

  init_system();  /* Initialize variables and hardware */

  init_ADC();     /* Initialise ADC */       
  init_GPT1();    /* Turn on timer 1 */
  init_GPT2();    /* Turn on timer 2 */
 
  
 for ( ; ; )
  {
   
   if ( ADCCTRL2 & INT_FLAG_SEQ1) /* Test for ADC event */
    { 
      ADCCTRL2 |= INT_FLAG_SEQ1; /* Reset timer 1 interrupt flag */  
	  
	  x = 0;
	  
	  while (ADCCTRL2 & SEQ1_BSY) 
	    x++;                     /* Wait for measurement to finish */
	  
	  x = read_ADC(); /* Read analog input from ADC0 */	
 	
      /* Processing goes here */
      
	  x >>= 5;  /* Make T1CMPR in range 0 to 3FFh */  
	
	  T1CMPR = x; /* ADC0 controls mark to space ratio */
	}
  }

}

 /* End of template.c */
