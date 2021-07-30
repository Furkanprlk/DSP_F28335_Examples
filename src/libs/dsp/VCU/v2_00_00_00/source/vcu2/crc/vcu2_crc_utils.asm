;;*****************************************************************************
;;! \file source/vcu2/vcu2_crc_utils.asm
;;!
;;! \brief  8-bit CRC
;;
;;  \date   Oct 8, 2012
;;! 
;;
;;  Group:            C2000
;;  Target Family:    F2837x
;;
;; (C)Copyright 2012, Texas Instruments, Inc.
;;*****************************************************************************
;;$TI Release: C28x VCU Library Version v2.00.00.00 $
;;$Release Date: Dec 6, 2013 $
;;*****************************************************************************
;;
;;*****************************************************************************
;; includes
;;*****************************************************************************
;;
;;*****************************************************************************
;; global defines
;;*****************************************************************************
;; CRC Routine defines


;;*****************************************************************************
;; macros
;;*****************************************************************************

;;*****************************************************************************
;; globals
;;*****************************************************************************
    .global _CRC_reset
;;*****************************************************************************
;; function definitions
;;*****************************************************************************
    .text

;; \brief Workaround to the silicon issue of first VCU calculation on power up being
;; erroneous
;; 
;; Details Due to the internal power-up state of the VCU module, it is possible 
;; that the first CRC result will be incorrect. This condition applies to the 
;; first result from each of the eight CRC instructions. 
;; This rare condition can only occur after a power-on reset, but will not
;; necessarily occur on every power on. A warm reset will not cause this condition 
;; to reappear.
;; Workaround(s) The application can reset the internal VCU CRC logic by 
;; performing a CRC calculation of a single byte in the initialization routine. 
;; This routine only needs to perform one CRC calculation and can use any of the 
;; CRC instructions
;; 
;; 
_CRC_reset:
    MOVB      XAR7, #0
    VCRC8L_1  *XAR7
    VCRCCLR
    LRETR

;; End of file
