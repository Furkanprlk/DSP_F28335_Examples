################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LIB_SRCS += \
C:/Flash28_API/Flash2802x_API_V201_CCS4.0v/lib/2802x_FlashAPI_BootROMSymbols_v2.01.lib \
C:/Flash28_API/Flash2802x_API_V201_CCS4.0v/lib/rts2800_ml.lib 

C_SRCS += \
../Example_Flash2802x_API.c \
../Example_Flash2802x_GlobalVariableDefs.c 

ASM_SRCS += \
../Example_Flash2802x_CsmKeys.asm 

CMD_SRCS += \
../Example_Flash28027_API.cmd 

ASM_DEPS += \
./Example_Flash2802x_CsmKeys.pp 

OBJS += \
C:/Flash28_API/Flash2802x_API_V100/example/Debug/Example_Flash2802x_API.obj \
C:/Flash28_API/Flash2802x_API_V100/example/Debug/Example_Flash2802x_CsmKeys.obj \
C:/Flash28_API/Flash2802x_API_V100/example/Debug/Example_Flash2802x_GlobalVariableDefs.obj 

C_DEPS += \
./Example_Flash2802x_API.pp \
./Example_Flash2802x_GlobalVariableDefs.pp 

OBJS__QTD += \
"C:\Flash28_API\Flash2802x_API_V100\example\Debug\Example_Flash2802x_API.obj" \
"C:\Flash28_API\Flash2802x_API_V100\example\Debug\Example_Flash2802x_CsmKeys.obj" \
"C:\Flash28_API\Flash2802x_API_V100\example\Debug\Example_Flash2802x_GlobalVariableDefs.obj" 

ASM_DEPS__QTD += \
".\Example_Flash2802x_CsmKeys.pp" 

C_DEPS__QTD += \
".\Example_Flash2802x_API.pp" \
".\Example_Flash2802x_GlobalVariableDefs.pp" 

C_SRCS_QUOTED += \
"../Example_Flash2802x_API.c" \
"../Example_Flash2802x_GlobalVariableDefs.c" 

ASM_SRCS_QUOTED += \
"../Example_Flash2802x_CsmKeys.asm" 


# Each subdirectory must supply rules for building sources it contributes
C:/Flash28_API/Flash2802x_API_V100/example/Debug/Example_Flash2802x_API.obj: ../Example_Flash2802x_API.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --include_path="C:/Flash28_API/Flash2802x_API_V201_CCS4.0v/include" --include_path="../DSP2802x_Headers/include" --quiet --diag_warning=225 --issue_remarks --large_memory_model --obj_directory="C:/Flash28_API/Flash2802x_API_V100/example/Debug" --preproc_with_compile --preproc_dependency="Example_Flash2802x_API.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

C:/Flash28_API/Flash2802x_API_V100/example/Debug/Example_Flash2802x_CsmKeys.obj: ../Example_Flash2802x_CsmKeys.asm $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --include_path="C:/Flash28_API/Flash2802x_API_V201_CCS4.0v/include" --include_path="../DSP2802x_Headers/include" --quiet --diag_warning=225 --issue_remarks --large_memory_model --obj_directory="C:/Flash28_API/Flash2802x_API_V100/example/Debug" --preproc_with_compile --preproc_dependency="Example_Flash2802x_CsmKeys.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

C:/Flash28_API/Flash2802x_API_V100/example/Debug/Example_Flash2802x_GlobalVariableDefs.obj: ../Example_Flash2802x_GlobalVariableDefs.c $(GEN_OPTS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c2000/include" --include_path="C:/Program Files/Texas Instruments/xdais_6_25_01_08/packages/ti/xdais" --include_path="C:/Flash28_API/Flash2802x_API_V201_CCS4.0v/include" --include_path="../DSP2802x_Headers/include" --quiet --diag_warning=225 --issue_remarks --large_memory_model --obj_directory="C:/Flash28_API/Flash2802x_API_V100/example/Debug" --preproc_with_compile --preproc_dependency="Example_Flash2802x_GlobalVariableDefs.pp" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


