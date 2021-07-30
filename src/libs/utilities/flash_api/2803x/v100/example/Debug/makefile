################################################################################
# Automatically-generated file. Do not edit!
################################################################################

EMPTY := 
SPACE := $(EMPTY) $(EMPTY)

ORDERED_OBJS += \
"C:/Flash28_API/Flash2803x_API_V100/lib/2803x_FlashAPI_BootROMSymbols.lib" \
"C:/Flash28_API/Flash2803x_API_V100/lib/rts2800_ml.lib" \
"../Example_Flash28035_API.cmd" \
"../DSP2803x_headers/cmd/DSP2803x_Headers_nonBIOS.cmd" \
"C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug/DSP2803x_CodeStartBranch.obj" \
"C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug/DSP2803x_CSMPasswords.obj" \
"C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug/Example_Flash2803x_GlobalVariableDefs.obj" \
"C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug/Example_Flash2803x_CsmKeys.obj" \
"C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug/Example_Flash2803x_API.obj" \

-include ../makefile.init

RM := "C:/Program Files/Texas Instruments/ccsv4/utils/Cygwin/rm" -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include DSP2803x_headers/cmd/subdir.mk
-include DSP2803x_common/source/subdir.mk
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
all: Example_Flash2803x_API.out

# Tool invocations
Example_Flash2803x_API.out: $(GEN_CMDS) $(CMD_SRCS) $(LIB_SRCS) $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	$(shell echo -z > ccsLinker.opt)
	$(shell echo -m"Example_Flash2803x_API.map" >> ccsLinker.opt)
	$(shell echo --stack_size=0x200 >> ccsLinker.opt)
	$(shell echo --warn_sections >> ccsLinker.opt)
	$(shell echo -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/lib" -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" -i"C:/Flash28_API/Flash2803x_API_V100/example" >> ccsLinker.opt)
	$(shell echo --priority >> ccsLinker.opt)
	$(shell echo --reread_libs >> ccsLinker.opt)
	$(shell echo --entry_point=code_start >> ccsLinker.opt)
	$(shell echo --rom_model >> ccsLinker.opt)
	$(if $(strip $(GEN_CMDS_QUOTED)), $(shell echo $(GEN_CMDS_QUOTED) >> ccsLinker.opt))
	$(shell type ccsObjs.opt >> ccsLinker.opt)
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsLinker.opt -o "Example_Flash2803x_API.out"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(S62_DEPS)$(ASM_DEPS)$(C55_DEPS)$(S_UPPER_DEPS)$(S_DEPS)$(CPP_DEPS)$(C64_DEPS)$(C43_DEPS)$(C62_DEPS)$(OBJS)$(C??_DEPS)$(S??_DEPS)$(S55_DEPS)$(C_DEPS)$(C_UPPER_DEPS)$(SA_DEPS)$(C2000_EXECUTABLE_OUTPUTS)$(C++_DEPS)$(CC_DEPS)$(S64_DEPS)$(CXX_DEPS)$(S43_DEPS)$(S67_DEPS)$(C67_DEPS)$(ASM_UPPER_DEPS)$(OPT_DEPS) "Example_Flash2803x_API.out"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
