################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
OBJS += \
C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug/DSP2803x_CSMPasswords.obj \
C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug/DSP2803x_CodeStartBranch.obj 


# Each subdirectory must supply rules for building sources it contributes
C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug/DSP2803x_CSMPasswords.obj: ../DSP2803x_common/source/DSP2803x_CSMPasswords.asm $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/Program Files/Texas Instruments/xdais_6_23/packages/ti/xdais" --include_path="../DSP2803x_common/include" --include_path="../DSP2803x_common/source/DSP2803x_Headers/include" --quiet --diag_warning=225 --issue_remarks --sat_reassoc=off --large_memory_model --fp_reassoc=off --obj_directory="C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug/DSP2803x_CodeStartBranch.obj: ../DSP2803x_common/source/DSP2803x_CodeStartBranch.asm $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/Program Files/Texas Instruments/xdais_6_23/packages/ti/xdais" --include_path="../DSP2803x_common/include" --include_path="../DSP2803x_common/source/DSP2803x_Headers/include" --quiet --diag_warning=225 --issue_remarks --sat_reassoc=off --large_memory_model --fp_reassoc=off --obj_directory="C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


