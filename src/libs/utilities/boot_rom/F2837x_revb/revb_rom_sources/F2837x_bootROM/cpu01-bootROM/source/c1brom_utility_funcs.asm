;; TI File $Revision: /main/1 $
;; Checkin $Date: August 13, 2012   11:53:45 $
;;###########################################################################
;;
;; FILE:    cbrom_utility_functions.asm
;;
;; TITLE:   Boot Rom C callable assembly utility functions.
;;
;; Functions:
;;
;;
;; Notes:
;;
;;###########################################################################
;; $TI Release: F2837x Boot ROM V1.0 $
;; $Release Date: October 2013 $
;;###########################################################################

	.global _branch_to_entryaddress
	.global _load_itrap_address

; C-calling convention: branch_to_entryaddress (unsigned long *entryaddress)
; Parameter is stored in XAR4
; Function moves the Entry Address into the ISR return from address on the stack

_branch_to_entryaddress:
             
	MOVL  ACC, *XAR4	  ; load ACC with the desired branch address
	MOVL *-SP[30], ACC    ; move branch address to cbrom_mtoc_ipc_int1_isr return address on stack
    LRETR

; C-calling convention: load_itrap_address (unsigned long *itrapaddress)
; Parameter is stored in XAR4
; Function loads the address where the ITRAP occurred stored from the stack and
; into the address pointed to by the itrapaddress pointer.
; The stack location where the ITRAP return address is stored on the stack will change 
; according to compiler optimizations, The below value is without any optimizations - 
; if the code uses optimizations please re-check the below value
;    

_load_itrap_address:
	MOVL ACC, *-SP[30];   ; load ITRAP address location on stack into ACC
	MOVL *XAR4, ACC       ; return ITRAP address back to calling function
	LRETR
