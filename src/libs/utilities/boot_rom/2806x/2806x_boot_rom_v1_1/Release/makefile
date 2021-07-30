################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

EMPTY := 
SPACE := $(EMPTY) $(EMPTY)

ORDERED_OBJS += \
$(GEN_CMDS_QUOTED) \
"./F2806x_headers/source/F2806x_GlobalVariableDefs.obj" \
"./source/rom_flash_api_table.obj" \
"./source/mac_plc.obj" \
"./source/Vectors_Boot.obj" \
"./source/SysCtrl_Boot.obj" \
"./source/Shared_Boot.obj" \
"./source/SelectMode_Boot.obj" \
"./source/SPI_Boot.obj" \
"./source/SCI_Boot.obj" \
"./source/Parallel_Boot.obj" \
"./source/Init_Boot.obj" \
"./source/ITRAPIsr.obj" \
"./source/IQmathTables.obj" \
"./source/IQNexpTable.obj" \
"./source/IQNasinTable.obj" \
"./source/I2C_Boot.obj" \
"./source/FPUmathTables.obj" \
"./source/CAN_Boot.obj" \
"../lnk/TMS320x2806x_boot_rom_lnk.cmd" \
"../flash_api/Flash2806x_API_V100.lib" \
"../flash_api/Flash2806x_APIfuncs.cmd" \
"../IQlib/IQmath.lib" \
"../IQlib/TMS320x2806x_iqfuncs.cmd" \
"../F2806x_headers/cmd/F2806x_Headers_nonBIOS.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include source/subdir.mk
-include lnk/subdir.mk
-include flash_api/subdir.mk
-include IQlib/subdir.mk
-include F2806x_headers/source/subdir.mk
-include F2806x_headers/cmd/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: TMS320x2806x_boot_rom.out

# Tool invocations
TMS320x2806x_boot_rom.out: $(OBJS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --diag_warning=225 --issue_remarks --large_memory_model -z -m"TMS320x2806x_boot_rom.map" --stack_size=0x200 --heap_size=0 --warn_sections -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/lib" -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" -i"C:/work/Octave_CCS_projects/collateral/Boot_ROM/2806x_boot_rom/boot_rom" -i"../flash_api" --reread_libs --xml_link_info="../boot_rom.xml" --entry_point=_InitBoot -o "TMS320x2806x_boot_rom.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C2000_EXECUTABLE_OUTPUTS__QTD) "TMS320x2806x_boot_rom.out"
	-$(RM) ".\source\CAN_Boot.obj" ".\source\FPUmathTables.obj" ".\source\I2C_Boot.obj" ".\source\IQNasinTable.obj" ".\source\IQNexpTable.obj" ".\source\IQmathTables.obj" ".\source\ITRAPIsr.obj" ".\source\Init_Boot.obj" ".\source\Parallel_Boot.obj" ".\source\SCI_Boot.obj" ".\source\SPI_Boot.obj" ".\source\SelectMode_Boot.obj" ".\source\Shared_Boot.obj" ".\source\SysCtrl_Boot.obj" ".\source\Vectors_Boot.obj" ".\source\mac_plc.obj" ".\source\rom_flash_api_table.obj" ".\F2806x_headers\source\F2806x_GlobalVariableDefs.obj" 
	-$(RM) ".\source\IQNasinTable.pp" ".\source\IQNexpTable.pp" ".\source\IQmathTables.pp" ".\source\ITRAPIsr.pp" ".\source\Init_Boot.pp" ".\source\Vectors_Boot.pp" ".\source\rom_flash_api_table.pp" 
	-$(RM) ".\source\CAN_Boot.pp" ".\source\I2C_Boot.pp" ".\source\Parallel_Boot.pp" ".\source\SCI_Boot.pp" ".\source\SPI_Boot.pp" ".\source\SelectMode_Boot.pp" ".\source\Shared_Boot.pp" ".\source\SysCtrl_Boot.pp" ".\source\mac_plc.pp" ".\F2806x_headers\source\F2806x_GlobalVariableDefs.pp" 
	-$(RM) ".\source\FPUmathTables.pp" 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
