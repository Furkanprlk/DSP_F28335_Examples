################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
F2837x_common/source/F2837x_Gpio.obj: C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_common/source/F2837x_Gpio.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_headers/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_common/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_common/include/driverlib_inc" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/include/common_headers" --gcc --define=CPU2 --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="F2837x_common/source/F2837x_Gpio.pp" --obj_directory="F2837x_common/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

F2837x_common/source/F2837x_Ipc.obj: C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_common/source/F2837x_Ipc.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt --float_support=fpu32 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_headers/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_common/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_common/include/driverlib_inc" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/include/common_headers" --gcc --define=CPU2 --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="F2837x_common/source/F2837x_Ipc.pp" --obj_directory="F2837x_common/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


