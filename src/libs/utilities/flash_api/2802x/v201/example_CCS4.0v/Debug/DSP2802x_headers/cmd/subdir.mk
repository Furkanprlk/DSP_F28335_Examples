################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../DSP2802x_headers/cmd/DSP2802x_Headers_nonBIOS.cmd 


# Each subdirectory must supply rules for building sources it contributes
DSP2802x_headers/cmd/DSP2802x_Headers_nonBIOS.out: ../DSP2802x_headers/cmd/DSP2802x_Headers_nonBIOS.cmd $(OBJS)
	@echo 'Building file: $<'
	@echo 'Invoking: Linker'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --quiet --diag_warning=225 --issue_remarks --large_memory_model --obj_directory="C:/Flash28_API/Flash2802x_API_V100/example/Debug" -z -m"../DSP2802x_headers/cmd/Debug/Example_Flash2802x_API.map" --stack_size=0x200 --warn_sections -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/lib" -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" -i"C:/Flash28_API/Flash2802x_API_V201_CCS4.0v/example" --priority --reread_libs --entry_point=code_start --rom_model -o "$@" "$<" "../Example_Flash28027_API.cmd" "../2802x_FlashAPI_BootROMSymbols_v2.01.lib" "../rts2800_ml.lib" $(ORDERED_OBJS)
	@echo 'Finished building: $<'
	@echo ' '


