################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
cpu01-bootROM/source/usb_dfu/bl_usb.obj: C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/usb_dfu/bl_usb.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_headers/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_common/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_common/include/driverlib_inc" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/include/common_headers" --gcc --define=CPU1 --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="cpu01-bootROM/source/usb_dfu/bl_usb.pp" --obj_directory="cpu01-bootROM/source/usb_dfu" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

cpu01-bootROM/source/usb_dfu/bl_usbfuncs.obj: C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/source/usb_dfu/bl_usbfuncs.c $(GEN_OPTS) $(GEN_SRCS)
	@echo 'Building file: $<'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccsv5/tools/compiler/c2000_6.1.0/bin/cl2000" -v28 -ml -mt -g --include_path="C:/ti/ccsv5/tools/compiler/c2000_6.1.0/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_headers/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_common/include" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_common/include/driverlib_inc" --include_path="C:/work/grepos/bootrom/Boot_ROM/F2837x_bootROM/F2837x_bootROM_dev/F2837x_bootROM/cpu01-bootROM/include/common_headers" --gcc --define=CPU1 --diag_warning=225 --display_error_number --asm_listing --preproc_with_compile --preproc_dependency="cpu01-bootROM/source/usb_dfu/bl_usbfuncs.pp" --obj_directory="cpu01-bootROM/source/usb_dfu" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


