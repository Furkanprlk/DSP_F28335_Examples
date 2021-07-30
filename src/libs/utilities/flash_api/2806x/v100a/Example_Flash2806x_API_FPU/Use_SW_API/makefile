################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4

ORDERED_OBJS += \
"./Example_Flash2806x_API.obj" \
"./Example_Flash2806x_CsmKeys.obj" \
"./F2806x_CodeStartBranch.obj" \
"./F2806x_GlobalVariableDefs.obj" \
"./F2806x_SysCtrl.obj" \
"./F2806x_usDelay.obj" \
"../Example_Flash2806x_SW_API.cmd" \
"C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_headers/cmd/F2806x_Headers_nonBIOS.cmd" \
"C:/ti/controlSUITE/libs/utilities/flash_api/2806x/v100a/lib/Flash2806x_API_wFPU_Library.lib" \
$(GEN_CMDS__FLAG) \
-l"libc.a" \
-l"Flash2806x_API_wFPU_Library.lib" \
-l"rts2800_fpu32.lib" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
Example_Flash2806x_API_FPU.out \

EXE_OUTPUTS__QUOTED += \
"Example_Flash2806x_API_FPU.out" \

BIN_OUTPUTS += \
Example_Flash2806x_API_FPU.hex \

BIN_OUTPUTS__QUOTED += \
"Example_Flash2806x_API_FPU.hex" \


# All Target
all: Example_Flash2806x_API_FPU.out

# Tool invocations
Example_Flash2806x_API_FPU.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=fpu32 --vcu_support=vcu0 -Ooff --define=_INLINE --define=SW_API --diag_warning=225 --display_error_number --diag_wrap=off -z -m"Example_Flash2806x_API_FPU.map" --stack_size=0x300 --warn_sections -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/lib" -i"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/include" -i"C:/ti/controlSUITE/libs/utilities/flash_api/2806x/v100a/lib" --reread_libs --display_error_number --diag_wrap=off --xml_link_info="Example_Flash2806x_API_FPU_linkInfo.xml" --rom_model -o "Example_Flash2806x_API_FPU.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

Example_Flash2806x_API_FPU.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: C2000 Hex Utility'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/bin/hex2000"  -o "Example_Flash2806x_API_FPU.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "Example_Flash2806x_API.pp" "F2806x_GlobalVariableDefs.pp" "F2806x_SysCtrl.pp" 
	-$(RM) "Example_Flash2806x_API.obj" "Example_Flash2806x_CsmKeys.obj" "F2806x_CodeStartBranch.obj" "F2806x_GlobalVariableDefs.obj" "F2806x_SysCtrl.obj" "F2806x_usDelay.obj" 
	-$(RM) "Example_Flash2806x_CsmKeys.pp" "F2806x_CodeStartBranch.pp" "F2806x_usDelay.pp" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

