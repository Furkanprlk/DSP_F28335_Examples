#include "c2000BoardSupport.h"
#include "DSP2833x_Device.h"
#include "DSP2833x_Examples.h"
#include "DSP2833x_GlobalPrototypes.h"
#include "rtwtypes.h"
#include "adc_oku.h"
#include "adc_oku_private.h"

void InitXintf16Gpio();
void init_board ()
{
  DisableDog();

  /* Initialize the PLL control: PLLCR and DIVSEL
   * DSP28_PLLCR and DSP28_DIVSEL are defined in DSP2833x_Examples.h
   */
  InitPll(10,2);
  InitPeripheralClocks();
  EALLOW;

  /* Configure low speed peripheral clocks */
  SysCtrlRegs.LOSPCP.all = 0U;

  /* Configure high speed peripheral clocks */
  SysCtrlRegs.HISPCP.all = 1U;
  EDIS;
  EALLOW;

  /* Perform additional configuration of the XTINF for speed up */
  XintfRegs.XINTCNF2.bit.XTIMCLK = 0;  /* XTIMCLK=SYSCLKOUT/1*/
  XintfRegs.XINTCNF2.bit.CLKOFF = 0;   /* XCLKOUT is enabled*/
  XintfRegs.XINTCNF2.bit.CLKMODE = 0;  /* XCLKOUT = XTIMCLK*/

  /* Make sure write buffer is empty before configuring buffering depth*/
  while (XintfRegs.XINTCNF2.bit.WLEVEL != 0) ;/* poll the WLEVEL bit*/
  XintfRegs.XINTCNF2.bit.WRBUFF = 0;   /* No write buffering*/

  /* Example: Assume Zone 7 is slow, so add additional BCYC cycles whenever
   * switching from Zone 7 to another Zone.  This will help avoid bus contention.
   */
  XintfRegs.XBANK.bit.BCYC = 3;        /* Add 7 cycles*/
  XintfRegs.XBANK.bit.BANK = 3;        /* select zone 7*/

  /* Zone 0 Configuration */
  /*
     XintfRegs.XTIMING0.bit.X2TIMING = 0;       // Timing scale factor = 1
     XintfRegs.XTIMING0.bit.XSIZE = 3;          // Always write as 11b
     XintfRegs.XTIMING0.bit.READYMODE = 1;      // XREADY is asynchronous
     XintfRegs.XTIMING0.bit.USEREADY = 0;       // Disable XREADY
     XintfRegs.XTIMING0.bit.XRDLEAD = 1;        // Read lead time
     XintfRegs.XTIMING0.bit.XRDACTIVE = 2;      // Read active time
     XintfRegs.XTIMING0.bit.XRDTRAIL = 1;       // Read trail time
     XintfRegs.XTIMING0.bit.XWRLEAD = 1;        // Write lead time
     XintfRegs.XTIMING0.bit.XWRACTIVE = 2;      // Write active time
     XintfRegs.XTIMING0.bit.XWRTRAIL = 1;       // Write trail time
   */
  XintfRegs.XTIMING0.all = (XintfRegs.XTIMING0.all & ~0x43FFFF) | 0x394A9;

  /* Zone 6 Configuration */
  /*
     XintfRegs.XTIMING6.bit.X2TIMING = 0;       // Timing scale factor = 1
     XintfRegs.XTIMING6.bit.XSIZE = 3;          // Always write as 11b
     XintfRegs.XTIMING6.bit.READYMODE = 1;      // XREADY is asynchronous
     XintfRegs.XTIMING6.bit.USEREADY = 0;       // Disable XREADY
     XintfRegs.XTIMING6.bit.XRDLEAD = 1;        // Read lead time
     XintfRegs.XTIMING6.bit.XRDACTIVE = 2;      // Read active time
     XintfRegs.XTIMING6.bit.XRDTRAIL = 1;       // Read trail time
     XintfRegs.XTIMING6.bit.XWRLEAD = 1;        // Write lead time
     XintfRegs.XTIMING6.bit.XWRACTIVE = 2;      // Write active time
     XintfRegs.XTIMING6.bit.XWRTRAIL = 1;       // Write trail time
   */
  XintfRegs.XTIMING6.all = (XintfRegs.XTIMING6.all & ~0x43FFFF) | 0x394A9;

  /* Zone 7 Configuration */
  /*
     XintfRegs.XTIMING7.bit.X2TIMING = 0;       // Timing scale factor = 1
     XintfRegs.XTIMING7.bit.XSIZE = 3;          // Always write as 11b
     XintfRegs.XTIMING7.bit.READYMODE = 1;      // XREADY is asynchronous
     XintfRegs.XTIMING7.bit.USEREADY = 0;       // Disable XREADY
     XintfRegs.XTIMING7.bit.XRDLEAD = 1;        // Read lead time
     XintfRegs.XTIMING7.bit.XRDACTIVE = 2;      // Read active time
     XintfRegs.XTIMING7.bit.XRDTRAIL = 1;       // Read trail time
     XintfRegs.XTIMING7.bit.XWRLEAD = 1;        // Write lead time
     XintfRegs.XTIMING7.bit.XWRACTIVE = 2;      // Write active time
     XintfRegs.XTIMING7.bit.XWRTRAIL = 1;       // Write trail time
   */
  XintfRegs.XTIMING7.all = (XintfRegs.XTIMING7.all & ~0x43FFFF) | 0x394A9;
  EDIS;
  InitXintf16Gpio();

  /* Flush pipeline to ensure that the write is complete. Wait to be sure. */
  asm(" RPT #6 || NOP");

  /* Disable and clear all CPU interrupts */
  DINT;
  IER = 0x0000;
  IFR = 0x0000;
  InitPieCtrl();
  InitPieVectTable();
  InitCpuTimers();

  /* initial ePWM GPIO assignment... */
  config_ePWM_GPIO();
  EALLOW;

  /* Disable TBCLK within ePWM before module configuration */
  SysCtrlRegs.PCLKCR0.bit.TBCLKSYNC = 0;
  EDIS;

  /* initial GPIO qualification settings.... */
  EALLOW;
  GpioCtrlRegs.GPAQSEL1.all = 0x0;
  GpioCtrlRegs.GPAQSEL2.all = 0x0;
  GpioCtrlRegs.GPBQSEL1.all = 0x0;
  GpioCtrlRegs.GPBQSEL2.all = 0x0;
  EDIS;
}

void InitXintf16Gpio()
{
  EALLOW;

  /*
     GpioCtrlRegs.GPCMUX1.bit.GPIO64 = 3;  // XD15
     GpioCtrlRegs.GPCMUX1.bit.GPIO65 = 3;  // XD14
     GpioCtrlRegs.GPCMUX1.bit.GPIO66 = 3;  // XD13
     GpioCtrlRegs.GPCMUX1.bit.GPIO67 = 3;  // XD12
     GpioCtrlRegs.GPCMUX1.bit.GPIO68 = 3;  // XD11
     GpioCtrlRegs.GPCMUX1.bit.GPIO69 = 3;  // XD10
     GpioCtrlRegs.GPCMUX1.bit.GPIO70 = 3;  // XD19
     GpioCtrlRegs.GPCMUX1.bit.GPIO71 = 3;  // XD8
     GpioCtrlRegs.GPCMUX1.bit.GPIO72 = 3;  // XD7
     GpioCtrlRegs.GPCMUX1.bit.GPIO73 = 3;  // XD6
     GpioCtrlRegs.GPCMUX1.bit.GPIO74 = 3;  // XD5
     GpioCtrlRegs.GPCMUX1.bit.GPIO75 = 3;  // XD4
     GpioCtrlRegs.GPCMUX1.bit.GPIO76 = 3;  // XD3
     GpioCtrlRegs.GPCMUX1.bit.GPIO77 = 3;  // XD2
     GpioCtrlRegs.GPCMUX1.bit.GPIO78 = 3;  // XD1
     GpioCtrlRegs.GPCMUX1.bit.GPIO79 = 3;  // XD0

     GpioCtrlRegs.GPBMUX1.bit.GPIO40 = 3;  // XA0/XWE1n
     GpioCtrlRegs.GPBMUX1.bit.GPIO41 = 3;  // XA1
     GpioCtrlRegs.GPBMUX1.bit.GPIO42 = 3;  // XA2
     GpioCtrlRegs.GPBMUX1.bit.GPIO43 = 3;  // XA3
     GpioCtrlRegs.GPBMUX1.bit.GPIO44 = 3;  // XA4
     GpioCtrlRegs.GPBMUX1.bit.GPIO45 = 3;  // XA5
     GpioCtrlRegs.GPBMUX1.bit.GPIO46 = 3;  // XA6
     GpioCtrlRegs.GPBMUX1.bit.GPIO47 = 3;  // XA7

     GpioCtrlRegs.GPCMUX2.bit.GPIO80 = 3;  // XA8
     GpioCtrlRegs.GPCMUX2.bit.GPIO81 = 3;  // XA9
     GpioCtrlRegs.GPCMUX2.bit.GPIO82 = 3;  // XA10
     GpioCtrlRegs.GPCMUX2.bit.GPIO83 = 3;  // XA11
     GpioCtrlRegs.GPCMUX2.bit.GPIO84 = 3;  // XA12
     GpioCtrlRegs.GPCMUX2.bit.GPIO85 = 3;  // XA13
     GpioCtrlRegs.GPCMUX2.bit.GPIO86 = 3;  // XA14
     GpioCtrlRegs.GPCMUX2.bit.GPIO87 = 3;  // XA15
     GpioCtrlRegs.GPBMUX1.bit.GPIO39 = 3;  // XA16
     GpioCtrlRegs.GPAMUX2.bit.GPIO31 = 3;  // XA17
     GpioCtrlRegs.GPAMUX2.bit.GPIO30 = 3;  // XA18
     GpioCtrlRegs.GPAMUX2.bit.GPIO29 = 3;  // XA19

     GpioCtrlRegs.GPBMUX1.bit.GPIO34 = 3;  // XREADY
     GpioCtrlRegs.GPBMUX1.bit.GPIO35 = 3;  // XRNW
     GpioCtrlRegs.GPBMUX1.bit.GPIO38 = 3;  // XWE0

     GpioCtrlRegs.GPBMUX1.bit.GPIO36 = 3;  // XZCS0
     GpioCtrlRegs.GPBMUX1.bit.GPIO37 = 3;  // XZCS7
     GpioCtrlRegs.GPAMUX2.bit.GPIO28 = 3;  // XZCS6
   */
  GpioCtrlRegs.GPCMUX1.all = (GpioCtrlRegs.GPCMUX1.all & ~0xFFFFFFFF) |
    0xFFFFFFFF;
  GpioCtrlRegs.GPBMUX1.all = (GpioCtrlRegs.GPBMUX1.all & ~0xFFFFFFF0) |
    0xFFFFFFF0;
  GpioCtrlRegs.GPCMUX2.all = (GpioCtrlRegs.GPCMUX2.all & ~0xFFFF) | 0xFFFF;
  GpioCtrlRegs.GPAMUX2.all = (GpioCtrlRegs.GPAMUX2.all & ~0xFF000000) |
    0xFF000000;
  EDIS;
}
