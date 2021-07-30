###########################################################################
## Makefile generated for component 'adc_oku'. 
## 
## Makefile     : adc_oku.mk
## Generated on : Wed May 26 13:28:54 2021
## Final product: $(RELATIVE_PATH_TO_ANCHOR)/adc_oku.out
## Product type : executable
## 
###########################################################################

###########################################################################
## MACROS
###########################################################################

# Macro Descriptions:
# PRODUCT_NAME            Name of the system to build
# MAKEFILE                Name of this makefile

PRODUCT_NAME              = adc_oku
MAKEFILE                  = adc_oku.mk
MATLAB_ROOT               = F:/Program Files/Polyspace/R2020b
MATLAB_BIN                = F:/Program Files/Polyspace/R2020b/bin
MATLAB_ARCH_BIN           = $(MATLAB_BIN)/win64
START_DIR                 = C:/Users/furka/Desktop/Furkan_dosya/adc_oku
SOLVER                    = 
SOLVER_OBJ                = 
CLASSIC_INTERFACE         = 0
TGT_FCN_LIB               = TI C28x
MODEL_HAS_DYNAMICALLY_LOADED_SFCNS = 0
RELATIVE_PATH_TO_ANCHOR   = ..
C_STANDARD_OPTS           = 
CPP_STANDARD_OPTS         = 

###########################################################################
## TOOLCHAIN SPECIFICATIONS
###########################################################################

# Toolchain Name:          Texas Instruments Code Composer Studio (C2000)
# Supported Version(s):    
# ToolchainInfo Version:   2020b
# Specification Revision:  1.0
# 
#-------------------------------------------
# Macros assumed to be defined elsewhere
#-------------------------------------------

# CCSINSTALLDIR
# CCSSCRIPTINGDIR
# TARGET_LOAD_CMD_ARGS
# TIF28XXXSYSSWDIR

#-----------
# MACROS
#-----------

TARGET_SCRIPTINGTOOLS_INSTALLDIR = $(CCSSCRIPTINGDIR)
TI_TOOLS                         = $(CCSINSTALLDIR)/bin
TI_INCLUDE                       = $(CCSINSTALLDIR)/include
TI_LIB                           = $(CCSINSTALLDIR)/lib
F28_HEADERS                      = $(TIF28XXXSYSSWDIR)/~SupportFiles/DSP280x_headers
CCOUTPUTFLAG                     = --output_file=
LDOUTPUTFLAG                     = --output_file=
EXE_FILE_EXT                     = $(PROGRAM_FILE_EXT)
PRODUCT_HEX                      = $(RELATIVE_PATH_TO_ANCHOR)/$(PRODUCT_NAME).hex
DOWN_EXE_JS                      = $(TARGET_PKG_INSTALLDIR)/tic2000/CCS_Config/runProgram_generic.js
CCS_CONFIG                       = $(TARGET_PKG_INSTALLDIR)/tic2000/CCS_Config/f28x_generic.ccxml
SHELL                            = %SystemRoot%/system32/cmd.exe

TOOLCHAIN_SRCS = 
TOOLCHAIN_INCS = 
TOOLCHAIN_LIBS = 

#------------------------
# BUILD TOOL COMMANDS
#------------------------

# Assembler: C2000 Assembler
AS_PATH = $(TI_TOOLS)
AS = "$(AS_PATH)/cl2000"

# C Compiler: C2000 C Compiler
CC_PATH = $(TI_TOOLS)
CC = "$(CC_PATH)/cl2000"

# Linker: C2000 Linker
LD_PATH = $(TI_TOOLS)
LD = "$(LD_PATH)/cl2000"

# C++ Compiler: C2000 C++ Compiler
CPP_PATH = $(TI_TOOLS)
CPP = "$(CPP_PATH)/cl2000"

# C++ Linker: C2000 C++ Linker
CPP_LD_PATH = $(TI_TOOLS)
CPP_LD = "$(CPP_LD_PATH)/cl2000"

# Archiver: C2000 Archiver
AR_PATH = $(TI_TOOLS)
AR = "$(AR_PATH)/ar2000"

# MEX Tool: MEX Tool
MEX_PATH = $(MATLAB_ARCH_BIN)
MEX = "$(MEX_PATH)/mex"

# Hex Converter: Hex Converter

# Download: Download
DOWNLOAD_PATH = $(TARGET_SCRIPTINGTOOLS_INSTALLDIR)/bin
DOWNLOAD = "$(DOWNLOAD_PATH)/dss.bat"

# Execute: Execute
EXECUTE = $(PRODUCT)

# Builder: GMAKE Utility
MAKE_PATH = %MATLAB%\bin\win64
MAKE = "$(MAKE_PATH)/gmake"


#-------------------------
# Directives/Utilities
#-------------------------

ASDEBUG             = -g
AS_OUTPUT_FLAG      = --output_file=
CDEBUG              = -g
C_OUTPUT_FLAG       = --output_file=
LDDEBUG             =
OUTPUT_FLAG         = --output_file=
CPPDEBUG            = -g
CPP_OUTPUT_FLAG     = --output_file=
CPPLDDEBUG          =
OUTPUT_FLAG         = --output_file=
ARDEBUG             =
STATICLIB_OUTPUT_FLAG =
MEX_DEBUG           = -g
RM                  = @del /F
ECHO                = @echo
MV                  = @move
RUN                 =

#----------------------------------------
# "Faster Builds" Build Configuration
#----------------------------------------

ARFLAGS              = -r
ASFLAGS              = -s \
                       -v28 \
                       -ml \
                       $(ASFLAGS_ADDITIONAL)
CFLAGS               = --compile_only \
                       --preproc_dependency="$(@:%.obj=%.dep)" --preproc_with_compile  \
                       --large_memory_model \
                       --silicon_version=28 \
                       --define="LARGE_MODEL" \
                       -I"$(F28_HEADERS)" \
                       -I"$(F28_HEADERS)/include" \
                       -I"$(TI_INCLUDE)"
CPPFLAGS             =
CPP_LDFLAGS          =
CPP_SHAREDLIB_LDFLAGS  =
DOWNLOAD_FLAGS       = $(TARGET_LOAD_CMD_ARGS) $(PRODUCT)
EXECUTE_FLAGS        =
OBJCOPYFLAGS_HEX     =  -i "$<" -o "$@" -order MS -romwidth 16 -q
LDFLAGS              = -z -I$(TI_LIB) \
                       --stack_size=$(STACK_SIZE) --warn_sections \
                       --heap_size=$(HEAP_SIZE) \
                       --reread_libs --rom_model \
                       --priority \
                       -m"$(PRODUCT_NAME).map"
MEX_CPPFLAGS         =
MEX_CPPLDFLAGS       =
MEX_CFLAGS           =
MEX_LDFLAGS          =
MAKE_FLAGS           = -f $(MAKEFILE)
SHAREDLIB_LDFLAGS    =



###########################################################################
## OUTPUT INFO
###########################################################################

PRODUCT = $(RELATIVE_PATH_TO_ANCHOR)/adc_oku.out
PRODUCT_TYPE = "executable"
BUILD_TYPE = "Top-Level Standalone Executable"

###########################################################################
## INCLUDE PATHS
###########################################################################

INCLUDES_BUILDINFO = -I$(START_DIR) -I$(START_DIR)/adc_oku_ert_rtw -I$(MATLAB_ROOT)/extern/include -I$(MATLAB_ROOT)/simulink/include -I$(MATLAB_ROOT)/rtw/c/src -I$(MATLAB_ROOT)/rtw/c/src/ext_mode/common -I$(MATLAB_ROOT)/rtw/c/ert -IC:/PROGRA~3/MATLAB/SUPPOR~1/R2020b/toolbox/target/SUPPOR~1/tic2000/inc -I$(MATLAB_ROOT)/toolbox/shared/can/src/scanutil -IC:/PROGRA~3/MATLAB/SUPPOR~1/R2020b/toolbox/target/SUPPOR~1/tic2000/src -IC:/PROGRA~3/MATLAB/SUPPOR~1/R2020b/toolbox/shared/SUPPOR~1/tic2000/src -IC:/PROGRA~3/MATLAB/SUPPOR~1/R2020b/toolbox/shared/SUPPOR~1/tic2000/inc -IC:/PROGRA~3/MATLAB/SUPPOR~1/R2020b/toolbox/target/shared/EXTERN~1/include -I$(MATLAB_ROOT)/toolbox/rtw/targets/common/can/blocks/tlc_c

INCLUDES = $(INCLUDES_BUILDINFO)

###########################################################################
## DEFINES
###########################################################################

DEFINES_ = -D__MW_TARGET_USE_HARDWARE_RESOURCES_H__
DEFINES_BUILD_ARGS = -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DTERMFCN=1 -DONESTEPFCN=1 -DMAT_FILE=0 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=0
DEFINES_CUSTOM = 
DEFINES_OPTS = -DTID01EQ=0
DEFINES_SKIPFORSIL = -DDAEMON_MODE=1 -DXCP_CUSTOM_PLATFORM -DMW_PIL_SCIFIFOLEN=16 -DSTACK_SIZE=1024 -DRT -DF28335 -DBOOT_FROM_FLASH=1 -DMW_FAST_RTS_INCLUDED=0
DEFINES_STANDARD = -DMODEL=adc_oku -DNUMST=1 -DNCSTATES=0 -DHAVESTDIO -DMODEL_HAS_DYNAMICALLY_LOADED_SFCNS=0

DEFINES = $(DEFINES_) $(DEFINES_BUILD_ARGS) $(DEFINES_CUSTOM) $(DEFINES_OPTS) $(DEFINES_SKIPFORSIL) $(DEFINES_STANDARD)

###########################################################################
## SOURCE FILES
###########################################################################

SRCS = $(START_DIR)/adc_oku_ert_rtw/MW_c28xx_board.c $(START_DIR)/adc_oku_ert_rtw/MW_c28xx_adc.c $(START_DIR)/adc_oku_ert_rtw/MW_c28xx_csl.c $(START_DIR)/adc_oku_ert_rtw/MW_c28xx_pwm.c $(START_DIR)/adc_oku_ert_rtw/adc_oku.c $(START_DIR)/adc_oku_ert_rtw/adc_oku_data.c C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/c2833xBoard_Realtime_Support.c C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/shared/supportpackages/tic2000/src/MW_c28xGlobalInterrupts.c C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_MemCopy.c C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_CpuTimers.c C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_DefaultIsr.c C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_GlobalVariableDefs.c C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_PieCtrl.c C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_PieVect.c C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_SysCtrl.c C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_usDelay.asm C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_CodeStartBranch.asm C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_ADC_cal.asm C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_DMA.c C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/profiler_Support.c C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/shared/supportpackages/tic2000/src/MW_c28xGPIO.c C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/c2833xSchedulerTimer0.c C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_Adc.c

MAIN_SRC = $(START_DIR)/adc_oku_ert_rtw/ert_main.c

ALL_SRCS = $(SRCS) $(MAIN_SRC)

###########################################################################
## OBJECTS
###########################################################################

OBJS = MW_c28xx_board.obj MW_c28xx_adc.obj MW_c28xx_csl.obj MW_c28xx_pwm.obj adc_oku.obj adc_oku_data.obj c2833xBoard_Realtime_Support.obj MW_c28xGlobalInterrupts.obj DSP2833x_MemCopy.obj DSP2833x_CpuTimers.obj DSP2833x_DefaultIsr.obj DSP2833x_GlobalVariableDefs.obj DSP2833x_PieCtrl.obj DSP2833x_PieVect.obj DSP2833x_SysCtrl.obj DSP2833x_usDelay.obj DSP2833x_CodeStartBranch.obj DSP2833x_ADC_cal.obj DSP2833x_DMA.obj profiler_Support.obj MW_c28xGPIO.obj c2833xSchedulerTimer0.obj DSP2833x_Adc.obj

MAIN_OBJ = ert_main.obj

ALL_OBJS = $(OBJS) $(MAIN_OBJ)

###########################################################################
## PREBUILT OBJECT FILES
###########################################################################

PREBUILT_OBJS = 

###########################################################################
## LIBRARIES
###########################################################################

LIBS = C:/ti/controlSUITE/libs/math/FPUfastRTS/V100/lib/rts2800_fpu32_fast_supplement.lib C:/ProgramData/MATLAB/SupportPackages/R2020b/3P.instrset/tic2000codegentools.instrset/ti-cgt-c2000_18.12.2.LTS/lib/rts2800_fpu32.lib C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/shared/supportpackages/tic2000/rtlib/IQmath_fpu32.lib C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/c2833xPeripherals.cmd $(MATLAB_ROOT)/toolbox/target/extensions/processor/tic2000/lib/SFO_TI_Build_V5_fpu.lib C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/c28335.cmd

###########################################################################
## SYSTEM LIBRARIES
###########################################################################

SYSTEM_LIBS = 

###########################################################################
## ADDITIONAL TOOLCHAIN FLAGS
###########################################################################

#---------------
# C Compiler
#---------------

CFLAGS_SKIPFORSIL = -v28 --float_support=fpu32 -ml -DF28335 -DBOOT_FROM_FLASH=1
CFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CFLAGS += $(CFLAGS_SKIPFORSIL) $(CFLAGS_BASIC)

#-----------------
# C++ Compiler
#-----------------

CPPFLAGS_SKIPFORSIL = -v28 --float_support=fpu32 -ml -DF28335 -DBOOT_FROM_FLASH=1
CPPFLAGS_BASIC = $(DEFINES) $(INCLUDES)

CPPFLAGS += $(CPPFLAGS_SKIPFORSIL) $(CPPFLAGS_BASIC)

#---------------
# C++ Linker
#---------------

CPP_LDFLAGS_SKIPFORSIL = --define F28335 --define PWM_DMAACCESS=0 --define BOOT_FROM_FLASH=1 --define BOOT_USING_BL=0

CPP_LDFLAGS += $(CPP_LDFLAGS_SKIPFORSIL)

#------------------------------
# C++ Shared Library Linker
#------------------------------

CPP_SHAREDLIB_LDFLAGS_SKIPFORSIL = --define F28335 --define PWM_DMAACCESS=0 --define BOOT_FROM_FLASH=1 --define BOOT_USING_BL=0

CPP_SHAREDLIB_LDFLAGS += $(CPP_SHAREDLIB_LDFLAGS_SKIPFORSIL)

#-----------
# Linker
#-----------

LDFLAGS_SKIPFORSIL = --define F28335 --define PWM_DMAACCESS=0 --define BOOT_FROM_FLASH=1 --define BOOT_USING_BL=0

LDFLAGS += $(LDFLAGS_SKIPFORSIL)

#--------------------------
# Shared Library Linker
#--------------------------

SHAREDLIB_LDFLAGS_SKIPFORSIL = --define F28335 --define PWM_DMAACCESS=0 --define BOOT_FROM_FLASH=1 --define BOOT_USING_BL=0

SHAREDLIB_LDFLAGS += $(SHAREDLIB_LDFLAGS_SKIPFORSIL)

###########################################################################
## INLINED COMMANDS
###########################################################################


all :

ifeq ($(PRODUCT_TYPE),"executable")
postbuild : $(PRODUCT_HEX)

$(PRODUCT_HEX): $(PRODUCT)
	@echo "### Invoking postbuild tool "Hex Converter" on "$<"..."
	$(CCSINSTALLDIR)/bin/hex2000 $(OBJCOPYFLAGS_HEX)
	@echo "### Done Invoking postbuild tool "Hex Converter" ..."

endif

ifeq ($(DEPRULES),1) 
ALL_DEPS:=$(patsubst %.obj,%.dep,$(ALL_OBJS))
all:
else
ALL_DEPS:=
endif




-include codertarget_assembly_flags.mk
-include ../codertarget_assembly_flags.mk
-include ../../codertarget_assembly_flags.mk
-include $(ALL_DEPS)


###########################################################################
## PHONY TARGETS
###########################################################################

.PHONY : all build buildobj clean info prebuild postbuild download execute


all : build postbuild
	@echo "### Successfully generated all binary outputs."


build : prebuild $(PRODUCT)


buildobj : prebuild $(OBJS) $(PREBUILT_OBJS) $(LIBS)
	@echo "### Successfully generated all binary outputs."


prebuild : 


postbuild : $(PRODUCT)


download : postbuild
	@echo "### Invoking postbuild tool "Download" ..."
	$(DOWNLOAD) $(DOWNLOAD_FLAGS)
	@echo "### Done invoking postbuild tool."


execute : download
	@echo "### Invoking postbuild tool "Execute" ..."
	$(EXECUTE) $(EXECUTE_FLAGS)
	@echo "### Done invoking postbuild tool."


###########################################################################
## FINAL TARGET
###########################################################################

#-------------------------------------------
# Create a standalone executable            
#-------------------------------------------

$(PRODUCT) : $(OBJS) $(PREBUILT_OBJS) $(LIBS) $(MAIN_OBJ)
	@echo "### Creating standalone executable "$(PRODUCT)" ..."
	$(LD) $(LDFLAGS) --output_file=$(PRODUCT) $(OBJS) $(MAIN_OBJ) $(LIBS) $(SYSTEM_LIBS) $(TOOLCHAIN_LIBS)
	@echo "### Created: $(PRODUCT)"


###########################################################################
## INTERMEDIATE TARGETS
###########################################################################

#---------------------
# SOURCE-TO-OBJECT
#---------------------

%.obj : %.cla
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : %.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : %.asm
	$(AS) $(ASFLAGS) --output_file="$@" "$<"


%.obj : %.cpp
	$(CPP) $(CPPFLAGS) --output_file="$@" "$<"


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.cla
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.asm
	$(AS) $(ASFLAGS) --output_file="$@" "$<"


%.obj : $(RELATIVE_PATH_TO_ANCHOR)/%.cpp
	$(CPP) $(CPPFLAGS) --output_file="$@" "$<"


%.obj : $(START_DIR)/%.cla
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(START_DIR)/%.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(START_DIR)/%.asm
	$(AS) $(ASFLAGS) --output_file="$@" "$<"


%.obj : $(START_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) --output_file="$@" "$<"


%.obj : $(START_DIR)/adc_oku_ert_rtw/%.cla
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(START_DIR)/adc_oku_ert_rtw/%.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(START_DIR)/adc_oku_ert_rtw/%.asm
	$(AS) $(ASFLAGS) --output_file="$@" "$<"


%.obj : $(START_DIR)/adc_oku_ert_rtw/%.cpp
	$(CPP) $(CPPFLAGS) --output_file="$@" "$<"


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.cla
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.asm
	$(AS) $(ASFLAGS) --output_file="$@" "$<"


%.obj : $(MATLAB_ROOT)/rtw/c/src/%.cpp
	$(CPP) $(CPPFLAGS) --output_file="$@" "$<"


%.obj : $(MATLAB_ROOT)/simulink/src/%.cla
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(MATLAB_ROOT)/simulink/src/%.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


%.obj : $(MATLAB_ROOT)/simulink/src/%.asm
	$(AS) $(ASFLAGS) --output_file="$@" "$<"


%.obj : $(MATLAB_ROOT)/simulink/src/%.cpp
	$(CPP) $(CPPFLAGS) --output_file="$@" "$<"


MW_c28xx_board.obj : $(START_DIR)/adc_oku_ert_rtw/MW_c28xx_board.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


MW_c28xx_adc.obj : $(START_DIR)/adc_oku_ert_rtw/MW_c28xx_adc.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


MW_c28xx_csl.obj : $(START_DIR)/adc_oku_ert_rtw/MW_c28xx_csl.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


MW_c28xx_pwm.obj : $(START_DIR)/adc_oku_ert_rtw/MW_c28xx_pwm.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


adc_oku.obj : $(START_DIR)/adc_oku_ert_rtw/adc_oku.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


adc_oku_data.obj : $(START_DIR)/adc_oku_ert_rtw/adc_oku_data.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


ert_main.obj : $(START_DIR)/adc_oku_ert_rtw/ert_main.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


c2833xBoard_Realtime_Support.obj : C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/c2833xBoard_Realtime_Support.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


MW_c28xGlobalInterrupts.obj : C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/shared/supportpackages/tic2000/src/MW_c28xGlobalInterrupts.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


DSP2833x_MemCopy.obj : C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_MemCopy.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


DSP2833x_CpuTimers.obj : C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_CpuTimers.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


DSP2833x_DefaultIsr.obj : C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_DefaultIsr.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


DSP2833x_GlobalVariableDefs.obj : C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_GlobalVariableDefs.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


DSP2833x_PieCtrl.obj : C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_PieCtrl.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


DSP2833x_PieVect.obj : C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_PieVect.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


DSP2833x_SysCtrl.obj : C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_SysCtrl.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


DSP2833x_usDelay.obj : C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_usDelay.asm
	$(AS) $(ASFLAGS) --output_file="$@" "$<"


DSP2833x_CodeStartBranch.obj : C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_CodeStartBranch.asm
	$(AS) $(ASFLAGS) --output_file="$@" "$<"


DSP2833x_ADC_cal.obj : C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_ADC_cal.asm
	$(AS) $(ASFLAGS) --output_file="$@" "$<"


DSP2833x_DMA.obj : C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_DMA.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


profiler_Support.obj : C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/profiler_Support.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


MW_c28xGPIO.obj : C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/shared/supportpackages/tic2000/src/MW_c28xGPIO.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


c2833xSchedulerTimer0.obj : C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/c2833xSchedulerTimer0.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


DSP2833x_Adc.obj : C:/ProgramData/MATLAB/SupportPackages/R2020b/toolbox/target/supportpackages/tic2000/src/DSP2833x_Adc.c
	$(CC) $(CFLAGS) --output_file="$@" "$<"


###########################################################################
## DEPENDENCIES
###########################################################################

$(ALL_OBJS) : rtw_proj.tmw $(MAKEFILE)


###########################################################################
## MISCELLANEOUS TARGETS
###########################################################################

info : 
	@echo "### PRODUCT = $(PRODUCT)"
	@echo "### PRODUCT_TYPE = $(PRODUCT_TYPE)"
	@echo "### BUILD_TYPE = $(BUILD_TYPE)"
	@echo "### INCLUDES = $(INCLUDES)"
	@echo "### DEFINES = $(DEFINES)"
	@echo "### ALL_SRCS = $(ALL_SRCS)"
	@echo "### ALL_OBJS = $(ALL_OBJS)"
	@echo "### LIBS = $(LIBS)"
	@echo "### MODELREF_LIBS = $(MODELREF_LIBS)"
	@echo "### SYSTEM_LIBS = $(SYSTEM_LIBS)"
	@echo "### TOOLCHAIN_LIBS = $(TOOLCHAIN_LIBS)"
	@echo "### ASFLAGS = $(ASFLAGS)"
	@echo "### CFLAGS = $(CFLAGS)"
	@echo "### LDFLAGS = $(LDFLAGS)"
	@echo "### SHAREDLIB_LDFLAGS = $(SHAREDLIB_LDFLAGS)"
	@echo "### CPPFLAGS = $(CPPFLAGS)"
	@echo "### CPP_LDFLAGS = $(CPP_LDFLAGS)"
	@echo "### CPP_SHAREDLIB_LDFLAGS = $(CPP_SHAREDLIB_LDFLAGS)"
	@echo "### ARFLAGS = $(ARFLAGS)"
	@echo "### MEX_CFLAGS = $(MEX_CFLAGS)"
	@echo "### MEX_CPPFLAGS = $(MEX_CPPFLAGS)"
	@echo "### MEX_LDFLAGS = $(MEX_LDFLAGS)"
	@echo "### MEX_CPPLDFLAGS = $(MEX_CPPLDFLAGS)"
	@echo "### OBJCOPYFLAGS_HEX = $(OBJCOPYFLAGS_HEX)"
	@echo "### DOWNLOAD_FLAGS = $(DOWNLOAD_FLAGS)"
	@echo "### EXECUTE_FLAGS = $(EXECUTE_FLAGS)"
	@echo "### MAKE_FLAGS = $(MAKE_FLAGS)"


clean : 
	$(ECHO) "### Deleting all derived files..."
	$(RM) $(subst /,\,$(PRODUCT))
	$(RM) $(subst /,\,$(ALL_OBJS))
	$(RM) *Object
	$(ECHO) "### Deleted all derived files."


