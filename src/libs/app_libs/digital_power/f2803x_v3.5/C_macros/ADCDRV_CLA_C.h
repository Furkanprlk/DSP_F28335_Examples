/**
 * ADC driver for the CLA.  Normalizes ADC results returning a floating point number
 * in the range [0.0, 1.0].  Requires ADC modules to be configured with ADC_SOC_CNF function
 * found within the ADC_SOC_Cnf.c source file.
 * @see ADC_SOC_Cnf.c
 */

#ifndef ADCDRV_CLA_C_H_
#define ADCDRV_CLA_C_H_

/**
 * 4 channel ADCDRV structure.
 */
typedef struct{
	volatile Uint16 *AdcResPtr1;
	volatile Uint16 *AdcResPtr2;
	volatile Uint16 *AdcResPtr3;
	volatile Uint16 *AdcResPtr4;

	float32 AdcResult1;
	float32 AdcResult2;
	float32 AdcResult3;
	float32 AdcResult4;
} ADCDRV_4ch_CLA_C;


/**
 * 8 channel ADCDRV structure.
 */
typedef struct{
	volatile Uint16 *AdcResPtr1;
	volatile Uint16 *AdcResPtr2;
	volatile Uint16 *AdcResPtr3;
	volatile Uint16 *AdcResPtr4;
	volatile Uint16 *AdcResPtr5;
	volatile Uint16 *AdcResPtr6;
	volatile Uint16 *AdcResPtr7;
	volatile Uint16 *AdcResPtr8;

	float32 AdcResult1;
	float32 AdcResult2;
	float32 AdcResult3;
	float32 AdcResult4;
	float32 AdcResult5;
	float32 AdcResult6;
	float32 AdcResult7;
	float32 AdcResult8;
} ADCDRV_8ch_CLA_C;

/**
 * ADC bit-resolution constant.
 */
#define INV_4096 ((float32) 0.000244140625)

/*
 * Normalizes ADC conversions.
 * @param ADC result
 * @returns floating point normalized ADC conversion in range [0.0, 1.0]
 */
#define ADCDRV_1ch_CLA_C(num) ((num) * INV_4096)

/*
 * Normalizes 4 ADC channel conversion results.  Pointers to
 * ADC result registers must be set during initialization.
 * @param ADCDRV_4ch_CLA_C structure
 * @returns floating point normalized ADC conversions in range [0.0, 1.0]
 */
#define ADCDRV_4ch_CLA_C(v)							\
	v.AdcResult1 = (*(v.AdcResPtr1) * INV_4096);	\
	v.AdcResult2 = (*(v.AdcResPtr2) * INV_4096);	\
	v.AdcResult3 = (*(v.AdcResPtr3) * INV_4096);	\
	v.AdcResult4 = (*(v.AdcResPtr4) * INV_4096)

/**
 * Initial values for ADCDRV_4ch_CLA_C structures.
 */
#define ADCDRV_4ch_CLA_C_INIT(v)					\
	/* Set default AdcResult registers. */			\
	v.AdcResPtr1 = &AdcResult.ADCRESULT1;			\
	v.AdcResPtr2 = &AdcResult.ADCRESULT2;			\
	v.AdcResPtr3 = &AdcResult.ADCRESULT3;			\
	v.AdcResPtr4 = &AdcResult.ADCRESULT4;			\
													\
	/* Set results to zero. */						\
	v.AdcResult1 = 0;								\
	v.AdcResult2 = 0;								\
	v.AdcResult3 = 0;								\
	v.AdcResult4 = (0)


/*
 * Normalizes 8 ADC channel conversion results.  Pointers to
 * ADC result registers must be set during initialization.
 * @param ADCDRV_8ch_CLA_C structure
 * @returns floating point normalized ADC conversions in range [0.0, 1.0]
 */
#define ADCDRV_8ch_CLA_C(v)							\
	v.AdcResult1 = (*(v.AdcResPtr1) * INV_4096);	\
	v.AdcResult2 = (*(v.AdcResPtr2) * INV_4096);	\
	v.AdcResult3 = (*(v.AdcResPtr3) * INV_4096);	\
	v.AdcResult4 = (*(v.AdcResPtr4) * INV_4096);	\
	v.AdcResult5 = (*(v.AdcResPtr5) * INV_4096);	\
	v.AdcResult6 = (*(v.AdcResPtr6) * INV_4096);	\
	v.AdcResult7 = (*(v.AdcResPtr7) * INV_4096);	\
	v.AdcResult8 = (*(v.AdcResPtr8) * INV_4096)

/**
 * Initial values for ADCDRV_8ch_CLA_C structures.
 */
#define ADCDRV_8ch_CLA_C_INIT(v)					\
	/* Set default AdcResult registers. */			\
	v.AdcResPtr1 = &AdcResult.ADCRESULT1;			\
	v.AdcResPtr2 = &AdcResult.ADCRESULT2;			\
	v.AdcResPtr3 = &AdcResult.ADCRESULT3;			\
	v.AdcResPtr4 = &AdcResult.ADCRESULT4;			\
	v.AdcResPtr5 = &AdcResult.ADCRESULT5;			\
	v.AdcResPtr6 = &AdcResult.ADCRESULT6;			\
	v.AdcResPtr7 = &AdcResult.ADCRESULT7;			\
	v.AdcResPtr8 = &AdcResult.ADCRESULT8;			\
													\
	/* Set results to zero. */						\
	v.AdcResult1 = 0;								\
	v.AdcResult2 = 0;								\
	v.AdcResult3 = 0;								\
	v.AdcResult4 = 0;								\
	v.AdcResult5 = 0;								\
	v.AdcResult6 = 0;								\
	v.AdcResult7 = 0;								\
	v.AdcResult8 = (0)


#endif /* ADCDRV_CLA_C_H_ */
