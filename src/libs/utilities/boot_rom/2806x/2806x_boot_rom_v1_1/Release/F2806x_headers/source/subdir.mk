################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../F2806x_headers/source/F2806x_GlobalVariableDefs.c 

OBJS += \
./F2806x_headers/source/F2806x_GlobalVariableDefs.obj 

C_DEPS += \
./F2806x_headers/source/F2806x_GlobalVariableDefs.pp 

OBJS__QTD += \
".\F2806x_headers\source\F2806x_GlobalVariableDefs.obj" 

C_DEPS__QTD += \
".\F2806x_headers\source\F2806x_GlobalVariableDefs.pp" 

C_SRCS_QUOTED += \
"../F2806x_headers/source/F2806x_GlobalVariableDefs.c" 


# Each subdirectory must supply rules for building sources it contributes
F2806x_headers/source/F2806x_GlobalVariableDefs.obj: ../F2806x_headers/source/F2806x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning=225 --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="F2806x_headers/source/F2806x_GlobalVariableDefs.pp" --obj_directory="F2806x_headers/source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


