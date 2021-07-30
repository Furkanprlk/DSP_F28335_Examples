;; TI File $Revision: /main/1 $
;; Checkin $Date: August 13, 2012   11:53:42 $
;;###########################################################################
;;
;; FILE:    c1brom_Init_Boot.asm
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
;; $TI Release: F2837X Boot ROM V1.0 $
;; $Release Date: November 1, 2012 $
;;###########################################################################

    .global _InitBoot
    .ref _c1brom_system_init
	.ref _c1brom_handle_fuse_err_if_any
    .ref _c1brom_configure_device_for_fast_boot
    .ref _c1brom_device_config
    .ref _sysctl_wdog_disable
;    .ref _deviceCal

	.sect ".bist_signature"
	.global c1_bist_signatures_base

c1_bist_signatures_base:		
								;; 99% coverage
	.long	0xb118ff21 			;;c28x_bist_signature1_bits_31_0:
	.long	0xaad1c534  		;;c28x_bist_signature1_bits_63_32:
	.long	0xf3c29406  		;;c28x_bist_signature1_bits_95_64:
	.long	0xaa4ea0e6  		;;c28x_bist_signature1_bits_127_96:
	.long	0xc2008cdd 			;;c28x_bist_signature1_bits_159_128:
	.long	0x48dff8ed  		;;c28x_bist_signature1_bits_192_160:
	.long	0x2ce37ad1  		;;c28x_bist_signature1_bits_223_192:
	.long	0xaf0f02ba  		;;c28x_bist_signature1_bits_255_224:
	.long	0x2739afc0			;;c28x_bist_signature1_bits_287_256:
	.long	0x5977869f 			;;c28x_bist_signature1_bits_319_288:
	.long	0x92af9366 			;;c28x_bist_signature1_bits_351_320:
	.long	0x323cfebe 			;;c28x_bist_signature1_bits_383_352:
	.long	0xf8efbcb1			;;c28x_bist_signature1_bits_415_384:
	.long	0xe76ce166 			;;c28x_bist_signature1_bits_447_416:
	.long	0x84c38125 			;;c28x_bist_signature1_bits_479_448:
	.long	0xe80932f3 			;;c28x_bist_signature1_bits_511_480:

								;; 95% coverage
	.long	0xed486881 			;;c28x_bist_signature2_bits_31_0:
	.long	0x6046b177  			;;c28x_bist_signature2_bits_63_32:
	.long	0x9c0d6cfa  			;;c28x_bist_signature2_bits_95_64:
	.long	0xa0073876  			;;c28x_bist_signature2_bits_127_96:
	.long	0xb0970d09 			;;c28x_bist_signature2_bits_159_128:
	.long	0x626890cb  			;;c28x_bist_signature2_bits_192_160:
	.long	0xc31dfc59  			;;c28x_bist_signature2_bits_223_192:
	.long	0x6d54176f  			;;c28x_bist_signature2_bits_255_224:
	.long	0x16d6d787			;;c28x_bist_signature2_bits_287_256:
	.long	0xc3787dc3 			;;c28x_bist_signature2_bits_319_288:
	.long	0x4ee3e09b 			;;c28x_bist_signature2_bits_351_320:
	.long	0xaa8e8df4 			;;c28x_bist_signature2_bits_383_352:
	.long	0xb66f6261			;;c28x_bist_signature2_bits_415_384:
	.long	0xf78d1893 			;;c28x_bist_signature2_bits_447_416:
	.long	0xeb38773b 			;;c28x_bist_signature2_bits_479_448:
	.long	0x55ee198f 			;;c28x_bist_signature2_bits_511_480:
 	
 	.sect ".test_signature1"
 	.long   0xFFFFFF81			;;~(*(0x3FFFFE)) - used for production testing

    .sect ".Version"
    .global	_c1brom_version
c1brom_version:
    .word 0x0101     ; Boot ROM Version v1.1
    .word 0x0114     ; Month/Year: (ex: 0x0109 = 1/09 = Jan 2009)

;	.sect ".otp_entry_points"
;	.global	_otp_func_refs
;_otp_func_refs:
;	.ref 	_ccore_brom_otp_dummy_branch_begin_boot
;	.long 	_ccore_brom_otp_dummy_branch_begin_boot
;	.ref 	_ccore_brom_otp_dummy_branch_end_boot
;	.long 	_ccore_brom_otp_dummy_branch_end_boot
;	.ref 	_ccore_brom_otp_pie_vector_mismatch_handler
;	.long 	_ccore_brom_otp_pie_vector_mismatch_handler
;	.ref 	_ccore_brom_otp_unsupported_bmode_handler
;	.long 	_ccore_brom_otp_unsupported_bmode_handler
;	.ref 	_ccore_brom_otp_hw_bist_reset_handler
;	.long 	_ccore_brom_otp_hw_bist_reset_handler
;	.ref 	_I2C_gpio_init_for_boot
;	.long 	_I2C_gpio_init_for_boot
;	.ref 	_SCI_gpio_init_for_boot
;	.long 	_SCI_gpio_init_for_boot
;	.ref 	_SPI_gpio_init_for_boot
;	.long 	_SPI_gpio_init_for_boot
;	.ref	_SPI_alt_gpio_init_for_boot
;	.long	_SPI_alt_gpio_init_for_boot

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
;; calcualte the Count for 75 uS at 15/4 MHz untrimmed clock, with buffer
;. This would result in 83uS blank window for count of 311
    MOV     @T,#311
    RPT      @T
    ||NOP

;    MOV     @T,#56
;   RPT      @T
;    ||NOP

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
; for debug
;	SB 0, UNC
c1brom_hwbist_resc_check:
;	ADDB         SP, #4
;Uint32  EntryAddr = 0xFFFFFFFF;
;	MOVB         ACC, #0
;	SUBB         ACC, #1
;	MOVL         *-SP[2], ACC
;57         Uint32  hw_bist_addr = 0xFFFFFFFF;
;	MOVB         ACC, #0
;	SUBB         ACC, #1
;	MOVL         *-SP[4], ACC
; 59         if((CpuSysRegs.RESC.bit.HWBISTn) & 0x1)
	MOVW         DP, #0x174e
	AND          AL, @0x0, #0x20
	LSR          AL, 5

	TBIT         @AL, #0x0
	SBF          c1brom_hwbist_resc_done, NTC
; 61             EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_8;
	MOVL         XAR4, #0x703DE
;	MOVL         ACC, *+XAR4[0]
;	MOVL         *-SP[2], ACC
	MOVL         XAR5, *+XAR4[0]
; 62             if((EntryAddr != 0xFFFFFFFF) && (EntryAddr != 0x00000000))
	MOVB         ACC, #0
	SUBB         ACC, #1
;	CMPL         ACC, *-SP[2]
	CMPL         ACC, XAR5
	SBF          c1brom_hwbist_resc_no_escape, EQ
;	MOVL         ACC, *-SP[2]
	MOVL         ACC, XAR5
	SBF          c1brom_hwbist_resc_no_escape, EQ
; 66                 ((void (*)(void))EntryAddr)();
;	MOVL         XAR7, *-SP[2]
;	LCR          *XAR7
	LCR          *XAR5
c1brom_hwbist_resc_no_escape:
; Accumualtor = HwbistRegs.CSTCRET.all;
	EALLOW
	MOVW		DP, #0x1780
	MOVL		ACC, @0x34
	SBF			c1brom_hwbist_resc_done, EQ	; check if not ZERO
	MOVL		XAR5, ACC
	SPM			#0
	LCR			*XAR5

; 76     }
c1brom_hwbist_resc_done:
;	SUBB         SP, #4

;	LCR _c1brom_handle_fuse_err_if_any
	MOVW         DP, #0x1741
	MOVL         ACC, @0x34
	SBF          c1brom_fuseerr_nope, EQ
	MOVB         ACC, #21
	CMPL         ACC, @0x34
	SBF          c1brom_fuseerr_reset, NEQ
	SB           c1brom_fuseerr_nope, UNC
; 37     	EALLOW;
c1brom_fuseerr_reset:
	EALLOW
; 38     	WdRegs.WDCR.all = 0x028;
	MOVW         DP, #0x1c0
	MOVB         @0x29, #0x28, UNC
; 39     	EDIS;
	EDIS
	ESTOP0			; to let execution stop here when debugger is connected
; 40     	while(1);
	SB           0, UNC
c1brom_fuseerr_nope:
; disable WDOG, else we need to keep it feeding
c1brom_disable_wdog:
	EALLOW
; 38     	WdRegs.WDCR.all = 0x028; - to enable WDOG
;    	WdRegs.WDCR.all = 0x068; - to disable WDOG
	MOVW         DP, #0x1c0
	MOVB         @0x29, #0x68, UNC
; 39     	EDIS;//get the WDOG enable code in assembly
	EDIS

; check reset cause

; if NOT debugger or SCC reset

	; change SYSDIVSEL to /1

	; change PSLEEP for 10 MHZ

	; read OTP to power up flash

	; restore default PSLEEP

; OTP PMM TRIM LOAD
; see if we will enable PLL
; end if
	LCR _c1brom_configure_device_for_fast_boot

; OTP device Config
	LCR _c1brom_device_config

; check reset cause

;119     {
c1brom_handle_ram_inits:
;124         if(CpuSysRegs.RESC.all & (SYSCTL_RESC_POR | SYSCTL_RESC_XRSN ))
	MOVW         DP, #0x174e
	MOVL         ACC, @0x0
	MOVB         AH, #0x0
	ANDB         AL, #0x3
	TEST         ACC
	SBF          c1brom_ram_init_for_hib_resc, EQ
;127             EALLOW;
	EALLOW
;129             MemCfgRegs.DxINIT.all = 0x000F;// bit0-M0, 1-M1,2-D0,3-D1
	MOVB         ACC, #15
	MOVW         DP, #0x17d0
	MOVL         @0x12, ACC
;130             MemCfgRegs.LSxINIT.all = 0x003F;    //LS0 - LS5
	MOVB         ACC, #63
	MOVL         @0x32, ACC
;    *(int *)0x5F452 =0xFFFF;      /* RAM INIT FOR GS0..GS15 Memory    */
	MOVW         DP, #0x17d1
	MOV          ACC, #0xFFFF
	MOVL         @0x12, ACC

;163                 MemCfgRegs.MSGxINIT.all = 0x0007;
	MOVB         ACC, #7
	MOVL         @0x32, ACC
;133             EDIS;
	EDIS
ram_init_wait1:						;; wait 2048 + 32(=buffer)cycles for RAM init to complete
    MOV     @T,#2080
    RPT      @T
    ||NOP
;137         }
	SB           c1brom_handle_ram_inits_done, UNC
;138         else if((CpuSysRegs.RESC.bit.HIBRESETn /*sysctl_reset_cause_check(SYSCTL_RESC_HIB)*/) == true) {
c1brom_ram_init_for_hib_resc:
	AND          AL, @0x0, #0x40
	LSR          AL, 6
	CMPB         AL, #0x1
	SBF          stack_init, NEQ
;140             if((CpuSysRegs.LPMCR.bit.M0M1MODE == 0x01) || (CpuSysRegs.LPMCR.bit.M0M1MODE == 0x3)) {
	MOVW         DP, #0x174d
	MOV          AL, @0x37
	ANDB         AL, #0x3
	CMPB         AL, #0x1
	SBF          c1brom_all_ram_init_for_hib_resc, EQ
	MOV          AL, @0x37
	ANDB         AL, #0x3
	CMPB         AL, #0x3
	SBF          c1brom_skip_mx_ram_init_for_hib_resc, NEQ
;142                 EALLOW;
c1brom_all_ram_init_for_hib_resc:
	EALLOW
;146                 MemCfgRegs.DxINIT.all = 0x000F;// bit0-M0, 1-M1,2-D0,3-D1
	MOVB         ACC, #15
	MOVW         DP, #0x17d0
	MOVL         @0x12, ACC
;147                 MemCfgRegs.LSxINIT.all = 0x003F;    //LS0 - LS5
	MOVB         ACC, #63
	MOVL         @0x32, ACC
;    *(int *)0x5F452 =0xFFFF;      /* RAM INIT FOR GS0..GS15 Memory    */
	MOVW         DP, #0x17d1
	MOV          ACC, #0xFFFF
	MOVL         @0x12, ACC
;163                 MemCfgRegs.MSGxINIT.all = 0x0007;
	MOVB         ACC, #7
	MOVL         @0x32, ACC
;150                 EDIS;
	EDIS
ram_init_wait2:						;; wait 2048 + 32(=buffer)cycles for RAM init to complete
    MOV     @T,#2080
    RPT      @T
    ||NOP
;154             }
	SB           c1brom_handle_ram_inits_done, UNC
;157                 EALLOW;
c1brom_skip_mx_ram_init_for_hib_resc:
	EALLOW
;160                 MemCfgRegs.DxINIT.all = 0x000C;// bit0-M0, 1-M1,2-D0,3-D1
	MOVB         ACC, #12
	MOVW         DP, #0x17d0
	MOVL         @0x12, ACC
;161                 MemCfgRegs.LSxINIT.all = 0x003F;    //LS0 - LS5
	MOVB         ACC, #63
	MOVL         @0x32, ACC

;    *(int *)0x5F452 =0xFFFF;      /* RAM INIT FOR GS0..GS15 Memory    */
	MOVW         DP, #0x17d1
	MOV          ACC, #0xFFFF
	MOVL         @0x12, ACC
;163                 MemCfgRegs.MSGxINIT.all = 0x0007;
	MOVB         ACC, #7
	MOVL         @0x32, ACC
;164                 EDIS;
	EDIS
ram_init_wait3:						;; wait 2048 + 32(=buffer)cycles for RAM init to complete
    MOV     @T,#2080
    RPT      @T
    ||NOP
;170     }
	SB           c1brom_handle_ram_inits_done, UNC

stack_init:							;; here means this is not POR, so just zero out the stack, 128 words
	MOV          AL, #0xE0
	MOV			 AH, #0
ram_zero_loop:
	MOV          *SP++,#0		;;zero stack
	SUBB		 ACC, #1
	BF			 ram_zero_loop,GEQ
stack_init_done:
    MOV SP, #__stack ; re-Initalize the stack pointer

c1brom_handle_ram_inits_done: ; C$L9:
; Start C-bootROM
    MOVW DP,#0   ; Initialize DP to point to the low 64 K
    CLRC OVM

; Set PM shift of 0

    SPM 0

	LCR	_c1brom_system_init

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
