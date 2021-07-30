//###########################################################################
// FILE:   c1brom_boot.c
// TITLE:  F28X7x Boot ROM Sources.
//
//! \addtogroup
//! <h1>  </h1>
//!
//! CPU1 Boot ROM main Source file
//!
//
//###########################################################################
// $TI Release: F2837x Boot ROM Version 0 $
// $Release Date: Oct 1, 2013 $
//###########################################################################


//the below line should start at line 18 for source level debug
#include "c1_bootrom.h"

/*variable to store MTOAIPCCOM register value*/
cur_c2c1_ipc_cmd_sts_t		 c1brom_current_c2c1_ipc;

Uint32	c1brom_status;
extern Uint32	iTrap_addr;

void WaitBoot(void);

void c1brom_change_clock_dividers_powerup_flash()
{
        EALLOW;

        // set the 1.6 multiplier bit
        AnalogSubsysRegs.INTOSC1CSR.bit.OSCCONFIG |= 0x2;
        // --NEED 20 uS settling time after the bit is written with 5-15 MHz clock

        asm(" MOV	@T,#90 ");
		asm(" RPT	@T \ 
				||NOP ");

		//set the divider to /1 to make flash init faster
		ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = 0;


		ClkCfgRegs.SYSPLLMULT.bit.IMULT = 12;
        ClkCfgRegs.SYSPLLCTL1.bit.PLLEN = 0x1;

        // set RWAIT to 0x3
        FlashCtrlRegs.FRDCNTL.bit.RWAIT = 0x3;
        //save the default PSLEEP value
        //change the PSLEEP VALUE for (15 * 1.6) MHZ...?
        FlashCtrlRegs.FPAC1.bit.PSLEEP = 0x120;

        //access OTP - read OTP revision or something to power up flash
        OTP_CPU_ID_VERSION;
        //change the PSLEEP value back to default

        FlashCtrlRegs.FPAC1.bit.PSLEEP = 0x860;
        FlashCtrlRegs.FRDCNTL.bit.RWAIT = 0xF;

        EDIS;

}

void c1brom_pmm_trim_config()
{

	if(TI_OTP_PMM_LC_TRIM_KEY != 0x5A5A)
		return;

	EALLOW;
	AnalogSubsysRegs.PMMREFTRIM.all = TI_OTP_PMM_LC_BGSLOPE_VAL_IREF_TRIM;
	AnalogSubsysRegs.PMMVREGTRIM.all = TI_OTP_PMM_LC_VREG_TRIM;		//this loads both VSINK and VREG and VREG2 TRIM
	AnalogSubsysRegs.PMMVMONTRIM.all = TI_OTP_PMM_LC_VMON_TRIM;
    EDIS;

	if(CpuSysRegs.RESC.all & (SYSCTL_RESC_POR | SYSCTL_RESC_XRSN))
	{
        // calculate the Count for 75 uS at 10MHz +/- 7% MHz efuse trimmed clock, with buffer
        // which is 1385, This would result in 81uS blank window

		//on Hibernate the blanking window will be at HIB RESC clearing
		asm(" MOV	@T,#1385 ");
		asm(" RPT	@T \ 
				||NOP ");
	}



}

void c1brom_intosc_trim_config()
{
	if(TI_OTP_OSC_TRIM_KEY != 0x5A5A)
		return;

	EALLOW;
	AnalogSubsysRegs.OSCREFTRIM.all = TI_OTP_OSC_REF_TRIM;
	AnalogSubsysRegs.INTOSC1TRIM.all = TI_OTP_OSC1_TRIM;
	AnalogSubsysRegs.INTOSC2TRIM.all = TI_OTP_OSC2_TRIM;
	EDIS;

}

void c1brom_enable_pll_ouput_to_clock()
{
	if(((OTP_BOOT_CONFIGURE_WORD & 0xFF000000) >> 24) != 0x5A) //simply return if key match fails
	{
		return;
	}

	if(((OTP_BOOT_CONFIGURE_WORD & 0x3) == 0x1) && (ClkCfgRegs.SYSPLLSTS.bit.LOCKS == 1))
	{
			EALLOW;
			ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = ((OTP_BOOT_CONFIGURE_WORD & 0x00FC) >> 2); //0x1; //set it to /2 before enabling PLL
			//if bits 1:0 of OTP_BOOT_CONFIGURE_WORD are equal to 01b then enable PLL else NO
			ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 1;
			EDIS;
	}
}

void c1brom_configure_device_for_fast_boot()
{
	uint32_t EntryAddr = 0xFFFFFFFF;

    if(CpuSysRegs.RESC.all & (SYSCTL_RESC_POR | SYSCTL_RESC_XRSN |
                                SYSCTL_RESC_HIB))
    {
    	//change dividers, set 1.6 multiplier, power up PLL, modify RWAIT and PSLEEP and wake up flash
    	c1brom_change_clock_dividers_powerup_flash();

    	c1brom_pmm_trim_config();

    	c1brom_enable_pll_ouput_to_clock();
    }

	EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_11;
	if((EntryAddr != 0xFFFFFFFF) &&
			(EntryAddr != 0x00000000))
	{
		/*if OTP is programmed, then call OTP function*/
		((void (*)(void))EntryAddr)();
	}

}


void c1brom_device_config()
{
	//PARTIDL
	DevCfgRegs.PARTIDL = TI_OTP_PARTID_L;
	DevCfgRegs.PARTIDH.all = TI_OTP_PARTID_H;	//should we write only PARTIDH bits?

	//DC0 to DC20
    DevCfgRegs.DC0.all = TI_OTP_REG_DC00;
    DevCfgRegs.DC1.all = TI_OTP_REG_DC01;
    DevCfgRegs.DC2.all = TI_OTP_REG_DC02;
    DevCfgRegs.DC3.all = TI_OTP_REG_DC03;
    DevCfgRegs.DC4.all = TI_OTP_REG_DC04;
    DevCfgRegs.DC5.all = TI_OTP_REG_DC05;
    DevCfgRegs.DC6.all = TI_OTP_REG_DC06;
    DevCfgRegs.DC7.all = TI_OTP_REG_DC07;
    DevCfgRegs.DC8.all = TI_OTP_REG_DC08;
    DevCfgRegs.DC9.all = TI_OTP_REG_DC09;
    DevCfgRegs.DC10.all = TI_OTP_REG_DC10;
    DevCfgRegs.DC11.all = TI_OTP_REG_DC11;
    DevCfgRegs.DC12.all = TI_OTP_REG_DC12;
    DevCfgRegs.DC13.all = TI_OTP_REG_DC13;
    DevCfgRegs.DC14.all = TI_OTP_REG_DC14;
    DevCfgRegs.DC15.all = TI_OTP_REG_DC15;
//    DevCfgRegs.DC16.all = TI_OTP_REG_DC16; - This is reserved
    DevCfgRegs.DC17.all = TI_OTP_REG_DC17;
    DevCfgRegs.DC18.all = TI_OTP_REG_DC18;
    DevCfgRegs.DC19.all = TI_OTP_REG_DC19;
    DevCfgRegs.DC20.all = TI_OTP_REG_DC20;

    //PERCNF1
    DevCfgRegs.PERCNF1.all = TI_OTP_REG_PERCNF1;

}


/*
 * Function to initialize C-BootROM environment
 */
void c1brom_init_boot_env()
{

	/*set C-BootROM health status to indicate that boot started*/
	c1brom_status |= C1_BOOTROM_START_BOOT;
	
	/*initialize current command variables to default values*/
	c1brom_current_c2c1_ipc.command = C2C1_BROM_IPC_COMMAND_ILLEGAL;
	c1brom_current_c2c1_ipc.status  = COMMAND_STATUS_INVALID;

	/* initialize iTrap address, and branch address variables to default values*/
	iTrap_addr = 0xFFFFFFFF;

}


//Read the GPyDAT register bit for the specified pin.
uint16_t c1brom_GPIO_ReadPin(uint16_t pin)
{
    volatile uint32_t *gpioDataReg = (void *)0;
    uint16_t pinVal = 0;

    gpioDataReg = (volatile uint32_t *)&GpioDataRegs + (pin/32)*GPY_DATA_OFFSET;
    pinVal = (gpioDataReg[GPYDAT] >> (pin % 32)) & 0x1;

    return pinVal;
}

//Set the GPyDAT register bit for the specified pin.
void c1brom_GPIO_WritePin(uint16_t pin, uint16_t outVal)
{
    volatile uint32_t *gpioDataReg = (void *)0;
    uint32_t pinMask = 0;

    gpioDataReg = (volatile uint32_t *)&GpioDataRegs + (pin/32)*GPY_DATA_OFFSET;
    pinMask = 1 << (pin % 32);

    if (outVal == 0)
        gpioDataReg[GPYCLEAR] = pinMask;
    else
        gpioDataReg[GPYSET] = pinMask;
}

uint16_t c1brom_read_otp_bootpinconfig()
{
    uint16_t pinconfig = 0;

    if(DcsmRegsZ1.Z1_BOOTCTRL.bit.KEY != KEY_VAL)
    {
      /*Z1 OTP BootMode Key not programmed, look for Z2 Key*/
      if(DcsmRegsZ2.Z2_BOOTCTRL.bit.KEY != KEY_VAL)
      {
          pinconfig = 0x0;
      }
      else
      {
          pinconfig = ((DcsmRegsZ2.Z2_BOOTCTRL.bit.BOOTPIN1 << 8)
                  | (DcsmRegsZ2.Z2_BOOTCTRL.bit.BOOTPIN0));
      }
    }
    else
    {
        pinconfig = ((DcsmRegsZ1.Z1_BOOTCTRL.bit.BOOTPIN1 << 8)
                | (DcsmRegsZ1.Z1_BOOTCTRL.bit.BOOTPIN0));
    }

    return pinconfig;
}

uint16_t c1brom_read_otp_bootmode()
{
    uint16_t BootMode = 0;

    if(DcsmRegsZ1.Z1_BOOTCTRL.bit.KEY != KEY_VAL)
    {
      /*Z1 OTP BootMode Key not programmed, look for Z2 Key*/
      if(DcsmRegsZ2.Z2_BOOTCTRL.bit.KEY != KEY_VAL)
      {
    		  BootMode = FLASH_BOOT;
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


uint16_t c1brom_decode_bootpins(uint16_t pinconfig)
{
    uint16_t bootpin0 = 0;
    uint16_t bootpin1 = 0;
    uint16_t bmode = 0;
    //default boot pins - mode0 is GPIO84, mode1 is GPIO72

    if((pinconfig &0xFF) == 0x0)
    {
        bootpin0 = 84;
    }
    else
    {
        bootpin0 = (pinconfig & 0xFF) - 1;
    }

    if(((pinconfig & 0xFF00) >> 8) == 0x0)
    {
        bootpin1 = 72;
    }
    else
    {
        bootpin1 = ((pinconfig & 0xFF00) >> 8) - 1;
    }

    if(bootpin0 > 168)
    {
    	//restrict the max pin to be used to GPIO168
    	bootpin0 = 84;
    }

    if(bootpin1 > 168)
    {
    	//restrict the max pin to be used to GPIO168
    	bootpin1 = 72;
    }

    bmode = (c1brom_GPIO_ReadPin(bootpin1) << 1);
    bmode |= c1brom_GPIO_ReadPin(bootpin0);

    return bmode;
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


uint32_t c1brom_system_init()
{
    uint32_t	EntryAddr = 0xFFFFFFFF;
	uint32_t    IoRestoreAddr = 0xFFFFFFFF;
    uint32_t    BootMode = 0xFFFFFFFF;

	EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_1;
	if((EntryAddr != 0xFFFFFFFF) &&
			(EntryAddr != 0x00000000))
	{
		/*if OTP is programmed, then call OTP function*/
		((void (*)(void))EntryAddr)();
	}

    /* enable C1 NMI*/
    EALLOW;
    NmiIntruptRegs.NMICFG.bit.NMIE = 1;
    c1brom_handle_nmi_at_start();

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

	/*set C-BootROM health status to indicate that boot started*/
	c1brom_status = C1_BOOTROM_DCSM_INIT_DONE;

    c1brom_init_boot_env();

    if(CpuSysRegs.RESC.all & (SYSCTL_RESC_POR | SYSCTL_RESC_XRSN |
                                SYSCTL_RESC_HIB))
    {
        //do the below only in this order, don;t dare to change
        EALLOW;
        // bypass PLL here
        if(ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN != 0)
        {
        	ClkCfgRegs.SYSPLLCTL1.bit.PLLCLKEN = 0;
        }
        //set PLL multiplier to 0x0
        if(ClkCfgRegs.SYSPLLMULT.bit.IMULT != 0)
        {
        	ClkCfgRegs.SYSPLLMULT.bit.IMULT = 0;
        }
        //set the divider to /1
        if(ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV != 0)
        {
        	ClkCfgRegs.SYSCLKDIVSEL.bit.PLLSYSCLKDIV = 0x0; //set it to /1
        }

        // remove the 1.6 multiplier
        AnalogSubsysRegs.INTOSC1CSR.bit.OSCCONFIG &= (~(0x2));

        EDIS;
        c1brom_intosc_trim_config();

		// calculate the Count for 12 uS at 10MHz +/- 7% MHz efuse trimmed clock, with buffer
		// This would result in 16uS blank window

		asm(" MOV	@T,#178 ");
		asm(" RPT	@T \ 
				||NOP ");

    }
    if(((*(uint32_t *)DEVICE_CAL_LOCATION) != 0xFFFFFFFF) &&
    		((*(uint32_t *)DEVICE_CAL_LOCATION) != 0x00000000))
     {
        (*C1BROM_DEVCAL)();
     }

    /*check reset cause, if HIBRESET then call IORESTOREADDR*/
    if(CpuSysRegs.RESC.bit.HIBRESETn != 0x00)
    {
    	c1brom_status |= C1_BOOTROM_HANDLED_HIBRESET;
    	EALLOW;

    	/*if CRESC.bit[1,0] == 0x00, there was no reset because of C28HWBIST*/

        EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_3;
        if((EntryAddr != 0xFFFFFFFF) &&
                (EntryAddr != 0x00000000))
        {
            /*if OTP is programmed, then call OTP function*/
            ((void (*)(void))EntryAddr)();
        }

        EALLOW;
        IoRestoreAddr = CpuSysRegs.IORESTOREADDR.all;

        if(IoRestoreAddr != 0x003FFFFF) //not at its default value
        {
        	((void (*)(void))IoRestoreAddr)();
        }

        // clear the IO Isolation here, user is supposed to clear this in IoRestoreAddr
        // function, but doesn't hurt to make sure.
        EALLOW;
		CpuSysRegs.LPMCR.bit.IOISODIS = 1;
    }

    //clear RESC bits so that bootROM would not go into
    //a unwanted reset handling if it got reset for some reason
    if (CpuSysRegs.RESC.bit.POR)
    {

    	//clear POR and XRSn
    	CpuSysRegs.RESC.all = (SYSCTL_RESC_POR | SYSCTL_RESC_XRSN);
    	c1brom_status |= (C1_BOOTROM_HANDLED_XRSN | C1_BOOTROM_HANDLED_POR);

    }

    if(CpuSysRegs.RESC.bit.XRSn)
    {

    	CpuSysRegs.RESC.all = SYSCTL_RESC_XRSN;
    	c1brom_status |= (C1_BOOTROM_HANDLED_XRSN);
    }

    if(CpuSysRegs.RESC.bit.HWBISTn)
    {
    	CpuSysRegs.RESC.all = SYSCTL_RESC_HWBIST;

    	c1brom_status |= (C1_BOOTROM_HANDLED_HWBISTRESET);
    }

    EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_4;
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
    	//PMM trims take effect here so have blanking periods now

        // calculate the Count for 75 uS at worst case clock (efuse untrimmed), with buffer
		// This would result in app 80uS blank window for count of 1200
		asm(" MOV	@T,#1200 ");
		asm(" RPT	@T \ 
				||NOP ");

	    EALLOW;
        BootMode = CpuSysRegs.HIBBOOTMODE;
        EDIS;

        EALLOW;
        //bring CPU2 out of reset
        DevCfgRegs.CPU2RESCTL.all = 0xA5A50000;
        EDIS;

        //bootmode.bits7:0 = key (0x5A is valid)
        //bootmode.bits15:8 = boot mode
        //bootmode.bits16:31 = RESERVED for future
        if ((BootMode & 0xFF) == 0x5A)
        {
            //good key
            BootMode = ((BootMode & 0xFF00) >> 8);
        }
        else
        {
            BootMode = SelectBootMode();
        }

    }
    else
    {
        EALLOW;
        //bring CPU2 out of reset
        DevCfgRegs.CPU2RESCTL.all = 0xA5A50000;

        EDIS;

    	BootMode = SelectBootMode();
    }

    c1brom_status |= C1_BOOTROM_RESC_HANDLED;

    EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_2;
    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }


    if(BootMode == FLASH_BOOT)
    {
         EntryAddr = FLASH_ENTRY_POINT;
         //to make sure wathDOG is enabled
         sysctl_wdog_enable();
         return EntryAddr;
    }

    else if(BootMode == RAM_BOOT)
    {
        EntryAddr = RAM_ENTRY_POINT;             //to make sure wathDOG is enabled
        sysctl_wdog_enable();
        return EntryAddr;
    }
    else if((BootMode == SCI_BOOT) || (BootMode == SCI_BOOT_ALTERNATE)) EntryAddr = SCI_Boot(BootMode);
    else if(BootMode == SPI_BOOT|| (BootMode == SPI_BOOT_ALTERNATE)) EntryAddr = SPI_Boot(BootMode);
    else if(BootMode == I2C_BOOT|| (BootMode == I2C_BOOT_ALTERNATE)) EntryAddr = I2C_Boot(BootMode);
    else if(BootMode == PARALLEL_BOOT) EntryAddr = Parallel_Boot();
    else if(BootMode == CAN_BOOT|| (BootMode == CAN_BOOT_TEST_DEFAULT)) EntryAddr = DCAN_Boot(BootMode);
    else if(BootMode == CAN_BOOT_ALTERNATE|| (BootMode == CAN_BOOT_TEST_ALT)) EntryAddr = DCAN_Boot(BootMode);
    else if (BootMode == USB_BOOT) EntryAddr = USB_Boot(BootMode);
    else if(CpuSysRegs.RESC.bit.TRSTn_pin_status == 0)
    {
        EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_12;
        if((EntryAddr != 0xFFFFFFFF) &&
                (EntryAddr != 0x00000000))
        {
            /*if OTP is programmed, then call OTP function*/
            ((void (*)(void))EntryAddr)();
        }

    	//if not in EMU boot mode then default to flash
       EntryAddr = FLASH_ENTRY_POINT;
    }
    else
    {
    	WaitBoot();
    }

    sysctl_wdog_enable();
    return EntryAddr;
}


void c1brom_enable_pie_in_boot(uint16_t mode)
{
    /*enable PIE*/

    // Initialize PIE control registers to their default state.
    // The default state is all PIE interrupts disabled and flags
    // are cleared.
    c1brom_init_pie_control();

    // Disable CPU interrupts and clear all CPU interrupt flags:
    IER = 0x0000;
    IFR = 0x0000;

    // Initialize the PIE vector table with pointers to the shell Interrupt
    // Service Routines (ISR).
    // This will populate the entire table, even if the interrupt
    // is not used in this example.  This is useful for debug purposes.
    c1brom_init_pie_vect_table();

    /*install interrupt handlers for MTOCIPCINT1 and ATOCIPCINT1 and iTRAP ISR*/

    EALLOW;

    PieVectTable.NMI_INT = &c1brom_handle_nmi;
    PieVectTable.ILLEGAL_INT = &c1brom_itrap_isr;

    if(mode == 1)
    {
    	PieVectTable.CIPC1_INT = &c1brom_c2c1_ipc_int1_isr;
        /*enable MTOCIPCINT1*/
        //PieCtrlRegs.PIEIER11.bit.INTx1 = 1;
        PieCtrlRegs.PIEIER1.bit.INTx13 = 1;


        /*enable interrupt 1 for IPC interrupts*/
        IER |= 0x0001;
        EINT;
    }
    EDIS;
    EINT;	//just to be safe
}

void WaitBoot(void)
{
//    sysctl_wdog_enable(); //- for debug
	if(((OTP_BOOT_CONFIGURE_WORD & 0xFF000000) >> 24) == 0x5A) //CHECK if key match fails
	{
		if(((OTP_BOOT_CONFIGURE_WORD >> 8) & 3) == 0x1)
		{
			c1brom_enable_pie_in_boot(1);
		}
	}
	else
	{
        sysctl_wdog_enable();
	}

    // If the emulator stops here
    // a) change EMU_KEY to 0x55AA
    // b) write the appropriate boot mode to EMU_BMODE
    // c) perform a debugger reset, and run
    asm("   ESTOP0");

	for(;;)
	{
	}
}
