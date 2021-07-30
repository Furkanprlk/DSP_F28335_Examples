################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../DSP2803x_headers/cmd/DSP2803x_Headers_nonBIOS.cmd 


# Each subdirectory must supply rules for building sources it contributes
DSP2803x_headers/cmd/DSP2803x_Headers_nonBIOS.out: ../DSP2803x_headers/cmd/DSP2803x_Headers_nonBIOS.cmd $(OBJS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Linker'
	$(shell echo -z > ccsLinker.opt)
	$(shell echo -m"../DSP2803x_headers/cmd/Debug/Example_Flash2803x_API.map" >> ccsLinker.opt)
	$(shell echo --stack_size=0x200 >> ccsLinker.opt)
	$(shell echo --warn_sections >> ccsLinker.opt)
	$(shell echo -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/lib" -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" -i"C:/Flash28_API/Flash2803x_API_V100/example" >> ccsLinker.opt)
	$(shell echo --priority >> ccsLinker.opt)
	$(shell echo --reread_libs >> ccsLinker.opt)
	$(shell echo --entry_point=code_start >> ccsLinker.opt)
	$(shell echo --rom_model >> ccsLinker.opt)
	$(shell echo $< >> ccsLinker.opt)
	$(shell echo ../Example_Flash28035_API.cmd >> ccsLinker.opt)
	$(shell echo ../2803x_FlashAPI_BootROMSymbols.lib >> ccsLinker.opt)
	$(shell echo ../rts2800_ml.lib >> ccsLinker.opt)
	$(shell type ccsObjs.opt >> ccsLinker.opt)
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsLinker.opt -o "$@"
	@echo 'Finished building: $<'
	@echo ' '


