/*****************************************************************************/
/*                                                                           */
/* 	                      dcmotor.c                                         */
/*                                                                           */
/*****************************************************************************/

/*
  Control of a DC motor driven by T2PWM.
  Monitor DC supply on ADCIN3. 
  Monitor motor current on ADCIN5.
  Calculate power taken by motor and output on T1PWM. 
  
  Because of polarity protection diode in the circuit, the
  voltage at the board will be approximately 0.6V less than
  that of the supply.        
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
 T1CMPR  = 0;       /* Duty = 0% */
 T1CNT   = 0xFFFE;  /* Set to -2 */
 T1CON   = 0x9142;  /* Start timer 1 */     
}

/* Initialise General Purpose Timer 2 */

void init_GPT2(void)
{
 MCRA   |= T2PWM;   /* Turn on T2PWM */
 T2CON   = 0x8142;  /* Turn off GPT2 */
 GPTCONA |= 0x0008; /* Controlled from GPT1 */
 T2PR    = 1475;    /* 10 kHz */
 T2CMPR  = 1475;    /* Duty cycle for motor off */
 T2CNT   = 0xFFFE;  /* Set to -2 */
 T2CON   = 0x9142;  /* Start timer 2 */
}
      
/***********************************************************/      
/*
  Initialise the analog-to-digital converter.
  Set up to measure channels 0 to 5.   
  
  An event from Event Manager A e.g. GPT1 will start the
  conversion.
*/
/***********************************************************/
      
void init_ADC()
{
  /* Non Cascade for 8 measurements. */    
  /* Will affect RESULT0 to RESULT5 only */
  
  ADCCTRL1 = (ADC_SOFT|ADC_CPS|ADC_ACQ_PS3|ADC_ACQ_PS2|ADC_ACQ_PS1|ADC_ACQ_PS0);

  CHSELSEQ1 = 0x3210; /* 8 measurements on Channels 0 - 5 */
  CHSELSEQ2 = 0x0054;
  CHSELSEQ3 = 0xFFFF;
  CHSELSEQ4 = 0xFFFF;
  MAX_CONV  = 0x0007; /* 8 measurements */
                                     
  /* Reset sequence at zero and EVA to start conversion */                                   
                                     
  ADCCTRL2 = (RST_SEQ1 | EVA_SOC_SEQ1); 
} 
   
/***********************************************************/   
/*
  Read potentiometer on ADCIN0.
  Value measured in RESULT0 will lie in range 0 to FFC0h.
  To ensure this is treated as a positive number, shift
  it one place to the right. This will make the value lie 
  in the range 0 to 7FE0h.
  
  Multiply this value by a scaling factor to produce an
  value in the range 0 to 100 percent.
  
  Return value in range 0 to 100 percent.
*/                           
/***********************************************************/
      
signed int read_potentiometer(void)
{
 signed int return_value;
 signed long scaled;
  
 scaled = (RESULT0 >> 1); /* Make room for sign bit */
 
 scaled *= 0x00C8; /* Scale in range 0 to 100 */
                
 return_value = (signed int)(scaled >> 16);               
 
 return(return_value);
}

/***********************************************************/
/*
  Control motor.
  
  Input: 0 to 100 (per cent) from potentiometer.
  Output: 0 to 1475 for PWM to output stage.  
  
  To ensure that motor is switched fully on and switched
  fully off, ignore 5% of extreme of potentiometer.
*/
/***********************************************************/

signed int control_motor(signed int input)
{
 signed int return_value;
 signed long scaled;
 
 if ( input < 5)
  {
   /* When potentiometer is at less than 5% travel, motor off */
   return_value = 0;
  }   
 else if ( input > 95)
  {
   /* When potentiometer is at 95% or more, turn motor fully on */ 
   return_value = 1475;
  } 
 else
  {
   /* Potentiometer between 5% and 95% of travel */
   /* Calculate output in range 0 to 1475 */
   
   scaled = (long)(input - 5);
   
   scaled *= 4196; /* Scale input */
   
   return_value = (signed int)(scaled >> 8);
  } 
 
 /* Reverse direction of potentiometer so high input */
 /* corresponds to a low value of T1PR */
 
 return(1475 - return_value);
}  
      
/***********************************************************/
/*
  Measure motor current.
  Read analog input on ADCIN5.
  The value in RESULT5 will be proportional to the current.
  Maximum current = 3.3V / 0.47R = 7.02A
  Therefore 0xFFC0 in RESULT5 will represent 7.02A.
  The function will return a signed value in range 
  0 to 702. 
*/
/***********************************************************/
   
volatile signed int measure_current(void)
{
 signed int return_value;
 signed long scaled;
  
 scaled = (RESULT5 >> 1); /* Make room for sign bit */
 
 scaled *= 0x057D; /* Scale in range 0 to 702 decimal */
 
 return_value = (signed int)(scaled >> 16);
 
 return(return_value);
}   

/***********************************************************/
/*
   Measure the supply voltage through a resistor divider.
 
   Read analog input on ADC3.
   The value in RESULT3 will be proportional to the voltage.
   
   Maximum voltage will be 3.3V * (33k + 3.3k)/3.3k = 36.3V
   Therefore 0xFFC0 in RESULT3 will represent 36.3V  
   
   The function will return a value in the range 0 to 3630
   to represent 0V to 36.30V
*/
/***********************************************************/

volatile signed int measure_voltage(void)
{
 signed int return_value;
 signed long scaled;
  
 scaled = (signed long)(RESULT3 >> 1); /* Make room for sign bit */
 
 scaled *= 0x1C63; /* Scale in range 0 to 3630 */         
 
 return_value = (signed int)(scaled >> 16);
 
 return(return_value);
}

/***********************************************************/
/*
  Calculate power from supply voltage and motor current.
  Maximum power = 7.02 A * 36.30 V
  We shall limit the maximum output to 33.00 V * 1.00A = 33 W.
  Returns an output in the range 0 to 1475 to represent
  0 to 33.0 W to drive T1PWM.
*/
/***********************************************************/

volatile signed int calculate_power(signed int current, 
                                    signed int voltage)
{
 signed long power;
 signed int return_value;
 
 power = current * voltage; 

 power *= 293; /* Scale output power */           
 
 return_value = (signed int)(power >> 16);
 
 if ( return_value > 1475) /* Limit output to 33 W */ 
  {
   return_value = 1475;
  }
  
 return (return_value);
}

/***********************************************************/
/*
  Main program to control motor.
  
  Uses timer running at 10 kHz to produce a PWM output
  from a potentiometer input.
*/
/***********************************************************/


void main(void)
{
 signed int x, y;    /* General purpose variables */
 signed int voltage; /* Supply voltage to motor */
 signed int current; /* Current taken by motor */
  
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
	  
      x = read_potentiometer(); /* Read analog input from ADCIN0 */	
 	
      current = measure_current(); /* 0 to 7.02 A */
      
      voltage = measure_voltage(); /* 0 to 36.30 V */
      
      y = calculate_power(current, voltage);  
  
      T1CMPR = y;  /* Ouput power on T1PWM */
	  
      y = control_motor(x); /* Control motor speed */ 
	
      T2CMPR = y; /* Output control pulses on T2PWM */
    }
  }

}

/* End of dcmotor.c */                                  

/************************************************************/
