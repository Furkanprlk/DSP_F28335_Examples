################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/Vectors_Boot.asm \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/c2brom_Init_Boot.asm \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/c2brom_utility_funcs.asm 

C_SRCS += \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/DCAN_Boot.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/I2C_Boot.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/Parallel_Boot.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/SCI_Boot.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/SPI_Boot.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/SelectMode_Boot.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/Shared_Boot.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/c2brom_boot.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/c2brom_checksum.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/c2core_bootrom_interrupts.c \
C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/c2core_bootrom_ipc_commands.c 

OBJS += \
./cpu02-bootROM/source/DCAN_Boot.obj \
./cpu02-bootROM/source/I2C_Boot.obj \
./cpu02-bootROM/source/Parallel_Boot.obj \
./cpu02-bootROM/source/SCI_Boot.obj \
./cpu02-bootROM/source/SPI_Boot.obj \
./cpu02-bootROM/source/SelectMode_Boot.obj \
./cpu02-bootROM/source/Shared_Boot.obj \
./cpu02-bootROM/source/Vectors_Boot.obj \
./cpu02-bootROM/source/c2brom_Init_Boot.obj \
./cpu02-bootROM/source/c2brom_boot.obj \
./cpu02-bootROM/source/c2brom_checksum.obj \
./cpu02-bootROM/source/c2brom_utility_funcs.obj \
./cpu02-bootROM/source/c2core_bootrom_interrupts.obj \
./cpu02-bootROM/source/c2core_bootrom_ipc_commands.obj 

ASM_DEPS += \
./cpu02-bootROM/source/Vectors_Boot.pp \
./cpu02-bootROM/source/c2brom_Init_Boot.pp \
./cpu02-bootROM/source/c2brom_utility_funcs.pp 

C_DEPS += \
./cpu02-bootROM/source/DCAN_Boot.pp \
./cpu02-bootROM/source/I2C_Boot.pp \
./cpu02-bootROM/source/Parallel_Boot.pp \
./cpu02-bootROM/source/SCI_Boot.pp \
./cpu02-bootROM/source/SPI_Boot.pp \
./cpu02-bootROM/source/SelectMode_Boot.pp \
./cpu02-bootROM/source/Shared_Boot.pp \
./cpu02-bootROM/source/c2brom_boot.pp \
./cpu02-bootROM/source/c2brom_checksum.pp \
./cpu02-bootROM/source/c2core_bootrom_interrupts.pp \
./cpu02-bootROM/source/c2core_bootrom_ipc_commands.pp 

C_DEPS__QUOTED += \
"cpu02-bootROM\source\DCAN_Boot.pp" \
"cpu02-bootROM\source\I2C_Boot.pp" \
"cpu02-bootROM\source\Parallel_Boot.pp" \
"cpu02-bootROM\source\SCI_Boot.pp" \
"cpu02-bootROM\source\SPI_Boot.pp" \
"cpu02-bootROM\source\SelectMode_Boot.pp" \
"cpu02-bootROM\source\Shared_Boot.pp" \
"cpu02-bootROM\source\c2brom_boot.pp" \
"cpu02-bootROM\source\c2brom_checksum.pp" \
"cpu02-bootROM\source\c2core_bootrom_interrupts.pp" \
"cpu02-bootROM\source\c2core_bootrom_ipc_commands.pp" 

OBJS__QUOTED += \
"cpu02-bootROM\source\DCAN_Boot.obj" \
"cpu02-bootROM\source\I2C_Boot.obj" \
"cpu02-bootROM\source\Parallel_Boot.obj" \
"cpu02-bootROM\source\SCI_Boot.obj" \
"cpu02-bootROM\source\SPI_Boot.obj" \
"cpu02-bootROM\source\SelectMode_Boot.obj" \
"cpu02-bootROM\source\Shared_Boot.obj" \
"cpu02-bootROM\source\Vectors_Boot.obj" \
"cpu02-bootROM\source\c2brom_Init_Boot.obj" \
"cpu02-bootROM\source\c2brom_boot.obj" \
"cpu02-bootROM\source\c2brom_checksum.obj" \
"cpu02-bootROM\source\c2brom_utility_funcs.obj" \
"cpu02-bootROM\source\c2core_bootrom_interrupts.obj" \
"cpu02-bootROM\source\c2core_bootrom_ipc_commands.obj" 

ASM_DEPS__QUOTED += \
"cpu02-bootROM\source\Vectors_Boot.pp" \
"cpu02-bootROM\source\c2brom_Init_Boot.pp" \
"cpu02-bootROM\source\c2brom_utility_funcs.pp" 

C_SRCS__QUOTED += \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/DCAN_Boot.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/I2C_Boot.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/Parallel_Boot.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/SCI_Boot.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/SPI_Boot.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/SelectMode_Boot.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/Shared_Boot.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/c2brom_boot.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/c2brom_checksum.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/c2core_bootrom_interrupts.c" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/c2core_bootrom_ipc_commands.c" 

ASM_SRCS__QUOTED += \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/Vectors_Boot.asm" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/c2brom_Init_Boot.asm" \
"C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/c2brom_utility_funcs.asm" 


