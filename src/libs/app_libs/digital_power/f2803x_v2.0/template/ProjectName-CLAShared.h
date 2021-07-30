//----------------------------------------------------------------------------------
//	FILE:			{ProjectName}-DPL-CLA.asm
//
//	Description:	CLA and CPU shared variables and constants 
//  
//   Revision/ Version: See {ProjectName}-Main.c
//----------------------------------------------------------------------------------
#ifndef CLA_SHARED_H
#define CLA_SHARED_H

#ifdef __cplusplus
extern "C" {
#endif


  #include "IQmathLib.h"
   // gives visibility of peripheral header files to CLA
  #include "PeripheralHeaderIncludes.h"
  // gives visibility of Incremental Build Options to CLA
  #include "ProjectName-Settings.h"
  #include "DSP2803x_Cla_defines.h"
  
      
// The following function is run by the CPU to 
// initialize the inputs for the CLA 
  
  extern void DPL_CLAInit(void);  
  extern interrupt void DPL_ISR(void);  

//
// The following are symbols defined in the CLA assembly code
// Including them in the shared header file makes them
// .global and the main CPU can make use of them.
//

  extern Uint32 Cla1Task1;
  extern Uint32 Cla1Task2;
  extern Uint32 Cla1Task3;
  extern Uint32 Cla1Task4;
  extern Uint32 Cla1Task5;
  extern Uint32 Cla1Task6;
  extern Uint32 Cla1Task7;
  extern Uint32 Cla1Task8;
  extern Uint32 Cla1Prog_Start;
  extern Uint32 Cla1T1End;
  extern Uint32 Cla1T2End;
  extern Uint32 Cla1T3End;
  extern Uint32 Cla1T4End;
  extern Uint32 Cla1T5End;
  extern Uint32 Cla1T6End;
  extern Uint32 Cla1T7End;
  extern Uint32 Cla1T8End;

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif  // end of CLA_SHARED definition
