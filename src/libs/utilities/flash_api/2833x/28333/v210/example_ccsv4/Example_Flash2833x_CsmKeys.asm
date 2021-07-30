;//###########################################################################
;//
;// FILE:  Example_Flash2833x_CsmKeys.asm	
;//
;// TITLE: F2833x Code Security Module Keys for
;//        the Flash API example
;//
;// NOTE:  
;//###########################################################################
;// $TI Release: F2833x API Release V1.0 $
;// $Release Date: September 14, 2007 $
;//###########################################################################

; Use this file to pass key values to the Example Flash program
; to unlock the Code Security module before attempting to erase,
; program or verify the part. 


          .global _PRG_key0
          .global _PRG_key1
          .global _PRG_key2
          .global _PRG_key3
          .global _PRG_key4
          .global _PRG_key5
          .global _PRG_key6
          .global _PRG_key7

; For erased flash the password locations will all be 0xFFFF       
           .text                         
_PRG_key0  .word 0xFFFF  ; PSWD bits 15-0
_PRG_key1  .word 0xFFFF  ; PSWD bits 31-16
_PRG_key2  .word 0xFFFF  ; PSWD bits 47-32
_PRG_key3  .word 0xFFFF  ; PSWD bits 63-48
_PRG_key4  .word 0xFFFF  ; PSWD bits 79-64   
_PRG_key5  .word 0xFFFF  ; PSWD bits 95-80   
_PRG_key6  .word 0xFFFF  ; PSWD bits 111-96   
_PRG_key7  .word 0xFFFF  ; PSWD bits 127-112   
                           
                           
                           
                           