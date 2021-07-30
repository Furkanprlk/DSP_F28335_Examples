################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
Example_Flash2806x_API.obj: ../Example_Flash2806x_API.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=softlib --vcu_support=vcu0 -Ooff --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_common/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_headers/include" --define=_INLINE --define=SW_API --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Example_Flash2806x_API.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Example_Flash2806x_CsmKeys.obj: ../Example_Flash2806x_CsmKeys.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=softlib --vcu_support=vcu0 -Ooff --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_common/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_headers/include" --define=_INLINE --define=SW_API --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="Example_Flash2806x_CsmKeys.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_CodeStartBranch.obj: C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_common/source/F2806x_CodeStartBranch.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=softlib --vcu_support=vcu0 -Ooff --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_common/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_headers/include" --define=_INLINE --define=SW_API --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="F2806x_CodeStartBranch.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_GlobalVariableDefs.obj: C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_headers/source/F2806x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=softlib --vcu_support=vcu0 -Ooff --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_common/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_headers/include" --define=_INLINE --define=SW_API --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="F2806x_GlobalVariableDefs.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_SysCtrl.obj: C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_common/source/F2806x_SysCtrl.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=softlib --vcu_support=vcu0 -Ooff --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_common/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_headers/include" --define=_INLINE --define=SW_API --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="F2806x_SysCtrl.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2806x_usDelay.obj: C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_common/source/F2806x_usDelay.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/bin/cl2000" -v28 -ml -mt --cla_support=cla0 --float_support=softlib --vcu_support=vcu0 -Ooff --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.4/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_common/include" --include_path="C:/ti/controlSUITE/device_support/f2806x/v140/F2806x_headers/include" --define=_INLINE --define=SW_API --diag_warning=225 --display_error_number --diag_wrap=off --preproc_with_compile --preproc_dependency="F2806x_usDelay.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


