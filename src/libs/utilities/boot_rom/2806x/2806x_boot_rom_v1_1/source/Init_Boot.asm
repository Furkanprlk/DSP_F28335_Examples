;; TI File $Revision: /main/5 $
;; Checkin $Date: March 8, 2011   15:18:33 $
;;###########################################################################
;;
;; FILE:    Init_Boot.asm
;;
;; TITLE:   Boot Rom Initialization and Exit routines.
;;
;; Functions:
;;
;;     _InitBoot
;;     _ExitBoot
;;
;; Notes:
;;
;;###########################################################################
;; $TI Release: TMS320x2806x Boot ROM V1.0 $
;; $Release Date: October 21, 2010 $
;;###########################################################################

    .global _InitBoot
    .ref _SelectBootMode

    .sect ".Flash"   ; Flash API checks this for
    .word 0xFFFE     ; silicon compatability

    .sect ".Version"
    .word 0x0101     ; Boot ROM Version v1.1
    .word 0x0111     ; Month/Year: (ex: 0x0109 = 1/09 = Jan 2009)

    .sect ".Checksum"; 64-bit Checksum
    .long 0xA71C7BB8 ; least significant 32-bits
    .long 0x00001D12 ; most significant 32-bits


    .sect ".InitBoot"

;-----------------------------------------------
; _InitBoot
;-----------------------------------------------
;-----------------------------------------------
; This function performs the initial boot routine
; for the boot ROM.
;
; This module performs the following actions:
;
;     1) Initalizes the stack pointer
;     2) Sets the device for C28x operating mode
;     3) Calls the main boot functions
;     4) Calls an exit routine
;-----------------------------------------------


_InitBoot:

; Initalize the stack pointer.

__stack:    .usect ".stack",0
    MOV SP, #__stack ; Initalize the stack pointer

; Initalize the device for running in C28x mode.

    C28OBJ       ; Select C28x object mode
    C28ADDR      ; Select C27x/C28x addressing
    C28MAP       ; Set blocks M0/M1 for C28x mode
    CLRC PAGE0   ; Always use stack addressing mode
    MOVW DP,#0   ; Initialize DP to point to the low 64 K
    CLRC OVM

; Set PM shift of 0

    SPM 0

; Decide which boot mode to use
    LCR  _SelectBootMode

; Cleanup and exit.  At this point the EntryAddr
; is located in the ACC register
    BF  _ExitBoot,UNC



;-----------------------------------------------
; _ExitBoot
;-----------------------------------------------
;-----------------------------------------------
;This module cleans up after the boot loader
;
; 1) Make sure the stack is deallocated.
;    SP = 0x400 after exiting the boot
;    loader
; 2) Push 0 onto the stack so RPC will be
;    0 after using LRETR to jump to the
;    entry point
; 2) Load RPC with the entry point
; 3) Clear all XARn registers
; 4) Clear ACC, P and XT registers
; 5) LRETR - this will also clear the RPC
;    register since 0 was on the stack
;-----------------------------------------------

_ExitBoot:

;-----------------------------------------------
;   Insure that the stack is deallocated
;-----------------------------------------------

    MOV SP,#__stack

;-----------------------------------------------
; Clear the bottom of the stack.  This will endup
; in RPC when we are finished
;-----------------------------------------------

    MOV  *SP++,#0
    MOV  *SP++,#0

;-----------------------------------------------
; Load RPC with the entry point as determined
; by the boot mode.  This address will be returned
; in the ACC register.
;-----------------------------------------------

    PUSH ACC
    POP  RPC

;-----------------------------------------------
; Put registers back in their reset state.
;
; Clear all the XARn, ACC, XT, and P and DP
; registers
;
; NOTE: Leave the device in C28x operating mode
;       (OBJMODE = 1, AMODE = 0)
;-----------------------------------------------
    ZAPA
    MOVL  XT,ACC
    MOVZ  AR0,AL
    MOVZ  AR1,AL
    MOVZ  AR2,AL
    MOVZ  AR3,AL
    MOVZ  AR4,AL
    MOVZ  AR5,AL
    MOVZ  AR6,AL
    MOVZ  AR7,AL
    MOVW  DP, #0

;------------------------------------------------
;   Restore ST0 and ST1.  Note OBJMODE is
;   the only bit not restored to its reset state.
;   OBJMODE is left set for C28x object operating
;   mode.
;
;  ST0 = 0x0000     ST1 = 0x0A0B
;  15:10 OVC = 0    15:13      ARP = 0
;   9: 7  PM = 0       12       XF = 0
;      6   V = 0       11  M0M1MAP = 1
;      5   N = 0       10  reserved
;      4   Z = 0        9  OBJMODE = 1
;      3   C = 0        8    AMODE = 0
;      2  TC = 0        7 IDLESTAT = 0
;      1 OVM = 0        6   EALLOW = 0
;      0 SXM = 0        5     LOOP = 0
;                       4      SPA = 0
;                       3     VMAP = 1
;                       2    PAGE0 = 0
;                       1     DBGM = 1
;                       0     INTM = 1
;-----------------------------------------------

    MOV  *SP++,#0
    MOV  *SP++,#0x0A0B
    POP  ST1
    POP  ST0

;------------------------------------------------
;   Jump to the EntryAddr as defined by the
;   boot mode selected and continue execution
;-----------------------------------------------

    LRETR

;eof ----------
