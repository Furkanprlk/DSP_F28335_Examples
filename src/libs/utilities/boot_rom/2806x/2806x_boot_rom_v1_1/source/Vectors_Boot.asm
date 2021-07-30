;; TI File $Revision: /main/4 $
;; Checkin $Date: March 8, 2011   15:18:39 $
;;###########################################################################
;;
;; FILE:    Vectors_Boot.h
;;
;; TITLE:   Boot Rom vector table.
;;
;; Functions:
;;
;; This section of code populates the vector table in the boot ROM.  The reset
;; vector at 0x3FFFC0 points to the entry into the boot loader functions (InitBoot())
;; The rest of the vectors are populated for test purposes only. 
;;
;;###########################################################################
;; $TI Release: TMS320x2806x Boot ROM V1.0 $
;; $Release Date: October 21, 2010 $
;;###########################################################################
;-----------------------------------------------------------
; The vector table located in boot ROM at 0x3F FFC0 - 0x3F FFFF
; will be filled with the following data. 
; 
; Only the reset vector, which points to the InitBoot
; routine will be used during normal operation.  The remaining
; vectors are set for internal testing purposes and will not be
; fetched from this location during normal operation.
; 
; On reset vector is always fetched from this table. 
;
;----------------------------------------------------------
     .ref _InitBoot
     .ref _ITRAPIsr
     .sect ".BootVecs"
     .long _InitBoot ;Reset
     .long 0x000042
     .long 0x000044
     .long 0x000046
     .long 0x000048
     .long 0x00004a
     .long 0x00004c
     .long 0x00004e
     .long 0x000050
     .long 0x000052
     .long 0x000054
     .long 0x000056
     .long 0x000058
     .long 0x00005a
     .long 0x00005c
     .long 0x00005e
     .long 0x000060
     .long 0x000062
     .long 0x000064
     .long _ITRAPIsr  ;ITRAP
     .long 0x000068
     .long 0x00006a
     .long 0x00006c
     .long 0x00006e
     .long 0x000070
     .long 0x000072
     .long 0x000074
     .long 0x000076
     .long 0x000078
     .long 0x00007a
     .long 0x00007c
     .long 0x00007e
     
