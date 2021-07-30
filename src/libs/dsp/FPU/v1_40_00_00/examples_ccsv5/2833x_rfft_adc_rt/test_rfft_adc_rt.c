// ========================================================================
//  This software is licensed for use with Texas Instruments C28x
//  family DSCs.  This license was provided to you prior to installing
//  the software.  You may review this license by consulting a copy of
//  the agreement in the doc directory of this library.
// ------------------------------------------------------------------------
//          Copyright (C) 2014-2015 Texas Instruments, Incorporated.
//                          All Rights Reserved.
// ========================================================================
//
//  File: Main.c -- Real-time RFFT with 12-bit ADC Input Test Example
//
//	TITLE:   DSP2833x Device Real-time Real FFT Test Program.   
//
//=========================================================================
//  DESCRIPTION:
//
//    This program shows how to compute a real FFT with 12-bit real-time ADC 
//    input and associated spectrum magnitude, phase. The input data is 
//    collected by interrupt service routine function adc_isr(). The signal
//    input (can be any signal from signal generator or sensor) is excerted
//    in ADC input A0. The signal is sampled by epwm module and sampling 
//    frequency is defined in Lab.h. Here is 48kHz. The dynamic range of the 
//    input signal should be less than 0~3V. Real time real FFT is conducted 
//    frame by frame. As long as one frame of data is collected by adc_isr, 
//    it will set the FFTStartFlag. Whenever the main program detect the 
//    FFTStartFlag set, the FFT calculate starts. The FFTStartFlag is cleared 
//    after the calculation finished.
//
//    The input buffer must be aligned to a multiple of the FFT size if using 
//    RFFT_adc_f32.  If you do not wish to align the input buffer then use the 
//    RFFT_adc_f32u function. In this case, the section alignment #pragma can 
//    be commented.  However, using this function will reduce cycle performance 
//    of the algorithm.
//
//
// FUNCTIONS:
//
//    void RFFT_adc_f32 (RFFT_ADC_F32_STRUCT *)
//    void RFFT_f32_mag (RFFT_F32_STRUCT *)
//    void RFFT_f32_phase (RFFT_F32_STRUCT *)
//
//    Where RFFT_ADC_F32_STRUCT is a structure defined as:
//
//	 typedef struct {
//	  	uint16_t   *InBuf;
//  	void	   *Tail;
//	 } RFFT_ADC_F32_STRUCT;
//
//    Where RFFT_F32_STRUCT is a structure defined as:
//
//    typedef struct {
//      float  *InBuf;
//      float  *OutBuf;
//      float  *CosSinBuf;
//      float  *MagBuf;
//      float  *PhaseBuf;
//      uint16_t FFTSize;
//      uint16_t FFTStages;
//    } RFFT_F32_STRUCT;
//
//  ASSUMPTIONS:
//
//	   * OutBuf of RFFT_F32_STRUCT has to be passed to Tail of 
//       RFFT_ADC_F32_STRUCT
//	   * Input signal is stored in Signal.asm
//     * FFTSize must be a power of 2 (32, 64, 128, etc)
//     * FFTSize must be greater or equal to 32
//     * FFTStages must be log2(FFTSize)
//     * InBuf, OutBuf, CosSinBuf are FFTSize in length
//     * MagBuf and PhaseBuf are FFTSize/2+1 in length
//     * MagBuf and PhaseBuf are not used by this function.
//       They are only used by the magitude and phase calculation functions.
//
//  Watch Variables:
//
//      InBuf(RFFT_ADC_F32_STRUCT)    Input buffer
//      InBuf(RFFT_F32_STRUCT)		  Not used
//		Tail						  Stored the address of OutBuf
//      OutBuf						  Output buffer
//      CosSinBuf        			  Twiddle factor buffer
//      MagBuf       				  Magnitude buffer
//      PhaseBuf                      Phase buffer
//      j							  Index of normalized digital frequency component
//      freq						  Real analog frequency of raw signal
//
//###########################################################################
// $TI Release: C28x Floating Point Unit Library V1.40.00.00 $
// $Release Date: Mar 10, 2014 $
//###########################################################################

#include "DSP28x_Project.h"     // Device Headerfile and Examples Include File
#include "math.h"
#include "fpu_rfft.h"

#define RFFT_STAGES     9
#define RFFT_SIZE       (1 << RFFT_STAGES) 

#define ADC_BUF_LEN         RFFT_SIZE   // ADC buffer length
#define ADC_SAMPLE_PERIOD   3124            // 3124 = (3125-1) = 48 KHz sampling w/ 150 MHz SYSCLKOUT

#define F_PER_SAMPLE        48000.0L/(float)RFFT_SIZE  //Internal sampling rate is 48kHz 

RFFT_ADC_F32_STRUCT rfft_adc;
RFFT_F32_STRUCT rfft;

float RFFToutBuff[RFFT_SIZE];                //Calculated FFT result
float RFFTF32Coef[RFFT_SIZE];        //Coefficient table buffer
float RFFTmagBuff[RFFT_SIZE/2+1];      //Magnitude of frequency spectrum

//--- Global Variables
uint16_t AdcBuf[ADC_BUF_LEN];					// ADC buffer allocation

volatile uint16_t FFTStartFlag = 0;			// One frame data ready flag

uint16_t DEBUG_TOGGLE = 1;					// Used in realtime mode investigation 

// Prototype statements for functions found within this file.
interrupt void adc_isr(void);

/**********************************************************************
* Function: main()
*
* Description: Main function for C2833x Real-time RFFT 
**********************************************************************/
void main(void)
{
	uint16_t i,j;
   	float freq;                       // Frequency of single-frequency-component signal
	
//--- CPU Initialization
	InitSysCtrl();						// Initialize the CPU (FILE: SysCtrl.c)
	InitGpio();							// Initialize the shared GPIO pins (FILE: Gpio.c)
	InitPieCtrl();						// Initialize and enable the PIE (FILE: PieCtrl.c)

//--- Peripheral Initialization
	InitAdc();							// Initialize the ADC (FILE: Adc.c)

// Interrupts that are used in this example are re-mapped to
// ISR functions found within this file.
   	EALLOW;  // This is needed to write to EALLOW protected register
   	PieVectTable.ADCINT = &adc_isr;
   	EDIS;    // This is needed to disable write to EALLOW protected registers

    rfft_adc.Tail = &rfft.OutBuf;				//Link the RFFT_ADC_F32_STRUCT to
   												//RFFT_F32_STRUCT. Tail pointer of 
   												//RFFT_ADC_F32_STRUCT is passed to
   												//the OutBuf pointer of RFFT_F32_STRUCT
    rfft.FFTSize  = RFFT_SIZE;				//Real FFT size
    rfft.FFTStages = RFFT_STAGES;			//Real FFT stages
    rfft_adc.InBuf = &AdcBuf[0];				//Input buffer
    rfft.OutBuf = &RFFToutBuff[0];   			//Output buffer
    rfft.CosSinBuf = &RFFTF32Coef[0];	//Twiddle factor
    rfft.MagBuf = &RFFTmagBuff[0];		//Magnitude output buffer

    RFFT_f32_sincostable(&rfft);  				//Calculate twiddle factor
 
 	//Clean up output buffer
    for (i=0; i < RFFT_SIZE; i++)
    {
    	 RFFToutBuff[i] = 0;
    }
   
   	//Clean up magnitude buffer
    for (i=0; i < RFFT_SIZE/2; i++)
    {
   		 RFFTmagBuff[i] = 0;
    }  

//--- Enable global interrupts
	asm(" CLRC INTM, DBGM");			// Enable global interrupts and realtime debug

//--- Main Loop
	while(1)							// endless loop - wait for an interrupt
	{
		if(FFTStartFlag)				// If one frame data ready, then do FFT
		{
			RFFT_adc_f32u(&rfft_adc);   // This version of FFT doesn't need buffer alignment
			RFFT_f32_mag(&rfft);		// Calculate spectrum amplitude
			
   			j = 1;
   			freq = RFFTmagBuff[1];
   			for(i=2;i<RFFT_SIZE/2+1;i++)
   			{
   				//Looking for the maximum valude of spectrum magnitude
      			if(RFFTmagBuff[i] > freq)
      			{
          			j = i;
          			freq = RFFTmagBuff[i]; 
      			}
   			}
   
   			freq = F_PER_SAMPLE * (float)j;	//Convert normalized digital frequency to analog frequency
   				
			FFTStartFlag = 0;			   	//Start collecting the next frame of data
		}
		asm(" NOP");
	}
} //end of main()

interrupt void  adc_isr(void)
{
	static uint16_t *AdcBufPtr = AdcBuf;					// Pointer to ADC data buffer
	static volatile uint16_t GPIO34_count = 0;			// Counter for pin toggle

	PieCtrlRegs.PIEACK.all = PIEACK_GROUP1;				// Must acknowledge the PIE group

//--- Manage the ADC registers
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;					// Reset SEQ1 to CONV00 state
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;					// Clear ADC SEQ1 interrupt flag

//--- Read the ADC result
	*AdcBufPtr++ = AdcMirror.ADCRESULT0;				// Read the result

//--- Brute-force the circular buffer
	if( AdcBufPtr == (AdcBuf + ADC_BUF_LEN) )
	{
		AdcBufPtr = AdcBuf;								// Rewind the pointer to the beginning
		FFTStartFlag = 1;								// One frame data ready
	}

//--- Example: Toggle GPIO18 so we can read it with the ADC
	if(DEBUG_TOGGLE == 1)
	{
		GpioDataRegs.GPATOGGLE.bit.GPIO18 = 1;			// Toggle the pin
	}

//--- Example: Toggle GPIO34 at a 0.5 sec rate (connected to the LED on the ControlCARD).
//             (1/48000 sec/sample)*(1 samples/int)*(x interrupts/toggle) = (0.5 sec/toggle)
//             ==> x = 24000
	if(GPIO34_count++ > 24000)							// Toggle slowly to see the LED blink
	{
		GpioDataRegs.GPBTOGGLE.bit.GPIO34 = 1;			// Toggle the pin
		GPIO34_count = 0;								// Reset the counter
	}
	
	return;
} //end of main()

//===========================================================================
// End of File
//===========================================================================

