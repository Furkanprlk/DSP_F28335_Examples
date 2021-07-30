################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
OBJS += \
C:/Flash28_API/Flash2802x_API_V100/example/Debug/DSP2802x_CSMPasswords.obj \
C:/Flash28_API/Flash2802x_API_V100/example/Debug/DSP2802x_CodeStartBranch.obj 

OBJS__QTD += \
"C:\Flash28_API\Flash2802x_API_V100\example\Debug\DSP2802x_CSMPasswords.obj" \
"C:\Flash28_API\Flash2802x_API_V100\example\Debug\DSP2802x_CodeStartBranch.obj" 


# Each subdirectory must supply rules for building sources it contributes
C:/Flash28_API/Flash2802x_API_V100/example/Debug/DSP2802x_CSMPasswords.obj: ../DSP2802x_common/source/DSP2802x_CSMPasswords.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --include_path="../DSP2802x_common/include" --include_path="../DSP2802x_common/source/DSP2802x_Headers/include" --quiet --diag_warning=225 --issue_remarks --large_memory_model --obj_directory="C:/Flash28_API/Flash2802x_API_V100/example/Debug" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

C:/Flash28_API/Flash2802x_API_V100/example/Debug/DSP2802x_CodeStartBranch.obj: ../DSP2802x_common/source/DSP2802x_CodeStartBranch.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --include_path="../DSP2802x_common/include" --include_path="../DSP2802x_common/source/DSP2802x_Headers/include" --quiet --diag_warning=225 --issue_remarks --large_memory_model --obj_directory="C:/Flash28_API/Flash2802x_API_V100/example/Debug" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


