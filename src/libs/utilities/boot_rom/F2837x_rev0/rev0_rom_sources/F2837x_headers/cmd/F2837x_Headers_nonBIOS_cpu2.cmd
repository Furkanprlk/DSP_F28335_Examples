
MEMORY
{
 PAGE 0:    /* Program Memory */

 PAGE 1:    /* Data Memory */ 

   ADCA_RESULT   : origin = 0x000B00, length = 0x000020
   ADCB_RESULT   : origin = 0x000B20, length = 0x000020
   ADCC_RESULT   : origin = 0x000B40, length = 0x000020
   ADCD_RESULT   : origin = 0x000B60, length = 0x000020

   ADCA          : origin = 0x007400, length = 0x000080
   ADCB          : origin = 0x007480, length = 0x000080
   ADCC          : origin = 0x007500, length = 0x000080
   ADCD          : origin = 0x007580, length = 0x000080
   
   CLA1         : origin = 0x001400, length = 0x000040     /* CLA registers */

   CMPSS1       : origin = 0x005C80, length = 0x000020
   CMPSS2       : origin = 0x005CA0, length = 0x000020
   CMPSS3       : origin = 0x005CC0, length = 0x000020
   CMPSS4       : origin = 0x005CE0, length = 0x000020
   CMPSS5       : origin = 0x005D00, length = 0x000020
   CMPSS6       : origin = 0x005D20, length = 0x000020
   CMPSS7       : origin = 0x005D40, length = 0x000020
   CMPSS8       : origin = 0x005D60, length = 0x000020

   CPU_TIMER0   : origin = 0x000C00, length = 0x000008     /* CPU Timer0 registers */
   CPU_TIMER1   : origin = 0x000C08, length = 0x000008     /* CPU Timer1 registers */
   CPU_TIMER2   : origin = 0x000C10, length = 0x000008     /* CPU Timer2 registers */

   DAC1         : origin = 0x005C00, length = 0x000010
   DAC2         : origin = 0x005C10, length = 0x000010
   DAC3         : origin = 0x005C20, length = 0x000010
   
   DCANA         : origin = 0x048000, length = 0x001000		/* DCAN A Registers */
   DCANB         : origin = 0x04A000, length = 0x001000		/* DCAN B Registers */

   DMA          : origin = 0x001000, length = 0x000200
   DMACLASRCSEL : origin = 0x007980, length = 0x000040

   ECAP1        : origin = 0x005000, length = 0x000020     /* Enhanced Capture 1 registers */
   ECAP2        : origin = 0x005020, length = 0x000020     /* Enhanced Capture 2 registers */
   ECAP3        : origin = 0x005040, length = 0x000020     /* Enhanced Capture 3 registers */
   ECAP4        : origin = 0x005060, length = 0x000020     /* Enhanced Capture 4 registers */
   ECAP5        : origin = 0x005080, length = 0x000020     /* Enhanced Capture 5 registers */
   ECAP6        : origin = 0x0050A0, length = 0x000020     /* Enhanced Capture 6 registers */
   
   EMIF1        : origin = 0x047000, length = 0x000800
   EMIF2        : origin = 0x047800, length = 0x000800

   EQEP1        : origin = 0x005100, length = 0x000040     /* Enhanced QEP 1 registers */
   EQEP2        : origin = 0x005140, length = 0x000040     /* Enhanced QEP 2 registers */
   EQEP3        : origin = 0x005180, length = 0x000040     /* Enhanced QEP 3 registers */

   EPWM1        : origin = 0x004000, length = 0x000100     /* Enhanced PWM 1 registers */
   EPWM2        : origin = 0x004100, length = 0x000100     /* Enhanced PWM 2 registers */
   EPWM3        : origin = 0x004200, length = 0x000100     /* Enhanced PWM 3 registers */
   EPWM4        : origin = 0x004300, length = 0x000100     /* Enhanced PWM 4 registers */
   EPWM5        : origin = 0x004400, length = 0x000100     /* Enhanced PWM 5 registers */
   EPWM6        : origin = 0x004500, length = 0x000100     /* Enhanced PWM 6 registers */
   EPWM7        : origin = 0x004600, length = 0x000100     /* Enhanced PWM 7 registers */
   EPWM8        : origin = 0x004700, length = 0x000100     /* Enhanced PWM 8 registers */
   EPWM9        : origin = 0x004800, length = 0x000100     /* Enhanced PWM 9 registers */
   EPWM10       : origin = 0x004900, length = 0x000100     /* Enhanced PWM 10 registers */
   EPWM11       : origin = 0x004A00, length = 0x000100     /* Enhanced PWM 11 registers */
   EPWM12       : origin = 0x004B00, length = 0x000100     /* Enhanced PWM 12 registers */

   FLASH_CTRL   : origin = 0x05F800, length = 0x000300
   FLASH_ECC    : origin = 0x05FB00, length = 0x000040
   
   GPIOCTRL     : origin = 0x007C00, length = 0x000180     /* GPIO control registers */
   GPIODAT      : origin = 0x007F00, length = 0x000030     /* GPIO data registers */


   I2CA         : origin = 0x007300, length = 0x000040     /* I2C-A registers */
   I2CB         : origin = 0x007340, length = 0x000040     /* I2C-B registers */

   IPC          : origin = 0x050000, length = 0x001000
   HWBIST       : origin = 0x05E000, length = 0x000100     /* HWBIST registers */

   MEMCFG       : origin = 0x05F400, length = 0x000400     /* Mem Config registers */

   MCBSPA       : origin = 0x006000, length = 0x000040     /* McBSP-A registers */
   MCBSPB       : origin = 0x006040, length = 0x000040     /* McBSP-A registers */

   NMIINTRUPT   : origin = 0x007060, length = 0x000010     /* NMI Watchdog Interrupt Registers */

   PIE_CTRL     : origin = 0x000CE0, length = 0x000020     /* PIE control registers */
   PIE_VECT     : origin = 0x000D00, length = 0x000200     /* PIE Vector Table */

   SCIA         : origin = 0x007200, length = 0x000010     /* SCI-A registers */
   SCIB         : origin = 0x007210, length = 0x000010     /* SCI-B registers */
   SCIC         : origin = 0x007220, length = 0x000010     /* SCI-C registers */
   SCID         : origin = 0x007230, length = 0x000010     /* SCI-D registers */
   
   SDFM1		: origin = 0x005E00, length = 0x000080	   /* Sigma delta 1 registers */
   SDFM2		: origin = 0x005E80, length = 0x000080	   /* Sigma delta 2 registers */

   SPIA         : origin = 0x006100, length = 0x000010
   SPIB         : origin = 0x006110, length = 0x000010
   SPIC         : origin = 0x006120, length = 0x000010

   DEV_CFG     : origin = 0x05D000, length = 0x000200
   CLK_CFG     : origin = 0x05D200, length = 0x000100
   CPU_SYS     : origin = 0x05D300, length = 0x000100

   TRIG         : origin = 0x007900, length = 0x000050
   WD           : origin = 0x007000, length = 0x000040

   XBAR_CONFIG  : origin = 0x007A00, length = 0x000200

   XINT         : origin = 0x007070, length = 0x000010







//   DEV_EMU      : origin = 0x000880, length = 0x000105     /* device emulation registers */
//   SYS_PWR_CTL  : origin = 0x000985, length = 0x000003     /* System power control registers */
//   FLASH_REGS   : origin = 0x000A80, length = 0x000060     /* FLASH registers */
                
//   ADC_RESULT   : origin = 0x000B00, length = 0x000020     /* ADC Results register mirror */
                
   DCSM_Z1      : origin = 0x05F000, length = 0x000030     /* Zone 1 Dual code security module registers */
   DCSM_Z2      : origin = 0x05F040, length = 0x000030     /* Zone 2 Dual code security module registers */
   DCSM_COMMON  : origin = 0x05F070, length = 0x000010     /* Common Dual code security module registers */
                

                
//   PIE_CTRL     : origin = 0x000CE0, length = 0x000020     /* PIE control registers */
//   PIE_VECT     : origin = 0x000D00, length = 0x000100     /* PIE Vector Table */
                
//   CLA1         : origin = 0x001400, length = 0x000080     /* CLA registers */
                
//   ECANA        : origin = 0x006000, length = 0x000040     /* eCAN-A control and status registers */
//   ECANA_LAM    : origin = 0x006040, length = 0x000040     /* eCAN-A local acceptance masks */
//   ECANA_MOTS   : origin = 0x006080, length = 0x000040     /* eCAN-A message object time stamps */
//   ECANA_MOTO   : origin = 0x0060C0, length = 0x000040     /* eCAN-A object time-out registers */
//   ECANA_MBOX   : origin = 0x006100, length = 0x000100     /* eCAN-A mailboxes */
                
//   ANASUBSYS    : origin = 0x006400, length = 0x000100     /* Analog Subsystem registers */
                
//   EPWM1        : origin = 0x006800, length = 0x000040     /* Enhanced PWM 1 registers */
//   EPWM2        : origin = 0x006840, length = 0x000040     /* Enhanced PWM 2 registers */
//   EPWM3        : origin = 0x006880, length = 0x000040     /* Enhanced PWM 3 registers */
//   EPWM4        : origin = 0x0068C0, length = 0x000040     /* Enhanced PWM 4 registers */
//   EPWM5        : origin = 0x006900, length = 0x000040     /* Enhanced PWM 5 registers */
//   EPWM6        : origin = 0x006940, length = 0x000040     /* Enhanced PWM 6 registers */
//   EPWM7        : origin = 0x006980, length = 0x000040     /* Enhanced PWM 7 registers */
                
//   ECAP1        : origin = 0x006A00, length = 0x000020     /* Enhanced Capture 1 registers */
                
//   EQEP1        : origin = 0x006B00, length = 0x000040     /* Enhanced QEP 1 registers */
                
//   GPIOCTRL     : origin = 0x006F80, length = 0x000040     /* GPIO control registers */
//   GPIODAT      : origin = 0x006FC0, length = 0x000020     /* GPIO data registers */
//   GPIOINT      : origin = 0x006FE0, length = 0x000020     /* GPIO __interrupt/LPM registers */

//   SYSTEM       : origin = 0x007010, length = 0x000020     /* System control registers */

//   SPIA         : origin = 0x007040, length = 0x000010     /* SPI-A registers */
//   SCIA         : origin = 0x007050, length = 0x000010     /* SCI-A registers */

//   NMIINTRUPT  : origin = 0x007060, length = 0x000010     /* NMI Watchdog Interrupt Registers */
//   XINTRUPT     : origin = 0x007070, length = 0x000010     /* external __interrupt registers */

//   ADC          : origin = 0x007100, length = 0x000080     /* ADC registers */
   
//   SCIB         : origin = 0x007750, length = 0x000010     /* SCI-B registers */
//   SCIC         : origin = 0x007770, length = 0x000010     /* SCI-A registers */

//   I2CA         : origin = 0x007900, length = 0x000040     /* I2C-A registers */
  
   DCSM_OTP_Z2  : origin = 0x078000, length = 0x000020     /* Part of Z1 OTP.  LinkPointer/JTAG lock/ Boot Mode */
   DCSM_OTP_Z1  : origin = 0x078200, length = 0x000020     /* Part of Z2 OTP.  LinkPointer/JTAG lock */
}


SECTIONS
{
/*** PIE Vect Table and Boot ROM Variables Structures ***/
  UNION run = PIE_VECT, PAGE = 1
   {
      PieVectTableFile
      GROUP
      {
         EmuKeyVar
         EmuBModeVar
         FlashCallbackVar
         FlashScalingVar
      }
   }

   AdcaResultFile        : > ADCA_RESULT,  PAGE = 1
   AdcbResultFile        : > ADCB_RESULT,  PAGE = 1
   AdccResultFile        : > ADCC_RESULT,  PAGE = 1
   AdcdResultFile        : > ADCD_RESULT,  PAGE = 1

   AdcaRegsFile          : > ADCA,         PAGE = 1
   AdcbRegsFile          : > ADCB,         PAGE = 1
   AdccRegsFile          : > ADCC,         PAGE = 1
   AdcdRegsFile          : > ADCD,         PAGE = 1
   
   Cla1RegsFile          : > CLA1,         PAGE = 1
   Cla1SoftIntRegsFile   : > PIE_CTRL, 	   PAGE = 1, type=DSECT

   Cmpss1RegsFile        : > CMPSS1,      PAGE = 1
   Cmpss2RegsFile        : > CMPSS2,      PAGE = 1
   Cmpss3RegsFile        : > CMPSS3,      PAGE = 1
   Cmpss4RegsFile        : > CMPSS4,      PAGE = 1
   Cmpss5RegsFile        : > CMPSS5,      PAGE = 1
   Cmpss6RegsFile        : > CMPSS6,      PAGE = 1
   Cmpss7RegsFile        : > CMPSS7,      PAGE = 1
   Cmpss8RegsFile        : > CMPSS8,      PAGE = 1

   CpuTimer0RegsFile    : > CPU_TIMER0,  PAGE = 1
   CpuTimer1RegsFile    : > CPU_TIMER1,  PAGE = 1
   CpuTimer2RegsFile    : > CPU_TIMER2,  PAGE = 1

   Dac1RegsFile          : > DAC1          PAGE = 1
   Dac2RegsFile          : > DAC2          PAGE = 1
   Dac3RegsFile          : > DAC3          PAGE = 1
   
   DcanaRegsFile		 : > DCANA,		   PAGE = 1
   DcanbRegsFile		 : > DCANB,		   PAGE = 1

   DcsmRegsZ1File		 : > DCSM_Z1,		   PAGE = 1
   DcsmRegsZ2File		 : > DCSM_Z2,		   PAGE = 1
   DcsmRegsCommonFile		 : > DCSM_COMMON,	   PAGE = 1

   DcsmOtpZ1File		 : > DCSM_OTP_Z1,	   PAGE = 1
   DcsmOtpZ2File		 : > DCSM_OTP_Z2,	   PAGE = 1

   DmaRegsFile           : > DMA           PAGE = 1
   DmaClaSrcSelRegsFile  : > DMACLASRCSEL  PAGE = 1

   ECap1RegsFile         : > ECAP1,        PAGE = 1
   ECap2RegsFile         : > ECAP2,        PAGE = 1
   ECap3RegsFile         : > ECAP3,        PAGE = 1
   ECap4RegsFile         : > ECAP4,        PAGE = 1
   ECap5RegsFile         : > ECAP5,        PAGE = 1
   ECap6RegsFile         : > ECAP6,        PAGE = 1
   
   Emif1RegsFile         : > EMIF1         PAGE = 1
   Emif2RegsFile         : > EMIF2         PAGE = 1

   EPwm1RegsFile         : > EPWM1,        PAGE = 1
   EPwm2RegsFile         : > EPWM2,        PAGE = 1
   EPwm3RegsFile         : > EPWM3,        PAGE = 1
   EPwm4RegsFile         : > EPWM4,        PAGE = 1
   EPwm5RegsFile         : > EPWM5,        PAGE = 1
   EPwm6RegsFile         : > EPWM6,        PAGE = 1
   EPwm7RegsFile         : > EPWM7,        PAGE = 1
   EPwm8RegsFile         : > EPWM8,        PAGE = 1
   EPwm9RegsFile         : > EPWM9,        PAGE = 1
   EPwm10RegsFile        : > EPWM10,       PAGE = 1
   EPwm11RegsFile        : > EPWM11,       PAGE = 1
   EPwm12RegsFile        : > EPWM12,       PAGE = 1

   EQep1RegsFile         : > EQEP1,        PAGE = 1
   EQep2RegsFile         : > EQEP2,        PAGE = 1
   EQep3RegsFile         : > EQEP3,        PAGE = 1

   GpioCtrlRegsFile      : > GPIOCTRL,     PAGE = 1
   GpioDataRegsFile      : > GPIODAT,      PAGE = 1

   FlashCtrlRegsFile     : > FLASH_CTRL    PAGE = 1
   FlashEccRegsFile      : > FLASH_ECC     PAGE = 1
   
   I2caRegsFile          : > I2CA,         PAGE = 1
   I2cbRegsFile          : > I2CB,         PAGE = 1
   IpcRegsFile           : > IPC,          PAGE = 1

   HwbistRegsFile        : > HWBIST        PAGE = 1

   MemCfgRegsFile        : > MEMCFG,       PAGE = 1
   McbspaRegsFile        : > MCBSPA,       PAGE = 1
   McbspbRegsFile        : > MCBSPB,       PAGE = 1

   NmiIntruptRegsFile    : > NMIINTRUPT,   PAGE = 1

   PieCtrlRegsFile       : > PIE_CTRL,     PAGE = 1

   SciaRegsFile         : > SCIA,         PAGE = 1
   ScibRegsFile         : > SCIB,         PAGE = 1
   ScicRegsFile         : > SCIC,         PAGE = 1
   ScidRegsFile         : > SCID,         PAGE = 1
   
   Sdfm1RegsFile		 : > SDFM1,		   PAGE = 1
   Sdfm2RegsFile		 : > SDFM2,		   PAGE = 1

   SpiaRegsFile          : > SPIA,        PAGE = 1
   SpibRegsFile          : > SPIB,        PAGE = 1
   SpicRegsFile          : > SPIC,        PAGE = 1

   DevCfgRegsFile       : > DEV_CFG,     PAGE = 1
   ClkCfgRegsFile       : > CLK_CFG,     PAGE = 1
   CpuSysRegsFile       : > CPU_SYS,     PAGE = 1

   TrigRegsFile          : > TRIG,         PAGE = 1

   WdRegsFile            : > WD,           PAGE = 1

   XbarConfigRegsFile    : > XBAR_CONFIG   PAGE = 1
   XintRegsFile          : > XINT          PAGE = 1
   MemCfgRegs		 : > MEMCFG        PAGE = 1

}

/*
//===========================================================================
// End of file.
//===========================================================================
*/
