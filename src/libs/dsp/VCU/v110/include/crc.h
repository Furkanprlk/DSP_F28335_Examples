/******************************************************************************
*******************************************************************************
* 
* FILE: crc.h
* 
* DESCRIPTION: CRC 8,16 and 32 API
*
* Notes: 
*   
*  o CRC implementations are based on tables. If the tables
*    are calculated on the fly, the macro GEN_CRC_TABLES shall be defined
*    and genCRC8Tables() shall be called during 
*    initialization. If the macro is not defined, pre-calculated tables will
*    will be used. Using the latter option can put the tables to flash.
*
*******************************************************************************
*  $TI Release: C28x VCU Library Version v1.10 $
*  $Release Date: September 26, 2011 $
*******************************************************************************
*  This software is licensed for use with Texas Instruments C28x
*  family DSCs.  This license was provided to you prior to installing
*  the software.  You may review this license by consulting a copy of
*  the agreement in the doc directory of this library.
* ------------------------------------------------------------------------
*          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
*                          All Rights Reserved.
******************************************************************************/

#ifndef __CRC_H__
#define __CRC_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "typedefs.h"

//###########################################################################
//
// Macro Definitions
//
//###########################################################################
#define INIT_CRC8 	 0x0		//!< Initial CRC Register Value
#define INIT_CRC16 0x0			//!< Initial CRC Register Value
#define INIT_CRC32 0x0			//!< Initial CRC Register Value
#define POLYNOMIAL16 0x8005		//!< CRC16 802.15.4 Polynomial
#define POLYNOMIAL32 0x04c11db7 //!< CRC32 PRIME Polynomial
#define POLYNOMIAL8  0x07		//!< CRC8 PRIME Polynomial
//###########################################################################
//
// Externally defined variables
//
//###########################################################################
extern uint16 crc8_table[];
extern uint16 crc16p1_table[];
extern uint16 crc16p2_table[];
extern uint32 crc32_table[];

//###########################################################################
//
// Prototypes for the APIs.
//
//###########################################################################

extern void genCRC8Table();
extern void genCRC16P1Table();
extern void genCRC16P2Table();
extern void genCRC32Table();
uint16 getCRC8_cpu(uint16 input_crc8_accum, uint16 *msg, parity_t parity, uint16 rxLen);
extern uint16 getCRC8_vcu(uint32 input_crc8_accum, uint16 *msg, parity_t parity, 
				uint16 rxLen);
uint16 getCRC16P1_cpu (uint16 input_crc16_accum, uint16 *msg, parity_t parity, uint16 rxLen);
extern uint16 getCRC16P1_vcu(uint32 input_crc16_accum, uint16 * msg, parity_t parity, 
    			uint16 rxLen);
uint16 getCRC16P2_cpu (uint16 input_crc16_accum, uint16 *msg, parity_t parity, uint16 rxLen);
extern uint16 getCRC16P2_vcu(uint32 input_crc16_accum, uint16 * msg, parity_t parity, 
    			uint16 rxLen);
uint32 getCRC32_cpu (uint32 input_crc32_accum, uint16 *msg, parity_t parity, uint16 rxLen);
extern uint32 getCRC32_vcu (uint32 input_crc32_accum, uint16 *msg, parity_t parity, 
				uint16 rxLen);
				
//###########################################################################
//
// Mark the end of the C bindings section for C++ compilers.
//
//###########################################################################
#ifdef __cplusplus
}
#endif //__cplusplus

#endif // __CRC_H__
