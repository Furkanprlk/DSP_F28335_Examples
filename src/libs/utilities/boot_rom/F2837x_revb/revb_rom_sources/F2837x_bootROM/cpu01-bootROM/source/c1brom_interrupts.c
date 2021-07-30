// TI File $Revision: /main/1 $
// Checkin $Date: August 13, 2012   11:53:47 $
//###########################################################################
//
// FILE:    ccore_bootrom_interrupts.c    
//
// TITLE:   B.C28x Boot ROM interrupt handlers
//
// Functions:
//
// Notes:
//
//###########################################################################
// $TI Release: F2837x Boot ROM V1.0 $
// $Release Date: October 2013 $
//###########################################################################

#include "c1_bootrom.h"

void c1brom_init_pie_control(void);
void c1brom_init_pie_vect_table(void);

void branch_to_entryaddress(Uint32 *entryaddress); 
void load_itrap_address (Uint32 *itrapaddress);

interrupt void c1brom_itrap_isr(void);
interrupt void c1brom_c2c1_ipc_int1_isr(void);
interrupt void c1brom_handle_nmi();
void c1brom_pie_vect_mismatch_handler();

extern cur_c2c1_ipc_cmd_sts_t		 c1brom_current_c2c1_ipc;
extern Uint32	c1brom_status;

volatile Uint16 c1brom_nmi_status;
Uint32	iTrap_addr;

/*
 * Function to handle unsupported PIE interrupts in C-BootROM
 */
interrupt void c1brom_pie_isr_not_supported()
{
	Uint16 interrupt_num = 0;
	Uint16 address_offset = 0;

	//PIEVECT of PIECTRL register stores the vector address from the PIE vector table from which the vector was fetched.
	// (the vector address - base address of PIE vector table)/2 gives the interrupt vector ID
	address_offset = ((PieCtrlRegs.PIECTRL.all) & (0x00000000FE));
	interrupt_num = (address_offset >> 1);

//	c1brom_send_ipc_to_master(C_BOOTROM_IPC_CTOM_PIE_INTERRUPT_NOT_SUPPORTED, 0, interrupt_num);

	/*acknowledge the interrupt; don't have to ACK interrupt nos less than 32, its done automatically by interrupt return*/
	if(interrupt_num >= 32)
	{
		/*for PIE multiplexed interrupts INT1 to INT12*/
		PieCtrlRegs.PIEACK.all |= (0x01 << ((address_offset >> 4) - 4));
	}
 
}

/*
 * Function to handle PIE vector mismatch handler in C-BootROM
 */
interrupt void c1brom_pie_vect_mismatch_handler()
{
	
	Uint32 EntryAddr = 0xFFFFFFFF;


    c1brom_status |= C1_BOOTROM_GOT_A_PIEMISMATCH;

    EALLOW;
    EntryAddr = (CpuSysRegs.PIEVERRADDR.all);
    EDIS;

    //commented out to allow debug
//    EntryAddr = TI_OTP_PIE_MISMATCH_HANDLER_EP;
//    if((EntryAddr != 0xFFFFFFFF) &&
//            (EntryAddr != 0x00000000))
//    {
//        /*do a dummy branch to OTP - if we later decide not to handler this the way done below*/
//        /*if OTP is programmed, then call OTP function*/
//        ((void (*)(void))EntryAddr)();
//    }


    if((EntryAddr != (uint32_t)0x003FFFFF))
    {
        ((void (*)(void))EntryAddr)();
    }
    else
    {
        //No need to send this as the other core has already got the NMI
    //  cbrom_send_ipc_to_master(C_BOOTROM_IPC_CTOM_PIE_VECTOR_ADDRESS_MISMATCH, 0, 0);

    //    cbrom_handle_nmi_for_pie_mismatch();

        //let watchdog reset the system, if the error happened
        //not because of NMI fetch, else NMIWD will reset the device
        if(NmiIntruptRegs.NMIFLG.all == 0x0)
        {
            sysctl_wdog_enable();
        }

        while(1);

    }

}

/*
 * Function to handle NMI interrupts in C-BootROM
 */
void c1brom_handle_nmi_at_start()
{
    uint32_t EntryAddr;

    EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_10;

    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*do a dummy branch to OTP - if we later decide not to handler this the way done below*/
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }

	/*check if NMI is triggered*/
	c1brom_nmi_status = NmiIntruptRegs.NMIFLG.all;
	do
	{
		if(c1brom_nmi_status & NMI_INT_CLOCKFAIL) /*check for CLOCKFAIL_NMI*/
		{
			c1brom_status |= C1_BOOTROM_GOT_A_MCLK_NMI;
			c1brom_nmi_status &= ~(NMI_INT_CLOCKFAIL);	/*clear bit 1*/

			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.CLOCKFAIL= 1;
			EDIS;

			c1brom_nmi_status = NmiIntruptRegs.NMIFLG.all;

			/*continue to run*/
			if((c1brom_nmi_status) == NMI_INT_FLG)
			{
				c1brom_nmi_status &= ~(NMI_INT_FLG);	/*clear bit 0*/
				/* clear the NMIINT flag and return because there is no other NMI set*/
				EALLOW;
				NmiIntruptRegs.NMIFLGCLR.bit.NMIINT = 1;
				EDIS;
				
				return;
			}
		}

		if(c1brom_nmi_status & NMI_INT_CPU1HWBISTERR) /*check for M3BISTERR NMI */
		{
			c1brom_status |= C1_BOOTROM_GOT_A_C1BISTERR_NMI;

			c1brom_nmi_status &= ~(NMI_INT_CPU1HWBISTERR);	/*clear bit 4*/
			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.CPU1HWBISTERR = 1;
			EDIS;
		}

		if(c1brom_nmi_status & NMI_INT_CPU2HWBISTERR) /*check for C28BISTERR NMI */
		{
			c1brom_status |= C1_BOOTROM_GOT_A_C2BISTERR_NMI;

			c1brom_nmi_status &= ~(NMI_INT_CPU2HWBISTERR);	/*clear bit 5*/

			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.CPU2HWBISTERR = 1;
			EDIS;
		
		}
		if(c1brom_nmi_status & NMI_INT_PIEVECTERR) /*check for AERR NMI */
		{
			c1brom_status |= C1_BOOTROM_GOT_A_PIEVECTERR_NMI;

			c1brom_nmi_status &= ~(NMI_INT_PIEVECTERR);	/*clear bit 6*/
			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.PIEVECTERR = 1;
			EDIS;
		}
        if(c1brom_nmi_status & NMI_INT_SYSDBG) /*check for PIEVECT NMI */
        {
            c1brom_status |= C1_BOOTROM_GOT_A_SYSDBG_NMI;

            c1brom_nmi_status &= ~(NMI_INT_SYSDBG);  /*clear bit 6*/
            EALLOW;
            NmiIntruptRegs.NMIFLGCLR.bit.SYSDBGNMI = 1;
            EDIS;
        }
        if(c1brom_nmi_status & NMI_INT_RL) /*check for PIEVECT NMI */
        {
            c1brom_status |= C1_BOOTROM_GOT_A_RL_NMI;

            c1brom_nmi_status &= ~(NMI_INT_RL);  /*clear bit 6*/
            EALLOW;
            NmiIntruptRegs.NMIFLGCLR.bit.RLNMI = 1;
            EDIS;
        }
        if(c1brom_nmi_status & NMI_INT_CPU2WDRST) /*check for PIEVECT NMI */
        {
            c1brom_status |= C1_BOOTROM_GOT_A_CPU2WDRST_NMI;

            c1brom_nmi_status &= ~(NMI_INT_CPU2WDRST);  /*clear bit 6*/
            EALLOW;
            NmiIntruptRegs.NMIFLGCLR.bit.CPU2WDRSn = 1;
            EDIS;
        }

        if(c1brom_nmi_status & NMI_INT_CPU2NMIWDRST) /*check for PIEVECT NMI */
        {
            c1brom_status |= C1_BOOTROM_GOT_A_CPU2WDRST_NMI;

            c1brom_nmi_status &= ~(NMI_INT_CPU2NMIWDRST);  /*clear bit 6*/
            EALLOW;
            NmiIntruptRegs.NMIFLGCLR.bit.CPU2NMIWDRSn = 1;
            EDIS;
        }

        if(c1brom_nmi_status & NMI_INT_OVF) /*check for PIEVECT NMI */
        {
            c1brom_status |= C1_BOOTROM_GOT_A_OVF_NMI;

            c1brom_nmi_status &= ~(NMI_INT_OVF);  /*clear bit 6*/
            EALLOW;
            NmiIntruptRegs.NMIFLGCLR.bit.OVF = 1;
            EDIS;
        }

        //there is a reason to check these two at the end
        //d owe really need to reset the device - can't it continue to boot?
        if(c1brom_nmi_status & NMI_INT_RAMUNCERR) /*check for C28RAMUNCERR NMI */
		{
			c1brom_status |= C1_BOOTROM_GOT_A_RAM_UNCERR_NMI;

			//if debugger connected - give a chance to user to know the scenario
			asm("   ESTOP0");
			//let NMIWD reset the device
			while(1);

//			c1brom_nmi_status &= ~(0x04);	/*clear bit 2*/
//			EALLOW;
//			NmiIntruptRegs.NMIFLGCLR.bit.C28RAMUNCERR = 1;
//			EDIS;
		}
		if(c1brom_nmi_status & NMI_INT_FLUNCERR) /*check for C28FLUNCERR NMI */
		{
			c1brom_status |= C1_BOOTROM_GOT_A_FLASH_UNCERR_NMI;

			//if debugger connected - give a chance to user to know the scenario
			asm("   ESTOP0");

            //let NMIWD reset the device
            while(1);

//			c1brom_nmi_status &= ~(0x08);	/*clear bit 3*/
//			EALLOW;
//			NmiIntruptRegs.NMIFLGCLR.bit.C28FLUNCERR = 1;
//			EDIS;
		}

		c1brom_nmi_status &= ~(0x01);	/*clear bit 0*/
		EALLOW;
		NmiIntruptRegs.NMIFLGCLR.bit.NMIINT = 1;
		EDIS;

		c1brom_nmi_status = NmiIntruptRegs.NMIFLG.all;

	}while(c1brom_nmi_status & 0x01);	/*check for NMIINT bit - bit 0*/

//	while(1);
}

/*
 * Function to handle NMI interrupts in C-BootROM
 */
interrupt void c1brom_handle_nmi()
{
    uint32_t EntryAddr;

    EntryAddr = TI_OTP_C1BROM_ESCAPE_POINT_10;

    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*do a dummy branch to OTP - if we later decide not to handler this the way done below*/
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }
	/*check if NMI is triggered*/
	c1brom_nmi_status = NmiIntruptRegs.NMIFLG.all;
	do
	{
		if(c1brom_nmi_status & NMI_INT_CLOCKFAIL) /*check for CLOCKFAIL_NMI*/
		{
			c1brom_status |= C1_BOOTROM_GOT_A_MCLK_NMI;
			c1brom_nmi_status &= ~(NMI_INT_CLOCKFAIL);	/*clear bit 1*/

			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.CLOCKFAIL= 1;
			EDIS;

			c1brom_nmi_status = NmiIntruptRegs.NMIFLG.all;

			/*continue to run*/
			if((c1brom_nmi_status) == NMI_INT_FLG)
			{
				c1brom_nmi_status &= ~(NMI_INT_FLG);	/*clear bit 0*/
				/* clear the NMIINT flag and return because there is no other NMI set*/
				EALLOW;
				NmiIntruptRegs.NMIFLGCLR.bit.NMIINT = 1;
				EDIS;
				
				return;
			}
		}

		if(c1brom_nmi_status & NMI_INT_CPU1HWBISTERR) /*check for M3BISTERR NMI */
		{
			c1brom_status |= C1_BOOTROM_GOT_A_C1BISTERR_NMI;

			c1brom_nmi_status &= ~(NMI_INT_CPU1HWBISTERR);	/*clear bit 4*/
			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.CPU1HWBISTERR = 1;
			EDIS;
		}

		if(c1brom_nmi_status & NMI_INT_CPU2HWBISTERR) /*check for C28BISTERR NMI */
		{
			c1brom_status |= C1_BOOTROM_GOT_A_C2BISTERR_NMI;

			c1brom_nmi_status &= ~(NMI_INT_CPU2HWBISTERR);	/*clear bit 5*/

			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.CPU2HWBISTERR = 1;
			EDIS;
		
		}
		if(c1brom_nmi_status & NMI_INT_PIEVECTERR) /*check for AERR NMI */
		{
			c1brom_status |= C1_BOOTROM_GOT_A_PIEVECTERR_NMI;

			c1brom_nmi_status &= ~(NMI_INT_PIEVECTERR);	/*clear bit 6*/
			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.PIEVECTERR = 1;
			EDIS;
		}
        if(c1brom_nmi_status & NMI_INT_SYSDBG) /*check for PIEVECT NMI */
        {
            c1brom_status |= C1_BOOTROM_GOT_A_SYSDBG_NMI;

            c1brom_nmi_status &= ~(NMI_INT_SYSDBG);  /*clear bit 6*/
            EALLOW;
            NmiIntruptRegs.NMIFLGCLR.bit.SYSDBGNMI = 1;
            EDIS;
        }
        if(c1brom_nmi_status & NMI_INT_RL) /*check for PIEVECT NMI */
        {
            c1brom_status |= C1_BOOTROM_GOT_A_RL_NMI;

            c1brom_nmi_status &= ~(NMI_INT_RL);  /*clear bit 6*/
            EALLOW;
            NmiIntruptRegs.NMIFLGCLR.bit.RLNMI = 1;
            EDIS;
        }
        if(c1brom_nmi_status & NMI_INT_CPU2WDRST) /*check for PIEVECT NMI */
        {
            c1brom_status |= C1_BOOTROM_GOT_A_CPU2WDRST_NMI;

            c1brom_nmi_status &= ~(NMI_INT_CPU2WDRST);  /*clear bit 6*/
            EALLOW;
            NmiIntruptRegs.NMIFLGCLR.bit.CPU2WDRSn = 1;
            EDIS;
        }

        if(c1brom_nmi_status & NMI_INT_CPU2NMIWDRST) /*check for PIEVECT NMI */
        {
            c1brom_status |= C1_BOOTROM_GOT_A_CPU2WDRST_NMI;

            c1brom_nmi_status &= ~(NMI_INT_CPU2NMIWDRST);  /*clear bit 6*/
            EALLOW;
            NmiIntruptRegs.NMIFLGCLR.bit.CPU2NMIWDRSn = 1;
            EDIS;
        }

        if(c1brom_nmi_status & NMI_INT_OVF) /*check for PIEVECT NMI */
        {
            c1brom_status |= C1_BOOTROM_GOT_A_OVF_NMI;

            c1brom_nmi_status &= ~(NMI_INT_OVF);  /*clear bit 6*/
            EALLOW;
            NmiIntruptRegs.NMIFLGCLR.bit.OVF = 1;
            EDIS;
        }

        //there is a reason to check these two at the end
        //d owe really need to reset the device - can't it continue to boot?
        if(c1brom_nmi_status & NMI_INT_RAMUNCERR) /*check for C28RAMUNCERR NMI */
		{
			c1brom_status |= C1_BOOTROM_GOT_A_RAM_UNCERR_NMI;

			//if debugger connected - give a chance to user to know the scenario
			asm("   ESTOP0");

			//let NMIWD reset the device
			while(1);

//			c1brom_nmi_status &= ~(0x04);	/*clear bit 2*/
//			EALLOW;
//			NmiIntruptRegs.NMIFLGCLR.bit.C28RAMUNCERR = 1;
//			EDIS;
		}
		if(c1brom_nmi_status & NMI_INT_FLUNCERR) /*check for C28FLUNCERR NMI */
		{
			c1brom_status |= C1_BOOTROM_GOT_A_FLASH_UNCERR_NMI;

			//if debugger connected - give a chance to user to know the scenario
			asm("   ESTOP0");

            //let NMIWD reset the device
            while(1);

//			c1brom_nmi_status &= ~(0x08);	/*clear bit 3*/
//			EALLOW;
//			NmiIntruptRegs.NMIFLGCLR.bit.C28FLUNCERR = 1;
//			EDIS;
		}

		c1brom_nmi_status &= ~(0x01);	/*clear bit 0*/
		EALLOW;
		NmiIntruptRegs.NMIFLGCLR.bit.NMIINT = 1;
		EDIS;

		c1brom_nmi_status = NmiIntruptRegs.NMIFLG.all;

	}while(c1brom_nmi_status & 0x01);	/*check for NMIINT bit - bit 0*/

//	while(1);
}
/*
 * Function called whenever an illegal interrupt occurs on B.C28X CPU
 */
interrupt void c1brom_itrap_isr(void)
{

	/*set boot status to indicate that B.C28X CPU is in iTRAP ISR, only a reset can pull it out of this*/
	c1brom_status |= C1_BOOTROM_IN_AN_ITRAP;



	/*accessing the glob var locally -sets DP pointer for the below inline ASMs*/
	iTrap_addr = 0xFFFFFFFF;

	/*get the iTrap address (return address from interrupt) stored in stack
	 * This particular return address stored in stack will change according to 
	 * compiler optimizations, 
	 */
	load_itrap_address (&iTrap_addr);

	/*return address from interrupt will be PC location where illegal instruction is executed + 1*/
	iTrap_addr -= 1;


	/*send IPC to master system with iTrap address in ADDR register*/
//	c1brom_send_ipc_to_master(C_BOOTROM_IPC_CTOM_CONTROL_SYSTEM_IN_ITRAP, iTrap_addr, 0);
    sysctl_wdog_enable();

	//if debugger connected - give a chance to user to know the scenario
    asm("   ESTOP0");
	while(1);
}

/*MTOCIPCINT1_isr()
 * 
 * interrupt handler which handles all IPC commands from master system
 * 
 */

interrupt void c1brom_c2c1_ipc_int1_isr(void)
{

	/*check if IPC flags are set properly*/
	if(0 == C1BROM_CHECK_C2C1_IPC_COMMAND_FLAGS_SET)
	{
		/*if both IPC1 and IPC32 flags are not set then return NAK*/
	    C1BROM_C2C1_IPC_COMMAND_NAK(c1brom_status | C1BROM_NAK_STATUS_CMD_NOT_SET_PROPERLY);

		/*ACK PIE interrupt and return*/
	    C1BROM_C2C1_IPC_INT1_ACK;
		return;		
	}

	/*see if C-BootROM is already busy processing another MTOCIPC command*/
	if((c1brom_current_c2c1_ipc.status != COMMAND_STATUS_INVALID) ||
		(c1brom_current_c2c1_ipc.command != C2C1_BROM_IPC_COMMAND_ILLEGAL))
		{
			//return NAK if busy
			C1BROM_C2C1_IPC_COMMAND_NAK(c1brom_status | C1BROM_NAK_STATUS_ALREADY_BUSY_WITH_YOUR_CMD);
		    C1BROM_C2C1_IPC_INT1_ACK;
			return;		
		}

	//not busy, then get busy with current command
	c1brom_current_c2c1_ipc.command = IpcRegs.IPCRECVCOM;
	c1brom_current_c2c1_ipc.status  = COMMAND_PENDING;


	/*boundary checks*/
	if((c1brom_current_c2c1_ipc.command == C2C1_BROM_IPC_COMMAND_ILLEGAL) ||
		 (c1brom_current_c2c1_ipc.command >= C2C1_BROM_IPC_MAX_SUPPORT_VALUE))
	{
		c1brom_current_c2c1_ipc.command = C2C1_BROM_IPC_COMMAND_ILLEGAL;
		c1brom_current_c2c1_ipc.status = COMMAND_STATUS_INVALID;
		C1BROM_C2C1_IPC_COMMAND_NAK(c1brom_status | C1BROM_NAK_STATUS_CMD_NOT_SUPPORTED);
		C1BROM_C2C1_IPC_INT1_ACK; // PIE ack for intr group_11 (incl IPC_MTOC_1)
	   	return;
	}

	//parse the command
	if(c1brom_current_c2c1_ipc.command == C2C1_BROM_IPC_SET_BITS_16)
	{
		c1brom_current_c2c1_ipc.status = c1brom_c2c1_ipc_set_bits_16();
	}
	else if	(c1brom_current_c2c1_ipc.command == C2C1_BROM_IPC_SET_BITS_32)
	{
		c1brom_current_c2c1_ipc.status = c1brom_c2c1_ipc_set_bits_32();
	}
	else if	(c1brom_current_c2c1_ipc.command == C2C1_BROM_IPC_CLEAR_BITS_16)
	{
		c1brom_current_c2c1_ipc.status = c1brom_c2c1_ipc_clear_bits_16();
	}
	else if	(c1brom_current_c2c1_ipc.command == C2C1_BROM_IPC_CLEAR_BITS_32)
	{
		c1brom_current_c2c1_ipc.status = c1brom_c2c1_ipc_clear_bits_32();
	}
	else if	(c1brom_current_c2c1_ipc.command == C2C1_BROM_IPC_DATA_WRITE_16)
	{
		c1brom_current_c2c1_ipc.status = c1brom_c2c1_ipc_write_data_16();
	}
	else if	(c1brom_current_c2c1_ipc.command == C2C1_BROM_IPC_DATA_WRITE_32)
	{
		c1brom_current_c2c1_ipc.status = c1brom_c2c1_ipc_write_data_32();
	}
	else if	(c1brom_current_c2c1_ipc.command == C2C1_BROM_IPC_DATA_READ_16)
	{
		c1brom_current_c2c1_ipc.status = c1brom_c2c1_ipc_read_data_16();
	}
	else if	(c1brom_current_c2c1_ipc.command == C2C1_BROM_IPC_DATA_READ_32)
	{
		c1brom_current_c2c1_ipc.status = c1brom_c2c1_ipc_read_data_32();
	}
	else if	(c1brom_current_c2c1_ipc.command == C2C1_BROM_IPC_SET_BITS_PROTECTED_16)
	{
		c1brom_current_c2c1_ipc.status = c1brom_c2c1_ipc_set_bits_protected_16();
	}
	else if	(c1brom_current_c2c1_ipc.command == C2C1_BROM_IPC_SET_BITS_PROTECTED_32)
	{
		c1brom_current_c2c1_ipc.status = c1brom_c2c1_ipc_set_bits_protected_32();
	}
	else if	(c1brom_current_c2c1_ipc.command == C2C1_BROM_IPC_CLEAR_BITS_PROTECTED_16)
	{
		c1brom_current_c2c1_ipc.status = c1brom_c2c1_ipc_clear_bits_protected_16();
	}
	else if	(c1brom_current_c2c1_ipc.command == C2C1_BROM_IPC_CLEAR_BITS_PROTECTED_32)
	{
		c1brom_current_c2c1_ipc.status = c1brom_c2c1_ipc_clear_bits_protected_32();
	}
	else if	(c1brom_current_c2c1_ipc.command == C2C1_BROM_IPC_DATA_WRITE_PROTECTED_16)
	{
		c1brom_current_c2c1_ipc.status = c1brom_c2c1_ipc_write_data_protected_16();
	}
	else if	(c1brom_current_c2c1_ipc.command == C2C1_BROM_IPC_DATA_WRITE_PROTECTED_32)
	{
		c1brom_current_c2c1_ipc.status = c1brom_c2c1_ipc_write_data_protected_32();
	}
	else if	(c1brom_current_c2c1_ipc.command == C2C1_BROM_IPC_DATA_READ_PROTECTED_16)
	{
		c1brom_current_c2c1_ipc.status = c1brom_c2c1_ipc_read_data_protected_16();
	}
	else if	(c1brom_current_c2c1_ipc.command == C2C1_BROM_IPC_DATA_READ_PROTECTED_32)
	{
		c1brom_current_c2c1_ipc.status = c1brom_c2c1_ipc_read_data_protected_32();
	}
	else	
	{
		c1brom_current_c2c1_ipc.status = COMMAND_COMPLETE_FAILURE;
	}
	
	//handle command complete
	if(COMMAND_COMPLETE_SUCCESS == c1brom_current_c2c1_ipc.status)
	{
		c1brom_current_c2c1_ipc.command = C2C1_BROM_IPC_COMMAND_ILLEGAL;
		c1brom_current_c2c1_ipc.status = COMMAND_STATUS_INVALID;
		C1BROM_C2C1_IPC_COMMAND_ACK;
		C1BROM_C2C1_IPC_INT1_ACK; // PIE ack for intr group_11 (incl IPC_MTOC_1)
	}
	else /*command failure*/
	{
		c1brom_current_c2c1_ipc.command = C2C1_BROM_IPC_COMMAND_ILLEGAL;
		c1brom_current_c2c1_ipc.status = COMMAND_STATUS_INVALID;
		C1BROM_C2C1_IPC_COMMAND_NAK(c1brom_status | C1BROM_NAK_STATUS_CMD_NOT_SUPPORTED);
		C1BROM_C2C1_IPC_INT1_ACK; // PIE ack for intr group_11 (incl IPC_MTOC_1)
	}
}
 
 

//---------------------------------------------------------------------------
// InitPieVectTable:
//---------------------------------------------------------------------------
// This function initializes the PIE vector table to a known state.
// This function must be executed after boot time.
//

void c1brom_init_pie_vect_table(void)
{
	int16	i;
	Uint32 *Dest = (void *) &PieVectTable;

    i = sizeof(struct PIE_VECT_TABLE);
    i -= 3;
    Dest  =  Dest  +  3;

	EALLOW;
    for(;  i > 0;  i--)
    {
		*Dest++ = (Uint32)&c1brom_pie_isr_not_supported;
    }
	EDIS;

	// Enable the PIE Vector Table
	PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

}


//---------------------------------------------------------------------------
// InitPieCtrl:
//---------------------------------------------------------------------------
// This function initializes the PIE control registers to a known state.
//
void c1brom_init_pie_control(void)
{
    // Disable Interrupts at the CPU level:
    DINT;

    // Disable the PIE
    PieCtrlRegs.PIECTRL.bit.ENPIE = 0;

	// Clear all PIEIER registers:
	PieCtrlRegs.PIEIER1.all = 0;
	PieCtrlRegs.PIEIER2.all = 0;
	PieCtrlRegs.PIEIER3.all = 0;
	PieCtrlRegs.PIEIER4.all = 0;
	PieCtrlRegs.PIEIER5.all = 0;
	PieCtrlRegs.PIEIER6.all = 0;
	PieCtrlRegs.PIEIER7.all = 0;
	PieCtrlRegs.PIEIER8.all = 0;
	PieCtrlRegs.PIEIER9.all = 0;
	PieCtrlRegs.PIEIER10.all = 0;
	PieCtrlRegs.PIEIER11.all = 0;
	PieCtrlRegs.PIEIER12.all = 0;

	// Clear all PIEIFR registers:
	PieCtrlRegs.PIEIFR1.all = 0;
	PieCtrlRegs.PIEIFR2.all = 0;
	PieCtrlRegs.PIEIFR3.all = 0;
	PieCtrlRegs.PIEIFR4.all = 0;
	PieCtrlRegs.PIEIFR5.all = 0;
	PieCtrlRegs.PIEIFR6.all = 0;
	PieCtrlRegs.PIEIFR7.all = 0;
	PieCtrlRegs.PIEIFR8.all = 0;
	PieCtrlRegs.PIEIFR9.all = 0;
	PieCtrlRegs.PIEIFR10.all = 0;
	PieCtrlRegs.PIEIFR11.all = 0;
	PieCtrlRegs.PIEIFR12.all = 0;

    // Enable the PIE
    PieCtrlRegs.PIECTRL.bit.ENPIE = 1;

	// Enables PIE to drive a pulse into the CPU
	PieCtrlRegs.PIEACK.all = 0xFFFF;

	// Enable Interrupts at the CPU level
    EINT;

}
//===========================================================================
// End of file.
//===========================================================================


