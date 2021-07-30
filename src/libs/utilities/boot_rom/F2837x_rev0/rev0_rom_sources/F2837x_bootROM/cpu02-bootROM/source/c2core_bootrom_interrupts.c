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
// $TI Release: F2837x Boot ROM Version 0 $
// $Release Date: Oct 1, 2013 $
//###########################################################################

#include "c2_bootrom.h"

void c2brom_init_pie_control(void);
void c2brom_init_pie_vect_table(void);

void branch_to_entryaddress(Uint32 *entryaddress); 
void load_itrap_address (Uint32 *itrapaddress);

interrupt void c2brom_itrap_isr(void);
interrupt void c2brom_c1c2_ipc_int1_isr(void);
interrupt void c2brom_handle_nmi();
void c2brom_pie_vect_mismatch_handler();
void c2brom_handle_nmi_for_pie_mismatch();

extern Uint32 I2C_Boot(void);
extern Uint32 SCI_Boot();
extern Uint32 SPI_Boot();
extern Uint32 SPI_Alternate_IO_Boot();
extern Uint32 Parallel_Boot();



extern cur_c1c2_ipc_cmd_sts_t	c2brom_current_c1c2_ipc;
extern Uint32	c2brom_status;

volatile Uint16 c2brom_nmi_status;
Uint32	iTrap_addr;
Uint32 c1c2_branch_addr;

/*
 * Function to handle unsupported PIE interrupts in C-BootROM
 */
interrupt void c2brom_pie_isr_not_supported()
{
	Uint16 interrupt_num = 0;
	Uint16 address_offset = 0;

	//PIEVECT of PIECTRL register stores the vector address from the PIE vector table from which the vector was fetched.
	// (the vector address - base address of PIE vector table)/2 gives the interrupt vector ID
	address_offset = ((PieCtrlRegs.PIECTRL.all) & (0x00000000FE));
	interrupt_num = (address_offset >> 1);

	c2brom_send_ipc_to_c1(C2_BOOTROM_IPC_CTOM_PIE_INTERRUPT_NOT_SUPPORTED, 0, interrupt_num);

	/*acknowledge the interrupt; don't have to ACK interrupt nos less than 32, its done automatically by interrupt return*/
	if(interrupt_num >= 32)
	{
		/*for PIE multiplexed interrupts INT1 to INT12*/
		PieCtrlRegs.PIEACK.all |= (0x01 << ((address_offset >> 4) - 4));
	}
 
}


void c2brom_handle_nmi_for_pie_mismatch()
{
    uint32_t EntryAddr;

    /*check if NMI is triggered*/
	c2brom_nmi_status = NmiIntruptRegs.NMIFLG.all;

    EntryAddr = TI_OTP_C2BROM_ESCAPE_POINT_11;

    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*do a dummy branch to OTP - if we later decide not to handler this the way done below*/
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }

    do
       {
           if(c2brom_nmi_status & NMI_INT_CLOCKFAIL) /*check for CLOCKFAIL_NMI*/
           {
               c2brom_status |= C2_BOOTROM_GOT_A_MCLK_NMI;
               c2brom_set_c2c1_boot_status(0);
               c2brom_nmi_status &= ~(NMI_INT_CLOCKFAIL);   /*clear bit 1*/

               EALLOW;
               NmiIntruptRegs.NMIFLGCLR.bit.CLOCKFAIL = 1;
               EDIS;

           }
           if(c2brom_nmi_status & NMI_INT_RAMUNCERR) /*check for C28RAMUNCERR NMI */
           {
               c2brom_status |= C2_BOOTROM_GOT_A_RAM_UNCERR_NMI;
               c2brom_send_ipc_to_c1(C2_BOOTROM_IPC_CTOM_CONTROL_SYSTEM_IN_RAMUNCERR, 0, 0);
               c2brom_nmi_status &= ~(NMI_INT_RAMUNCERR);   /*clear bit 2*/

               EALLOW;
               NmiIntruptRegs.NMIFLGCLR.bit.RAMUNCERR = 1;
               EDIS;
           }
           if(c2brom_nmi_status & NMI_INT_FLUNCERR) /*check for C28FLUNCERR NMI */
           {
               c2brom_status |= C2_BOOTROM_GOT_A_FLASH_UNCERR_NMI;
               c2brom_send_ipc_to_c1(C2_BOOTROM_IPC_CTOM_CONTROL_SYSTEM_IN_FLUNCERR, 0, 0);
               c2brom_nmi_status &= ~(NMI_INT_FLUNCERR);    /*clear bit 3*/

               EALLOW;
               NmiIntruptRegs.NMIFLGCLR.bit.FLUNCERR = 1;
               EDIS;
           }

           if(c2brom_nmi_status & NMI_INT_CPU1HWBISTERR) /*check for M3BISTERR NMI */
           {
               c2brom_status |= C2_BOOTROM_GOT_A_C1BISTERR_NMI;
               c2brom_nmi_status &= ~(NMI_INT_CPU1HWBISTERR);   /*clear bit 4*/

               EALLOW;
               NmiIntruptRegs.NMIFLGCLR.bit.CPU1HWBISTERR = 1;
               EDIS;
           }

           if(c2brom_nmi_status & NMI_INT_CPU2HWBISTERR) /*check for C28BISTERR NMI */
           {
               c2brom_status |= C2_BOOTROM_GOT_A_C2BISTERR_NMI;
               c2brom_nmi_status &= ~(NMI_INT_CPU2HWBISTERR);   /*clear bit 5*/

               EALLOW;
               NmiIntruptRegs.NMIFLGCLR.bit.CPU2HWBISTERR = 1;
               EDIS;

           }
           if(c2brom_nmi_status & NMI_INT_PIEVECTERR) /*check for PIEVECT NMI */
           {
               c2brom_status |= C2_BOOTROM_GOT_A_PIEVECTERR_NMI;

               c2brom_nmi_status &= ~(NMI_INT_PIEVECTERR);  /*clear bit 6*/
               EALLOW;
               NmiIntruptRegs.NMIFLGCLR.bit.PIEVECTERR = 1;
               EDIS;
           }
           if(c2brom_nmi_status & NMI_INT_SYSDBG) /*check for PIEVECT NMI */
           {
               c2brom_status |= C2_BOOTROM_GOT_A_SYSDBG_NMI;

               c2brom_nmi_status &= ~(NMI_INT_SYSDBG);  /*clear bit 6*/
               EALLOW;
               NmiIntruptRegs.NMIFLGCLR.bit.SYSDBGNMI = 1;
               EDIS;
           }
           if(c2brom_nmi_status & NMI_INT_RL) /*check for PIEVECT NMI */
           {
               c2brom_status |= C2_BOOTROM_GOT_A_RL_NMI;

               c2brom_nmi_status &= ~(NMI_INT_RL);  /*clear bit 6*/
               EALLOW;
               NmiIntruptRegs.NMIFLGCLR.bit.RLNMI = 1;
               EDIS;
           }
           if(c2brom_nmi_status & NMI_INT_OVF) /*check for PIEVECT NMI */
           {
               c2brom_status |= C2_BOOTROM_GOT_A_OVF_NMI;

               c2brom_nmi_status &= ~(NMI_INT_OVF);  /*clear bit 6*/
               EALLOW;
               NmiIntruptRegs.NMIFLGCLR.bit.OVF = 1;
               EDIS;
           }

           c2brom_nmi_status &= ~(0x01);    /*clear bit 0*/
           EALLOW;
           NmiIntruptRegs.NMIFLGCLR.bit.NMIINT = 1;
           EDIS;

           c2brom_set_c2c1_boot_status(0);

           c2brom_nmi_status = NmiIntruptRegs.NMIFLG.all;

       }while(c2brom_nmi_status & 0x01);    /*check for NMIINT bit - bit 0*/

	return;

}

/*
 * Function to handle PIE vector mismatch handler in C-BootROM
 */
interrupt void c2brom_pie_vect_mismatch_handler()
{
	
	uint32_t EntryAddr = 0xFFFFFFFF;

	c2brom_status |= C2_BOOTROM_GOT_A_PIEMISMATCH;
	c2brom_set_c2c1_boot_status(0);

	EALLOW;
	EntryAddr = (CpuSysRegs.PIEVERRADDR.all);
	EDIS;

	if((EntryAddr != (uint32_t)0x003FFFFF))
	{
		((void (*)(void))EntryAddr)();
	}
	else
	{
		//No need to send this as the other core has already got the NMI
	    //c2brom_send_ipc_to_master(C_BOOTROM_IPC_CTOM_PIE_VECTOR_ADDRESS_MISMATCH, 0, 0);

		c2brom_handle_nmi_for_pie_mismatch();

		while(1);
	}


}

//c- callable function
void c2brom_handle_nmi_at_start()
{
    uint32_t EntryAddr;

    EntryAddr = TI_OTP_C2BROM_ESCAPE_POINT_12;

    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*do a dummy branch to OTP - if we later decide not to handler this the way done below*/
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }

    /*check if NMI is triggered*/
	c2brom_nmi_status = NmiIntruptRegs.NMIFLG.all;
	do
	{
		if(c2brom_nmi_status & NMI_INT_CLOCKFAIL) /*check for CLOCKFAIL_NMI*/
		{
			c2brom_status |= C2_BOOTROM_GOT_A_MCLK_NMI;
			c2brom_set_c2c1_boot_status(0);
			c2brom_nmi_status &= ~(NMI_INT_CLOCKFAIL);	/*clear bit 1*/

			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.CLOCKFAIL = 1;
			EDIS;

			c2brom_nmi_status = NmiIntruptRegs.NMIFLG.all;

			/*continue to run*/
			if((c2brom_nmi_status) == NMI_INT_FLG)
			{
				c2brom_nmi_status &= ~(NMI_INT_FLG);	/*clear bit 0*/
				/* clear the NMIINT flag and return because there is no other NMI set*/
				EALLOW;
				NmiIntruptRegs.NMIFLGCLR.bit.NMIINT = 1;
				EDIS;

				return;
			}
		}
		if(c2brom_nmi_status & NMI_INT_RAMUNCERR) /*check for C28RAMUNCERR NMI */
		{
			c2brom_status |= C2_BOOTROM_GOT_A_RAM_UNCERR_NMI;
			c2brom_send_ipc_to_c1(C2_BOOTROM_IPC_CTOM_CONTROL_SYSTEM_IN_RAMUNCERR, 0, 0);
			c2brom_nmi_status &= ~(NMI_INT_RAMUNCERR);	/*clear bit 2*/

			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.RAMUNCERR = 1;
			EDIS;
		}
		if(c2brom_nmi_status & NMI_INT_FLUNCERR) /*check for C28FLUNCERR NMI */
		{
			c2brom_status |= C2_BOOTROM_GOT_A_FLASH_UNCERR_NMI;
			c2brom_send_ipc_to_c1(C2_BOOTROM_IPC_CTOM_CONTROL_SYSTEM_IN_FLUNCERR, 0, 0);
			c2brom_nmi_status &= ~(NMI_INT_FLUNCERR);	/*clear bit 3*/

			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.FLUNCERR = 1;
			EDIS;
		}

		if(c2brom_nmi_status & NMI_INT_CPU1HWBISTERR) /*check for M3BISTERR NMI */
		{
			c2brom_status |= C2_BOOTROM_GOT_A_C1BISTERR_NMI;
			c2brom_nmi_status &= ~(NMI_INT_CPU1HWBISTERR);	/*clear bit 4*/

			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.CPU1HWBISTERR = 1;
			EDIS;
		}

		if(c2brom_nmi_status & NMI_INT_CPU2HWBISTERR) /*check for C28BISTERR NMI */
		{
			c2brom_status |= C2_BOOTROM_GOT_A_C2BISTERR_NMI;
			c2brom_nmi_status &= ~(NMI_INT_CPU2HWBISTERR);	/*clear bit 5*/

			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.CPU2HWBISTERR = 1;
			EDIS;

		}
		if(c2brom_nmi_status & NMI_INT_PIEVECTERR) /*check for PIEVECT NMI */
		{
			c2brom_status |= C2_BOOTROM_GOT_A_PIEVECTERR_NMI;

			c2brom_nmi_status &= ~(NMI_INT_PIEVECTERR);	/*clear bit 6*/
			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.PIEVECTERR = 1;
			EDIS;
		}
		if(c2brom_nmi_status & NMI_INT_SYSDBG) /*check for PIEVECT NMI */
        {
            c2brom_status |= C2_BOOTROM_GOT_A_SYSDBG_NMI;

            c2brom_nmi_status &= ~(NMI_INT_SYSDBG);  /*clear bit 6*/
            EALLOW;
            NmiIntruptRegs.NMIFLGCLR.bit.SYSDBGNMI = 1;
            EDIS;
        }
        if(c2brom_nmi_status & NMI_INT_RL) /*check for PIEVECT NMI */
        {
            c2brom_status |= C2_BOOTROM_GOT_A_RL_NMI;

            c2brom_nmi_status &= ~(NMI_INT_RL);  /*clear bit 6*/
            EALLOW;
            NmiIntruptRegs.NMIFLGCLR.bit.RLNMI = 1;
            EDIS;
        }
        if(c2brom_nmi_status & NMI_INT_OVF) /*check for PIEVECT NMI */
        {
            c2brom_status |= C2_BOOTROM_GOT_A_OVF_NMI;

            c2brom_nmi_status &= ~(NMI_INT_OVF);  /*clear bit 6*/
            EALLOW;
            NmiIntruptRegs.NMIFLGCLR.bit.OVF = 1;
            EDIS;
        }


		c2brom_nmi_status &= ~(0x01);	/*clear bit 0*/
		EALLOW;
		NmiIntruptRegs.NMIFLGCLR.bit.NMIINT = 1;
		EDIS;

		c2brom_set_c2c1_boot_status(0);

		c2brom_nmi_status = NmiIntruptRegs.NMIFLG.all;

	}while(c2brom_nmi_status & 0x01);	/*check for NMIINT bit - bit 0*/
//	while(1);
}
/*
 * Function to handle NMI interrupts in C-BootROM
 */
interrupt void c2brom_handle_nmi()
{
    uint32_t EntryAddr;

    EntryAddr = TI_OTP_C2BROM_ESCAPE_POINT_12;

    if((EntryAddr != 0xFFFFFFFF) &&
            (EntryAddr != 0x00000000))
    {
        /*do a dummy branch to OTP - if we later decide not to handler this the way done below*/
        /*if OTP is programmed, then call OTP function*/
        ((void (*)(void))EntryAddr)();
    }

    /*check if NMI is triggered*/
	c2brom_nmi_status = NmiIntruptRegs.NMIFLG.all;
	do
	{
		if(c2brom_nmi_status & NMI_INT_CLOCKFAIL) /*check for CLOCKFAIL_NMI*/
		{
			c2brom_status |= C2_BOOTROM_GOT_A_MCLK_NMI;
			c2brom_set_c2c1_boot_status(0);
			c2brom_nmi_status &= ~(NMI_INT_CLOCKFAIL);	/*clear bit 1*/

			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.CLOCKFAIL = 1;
			EDIS;

			c2brom_nmi_status = NmiIntruptRegs.NMIFLG.all;

			/*continue to run*/
			if((c2brom_nmi_status) == NMI_INT_FLG)
			{
				c2brom_nmi_status &= ~(NMI_INT_FLG);	/*clear bit 0*/
				/* clear the NMIINT flag and return because there is no other NMI set*/
				EALLOW;
				NmiIntruptRegs.NMIFLGCLR.bit.NMIINT = 1;
				EDIS;
				
				return;
			}
		}
		if(c2brom_nmi_status & NMI_INT_RAMUNCERR) /*check for C28RAMUNCERR NMI */
		{
			c2brom_status |= C2_BOOTROM_GOT_A_RAM_UNCERR_NMI;
			c2brom_send_ipc_to_c1(C2_BOOTROM_IPC_CTOM_CONTROL_SYSTEM_IN_RAMUNCERR, 0, 0);
			c2brom_nmi_status &= ~(NMI_INT_RAMUNCERR);	/*clear bit 2*/

			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.RAMUNCERR = 1;
			EDIS;
		}
		if(c2brom_nmi_status & NMI_INT_FLUNCERR) /*check for C28FLUNCERR NMI */
		{
			c2brom_status |= C2_BOOTROM_GOT_A_FLASH_UNCERR_NMI;
			c2brom_send_ipc_to_c1(C2_BOOTROM_IPC_CTOM_CONTROL_SYSTEM_IN_FLUNCERR, 0, 0);
			c2brom_nmi_status &= ~(NMI_INT_FLUNCERR);	/*clear bit 3*/

			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.FLUNCERR = 1;
			EDIS;
		}

		if(c2brom_nmi_status & NMI_INT_CPU1HWBISTERR) /*check for M3BISTERR NMI */
		{
			c2brom_status |= C2_BOOTROM_GOT_A_C1BISTERR_NMI;
			c2brom_nmi_status &= ~(NMI_INT_CPU1HWBISTERR);	/*clear bit 4*/

			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.CPU1HWBISTERR = 1;
			EDIS;
		}

		if(c2brom_nmi_status & NMI_INT_CPU2HWBISTERR) /*check for C28BISTERR NMI */
		{
			c2brom_status |= C2_BOOTROM_GOT_A_C2BISTERR_NMI;
			c2brom_nmi_status &= ~(NMI_INT_CPU2HWBISTERR);	/*clear bit 5*/

			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.CPU2HWBISTERR = 1;
			EDIS;
		
		}
		if(c2brom_nmi_status & NMI_INT_PIEVECTERR) /*check for PIEVECT NMI */
		{
			c2brom_status |= C2_BOOTROM_GOT_A_PIEVECTERR_NMI;

			c2brom_nmi_status &= ~(NMI_INT_PIEVECTERR);	/*clear bit 6*/
			EALLOW;
			NmiIntruptRegs.NMIFLGCLR.bit.PIEVECTERR = 1;
			EDIS;
		}
		if(c2brom_nmi_status & NMI_INT_SYSDBG) /*check for PIEVECT NMI */
        {
            c2brom_status |= C2_BOOTROM_GOT_A_SYSDBG_NMI;

            c2brom_nmi_status &= ~(NMI_INT_SYSDBG);  /*clear bit 6*/
            EALLOW;
            NmiIntruptRegs.NMIFLGCLR.bit.SYSDBGNMI = 1;
            EDIS;
        }
        if(c2brom_nmi_status & NMI_INT_RL) /*check for PIEVECT NMI */
        {
            c2brom_status |= C2_BOOTROM_GOT_A_RL_NMI;

            c2brom_nmi_status &= ~(NMI_INT_RL);  /*clear bit 6*/
            EALLOW;
            NmiIntruptRegs.NMIFLGCLR.bit.RLNMI = 1;
            EDIS;
        }
        if(c2brom_nmi_status & NMI_INT_OVF) /*check for PIEVECT NMI */
        {
            c2brom_status |= C2_BOOTROM_GOT_A_OVF_NMI;

            c2brom_nmi_status &= ~(NMI_INT_OVF);  /*clear bit 6*/
            EALLOW;
            NmiIntruptRegs.NMIFLGCLR.bit.OVF = 1;
            EDIS;
        }


		c2brom_nmi_status &= ~(0x01);	/*clear bit 0*/
		EALLOW;
		NmiIntruptRegs.NMIFLGCLR.bit.NMIINT = 1;
		EDIS;

		c2brom_set_c2c1_boot_status(0);

		c2brom_nmi_status = NmiIntruptRegs.NMIFLG.all;

	}while(c2brom_nmi_status & 0x01);	/*check for NMIINT bit - bit 0*/
	while(1);
}

/*
 * Function called whenever an illegal interrupt occurs on B.C28X CPU
 */
interrupt void c2brom_itrap_isr(void)
{

	/*set boot status to indicate that B.C28X CPU is in iTRAP ISR, only a reset can pull it out of this*/
	c2brom_status |= C2_BOOTROM_IN_AN_ITRAP;

	/*check if RAM is accessible at this point,
	 * so read back the prev. value that was written
	 */
	if((c2brom_status & C2_BOOTROM_IN_AN_ITRAP) == 0x0)
	{
		//if RAM is not accessible then don;t do any function calls.
		//just send IPC to Master and enter while(1) loop

		//wait until master finishes up with current IPC, if any.
		while(IpcRegs.IPCFLG.bit.IPC0);

		IpcRegs.IPCSENDCOM = C2_BOOTROM_IPC_CTOM_CONTROL_SYSTEM_IN_ITRAP;
		IpcRegs.IPCSENDADDR = 0xFFFFFFFF;
		IpcRegs.IPCSENDDATA = 0xFFFFFFFF;
		IpcRegs.IPCSET.all = 0x80000001;	//set bit 31 and bit 0

		while(1);
	}
	/*if here then RAM is still accessible so provide enough debug info*/

	c2brom_set_c2c1_boot_status(0);

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
	c2brom_send_ipc_to_c1(C2_BOOTROM_IPC_CTOM_CONTROL_SYSTEM_IN_ITRAP, iTrap_addr, 0);
	
	while(1);
}

/*C122IPCINT1_isr()
 * 
 * interrupt handler which handles all IPC commands from master system
 * 
 */

interrupt void c2brom_c1c2_ipc_int1_isr(void)
{

	/*check if IPC flags are set properly*/
	if(0 == C2BROM_CHECK_C1C2_IPC_COMMAND_FLAGS_SET)
	{
		/*if both IPC1 and IPC32 flags are not set then return NAK*/
	    C2BROM_C1C2_IPC_COMMAND_NAK(c2brom_status | C2_BOOTROM_NAK_STATUS_CMD_NOT_SET_PROPERLY);

		/*ACK PIE interrupt and return*/
	    C2BROM_C1C2_IPC_INT1_ACK;
		return;		
	}

	/*see if C-BootROM is already busy processing another MTOCIPC command*/
	if((c2brom_current_c1c2_ipc.status != COMMAND_STATUS_INVALID) ||
		(c2brom_current_c1c2_ipc.command != C1C2_BROM_IPC_COMMAND_ILLEGAL))
		{
			//return NAK if busy
	    C2BROM_C1C2_IPC_COMMAND_NAK(c2brom_status | C2_BOOTROM_NAK_STATUS_ALREADY_BUSY_WITH_YOUR_CMD);
	    C2BROM_C1C2_IPC_INT1_ACK;
			return;		
		}

	//not busy, then get busy with current command
	c2brom_current_c1c2_ipc.command = IpcRegs.IPCRECVCOM;
	c2brom_current_c1c2_ipc.status  = COMMAND_PENDING;


	/*boundary checks*/
	if((c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_COMMAND_ILLEGAL) ||
		 (c2brom_current_c1c2_ipc.command >= C1C2_BROM_IPC_MAX_SUPPORT_VALUE))
	{
		c2brom_current_c1c2_ipc.command = C1C2_BROM_IPC_COMMAND_ILLEGAL;
		c2brom_current_c1c2_ipc.status = COMMAND_STATUS_INVALID;
		C2BROM_C1C2_IPC_COMMAND_NAK(c2brom_status | C2_BOOTROM_NAK_STATUS_CMD_NOT_SUPPORTED);
		C2BROM_C1C2_IPC_INT1_ACK; // PIE ack for intr group_11 (incl IPC_MTOC_1)
	   	return;
	}

	//parse the command
	if(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_SET_BITS_16)
	{
		c2brom_current_c1c2_ipc.status = c2brom_c1c2_ipc_set_bits_16();
	}
	else if	(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_SET_BITS_32)
	{
		c2brom_current_c1c2_ipc.status = c2brom_c1c2_ipc_set_bits_32();
	}
	else if	(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_CLEAR_BITS_16)
	{
		c2brom_current_c1c2_ipc.status = c2brom_c1c2_ipc_clear_bits_16();
	}
	else if	(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_CLEAR_BITS_32)
	{
		c2brom_current_c1c2_ipc.status = c2brom_c1c2_ipc_clear_bits_32();
	}
	else if	(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_DATA_WRITE_16)
	{
		c2brom_current_c1c2_ipc.status = c2brom_c1c2_ipc_write_data_16();
	}
	else if	(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_DATA_WRITE_32)
	{
		c2brom_current_c1c2_ipc.status = c2brom_c1c2_ipc_write_data_32();
	}
	else if	(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_DATA_READ_16)
	{
		c2brom_current_c1c2_ipc.status = c2brom_c1c2_ipc_read_data_16();
	}
	else if	(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_DATA_READ_32)
	{
		c2brom_current_c1c2_ipc.status = c2brom_c1c2_ipc_read_data_32();
	}
	else if	(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_SET_BITS_PROTECTED_16)
	{
		c2brom_current_c1c2_ipc.status = c2brom_c1c2_ipc_set_bits_protected_16();
	}
	else if	(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_SET_BITS_PROTECTED_32)
	{
		c2brom_current_c1c2_ipc.status = c2brom_c1c2_ipc_set_bits_protected_32();
	}
	else if	(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_CLEAR_BITS_PROTECTED_16)
	{
		c2brom_current_c1c2_ipc.status = c2brom_c1c2_ipc_clear_bits_protected_16();
	}
	else if	(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_CLEAR_BITS_PROTECTED_32)
	{
		c2brom_current_c1c2_ipc.status = c2brom_c1c2_ipc_clear_bits_protected_32();
	}
	else if	(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_DATA_WRITE_PROTECTED_16)
	{
		c2brom_current_c1c2_ipc.status = c2brom_c1c2_ipc_write_data_protected_16();
	}
	else if	(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_DATA_WRITE_PROTECTED_32)
	{
		c2brom_current_c1c2_ipc.status = c2brom_c1c2_ipc_write_data_protected_32();
	}
	else if	(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_DATA_READ_PROTECTED_16)
	{
		c2brom_current_c1c2_ipc.status = c2brom_c1c2_ipc_read_data_protected_16();
	}
	else if	(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_DATA_READ_PROTECTED_32)
	{
		c2brom_current_c1c2_ipc.status = c2brom_c1c2_ipc_read_data_protected_32();
	}
	else if	(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_BRANCH_CALL)
	{

		/*set boot status to indicate that B.C28X CPU is will be branching to Control system requested address*/
		c2brom_status |= C2_BOOTROM_IN_C1TOC2_BRANCH;
		c2brom_set_c2c1_boot_status(0);

		c1c2_branch_addr = IpcRegs.IPCRECVADDR;

		/*the return address from the interrupt service routine will be pushed into stack
		 * (please look at C28X assembly reference guide for more info)
		 * modify the stack location which holds the return address to the required branch address
		 * so when iRET is executed it will branch to the required location
		 * */
				
		branch_to_entryaddress(&c1c2_branch_addr);
		c2brom_current_c1c2_ipc.status = COMMAND_COMPLETE_SUCCESS;
	}
	else if	(c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_FUNCTION_CALL)
	{
		IpcRegs.IPCLOCALREPLY = c2brom_c1c2_ipc_func_call_command();
		c2brom_current_c1c2_ipc.status = COMMAND_COMPLETE_SUCCESS;
	}
	else if (c2brom_current_c1c2_ipc.command == C1C2_BROM_IPC_EXECUTE_BOOTMODE_CMD)
	{
		if((C1C2_BROM_BOOTMODE_COMMAND_ILLEGAL != IpcRegs.IPCBOOTMODE) &&
		   (IpcRegs.IPCBOOTMODE < C1C2_BROM_BOOTMODE_BOOT_COMMAND_MAX_SUPPORT_VALUE))
		{
			c1c2_branch_addr = 0xFFFFFFFF;
			
			if( IpcRegs.IPCBOOTMODE == C1C2_BROM_BOOTMODE_BOOT_FROM_RAM)
			{
				c1c2_branch_addr = RAM_ENTRY_POINT;
			}
			else if( IpcRegs.IPCBOOTMODE == C1C2_BROM_BOOTMODE_BOOT_FROM_FLASH)
			{
			    c1c2_branch_addr = FLASH_ENTRY_POINT;
			}
			else if( IpcRegs.IPCBOOTMODE == C1C2_BROM_BOOTMODE_BOOT_FROM_SCI)
			{
			    c1c2_branch_addr = SCI_Boot();
			}
			else if( IpcRegs.IPCBOOTMODE == C1C2_BROM_BOOTMODE_BOOT_FROM_SPI)
			{
			    c1c2_branch_addr = SPI_Boot();
			}
			else if( IpcRegs.IPCBOOTMODE == C1C2_BROM_BOOTMODE_BOOT_FROM_I2C)
			{
			    c1c2_branch_addr = I2C_Boot();
			}
			else if( IpcRegs.IPCBOOTMODE == C1C2_BROM_BOOTMODE_BOOT_FROM_PARALLEL)
			{
			    c1c2_branch_addr = Parallel_Boot();
			}
			
			if(c1c2_branch_addr != 0xFFFFFFFF)
			{
				c2brom_status |= C2_BOOTROM_BOOT_COMPLETE;
				c2brom_set_c2c1_boot_status(C2_BOOTROM_BOOTSTS_CTOM_BOOT_CMD_ACK);
		
				/*the return address from the interrupt service routine will be pushed into stack
				 * (please look at C28X assembly reference guide for more info)
				 * modify the stack location which holds the return address to the required branch address
				 * so when iRET is executed it will branch to the required location
				 * */
				branch_to_entryaddress(&c1c2_branch_addr);

				c2brom_current_c1c2_ipc.status = COMMAND_COMPLETE_SUCCESS;
			}
			else
			{
				c2brom_current_c1c2_ipc.status = COMMAND_COMPLETE_FAILURE;
			}
		} 
		else
		{
			c2brom_set_c2c1_boot_status(C2_BOOTROM_BOOTSTS_CTOM_BOOT_CMD_NAK_STATUS_NOT_SUPPORTED);
			c2brom_current_c1c2_ipc.status = COMMAND_COMPLETE_SUCCESS;

			c1c2_branch_addr = TI_OTP_C2BROM_ESCAPE_POINT_10;
			if((c1c2_branch_addr != 0xFFFFFFFF) &&
					(c1c2_branch_addr != 0x00000000))

			{
				/*if OTP is programmed, then call OTP function*/
				((void (*)(void))c1c2_branch_addr)();
			}
		}
	}
	else	
	{
		c2brom_current_c1c2_ipc.status = COMMAND_COMPLETE_FAILURE;
	}
	
	//handle command complete
	if(COMMAND_COMPLETE_SUCCESS == c2brom_current_c1c2_ipc.status)
	{
		c2brom_current_c1c2_ipc.command = C1C2_BROM_IPC_COMMAND_ILLEGAL;
		c2brom_current_c1c2_ipc.status = COMMAND_STATUS_INVALID;
		C2BROM_C1C2_IPC_COMMAND_ACK;
		C2BROM_C1C2_IPC_INT1_ACK; // PIE ack for intr group_1 (incl IPC_MTOC_1)
	}
	else /*command failure*/
	{
		c2brom_current_c1c2_ipc.command = C1C2_BROM_IPC_COMMAND_ILLEGAL;
		c2brom_current_c1c2_ipc.status = COMMAND_STATUS_INVALID;
		C2BROM_C1C2_IPC_COMMAND_NAK(c2brom_status | C2_BOOTROM_NAK_STATUS_CMD_NOT_SUPPORTED);
		C2BROM_C1C2_IPC_INT1_ACK; // PIE ack for intr group_11 (incl IPC_MTOC_1)
	}
}
 
 
//---------------------------------------------------------------------------
// InitPieVectTable:
//---------------------------------------------------------------------------
// This function initializes the PIE vector table to a known state.
// This function must be executed after boot time.
//

void c2brom_init_pie_vect_table(void)
{
	int16	i;
	Uint32 *Dest = (void *) &PieVectTable;

	EALLOW;
	Dest += 3;
	for(i=3; i < sizeof(struct PIE_VECT_TABLE); i++)
	{
		*Dest++ = (Uint32)&c2brom_pie_isr_not_supported;
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
void c2brom_init_pie_control(void)
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


