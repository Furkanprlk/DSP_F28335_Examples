################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
F2837x_headers/source/F2837x_GlobalVariableDefs.obj: C:/work/grepos/bootrom_local/Boot_ROM/F2837x_bootROM/customer_relelases/delta_rev0_relelase_oct2_2013/F2837x_rev0_bootROM_source/F2837x_headers/source/F2837x_GlobalVariableDefs.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.3/bin/cl2000" -v28 -ml --float_support=fpu32 -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.3/include" --include_path="C:/work/grepos/bootrom_local/Boot_ROM/F2837x_bootROM/customer_relelases/delta_rev0_relelase_oct2_2013/F2837x_rev0_bootROM_source/F2837x_bootROM/cpu01-bootROM/include" --include_path="C:/work/grepos/bootrom_local/Boot_ROM/F2837x_bootROM/customer_relelases/delta_rev0_relelase_oct2_2013/F2837x_rev0_bootROM_source/F2837x_headers/include" --include_path="C:/work/grepos/bootrom_local/Boot_ROM/F2837x_bootROM/customer_relelases/delta_rev0_relelase_oct2_2013/F2837x_rev0_bootROM_source/F2837x_common/include" --include_path="C:/work/grepos/bootrom_local/Boot_ROM/F2837x_bootROM/customer_relelases/delta_rev0_relelase_oct2_2013/F2837x_rev0_bootROM_source/F2837x_common/include/driverlib_inc" --include_path="C:/work/grepos/bootrom_local/Boot_ROM/F2837x_bootROM/customer_relelases/delta_rev0_relelase_oct2_2013/F2837x_rev0_bootROM_source/F2837x_bootROM/cpu01-bootROM/source/tables" --gcc --define=CPU1 --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="F2837x_headers/source/F2837x_GlobalVariableDefs.pp" --obj_directory="F2837x_headers/source" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


