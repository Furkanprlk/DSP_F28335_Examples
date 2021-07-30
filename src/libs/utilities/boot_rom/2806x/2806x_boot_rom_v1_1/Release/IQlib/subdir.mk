################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LIB_SRCS += \
../IQlib/IQmath.lib 

CMD_SRCS += \
../IQlib/TMS320x2806x_iqfuncs.cmd 


# Each subdirectory must supply rules for building sources it contributes
IQlib/IQmath.out: ../IQlib/IQmath.lib $(GEN_CMDS)
	@echo 'Building file: $<'
	@echo 'Invoking: Linker'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --diag_warning=225 --issue_remarks --large_memory_model -z -m"../IQlib/Release/2803x_boot_rom.map" --stack_size=0x200 --heap_size=0 --warn_sections -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/lib" -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" -i"C:/work/Octave_CCS_projects/collateral/Boot_ROM/2806x_boot_rom/boot_rom" -i"../flash_api" --reread_libs --xml_link_info="../IQlib/boot_rom.xml" --entry_point=_InitBoot -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


