#ifndef _VCU0_CRC_H_
#define _VCU0_CRC_H_
//#############################################################################
//! \file include/vcu0/vcu0_crc.h
//!
//! \brief  Cyclic Redundancy Check Header File
//!
//! \date   Apr 7, 2011
//!
//! \note   CRC implementations are based on tables. If the tables
//!  are calculated on the fly, the macro GEN_CRC_TABLES shall be defined
//!  and genCRC8Tables() shall be called during 
//!  initialization. If the macro is not defined, pre-calculated tables will
//!  will be used. Using the latter option can put the tables to flash.
//
//  Group: 			C2000
//  Target Family:	F2837x
//
// (C)Copyright 2012, Texas Instruments, Inc.
//#############################################################################
//$TI Release: C28x VCU Library Version v2.00.00.00 $
//$Release Date: Dec 6, 2013 $
//#############################################################################

//*****************************************************************************
// includes
//*****************************************************************************
#include "vcu0_types.h"

//!
//! \defgroup VCU0_CRC Cyclic Redundancy Check (VCU0)

//!
//! \ingroup VCU0_CRC
// @{

#ifdef __cplusplus
extern "C" {
#endif

//*****************************************************************************
// defines
//*****************************************************************************
#define INIT_CRC8 	   0x0		    //!< Initial CRC Register Value
#define INIT_CRC16     0x0		    //!< Initial CRC Register Value
#define INIT_CRC32     0x0		    //!< Initial CRC Register Value
#define POLYNOMIAL16_1 0x8005		//!< CRC16 802.15.4 Polynomial
#define POLYNOMIAL16_2 0x1021		//!< CRC16 Alternate Polynomial
#define POLYNOMIAL32   0x04c11db7   //!< CRC32 PRIME Polynomial
#define POLYNOMIAL8    0x07		    //!< CRC8 PRIME Polynomial

//*****************************************************************************
// globals
//*****************************************************************************
extern uint16 crc8_table[];
extern uint16 crc16p1_table[];
extern uint16 crc16p2_table[];
extern uint32 crc32_table[];

//*****************************************************************************
// function prototypes
//*****************************************************************************

//! \brief VCU(ASM)- function to get the 8-bit CRC
//!  
//! Calculate the 8-bit CRC of a message buffer by using the VCU instructions,
//! VCRC8L_1 and VCRC8H_1
//! 
//! \param input_crc8_accum The seed value for the CRC, in the event of a 
//!  multi-part message, the result of the previous crc8 can be used as 
//!  the initial value for the current segment crc8 calculation
//!  until the final crc is derived.
//! \param msg Address of the message buffer
//! \param parity Parity of the first message byte. The parity 
//! determines whether the CRC begins at the low byte (EVEN) or at the high byte (ODD).
//! \param rxLen Length of the message in bytes
//! \return CRC result
//      
extern uint16 getCRC8_vcu(uint32 input_crc8_accum, uint16 *msg, parity_t parity, 
				uint16 rxLen);

//! \brief VCU(ASM)- function to get the 16-bit CRC
//!  
//! Calculate the 16-bit CRC of a message buffer by using the VCU instructions
//! VCRC16P1H_1 and VCRC16P1L_1
//! 
//! \param input_crc16_accum The seed value for the CRC, in the event of a 
//! multi-part message, the result of the previous crc16 can be used as the initial 
//! value for the current segment crc16 calculation
//!  until the final crc is derived.
//! \param msg Address of the message buffer
//! \param parity Parity of the first message byte. The parity 
//! determines whether the CRC begins at the low byte (EVEN) or at the high byte (ODD).
//! \param rxLen Length of the message in bytes
//! \return CRC result
//    
extern uint16 getCRC16P1_vcu(uint32 input_crc16_accum, uint16 * msg, parity_t parity, 
    			uint16 rxLen);

//! \brief VCU(ASM)- function to get the 16-bit CRC
//!  
//! Calculate the 16-bit CRC of a message buffer by using the VCU instructions
//! VCRC16P2H_1 and VCRC16P2L_1
//!  
//! \param input_crc16_accum The seed value for the CRC, in the event of a 
//! multi-part message, the result of the previous crc16 can be used as the 
//! initial value for the current segment crc16 calculation
//!  until the final crc is derived.
//! \param msg Address of the message buffer
//! \param parity Parity of the first message byte. The parity determines whether 
//! the CRC begins at the low byte (EVEN) or at the high byte (ODD).
//! \param rxLen Length of the message in bytes
//! \return CRC result
//    
extern uint16 getCRC16P2_vcu(uint32 input_crc16_accum, uint16 * msg, parity_t parity, 
    			uint16 rxLen);
                
//! \brief VCU(ASM)- function to get the 32-bit CRC
//!  
//! Calculate the 32-bit CRC of a message buffer by using the VCU instructions
//! VCRC32H_1 and VCRC32L_1
//!
//! \param input_crc32_accum The seed value for the CRC, in the event of a 
//! multi-part message, the result of the previous crc32 can be used as the 
//! initial value for the current segment crc32 calculation
//!  until the final crc is derived.
//! \param msg Address of the message buffer
//! \param parity Parity of the first message byte. The parity determines 
//! whether the CRC begins at the low byte (EVEN) or at the high byte (ODD).
//! \param rxLen Length of the message in bytes
//! \return CRC result
//   
extern uint32 getCRC32_vcu (uint32 input_crc32_accum, uint16 *msg, parity_t parity, 
				uint16 rxLen);

//! \brief Generate the CRC lookup table using the polynomial 0x7
//! 
//! This function generates the CRC8 table for every possible byte,
//! i.e. 2^8 = 256 table values, using the CRC8_PRIME polynomial 0x07. It
//! expects a global array, crc8_table, to be defined in the application
//! code
// 
extern void genCRC8Table();

//! \brief Generate the CRC lookup table using the polynomial 0x8005
//! 
//! This function generates the CRC16 table for every possible byte,
//! i.e. 2^8 = 256 table values, using the CRC16_802_15_4 polynomial 0x8005. It
//! expects a global array, crc16p1_table, to be defined in the application
//! code
// 
extern void genCRC16P1Table();

//! \brief Generate the CRC lookup table using the polynomial 0x1021
//! 
//! This function generates the CRC16 table for every possible byte,
//! i.e. 2^8 = 256 table values, using the CRC16_ALT polynomial 0x1021. It
//! expects a global array, crc16p2_table, to be defined in the application
//! code
//
extern void genCRC16P2Table();

//! \brief Generate the CRC lookup table using the polynomial 0x04c11db7
//! 
//! This function generates the CRC32 table for every possible byte,
//! i.e. 2^8 = 256 table values, using the CRC32_PRIME polynomial 0x04c11db7. 
//! It expects a global array, crc32_table, to be defined in the application
//! code
// 
extern void genCRC32Table();

//! \brief C- function to get the 8-bit CRC
//!  
//! Calculate the 8-bit CRC of a message buffer by using the lookup table,
//! crc8_table, based on the polynomial 0x7.
//! 
//! \param input_crc8_accum The seed value for the CRC, in the event of a 
//! multi-part message, the result of the previous crc8 can be used as the 
//! initial value for the current segment crc8 calculation
//!  until the final crc is derived.
//! \param msg Address of the message buffer
//! \param parity Parity of the first message byte. The parity determines 
//! whether the CRC begins at the low byte (EVEN) or at the high byte (ODD).
//! \param rxLen Length of the message in bytes
//! \return CRC result
// 
uint16 getCRC8_cpu(uint16 input_crc8_accum, uint16 *msg, parity_t parity, uint16 rxLen);

//! \brief C- function to get the 16-bit CRC
//!  
//! Calculate the 16-bit CRC of a message buffer by using the lookup table,
//! crc16p1_table, based on the polynomial 0x8005.
//! 
//! \param input_crc16_accum The seed value for the CRC, in the event of a 
//! multi-part message, the result of the previous crc16 can be used as the 
//! initial value for the current segment crc16 calculation
//!  until the final crc is derived.
//! \param msg Address of the message buffer
//! \param parity Parity of the first message byte. The parity determines whether 
//! the CRC begins at the low byte (EVEN) or at the high byte (ODD).
//! \param rxLen Length of the message in bytes
//! \return CRC result
// 
uint16 getCRC16P1_cpu (uint16 input_crc16_accum, uint16 *msg, parity_t parity, uint16 rxLen);

//! \brief C- function to get the 16-bit CRC
//!  
//! Calculate the 16-bit CRC of a message buffer by using the lookup table,
//! crc16p2_table, based on the polynomial 0x1021.
//! 
//! \param input_crc16_accum The seed value for the CRC, in the event of a 
//! multi-part message, the result of the previous crc16 can be used as the 
//! initial value for the current segment crc16 calculation
//!  until the final crc is derived.
//! \param msg Address of the message buffer
//! \param parity Parity of the first message byte. The parity determines whether 
//! the CRC begins at the low byte (EVEN) or at the high byte (ODD).
//! \param rxLen Length of the message in bytes
//! \return CRC result
// 
uint16 getCRC16P2_cpu (uint16 input_crc16_accum, uint16 *msg, parity_t parity, uint16 rxLen);

//! \brief C- function to get the 32-bit CRC
//!  
//! Calculate the 32-bit CRC of a message buffer by using the lookup table,
//! crc32_table, based on the polynomial 0x04c11db7.
//!  
//! \param input_crc32_accum The seed value for the CRC, in the event of a 
//! multi-part message, the result of the previous crc32 can be used as the 
//! initial value for the current segment crc32 calculation
//!  until the final crc is derived.
//! \param msg Address of the message buffer
//! \param parity Parity of the first message byte. The parity determines whether the 
//! CRC begins at the low byte (EVEN) or at the high byte (ODD).
//! \param rxLen Length of the message in bytes
//! \return CRC result
// 
uint32 getCRC32_cpu (uint32 input_crc32_accum, uint16 *msg, parity_t parity, uint16 rxLen);

//! \brief Workaround to the silicon issue of first VCU calculation on power up being
//!  erroneous
//! 
//! Due to the internal power-up state of the VCU module, it is possible 
//! that the first CRC result will be incorrect. This condition applies to the 
//! first result from each of the eight CRC instructions. 
//! This rare condition can only occur after a power-on reset, but will not
//! necessarily occur on every power on. A warm reset will not cause this condition 
//! to reappear.
//! The application can reset the internal VCU CRC logic by 
//! performing a CRC calculation of a single byte in the initialization routine. 
//! This routine only needs to perform one CRC calculation and can use any of the 
//! CRC instructions
//
void CRC_reset(void);
				
#ifdef __cplusplus
}
#endif // extern "C"

// @} //ingroup

#endif //end of _VCU0_CRC_H_ definition

