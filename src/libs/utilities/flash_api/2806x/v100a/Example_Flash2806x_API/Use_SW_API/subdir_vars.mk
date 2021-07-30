################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CMD_SRCS += \
../Example_Flash2806x_SW_API.cmd \
C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_headers/cmd/F2806x_Headers_nonBIOS.cmd 

LIB_SRCS += \
C:/ti/controlSUITE/libs/utilities/flash_api/2806x/v100a/lib/Flash2806x_API_V100.lib 

ASM_SRCS += \
../Example_Flash2806x_CsmKeys.asm \
C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_common/source/F2806x_CodeStartBranch.asm \
C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_common/source/F2806x_usDelay.asm 

C_SRCS += \
../Example_Flash2806x_API.c \
C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_headers/source/F2806x_GlobalVariableDefs.c \
C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_common/source/F2806x_SysCtrl.c 

OBJS += \
./Example_Flash2806x_API.obj \
./Example_Flash2806x_CsmKeys.obj \
./F2806x_CodeStartBranch.obj \
./F2806x_GlobalVariableDefs.obj \
./F2806x_SysCtrl.obj \
./F2806x_usDelay.obj 

ASM_DEPS += \
./Example_Flash2806x_CsmKeys.pp \
./F2806x_CodeStartBranch.pp \
./F2806x_usDelay.pp 

C_DEPS += \
./Example_Flash2806x_API.pp \
./F2806x_GlobalVariableDefs.pp \
./F2806x_SysCtrl.pp 

C_DEPS__QUOTED += \
"Example_Flash2806x_API.pp" \
"F2806x_GlobalVariableDefs.pp" \
"F2806x_SysCtrl.pp" 

OBJS__QUOTED += \
"Example_Flash2806x_API.obj" \
"Example_Flash2806x_CsmKeys.obj" \
"F2806x_CodeStartBranch.obj" \
"F2806x_GlobalVariableDefs.obj" \
"F2806x_SysCtrl.obj" \
"F2806x_usDelay.obj" 

ASM_DEPS__QUOTED += \
"Example_Flash2806x_CsmKeys.pp" \
"F2806x_CodeStartBranch.pp" \
"F2806x_usDelay.pp" 

C_SRCS__QUOTED += \
"../Example_Flash2806x_API.c" \
"C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_headers/source/F2806x_GlobalVariableDefs.c" \
"C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_common/source/F2806x_SysCtrl.c" 

ASM_SRCS__QUOTED += \
"../Example_Flash2806x_CsmKeys.asm" \
"C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_common/source/F2806x_CodeStartBranch.asm" \
"C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_common/source/F2806x_usDelay.asm" 


