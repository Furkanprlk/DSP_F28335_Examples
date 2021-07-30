
//###########################################################################
//
// FILE:   F28x_Project.h
//
// TITLE:  F28x Project Headerfile and Examples Include File
//
//###########################################################################
// $TI Release:  $
// $Release Date:  $
//###########################################################################

#ifndef F28X_PROJECT_H
#define F28X_PROJECT_H

#if (!defined(CPU1) && !defined(CPU2))
#error "You must define CPU1 or CPU2 in your project properties.  Otherwise, the offsets in your header files will be inaccurate."
#endif

#if (defined(CPU1) && defined(CPU2))
#error "You have defined both CPU1 and CPU2 in your project properties.  Only a single CPU should be defined."
#endif

#include "F2837x_Cla_typedefs.h"  // F2837x CLA Type definitions
#include "F2837x_Device.h"        // F2837x Headerfile Include File
#include "F2837x_Examples.h"    // F2837x Examples Include File


#endif  // end of F28X_PROJECT_H definition

