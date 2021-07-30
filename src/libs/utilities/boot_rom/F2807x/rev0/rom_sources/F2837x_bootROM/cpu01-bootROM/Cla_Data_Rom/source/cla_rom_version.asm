;; TI File $Revision: /main/1 $
;; Checkin $Date: August 14, 2012   12:48:33 $
;;###########################################################################
;;
;; FILE:    cla_rom_version.asm
;;
;; TITLE:   CLA data ROM Version and checksum values.
;;
;; Functions:
;;
;;
;; Notes:
;;
;;###########################################################################
;; $TI Release: F2837x Boot ROM Version 0 $
;; $Release Date: Oct 1, 2013 $
;;###########################################################################

    .sect ".CROMVersion"
    .word 0x0100     ; Boot ROM Version v1.0
    .word 0x0413     ; Month/Year: (ex: 0x0109 = 1/09 = Jan 2009)

