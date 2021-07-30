################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
cpu02-bootROM/Cla_Data_Rom/source/cla_rom_version.obj: C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/Cla_Data_Rom/source/cla_rom_version.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.6/bin/cl2000" -v28 -ml --float_support=fpu32 --vcu_support=vcu0 -g --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.6/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_headers/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_common/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_common/include/driverlib_inc" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/tables" --gcc --define=CPU2 --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="cpu02-bootROM/Cla_Data_Rom/source/cla_rom_version.pp" --obj_directory="cpu02-bootROM/Cla_Data_Rom/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

cpu02-bootROM/Cla_Data_Rom/source/fft_twiddle_bit_reverse.obj: C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/Cla_Data_Rom/source/fft_twiddle_bit_reverse.asm $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"c:/ti/ccsv6/tools/compiler/c2000_6.2.6/bin/cl2000" -v28 -ml --float_support=fpu32 --vcu_support=vcu0 -g --include_path="c:/ti/ccsv6/tools/compiler/c2000_6.2.6/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_headers/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_common/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_common/include/driverlib_inc" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM-REVB/F2837x_bootROM_dev/F2837x_bootROM/cpu02-bootROM/source/tables" --gcc --define=CPU2 --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="cpu02-bootROM/Cla_Data_Rom/source/fft_twiddle_bit_reverse.pp" --obj_directory="cpu02-bootROM/Cla_Data_Rom/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


