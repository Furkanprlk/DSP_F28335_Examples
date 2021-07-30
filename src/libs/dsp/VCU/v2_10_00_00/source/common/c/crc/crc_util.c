//#############################################################################
//! \file source/common/C/crc/crc_util.c
//!
//! \brief  Utility routines for CRC calculations
//!
//! \date   Jul 23, 2013
//! 
//
//  Group: 			C2000
//  Target Family:	F2837x
//
// Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/ 
// ALL RIGHTS RESERVED 
//#############################################################################
//$TI Release: C28x VCU Library Version v2.10.00.00 $
//$Release Date: Mar 3, 2015 $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "vcu2_crc.h"
//*****************************************************************************
// defines
//*****************************************************************************

//*****************************************************************************
// globals
//*****************************************************************************

//*****************************************************************************
// function definitions
//*****************************************************************************
uint32_t CRC_bitReflect(uint32_t valToReverse,int16_t bitWidth)
{
	int16_t i,j,p,t;
	uint32_t pattern, skip;
	//unsigned int a, b;
	uint32_t value = valToReverse;

	//Determine what power of 2 bitWidth is
	t = bitWidth; p = 0;
	while(t > 1){
		t = t >> 1;
		p++;
	}

	//Start the reversing process
	for(i = 0; i < p; i++){
		//Increment skip
		skip = CRC_pow2(i);

		//Initialize pattern
		pattern = 0xFFFFFFFF;
		//First generate the pattern for the switch
		for(j = 0; j < (bitWidth/skip)-1; j++){
			pattern ^= (pattern << skip);
		}

		//Make the switch
		//a = ((value & pattern) << skip);
		//b = ((value >> skip) & pattern);
		//value = a | b;
		value = (((value & pattern) << skip) | ((value >> skip) & pattern));
	}

	return value;

}


uint16_t CRC_pow2(uint16_t power)
{
	if (power == 0){
		return 1;
	}else{
		return(2 * CRC_pow2(--power));
	}
}
// End of file
