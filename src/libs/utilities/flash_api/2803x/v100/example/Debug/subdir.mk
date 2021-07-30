################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LIB_SRCS += \
C:/Flash28_API/Flash2803x_API_V100/lib/2803x_FlashAPI_BootROMSymbols.lib \
C:/Flash28_API/Flash2803x_API_V100/lib/rts2800_ml.lib 

C_SRCS += \
../Example_Flash2803x_API.c \
../Example_Flash2803x_GlobalVariableDefs.c 

ASM_SRCS += \
../Example_Flash2803x_CsmKeys.asm 

CMD_SRCS += \
../Example_Flash28035_API.cmd 

ASM_DEPS += \
./Example_Flash2803x_CsmKeys.pp 

OBJS += \
C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug/Example_Flash2803x_API.obj \
C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug/Example_Flash2803x_CsmKeys.obj \
C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug/Example_Flash2803x_GlobalVariableDefs.obj 

C_DEPS += \
./Example_Flash2803x_API.pp \
./Example_Flash2803x_GlobalVariableDefs.pp 

C_SRCS_QUOTED += \
"../Example_Flash2803x_API.c" \
"../Example_Flash2803x_GlobalVariableDefs.c" 

ASM_SRCS_QUOTED += \
"../Example_Flash2803x_CsmKeys.asm" 


# Each subdirectory must supply rules for building sources it contributes
C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug/Example_Flash2803x_API.obj: ../Example_Flash2803x_API.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/Program Files/Texas Instruments/xdais_6_23/packages/ti/xdais" --include_path="C:/Flash28_API/Flash2803x_API_V100/include" --include_path="../DSP2803x_Headers/include" --quiet --diag_warning=225 --issue_remarks --sat_reassoc=off --large_memory_model --fp_reassoc=off --obj_directory="C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug" --preproc_with_compile --preproc_dependency="Example_Flash2803x_API.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug/Example_Flash2803x_CsmKeys.obj: ../Example_Flash2803x_CsmKeys.asm $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/Program Files/Texas Instruments/xdais_6_23/packages/ti/xdais" --include_path="C:/Flash28_API/Flash2803x_API_V100/include" --include_path="../DSP2803x_Headers/include" --quiet --diag_warning=225 --issue_remarks --sat_reassoc=off --large_memory_model --fp_reassoc=off --obj_directory="C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug" --preproc_with_compile --preproc_dependency="Example_Flash2803x_CsmKeys.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug/Example_Flash2803x_GlobalVariableDefs.obj: ../Example_Flash2803x_GlobalVariableDefs.c $(GEN_SRCS) $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/Program Files/Texas Instruments/xdais_6_23/packages/ti/xdais" --include_path="C:/Flash28_API/Flash2803x_API_V100/include" --include_path="../DSP2803x_Headers/include" --quiet --diag_warning=225 --issue_remarks --sat_reassoc=off --large_memory_model --fp_reassoc=off --obj_directory="C:/tidcs/c28/Flash28_API_1234/Flash2803x_API_V100_BUILD/example/Debug" --preproc_with_compile --preproc_dependency="Example_Flash2803x_GlobalVariableDefs.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


