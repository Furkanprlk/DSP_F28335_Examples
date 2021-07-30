################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
source/PM_sincos_adcisr.obj: ../source/PM_sincos_adcisr.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -mt -ml --vcu_support=vcu2 --cla_support=cla1 --tmu_support=tmu0 --float_support=fpu32 --opt_for_speed=3 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/ti/controlSUITE/libs/app_libs/position_manager/v01_00_00_00/sincos/examples/PM_sincos_example/include" --include_path="C:/ti/controlSUITE/device_support/F2837xD/v170/F2837xD_headers/include" --include_path="C:/ti/controlSUITE/libs/app_libs/position_manager/v01_00_00_00/sincos/Float/include" --include_path="C:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="C:/ti/controlSUITE/device_support/F2837xD/v170/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --diag_wrap=off --display_error_number --diag_suppress=16002 --diag_suppress=303 --preproc_with_compile --preproc_dependency="source/PM_sincos_adcisr.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/PM_sincos_main.obj: ../source/PM_sincos_main.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -mt -ml --vcu_support=vcu2 --cla_support=cla1 --tmu_support=tmu0 --float_support=fpu32 --opt_for_speed=3 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/ti/controlSUITE/libs/app_libs/position_manager/v01_00_00_00/sincos/examples/PM_sincos_example/include" --include_path="C:/ti/controlSUITE/device_support/F2837xD/v170/F2837xD_headers/include" --include_path="C:/ti/controlSUITE/libs/app_libs/position_manager/v01_00_00_00/sincos/Float/include" --include_path="C:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="C:/ti/controlSUITE/device_support/F2837xD/v170/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --diag_wrap=off --display_error_number --diag_suppress=16002 --diag_suppress=303 --preproc_with_compile --preproc_dependency="source/PM_sincos_main.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

source/sincos.obj: ../source/sincos.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/bin/cl2000" -v28 -mt -ml --vcu_support=vcu2 --cla_support=cla1 --tmu_support=tmu0 --float_support=fpu32 --opt_for_speed=3 --include_path="C:/ti/ccsv6/tools/compiler/ti-cgt-c2000_6.4.9/include" --include_path="C:/ti/controlSUITE/libs/app_libs/position_manager/v01_00_00_00/sincos/examples/PM_sincos_example/include" --include_path="C:/ti/controlSUITE/device_support/F2837xD/v170/F2837xD_headers/include" --include_path="C:/ti/controlSUITE/libs/app_libs/position_manager/v01_00_00_00/sincos/Float/include" --include_path="C:/ti/controlSUITE/libs/math/IQmath/v160/include" --include_path="C:/ti/controlSUITE/device_support/F2837xD/v170/F2837xD_common/include" -g --define=CPU1 --diag_warning=225 --diag_wrap=off --display_error_number --diag_suppress=16002 --diag_suppress=303 --preproc_with_compile --preproc_dependency="source/sincos.pp" --obj_directory="source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


