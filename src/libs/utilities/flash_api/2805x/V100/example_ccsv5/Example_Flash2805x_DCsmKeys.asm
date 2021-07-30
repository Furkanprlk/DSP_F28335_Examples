;//###########################################################################
;//
;// FILE:  Example_Flash2805x_DCsmKeys.asm	
;//
;// TITLE: F2805x Dual Code Security Module Keys for
;//        the Flash API example
;//
;// NOTE:  
;//###########################################################################
;// $TI Release: F2805x API Release V1.00 $
;// $Release Date: $
;//###########################################################################

; Use this file to pass key values to the Example Flash program
; to unlock the Code Security module before attempting to erase,
; program or verify the part. 


          .global _Z1_PRG_key0
          .global _Z1_PRG_key1
          .global _Z1_PRG_key2
          .global _Z1_PRG_key3

          .global _Z2_PRG_key0
          .global _Z2_PRG_key1
          .global _Z2_PRG_key2
          .global _Z2_PRG_key3


; For erased flash the password locations will all be 0xFFFF       
           .text                         
_Z1_PRG_key0  .long 0xFFFFFFFF  ; PSWD bits 31-0 Zone1
_Z1_PRG_key1  .long 0xFFFFFFFF  ; PSWD bits 63-32
_Z1_PRG_key2  .long 0xFFFFFFFF  ; PSWD bits 95-64
_Z1_PRG_key3  .long 0xFFFFFFFF  ; PSWD bits 127-96

_Z2_PRG_key0  .long 0xFFFFFFFF  ; PSWD bits 31-0 Zone2
_Z2_PRG_key1  .long 0xFFFFFFFF  ; PSWD bits 63-32
_Z2_PRG_key2  .long 0xFFFFFFFF  ; PSWD bits 95-64
_Z2_PRG_key3  .long 0xFFFFFFFF  ; PSWD bits 127-96
                           
                           
                           
                           
