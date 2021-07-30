;******************************************************************************
;******************************************************************************
; 
; FILE NAME: crc32_vcu.asm
;
; DESCRIPTION: This file contains the functions to do the CRC32 using VCU
;   polynomial  = 0x04c11db7
;
;******************************************************************************
;  $TI Release: C28x VCU Library Version v1.10 $
;  $Release Date: September 26, 2011 $
;******************************************************************************
;  This software is licensed for use with Texas Instruments C28x
;  family DSCs.  This license was provided to you prior to installing
;  the software.  You may review this license by consulting a copy of
;  the agreement in the doc directory of this library.
; ------------------------------------------------------------------------
;          Copyright (C) 2010-2011 Texas Instruments, Incorporated.
;                          All Rights Reserved.
;******************************************************************************


 ;/*! ASM- function to get the 32-bit CRC
; *
; * \param ACC = The initial value of crc, in case the message has been
; *  chopped into several parts, you can use the crc32 of the previous
; *  segment as the init value for the current segment crc32 calculation
; *  until the final crc is derived.
; * \param *+XAR4 = Address of the message buffer
; * \param AR5 = Parity of the first message byte, i.e. whether its on an even
; *  or odd address
; * \param *-SP[1]/AR0 = Length of the message in bytes
; *  
; * Calculate the 32-bit CRC of a message buffer by using the VCU instructions
; * VCRC32H_1 and VCRC32L_1
; *
; * \return CRC result in ACC
; */   
      .def _getCRC32_vcu

_getCRC32_vcu:
	  PUSH		  XAR0
	  PUSH		  XAR1
      MOVZ        AR0, *-SP[7]       ; load rxLen
	  ADDB        SP, #4              ; allocate 4 words for local
      VMOV32      *-SP[2], VCRC       ; Store current CRC
      VCRCCLR    
      MOVL        *-SP[4], ACC
      VMOV32      VCRC,*-SP[4]        ; VCRC = Inital value
      MOV         AL, AR5              ; check the parity       
      SBF         _CRC32_loop_prep, EQ
      VCRC32H_1   *XAR4++             ; if parity=1, calculate high byte first
      DEC         AR0            
      SBF         _CRC32done, EQ
      
_CRC32_loop_prep:      
      MOV         AL, AR0
      MOV         AH, AR0
      AND         AL, #0xFFF8         ; check to see if the length is greater than 8 bytes
      BF          _CRC32_LSB,EQ
      LSR         AL, #3              ; loop in 8 bytes
      MOV         AR1, AL
      SUB         AR1, #1
      
      .align     (2)                  ; align at 32-bit boundary to remove penalty
      RPTB        _CRC32_post, AR1  ; loop for the middle part of the packet
      VCRC32L_1   *XAR4               
      VCRC32H_1   *XAR4++ 
      VCRC32L_1   *XAR4               
      VCRC32H_1   *XAR4++ 
      VCRC32L_1   *XAR4               
      VCRC32H_1   *XAR4++ 
      VCRC32L_1   *XAR4               
      VCRC32H_1   *XAR4++ 
_CRC32_post: 
      LSL         AL, #3              ; calculating remaining number of bytes
      SUB         AH, AL
      SBF         _CRC32done, EQ      ; if multiple of 8, done
      MOV         AR0, AH
_CRC32_LSB
      VCRC32L_1   *XAR4               ; if parity=0, calculate the low byte
      DEC         AR0       
      SBF         _CRC32done, EQ
      VCRC32H_1   *XAR4++
      DEC         AR0       
      SBF         _CRC32_LSB, NEQ
_CRC32done
      VMOV32       *-SP[4], VCRC        ; Store CRC
      MOVL        ACC, *-SP[4]          ; return ACC 
      VMOV32       VCRC, *-SP[2]        ; Restore VCRC
      SUBB         SP, #4               ; restore stack pointer
      POP		   XAR1
      POP		   XAR0
      LRETR

