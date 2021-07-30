/*****************************************************************************/
/*                                                                           */
/* 	                      IIR.c                                              */
/*                                                                           */
/*****************************************************************************/
/*
  Using an Infinite Impulse Response (IIR) filter.
  1 kHz bandstop filter using 10 kHz sampling rate. 
  When reaching a new value, can oscillate positive and negative.
  Takes input on ADCIN2
  Produces output on T1PWM
*/

#include "system.h"
#include "eva.h"
#include "io2407.h"
#include "adc.h"

/* Initialise General Purpose Timer 1. */

void init_GPT1(void)
{
 MCRA   |= T1PWM;   /* Turn on T1PWM */
 T1CON   = 0x8142;  /* GPT1 off */
 GPTCONA |= 0x0141; /* Active low. PR starts ADC */
 T1PR    = 1475;    /* Sample at 10 kHz */
 T1CMPR  = 1475/2;  /* Duty = 50% */
 T1CNT   = 0xFFFE;  /* Set to -2 */
 T1CON   = 0x9142;  /* Start timer 1 */     
 
 EVAIFRA = 0xFFFF;  /* Clear any pending interrupts */
 EVAIMRA |= T1PINT_FLAG; /* Enable T1 period interrupt */
}


/************************************************************/
/*
  Initialise analog to digital converter.
*/
/************************************************************/

void init_ADC()
{
  /* Non Cascade for 8 measurements. */    
  /* Will affect RESULT0 to RESULT7 only */
  
  ADCCTRL1 = (ADC_SOFT|ADC_CPS|ADC_ACQ_PS3|ADC_ACQ_PS2|ADC_ACQ_PS1|ADC_ACQ_PS0);

  CHSELSEQ1 = 0x0210; /* Measurements on Channels 0,1,2 */
  CHSELSEQ2 = 0x0000;
  CHSELSEQ3 = 0xFFFF;
  CHSELSEQ4 = 0xFFFF;
  MAX_CONV  = 0x0007; /* 8 measurements */
                                     
  /* Reset sequence at zero and EVA start of conversion */                                   
                                     
  ADCCTRL2 = (RST_SEQ1 | EVA_SOC_SEQ1); 
} 

/***********************************************************/
/* 
  Read in sample from analog to digital converter.
  For test purposes, can connect potentiometer to ADCIN0 
  and use RESULT0 instead of RESULT2. 
*/
/***********************************************************/
   
volatile signed int read_ADC(void)
{
 signed int a;
 signed int b;
 
 /* Shift the value one place to the right to make space   */
 /* for the sign bit */
 
 a = (signed int)(RESULT1 >> 1);  /* Reference on ADCIN1 */
 b = (signed int)(RESULT2 >> 1);  /* Input signal from ADCIN2 */

#ifdef TESTMAX
 a = 0xFFC0/4;     /* Test purposes to test maximum */
 b = 0xFFC0/2;     /* To test, change to ifdef to ifndef */
#endif

#ifdef TESTMIN
 a = 0xFFC0/4;     /* Test purposes to test minimum */
 b = 0;            /* To test, change ifdef to ifndef */
#endif

 return((b) - (a));  /* Input - Reference */
}   

/***********************************************************/
/*
  IIR Fiter.
  1 kHz bandstop filter using 10 kHz sampling rate.
  Input: Newest sample.
  Returns: Output from filter in range -16368 to +16368.
*/
/***********************************************************/
   
signed int IIR_filter(signed int new_input)
{
 /* Following two variables declared as static to retain   */
 /* values between calls */
 
 static signed int x[3] = {0,0,0};
 static signed int y[3] = {0,0,0};
 signed long sum;
 
 #define N 2 

 #define A 30827 /* 0.9408 decimal */
 #define B 19093 /* 0.5827 decimal */
 #define C 28891 /* 0.8817 decimal */
 
 sum  = C * y[N-2];
 sum -= B * y[N-1]; 
 sum += A * x[N-2];
 sum -= B * x[N-1];
 sum += A * x[N];    
 
 y[N] = (signed int)(sum >> 16);              
               
 y[N-2] = y[N-1];   /* Shuffle values along one place */
 y[N-1] = y[N]; 

 x[N-2] = x[N-1];
 x[N-1] = x[N];
 x[N] = new_input; /* Read in new value */
 
 return(y[N]);     /* Return new value */
}

/***********************************************************/
/* 
  Convert IIR filter output to PWM
  Output from IIR is in range -16368 to +16368.
  Convert to range 0 to 1475.
*/
/***********************************************************/
      
unsigned int scale_IIR_output(signed int value)
{
 /* IIR filters can be unstable, therefore limit output */
 
 if ( value > 16368) /* Limit output swing */
    value = 16368;
 else if ( value < -16368) 
    value = -16368;
         
 value += 16368; /* Convert from signed to unsigned */
	  
 /* Scale ouput to be in range 0 to 1475 */
	  
 value = ((signed int)(((signed long) value * 2953) >> 16));

 return(value); /* Return unsigned value */
}      
      
/***********************************************************/

void main(void)
{
  signed int x; /* General purpose variable. Must be signed */
  signed int y; /* General purpose variable. */
  
  init_system();  /* Initialize variables and hardware */

  init_ADC();     /* Initialise ADC */       
  init_GPT1();    /* Turn on timer 1 */
  
 for ( ; ; )
  {
   
   if ( ADCCTRL2 & INT_FLAG_SEQ1) /* Test for ADC event */
    { 
      ADCCTRL2 |= INT_FLAG_SEQ1; /* Reset timer 1 interrupt flag */  
	  
	  x = 0;
	  
	  while (ADCCTRL2 & SEQ1_BSY) /* Wait for measurement to finish */
	    x++;
	  
	  x = read_ADC(); /* Read new input from ADC */
	  
	  y =  IIR_filter(x); /* Apply IIR filter */
	  
	  T1CMPR = scale_IIR_output(y); /* Output to PWM */
	}
  }

}

 /* End of IIR.c */
