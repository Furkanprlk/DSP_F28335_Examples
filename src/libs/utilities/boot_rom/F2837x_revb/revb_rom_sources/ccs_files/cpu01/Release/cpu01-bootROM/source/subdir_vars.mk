################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/Vectors_Boot.asm \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/c1brom_Init_Boot.asm \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/c1brom_utility_funcs.asm 

C_SRCS += \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/DCAN_Boot.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/I2C_Boot.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/Parallel_Boot.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/SCI_Boot.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/SPI_Boot.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/SelectMode_Boot.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/Shared_Boot.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/USB_Boot.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/USB_Boot_Funcs.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/USB_Structs.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/c1brom_boot.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/c1brom_checksum.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/c1brom_interrupts.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/c1brom_ipc_commands.c 

OBJS += \
./cpu01-bootROM/source/DCAN_Boot.obj \
./cpu01-bootROM/source/I2C_Boot.obj \
./cpu01-bootROM/source/Parallel_Boot.obj \
./cpu01-bootROM/source/SCI_Boot.obj \
./cpu01-bootROM/source/SPI_Boot.obj \
./cpu01-bootROM/source/SelectMode_Boot.obj \
./cpu01-bootROM/source/Shared_Boot.obj \
./cpu01-bootROM/source/USB_Boot.obj \
./cpu01-bootROM/source/USB_Boot_Funcs.obj \
./cpu01-bootROM/source/USB_Structs.obj \
./cpu01-bootROM/source/Vectors_Boot.obj \
./cpu01-bootROM/source/c1brom_Init_Boot.obj \
./cpu01-bootROM/source/c1brom_boot.obj \
./cpu01-bootROM/source/c1brom_checksum.obj \
./cpu01-bootROM/source/c1brom_interrupts.obj \
./cpu01-bootROM/source/c1brom_ipc_commands.obj \
./cpu01-bootROM/source/c1brom_utility_funcs.obj 

ASM_DEPS += \
./cpu01-bootROM/source/Vectors_Boot.pp \
./cpu01-bootROM/source/c1brom_Init_Boot.pp \
./cpu01-bootROM/source/c1brom_utility_funcs.pp 

C_DEPS += \
./cpu01-bootROM/source/DCAN_Boot.pp \
./cpu01-bootROM/source/I2C_Boot.pp \
./cpu01-bootROM/source/Parallel_Boot.pp \
./cpu01-bootROM/source/SCI_Boot.pp \
./cpu01-bootROM/source/SPI_Boot.pp \
./cpu01-bootROM/source/SelectMode_Boot.pp \
./cpu01-bootROM/source/Shared_Boot.pp \
./cpu01-bootROM/source/USB_Boot.pp \
./cpu01-bootROM/source/USB_Boot_Funcs.pp \
./cpu01-bootROM/source/USB_Structs.pp \
./cpu01-bootROM/source/c1brom_boot.pp \
./cpu01-bootROM/source/c1brom_checksum.pp \
./cpu01-bootROM/source/c1brom_interrupts.pp \
./cpu01-bootROM/source/c1brom_ipc_commands.pp 

C_DEPS__QUOTED += \
"cpu01-bootROM\source\DCAN_Boot.pp" \
"cpu01-bootROM\source\I2C_Boot.pp" \
"cpu01-bootROM\source\Parallel_Boot.pp" \
"cpu01-bootROM\source\SCI_Boot.pp" \
"cpu01-bootROM\source\SPI_Boot.pp" \
"cpu01-bootROM\source\SelectMode_Boot.pp" \
"cpu01-bootROM\source\Shared_Boot.pp" \
"cpu01-bootROM\source\USB_Boot.pp" \
"cpu01-bootROM\source\USB_Boot_Funcs.pp" \
"cpu01-bootROM\source\USB_Structs.pp" \
"cpu01-bootROM\source\c1brom_boot.pp" \
"cpu01-bootROM\source\c1brom_checksum.pp" \
"cpu01-bootROM\source\c1brom_interrupts.pp" \
"cpu01-bootROM\source\c1brom_ipc_commands.pp" 

OBJS__QUOTED += \
"cpu01-bootROM\source\DCAN_Boot.obj" \
"cpu01-bootROM\source\I2C_Boot.obj" \
"cpu01-bootROM\source\Parallel_Boot.obj" \
"cpu01-bootROM\source\SCI_Boot.obj" \
"cpu01-bootROM\source\SPI_Boot.obj" \
"cpu01-bootROM\source\SelectMode_Boot.obj" \
"cpu01-bootROM\source\Shared_Boot.obj" \
"cpu01-bootROM\source\USB_Boot.obj" \
"cpu01-bootROM\source\USB_Boot_Funcs.obj" \
"cpu01-bootROM\source\USB_Structs.obj" \
"cpu01-bootROM\source\Vectors_Boot.obj" \
"cpu01-bootROM\source\c1brom_Init_Boot.obj" \
"cpu01-bootROM\source\c1brom_boot.obj" \
"cpu01-bootROM\source\c1brom_checksum.obj" \
"cpu01-bootROM\source\c1brom_interrupts.obj" \
"cpu01-bootROM\source\c1brom_ipc_commands.obj" \
"cpu01-bootROM\source\c1brom_utility_funcs.obj" 

ASM_DEPS__QUOTED += \
"cpu01-bootROM\source\Vectors_Boot.pp" \
"cpu01-bootROM\source\c1brom_Init_Boot.pp" \
"cpu01-bootROM\source\c1brom_utility_funcs.pp" 

C_SRCS__QUOTED += \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/DCAN_Boot.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/I2C_Boot.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/Parallel_Boot.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/SCI_Boot.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/SPI_Boot.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/SelectMode_Boot.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/Shared_Boot.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/USB_Boot.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/USB_Boot_Funcs.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/USB_Structs.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/c1brom_boot.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/c1brom_checksum.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/c1brom_interrupts.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/c1brom_ipc_commands.c" 

ASM_SRCS__QUOTED += \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/Vectors_Boot.asm" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/c1brom_Init_Boot.asm" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/c1brom_utility_funcs.asm" 


