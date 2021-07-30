/************************************************************/
/*                                          
   io2407.h                                 
   Header file for Input / Outputs and Mode Control      
*/                                                                     
/************************************************************/

/* I/0 Multiplex control register A. Selects primary or secondary function */

#define MCRA *(volatile unsigned int *) 0x7090
#define MCRB *(volatile unsigned int *) 0x7092
#define MCRC *(volatile unsigned int *) 0x7094

/* Data and direction registers for input/ output ports */

#define PADATDIR *(volatile unsigned int *)0x7098
#define PBDATDIR *(volatile unsigned int *)0x709A
#define PCDATDIR *(volatile unsigned int *)0x709C
#define PDDATDIR *(volatile unsigned int *)0x709E
#define PEDATDIR *(volatile unsigned int *)0x7095
#define PFDATDIR *(volatile unsigned int *)0x7096

/* End of io2407.h */
