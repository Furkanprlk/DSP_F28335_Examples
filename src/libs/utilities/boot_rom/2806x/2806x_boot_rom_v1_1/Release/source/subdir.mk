################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/CAN_Boot.c \
../source/I2C_Boot.c \
../source/Parallel_Boot.c \
../source/SCI_Boot.c \
../source/SPI_Boot.c \
../source/SelectMode_Boot.c \
../source/Shared_Boot.c \
../source/SysCtrl_Boot.c 

ASM_SRCS += \
../source/IQNasinTable.asm \
../source/IQNexpTable.asm \
../source/IQmathTables.asm \
../source/ITRAPIsr.asm \
../source/Init_Boot.asm \
../source/Vectors_Boot.asm \
../source/rom_flash_api_table.asm 

ASM_UPPER_SRCS += \
../source/FPUmathTables.ASM 

ASM_DEPS += \
./source/IQNasinTable.pp \
./source/IQNexpTable.pp \
./source/IQmathTables.pp \
./source/ITRAPIsr.pp \
./source/Init_Boot.pp \
./source/Vectors_Boot.pp \
./source/rom_flash_api_table.pp 

OBJS += \
./source/CAN_Boot.obj \
./source/FPUmathTables.obj \
./source/I2C_Boot.obj \
./source/IQNasinTable.obj \
./source/IQNexpTable.obj \
./source/IQmathTables.obj \
./source/ITRAPIsr.obj \
./source/Init_Boot.obj \
./source/Parallel_Boot.obj \
./source/SCI_Boot.obj \
./source/SPI_Boot.obj \
./source/SelectMode_Boot.obj \
./source/Shared_Boot.obj \
./source/SysCtrl_Boot.obj \
./source/Vectors_Boot.obj \
./source/mac_plc.obj \
./source/rom_flash_api_table.obj 

C_DEPS += \
./source/CAN_Boot.pp \
./source/I2C_Boot.pp \
./source/Parallel_Boot.pp \
./source/SCI_Boot.pp \
./source/SPI_Boot.pp \
./source/SelectMode_Boot.pp \
./source/Shared_Boot.pp \
./source/SysCtrl_Boot.pp \
./source/mac_plc.pp 

ASM_UPPER_DEPS += \
./source/FPUmathTables.pp 

OBJS__QTD += \
".\source\CAN_Boot.obj" \
".\source\FPUmathTables.obj" \
".\source\I2C_Boot.obj" \
".\source\IQNasinTable.obj" \
".\source\IQNexpTable.obj" \
".\source\IQmathTables.obj" \
".\source\ITRAPIsr.obj" \
".\source\Init_Boot.obj" \
".\source\Parallel_Boot.obj" \
".\source\SCI_Boot.obj" \
".\source\SPI_Boot.obj" \
".\source\SelectMode_Boot.obj" \
".\source\Shared_Boot.obj" \
".\source\SysCtrl_Boot.obj" \
".\source\Vectors_Boot.obj" \
".\source\mac_plc.obj" \
".\source\rom_flash_api_table.obj" 

ASM_DEPS__QTD += \
".\source\IQNasinTable.pp" \
".\source\IQNexpTable.pp" \
".\source\IQmathTables.pp" \
".\source\ITRAPIsr.pp" \
".\source\Init_Boot.pp" \
".\source\Vectors_Boot.pp" \
".\source\rom_flash_api_table.pp" 

C_DEPS__QTD += \
".\source\CAN_Boot.pp" \
".\source\I2C_Boot.pp" \
".\source\Parallel_Boot.pp" \
".\source\SCI_Boot.pp" \
".\source\SPI_Boot.pp" \
".\source\SelectMode_Boot.pp" \
".\source\Shared_Boot.pp" \
".\source\SysCtrl_Boot.pp" \
".\source\mac_plc.pp" 

ASM_UPPER_DEPS__QTD += \
".\source\FPUmathTables.pp" 

C_SRCS_QUOTED += \
"../source/CAN_Boot.c" \
"../source/I2C_Boot.c" \
"../source/Parallel_Boot.c" \
"../source/SCI_Boot.c" \
"../source/SPI_Boot.c" \
"../source/SelectMode_Boot.c" \
"../source/Shared_Boot.c" \
"../source/SysCtrl_Boot.c" 

ASM_UPPER_SRCS_QUOTED += \
"../source/FPUmathTables.ASM" 

ASM_SRCS_QUOTED += \
"../source/IQNasinTable.asm" \
"../source/IQNexpTable.asm" \
"../source/IQmathTables.asm" \
"../source/ITRAPIsr.asm" \
"../source/Init_Boot.asm" \
"../source/Vectors_Boot.asm" \
"../source/rom_flash_api_table.asm" 


# Each subdirectory must supply rules for building sources it contributes
source/CAN_Boot.obj: ../source/CAN_Boot.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning=225 --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="source/CAN_Boot.pp" --obj_directory="source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

source/FPUmathTables.obj: ../source/FPUmathTables.ASM $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning=225 --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="source/FPUmathTables.pp" --obj_directory="source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

source/I2C_Boot.obj: ../source/I2C_Boot.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning=225 --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="source/I2C_Boot.pp" --obj_directory="source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

source/IQNasinTable.obj: ../source/IQNasinTable.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning=225 --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="source/IQNasinTable.pp" --obj_directory="source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

source/IQNexpTable.obj: ../source/IQNexpTable.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning=225 --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="source/IQNexpTable.pp" --obj_directory="source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

source/IQmathTables.obj: ../source/IQmathTables.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning=225 --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="source/IQmathTables.pp" --obj_directory="source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

source/ITRAPIsr.obj: ../source/ITRAPIsr.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning=225 --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="source/ITRAPIsr.pp" --obj_directory="source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

source/Init_Boot.obj: ../source/Init_Boot.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning=225 --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="source/Init_Boot.pp" --obj_directory="source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

source/Parallel_Boot.obj: ../source/Parallel_Boot.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning=225 --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="source/Parallel_Boot.pp" --obj_directory="source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

source/SCI_Boot.obj: ../source/SCI_Boot.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning=225 --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="source/SCI_Boot.pp" --obj_directory="source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

source/SPI_Boot.obj: ../source/SPI_Boot.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning=225 --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="source/SPI_Boot.pp" --obj_directory="source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

source/SelectMode_Boot.obj: ../source/SelectMode_Boot.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning=225 --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="source/SelectMode_Boot.pp" --obj_directory="source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

source/Shared_Boot.obj: ../source/Shared_Boot.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning=225 --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="source/Shared_Boot.pp" --obj_directory="source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

source/SysCtrl_Boot.obj: ../source/SysCtrl_Boot.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning=225 --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="source/SysCtrl_Boot.pp" --obj_directory="source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

source/Vectors_Boot.obj: ../source/Vectors_Boot.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning=225 --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="source/Vectors_Boot.pp" --obj_directory="source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

source/mac_plc.obj: ../source/mac_plc.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning="225" --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="source/mac_plc.pp" --obj_directory="source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '

source/rom_flash_api_table.obj: ../source/rom_flash_api_table.asm $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: Compiler'
	"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/bin/cl2000" --silicon_version=28 -g --define="_DEBUG" --define="LARGE_MODEL" --include_path="C:/Program Files/Texas Instruments/ccsv4/tools/compiler/C2000 Code Generation Tools 5.2.10/include" --include_path="../include" --include_path="../F2806x_headers/include" --include_path="/packages/ti/xdais" --quiet --diag_warning=225 --issue_remarks --large_memory_model --preproc_with_compile --preproc_dependency="source/rom_flash_api_table.pp" --obj_directory="source" $(GEN_OPTS_QUOTED) $(subst #,$(wildcard $(subst $(SPACE),\$(SPACE),$<)),"#")
	@echo 'Finished building: $<'
	@echo ' '


