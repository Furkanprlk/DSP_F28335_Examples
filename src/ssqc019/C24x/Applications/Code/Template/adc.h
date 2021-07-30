/***********************************************************/
/* 
  adc.h
  Header file for analog-to-digital conversion
*/
/***********************************************************/


#define ADCCTRL1      *(volatile unsigned int *) 0x70A0
#define ADCCTRL2      *(volatile unsigned int *) 0x70A1
#define MAX_CONV     *(volatile unsigned int *) 0x70A2 
#define CHSELSEQ1    *(volatile unsigned int *) 0x70A3 
#define CHSELSEQ2    *(volatile unsigned int *) 0x70A4 
#define CHSELSEQ3    *(volatile unsigned int *) 0x70A5
#define CHSELSEQ4    *(volatile unsigned int *) 0x70A6
#define AUTO_SEQ_SR  *(volatile unsigned int *) 0x70A7 

#define RESULT0      *(volatile unsigned int *) 0x70A8
#define RESULT1      *(volatile unsigned int *) 0x70A9
#define RESULT2      *(volatile unsigned int *) 0x70AA
#define RESULT3      *(volatile unsigned int *) 0x70AB
#define RESULT4      *(volatile unsigned int *) 0x70AC
#define RESULT5      *(volatile unsigned int *) 0x70AD
#define RESULT6      *(volatile unsigned int *) 0x70AE
#define RESULT7      *(volatile unsigned int *) 0x70AF
#define RESULT8      *(volatile unsigned int *) 0x70B0
#define RESULT9      *(volatile unsigned int *) 0x70B1
#define RESULT10     *(volatile unsigned int *) 0x70B2
#define RESULT11     *(volatile unsigned int *) 0x70B3
#define RESULT12     *(volatile unsigned int *) 0x70B4
#define RESULT13     *(volatile unsigned int *) 0x70B5
#define RESULT14     *(volatile unsigned int *) 0x70B6
#define RESULT15     *(volatile unsigned int *) 0x70B7

#define CALIBRATION  *(volatile unsigned int *)0x70B8

/* Individual bits of ADCCTRL1 */ 

#define  ADC_RESVD	      0x8000  
#define  ADC_RESET	      0x4000
#define  ADC_SOFT	  	  0x2000
#define  ADC_FREE	  	  0x1000
#define  ADC_ACQ_PS3	  0x0800
#define  ADC_ACQ_PS2	  0x0400
#define  ADC_ACQ_PS1	  0x0200
#define  ADC_ACQ_PS0	  0x0100
#define  ADC_CPS	      0x0080
#define  ADC_CONT_RUN	  0x0040
#define  ADC_INT_PRI	  0x0020
#define  ADC_SEQ_CASC	  0x0010
#define  ADC_CAL_ENA	  0x0008
#define  ADC_BRG_ENA	  0x0004
#define  ADC_HI_LO	  	  0x0002
#define  ADC_FTEST_ENA	  0x0001

/* Individual bits of ADCTRL2 */

#define RST_SEQ1	      0x4000
#define STRT_CAL		  0x4000	
#define SOC_SEQ1	      0x2000
#define SEQ1_BSY	      0x1000 
#define INT_FLAG_SEQ1     0x0200 
#define EVA_SOC_SEQ1      0x0100

#define ADC_SIZE    16
        
/* End of ADC.h */
