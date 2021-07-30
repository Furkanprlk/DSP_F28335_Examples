;
;   Spectrum Digital Test code for EVM320C240
;   Copyright (c) 1997.
;   Spectrum Digital, Inc.
;   ALL RIGHTS RESERVED
;
;
;   RTXC assembly language code, vectors for test code on EVM320C240
;       
    .ref    _bad_trap   ; illegal trap
	.ref   	_c_int0     ; entry point to the code
	.ref    _c_int2     ; timer interrupt

	.global	_vector

                            ; also check the conditional compile in
                            ; scidrv.c and scidrv.h

	.sect	"vectors"
_vector: 
RSVECT      B    _c_int0    ; PM 0  Reset Vector            1
INT1	  	B    _bad_trap	; PM 2	Int level 1		4
INT2	  	B    _c_int2	; PM 4	Int level 2		5
INT3	  	B    _bad_trap	; PM 6	Int level 3		6
INT4	  	B    _bad_trap	; PM 8	Int level 4		7
INT5	  	B    _bad_trap	; PM A	Int level 5		8
INT6	  	B    _bad_trap	; PM C	Int level 6		9
RESERVED        B    _bad_trap  ; PM E  (Analysis Int)         10
SW_INT8   	B    _bad_trap	; PM 10  	User S/W int	-
SW_INT9   	B    _bad_trap	; PM 12  	User S/W int	-
SW_INT10  	B    _bad_trap	; PM 14  	User S/W int	-
SW_INT11  	B    _bad_trap	; PM 16  	User S/W int	-
SW_INT12  	B    _bad_trap	; PM 18  	User S/W int	-
SW_INT13  	B    _bad_trap	; PM 1A  	User S/W int	-
SW_INT14  	B    _bad_trap	; PM 1C  	User S/W int	-
SW_INT15  	B    _bad_trap	; PM 1E  	User S/W int	-
SW_INT16  	B    _bad_trap	; PM 20  	User S/W int	-
TRAP	  	B    _bad_trap	; PM 22  	Trap vector	-
NMI		B    _bad_trap	; PM 24 	Non maskable int
EMU_TRAP  	B    _bad_trap	; PM 26  	Emulator Trap	2
SW_INT20  	B    _bad_trap	; PM 28  	User S/W int	-
SW_INT21  	B    _bad_trap	; PM 2A  	User S/W int	-
SW_INT22  	B    _bad_trap	; PM 2C  	User S/W int	-
SW_INT23  	B    _bad_trap	; PM 2E  	User S/W int	-

        .end             
                         
