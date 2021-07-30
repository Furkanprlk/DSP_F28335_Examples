/**************************************************************/
/*                                                            */
/* 	                      fft.c                               */
/*                                                            */
/**************************************************************/

/*
  Fast Fourier Transform (FFT).
  Using 8 points, takes about 1.2 ms to execute one FFT.
  Sets up General Purpose Timer 1 to generate events at 10 kHz. 
  Will produce 10 kHz output on T1PWM and T1PWM pins.
*/

#include "system.h"
#include "eva.h"
#include "io2407.h"
#include "adc.h"  
#include "interrup.h"

#include "fftcmplx.h"  /* Complex structure definition*/

extern void FFT(COMPLEX *Y, int N); /* FFT Function */

/* The following define gives the number of samples. */
/* It should divide exactly into 512 */
/* Should N be increased, to say to 32, then the execution */
/* time of the FFT would increase */

#define N 8

unsigned int perform_fft = 0; /* Flag driven by interrupt */

/*************************************************************/
/*
   Initialise General Purpose Timers GPT1 and GPT2
*/
/*************************************************************/

/* Initialise General Purpose Timer 1. */

void init_GPT1(void)
{
 MCRA   |= T1PWM;   /* Turn on T1PWM */
 T1CON   = 0x8142;  /* Turn off GPT1 */
 GPTCONA = 0x0041;  /* Active low. */
 T1PR    = 1475;    /* Sample at 10 kHz */
 T1CMPR  = 0;       /* Duty = 0% */
 T1CNT   = 0xFFFE;  /* Set to -2 */
 T1CON   = 0x9142;  /* Start timer 1 */     
 
 EVAIFRA = 0xFFFF;  /* Clear any pending interrupts */
 EVAIMRA |= T1PINT_FLAG; /* Enable T1 period interrupt */
}

/* Initialise General Purpose Timer 2 */

void init_GPT2(void)
{
 MCRA   |= T2PWM;   /* Turn on T2PWM */
 T2CON   = 0x8142;  /* Turn off GPT2 */
 GPTCONA |= 0x0008; /* Controlled from GPT1 */
 T2PR    = 1475;    /* Sample at 10 kHz */
 T2CMPR  = 0;       /* Duty cycle 0% decimal */
 T2CNT   = 0xFFFE;  /* Set to -2 */
 T2CON   = 0x9142;  /* Start timer 2 */
}

/**************************************************************/

void init_ADC()
{
  /* Non Cascade for 8 measurements. */    
  /* Will affect RESULT0 to RESULT7 only */
  
  ADCCTRL1 = (ADC_SOFT | ADC_CPS /*| ADC_ACQ_PS3 | ADC_ACQ_PS2*/ );

  CHSELSEQ1 = 0x3210; /* 8 measurements 0 */
  CHSELSEQ2 = 0x0000;
  CHSELSEQ3 = 0xFFFF;
  CHSELSEQ4 = 0xFFFF;
  MAX_CONV  = 0x0007; /* 8 measurements, not 0 */
                                     
  /* Reset sequence at zero and software start of conversion */                                   
                                     
  ADCCTRL2 = ( RST_SEQ1 | SOC_SEQ1); 
  
} /* No semicolon here */

/***********************************************************/

int input_buffer[N] = {8191, 8191, 8191, 8191, 0, 0, 0, 0};

COMPLEX y[N]; /* Variable passed to FFT and modified */   

/***********************************************************/
/*
  Shuffle input buffer along one place.
  Put latest input from ADC into first buffer location.
  Input from ADCIN2 lies in range 0 to FFC0h (65472 decimal).
  Divide by 8 to limit range from 0 to 8184.
*/
/***********************************************************/

void shuffle_and_read(void)
{
 signed int i;
 
 for ( i = N-1 ; i > 0 ; i--)
  {
   input_buffer[i] = input_buffer[i-1];
  }

 input_buffer[0] = (RESULT2 >> 3);
}       

/***********************************************************/
/*
  Copy from input buffer to complex structure.
  When FFT is performed, the complex structure is overwritten
  by the return values.
*/
/***********************************************************/

void copy_input_to_complex(void)
{
 unsigned int i;
 
 for ( i = 0 ; i < N; i++)
  {
   (y[i]).real = input_buffer[i];
   (y[i]).imag = 0;
  }
}

/***********************************************************/
/* 
   Main program 
   Uses timers to read analog input on ADCIN2 into a buffer
   and then perform an 8-point FFT on it.
*/
/**********************************************************/

void main(void)
{
  signed int output1, output2;
  signed int x;   /* General purpose variable. */
  signed int i;   /* Counter */   
  signed long temp;
  
  init_system();  /* Initialize variables and hardware */

  init_ADC();     /* Initialise ADC */       
  init_GPT1();    /* Turn on timer 1 */
  init_GPT2();    /* Turn on timer 2 */
  
  MCRB &= 0xFFFE; /* I/O on IOPC0 for monitoring purposes */
 
  IMR |= INT2;    /* Turn on INT 2 */
  
  asm("    CLRC INTM"); /* Turn on maskable interrupts */ 
  
  for ( ;; )
  {  
    if ( perform_fft != 0 )
      {
       perform_fft = 0;  /* Clear flag used to start fft */
       
       PCDATDIR = 0x0101;   /* IOPC0 high */
     
       ADCCTRL2 |= SOC_SEQ1;   /* Start next conversion*/ 
     
       copy_input_to_complex(); /* Copy inputs from receive buffer */
                                  
   
       FFT(y,8);          /* Calls generic FFT function*/
   
       /* Determine magnitude of (y[0]).real */
       /* output1 lies in range 0 to 32736 */
   
       if ( (y[0]).real > 0)
         output1 = (y[0]).real; 
       else
         output1 = -(y[0]).real; 
     
       /* Determine magnitude of (y[0]).real */
       /* output2 lies in range -32736 to 32736 */
   
       if ( (y[2]).real > 0)
         output2 = (y[2]).real; 
       else
         output2 = -(y[2]).real;       
     
       /* Scale output in range 0 to 1475 */
     
       temp = (signed long)(output1 * 2952);
       output1 = (signed int)(temp >> 16);
   
       T1CMPR = output1;

       temp = (signed long)( output2 * 2952);
       output2 = (signed int)(temp >> 16);
   
       T2CMPR = output1;  

       shuffle_and_read();  /* Read in latest value from ADC */
                            /* and put into buffer */

       PCDATDIR = 0x0100;   /* IOPC0 low */
     
     } /* End if */
    
  } /* End for */

} /* End main() */

/************************************************************/

/* Interrupt routine */
/* The interrupt occurs once every 0.1 ms.
/* Will make perform_fft = 1 once every 20 * 0.1 ms = 2 ms */

void c_int2(void)
{
 static unsigned int x;
 
 if ( 0x0027 == PIVR) 
    {
     EVAIFRA |= T1PINT_FLAG; /* Clear GPT1 period interrupt */
     
     if ( x < 19 )   /* Increase if FFT with more points */
      { 
        x++;
      }
     else
      {
        x = 0;
        perform_fft = 1; /* Global flag to start FFT */
      } 
    
    }
}

/* End of fft.c */

/************************************************************/ 
