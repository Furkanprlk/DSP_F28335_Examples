;;*****************************************************************************
;;! \file source/vcu0/vcu0_crc_utils.asm
;;!
;;! \brief  CRC Utility routines
;;
;;  \date   Apr 7, 2011
;;!
;;
;;  Group:            C2000
;;  Target Family:    F2837x
;;
;; Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/ 
;; ALL RIGHTS RESERVED
;;*****************************************************************************
;;$TI Release: C28x VCU Library Version v2.10.00.00 $
;;$Release Date: Mar 3, 2015 $
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

;
;/*! Workaround to the silicon issue of first VCU calculation on power up being
; *  erroneous
; *
; * Details Due to the internal power-up state of the VCU module, it is possible 
; * that the first CRC result will be incorrect. This condition applies to the 
; * first result from each of the eight CRC instructions. 
; * This rare condition can only occur after a power-on reset, but will not
; * necessarily occur on every power on. A warm reset will not cause this condition 
; * to reappear.
; * Workaround(s): The application can reset the internal VCU CRC logic by 
; * performing a CRC calculation of a single byte in the initialization routine. 
; * This routine only needs to perform one CRC calculation and can use any of the 
; * CRC instructions
; *
; */
      .def _CRC_reset

_CRC_reset:
      MOVB      XAR7, #0
      VCRC8L_1  *XAR7
      VCRCCLR
      LRETR

;; End of file
