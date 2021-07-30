/***********************************************************/
/* 
  EVA.h
  Header file for Event Manager A
*/
/***********************************************************/


#define GPTCONA *(volatile unsigned int *) 0x7400
#define T1CNT   *(volatile unsigned int *) 0x7401
#define T1CMPR  *(volatile unsigned int *) 0x7402
#define T1PR    *(volatile unsigned int *) 0x7403
#define T1CON   *(volatile unsigned int *) 0x7404

#define T2CNT   *(volatile unsigned int *) 0x7405
#define T2CMPR  *(volatile unsigned int *) 0x7406
#define T2PR    *(volatile unsigned int *) 0x7407
#define T2CON   *(volatile unsigned int *) 0x7408 

#define T1PWM 0x1000
#define T2PWM 0x2000  

#define EVAIMRA *(volatile unsigned int*) 0x742C
#define EVAIFRA *(volatile unsigned int*) 0x742F

#define T1PINT_FLAG 0x0080

/* End of EVA.h */