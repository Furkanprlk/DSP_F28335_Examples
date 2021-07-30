/*****************************************************************************/
/*                                                                           */
/* 	                      stepper.c                                              */
/*                                                                           */
/*****************************************************************************/

/*
  Code to use potentiometer on ADCIN0 to control speed of 
  a stepper motor. Uses L293D motor driver IC on I/O Port E.
 
  Steper motor windings = I/O Port E bits 3 to 0. 
  Motor driver enable = I/O Port E bit 4. 
  
  Connect winding 1 of stepper motor to outputs driven by IOPE0 and IOPE1.
  Connect winding 2 of stepper motor to outputs driven by IOPE1 and IOPE3.
  
  Speed of motor is controlled by a potentiometer on ADC0.
  Center position is off. Amount of travel of potentiometer
  for which there is no output is determined by the deadband.
*/

#include "system.h"
#include "eva.h"
#include "io2407.h"
#include "adc.h"

/* Defines */

/* Percentage of potentiometer travel where ouput is off */
           
#define DEADBAND_PERCENT 10

/* Maximum input to ADC is FFC0h = 65472 decimal */  

#define DEADBAND_MAX ((65472*(50+DEADBAND_PERCENT/2))/100)
#define DEADBAND_MIN ((65472*(50-DEADBAND_PERCENT/2))/100)

/*
 The following variable will depend on the actual stepper
 motor used. This determines the fastest speed the timer 
 can run at. Increase 0xFFF for slower speed  
*/

#define MAXIMUM_SPEED 0x0FFF                            

/* Tables to turn on the stepper motor windings */

unsigned int single_step[4] = {0x01, 0x04, 0x02, 0x08}; 

unsigned int half_step[8] = {1,5,4,6,2,10,8,9};


/* Initialise General Purpose Timer 1. */

void init_GPT1(void)
{
 MCRA   |= T1PWM;   /* Turn on T1PWM */
 T1CON   = 0x8342;  /* Clock divided by 128 */
 GPTCONA |= 0x0141; /* Active low. PR starts ADC */
 T1PR    = 0xFFFF;  /* Slowest speed */
 T1CMPR  = MAXIMUM_SPEED/2;  /* Duty = 50% of fastest speed */
 T1CNT   = 0xFFFE;  /* Set to -2 */
 T1CON   = 0x9342;  /* Start timer 1 */     
}

/***********************************************************/

void init_ADC()
{
  /* Non Cascade for 8 measurements. */    
  /* Will affect RESULT0 to RESULT7 only */
  
  ADCCTRL1 = (ADC_SOFT|ADC_CPS|ADC_ACQ_PS3|ADC_ACQ_PS2|ADC_ACQ_PS1|ADC_ACQ_PS0);

  CHSELSEQ1 = 0x0000; /* 8 measurements on Channels 0 */
  CHSELSEQ2 = 0x0000;
  CHSELSEQ3 = 0xFFFF;
  CHSELSEQ4 = 0xFFFF;
  MAX_CONV  = 0x0007; /* 8 measurements */
                                     
  /* Reset sequence at zero and EVA start of conversion */                                   
                                     
  ADCCTRL2 = (RST_SEQ1 | EVA_SOC_SEQ1); 
} 

/***********************************************************/
/*
  Read ADCIN0. RESULT0 will lie in range 0 to FFC0h.
  Returned value will lie in range -100 to +100
  with deadband in centre of range.
*/
/***********************************************************/
   
volatile signed int read_ADC(void)
{
 unsigned int input;
 signed int output;
 
 input = RESULT0; /* Read input */
 
 if ( input >= DEADBAND_MIN && input <= DEADBAND_MAX)
   {
    /* Input lies in deadband. No output */
    output = 0;
   }
 else if ( input > DEADBAND_MAX)
  {                  
   output = (signed int)((input-DEADBAND_MAX) * 100)/(0xFFC0-DEADBAND_MAX);
  }
 else
  {
   /* Input is less than DEADBAND_MIN */
  
   output = -(signed int)((DEADBAND_MIN-input)*100)/(DEADBAND_MIN);
  } 
  
 return(output); /* Returned signed output */
                 /* in range -100 to +100 */
}   

/***********************************************************/
/*
  Generate Output.
  Input: -100 to +100.
  Output: Speed for T1PWM. Value between FFFFh (slowest)
          and MAXIMUM_SPEED (fastest). 
          Zero must not be used as stops T1PWM running.
*/
/***********************************************************/

unsigned int set_output_speed(signed int input)
{
 unsigned int return_value;
 signed long scaled_value;
 
 if ( 0 == input)
  { 
   return_value = 0xFFFF; /* Leave period at maximum */
  }
 else if ( input > 0)
  {
   /* Input value in range 1 to 100 */
   /* Convert to output in between 0xFFFF to MAXIMUM_SPEED */
   
   scaled_value = ((0xFFFF - MAXIMUM_SPEED) * (signed long)input)/100;
   return_value = 0xFFFF - (unsigned int) scaled_value; 
  }   
 else
  {
   /* Input value in range -1 to -100 */
   /* Convert to output between 0xFFFF and MAXIMUM_SPEED */
   
   scaled_value = ((0xFFFF - MAXIMUM_SPEED) * (signed long)(-input))/100;
   return_value = (65535 - (unsigned int) scaled_value);
  }
  
 return(return_value);  
}

/***********************************************************/
/*
   Determine which windings are to be powered on/off.     
   
   Full step uses the table single_step[].
   
   Take next value of windings to be turned on from table.
   
   1Fxx = Direction bits of I/O data and direction register. 
   xx10 = Data bits. L293 enabled.
*/
/***********************************************************/
      
unsigned int set_single_step_output(signed int input)
{
 unsigned int return_value;
 static unsigned int next = 0; /* Retains values between calls */

 if ( 0 == input)
  {
   return_value = 0x1F10; /* Enable on. All windings off */  
  }                       
 else if ( input > 0)
  {
   /* Positive input in range 1 to 100 */
   /* Move stepper motor forwards one single step */
   /* Point to next element of table */
   
   if ( next < 3 ) 
     next++;
   else
     next = 0;   

   /* Take value from table and set direction bits */
   /* Enable motor driver outputs */
   
   return_value = single_step[next] | 0x1F10;  
  } 
 else
  {
   /* Negative input in range -1 to -100 */
   /* Move stepper motor backwards one single step */
   
   if ( next > 0 )
     next--;   
   else
     next = 3;  
   
   /* Take next value from table and set direction bits */
   /* Enable motor drive outputs */
    
   return_value = single_step[next] | 0x1F10; 
  }
 
 return(return_value);
}
      

/***********************************************************/
/*
   Determine which windings are to be powered on/off.     
   
   Half step uses the table half_step[].
   
   Take next value of windings to be turned on from table.
   
   1Fxx = Direction bits of I/O data and direction register. 
   xx10 = Data bits. L293 enabled.
*/
/***********************************************************/
      
unsigned int set_half_step_output(signed int input)
{
 unsigned int return_value;
 static unsigned int next = 0; /* Retains values between calls */

 if ( 0 == input)
  {
   return_value = 0x1F10; /* Enable on. All windings off */  
  }                       
 else if ( input > 0)
  {
   /* Positive input in range 1 to 100 */
   /* Move stepper motor forwards one half step */
   /* Point to next element of table */
   
   if ( next < 7 ) 
     next++;
   else
     next = 0;   

   /* Take value from table and set direction bits */
   /* Enable motor driver outputs */
   
   return_value = half_step[next] | 0x1F10;  
  } 
 else
  {
   /* Negative input in range -1 to -100 */
   /* Move stepper motor backwards one half step */
   
   if ( next > 0 )
     next--;   
   else
     next = 7;  
   
   /* Take next value from table and set direction bits */
   /* Enable motor drive outputs */
    
   return_value = half_step[next] | 0x1F10; 
  }
 
 return(return_value);
}
      
/***********************************************************/      

void main(void)
{
  signed int x;   /* General purpose variable */
  unsigned int y; /* General purpose variable */
  
  init_system();  /* Initialize variables and hardware */

  init_ADC();     /* Initialise ADC */       
  init_GPT1();    /* Turn on timer 1 */
  
  MCRC = 0xFFE0;  /* Turn off clkout on IOPEO bit 0 */
  
 for ( ; ; )
  {
   
   if ( ADCCTRL2 & INT_FLAG_SEQ1) /* Test for ADC event */
    { 
      ADCCTRL2 |= INT_FLAG_SEQ1; /* Reset timer 1 interrupt flag */  
	  
	  x = 0;
	  
	  while (ADCCTRL2 & SEQ1_BSY) 
	    x++;                     /* Wait for measurement to finish */
	  
	  x = read_ADC(); /* Read analog input from ADC0 */	
 	                  /* Put into range -100 to +100 */
 	  
      y = set_output_speed(x); /* Calculate output */
      
      T1PR = y;      /* Set period of GPT1 */
      
      y =  set_half_step_output(x); /* Next element */
	
	  PEDATDIR = y;  /* Output on I/O Port E */
	}      

  }

}

/*****************************************************************************/
/*                                                                           */
/* 	                      End of stepper.c                                   */
/*                                                                           */
/*****************************************************************************/

