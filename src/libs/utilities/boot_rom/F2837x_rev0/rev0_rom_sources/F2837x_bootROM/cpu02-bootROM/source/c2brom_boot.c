// TI File $Revision: /main/1 $
// Checkin $Date: August 13, 2012   11:53:46 $
//###########################################################################
//
// FILE:    c2brom_boot.c
//
// TITLE:   main boot loader file for C2-Core
//
// Functions:
//
//     
//     
//     
//
//###########################################################################
// $TI Release: F2837x Boot ROM Version 0 $
// $Release Date: Oct 1, 2013 $
//###########################################################################

#include "c2_bootrom.h"


/*variable to store MTOAIPCCOM register value*/
cur_c1c2_ipc_cmd_sts_t		 c2brom_current_c1c2_ipc;


Uint32	c2brom_status;
extern Uint32 c1c2_branch_addr;
extern Uint32	iTrap_addr;

void c2brom_handle_idle_lpm(void);


/*
 * Function to initialize C-BootROM environment
 */
void c2brom_init_boot_env()
{
	
	/*initialize current command variables to default values*/
	c2brom_current_c1c2_ipc.command = C1C2_BROM_IPC_COMMAND_ILLEGAL;
	c2brom_current_c1c2_ipc.status  = COMMAND_STATUS_INVALID;


	/* initialize iTrap address, and branch address variables to default values*/
	iTrap_addr = 0xFFFFFFFF;
	c1c2_branch_addr = 0xFFFFFFFF;

	/*set MTOABOOTSTS register to indicate that boot started*/
	c2brom_set_c2c1_boot_status(C2_BOOTROM_BOOTSTS_SYSTEM_START_BOOT);

}

void c2brom_powerup_flash_faster()
{
	uint32_t EntryAddr = 0xFFFFFFFF;

	if(CpuSysRegs.RESC.all & (SYSCTL_RESC_POR | SYSCTL_RESC_XRSN | SYSCTL_RESC_HIB))
	{
		//should we clear the reset cause here? not yet because there is no place
		//to save the status as RAM will be RAM-INIT'd in the flow down below
		  EALLOW;
		  // set RWAIT to 0x3
		  FlashCtrlRegs.FRDCNTL.bit.RWAIT = 0x3;
		  // pump is already active because of CPU1

		//save the default PSLEEP value
		//change the PSLEEP VALUE for 10MHZ...?
		//access OTP - read OTP revision or something to power up flash
		 (OTP_CPU_ID_VERSION);

		//change the PSLEEP value back to default
		//         FlashCtrlRegs.FPAC1.bit.PSLEEP =  0x860;
		  FlashCtrlRegs.FRDCNTL.bit.RWAIT = 0xF;

		  EDIS;
	}

	EntryAddr = TI_OTP_C2BROM_ESCAPE_POINT_13;
	if((EntryAddr != 0xFFFFFFFF) &&
		  (EntryAddr != 0x00000000))
	{
		  /*if OTP is programmed, then call OTP function*/
		  ((void (*)(void))EntryAddr)();
	}

}

//#################################################
// void InitDCSM(void)
//--------------------------------------------
// This function initializes code security module, until this function is executed
// all access to RAM and JTAG is blocked.
//
// Note that when this function is called by PreBoot(), stack is set to PIE RAM
//--------------------------------------------

void InitDCSM()
{
    int i = 0;
    unsigned long LinkPointer = 0;
    unsigned long *Z1_ZoneSelBlockPtr = (void *)0;
    unsigned long *Z2_ZoneSelBlockPtr = (void *)0;
    unsigned long dummy_read = 0;

    int bitpos = 28;
    int zerofound = 0;

    dummy_read = *(unsigned long *)0x703F0;         /* Dummy read of SECDC REGISTER   */

    dummy_read = *(unsigned long *)0x78000;         /* Dummy read of Z1 - LinkPointer1 */
    dummy_read = *(unsigned long *)0x78004;         /* Dummy read of Z1 - LinkPointer2 */
    dummy_read = *(unsigned long *)0x78008;         /* Dummy read of Z1 - LinkPointer3 */
    dummy_read = *(unsigned long *)0x78200;         /* Dummy read of Z2 - LinkPointer1 */
    dummy_read = *(unsigned long *)0x78204;         /* Dummy read of Z2 - LinkPointer2 */
    dummy_read = *(unsigned long *)0x78208;         /* Dummy read of Z2 - LinkPointer3 */

    dummy_read = *(unsigned long *)0x78010;         /* Dummy read of Z1 - PSWDLOCK  */
    dummy_read = *(unsigned long *)0x78210;         /* Dummy read of Z2 - PSWDLOCK  */

    dummy_read = *(unsigned long *)0x78014;         /* Dummy read of Z1 - CRCLOCK  */
    dummy_read = *(unsigned long *)0x78214;         /* Dummy read of Z2 - CRCLOCK  */

    dummy_read = *(unsigned long *)0x78018;         /* Dummy read of Z1 - JTAGLOCK  */
    dummy_read = *(unsigned long *)0x78218;         /* Dummy read of Z2 - JTAGLOCK  */

    dummy_read = *(unsigned long *)0x7801E;         /* Dummy read of Z1 - BOOTCTRL  */
    dummy_read = *(unsigned long *)0x7821E;         /* Dummy read of Z2 - BOOTCTRL  */

    LinkPointer = *(unsigned long *)0x5F000;         /* Read Z1-Linkpointer out of Z1-LINKPOINTER register */
    LinkPointer = LinkPointer << 3;                              /* Bits 31,30 and 29 as most-sigificant 0 are invalid LinkPointer options */
    while ((zerofound == 0) && (bitpos > -1))
    {
        if ((LinkPointer & 0x80000000) == 0)
        {
            zerofound = 1;
            Z1_ZoneSelBlockPtr = (unsigned long *)(0x78000 + ((bitpos + 3)*16));
        }
        else
        {
            bitpos--;
            LinkPointer = LinkPointer << 1;
        }
    }
    if (zerofound == 0)
    {
        Z1_ZoneSelBlockPtr = (unsigned long *)0x78020;
    }

    bitpos = 28;
    zerofound = 0;
    LinkPointer = *(unsigned long *)0x5F040;         /* Read Z2-Linkpointer out of Z1-LINKPOINTER register */
    LinkPointer = LinkPointer << 3;                              /* Bits 31 and 30 as most-sigificant 0 are invalid LinkPointer options */
    while ((zerofound == 0) && (bitpos > -1))
    {
        if ((LinkPointer & 0x80000000) == 0)
        {
            zerofound = 1;
            Z2_ZoneSelBlockPtr = (unsigned long *)(0x78200 + ((bitpos + 3)*16));
        }
        else
        {
            bitpos--;
            LinkPointer = LinkPointer << 1;
        }
    }
    if (zerofound == 0)
    {
        Z2_ZoneSelBlockPtr = (unsigned long *)0x78220;
    }

    /* Perform dummy reads of the Zone Select Block locations */
    for (i = 0; i < 8; i++)
    {
        dummy_read =  *Z1_ZoneSelBlockPtr;
        dummy_read =  *Z2_ZoneSelBlockPtr;
        Z1_ZoneSelBlockPtr++;
        Z2_ZoneSelBlockPtr++;
    }

//to avaoid 'set but never used' error
  dummy_read = dummy_read;

  //clear local stack before returning
  i = 0;
  LinkPointer = 0;
  Z1_ZoneSelBlockPtr = (void *)0;
  Z2_ZoneSelBlockPtr = (void *)0;
  dummy_read = 0;
  bitpos = 0;
  zerofound = 0;

}


uint16_t c2brom_evaluate_bootmode(uint16_t bootmode, uint16_t bootmode_type)
{
    if(bootmode_type == HIB_BOOT_TYPE)
    {
         if((bootmode != FLASH_BOOT) || (bootmode != RAM_BOOT))
         {
             bootmode = WAIT_BOOT;
         }
    }
    else if (bootmode_type == STAND_ALONE_BOOT_TYPE)
    {
         if(bootmode != FLASH_BOOT)
         {
             bootmode = WAIT_BOOT;
         }
    }
    else if (bootmode_type == EMU_BOOT_TYPE)
    {
        //this function is called when boot mode is
    	//read from OTP in get mode code
    	//if not flash then we default to WAIT
	   if(bootmode != FLASH_BOOT)
	   {
		   bootmode = WAIT_BOOT;
	   }

    }
    return bootmode;

}

uint16_t c2brom_read_otp_bootmode()
{
    uint16_t BootMode;

    if(DcsmRegsZ1.Z1_BOOTCTRL.bit.KEY != KEY_VAL)
    {
      /*Z1 OTP BootMode Key not programmed, look for Z2 Key*/
      if(DcsmRegsZ2.Z2_BOOTCTRL.bit.KEY != KEY_VAL)
      {
          BootMode = WAIT_BOOT;
      }
      else
      {
          BootMode = DcsmRegsZ2.Z2_BOOTCTRL.bit.BMODE;
      }
    }
    else
    {
        BootMode = DcsmRegsZ1.Z1_BOOTCTRL.bit.BMODE;
    }

    return BootMode;
}

uint32_t c2brom_system_init()
{
	uint32_t	EntryAddr = 0xFFFFFFFF;
	uint32_t    IoRestoreAddr = 0xFFFFFFFF;
	uint32_t    BootMode = 0xFFFFFFFF;


    EntryAddr = TI_OTP_C2BROM_ESCAPE_POINT_1;
    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }

    /*set C-BootROM health status to indicate that boot started*/
    c2brom_status |= C2_BOOTROM_START_BOOT;
    /*set C2TOC1BOOTSTS register to indicate that boot started*/
    c2brom_set_c2c1_boot_status(0);

    /* enable C2 NMI*/
    EALLOW;
    NmiIntruptRegs.NMICFG.bit.NMIE = 1;
    //call NMI handler here because NMIWD could be ticking
    //because of stale NMI condition that could hanve occured before
    //NMIE is set
    c2brom_handle_nmi_at_start();

    InitDCSM();

    //not to trip ECSL if the passwords are ALL_1,
    //which would be the case with fresh erased parts.
    EALLOW;
      DcsmRegsZ1.Z1_CSMKEY0 = 0xFFFFFFFF;
      DcsmRegsZ1.Z1_CSMKEY1 = 0xFFFFFFFF;
      DcsmRegsZ1.Z1_CSMKEY2 = 0xFFFFFFFF;
      DcsmRegsZ1.Z1_CSMKEY3 = 0xFFFFFFFF;
      DcsmRegsZ2.Z2_CSMKEY0 = 0xFFFFFFFF;
      DcsmRegsZ2.Z2_CSMKEY1 = 0xFFFFFFFF;
      DcsmRegsZ2.Z2_CSMKEY2 = 0xFFFFFFFF;
      DcsmRegsZ2.Z2_CSMKEY3 = 0xFFFFFFFF;
    EDIS;

    c2brom_status |= C2_BOOTROM_DCSM_INIT_DONE;
    /*set C2TOC1BOOTSTS register to indicate that boot started*/
    c2brom_set_c2c1_boot_status(0);

	EntryAddr = TI_OTP_C2BROM_ESCAPE_POINT_2;
	if((EntryAddr != 0xFFFFFFFF) &&
			(EntryAddr != 0x00000000))
	{
		/*if OTP is programmed, then call OTP function*/
		((void (*)(void))EntryAddr)();
	}

	c2brom_init_boot_env();

	/*check reset cause, if HWBIST then call IORESTOREADDR*/
	
	if(CpuSysRegs.RESC.bit.HIBRESETn != 0x00)
	{

		/*if CRESC.bit[1,0] == 0x00, there was no reset because of C28HWBIST*/
		EALLOW;

		EntryAddr = TI_OTP_C2BROM_ESCAPE_POINT_3;
		if((EntryAddr != 0xFFFFFFFF) &&
				(EntryAddr != 0x00000000))
		{
			/*if OTP is programmed, then call OTP function*/
			((void (*)(void))EntryAddr)();
		}

		EALLOW;
		IoRestoreAddr = CpuSysRegs.IORESTOREADDR.all;
		EDIS;
		if(IoRestoreAddr != 0x003FFFFF)	//not at its default value
		{
			((void (*)(void))IoRestoreAddr)();
		}
		EALLOW;
	}
	//clear RESC bits so that bootROM would not go into
	//a fault reset handling if it got reset for some reason
	if (CpuSysRegs.RESC.bit.POR)
	{
		//clear POR and XRSn
	    CpuSysRegs.RESC.all = (SYSCTL_RESC_POR | SYSCTL_RESC_XRSN);
	}

    if(CpuSysRegs.RESC.bit.XRSn)
    {
    	CpuSysRegs.RESC.all = SYSCTL_RESC_XRSN;
    }

	if(CpuSysRegs.RESC.bit.HWBISTn)
	{
        CpuSysRegs.RESC.all = SYSCTL_RESC_HWBIST;
	}

	EDIS;

	c2brom_status |= C2_BOOTROM_RESC_HANDLED;
    /*set C2TOC1BOOTSTS register to indicate that boot started*/
    c2brom_set_c2c1_boot_status(0);


	EntryAddr = TI_OTP_C2BROM_ESCAPE_POINT_4;
	if((EntryAddr != 0xFFFFFFFF) &&
			(EntryAddr != 0x00000000))
	{
		/*if OTP is programmed, then call OTP function*/
		((void (*)(void))EntryAddr)();
	}


	/*read RESC again*/
    if(CpuSysRegs.RESC.bit.HIBRESETn)
    {
        CpuSysRegs.RESC.all = SYSCTL_RESC_HIB; //clear hib reset
        EALLOW;
        BootMode = CpuSysRegs.HIBBOOTMODE;
        EDIS;

        //bootmode.bits7:0 = key (0x5A is valid)
        //bootmode.bits15:8 = boot mode
        //bootmode.bits16:31 = RESERVED for future
        if ((BootMode & 0xFF) == 0x5A)
        {
            //good key

            //check for validity of boot mode here - lets see???
            BootMode = c2brom_evaluate_bootmode(((BootMode & 0xFF00) >> 8),
                                                    HIB_BOOT_TYPE);
        }
        else
        {
            BootMode = SelectBootMode();
        }

    }
    else
    {
        BootMode = SelectBootMode();
    }

    sysctl_wdog_disable();

    if(BootMode == FLASH_BOOT)
    {
         EntryAddr = FLASH_ENTRY_POINT;
         //to make sure wathDOG is enabled
         sysctl_wdog_enable();

         c2brom_status |= (C2_BOOTROM_IN_FLASH_BOOT | C2_BOOTROM_BOOT_COMPLETE);
         /*set C2TOC1BOOTSTS register to indicate that boot started*/
         c2brom_set_c2c1_boot_status(0);

         return EntryAddr;
    }
   else if(BootMode == RAM_BOOT)
   {
       //to make sure wathDOG is enabled
       sysctl_wdog_enable();
       EntryAddr = RAM_ENTRY_POINT;
       return EntryAddr;
   }
   else if(BootMode == SCI_BOOT)
   {
       EntryAddr = SCI_Boot();
       return EntryAddr;
   }
   else if(BootMode == SPI_BOOT)
   {
       EntryAddr = SPI_Boot();
       return EntryAddr;
   }
   else if(BootMode == I2C_BOOT)
   {
       EntryAddr = I2C_Boot();
       return EntryAddr;
   }
   else if(BootMode == PARALLEL_BOOT)
   {
       EntryAddr = Parallel_Boot();
       return EntryAddr;
   }
   else if((BootMode == CAN_BOOT) || ((BootMode == CAN_BOOT_TEST)))
   {
       EntryAddr = DCAN_Boot(BootMode);
       return EntryAddr;
   }

   else
   {
        //continue boot - get into IDLE mode
   };

    /*enable PIE*/

    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    c2brom_init_pie_control();

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    c2brom_init_pie_vect_table();

    /*install interrupt handlers for MTOCIPCINT1 and ATOCIPCINT1 and iTRAP ISR*/

    EALLOW;

    PieVectTable.NMI_INT = &c2brom_handle_nmi;
    PieVectTable.ILLEGAL_INT = &c2brom_itrap_isr;
    PieVectTable.CIPC1_INT = &c2brom_c1c2_ipc_int1_isr;

    /*Configure IDLE Low Power Mode*/
    CpuSysRegs.LPMCR.bit.LPM = 0x0000;  // LPM mode = Idle

    /*enable MTOCIPCINT1*/
    //PieCtrlRegs.PIEIER11.bit.INTx1 = 1;
    PieCtrlRegs.PIEIER1.bit.INTx13 = 1;


    /*enable PIE*/
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

    /*enable interrupt 1 for IPC interrupts*/
    IER |= 0x0001;
    EDIS;
    EINT;

	/*set BOOTSTS register to indicate that boot started*/
	c2brom_set_c2c1_boot_status(C2_BOOTROM_BOOTSTS_SYSTEM_READY);
	
	c2brom_handle_idle_lpm();

    return EntryAddr;	//should never reach here
}

/*function called to put CPU in IDLE mode
 */
void c2brom_handle_idle_lpm(void)
{
	sysctl_wdog_disable();

	asm(" ESTOP0"); //when connected to debugger stop here

	while(1)
	{
		asm(" IDLE");                            // Device waits in IDLE until interrupts
	}/*while(1)*/
}
 
