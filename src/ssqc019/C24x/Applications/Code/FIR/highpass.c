/***********************************************************/
/*
  Highpass FIR filter.
*/
/***********************************************************/

unsigned int highpass_filter(signed int newest_sample);

#define N 11

extern array[N+1];

/* 
  Do not declare constants as unsigned! 

  array[] must be declared static inside function so that
  the values are kept between calls.       

  Input: Newest sample in range -3FF0h to +3FF0h.
  Returns: Unsigned value in range 0 to 1475 for T1PWM.
*/
/***********************************************************/

unsigned int highpass_filter(signed int newest_sample)
{
 static signed int constants2[N] = {0,-1534,-3306,-4961,-6134, 26214,-6134,-4961,-3306,-1534,0};
 signed long sum;
 unsigned int i;    
 unsigned int return_value;
  
 sum = 0; /* Start accumulation at zero */
 
 for (i = N-1 ; i > 0 ; i--)
   {
    array[i] = array[i-1]; /* Shuffle along one place */
    sum += ( array[i] * constants2[i]);
   } 
	    
 array[0] = newest_sample;  /* Input new value */
 sum +=  ( array[0] * constants2[0] );
       
 sum += 887384476;  /* Convert to unsigned. Add MAXIMUM */
 sum += 0x8000;     /* Round up */
 
 /* High word of sum will contain required value */
 /* Scale to give output 0 to 1475 for T1PWM */
       
 return_value = (unsigned int)(((sum>>16)*0x0FA4 )>>16); 
 
 /* return_value can exceed 1475. Therefore limit range */
 
 if ( return_value > 1475)
   return_value = 1475;
 
 return(return_value);
}
                      
/* End of asmlpass.c */                      
                      