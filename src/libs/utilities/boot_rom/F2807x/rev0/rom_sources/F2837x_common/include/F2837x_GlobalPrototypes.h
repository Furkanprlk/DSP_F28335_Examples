//###########################################################################
//
// FILE:   F2837x_GlobalPrototypes.h
//
// TITLE:  Global prototypes for F2837x Examples
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
//###########################################################################

#ifndef F2837x_GLOBALPROTOTYPES_H
#define F2837x_GLOBALPROTOTYPES_H

#ifdef __cplusplus
extern "C" {
#endif

/*---- shared global function prototypes -----------------------------------*/
extern void EnableInterrupts(void);
extern void InitAPwm1Gpio(void);
extern void InitECap(void);
extern void InitECapGpio(void);
extern void InitECap1Gpio(Uint16 pin);
extern void InitECap2Gpio(Uint16 pin);
extern void InitECap3Gpio(Uint16 pin);
extern void InitECap4Gpio(Uint16 pin);
extern void InitECap5Gpio(Uint16 pin);
extern void InitECap6Gpio(Uint16 pin);
extern void InitEQep1Gpio(void);
extern void InitEQep2Gpio(void);
extern void InitEQep3Gpio(void);
extern void InitEPwmGpio(void);
extern void InitEPwm1Gpio(void);
extern void InitEPwm2Gpio(void);
extern void InitEPwm3Gpio(void);
extern void InitEPwm4Gpio(void);
extern void InitEPwm5Gpio(void);
extern void InitEPwm6Gpio(void);
extern void InitEPwm7Gpio(void);
extern void InitEPwm8Gpio(void);
extern void InitEPwm9Gpio(void);
extern void InitEPwm10Gpio(void);
extern void InitEPwm11Gpio(void);
extern void InitEPwm12Gpio(void);
extern void InitPeripheralClocks(void);
extern void InitPieCtrl(void);
extern void InitPieVectTable(void);
extern void InitSpiGpio(void);
extern void InitSpiaGpio(void);
extern void InitSysCtrl(void);

//LPM functions in F2837x_SysCtrl.c
void IDLE();
void STANDBY();
void HALT();
void HIB();

// DMA Functions
extern void DMAInitialize(void);
// DMA Channel 1
extern void DMACH1AddrConfig(volatile Uint16 *DMA_Dest,
                             volatile Uint16 *DMA_Source);
extern void DMACH1BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep);
extern void DMACH1TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep);
extern void DMACH1WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize,
                             int16 deswstep);
extern void DMACH1ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot,
                             Uint16 cont, Uint16 synce, Uint16 syncsel,
                             Uint16 ovrinte, Uint16 datasize,
                             Uint16 chintmode,
                             Uint16 chinte);
extern void StartDMACH1(void);
// DMA Channel 2
extern void DMACH2AddrConfig(volatile Uint16 *DMA_Dest,
                             volatile Uint16 *DMA_Source);
extern void DMACH2BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep);
extern void DMACH2TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep);
extern void DMACH2WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize,
                             int16 deswstep);
extern void DMACH2ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot,
                             Uint16 cont, Uint16 synce, Uint16 syncsel,
                             Uint16 ovrinte, Uint16 datasize,
                             Uint16 chintmode,
                             Uint16 chinte);
extern void StartDMACH2(void);
// DMA Channel 3
extern void DMACH3AddrConfig(volatile Uint16 *DMA_Dest,
                             volatile Uint16 *DMA_Source);
extern void DMACH3BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep);
extern void DMACH3TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep);
extern void DMACH3WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize,
                             int16 deswstep);
extern void DMACH3ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot,
                             Uint16 cont, Uint16 synce, Uint16 syncsel,
                             Uint16 ovrinte, Uint16 datasize,
                             Uint16 chintmode,
                             Uint16 chinte);
extern void StartDMACH3(void);
// DMA Channel 4
extern void DMACH4AddrConfig(volatile Uint16 *DMA_Dest,
                             volatile Uint16 *DMA_Source);
extern void DMACH4BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep);
extern void DMACH4TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep);
extern void DMACH4WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize,
                             int16 deswstep);
extern void DMACH4ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot,
                             Uint16 cont, Uint16 synce, Uint16 syncsel,
                             Uint16 ovrinte, Uint16 datasize,
                             Uint16 chintmode,
                             Uint16 chinte);
extern void StartDMACH4(void);
// DMA Channel 5
extern void DMACH5AddrConfig(volatile Uint16 *DMA_Dest,
                             volatile Uint16 *DMA_Source);
extern void DMACH5BurstConfig(Uint16 bsize, int16 srcbstep, int16 desbstep);
extern void DMACH5TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep);
extern void DMACH5WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize,
                             int16 deswstep);
extern void DMACH5ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot,
                             Uint16 cont, Uint16 synce, Uint16 syncsel,
                             Uint16 ovrinte, Uint16 datasize,
                             Uint16 chintmode,
                             Uint16 chinte);
extern void StartDMACH5(void);
// DMA Channel 6
extern void DMACH6AddrConfig(volatile Uint16 *DMA_Dest,
                             volatile Uint16 *DMA_Source);
extern void DMACH6BurstConfig(Uint16 bsize,Uint16 srcbstep, int16 desbstep);
extern void DMACH6TransferConfig(Uint16 tsize, int16 srctstep, int16 deststep);
extern void DMACH6WrapConfig(Uint16 srcwsize, int16 srcwstep, Uint16 deswsize,
                             int16 deswstep);
extern void DMACH6ModeConfig(Uint16 persel, Uint16 perinte, Uint16 oneshot,
                             Uint16 cont, Uint16 synce, Uint16 syncsel,
                             Uint16 ovrinte, Uint16 datasize,
                             Uint16 chintmode,
                             Uint16 chinte);
extern void StartDMACH6(void);


//GPIO Functions
extern void InitGpio();
extern void GPIO_SetupPinMux(Uint16 pin, Uint16 cpu, Uint16 peripheral);
extern void GPIO_SetupPinOptions(Uint16 pin, Uint16 output, Uint16 flags);
extern void GPIO_SelectIpcInt(Uint16 newFlag);
Uint16 GPIO_ReadPin(Uint16 pin);
void GPIO_WritePin(Uint16 pin, Uint16 outVal);


//IPC Functions
extern void InitIpc();
extern Uint64 ReadIpcTimer();
extern void SendIpcData(void *data, Uint16 word_length, Uint16 flag);
extern void RecvIpcData(void *recv_buf, Uint16 word_length);
extern void FillIpcSendData(Uint16 fill_data);
extern void SendIpcCommand(Uint32 command, Uint32 address, Uint32 data, Uint16 flag);
extern void SendIpcFlag(Uint16 flag);
extern void AckIpcFlag(Uint16 flag);
extern void CancelIpcFlag(Uint16 flag);
extern void WaitForIpcFlag(Uint16 flag);
extern void WaitForIpcAck(Uint16 flag);
extern void IpcSync(Uint16 flag);
extern void SeizeFlashPump();
extern void ReleaseFlashPump();

// CAN Functions
extern void CanGpioPinMuxing(Uint32 ulBase, Uint16 canTxRxPin);
extern void CanAGpioConfig(Uint16 canaTxRxPin);
extern void CanBGpioConfig(Uint16 canbTxRxPin);
extern void CanModuleClkSelect(Uint32 ulBase, Uint16 ucSource);

// I2C Functions
extern void I2cAGpioConfig(Uint16 I2caDataClkPin);
extern void I2cBGpioConfig(Uint16 I2cbDataClkPin);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif   // - end of F2837x_GLOBALPROTOTYPES_H

//===========================================================================
// End of file.
//===========================================================================
