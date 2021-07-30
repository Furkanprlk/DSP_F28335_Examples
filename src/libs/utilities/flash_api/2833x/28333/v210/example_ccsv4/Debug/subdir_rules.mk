################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
DSP2833x_CSMPasswords.obj: C:/ti/controlSUITE/device_support/f2833x/v132/DSP2833x_common/source/DSP2833x_CSMPasswords.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/controlSUITE/libs/utilities/flash_api/2833x/28333/v210/include" --include_path="C:/ti/controlSUITE/device_support/f2833x/v132/DSP2833x_Headers/include" --define="_DEBUG" --define="LARGE_MODEL" -g --diag_warning=225 --issue_remarks --quiet --preproc_with_compile --preproc_dependency="DSP2833x_CSMPasswords.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

DSP2833x_CodeStartBranch.obj: C:/ti/controlSUITE/device_support/f2833x/v132/DSP2833x_common/source/DSP2833x_CodeStartBranch.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/controlSUITE/libs/utilities/flash_api/2833x/28333/v210/include" --include_path="C:/ti/controlSUITE/device_support/f2833x/v132/DSP2833x_Headers/include" --define="_DEBUG" --define="LARGE_MODEL" -g --diag_warning=225 --issue_remarks --quiet --preproc_with_compile --preproc_dependency="DSP2833x_CodeStartBranch.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Example_Flash2833x_API.obj: C:/ti/controlSUITE/libs/utilities/flash_api/2833x/28333/v210/example_ccsv4/Example_Flash2833x_API.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/controlSUITE/libs/utilities/flash_api/2833x/28333/v210/include" --include_path="C:/ti/controlSUITE/device_support/f2833x/v132/DSP2833x_Headers/include" --define="_DEBUG" --define="LARGE_MODEL" -g --diag_warning=225 --issue_remarks --quiet --preproc_with_compile --preproc_dependency="Example_Flash2833x_API.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Example_Flash2833x_CsmKeys.obj: C:/ti/controlSUITE/libs/utilities/flash_api/2833x/28333/v210/example_ccsv4/Example_Flash2833x_CsmKeys.asm $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/controlSUITE/libs/utilities/flash_api/2833x/28333/v210/include" --include_path="C:/ti/controlSUITE/device_support/f2833x/v132/DSP2833x_Headers/include" --define="_DEBUG" --define="LARGE_MODEL" -g --diag_warning=225 --issue_remarks --quiet --preproc_with_compile --preproc_dependency="Example_Flash2833x_CsmKeys.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Example_Flash2833x_GlobalVariableDefs.obj: C:/ti/controlSUITE/libs/utilities/flash_api/2833x/28333/v210/example_ccsv4/Example_Flash2833x_GlobalVariableDefs.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/ti/ccsv7/tools/compiler/ti-cgt-c2000_16.9.1.LTS/include" --include_path="C:/ti/controlSUITE/libs/utilities/flash_api/2833x/28333/v210/include" --include_path="C:/ti/controlSUITE/device_support/f2833x/v132/DSP2833x_Headers/include" --define="_DEBUG" --define="LARGE_MODEL" -g --diag_warning=225 --issue_remarks --quiet --preproc_with_compile --preproc_dependency="Example_Flash2833x_GlobalVariableDefs.d" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


