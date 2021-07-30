// TI File $Revision: /main/1 $
// Checkin $Date: January 22, 2009   16:46:29 $
//###########################################################################
//
// FILE:    DSP2803x_BootVars.h
//
// TITLE:   DSP2803x Boot Variable Definitions.
//
// NOTES:
//
//###########################################################################
// $TI Release: TMS320x2803x Boot ROM V1.0 $
// $Release Date: January 22, 2009 $
//###########################################################################

#ifndef DSP2803x_BOOT_VARS_H
#define DSP2803x_BOOT_VARS_H

#ifdef __cplusplus
extern "C" {
#endif



//---------------------------------------------------------------------------
// External Boot ROM variable definitions:
//
extern Uint16 EmuKey;
extern Uint16 EmuBMode;
extern Uint32 Flash_CPUScaleFactor;
extern void (*Flash_CallbackPtr) (void);

#ifdef __cplusplus
}
#endif /* extern "C" */

#endif  // end of DSP2803x_BOOT_VARS_H definition

//===========================================================================
// End of file.
//===========================================================================

