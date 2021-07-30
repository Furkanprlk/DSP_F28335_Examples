/************************************************************/
/*                                                          */
/* 	                      FIR.c                             */
/*                                                          */
/************************************************************/
/*
  Finite Inpulse Response (FIR) Filters.
  Uses Analogue input on ADCIN2.
  Produces low-pass or high-pass filter on T1PWM (IOPB4).
  Produces comb filter on T2PWM (IOPB5).   
  
  The C code version of the lowpass filter takes 42 us to
  execute. The assembly language version requires 13 us.
*/
/***********************************************************/

#include "system.h"
#include "eva.h"
#include "io2407.h"
#include "adc.h"       

extern unsigned int highpass_filter(signed int newest_sample);

/* Assembly language version of lowpass filter */

extern unsigned int lowpass_asm(signed int newest_sample);

/***********************************************************/        
/*
        Setup the General Purpose Timers GPT1 and GPT2.
*/                                              
/***********************************************************/
        
void init_GPT1(void)
{
 MCRA   |= 0x1000;  /* Turn on T1PWM */
 T1CON   = 0x8142;  /* Timer off */
 GPTCONA |= 0x0141; /* Active low, PR starts ADC. OE */
 T1PR    =   1475;  /* 10 kHz on IOPB4 */
 T1CMPR  = 1475/2;  /* 50% mark-space */
 T1CNT   = 0xFFFE;  /* Set to -2 */
 T1CON   = 0x9142;  /* Start timer 1 */
}

/* Initialise General Purpose Timer 2 */

void init_GPT2(void)
{
 MCRA   |= T2PWM;   /* Turn on T2PWM */
 T2CON   = 0x8142;  /* Turn off GPT2 */
 GPTCONA |= 0x0088; /* Controlled from GPT1 */
 T2PR    = 1475;    /* 10 kHz output on IOPB5 */
 T2CMPR  = 1475/2;  /* Duty cycle 50% */
 T2CNT   = 0xFFFE;  /* Set to -2 */
 T2CON   = 0x9142;  /* Start timer 2 */
}

/***********************************************************/
/*                                                             
           Setup Analog to Digital Conversions.
*/                                                             
/***********************************************************/

void init_ADC()
{
  /* Non Cascade for 8 measurements. */    
  /* Will affect RESULT0 to RESULT2 only */
  
  ADCCTRL1 = (ADC_SOFT|ADC_CPS|ADC_ACQ_PS3|ADC_ACQ_PS2|ADC_ACQ_PS1|ADC_ACQ_PS0);

  CHSELSEQ1 = 0x0210; /* 8 measurements on Channels 0,1,2 */
  CHSELSEQ2 = 0x0000;
  CHSELSEQ3 = 0xFFFF;
  CHSELSEQ4 = 0xFFFF;
  MAX_CONV  = 0x0007; /* 8 measurements 0 */
                                     
  /* Reset sequence at zero and EVA to start conversion */                                   
                                     
  ADCCTRL2 = (RST_SEQ1 | EVA_SOC_SEQ1); 
  
} /* No semicolon here */

/***********************************************************/
/*
 Reads unsigned input signal on ADCIN2 and compares it with 
 the (center zero) reference on ADCIN1. Converts unsigned input
 to signed for calculations.
  
 For test purposes, can use RESULT0 as potentiometer input 
 instead of RESULT2.
 
 ADC inputs are in range 0 to FFC0h.
 
 Returns: Signed ADC input in range -3FF0h to +3FF0h. 
*/
/***********************************************************/

volatile signed int read_ADC(void)
{
 signed int a;
 signed int b;
 
 /* Shift to make room for sign bit */
 
 a = (signed int)(RESULT1 >> 1);  /* Reference on ADCIN1 */
 b = (signed int)(RESULT2 >> 1);  /* Input signal from ADCIN2 */

#ifdef TESTMAX
 a = 0xFFC0/4;        /* Test purposes to test maximum */
 b = 0xFFC0/2;        /* For test, change ifdef to ifndef */
#endif

 return(b - a);  /* Return signed input - signed reference */
}

/***********************************************************/
/* 
  Lowpass FIR filter using 11 coefficients.
  1 kHz low-pass filter using 10 kHz sampling speed.
  
  Input: Latest measurement from ADC.
  Output: Signed output from low-pass filter
*/
/***********************************************************/

#define N 11

/* Do not declare the following as unsigned! */

signed int array[N+1] = {0,0,0,0,0,0,0,0,0,0,0,0}; /* Extra dummy value */
signed int constants[N] = {0,1534,3306,4961,6134,6554,6134,4961,3306,1534,0}; 

/*
  Input: Newest sample in range -3FF0h to +3FF0h.
  Returns: Unsigned value in range 0 to 1475 for T1PWM.
*/

unsigned int lowpass_filter(signed int newest_sample)
{
 signed long sum;
 unsigned int i;    
 unsigned int return_value;

 sum = 0;
 for (i = N-1 ; i > 0 ; i--)
   {
    array[i] = array[i-1]; /* Shuffle along one place */
    sum += (array[i] * constants[i]);
   } 
	    
 array[0] = newest_sample;  /* Input new value */
 sum += (array[0] * constants[0] );
       
 sum += 628924032;  /* Convert to unsigned. Add MAXIMUM */
 sum += 0x8000;     /* Round up */
 
 /* High word of sum will contain required value */
 /* Scale to give output 0 to 1475 for T1PWM */
       
 return_value = (unsigned int)(((sum>>16)*0x13AC)>>16); 
 
 if ( return_value > 1475) /* Range limit output */
   return_value = 1475; 
 
 return(return_value);
}

/***********************************************************/
/* 
  Produce comb filter on T2PWM.
  Takes average of first element of array and last element.
  Relies on low-pass filter above to update elements of array. 
  Returns: Value in range 0 to 1475 for T2PWM.
*/
/***********************************************************/

unsigned int comb_filter(void)
{
 signed int x; 
 signed int return_value;  
                      
 /* 
    Take average of oldest and newest samples.
    Note that shift right by 1 is more code efficient
    than divide by 2. A division calls a library function
    rather than a simple shift.
 */   

 x = (array[0] + array[N-1]) >>1 ;  /* Take average */
       
 x += 0xFFC0/4; /* Convert to unsigned */

 /* Scale in range 0 to 1475 for T2PWM */
 
 return_value = ((signed int)(((signed long) x * 2953) >> 16));       
 
 if ( return_value > 1475)  /* Range limit output */
   return_value = 1475;
 
 return(return_value);
}   

/***********************************************************/
/*                                                         */
/* 		    Main routine begins here                       */
/*                                                         */
/***********************************************************/
/*
  Note: While processing is going on, IOPC0 is high.
        This can be used to ensure processing does not
        take more than 100 us to execute.

  Can use either highpass_filter(), lowpass_filter()
  or lowpass_asm(). 
*/

void main(void)
{
 signed int x;
 unsigned int y;
  
 init_system();  /* Initialize variables and hardware */
  
 init_GPT1();  /* Turn on General Purpose Timer 1 */ 
 init_GPT2();  /* Turn on General Purpose Timer 2 */
 init_ADC();   /* Initialise ADCs */
 
 MCRB &= 0xFFFE; /* Setup IOPC0 as an input / output port */
 
 for ( ; ; )
  {
    if ( ADCCTRL2 & INT_FLAG_SEQ1) /* Test for ADC event */
      { 
       PCDATDIR = 0x0101; /* IOPC0 high */
       
       ADCCTRL2 |= INT_FLAG_SEQ1;
       
       x = 0;
       while (ADCCTRL2 & SEQ1_BSY) x++;
        /* Here typical value of x = 22 */
       
       x = read_ADC(); /* Read in latest sample */

       /* T1CMPR = lowpass_filter(x); */
       
       T1CMPR = lowpass_asm(x); 
       
       /* T1CMPR = highpass_filter(x); */   
                 
       T2CMPR = comb_filter(); /* Comb filter on T2PWM */
         
       PCDATDIR = 0x0100; /* IOPC0 low */
	
      }  
  } 
}

/* End of FIR.c */
