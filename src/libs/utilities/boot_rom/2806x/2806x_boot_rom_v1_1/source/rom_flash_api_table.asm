;; TI File $Revision: /main/4 $
;; Checkin $Date: March 8, 2011   15:18:36 $
;;###########################################################################
;;
;; FILE:    rom_flash_api_table.asm
;;
;; TITLE:   defines the ROM API tables, exported to customers.
;;
;; Functions:
;;
;;     
;;     
;;
;; Notes:
;;
;;###########################################################################
;; $TI Release: TMS320x2806x Boot ROM V1.0 $
;; $Release Date: January 22, 2009 $
;;###########################################################################


	.def	_romApiTable_start
	.def	_rom_flash_ApiTable_start
	.def	__romApi_Flash2806x_Program
	.def	__romApi_Flash2806x_Erase
	.def	__romApi_Fl28x_EraseVerify
	.def	__romApi_Fl28x_ErasePulse
	.def	__romApi_Fl28x_LeaveCmdMode
	.def	__romApi_Fl28x_EnterCmdMode
	.def	__romApi_Fl28x_FlashRegSleep
	.def	__romApi_Fl28x_OpenPulse
	.def	__romApi_Fl28x_ClosePulse
	.def	__romApi_Fl28x_MaskAll
	.def	__romApi_Fl28x_ProgVerify
	.def	__romApi_Fl28x_ProgPulse
	.def	__romApi_Fl28x_CompactVerify
	.def	__romApi_Fl28x_CompactPulse
	.def	__romApi_Fl2806x_EraseSector
	.def	__romApi_Fl2806x_CompactSector
	.def	__romApi_Fl28x_DepRecoverCompactSector
	.def	__romApi_Fl28x_ClearLoop
	.def	__romApi_Flash2806x_Verify
	.def	__romApi_Fl2806x_ClearSector
	.def	__romApi_Flash2806x_DepRecover
	.def	__romApi_Fl2806x_Init
	.def	__romApi_Flash2806x_ToggleTest
	.def	__romApi_Fl28x_WatchDogDisable
	.def	__romApi_Fl28x_DisableNMI
	.def	__romApi_Fl28x_Delay
	.def	__romApi_Fl28x_DisableInt
	.def	__romApi_Fl28x_RestoreInt
	.def	__romApi_Flash2806x_APIVersionHex
	.def	_rom_flash_ApiTable_end
	.def	_rom_rom_ApiTable_start
	.def	_rom_rom_spi_boot
	.def	__rom_SPI_Boot
	.def	__rom_SPIA_SetAddress_KeyChk
	.def	__rom_SPIA_GetWordData
	.def	__rom_SelectBootMode
	.def	__rom_WaitBoot
	.def	__rom_CAN_Boot
	.def	__rom_CAN_Init
	.def	__rom_CAN_GetWordData
	.def	__rom_I2C_Boot
	.def	__rom_I2C_GetWord
	.def	__rom_Parallel_Boot
	.def	__rom_Parallel_GetWordData_8bit
	.def	__rom_SCI_Boot
	.def	__rom_SCIA_GetWordData
	.def	__rom_CopyData
	.def	__rom_GetLongData
	.def	__rom_ReadReservedFn
	.def	__rom_WatchDogDisable
	.def	__rom_WatchDogEnable
	.def	_rom_rom_ApiTable_end
	.def	_romApiTable_end
	

	.ref 	_Flash2806x_Program	
	.ref 	_Flash2806x_Erase
	.ref 	_Fl28x_EraseVerify
	.ref 	_Fl28x_ErasePulse
	.ref 	_Fl28x_LeaveCmdMode
	.ref 	_Fl28x_EnterCmdMode
	.ref 	_Fl28x_FlashRegSleep
	.ref 	_Fl28x_OpenPulse
	.ref 	_Fl28x_ClosePulse
	.ref 	_Fl28x_MaskAll
	.ref 	_Fl28x_ProgVerify
	.ref 	_Fl28x_ProgPulse
	.ref 	_Fl28x_CompactVerify
	.ref 	_Fl28x_CompactPulse
	.ref 	_Fl2806x_EraseSector
	.ref 	_Fl2806x_CompactSector
	.ref 	_Fl28x_DepRecoverCompactSector
	.ref 	_Fl28x_ClearLoop
	.ref 	_Flash2806x_Verify
	.ref 	_Fl2806x_ClearSector
	.ref 	_Flash2806x_DepRecover
	.ref 	_Fl2806x_Init
	.ref 	_Flash2806x_ToggleTest
	.ref 	_Fl28x_WatchDogDisable
	.ref 	_Fl28x_DisableNMI
	.ref 	_Fl28x_Delay
	.ref 	_Fl28x_DisableInt
	.ref 	_Fl28x_RestoreInt
	.ref 	_Flash2806x_APIVersionHex
	.ref 	_SPI_Boot
	.ref 	_SPIA_SetAddress_KeyChk
	.ref 	_SPIA_GetWordData
	.ref 	_SelectBootMode
	.ref 	_WaitBoot
	.ref 	_CAN_Boot
	.ref 	_CAN_Init
	.ref 	_CAN_GetWordData
	.ref 	_I2C_Boot
	.ref 	_I2C_GetWord
	.ref 	_Parallel_Boot
	.ref 	_Parallel_GetWordData_8bit
	.ref 	_SCI_Boot
	.ref 	_SCIA_GetWordData
	.ref 	_CopyData
	.ref 	_GetLongData
	.ref 	_ReadReservedFn
	.ref 	_WatchDogDisable
	.ref 	_WatchDogEnable
	 	

	.sect ".romApiTable" 
_romApiTable_start:
	.word	0x0100		;rom API table version v0.1
	.word	0x1010		; month/year (ex: 0x1010 = 10/10 = Oct 2010)
_rom_flash_ApiTable_start:
__romApi_Flash2806x_Program:
 	LB	_Flash2806x_Program
__romApi_Flash2806x_Erase:
 	LB	_Flash2806x_Erase
__romApi_Fl28x_EraseVerify:
 	LB	_Fl28x_EraseVerify
__romApi_Fl28x_ErasePulse:
 	LB	_Fl28x_ErasePulse
__romApi_Fl28x_LeaveCmdMode:
 	LB	_Fl28x_LeaveCmdMode
__romApi_Fl28x_EnterCmdMode:
 	LB	_Fl28x_EnterCmdMode
__romApi_Fl28x_FlashRegSleep:
 	LB	_Fl28x_FlashRegSleep
__romApi_Fl28x_OpenPulse:
 	LB	_Fl28x_OpenPulse
__romApi_Fl28x_ClosePulse:
 	LB	_Fl28x_ClosePulse
__romApi_Fl28x_MaskAll:
 	LB	_Fl28x_MaskAll
__romApi_Fl28x_ProgVerify:
 	LB	_Fl28x_ProgVerify
__romApi_Fl28x_ProgPulse:
 	LB	_Fl28x_ProgPulse
__romApi_Fl28x_CompactVerify:
 	LB	_Fl28x_CompactVerify
__romApi_Fl28x_CompactPulse:
 	LB	_Fl28x_CompactPulse
__romApi_Fl2806x_EraseSector:
 	LB	_Fl2806x_EraseSector
__romApi_Fl2806x_CompactSector:
 	LB	_Fl2806x_CompactSector
__romApi_Fl28x_DepRecoverCompactSector:
 	LB	_Fl28x_DepRecoverCompactSector
__romApi_Fl28x_ClearLoop:
	LB	_Fl28x_ClearLoop
__romApi_Flash2806x_Verify:
 	LB	_Flash2806x_Verify
__romApi_Fl2806x_ClearSector:
 	LB	_Fl2806x_ClearSector
__romApi_Flash2806x_DepRecover:
 	LB	_Flash2806x_DepRecover
__romApi_Fl2806x_Init:
 	LB	_Fl2806x_Init
__romApi_Flash2806x_ToggleTest:
 	LB	_Flash2806x_ToggleTest
__romApi_Fl28x_WatchDogDisable:
 	LB	_Fl28x_WatchDogDisable
__romApi_Fl28x_DisableNMI:
 	LB	_Fl28x_DisableNMI
__romApi_Fl28x_Delay:
 	LB	_Fl28x_Delay
__romApi_Fl28x_DisableInt:
 	LB	_Fl28x_DisableInt
__romApi_Fl28x_RestoreInt:
 	LB	_Fl28x_RestoreInt
__romApi_Flash2806x_APIVersionHex:
 	LB	_Flash2806x_APIVersionHex
_rom_flash_ApiTable_end:
_rom_rom_ApiTable_start:
_rom_rom_spi_boot:
__rom_SPI_Boot:
 	LB	_SPI_Boot
__rom_SPIA_SetAddress_KeyChk:
 	LB	_SPIA_SetAddress_KeyChk
__rom_SPIA_GetWordData:
 	LB	_SPIA_GetWordData
__rom_SelectBootMode:
 	LB	_SelectBootMode
__rom_WaitBoot:
 	LB	_WaitBoot
__rom_CAN_Boot:
 	LB	_CAN_Boot
__rom_CAN_Init:
 	LB	_CAN_Init
__rom_CAN_GetWordData:
 	LB	_CAN_GetWordData
__rom_I2C_Boot:
 	LB	_I2C_Boot
__rom_I2C_GetWord:
 	LB	_I2C_GetWord
__rom_Parallel_Boot:
 	LB	_Parallel_Boot
__rom_Parallel_GetWordData_8bit:
 	LB	_Parallel_GetWordData_8bit
__rom_SCI_Boot:
 	LB	_SCI_Boot
__rom_SCIA_GetWordData:
 	LB	_SCIA_GetWordData
__rom_CopyData:
 	LB	_CopyData
__rom_GetLongData:
 	LB	_GetLongData
__rom_ReadReservedFn:
 	LB	_ReadReservedFn
__rom_WatchDogDisable:
 	LB	_WatchDogDisable
__rom_WatchDogEnable:
 	LB	_WatchDogEnable
_rom_rom_ApiTable_end:
_romApiTable_end:

 	