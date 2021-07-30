################################################################################
# Automatically-generated file. Do not edit!
################################################################################

EMPTY := 
SPACE := $(EMPTY) $(EMPTY)

ORDERED_OBJS += \
$(GEN_CMDS_QUOTED) \
"C:/Flash28_API/Flash2802x_API_V201_CCS4.0v/lib/rts2800_ml.lib" \
"../Example_Flash28027_API.cmd" \
"../DSP2802x_headers/cmd/DSP2802x_Headers_nonBIOS.cmd" \
"C:/Flash28_API/Flash2802x_API_V100/example/Debug/DSP2802x_CodeStartBranch.obj" \
"C:/Flash28_API/Flash2802x_API_V100/example/Debug/DSP2802x_CSMPasswords.obj" \
"C:/Flash28_API/Flash2802x_API_V100/example/Debug/Example_Flash2802x_GlobalVariableDefs.obj" \
"C:/Flash28_API/Flash2802x_API_V100/example/Debug/Example_Flash2802x_CsmKeys.obj" \
"C:/Flash28_API/Flash2802x_API_V100/example/Debug/Example_Flash2802x_API.obj" \
"C:/Flash28_API/Flash2802x_API_V201_CCS4.0v/lib/2802x_FlashAPI_BootROMSymbols_v2.01.lib" \

-include ../makefile.init

RM := DEL /F

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include DSP2802x_headers/cmd/subdir.mk
-include DSP2802x_common/source/subdir.mk
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
all: Example_Flash2802x_API.out

# Tool invocations
Example_Flash2802x_API.out: $(GEN_CMDS) $(CMD_SRCS) $(LIB_SRCS) $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Linker'
	$(shell echo --silicon_version=28 > ccsLinker.opt)
	$(shell echo -g >> ccsLinker.opt)
	$(shell echo --define="_DEBUG" --define="LARGE_MODEL" >> ccsLinker.opt)
	$(shell echo --quiet >> ccsLinker.opt)
	$(shell echo --diag_warning=225 >> ccsLinker.opt)
	$(shell echo --issue_remarks >> ccsLinker.opt)
	$(shell echo --large_memory_model >> ccsLinker.opt)
	$(shell echo --obj_directory="C:/Flash28_API/Flash2802x_API_V100/example/Debug" >> ccsLinker.opt)
	$(shell echo -z >> ccsLinker.opt)
	$(shell echo -m"Example_Flash2802x_API.map" >> ccsLinker.opt)
	$(shell echo --stack_size=0x200 >> ccsLinker.opt)
	$(shell echo --warn_sections >> ccsLinker.opt)
	$(shell echo -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/lib" -i"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" -i"C:/Flash28_API/Flash2802x_API_V201_CCS4.0v/example" >> ccsLinker.opt)
	$(shell echo --priority >> ccsLinker.opt)
	$(shell echo --reread_libs >> ccsLinker.opt)
	$(shell echo --entry_point=code_start >> ccsLinker.opt)
	$(shell echo --rom_model >> ccsLinker.opt)
	$(shell type ccsObjs.opt >> ccsLinker.opt)
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" -@ccsLinker.opt -o "Example_Flash2802x_API.out"
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C2000_EXECUTABLE_OUTPUTS__QTD) "Example_Flash2802x_API.out"
	-$(RM) "C:\Flash28_API\Flash2802x_API_V100\example\Debug\Example_Flash2802x_API.obj" "C:\Flash28_API\Flash2802x_API_V100\example\Debug\Example_Flash2802x_CsmKeys.obj" "C:\Flash28_API\Flash2802x_API_V100\example\Debug\Example_Flash2802x_GlobalVariableDefs.obj" "C:\Flash28_API\Flash2802x_API_V100\example\Debug\DSP2802x_CSMPasswords.obj" "C:\Flash28_API\Flash2802x_API_V100\example\Debug\DSP2802x_CodeStartBranch.obj" 
	-$(RM) ".\Example_Flash2802x_CsmKeys.pp" 
	-$(RM) ".\Example_Flash2802x_API.pp" ".\Example_Flash2802x_GlobalVariableDefs.pp" 
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
